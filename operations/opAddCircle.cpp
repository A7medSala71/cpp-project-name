#include "opAddCircle.h"
#include"../Shapes/Circle.h"
#include"../controller.h"
#include"../GUI/GUI.h"
opAddCircle::opAddCircle(controller* pCont):operation(pCont)
{
}

opAddCircle::~opAddCircle()
{
}

void opAddCircle::Execute()
{
	Point Center;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Circle: Click at Center");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(Center.x, Center.y);

	string msg = "center is at (" + to_string(Center.x) + ", " + to_string(Center.y) + " )";

	pUI->PrintMessage("Enter Radius");
	string s = pUI->GetSrting();
	int radius = stoi(s);	

	//Preapre all rectangle parameters
	GfxInfo CircleGfxInfo;

	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pUI->getCrntDrawColor();
	CircleGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	CircleGfxInfo.isSelected = false;	//defualt is not selected


	CircleGfxInfo.isFilled = pUI->getIsFilled();
	if (CircleGfxInfo.isFilled)
		CircleGfxInfo.FillClr = pUI->getCrntFillColor();

	//Create a rectangle with the above parameters
	pCirc = new Circle(Center, radius, CircleGfxInfo);

	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pCirc);
}

void opAddCircle::Undo()
{
	Graph* pGr = pControl->getGraph();

	pGr->RemoveShape(pCirc);
}

void opAddCircle::Redo()
{
	Graph* pGr = pControl->getGraph();

	pGr->Addshape(pCirc);
}
