/////////////////////////////////////////////////
//
//	printBinData.c
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
//      Filename:                printBinData.c
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>

void printBinData(bool array[48], int i)
{
	//what I need here is an array with 8 entries
	printf("%d%d%d%d%d%d%d%d ", array[(8*i) + 7], array[(8*i) + 6],
				    array[(8*i) + 5], array[(8*i) + 4],
				    array[(8*i) + 3], array[(8*i) + 2],
				    array[(8*i) + 1], array[(8*i) + 0]);
	return;
}

/////////////////////////////////////////////////
//
//	End of File
//
/////////////////////////////////////////////////
