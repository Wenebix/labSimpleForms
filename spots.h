#ifndef SPOTS_H
#define SPOTS_H


class Spots
{
public:
    Spots();
    void startGame();
    bool isFinished();
    int getItem(int i,int j);
    int getEmptyX() const;
    int getEmptyY() const;
    void reCalc(int i, int j);
    void setEmptyX(int i);
    void setEmptyY(int j);
    void restartGame();
    void nullMovings();
    int getMoves() const;
private:
    int emptyX;
    int emptyY;
    int table[4][4];
    int cpytable[4][4];
    int copyX;
    int copyY;
    int countMovings;
};

#endif // SPOTS_H
