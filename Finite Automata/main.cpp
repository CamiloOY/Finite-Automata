#include <iostream>
#include "DFA.h"

int main() {
	std::function<int(int, char)> transitions = [](int current_state, char letter) -> int {
		switch(letter) {
		case 'a':
			return (current_state + 1) % 3;
		case 'b':
			return current_state;
		default:
			throw "Invalid letter";
		}
	};
	DFA<int> triple_as({0, 1, 2}, {'a', 'b'}, transitions, 0, {0});
	std::string test_strings[7] = {"aaa", "abbaa", "abba", "", "aaaaaa", "baaa", "aaaaa"};
	for(int i = 0; i < 7; i++) {
		std::cout << test_strings[i] << ": " << triple_as.acceptsString(test_strings[i]) << '\n';
	}
	return 0;
}