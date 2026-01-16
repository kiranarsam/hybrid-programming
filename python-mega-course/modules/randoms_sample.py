import random

lower_bound = 8
upper_bound = 10

# Pick a random int using randrange()
rand = random.randrange(lower_bound, upper_bound + 1) # We add 1 to upper_bound because randrange does not include the upper_bound number.

print(rand)

# Pick a random int using randint()
rand = random.randint(lower_bound, upper_bound)

print(rand)
