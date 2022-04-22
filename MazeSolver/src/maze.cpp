#include "maze.h"
#include <vector>
#include <fstream>

using namespace std;

void maze::maze_remove_char(char maze[][52]) {
    for (int i = 0; i < 51; i++) {
        for (int j = 0; j < 52; j++) {
            //replace all characters with blank spaces to clear the maze
            if (maze[i][j] == '@') {
                maze[i][j] = ' ';
            }
            if (j == 51)
                printf("\n");
            printf("%c", maze[i][j]);
        }
    }
}

void maze::print_solution(char maze[][52], stack stack) {

    position pos;
    pos.m_row = 1;
    pos.m_col = 1;

    //while the stack isn't empty, loop through the array
    while (stack.peek() != position(-1, -1)) {

        pos.m_col = 0;
        pos.m_row = 0;

        for (int i = 0; i < 51; i++) {
            //reset the column each time program moves down a row
            pos.m_col = 0;

            for (int j = 0; j < 52; j++) {
                //compare the position to the position in the stack, if they are the same,
                //add # to the maze to mark the solution path
                if (pos == stack.peek()) {
                    maze[i][j] = '#';
                    stack.pop();
                }
                pos.m_col++;
            }
            pos.m_row++;
        }
    }
}

void maze::solve_maze(char maze[][52], char **argv) {

    stack stack;
    position pos;
    pos.m_row = 1;
    pos.m_col = 0;

    //vector to hold the locations visited to use for backtracking when a dead end is
    //reached
    vector<char> prev;
    char prevPosition;
    bool done = false;

    while (!done) {

        //if the stack has reached row 49, col 50, the maze has been solved
        if (pos.m_row == 49 && pos.m_col == 50) {
            done = true;
            break;
        }
        //checking the right position to see if it is empty
        if (isblank(maze[pos.m_row][pos.m_col + 1])) {
            //if it is empty, add the position to the stack
            stack.push({pos.m_row, pos.m_col});
            //print a symbol to the maze to continue progressing through the maze
            maze[pos.m_row][pos.m_col] = '@';
            pos.m_col++;

            //because the stack has moved to the right, add 'R' to the vector to use
            //for backtracking as needed
            prev.push_back('R');
            continue;
        }
        //checking down position
        if (isblank(maze[pos.m_row + 1][pos.m_col])) {
            stack.push({pos.m_row, pos.m_col});
            maze[pos.m_row][pos.m_col] = '@';
            pos.m_row++;

            prev.push_back('D');
            continue;
        }
        //checking left position
        if (isblank(maze[pos.m_row][pos.m_col - 1])) {
            stack.push({pos.m_row, pos.m_col});
            maze[pos.m_row][pos.m_col] = '@';
            pos.m_col--;

            prev.push_back('L');
            continue;
        }

        //checking up position
        if (isblank(maze[pos.m_row - 1][pos.m_col])) {
            stack.push({pos.m_row, pos.m_col}); //push coordinates into stack
            maze[pos.m_row][pos.m_col] = '@';
            pos.m_row--;

            prev.push_back('U');
            continue;
        }
            //if there are no empty position to move to, begin to backtrack
        else {

            //look at the last position visited by checking the last element in the prev
            //vector this will be used to determine which direction to backtrack
            prevPosition = prev.back();

            //mark the current position with a symbol so the program won't try to move there
            //again
            maze[pos.m_row][pos.m_col] = '@';
            //delete this position from the stack as it's not part of the solution
            stack.pop();

            //this switch is used in tandem with the prev vector to backtrack according to
            //positions already travelled
            switch (prevPosition) {
                case 'R':
                    pos.m_col--;
                    break;
                case 'D':
                    pos.m_row--;
                    break;
                case 'L':
                    pos.m_col++;
                    break;
                case 'U':
                    pos.m_row++;
                    break;
            }

            prev.pop_back();
            continue;
        }
    }

    //once the stack has arrived at the end position, call the removeChar method to delete
    //all symbols added to the array
    maze_remove_char(maze);

    //once all chars have been removed, call the print_solution method to begin popping
    //positions off the stack and adding them to the maze array building the solution path
    print_solution(maze, stack);

    //once the solution has been marked on the maze, call the save method
    save_solution(maze, argv);
}

void maze::save_solution(char (*maze)[52], char **argv) {

    //create a string to hold the path and the filename passed in from user
    string path = "../solved/";
    string name = argv[2];
    string savedName = path + name;

    //write the solved maze to the file and save it in the solved folder
    ofstream output_file((savedName));
    if (output_file.is_open()) {
        for (int i = 0; i < 51; i++) {
            for (int k = 0; k < 52; k++) {
                output_file << maze[i][k];
            }
        }
        output_file.close();
    }

    cout << "Maze has been solved and saved. Exiting application." << endl;
}

void maze::load_maze(int argc, char **argv) {

    //check to see if the user has loaded in a maze, a maze and a solution name
    //must be loaded in for the program to run
    if (argc < 3) {
        cout << "Error! maze filename must be included and Save filename must be included." << endl;
        cout << "Example: EDIT <filename>" << endl;

        //exit the application if user doesn't include a maze and save file name
        EXIT_FAILURE;
    }

    //set up the initial size of the maze
    char maze[51][52];
    FILE *p;
    char ch;

    //pointer will be used to go through the maze char by char to build it into a 2d array
    p = fopen(argv[argc - 2], "r");

    while (true) {

        //check to see if the file has ended, if so, 2d array is finished construction
        if (ch == EOF) {  //end of file
            break;
        }
        for (int i = 0; i < 51; i++) {
            for (int k = 0; k < 52; k++) {
                ch = fgetc(p);
                maze[i][k] = ch;
                if (k == 52) {
                    ch = '\0';
                }
            }
        }
    }

    //solve maze requires the argv to pass to the save method and needs the newly created
    //2d array to begin solving the maze
    solve_maze(maze, argv);
}

