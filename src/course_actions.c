#include <string.h>
#include <stdio.h>
#include "course_actions.h"
#include "course_list.h"
#include "helpers.h"
#include "course.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void course_actions_view_specific(struct Course *course, size_t index, bool show_id)
{
    if (course != NULL)
    {
        if (show_id)
            printf("%lu\t%s\t%s\t\t%s\t%.2f / %.2f\t%.2f\t\tu%lu, r%lu\n", index + 1, course->name, course->title, course->semester_name, course->credits_passed, course->credits_counted, course->grade_points, index + 1, index + 1);
        else
            printf("%s\t%s\t\t%s\t%.2f / %.2f\t%.2f\n", course->name, course->title, course->semester_name, course->credits_passed, course->credits_counted, course->grade_points);
    }
}

void course_actions_view(struct CourseList *course_list)
{
    printf("\n");
    heading("List of All Courses");

    course_actions_view_range(course_list->items, course_list->quantity, true);

    printf("\nGlobal actions: a, h, s, v\n\n");
}

void course_actions_view_range(struct Course *begin, size_t length, bool show_id)
{
    print_yellow(true);
    printf("%sName\tTitle\t\t\tSemester\tCredits\t\tGrade Points%s\n", show_id ? "ID\t" : "", show_id ? "\tActions" : "");
    print_reset();

    print_reset();
    for (struct Course *i = begin; length-- != 0; i++)
        course_actions_view_specific(i, i - begin, show_id);
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
    else if (command == 's')
        course_actions_summary(course_list);
    else
    {
        print_red(false);
        printf("Unrecognized action. Please try again.\n");
        print_reset();
    }
}

void course_actions_update(struct CourseList *course_list, size_t index)
{
    if (index >= course_list->quantity)
    {
        print_red(false);
        printf("Course not found\n");
        print_reset();
        return;
    }

    struct Course *course = &course_list->items[index];
    printf("\n");
    heading("Course Update");
    printf("\n");

    course_actions_view_range(course_list->items + index, 1, false);

    printf("\nPlease enter the new properties (leave blank for skipping):\n\n");

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

    if (course_list_save(course_list))
    {
        print_green(false);
        printf("\nSuccessfully updated the course.\n");
        print_reset();
    }
    else
    {
        print_red(false);
        printf("\nFailed to update the course.\n");
        print_reset();
    }
    printf("\n");
}

void course_actions_remove(struct CourseList *course_list, size_t index)
{
    printf("\n");
    heading("Course Removal");
    printf("\n");

    course_actions_view_range(course_list->items + index, 1, false);

    printf("\nAre you sure you want to remove the above course? (y|N) ");

    char confirmation[2];
    fflush(stdin);
    fgets(confirmation, 2, stdin);

    if (strcmp(confirmation, "Y") == 0 || strcmp(confirmation, "y") == 0)
    {
        if (course_list_remove(course_list, index))
        {
            print_green(false);
            printf("\nSuccessfully removed the course!\n\n");
            print_reset();
        }
        else
        {
            print_red(false);
            printf("\nFailed to remove the course.\n\n");
            print_reset();
        }

        course_list_save(course_list);
    }
}

void course_actions_help(struct CourseList *course_list)
{
    printf("\n");
    heading("Help");
    printf("h: Help\nv: View all courses\ns: Summary\na: Add a new course\nu[id]: Update a specific course based on its ID\nr[id]: Remove a specific course based on its ID\n\n");
}

void course_actions_add(struct CourseList *course_list)
{
    struct Course course = course_empty();

    printf("\n");
    heading("Add New Course");

    printf("\nName: ");
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
    if (course_list_save(course_list))
    {
        print_green(false);
        printf("\nSuccessfully added the course.\n");
        print_reset();
    }
    else
    {
        print_red(false);
        printf("\nFailed to add the course.\n");
        print_reset();
    }

    printf("\n");
}

void course_actions_summary(struct CourseList *course_list)
{
    float total_credits = 0, total_grade_points = 0;
    for (size_t i = 0; i < course_list->quantity; i++)
    {
        total_grade_points += course_list->items[i].grade_points;
        total_credits += MIN(course_list->items[i].credits_counted, course_list->items[i].credits_passed);
    }

    print_yellow(false);
    printf("\n");
    heading("Summary");
    print_reset();
    printf("CGPA: %.2f\n\n", total_grade_points / total_credits);
}