import math


def frequency_analysis(text: str, alphabet: str) -> dict:
    frequencies = {c: 0 for c in alphabet}
    total_chars = 0

    for char in text:
        c = char.lower()
        if c in alphabet:
            frequencies[c] = frequencies.get(c, 0) + 1
            total_chars += 1

    for char, count in frequencies.items():
        frequency = count / total_chars * 100
        frequencies[char] = frequency

    return frequencies


def calculate_score(vector1, vector2):
    if len(vector1) != len(vector2):
        raise ValueError("Векторы должны иметь одинаковую длину")

    diff_vector = [x - y for x, y in zip(vector1, vector2)]
    squared_diff = [x**2 for x in diff_vector]
    sum_squared_diff = sum(squared_diff)
    score = math.sqrt(sum_squared_diff)

    return score


def find_shift(ciphertext: str, alphabet: str, target_frequencies: dict):
    def shift(lst, n):
        return lst[n:] + lst[:n]

    frequencies = frequency_analysis(ciphertext, alphabet)
    frequencies = list(frequencies.values())
    target = list(target_frequencies.values())
    best_shift, best_score = 0, float("inf")

    for i in range(26):
        score = calculate_score(shift(frequencies, i), target)
        if score < best_score:
            best_score = score
            best_shift = i

    return best_shift
