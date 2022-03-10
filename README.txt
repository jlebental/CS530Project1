////////////////////////////////////////////////
//
//		README.txt
//
//
//
//	My name:		 Jared Lebental
//	RedId:			 820170306
//	partners' names:	 N/A
//	class account username:  cssc0419@edoras.sdsu.edu
//	partners' acct username: N/A
//	Class Information:	 CS530, Spring 2022
//	Assignment Information:	 Project #1, xed
//	Filename:		 README.txt
//
/////////////////////////////////////////////////

		 Contents
File Manifest
	Before make || after make clean
	After make
Compile Instructions
Operating Instructions
Design Choices
Extra Functionalities
Known Bugs
	patch 1
	patch 2
Lessons learned








--------------
File Manifest (before make command OR after make clean command)
--------------

..
a1
| README.txt
| makefile
| main.c
| hexDump.c
| binDump.c
| printBinData.c
| functions.h

--------------
File Manifest (after make command)
--------------

..
a1
| README.txt
| makefile
| main.c
| hexDump.c
| binDump.c
| printBinData.c
| functions.h
| main.o
| hexDump.o
| binDump.o
| printBinData.o
| xed








--------------
Compile Instructions

	Compiling xed is done in one step through the terminal. While in the directory containing the prject, try "make" in the command line. The make program will perform all compilation on behalf of the user.








--------------
Operating Instructions
	command line options/arguments, required inputs, etc
	try "xed _file_"	Performs a hexadecimal dump of the data in the passed file. 
				The resulting output will appear as "<address>:	<B0B1> <B2B3> ... <BEBF>	123456789ABCDEF". 
				Each line will contain 8 pairs of bytes and will represent 16 bytes pulled from the passed file.
				<address> is a hexadecimal value representing the line of data's position in the program. 
					It increments by 16 line by line since it holds 16 bytes of data per line.
				<B0B1> ... all represent individual bytes of data represented in hexadecimal format.
				123... represent the human readable form of the extracted data. Non human readable characters are printed as '.'.
	
	try "xed -b _file_"	Performs a binary dump of the data in the passed file.
				Similar to the hexadecimal dump with some exceptions.
				The resulting output will appear as "<address>: bbbbbbbb ... bbbbbbbb 123456"
				Each line will contain 6 octets. Each octet represents one byte of data collected from the passed file. Each octet prints its byte in binary form.
				The addresses increase by 6 line by line.








--------------
Design Choices

In implementing xed I elected to seperate functions into different files. As a result we have not one file to compile for our program but several. This should improve human readability in our code.
We seperated a function called printBinData() from the rest of the code because it looked better to see a function saying exactly what it was doing than to see the statement the function ran to create the desired output.
More decisions were considered to isolate specific functionalities in the program to improve human readability but time and external needs from other courses prevented us from pursuing them. A project for another day.
Our main function only permits two particular types of operating instructions based on the amount of arguments passed and throws errors otherwise. See Operating instructions.









--------------
Extra Functionalities

It was not required that the program print a statement declaring the name of the file which was passed but I added this functionality. It made it easier to debug the code and see what the commandline was passing into the program.








--------------
Known bugs

try "xed xed". The following hexDump is incorrect. several points in the data print as 16byte hex values (ex: ffffffb1). Each of these points is printed as '?' in the human readable portion of the output. This ruins the blocking of the table. It is unknown at this time if this bug is prevalent just in xed or in all executable files. I know xxd can handle the hexDump properly, but my xed cannot.
The same bug is occurring when we hexdump on .o files.





----

patch 1:

 identified that every time these f's occured there was a negative value. solved by performing bitwise AND on any negative values found with the value 3. This way we keep the 2 good bits of data and dump the excess. Noticed that xxd and xed had the same 2 endbits at these locations despite all these f's.
	BUT there is still an issue. xed will make a hexdump now that is many times smaller in total addresses than xxd. example: 5d0 length vs 3300 length.
	To be honest, im getting a feelling that these f's indicate parts of the object file referring to addresses. like a format 4 instruction with 4 bytes in them. But if that were the case then why would every address be one?
	Clearly if it stops its because it found the EOF character. But then does that mean that an object file doesn't end at the first EOF? Tried a patch that went to the second EOF found in a file but it didn't work. Right now our program works on .txt files. It just hates obj code for some reason
	you can't vim the xxd program but its written and able to be read online. But I'm really out of time here. its mostly argument handling and confusing variables anyways. I just want to know how its so good at reading object files. And why object files close earlier on xed than on xxd.
	Isn't it strange that when I specify %02x it gives me 8 bits of detail? Isn't it weird that it can pull a negative value anyways? fgetc() is supposed to return an unsigned value.
	some stackexchange post said try making c an int not a char because fgetc and its relatives actually return ints not char

One bug remains: the misaddressing bug. We are not getting enough addresses even though we have solved our negative 8 bit entries problem with our bitwise & code.








----

patch 2: 

YEP FOR SOME REASON THAT WORKS. Turning c into an int rather than a char has resolved the issue. Why? Updated the binDump.c file with this cchange too. The program xed now operates as expected on executables and object files and txt files. Thats all I've tested but I suppose it'll work on anything if it works on that.

	WHY IT WORKS(and really I'm just quoting the stack exhchange here): when reading the value into a char instead of an int one of two undesirable things happens: if plain char is unsigned then you never reach EOF which is a negative value. OR if plain char is signed then a legitamate character like 0xFF is treated the same as EOF and so EOF is detected prematurely even though 0xFF is something like y-umlaut, the y with two dots over it, or some other character like that.
	So (and now i'm interpolating here) we read into an int value, the appropriate return type of fgetc() and as a result we don't accidentally find an EOF instead of an actual value. In any case it DOES work so I'm happy with the patch

No further Bugs have been detected at this time. All bugs thus for located have been resolved.







----

--------------
Lessons Learned
--------------
	Friday February 4th: 
	Learned how to sign into edoras account. Googled how to make C files in terminal, learned the following command line instructions: pwd, ls, mkdir _dirname1_ _dirName2_ etc., cd _targetDirectoryName_, cd .., Touch _fileName.fileExtenion_, Open _file_ NOTE: nonfunctional in edoras evidently, man _command_, cat _file_, vim, _file_. Learned the following Vim instructions from vim tutorial 1 on canvas: i, ESC, hjkl, u, CTRL R, dd, :w enter, :q enter, 0, $. Learned class header information for all files. Learned what goes in a README file.
	Sunday February 6th:
	Learned how to open files from a C program: fopen(_filename_, _mode_), exit(_status_), fgetc(_FILE var pointer_), fclose(_FILE var pointer_), FILE data type, r operating mode of fopen(). Learned the gcc command line instruction. Built and ran helloworld.c from cmdline. Developed and deugged hexDump.C which reads ExampleFile.txt from the same directory and prints its memory content beside its addresses 16 bytes per line first in hex code and then human readable language. Learned about C files' main() arguments: argc, *argv[]. Added cmd line functionality. Try: "a.out _filename_" to select the file we read. Next thing to develop is a binDump.c file. Also need the binary flag command line functionality to work. Still need to learn makefile. Not sure where to start at all in regards to an include file.
	Monday February 7th:
	Added cmdline functionality: Try "a.out _-b_ _filename_" to perform a binary dump. Try "a.out" to get no output not enough args or try "a.out _1_ _2_ _3_ ..." to get no output too many args. Developed and debugged binary dump, sits within hexDump.c not in its own file. Learned there is no C argument format for binary. Researched bitwise operator '&' to convert char data types into binary values. Learned gcc _filename_ -o _executable name_. Tried learning Makefiles on tutorialpoint... okay theres some tips in there but main concept is blurry. Gained true understanding of makefile concept via https://www.youtube.com/watch?v=_r7i5X0rXJk . Developed basic Makefile for program xed.
	Tuesday February 8th:
	Began parsing hexDump.c for seperable functions. Seperated binDump(), hexDump(), and printBinData() as functions. Thought of other functions to seperate: char2binarrayconv(), printHexLine(), printBinLine(), fillhexLine(), fillBinLine(), CMDLineInterpreter(), hexEOFHandler(), binEOFHandler(). Scope concerns though and I have other courses. Sufficient to create a few seperable files and use Make to organize them for now. Created new files main.c, printBinData.c, and binDump.c in addition to hexDump.c. Learned a new way to make files. Try VIM _ new file name_ and save the file while still in VIM.
	Monday February 14th:
	Learned the following command line instructions: mv _oldfilename_ _newfilename_, mv _file_ _destination filepath_, rmdir _empty directory_, scp _user@host:filepath_ _newfilename_, zip -r _outputzipfilename_ _file1_ _file2_ ..., unzip _zipfilename_ -d _destination folder_. Also try: vim _zipfile_ to vim around through the contents of a zipfile, write permitted. Moved all files to a1. Deleted C Files Directory. Updated files with headers appropriate for submission. Updated README.txt. Began troubleshooting xed for known bugs. Applied patch 1 (see known bugs). Applied patch 2. Packaged assignment for submission. 

	FINAL NOTE: fun intro project. I'm no command line programmer but this was a fun entry into it. I know enough to do this more I think now.




////////////////////////////////////////////////
//
//		END OF FILE
//
////////////////////////////////////////////////
