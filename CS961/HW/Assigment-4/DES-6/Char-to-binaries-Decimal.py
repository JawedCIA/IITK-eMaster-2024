# Define the character to binary mapping
char_to_bin = {
    'f': '0000',
    'g': '0001',
    'h': '0010',
    'i': '0011',
    'j': '0100',
    'k': '0101',
    'l': '0110',
    'm': '0111',
    'n': '1000',
    'o': '1001',
    'p': '1010',
    'q': '1011',
    'r': '1100',
    's': '1101',
    't': '1110',
    'u': '1111'
}

# Given ciphertext
ciphertext = "rjugkhhullgusorklsklholnruogslhn"

# Function to convert a ciphertext string to binary using the mapping
def ciphertext_to_binary(ciphertext, char_to_bin):
    return ''.join(char_to_bin[char] for char in ciphertext)

# Convert the given ciphertext to binary
binary_ciphertext = ciphertext_to_binary(ciphertext, char_to_bin)

# Convert binary pairs to decimal and display results
def binary_to_decimal(binary_str, original_text):
    decimal_values = []
    binary_pairs = []
    corresponding_chars = []
    for i in range(0, len(binary_str), 8):
        binary_pair = binary_str[i:i+8]
        if len(binary_pair) < 8:  # If the binary_pair is less than 8 bits, pad it
            binary_pair = binary_pair.ljust(8, '0')
        binary_pairs.append(binary_pair)
        decimal_value = int(binary_pair, 2)
        decimal_values.append(decimal_value)
        corresponding_chars.append(original_text[(i//8)*2:(i//8)*2+2])  # Extract corresponding characters
    return binary_pairs, decimal_values, corresponding_chars

binary_pairs, decimal_values, corresponding_chars = binary_to_decimal(binary_ciphertext, ciphertext)

# Display the results in a tabular format
print("Binary Pair  |  Decimal Value  |  Corresponding Characters")
print("--------------------------------------------------------")
for binary_pair, decimal_value, chars in zip(binary_pairs, decimal_values, corresponding_chars):
    print(f"{binary_pair}  |  {decimal_value}  |  {chars}")
