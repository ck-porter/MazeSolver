#ifndef ASSIGNMENT_2_POSITION_H
#define ASSIGNMENT_2_POSITION_H

#include <iostream>

class position {
public:
    int m_row;
    int m_col;

    position(int, int);

    position();

    bool operator==(position position);

    bool operator!=(position position);
};

std::ostream &operator<<(std::ostream &output, position position);

#endif //ASSIGNMENT_2_POSITION_H
