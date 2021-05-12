#ifndef __STRUCT_COURSE_H__
#define __STRUCT_COURSE_H__

struct Course
{
    const char *name;
    const char *title;
    const char *semester_name;
    float credits_counted;
    float credits_passed;
    float grade_points;
};

#endif // __STRUCT_COURSE_H__