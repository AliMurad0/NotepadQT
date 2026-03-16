📝 Notepad with Undo — Qt GUI & Custom Stack

A text editing application with undo history powered by a hand-rolled, template-based linked list stack — no STL allowed.

🧠 Overview
This project implements a minimal text editor in C++ with a Qt GUI, where every keystroke and deletion is tracked using a custom stack built from scratch using templated linked lists. The goal was to demonstrate deep understanding of memory management, the Command Pattern, and LIFO-based undo logic — without relying on std::stack or any STL container.

✨ Features

✅ Insert & Delete text with cursor-aware positioning
✅ Undo — reverses any action using a custom stack
✅ Qt GUI — clean, minimalist interface with a live status bar
✅ Command Pattern — every action is encapsulated as a Command struct
✅ No STL — the stack is implemented via raw pointer-based linked list
✅ No memory leaks — custom destructor handles all heap cleanup


🏗️ Architecture
The project follows a 3-Layer Modular Architecture with strict separation of concerns:
┌─────────────────────────────────────────────┐
│         Interface Layer  (Qt GUI)            │
│   Captures user input, renders text.        │
│   Zero processing — only signals backend.   │
├─────────────────────────────────────────────┤
│         Logic Layer  (Notepad.cpp/.h)        │
│   Converts actions into Command objects.    │
│   Implements undo inverse logic.            │
├─────────────────────────────────────────────┤
│    Data Structure Layer  (SimpleStack.h)     │
│   Template linked-list stack on the heap.  │
│   Strict LIFO. O(1) push/pop.               │
└─────────────────────────────────────────────┘

📁 File Structure
├── command.h          # Command struct & ActionType enum (INSERT / DELETE)
├── simpleStack.h      # Template linked-list stack (no STL)
├── Notepad.h          # Notepad class declaration
├── Notepad.cpp        # Notepad logic — insert, delete, undo
└── main.cpp           # Qt GUI entry point (not included in this repo)

🔬 Data Structures & Algorithms
SimpleStack<T> — Custom Template Stack
A generic, reusable stack backed by a singly linked list.
cpptemplate <typename T>
class SimpleStack {
    struct Node { T data; Node* next; };
    Node* top_node;
public:
    void push(T item);   // O(1)
    T    pop();          // O(1)
    T    peek();         // O(1)
    bool isEmpty();
    ~SimpleStack();      // Cleans up all heap nodes
};
OperationTime ComplexityNotespushO(1)Allocates new node on heappopO(1)Frees node, returns dataInsert/Delete textO(N)Standard std::string behaviorSpaceO(N)Linear in number of actions
Why linked list over array?

Infinite growth — history expands dynamically with no fixed limit
Constant-time push/pop regardless of history depth
Manual memory control — demonstrates heap allocation and pointer management


The Command Pattern
Every user action is wrapped into a Command object before being pushed to the stack:
cppstruct Command {
    ActionType type;   // INSERT or DELETE
    string     text;   // The affected text
    int        position;
    int        length;
};
Undo simply pops the last Command and applies the mathematical inverse:

If the action was INSERT → erase that text
If the action was DELETE → re-insert that text


⚙️ How It Works — Data Flow
User types "A"
     │
     ▼
Qt captures keystroke
     │
     ▼
Notepad::insertText("A")
  → wraps into Command { INSERT, "A", pos, len }
  → undoStack.push(cmd)
  → content.insert(...)
     │
     ▼
User clicks Undo
     │
     ▼
Notepad::undo()
  → cmd = undoStack.pop()
  → reverses the action on content
  → GUI updates via getContent()

🖥️ Building & Running
Prerequisites

C++17 or later
Qt Framework (Qt5 or Qt6)
A C++ compiler (GCC / Clang / MSVC)

Build with Qt Creator

Clone the repository
Open the .pro file in Qt Creator
Configure the kit and click Run

Build with CMake (if applicable)
bashmkdir build && cd build
cmake ..
make
./notepad

💡 Design Decisions & Challenges
Why a custom stack instead of std::stack?
The project requirement was to demonstrate manual memory management. Using std::stack would abstract away the exact pointer logic (heap allocation, node chaining, destructor cleanup) that this project was designed to showcase.
Why minimalist Qt GUI?
A minimal interface ensures the demo focuses on the stack algorithm in action, not graphical rendering. The status bar deliberately logs internal stack events (e.g., "Pushed [INSERT] to Stack") to make the invisible algorithm visible during a live demo.
Linked List vs. Array-backed Stack
We chose a linked list despite its added complexity (pointer management, risk of segfaults) because it offers dynamic, unbounded growth — more appropriate for a real undo history that has no predetermined limit.

📊 Complexity Summary
OperationTimeSpacePush to stackO(1)O(1) per nodePop (undo)O(1)—Insert textO(N)—Delete textO(N)—Full undo history—O(N) total
Hello!  This is my first Project!!
