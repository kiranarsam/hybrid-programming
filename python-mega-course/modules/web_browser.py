import webbrowser

user_term = input("Enter a search term: ")

# replace space with + in the url
user_term = user_term.replace(" ", "+")
# opens a google page
# webbrowser.open("https://google.com/search?q=" + user_term)
webbrowser.open(f"https://google.com/search?q={user_term}")
