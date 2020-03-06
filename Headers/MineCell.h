#ifndef MINESWEEPER_MINECELL_H
#define MINESWEEPER_MINECELL_H

#include <ostream>
#include <iostream>

class MineCell {
private:
    int value;
    bool mined;
    bool marked;
    bool deployed;
public:
    MineCell() = default;

    MineCell(int value, bool mined, bool marked, bool deployed)
            : value(value) , mined(mined), marked(marked), deployed(deployed) {
    }

    ~MineCell() = default;

    void IncValue() {
        value++;
    }

    bool IsMined() const {
        return mined;
    }

    bool IsDeployed() const {
        return deployed;
    }

    bool IsMarked() const {
        return marked;
    }

    int GetValue() const {
        return value;
    }

    void SetMarked(bool mark) {
        this->marked = mark;
    }

    void SetMined(bool mine) {
        this->mined = mine;
    }

    void SetDeployed(bool deploy) {
        this->deployed = deploy;
    }

    void Clear() {
        value = 0;
        mined = marked = deployed = false;
    }

    friend std::ostream &operator<<(std::ostream &os, const MineCell &cell);
};


#endif //MINESWEEPER_MINECELL_H
