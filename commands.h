
#ifndef COMMANDS_H
#define COMMANDS_H


typedef enum {
    Register,
    Login,
    Enter_library,
    Get_books,
    Get_book,
    Add_book,
    Delete_book,
    Logout,
    Exit,
    Unknown,
} Command;

// structure that maps a string to a command
typedef struct {
    const char *name;
    Command command;
} CommandMapping;

// array of commands
extern CommandMapping commands_map[];

// function that returns the command corresponding to a string
Command get_command(const char *input);

#endif