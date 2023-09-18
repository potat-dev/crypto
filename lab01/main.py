from caesar import encrypt, decrypt
from analysis import frequency_analysis, find_shift
from alphabets.english import alphabet, alphabet_frequencies

shift = 3
display_limit = 200

with open("test_data/harry-potter.txt", "r", encoding="utf-8") as f:
    plaintext = f.read()

print("Исходный текст:", plaintext[:display_limit], "\n")

ciphertext = encrypt(plaintext, shift, alphabet)
print("Зашифрованный текст:", ciphertext[:display_limit], "\n")

decrypted_text = decrypt(ciphertext, shift, alphabet)
print("Расшифрованный текст:", decrypted_text[:display_limit], "\n")

print("Частотный анализ:")
frequencies = frequency_analysis(ciphertext, alphabet)

for char, frequency in frequencies.items():
    print(f"{char}: {frequency:.2f}%")

# попытка восстановить сдвиг частотным анализом

founded_shift = find_shift(ciphertext, alphabet, alphabet_frequencies)
print("Вычисленный сдвиг:", founded_shift)
