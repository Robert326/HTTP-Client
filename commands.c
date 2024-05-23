
#include "commands.h"
#include <string.h>

CommandMapping commands_map[] = {
    {"register", Register},
    {"login", Login},
    {"enter_library", Enter_library},
    {"get_books", Get_books},
    {"get_book", Get_book},
    {"add_book", Add_book},
    {"delete_book", Delete_book},
    {"logout", Logout},
    {"exit", Exit},
 
};

Command get_command(const char *input) {
    for (int i = 0; i < sizeof(commands_map) / sizeof(CommandMapping); i++) {
        if (strcmp(input, commands_map[i].name) == 0) {
            return commands_map[i].command;
        }
    }
    return Unknown;
}