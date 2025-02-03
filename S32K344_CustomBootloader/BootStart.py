import time
import serial
import os
import sys
import json
from colorama import Fore, Style, init

init(autoreset=True)

fault = False
uart_port = "COM10"
baudrate = 9600
ser = serial.Serial(uart_port, baudrate, timeout=1)

print(Fore.CYAN + Style.BRIGHT + """
╔═════════════════════════════════════════════════════════════════════════════════════════╗
║   ▄████████  ▄█          ▄████████    ▄████████    ▄█    █▄       ▄████████    ▄████████║
║  ███    ███ ███         ███    ███   ███    ███   ███    ███     ███    ███   ███    ███║
║  ███    █▀  ███         ███    ███   ███    █▀    ███    ███     ███    █▀    ███    ███║
║ ▄███▄▄▄     ███         ███    ███   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄      ▄███▄▄▄▄██▀║
║▀▀███▀▀▀     ███       ▀███████████ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ▀▀███▀▀▀▀▀  ║
║  ███        ███         ███    ███          ███   ███    ███     ███    █▄  ▀███████████║
║  ███        ███▌    ▄   ███    ███    ▄█    ███   ███    ███     ███    ███   ███    ███║
║  ███        █████▄▄██   ███    █▀   ▄████████▀    ███    █▀      ██████████   ███    ███║
║             ▀                                                                 ███    ███║
╚═════════════════════════════════════════════════════════════════════════════════════════╝
""")

def send_bin_file(filename):
    file_size = os.path.getsize(filename)
    start_time = time.time()
    print("Program Executing...")
    time.sleep(1)
    print("Boot Request Send")
    ser.write(b"!OTTO")

    while True:
        if ser.in_waiting > 0:
            response = ser.read(4).strip().decode()
            if response == "!STR":
                break
    
    time.sleep(1)
    print("Waking Up")
  
    with open(filename, "rb") as bin_file:
        index = 0
        bytes_sent = 0
        total_blocks = file_size // 4
        progress_bar_length = 50
        spinner = ['|', '/', '-', '\\']
        print(Fore.GREEN + "Flash Programming")
        
        while True:
            if fault == True:
                break
            data = bin_file.read(4)
            if not data:
                break
            
            byte_array = bytearray(data)
            ser.write(byte_array)
            index += 1
            bytes_sent += len(data)
            
            blocks_sent = (bytes_sent // 4)
            num_blocks = int((blocks_sent / total_blocks) * progress_bar_length)
            bar = "#" * num_blocks + "-" * (progress_bar_length - num_blocks)
            spinner_char = spinner[index % len(spinner)]
            
            sys.stdout.write(
                f"\r{Fore.YELLOW}[{bar}] {Fore.MAGENTA}{spinner_char} % {num_blocks * 2}"
            )
            sys.stdout.flush()

            time.sleep(0.01)
            
            while True:
                if ser.in_waiting > 0:
                    response = ser.read(3).strip().decode()
                    if response == "!NXT":
                        break
                    if response == "!ERR":
                        fault = True
                        break
                    

    end_time = time.time()
    elapsed_time = end_time - start_time
    
    print(Fore.GREEN + "\nFlash Programming Done!")
    print(Fore.BLUE + f"Flash Time: {elapsed_time:.2f} seconds.")
    ser.write(b"!OTTO")

filename = "app.bin"
send_bin_file(filename)
