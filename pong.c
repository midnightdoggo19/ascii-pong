#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define BAT_LENGTH 5
#define BAT_CHAR '#'
#define BALL_CHAR 'O'
#define SLEEP_TIME 25000

typedef struct {
    float x, y;
    float dx, dy;
} ball_object;

// Global State Variables
int g_width, g_height;
ball_object ball;
int p1_y, p2_y; // BAT's Y position
int score1, score2;
bool game_over;

typedef struct keymap {
	char p1up;
	char p1down;
	char p2up;
	char p2down;
};
struct keymap defaultbindings = {'w', 'a', 'i', 'k'};
struct keymap *bindings = &defaultbindings;

void setup();
void reset_positions();
void draw();
void input();
void logic();

int main(int argc, char* argv[]) {
    setup();

    // set keybingings
    if (argc > 1) {
        bindings->p1up = argv[1][0];
        bindings->p1down = argv[1][1];

        bindings->p2up = argv[2][0];
        bindings->p2down = argv[2][1];
    }

    while (!game_over) {
        input();
        logic();
        draw();
        usleep(SLEEP_TIME); // decides the pace of the game
    }

    endwin();

    // Print final score
    printf("Hope you enjoyed!\n");
    printf("Final Score -> Player 1: %d | Player 2: %d\n", score1, score2);
    if (score1 > score2) printf("Player 1 wins!\n");
    else printf("Player 2 wins!\n");

    return 0;
}

void setup() {
    // Initialize ncurses
    initscr();            // Start ncurses mode
    curs_set(0);          // Hide the cursor
    nodelay(stdscr, TRUE);// Make getch() non-blocking
    srand(time(NULL));    // Seed the random number generator

    getmaxyx(stdscr, g_height, g_width); // Gets terminal window dimensions
    score1 = 0;
    score2 = 0;
    game_over = false;
    reset_positions();
}

void reset_positions() {
    p1_y = p2_y = g_height / 2 - BAT_LENGTH / 2;
    ball.x = g_width / 2.0f;
    ball.y = g_height / 2.0f;

    // Set a random initial direction for the ball
    ball.dx = (rand() % 2 == 0) ? 1.0f : -1.0f;
    ball.dy = 0.8f;
}

void draw() {
    clear();

    box(stdscr, 0, 0); // ncurses function to draw boxes. TODO: don't understand how it works, gotta check out what ts is

    char score_text[50];
    sprintf(score_text, "Player 1: %d | Player 2: %d", score1, score2);
    mvprintw(1, g_width / 2 - strlen(score_text) / 2, "%s", score_text);

    for (int i = 0; i < BAT_LENGTH; ++i) {
        mvaddch(p1_y + i, 2, BAT_CHAR);
        mvaddch(p2_y + i, g_width - 3, BAT_CHAR);
    }

    mvaddch((int)ball.y, (int)ball.x, BALL_CHAR);

    refresh(); // Refreshes the screen to show changes
}

// handle input
void input() {
    int key = getch();

    if ((key == ((int) bindings->p1up)) && (p1_y > 2)) p1_y--;
    if ((key == ((int) bindings->p1down) && (p1_y < g_height - BAT_LENGTH - 2))) p1_y++;
    if ((key == ((int) bindings->p2up) && (p2_y > 2))) p2_y--;
    if ((key == ((int) bindings->p2down) && (p2_y < g_height - BAT_LENGTH - 2))) p2_y++;
    if (key == 'q') game_over = true;
}

void logic() {
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Ball collision
    if (ball.y <= 1 || ball.y >= g_height - 2) {
        ball.dy *= -1;
    }

    // Ball's collision with bats
    if (ball.x <= 3 && ball.y >= p1_y && ball.y < p1_y + BAT_LENGTH) {
        ball.dx *= -1;
    }
    if (ball.x >= g_width - 4 && ball.y >= p2_y && ball.y < p2_y + BAT_LENGTH) {
        ball.dx *= -1;
    }

    // Score when ball goes beyond terminal window in the x direction
    if (ball.x < 1) {
        score2++;
        reset_positions();
    }
    if (ball.x > g_width - 2) {
        score1++;
        reset_positions();
    }
}
