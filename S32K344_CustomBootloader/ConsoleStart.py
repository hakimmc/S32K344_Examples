import serial
import time
import random
import string

def main():
    com_port = "COM5"
    baud_rate = 9600
    
    try:
        ser = serial.Serial(com_port, baud_rate, timeout=1)
        print(f"Connected: {com_port} ({baud_rate} baud)")
        
        while True:
            letters = string.ascii_lowercase
            response = ''.join(random.choice(letters) for i in range(24))
            ser.write(response.encode('utf-8'))
            print(f"Sent: {response.strip()}")
            feedback = ser.read_until().decode('utf-8', errors='ignore').strip()
            print(f"Received feedback: {feedback}")
            time.sleep(1)

    except serial.SerialException as e:
        print(f"Serial port error: {e}")
    except Exception as e:
        print(f"Unknown error: {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial port closed.")

if __name__ == "__main__":
    main()