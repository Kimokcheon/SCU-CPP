import random

def generate_random_big_integer(bit_length):
    random_integer = random.randint(2**(bit_length-1), 2**bit_length - 1)
    return random_integer

def generate_random_integer(N):
    return random.randint(0, N - 1)

operators = ['+', '-', '*']
a_s = []
b_s = []
results = []

if __name__ == '__main__':
    with open("inputs.txt", "w") as fin:
        test_case = 100
        for _ in range(test_case):
            a = generate_random_big_integer(499)
            b = generate_random_big_integer(499)
            op = operators[generate_random_integer(3)]
            fin.write(f'{op} {a} {b}\n')
            a_s.append(a)
            b_s.append(b)
            if op == '+':
                results.append(a + b)
            elif op == '-':
                results.append(a - b)
            elif op == '*':
                results.append(a * b)
    with open("outputs.txt", "w") as fin:
        for res in results:
            fin.write(f'{res}\n')