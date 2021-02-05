-COSC1252/1254 - Assignment 1 - Data Structures----------------------------------
Implement reading two files: a dictionary and a textfile using the following 
datastructures:
	std::list	std::vector	std::set
	custom list	custom binary search tree 
Count the number of occurances of the words in textfile that are found in 
dictionary. For the words not found in dictionary, calculate the edit distance for
that word and return the closest match. Save all results in an output file and 
then time and profile the performance of these datastructures. Record the results 
in a comparison report. 

-Getting Started-----------------------------------------------------------------
Source files included in this submission are: 
	my_list.cpp	my_list.h
	my_vector.cpp	my_vector.h
	my_set.cpp	my_set.h
	c_list.cpp	c_list.h
	c_bst.cpp	c_bst.h
	Makefile

-Prerequisites-------------------------------------------------------------------
This can be run on RMIT core teaching servers (jupiter, saturn, titan)

-Installing----------------------------------------------------------------------
1. Ensure all source files for the datastructure are within the same directory.
2. Compile the program using 'make'. This will call on Makefile to compile all
   the source files.
3. Run the program by issuing the following command in console:
./a1 -s [datastructure] -d [dictionary.txt] -t [textfile.txt] -o [output.txt]
	datastructure:	choose from: list, vector, set, clist, cbst
	dictionary:	your textfile that contains unique words separated by \n
	textfile:	your textfile that contains words and deliminators, 
			some words may appear more than once.
	output:		specify a file to store the results of the running of the 
			datastructure.

-Running the program------------------------------------------------------------
1. After issuing the command to run, console should print your commands.
   Specifing which datastructure was selected, which file is used for dictionary,
   which file is used for textfile, and the output file to be used.
2. There should be a new file created that is saved in the same directory under
   the name specified for output file. This should contain the results of the
   datastructure of the running of the program. Word count and closest matches.

-Built With----------------------------------------------------------------------
N/A

-Authors-------------------------------------------------------------------------
Christine Huynh (s3438653)

-Acknowledgments-----------------------------------------------------------------
Paul Miller - source material intlist (.cpp, .h)
Various authors - stackoverflow.com
Various authors - codereview.stackexchange.com