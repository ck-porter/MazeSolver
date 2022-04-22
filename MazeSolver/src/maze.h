#ifndef ASSIGNMENT_2_MAZE_H
#define ASSIGNMENT_2_MAZE_H

#include "position.h"
#include "stack.h"

class maze {
public:
    maze() = default;

    void maze_remove_char(char maze[][52]);

    void print_solution(char maze[][52], stack stack);

    void solve_maze(char maze[][52], char **argv);

    void save_solution(char maze[][52], char **argv);

    void load_maze(int argc, char **argv);
};


#endif //ASSIGNMENT_2_MAZE_H
