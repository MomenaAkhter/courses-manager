#ifndef __CSV_H__
#define __CSV_H__

#include <stdio.h>
#include "structs/CsvWriteSession.h"

// Reading
void csv_read_string(FILE *, char *);
void csv_read_float(FILE *, float *);

// Writing
struct CsvWriteSession *csv_write_session_new(FILE *);
void csv_line_write(struct CsvWriteSession *);
void csv_line_add_string(struct CsvWriteSession *, const char *);
void csv_line_add_float(struct CsvWriteSession *, float *);

#endif // __CSV_H__