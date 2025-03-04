#include <stdlib.h>
#include <string.h>  
#include <stdio.h> 
#include <stdbool.h>

bool get_full_directory_path(const char* local_directory_name, char full_path[]){ 
    // string literal representing the find command that we will concatenate our input path to
    const char find_command_prefix[] = "find ~ -type d -name "; 

    // build the find command (composed of the above prefix and the input local directory)
    char* full_command = (char*)malloc(strlen(find_command_prefix) + strlen(local_directory_name) + 1);    
    if(full_command == NULL){  
        return false;
    } 
    strcpy(full_command, find_command_prefix); 
    strcat(full_command, local_directory_name);

    // execute the find command and put the stdout result in a file 
    FILE* command_result = popen(full_command, "r"); 
    if(command_result == NULL){  
        free(full_command);
        return false;
    } 

    // copy the contents of the above file (output of the executed find command) into the second input parameter
    int index = 0;
    char ch; 
    while((ch = fgetc(command_result)) != EOF){ 
        full_path[index] = ch; 
        index++;
    }  
    full_path[index] = '\0'; 

    // if the path is doesn't exist, (indicated by the second parameter being empty) return false
    if(strlen(full_path) == 0){ 
        free(full_command); 
        fclose(command_result);  
        return false;
    }

    // free dynamically allocated memory
    free(full_command); 
    fclose(command_result);  

    // return true if the above procedures succeed
    return true;
} 