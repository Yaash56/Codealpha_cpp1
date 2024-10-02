#include <iostream>
#include <vector>

#define UNASSIGNED 0  

using namespace std;
class SudokuSolver {
public:
    bool SolveSudoku(std::vector<std::vector<int>>& grid) {
        int row, col;

        
        if (!FindUnassignedLocation(grid, row, col))
            return true;  // Puzzle is solved

        
        for (int num = 1; num <= 9; num++) {
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;

            
                if (SolveSudoku(grid))
                    return true;
                grid[row][col] = UNASSIGNED;
            }
        }
        return false;  
    }

    void printGrid(const std::vector<std::vector<int>>& grid) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                cout << grid[row][col] << " ";
            }
            cout << endl;
        }
    }

private:
    bool FindUnassignedLocation(const std::vector<std::vector<int>>& grid, int& row, int& col) {
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 9; col++) {
                if (grid[row][col] == UNASSIGNED)
                    return true;
            }
        }
        return false;
    }

    bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
        return !UsedInRow(grid, row, num) &&
               !UsedInCol(grid, col, num) &&
               !UsedInBox(grid, row - row % 3, col - col % 3, num);
    }

    bool UsedInRow(const std::vector<std::vector<int>>& grid, int row, int num) {
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == num)
                return true;
        }
        return false;
    }

    bool UsedInCol(const std::vector<std::vector<int>>& grid, int col, int num) {
        for (int row = 0; row < 9; row++) {
            if (grid[row][col] == num)
                return true;
        }
        return false;
    }

    bool UsedInBox(const std::vector<std::vector<int>>& grid, int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;
            }
        }
        return false;
    }
};

int main() {

    std::vector<std::vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver;

    if (solver.SolveSudoku(grid)) {
        cout << "Sudoku Solved!" << endl;
        solver.printGrid(grid);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

