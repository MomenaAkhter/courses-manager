/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#include "csv.h"
#include <ctype.h>
#include <stdlib.h>

// Read the next string from an opened CSV file
void csv_read_string(FILE* file, char* string)
{
    int j = 0;
    while (!feof(file)) {
        char c;
        fscanf(file, "%c", &c);

        // Whitespaces at the beginning will be ignored
        if (isspace(c) && j == 0)
            continue;

        // Commas and end-of-files will end the string
        if (c == ',' || feof(file)) {
            string[j] = '\0';
            break;
        }

        string[j] = c;
        j++;
    }
}

// Read the next float from an opened CSV file
void csv_read_float(FILE* file, float* float_)
{
    fscanf(file, "%f,", float_);
}

// Create a new session for writing to a CSV file
struct CsvWriteSession* csv_write_session_new(FILE* file)
{
    struct CsvWriteSession* session = (struct CsvWriteSession*)malloc(sizeof(struct CsvWriteSession));
    *session = (struct CsvWriteSession) { .file = file, .line_value_quantity = 0 };
    return session;
}

// Write an entire line to a CSV file
void csv_line_write(struct CsvWriteSession* session)
{
    for (int i = 0; i < session->line_value_quantity; i++) {
        switch (session->line_value_types[i]) {
        case 0:
            fprintf(session->file, "%s", (const char*)session->line_values[i]);
            break;
        default:
            fprintf(session->file, "%f", *((float*)session->line_values[i]));
        }
        if (i + 1 != session->line_value_quantity)
            fprintf(session->file, ", ");
    }
    fprintf(session->file, "\n");

    session->line_values = (void**)realloc(session->line_values, 0);
    session->line_value_types = (int*)realloc(session->line_value_types, 0);
    session->line_value_quantity = 0;
}

// Add a value to a line to be written to a CSV file
void csv_line_add_value(struct CsvWriteSession* session, void* value, int type)
{
    session->line_values = (void**)realloc(session->line_values, sizeof(void*) * (session->line_value_quantity + 1));
    session->line_value_types = (int*)realloc(session->line_value_types, sizeof(int*) * (session->line_value_quantity + 1));

    session->line_values[session->line_value_quantity] = (void*)value;
    session->line_value_types[session->line_value_quantity] = type;
    session->line_value_quantity++;
}

// Add a string to a line to be written to a CSV file
void csv_line_add_string(struct CsvWriteSession* session, const char* string)
{
    csv_line_add_value(session, (void*)string, 0);
}

// Add a float to a line to be written to a CSV file
void csv_line_add_float(struct CsvWriteSession* session, float* float_)
{
    csv_line_add_value(session, (void*)float_, 1);
}