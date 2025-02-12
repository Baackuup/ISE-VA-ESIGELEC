#ifndef Shapes_H
#define Shapes_H

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

#define MATRIXSIZE 5
#define INSTRUCTIONSIZE 80
#define SUBMATRIXTYPECOUNT 4
#define MATRIXSCREENS 9
#define ARROWSCREENS 7

enum ArrowStyle {Straight=0, Angled=1, Exclaim=2, Stop=3};
enum Action {Clear=0, N=1, NE=2, SE=3, S=4, SW=5, NW=6, Wait=7, Refuge=8};
enum Manufacturer {Lampy=0, MyWay=1, Matrixmagic=2};

typedef BOOL GuideMatrix[MATRIXSIZE][MATRIXSIZE];
typedef char Instruction[INSTRUCTIONSIZE];


#endif