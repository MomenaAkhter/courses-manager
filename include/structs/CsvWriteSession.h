#ifndef __STRUCT_CSVWRITESESSION_H__
#define __STRUCT_CSVWRITESESSION_H__

#include <stdbool.h>

struct CsvWriteSession
{
    void **line_values;
    int *line_value_types;
    size_t line_value_quantity;
    FILE *file;
};

#endif // __STRUCT_CSVWRITESESSION_H__