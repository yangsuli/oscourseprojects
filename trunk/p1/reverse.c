#include <stdio.h>
#include <stdlib.h>

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

	return 0; // we won't explictly close input and output because the standard didn't say anything about fclose(stdin) or fclose(stdout). Instead we shall rely on the behaviour that all stream got closed when program terminates (by returning from main or calling exit() )


}
