from modules import functions
import FreeSimpleGUI as sg
import time

# initialize todos file
functions.initialize_todos()

todos = functions.get_todos()

# GUI theme
sg.theme("LightPurple")

clock_label = sg.Text(key="clock")
label = sg.Text("Type in a to-do")
input_box = sg.InputText(tooltip="Enter todo", key="todo")
add_button = sg.Button("Add")
# add_button = sg.Button(key="Add", image_source="add.png", mouseover_colors="LightBlue2", tooltip="Add todo", size=2)
# close_button = sg.Button("Close")
list_box = sg.Listbox(values=todos, key='todos',
                      enable_events=True, size=[45, 10])
edit_button = sg.Button("Edit")
complete_button = sg.Button("Complete")
exit_button = sg.Button("Exit")
output_label = sg.Text(key="output")

layout = [[clock_label],
          [label],
          [input_box, add_button],
          [list_box, edit_button, complete_button],
          [exit_button, output_label]]

window = sg.Window("Todo App",
                   layout=layout,
                   font=('Helvetica', 20))

while True:
    event, values = window.read(timeout=1000)
    # print(event, values)
    window["clock"].update(value=time.strftime("%b %d %Y %H:%M:%S"))
    match event:
        case 'Add':
            new_todo = values['todo'].strip()
            if len(new_todo) != 0:
                todos.append(new_todo.capitalize())
                window['todos'].update(values=todos)
                window["output"].update(value="Added successfully")
                window['todo'].update(value="")
        case "Edit":
            if len(values['todos']) != 0:
                todo_to_edit = values['todos'][0].strip()
                todo_to_add = values['todo'].strip()
                index = todos.index(todo_to_edit)
                if len(todo_to_add) != 0:
                    todos[index] = todo_to_add.capitalize()
                    window['todos'].update(values=todos)
                    window["output"].update(value="Edited successfully")
        case "todos":
            if len(values['todos']) != 0:
                window['todo'].update(value=values['todos'][0])
        case "Complete":
            todo_to_complete = values['todo'].strip()
            if len(todo_to_complete) != 0:
                try:
                    todos.remove(todo_to_complete)
                    window['todos'].update(values=todos)
                    window["output"].update(value="Removed successfully")
                    window['todo'].update(value="")
                except:
                    sg.popup("Unable to delete, content not found ", font=('Helvetica', 20))
                    window["output"].update(value="Error occurred while removing from list")
        case "Exit":
              break
        case sg.WIN_CLOSED:
              # exit() # exits the program completely
              break

functions.write_todos(todos=todos)
# Make sure application is done, please close the window
window.close()