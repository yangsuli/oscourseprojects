#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 512
#define MAX_ARGUMENTS 512
#define MAX_COMMANDS 512
#define NUM_BUILD_IN 3


extern const char delims_for_args[] ;
extern const char delims_for_cmds_serial[] ;
extern const char delims_for_cmds_parallel[] ;
extern const char prompt[] ; 
extern const char *support_build_in[NUM_BUILD_IN] ;
extern const char *redirection_chars ;
extern const char *grep_chars ;
extern const char *grep_path ;

bool read_one_line(char * buf, int n, FILE * input);
bool is_eol(char x);
void initialize_buf_with_eol(char *buf, int size);
void run_parallel_commands(char* parallel_cmd);
void parse_args(char *buf, char **argv, int max_args, const char * delims);
void lauch_shell(char *batch_file);
bool check_build_in_cmd(char * str);
void deal_with_build_in(char *argv[]);
int run_command(char *cmd);
