#ifndef __STRUCT_COURSELIST_H__
#define __STRUCT_COURSELIST_H__

#include <stdlib.h>
#include "Course.h"

struct CourseList
{
    struct Course *items;
    size_t quantity;
    const char *source;
};

#endif // __STRUCT_COURSELIST_H__