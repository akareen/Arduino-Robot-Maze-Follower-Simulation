#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int get_files(void){

    int n=0, i=0;
    DIR *d;
    struct dirent *dir;
    d = opendir("./Map Designs/");

    //Check that the directory can be opened
    if (d == NULL){
        printf("Error opening directory\n");
        return 1;
    }

    //Determine the number of files
    while((dir = readdir(d)) != NULL) {
        if ( !strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") )
        {

        } else {
            n++;
        }
    }
    rewinddir(d);

    char *filesList[n];

    //Put file names into the array
    while((dir = readdir(d)) != NULL) {
        if ( !strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") )
        {}
        else {
        filesList[i] = (char*) malloc (strlen(dir->d_name)+1);
        strncpy (filesList[i],dir->d_name, strlen(dir->d_name) );
        i++;
        }
    }
    rewinddir(d);

    //close the directory string
    if (closedir(d) == -1){
        printf("Error closing directory\n");
        return 1;
    }

    for(i=0; i<=n; i++)
        printf("%s\n", filesList[i]);
    return 0;
    }                           
    

 

