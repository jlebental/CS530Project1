#################################################
##
##	makefile
##
#################################################
##
##	My name:                 Jared Lebental
##      RedId:                   820170306
##      partners' names:         N/A
##      class account username:  cssc0419@edoras.sdsu.edu
##      partners' acct username: N/A
##      Class Information:       CS530, Spring 2022
##      Assignment Information:  Project #1, xed
##      Filename:                makefile
##
#################################################

xed: main.o hexDump.o binDump.o printBinData.o
	gcc main.o hexDump.o binDump.o printBinData.o -o xed

hexDump.o: hexDump.c functions.h
	gcc -c hexDump.c

binDump.o: binDump.c functions.h
	gcc -c binDump.c

printBinData.o: printBinData.c functions.h
	gcc -c printBinData.c

clean:
	rm *.o xed

clean_objects:
	rm *.o

#################################################
##
##	End of File
##
#################################################
