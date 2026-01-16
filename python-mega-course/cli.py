# functions is the python filename
# from functions import get_todos, write_todos

# below import is <folder_name><.><filename>
# filename is Python file as filename.py
# folder_name where the filename is exists
# import modules.functions as functions
from modules import functions

import time

# main function
def main():
    '''
    Main application
    '''
    todos = functions.get_todos()

    while True:
        user_action = input("Type add, show, edit, complete, or exit: ")
        user_action = user_action.strip()

        match user_action:
            case 'add':
                todo = input("Enter a todo: ")
                if len(todo) != 0:
                    todos.append(todo.capitalize())

            case 'show' | 'display': # using bitwise operator '|'
                # implement enumerate function
                for index, item in enumerate(todos):
                    result = f"{index + 1}-{item}"
                    print(result.strip())
            case 'edit':
                number_to_edit = int(input("Enter number of the todo to edit: "))
                number_index = number_to_edit - 1
                new_todo = input("Enter a todo: ")
                if len(new_todo) != 0:
                    todos[number_index] = new_todo.capitalize()
            case 'complete':
                number_to_remove = int(input("Enter number to remove: "))
                number_index = number_to_remove - 1
                todos.pop(number_index)
            case 'exit':
                print('Bye!')
                break
            # case whatever:
            # (or)
            case _:
                print("Entered invalid command! Unable to process.")
    # print('Bye!')
    # override the below file
    functions.write_todos(todos)


def todo_app_one():
    todos = functions.get_todos()

    while True:
        user_action = input("Type add, show, edit, complete, or exit: ")
        user_action = user_action.strip()

        if user_action.startswith('add'):
            todo = user_action[4:]
            if len(todo) != 0:
                todos.append(todo.capitalize())

        elif user_action.startswith('show') or user_action.startswith('display'): # using bitwise operator '|'
            # implement enumerate function
            for index, item in enumerate(todos):
                result = f"{index + 1}-{item}"
                print(result.strip())
        elif user_action.startswith('edit'):
            try:
                number_to_edit = int(user_action[5:])
                number_index = number_to_edit - 1
                new_todo = input("Enter a todo: ")
                if len(new_todo) != 0:
                    todos[number_index] = new_todo.capitalize()
            except ValueError:
                print("Enter a valid number to edit")
                continue
        elif user_action.startswith('complete'):
            try:
                number_to_remove = int(user_action[8:])
                number_index = number_to_remove - 1
                todos.pop(number_index)
            except ValueError:
                print("Enter a valid number to edit")
                continue
            except IndexError:
                print("There is no item with that number")
        elif user_action.startswith('exit'):
            print('Bye!')
            break
        else:
            print("Entered invalid command! Unable to process.")
    # override the below file
    functions.write_todos(todos=todos)

# Main entry of the execution
if __name__ == "__main__":
    # '''
    # Entry for execution
    # '''
    now = time.strftime("%d %b %Y %H:%M:%S")
    print("Today is ", now)
    # print("Hello from Main")
    # main()

    # Call todo_app_one() method to execute
    todo_app_one()
