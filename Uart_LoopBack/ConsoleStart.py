import serial
import time

def main():
    com_port = "COM5"
    baud_rate = 9600
    
    try:
        ser = serial.Serial(com_port, baud_rate, timeout=1)
        print(f"Connected: {com_port} ({baud_rate} baud)")
        
        while True:
            received_data = ser.read_until().decode('utf-8', errors='ignore').strip()
            
            if received_data == "data":
                response = "!ABCDEFGHIJKLMNOPQRSTUVWX\n"
                ser.write(response.encode('utf-8'))
                print(f"Sent: {response.strip()}")
                
                time.sleep(1)
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