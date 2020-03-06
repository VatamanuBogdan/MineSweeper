#include "MineCell.h"
#include "MineSweeper.h"

std::ostream &operator<<(std::ostream &os, const MineCell &cell) {
    if (cell.marked) {
        os << " M";
        return os;
    }

    if (cell.mined && MineSweeper::GetInstance().IsFinished()) {
        os << " B";
        return os;
    }

    if (!cell.deployed) {
        os << "[]";
        return os;
    }

    os << " " << cell.value;
    return os;
}
