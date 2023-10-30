/* macros */
#define COMMAND_LIMIT 1000
#define COMMAND_END                                                           \
        {                                                                     \
                0                                                             \
        }

/* enums */
typedef enum {
        word,
        flag,
} cmd_type;

/* structs */
typedef struct {
        cmd_type type;
        char *word;
        char *s_flag;
        char *flag;
        char *description;
        short has_opt;
        char *out;
        short set;
} cmd;

/* function prototypes  */
static inline int is_last_cmd(cmd *cmd);
static inline int cmds_parse(int argc, char **argv, cmd *cmds);
static inline int str_cmp(const char *str1, const char *str2);

/* function implementations */
static inline int
is_last_cmd(cmd *cmd)
{
        if (cmd->word == 0 && cmd->s_flag == 0 && cmd->flag == 0 &&
            cmd->set == 0 && cmd->out == 0 && cmd->type == 0 &&
            cmd->description == 0) {
                return 1;
        }

        return -1;
}

static inline int
cmds_parse(int argc, char **argv, cmd *cmds)
{
        if (argc == 1) return -1;
        int i = 1;

        do {
                char *curr_argv = argv[i];
                for (int j = 0; j < COMMAND_LIMIT; j++) {
                        cmd *curr_cmd = &cmds[j];

                        if (is_last_cmd(curr_cmd) > 0) goto end;

                        int parsed = 0;
                        switch (cmds[j].type) {
                        case word:
                                if (str_cmp(curr_cmd->word, curr_argv) > 0) {
                                        curr_cmd->set = 1;
                                        parsed = 1;
                                }
                                break;
                        case flag:
                                if (str_cmp(curr_cmd->flag, curr_argv) > 0 ||
                                    str_cmp(curr_cmd->s_flag, curr_argv) > 0) {
                                        curr_cmd->set = 1;

                                        if (curr_cmd->has_opt == 1) {
                                                curr_cmd->out = argv[++i];
                                        }
                                        parsed = 1;
                                }
                                break;
                        default:
                                return -1;
                        }
                        if (parsed == 1) break;
                }
                i++;
        } while (i < argc);
end:
        return 0;
}

static inline int
str_cmp(const char *str1, const char *str2)
{
        while (*str1 && (*str1 == *str2)) {
                str1++;
                str2++;
        }

        if (*str1 == '\0' && *str2 == '\0') { return 1; }
        return -1;
}
