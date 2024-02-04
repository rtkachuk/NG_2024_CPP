#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//       0 1 2 3 4 5 6 7 8 9
//       a
//       4



// 00 01 02 03 04 05
// 10 11 12 13 14 15
// 20 21 22 23 24 25
//
//
//
//

struct position {
    int x;
    int y;
};

const int ROW_SIZE = 10;
const int COL_SIZE = 20;

void drawLine(int size) {
    for (int elemNumber = 0; elemNumber < size; elemNumber++)
        cout << "=";
    cout << endl;
}

void drawMap(char map[ROW_SIZE][COL_SIZE], position player) {
    for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = 0; col < COL_SIZE; col++) {
            if (row == player.y && col == player.x)
                cout << "@";
            else
                cout << map[row][col];
        }
        cout << endl;
    }
}

void mapInit(char map[ROW_SIZE][COL_SIZE], char playerMap[ROW_SIZE][COL_SIZE]) {
    for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = 0; col < COL_SIZE; col++) {
            if (row == 0 || col == 0 || row == ROW_SIZE - 1 || col == COL_SIZE - 1)
                map[row][col] = '*';
            else {
                int chance = rand() % 10;
                switch(chance) {
                case 1: map[row][col] = 's'; break;
                case 2: map[row][col] = 't'; break;
                default: map[row][col] = ' ';
                }
            }
            playerMap[row][col] = '*';
        }
    }
}

bool checkPosition(char map[ROW_SIZE][COL_SIZE], position pos) {
    char item = map[pos.y][pos.x];
    return item == ' ';
}

bool updatePlayerPosition(char map[ROW_SIZE][COL_SIZE], char direction, position *player) {
    position tempPosition;
    tempPosition = *player;
    switch (direction) {
    case 'w': tempPosition.y--; break;
    case 's': tempPosition.y++; break;
    case 'a': tempPosition.x--; break;
    case 'd': tempPosition.x++; break;
    }
    if (checkPosition(map, tempPosition)) {
        *player = tempPosition;
        return true;
    }
    return false;
}

void updatePlayerMap(char map[ROW_SIZE][COL_SIZE], char playerMap[ROW_SIZE][COL_SIZE], position player) {
    for (int row = player.y-1; row <= player.y+1; row++) {
        for (int col = player.x - 1; col <= player.x + 1; col++) {
            playerMap[row][col] = map[row][col];
        }
    }
}

int main()
{
    srand(time(NULL));

    char map[ROW_SIZE][COL_SIZE];
    char playerMap[ROW_SIZE][COL_SIZE];

    position player;
    player.x = COL_SIZE / 2;
    player.y = ROW_SIZE / 2;
    char direction = ' ';

    mapInit(map, playerMap);

    while (true) {
        drawMap(playerMap, player);
        drawLine(COL_SIZE);

        cout << "Enter direction: ";
        cin >> direction;
        if (updatePlayerPosition(map, direction, &player))
            updatePlayerMap(map, playerMap, player);
        system("clear");
    }

    return 0;
}
