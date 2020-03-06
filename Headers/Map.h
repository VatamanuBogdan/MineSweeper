#ifndef MINESWEEPER_MAP_H
#define MINESWEEPER_MAP_H

#include <vector>
#include <ostream>
#include "MineCell.h"

class Map {
private:
    const int Lines = 25;
    const int Columns = 25;
    std::vector<std::vector<MineCell>> matrix;

public:
    Map();

    ~Map() = default;

    MineCell& Get(int line, int column) {
        return matrix[line][column];
    }

    int GetLinesSize() const {
        return Lines;
    }

    int GetColumnSize() const {
        return Columns;
    }

    void Init(int MineNumber);

    void Mine(int line, int column);

    friend std::ostream &operator<<(std::ostream &os, const Map &map);
};

#endif //MINESWEEPER_MAP_H
