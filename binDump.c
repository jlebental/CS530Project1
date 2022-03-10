/////////////////////////////////////////////////
//
//	binDump.c
//
/////////////////////////////////////////////////
//
//	My name:                 Jared Lebental
//      RedId:                   820170306
//      partners' names:         N/A
//      class account username:  cssc0419@edoras.sdsu.edu
//      partners' acct username: N/A
//      Class Information:       CS530, Spring 2022
//      Assignment Information:  Project #1, xed
//      Filename:                binDump.c
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

void binDump(FILE *fptr)
{
        int dumpAddr = 0;       //dumpAddr starts at 0 and increases by 6
        int i;                  //counter index
        int c = 'f';           //c initialized to f so it isn't mistaken for EOF
        int binLine [6];       //this is our 6 char array to hold 6 bytes of memory for each line
        bool binConvLine[48];   //this 48 bit array will hold the binary pieces of the entries of binLine

        //file parsing loop
	while(c != EOF)
	{       
		//fill 6 char array
		for(i = 0; i < 6; i++)
		{       
			c = fgetc(fptr);
			if(c != EOF)    binLine[i] = c;                                                                                                                                                      else            break;                                                                                                                                                       }                                                                                                                                                                                    if(c == EOF)    continue;                                                                                                                                                            //fill 48 bit array
		for(i = 0; i < 6; i++)
		{
			binConvLine[(8 * i) + 7] = binLine[i] & 128;    //binConvLine[8i+7] = binLine[i][7]
			binConvLine[(8 * i) + 6] = binLine[i] & 64;     //binConvLine[8i+6] = binLine[i][6]
			binConvLine[(8 * i) + 5] = binLine[i] & 32;     //binConvLine[8i+5] = binLine[i][5]
			binConvLine[(8 * i) + 4] = binLine[i] & 16;     //binConvLine[8i+4] = binLine[i][4]
			binConvLine[(8 * i) + 3] = binLine[i] & 8;      //binConvLine[8i+3] = binLine[i][3]
			binConvLine[(8 * i) + 2] = binLine[i] & 4;      //binConvLine[8i+2] = binLine[i][2]
			binConvLine[(8 * i) + 1] = binLine[i] & 2;      //binConvLine[8i+1] = binLine[i][1]
			binConvLine[(8 * i) + 0] = binLine[i] & 1;      //binConvLine[8i]   = binLine[i][0]
		}

		//print address, binary data, and human readables
		printf("%08x:\t", dumpAddr);
		for(i = 0; i < 6; i++)
		{
			printBinData(binConvLine, i);
		}
		printf("\t");
		for(i = 0; i < 6; i++)
		{
			if(0 <= binLine[i] && binLine[i] < 32)  printf(".");
			else                                    printf("%c", binLine[i]);
		}
		printf("\n");

		//increment dumpAddr by 6;
		dumpAddr += 6;
	}
	//completing the EOF line
	while(i < 6)
	{
		binLine[i] = EOF;
		++i;
	}
	//converting to binary          //_FIXME: this conversion could be made into a function if I can figure out whether array values are passed back after a function call ends_
	for(i = 0; i < 6; i++)
	{
		binConvLine[(8*i) + 7] = binLine[i] & 128;
		binConvLine[(8*i) + 6] = binLine[i] & 64;
		binConvLine[(8*i) + 5] = binLine[i] & 32;
		binConvLine[(8*i) + 4] = binLine[i] & 16;
		binConvLine[(8*i) + 3] = binLine[i] & 8;
		binConvLine[(8*i) + 2] = binLine[i] & 4;
		binConvLine[(8*i) + 1] = binLine[i] & 2;
		binConvLine[(8*i) + 0] = binLine[i] & 1;
	}
	//printing address, data, and human readables
	printf("%08x:\t", dumpAddr);
	for(i = 0; i < 6; i++)
	{
		if(binLine[i] == EOF)   printf("         ");
		else                    printBinData(binConvLine, i);
	}
	printf("\t");
	for(i = 0; i < 6; i++)
	{
		if(binLine[i] == EOF)                           printf(" ");
		else if(0 <= binLine[i] && binLine[i] < 32)     printf(".");
		else                                            printf("%c", binLine[i]);
	}
	printf("\n");
}

/////////////////////////////////////////////////
//
//	End of File
//
/////////////////////////////////////////////////
