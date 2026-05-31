#include <iostream>
#include <ctime>
using namespace std;
int blokUtok=0; //zabraneni damage pristiho tahu monstra
int extraReady[3]={0,0,0}; //monstrum je ready na extra silny utok;

void levelXP(int xp, int &level, int &AT, int &maxHP, int &maxEN){
    int aktualniLevel = level;
    if(xp<10){
        level = 0;
    }else if(xp<10){
        level = 1;
    }else if(xp<30){
        level = 2;
    }else if(xp<60){
        level = 3;
    }else if(xp<100){
        level = 4;
    }else if(xp<150){
        level = 5;
    }else if(xp<210){
        level = 6;
    }else if(xp<280){
        level = 7;
    }else if(xp<360){
        level = 8;
    }else if(xp<450){
        level = 9;
    }else if(xp>=450){
        level = 10;
    }
    if(level>aktualniLevel){
        for(int i=0; i<(level-aktualniLevel); i++){
            maxHP+=(level-i);
            if((level-i)%2==0){
                maxEN+=5;
            }
            AT+=5;
        }
        cout << "Dosahl jsi level " << level << "! Tvoje stats jsou nyni:\nHP max: " << maxHP << "\nEN max: " << maxEN << "\nAT: " << AT << endl;
    }
}
int penizeDrop(int Mpocet){
    int penize=0;
    int r1 = rand()%11+5;
    penize = r1*Mpocet;
    return penize;
}

void vypisStats(int HP, int maxHP, int EN, int maxEN, int AT){
    cout << "HP: " << HP << "/" << maxHP << endl;
    cout << "EN: " << EN << "/" << maxEN << endl;
    cout << "AT: " << AT << endl;
}
void vypisStats(int HP, int maxHP, int EN, int maxEN){
    cout << "HP: " << HP << "/" << maxHP << endl;
    cout << "EN: " << EN << "/" << maxEN << endl;
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
     cout << "Na koho?" << endl << monstrum1 << " = 1" << endl << monstrum2 << " = 2" << endl;
        do{
            cin >> target;
        }while(target<1||target>2);
    return target;
}
int volbaTarget(string monstrum1, string monstrum2, string monstrum3){
    int target;
     cout << "Na koho?" << endl << monstrum1 << " = 1" << endl << monstrum2 << " = 2" << endl << monstrum3 << " = 3" << endl;
        do{
            cin >> target;
        }while(target<1||target>3);
    return target;
}

void tahMonstra(string monstrum[], int M, int &HPM, int maxHPM, int &ENM, int ATM, int &HP, int poradi){
    int r1 = rand()%10;
    int r2 = rand()%6+5;
    if(extraReady[poradi]>0){
        cout << monstrum[M] << " pouziva *extra* silny utok: " << ATM << "x4 = " << ATM*4 << endl;
        HP-=(ATM*4);
        ENM-=15;
        extraReady[poradi]--;
        if(ENM<0){
            ENM=0;
        }
        r1=10;
    }

    switch(r1){
    default:
        cout << "chyba" << endl;
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        cout  << monstrum[M] << " utoci silou " << ATM << endl;
        HP-=ATM;
        break;
    case 5:
    case 6:
        if(ENM>=10){
        cout  << monstrum[M] << " utoci silou x2 -> " <<ATM*2 << endl;
        HP-=(ATM*2);
        ENM-=10;
        }else{
        cout  << monstrum[M] << " chce pouzit silny utok, ale nema dost energie" << endl;
        }
        break;
    case 7:
    case 8:
        {
        int rozdil = maxHPM - HPM;
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
    case 9:
        cout << monstrum[M] << " se pripravuje na *extra* silny utok" << endl;
        extraReady[poradi]=1;
        break;
    case 10:
        break;
    }

        if(HP<0){
            HP=0;
        }
}
void tahHrace1(string monstrum[], int M, int &HPM, int maxHPM, int ENM, int maxENM, int ATM, int &HP, int maxHP, int AT, int &EN, int maxEN){
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
            cout << monstrum[M] << ": " << endl;
            vypisStats(HPM, maxHPM, ENM, maxENM);
            cout << "Co chces udelat?(1/2) ";
            do{
            cin >> volba;
            }while(volba<1||volba>2);
            }
        if(volba==2){
            cout << "\nSilny utok (10 EN) = 3" << endl;
            cout << "Uzdravit se (5 EN) = 4" << endl;
            cout << "Blokovat utok (10 EN) = 5" << endl;
            cout << "Zpet na moznosti = 9" << endl;
        do{
            cin >> volba;
        }while(!(volba==3||volba==4||volba==5||volba==9));
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
            vypisStats(HP, maxHP, EN, maxEN);
            break;
        case 5:
            if(EN>=10){
            cout << "Blokujes pristi utok nepratele " << monstrum[M] << endl;
            blokUtok++;
            EN-=10;
            }else{
            cout << "Nemas dost energie" << endl;
            }
            break;
        default:
            cout << "CHYBA" << endl;
            break;
        }
}
void tahHrace2(string monstrum[], int M1, int &HPM1, int maxHPM1, int ENM1, int maxENM1, int ATM1, int M2, int &HPM2, int maxHPM2, int ENM2, int maxENM2, int ATM2, int &HP, int maxHP, int AT, int &EN, int maxEN, int &target){
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
            vypisStats(HPM1, maxHPM1, ENM1, maxENM1, ATM1);
            cout << monstrum[M2] << ": " << endl;
            vypisStats(HPM2, maxHPM2, ENM2, maxENM2, ATM2);
            cout << "Co chces udelat?(1/2) ";
            do{
            cin >> volba;
            }while(volba<1||volba>2);
            }
        if(volba==2){
        cout << "\nHromadny utok (5 EN) = 3" << endl;
        cout << "Silny utok (10 EN) = 4" << endl;
        cout << "Uzdravit se (5 EN) = 5" << endl;
        cout << "Blokovat utok (10 EN) = 6" << endl;
        cout << "Zpet na moznosti = 9" << endl;
        do{
            cin >> volba;
        }while(!(volba==3||volba==4||volba==5||volba==6||volba==9));
        }
    }while(volba==9);

    if(volba==1||volba==4||volba==6){
        if(HPM1>0&&HPM2>0){
            target = volbaTarget(monstrum[M1], monstrum[M2]);
        }else if(HPM1>0){
            target = 1;
        }else{
            target = 2;
        }
    }

        switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            if(target==1){
                HPM1-=AT;
            }
            if(target==2){
                HPM2-=AT;
            }
            break;
        case 3:
            cout << "Utocis na vsechny mostra " << AT << "x2" <<endl;
            utokHromadny(AT, HPM1, HPM2, EN);
            break;
        case 4:
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            if(target==1){
                utokSilny(AT, HPM1, EN);
            }
            if(target==2){
                utokSilny(AT, HPM2, EN);
            }
            break;
        case 5:
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, maxHP, EN, maxEN);
            break;
        case 6:
            if(EN>=10){
            if(target==1){
                cout << "Blokujes pristi utok nepratele " << monstrum[M1] << endl;
            }
            if(target==2){
                cout << "Blokujes pristi utok nepratele " << monstrum[M2] << endl;
            }
            blokUtok++;
            EN-=10;
            }else{
            cout << "Nemas dost energie" << endl;
            }
            break;
        default:
            cout << "CHYBA" << endl;
            break;
        }
}
void tahHrace3(string monstrum[], int M1, int &HPM1, int maxHPM1, int ENM1, int maxENM1, int ATM1, int M2, int &HPM2, int maxHPM2, int ENM2, int maxENM2, int ATM2, int M3, int &HPM3, int maxHPM3, int ENM3, int maxENM3, int ATM3, int &HP, int maxHP, int AT, int &EN, int maxEN, int &target){
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
            vypisStats(HPM1, maxHPM1, ENM1, maxENM1, ATM1);
            cout << monstrum[M2] << ": " << endl;
            vypisStats(HPM2, maxHPM2, ENM2, maxENM2, ATM2);
            cout << monstrum[M3] << ": " << endl;
             vypisStats(HPM3, maxHPM3, ENM3, maxENM3, ATM3);
            cout << "Co chces udelat?(1/2) ";
            do{
            cin >> volba;
            }while(volba<1||volba>2);
            }
        if(volba==2){
        cout << "\nHromadny utok (5 EN) = 3" << endl;
        cout << "Silny utok (10 EN) = 4" << endl;
        cout << "Uzdravit se (5 EN) = 5" << endl;
        cout << "Blokovat utok (10 EN) = 6" << endl;
        cout << "Zpet na moznosti = 9" << endl;
        do{
            cin >> volba;
        }while(!(volba==3||volba==4||volba==5||volba==6||volba==9));
        }
    }while(volba==9);

    if(volba==1||volba==4||volba==6){
        if(HPM1>0&&HPM2>0&&HPM3>0){
            target = volbaTarget(monstrum[M1], monstrum[M2], monstrum[M3]);
        }else if(HPM1>0&&HPM2>0){
            target = volbaTarget(monstrum[M1], monstrum[M2]);
        }else if(HPM2>0&&HPM3>0){
            target = volbaTarget(monstrum[M2], monstrum[M3]);
        }else if(HPM1>0&&HPM3>0){
            target = volbaTarget(monstrum[M1], monstrum[M3]);
        }else if(HPM1>0){
            target = 1;
        }else if(HPM2>0){
            target = 2;
        }else if(HPM3>0){
            target = 3;
        }


    }

        switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            if(target==1){
                HPM1-=AT;
            }
            if(target==2){
               HPM2-=AT;
            }
            if(target==3){
                HPM2-=AT;
            }
            break;
        case 3:
            cout << "Utocis na vsechny mostra " << AT << "x3" <<endl;
            utokHromadny(AT, HPM1, HPM2, HPM3, EN);
            break;
        case 4:
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            if(target==1){
                utokSilny(AT, HPM1, EN);
            }
            if(target==2){
                utokSilny(AT, HPM2, EN);
            }
            if(target==3){
                utokSilny(AT, HPM3, EN);
            }
            break;
        case 5:
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, maxHP, EN, maxEN);
            break;
        case 6:
            if(EN>=10){
            if(target==1){
                cout << "Blokujes pristi utok nepratele " << monstrum[M1] << endl;
            }
            if(target==2){
                cout << "Blokujes pristi utok nepratele " << monstrum[M2] << endl;
            }
            if(target==3){
                cout << "Blokujes pristi utok nepratele " << monstrum[M3] << endl;
            }
            blokUtok++;
            EN-=10;
            }else{
            cout << "Nemas dost energie" << endl;
            }
            break;
        default:
            cout << "CHYBA" << endl;
            break;
        }
}

void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    int tahM, target; //monstrum
    int maxHPM = monstraStats[M][0];
    int maxENM = monstraStats[M][1];
    int ATM = monstraStats[M][2];
    int XPM = monstraStats[M][3];
    int HPM = maxHPM;
    int ENM = maxENM;
    int kolo = 1;
    if(HP>0){
    cout << "------------------" << "\nUtoci na tebe " << monstrum[M] << "\n------------------" << endl;
    extraReady[0]=0;
    while(HP>0&&HPM>0){
        cout << "KOLO " << kolo << ":" << endl;
        tahHrace1(monstrum, M, HPM, maxHPM, ENM, maxENM, ATM, HP, maxHP, AT, EN, maxEN);

        if(HPM<0){
            HPM=0;
        }
        cout << monstrum[M] << " ma " << HPM << " HP" << endl;
        if(blokUtok>0){
            ATM = 0;
            blokUtok--;
        }else{
            ATM = monstraStats[M][2];
        }

        if(HPM>0){
            tahMonstra(monstrum, M, HPM, maxHPM, ENM, ATM, HP, 0);
        }
    cout << "Tvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
    kolo++;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM==0){
        int drop = penizeDrop(1);
        cout << "Porazil jsi " << monstrum[M]  << ". Ziskal jsi " << XPM << " xp a " << drop << " zlata." << endl;
        XP+=XPM;
        penize+=drop;
    }
    }

}
void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M1, int M2, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    int target; //monstrum
    int maxHPM1 = monstraStats[M1][0];
    int maxENM1 = monstraStats[M1][1];
    int ATM1 = monstraStats[M1][2];
    int XPM1 = monstraStats[M1][3];
    int maxHPM2 = monstraStats[M2][0];
    int maxENM2 = monstraStats[M2][1];
    int ATM2 = monstraStats[M2][2];
    int XPM2 = monstraStats[M2][3];
    int HPM1 = maxHPM1;
    int ENM1 = maxENM1;
    int HPM2 = maxHPM2;
    int ENM2 = maxENM2;
    if(HP>0){
    cout << "------------------" << "\nUtoci na tebe " << monstrum[M1] << " a " << monstrum[M2] << "\n------------------" << endl;
    extraReady[0]=0;
    extraReady[1]=0;
    while(HP>0&&(HPM1>0||HPM2>0)){

        tahHrace2(monstrum, M1, HPM1, maxHPM1, ENM1, maxENM1, ATM1, M2, HPM2, maxHPM2, ENM2, maxENM2, ATM2, HP, maxHP, AT, EN, maxEN, target);

        if(HPM1<0){
            HPM1=0;
        }
        if(HPM2<0){
            HPM2=0;
        }
        cout << monstrum[M1] << " ma " << HPM1 << " HP" << endl;
        cout << monstrum[M2] << " ma " << HPM2 << " HP" << endl;
        if(blokUtok>0){
            if(target==1){
                ATM1=0;
            }
            if(target==2){
                ATM2=0;
            }
            blokUtok--;
        }else{
            ATM1 = monstraStats[M1][2];
            ATM2 = monstraStats[M2][2];
        }

        if(HPM1>0){
            tahMonstra(monstrum, M1, HPM1, maxHPM1, ENM1, ATM1, HP, 0);
        }
        if(HPM2>0){
            tahMonstra(monstrum, M2, HPM2, maxHPM2, ENM2, ATM2, HP, 1);
        }
    cout << "Tvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM1==0&&HPM2==0){
        int drop = penizeDrop(2);
        cout << "Porazil jsi " << monstrum[M1] << " a " << monstrum[M2]  << ". Ziskal jsi " << XPM1+XPM2 << " xp a " << drop << " zlata." << endl;
        XP+=(XPM1+XPM2);
        penize+=drop;
    }
    }
}
void bojovaSmycka(string monstrum[5], int monstraStats[5][4], int M1, int M2, int M3, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    int target; //monstrum
    int maxHPM1 = monstraStats[M1][0];
    int maxENM1 = monstraStats[M1][1];
    int ATM1 = monstraStats[M1][2];
    int XPM1 = monstraStats[M1][3];
    int maxHPM2 = monstraStats[M2][0];
    int maxENM2 = monstraStats[M2][1];
    int ATM2 = monstraStats[M2][2];
    int XPM2 = monstraStats[M2][3];
    int maxHPM3 = monstraStats[M3][0];
    int maxENM3 = monstraStats[M3][1];
    int ATM3 = monstraStats[M3][2];
    int XPM3 = monstraStats[M3][3];
    int HPM1 = maxHPM1;
    int ENM1 = maxENM1;
    int HPM2 = maxHPM2;
    int ENM2 = maxENM2;
    int HPM3 = maxHPM3;
    int ENM3 = maxENM3;
    if(HP>0){
    cout << "------------------" << "\nUtoci na tebe " << monstrum[M1] << ", " << monstrum[M2] << " a " << monstrum[M3] << "\n------------------" << endl;
    extraReady[0]=0;
    extraReady[1]=0;
    extraReady[2]=0;
    while(HP>0&&(HPM1>0||HPM2>0||HPM3>0)){

        tahHrace3(monstrum, M1, HPM1, maxHPM1, ENM1, maxENM1, ATM1, M2, HPM2, maxHPM2, ENM2, maxENM2, ATM2, M3, HPM3, maxHPM3, ENM3, maxENM3, ATM3, HP, maxHP, AT, EN, maxEN, target);

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
        if(blokUtok>0){
            if(target==1){
                HPM1-=AT;
            }
            if(target==2){
                HPM2-=AT;
            }
            if(target==3){
                HPM3-=AT;
            }
            blokUtok--;
        }else{
            ATM1 = monstraStats[M1][2];
            ATM2 = monstraStats[M2][2];
            ATM3 = monstraStats[M3][2];
        }

        if(HPM1>0){
            tahMonstra(monstrum, M1, HPM1, maxHPM1, ENM1, ATM1, HP, 0);
        }
        if(HPM2>0){
            tahMonstra(monstrum, M2, HPM2, maxHPM2, ENM2, ATM2, HP, 1);
        }
        if(HPM3>0){
            tahMonstra(monstrum, M3, HPM3, maxHPM3, ENM3, ATM3, HP, 2);
        }
    cout << "Tvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM1==0&&HPM2==0){
        int drop = penizeDrop(3);
        cout << "Porazil jsi " << monstrum[M1] << ", " << monstrum[M2] << " a " << monstrum[M3] << ". Ziskal jsi " << XPM1+XPM2+XPM3 << " xp a "  << drop << " zlata." << endl;
        XP+=(XPM1+XPM2+XPM3);
        penize+=drop;
    }
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
            vypisStats(postavyStats[0][0], postavyStats[0][0], postavyStats[0][1], postavyStats[0][1], postavyStats[0][2]);
            break;
        case 1:
            cout << postavy[1] << ": " << endl;
            vypisStats(postavyStats[1][0], postavyStats[1][0], postavyStats[1][1], postavyStats[1][1], postavyStats[1][2]);
            break;
        case 2:
            cout << postavy[2] << ": " << endl;
            vypisStats(postavyStats[2][0], postavyStats[2][0], postavyStats[2][1], postavyStats[2][1], postavyStats[2][2]);
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
    int level = 0;
    int penize = 0;

    string monstra[5] = {"Mravenec","Beruska","Slimak","Stonozka","Svab"};
    int monstraStats[5][4] = {{30, 0, 5, 3},{45, 5, 8, 5},{50, 10, 3, 7},{65, 15, 12, 10},{75, 15, 10, 15}}; //HP, EN, AT, XP
    int M1, M2, M3; //monstra

    cout << "BROUKOVOD" << endl;
    postava = volbaPostavy(postavy, postavyStats, maxHP, maxEN, AT);
    vymaxHPEN(maxHP, HP, maxEN, EN);

    M1 = rand()%5;
    M2 = rand()%5;
    M3 = rand()%5;
    int bojPocet = rand()%3;

    bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP, maxEN, XP, penize);
    cout << "Mas " << penize << " zlata." << endl;

    switch(bojPocet){
    case 0:
        bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP, maxEN, XP, penize);
        break;
    case 1:
        bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, maxEN, XP, penize);
        break;
    case 2:
        bojovaSmycka(monstra, monstraStats, M1, M2, M3, HP, EN, AT, maxHP, maxEN, XP, penize);
        break;
    default:
        cout << "chyba" << endl;
        break;
    }
    levelXP(XP, level, AT, maxHP, maxEN);

    return 0;
}
