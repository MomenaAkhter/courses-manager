/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#include "helpers.h"
#include "course_list.h"
#include "structs/CourseList.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Trim a string, removing whitespaces from both ends
char* trim(char* str)
{
    char* end;

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

// The following functions with prefix "print_" are associated with changing the color of the printed text on the shell
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

// Reset color of the next text that is going to be printed
void print_reset()
{
    printf("\033[0m");
}

// Add a heading (a piece of text underlined with '=')
void heading(const char* text)
{
    print_yellow(false);
    printf("%s\n", text);
    for (int i = 0; i < strlen(text); i++)
        printf("=");
    printf("\n");
    print_reset();
}

// Determine the grade using NSU's policies
void grade(float grade_points, float credits, char* string)
{
    if (credits == 0) {
        strcpy(string, "F");
        return;
    }

    // Round the floating-point value to the nearest decimal place
    float grade_points_average = roundf(grade_points / credits * 10) / 10;

    if (grade_points_average == 4.0f)
        strcpy(string, "A");
    else if (grade_points_average == 3.7f)
        strcpy(string, "A-");
    else if (grade_points_average == 3.3f)
        strcpy(string, "B+");
    else if (grade_points_average == 3.0f)
        strcpy(string, "B");
    else if (grade_points_average == 2.7f)
        strcpy(string, "B-");
    else if (grade_points_average == 2.3f)
        strcpy(string, "C+");
    else if (grade_points_average == 2.0f)
        strcpy(string, "C");
    else if (grade_points_average == 1.7f)
        strcpy(string, "C-");
    else if (grade_points_average == 1.3f)
        strcpy(string, "D+");
    else if (grade_points_average == 1.0f)
        strcpy(string, "D");
    else
        strcpy(string, "F");
}