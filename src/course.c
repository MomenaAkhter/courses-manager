/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#include "course.h"
#include <stdlib.h>

// Create an empty course
struct Course course_empty()
{
    return (struct Course) { .name = (const char*)calloc(8, sizeof(char)), .title = (const char*)calloc(51, sizeof(char)), .semester_name = (const char*)calloc(31, sizeof(char)), .credits_counted = 0, .credits_passed = 0, .grade_points = 0 };
}