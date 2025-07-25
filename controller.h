#pragma once

#include "DEFS.h"
#include "Shapes\Graph.h"
#include "GUI\GUI.h"
#include<stack>
#include<iostream>
using namespace std;

class operation; //forward declaration

//Main class that manages everything in the application.
class controller
{
	Graph* pGraph;	//pointe to the grapg
	GUI* pGUI;		//Pointer to UI class
	stack<operation*> Undo_Stack;
	stack<operation*> Redo_Stack;
public:	
	controller(); 
	~controller();
	
	// -- operation-Related Functions
	//Reads the input command from the user and returns the corresponding operation type
	operationType GetUseroperation() const;
	operation* createOperation(operationType) ; //Creates an operation
	void Run();
	
	Graph* getGraph() const;
	
	// -- Interface Management Functions
	GUI *GetUI() const; //Return pointer to the UI
	void UpdateInterface() const;	//Redraws all the drawing window	
	void Undo();
	void Redo();
};

