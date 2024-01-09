#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

typedef struct dirent dirent;

int indentation;//will be use for sub levels and further file depth
int initialIndent = 0;//inital indent should be zero

void sortPath(char** toSort, int size){//sort array similar to in same manner as lis
    char* temp;//used to hold temp name
    int swapIndex = 0;
    //Selection sort
    for(int i = 0; i < size; i++){
        swapIndex = i;
        for(int j = i + 1; j < size; j++){
            if(strcasecmp(toSort[swapIndex], toSort[j]) > 0){
                swapIndex = j;
            }
        }
        temp = toSort[i];
        toSort[i] = toSort[swapIndex];
        toSort[swapIndex] = temp;
    }
}

char** pathSizeAdjust(char** pathToChange, int size){//function used to adjust current directory path 
    char** temp = realloc(pathToChange, (size + 1) * sizeof(char*));//reallocate more memory for further recursive call
    if(temp == NULL){//if null then reached end of path or no file
        return NULL;
    }
    return temp;//return newly sized array
}

void directoryFiles(char* directoryPassed){//recursively iterate through all files and sub directories
    DIR* directory = opendir(directoryPassed);
    if (directory == NULL){//if directory does not exist or empty
        return;
    }

    dirent* dirFiles = readdir(directory);
    int size = 0;
    char** fileNames = malloc(sizeof(char*));//array of strings to hold directory path
    while(dirFiles != NULL){//while not null continue to read files
        if(dirFiles->d_name[0] != '.'){
            fileNames[size] = malloc((strlen(dirFiles->d_name) + 1) * sizeof(char));
            strncpy(fileNames[size], dirFiles->d_name, strlen(dirFiles->d_name) + 1);
            fileNames = pathSizeAdjust(fileNames, size + 1);
            size++; 
        }
        dirFiles = readdir(directory);
    }

    sortPath(fileNames, size);//sort corrent path/current files in inner directory
    for(int i = 0; i < size; i++){
        
        struct stat info; // place declaration inside so we avoid the . and .. hidden directories
        char* directoryPath = malloc(sizeof(char) * (strlen(directoryPassed) + strlen("/") + strlen(fileNames[i]) + 1)); //Alloctae for path
        strncpy(directoryPath, directoryPassed, strlen(directoryPassed) + 1);//copy file to path
        strncat(directoryPath, "/", 2);//concat / to indicate string path
        strncat(directoryPath, fileNames[i], strlen(fileNames[i]) + 1);
        stat(directoryPath, &info);
        if (initialIndent != 0){//increase indent to current level
            for (int i = 1; i <= initialIndent; i++){
                    printf("  ");
            }
        }
        printf("- %s\n", fileNames[i]);
        if(S_ISDIR(info.st_mode)){
            initialIndent++;//increment indent
            directoryFiles(directoryPath);//recursive call to continue file search
            indentation+= 2;//increment indent two spaces
            initialIndent--;//decrease indent after recursive call   
        }
        free(directoryPath);//free current path
           
           
    }
    closedir(directory);//close firectory
    for(int i = 0; i < size; i++){//free all dynamically allocated memory
        free(fileNames[i]);
    }
    indentation = 0;
    free(fileNames);
}

int main(int argc, char* argv[]){
    printf(".\n");//print initial directory "."
    directoryFiles(".");//pass current directory to recursive function

    return EXIT_SUCCESS;
}