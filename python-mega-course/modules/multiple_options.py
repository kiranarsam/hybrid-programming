import json

with open("files/questions.json", "r") as file:
    content = file.read()

data = json.loads(content)

# print(type(data))
# print(type)x
for qid, question in enumerate(data):
    print(f"Q-{qid + 1}) {question["question_tag"]}")
    for index, alternative in enumerate(question["alternative_tag"]):
        print(f"{index + 1}. {alternative}")

    user_choice = input("Enter your answer: ")
    question["user_choice"] = int(user_choice)
    print()

score = 0
for index, question in enumerate(data):
    if question["user_choice"] == question["correct_tag"]:
        score = score + 1

    print(f"Q-{index + 1}: Your answer: {question["user_choice"]}, Correct answer: {question["correct_tag"]}")

print(f"Total Score: {score}/{len(data)}")
