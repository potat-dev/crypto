from cipher import *

aes = AES(b'0123456789abcdef')
key = b'0123456789abcdef'

input_filename = 'assets/mars.bmp'

ecb_ecrypted_filename = 'assets/ecb_enc.bmp'
ecb_decrypted_filename = 'assets/ecb_dec.bmp'

cbc_encrypted_filename = 'assets/cbc_enc.bmp'
cbc_decrypted_filename = 'assets/cbc_dec.bmp'


encrypt_bmp(key, input_filename, ecb_ecrypted_filename, mode=BlockMode.ECB)
decrypt_bmp(key, ecb_ecrypted_filename, ecb_decrypted_filename, mode=BlockMode.ECB)

encrypt_bmp(key, input_filename, cbc_encrypted_filename, mode=BlockMode.CBC)
decrypt_bmp(key, cbc_encrypted_filename, cbc_decrypted_filename, mode=BlockMode.CBC)
