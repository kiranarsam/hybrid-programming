from dotenv import load_dotenv
import os
from langchain_google_genai import ChatGoogleGenerativeAI

load_dotenv()

gemini_api_key = os.getenv("GEMINI_API_KEY")

system_prompt = """
You are Agent.
Answer questions through Agent questioning and resaoning...
Answer 2-6 sentences
"""
llm = ChatGoogleGenerativeAI(
    model="gemini-2.5-flash",
    google_api_key=gemini_api_key,
    temperature=0.5
)

print("Hi, I am Agent, how can I help you today?")

history = []

while True:
    user_input = input("You: ")
    # exit the loop
    if user_input == 'exit':
        break
    # Add previous history
    history.append({"role": "user", "content":user_input})
    # get the feedback from the llm ai agent, based on provided prompt
    response = llm.invoke([
        {"role": "system", "content":system_prompt} + history
    ])
    print("Agent:", response.content)
    # Add response content to history
    history.append({"role":"assistant", "content":response.content})
