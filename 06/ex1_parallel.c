// Program that recursively calculates a folder size (with all sub-folders) using OpenMP and Tasks.

#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int calculate_folder_size(const char *path) {

    struct stat sb;

    if (lstat(path, &sb) == 0) {
        if (S_ISREG(sb.st_mode)) { // if it's a file, not a directory (base case)
            return sb.st_size;
        }
    } else {
        perror("LSTAT ERROR\n");
    }

    DIR *folder = opendir(path);

    if (folder == NULL) {
        perror("OPENDIR ERROR");
        return 0;
    }

    struct dirent *element;
    size_t size = 4096;

    // iterate through all elements in the folder, until element = NULL
    // readdir always returns the next element in the folder
    for (element = readdir(folder); element != NULL; element = readdir(folder)) {

        long path_length = sizeof(char) * (strlen(path) + strlen(element->d_name) + 2);
        char *name = (char *) malloc(path_length);

        strcpy(name, path);
        strcpy(name + strlen(path), "/");
        strcpy(name + strlen(path) + 1, element->d_name);

        if (element->d_type == DT_DIR) {
            if (strcmp(element->d_name, ".") != 0 && strcmp(element->d_name, "..") != 0) {

                // recursive call of calculate_folder_size

                size += calculate_folder_size(name);
            }
        } else {

            int status = lstat(name, &sb);
            if (status == 0) {
                size += sb.st_size;
            } else {
                perror("LSTAT ERROR\n");
            }
        }
        free(name);
    }


    closedir(folder);

    return size;
}


/**
 * Main function.
 * */
int main(int argc, char **argv) {

    double start_time = omp_get_wtime();

    if (argc != 2) {
        printf("Usage: testprog <dirname>\n");
        return EXIT_FAILURE;
    }
    char *str = argv[1];

    struct stat sb;
    int error = stat(str, &sb);
    switch (error) {
        case EACCES:
            printf("Access denied.\n");
            break;
        case EFAULT :
            printf("Bad address.\n");
            break;
        case ENOENT:
            printf("A component of the path does not exist, or the path is an empty string.\n");
            break;
        case ENOTDIR:
            printf("A component of the path is not a directory.\n");
            break;
        default:
            printf("Path ok.\n");
    }
    int folder_size;

#pragma omp parallel shared(str)
    {
#pragma omp single
        {
            folder_size = calculate_folder_size(str);
        }
    }

    double end_time = omp_get_wtime();
    printf("Size: %d, Elapsed time: %2.2f seconds\n", folder_size, end_time - start_time);
}
