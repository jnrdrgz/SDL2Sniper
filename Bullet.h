#ifndef BULLET_H
#define BULLET_H


class Bullet
{
public:
    Bullet(){active = false;}
    void setxy(int x, int y){this->x = x; this->y = y;}
    int getx(){return x;}
    int gety(){return y;}
    void change_state(){active=!active;}
    bool isActive(){return active;}
private:
    int x=0,y=0;
    bool active;
};

#endif // BULLET_H
