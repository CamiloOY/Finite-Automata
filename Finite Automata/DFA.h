#pragma once

#include <unordered_set>
#include <string>
#include <functional>

// M=(Q,Sigma,delta,s,F)

template<typename T>
class DFA {
public:
	DFA(std::vector<T> states, std::unordered_set<char> alphabet, std::function<T(T, char)> transitions, T initial_state, std::vector<T> final_states) : states(states), alphabet(alphabet), transition_function(transitions), initial_state(initial_state), final_states(final_states) { // TODO: Ensure s is in Q and F is a subset of Q

	}

	bool acceptsString(std::string str) {
		T current_state = initial_state;
		for(int c = 0; c < str.length(); c++) {
			current_state = transition_function(current_state, str[c]);
		}
		return std::find(final_states.begin(), final_states.end(), current_state) != final_states.end();
	}

	template<typename U>
	DFA<std::pair<T, U>> cross(DFA<U> other) {
		std::vector<std::pair<T, U>> new_states;
		for(T el_a : states) {
			for(U el_b : other.states) {
				new_states.push_back({el_a, el_b});
			}
		}
		std::vector<std::pair<T, U>> new_final_states;
		for(T el_a : final_states) {
			for(U el_b : other.final_states) {
				new_final_states.push_back({el_a, el_b});
			}
		}
		std::function<std::pair<T, U>(std::pair<T, U>, char)> transitions = [=](std::pair<T, U> current_state, char letter) -> std::pair<T, U> {
			return {this->transition_function(current_state.first, letter), other.transition_function(current_state.second, letter)};
		};
		return DFA<std::pair<T, U>>(new_states, alphabet, transitions, {initial_state, other.initial_state}, new_final_states);
	}

private:
	std::vector<T> states;
	std::unordered_set<char> alphabet;
	std::function<T(T, char)> transition_function;
	T initial_state;
	std::vector<T> final_states;
};