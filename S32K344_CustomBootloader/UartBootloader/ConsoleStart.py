import serial
import time
import sys

# Seri port ayarları
SERIAL_PORT = "COM5"  # Linux/Mac için: "/dev/ttyUSB0"
BAUD_RATE = 9600

# Protokol Mesajları
START_MSG = b'!OTTO'  # Başlangıç mesajı
READY_MSG = b'!STR'   # Cihazdan gelecek başlama sinyali
NEXT_MSG = b'!NXT'    # Cihazdan her paket öncesi gelecek sinyal
END_MSG = b'!OTTO'    # Gönderim bitiş mesajı
SKIP_MSG = b'!SKIPJUMP'   # Tamamen sıfır olan bloklar için mesaj

# CRC Hesaplama Fonksiyonu (Toplam % 255)
def calculate_crc(data):
    return sum(data) % 255

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
                yield chunk + bytes([crc]), index, len(chunks)

# UART okuma fonksiyonu
def wait_for_message(ser, expected_msg):
    while True:
        response = ser.read(len(expected_msg))
        if response == expected_msg:
            return

# Yükleme animasyonu
def print_progress_bar(progress, total, bar_length=40):
    percent = (progress / total) * 100
    bar_filled = int(bar_length * progress / total)
    bar = "#" * bar_filled + "-" * (bar_length - bar_filled)
    sys.stdout.write(f"\r[{bar}] {percent:.2f}%")
    sys.stdout.flush()

# UART ile dosyayı gönder
def send_file(file_path):
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        time.sleep(2)  # UART başlatma süresi

        # Adım 1: "!OTTO" mesajı gönder
        ser.write(START_MSG)
        print("Sent: !OTTO")
        
        # Adım 2: "!STR" mesajını bekle
        wait_for_message(ser, READY_MSG)
        print("Received: !STR")

        # Adım 3: Bin dosyasını gönder
        for packet, index, total in read_bin_file(file_path):
            ser.write(packet)
            print_progress_bar(index + 1, total)
            wait_for_message(ser, NEXT_MSG)

        # Adım 4: Tüm veriler yollandıktan sonra tekrar "!OTTO" gönder
        ser.write(END_MSG)
        print("\nSent: !OTTO")

if __name__ == "__main__":
    file_path = "firmware.bin"  # Gönderilecek bin dosyası
    send_file(file_path)
    print("\nDosya gönderimi tamamlandı.")
