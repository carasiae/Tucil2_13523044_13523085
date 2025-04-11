#include "cli.h"
#include <stdio.h>
#include <string.h>

void get_input(char* input_filepath, 
              char* output_filepath, 
              char* gif_output_filename, 
              int* minimum_block_size,
              double* error_threshold,
              VarianceFunction** variance_fn) {

    // get input file path
    int valid = 0;
    while (!valid) {
        puts(" ");
        puts("Insert absolute path to input image file: ");
        printf(">>> ");
        fgets(input_filepath, MAX_FILEPATH_LEN, stdin);
        input_filepath[strcspn(input_filepath, "\n")] = '\0';
        FILE *file = fopen(input_filepath, "r");
        if (file) {
            fclose(file);
            valid = 1;
        }
        else {
            puts("File doesn't exist. please try again");
        }
    }

    // get error measurements method
    int choice = 0;
    while (!choice) {
        puts(" ");
        puts("Pick Error Measurements Method:");
        puts("1. Variance");
        puts("2. Mean Absolute Deviation (MAD)");
        puts("3. Max Pixel Difference");
        puts("4. Entropy");
        printf(">>> ");
    
        choice = 0;
        scanf("%d", &choice);
        switch (choice) {
            case 1: *variance_fn = &variance; break;
            case 2: *variance_fn = &mean_absolute_deviation; break;
            case 3: *variance_fn = &max_pixel_difference; break;
            case 4: *variance_fn = &entropy; break;
            default:
                choice = 0;
                puts("Invalid choice. Please pick again.");
                break;
        }

        // flush input
        while (getchar() != '\n');
    }
    
    // get error threshold
    valid = 0;
    while (!valid) {
        puts(" ");
        printf("Insert error threshold ");
        switch (choice) {
            case 1: printf("[0 - 16000]: \n"); break;
            case 2: printf("[0 - 255]: \n"); break;
            case 3: printf("[0 - 255]: \n"); break;
            case 4: printf("[0 - 8]: \n"); break;
        }
        printf(">>> ");
        scanf("%lf", error_threshold);
        switch (choice) {
            case 1: 
                if (*error_threshold >= 0 && *error_threshold <= 16000) valid = 1;
                break;
            case 2: 
                if (*error_threshold >= 0 && *error_threshold <= 255) valid = 1;
                break;
            case 3: 
                if (*error_threshold >= 0 && *error_threshold <= 255) valid = 1;
                break;
            case 4: 
                if (*error_threshold >= 0 && *error_threshold <= 8) valid = 1;
                break;
        }
        if (!valid) puts("Invalid input range.");

        // flush input
        while (getchar() != '\n');
    }

    // get minimum block size (not sure whats the range is. assuming must be bigger than 0)
    valid = 0;
    while (!valid) {
        puts(" ");
        puts("Insert minimum block size:");
        printf(">>> ");
        scanf("%d", minimum_block_size);
        if (*minimum_block_size > 0) valid = 1;
        else puts("Can't be smaller than 1");

        // flush input
        while (getchar() != '\n');
    }

    // get output filepath
    valid = 0;
    while (!valid) {
        puts(" ");
        puts("Insert absolute path to output image file: ");
        printf(">>> ");
        fgets(output_filepath, MAX_FILEPATH_LEN, stdin);
        output_filepath[strcspn(output_filepath, "\n")] = '\0';
        FILE *file = fopen(output_filepath, "wb");
        if (file == NULL) {
            puts("File directory doesn't exist. please try again");
        }
        else {
            fclose(file);
            valid = 1;    
        }
    }

    // get output filepath
    valid = 0;
    while (!valid) {
        puts(" ");
        puts("Insert absolute path to output GIF file: ");
        printf(">>> ");
        fgets(gif_output_filename, MAX_FILEPATH_LEN, stdin);
        gif_output_filename[strcspn(gif_output_filename, "\n")] = '\0';
        FILE *file = fopen(gif_output_filename, "wb");
        if (file == NULL) {
            puts("File directory doesn't exist. please try again");
        }
        else {
            fclose(file);
            valid = 1;    
        }
    }
}



