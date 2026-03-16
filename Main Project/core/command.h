                                                                                                                                                                                                                       #ifndef COMMAND_H
#define COMMAND_H
#include <string>
using namespace std;

enum ActionType { INSERT, DELETE };

struct Command {
    ActionType type;
    string text;
    int position;
    int length;
};

#endif