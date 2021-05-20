/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#include "course_actions.h"
#include "course_list.h"
#include "helpers.h"
#include "structs/Course.h"
#include <stdio.h>
#include <string.h>

int main()
{
    // Load the course list from the CSV file
    struct CourseList* course_list = course_list_load("courses.csv");

    // Listen infinitely for user commands until the command "q" is executed
    char action[10];
    strcpy(action, "v");
    while (strcmp(action, "q") != 0) {
        // Process an action
        course_actions_process(&course_list, action);

        printf("Action: ");
        scanf("%s", action);
    }

    return 0;
}