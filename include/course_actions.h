#ifndef __COURSE_ACTIONS_H__
#define __COURSE_ACTIONS_H__

#include <stdlib.h>
#include "structs/CourseList.h"

void course_actions_view(struct CourseList *);
void course_actions_update(struct CourseList *, size_t);
void course_actions_remove(struct CourseList *, size_t);
void course_actions_add(struct CourseList *);
void course_actions_search(struct CourseList *, const char *);
void course_actions_process(struct CourseList *, char *);
void course_actions_help(struct CourseList *);
void course_actions_summary(struct CourseList *);

#endif // __COURSE_ACTIONS_H__