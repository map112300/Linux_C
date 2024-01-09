#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

void swap(long* x, long* y){

	long temp = *x;
	*x = *y;
	*y = temp;
}

int main(int argc, char* argv[]){

	//char* arrSort;//this array will hold all values that need to be sorted
	if(argc == 1){//case-insensitive lexicographic sorting to be done
		
		long stringBuff = 100;//this will be original memory allocation for string array
		long memoryTracker = 5;
		char** stringArray = malloc(sizeof(char) * stringBuff);//dynamically allocate string array with 100 indices
	
		long count = 0;
		long i = 0;

	while(!feof(stdin)){//read from the command line until ctrl d

		//get command line string of arbitrary length and add it to string array
		char* userInput = NULL;
		size_t size = 0;
		getline(&userInput, &size, stdin);
		stringArray[i] = userInput;
		
		i++;
		count++;//store the amount of stirngs
		memoryTracker++;

		if(memoryTracker == stringBuff){
				stringBuff *= 10;
				stringArray = realloc(stringArray, (sizeof(char) * stringBuff));
				//reallocate another n bytes of space
				memoryTracker = 0;
				//reset memory tracker
			}

		if(feof(stdin)){
			free(userInput);
			break;
		}
	}
		//now sort strings, and free at end
		count -= 1;
		char temp[2048];
		for(long i = 0; i < count; ++i){
			for(long j = i+1; j < count; ++j){
				if(strcasecmp(stringArray[i], stringArray[j]) > 0){//compare to see which is larger
					//swap values of stringArray[j] into stringArray[i]
					strcpy(temp, stringArray[i]);
					strcpy(stringArray[i], stringArray[j]);
					strcpy(stringArray[j], temp);
				}
				
			}
		}
		//print lexicographical sort
		for(long i = 0; i < count; i++){
			printf("%s", stringArray[i]);
		}

		//free all dynamically allocated memory
		for(long i = 0; i < count; i++){
			free(stringArray[i]);
		}
		free(stringArray);
		
	///INTEGER CASE
	}else if(argc == 2 && strcmp(argv[1], "-n") == 0){//case to perform numeric sorting all inputs are ints

		long maintainSize = 10;

		long* valArray = malloc(sizeof(long) * maintainSize);
		long memoryTracker = 5;//maintains track of memory with buffer space to reallocate
		long count = 0;
		long i = 0;
		//pass values into array
		while(!feof(stdin)){
			scanf("%ld", &valArray[i]);
			count++;
			memoryTracker++;
			i++;

			//if user next input will exceed memory allocation
			if(memoryTracker == maintainSize){
				maintainSize *= 10;//allocate 10x more bytes of memory to our array
				valArray = realloc(valArray, (sizeof(long) * maintainSize));
				//reallocate another n*long bytes of space
				memoryTracker = 0;
				//reset memory tracker
			}
		}

		count -= 1;
		//selection sort with swap
		for(long i = 0; i < count-1; i++){
			long min = i;//maintain minimum value
			for(long j = i+1; j < count; j++)
			{
				if(valArray[j] < valArray[min]){//move through array until smaller value is found
					min = j;//update index of minimum 
				}
			}
			swap(&valArray[min], &valArray[i]);//swap current min with new min until array is sorted
		}

		for(long i = 0; i < count; i++){
			printf("%ld\n", valArray[i]);
		}
		free(valArray);
	}
    	return EXIT_SUCCESS;
}
