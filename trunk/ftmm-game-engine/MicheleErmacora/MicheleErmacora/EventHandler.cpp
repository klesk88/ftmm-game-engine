

#include "EventHandler.h";

EventHandler::EventHandler(){

	std::vector <Event*>* vector_of_events = new std::vector <Event*>(3,nullptr);
	input=vector_of_events->begin();
	physics=vector_of_events->begin()+1;
	ai=vector_of_events->begin()+2;
	

}


void EventHandler::addEvents(Event* ev){
	

	//if(std::type_info.name(ev=="")
	vector_of_events->insert(returnIndex(input,ai,ev->getPriority()),ev);
		//increment the iterator pointing to the position of the other 2 events
		physics++;
		ai++;
	//if(std::type_info.name(ev=="")
		vector_of_events->insert(returnIndex(ai,physics,ev->getPriority()),ev);
		ai++;
	//if(std::type_info.name(ev=="")
		vector_of_events->insert(returnIndex(physics,vector_of_events->end(),ev->getPriority()),ev);
}

std::vector<Event*>::iterator EventHandler::returnIndex(std::vector<Event*>::iterator begin,std::vector<Event*>::iterator end,int priority){
	std::vector<Event*>::iterator i;

	for(i=begin; i!=end;i++){
		if(priority>(*i)->getPriority())//if the priority of the event is greater then the priority off the first member of the vector
		{	
			
			return i;
		}
		else{
			/*
				if the priority of the event I want to put in the vector is equal to the actual priority
				of the element already present in the vector, and also the last element of the vector
				have the same priority, so that means all the lements from now on have the same priority, 
				put the element in the end.
			*/
			if(priority==(*i)->getPriority() && priority==(*(end-1))->getPriority())
			{
				return i;
			}
		}
		
	}


}


void EventHandler::removeEvents(){
	
		vector_of_events->erase(vector_of_events->begin());//remove the event in first position because is the event compelete
	}

std::vector<Event*> * EventHandler::returnVectorOfEvents(){

	return &(*vector_of_events);
}

std::vector<Event*>::iterator EventHandler::returnAiStartPointer(){

	return ai;
}

std::vector<Event*>::iterator EventHandler::returnInputStartPointer(){

	return input;
}

std::vector<Event*>::iterator EventHandler::returnPhysicsStartPointer(){

	return physics;
}

std::vector<Event*>::iterator EventHandler::returnAiEndPointer(){

	return vector_of_events->end();
}

std::vector<Event*>::iterator EventHandler::returnPhysicsEndPointer(){

	return ai-1;
}

std::vector<Event*>::iterator EventHandler::returnInputEndPointer(){

	return physics-1;
}