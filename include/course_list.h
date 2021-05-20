/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#ifndef __COURSE_LIST_H__
#define __COURSE_LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include "structs/Course.h"
#include "structs/CourseList.h"

struct CourseList *course_list_empty();
struct CourseList *course_list_load(const char *);
bool course_list_save(struct CourseList *);
size_t course_list_quantity(struct CourseList *);
void course_list_add(struct CourseList *, struct Course);
void course_list_free(struct CourseList *);
struct Course *course_list_get(struct CourseList *, size_t);
bool course_list_update(struct CourseList *, size_t, struct Course);
bool course_list_remove(struct CourseList *, size_t);
void course_list_print(struct CourseList *, size_t);
void course_list_print_all(struct CourseList *);

#endif // __COURSE_LIST_H__