
def InifiniteTodoList():
    user_prompt = "Enter a todo: "

    todos = []

    while True:
        todo = input(user_prompt)

        if todo == "exit" or len(todo) == 0:
            break
        todos.append(todo)
        print(todo.capitalize()) # captialize() method from str object
        print(todo.title()) # title() method from str object
        print(todos)


# InifiniteTodoList()

def TodoList():

    todos = []

    while True:
        user_action = input("Type add, show or exit: ")
        user_action = user_action.strip()

        match user_action:
            case 'add':
                todo = input("Enter a todo: ")
                todos.append(todo.capitalize())
            case 'show' | 'display': # using bitwise operator '|'
                # print(todos)
                for item in todos:
                    print(item)
            case 'exit':
                print('Bye!')
                break
            # case whatever:
            case _:
                print("Entered invalid command! ")

# TodoList()

def DisplayForEach():
    for char in 'meals':
        print(char.capitalize())

    # it prints every letter with capital on new line, M E A L S

def BuiltinMethods():
    import builtins

    builtins_data = dir(builtins)

    with open("builtins.txt", "w", encoding="utf-8") as f:
        for item in builtins_data:
            f.write(item + "\n")

# Invoke below function to know python builtins functions, macros, variables, etc
# BuiltinMethods()

# list outs built-in functions of the string
# dir(str)
# or
# dir("some string")
# help function or user manual of the str function capitalize() method
# help("hello".capitalize)
# dir(list)
# dir([])
# dir(str)
# etc..,


# import builtins

# zip function
def ZipFunction():
    contents = ["one", "two", "three"]
    numbers = [11, 22, 33]

    for content, number in zip(contents, numbers):
        print(f"{number} - {content}")

# ZipFunction()


# Journals
def Journals():
    date = input("Enter today's date: ")
    mood = input("How do you rate your mood from 1 to 10? ")
    thoughts = input("Let your thoughts flow: \n")

    with open(f"{date}.txt", "w") as file:
        file.write(mood + 2 * "\n")
        file.write(thoughts)

    if 'mood' in mood:
        print("mood is present in mood variable")
    else:
        print("mood is not present in mood variable")

# Journals()

def RectangleArea():
    try:
        width = float(input("Enter width of the rectangle: "))
        length = float(input("Enter length of the rectangle: "))

        if width == length:
            exit("This looks to be square")

        area = width * length
        print("Area = ", area)
    except ValueError:
        print("Enter a valid value in float")

# RectangleArea()

def getAverageOfTemperatures():
    with open("data.txt", 'r') as file:
        data = file.readlines()

    values = data[1:]
    values = [float(i) for i in values]
    # sum() and len() built-in function accepting list object
    # max(), min(), pow(),
    average = sum(values) / len(values)

    return average

# averageTemp = getAverageOfTemperatures()
# print(averageTemp)

from modules.converter import convertDistance

def convertFeetInches():
    feet_inches = input("Enter feet and inches: ")

    meters = convertDistance(feet_inches)

    if meters < 1:
        print("Kid is too small")
    else:
        print("Kid can use the slide")

    return f"feet_inches is equal to {meters} meters."

# resultMeters = convertDistance()
# print(resultMeters)

def Speed(distance, time):
    result = distance / time
    return result
