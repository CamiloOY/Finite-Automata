#pragma once

#include <unordered_set>
#include <string>
#include <functional>

// M=(Q,Sigma,delta,s,F)

template<typename T>
class DFA {
public:
	DFA(std::unordered_set<T> states, std::unordered_set<char> alphabet, std::function<T(T, char)> transitions, T initial_state, std::unordered_set<T> final_states) : states(states), alphabet(alphabet), transition_function(transitions), initial_state(initial_state), final_states(final_states) { // TODO: Ensure s is in Q and F is a subset of Q

	}

	bool acceptsString(std::string str) {
		T current_state = initial_state;
		for(int c = 0; c < str.length(); c++) {
			current_state = transition_function(current_state, str[c]);
		}
		return final_states.count(current_state);
	}

private:
	std::unordered_set<T> states;
	std::unordered_set<char> alphabet;
	std::function<T(T, char)> transition_function;
	T initial_state;
	std::unordered_set<T> final_states;
};