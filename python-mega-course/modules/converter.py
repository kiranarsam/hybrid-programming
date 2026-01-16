from parser import parseFeetInches

def convertDistance(feet_inches):
    f, i = parseFeetInches(feet_inches)

    meters = f * 0.3048 + i * 0.0254

    return meters

if __name__ == "__main__":
    meters = convertDistance("3 30")
    print("Meters = ", meters)