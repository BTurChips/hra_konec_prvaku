#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int vypis_postavy_stats(){
    int volba_postavy; //volitelne archetypy hrace
    string postavy[4] = {"CVRCEK", "SVAB", "CHROUST", "RUMENICE"};
    string stats_kategorie[4] = {"Zivoty", "Energie", "Utok", "Obrana"};
    int postavy_stats[4][4] = {{3, 8, 6, 5}, {8, 3, 5, 6}, {6, 5, 3, 8}, {5, 6, 8, 3}}; //max_hp, max_en, at, df
    char zvolit = 'a';

    do{
    cout << "zvol za koho chces hrat:\n(Cvrcek=1, Svab=2, Chroust=3, Rumenice=4) ";
    cin >> volba_postavy;
    cout << endl;
    switch (volba_postavy){
         case 1:
            cout << postavy[0] << endl;
            for(int i=0; i<4;i++){
                cout << stats_kategorie[i] << ": " << postavy_stats[0][i] << endl;
            }
            break;
         case 2:
             cout << postavy[1] << endl;
            for(int i=0; i<4;i++){
                cout << stats_kategorie[i] << ": " << postavy_stats[1][i] << endl;
            }
            break;
         case 3:
             cout << postavy[2] << endl;
            for(int i=0; i<4;i++){
                cout << stats_kategorie[i] << ": " << postavy_stats[2][i] << endl;
            }
             break;
         case 4:
             cout << postavy[3] << endl;
            for(int i=0; i<4;i++){
                cout << stats_kategorie[i] << ": " << postavy_stats[3][i] << endl;
            }
            break;
         default:
             cout << "Zvolte postavu: ";
             cin >> volba_postavy;
             vypis_postavy_stats();
            break;
    }
    cout << "Chces hrat za tuto postavu?(a/n) ";
    cin >> zvolit;
    }while(zvolit!='a'||zvolit!='A');
    return volba_postavy;
}

int main(){
    string hrac_jmeno;
    char jmeno_potvrdit = 'a';
    string postavy[4] = {"CVRCEK", "SVAB", "CHROUST", "RUMENICE"};
    int hrac_max_hp, hrac_hp; //health
    int hrac_max_en, hrac_en; //energy
    int hrac_penize;
    int hrac_xp, hrac_lv; //level
    int hrac_at; //attack
    int hrac_df; //defense
    string hrac_inv[3]; //inventory

    int hrac[9] = {hrac_max_hp, hrac_hp, hrac_max_en, hrac_en, hrac_penize, hrac_xp, hrac_lv, hrac_at, hrac_df};

    cout << "IMAGO\nVitej ve hre, ";
    vypis_postavy_stats();

    if(vypis_postavy_stats()==1){ //startovni stats hrace
        hrac_max_hp = 3;
        hrac_max_en = 8;
        hrac_at = 6;
        hrac_df = 5;
        cout << "Jsi " << postavy[0] << "! ";
    }else if(vypis_postavy_stats()==2){
        hrac_max_hp = 8;
        hrac_max_en = 3;
        hrac_at = 5;
        hrac_df = 6;
        cout << "Jsi " << postavy[1] << "! ";
    }else if(vypis_postavy_stats()==3){
        hrac_max_hp = 6;
        hrac_max_en = 5;
        hrac_at = 3;
        hrac_df = 8;
        cout << "Jsi " << postavy[2] << "! ";
    }else{
        hrac_max_hp = 5;
        hrac_max_en = 6;
        hrac_at = 8;
        hrac_df = 3;
        cout << "Jsi " << postavy[3] << "! ";
    }
    hrac_hp = hrac_max_hp;
    hrac_en = hrac_max_en;
    hrac_penize = 0;
    hrac_xp = 0;
    hrac_lv = 0;

    do{
        cout << "\nZadej své jméno: ";
        cin >> hrac_jmeno;
        cout << "Chceš se jmenovat " << hrac_jmeno << "?(y/n) ";
        cin >> jmeno_potvrdit;
    }while(jmeno_potvrdit!='a'||jmeno_potvrdit!='A');

return 0;
}
