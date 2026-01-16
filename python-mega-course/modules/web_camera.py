import streamlit as st
# package pillow
from PIL import Image

st.set_page_config(layout="wide")
st.subheader("Color to Grayscale Converter")

uploaded_image = st.file_uploader("Upload Image")

camera_image = None
with st.expander(label="Start Camera", ):
    camera_image = st.camera_input(label="Camera")

# print(camera_image)
if camera_image:
    img = Image.open(camera_image)
    gray_img = img.convert("L")
    st.image(gray_img)

if uploaded_image:
    # Open the user uploaded image with PIL
    img = Image.open(uploaded_image)
    # Convert the image to grayscale
    gray_uploaded_img = img.convert('L')
    # Display the grayscale image on the webpage
    st.image(gray_uploaded_img)
