#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "helpers.h"
#include "structs/CourseList.h"
#include "course_list.h"

char *trim(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

void print_red(bool bold)
{
    printf(bold ? "\033[1;31m" : "\033[0;31m");
}
void print_green(bool bold)
{
    printf(bold ? "\033[1;32m" : "\033[0;32m");
}
void print_yellow(bool bold)
{
    printf(bold ? "\033[1;33m" : "\033[0;33m");
}
void print_purple(bool bold)
{
    printf(bold ? "\033[1;35m" : "\033[0;35m");
}
void print_reset()
{
    printf("\033[0m");
}

void heading(const char *text)
{
    print_yellow(false);
    printf("%s\n", text);
    for (int i = 0; i < strlen(text); i++)
        printf("=");
    printf("\n");
    print_reset();
}

// Determine the grade using NSU's policies
void grade(float grade_points, float credits, char *string)
{
    float grade_points_average = grade_points / credits;
    if (grade_points_average == 4)
        strcpy(string, "A");
    else if (grade_points_average >= 3.7)
        strcpy(string, "A-");
    else if (grade_points_average >= 3.3)
        strcpy(string, "B+");
    else if (grade_points_average >= 3)
        strcpy(string, "B");
    else if (grade_points_average >= 2.7)
        strcpy(string, "B-");
    else if (grade_points_average >= 2.3)
        strcpy(string, "C+");
    else if (grade_points_average >= 2)
        strcpy(string, "C");
    else if (grade_points_average >= 1.7)
        strcpy(string, "C-");
    else if (grade_points_average >= 1.3)
        strcpy(string, "D+");
    else if (grade_points_average >= 1)
        strcpy(string, "D");
    else
        strcpy(string, "F");
}