#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

/*NOTES
*/

void filesInDirectory(const char* directoryPassed, char* lookingFor){//function to read all files within a passed directory

   DIR* directory = opendir(directoryPassed);//creates directory pointer and opens current directory
   if(directory == NULL){//if directory is empty return
       return;
   }
   
   struct dirent* dirFiles;//dirent struct to read contents of directory
   dirFiles = readdir(directory);//read files from opened directory

   
   while(dirFiles != NULL){//while directory is not empty

       if(strstr(dirFiles->d_name, lookingFor)){//if we found a match within the currently passed directory
                char dirPath[100000];//will hold correct path of found file
                strcat(dirPath, directoryPassed);//concat directory if current . else specific directory
                strcat(dirPath, "/");
                strcat(dirPath, dirFiles->d_name);//file name that matches
                printf("%s\n", dirPath);//print correct path
                strcpy(dirPath, "");//reset path string
        }
        
        if(dirFiles->d_type == 4 && strcmp(dirFiles->d_name, ".") != 0 && strcmp(dirFiles->d_name, "..") != 0){//if we come across a directory we want to make a recursive call to check that directory
            char directoriesString[100000] = {0};//create new char path string
            strcat(directoriesString, directoryPassed);//adds parent directory
            strcat(directoriesString, "/");
            strcat(directoriesString, dirFiles->d_name);//adds all additional sub directories of parent
            //printf("being passed: %s\n", directoriesString);
            filesInDirectory(directoriesString, lookingFor);//recursive call on directory path
            strcpy(directoriesString, "");//reset string
        }

       dirFiles = readdir(directory);
   }
    closedir(directory);
}


int main(int argc, char* argv[]){

    if(argv[1] == NULL){//if no argument given
        return EXIT_SUCCESS;
    }
    //holds argument string
    char* lookingFor = NULL;
    lookingFor = argv[1];
    
    filesInDirectory(".", lookingFor);//want to search through files in current directory
    
    return EXIT_SUCCESS;
}
