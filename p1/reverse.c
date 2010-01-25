#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 4096

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
		        break;
		default:
			fprintf(stderr,"Usage: reverse <input> <output>\n");
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
	while(current != NULL){
		fprintf(output,current->line);
		p = current;
		current = current->prev;
		free(p);
	}

	return 0; // we won't explictly close input and output because the standard didn't say anything about fclose(stdin) or fclose(stdout). Instead we shall rely on the behaviour that all stream got closed when program terminates (by returning from main or calling exit() )


}

