# crc_encoder.py

def xor(a, b):
    result = []
    for i in range(1, len(b)):
        if a[i] == b[i]:
            result.append('0')
        else:
            result.append('1')
    return ''.join(result)

def mod2div(divident, divisor):
    pick = len(divisor)
    tmp = divident[0:pick]

    while pick < len(divident):
        if tmp[0] == '1':
            tmp = xor(divisor, tmp) + divident[pick]
        else:
            tmp = xor('0'*pick, tmp) + divident[pick]
        pick += 1

    if tmp[0] == '1':
        tmp = xor(divisor, tmp)
    else:
        tmp = xor('0'*pick, tmp)

    checkword = tmp
    return checkword

def encode_data(data, key):
    l_key = len(key)
    #print(f"{l_key}")
    appended_data = data + '0'*(l_key-1)
    remainder = mod2div(appended_data, key)
    re_key = len(remainder)
    #print(f"{re_key}")
    codeword = data + remainder
    #print(f"{codeword}")
    return codeword

