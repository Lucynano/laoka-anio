#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

enum Jour {
    LUNDI,
    MARDI,
    MERCREDI,
    JEUDI,
    VENDREDI,
    SAMEDI,
    DIMANCHE
};

struct Plat {
    string nom;
    string laoka;
    string fangarony;
    string mode;
    vector<string> fanampiny;
};

Plat genererLaokaNormal()
{
    Plat p;

    p.nom = "Vary sy Laoka";

    vector<string> laokaNormal = {"Hena omby", "Hena kisoa", "Totokena omby", "Hena baolina", "Kitoza", "Saosisy"};

    p.laoka = laokaNormal[rand() % laokaNormal.size()];

    if (p.laoka == "Hena omby") {
        vector<string> fangarony = {"Tsaramaso", "Kabaro", "Carotte + Ovy", "Petit pois", "Voatavo", "Anana","Voanjobory"};

        p.fangarony = fangarony[rand() % fangarony.size()];
        p.mode = "Rony";

        p.fanampiny = {"Oignon", "Tomate", "Poivre", "Sel", "Huile", "Tongolo gasy"};

    } else if(p.laoka == "Hena kisoa") {
        vector<string> fangarony = {"Tsaramaso", "Kabaro", "Carotte", "Petit pois", "Ravitoto", "Anana","Voanjobory", "Laisoa"};

        p.fangarony = fangarony[rand() % fangarony.size()];
        p.mode = "Ritra";

        p.fanampiny = {"Oignon", "Tomate", "Poivre", "Sel", "Huile", "Tongolo gasy"};

    } else if(p.laoka == "Totokena omby") {
        vector<string> fangarony = {"Tsaramaso", "Haricot vert", "Petit pois", "Anana","Voanjobory", "Ovy"};

        p.fangarony = fangarony[rand() % fangarony.size()];

        if(p.fangarony == "Tsaramaso" || p.fangarony == "Voanjobory" || p.fangarony == "Petit pois") {
            p.mode = "Rony";
        } else {
            p.mode = "Ritra";
        }

        p.fanampiny = {"Oignon", "Tomate", "Poivre", "Sel", "Huile", "Tongolo gasy"};
    } else if(p.laoka == "Hena baolina"){
        p.mode = "Ritra";
        p.fanampiny = {"Sel", "Poivre", "Tongolo maintso"};
    } else {
        p.mode = "Ritra";
        p.fanampiny = {"Sel", "Poivre", "Huile"};
    }

    return p;
}

Plat genererLaokaVendredi() {
    Plat p;
    
    vector<string> nomPlat = {"Pate", "Vary sy Laoka"};

    p.nom = nomPlat[rand() % nomPlat.size()];
    
    if(p.nom == "Vary sy Laoka") {
        vector<string> laokaVendredi = {"Thon", "Sardine", "Atody", "Filet de poisson", "Akoho", "Frite"};

        p.laoka = laokaVendredi[rand() % laokaVendredi.size()];
    
        if(p.laoka != "Thon" && p.laoka != "Sardine") {
            if(p.laoka == "Atody") {
                p.mode = "Ritra";
                p.fanampiny = {"Tomate", "Poivre", "Oignon", "Sel", "Tongolo gasy", "Huile"};
            } else {
                p.mode = "Frire";
                if(p.laoka != "Frite") p.fanampiny = {"Atody", "Chapelure", "Poivre", "Sel", "Huile"};
            }
        }
    } else p.laoka = "Pate";
    

    return p;
}

void afficherPlat(const Plat& p) {
    cout << "\nPlat du jour: " << p.nom << endl;
    if(p.nom == "Vary sy Laoka") {
        cout << "\nLaoka: ";

        if(!p.fangarony.empty()) cout << p.fangarony << " sy ";
        
        cout << p.laoka << endl;

        if(!p.mode.empty()) cout << "\nMode cuisson: " << p.mode << endl;

        cout << "\nRecettes: " << endl;
        cout << "- " << p.laoka << endl;

        if(!p.fangarony.empty()) cout << "- " << p.fangarony << endl; 

        if(!p.fanampiny.empty()) {
            for(auto f : p.fanampiny) 
                cout << "- " << f << endl;
        }
    }

    cout << "\nBon appetit !!!\n" << endl;
}

bool dejaChoisi(const string &laoka, const vector<string> &historique) {
    return find(historique.begin(), historique.end(), laoka) != historique.end();
}

vector<string> chargerHistorique() {
    vector<string> historique;
    ifstream file("historique.txt"); // Lecture dans le fic

    string ligne;
    while(getline(file, ligne)) {
        if(!ligne.empty()) historique.push_back((ligne));
    }

    file.close();

    return historique;
}

void sauvegarderHistorique(const vector<string>& historique) {
    ofstream file("historique.txt"); // Ecriture dans le fic

    for(const auto& item : historique) {
        file << item << endl;
    }

    file.close();
}

bool jourExiste(int jour) {
    ifstream file("historique.txt");
    string ligne;

    string prefix = to_string(jour) + ".";

    while(getline(file, ligne)) {
        if(ligne.find(prefix) == 0) {
            return true; // le jour existe deja
        }
    }

    return false; // non trouve
}

bool estLundi() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return now->tm_wday == 1;
}

int main() {
    srand(time(0));

    // Chaque lundi l'historique se reinitialise
    if(estLundi()) {
        ofstream file("historique.txt");
        file.close();
    }

    vector<string> historiqueSemaine = chargerHistorique();

    int jourInput = 0;

    cout << "Entrer le jour (1 -> Lundi, 2 -> Mardi, ..., 7 -> Dimanche): ";

    // 1 a 7 seulement le choix sinon invalide
    while(!(cin >> jourInput) || jourInput < 1 || jourInput > 7) {
        cout << "Entree invalide !" << "\n" << "\nReesayez: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Un jour deja tape ne peut plus etre retaper sauf a la semaine prochaine
    if(jourExiste(jourInput)) {
        cout << "Ce jour a deja un plat du jour !" << endl;
    } else {
        Jour jour = static_cast<Jour>(jourInput - 1);
    
        Plat p;
    
        string cle; // pour stocker le laoka avec fangarony
    
        do {
            if(jour == VENDREDI)
                p = genererLaokaVendredi();
            else
                p = genererLaokaNormal();
    
            if(!p.fangarony.empty())
                cle = to_string(jourInput) + ". " + p.fangarony + " sy " + p.laoka;
            else
                cle = to_string(jourInput) + ". " + p.laoka;
        } while(dejaChoisi(cle, historiqueSemaine));
    
        // Stocker les laoka du semaine pour eviter la redondance
        historiqueSemaine.push_back(cle);
    
        // Stocker dans un fic temporaire
        sauvegarderHistorique(historiqueSemaine);
    
        afficherPlat(p);
    }

    return 0;
}