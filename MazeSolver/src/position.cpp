#include <sstream>
#include "position.h"

position::position(int row, int col)
        : m_row(row), m_col(col) {
}

position::position() = default;

bool position::operator==(position position) {
    return (this->m_row == position.m_row) && (this->m_col == position.m_col);
}

bool position::operator!=(position position) {
    return (this->m_row != position.m_row) || (this->m_col != position.m_col);
}

std::ostream &operator<<(std::ostream &output, position position) {
    output << "(" << position.m_row << ")" << "(" << position.m_col << ")";
    return output;
}