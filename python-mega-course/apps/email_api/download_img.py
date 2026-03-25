import requests

# url = r"https://en.wikipedia.org/wiki/File:The_Blue_Marble,_AS17-148-22727.jpg"
url = "https://en.wikipedia.org/wiki/Earth#/media/File:The_Blue_Marble,_AS17-148-22727.jpg"

response = requests.get(url=url, verify=False)
# data = response.json()

# in write binary mode
with open("earth.jpg", 'wb') as file:
    # response.content as binary data
    file.write(response.content)
