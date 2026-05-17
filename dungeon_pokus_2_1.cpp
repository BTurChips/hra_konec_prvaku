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
int volbaTarget(string monstrum1, string monstrum2){
    int target;
     cout << "Na koho chces zautocit?" << endl << monstrum1 << " = 11" << endl << monstrum2 << " = 12" << endl;
        do{
            cin >> target;
        }while(target<11||target>12);
    return target;
}
int volbaTarget(string monstrum1, string monstrum2, string monstrum3){
    int target;
     cout << "Na koho chces zautocit?" << endl << monstrum1 << " = 11" << endl << monstrum2 << " = 12" << endl << monstrum3 << " = 13" << endl;
        do{
            cin >> target;
        }while(target<11||target>13);
    return target;
}

void tahMonstra(string monstrum[], int M, int &HPM, int &ENM, int monstraStats[5][4], int &HP){
    int r1 = rand()%5;
    int r2 = rand()%6+5;

    switch(r1){
    default:
        cout << "chyba" << endl;
        break;
    case 0:
    case 1:
    case 2:
        cout  << monstrum[M] << " utoci silou " << monstraStats[M][2] << endl;
        HP-=monstraStats[M][2];
        break;
    case 3:
        if(ENM>=10){
        cout  << monstrum[M] << " utoci silou x2 -> " << monstraStats[M][2]*2 << endl;
        HP-=(monstraStats[M][2]*2);
        ENM-=10;
        }else{
        cout  << monstrum[M] << " chce pouzit silny utok, ale nema dost energie" << endl;
        }
        break;
    case 4:
        int rozdil = monstraStats[M][0] - HPM;
        if(rozdil>0){
            cout  << monstrum[M] << " se pokousi uzdravit" << endl;
            if(ENM>=5){
                if(rozdil>r2){
                    cout  << monstrum[M] << " se leci o " << r2 << " zivotu" << endl;
                    HPM+=r2;
                }else{
                    cout  << monstrum[M] << " se leci o " << rozdil << " zivotu" << endl;
                    HPM+=rozdil;
                }
                ENM-=5;
            }else{
            cout << "nema dost energie" << endl;
            }
        }else{
            cout << monstrum[M] << " premysli co udela" << endl;
           }
        break;
    }

        if(HP<0){
            HP=0;
        }
}
void tahHrace1(string monstrum[5], int M, int &HPM, int ENM, int ATM, int &HP, int maxHP, int AT, int &EN){
    int volba;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
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
            cout << "\nSilny utok (10 EN) = 3" << endl;
            cout << "Uzdravit se (5 EN) = 4" << endl;
            cout << "Zpet na moznosti = 9" << endl;
        do{
            cin >> volba;
        }while(!(volba==3||volba==4||volba==9));
        }
    }while(volba==9);

        switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            HPM-=AT;
            break;
        case 3:
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            utokSilny(AT, HPM, EN);
            break;
        case 4:
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, EN);
            break;
        case 5:
            cout << "Utocis na vsechny mostra " << AT << "x1" <<endl;
            utokHromadny(AT, HPM, EN);
            break;
        default:
            cout << "CHYBA" << endl;
            break;
        }
}
void tahHrace2(string monstrum[5], int M1, int &HPM1, int ENM1, int ATM1, int M2, int &HPM2, int ENM2, int ATM2, int &HP, int maxHP, int AT, int &EN){
    int volba;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
            cout << "Zobrazit schopnosti = 2" << endl;
        do{
            cin >> volba;
        }while(volba<0||volba>2);
        while(volba==0){
            cout << monstrum[M1] << ": " << endl;
            vypisStats(HPM1, ENM1, ATM1);
            cout << monstrum[M2] << ": " << endl;
            vypisStats(HPM2, ENM2, ATM2);
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
    }while(volba==9);

    int target = 11;

    if(volba==1||volba==4){
       target = volbaTarget(monstrum[M1], monstrum[M2]);
    }

        switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            if(target==11){
                HPM1-=AT;
            }
            if(target==12){
                HPM2-=AT;
            }
            break;
        case 3:
            cout << "Utocis na vsechny mostra " << AT << "x2" <<endl;
            utokHromadny(AT, HPM1, HPM2, EN);
            break;
        case 4:
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            if(target==11){
                utokSilny(AT, HPM1, EN);
            }
            if(target==12){
                utokSilny(AT, HPM2, EN);
            }
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
}
void tahHrace3(string monstrum[5], int M1, int &HPM1, int ENM1, int ATM1, int M2, int &HPM2, int ENM2, int ATM2, int M3, int &HPM3, int ENM3, int ATM3, int &HP, int maxHP, int AT, int &EN){
    int volba;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
            cout << "Zobrazit schopnosti = 2" << endl;
        do{
            cin >> volba;
        }while(volba<0||volba>2);
        while(volba==0){
            cout << monstrum[M1] << ": " << endl;
            vypisStats(HPM1, ENM1, ATM1);
            cout << monstrum[M2] << ": " << endl;
            vypisStats(HPM2, ENM2, ATM2);
            cout << monstrum[M3] << ": " << endl;
            vypisStats(HPM3, ENM3, ATM3);
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
    }while(volba==9);

    int target = 11;

    if(volba==1||volba==4){
       target = volbaTarget(monstrum[M1], monstrum[M2], monstrum[M3]);
    }

        switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            if(target==11){
                HPM1-=AT;
            }
            if(target==12){
                HPM2-=AT;
            }
            if(target==13){
                HPM3-=AT;
            }
            break;
        case 3:
            cout << "Utocis na vsechny mostra " << AT << "x3" <<endl;
            utokHromadny(AT, HPM1, HPM2, HPM3, EN);
            break;
        case 4:
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            if(target==11){
                utokSilny(AT, HPM1, EN);
            }
            if(target==12){
                utokSilny(AT, HPM2, EN);
            }
            if(target==13){
                utokSilny(AT, HPM3, EN);
            }
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
}

void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M, int &HP, int &EN, int AT, int maxHP, int &XP){
    int tahM, target; //monstrum
    int HPM = monstraStats[M][0];
    int ENM = monstraStats[M][1];
    int ATM = monstraStats[M][2];
    int XPM = monstraStats[M][3];

    cout << "------------------" << "\nUtoci na tebe " << monstrum[M] << "\n------------------" << endl;

    while(HP>0&&HPM>0){

        tahHrace1(monstrum, M, HPM, ENM, ATM, HP, maxHP, AT, EN);

        if(HPM<0){
            HPM=0;
        }
        cout << monstrum[M] << " ma " << HPM << " HP" << endl;

        if(HPM>0){
            tahMonstra(monstrum, M, HPM, ENM, monstraStats, HP);
        }
    cout << "Tvuj stav je nyni: " << endl;
    vypisStats(HP, EN);
    cout << "------------------" << endl;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM==0){
        cout << "Porazil jsi " << monstrum[M]  << ". Ziskal jsi " << XPM << " xp" << endl;
        XP+=XPM;
    }
}
void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M1, int M2, int &HP, int &EN, int AT, int maxHP, int &XP){
    int target; //monstrum
    int HPM1 = monstraStats[M1][0];
    int ENM1 = monstraStats[M1][1];
    int ATM1 = monstraStats[M1][2];
    int XPM1 = monstraStats[M1][3];

    int HPM2 = monstraStats[M2][0];
    int ENM2 = monstraStats[M2][1];
    int ATM2 = monstraStats[M2][2];
    int XPM2 = monstraStats[M2][3];

    cout << "------------------" << "\nUtoci na tebe " << monstrum[M1] << " a " << monstrum[M2] << "\n------------------" << endl;

    while(HP>0&&HPM1>0||HPM2>0){

        tahHrace2(monstrum, M1, HPM1, ENM1, ATM1, M2, HPM2, ENM2, ATM2, HP, maxHP, AT, EN);

        if(HPM1<0){
            HPM1=0;
        }
        if(HPM2<0){
            HPM2=0;
        }
        cout << monstrum[M1] << " ma " << HPM1 << " HP" << endl;
        cout << monstrum[M2] << " ma " << HPM2 << " HP" << endl;

        if(HPM1>0){
            tahMonstra(monstrum, M1, HPM1, ENM1, monstraStats, HP);
        }
        if(HPM2>0){
            tahMonstra(monstrum, M2, HPM2, ENM2, monstraStats, HP);
        }
    cout << "Tvuj stav je nyni: " << endl;
    vypisStats(HP, EN);
    cout << "------------------" << endl;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM1==0&&HPM2==0){
        cout << "Porazil jsi " << monstrum[M1] << " a " << monstrum[M2]  << ". Ziskal jsi " << XPM1+XPM2 << " xp" << endl;
        XP+=(XPM1+XPM2);
    }
}
void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M1, int M2, int M3, int &HP, int &EN, int AT, int maxHP, int &XP){
    int target; //monstrum
    int HPM1 = monstraStats[M1][0];
    int ENM1 = monstraStats[M1][1];
    int ATM1 = monstraStats[M1][2];
    int XPM1 = monstraStats[M1][3];

    int HPM2 = monstraStats[M2][0];
    int ENM2 = monstraStats[M2][1];
    int ATM2 = monstraStats[M2][2];
    int XPM2 = monstraStats[M2][3];

    int HPM3 = monstraStats[M3][0];
    int ENM3 = monstraStats[M3][1];
    int ATM3 = monstraStats[M3][2];
    int XPM3 = monstraStats[M3][3];

    cout << "------------------" << "\nUtoci na tebe " << monstrum[M1] << ", " << monstrum[M2] << " a " << monstrum[M3] << "\n------------------" << endl;

    while(HP>0&&(HPM1>0||HPM2>0||HPM3>0)){

        tahHrace3(monstrum, M1, HPM1, ENM1, ATM1, M2, HPM2, ENM2, ATM2, M3, HPM3, ENM3, ATM3, HP, maxHP, AT, EN);

        if(HPM1<0){
            HPM1=0;
        }
        if(HPM2<0){
            HPM2=0;
        }
        if(HPM3<0){
            HPM3=0;
        }
        cout << monstrum[M1] << " ma " << HPM1 << " HP" << endl;
        cout << monstrum[M2] << " ma " << HPM2 << " HP" << endl;
        cout << monstrum[M3] << " ma " << HPM3 << " HP" << endl;

        if(HPM1>0){
            tahMonstra(monstrum, M1, HPM1, ENM1, monstraStats, HP);
        }
        if(HPM2>0){
            tahMonstra(monstrum, M2, HPM2, ENM2, monstraStats, HP);
        }
        if(HPM3>0){
            tahMonstra(monstrum, M3, HPM3, ENM3, monstraStats, HP);
        }
    cout << "Tvuj stav je nyni: " << endl;
    vypisStats(HP, EN);
    cout << "------------------" << endl;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM1==0&&HPM2==0){
        cout << "Porazil jsi " << monstrum[M1] << ", " << monstrum[M2] << " a " << monstrum[M3] << ". Ziskal jsi " << XPM1+XPM2+XPM3 << " xp" << endl;
        XP+=(XPM1+XPM2+XPM3);
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
    int XP=0;

    string monstra[5] = {"Mravenec","Beruska","Slimak","Stonozka","Svab"};
    int monstraStats[5][4] = {{30, 0, 5, 2},{50, 5, 8, 5},{65, 10, 3, 6},{35, 15, 12, 10},{75, 15, 10, 13}}; //HP, EN, AT, XP
    int M1, M2, M3; //monstra

    cout << "BROUKOVOD" << endl;
    postava = volbaPostavy(postavy, postavyStats, maxHP, maxEN, AT);
    vymaxHPEN(maxHP, HP, maxEN, EN);

    M1 = rand()%5;
    M2 = rand()%5;
    M3 = rand()%5;
    int bojPocet = rand()%3;

    switch(bojPocet){
    case 0:
        bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP, XP);
        break;
    case 1:
        bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, XP);
        break;
    case 2:
        bojovaSmycka(monstra, monstraStats, M1, M2, M3, HP, EN, AT, maxHP, XP);
        break;
    default:
        cout << "chyba" << endl;
        break;
    }

    return 0;
}
