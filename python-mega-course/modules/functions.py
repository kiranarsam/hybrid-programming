import os

TODO_FILENAME = "todos.txt"

def initialize_todos():
    if not os.path.exists(TODO_FILENAME):
        with open(TODO_FILENAME, 'w') as file:
            pass

def get_todos(filename=TODO_FILENAME):
    """
    Return list of todos from the text file
    """
    try:
        with open(filename, "r") as file:
            todos = file.readlines()
            todos = [item.strip() for item in todos]
    except:
        print("File not found: todos.txt ")
        todos = []

    return todos

def write_todos(todos, filename=TODO_FILENAME):
    """
    Write list of todos into the file
    """
    with open(filename, "w") as file:
        for item in todos:
            file.writelines(item + "\n")

# if we call this file from main.py, then below __name__ is "module.functions" and not "__main__"
# print(__name__)
if __name__ == "__main__":
    print("Ignoring direct executing this file")
