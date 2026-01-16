import glob

# search all filename having with extension ".txt"
myfiles = glob.glob(r"modules/*")

print(myfiles)

for filepath in myfiles:
    if "parser" in filepath:
        with open(filepath, "r") as file:
            print(file.read())
