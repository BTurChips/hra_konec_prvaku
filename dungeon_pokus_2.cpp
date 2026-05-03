#include <iostream>
#include <ctime>
using namespace std;

void vypisStats(int HP, int EN, int AT){
    cout << "HP: " << HP << endl;
    cout << "EN: " << EN << endl;
    cout << "AT: " << AT << endl;
}
void vypisStats(int HP, int EN){
    cout << "HP: " << HP << endl;
    cout << "EN: " << EN << endl;
}

void utokSilny(int AT, int &HP, int &EN){
    if(EN>=10){
        HP-=(AT*2);
        EN-=10;
    }else{
        cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
    }
}
void utokHromadny(int AT, int &HP1, int &EN){
    if(EN>=5){
       HP1-=AT;
       EN-=5;
    }else{
        cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
    }
}
void utokHromadny(int AT, int &HP1, int &HP2, int &EN){
    if(EN>=5){
       HP1-=AT;
       HP2-=AT;
       EN-=5;
    }else{
        cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
    }
}
void utokHromadny(int AT, int &HP1, int &HP2, int &HP3, int &EN){
    if(EN>=5){
       HP1-=AT;
       HP2-=AT;
       HP3-=AT;
       EN-=5;
    }else{
        cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
    }
}
void blockUtok(){
    //pristi kolo mensi damage
}
int healHP(int x, int &HP, int maxHP, int &EN){
    int rozdil;
    rozdil = maxHP-HP;
    if(EN>=5){
        if(rozdil<=x){
            HP+=rozdil;
            return rozdil;
        }else{
            HP+=x;
            return x;
        }
        EN-=5;
    }else{
        cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
        return 0;
    }
}

int bojMoznosti(string monstrum, int HPM, int ENM, int ATM){
    int volba;
    cout << "\nCo chces udelat?" << endl;
    cout << "Prohlednout " << monstrum << " = 0" << endl;
    cout << "Utocit na " << monstrum << " = 1" << endl;
    cout << "Zobrazit schopnosti = 2" << endl;
    do{
    cin >> volba;
    }while(volba<0||volba>2);
    while(volba==0){
        cout << monstrum << ": " << endl;
        vypisStats(HPM, ENM, ATM);
        cout << "Co chces udelat?(1/2) ";
        do{
        cin >> volba;
        }while(volba<1||volba>2);
        }
    if(volba==2){
        cout << "\nHromadny utok (5 EN) = 3" << endl;
        cout << "Silny utok (10 EN) = 4" << endl;
        cout << "Uzdravit se (5 EN) = 5" << endl;
        cout << "Zpet na moznosti = 9" << endl;
        do{
            cin >> volba;
        }while(!(volba==3||volba==4||volba==5||volba==9));
    }
    if(volba==9){
        bojMoznosti(monstrum, HPM, ENM, ATM);
    }
    return volba;
}
void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M, int &HP, int &EN, int AT, int maxHP){
    int tahHrac; //hrac
    int tahM; //monstrum
    int HPM = monstraStats[M][0];
    int ENM = monstraStats[M][1];
    int ATM = monstraStats[M][2];
    int XPM = monstraStats[M][3];

    cout << "------------------" << "\nUtoci na tebe " << monstrum[M] << "\n------------------" << endl;

    while(HP>0&&HPM>0){
        tahHrac = bojMoznosti(monstrum[M], HPM, ENM, ATM);

        switch(tahHrac){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            HPM-=AT;
            break;
        case 3:
            cout << "Utocis na vsechny mostra " << AT << "x1" <<endl;
            utokHromadny(AT, HPM, EN);
            break;
        case 4:
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            utokSilny(AT, HPM, EN);
            break;
        case 5:
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, EN);
            break;
        default:
            cout << "CHYBA" << endl;
            break;
        }

        if(HPM<0){
            HPM=0;
        }
        cout << monstrum[M] << " ma " << HPM << " HP" << endl;

        if(HPM>0){
            cout  << monstrum[M] << " utoci silou " << ATM << endl;
            HP-=ATM;
            if(HP<0){
                HP=0;
            }
            cout << "Tvuj stav je nyni: " << endl;
            vypisStats(HP, EN);
            cout << "------------------" << endl;
        }
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM==0){
        cout << "Porazil jsi " << monstrum[M]  << "." << endl;
    }
}


void vymaxHPEN(int maxHP, int &HP, int maxEN, int &EN){
    HP = maxHP;
    EN = maxEN;
}
int volbaPostavy(string postavy[3], int postavyStats[3][3], int &maxHP, int &maxEN, int &AT){
    int volba;
    bool potvrzeno = false;
    while(potvrzeno==false){
        cout << "Vyber si postavu: " << endl;
        for(int i=0; i<3; i++){
            cout << postavy[i] << " = " << i << endl;
        }
        do{
            cin >> volba;
        }while(volba<0||volba>2);

        switch(volba){
        case 0:
            cout << postavy[0] << ": " << endl;
            vypisStats(postavyStats[0][0],postavyStats[0][1],postavyStats[0][2]);
            break;
        case 1:
            cout << postavy[1] << ": " << endl;
            vypisStats(postavyStats[1][0],postavyStats[1][1],postavyStats[1][2]);
            break;
        case 2:
            cout << postavy[2] << ": " << endl;
            vypisStats(postavyStats[2][0],postavyStats[2][1],postavyStats[2][2]);
            break;
        default:
            cout << "CHYBA";
            break;
        }
        cout << "Chcete zvolit postavu " << postavy[volba] << "? (0=ne, 1=ano) ";
        cin >> potvrzeno;
    }
    cout << "Zvolena postava: " << postavy[volba] << endl;
    maxHP=postavyStats[volba][0];
    maxEN=postavyStats[volba][1];
    AT=postavyStats[volba][2];
    return volba;
}

int main(){
    srand(time(0));
    int postava; //postava hrace
    string postavy[3] = {"Cvrcek","Chroust","Rumenice"};
    int postavyStats[3][3] = {{20, 15, 25},{30, 10, 20},{25, 15, 20}}; //maxHP(zivoty), maxEN(energie), baseAP(utok)
    int maxHP, maxEN;
    int HP, EN, AT;

    string monstra[5] = {"Mravenec","Beruska","Slimak","Stonozka","Svab"};
    int monstraStats[5][4] = {{30, 0, 5, 2},{50, 5, 8, 5},{65, 10, 3, 6},{35, 15, 12, 10},{75, 15, 10, 13}}; //HP, EN, AT, XP
    int M1, M2, M3; //monstra

    cout << "BROUKOVOD" << endl;
    postava = volbaPostavy(postavy, postavyStats, maxHP, maxEN, AT);
    vymaxHPEN(maxHP, HP, maxEN, EN);
    M1 = rand()%5;
    bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP);
    return 0;
}
