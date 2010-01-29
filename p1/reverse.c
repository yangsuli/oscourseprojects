#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 1024


//Note that there is no bool type in C
bool is_eol(char x){
	return (x == '\n'|| x == '\r');
}

//given two string, check if they refer to the same file. If yes, return true, else return false
bool is_same_file(const char *file1, const char *file2){
	struct stat * buf1 = malloc(sizeof(struct stat));
	struct stat * buf2 = malloc(sizeof(struct stat));
	if( !buf1 || !buf2){
		fprintf(stderr,"malloc failed!\n");
		exit(1);
	}
	if( !stat(file1,buf1) || !stat(file2,buf2) ){
		fprintf(stderr,"can not stat file\n");
		exit(1);
	}
	int same;
        if(buf1->st_ino == buf2->st_ino){
		same = true;
	}else{
		same = false;
	}
        free(buf1);
	free(buf2);
	return same;
}

struct node {
	char line[MAX_LINE_SIZE];
	struct node * next;
	struct node * prev;
};

int main(int argc, char * argv[]){
	/*
	   if(argc > 3){
	   fprintf(stderr,"Usage: reverse <input> <output>\n");
	   exit(1);
	   }
	 */

	FILE *input,*output;

	switch(argc){
		case 1: 
			input = stdin;
			output = stdout;
			break;
		case 2: 
			input = fopen(argv[1],"r");
			if(input == NULL){
				fprintf(stderr, "Error: Cannot open file '%s'\n",argv[1]);
				exit(1);
			}
			output = stdout;
			break;
		case 3:
			if(strcmp(argv[1],argv[2])==0){
				fprintf(stderr,"Input and output file must differ\n");
				exit(1);
			}

			output = fopen(argv[2],"w");
			if(output == NULL){
				fprintf(stderr,"Error: Cannot open file '%s'\n",argv[2]);
				exit(1);
			}
			input = fopen(argv[1],"r");
			if(input == NULL){
				fprintf(stderr, "Error: Cannot open file '%s'\n",argv[1]);
				exit(1);
			}
			if(is_same_file(argv[1],argv[2])){
				fprintf(stderr,"Input and output file must differ\n");
				exit(1);
			}
			break;
		default:
			fprintf(stderr,"Usage: reverse <infile> <outfile>\n");
			exit(1);
	}

	char buf[MAX_LINE_SIZE];

	struct node *list = NULL; //the linked list that contains lines read from input file; 
	struct node *prev = NULL, *p = NULL, *current = NULL;

	//read the input file by line, and store the lines into a linked list.
	while(fgets(buf,MAX_LINE_SIZE,input)!=NULL){
		current = (struct node *)malloc(sizeof(struct node));
		if(current == NULL){
			fprintf(stderr,"malloc failed!\n");
			exit(1);
		}
		int i = 0;
		for( i = 0; i < MAX_LINE_SIZE; i++){
			current->line[i] = '\n'; //initialize with EOLs, essencial for future check
		}
		if(list == NULL){
			list = current;
		}
		current->prev = prev;
		if(current->prev != NULL){
			current->prev->next = current;
		}
		strcpy(current->line,buf);
		prev = current;

	}

	//since the pointer current now points to the last element in the list
	//struct node * last = current;
	while(current != NULL){
		struct node * current_line_start = current;
		while(current_line_start->prev != NULL && !is_eol(current_line_start->prev->line[MAX_LINE_SIZE - 2])){
			//fprintf(output,"%c\n",current_line_start->prev->line[MAX_LINE_SIZE - 2]);
			current_line_start = current_line_start->prev;
		}
		p = current_line_start;
		do{
			fprintf(output,p->line);
			//handle the special case that input file doesn't end with an EOF
		/*	if( p == last && !strchr(p->line,'\n') && !strchr(p->line,'\r') ){
				fprintf(output,"\n");
			} */
			p = p -> next;
		}while(p != current->next);

		current = current_line_start->prev;

	}

	//free the whole list;
	current = list;
	while(current != NULL){
		p = current->next;
		free(current);
		current = p;
	}

	return 0; // we won't explictly close input and output because the standard didn't say anything about fclose(stdin) or fclose(stdout). Instead we shall rely on the behaviour that all stream got closed when program terminates (by returning from main or calling exit() )


}


