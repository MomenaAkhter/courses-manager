/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#include "course_actions.h"
#include "course.h"
#include "course_list.h"
#include "helpers.h"
#include <stdio.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Print a specific course based on the index
void course_actions_view_specific(struct Course* course, size_t index, bool show_id)
{
    if (course != NULL) {
        // char format[70];
        // sprintf(format, "%s%-10.7s%-28.24s%-11.11s%.2f%s\n", show_id ? "%lu\t" : "", course->name, course->title, course->semester_name, 1.0f, show_id ? "\t\tu%lu, r%lu" : "");

        // printf("%s\n", format);

        char grade_string[3];
        grade(course->grade_points, MIN(course->credits_counted, course->credits_passed), grade_string);

        if (show_id)
            printf("%lu\t%-10.7s%-28.24s%-11.11s\t%.2f / %.2f\t%.2f (%s)\tu%lu, r%lu\n", index + 1, course->name, course->title, course->semester_name, course->credits_passed, course->credits_counted, course->grade_points, grade_string, index + 1, index + 1);
        else
            printf("%-10.7s%-28.24s%-11.11s\t%.2f / %.2f\t%.2f (%s)\n", course->name, course->title, course->semester_name, course->credits_passed, course->credits_counted, course->grade_points, grade_string);
    }
}

// Action: View courses
void course_actions_view(struct CourseList* course_list)
{
    printf("\n");
    heading("List of All Courses");

    course_actions_view_range(course_list->items, course_list->quantity, true);

    printf("\nGlobal actions: a, h, s, o, v, l\n\n");
}

// Print courses in a specific range
void course_actions_view_range(struct Course* begin, size_t length, bool show_id)
{
    print_yellow(true);
    printf("%s%-10.7s%-28.24s%-11.11s\tCredits\t\tGrade Points%s\n", show_id ? "ID\t" : "", "Name", "Title", "Semester", show_id ? "\tActions" : "");
    print_reset();

    print_reset();
    for (struct Course* i = begin; length-- != 0; i++)
        course_actions_view_specific(i, i - begin, show_id);
}

// Process a given action
void course_actions_process(struct CourseList** course_list_handle, char* action)
{
    char command;
    size_t index;

    sscanf(action, "%c%lu", &command, &index);

    if (command == 'v')
        course_actions_view(*course_list_handle);
    else if (command == 'u')
        course_actions_update(*course_list_handle, index - 1);
    else if (command == 'r')
        course_actions_remove(*course_list_handle, index - 1);
    else if (command == 'h')
        course_actions_help(*course_list_handle);
    else if (command == 'a')
        course_actions_add(*course_list_handle);
    else if (command == 'o')
        course_actions_overview(*course_list_handle);
    else if (command == 's')
        course_actions_search(*course_list_handle);
    else if (command == 'l')
        course_actions_load(course_list_handle);
    else {
        print_red(false);
        printf("Unrecognized action. Please try again.\n");
        print_reset();
    }
}

// Action: Update a course
void course_actions_update(struct CourseList* course_list, size_t index)
{
    if (index >= course_list->quantity) {
        print_red(false);
        printf("Course not found\n");
        print_reset();
        return;
    }

    struct Course* course = &course_list->items[index];
    printf("\n");
    heading("Course Update");
    printf("\n");

    course_actions_view_range(course_list->items + index, 1, false);

    printf("\nPlease enter the new properties (leave blank for skipping a property):\n\n");

    printf("Name: ");
    char name[7];
    fflush(stdin);
    fgets(name, 7, stdin);
    char* trimmed_name = trim(name);
    if (strlen(trimmed_name) != 0)
        strcpy((char*)course->name, trimmed_name);

    printf("Title: ");
    char title[51];
    fflush(stdin);
    fgets(title, 51, stdin);
    char* trimmed_title = trim(title);
    if (strlen(trimmed_title) != 0)
        strcpy((char*)course->title, trimmed_title);

    printf("Semester name: ");
    char semester_name[31];
    fflush(stdin);
    fgets(semester_name, 31, stdin);
    char* trimmed_semester_name = trim(semester_name);
    if (strlen(trimmed_semester_name) != 0)
        strcpy((char*)course->semester_name, trimmed_semester_name);

    printf("Credits counted: ");
    char credits_counted[6];
    fflush(stdin);
    fgets(credits_counted, 6, stdin);
    char* trimmed_credits_counted = trim(credits_counted);
    if (strlen(trimmed_credits_counted) != 0)
        sscanf(trimmed_credits_counted, "%f", &course->credits_counted);

    printf("Credits passed: ");
    char credits_passed[6];
    fflush(stdin);
    fgets(credits_passed, 6, stdin);
    char* trimmed_credits_passed = trim(credits_passed);
    if (strlen(trimmed_credits_passed) != 0)
        sscanf(trimmed_credits_passed, "%f", &course->credits_passed);

    printf("Grade points: ");
    char grade_points[6];
    fflush(stdin);
    fgets(grade_points, 6, stdin);
    char* trimmed_grade_points = trim(grade_points);
    if (strlen(trimmed_grade_points) != 0)
        sscanf(trimmed_grade_points, "%f", &course->grade_points);

    if (course_list_save(course_list)) {
        print_green(false);
        printf("\nSuccessfully updated the course.\n");
        print_reset();
    } else {
        print_red(false);
        printf("\nFailed to update the course.\n");
        print_reset();
    }
    printf("\n");
}

// Action: Remove a course
void course_actions_remove(struct CourseList* course_list, size_t index)
{
    printf("\n");
    heading("Course Removal");
    printf("\n");

    course_actions_view_range(course_list->items + index, 1, false);

    printf("\nAre you sure you want to remove the above course? (y|N) ");

    char confirmation[2];
    fflush(stdin);
    fgets(confirmation, 2, stdin);

    if (strcmp(confirmation, "Y") == 0 || strcmp(confirmation, "y") == 0) {
        if (course_list_remove(course_list, index)) {
            print_green(false);
            printf("\nSuccessfully removed the course!\n\n");
            print_reset();
        } else {
            print_red(false);
            printf("\nFailed to remove the course.\n\n");
            print_reset();
        }

        course_list_save(course_list);
    }
}

// Action: Help
void course_actions_help(struct CourseList* course_list)
{
    printf("\n");
    heading("Help");
    printf("h: Help\nv: View all courses\no: Overview\na: Add a new course\nu[id]: Update a specific course based on its ID\nr[id]: Remove a specific course based on its ID\ns: Search for courses\nl: Load CSV file.\n\n");
}

// Action: Add a new course
void course_actions_add(struct CourseList* course_list)
{
    struct Course course = course_empty();

    printf("\n");
    heading("Add New Course");

    printf("\nName: ");
    char name[7];
    fflush(stdin);
    fgets(name, 7, stdin);
    char* trimmed_name = trim(name);
    strcpy((char*)course.name, trimmed_name);

    printf("Title: ");
    char title[51];
    fflush(stdin);
    fgets(title, 51, stdin);
    char* trimmed_title = trim(title);
    strcpy((char*)course.title, trimmed_title);

    printf("Semester name: ");
    char semester_name[31];
    fflush(stdin);
    fgets(semester_name, 31, stdin);
    char* trimmed_semester_name = trim(semester_name);
    strcpy((char*)course.semester_name, trimmed_semester_name);

    printf("Credits counted: ");
    char credits_counted[6];
    fflush(stdin);
    fgets(credits_counted, 6, stdin);
    char* trimmed_credits_counted = trim(credits_counted);
    sscanf(trimmed_credits_counted, "%f", &course.credits_counted);

    printf("Credits passed: ");
    char credits_passed[6];
    fflush(stdin);
    fgets(credits_passed, 6, stdin);
    char* trimmed_credits_passed = trim(credits_passed);
    sscanf(trimmed_credits_passed, "%f", &course.credits_passed);

    printf("Grade points: ");
    char grade_points[6];
    fflush(stdin);
    fgets(grade_points, 6, stdin);
    char* trimmed_grade_points = trim(grade_points);
    sscanf(trimmed_grade_points, "%f", &course.grade_points);

    course_list_add(course_list, course);
    if (course_list_save(course_list)) {
        print_green(false);
        printf("\nSuccessfully added the course.\n");
        print_reset();
    } else {
        print_red(false);
        printf("\nFailed to add the course.\n");
        print_reset();
    }

    printf("\n");
}

// Action: Show an overview of all the courses and its associated information
void course_actions_overview(struct CourseList* course_list)
{
    float total_credits = 0, total_grade_points = 0;
    const char** semester_names = (const char**)calloc(0, sizeof(const char*));
    size_t semester_names_count = 0;
    for (size_t i = 0; i < course_list->quantity; i++) {
        total_grade_points += course_list->items[i].grade_points;
        total_credits += MIN(course_list->items[i].credits_counted, course_list->items[i].credits_passed);

        bool semester_name_found = false;
        for (int j = 0; j < semester_names_count; j++) {
            if (strcmp(course_list->items[i].semester_name, semester_names[j]) == 0) {
                semester_name_found = true;
                break;
            }
        }

        if (!semester_name_found) {
            semester_names = (const char**)realloc(semester_names, (semester_names_count + 1) * sizeof(const char*));
            semester_names[semester_names_count] = course_list->items[i].semester_name;
            semester_names_count++;
        }
    }

    print_yellow(false);
    printf("\n");
    heading("Overview");
    printf("\n");
    print_reset();

    printf("CGPA: %.2f\nTotal Grade Points: %.2f\nTotal Credits: %.2f\n", total_grade_points / total_credits, total_grade_points, total_credits);

    size_t best_semester = 0, worst_semester = 0;
    float best_semester_tgpa = -1, worst_semester_tgpa = -1;
    printf("\nTGPAs:\n");
    for (size_t i = 0; i < semester_names_count; i++) {
        printf("\t%s: ", semester_names[i]);
        float total_grade_points = 0, total_credits = 0;
        for (size_t j = 0; j < course_list->quantity; j++) {
            if (strcmp(course_list->items[j].semester_name, semester_names[i]) == 0) {
                total_grade_points += course_list->items[j].grade_points;
                total_credits += MIN(course_list->items[j].credits_counted, course_list->items[j].credits_passed);
            }
        }
        float tgpa = total_grade_points / total_credits;
        printf("\t%.2f\n", tgpa);

        if (i == 0) {
            best_semester_tgpa = tgpa;
            worst_semester_tgpa = tgpa;
        } else {
            if (tgpa < worst_semester_tgpa) {
                worst_semester_tgpa = tgpa;
                worst_semester = i;
            }
            if (tgpa > best_semester_tgpa) {
                best_semester_tgpa = tgpa;
                best_semester = i;
            }
        }
    }

    printf("Best semester: %s (%.2f)\n", semester_names[best_semester], best_semester_tgpa);
    printf("Worst semester: %s (%.2f)\n", semester_names[worst_semester], worst_semester_tgpa);

    printf("\n");
}

// Action: Search for a specific course[s]
void course_actions_search(struct CourseList* course_list)
{
    printf("\n");
    heading("Search");

    printf("\nQuery: ");
    char query[100];
    fflush(stdin);
    fgets(query, 100, stdin);
    char* query_trimmed = trim(query);

    if (strlen(query_trimmed) > 0) {
        printf("\n");
        course_actions_view_range(NULL, 0, true);
        for (size_t i = 0; i < course_list->quantity; i++) {
            if (strstr(course_list->items[i].name, query_trimmed) != NULL || strstr(course_list->items[i].title, query_trimmed) != NULL || strstr(course_list->items[i].semester_name, query_trimmed) != NULL) {
                course_actions_view_specific(course_list->items + i, i, true);
            }
        }
    } else {
        print_red(false);
        printf("\nCan't accept blank queries.\n");
        print_reset();
    }

    printf("\n");
}

// Action: Reload from the file
void course_actions_load(struct CourseList** course_list_handle)
{
    char file_path[101];
    strcpy(file_path, (*course_list_handle)->source);
    course_list_free(*course_list_handle);
    *course_list_handle = course_list_load(file_path);
}