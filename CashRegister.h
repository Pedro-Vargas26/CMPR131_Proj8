#pragma once
#ifndef CASHREGISTER_H
#define CASHREGISTER_H

#include "PrintableItem.h"
#include <queue>
#include <ostream>
#include <windows.h>
using std::ostream;
using std::queue;

class CashRegister : public PrintableItem {
private:
    queue<PrintableItem> line;
public:
    CashRegister() : PrintableItem() {
        this->setDesign((char)203); 
    }

    void appendCustomer(const PrintableItem& newSprite) { line.push(newSprite); }
    void removeCustomer() { if (!line.empty()) line.pop(); }
    int lineLength() const { return static_cast<int>(line.size()); }


    COORD getNextCustomerPosition() const noexcept {
        COORD next;
        next.X = getX() + static_cast<SHORT>(line.size() + 1);
        next.Y = getY();
        return next;
    }

    
    void drawQueue() const noexcept {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD regPos = { static_cast<SHORT>(getX()), static_cast<SHORT>(getY()) };

        // Draw register
        SetConsoleCursorPosition(hConsole, regPos);
        std::cout << draw();
        COORD label = { static_cast<SHORT>(getX()), static_cast<SHORT>(getY() - 1) };
        SetConsoleCursorPosition(hConsole, label);
        std::cout << "[" << lineLength() << "]" << std::endl;

        int offset = 1;
        for (size_t i = 0; i < line.size(); ++i) {
            COORD cPos = { static_cast<SHORT>(getX() + offset++), static_cast<SHORT>(getY()) };
            SetConsoleCursorPosition(hConsole, cPos);
            std::cout << '*';
        }

 

    }

    friend ostream& operator<<(ostream& os, const CashRegister& obj) noexcept {
        os << "[" << obj.lineLength() << "]" << obj.draw();
        return os;
    }
};

#endif
