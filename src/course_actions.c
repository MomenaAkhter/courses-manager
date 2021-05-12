#include <string.h>
#include <stdio.h>
#include "course_actions.h"
#include "course_list.h"
#include "helpers.h"
#include "course.h"

void course_actions_view_specific(struct CourseList *course_list, size_t index)
{
    struct Course *course = course_list_get(course_list, index);
    if (course != NULL)
        printf("%lu\t%s\t%s\t\t%s\t%.2f / %.2f\t%.2f\t\tu%lu, r%lu\n", index + 1, course->name, course->title, course->semester_name, course->credits_passed, course->credits_counted, course->grade_points, index + 1, index + 1);
}

void course_actions_view(struct CourseList *course_list)
{
    printf("Global actions: a, h\nID\tName\tTitle\t\t\tSemester\tCredits\t\tGrade Points\tActions\n");
    for (int i = 0; i < course_list->quantity; i++)
        course_actions_view_specific(course_list, i);
}

void course_actions_process(struct CourseList *course_list, char *action)
{
    char command;
    size_t index;

    sscanf(action, "%c%lu", &command, &index);

    if (command == 'v')
        course_actions_view(course_list);
    else if (command == 'u')
        course_actions_update(course_list, index - 1);
    else if (command == 'r')
        course_actions_remove(course_list, index - 1);
    else if (command == 'h')
        course_actions_help(course_list);
    else if (command == 'a')
        course_actions_add(course_list);
    else
        printf("Unrecognized action. Please try again.\n");
}

void course_actions_update(struct CourseList *course_list, size_t index)
{
    if (index >= course_list->quantity)
        printf("Course not found\n");

    struct Course *course = &course_list->items[index];
    printf("Please enter the new properties (leave blank for skipping):\n");

    printf("Name: ");
    char name[7];
    fflush(stdin);
    fgets(name, 7, stdin);
    char *trimmed_name = trim(name);
    if (strlen(trimmed_name) != 0)
        strcpy((char *)course->name, trimmed_name);

    printf("Title: ");
    char title[51];
    fflush(stdin);
    fgets(title, 51, stdin);
    char *trimmed_title = trim(title);
    if (strlen(trimmed_title) != 0)
        strcpy((char *)course->title, trimmed_title);

    printf("Semester name: ");
    char semester_name[31];
    fflush(stdin);
    fgets(semester_name, 31, stdin);
    char *trimmed_semester_name = trim(semester_name);
    if (strlen(trimmed_semester_name) != 0)
        strcpy((char *)course->semester_name, trimmed_semester_name);

    printf("Credits counted: ");
    char credits_counted[6];
    fflush(stdin);
    fgets(credits_counted, 6, stdin);
    char *trimmed_credits_counted = trim(credits_counted);
    if (strlen(trimmed_credits_counted) != 0)
        sscanf(trimmed_credits_counted, "%f", &course->credits_counted);

    printf("Credits passed: ");
    char credits_passed[6];
    fflush(stdin);
    fgets(credits_passed, 6, stdin);
    char *trimmed_credits_passed = trim(credits_passed);
    if (strlen(trimmed_credits_passed) != 0)
        sscanf(trimmed_credits_passed, "%f", &course->credits_passed);

    printf("Grade points: ");
    char grade_points[6];
    fflush(stdin);
    fgets(grade_points, 6, stdin);
    char *trimmed_grade_points = trim(grade_points);
    if (strlen(trimmed_grade_points) != 0)
        sscanf(trimmed_grade_points, "%f", &course->grade_points);

    course_list_save(course_list);
}

void course_actions_remove(struct CourseList *course_list, size_t index)
{
    if (course_list_remove(course_list, index))
        printf("Successfully removed course!\n");
    else
        printf("Failed to remove course.\n");

    course_list_save(course_list);
}

void course_actions_help(struct CourseList *course_list)
{
    printf("Commands:\nh: Help\na: Add a new course\nu[id]: Update a specific course based on its ID\nr[id]: Remove a specific course based on its ID\n");
}

void course_actions_add(struct CourseList *course_list)
{
    struct Course course = course_empty();

    printf("Name: ");
    char name[7];
    fflush(stdin);
    fgets(name, 7, stdin);
    char *trimmed_name = trim(name);
    strcpy((char *)course.name, trimmed_name);

    printf("Title: ");
    char title[51];
    fflush(stdin);
    fgets(title, 51, stdin);
    char *trimmed_title = trim(title);
    strcpy((char *)course.title, trimmed_title);

    printf("Semester name: ");
    char semester_name[31];
    fflush(stdin);
    fgets(semester_name, 31, stdin);
    char *trimmed_semester_name = trim(semester_name);
    strcpy((char *)course.semester_name, trimmed_semester_name);

    printf("Credits counted: ");
    char credits_counted[6];
    fflush(stdin);
    fgets(credits_counted, 6, stdin);
    char *trimmed_credits_counted = trim(credits_counted);
    sscanf(trimmed_credits_counted, "%f", &course.credits_counted);

    printf("Credits passed: ");
    char credits_passed[6];
    fflush(stdin);
    fgets(credits_passed, 6, stdin);
    char *trimmed_credits_passed = trim(credits_passed);
    sscanf(trimmed_credits_passed, "%f", &course.credits_passed);

    printf("Grade points: ");
    char grade_points[6];
    fflush(stdin);
    fgets(grade_points, 6, stdin);
    char *trimmed_grade_points = trim(grade_points);
    sscanf(trimmed_grade_points, "%f", &course.grade_points);

    course_list_add(course_list, course);
    course_list_save(course_list);
}