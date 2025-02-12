#ifndef Matrices_H
#define Matrices_H

GuideMatrix ArrowStyleMatrix [SUBMATRIXTYPECOUNT]=
//Straight  
{FALSE,FALSE,TRUE ,FALSE,FALSE,
 FALSE,TRUE ,TRUE ,TRUE ,FALSE,
 TRUE ,FALSE,TRUE ,FALSE,TRUE ,
 FALSE,FALSE,TRUE ,FALSE,FALSE,
 FALSE,FALSE,TRUE ,FALSE,FALSE,
//Angled  
 TRUE ,TRUE ,TRUE ,TRUE ,FALSE,
 TRUE ,TRUE ,FALSE,FALSE,FALSE,
 TRUE ,FALSE,TRUE ,FALSE,FALSE,
 TRUE ,FALSE,FALSE,TRUE ,FALSE,
 FALSE,FALSE,FALSE,FALSE,TRUE ,
//Exclaim
 FALSE,TRUE ,TRUE ,TRUE ,FALSE,
 FALSE,TRUE ,TRUE ,TRUE ,FALSE,
 FALSE,TRUE ,TRUE ,TRUE ,FALSE,
 FALSE,FALSE,FALSE,FALSE,FALSE,
 FALSE,TRUE ,TRUE ,TRUE ,FALSE,
//Stop
 FALSE,TRUE ,TRUE ,TRUE ,FALSE,
 TRUE ,FALSE,FALSE,FALSE,TRUE ,
 TRUE ,TRUE ,TRUE ,TRUE ,TRUE ,
 TRUE ,FALSE,FALSE,FALSE,TRUE ,
 FALSE,TRUE ,TRUE ,TRUE ,FALSE} ;

Instruction MatrixTexts[MATRIXSCREENS]=
{	"Clear screen",
	"Move ahead",
	"Move ahead, keep right",
	"Turn around, move ahead, keep left",
	"Turn around, move ahead",
	"Turn around, move ahead, keep right",
	"Move ahead, keep left",
	"Stop and wait for assistance",
	"Go to refuge"
	};

#endif