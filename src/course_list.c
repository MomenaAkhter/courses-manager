/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#include "course_list.h"
#include "course.h"
#include "csv.h"
#include "structs/CourseList.h"
#include "structs/CsvWriteSession.h"
#include <stdio.h>
#include <string.h>

// Create an empty course list
struct CourseList* course_list_empty()
{
    struct CourseList* course_list = (struct CourseList*)malloc(sizeof(struct CourseList));

    *course_list = (struct CourseList) { .quantity = 0, .items = calloc(0, sizeof(struct Course)) };

    return course_list;
}

// Load course list from a file
struct CourseList* course_list_load(const char* file_path)
{
    FILE* file = fopen(file_path, "r");

    if (file == NULL)
        return NULL;

    struct CourseList* course_list = course_list_empty();

    while (!feof(file)) {
        struct Course course = course_empty();

        csv_read_string(file, (char*)course.name);
        csv_read_string(file, (char*)course.title);
        csv_read_string(file, (char*)course.semester_name);
        csv_read_float(file, &course.credits_counted);
        csv_read_float(file, &course.credits_passed);
        csv_read_float(file, &course.grade_points);

        // If the name is blank, avoid adding the course
        if (strlen(course.name) > 0)
            course_list_add(course_list, course);
    }

    fclose(file);

    course_list->source = (const char*)realloc((char*)course_list->source, sizeof(char) * 101);
    strcpy((char*)course_list->source, file_path);

    return course_list;
}

// Save course list to a file
bool course_list_save(struct CourseList* course_list)
{
    FILE* file = fopen(course_list->source, "w");

    if (file == NULL)
        return false;

    struct CsvWriteSession* csv_write_session = csv_write_session_new(file);

    for (int i = 0; i < course_list->quantity; i++) {
        struct Course course = course_list->items[i];
        csv_line_add_string(csv_write_session, course.name);
        csv_line_add_string(csv_write_session, course.title);
        csv_line_add_string(csv_write_session, course.semester_name);
        csv_line_add_float(csv_write_session, &course.credits_counted);
        csv_line_add_float(csv_write_session, &course.credits_passed);
        csv_line_add_float(csv_write_session, &course.grade_points);
        csv_line_write(csv_write_session);
    }

    fclose(file);

    return true;
}

// Quantity of items in a course list
size_t course_list_quantity(struct CourseList* course_list)
{
    return course_list->quantity;
}

// Add a new course to a course list
void course_list_add(struct CourseList* course_list, struct Course course)
{
    course_list->quantity++;
    course_list->items = (struct Course*)realloc(course_list->items, sizeof(struct Course) * course_list->quantity);
    course_list->items[course_list->quantity - 1] = course;
}

// Get a course from a course list
struct Course* course_list_get(struct CourseList* course_list, size_t index)
{
    if (index < course_list->quantity)
        return &course_list->items[index];
    else
        return NULL;
}

// Update a course in a course list
bool course_list_update(struct CourseList* course_list, size_t index, struct Course course)
{
    if (index >= course_list->quantity)
        return false;

    if (course.name != NULL)
        course_list->items[index].name = course.name;
    if (course.title != NULL)
        course_list->items[index].title = course.title;
    if (course.semester_name != NULL)
        course_list->items[index].semester_name = course.semester_name;
    course_list->items[index].credits_counted = course.credits_counted;
    course_list->items[index].credits_passed = course.credits_passed;
    course_list->items[index].grade_points = course.grade_points;

    return true;
}

// Remove a course in a course list
bool course_list_remove(struct CourseList* course_list, size_t index)
{
    if (index >= course_list->quantity)
        return false;

    course_list->quantity--;

    for (size_t i = index; i < course_list->quantity; i++)
        course_list->items[i] = course_list->items[i + 1];

    return true;
}

// Free dynamically allocated memory blocks associated with a course list
void course_list_free(struct CourseList* course_list)
{
    for (int i = 0; i < course_list->quantity; i++) {
        free((char*)course_list->items[i].name);
        free((char*)course_list->items[i].title);
        free((char*)course_list->items[i].semester_name);
    }
    free(course_list->items);
    free(course_list);
}