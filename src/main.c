#include <stdio.h>
#include <string.h>
#include "structs/Course.h"
#include "course_list.h"
#include "course_actions.h"
#include "helpers.h"

int main()
{
    struct CourseList *course_list = course_list_load("courses.csv");

    char action[10];
    strcpy(action, "v");
    while (strcmp(action, "q") != 0)
    {
        course_actions_process(course_list, action);

        printf("Action: ");
        scanf("%s", action);
    }

    // course_list_save(course_list, "courses2.csv");

    return 0;
}