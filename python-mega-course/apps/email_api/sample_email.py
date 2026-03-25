import requests
from send_email import send_email

# url = "http://google.com"
# yahoo_url = "https://finance.yahoo.com"
apikey = "8fbae5e5bf1041389c09c0b7972d76ca"
# url = f"https://newsapi.org/v2/top-headlines?sources=bbc-news&apiKey={apikey}"

url = f"https://newsapi.org/v2/everything?q=tesla&sortBy=publishedAt&apiKey={apikey}"

# request = requests.get(url=url)
request = requests.get(url=url, verify=False)
# request = requests.get(yahoo_url)
# content = request.text
content = request.json()
# print(type(content))

body = ""
for article in content["articles"]:
    if article["title"] is not None:
        body = body + article["title"] + "\n" + str(article["description"]) + 2*"\n"

body = body.encode("utf-8")
send_email(message=body)