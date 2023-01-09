#include <iostream> 
#include <vector>
#include <array>

void DisplayCellsRow(const std::vector<bool>& cells);
std::vector<bool> ProcessCells(const std::vector<bool>& cells, const std::array<bool, 8>& rule);


int main()
{
	// declare a variable for the number of cells in a row (50) 
	int numCells = 50;
		// declare a variable for the number of iterations (40) 
	int iterations = 40;

		// create vector of cell states boolean (true = alive/false = dead) 
		// there is a constructor that allows you to provided the number of elementsand the default value(int, bool)
		std::vector<bool> cells(numCells, false);
		cells[numCells / 2] = true;

	system("Color F9");

	//rules:
	std::array<bool, 8> rule30 = { 0, 0, 0, 1, 1, 1, 1, 0 };
	std::array<bool, 8> rule90 = { 0, 1, 0, 1, 1, 0, 1, 0 };
	std::array<bool, 8> rule110 = { 0, 1, 1, 0, 1, 1, 1, 0 };
	std::array<bool, 8> rule184 = { 1, 0 ,1, 1, 1, 0, 0, 0 };

	// display each iteration 
	for (int i = 0; i < iterations; i++)
	{
		DisplayCellsRow(cells);
		cells = ProcessCells(cells, rule110);
	}
}

void DisplayCellsRow(const std::vector<bool>& cells)
{
	// display a row of cells to the console 
	// display a 'X' if the cell is alive (true) or a '-' if dead (false) 
	// place a space between characters 
	// example: - - X X - - X - - - X - - 
	for (auto cell : cells)
	{
		cell ? std::cout << "X " : std::cout << "- ";
	}
	// go to the next line after displaying the row 
	std::cout << std::endl;
}

std::vector<bool> ProcessCells(const std::vector<bool>& cells, const std::array<bool, 8>& rule)
{
	// create cells that will store the cell states after being processed 
	// use constructor that takes the number of elements to create 
	std::vector<bool> processed(cells.size());

	for (int i = 0; i < processed.size(); i++)
	{
		// get the current and neighboring cell states using (i)ndex 
		int left = i - 1;
		int center = i;
		int right = i + 1; 

	   // wrap left and right index if past the edges (left < 0 or right >= size) 
		if (left < 0) { left = processed.size() - 1; }
		if (right >= processed.size()) { right = 0; }

		bool states[3];
		states[0] = cells[left];
		states[1] = cells[i];
		states[2] = cells[right];

		bool state = false;

		// current pattern 111 110 101 100 011 010 001 000 
		// rule			    0   1   2   3   4   5   6   7 
		if (states[0] && states[1] && states[2]) state = rule[0];		  // 1 1 1
		else if (states[0] && states[1] && !states[2]) state = rule[1];   // 1 1 0
		else if (states[0] && !states[1] && states[2]) state = rule[2];   // 1 0 1
		else if (states[0] && !states[1] && !states[2]) state = rule[3];  // 1 0 0
		else if (!states[0] && states[1] && states[2]) state = rule[4];   // 0 1 1
		else if (!states[0] && states[1] && !states[2]) state = rule[5];  // 0 1 0
		else if (!states[0] && !states[1] && states[2]) state = rule[6];  // 0 0 1
		else if (!states[0] && !states[1] && !states[2]) state = rule[7]; // 0 0 0
		//<code remaining patternsand rules>

			//<set processed at(i)ndex to state>
		processed[i] = state;
	}

	return processed;
}
