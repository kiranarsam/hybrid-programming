import zipfile
import pathlib

def make_archive(filepaths, dest_dir):
    dest_path = pathlib.Path(dest_dir, "compressed.zip")
    with zipfile.ZipFile(dest_path, 'w') as archive:
        for filepath in filepaths:
            filepath = pathlib.Path(filepath)
            archive.write(filepath, arcname=filepath.name)
            # archive.write(filepath)

if __name__ == "__main__":
    function_path = pathlib.Path("modules", "functions.py")
    make_archive(filepaths=[function_path], dest_dir="dest")