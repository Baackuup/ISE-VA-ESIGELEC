#include <stdio.h>
#include "Shapes.h"
#include "SignMatrix.h"
#include "SignCommandExt.h"

void Announce(enum Action ThisAction)
{
	printf("%s\n\n",MatrixTexts[ThisAction]);
}

void UpdateDisplay(enum Action ThisAction)
{
	DrawArrow(ThisAction);
	Announce(ThisAction);
}

void WaitForHelp()
{
	UpdateDisplay(Wait);
}

void UseRefuge()
{
	UpdateDisplay(Refuge);
}

void SpecifyArrow()
{
	enum Action Choice=Clear;
	static int MaxChoice=NW;
	int Count;

	printf(" \n");
	for (Count=0; Count<ARROWSCREENS; Count++)
	{
		printf("(%d) %s \n",Count,MatrixTexts[Count]);
	}
	scanf("%d",&Choice);
	printf ("\n");

	if (N<=Choice && MaxChoice>=Choice)
		UpdateDisplay(Choice);
}

int SignCommand(void)
{ 
	int Quit=0;
	int Choice=0;
	static int MaxChoice=3;
	while (!Quit)
	{
		printf(" \n \n(0) Quit (1) Follow arrows (2) No Entry (3) Use Refuges \n");
		scanf("%d",&Choice);
		printf ("\n");

		if (0<=Choice && MaxChoice>=Choice)
		{
			switch (Choice)
			{
				case 0:
					Quit=1;
					break;
				case 1:
					// Follow arrows
					{
						SpecifyArrow();
						break;
					}
				case 2:
					// Wait for help
					{
						WaitForHelp();
						break;
					}
				case 3:
					// Use Refuges
					{
						UseRefuge();
						break;
					}
			}
		}
	}
    return 0;
}
