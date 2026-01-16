import csv

with open("files/weather.csv", "r") as file:
    data = list(csv.reader(file))

print(data)

user_input = "London"

for row in data[1:]:
    if row[0] in user_input:
        print(f"London Temperature: {row[1]}")