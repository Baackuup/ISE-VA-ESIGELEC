#include "MatrixDrain.h"
#include "Shapes.h"

int MatrixDrain (enum Manufacturer Brand, int ElementCount)
{
	int Drain;

	switch (Brand)
	{
	case Lampy:
		Drain=3*ElementCount*LampyFactor(ElementCount);
		break;
	case MyWay:
		if (ElementCount<20)
			Drain=4*ElementCount;
		else
			Drain=3*ElementCount;
		break;
	case Matrixmagic:
		if (ElementCount<10)
			Drain=2*ElementCount;
		else
			if (ElementCount<20)
				Drain=3*ElementCount;
			else
				Drain=4*ElementCount;
		break;
	default:
		Drain=4*ElementCount;
	}
	BatteryCapacity=BatteryCapacity-Drain;
	return Drain;
}
