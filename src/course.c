#include <stdlib.h>
#include "course.h"

struct Course course_empty()
{
    return (struct Course){.name = (const char *)calloc(8, sizeof(char)), .title = (const char *)calloc(51, sizeof(char)), .semester_name = (const char *)calloc(31, sizeof(char)), .credits_counted = 0, .credits_passed = 0, .grade_points = 0};
}