def encrypt(plaintext, shift, alphabet):
    ciphertext = ""
    for char in plaintext:
        c = char.lower()
        if c in alphabet:
            index = alphabet.index(c)
            shifted_index = (index + shift) % len(alphabet)
            shifted_char = alphabet[shifted_index]
            ciphertext += shifted_char
        else:
            ciphertext += c
    return ciphertext


def decrypt(ciphertext, shift, alphabet):
    return encrypt(ciphertext, -shift, alphabet)
