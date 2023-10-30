#include "carg.h"
#include <stdio.h>

#define HELLO_CMD 0
#define WORLD_CMD 1
#define TEXT_CMD  2

cmd cmds[] = {
    {word, "hello", 0, 0, "very short description", 0, 0, 0},
    {flag, 0, "-w", "--world", "very very very long description", 0, 0, 0},
    {flag, 0, "-t", "--text", "test test", 1, 0, 0},
    COMMAND_END};

int
main(int argc, char **argv)
{
        if (cmds_parse(argc, argv, cmds) == 0) {
                if (cmds[HELLO_CMD].set > 0) puts("hello is set");
                if (cmds[WORLD_CMD].set > 0) puts("world is set");
                if (cmds[TEXT_CMD].set > 0)
                        printf("text is set: %s\n", cmds[TEXT_CMD].out);
        };
}
