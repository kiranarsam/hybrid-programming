import requests
from send_email import send_email

topic = "tesla"

apikey = "8fbae5e5bf1041389c09c0b7972d76ca"
# url = f"https://newsapi.org/v2/top-headlines?sources=bbc-news&apiKey={apikey}"
url = f"https://newsapi.org/v2/everything?" \
      f"q={topic}&" \
      f"sortBy=publishedAt&" \
      f"apiKey={apikey}&" \
      f"language=en"

request = requests.get(url=url, verify=False)
content = request.json()

body = "Subject: Today's News" + "\n"
for article in content["articles"][:10]:
    if article["title"] is not None:
        body = body + article["title"] + "\n" \
               + str(article["description"]) + "\n" \
               + str(article["url"]) + 2*"\n"

body = body.encode("utf-8")
print(body)
# send_email(message=body)