#include "Display.h"
#include "../Game.h"
#include "../utils/Log.h"
#include "../lib/ccolor.h"

#define ENEMY_COLORS_OFFSET 100
#define ENEMY_COLORS_SIZE 20
#define ENEMY_COLORS_BUCKET_SIZE 5

#define TOWER_COLORS_OFFSET 200
#define TOWER_COLORS_SIZE 50
#define TOWER_COLORS_BUCKET_SIZE 5

double frand(double min, double max){
    double delta = max - min;
    double rr = rand() / (double)RAND_MAX;
    return (rr * delta) + min;
}

void prepare_colors(){
    start_color();
    init_color(20, 500, 500, 500);
    init_pair(1, 20, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    float towerCoreHue = 0.5;
    float currentBucketHue = towerCoreHue;
    uint16_t currentBucketCount = 0;
    for (uint16_t i = TOWER_COLORS_OFFSET; i < TOWER_COLORS_OFFSET + TOWER_COLORS_SIZE; i++) {

        if (currentBucketCount == 0){
            currentBucketHue = towerCoreHue;
            currentBucketHue += frand(-0.1, 0.1);
            currentBucketHue *= 360;
        }

        double saturation = 0.8 + frand(0.0, 0.2);
        double value = 0.8 + frand(0.0, 0.2);
        hsv raw_color = {currentBucketHue, saturation, value};
        rgb color = hsv2rgb(raw_color);

        uint16_t r = color.r * 1000;
        uint16_t g = color.g * 1000;
        uint16_t b = color.b * 1000;

        init_color(i, r, g, b);
        Log::Debug("DISPLAY", "Tower color", i, "set as", r, g, b);
        init_pair(i, i, COLOR_BLACK);

        currentBucketCount = (currentBucketCount + 1) % TOWER_COLORS_BUCKET_SIZE;
    }

    float enemyHueColor = 0.0;
    currentBucketCount = 0;
    for (uint16_t i = ENEMY_COLORS_OFFSET; i < ENEMY_COLORS_OFFSET + ENEMY_COLORS_SIZE; i++) {

        if (currentBucketCount == 0){
            currentBucketHue = enemyHueColor;
            currentBucketHue += frand(-0.1, 0.1);
            if (currentBucketHue < 0)
                currentBucketHue = 1 - currentBucketHue;
            currentBucketHue *= 360;
        }

        double saturation = 0.8 + frand(0.0, 0.2);
        double value = 0.8 + frand(0.0, 0.2);
        hsv raw_color = {currentBucketHue, saturation, value};
        rgb color = hsv2rgb(raw_color);

        uint16_t r = color.r * 1000;
        uint16_t g = color.g * 1000;
        uint16_t b = color.b * 1000;

        init_color(i, r, g, b);
        Log::Debug("DISPLAY", "Enemy color", i, "set as", r, g, b);
        init_pair(i, i, COLOR_BLACK);

        currentBucketCount = (currentBucketCount + 1) % ENEMY_COLORS_BUCKET_SIZE;
    }

}

bool Display::Setup(TSVReader &reader) {
    initscr();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    prepare_colors();

    if (!has_colors()) {
        Log::Err("Display", "Terminal does not support colors!");
        return false;
    }

    return true;
}

void Display::Ready() {
    PrepareWindows();
}

Display::~Display() {
    endwin();
}

void Display::Render() {
    doupdate();
}

void Display::PrepareWindows() {
    std::vector<WINDOW *> windows;
    int lastY = 0;
    for (auto sys : m_Game->Fragments) {
        int width = 0, height = 0;
        sys->RequestDimensions(width, height);

        if (height == 0 || width == 0)
            continue;

        WINDOW *win = newwin(height, width, lastY, 0);
        windows.push_back(win);
        lastY += height;
        sys->SetWindow(win);
    }

    int terminalX;
    int terminalY;
    getmaxyx(stdscr, terminalY, terminalX);
    int allWindowsHeight = lastY;
    int offset = (terminalY - allWindowsHeight) / 2;
    lastY = offset;
    for (auto win : windows) {
        int windowX;
        int windowY;
        getmaxyx(win, windowY, windowX);
        mvwin(win, lastY, (terminalX - windowX) / 2);
        lastY += windowY;
    }
}

int Display::GetEnemyColor(int base, int variation) {
    int color = (base * ENEMY_COLORS_BUCKET_SIZE) % ENEMY_COLORS_SIZE;
    color += variation % ENEMY_COLORS_BUCKET_SIZE;
    color %= ENEMY_COLORS_SIZE;
    return COLOR_PAIR(ENEMY_COLORS_OFFSET + color);
}

int Display::GetTowerColor(int base, int variation) {
    int color = (base * TOWER_COLORS_BUCKET_SIZE) % TOWER_COLORS_SIZE;
    color += variation % TOWER_COLORS_BUCKET_SIZE;
    color %= TOWER_COLORS_SIZE;
    return COLOR_PAIR(TOWER_COLORS_OFFSET + color);
}

int Display::GetWallColor() {
    return COLOR_PAIR(1);
}

int Display::GetPathColor() {
    return COLOR_PAIR(2);
}