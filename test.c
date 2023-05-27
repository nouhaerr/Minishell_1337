#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* line = readline("Enter a command: ");
    add_history(line);

    printf("Original command: %s\n", line);

    rl_replace_line("Updated command", 0);
    rl_redisplay();

    return 0;
}