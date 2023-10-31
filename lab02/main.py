from cipher import *

key = b'0123456789abcdef'

input_filename = 'assets/mars.bmp'

ecb_enc_filename = 'encrypted/ecb_enc.bmp'
ecb_dec_filename = 'encrypted/ecb_dec.bmp'

cbc_enc_filename = 'encrypted/cbc_enc.bmp'
cbc_dec_filename = 'encrypted/cbc_dec.bmp'

encrypt_bmp(key, input_filename, ecb_enc_filename, mode=BlockMode.ECB)
decrypt_bmp(key, ecb_enc_filename, ecb_dec_filename, mode=BlockMode.ECB)

encrypt_bmp(key, input_filename, cbc_enc_filename, mode=BlockMode.CBC)
decrypt_bmp(key, cbc_enc_filename, cbc_dec_filename, mode=BlockMode.CBC)
