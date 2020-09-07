#
# Find all the prime factors of a number
# and print them + the largest prime factor
# 
# Idea by: https://projecteuler.net/problem=3
# 
# Made in 7/9/2020 by Matt Zafeiriou
#

number = 600851475143
current = 2
max = 2

def isPrime(num):

    for i in range(2, num - 1):
        if num % i == 0:
            return False

    return True

while True:

    if isPrime(number):
        if number > max:
            max = number
        print(number)
        break

    while not isPrime(current):
        current += 1
    # current is prime now

    while not number % current == 0:
        current += 1

    number = int(number / current)
    if current > max:
        max = current
    print(current)
    

print("Max is: " + str(max))
