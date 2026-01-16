
def parseFeetInches(feet_inches):
    parts = feet_inches.split(" ")
    feet = float(parts[0])
    inches = float(parts[1])

    return feet, inches

if __name__ == "__main__":
    parseFeetInches("2 20")