#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Klasa reprezentująca smoka
class Dragon {
public:
    string name;
    int health;
    int damage;

    Dragon(string n, int h, int d) : name(n), health(h), damage(d) {}

    void attack() {
        cout << name << " atakuje zadajac " << damage << " obrazen!" << endl;
    }
};

// Klasa reprezentująca gracza-strażaka
class Firefighter {
public:
    int health;
    int water;
    int experience;

    Firefighter() : health(100), water(100), experience(0) {}

    void useExtinguisher() {
        if (water > 0) {
            cout << "Uzywasz wody do gaszenia pozaru!" << endl;
            water -= 10;
        } else {
            cout << "Brak wody!" << endl;
        }
    }

    void rescueCivilian() {
        cout << "Ratujesz cywila!" << endl;
        experience += 10;
    }
};

void displayStatus(Firefighter &ff, Dragon &dragon) {
    cout << "Status Gracza: Zdrowie = " << ff.health << ", Woda = " << ff.water << ", Doswiadczenie = " << ff.experience << endl;
    cout << "Status Smoka: Zdrowie = " << dragon.health << endl;
}

void fight(){
    cout << "pass";
}

int main() {
    srand(std::time(0));
    Firefighter player;


    bool showMenu = true;
    cout << "Straznicy Zaru: Ognisty Konflikt" << endl;
    while (showMenu) {
        cout << "1. Nowa gra\n2. Wczytaj zapis\n3. Wyjscie z gry\n";
        string choiceStr;
        cin >> choiceStr;
        int choice;
        try {
            choice = stoi(choiceStr);
        } catch (invalid_argument){
            choice = -999;
        }

        switch (choice) {
            case 1:
                player = Firefighter();
                showMenu = false;
                break;
            case 2:
                cout << "Coming soon..." << endl;
                break;
            case 3:
                cout << "Do zobaczenia!" << endl;
                return 0;
                break;
            default:
                cout << "Nieprawidlowy wybor." << endl;
                break;
        }

    }


    bool gameOver = false;
    while (!gameOver) {
        Dragon dragon("Wladca Zaru", 100, 20);
        displayStatus(player, dragon);

        cout << "\nWybierz akcje:\n1. Walka ze smokiem\n2. Gaszenie pozaru\n3. Ratowanie cywila\n4. Wyjscie z gry\n";
        string choiceStr;
        cin >> choiceStr;
        int choice;
        try {
            choice = stoi(choiceStr);
        } catch (invalid_argument){
            choice = -999;
        }

        switch (choice) {
            case 1:
                player.health -= dragon.damage;
                dragon.health -= 10;
                dragon.attack();
                cout << "Zadajesz 10 obrazen smokowi!" << endl;
                if (player.health <= 0) {
                    cout << "Zostałes pokonany przez smoka. Gra skonczona." << endl;
                    gameOver = true;
                } else if (dragon.health <= 0) {
                    cout << "Pokonales smoka! Wygrałes gre!" << endl;
                    gameOver = true;
                }
                break;
            case 2:
                player.useExtinguisher();
                break;
            case 3:
                player.rescueCivilian();
                break;
            case 4:
                gameOver = true;
                break;
            default:
                cout << "Nieprawidlowy wybor. " << endl;
                break;
        }
    }

    cout << "Dziekujemy za gre!" << endl;
    return 0;
}
