"""A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two n-digit numbers."""

# Created in 7/9/2020 by Matt Zafeiriou

digits = 2 # digits = n
first = 10 ** (digits - 1)
max = 0

def isPalindromic(num):
    temp = num
    rev = 0
 
    while temp != 0:
        rev = (rev * 10) + (temp % 10)
        temp = temp // 10

    return num == rev

while True:
    
    for i in range(10 ** (digits - 1),10 ** digits):
        sum = i * first
        if isPalindromic(sum):
            if sum > max:
                max = sum

    first += 1
    if first > (10 ** digits) - 1:
        break

print("Max: " + str(max))
