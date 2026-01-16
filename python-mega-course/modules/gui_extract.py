import FreeSimpleGUI as sg
from zip_extractor import extract_archive

sg.theme("Black")

label1 = sg.Text("Select Archive: ")
input1 = sg.Input()
choose_btn1 = sg.FileBrowse("Choose", key="archive")

label2 = sg.Text("Select Dest Folder: ")
input2 = sg.Input()
choose_btn2 = sg.FolderBrowse("Choose", key="folder")

ext_btn = sg.Button("Extract")
output_label = sg.Text(key="output", text_color="green")

layout = [[label1, input1, choose_btn1],
          [label2, input2, choose_btn2],
          [ext_btn, output_label]]

window = sg.Window("Archive Extractor",
                   layout=layout,
                   )

while True:
    event, values = window.read()
    print(event, values)
    match event:
        case "Extract":
            archive_path = values["archive"]
            dest_dir = values["folder"]
            extract_archive(archive_path, dest_dir)

            window["output"].update("Extracted Successfully")

        case sg.WIN_CLOSED:
            break


window.close()
