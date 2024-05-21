#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

void sleep(int time_ms){
    this_thread::sleep_for(chrono::milliseconds(time_ms));
}

int getChoice(){
    string choiceStr;
    int choice;
    cin >> choiceStr;
    try {
        choice = stoi(choiceStr);
    } catch (invalid_argument){
        choice = -999;
    }
    return choice;
}

// Klasa reprezentująca smoka
class Dragon {
public:
    string name;
    int health;
    int damage;

    Dragon(string n, int h, int d) : name(n), health(h), damage(d) {}

    void attack(int real_damage) {
        cout << name << " atakuje zadajac " << real_damage << " obrazen!" << endl;
    }
    void print_info() {
        cout << "[" << name << "]" << endl;
        if (name == "NIKCZEMNIUCH") {
            cout << "Sila: brak danych" << endl;
        } else {
            cout << "Sila: " << damage << endl;
        }
        cout << "Zdrowie: " << health << endl << endl;
    }
};

// Klasa reprezentująca gracza-strażaka
class Firefighter {
public:
    int health;
    int water;
    int experience;
    int extinguisher_lvl;
    int waterBomb_lvl;
    int waterBomb_amt;

    Firefighter() : health(120), water(100), experience(0), extinguisher_lvl(0), waterBomb_lvl(0), waterBomb_amt(0) {}

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
    int max_player_health = player.health;
    int max_dragon_health = dragon.health;
    dragon.print_info();
    while (player.health >= 0 && dragon.health > 0) {
        int base_player_damage;
        bool choice_accepted = false;
        while (!choice_accepted) {
            cout << "Wybierz atak:" << endl;
            if (player.extinguisher_lvl > 0) {
                cout << "1. Gasnica" << endl;
            }

            if (player.waterBomb_lvl > 0 && player.waterBomb_amt > 0) {
                cout << "2. Bomba wodna" << endl;
            }

            int choice = getChoice();
            switch (choice) {
                case 1:
                    base_player_damage = player.extinguisher_lvl * 10;
                    choice_accepted = true;
                    break;
                case 2:
                    if (player.waterBomb_lvl > 0 && player.waterBomb_amt > 0){
                        base_player_damage = -10;
                        choice_accepted = true;
                    } else {
                        cout << "Nieprawidlowy wybor." << endl;
                    }
                    break;
                case 3:
                    base_player_damage = -10;
                    choice_accepted = true;
                    break;
                default:
                    cout << "Nieprawidlowy wybor." << endl;
                    break;
            }
        }

        //Generator liczb losowych z losowym ziarniem
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(static_cast<int>(base_player_damage * 0.75), static_cast<int>(base_player_damage * 1.25));
        int real_player_damage = dis(gen);

        uniform_int_distribution<> dis2(static_cast<int>(dragon.damage * 0.75), static_cast<int>(dragon.damage * 1.25));
        int real_dragon_damage = dis2(gen);

        player.health -= real_dragon_damage;
        dragon.health -= real_player_damage;
        dragon.attack(real_dragon_damage);
        cout << "Zadajesz "<< real_player_damage <<" obrazen smokowi!" << endl << endl;
        cout << "Poziom twojego zdrowia: " << player.health << "/" << max_player_health << endl;
        cout << "Poziom zdrowia przeciwnika: " << dragon.health << "/" << max_dragon_health << endl;
        if (player.health <= 0) {
            cout << "Porazka" << endl;
            player.experience += 1;
            cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
            cin.get();
            return -1;
        } else if (dragon.health <= 0) {
            cout << "Zwyciestwo! Zdobywasz: "<< max_dragon_health << "xp." << endl;
            player.experience+= max_dragon_health;
            cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
            cin.get();
            return 1;
        }
    }
}

void print_letter_by_letter(string string){
    for (int i = 0; i < string.length(); i ++){
        cout << string[i] << flush;
        sleep(50);
    }
    cout << endl;
}


int main() {
    Firefighter player;

    bool showMenu = true;
    cout << "Straznicy Zaru: Ognisty Konflikt" << endl;
    while (showMenu) {
        cout << "1. Nowa gra\n2. Wczytaj zapis\n0. Wyjscie z gry\n";
        int choice = getChoice();

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
        Dragon Wladca_Zaru("Wladca Zaru", 10000, 250);
        Dragon Nikczemniuch("NIKCZEMNIUCH",60,15);
        if (player.experience == 0){
            system("cls");
            print_letter_by_letter("Witaj w miescie Pyroklas!");
            sleep(500);
            print_letter_by_letter("Codzienne zycie splata sie tu z cieniem niebezpieczenstwa unoszacego sie w powietrzu. "
                                   "W miasteczku, gdzie smoki nie sa legenda, ale rzeczywistoscia. "
                                   "Ostatnio jednak atmosfera napiecia narasta, a grozba zlowrogich pozarow staje sie coraz bardziej realna. "
                                   "Jako mlody adept pozarnictwa wstepujesz w szeregi lokalnej jednostki strazy pozarnej, aby wesprzec ich w dzialaniach.");
            sleep(2000);
            cout << "[---GLOWNA SIEDZIBA STRAZNIKOW ZARU---]" << endl;
            cout << "Dowodca Strazakow Samuel: ";
            print_letter_by_letter("Witaj swiezaku, jestem Sam i dowodze tymi oszolomami.");
            sleep(3000);
            print_letter_by_letter("To jest Franek, poznajcie sie, wdrozy Cie w nasze szeregi i oprowadzi po jednostce.");
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Czesc mlody, na poczatek, trzymaj podstawowy przedmiot kazdego strazaka");
            sleep(500);
            player.extinguisher_lvl++;
            cout << "[+] DODANO PRZEDMIOT: ZWYKLA GASNICA" << endl;
            sleep(500);
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("W tych czasach kazdy z nas nosi pod reka swoja gasnice. "
                                   "To narzedzie ktore najlepiej sprawdza sie w ratowaniu cywili, ale od biedy moze tez "
                                   "sluzyc w walce ze smokami.");
            sleep(1000);
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Pozwol, ze oprowadze Cie teraz po naszej centrali...");
            cout << "[TRACHHH!]" << endl;
            sleep(2000);
            cout << "Dowodca Strazakow Samuel: ";
            print_letter_by_letter("SLYSZELISCIE TO!? TO NIKCZEMNIUCH! Myslalem ze ostatnim razem udalo nam sie go pokonac, "
                                   "ale wyglada na to za powrocil! Franek, bierz nowego i zajmijcie sie nim. Ja zbiore chlopakow i "
                                   "zaraz do was dolaczymy!");
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Za mna mlody, wydaje mi sie, ze wyladowal na dachu. Pamietaj o gasnicy! ");
            sleep(3000);
            cout << "[---GLOWNA SIEDZIBA STRAZNIKOW ZARU - DACH---]" << endl;
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Acha! Jest tutaj! Do dziela mlody!");
            fight(player,Nikczemniuch);


        }
        cout << "\nWybierz akcje:\n1. Walka ze smokiem\n2. Gaszenie pozaru\n3. Ratowanie cywila\n0. Wyjscie z gry\n";

        int choice = getChoice();

        switch (choice) {
            case 1:
                if (fight(player,Wladca_Zaru) < 0){
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
