## Python Mega Course

Small python projects
https://dailypythonprojects.substack.com/

## Python module index
https://docs.python.org/3/py-modindex.html

## pypi org
Able to search all kind of python modules, instructions to install.
https://pypi.org/

Python project in separate virtual environment through command line argument.

```bash
$ mkdir my_python_project
$ cd my_python_project
$ python -m venv .venv
# Activate the virtual environment (choose one)
# Command Prompt: .venv\Scripts\activate
# PowerShell: .venv\Scripts\Activate.ps1
$ pip install <package_name>  # Install dependencies
$ python my_script.py # Run script
$ deactivate
```

Installing dependency python modules

```bash
# Activate virtual environment
$ .venv\Scripts\activate

# first install pip-tools from venv
$ pip install pip-tools
# create requirements.in file, add dependency modules

# existing modules the virtual environemnt to generate
$ pip freeze > requirements.txt
# On clone project or these examples need to run, above requirements.txt
# dependency packages need to be installed

# generate requirements.txt file using pip-compile
$ pip-compile requirements.in

# Install requirements.txt file using below command
$ pip install -r requirements.txt

```

## python forums
* stackoverflow
* redit
* python community
* discord.com

## Python Uages
* Web Development
* Data Science / Machine Learning / AI
* Automations
* General Programming
* Web Scraping
* Others

## Python major version release
* 1.0.0 - 1994
* 2.0.0 - 2000
* 3.0.0 - 2008

## python patch release, example
python major.minor.patch

Example Python 3.11.2

2 - patch release
11 - big features and backward compatibility
3 - major version
