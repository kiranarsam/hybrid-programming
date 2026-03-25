import smtplib, ssl

def send_email(message):
    host = "smtp.gmail.com"
    port = 465

    username = "app8flask@gmail.com"
    # password = "pmuuyjaxfejfpxkc"

    # to get below GMAIL APP PASSWORD, follow below steps:
    # goto: https://myaccount.google.com/apppasswords
    # or Security => 2-Step-Verification (if off, turned3 on) => App Passwords
    # Create a new one under your app passwords, use that key in the variable password, try sending mail
    password = "YOUR_GMAIL_APP_PASSWORD"

    receiver = "app8flask@gmail.com"
    context = ssl.create_default_context()

    with smtplib.SMTP_SSL(host, port, context=context) as server:
        server.login(username, password)
        server.sendmail(username, receiver, message)
