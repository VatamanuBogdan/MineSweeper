#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include <iostream>
#include "Map.h"

using Choice = char;

class MineSweeper {
private:
    MineSweeper() = default;
public:
    MineSweeper(MineSweeper&) = delete;

    MineSweeper operator= (const MineSweeper&) = delete;

private:
    Map map;
    bool GameEnded{};
    int FoundMines{};
    const int MinesNumber = 100;
    int MarkedMines{};

    struct UserInput {
        Choice choice;
        short line, column;
        UserInput() = default;

        UserInput(char choice, short line, short column)
                : choice(choice), line(line), column(column) {
        }
    };

private:
    void DeployChain(int line, int column);

    void Init();

    void Display();

    void LoopGame();

    bool UICondition(const UserInput &c);

    UserInput GetUI(std::istream& in);

    void Mark(int line, int column);

    void Deploy(int line, int column);

    void ApplyFunction(const UserInput &ui);

    UserInput ParseUserInput(std::istream &in);

public:
    bool IsFinished();

    int GetMarkedMines();

    int GetMinesNumber();

    static MineSweeper& GetInstance();

    void Run();
};


#endif //MINESWEEPER_MINESWEEPER_H
