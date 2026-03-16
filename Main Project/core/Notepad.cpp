#include "Notepad.h"
#include <iostream>

using namespace std;

Notepad::Notepad() {
    content = "";
    cursorPosition = 0;
}

void Notepad::insertText(string text) {
    Command cmd;
    cmd.type = INSERT;
    cmd.text = text;
    cmd.position = cursorPosition;
    cmd.length = text.length();

    undoStack.push(cmd);
    content.insert(cursorPosition, text);
    cursorPosition += text.length();
}

void Notepad::deleteText(int length) {
    if (length <= 0 || cursorPosition < length) return;

    int startPos = cursorPosition - length;
    string deletedText = content.substr(startPos, length);

    Command cmd;
    cmd.type = DELETE;
    cmd.text = deletedText;
    cmd.position = cursorPosition;
    cmd.length = length;

    undoStack.push(cmd);
    content.erase(startPos, length);
    cursorPosition = startPos;
}

void Notepad::undo() {
    if (undoStack.isEmpty()) return;

    Command cmd = undoStack.pop();

    if (cmd.type == INSERT) {
        content.erase(cmd.position, cmd.length);
        cursorPosition = cmd.position;
    }
    else {
        content.insert(cmd.position - cmd.length, cmd.text);
        cursorPosition = cmd.position;
    }
}

void Notepad::display() {
    cout << content << endl;
}

// 🔹 ADDED FOR GUI
string Notepad::getContent() const {
    return content;
}

int Notepad::getCursorPosition() const {
    return cursorPosition;
}
