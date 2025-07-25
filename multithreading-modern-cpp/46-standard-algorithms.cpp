// Uses a standard algorithm to find a character in a string
#include <iostream>
#include <string>
#include <algorithm>

using namespace std::literals;

void stringSearch(const std::string& token = "default"s)
{
  std::string str("Hello world");
	std::cout << "String to search: " << str << '\n';

	// Search string for first occurrence of 'o'
	std::cout << "Searching for first occurrence of \'o\'\n";
  std::string::const_iterator res = str.cend();
  if(token == "predicate")
  {
    // Use a predicate function which ignores case
	  res = std::find_if(str.cbegin(), str.cend(),
					[](const char c) {
						return ::toupper(c) == 'O';
					});
  }
  else
  {
    res = std::find(str.cbegin(), str.cend(), 'o');
  }

	// Did we find it?
	if (res != str.cend()) {
		// Access the result
		std::cout << "Found a matching element at index: " << res - str.cbegin() << '\n';

		std::cout << "At this point in the string: ";
		for (auto it = res; it != str.cend(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}
	else
		std::cout << "No matching element\n";
}

int main() {

  stringSearch();
  stringSearch("predicate");

  return 0;
}