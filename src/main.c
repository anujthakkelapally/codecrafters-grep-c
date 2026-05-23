#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool match_pattern(const char* input_line, const char* pattern) {
    if (strlen(pattern) == 1) {
        return strchr(input_line, pattern[0]) != NULL;
    }
    else if (strcmp(pattern, "\\d") == 0) {
        for (int i = 0; input_line[i] != '\0'; i++) {
            if (isdigit(input_line[i]) != 0) {
                return true;
            }
        }
        return false;
    }
    else if (strcmp(pattern, "\\w") == 0) {
        for (int i = 0; input_line[i] != '\0'; i++) {
            if ((isalnum(input_line[i]) != 0) || (input_line[i] == '_')) {
                return true;
            }
        }
        return false;
    }
    else if ((pattern[0] == '[') && (pattern[1] != '^')) {
        int index = 1;
        while (pattern[index] != ']') {
            for (int i = 0; input_line[i] != '\0'; i++) {
                if (input_line[i] == pattern[index]) {
                    return true;
                }
            }
            index += 1;
        }
        return false;
    }
    else if ((pattern[0] == '[') && (pattern[1] == '^')) {
        for (int input_index = 0; input_line[input_index] != '\0'; input_index++) {
            bool unmatched = true;
            for (int pattern_index = 2; pattern[pattern_index] != '\0'; pattern_index++) {
                if (input_line[input_index] == pattern[pattern_index]) {
                    unmatched = false;
                }
            }
            if (unmatched) {
                return true;
            }
        }

        return false;
    }
    else {
        fprintf(stderr, "Unhandled pattern %s\n", pattern);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    fprintf(stderr, "Logs from your program will appear here\n");

    if (argc != 3) {
        fprintf(stderr, "Expected two arguments\n");
        return 1;
    }

    const char* flag = argv[1];
    const char* pattern = argv[2];

    if (strcmp(flag, "-E") != 0) {
        fprintf(stderr, "Expected first argument to be '-E'\n");
        return 1;
    }

    char input_line[1024];
    if (fgets(input_line, sizeof(input_line), stdin) == NULL) {
        return 1;
    }

    // Remove trailing newline
    input_line[strcspn(input_line, "\n")] = '\0';

    if (match_pattern(input_line, pattern)) {
        return 0;
    } else {
        return 1;
    }
}
