/*
Q.1 Write a C program to implement the shell. It should display the command 
prompt “myshell$”. Tokenize the command line and execute the given command 
by creating the child process. Additionally, it should interpret the following ‘list’ commands:
myshell$ list f dirname :- To print names of all the files in the current directory.
myshell$ list i dirname :- To print names and inodes of the files in the current directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void list_files(char *dirname) {
    struct dirent *de;
    DIR *dr = opendir(dirname);
    if (dr == NULL) {
        printf("Could not open current directory\n");
        return;
    }
    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }
    closedir(dr);
}

void list_files_with_inodes(char *dirname) {
    struct dirent *de;
    struct stat statbuf;
    DIR *dr = opendir(dirname);
    if (dr == NULL) {
        printf("Could not open directory\n");
        return;
    }
    while ((de = readdir(dr)) != NULL) {
        if (stat(de->d_name, &statbuf) == 0) {
            printf("File: %s, Inode: %ld\n", de->d_name, statbuf.st_ino);
        }
    }
    closedir(dr);
}

int main() {
    char command[100];
    char *args[10];
    char *token;

    while (1) {
        printf("myshell$ ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0'; // Remove newline
        
        token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "list") == 0) {
            if (strcmp(args[1], "f") == 0) {
                list_files(args[2]);
            } else if (strcmp(args[1], "i") == 0) {
                list_files_with_inodes(args[2]);
            }
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
            } else {
                wait(NULL);
            }
        }
    }
    return 0;
}


