#include <iostream>
#include <ctime>
using namespace std;

int generujDamage(){
    int damage = rand()%11+10;
    return damage;
}
void vypisHealth(int hp){
    cout << "HP: " << hp << endl;
}
void bojovaSmycka(int &HP, int HPenemy1){
    cout << "Hrac: " << HP << ", Nepritel: " << HPenemy1 << endl;
    while(HP>0){
        HP-=generujDamage();
        if(HP<0){
            HP=0;
        }
        cout << "Hrac: ";
        vypisHealth(HP);
        if(HP==0){
            cout << "PROHRA";
        }else{
            HPenemy1-=generujDamage();
            if(HPenemy1<0){
                HPenemy1=0;
        }
        cout << "Nepritel: ";
        vypisHealth(HPenemy1);
        if(HPenemy1==0){
            cout << "VYHRA";
            break;
        }
        }
    }
}

int main(){
    srand(time(0));
    int HP = 100; //hrac
    int HPenemy1 = 80; //enemy1

    bojovaSmycka(HP, HPenemy1);
    if(HP>0){
        cout << "\nHracovi zbylo " << HP << " zivotu.";
    }
    return 0;
}

