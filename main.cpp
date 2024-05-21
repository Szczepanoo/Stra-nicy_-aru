#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

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
    int damage;

    Firefighter() : health(100), water(100), experience(0), damage(10) {}

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

int fight(Firefighter &player, Dragon &dragon) {
    while (player.health >= 0 && dragon.health > 0) {
        player.health -= dragon.damage;
        dragon.health -= player.damage;
        dragon.attack();
        cout << "Zadajesz 10 obrazen smokowi!" << endl;
        if (player.health <= 0) {
            cout << "Zostales pokonany przez smoka. Gra skonczona." << endl;
            return -1;
        } else if (dragon.health <= 0) {
            cout << "Pokonales smoka! Wygrałes gre!" << endl;
            return 1;
        }
    }
}

void print_letter_by_letter(string string){
    for (int i = 0; i < string.length(); i ++){
        cout << string[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << endl;
}

int main() {
    srand(time(0));
    Firefighter player;


    bool showMenu = true;
    cout << "Straznicy Zaru: Ognisty Konflikt" << endl;
    while (showMenu) {
        cout << "1. Nowa gra\n2. Wczytaj zapis\n0. Wyjscie z gry\n";
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
            case 0:
                cout << "Do zobaczenia!" << endl;
                return 0;
            default:
                cout << "Nieprawidlowy wybor." << endl;
                break;
        }

    }


    bool gameOver = false;
    while (!gameOver) {
        Dragon dragon("Wladca Zaru", 100, 20);
        displayStatus(player, dragon);
        if (player.experience == 0){
            system("cls");
            print_letter_by_letter("Witaj w miescie Pyroklas!");
            this_thread::sleep_for(chrono::milliseconds(500));
            print_letter_by_letter("Codzienne zycie splata sie tu z cieniem niebezpieczenstwa unoszacego sie w powietrzu. W miasteczku, gdzie smoki nie sa legenda, ale rzeczywistoscia. Ostatnio jednak atmosfera napiecia narasta, a grozba plonacych pozarow staje sie coraz bardziej palaca.");
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Dowodca Strazakow Samuel: Witaj swiezaku, jestem Sam i dowodze tymi szajbusami." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            cout << "To jest Franek, zajmie sie twoim wdrozeniem";

        }
        cout << "\nWybierz akcje:\n1. Walka ze smokiem\n2. Gaszenie pozaru\n3. Ratowanie cywila\n0. Wyjscie z gry\n";
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
                if (fight(player,dragon) < 0){
                    gameOver = true;
                }
                break;
            case 2:
                player.useExtinguisher();
                break;
            case 3:
                player.rescueCivilian();
                break;
            case 0:
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
