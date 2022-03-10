/////////////////////////////////////////////////
//
//	hexDump.c
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
//      Filename:                hexDump.c
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

void hexDump(FILE *fptr)
{
	int dumpAddr = 0;	//our address counter starts at 0 and increments by 16.
	int i;			//counter index
	int c = 'f';		//initialize c to f so that it doesn't contain EOF
	int hexLine [16];	//our array holding one line of our output
	int firstEOF = 0;


	//file parsing loop
	while(c != EOF && firstEOF < 2)
	{
		//fill 16 char line array
		for(i = 0; i < 16; i++)
		{
			c = fgetc(fptr);
			if(c != EOF)    hexLine[i] = c; //if one of the 16 values we pull is EOF, we need to stop looping immediately immediately
			else break;
		}
		if(c == EOF) {firstEOF+=1; continue;}
	
		//printing address, line array hex, and line array human readables
		printf("%08x:\t", dumpAddr);
		for(i = 0; i < 16 || hexLine[i] == EOF; i += 2)
		{
			printf("%02x%02x ", hexLine[i], hexLine[i+1]);
		/*
		//ADDED FOR TESTING
			//printf("%02x ", hexLine[i]);
			if(hexLine[i] < 0)	
			{
				//printf("<- neg ");
				hexLine[i] = hexLine[i] & 3;//255;	//need the first 8 characters 1+2+4+8+16+32+64+128 = 3+12+48+192 = 15 + 240 = 255
			}
			printf("%02x ", hexLine[i]);
			if(hexLine[i] < 0)	printf(" <- neg ");
		*/
		}
		printf("\t");
		for(i = 0; i < 16; i++)
		{
			if((0 <= hexLine[i] && hexLine[i] < 32) || 128 <= hexLine[i]) printf(".");                     //checks for non human readable characters[0,31] and prints '.' in their place
			else                             printf("%c", (unsigned char)hexLine[i]);
		}
		printf("\n");
		//increment dumpAddr variable by 16
		dumpAddr += 16;
		}
	//completing the EOF line
	//EOF won't be found in line because the loop breaks before its assigned.
	//and no you don't need to increment i because its in the position EOF was found
	while(i < 16)
	{
	hexLine[i] = EOF;
	i++;
	}
	
	//printing the EOF line
	printf("%08x:\t", dumpAddr);
	for(i = 0; i < 16; i++)
	{
		if(hexLine[i] == EOF)   printf("  ");
		else                    printf("%02x", hexLine[i]);
		if(i % 2 == 1)          printf(" ");
	}
	printf("\t");
	for(i = 0; i < 16; i++)
	{
		if(0 <= hexLine[i] && hexLine[i] < 32) printf(".");
		else if (hexLine[i] == EOF)      printf(" ");
		else                             printf("%c", hexLine[i]);
	}
	printf("\n");	
}

/////////////////////////////////////////////////
//
//	End of File
//
/////////////////////////////////////////////////
