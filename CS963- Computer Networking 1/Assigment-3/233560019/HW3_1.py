import random
from crc_encoder import encode_data, xor, mod2div
from colorama import init, Fore, Back, Style

# Initialize colorama
init()
#pip install colorama
#############################
k = 10  # Number of bits in data block 
n = 17  # Total number of bits in frame (n > k)
crc_divisor = '110101'  # Example CRC divisor
############################

def introduce_error(frame):
    #frame length
    frame_l=len(frame)
    # Simulate error by flipping a bit in the frame
    #introduce error at different positions by genrating random number for error
    # Generate a random number between 1 and 10
    index_error = random.randint(1, frame_l-1)
    frame = frame[:index_error] + ('0' if frame[index_error] == '1' else '1') + frame[index_error+1:]
    return frame

def detect_error(frame, key):
    # Check if the remainder after division is zero
    remainder = mod2div(frame, key)
    return int(remainder, 2) != 0

########################################
print(f"{Style.BRIGHT + Fore.YELLOW}+++++++++++++++++++++++++ CRC Using MODUL0 2 Arithmetic +++++++++++++++++ {Style.RESET_ALL}")
print(f"{Style.BRIGHT + Fore.RED}=============== TEST RUN =========================== {Style.RESET_ALL}")
# Generating random data block 2
for i in range(1,3):
    print(f"Validating for {i} input data")
    random_range=random.randint(5, 17)
    data_block_1 = ''.join(str(random.randint(0, 1)) for _ in range(random_range))
    # Generating random data block 2
    random_range=random.randint(5, 20)
    data_block_2 = ''.join(str(random.randint(0, 1)) for _ in range(random_range))
    print(f"{i}st Input data: {data_block_1}")
    print(f"{i}st Input data length: {len(data_block_1)}")
    frame_1 = encode_data(data_block_1, crc_divisor)
    l_frame_1=len(frame_1)
    l_crc_divisor=len(crc_divisor)
    l_crc_divisor_actual=l_frame_1 - len(data_block_1) + 1
    print(f"{i}st Frame : {frame_1}")
    print(f"{i}st Frame length: {l_frame_1}")
    print(f"crc_divior used: {crc_divisor}")
    print(f"crc_divior length:{l_crc_divisor}")
    if(l_crc_divisor_actual == l_crc_divisor):
        print(f"Genrated CRC pattern is correct for test input {data_block_1}")
    else:
        print(f"Genrated CRC pattern is not correct for test input {data_block_1}")
    print("-------------------------------")
print(f"{Style.BRIGHT + Fore.RED}=============== TEST RUN END =========================== {Style.RESET_ALL}")

print(f"{Fore.GREEN}============= Actual RUN: START ========================== {Style.RESET_ALL}")

#######################################
# Generating random data block
data_block = ''.join(str(random.randint(0, 1)) for _ in range(k))
#data_block = '1101101101'  # Example data block
print(f"Using CRC Divisor P as: {Style.BRIGHT + Fore.YELLOW} {crc_divisor}{Style.RESET_ALL}")
print(f"(a) Generated a message {Style.BRIGHT + Fore.BLUE}{data_block}{Style.RESET_ALL} of k= {Style.BRIGHT + Fore.BLUE}{k}{Style.RESET_ALL} bits")

frame = encode_data(data_block, crc_divisor)
l_frame=len(frame)
print(f"(b) Genrated the corresponding {Style.BRIGHT + Fore.BLUE}{l_frame}{Style.RESET_ALL}-bit frame T as {Style.BRIGHT + Fore.BLUE}{frame}{Style.RESET_ALL} for transmission")

# Introduce error
corrupted_frame =introduce_error(frame)

print(f"(c) Frame with error: {Style.BRIGHT + Fore.BLUE}{corrupted_frame}{Style.RESET_ALL}")
# Check for error detection
error_detected = detect_error(corrupted_frame, crc_divisor)
if error_detected:
    print(f"(d){Style.BRIGHT + Fore.RED} Error detected!!, Frame should be discarded.{Style.RESET_ALL}")
else:
   print(f"(d){Style.BRIGHT + Fore.GREEN}(d) No error detected!!, Frame should be accepted.{Style.RESET_ALL}")



print(f"{Style.BRIGHT + Fore.GREEN}============= Actual RUN: END ========================== {Style.RESET_ALL}")
