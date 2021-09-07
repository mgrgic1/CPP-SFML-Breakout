#include "StateManager.hpp"


	void StateManager::LoadState(std::unique_ptr<State> addingState, bool replace) 
	{
		this->adding = true;
		this->replacing = replace;
		this->newState = std::move(addingState);
	}

	void StateManager::RemoveState() 
	{
		this->removing = true;
	}

	//handling state changes such as adding, removing, or deleting a state
	//since individual behaviors are not called, this void function will handle all of it
	//called in Game loop
	void StateManager::ProcessStateChanges() 
	{
		if(this->removing && !this->stateStack.empty()) {
			this->stateStack.pop();

			if(!this->stateStack.empty()) {
				this->stateStack.top()->Resume();
			}

			this->removing = false;
		} //removing state


		if(adding) 
		{
			if(!this->stateStack.empty()) 
			{
				if(this->replacing) {
					this->stateStack.pop();
				}
				else {
					this->stateStack.top()->Pause();
				}

			}

			this->stateStack.push(std::move(this->newState));
			this->stateStack.top()->Start();
			this->adding = false;
		}//adding state

	}//end process state changes

	std::unique_ptr<State>& StateManager::CurrentState()
	{

		return this->stateStack.top();
	}