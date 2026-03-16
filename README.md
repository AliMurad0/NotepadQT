# 📝 Notepad with Undo — Qt GUI & Custom Stack
**Intelligent Text Editing with a Hand-Rolled, Template-Based Linked List Stack**
 
 
> A minimal text editor built in **C++ with a Qt GUI**, where undo history is powered entirely by a **custom stack built from scratch** using templated linked lists — no `std::stack`, no STL containers.
 
[Features](#-key-features) • [Architecture](#️-system-architecture) • [Quick Start](#-quick-start) • [Complexity](#-complexity-analysis) • [Team](#-team)
 
---
 
## 📖 Overview
 
Standard text editors rely on black-box STL containers and pre-built undo libraries. This project strips all of that away.
 
The **Notepad with Undo** implements a complete text editing pipeline — from capturing keystrokes in a Qt GUI to reversing them using a **raw, pointer-based linked list stack** — demonstrating deep algorithmic control at every layer.
 
This approach achieves **O(1) push/pop** for all undo operations with **zero memory leaks**, using manual heap allocation and a custom destructor — without relying on any standard library containers.
 
---
 
## ✨ Key Features
 
| Feature | Description |
|---|---|
| 🧠 Custom Template Stack | `SimpleStack<T>` — a generic linked-list stack with manual heap management |
| ↩️ Undo Engine | Reverses any insert or delete action using the Command Pattern |
| 🖥️ Qt GUI | Minimalist interface with a live status bar showing internal stack events |
| 🔒 No STL Containers | `std::stack` is fully replaced by a raw pointer-based implementation |
| ♻️ No Memory Leaks | Custom destructor traverses and frees all heap nodes on exit |
| 🧩 Command Pattern | Every keystroke is encapsulated as a `Command` struct before being pushed |
| 📐 Modular Architecture | Strict 3-layer separation: GUI → Logic → Data Structure |
 
---
 
## 🏗️ System Architecture
 
The system is built on a **3-Layer Modular Architecture**, mirroring real-world software engineering principles:
 
```
┌──────────────────────────────────────────────────────────┐
│              Interface Layer  (Qt GUI / main.cpp)         │
│   Captures user input. Renders text. Zero logic here.    │
│   Sends signals → backend via Qt Slot/Signal mechanism.  │
├──────────────────────────────────────────────────────────┤
│              Logic Layer  (Notepad.cpp / Notepad.h)       │
│   The "Controller." Converts actions into Command objs.  │
│   Implements inverse logic for undo (insert ↔ delete).   │
├──────────────────────────────────────────────────────────┤
│         Data Structure Layer  (SimpleStack.h)             │
│   Raw C++ template class. Manages heap-allocated nodes.  │
│   Strict LIFO. O(1) push/pop. Custom destructor.         │
└──────────────────────────────────────────────────────────┘
```
 
### 🔁 The Qt–Backend Data Flow
 
```
User types "A"
      │
      ▼
Qt captures keystroke via Signal
      │
      ▼
Notepad::insertText("A")
  ├── Wraps into Command { INSERT, "A", position, length }
  ├── undoStack.push(cmd)        ← O(1), new Node on Heap
  └── content.insert(...)        ← O(N), std::string operation
      │
      ▼
User clicks "Undo"
      │
      ▼
Notepad::undo()
  ├── cmd = undoStack.pop()      ← O(1), frees Node from Heap
  ├── Reverses the action on content
  └── GUI updates via getContent()
```
 
---
 
## 📁 Project Structure
 
```
notepad-undo/
│
├── command.h           # Command struct & ActionType enum (INSERT / DELETE)
├── simpleStack.h       # Template linked-list stack — no STL
├── Notepad.h           # Notepad class declaration
├── Notepad.cpp         # Core logic — insertText, deleteText, undo
└── main.cpp            # Qt GUI entry point (Slot/Signal wiring)
```
 
---
 
## 🚀 Quick Start
 
### Prerequisites
- C++17 or later
- [Qt Framework](https://www.qt.io/download) — Qt5 or Qt6
- GCC / Clang / MSVC
 
### 1. Clone the Repository
```bash
git clone https://github.com/YOUR_USERNAME/notepad-undo.git
cd notepad-undo
```
 
### 2. Open in Qt Creator
1. Open the `.pro` file in **Qt Creator**
2. Select your kit (Desktop GCC/MSVC)
3. Click **Build → Run**
 
### 3. Build with CMake (Alternative)
```bash
mkdir build && cd build
cmake ..
make
./notepad
```
 
---
 
## 🔬 Data Structures & Algorithms
 
### `SimpleStack<T>` — Custom Template Stack
 
A fully generic, reusable stack backed by a **singly linked list**:
 
```cpp
template <typename T>
class SimpleStack {
    struct Node {
        T     data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* top_node;
 
public:
    void push(T item);    // O(1) — allocates new Node on Heap
    T    pop();           // O(1) — frees Node, returns data
    T    peek();          // O(1) — no deallocation
    bool isEmpty() const;
    ~SimpleStack();       // Traverses & frees all remaining Nodes
};
```
 
**Why a Linked List instead of an Array?**
 
| Property | Linked List (This Project) | Dynamic Array (`std::vector`) |
|---|---|---|
| Growth | Infinite — no fixed limit | Requires reallocation at capacity |
| Push / Pop | **O(1) always** | Amortized O(1), worst-case O(N) |
| Memory Layout | Per-node heap allocation | Contiguous memory block |
| Manual Control | ✅ Full pointer access | ❌ Abstracted away |
 
---
 
### The Command Pattern
 
Every user action is encapsulated as a `Command` object **before** any mutation occurs:
 
```cpp
struct Command {
    ActionType type;    // INSERT or DELETE
    string     text;    // The affected text content
    int        position;
    int        length;
};
```
 
Undo applies the **mathematical inverse**:
 
```cpp
void Notepad::undo() {
    Command cmd = undoStack.pop();
 
    if (cmd.type == INSERT)
        content.erase(cmd.position, cmd.length);          // Reverse insert → delete
    else
        content.insert(cmd.position - cmd.length, cmd.text); // Reverse delete → reinsert
}
```
 
---
 
## 📊 Complexity Analysis
 
| Operation | Time Complexity | Notes |
|---|---|---|
| `push` (record action) | **O(1)** | New node allocated on heap |
| `pop` (undo) | **O(1)** | Node freed immediately |
| `peek` | **O(1)** | No deallocation |
| Insert text | O(N) | `std::string::insert` — length dependent |
| Delete text | O(N) | `std::string::erase` — length dependent |
| **Space (history)** | **O(N)** | Linear in number of stored actions |
 
> **O(1) undo** — regardless of how deep the history is — is the core algorithmic achievement of this project.
 
---
 
## 🖥️ Interface & Visual Debugging
 
The Qt GUI was intentionally kept **minimalist** so the focus remains on the algorithm, not graphical overhead.
 
| Element | Purpose |
|---|---|
| Central Text Area | The editing canvas — directly mirrors the `content` string in memory |
| Status Bar | Logs internal stack events live (e.g., *"Pushed \[INSERT\] to Stack"*) |
| Undo Button | Triggers `Notepad::undo()` → pops stack → refreshes GUI |
 
The **Status Bar** is a deliberate design choice: it makes the invisible stack algorithm *visible* during live demos, proving the DSA concept in real time without a debugger.
 
---
 
## 🔮 Future Work
 
- [ ] **Redo Stack** — Add a second `SimpleStack<Command>` for redo functionality
- [ ] **Persistent History** — Serialize the stack to disk for session recovery
- [ ] **Doubly Linked List** — Explore bidirectional traversal for redo optimization
- [ ] **File I/O** — Save and load `.txt` files via Qt's `QFile`
- [ ] **Cursor Highlighting** — Visual cursor position indicator in the GUI
 
---
 
## 🛠️ Tech Stack
 
| Layer | Technologies |
|---|---|
| Language | C++17 |
| GUI Framework | Qt5 / Qt6 — QWidget, QTextEdit, Slot/Signal |
| Data Structure | Custom Template Linked-List Stack |
| Design Pattern | Command Pattern |
| Build System | Qt Creator / CMake |
| IDE | Qt Creator + VS Code |
 
---