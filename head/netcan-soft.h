// Heads
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

// Define keys
#define UP 171
#define DOWN 172
#define LEFT 174
#define RIGHT 173
#define ENTER 13
#define EXIT 27
#define KILL 3
#define TAB 9

//Define fcs_theme;
struct fcs_theme {
    int box;
    int cursor;
    int title;
    int path;
    int menu_color;
    int menu_font_color;
    int up, down, left, right, enter, menu;
    int fix;
};
