/*
Name: Momena Akhter Shukhi
ID: 162 0763 042
*/

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <stdbool.h>

char *trim(char *);
void print_red(bool);
void print_green(bool);
void print_yellow(bool);
void print_purple(bool);
void print_reset();
void heading(const char *);
void grade(float, float, char *);

#endif // __HELPERS_H__