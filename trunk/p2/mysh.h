#define MAX_LINE_LENGTH 512

void read_one_line(char * buf, int n, FILE * input);

bool is_eol(char x);

void initialize_buf_with_eol(char *buf, int size);
