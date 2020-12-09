#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
    DIR *mydir;
    char *c;
    int i;
    struct dirent *myfile;
    struct stat fileStat;
    mydir = opendir(".");
    stat(".", &fileStat);
    while((myfile = readdir(mydir)) != NULL)
    {
        stat(myfile->d_name, &fileStat);
        if(strcmp(myfile->d_name, ".") != 0 && strcmp(myfile->d_name, "..") != 0)
        {
            printf("%s\n", myfile->d_name);
            printf("File Permission:\n");
            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n");
        }
    }
    closedir(mydir);
    return 0;
}


