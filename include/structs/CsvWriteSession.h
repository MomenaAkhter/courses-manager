#ifndef __CSVWRITESESSION_H__
#define __CSVWRITESESSION_H__

#include <stdbool.h>

struct CsvWriteSession
{
    void **line_values;
    int *line_value_types;
    size_t line_value_quantity;
    FILE *file;
};

#endif // __CSVWRITESESSION_H__