#include <iostream>
#include <ctime>
using namespace std;
int blokUtok=0; //zabraneni damage pristiho tahu monstra
int extraReady[3]={0,0,0}; //monstrum je ready na extra silny utok;
int tokenyEN=3; //tokeny na doplneni EN behem boje, vyuziti nestoji tah
int podZemi=0; //monstrum je pod zemi

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
    int r0 = rand()%2;
    int penize=0;
    if(r0==1){
        int r1 = rand()%11+5;
        penize = r1*Mpocet;
    }
    return penize;
}
void vymaxHPEN(int maxHP, int &HP, int maxEN, int &EN){
    HP = maxHP;
    EN = maxEN;
}
void goonSummon(int goon, string monstrum[], int monstraStats[7][4], string &G, int &maxHPG, int &HPG, int &maxENG, int &ENG, int &ATG, int &XPG){
    G=monstrum[goon];
    maxHPG=monstraStats[goon][0];
    maxENG=monstraStats[goon][1];
    ATG=monstraStats[goon][2];
    XPG=monstraStats[goon][3];
    HPG=maxHPG;
    ENG=maxENG;
}
void goonReset(int goon, string monstrum[], string &G, int &maxHPG, int &HPG, int &maxENG, int &ENG, int &ATG){
    G="empty";
    maxHPG=0;
    maxENG=0;
    ATG=0;
    HPG=maxHPG;
    ENG=maxENG;
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
    HP-=(AT*2);
    EN-=10;
}
void utokHromadny(int AT, int &HP1, int &EN){
    HP1-=AT;
    EN-=5;
}
void utokHromadny(int AT, int &HP1, int &HP2, int &EN){
    HP1-=AT;
    HP2-=AT;
    EN-=5;
}
void utokHromadny(int AT, int &HP1, int &HP2, int &HP3, int &EN){
    HP1-=AT;
    HP2-=AT;
    HP3-=AT;
    EN-=5;
}

int healHP(int x, int &HP, int maxHP, int &EN){
    int rozdil;
    rozdil = maxHP-HP;
    if(rozdil<=x){
        HP+=rozdil;
        return rozdil;
    }else{
        HP+=x;
        return x;
    }
    EN-=5;
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
    if(podZemi>0){
        cout << "Kam?" << endl;
    }else{
        cout << "Na koho?" << endl;
    }
      cout << monstrum1 << " = 1" << endl << monstrum2 << " = 2" << endl << monstrum3 << " = 3" << endl;
        do{
            cin >> target;
        }while(target<1||target>3);
    return target;
}

void tahMonstra(string monstrum[], int M, int &HPM, int maxHPM, int &ENM, int ATM, int &HP, int poradi, int special=1){
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
    if(special==0){
        r1=0;
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
void tahMiniboss(string miniBoss[], string monstrum[], int MB, int G, int kolo,int maxHPMB, int &HPMB, int &ENMB, int maxENMB, int ATMB, int &HP, int &AT, bool &G1, bool &G2){
    if(MB==0){
        cout << endl;
        if(kolo%3==1){
            if((G1==false&&G2==false)&ENMB>=5){
                cout << miniBoss[MB] << " privolava na pomoc monstrum " << monstrum[G] << ".\n";
                G1=true;
                ENMB-=5;
            }else if((G1==true&&G2==false)&ENMB>=5){
                 cout << miniBoss[MB] << " privolava na pomoc 2. monstrum " << monstrum[G] << ".\n";
                G2=true;
                ENMB-=5;
            }else if((G1==false&&G2==true)&ENMB>=5){
                 cout << miniBoss[MB] << " privolava na pomoc 2. monstrum " << monstrum[G] << ".\n";
                G1=true;
                ENMB-=5;
            }else if((HPMB<maxHPMB)&ENMB>=5){
                if((maxHPMB-HPMB)>=5){
                    cout << miniBoss[MB] << "se leci o 5 HP.\n";
                    HPMB+=5;
                }else{
                    cout << miniBoss[MB] << "se leci o " << maxHPMB-HPMB << " HP.\n";
                    HPMB+=(maxHPMB-HPMB);
                }
                ENMB-=5;
            }else{
                cout << miniBoss[MB] << " si dava pauzu.\n";
            }
        }else{
            int rB= rand()%5;
            switch(rB){
            case 0:
            case 1:
            case 2:
            case 3:
                cout << miniBoss[MB] << " utoci silou " << ATMB << ".\n";
                HP-=ATMB;
                break;
            case 4:
                cout << miniBoss[MB] << " se ti vysmiva.\n";
                ENMB+=5;
                break;
            }
        }
        }else{
            if(kolo%2==0){
                cout << miniBoss[MB] << " se schovava pod zemi.\n";
                podZemi++;
            }else{
                cout << miniBoss[MB] << " utoci silou " << ATMB << ".\n";
                HP-=ATMB;
            }
        }
}

void tahHrace1(string monstrum1, int &HPM, int maxHPM, int ENM, int maxENM, int ATM, int &HP, int maxHP, int AT, int &EN, int maxEN){
    int volba=0;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
            cout << "Zobrazit schopnosti = 2" << endl;
            cout << "Pouzit token = 3" << endl;
        do{
            cin >> volba;
        }while(volba<0||volba>3);
        if(volba==0){
            cout << monstrum1 << ": " << endl;
            vypisStats(HPM, maxHPM, ENM, maxENM);
        }else if(volba==3){
            if(tokenyEN>0){
                int t=0;
                if((maxEN-EN)>=5){
                    t=5;
                }else{
                    t=(maxEN-EN);
                }
                EN+=t;
                tokenyEN--;
                cout << "Energie zvysena o " << t << ", zbyva ti " << tokenyEN << " tokenu.\n";
            }else{
                cout << "\nNemas zadne tokeny.\n";
            }
            volba=0;
        }else if(volba==2){
            cout << "\nSilny utok (10 EN) = 4" << endl;
            cout << "Uzdravit se (5 EN) = 5" << endl;
            cout << "Blokovat utok (10 EN) = 6" << endl;
            cout << "Zpet na moznosti = 0" << endl;
        do{
            cin >> volba;
        }while(!(volba==0||volba==4||volba==5||volba==6));
        }
    switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            HPM-=AT;
            break;
        case 4:
            if(EN>=10){
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            utokSilny(AT, HPM, EN);
            }
            else{
            cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 5:
            if(EN>=5){
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, maxHP, EN, maxEN);
            }else{
            cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 6:
            if(EN>=10){
            cout << "Blokujes pristi utok nepratele " << monstrum1 << endl;
            blokUtok++;
            EN-=10;
            }else{
            cout << "Nemas dost energie" << endl;
            volba=0;
            }
            break;
        default:
            break;
        }
    }while(volba==0);
}
void tahHrace2(string monstrum1, string monstrum2, int &HPM1, int maxHPM1, int ENM1, int maxENM1, int ATM1, int &HPM2, int maxHPM2, int ENM2, int maxENM2, int ATM2, int &HP, int maxHP, int AT, int &EN, int maxEN, int &target){
    int volba;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
            cout << "Zobrazit schopnosti = 2" << endl;
            cout << "Pouzit token = 3" << endl;
        do{
            cin >> volba;
        }while(volba<0||volba>3);
        if(volba==0){
            cout << monstrum1 << ": " << endl;
            vypisStats(HPM1, maxHPM1, ENM1, maxENM1, ATM1);
            cout << monstrum2 << ": " << endl;
            vypisStats(HPM2, maxHPM2, ENM2, maxENM2, ATM2);
        }else if(volba==3){
            if(tokenyEN>0){
                int t=0;
                if((maxEN-EN)>=5){
                    t=5;
                }else{
                    t=(maxEN-EN);
                }
                EN+=t;
                tokenyEN--;
                cout << "Energie zvysena o " << t << ", zbyva ti " << tokenyEN << " tokenu.\n";
            }else{
                cout << "\nNemas zadne tokeny.\n";
            }
            volba=0;
        }else if(volba==2){
        cout << "\nSilny utok (10 EN) = 4" << endl;
        cout << "Uzdravit se (5 EN) = 5" << endl;
        cout << "Blokovat utok (10 EN) = 6" << endl;
        cout << "Hromadny utok (5 EN) = 7" << endl;
        cout << "Zpet na moznosti = 0" << endl;
        do{
            cin >> volba;
        }while(!(volba==0||volba==4||volba==5||volba==6||volba==7));
        }

    if(volba==1||volba==4||volba==6){
        if(HPM1>0&&HPM2>0){
            target = volbaTarget(monstrum1, monstrum2);
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
        case 4:
            if(EN>=10){
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            if(target==1){
                utokSilny(AT, HPM1, EN);
            }
            if(target==2){
                utokSilny(AT, HPM2, EN);
            }
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 5:
            if(EN>=5){
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, maxHP, EN, maxEN);
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 6:
            if(EN>=10){
            if(target==1){
                cout << "Blokujes pristi utok nepratele " << monstrum1 << endl;
            }
            if(target==2){
                cout << "Blokujes pristi utok nepratele " << monstrum2 << endl;
            }
            blokUtok++;
            EN-=10;
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 7:
            if(EN>=5){
            cout << "Utocis na vsechny mostra " << AT << "x2" <<endl;
            utokHromadny(AT, HPM1, HPM2, EN);
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        default:
            break;
        }
    }while(volba==0);
}
void tahHrace3(string monstrum1, string monstrum2, string monstrum3, int &HPM1, int maxHPM1, int ENM1, int maxENM1, int ATM1, int &HPM2, int maxHPM2, int ENM2, int maxENM2, int ATM2, int &HPM3, int maxHPM3, int ENM3, int maxENM3, int ATM3, int &HP, int maxHP, int AT, int &EN, int maxEN, int &target){
    int volba;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
            cout << "Zobrazit schopnosti = 2" << endl;
            cout << "Pouzit token = 3" << endl;
        do{
            cin >> volba;
        }while(volba<0||volba>3);
        if(volba==0){
            cout << monstrum1 << ": " << endl;
            vypisStats(HPM1, maxHPM1, ENM1, maxENM1, ATM1);
            cout << monstrum2 << ": " << endl;
            vypisStats(HPM2, maxHPM2, ENM2, maxENM2, ATM2);
            cout << monstrum3 << ": " << endl;
             vypisStats(HPM3, maxHPM3, ENM3, maxENM3, ATM3);
        }else if(volba==3){
            if(tokenyEN>0){
                int t=0;
                if((maxEN-EN)>=5){
                    t=5;
                }else{
                    t=(maxEN-EN);
                }
                EN+=t;
                tokenyEN--;
                cout << "Energie zvysena o " << t << ", zbyva ti " << tokenyEN << " tokenu.\n";
            }else{
                cout << "\nNemas zadne tokeny.\n";
            }
            volba=0;
        }else if(volba==2){
        cout << "\nSilny utok (10 EN) = 4" << endl;
        cout << "Uzdravit se (5 EN) = 5" << endl;
        cout << "Blokovat utok (10 EN) = 6" << endl;
         cout << "Hromadny utok (5 EN) = 7" << endl;
        cout << "Zpet na moznosti = 0" << endl;
        do{
            cin >> volba;
        }while(!(volba==0||volba==4||volba==5||volba==6||volba==7));
        }

    if(volba==1||volba==4||volba==6){
        if(HPM1>0&&HPM2>0&&HPM3>0){
            target = volbaTarget(monstrum1, monstrum2, monstrum3);
        }else if(HPM1>0&&HPM2>0){
            target = volbaTarget(monstrum1, monstrum2);
        }else if(HPM2>0&&HPM3>0){
            target = volbaTarget(monstrum2, monstrum3);
        }else if(HPM1>0&&HPM3>0){
            target = volbaTarget(monstrum1, monstrum3);
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

        case 4:
            if(EN>=10){
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
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 5:
            if(EN>=5){
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, maxHP, EN, maxEN);
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 6:
            if(EN>=10){
            if(target==1){
                cout << "Blokujes pristi utok nepratele " << monstrum1 << endl;
            }
            if(target==2){
                cout << "Blokujes pristi utok nepratele " << monstrum2 << endl;
            }
            if(target==3){
                cout << "Blokujes pristi utok nepratele " << monstrum3 << endl;
            }
            blokUtok++;
            EN-=10;
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 7:
            if(EN>=5){
            cout << "Utocis na vsechny mostra " << AT << "x3" <<endl;
            utokHromadny(AT, HPM1, HPM2, HPM3, EN);
            }else{
                cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        default:
            break;
        }
    }while(volba==0);
}
void tahHraceHLB(string monstrum1, int &HPM, int maxHPM, int ATM, int &HP, int maxHP, int AT, int &EN, int maxEN){
    int volba=0;
    do{
        cout << "\nCo chces udelat?" << endl;
            cout << "Prohlednout nepratele = 0" << endl;
            cout << "Utocit na nepratele = 1" << endl;
            cout << "Zobrazit schopnosti = 2" << endl;
            cout << "Pouzit token = 3" << endl;
        do{
            cin >> volba;
        }while(volba<0||volba>3);
        if(volba==0){
            cout << monstrum1 << ": " << endl;
             cout << "HP: " << HPM << "/" << maxHPM << endl;
        }else if(volba==3){
            if(tokenyEN>0){
                int t=0;
                if((maxEN-EN)>=5){
                    t=5;
                }else{
                    t=(maxEN-EN);
                }
                EN+=t;
                tokenyEN--;
                cout << "Energie zvysena o " << t << ", zbyva ti " << tokenyEN << " tokenu.\n";
            }else{
                cout << "\nNemas zadne tokeny.\n";
            }
            volba=0;
        }else if(volba==2){
            cout << "\nSilny utok (10 EN) = 4" << endl;
            cout << "Uzdravit se (5 EN) = 5" << endl;
            cout << "Blokovat utok (10 EN) = 6" << endl;
            cout << "Zpet na moznosti = 0" << endl;
        do{
            cin >> volba;
        }while(!(volba==0||volba==4||volba==5||volba==6));
        }
    switch(volba){
        case 1:
            cout << "\nUtocis silou " << AT << endl;
            HPM-=AT;
            break;
        case 4:
            if(EN>=10){
            cout << "Utocis silou x2 -> " << AT*2 << endl;
            utokSilny(AT, HPM, EN);
            }
            else{
            cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 5:
            if(EN>=5){
            int x;
            x = healHP(10, HP, maxHP, EN);
            cout << "Uzdravil jsi se o " << x << "HP" << endl;
            vypisStats(HP, maxHP, EN, maxEN);
            }else{
            cout << "Nedostatek energie pro vyuziti schopnosti." << endl;
            volba=0;
            }
            break;
        case 6:
            if(EN>=10){
            cout << "Blokujes pristi utok nepratele " << monstrum1 << endl;
            blokUtok++;
            EN-=10;
            }else{
            cout << "Nemas dost energie" << endl;
            volba=0;
            }
            break;
        default:
            break;
        }
    }while(volba==0);
}

void bojovaSmycka(string monstrum[], int monstraStats[7][4], int M, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    string monstrum1 = monstrum[M];
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
        tahHrace1(monstrum1, HPM, maxHPM, ENM, maxENM, ATM, HP, maxHP, AT, EN, maxEN);

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
    cout << "\nTvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
    kolo++;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM==0){
        int drop = penizeDrop(1);
        cout << "Porazil jsi " << monstrum1  << ". Ziskal jsi " << XPM << " xp a " << drop << " zlata." << endl;
        XP+=XPM;
        penize+=drop;
    }
    }

}
void bojovaSmycka(string monstrum[], int monstraStats[7][4], int M1, int M2, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    string monstrum1 = monstrum[M1];
    string monstrum2 = monstrum[M2];
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
    int kolo = 1;
    if(HP>0){
    cout << "------------------" << "\nUtoci na tebe " << monstrum[M1] << " a " << monstrum[M2] << "\n------------------" << endl;
    extraReady[0]=0;
    extraReady[1]=0;
    while(HP>0&&(HPM1>0||HPM2>0)){
        cout << "KOLO " << kolo << ":" << endl;
        tahHrace2(monstrum1, monstrum2, HPM1, maxHPM1, ENM1, maxENM1, ATM1, HPM2, maxHPM2, ENM2, maxENM2, ATM2, HP, maxHP, AT, EN, maxEN, target);

        if(HPM1<0){
            HPM1=0;
        }
        if(HPM2<0){
            HPM2=0;
        }
        cout << monstrum1 << " ma " << HPM1 << " HP" << endl;
        cout << monstrum2 << " ma " << HPM2 << " HP" << endl;
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
    cout << "\nTvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
    kolo++;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM1==0&&HPM2==0){
        int drop = penizeDrop(2);
        cout << "Porazil jsi " << monstrum1 << " a " << monstrum2  << ". Ziskal jsi " << XPM1+XPM2 << " xp a " << drop << " zlata." << endl;
        XP+=(XPM1+XPM2);
        penize+=drop;
    }
    }
}
void bojovaSmycka(string monstrum[], int monstraStats[7][4], int M1, int M2, int M3, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    string monstrum1 = monstrum[M1];
    string monstrum2 = monstrum[M2];
    string monstrum3 = monstrum[M3];
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
    int kolo = 1;
    if(HP>0){
    cout << "------------------" << "\nUtoci na tebe " << monstrum[M1] << ", " << monstrum[M2] << " a " << monstrum[M3] << "\n------------------" << endl;
    extraReady[0]=0;
    extraReady[1]=0;
    extraReady[2]=0;
    while(HP>0&&(HPM1>0||HPM2>0||HPM3>0)){
        cout << "KOLO " << kolo << ":" << endl;
        tahHrace3(monstrum1, monstrum2, monstrum3, HPM1, maxHPM1, ENM1, maxENM1, ATM1, HPM2, maxHPM2, ENM2, maxENM2, ATM2, HPM3, maxHPM3, ENM3, maxENM3, ATM3, HP, maxHP, AT, EN, maxEN, target);

        if(HPM1<0){
            HPM1=0;
        }
        if(HPM2<0){
            HPM2=0;
        }
        if(HPM3<0){
            HPM3=0;
        }
        cout << monstrum1 << " ma " << HPM1 << " HP" << endl;
        cout << monstrum2 << " ma " << HPM2 << " HP" << endl;
        cout << monstrum3 << " ma " << HPM3 << " HP" << endl;
        if(blokUtok>0){
            if(target==1){
                ATM1=0;
            }
            if(target==2){
                ATM2=0;
            }
            if(target==3){
                ATM3=0;
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
    cout << "\nTvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
    }
    kolo++;
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPM1==0&&HPM2==0){
        int drop = penizeDrop(3);
        cout << "Porazil jsi " << monstrum1 << ", " << monstrum2 << " a " << monstrum3 << ". Ziskal jsi " << XPM1+XPM2+XPM3 << " xp a "  << drop << " zlata." << endl;
        XP+=(XPM1+XPM2+XPM3);
        penize+=drop;
    }
    }
}
void miniBossfight(string miniBoss[], int MBStats[2][5], int MB, string monstrum[], int monstraStats[7][4], int goon, int &HP, int &EN, int AT, int maxHP, int maxEN, int &XP, int &penize){
    int maxHPMB = MBStats[MB][0];
    int maxENMB = MBStats[MB][1];
    int ATMB = MBStats[MB][2];
    int XPMB = MBStats[MB][3];
    int penizeMB = MBStats[MB][4];
    int HPMB = maxHPMB;
    int ENMB = maxENMB;
    string sG1, sG2; //G1 a G2 jsou goons, monstra co muze MB privolat
    bool G1, G2;
    int maxHPG1, HPG1, maxENG1, ENG1, ATG1, XPG1;
    int maxHPG2, HPG2, maxENG2, ENG2, ATG2, XPG2;
    goonReset(goon, monstrum, sG1, maxHPG1, HPG1, maxENG1, ENG1, ATG1);
    goonReset(goon, monstrum, sG2, maxHPG2, HPG2, maxENG2, ENG2, ATG2);
    int target = 1;
    int zabitychGoons=0;
    if(HP>0){
    cout << "------------------" << "\nUtoci na tebe " << miniBoss[MB] << "\n------------------" << endl;
    int kolo=1;
    extraReady[0]=0;
    while((HPMB>0||HPG1>0||HPG2>0)&&HP>0){
        cout << "KOLO " << kolo << ":\n";
        if(HPMB>0){
        tahMiniboss(miniBoss, monstrum, MB, goon, kolo, maxHPMB, HPMB, ENMB, maxENMB, ATMB, HP, AT, G1, G2);
        }
        if(podZemi>0){
            int bossZem = rand()%3+1;
            target = volbaTarget(monstrum[6], monstrum[6], monstrum[6]);
            if(target==bossZem){
                cout << "\nTrefa! Utocis silou " << AT << ".\n";
                HPMB-=AT;
            }else{
                cout << "\nVedle!\n";
            }
            cout << miniBoss[MB] << " leze ze zeme.\n";
            podZemi--;
        }else{

        if(G1==true&&HPG1==0){
            goonSummon(goon, monstrum, monstraStats, sG1, maxHPG1, HPG1, maxENG1, ENG1, ATG1, XPG1);
        }
        if(G2==true&&HPG2==0){
            goonSummon(goon, monstrum, monstraStats, sG2, maxHPG2, HPG2, maxENG2, ENG2, ATG2, XPG2);
        }
        if(HP>0){
            if(HPMB>0&&HPG1==0&&HPG2==0){
                tahHrace1(miniBoss[MB], HPMB, maxHPMB, ENMB, maxENMB, ATMB, HP, maxHP, AT, EN, maxEN);
            }else if(HPMB>0&&HPG1>0&&HPG2==0){
                tahHrace2(miniBoss[MB], sG1, HPMB, maxHPMB, ENMB, maxENMB, ATMB, HPG1, maxHPG1, ENG1, maxENG1, ATG1, HP, maxHP, AT, EN, maxEN, target);
            }else if(HPMB>0&&HPG1==0&&HPG2>0){
                tahHrace2(miniBoss[MB], sG2, HPMB, maxHPMB, ENMB, maxENMB, ATMB, HPG2, maxHPG2, ENG2, maxENG2, ATG2, HP, maxHP, AT, EN, maxEN, target);

            }else if(HPMB>0&&HPG1>0&&HPG2>0){
                tahHrace3(miniBoss[MB], sG1, sG2, HPMB, maxHPMB, ENMB, maxENMB, ATMB, HPG1, maxHPG1, ENG1, maxENG1, ATG1, HPG2, maxHPG2, ENG2, maxENG2, ATG2, HP, maxHP, AT, EN, maxEN, target);
            }else if(HPMB==0&&HPG1>0&&HPG2>0){
                tahHrace2(sG1, sG2, HPG1, maxHPG1, ENG1, maxENG1, ATG1, HPG2, maxHPG2, ENG2, maxENG2, ATG2, HP, maxHP, AT, EN, maxEN, target);
            }else if(HPMB==0&&HPG1>0&&HPG2==0){
                tahHrace1(sG1, HPG1, maxHPG1, ENG1, maxENG1, ATG1, HP, maxHP, AT, EN, maxEN);
            }else{
                tahHrace1(sG2, HPG2, maxHPG2, ENG2, maxENG2, ATG2, HP, maxHP, AT, EN, maxEN);
            }
            if(HPG1<=0&&G1==true){
                zabitychGoons++;
                G1=false;
                goonReset(goon, monstrum, sG1, maxHPG1, HPG1, maxENG1, ENG1, ATG1);
            }
            if(HPG2<=0&&G2==true){
                zabitychGoons++;
                G2=false;
                goonReset(goon, monstrum, sG2, maxHPG2, HPG2, maxENG2, ENG2, ATG2);
            }
        }
        if(HPMB<0){
            HPMB=0;
        }
        if(HPG1<0){
            HPG1=0;
        }
        if(HPG2<0){
            HPG2=0;
        }

        if(HPMB>0){
            cout << miniBoss[MB] << " ma " << HPMB << " HP" << endl;
        }
        if(G1==true){
            cout << sG1 << " ma " << HPG1 << " HP" << endl;
        }
        if(G2==true){
            cout << sG2 << " ma " << HPG2 << " HP" << endl;
        }

        if(blokUtok>0){
            if(target==1){
                ATMB=0;
            }
            if(target==2){
                ATG1=0;
            }
            if(target==3){
                ATG2=0;
            }
            blokUtok--;
        }else{
            ATMB = MBStats[MB][2];
            ATG1 = monstraStats[goon][2];
            ATG2 = monstraStats[goon][2];
        }

        if(HPG1>0){
            tahMonstra(monstrum, goon, HPG1, maxHPG1, ENG1, ATG1, HP, 1, 0);
        }
        if(HPG2>0){
            tahMonstra(monstrum, goon, HPG2, maxHPG2, ENG2, ATG2, HP, 2, 0);
        }
        }
        cout << "\nTvuj stav je nyni: " << endl;
        vypisStats(HP, maxHP, EN, maxEN);
        cout << "------------------" << endl;
        kolo++;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else{
        if(MB==0&&zabitychGoons>0){
            int drop = penizeMB + zabitychGoons;
            cout << "Porazil jsi bosse " << miniBoss[MB] << " a " << zabitychGoons << " " << monstrum[goon] << ". Ziskal jsi " << XPMB+(zabitychGoons*XPG1) << " xp a "  << drop << " zlata." << endl;
            XP+=(XPMB+(zabitychGoons*XPG1));
            penize+=drop;
        }else{
            int drop = penizeMB;
            cout << "Porazil jsi bosse " << miniBoss[MB] << ". Ziskal jsi " << XPMB << " xp a "  << drop << " zlata." << endl;
            XP+=XPMB;
            penize+=drop;
        }
    }
    }
}

void menuPauza(int &HP, int &EN, int AT, int maxHP, int maxEN, int level, int zlato, int postava, string postavy[]){
    if(HP>0){
    int volba;
    cout << "\nCo chces delat?\nOdpocinout si = 0\nZobrazit muj stav = 1\nPokracovat v ceste = 2\n";
    do{
        cin >> volba;
    }while(volba<0||volba>2);
    switch(volba){
    case 0:
        int volba2;
        cout << "HP(0) nebo EN(1)?";
        do{
        cin >> volba2;
        }while(volba2<0||volba2>1);
        if(volba2==0){
            cout << "\nZivoty doplneny.";
            HP = maxHP;
        }else{
            cout << "\nEnergie doplnena.";
            EN = maxEN;
        }
        cout << "\nPokracujes v ceste.\n";
        break;
    case 1:
        cout << "Tvuj stav je:\n" << postavy[postava] << ": level " << level << ", zlato: " << zlato << endl;
        vypisStats(HP, maxHP, EN, maxEN, AT);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, zlato, postava, postavy);
        break;
    case 2:
        cout << "Pokracujes v ceste.\n";
        break;
    default:
        cout << "???\n";
    }
    }
}
void menuObchod(int &HP, int &EN, int &AT, int &maxHP, int &maxEN, int &penize){
    if(HP>0){
    int volba;
    while(volba!=0){
    cout << "\n--OBCHOD-- Mas " << penize << " zlata.\nDoplnit HP a EN(5 zlata) = 1\nZvysit maxHP(8 zlata) = 2\nZvysit maxEN(10 zlata) = 3\nZvysit utok(10 zlata) = 4\nKoupit token energie(5 zlata) = 5\nPokracovat v ceste = 0\n";
    do{
        cin >> volba;
    }while(volba<0||volba>5);
    switch(volba){
    case 1:
        if(penize>=5){
            penize-=5;
            vymaxHPEN(maxHP, HP, maxEN, EN);
            cout << "\nZivoty a energie doplneny.\n";
            cout << "Tvuj stav je nyni:\n";
            vypisStats(HP, maxHP, EN, maxEN);
        }else{
            cout << "\nNa to nemas dost zlata.\n";
        }
        break;
    case 2:
        if(penize>=8){
            penize-=8;
            maxHP+=3;
            cout << "\nMaximalni zivoty zvyseny. Tvoje max zivoty jsou nyni: " << maxHP << endl;

        }else{
            cout << "\nNa to nemas dost zlata.\n";
        }
        break;
    case 3:
        if(penize>=10){
            penize-=10;
            maxEN+=3;
            cout << "\nMaximalni energie zvysena. Tvoje max energie je nyni: " << maxEN << endl;
        }else{
            cout << "\nNa to nemas dost zlata.\n";
        }
        break;
    case 4:
        if(penize>=10){
            penize-=10;
            AT+=3;
            cout << "\nUtok zvysen. Tvuj utok je nyni: " << AT << endl;
        }else{
            cout << "\nNa to nemas dost zlata.\n";
        }
        break;
    case 5:
        if(penize>=5&&tokenyEN<10){
            penize-=5;
            tokenyEN++;
            cout << "\nZiskal si token energie, mas " << tokenyEN << " tokenu. \n";
        }else if(tokenyEN>=10){
            cout << "\nUz mas maximalni pocet tokenu.\n";
        }else{
            cout << "\nNa to nemas dost zlata.\n";
        }
        break;
    case 0:
        cout << "\nPokracujes v ceste.\n";
        break;
    }
    }
    }
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
    int postavyStats[3][3] = {{20, 15, 25},{30, 10, 20},{25, 15, 20}}; //maxHP(zivoty), maxEN(energie), AT(utok)
    int maxHP, maxEN;
    int HP, EN, AT;
    int XP=0;
    int level = 0;
    int penize = 0;

    string monstra[7] = {"Mravenec","Beruska","Slimak","Stonozka","Svab","Vcela", "Zem"};
    int monstraStats[7][4] = {{30, 0, 5, 3},{45, 5, 8, 5},{50, 10, 3, 7},{65, 15, 12, 10},{75, 15, 10, 15},{5, 0, 10, 1},{0, 0, 0, 0}}; //HP, EN, AT, XP
    int M1, M2, M3; //monstra

    string miniBoss[2] = {"Vceli kralovna", "Cerv"};
    int MBStats[2][5] = {{120, 40, 10, 50, 40},{110, 0, 10, 40, 35}}; //HP, EN, AT, XP, zlato
    int MB=1;

    cout << "~BROUKOVOD~~~~" << endl;
    cout << "HP jsou zivoty, EN je energie.\nNa zacatek dostavas 3 tokeny na doplneni energie behem boje.\n\n";
    postava = volbaPostavy(postavy, postavyStats, maxHP, maxEN, AT);
    vymaxHPEN(maxHP, HP, maxEN, EN);
    cout << "\nVydavas se na cestu.\n";

    M1=0;
    bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    M1=rand()%2;
    bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    menuObchod(HP, EN, AT, maxHP, maxEN, penize);

    M1=rand()%2+1;
    M2=rand()%3+1;
    bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    MB=1;
    miniBossfight(miniBoss, MBStats, MB, monstra, monstraStats, 5, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    menuObchod(HP, EN, AT, maxHP, maxEN, penize);

    M1=rand()%2+1;
    bojovaSmycka(monstra, monstraStats, M1, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    M1=rand()%3+1;
    M2=rand()%4+1;
    bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    M1=rand()%3+1;
    M2=rand()%4+1;
    bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    MB=0;
    miniBossfight(miniBoss, MBStats, MB, monstra, monstraStats, 5, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    menuObchod(HP, EN, AT, maxHP, maxEN, penize);

    M1=rand()%2;
    M2=rand()%3+1;
    bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    M1=rand()%2+1;
    M2=rand()%4;
    bojovaSmycka(monstra, monstraStats, M1, M2, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    M1=rand()%2+1;
    M2=rand()%4+1;
    M3=rand()%3+1;
    bojovaSmycka(monstra, monstraStats, M1, M2, M3, HP, EN, AT, maxHP, maxEN, XP, penize);
        levelXP(XP, level, AT, maxHP, maxEN);
        menuPauza(HP, EN, AT, maxHP, maxEN, level, penize, postava, postavy);

    menuObchod(HP, EN, AT, maxHP, maxEN, penize);



    //HLAVNI BOSS
    if(HP>0){

    string hlavniBoss[3] = {"Larvog", "Kokon", "Imago"};
        int maxHPHB = 500;
        int ATHB = 5;
        int XPHB = 100;
        int penizeHB = 100;
        int kolo=1;
        int HPHB = maxHPHB;
        int ATsave = AT;
        int faze=0;
        int jHB=0;
        cout << "------------------" << "\nUtoci na tebe " << hlavniBoss[0] << "\n------------------" << endl;
    while(HP>0&&HPHB>0){
            if(kolo%3==1){
                faze++;
            }
            int rM = rand()%4;
            int rA = rand()%11+10;
            AT=ATsave;
        cout << "KOLO " << kolo << ":\n\n";
        if(HPHB>0){
            switch(kolo){
            case 1: //faze 1
                cout << hlavniBoss[0] << " se rozhlizi.\n";
                cout << hlavniBoss[0] << " utoci silou " << ATHB << endl;
                HP-=ATHB;
                break;
            case 2:
                cout << hlavniBoss[0] << " se na neco chysta.\n";
                cout << hlavniBoss[0] << " utoci silou " << ATHB << endl;
                HP-=ATHB;
                if((maxHPHB-HPHB)>=2){
                    cout << hlavniBoss[0] << " se leci o 2HP\n";
                }
                break;
            case 3:
                cout << hlavniBoss[0] << " roste.\n";
                cout << hlavniBoss[0] << " utoci silou " << ATHB << endl;
                HP-=ATHB;
                if((maxHPHB-HPHB)>=2){
                    cout << hlavniBoss[0] << " se leci o 2HP\n";
                }
                break;
            case 4://faze 2
                cout << hlavniBoss[0] << " utoci silneji.\n";
                if(rM==0){
                    cout << hlavniBoss[0] << " utoci silou 2x" << ATHB*2 << " = " << ATHB*4 << endl;
                    HP-=(4*ATHB);
                }else{
                    cout << hlavniBoss[0] << " utoci silou " << ATHB*2 << endl;
                    HP-=(2*ATHB);
                }
                break;
            case 5:
                cout << hlavniBoss[0] << " se smeje.\n";
                if(rM==0){
                    cout << hlavniBoss[0] << " utoci silou 2x" << ATHB*2 << " = " << ATHB*4 << endl;
                    HP-=(4*ATHB);
                }else{
                    cout << hlavniBoss[0] << " utoci silou " << ATHB*2 << endl;
                    HP-=(2*ATHB);
                }
                break;
            case 6:
                cout << hlavniBoss[0] << " roste.\n";
                if(rM==0){
                    cout << hlavniBoss[0] << " utoci silou 2x" << ATHB*2 << " = " << ATHB*4 << endl;
                    HP-=(4*ATHB);
                }else{
                    cout << hlavniBoss[0] << " utoci silou " << ATHB*2 << endl;
                    HP-=(2*ATHB);
                }
                break;
            case 7://faze 3
                cout << hlavniBoss[0] << " ma jedovaty utok (permanentni damage).\n";
                cout << hlavniBoss[0] << " utoci silou " << ATHB*2 << endl;
                HP-=(2*ATHB);
                maxHP-=(2*ATHB);
                break;
            case 8:
                cout << hlavniBoss[0] << " se raduje.\n";
                cout << hlavniBoss[0] << " utoci silou " << ATHB*2 << endl;
                HP-=(2*ATHB);
                maxHP-=(2*ATHB);
                break;
            case 9:
                cout << hlavniBoss[0] << " se na neco chysta.\n";
                cout << hlavniBoss[0] << " utoci silou " << ATHB*2 << endl;
                HP-=(2*ATHB);
                maxHP-=(2*ATHB);
                break;
            case 10://faze 4
                cout << hlavniBoss[0] << " je nyni " << hlavniBoss[1] << ".\n";
                jHB=1;
                AT=0;
                break;
            case 11:
                cout << hlavniBoss[1] << " se nehybe.\n";
                AT=0;
                break;
            case 12:
                cout << hlavniBoss[1] << " se chechta.\n";
                AT=0;
                break;
            case 13://faze 5
                cout << "Z " << hlavniBoss[1] << "u se stava " << hlavniBoss[2] << "!\n";
                cout << hlavniBoss[2] << " utoci silou 3x" << rA << " = " << 3*rA << endl;
                HP-=(3*rA);
                jHB=2;
                break;
            default:
                cout << hlavniBoss[2] << " utoci silou 3x" << rA << " = " << 3*rA << endl;
                HP-=(3*rA);
                break;
            }
        }
        if(HP>0){
        tahHraceHLB(hlavniBoss[jHB], HPHB, maxHPHB, ATHB, HP, maxHP, AT, EN, maxEN);
        }
        if(HPHB<0){
            HPHB=0;
        }
        if(HP<0){
            HP=0;
        }
        if(maxHP<0){
            maxHP=0;
        }
        cout << hlavniBoss[0] << " ma " << HPHB << " HP" << endl;
        if(blokUtok>0){
            ATHB = 0;
            blokUtok--;
        }else{
            ATHB = 5;
        }
        cout << "\nTvuj stav je nyni: " << endl;
    vypisStats(HP, maxHP, EN, maxEN);
    cout << "------------------" << endl;
        kolo++;
    }
    if(HP==0){
        cout << "Prohral jsi.";
    }else if(HPHB==0){
        int drop = penizeHB;
        cout << "Porazil jsi " << hlavniBoss[jHB]  << ". Ziskal jsi " << XPHB << " xp a " << drop << " zlata." << endl;
        XP+=XPHB;
        penize+=drop;
        cout << "Konec hry! Vyhral jsi :)" << endl;
    }
    }

    /*switch(bojPocet){
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
    }*/

    return 0;
}
