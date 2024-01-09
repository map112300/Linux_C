#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[]){

	char* stringToMatch;

    if(argc == 1){//case where no string is written in command line
        printf("No string entered\n");
        return EXIT_SUCCESS;
    }

    if(argc > 2){
        //if case check is present pass to method that does not check for case
        if(strcmp(argv[1], "-i") == 0)
        {
            stringToMatch = argv[2]; //this is the string we must look for
            char* upperMatch = malloc(sizeof(strlen(stringToMatch)+1)); //+1 to account for null terminating
            strcpy(upperMatch, stringToMatch); //copy string toMatch into upperMatch
           
            //transform command line string to upper case
            for(int i = 0; upperMatch[i] != '\0'; i++){
                upperMatch[i] = toupper(stringToMatch[i]);
            }
            
                while(!feof(stdin)){
                char* userInput = NULL;
                size_t size = 0;
                getline(&userInput, &size, stdin);
            
                if(feof(stdin)){//ctrl D case
                   free(userInput);
                   free(upperMatch);
                   break;
		        }

                //will be used to point to characters in string
                int upperPtr = 0;
                int userPtr = 0;
                int matchPtr = 0;
        
                while(userInput[userPtr] != '\0'){//while we are not at the end of the userString
                    while(userInput[userPtr] == upperMatch[upperPtr]|| userInput[userPtr] == stringToMatch[matchPtr]){//while values of lower/upper are equal
                        //increment pointers and continue to check
                        userPtr++;
                        matchPtr++;
                        upperPtr++;
                        //if we have gone through our entire string and everything matches
                        if (stringToMatch[matchPtr] == '\0' || upperMatch[upperPtr] == '\0')
                        {
                            printf("%s", userInput);
                        }
                    }
                    
                    userPtr++;//does not match continue through string
                    //reset string ptrs
                    upperPtr = 0;
                    matchPtr = 0;
                }
                free(userInput);
            }
        
            
        }
        
    }else{
        //if we do not have case check
        stringToMatch = argv[1];//this is the string we are looking for in stdin strings
         
        //create a string to hold the value of the user input string from stdin
        while(!feof(stdin)){

         char* userInput = NULL;
         size_t size = 0;
         getline(&userInput, &size, stdin);//gets line from the command line
         
         if(feof(stdin)){//case where user enters ctrl D must free already allocated input
	     free(userInput);
	     break;
	}
      
         if(strstr(userInput, stringToMatch)){//if the user string contains command line string print out user string 
             printf("%s", userInput);
         }
         //free userInput
         free(userInput);
        }
        
    }

    return EXIT_SUCCESS;
}
