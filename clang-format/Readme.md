# C++ Honda Standard Guideline Using Clang Format
Based on honda c++ guidelines, fixing of alignment issues considered as top priority to meet source code in good shape.

## Pre-Requirements to install
clang-format binary should be installed in linux build environment

## Install Packages
```bash
$ sudo apt install clang-format
```

## Command to execute
Simple command to check and update as per clang-format file
```bash
# source-file: .h, .hpp, or .cpp
# format-file: .clang-format
$ sudo clang-format -i --style=file:<format-file> <source-file.cpp>
```

## Changes to be done as per alignment
Trimming the file, extra spaces to be deleted on every line of the file.
Resolving space issues
Expanding tabs into spaces
Namepsace issues
Each line should not be extend 180 characters
4 space character alignment
etc.,

## Enhancement for Alignment Changes
If anything is missed in formatting the source code with proper alignment.
Feel, free to change the format file **.clang-format**
