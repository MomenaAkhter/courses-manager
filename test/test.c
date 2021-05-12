#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "course_list.h"

int fails = 0;
int counter = 1;

void assert(bool assertion, const char *message)
{
    if (!assertion)
    {
        printf("(%d) Assertion failed: %s\n", counter, message);
        fails++;
    }
    counter++;
}

void assert_str_eq(const char *str1, const char *str2)
{
    if (strcmp(str1, str2) != 0)
    {
        printf("(%d) Strings mismatch: '%s' and '%s'\n", counter, str1, str2);
        fails++;
    }
    counter++;
}

int main()
{
    struct CourseList *course_list = course_list_empty();
    assert(course_list != NULL, "Course list is null!");
    assert(course_list_quantity(course_list) == 0, "Course list should be empty");

    course_list_add(course_list, (struct Course){.name = "CSE115", .title = "Hey now brown cow!", .semester_name = "Fuck you", .credits_counted = 3, .credits_passed = 3, .grade_points = 9});

    assert(course_list_quantity(course_list) == 1, "Course list should be 1 in size");
    assert_str_eq(course_list_get(course_list, 0)->name, "CSE115");

    course_list_update(course_list, 0, (struct Course){.name = "CSE215"});

    assert_str_eq(course_list_get(course_list, 0)->name, "CSE215");

    course_list_add(course_list, (struct Course){.name = "CSE373", .title = "Hey now fuck cow!", .semester_name = "Fuck you", .credits_counted = 3, .credits_passed = 3, .grade_points = 9});
    course_list_add(course_list, (struct Course){.name = "CSE425", .title = "Hey now fuck cow!", .semester_name = "Fuck you", .credits_counted = 3, .credits_passed = 3, .grade_points = 9});
    assert(course_list_quantity(course_list) == 3, "Course list should be 3 in size");

    course_list_delete(course_list, 0);

    assert(course_list_quantity(course_list) == 2, "Course list should be 2 in size");
    assert_str_eq(course_list_get(course_list, 0)->name, "CSE373");
    assert_str_eq(course_list_get(course_list, 1)->name, "CSE425");

    if (fails == 0)
        printf("OK\n");

    return 0;
}