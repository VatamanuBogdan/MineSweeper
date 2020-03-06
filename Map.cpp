#include "Map.h"

#include <cstdlib>
#include <ctime>
#include "MineCell.h"
#include "MineSweeper.h"

Map::Map() {
    matrix.resize(Lines);
    for (int i = 0; i < Lines; i++) {
        matrix[i].resize(Columns);
    }
}

void Map::Init(int MinesNumber) {
    srand(time(nullptr));
    for (int i = 0; i < Lines; i++) {
        for (int j = 0; j < Columns; j++)
            matrix[i][j].Clear();
    }

    int line, column;
    for (int i = 0; i < MinesNumber; i++) {
        while (true) {
            line = rand() % Lines   , column = rand() % Columns;
            if (!matrix[line][column].IsMined())
                break;
        }
        Mine(line, column);
    }
}

void Map::Mine(int line, int column) {
    using namespace std;
    if (matrix[line][column].IsMined()) {
        return;
    }
    int lu = max(line - 1, 0), ld = min(line + 1, Lines - 1);
    int cl = max(column - 1, 0), cr = min(column + 1, Columns - 1);
    for (int i = lu; i <= ld; i++) {
        for (int j = cl; j <= cr; j++)
            matrix[i][j].IncValue();
    }
    matrix[line][column].SetMined(true);
}

std::ostream &operator<<(std::ostream &os, const Map &map) {
    os << "{Marked Mines " << MineSweeper::GetInstance().GetMarkedMines() << "/";
    os << MineSweeper::GetInstance().GetMinesNumber() << "}" << std::endl;
    for (int i = 0; i <= map.Columns; i++) {
        os << "____";
    }
    os << std::endl;
    os << "   | ";
    for (int i = 0; i < map.Columns; i++) {
        if (i < 9) {
            os << " ";
        }
        os << i + 1 << "  ";
    }
    os << std::endl << "---+";
    for (int i = 0; i < map.Columns; i++) {
        os << "----";
    }
    os << std::endl;
    for (int i = 0; i < map.Lines; i++) {
        os << i + 1;
        if (i < 9) {
            os << " ";
        }
        os << " | ";
        for (int j = 0; j < map.Columns; j++)
            os << map.matrix[i][j] << "  ";
        os << std::endl;
    }

    return os;
}
