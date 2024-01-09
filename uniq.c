#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


int main(int argc, char* argv[]){

    long stringBuff = 100;
    long memoryTracker = 5;
    
    //dynamically allocate memory for array of strings
    char** stringArray = malloc(sizeof(char) * stringBuff);
    long i = 0;
    long count = 0;

    while(!feof(stdin)){//while arguments are still being passed through stdin

    //get command line string of arbitrary length and add it to string array
		char* userInput = NULL;
		size_t size = 0;
		getline(&userInput, &size, stdin);
		stringArray[i] = userInput;//add user input into array

		i++;//increment index of i
		count++;//store the amount of stirngs
		memoryTracker++;

        //conditional to reallocate memory if need be
		if(memoryTracker == stringBuff){
                stringBuff *= 10;
				stringArray = realloc(stringArray, (sizeof(char) * stringBuff));
				//reallocate another n bytes of space
				memoryTracker = 0;
				//reset memory tracker
			}
    }
    //count -= 1;
    //once input is done travers through array and print out correct info 
    i = 0;
    long j = 0;
    j = i;
    long isSame = 1;
    for(i = 1; i < count; i++){
        if(strcmp(stringArray[i-1], stringArray[i]) == 0){//if the same increment count continue search
            isSame += 1;
            //need to account for last case
            if(i == j-1){
                printf("%ld %s", isSame, stringArray[i-1]);
                return 0;
            }
        }else{//strings are different
            printf("%ld %s", isSame, stringArray[i-1]);
            //reset count
            isSame = 1;
        }
    }

    //free all dynamically allocated memory
    for(long i = 0; i < count; i++){
        free(stringArray[i]);
    }
    free(stringArray);

    return EXIT_SUCCESS;
}