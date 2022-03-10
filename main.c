/////////////////////////////////////////////////
//
//	main.c
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
//      Filename:                main.c
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[])
{
        FILE *fptr;
        char fileName[100];
        bool b_flag;

//
//What follows is cmdline functionality
//Some notes
//argv[0] points to the name of the program itself
//argv[1] would be the first arg
//
//argc would be 1 if no arguments were passed
//argc would be 2 if one arg were passed
//

	if(argc == 2)                                                   //means we were passed just a filename. Later if the filename ain't valid, the program just won't do anything
	{
		printf("You entered just a filename: %s\n\n", argv[1]);
		b_flag = false;
		strcpy(fileName, argv[1]);
	}
	else if (argc == 3)                                             //means we were passed two args. They have to be in the sequence flags and then filename
	{
		printf("you entered a filename and the b flag\n\n");
		printf(argv[1]);
		if(strcmp(argv[1], "-b") == 0)                          //check to see if the -b flag was entered correctly
		{
			printf("Your first arg was %s\n", argv[1]);
			printf("Your 2nd arg was %s\n", argv[2]);
			b_flag = true;
			strcpy(fileName, argv[2]);
		}
                else                                                    //if the -b flag wasn't input correctly, we aren't working today
                {
                        printf("\nYour first flag may only be '-b' if you throw a binary flag. Try again.\n");
                        exit(0);
                }
        }
        else if (argc > 3)                                              //means we got too many arguments
        {
                printf("You passed too many arguments. Try _program name_ _FileName_ _Binary Flag optional(-b)_\n");
                exit(0);
        }
        else                                                            //means we were not passed a filename
        {
                printf("You didn't pass enough arguments. Try _program name_ _FileName_ _Binary Flag optional (-b)_\n");
                exit(0);
        }

//
//What precedes is cmdline functionality
//What follows is the and data retrieval and printing from the entered file, whether hex or bin
//
        //file opened
	fptr = fopen(fileName, "r");

	//check for file open failure
	if(fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}

	//enter either hexDump or binDump based on whether binary flag is set   
	if(!b_flag)     hexDump(fptr);
	else            binDump(fptr);

	//close file and return
	fclose(fptr);
	return 0;
}

/////////////////////////////////////////////////
//
//	End of File
//
/////////////////////////////////////////////////
