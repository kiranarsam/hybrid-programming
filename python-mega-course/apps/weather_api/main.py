from flask import Flask, render_template
import pandas as pd

filename_station_10 = "data_small/TG_STAID" + str(10).zfill(6) + ".txt"
df_station_10 = pd.read_csv(filename_station_10, skiprows=20, parse_dates=["    DATE"])

df_stations = pd.read_csv("data_small/stations.txt", skiprows=17)
df_stations = df_stations[["STAID","STANAME                                 "]]

my_var = "Hello My World"

app = Flask(__name__)

# Default Page Route
@app.route("/")
def index():
    return render_template("index.html", data=df_stations.to_html())

@app.route("/about")
def about():
    return render_template("about.html")

@app.route("/contact-us")
def contact_us():
    return render_template("contact-us.html")

@app.route("/store")
def store():
    return render_template("store.html")

@app.route("/api/v1/<station>/<date>")
def temperature(station, date):
    # default temperature for station is 10
    df = df_station_10
    curr_temp = df.loc[df['    DATE'] == date]['   TG'].squeeze()/10
    temp = {
        "station" : station,
        "date" : date,
        "temperature" : curr_temp
    }
    return temp

@app.route("/api/v1/<station>")
def all_station_data(station):
    df = df_station_10
    result = df.to_dict(orient="records")
    return result

@app.route("/api/v1/yearly/<station>/<year>")
def all_station_by_year(station, year):
    df = df_station_10
    df["    DATE"] = df["    DATE"].astype(str)
    result = df[df["    DATE"].str.startswith(year)]
    return result.to_dict(orient="records")

if __name__ == "__main__":
    app.run(debug=True, port=5001)
