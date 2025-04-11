#include "cli.h"
#include <stdio.h>
#include <string.h>
#include "file_size.h"

void clean_and_moveup_cursor(int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("\033[2K\033[1A");
    }
    printf("\033[2K");
}

void get_input(char* input_filepath, 
               char* output_filepath, 
               char* gif_output_filename, 
               int* minimum_block_size,
               double* error_threshold,
               VarianceFunction** variance_fn) {
    
    puts(
    "\n\033[38;2;56;118;29m ██████╗ ██╗   ██╗ █████╗ ██████╗     ████████╗██████╗ ███████╗███████╗                   \n"
    "██╔═══██╗██║   ██║██╔══██╗██╔══██╗    ╚══██╔══╝██╔══██╗██╔════╝██╔════╝                   \n"
    "██║   ██║██║   ██║███████║██║  ██║       ██║   ██████╔╝█████╗  █████╗                     \n"
    "██║▄▄ ██║██║   ██║██╔══██║██║  ██║       ██║   ██╔══██╗██╔══╝  ██╔══╝                     \n"
    "╚██████╔╝╚██████╔╝██║  ██║██████╔╝       ██║   ██║  ██║███████╗███████╗                   \n"
    " ╚══▀▀═╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝        ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝                   \n"
                                                                                              "\n"
    "\033[38;2;206;126;0m ██████╗ ██████╗ ███╗   ███╗██████╗ ██████╗ ███████╗███████╗███████╗██╗ ██████╗ ███╗   ██╗\n"
    "██╔════╝██╔═══██╗████╗ ████║██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝██║██╔═══██╗████╗  ██║\n"
    "██║     ██║   ██║██╔████╔██║██████╔╝██████╔╝█████╗  ███████╗███████╗██║██║   ██║██╔██╗ ██║\n"
    "██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██╔══██╗██╔══╝  ╚════██║╚════██║██║██║   ██║██║╚██╗██║\n"
    "╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ██║  ██║███████╗███████║███████║██║╚██████╔╝██║ ╚████║\n"
    " ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝\033[0m\n");
                                                                                              
    puts("A \033[38;2;177;209;130mQuadTree\033[0m PNG Compressor by \033[38;2;161;227;249mBoredAngel\033[0m & \033[38;2;54;116;181mLQMMM\033[0m \n\n\n");

    // get input file path
    int valid = 0;
    while (!valid) {
        clean_and_moveup_cursor(3);
        puts("\n\nInsert absolute path to input image file: ");
        printf(">>> \033[0K");
        fgets(input_filepath, MAX_FILEPATH_LEN, stdin);
        input_filepath[strcspn(input_filepath, "\n")] = '\0';
        trim(input_filepath);
        FILE *file = fopen(input_filepath, "r");
        if (file) {
            fclose(file);
            valid = 1;
        }
        else {
            printf("File doesn't exist. please try again\033[1A");
        }
    }
    puts("\033[2K");
    clean_and_moveup_cursor(4);
    printf("\n\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Input Image Absolute Path\033[0m  : %s\n\n\n\n\n\n\n", input_filepath);

    // get error measurements method
    int choice = 0;
    while (!choice) {
        clean_and_moveup_cursor(6);
        puts("\nPick Error Measurements Method:");
        puts("1. Variance");
        puts("2. Mean Absolute Deviation (MAD)");
        puts("3. Max Pixel Difference");
        puts("4. Entropy");
        printf(">>> \033[0K");
    
        choice = 0;
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                *variance_fn = &variance; 
                puts("\033[2K");
                clean_and_moveup_cursor(8);
                printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Error Measurements Method\033[0m  : %s\n\n\n", "variance");
                break;
            case 2: 
                *variance_fn = &mean_absolute_deviation;
                puts("\033[2K");
                clean_and_moveup_cursor(8); 
                printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Error Measurements Method\033[0m  : %s\n\n\n", "Mean Absolute Deviation");
                break;
            case 3: 
                *variance_fn = &max_pixel_difference; 
                puts("\033[2K");
                clean_and_moveup_cursor(8);
                printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Error Measurements Method\033[0m  : %s\n\n\n", "Max Pixel Difference");
                break;
            case 4: 
                *variance_fn = &entropy; 
                puts("\033[2K");
                clean_and_moveup_cursor(8);
                printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Error Measurements Method\033[0m  : %s\n\n\n", "Entropy");
                break;
            default:
                choice = 0;
                printf("Invalid choice. Please pick again.\033[1A");
                break;
        }

        // flush input
        while (getchar() != '\n');
    }

    // get error threshold
    valid = 0;
    while (!valid) {
        clean_and_moveup_cursor(2);
        printf("\nInsert error threshold ");
        switch (choice) {
            case 1: printf("[0 - 65025]: \n"); break;
            case 2: printf("[0 - 255]: \n"); break;
            case 3: printf("[0 - 255]: \n"); break;
            case 4: printf("[0 - 8]: \n"); break;
        }
        printf(">>> \033[0K");
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
        if (!valid) printf("Invalid input range.\033[1A");

        // flush input
        while (getchar() != '\n');
    }
    puts("\033[2K");
    clean_and_moveup_cursor(4);
    printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Error Threshold\033[0m            : %lf\n\n\n", *error_threshold);


    // get minimum block size (not sure whats the range is. assuming must be bigger than 0)
    valid = 0;
    while (!valid) {
        clean_and_moveup_cursor(2);
        puts("\nInsert minimum block size [0 - image_size]:");
        printf(">>> ");
        scanf("%d", minimum_block_size);
        if (*minimum_block_size > 0) valid = 1;
        else printf("Can't be smaller than 1\033[1A");

        // flush input
        while (getchar() != '\n');
    }
    puts("\033[2K");
    clean_and_moveup_cursor(4);
    printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Minimum Block Size\033[0m         : %d\n\n\n", *minimum_block_size);

    // get PNG output filepath
    valid = 0;
    while (!valid) {
        clean_and_moveup_cursor(2);
        puts("\nInsert absolute path to output image file: ");
        printf(">>> \033[0K");
        fgets(output_filepath, MAX_FILEPATH_LEN, stdin);
        output_filepath[strcspn(output_filepath, "\n")] = '\0';
        trim(output_filepath);
        if (strcmp(input_filepath, output_filepath) == 0) {
            printf("Output file cannot be the same as input file\033[1A");
            continue;
        }
        FILE *file = fopen(output_filepath, "wb");
        if (file == NULL) {
            printf("File directory doesn't exist. please try again\033[1A");
        }
        else {
            fclose(file);
            valid = 1;    
        }
    }
    puts("\033[2K");
    clean_and_moveup_cursor(4);
    printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Output Image Absolute Path\033[0m : %s\n\n\n", output_filepath);


    // get GIF output filepath
    valid = 0;
    while (!valid) {
        clean_and_moveup_cursor(2);
        puts("\nInsert absolute path to output GIF file: ");
        printf(">>> \033[0K");
        fgets(gif_output_filename, MAX_FILEPATH_LEN, stdin);
        gif_output_filename[strcspn(gif_output_filename, "\n")] = '\0';
        trim(gif_output_filename);
        if (strcmp(input_filepath, gif_output_filename) == 0) {
            printf("Output file cannot be the same as input file\033[1A");
            continue;
        }
        FILE *file = fopen(gif_output_filename, "wb");
        if (file == NULL) {
            printf("File directory doesn't exist. please try again\033[1A");
        }
        else {
            fclose(file);
            valid = 1;    
        }
    }
    puts("\033[2K");
    clean_and_moveup_cursor(4);
    printf("\033[38;2;177;209;130m[*]\033[38;2;206;126;0m Output GIF Absolute Path\033[0m   : %s\n\n", gif_output_filename);
    puts("\033[38;2;206;126;0mCompressing....\033[0m\n");
}

