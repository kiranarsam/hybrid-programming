## When multithreading is useful?
1. When you're waiting for something external and want to execute code meanwhile.
   (asynchronous execution)

Example: pinging remote servers
Example: drawing graphics while also processing user input

2. Distributing processing across multiple cores
Example: calculating PI to lots of digits.
