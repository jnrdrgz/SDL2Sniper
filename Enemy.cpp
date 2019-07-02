#include "Enemy.h"

Enemy::Enemy(int x, int y, int w, int h, int vel){
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    this->vel = vel;
    active = true;
    last_w = w;
    last_h = h;
    //texture = textureManager["solider.png"]
}

int Enemy::getX(){
    return dst.x;
}

int Enemy::getY(){
    return dst.y;
}

int Enemy::getYmax(){
    return dst.y+last_h;
}
int Enemy::getXmax(){
    return dst.x+last_w;
}

void Enemy::closer(){
    if(!(dst.y > 540)){
        dst.x -= 1;
        dst.y += 1;
        dst.w += 1;
        dst.h += 1;

        last_w += 1;
        last_h += 1;
    }

}

void Enemy::walk(){
                //sh
    if(!(dst.y > 540)){
        dst.x -= vel;
        dst.y += vel;
        dst.w += vel;
        dst.h += vel;

        last_w += vel;
        last_h += vel;
    }
}

void Enemy::mov(int dir){
    if(dir == 1){
        dst.x-=3;
    } else {
        dst.x+=3;
    }
}

void Enemy::go_back(){
    dst.x += 1;
    dst.y -= 1;
    dst.w -= 1;
    dst.h -= 1;

    last_w -= vel;
    last_h -= vel;
}
void Enemy::zoom(){
    last_w = dst.w;
    last_h = dst.h;
    dst.w *= 3;
    dst.h *= 3;
}

void Enemy::dezoom(){
    dst.w = last_w;
    dst.h = last_h;
}

void Enemy::kill(){
    active = false;
    SDL_DestroyTexture(texture); //???
}

void Enemy::update(){
    if(active){
        walk();
    }
}

bool Enemy::isActive(){
    return active;
}

bool Enemy::isInside(Bullet b){
    int bx = b.getx();
    int by = b.gety();

    if(bx > dst.x
    && by > dst.y
    && bx < dst.x + dst.w
    && by < dst.y + dst.h){

        return true;

    }
    return false;
}

bool Enemy::hurt(int &health, int f){
    if(dst.y+dst.h >= 540 && dst.y+dst.h <= 540+dst.h ){
        if(f == 30){
            health--;
        }
        return true;
    }
    return false;
}

void Enemy::draw(SDL_Renderer* r){
//        if(active){
        if(texture != NULL){

        } else {
            SDL_SetRenderDrawColor(r, 0,0,0,255);
            SDL_RenderFillRect(r, &dst);
        }
//        }
}
