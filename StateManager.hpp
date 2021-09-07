#pragma once
#include <stack>
#include <memory>
#include "State.hpp"

class StateManager {

public:
	StateManager(){};
	~StateManager(){};

	void LoadState(std::unique_ptr<State> addingState, bool replace = true);
	void RemoveState();
	void ProcessStateChanges();

	std::unique_ptr<State>& CurrentState();


private:
	std::stack<std::unique_ptr<State>> stateStack;
	std::unique_ptr<State> newState;

	bool adding;
	bool removing;
	bool replacing;

};