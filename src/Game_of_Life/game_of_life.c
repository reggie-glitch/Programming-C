#include <ncurses.h>
#include <stdio.h>

#define STR 25
#define COL 80

void input_matrix(int matrix[STR][COL]);
void update_matrix(int matrix1[STR][COL], int matrix2[STR][COL]);
int count_neighbors(int matrix1[STR][COL], int i, int j);
int decision(int neighbors, int condition);
void replace(int matrix2[STR][COL], int matrix1[STR][COL]);
int check(const int matrix1[STR][COL], const int matrix2[STR][COL]);
int change_speed(char control_button, int *flag, int time_mili_sec);
int count(int matrix[STR][COL]);

int main() {
    int matrix1[STR][COL] = {0};
    int matrix2[STR][COL] = {0};
    int time_mili_sec = 500;
    int stop = 0;

    input_matrix(matrix1);
    if (freopen("/dev/tty", "r", stdin)) initscr();
    nodelay(stdscr, true);

    while (stop != 1) {
        timeout(time_mili_sec);
        char control_button = getch();

        if (count(matrix1) == 0) {
            stop = 1;
        }

        time_mili_sec = change_speed(control_button, &stop, time_mili_sec);

        erase();
        update_matrix(matrix1, matrix2);
        refresh();

        if (check(matrix1, matrix2) == STR * COL) {
            stop = 1;
        }
        replace(matrix2, matrix1);
    }

    endwin();
    return 0;
}

void input_matrix(int matrix[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void update_matrix(int matrix1[STR][COL], int matrix2[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            matrix2[i][j] = decision(count_neighbors(matrix1, i, j), matrix1[i][j]);
            if (matrix2[i][j] == 1)
                printw("0");
            else
                printw("-");
        }
        printw("\n");
    }
}

int count_neighbors(int matrix1[STR][COL], int i, int j) {
    int sum = 0;

    int i_up = i - 1, j_left = j - 1, i_down = i + 1, j_right = j + 1;

    if (i_up < 0) i_up = STR - 1;
    if (j_left < 0) j_left = COL - 1;
    if (i_down > STR - 1) i_down = i_down % STR;
    if (j_right > COL - 1) j_right = j_right % COL;

    sum += matrix1[i_up][j_left];
    sum += matrix1[i_up][j];
    sum += matrix1[i_up][j_right];
    sum += matrix1[i][j_right];
    sum += matrix1[i_down][j_right];
    sum += matrix1[i_down][j];
    sum += matrix1[i_down][j_left];
    sum += matrix1[i][j_left];

    return sum;
}

int decision(int neighbors, int condition) {
    int next_gen = -1;
    if ((neighbors == 2 || neighbors == 3) && condition == 1) {
        next_gen = 1;
    } else if (neighbors == 3 && condition == 0) {
        next_gen = 1;
    } else {
        next_gen = 0;
    }
    return next_gen;
}

void replace(int matrix2[STR][COL], int matrix1[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            matrix1[i][j] = matrix2[i][j];
        }
    }
}

int check(const int matrix1[STR][COL], const int matrix2[STR][COL]) {
    int ans = 0;
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            if (matrix1[i][j] == matrix2[i][j]) ans++;
        }
    }
    return ans;
}

int change_speed(char control_button, int *flag, int time_mili_sec) {
    if (control_button == 'a' || control_button == 'A') {
        time_mili_sec -= 100;
        if (time_mili_sec < 10) time_mili_sec = 10;
    } else if (control_button == 'z' || control_button == 'Z') {
        time_mili_sec += 100;
        if (time_mili_sec > 2000) time_mili_sec = 2000;
    } else if (control_button == ' ') {
        *flag = 1;
    }

    return time_mili_sec;
}

int count(int matrix[STR][COL]) {
    int sum = 0;
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}