import requests
import streamlit as st

# url = f"https://newsapi.org/v2/everything?q=tesla&sortBy=publishedAt&apiKey={apikey}"
# url = "https://en.wikipedia.org/wiki/File:The_Blue_Marble,_AS17-148-22727.jpg"

# url = "https://api.nasa.gov/planetary/apod?api_key=DEMO_KEY"
url = "https://api.nasa.gov/planetary/apod?api_key=wdlVn1n7PGw6i03MwUuStbLYxzSkATtpRj8b9vQE"

response = requests.get(url=url, verify=False)
data = response.json()

# print(data)

title = data["title"]
image_url = data["url"]
explanation = data["explanation"]

image_filepath = "astronat.png"
astro_resp = requests.get(image_url, verify=False)
with open(image_filepath, "wb") as file:
    file.write(astro_resp.content)

st.title(title)
st.image(image_filepath)
st.write(explanation)


# in write binary mode
# with open("earth.png", 'wb') as file:
#     # response.content as binary data
#     file.write(response.content)
