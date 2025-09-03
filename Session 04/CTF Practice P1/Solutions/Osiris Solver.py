# Constants
MAX_BITS = 8

# Bit rotation functions
def ROL1(val, r_bits):
    """
    Rotate left: 0b1001 --> 0b0011
    Performs left rotation on an 8-bit value
    """
    return (val << r_bits % MAX_BITS) & (2**MAX_BITS - 1) | \
           ((val & (2**MAX_BITS - 1)) >> (MAX_BITS - (r_bits % MAX_BITS)))

def ROR1(val, r_bits):
    """
    Rotate right: 0b1001 --> 0b1100
    Performs right rotation on an 8-bit value
    """
    return ((val & (2**MAX_BITS - 1)) >> r_bits % MAX_BITS) | \
           (val << (MAX_BITS - (r_bits % MAX_BITS)) & (2**MAX_BITS - 1))

# Original equations (commented out for reference)
# These are the original conditions that need to be reversed:
# __ROR1__(__ROL1__(*a1, 0x30), 0x33) == 0xA8
# && __ROL1__(__ROL1__(a1[1], 0x10), 0xF) == 0xA3
# && (__ROL1__(a1[2], 0x44) ^ 0x3A) == 0xE
# && __ROR1__(a1[3] ^ 0x43, 0x2F) == 0xC
# && __ROR1__(a1[4] ^ 0xC, 0x2F) == 0xBC
# && (__ROL1__(a1[5], 0x14) ^ 0x11) == 0x54
# && __ROL1__(a1[6] ^ 0x12, 0x2A) == 0xA5
# && __ROL1__(__ROR1__(a1[7], 0x38), 0x44) == 0x53
# && __ROR1__(a1[8] ^ 0x38, 0x13) == 0x61
# && (__ROR1__(a1[9], 0x43) ^ 0x1F) == 121
# && __ROR1__(__ROR1__(a1[10], 0x26), 0x3C) == 0xD7
# && __ROL1__(__ROR1__(a1[11], 0x33), 0x33) == 0x31
# && __ROL1__(__ROL1__(a1[12], 0x1C), 0x15) == 0xCC
# && __ROR1__(a1[13] ^ 0x3A, 0x2A) == 0x59
# && __ROR1__(__ROR1__(a1[14], 0x10), 0x2A) == 0x5E
# && __ROR1__(__ROL1__(a1[15], 0x30), 0x18) == 0x30
# && (__ROR1__(a1[16], 0x27) ^ 0x20) == 0xCA
# && __ROR1__(__ROR1__(a1[17], 0x23), 0x2B) == 0x7D
# && __ROL1__(__ROR1__(a1[18], 0x13), 0x3E) == 0x23
# && __ROL1__(__ROR1__(a1[19], 0x3A), 0xC) == 0xCC
# && (__ROL1__(a1[20], 0xD) ^ 0x13) == 0xB5
# && __ROR1__(a1[21] ^ 0x27, 0x15) == 0xA0
# && (a1[22] ^ 0x33) == 0x61
# && (__ROR1__(a1[23], 0x26) ^ 0x19) == 0xC0
# && __ROL1__(a1[24] ^ 0x1B, 0x22) == 0xA0
# && __ROR1__(__ROR1__(a1[25], 0x24), 0x2C) == 0x5F
# && (a1[26] ^ 0x79) == 0xE
# && __ROL1__(__ROR1__(a1[27], 0x14), 0xA) == 0x1A
# && (__ROL1__(a1[28], 0x45) ^ 0x3A) == 0xBC
# && (__ROL1__(a1[29], 0x12) ^ 0x3F) == 0xE3
# && __ROL1__(a1[30] ^ 0x33, 0x2E) == 0x1B
# && __ROL1__(__ROL1__(a1[31], 0x27), 0x2C) == 0x1B
# && (__ROR1__(a1[32], 33) ^ 0x19) == 1
# && __ROR1__(__ROR1__(a1[33], 0x26), 0x3C) == 0x5B
# && (a1[34] ^ 0x3D) == 0xE
# && __ROR1__(a1[35] ^ 0x3E, 0x13) == 0x61
# && __ROL1__(__ROR1__(a1[36], 0x23), 0x18) == 0xEB
# && __ROR1__(__ROL1__(a1[37], 0x31), 0x37) == 0xB9
# && __ROR1__(__ROR1__(a1[38], 0x2B), 0xB) == 0xCC
# && (a1[39] ^ 0x33) == 0x4B
# && a1[40] == 0x37
# && __ROR1__(__ROL1__(a1[41], 0xC), 0xA) == 0xF5


def solve():
    """
    Extract the password from the above conditions and return it as a string.
    This password starts with EGCERT{ and ends with }
    """
    password = []
    print("Solving...")
    
    # Solve each character by reversing the original equations
    password.append(chr(ROL1(ROR1(0xA8, 0x30), 0x33)))
    password.append(chr(ROR1(ROR1(0xA3, 0xF), 0x10)))
    password.append(chr(ROL1(0xE ^ 0x3A, 0x44)))
    password.append(chr(ROL1(0xC, 0x2F) ^ 0x43))
    password.append(chr(ROL1(0xBC, 0x2F) ^ 0xC))
    password.append(chr(ROL1(0x54 ^ 0x11, 0x14)))
    password.append(chr((ROR1(0xA5, 0x2A) ^ 0x12)))
    password.append(chr(ROL1(ROR1(0x53, 0x44), 0x38)))
    password.append(chr(ROL1(0x61, 0x13) ^ 0x38))
    password.append(chr((ROL1(0x79 ^ 0x1F, 0x43))))
    password.append(chr(ROL1(ROL1(0xD7, 0x3C), 0x26)))
    password.append(chr(ROL1(ROR1(0x31, 0x33), 0x33)))
    password.append(chr(ROR1(ROR1(0xCC, 0x15), 0x1C)))
    password.append(chr((ROL1(0x59, 0x2A)) ^ 0x3A))
    password.append(chr(ROL1(ROL1(0x5E, 0x2A), 0x10)))
    password.append(chr(ROR1(ROL1(0x30, 0x18), 0x30)))
    password.append(chr(ROL1((0xCA ^ 0x20), 0x27)))
    password.append(chr(ROL1(ROL1(0x7D, 0x2B), 0x23)))
    password.append(chr(ROL1(ROR1(0x23, 0x3E), 0x13)))
    password.append(chr(ROL1(ROR1(0xCC, 0xC), 0x3A)))
    password.append(chr(ROR1((0xB5 ^ 0x13), 0xD)))
    password.append(chr(ROL1(0xA0, 0x15) ^ 0x27))
    password.append(chr(0x61 ^ 0x33))
    password.append(chr(ROL1((0xC0 ^ 0x19), 0x26)))
    password.append(chr(ROR1(0xA0, 0x22) ^ 0x1B))
    password.append(chr(ROL1(ROL1(0x5F, 0x2C), 0x24)))
    password.append(chr(0xE ^ 0x79))
    password.append(chr(ROL1(ROR1(0x1A, 0xA), 0x14)))
    password.append(chr(ROR1((0xBC ^ 0x3A), 0x45)))
    password.append(chr(ROR1((0xE3 ^ 0x3F), 0x12)))
    password.append(chr(ROR1(0x1B, 0x2E) ^ 0x33))
    password.append(chr(ROR1(ROR1(0x1B, 0x2C), 0x27)))
    password.append(chr(ROL1((1 ^ 0x19), 0x21)))
    password.append(chr(ROL1(ROL1(0x5B, 0x3C), 0x26)))
    password.append(chr(0xE ^ 0x3D))
    password.append(chr(ROL1(0x61, 0x13) ^ 0x3E))
    password.append(chr(ROL1(ROR1(0xEB, 0x18), 0x23)))
    password.append(chr(ROR1(ROL1(0xB9, 0x37), 0x31)))
    password.append(chr(ROL1(ROL1(0xCC, 0xB), 0x2B)))
    password.append(chr(0x4B ^ 0x33))
    password.append(chr(0x37))
    password.append(chr(ROR1(ROL1(0xF5, 0xA), 0xC)))
    
    return ''.join(password)


if __name__ == "__main__":
    print(solve())