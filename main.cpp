#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <array>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;


// Klasa reprezentująca smoka
class Dragon {
public:
    string name;
    int health;
    int damage;

    Dragon(string n, int h, int d) : name(std::move(n)), health(h), damage(d) {}

    // Wyswietlnie (przed walką) informacji o smoku
    void print_info() const {
        cout << endl << "[" << name << "]" << endl;
        if (name == "NIKCZEMNIUCH" || name == "WLADCA ZARU") {
            cout << "Sila: brak danych" << endl;
        } else {
            cout << "Sila: " << damage << endl;
        }
        if (name == "WLADCA ZARU"){
            cout << "Zdrowie: brak danych" << endl;
        } else {
            cout << "Zdrowie: " << health << endl << endl;
        }
    }
};


// Klasa reprezentująca gracza-strażaka
class Firefighter {
public:
    string name;
    int health;
    int max_health;
    int experience;
    int extinguisher_lvl;
    int waterBomb_lvl;
    int waterBomb_amt;
    int medkits;
    int respect_points;
    int burzogniew_hp;
    int pyros_hp;
    int zguba_miast_hp;
    int wladca_zaru_hp;

    // Constructor with default parameters
    Firefighter() : health(120), max_health(120), experience(0), extinguisher_lvl(0), waterBomb_lvl(0),
    waterBomb_amt(0), medkits(0), respect_points(0), burzogniew_hp(100), pyros_hp(500), zguba_miast_hp(700), wladca_zaru_hp(1000){}

    // Constructor
    Firefighter(string name, int health, int max_health, int experience,int extinguisher_lvl, int waterBomb_lvl,
                int waterBomb_amt, int medkits, int respect_points, int burzogniew_hp, int pyros_hp, int zguba_miast_hp, int wladca_zaru_hp):
            name(std::move(name)),
            health(health),
            max_health(max_health),
            experience(experience),
            extinguisher_lvl(extinguisher_lvl),
            waterBomb_lvl(waterBomb_lvl),
            waterBomb_amt(waterBomb_amt),
            medkits(medkits),
            respect_points(respect_points),
            burzogniew_hp(burzogniew_hp),
            pyros_hp(pyros_hp),
            zguba_miast_hp(zguba_miast_hp),
            wladca_zaru_hp(wladca_zaru_hp) {}

            // Funkcja zapisująca gre
    void saveGame(Dragon &burzogniew, Dragon &pyros, Dragon &zguba_miast, Dragon &wladca_zaru) {
        const string filename = "game_saves.csv";

        // Otwarcie pliku w trybie dopisywania, utworzy plik, jesli nie istnieje
        ofstream file(filename, ios::app);

        burzogniew_hp = burzogniew.health;
        pyros_hp = pyros.health;
        zguba_miast_hp = zguba_miast.health;
        wladca_zaru_hp = wladca_zaru.health;

        if (file.is_open()) {
            file << name << ","
                 << health << ","
                 << max_health << ","
                 << experience << ","
                 << extinguisher_lvl << ","
                 << waterBomb_lvl << ","
                 << waterBomb_amt << ","
                 << medkits << ","
                 << respect_points << ","
                 << burzogniew_hp << ","
                 << pyros_hp << ","
                 << zguba_miast_hp << ","
                 << wladca_zaru_hp << "\n";
            file.close();
            cout << "[ZAPISANO GRE]" << endl;
        } else {

            // Blad przy otwarciu pliku
            cout << "[WYSTAPIL BLAD PODCZAS ZAPISU]" << filename << endl;
        }
    }

    // Funkcja pokazująca ekwipunek i podstawowe statystyki
    void showEquiment() const{
        cout << endl << "[" << name << "]" << endl;
        cout << "Doswiadczenie: " << experience << endl;
        cout << "Punkty Respektu: " << respect_points << endl;
        cout << "Stan zdrowia: "<< health << "/" << max_health << endl;
        switch (extinguisher_lvl) {
            case 1:
                cout << "Gasnica: ZWYKLA GASNICA" << endl;
                break;
            case 2:
                cout << "Gasnica: ULEPSZONA GASNICA" << endl;
                break;
            case 3:
                cout << "Gasnica: GASNICA DOWODCY SAMUELA" << endl;
                break;
            case 4:
                cout << "Gasnica: LEGENDARNA GASNICA RYCERZA OGNIA" << endl;
                break;
            case 5:
                cout << "Gasnica: GASNICA ZE SMOCZEJ LUSKI" << endl;
                break;
            default:
                cout << "Gasnica: BRAK" << endl;
                break;
        }
        if (waterBomb_lvl > 0) {
            cout << "Bomby wodne (poz): " << waterBomb_lvl << endl;
            cout << "Bomby wodne (szt): " << waterBomb_amt << endl;
        }
        cout << "Apteczki (szt): " << medkits << endl;
    }


};


// Funkcja pobierajaca liczbe od uzytkownika
int getChoice(){
    string choiceStr;
    int choice;
    cin >> choiceStr;
    try {
        choice = stoi(choiceStr);
    } catch (invalid_argument &){
        //Zwaracamy -999 w przypadku błędu konwersji
        choice = -999;
    }
    return choice;
}


// Funkcja wczytująca grę
Firefighter loadGame() {
    string filename = "game_saves.csv";
    ifstream file(filename);
    vector<Firefighter> firefighters;
    string line;

    if (file.is_open()) {
        // Przesunięcie wskaźnika pliku na początek
        file.seekg(0, ios::beg);

        // Jezeli plik jest pusty
        if (file.peek() == std::ifstream::traits_type::eof()){
            cout << "[NIE ZNALEZIONO ZAPISANYCH STANOW GRY]" << endl;
            cout << "[STWORZONO NOWA POSTAC]" << endl;
            file.close();
            return {};
        }

        // Wczytywanie postaci
        while (getline(file, line)) {
            stringstream ss(line);
            string name;
            int health, max_health, experience, extinguisher_lvl, waterBomb_lvl, waterBomb_amt, medkits,
                respect_points, burzogniew_hp, pyros_hp, zguba_miast_hp, wladca_zaru_hp;
            char comma;

            getline(ss, name, ',');
            ss >> health >> comma >> max_health >> comma >> experience >> comma >> extinguisher_lvl >> comma
               >> waterBomb_lvl >> comma >> waterBomb_amt >> comma >> medkits >> comma >> respect_points >> comma
               >> burzogniew_hp >> comma >> pyros_hp >> comma >> zguba_miast_hp >> comma >> wladca_zaru_hp;

            firefighters.emplace_back(name, health, max_health, experience, extinguisher_lvl, waterBomb_lvl,
                                      waterBomb_amt, medkits, respect_points, burzogniew_hp, pyros_hp, zguba_miast_hp, wladca_zaru_hp);
        }
        file.close();

        // Wyświetlanie listy postaci
        for (size_t i = 0; i < firefighters.size(); ++i) {
            cout << i + 1 << ". " << firefighters[i].name << " (Zdrowie: " << firefighters[i].health << ", Doswiadczenie: " << firefighters[i].experience << ")\n";
        }

        while (true) {
            // Wybór postaci przez użytkownika
            int choice;
            cout << "Wybierz zapis (1-" << firefighters.size() << "): ";
            choice = getChoice();

            // Zwracanie wybranej postaci
            if (choice > 0 && choice <= firefighters.size()) {
                cout << "[WCZYTANO ZAPIS]" << endl;
                return firefighters[choice - 1];
            } else {
                cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
            }
        }
    } else {
        cout << "[NIE ZNALEZIONO ZAPISANYCH STANOW GRY]" << endl;
        cout << "[STWORZONO NOWA POSTAC]" << endl;
        return {}; // Zwracanie domyślnej (nowej) postaci w razie błędu
    }
}


// Funkcja zatrzymujaca grę na określony czas
void sleep(int time_ms){
    this_thread::sleep_for(chrono::milliseconds(time_ms));
}


// Funkcja wyswietlajaca wypowiadane kwestie
void print_letter_by_letter(string string){
    for (int i = 0; i < string.length(); i ++){
        cout << string[i] << flush;
        sleep(20);
    }
    cout << endl;
}


// Funkcja zamieniająca wszystkie litery w slowie na duze
string toUpperCase(const string& input) {
    string result = input;

    for (char& c : result) {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }

    return result;

}


// Funkcja szyfrująca szyfrem Cezara
string encryptCaesar(const string& text, int shift) {
    string result;

    for (char c : text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            result += (c - offset + shift) % 26 + offset;
        } else {
            result += c;
        }
    }

    return result;
}


// Funkcja deszyfrująca szyfr Cezara
string decryptCaesar(const string& text, int shift) {
    return encryptCaesar(text, 26 - (shift % 26));
}


// Funkcja walki z bossami
int fight(Firefighter &player, Dragon &dragon) {
    int max_dragon_health = dragon.health;

    // Intro do bitwy z drugim bossem - pierwszy jest w prologu
    if (dragon.name == "BURZOGNIEW"){
        cout << "Dowodca Strazakow Samuel: ";
        print_letter_by_letter("UWAGA WSZYSCY PELNA MOBILIZACJA! Namierzylismy BURZOGNIEWA! Terroryzuje ludzi w parku! "
                               "Ruszajmy tam zanim sie zmyje!");
        sleep(2000);
        cout << "[PYROKLAS - PARK MIEJSKI]" << endl;
        cout << "Dowodca Strazakow Samuel: ";
        print_letter_by_letter("Oho! Jest tutaj! Do ataku!");
    }

    // Intro do bitwy z trzecim bossem
    if (dragon.name == "PYROS"){
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Brygada Rycerzy Ognia zmaga sie wlasnie z atakiem jednego ze smokow i potrzebuja naszej pomocy! "
                               "Ze wstepnych ustalen wynika, ze jest to PYROS! Nie tracmy czasu! Ruszajmy!");
        sleep(2000);
        cout << "[SIEDZIBA BRYGADY RYCERZY OGNIA]" << endl;
        cout << "Rycerz Ognia Artur: ";
        print_letter_by_letter("Dobrze, ze jestescie, bo juz nie dajemy sobie z nim rady. Jest znacznie potezniejszy "
                               "niz przypuszczalismy!");
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("UDERZMY W NIEGO RAZEM! DO ATAKU MLODY! ZA SAMUELAAA!");
    }

    // Intro do walki z czwartym bossem
    if (dragon.name == "ZGUBA MIAST"){
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("UWAGA! NAMIERZYLISMY ZGUBE MIAST! Sluchaj mlody - to NAJPOTEZNIEJSZY znany nam smok! "
                               "Bomby wodne od Ryczerzy Ognia swietnie sie sprawdza przeciwko niemu! "
                               "Wyladowal na rynku i atakuje mieszkancow! Ruchy mlody! DO SAMOCHODU! ");
        sleep(2000);
        cout << "[RYNEK W PYROKLESIE]" << endl;
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Mamy go! Teraz mlody! DAJMY MU POPALIC!");
    }

    // Intro do walki z piątym bossem
    if (dragon.name == "WLADCA ZARU"){
        cout << "[TRACHH!!!]" << endl;
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Co sie dzieje?! BUDYNEK ZACZYNA PEKAC W POL!!!");
        cout << "[BUUCH!!]" << endl;
        cout << "Strazak Marcel: ";
        print_letter_by_letter("UCIEKAJMY Z BUDYNKU! ZARAZ SIE ZAWALI!!");
        cout << "Wladca Zaru: ";
        print_letter_by_letter("[KRAA!!] KTO SMIE ZAKLOCAC ODWIECZY SPOKOJ SMOCZEJ CYWYLIZACJI!!");
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("O cholera!! TO WLADCA ZARU!! MUSIMY GO POKONAC!! DO ATAKU!!");
        cout << "Wladca Zaru: ";
        print_letter_by_letter("NIC Z TEGO NEDZNI STRAZACY! [KRRRAA!] POZALUJECIE SWYCH DECYZJI!!");
    }

    // Wyświetlenie informacji o aktualnym bossie
    dragon.print_info();

    // Główna pętla walki
    while (player.health >= 0 && dragon.health > 0) {
        int base_player_damage;
        bool choice_accepted = false;
        bool usemedkit = false;
        while (!choice_accepted) {
            cout << "Wybierz akcje:" << endl;
            if (player.extinguisher_lvl > 0) {
                cout << "1. Atak gasnica" << endl;
            }
            if (player.waterBomb_lvl > 0 && player.waterBomb_amt > 0) {
                cout << "2. Bomba wodna" << endl;
            }
            if (player.medkits > 0){
                cout << "9. Apteczka" << endl;
            }

            int choice = getChoice();
            switch (choice) {
                case 1:
                    switch (player.extinguisher_lvl) {
                        case 1:
                            base_player_damage = 10;
                            break;
                        case 2:
                            base_player_damage = 25;
                            break;
                        case 3:
                            base_player_damage = 40;
                            break;
                        case 4:
                            base_player_damage = 60;
                            break;
                        case 5:
                            base_player_damage = 90;
                            break;
                    }

                    choice_accepted = true;
                    break;
                case 2:
                    if (player.waterBomb_lvl > 0 && player.waterBomb_amt > 0){
                        switch (player.waterBomb_lvl) {
                            case 1:
                                base_player_damage = dragon.health / 2;
                                break;
                            case 2:
                                base_player_damage = (dragon.health * 6) / 10;
                                break;
                            case 3:
                                base_player_damage = (dragon.health * 7) / 10;
                                break;
                        }
                        player.waterBomb_amt--;
                        choice_accepted = true;
                    } else {
                        cout << "Nieprawidlowy wybor." << endl;
                    }
                    break;
                case 9:
                    if (player.medkits > 0){
                        base_player_damage = 0;
                        usemedkit = true;
                        choice_accepted = true;
                    } else {
                        cout << "Nieprawidlowy wybor." << endl;
                    }
                    break;
                default:
                    cout << "Nieprawidlowy wybor." << endl;
                    break;
            }
        }

        //Generator liczb losowych z losowym ziarniem
        random_device rd;
        mt19937 gen(rd());

        // Zadanych obrażeń +/- 25% obrażeń bazowych
        uniform_int_distribution<> dis(static_cast<int>(base_player_damage * 0.75), static_cast<int>(base_player_damage * 1.25));
        int real_player_damage = dis(gen);

        uniform_int_distribution<> dis2(static_cast<int>(dragon.damage * 0.75), static_cast<int>(dragon.damage * 1.25));
        int real_dragon_damage = dis2(gen);

        // Uzycie apteczki lub atak na smoka
        if (usemedkit){
            player.health = player.max_health;
            cout << "[-] UZYTO APTECZKI" << endl;
            player.medkits--;
            cout << "Pozostalo " << player.medkits << "szt." << endl;
        } else {
            dragon.health -= real_player_damage;
            cout << "Zadajesz " << real_player_damage << " obrazen smokowi!" << endl;
        }


        // Sprawdzenie czy gracz przegrywa w walce z pierwszym smokiem
        if (player.health - real_dragon_damage <= 0 && dragon.name == "NIKCZEMNIUCH"){
            cout << "Starszy Strazak Franciszek zadaje 35 obrazen smokowi!" << endl;
            cout << "Poziom zdrowia przeciwnika: " << dragon.health - 35 << "/" << max_dragon_health  << endl;
            cout << "Zwyciestwo!" << endl;
            cout << "Zdobywasz: 10xp" << endl;
            player.experience += 10;
            cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
            cin.ignore();
            cin.get();
            return 1;

        }

        player.health -= real_dragon_damage;
        cout << dragon.name << " atakuje zadajac " << real_dragon_damage << " obrazen!" << endl << endl;
        cout << "Poziom twojego zdrowia: " << player.health << "/" << player.max_health << endl;

        // Ukrycie poziomu zdrowia finałowego bossa
        if (dragon.name == "WLADCA ZARU"){
            cout << "Poziom zdrowia przeciwnika: ???/???" << endl;
        } else{
            cout << "Poziom zdrowia przeciwnika: " << dragon.health << "/" << max_dragon_health << endl;
        }

        if (player.health <= 0) {
            cout << "Porazka" << endl;
            player.experience += 1;
            cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
            cin.ignore();
            cin.get();
            return -1;
        } else if (dragon.health <= 0) {
            cout << "Zwyciestwo!" << endl;
            cout << "Zdobywasz: "<< max_dragon_health << "xp." << endl;
            player.experience += max_dragon_health;
            cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
            cin.ignore();
            cin.get();

            // Outro bitwy z drugim bossem
            if (dragon.name == "BURZOGNIEW"){
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("SAMUEL OBERWAL! DAJCIE APTECZKE!");
                cout << "Dowodca Strazakow Samuel: ";
                print_letter_by_letter("Oj Franek, Franek [YHY, YHY!] Tyle lat na sluzbie... i nie "
                                       "potrafisz dostrzec... ze mi juz nic... nie... pomoze [YHY!] Zajmij sie mlodym... "
                                       "A ty swiezaku... wez to: ");
                cout << "[+] DODANO PRZEDMIOT: GASNICA DOWODCY" << endl;
                player.extinguisher_lvl  = 3;
                cout << "Dowodca Strazakow Samuel: ";
                print_letter_by_letter("Tobie [YHY] przyda sie bardziej... niz mi....");
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("SAM NIE ROB TEGO! SLYSZYSZ MNIE SAM?! SAM SAAAM!");
                cout << "Strazak Marcel: ";
                print_letter_by_letter("Franek, to koniec, juz mu nie pomozemy...");
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Przegrupujcie sie i widzimy sie w bazie. Te smoki musza za to zaplacic...");
                sleep(2000);
            }

            // Outro bitwy z trzecim bossem
            if (dragon.name == "PYROS"){
                cout << "Rycerz Ognia Artur: ";
                print_letter_by_letter("WOW! To byla ciezka walka! Odnieslismy ogromne straty i zostalo nam troche, atktualnie "
                                       "nie potrzebnego sprzetu. Mysle, ze w ramach podziekowania za pomoc nalezy wam sie to: ");
                cout << "[+] DODANO PRZEDMIOT: LEGENDARNA GASNICA RYCERZA OGNIA" << endl;
                player.extinguisher_lvl++;
                sleep(2000);
                cout << "[+] ULEPSZONO BOMBY WODNE" << endl;
                player.waterBomb_lvl++;
                cout << "Rycerz Ognia Artur: ";
                print_letter_by_letter("Chociaz tyle moge zrobic.");
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Gdybyscie potrzebowali kiedys pomocy nie wahajcie sie nas wzywac. Na nas juz pora mlody. "
                                       "Wracamy do bazy.");
                sleep(2000);
            }

            // Outro bitwy z czwartym bossem
            if (dragon.name == "ZGUBA MIAST"){
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Ugh! Myslalem, ze nie ujdziemy z tego calo! Mial naprawde solidny pancerz. W zasadzie to...");
                sleep(2000);
                cout << "[TRACHH!!]" << endl;
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Mozemy go uzyc do ulepszenia broni! Zostalo nam tylko starcie z WLADCA ZARU - jezeli on "
                                       " faktycznie istnieje... W tej walce kazde ulepszenie jest na wage zlota...");
                cout << "[+] DODANO PRZEDMIOT: GASNICA ZE SMOCZEJ LUSKI" << endl;
                cout << "[+] ULEPSZONO BOMBY WODNE" << endl;
                player.waterBomb_lvl ++;
                player.extinguisher_lvl ++;
            }

            // Dodanie apteczek i zdrowia, jeśli nie jest to pierwsza lub ostatnia walka
            if (dragon.name != "NIKCZEMNIUCH" && dragon.name != "WLADCA ZARU"){
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Wez to i opatrz rany.");
                cout << "[+] DODANO APTECZKI: 3" << endl;
                sleep(1000);
                player.medkits += 3;
                player.max_health += 60;
                cout << "[ZWIEKSZONO MAKSYMALNE ZDROWIE DO "<< player.max_health << "]" << endl;
                cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
                cin.ignore();
                cin.get();
            }

            return 1;
        }
    }
}


// Pierwsza misja ratunkowa
void RCMission1(Firefighter &player){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(0, 2);
    uniform_int_distribution<> dis2(1,25);

    int string_index = dis(gen);
    int key = dis2(gen);

    array<string, 3> sentences = {
            "W mrocznych zakamarkach gdzie cienie tancza w rytm ukrytych prawd poszukaj kryjowki skrytej pod kamieniem ktory nosi na sobie slady czasu.",
            "Pod plomieniami dnia na skraju zapomnianej rzeki odkryj wejscie do podziemnego labiryntu ktorego wejscie strzeze zardzewialy klucz.",
            "W miejscu gdzie kamienie szepcza opowiesci o dawnych czasach zanurz sie w mrocznej studni ktora ukrywa droge do zagubionego swiata podziemnego."
    };

    string encrypted_string = encryptCaesar(sentences[string_index],key);

    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Brygada jest juz w drodze na ratunek cywili w zawalonym szpitalu. "
                           "Ze wzgledu na zniszczenia tradycyjne wejscie do budynku odpada. "
                           "Udalo nam sie pozyskac plany kanalow, tylko problem w tym ze sa zaszyfrowane. "
                           "Musisz okreslic jaki jest klucz tego szyfru. Wstepnie ustalilismy ze jest to liczba miedzy 1 a 25. "
                           "Fragmenty planu wygladaja nastepujaco: ");
    cout << endl << encrypted_string << endl << endl;

    bool mission_completed = false;
    while (!mission_completed) {
        cout << "Wprowadz klucz: ";
        int user_key = getChoice();
        if (user_key > 25 || user_key < 1) {
            cout << "Nieprawidlowy klucz." << endl;
        } else {
            cout << "Fragment po zastosowaniu podanego klucza: " << endl;
            cout << decryptCaesar(encrypted_string, user_key) << endl << endl;

            cout << "[Wybierz akcje]" << endl;
            cout << "1. Zatwierdz" << endl;
            cout << "2. Sprobuj ponownie" << endl;
            int accept_result = getChoice();
            if (accept_result == 1){
                if (user_key == key){
                    mission_completed = true;
                    cout << "Starszy Strazak Franek: ";
                    print_letter_by_letter("Kurde, wyglada na to, ze twoje rozwiazanie ma sens. "
                                           "Przesylam rozszyfrowane plany chlopakom. Swietna robota mlody. ");
                    cout << endl << "[MISJA ZAKONCZONA SUKCESEM]" << endl;
                    cout << "Zdobywasz: 130xp." << endl;
                    cout << "Zdobyto punkty respektu: 250" << endl;
                    cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
                    player.experience += 130;
                    player.respect_points += 250;
                    cin.ignore();
                    cin.get();

                } else {
                    cout << "Starszy Strazak Franek: ";
                    print_letter_by_letter("Cos mi tu nie gra. Sprobuj jeszcze raz.");
                }
            }

        }
    }

}


// Druga misja ratunkowa
void RCMission2(Firefighter &player){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(0, 2);
    int poem_index = dis(gen);
    array<string,3> poems = {
            "W starym lesie, tam gdzie dab jeden stoi,\n"
            "Czeka tajemnica, ktora swiat odkryc boi.\n"
            "Dwanascie godzin zegar wybija,\n"
            "Dziewiec marzen w sercach sie rozwija.\n"
            ,
            "Dwa strumyki plyna, ich spiew to cud,\n"
            "Trzy slonca blask wsrod lesnych wrot.\n"
            "Szesc jeleni biega wsrod cieni,\n"
            "Piec gwiazd blyszczy w nocnej przestrzeni.\n"
            ,
            "Szesc lisci spadlo z drzewa wysokiego,\n"
            "Osiem razy uslyszysz echo glosu swojego.\n"
            "Dwadziescia lat minelo jak jeden dzien,\n"
            "A w starym lesie wciaz tajemnic cien.\n"
    };

    array<int,3> codes = {
            1129,
            2365,
            6820
    };

    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Szybko mlody! Jeden ze smokow zaatakowal SZKOLE! Pakuj sie do samochodu! Ruszamy! ");
    sleep(3000);
    cout << "[SZKOLA PODSTAWOWA W PYROKLESIE]" << endl;
    sleep(1000);
    cout << "Uczen Tomek: ";
    print_letter_by_letter("RAATUUNKUU!! POMOCYYY!!!");
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Jestesmy! Ktoredy mozna wejsc do srodka?");
    cout << "Uczen Tomek: ";
    print_letter_by_letter("Najprosciej glownym wejsciem, ale jest zawalone! Z tylu jest jeszcze wejscie dla personelu. "
                           "Od niedawna zamontowany jest tam nowy zamek i do otwarcia drzwi potrzebny jest KOD. "
                           "Pan Dyrektor rozdal nam takie karteczki, gdybysmy w sytuacji awaryjnej potrzebowali otworzyc te drzwi, "
                           "podobno kod jest na nich zapisany, ale ja tego nie rozumiem: ");

    cout << endl << poems[poem_index] << endl;

    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Jak mozna rozdac uczniom kartki z zaszyfrowanym kodem do awaryjnego wejscia?! "
                           "Mlody, potrafisz odczytac kod z tego tekstu? ");

    bool code_correct = false;
    while (!code_correct) {
        cout << "Twoja odpowiedz: ";
        int user_code = getChoice();
        if (user_code == codes[poem_index]){
            code_correct = true;
        } else {
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Ten kod nie dziala. Sprobujmy innego.");
        }
    }
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Udalo sie! Drzwi otwarte! Wchodzimy! Swietnie sie spisales, mlody!");

    cout << endl << "[MISJA ZAKONCZONA SUKCESEM]" << endl;
    cout << "Zdobywasz: 100xp." << endl;
    cout << "Zdobyto punkty respektu: 150" << endl;
    cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
    player.experience += 100;
    player.respect_points += 150;
    cin.ignore();
    cin.get();

}


// Funkcja losująca misję ratunkową
void RescueCivilianMission(Firefighter &player){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1, 2);

    int mission_number = dis(gen);

    switch (mission_number) {
        case 1:
            RCMission1(player);
            break;
        case 2:
            RCMission2(player);
            break;
        default:
            cout << "[WYSTAPIL NIEZNANY BLAD]" << endl;
            break;
    }

}


// Pierwsza misja gaszenia pożaru
void SCMission1(Firefighter &player){
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Szybko mlody. Wskakuj do samochodu! Wybuchl pozar w dzielnicy przemyslowej!");
    cout << "[PYROKLAS - DZIELNICA PRZEMYSLOWA]" << endl;
    sleep(2000);
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("O nie! Jeden z zaworow doprowadzajacych wode do tego budynku ulegl awarii! "
                           "Musimy przekierowac wode w taki sposob, aby ominac uszkodzony zawor! "
                           "Mlody, ustaw wszsytkie zawory w taki sposob, by tylko te na drodze od hydranta do budynku byly otwarte, "
                           "a pozostale zamkniete. Zawor otwarty jest oznaczony litera O, zamkniety Z. "
                           "\nAktualny schemat rurociagow wyglada tak: ");
    sleep(1000);
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1,2);

    int valve_type = dis(gen);
    string sequence;
    int valves_amt;
    if (valve_type == 1) {
        cout << endl << endl;
        cout << "Hydrant -> [Zawor 1] -> [AWARIA (X/X)] -> [Zawor 6] -> [Zawor 7] -> Budynek" << endl;
        cout << "        \\                                             /" << endl;
        cout << "          [Zawor 2] -> [Zawor 3] -> [Zawor 4] -> [Zawor 5]" << endl;


        sequence = "ZOOOOZO";
        valves_amt = 7;
    } else {
        cout << endl << endl;
        cout << "          [Zawor 1] -> [Zawor 3] -> [Zawor 4] -> [Zawor 7]" << endl;
        cout << "         /                              \\ " << endl;
        cout << "Hydrant                               [Zawor 5]             [Zawor 9] -> Budynek" << endl;
        cout << "        \\                                 \\                 /" << endl;
        cout << "          [Zawor 2] -> [AWARIA (X/X)] -> [Zawor 6] -> [Zawor 8]" << endl;


        sequence = "OZOOOOZOO";
        valves_amt = 9;
    }

    bool sequence_correct = false;
    while (!sequence_correct) {
        cout << endl;
        string user_sequence;
        for (int i = 1; i <= valves_amt; i++) {
            string user_input;
            cout << "Zawor " << i << " (O/Z): ";
            cin >> user_input;
            user_sequence += user_input;
        }
        cout << endl;
        string upper_user_sequence = toUpperCase(user_sequence);
        if (sequence == upper_user_sequence){
            cout << "Starszy Strazak Franciszek: ";
            cout << "Dobra robota mlody! Mozemy teraz ugasic ten budynek!" << endl;
            sequence_correct = true;
        } else {
            cout << "Starszy Strazak Franciszek: ";
            cout << "Woda wciaz nie doplywa do budynku. Sprobuj jeszcze raz!";
        }
    }

    cout << endl << "[MISJA ZAKONCZONA SUKCESEM]" << endl;
    cout << "Zdobywasz: 210xp." << endl;
    player.experience += 210;

    // Dodanie bomb wodnych jeśli są odblokowane
    if (player.waterBomb_lvl > 0){

        uniform_int_distribution<> dis2(1,3);

        int foundBombsAmt = dis2(gen);
        cout << "[+] ZNALEZIONO BOMBY WODNE: " << foundBombsAmt << endl;
        player.waterBomb_amt += foundBombsAmt;
    }

    player.max_health += 25;
    cout << "[ZWIEKSZONO MAKSYMALNE ZDROWIE DO "<< player.max_health << "]" << endl;
    cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
    cin.ignore();
    cin.get();

    // Odblokowanie bomb wodnych po pierwszym ukończeniu
    if (player.waterBomb_lvl == 0){
        sleep(3000);
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Ej mlody zobacz na to! Widzisz te mala skrzyneczke? Tam pod gruzami.");
        sleep(1000);
        print_letter_by_letter("Sprobojemy ja otworzyc?");
        sleep(2000);
        cout << "[TRZASSK!]" << endl;
        print_letter_by_letter("Ha! Tak wlasnie myslalem! TO BOMBY WODNE! Wez sobie troche.");
        cout << "[+] DODANO BOMBY WODNE: 3" << endl;
        sleep(1000);
        player.waterBomb_lvl++;
        player.waterBomb_amt += 3;
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("To bardzo potezna bron, ktora swietnie sprawdza sie w walce ze Smokami. "
                               "Obrazenia jakie zadaja sa zalezne od stanu zdrowia przeciwnika. "
                               "Kilka takich sztuk wystarczy, aby oslabic bestie i dobic salwa z gasnicy. ");
        cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
        cin.ignore();
        cin.get();
        sleep(2000);
    }

}


// Druga misja gaszenia pożaru
void SCMission2(Firefighter &player){
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Mlody! Ruszamy na pomoc chlopakom ktorzy walcza z pozarem w dzielnicy biurowej! "
                           "Pojechali juz kilka godzin temu, a wciaz otrzymujemy stamtad sygnal alarmowy!");
    sleep(2000);
    cout << "[PYROKLAS - DZIELNICA BIUROWA]" << endl;
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Czesc Dominik, dostalismy sygnal alarmowy z tego budynku, ale widze, ze sytuacja opanowana?");
    sleep(1000);
    cout << "Strazak Dominik: ";
    print_letter_by_letter("Witajcie, wlasnie udalo nam sie opanowac ogien, tylko ten ALARM WCIAZ WYJE. Moze to blokowac "
                           "odbieranie sygnalow z innych czesci miasta. Wiecie moze co z tym zrobic?");
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Zajmiemy sie tym! Pamietam, ze panel kontrolny jest w piwnicy tamtego biurowca. Za mna mlody!");
    sleep(2000);
    cout << "[BIUROWIEC J.D. ENTERTAINMENT - PIWNICA]" << endl;
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("O! Tutaj jest ten panel. Poprawne wylaczenie alarmu wymagana odlaczenia poszczegolnych modulow "
                           "w odpowiedniej kolejnosci. Najpierw trzeba odlaczyc czujniki dymu, nastepnie czujniki ciepla. "
                           "Wtedy mozemy odlaczyc syrene alarmowa od panelu kontrolnego i na koncu panel kontrolny od zasilania. "
                           "Tu na klapie jest dokladna instrukcja opisujaca ktory przewod laczy sie z ktorym modulem. "
                           "Niestety ma juz swoje lata i niektore litery sa nieczytelne. Ja nie potrafie tego odczytac. "
                           "Jestes w stanie podac mi kolory przewodow w kolejnosci jakiej nalezy odlaczac moduly? ");

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1,2);
    int note_type = dis(gen);
    string note;
    string sequence;
    if (note_type == 1) {
        note =
                "Czer  ny  rzewod: Lac y syr ne alar owa z pa  lem kont  lnym\n"
                "Nie  e ki pr ewod: aczy czu niki d mu z panel m kontrol  m\n"
                "Zie ony prze od: Lacz pan l kont olny z zasi  niem\n"
                "Bi ly przew d: La  y czu  iki ci pla z pane em k  trolnym\n";

        sequence = "NBCZ";
    } else {
        note =
                "Zie ony prze od: Lac y syr ne alar owa z pa  lem kont  lnym\n"
                "Nie  e ki pr ewod: aczy czu niki d mu z panel m kontrol  m\n"
                "Bi ly przew d: Lacz pan l kont olny z zasi  niem\n"
                "Czer  ny  rzewod: La  y czu  iki ci pla z pane em k  trolnym\n";

        sequence = "NCZB";
    }

    cout << endl << note << endl;
    bool sequence_correct = false;
    while (!sequence_correct) {
        cout << endl;
        string user_sequence;
        for (int i = 1; i <= 4; i++) {
            string user_input;
            cout << "Przewod " << i << " (N/B/C/Z): ";
            cin >> user_input;
            user_sequence += user_input;
        }
        cout << endl;
        string upper_user_sequence = toUpperCase(user_sequence);
        if (sequence == upper_user_sequence){
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Udalo sie! Nareszcie cisza i spokoj!");
            sequence_correct = true;
        } else {
            cout << "Starszy Strazak Franciszek: ";
            cout << "Alarm sie nie wylaczyl! Sprobujmy jeszcze raz! Wystarczy ze podasz mi pierwsza litere danego koloru." << endl;
        }
    }
    sleep(1000);
    cout << endl << "[MISJA ZAKONCZONA SUKCESEM]" << endl;
    cout << "Zdobywasz: 190xp." << endl;

    // Dodanie bomb wodnych jeśli są odblokowane
    if (player.waterBomb_lvl > 0){

        uniform_int_distribution<> dis2(1,3);

        int foundBombsAmt = dis2(gen);
        cout << "[+] ZNALEZIONO BOMBY WODNE: " << foundBombsAmt << endl;
        player.waterBomb_amt += foundBombsAmt;
    }
    player.max_health += 20;
    cout << "[ZWIEKSZONO MAKSYMALNE ZDROWIE DO "<< player.max_health << "]" << endl;
    cout << "Nacisnij ENTER, aby kontynuowac..." << endl;
    player.experience += 190;
    cin.ignore();
    cin.get();

    // Ulepeszenie gaśnicy (jeśli jest na pierwszym poziomie) po pierwszym ukończeniu misji
    if (player.extinguisher_lvl == 1){
        sleep(2000);
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Widzisz te zakurzona gablota przeciwpozarowa? Jesli dobrze widze jest tam gasnica.");
        sleep(2000);
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Zamknieta. Budynek jest w takim stanie, ze lada chwila moze sie zawalic.");
        sleep(2000);
        cout << "[BRZDEKKK!]" << endl;
        cout << "Starszy Strazak Franciszek: ";
        print_letter_by_letter("Zabierzmy ja stad. Szkoda by bylo gdyby zostala tu pod gruzami. W zasadzie to mozesz ja wziac. "
                               "Jest to lepszy model niz ten ktory dostales ode mnie w trakcie szkolenia. ");
        cout << "[+] DODANO PRZEDMIOT: ULEPSZONA GASNICA";
        player.extinguisher_lvl++;
    }

}


// Funkcja losująca misje gaszenia pożaru
void SaveCityMission(Firefighter &player){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1, 2);

    int mission_number = dis(gen);

    switch (mission_number) {
        case 1:
            SCMission1(player);
            break;
        case 2:
            SCMission2(player);
            break;
        default:
            cout << "[WYSTAPIL NIEZNANY BLAD]" << endl;
            break;
    }
}

// Funkcja obsługująca dobre zakończenie (wysoki poziom respektu + pokonanie finałowego bossa)
void GoodEnding(){
    system("cls");
    sleep(3000);
    cout << "[TRAAACHHH!!!]";
    sleep(2000);
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Cholera mlody. Udalo sie. SMOKI POKONANE!");
    sleep(2000);
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Chlopaki! Chodzcie oglosic ludziom, ze to koniec walki z tymi gadami! PYROKLAS ZNOWU JEST WOLNY! "
                           "Szkoda, ze nie ma tu z nami Samuela.");
    sleep(2000);
    cout << "[RYNEK W PYROKLESIE]" << endl;
    cout << "Mieszkancy Pyroklasu: " << endl;
    print_letter_by_letter("HURRA! NIECH ZYJA DZIELNI STRAZACY!");
    sleep(2000);
    print_letter_by_letter("HURRA! NIECH ZYJE WOLNY PYROKLAS!");
    sleep(2000);
    print_letter_by_letter("HURRA!! HURRA!! HURRA!!");
    sleep(2000);
    cout << endl << endl << endl;
    print_letter_by_letter("Straznicy Zaru: Ognisty Konflikt");
    print_letter_by_letter("Scenariusz i rezyseria: Jacob Digital Entertainment");

    exit(0);
}

// Funkcja obsługująca złe zakończenie (porażka w walce z dowolnym bossem)
void BadEnding(){
    sleep(3000);
    system("cls");
    print_letter_by_letter("...");
    sleep(3000);
    print_letter_by_letter("To koniec.");
    sleep(3000);
    print_letter_by_letter("\"Ku pamieci Straznikow Zaru - brygadzie strazakow walczacej z armia smokow\"?");
    sleep(3000);
    print_letter_by_letter("A moze: \"Tu spoczywaja Strazacy walczacy w wojnie ze smokami\"?");
    sleep(3000);
    print_letter_by_letter("To bez znaczenia.");
    sleep(3000);
    print_letter_by_letter("Wiesz co ma znaczenie?");
    sleep(3000);
    print_letter_by_letter("Ze Pyroklas nie dalo sie uratowac.");
    sleep(3000);
    print_letter_by_letter("To od poczatku byla operacja skazana na porazke.");
    sleep(3000);
    print_letter_by_letter("Zrobiles wszystko co mogles");
    sleep(3000);
    print_letter_by_letter("Prawda?");

    cout << endl << endl << endl;
    print_letter_by_letter("Straznicy Zaru: Ognisty Konflikt");
    print_letter_by_letter("Scenariusz i rezyseria: Jacob Digital Entertainment");

    exit(0);
}


// Funkcja obsługująca neturalne zakończenie (niski poziom respektu + pokonanie wszystkich bossów)
void NeutralEnding(){
    system("cls");
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Udalo sie mlody. To koniec!");
    sleep(2000);
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Miasto jest w ruinie, ale odbudujemy je. Zawsze je odbudowujemy.");
    sleep(2000);
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Szkoda, ze Samuel tego nie doswiadczyl... Wolny Pyroklas marzyl mu sie... odkad pamietam.");
    sleep(2000);
    cout << "Strazak Marcel: ";
    print_letter_by_letter("To co zrobimy teraz?");
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Powiemy ludziom, ze smoki zostaly pokonane i... to tyle. Odbudujemy nasza jednostke i "
                           "wrocimy do dawnego zycia: gaszenia pozarow i sciagania kotow z drzew. ");
    sleep(2000);
    cout << "Starszy Strazak Franciszek: ";
    print_letter_by_letter("Dzieki mlody. Bez Ciebie nie dalibysmy sobie rady.");

    cout << endl << endl << endl;
    print_letter_by_letter("Straznicy Zaru: Ognisty Konflikt");
    print_letter_by_letter("Scenariusz i rezyseria: Jacob Digital Entertainment");

    exit(0);
}


// Funkcja wybierająca misje polowania na smoki
void HuntForDragonMission(Firefighter &player, Dragon &burzogniew, Dragon &pyros, Dragon &zgubaMiast, Dragon &wladca_Zaru){
    if (burzogniew.health >= 0){
        if (player.waterBomb_lvl == 0 || player.extinguisher_lvl < 2){

            // Ostreżenie o słabym ekwipunku
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Wedlug mnie to teraz zly pomysl. Lepiej bedzie wybrac sie na misje gaszenia pozaru. "
                                   "Byc moze uda nam sie znalezc dla Ciebie lepszy sprzet. Jesli jednak chesz wyruszyc na polowanie "
                                   "- nie zatrzymuje Cie.");
            cout << "Wybierz akcje:" << endl;
            cout << "1. Wyrusz na polowanie." << endl;
            cout << "2. Powrot." << endl;
            int choice = getChoice();
            if (choice != 1){
                return;
            } else {
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Pamietaj, ze Cie ostrzegalem.");
                sleep(2000);
                if (fight(player, burzogniew) == -1){
                    BadEnding();
                }
            }

        } else {
            if (fight(player, burzogniew) == -1){
                BadEnding();
            }
        }

    } else if (pyros.health >= 0){
        if (player.health < 300 || player.waterBomb_amt < 3){

            // Ostreżenie o słabym ekwipunku
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Wedlug mnie to teraz zly pomysl. Powinnismy lepiej sie przygotowac. "
                                   "Byc moze uda nam sie znalezc troche bomby wodnych i lepszy sprzet. Jesli jednak chesz wyruszyc na polowanie "
                                   "- nie zatrzymuje Cie.");
            cout << "Wybierz akcje:" << endl;
            cout << "1. Wyrusz na polowanie." << endl;
            cout << "2. Powrot." << endl;
            int choice = getChoice();
            if (choice != 1){
                return;
            } else {
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Pamietaj, ze Cie ostrzegalem.");
                sleep(2000);
                if (fight(player, pyros) == -1){
                    BadEnding();
                }
            }

        } else {
            if (fight(player, pyros) == -1){
                BadEnding();
            }
        }
    } else if (zgubaMiast.health >= 0){

        if (player.health < 400 || player.waterBomb_amt < 3){

            // Ostrzeżenie o słabym ekwipunku
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Uwazam, ze nie jestesmy jeszcze gotowi. Powinnismy poszukac troche bomb wodnych. "
                                   "Byc moze uda nam sie znalezc tez lepszy sprzet. "
                                   "Jesli jednak chesz wyruszyc na polowanie - nie zatrzymuje Cie.");
            cout << "Wybierz akcje:" << endl;
            cout << "1. Wyrusz na polowanie." << endl;
            cout << "2. Powrot." << endl;
            int choice = getChoice();
            if (choice != 1){
                return;
            } else {
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Pamietaj, ze Cie ostrzegalem.");
                sleep(2000);
                if (fight(player, zgubaMiast) == -1){
                    BadEnding();
                }
            }

        } else {
            if (fight(player, zgubaMiast) == -1){
                BadEnding();
            }
        }

    } else if (wladca_Zaru.health >= 0){

        // Informacja o ostatecznej walce
        cout << "[===UWAGA===]" << endl;
        print_letter_by_letter("Przystepujesz teraz do finalowej misji po ktorej nastapi epilog. Po przejsciu dalej "
                               "nie bedziesz miec mozliwosci powrotu do Siedziby Straznikow Zaru. Jesli chesz wykonac wiecej misji "
                               "wroc teraz do Centrum Dowodzenia.");

        cout << "Wybierz akcje:" << endl;
        cout << "1. Kontynuuj." << endl;
        cout << "2. Powrot do bazy." << endl;
        int choice = getChoice();
        if (choice != 1){
            return;
        } else {
            sleep(2000);
            if (fight(player, wladca_Zaru) == -1){
                BadEnding();
            } else {
                if (player.respect_points < 600){
                    NeutralEnding();
                } else {
                    GoodEnding();
                }
            }
        }
    }
}


// Główna funkcja
int main() {
    // Utworzenie przeciwników
    Dragon Nikczemniuch("NIKCZEMNIUCH",60,20);
    Dragon Burzogniew("BURZOGNIEW",100,50);
    Dragon Pyros("PYROS",500,60);
    Dragon Zguba_Miast("ZGUBA MIAST",700,80);
    Dragon Wladca_Zaru("WLADCA ZARU", 1200, 210);

    Firefighter player;

    // Menu startowe
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
                player = loadGame();
                // Aktualizacja hp bossów po wczytaniu gry
                Burzogniew.health = player.burzogniew_hp;
                Pyros.health = player.pyros_hp;
                Zguba_Miast.health = player.zguba_miast_hp;
                Wladca_Zaru.health = player.wladca_zaru_hp;
                showMenu = false;
                break;
            case 0:
                cout << "Do zobaczenia!" << endl;
                return 0;
            default:
                cout << "Nieprawidlowy wybor." << endl;
                break;
        }

    }

    // Prolog
    if (player.experience == 0){
            system("cls");
            print_letter_by_letter("Witaj w miescie Pyroklas!");
            sleep(500);
            print_letter_by_letter("Codzienne zycie splata sie tu z cieniem niebezpieczenstwa unoszacego sie w powietrzu. "
                                   "W miasteczku, gdzie smoki nie sa legenda, ale rzeczywistoscia. "
                                   "Ostatnio jednak atmosfera napiecia narasta, a grozba zlowrogich pozarow staje sie coraz bardziej realna. "
                                   "Jako mlody adept pozarnictwa wstepujesz w szeregi lokalnej jednostki strazy pozarnej, aby wesprzec ich w dzialaniach.");
            sleep(2000);
            cout << "[GLOWNA SIEDZIBA STRAZNIKOW ZARU]" << endl;
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
                                   "To narzedzie ktore najlepiej sprawdza sie w gaszeniu pozarow, ale od biedy moze tez "
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
            cout << "[GLOWNA SIEDZIBA STRAZNIKOW ZARU - DACH]" << endl;
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Acha! Jest tutaj! Do dziela mlody!");
            fight(player,Nikczemniuch);
            sleep(2000);
            cout << "Dowodca Strazakow Samuel: ";
            print_letter_by_letter("Psia kostka! Cale szczescie zyjecie! I.. to... Nikczemniuch!? Pokonany?! "
                                   "Musze przyznac niezle wam poszlo!");
            sleep(1000);
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Z calym szacunkiem kapitanie, ale to zasluga mlodego. Moj udzial w tej walce byl znikomy");
            sleep(1000);
            cout << "Dowodca Strazakow Samuel: ";
            print_letter_by_letter("Ach tak? To w takim razie moze powiedz jak Ci na imie swiezy?");
            cout << "Twoja odpowiedz: (NIE WPISUJ SPACJI)";
            getline(cin, player.name);
            cout << "Dowodca Strazakow Samuel: ";
            print_letter_by_letter("Milo Cie poznac " + player.name + ". Franek dokonczyl twoje szkolenie? "
                                                                      "Jeden problem rozwiazany, ale nie mozemy teraz spoczac na laurach. "
                                                                      "Bierzmy sie do roboty.");
            sleep(1000);
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Najpierw wez ten zestaw apteczek. Ten gad niezle cie poturbowal.");
            player.medkits += 5;
            cout << "[+] DODANO APTECZKI: 5" << endl;
            sleep(1000);
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("To maly pakunek, ktory zawsze warto miec przy sobie. Szczegolnie jesli wybierasz sie "
                                   "na polowanie na smoki. Przywroci Cie do pelni sil, ale jej uzycie moze sprawic, ze "
                                   "latwiej bedzie Cie trafic. Uzyj jednej od razu.");
            cout << "[Nacisnij 9 by uzyc apteczki]"<< endl;
            int useMedkit = getChoice();
            if (useMedkit == 9){
                player.health = player.max_health;
                player.medkits--;
                cout << "[PRZYWROCONO ZDROWIE]" << endl;
                sleep(1000);
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("No, od razu lepiej.");
            } else {
                cout << "Starszy Strazak Franciszek: ";
                print_letter_by_letter("Nie upieram sie. Mozesz zostawic je sobie na pozniej. "
                                       "Pamietaj, ze stawanie do walki oslabionym moze sie zle skonczyc.");
            }
            sleep(1000);
            cout << "Starszy Strazak Franciszek: ";
            print_letter_by_letter("Przejdzmy teraz do omowienia naszych codziennych aktywnosci. "
                                   "Standardowo wykonujemy 2 rodzaje misji: ratowanie cywili i gaszenie pozarow. "
                                   "Dodatkowo, kiedy juz ulepszysz wystarczajaco swoje wyposazenie, mozesz wyruszyc na polowanie na smoki. "
                                   "Kazda z misji polega na czyms innym i jest niemniej wazna od pozostalych. "
                                   "Misje ratunkowe zwiekszaja poziom bezpieczenstwa w miescie oraz nasz poziom respektu wsrod ludzi. "
                                   "Gaszenie pozarow odblokowuje dostep do zniszczonych czesci miasta, "
                                   "w ktorych istnieje szansa na odnalezienie lepszej broni lub nowego ekwipunku. "
                                   "Polowanie na smoki to najbardziej wymagajaca misja. "
                                   "Z naszych ustalen wynika, ze w miescie grasuja 4 smoki, no teraz to juz 3 i Wladca Zaru - prawdopodobnie "
                                   "rowniez smok - najpotezniejszy i najsilniejszy ze wszystkich. "
                                   "Mysle, ze polowanie na smoki to aktualnie zly wybor, ale decyzja nalezy do Ciebie. "
                                   "Czym chcesz sie teraz zajac?");


        }

    // Główna pętla gry
    bool gameOver = false;
    while (!gameOver) {
        cout << endl << "[CENTRUM DOWODZENIA]";
        cout << "\n[Wybierz akcje]\n1. Misja ratunkowa\n2. Gaszenie pozaru\n3. Polowanie na smoki\n4. Wyswietl ekwipunek\n"
                "5. Zapisz gre\n9. Uzyj apteczki\n0. Wyjscie z gry\n";

        int choice = getChoice();

        switch (choice) {
            case 1:
                RescueCivilianMission(player);
                break;
            case 2:
                SaveCityMission(player);
                break;
            case 3:
                HuntForDragonMission(player, Burzogniew, Pyros, Zguba_Miast, Wladca_Zaru);
                break;
            case 4:
                player.showEquiment();
                break;
            case 5:
                player.saveGame(Burzogniew, Pyros, Zguba_Miast, Wladca_Zaru);
                break;
            case 9:
                player.health = player.max_health;
                cout << "[PRZYWROCONO ZDROWIE]" << endl;
                cout << "Poziom zdrowia: " << player.health << "/" << player.max_health << endl;
                break;
            case 0:
                gameOver = true;
                break;
            default:
                cout << "Nieprawidlowy wybor. " << endl;
                break;
        }
    }

    cout << "Do zobaczenia!" << endl;
    return 0;
}
