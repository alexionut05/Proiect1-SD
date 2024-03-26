import random
g=open("date.in", "w")
num_numbers = 10**7     #cate numere vrei

random_numbers = [random.randint(1, 10**12) for _ in range(num_numbers)]
                                #intervalul 
for number in random_numbers:
    g.write(str(number) + " ")
