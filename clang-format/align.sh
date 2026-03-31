#!/bin/bash

set -e

SRC_FOLDER="$1"
[ -z "$SRC_FOLDER" ] && SRC_FOLDER=""

if command -v clang-format &> /dev/null; then
  DUMMY=""
else
  echo "clang-format is not installed."
  exit 1
fi

PWD=$(pwd)
# clang file path

CLANG_FORMAT=$PWD/.clang-format

usage() {
  echo "Usage:"
  echo "    ./align.sh [all]"
  echo ""
  echo "Options:"
  echo ""
  echo "  all         - Includes all"
  echo ""
  exit 1
}

align_all() {
  echo "Processing for align_all"
  list_of_files=(
    \*.cpp
    \*.c
    \*.h
    \*.hpp
  )

  perform_alignment "${list_of_files[@]}"
}

perform_alignment() {
  list_of_files=$1

  for file_path in "${list_of_files[@]}"
  do
    local filename="${PWD}/${file_path}"
    echo "Aligning filename = $filename"
    clang-format -i --style=file:$CLANG_FORMAT ${filename}
  done
}

SRC_FOLDER="$PWD/$SRC_FOLDER"
if [ -d "$SRC_FOLDER" ]; then
  DUMMY=""
else
  SRC_FOLDER="$PWD"
fi

pushd $SRC_FOLDER

if [[ -n "$SRC_FOLDER" ]]; then
  align_all
else
  usage
fi
popd

# Done
echo "# Done"
