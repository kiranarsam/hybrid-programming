import streamlit as st
from modules import functions

functions.initialize_todos()
todos = functions.get_todos()

def add_todo_item():
    new_todo = st.session_state["add_todo"]
    # print(new_todo)
    new_todo = new_todo.strip()
    if len(new_todo) != 0:
        todos.append(new_todo)
        functions.write_todos(todos)

# this works for all kind of screens
st.set_page_config(layout="wide")

st.title("My App")
st.subheader("This is my app")
st.write("This application is to increase the <b>productivity</b>.", unsafe_allow_html=True)

st.text_input(label="Enter a new todo", placeholder="Add new item ...",
              on_change=add_todo_item, key='add_todo')

for index, todo in enumerate(todos):
    checkbox = st.checkbox(label=todo, key=todo)
    if checkbox:
        removed_todo = todos.pop(index)
        functions.write_todos(todos)
        del st.session_state[todo]
        st.rerun()


# print("Hello")
# print(st.session_state)
# st.session_state
