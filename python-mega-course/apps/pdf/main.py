
# third party library
from fpdf import FPDF
import pandas as pd

# print("Hello from pdf")
pdf = FPDF(orientation="portrait", unit="mm", format="A4")

pdf.set_auto_page_break(auto=False, margin=0)

df = pd.read_csv("topics.csv")

# A4 width and hight is max width is 210, max height 298

for index, row in df.iterrows():
    # print(index, row["Order"], row["Topic"], row["Pages"])
    pdf.add_page()
    # Set the header
    pdf.set_font(family="Times", style="B", size=34)
    # set color RGB
    pdf.set_text_color(100, 100, 100)
    pdf.cell(w=0, h=10, txt=row["Topic"], ln=1, align="L")
    # line will appear from point (10, 21) to point (200, 21)
    # start from line 20, every line gap is 10mm
    for hz_line in range(20, 298, 10):
        pdf.line(10, hz_line, 200, hz_line)

    # Set the footer
    pdf.ln(267)
    pdf.set_font(family="Times", style="I", size=8)
    pdf.set_text_color(180, 180, 180)
    pdf.cell(w=0, h=10, txt=row["Topic"], ln=1, align="R")

    for i in range(row["Pages"] - 1):
        pdf.add_page()

        # set the footer
        pdf.ln(277)
        pdf.set_font(family="Times", style="I", size=8)
        pdf.set_text_color(180, 180, 180)
        pdf.cell(w=0, h=10, txt=row["Topic"], ln=1, align="R")

        for hz_line in range(20, 298, 10):
            pdf.line(10, hz_line, 200, hz_line)

pdf.output("output.pdf")
