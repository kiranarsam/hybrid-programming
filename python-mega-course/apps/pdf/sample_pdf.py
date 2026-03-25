
# third party library
from fpdf import FPDF

# print("Hello from pdf")
pdf = FPDF(orientation="portrait", unit="mm", format="A4")
# print(type(pdf))

# first page
pdf.add_page()
pdf.set_font(family="Times", style="B", size=12)
pdf.cell(w=0, h=12, txt="Python Programming", ln=1, align="L")
pdf.set_font(family="Times", style="B", size=10)
pdf.cell(w=0, h=10, txt="Python Module PDF", ln=1, align="L")

# second page
pdf.add_page()
pdf.set_font(family="Times", style="B", size=12)
pdf.cell(w=0, h=12, txt="Python Programming", ln=1, align="L")
pdf.set_font(family="Times", style="B", size=10)
pdf.cell(w=0, h=10, txt="Python Module PDF", ln=1, align="L")

pdf.output("output.pdf")
