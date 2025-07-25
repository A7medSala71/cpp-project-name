#include "GUI.h"

GUI::GUI()
{

	width = 1300;
	height = 700;
	wx = 5;
	wy = 5;


	StatusBarHeight = 50;
	ToolBarHeight = 50;
	MenuIconWidth = 80;

	DrawColor = DARKGREEN;	//default Drawing color
	FillColor = WHITE;	//default Filling color
	MsgColor = BLUE;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use it for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames
	IsFilled = false;


	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");

	CreateDrawToolBar();
	CreateStatusBar();
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if( Label.size() > 0)	
				Label.resize(Label.size() - 1);
			else
				Key = '\0';		
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	//[1] If user clicks on the Toolbar
	if (y >= 0 && y < ToolBarHeight)
	{
		//Check whick Menu icon was clicked
		//==> This assumes that menu icons are lined up horizontally <==
		int ClickedIconOrder = (x / MenuIconWidth);
		//Divide x coord of the point clicked by the menu icon width (int division)
		//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

		switch (ClickedIconOrder)
		{
		case ICON_RECT: return DRAW_RECT;
		case ICON_TRI: return DRAW_TRI;
		case ICON_Line: return DRAW_LINE;
		case ICON_Sqr: return DRAW_Sqr;
		case ICON_Circ: return DRAW_CIRC;
		case ICON_Oval: return Draw_Oval;
		case ICON_RegPol: return Draw_RegPol;
		case ICON_Pol: return Draw_Pol;
		case ICON_Undo: return UNDO;
		case ICON_Redo: return REDO;
		case ICON_Select: return Select_Shape;
		case ICON_ChngPenCol: return CHNG_DRAW_CLR;
		case ICON_ChngFillCol: return CHNG_FILL_CLR;
		case ICON_StickIMG: return STICK_IMG;
		case ICON_ColorPalet: return Palette;

		case ICON_EXIT: return EXIT;

		default: return EMPTY;	//A click on empty place in desgin toolbar
		}
	}

	//[2] User clicks on the drawing area
	if (y >= ToolBarHeight && y < height - StatusBarHeight)
	{
		return DRAWING_AREA;
	}

	//[3] User clicks on the status bar
	return STATUS;
	

}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() 
{

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu icon
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_TRI] = "images\\MenuIcons\\Menu_Tri.jpg";
	MenuIconImages[ICON_Line] = "images\\MenuIcons\\Menu_Line.jpeg";
	MenuIconImages[ICON_Sqr] = "images\\MenuIcons\\Menu_Sqr.jpeg";
	MenuIconImages[ICON_Circ] = "images\\MenuIcons\\Menu_Circ.jpeg";
	MenuIconImages[ICON_Oval] = "images\\MenuIcons\\Menu_Oval.jpeg";
	MenuIconImages[ICON_RegPol] = "images\\MenuIcons\\Menu_RegPol.jpeg";
	MenuIconImages[ICON_Pol] = "images\\MenuIcons\\Menu_Pol.jpeg";
	MenuIconImages[ICON_Undo] = "images\\MenuIcons\\Menu_Undo.jpeg";
	MenuIconImages[ICON_Redo] = "images\\MenuIcons\\Menu_Redo.jpeg";
	MenuIconImages[ICON_Select] = "images\\MenuIcons\\Menu_Select.jpeg";
	MenuIconImages[ICON_ChngPenCol] = "images\\MenuIcons\\Menu_ChgPenCol.jpeg";
	MenuIconImages[ICON_ChngFillCol] = "images\\MenuIcons\\Menu_Fill.jpeg";
	MenuIconImages[ICON_StickIMG] = "images\\MenuIcons\\Menu_StickIMG.jpeg";
	MenuIconImages[ICON_ColorPalet] = "images\\MenuIcons\\Menu_ColPalet.jpeg";


	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu icon and add it to the list

	//Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////



void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
window* GUI::GetWindow() const
{
	return pWind;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

void GUI::SetCrntDrawColor(color c)
{
	DrawColor = c;
}

void GUI::SetCrntFillColor(color c)
{
	FillColor = c;
}

color GUI::getBGColor() const
{
	return BkGrndColor;
}

bool GUI::getIsFilled() const
{
	return IsFilled;
}

void GUI::enableFilling()
{
	IsFilled = true;
}

void GUI::disableFilling()
{
	IsFilled = false;
}

void GUI::setIsFilled(bool filled)
{
	IsFilled = filled;
}


//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

	if (RectGfxInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = RectGfxInfo.DrawClr;
}

void GUI::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const
{
	color DrawingClr;
	if (LineGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);

	if (LineGfxInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = LineGfxInfo.DrawClr;
}

void GUI::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const
{
	color DrawingClr;
	if (TriGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);


	if (TriGfxInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = TriGfxInfo.DrawClr;
}

void GUI::DrawSquare(Point center, int length, GfxInfo SquareGfxInfo) const
{
	color DrawingClr;
	if (SquareGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SquareGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;
	Point P1 = { center.x - length / 2, center.y - length / 2 };
	Point P2 = { center.x + length / 2, center.y + length / 2 };

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

	if (SquareGfxInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = SquareGfxInfo.DrawClr;

}
void GUI::DrawCircle(Point center, int radius, GfxInfo CircleInfo) const
{
	color DrawingClr;
	if (CircleInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = CircleInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircleInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircleInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawCircle(center.x,center.y,radius, style);

	if (CircleInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = CircleInfo.DrawClr;
}
void GUI::DrawOval(Point center, int Horizontal_diam, int Vert_diam, GfxInfo OvalInfo) const
{
	color DrawingClr;
	if (OvalInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = OvalInfo.DrawClr;

	pWind->SetPen(DrawingClr, OvalInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (OvalInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(OvalInfo.FillClr);
	}
	else
		style = FRAME;
	Point P1 = { center.x - Horizontal_diam / 2, center.y - Vert_diam / 2 };
	Point P2 = { center.x + Horizontal_diam / 2, center.y + Vert_diam / 2 };

	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
	


	if (OvalInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = OvalInfo.DrawClr;
}
void GUI::DrawPol(int numofvert, int* arr_x, int*arr_y, GfxInfo PolInfo) const
{
	color DrawingClr;
	if (PolInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = PolInfo.DrawClr;

	pWind->SetPen(DrawingClr, PolInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (PolInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(PolInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawPolygon(arr_x,arr_y,numofvert,style);

	if (PolInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = PolInfo.DrawClr;
}
void GUI::DrawRegPol(int numofvert, int* arr_x, int* arr_y, GfxInfo RegPolInfo) const
{
	color DrawingClr;
	if (RegPolInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RegPolInfo.DrawClr;

	pWind->SetPen(DrawingClr, RegPolInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RegPolInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RegPolInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawPolygon(arr_x, arr_y, numofvert, style);

	if (RegPolInfo.isSelected)
		DrawingClr = HighlightColor;
	else
		DrawingClr = RegPolInfo.DrawClr;
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

