#include <string.h>
#include <stdio.h>
#include "course_actions.h"
#include "course_list.h"

void course_actions_view_specific(struct CourseList *course_list, size_t index)
{
    struct Course *course = course_list_get(course_list, index);
    if (course != NULL)
        printf("%lu\t%s\t%s\t\t%s\t%.2f / %.2f\t%.2f\t\tu%lu r%lu\n", index + 1, course->name, course->title, course->semester_name, course->credits_counted, course->credits_passed, course->grade_points, index + 1, index + 1);
}

void course_actions_view(struct CourseList *course_list)
{
    printf("ID\tName\tTitle\t\t\tSemester\tCredits\t\tGrade Points\tActions\n");
    for (int i = 0; i < course_list->quantity; i++)
        course_actions_view_specific(course_list, i);
}

void course_actions_process(struct CourseList *course_list, char *action)
{
    char command;
    size_t index;

    printf("%c %lu\n", command, index);

    if (command == 'v')
        course_actions_view(course_list);
    else if (command == 'u')
        course_actions_update(course_list, index);
    else if (command == 'r')
        course_actions_remove(course_list, index);
    else
        printf("Unrecognized action. Please try again.\n");
}

void course_actions_update(struct CourseList *course_list, size_t index)
{
    if (index >= course_list->quantity)
        printf("Course not found\n");

    struct Course course = course_list->items[index];
    printf("Please enter the new properties (leave blank for skipping):\n");

    printf("Name: ");
    char name[7];
    fgets(name, 7, stdin);
}