#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define RED     1
#define GREEN   2
#define YELLOW  3
#define BLUE    4
#define MAGENTA  5
#define WHITE   6

void addstr_center(char* s, int y_off, int x_off) {
    int y = LINES / 2-1 + y_off;
    int x = (COLS / 2) + x_off;
    mvaddstr(y, x, s);
}

void switch_color(char* color_name) {
    switch(color_name[0]) {
        case 'R':
            attron(COLOR_PAIR(RED));
            break;
        case 'G':
            attron(COLOR_PAIR(GREEN));
            break;
        case 'Y':
            attron(COLOR_PAIR(YELLOW));
            break;
        case 'B':
            attron(COLOR_PAIR(BLUE));
            break;
        case 'M':
            attron(COLOR_PAIR(MAGENTA));
            break;
        case 'W':
            attron(COLOR_PAIR(WHITE));
            break;
        default:
            break;
    }
}

char* random_color_name() {
    int r = rand() % 5;
    switch(r) {
        case 0:
            return "RED";
            break;
        case 1:
            return "GREEN";
            break;
        case 2:
            return "YELLOW";
            break;
        case 3:
            return "BLUE";
            break;
        case 4:
            return "MAGENTA";
            break;
        case 5:
            return "WHITE";
            break;
        default:
            return "ERROR";
            break;
    }
}

float isochronic() {
    time_t start, end;
    time(&start);

    for(unsigned i = 0; i < LINES; i++) {
        char* c = random_color_name();
        switch_color(c);
        addstr_center(c, i-(LINES/2)+1, 0);

        c = random_color_name();
        switch_color(c);
        addstr_center(c, i-(LINES/2)+1, -23);

        c = random_color_name();
        switch_color(c);
        addstr_center(c, i-(LINES/2)+1, 17);
    }

    getch();
    time(&end);
    return difftime(end, start);
}

float anisochronic() {
    time_t start, end;
    time(&start);

    for(unsigned i = 0; i < LINES; i++) {
        char* c = random_color_name();
        switch_color(c);
        c = random_color_name();
        addstr_center(c, i-(LINES/2)+1, 0);

        c = random_color_name();
        switch_color(c);
        c = random_color_name();
        addstr_center(c, i-(LINES/2)+1, -23);

        c = random_color_name();
        switch_color(c);
        c = random_color_name();
        addstr_center(c, i-(LINES/2)+1, 17);
    }

    getch();
    time(&end);
    return difftime(end, start);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    initscr();

    if(has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support color!");
        return -1;
    } else {
        start_color();
        init_pair(RED, COLOR_RED, COLOR_BLACK);
        init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    }

    if(COLS < 50) {
        endwin();
        printf("Terminal is too small");
        return -1;
    }

    char* c = "Press any key after having read README.md...";
    addstr_center(c, 0, -1 * strlen(c)/2);
    getch();

    clear();

    attron(A_BOLD);
    float isotime = isochronic();
    clear();
    float anisotime = anisochronic();
    clear();

    endwin();

    printf("ISOCHRONIC: %.0f\nANISOCHRONIC: %.0f\nRATIO: %.2f\n", isotime, anisotime, (anisotime / isotime));

    return 0;
}
