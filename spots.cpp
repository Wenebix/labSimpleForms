#include "spots.h"
#include "math.h"
#include <QRandomGenerator>
#include <QVector>
using namespace std;
Spots::Spots()
{
    startGame();
}

int Spots::getItem(int i, int j) {
    return table[i][j];
}

int Spots::getEmptyX() const {
    return emptyX;
}

int Spots::getEmptyY() const {
    return emptyY;
}

void Spots::startGame() {
    QRandomGenerator *tmp = QRandomGenerator::global();
    vector <bool> t(16, 0);
    countMovings = 0;
    vector <int> check;
    for(int i = 0;i<4;i++) {
        for(int j = 0; j<4;j++) {
            while(true) {
                int temp = tmp->bounded(0,16);
                if (!t[temp]) {
                    t[temp] = 1;
                    table[i][j]=temp;
                    cpytable[i][j]=temp;
                    if (temp) {
                        check.push_back(temp);
                    } else {
                        setEmptyX(i);
                        setEmptyY(j);
                        copyX = i;
                        copyY = j;
                    }
                    break;
                }
            }
        }
    }
    int cnt=0;
    for(int i = 0; i<check.size();i++) {
        for(int j=i+1;j<check.size();j++) {
            if (check[i]>check[j]) cnt++;
        }
    }
    cnt+=getEmptyX()+1;
    if (cnt%2!=0) {
        startGame();
    }

}

void Spots::setEmptyX(int i) {
    emptyX = i;
}

void Spots::setEmptyY(int j) {
    emptyY=j;
}

void Spots::reCalc(int i, int j) {
    if (i>3 || i<0 || j > 3 || j < 0) {
        return;
    }
    if (abs(i-getEmptyX())+abs(j-getEmptyY())==1) {
      table[emptyX][emptyY]=table[i][j];
      table[i][j]=0;
      setEmptyX(i);
      setEmptyY(j);
      countMovings++;
    }
}

int Spots::getMoves() const {
    return countMovings;
}
bool Spots::isFinished() {
    int cnt = 1;
    for(int i = 0;i <4; i++) {
        for(int j= 0;j<4;j++) {
            if (cnt==16 && table[i][j]==0) {
                return true;
            }
            if (table[i][j]!=cnt) {
                return false;
            }
            cnt++;
        }
    }
    return true;
}

void Spots::restartGame() {
    for(int i = 0; i<4; i++) {
        for ( int j = 0; j<4; j++) {
            table[i][j]=cpytable[i][j];
        }
    }
    emptyX = copyX;
    emptyY = copyY;
    countMovings = 0;
}

void Spots::nullMovings()
{
    countMovings = 0;
}

