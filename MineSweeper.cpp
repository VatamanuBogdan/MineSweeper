#include "MineSweeper.h"

#include <iostream>
#include <utility>
#include <queue>

#include "MineCell.h"

void MineSweeper::Init() {
    map.Init(MinesNumber);
    GameEnded = false;
    FoundMines = 0;
    MarkedMines = 0;
}

MineSweeper &MineSweeper::GetInstance()  {
    static auto* instance =  new MineSweeper;
    return *instance;
}

bool MineSweeper::IsFinished() {
    return GameEnded;
}

int MineSweeper::GetMarkedMines() {
    return MarkedMines;
}

int MineSweeper::GetMinesNumber() {
    return MinesNumber;
}

void MineSweeper::Display() {
    if (system("CLS"))
        system("clear");
    std::cout << map << std::endl;
    std::cout << "Deploy(D) / Mark(M) <line> <column>" << std::endl;
}

void MineSweeper::DeployChain(int line, int column) {
    static const short moves = 8;
    static const short dl[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    static const short dc[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    std::queue<std::pair<int, int>> local_queue;
    std::pair<int, int> coords;
    MineCell *temp = &map.Get(line, column);
    temp->SetDeployed(true);
    if (temp->GetValue() != 0) {
        for (int i = 0; i < moves; i++) {
            if (map.Get(line + dl[i], column + dc[i]).GetValue() == 0) {
                local_queue.push({line + dl[i], column + dc[i]});
                break;
            }
        }
    }
    else {
        local_queue.push({line, column});
    }

    int size;
    while (!local_queue.empty()) {
        size = local_queue.size();
        while (size--) {
            coords = local_queue.front();
            local_queue.pop();
            for (int i = 0; i < moves; i++) {
                line = coords.first + dl[i]     ,   column = coords.second + dc[i];
                if (line < 0 || line >= map.GetLinesSize())
                    continue;

                if (column < 0 || column >= map.GetColumnSize())
                    continue;

                temp = &map.Get(line, column);
                if ( !temp->IsDeployed() && !temp->IsMarked() && !temp->IsMined()) {
                    if (temp->GetValue() == 0) {
                        local_queue.push({line, column});
                    }
                    temp->SetDeployed(true);
                }
            }
        }
    }
}

void MineSweeper::Mark(int line, int column) {
    MineCell& cell = map.Get(line, column);
    if (cell.IsDeployed())
        return;

    if (cell.IsMarked()) {
        cell.SetMarked(false);
        if (cell.IsMined()) {
            FoundMines--;
        }
        MarkedMines--;
    }
    else {
        cell.SetMarked(true);
        if (cell.IsMined()) {
            FoundMines++;
        }
        MarkedMines++;
    }
    if (FoundMines == MinesNumber) {
        GameEnded = true;
    }
}

void MineSweeper::Deploy(int line, int column) {
    MineCell& cell = map.Get(line, column);
    if (cell.IsMarked()) {
        return;
    }

    if (cell.IsMined()) {
        GameEnded = true;
    } else {
        DeployChain(line, column);
    }
}

void MineSweeper::ApplyFunction(const MineSweeper::UserInput &ui) {
    if (ui.choice == 'M' || ui.choice == 'm') {
        Mark(ui.line, ui.column);
    }
    else if (ui.choice == 'D' || ui.choice == 'd'){
        Deploy(ui.line, ui.column);
    }
}

void MineSweeper::LoopGame() {
    UserInput ui{};
    while (!GameEnded) {
        Display();
        ApplyFunction(GetUI(std::cin));
    }
    Display();
    if (FoundMines == MinesNumber) {
        std::cout << "YOU WON" << std::endl;
    }
    else {
        std::cout << "YOU LOST" << std::endl;
    }
}

void MineSweeper::Run() {
    Choice choice;
    while (true) {
        Init();
        LoopGame();
        std::cout << "Do you want to retry? <Y/n>";
        std::cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }
}

MineSweeper::UserInput MineSweeper::ParseUserInput(std::istream &in) {
    static Choice choice;
    static short line, column;
    in >> choice >> line >> column;
    line--  ,   column--;
    return {choice, line, column};
}

inline bool MineSweeper::UICondition(const UserInput& c) {
    bool choice = c.choice == 'D' || c.choice == 'd' || c.choice == 'M' || c.choice == 'm';
    bool value = c.line < map.GetLinesSize() && c.line >= 0 && c.column < map.GetColumnSize() && c.column >= 0;
    return choice && value;
}

MineSweeper::UserInput MineSweeper::GetUI(std::istream &in) {
    UserInput ui{};
    do {
        ui = ParseUserInput(in);
        if (UICondition(ui))
            break;
        Display();
    } while(true);
    return ui;
}

