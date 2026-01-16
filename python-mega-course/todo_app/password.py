# using list
def password_validation_one():
    password = input("Enter new passord: ")

    result = []

    if len(password) >= 8:
        result.append(True)
    else:
        result.append(False)

    digit = False
    uppercase = False

    for i in password:
        if i.isdigit():
            digit = True

        if i.isupper():
            uppercase = True


    result.append(digit)
    result.append(uppercase)

    print(result)

    if all(result) == True:
        print("Strong Password")
    else:
        print("Weak Password")

# using dictionary
def password_validation_two():
    password = input("Enter new passord: ")

    result = {}

    if len(password) >= 8:
        result["length"] = True
    else:
        result["length"] = False

    digit = False
    uppercase = False

    for i in password:
        if i.isdigit():
            digit = True

        if i.isupper():
            uppercase = True


    result["digit"] = digit
    result["uppercase"] = uppercase

    print(result)

    # all() method is used
    if all(result.values()) == True:
        print("Strong Password")
    else:
        print("Weak Password")

# test above functions
# password_validation_one()
# password_validation_two()
