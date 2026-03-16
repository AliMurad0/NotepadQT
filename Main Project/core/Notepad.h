#ifndef NOTEPAD_H
#define NOTEPAD_H

#include "SimpleStack.h"
#include "Command.h"
#include <string>

using namespace std;

class Notepad {
private:
    string content;
    int cursorPosition;
    SimpleStack<Command> undoStack;

public:
    Notepad();

    void insertText(string text);
    void deleteText(int length);
    void undo();
    void display();   // still exists (console)

    // 🔹 ADDED FOR GUI (SAFE)
    string getContent() const;
    int getCursorPosition() const;
};

#endif
