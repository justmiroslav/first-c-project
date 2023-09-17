#include <stdio.h>
#include <string.h>

char text[100];
int text_len = 0;

void append_text(char *new_text) {
    if (text_len + strlen(new_text) >= 100) {
        printf("Error: Text too long\n");
        return;
    }
    strcat(text, new_text);
    text_len += strlen(new_text);
}

void new_line() {
    if (text_len >= 100) {
        printf("Error: Text too long\n");
        return;
    }
    text[text_len++] = '\n';
    text[text_len] = '\0';
}

void save_text(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fputs(text, file);
        fclose(file);
        printf("Text has been saved successfully\n");
    } else {
        printf("Error opening file for saving\n");
    }
}

void load_text(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        printf("\n");
        fclose(file);
    } else {
        printf("Error opening file for loading\n");
    }
}

void print_text() {
    printf("%s\n", text);
}

int main() {
    int command;
    char input[100];
    char filename[100];
    while (true) {
        printf("Enter the command!\n");
        scanf("%d", &command);
        if (command == 1) {
            printf("Enter text to append:\n");
            scanf(" %[^\n]", input);
            append_text(input);
        } else if (command == 2) {
            new_line();
            printf("New line is started\n");
        } else if (command == 3) {
            printf("Enter the file name for saving:\n");
            scanf(" %[^\n]", filename);
            save_text(filename);
        } else if (command == 4) {
            printf("Enter the file name for loading:\n");
            scanf(" %[^\n]", filename);
            load_text(filename);
        } else if (command == 5) {
            print_text();
        } else if (command == 8) {
            break;
        } else {
            printf("Incorrect command. Enter a valid command.\n");
        }
    }
    return 0;
}