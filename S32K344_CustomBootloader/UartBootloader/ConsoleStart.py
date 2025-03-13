import serial
import time
import sys

# Seri port ayarları
SERIAL_PORT = "COM3"  # Linux/Mac için: "/dev/ttyUSB0"
BAUD_RATE = 9600
TIMEOUT = 5  # Timeout süresi (saniye cinsinden)

# Protokol Mesajları
START_MSG = b'!OTTOWAKE!'  # Başlangıç mesajı
READY_MSG = b'!STR'   # Cihazdan gelecek başlama sinyali
NEXT_MSG = b'!NXT'    # Cihazdan her paket öncesi gelecek sinyal
END_MSG = b'!OTTOJUMP!'    # Gönderim bitiş mesajı
SKIP_MSG = b'!SKIPJUMP!'   # Tamamen sıfır olan bloklar için mesaj

# CRC Hesaplama Fonksiyonu (Toplam % 255)
def calculate_crc(data):
    return (ord('!') + sum(data)) % 255

# Bin dosyasını oku ve parçala (8 byte + 1 byte CRC)
def read_bin_file(file_path):
    with open(file_path, "rb") as f:
        file_data = f.read()
        total_size = len(file_data)
        chunks = [file_data[i:i+8] for i in range(0, total_size, 8)]
        
        for index, chunk in enumerate(chunks):
            # Eğer chunk tamamen sıfırlardan oluşuyorsa, "!SKIP" mesajını gönder
            if all(byte == 0 for byte in chunk):
                yield SKIP_MSG, index, len(chunks)
            else:
                # Eğer son parça eksikse, 8 bayta tamamla
                if len(chunk) < 8:
                    chunk = chunk.ljust(8, b'\x00')
                crc = calculate_crc(chunk)
                packet = b'!' + chunk + bytes([crc])
                yield packet, index, len(chunks)

# UART okuma fonksiyonu
def wait_for_message(ser, expected_msg):
    start_time = time.time()
    while time.time() - start_time < TIMEOUT:
        response = ser.read(len(expected_msg))
        if response == expected_msg:
            return True
    return False

# Yükleme animasyonu ve veri gösterimi
def print_progress_bar(progress, total, packet, bar_length=40):
    percent = (progress / total) * 100
    bar_filled = int(bar_length * progress / total)
    bar = "#" * bar_filled + "-" * (bar_length - bar_filled)
    data_repr = "[!]{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} [{:02X}]".format(*packet[1:], packet[-1])
    sys.stdout.write(f"\r[{bar}] {percent:.2f}% {data_repr}")
    sys.stdout.flush()

# UART ile dosyayı gönder
def send_file(file_path):
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        time.sleep(2)  # UART başlatma süresi

        # Adım 1: "!OTTO" mesajı gönder
        while True:
            ser.write(START_MSG)
            print("Sent: !OTTO")
            if wait_for_message(ser, READY_MSG):
                break
            print("Retrying: !OTTO")
        
        print("Received: !STR")

        # Adım 3: Bin dosyasını gönder
        for packet, index, total in read_bin_file(file_path):
            while True:
                ser.write(packet)
                print_progress_bar(index + 1, total, packet)
                if wait_for_message(ser, NEXT_MSG):
                    break
                print("Retrying packet", index + 1)

        # Adım 4: Tüm veriler yollandıktan sonra tekrar "!OTTO" gönder
        while True:
            ser.write(END_MSG)
            print("Sent: !OTTOJUMP")
            break

if __name__ == "__main__":
    file_path = "firmware.bin"  # Gönderilecek bin dosyası
    send_file(file_path)
    print("\nDosya gönderimi tamamlandı.")
