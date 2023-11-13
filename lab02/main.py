from vcc_new import *

key = b'0123456789ABCDEF'
iv = b'0123456789ABCDEF'

# key = os.urandom(VCC.KEY_SIZE)
# iv = os.urandom(VCC.IV_SIZE)

input_filename = 'assets/pesik.bmp'

ecb_enc_filename = 'encrypted/ecb_enc.bmp'
ecb_dec_filename = 'encrypted/ecb_dec.bmp'

cbc_enc_filename = 'encrypted/cbc_enc.bmp'
cbc_dec_filename = 'encrypted/cbc_dec.bmp'

encrypt_bmp(key, input_filename, ecb_enc_filename, mode=BlockMode.ECB, iv=iv)
print('Encrypted file: %s' % ecb_enc_filename)

decrypt_bmp(key, ecb_enc_filename, ecb_dec_filename, mode=BlockMode.ECB, iv=iv)
print('Decrypted file: %s' % ecb_dec_filename)

encrypt_bmp(key, input_filename, cbc_enc_filename, mode=BlockMode.CBC, iv=iv)
print('Encrypted file: %s' % cbc_enc_filename)

decrypt_bmp(key, cbc_enc_filename, cbc_dec_filename, mode=BlockMode.CBC, iv=iv)
print('Decrypted file: %s' % cbc_dec_filename)
