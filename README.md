XOdia_judge
===========

Xodia is a simple contest consisting of two programs (XOdia currently supports c/c++ bots) which play against each other on a platform created or provided to the Judge.

DOCUMENTATION:
-------------

JUDGE V.2 (INITIAL COMMITED VERSION):
	Requirements:
		- Python v2.7 
		- Platform for game-play.(I have used grid.txt which is a modified sudoku grid, which bots will capture to score maximum points. More description below)
		- Two bots (as of now only c/c++ programs) whose names are to be passed to the Judge as arguments.
		- An external shell/bash/batch script to call the Judge with required arguments. (NOTE: Script is not necessary, but is recommended in contest environment)

	Execution:
		You should have following files in same folder as judge:
			-Bot1 and Bot2 programs (.c/cpp files)
			-Grid.txt (Gameplay platform)

		Use
			"python judge.py <bot1_file_name> <bot2_file_name>"
		to execute the judge.

		A log file will be created consisting of all the moves played by bot1 and bot2.
		The file follows following nomenclature: <bot1_file_name>.<bot2_file_name>.log

	Expectations from V3:
		-Secure Resource limits
		-V2 follows Linear programming style, It will be converted to functional.
		-The game-play platform and rules will be generalized.
		-Support for more Languages. (Python at priority)

DETAILS ON GRID.TXT:
	It contains a 18x18 sudoku grid, which give weight to each block of array. Followed by 18x18 Sudoku grid is a blank linear 324 (18*18) array filled with dots.
	The dots will be replaced by X/x or an O/o Depending on which bot captures it.

	Thus Initially the grid.txt must look like:

	2 4 8 3 9 5 7 1 6 1 4 5 3 2 7 6 9 8 
	5 7 1 6 2 8 3 4 9 8 3 9 6 5 4 1 2 7 
	9 3 6 7 4 1 5 8 2 6 7 2 9 1 8 5 4 3 
	6 8 2 5 3 9 1 7 4 4 9 6 1 8 5 3 7 2 
	3 5 9 1 7 4 6 2 8 2 1 8 4 7 3 9 5 6 
	7 1 4 8 6 2 9 5 3 7 5 3 2 9 6 4 8 1 
	8 6 3 4 1 7 2 9 5 3 6 7 5 4 2 8 1 9 
	1 9 5 2 8 6 4 3 7 9 8 4 7 6 1 2 3 5 
	4 2 7 9 5 3 8 6 1 5 2 1 8 3 9 7 6 4 
	3 2 9 6 5 7 8 4 1 5 3 4 6 7 8 9 1 2 
	7 4 5 8 3 1 2 9 6 6 7 2 1 9 5 3 4 8 
	6 1 8 2 4 9 3 7 5 1 9 8 3 4 2 5 6 7 
	1 9 3 4 6 8 5 2 7 8 5 9 7 6 1 4 2 3 
	2 7 6 1 9 5 4 8 3 4 2 6 8 5 3 7 9 1 
	8 5 4 3 7 2 6 1 9 7 1 3 9 2 4 8 5 6 
	4 3 2 7 1 6 9 5 8 9 6 1 5 3 7 2 8 4 
	5 8 7 9 2 3 1 6 4 2 8 7 4 1 9 6 3 5 
	9 6 1 5 8 4 7 3 2 3 4 5 2 8 6 1 7 9
	....................................................................................................................................................................................................................................................................................................................................

	Now, Let Bot1 = X and Bot2 = Y

	X places its move at coordinated(0,3), the grid.txt should look like:

	2 4 8 3 9 5 7 1 6 1 4 5 3 2 7 6 9 8 
	5 7 1 6 2 8 3 4 9 8 3 9 6 5 4 1 2 7 
	9 3 6 7 4 1 5 8 2 6 7 2 9 1 8 5 4 3 
	6 8 2 5 3 9 1 7 4 4 9 6 1 8 5 3 7 2 
	3 5 9 1 7 4 6 2 8 2 1 8 4 7 3 9 5 6 
	7 1 4 8 6 2 9 5 3 7 5 3 2 9 6 4 8 1 
	8 6 3 4 1 7 2 9 5 3 6 7 5 4 2 8 1 9 
	1 9 5 2 8 6 4 3 7 9 8 4 7 6 1 2 3 5 
	4 2 7 9 5 3 8 6 1 5 2 1 8 3 9 7 6 4 
	3 2 9 6 5 7 8 4 1 5 3 4 6 7 8 9 1 2 
	7 4 5 8 3 1 2 9 6 6 7 2 1 9 5 3 4 8 
	6 1 8 2 4 9 3 7 5 1 9 8 3 4 2 5 6 7 
	1 9 3 4 6 8 5 2 7 8 5 9 7 6 1 4 2 3 
	2 7 6 1 9 5 4 8 3 4 2 6 8 5 3 7 9 1 
	8 5 4 3 7 2 6 1 9 7 1 3 9 2 4 8 5 6 
	4 3 2 7 1 6 9 5 8 9 6 1 5 3 7 2 8 4 
	5 8 7 9 2 3 1 6 4 2 8 7 4 1 9 6 3 5 
	9 6 1 5 8 4 7 3 2 3 4 5 2 8 6 1 7 9
	.xXx...............xxx..............................................................................................................................................................................................................................................................................................................

	Y places its move at coordinated(1,2), the grid.txt should look like:

	2 4 8 3 9 5 7 1 6 1 4 5 3 2 7 6 9 8 
	5 7 1 6 2 8 3 4 9 8 3 9 6 5 4 1 2 7 
	9 3 6 7 4 1 5 8 2 6 7 2 9 1 8 5 4 3 
	6 8 2 5 3 9 1 7 4 4 9 6 1 8 5 3 7 2 
	3 5 9 1 7 4 6 2 8 2 1 8 4 7 3 9 5 6 
	7 1 4 8 6 2 9 5 3 7 5 3 2 9 6 4 8 1 
	8 6 3 4 1 7 2 9 5 3 6 7 5 4 2 8 1 9 
	1 9 5 2 8 6 4 3 7 9 8 4 7 6 1 2 3 5 
	4 2 7 9 5 3 8 6 1 5 2 1 8 3 9 7 6 4 
	3 2 9 6 5 7 8 4 1 5 3 4 6 7 8 9 1 2 
	7 4 5 8 3 1 2 9 6 6 7 2 1 9 5 3 4 8 
	6 1 8 2 4 9 3 7 5 1 9 8 3 4 2 5 6 7 
	1 9 3 4 6 8 5 2 7 8 5 9 7 6 1 4 2 3 
	2 7 6 1 9 5 4 8 3 4 2 6 8 5 3 7 9 1 
	8 5 4 3 7 2 6 1 9 7 1 3 9 2 4 8 5 6 
	4 3 2 7 1 6 9 5 8 9 6 1 5 3 7 2 8 4 
	5 8 7 9 2 3 1 6 4 2 8 7 4 1 9 6 3 5 
	9 6 1 5 8 4 7 3 2 3 4 5 2 8 6 1 7 9
	yyXX..............yYyX..............................................................................................................................................................................................................................................................................................................