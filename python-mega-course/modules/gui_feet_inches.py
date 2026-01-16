import FreeSimpleGUI as sg
import converter

label1 = sg.Text("Enter feet:")
input1 = sg.Input(key="feet")

label2 = sg.Text("Enter inches:")
input2 = sg.Input(key="inch")

compress_button = sg.Button("Convert", key="convert")
exit_button = sg.Button("Exit", key="exit")

output_label = sg.Text(key="output")

layout = [[label1, input1],
          [label2, input2],
          [compress_button, exit_button, output_label]]

window = sg.Window("File Compressor",
                   layout=layout,
                   font=('Helvetica', 20))

while True:
    event, values = window.read()
    match event:
        case "convert":
            feet = values["feet"].strip()
            if len(feet) == 0:
                feet = 0.
            inch = values["inch"].strip()
            if len(inch) == 0:
                inch = 0

            meters = converter.convertDistance(f"{feet} {inch}")
            window["output"].update(value=f"{meters} m")

        case "exit":
            break
        case sg.WIN_CLOSED:
            break

window.close()
