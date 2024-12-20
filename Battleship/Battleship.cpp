#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Size of the game board
const int SIZE = 10;

// Function to initialize the field
void initializeField(int field[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = 0;
        }
    }
}

// Function to place ships on the field ensuring no overlap
void placeShips(int field[SIZE][SIZE], int shipCount) {
    while (shipCount > 0) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (field[x][y] == 0) {
            field[x][y] = 1;
            shipCount--;
        }
    }
}

// Function to display the field (ships hidden)
void displayField(const int field[SIZE][SIZE]) {
    cout << "  ";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == 1) {
                cout << ". "; // Hide ship location
            }
            else if (field[i][j] == -1) {
                cout << "X "; // Mark hit
            }
            else if (field[i][j] == -2) {
                cout << "O "; // Mark miss
            }
            else {
                cout << ". "; // Default
            }
        }
        cout << endl;
    }
}

// Function to execute a shot
bool makeShot(int field[SIZE][SIZE], int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        cout << "The enemy is in another zone, STOP LOSING SHELLS!" << endl;
        return false;
    }

    if (field[x][y] == 1) {
        cout << "Gotcha, You are the best comandor!" << endl;
        field[x][y] = -1; // Mark hit
        return true;
    }
    else if (field[x][y] == 0) {
        cout << "You missed comandor, try to be get serious" << endl;
        field[x][y] = -2; // Mark miss
    }
    else {
        cout << "You already shot here!" << endl;
    }

    return false;
}

// Function to check if the game is over
bool isGameOver(const int field[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    srand(time(0));

    int player1[SIZE][SIZE];
    int player2[SIZE][SIZE];

    initializeField(player1);
    initializeField(player2);

    placeShips(player1, 12); // Place 12 ships for player 1
    placeShips(player2, 12); // Place 12 ships for player 2

    bool player1Turn = true;

    while (true) {
        cout << "\nComandor 1's field (hidden):" << endl;
        displayField(player1);

        cout << "\nComandor 2's field (hidden):" << endl;
        displayField(player2);

        int x, y;
        if (player1Turn) {
            cout << "Comandor 1's turn." << endl;
        }
        else {
            cout << "Comandor 2's turn." << endl;
        }

        cout << "We found the enemy, Enter the coordinates comandor (x y): ";
        cin >> x >> y;

        if (player1Turn) {
            if (makeShot(player2, x, y) && isGameOver(player2)) {
                cout << "Comandor 1 wins! Damn, they got lucky as hell today. EVACUATE NOW! We'll have our revenge soon enough." << endl;
                break;
            }
        }
        else {
            if (makeShot(player1, x, y) && isGameOver(player1)) {
                cout << "Comandor 2 wins! Damn, they got lucky as hell today. EVACUATE NOW! We'll have our revenge soon enough." << endl;
                break;
            }
        }

        player1Turn = !player1Turn;
    }

    return 0;
}
