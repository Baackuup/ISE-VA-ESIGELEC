#include <stdio.h>
#include "Shapes.h"
#include "Matrices.h"
#include "SignMatrix.h"

void SetElement (int Line, int Column)
//Illuminate the matrix element
{
	printf ("*");
}

void ResetElement (int Line, int Column)
//Extinguish the matrix element
{
	printf (" ");
}

void DrawMatrix(enum ArrowStyle ThisArrow, BOOL bForward, BOOL bLeft)
{
	int StartLine=0;
	int EndLine=MATRIXSIZE;
	int LineIncrement=1;
	
	int StartColumn=0;
	int EndColumn=MATRIXSIZE;
	int ColumnIncrement=1;
	
	int Line;
	int Column;

	//First check for display which contains no arrows
	if (ThisArrow!=Stop && ThisArrow != Exclaim) goto AssessArrow;

Display:

	Line=StartLine;
	
	do
	{
		Column=StartColumn;
		do
		{
			if (ArrowStyleMatrix[ThisArrow][Line][Column])
				SetElement(Line,Column);
			else
				ResetElement(Line,Column);			
			Column+=ColumnIncrement;
		} while (Column!=EndColumn);
		
		Line+=LineIncrement;
		printf ("\n");
	} while (Line!=EndLine);
	printf ("\n");
	
	return;

AssessArrow:
		
	//This is an arrow display
	//Vary sequence order dependent on orientation
	if (!bForward)
	{
		StartLine=MATRIXSIZE-1;
		EndLine=-1;
		LineIncrement=-1;
	}

	if (!bLeft)
	{
		StartColumn=MATRIXSIZE-1;
		EndColumn=-1;
		ColumnIncrement=-1;
	}
goto Display;
}



void DrawArrow(enum Action ThisWay)
{
	BOOL bLeft;
	BOOL bForward;
	enum ArrowStyle ThisArrowStyle;
	
	switch (ThisWay)
	{
		case N:
			ThisArrowStyle=Straight;
			bForward=TRUE;
			bLeft=TRUE;
			break;
		case NE:
			ThisArrowStyle=Angled;
			bForward=TRUE;
			bLeft=FALSE;
			break;
		case SE:
			ThisArrowStyle=Angled;
			bForward=FALSE;
			bLeft=FALSE;
			break;
		case S:
			ThisArrowStyle=Straight;
			bForward=FALSE;
			bLeft=TRUE;
			break;
		case SW:
			ThisArrowStyle=Angled;
			bForward=FALSE;
			bLeft=TRUE;
			break;
		case NW:
			ThisArrowStyle=Angled;
			bForward=TRUE;
			bLeft=TRUE;
			break;
		case Wait:
			ThisArrowStyle=Stop;
			break;
		case Refuge:
			ThisArrowStyle=Exclaim;
			break;
		default:
			ThisArrowStyle=Straight;
			bForward=FALSE;
			bLeft=TRUE;
			break;
	}
	DrawMatrix(ThisArrowStyle, bForward, bLeft);
}


		
	
	
	
