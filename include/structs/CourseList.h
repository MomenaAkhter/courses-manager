#ifndef __COURSELIST_H__
#define __COURSELIST_H__

#include <stdlib.h>
#include "Course.h"

struct CourseList
{
    struct Course *items;
    size_t quantity;
};

#endif // __COURSELIST_H__