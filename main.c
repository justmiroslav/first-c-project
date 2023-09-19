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
        text_len = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            strcat(text, line);
            text_len += strlen(line);
        }
        fclose(file);
        printf("Text has been loaded successfully\n");
    } else {
        printf("Error opening file for loading\n");
    }
}

void print_text() {
    printf("%s\n", text);
}

void insert_text(int line, int index, char *new_text) {
    if (line < 0 || line >= text_len) {
        printf("Error: Invalid line\n");
        return;
    }
    int new_len = strlen(new_text);
    int current_line = 0;
    int i = 0;
    while (current_line < line) {
        if (text[i] == '\n') {
            current_line++;
        }
        i++;
    }
    int line_end = i;
    while (text[line_end] != '\n' && text[line_end] != '\0') {
        line_end++;
    }
    if (index < 0 || index > line_end || text_len + new_len >= 100) {
        printf("Error: Invalid index or text too long\n");
        return;
    }
    i += index;
    for (int j = line_end + new_len; j > i; j--) {
        text[j] = text[j - new_len];
    }
    for (int j = i, k = 0; k < new_len; j++, k++) {
        text[j] = new_text[k];
    }
    text_len += new_len;
}

void search_text(char *search_text) {
    int search_len = strlen(search_text);
    int current_line = 0;
    int idx = 0;
    bool correct_word = false;
    for (int i = 0; i < text_len; i++) {
        if (text[i] == '\n') {
            current_line++;
            idx = 0;
        } else {
            bool found = true;
            for (int j = 0; j < search_len; j++) {
                if (text[i + j] != search_text[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                printf("Text is present in this position: %d %d\n", current_line, idx);
                correct_word = true;
            }
        }
        if (text[i] != '\n') {
            idx++;
        }
    }
    if (!correct_word) {
        printf("Text not found.\n");
    }
}

int main() {
    int command, line, index;
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
        } else if (command == 6) {
            printf("Choose line and index:\n");
            scanf("%d %d", &line, &index);
            printf("Enter text to insert:\n");
            scanf(" %[^\n]", input);
            insert_text(line, index, input);
        } else if (command == 7) {
            printf("Enter text to search:\n");
            scanf(" %[^\n]", input);
            search_text(input);
        } else if (command == 8) {
            break;
        } else {
            printf("Incorrect command. Enter a valid command.\n");
        }
    }
    return 0;
}