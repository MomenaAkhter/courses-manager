#include <stdlib.h>
#include "csv.h"

void csv_read_string(FILE *file, char *string)
{
    int j = 0;
    for (int i = 0;; i++)
    {
        char c;
        fscanf(file, "%c", &c);

        if ((c == ' ' || c == '\n' || c == '\t') && j == 0)
            continue;

        if (c == ',' || feof(file))
        {
            string[j] = '\0';
            break;
        }

        string[j] = c;
        j++;
    }
}

void csv_read_float(FILE *file, float *float_)
{
    fscanf(file, "%f,", float_);
}

struct CsvWriteSession *csv_write_session_new(FILE *file)
{
    struct CsvWriteSession *session = (struct CsvWriteSession *)malloc(sizeof(struct CsvWriteSession));
    *session = (struct CsvWriteSession){.file = file, .line_value_quantity = 0};
    return session;
}

void csv_line_write(struct CsvWriteSession *session)
{
    for (int i = 0; i < session->line_value_quantity; i++)
    {
        switch (session->line_value_types[i])
        {
        case 0:
            fprintf(session->file, "%s", (const char *)session->line_values[i]);
            break;
        default:
            fprintf(session->file, "%f", *((float *)session->line_values[i]));
        }
        if (i + 1 != session->line_value_quantity)
            fprintf(session->file, ", ");
    }
    fprintf(session->file, "\n");

    session->line_values = (void **)realloc(session->line_values, 0);
    session->line_value_types = (int *)realloc(session->line_value_types, 0);
    session->line_value_quantity = 0;
}

void csv_line_add_value(struct CsvWriteSession *session, void *value, int type)
{
    session->line_values = (void **)realloc(session->line_values, sizeof(void *) * (session->line_value_quantity + 1));
    session->line_value_types = (int *)realloc(session->line_value_types, sizeof(int *) * (session->line_value_quantity + 1));

    session->line_values[session->line_value_quantity] = (void *)value;
    session->line_value_types[session->line_value_quantity] = type;
    session->line_value_quantity++;
}

void csv_line_add_string(struct CsvWriteSession *session, const char *string)
{
    csv_line_add_value(session, (void *)string, 0);
}

void csv_line_add_float(struct CsvWriteSession *session, float *float_)
{
    csv_line_add_value(session, (void *)float_, 1);
}