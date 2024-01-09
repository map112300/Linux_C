#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct dirent* dir;
    struct dirent* list[3000];
    int count = 0;
    DIR * dirp = opendir(".");
    dir = readdir(dirp);
    struct dirent* temp;
    char * input  = argv[1];
    while (dir != NULL){
        while ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..")== 0) ){
            dir = readdir(dirp);
        }

        //printf("%s  ", dir->d_name);
        list[count++] = dir;
        
        dir = readdir(dirp);
    }

    // sort inorder
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            
            if (strcasecmp(list[i]->d_name, list[j]->d_name) > 0) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    if (argc == 2){
        if (strcmp(input, "-l")!=0){
            printf("error\n");
            return EXIT_FAILURE;
        }
        for (int i =0; i< count; i++){
            if ((strcmp(list[i]->d_name, ".vscode")== 0)){
                continue;
            }
            struct stat fileStat;
            stat(list[i]->d_name, &fileStat);

            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x " : "- ");
            uid_t userid  = fileStat.st_uid;
            gid_t groupid = fileStat.st_gid;
            //char * username = getUser(userid);
            //char * groupname = getGroup(groupid);
            struct passwd *pws;
            pws = getpwuid(userid);
            printf("%s ", pws->pw_name);
            struct group *gpws;
            gpws = getgrgid(groupid);
            printf("%s ", gpws->gr_name);
            //printf(groupname);
            printf("%ld ", fileStat.st_size);
            char* ti = ctime(&fileStat.st_mtime);
            ti[strlen(ti)-9] = '\0';
            printf("%s ", ti);

            printf("%s\n", list[i]->d_name);
            
            
        }
    }
    else{
        for (int i =0; i< count; i++){
            if ((strcmp(list[i]->d_name, ".vscode")== 0)){
                continue;
            }
            printf("%s\n", list[i]->d_name);
        }
    }
    closedir(dirp);
    return EXIT_SUCCESS;
}