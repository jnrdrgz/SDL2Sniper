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

Enemy::Enemy(int x, int y, int w, int h, int vel, SDL_Texture* t){
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    this->vel = vel;
    active = true;
    last_w = w;
    last_h = h;
    texture = t;
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
    //SDL_DestroyTexture(texture); //???
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
    if(dst.y+dst.h >= 540 && dst.y+dst.h <= 540+dst.h && active){
        if(f == 30){
            health--;
            if(health < 0){
                health = 0;
            }
            std::cout << health << std::endl;
        }
        return true;
    }
    return false;
}

void Enemy::set_texture(SDL_Texture* t)
{
    texture = t;
}


void Enemy::draw(SDL_Renderer* r){
//        if(active){
        if(texture != NULL){
            if(active){
                SDL_RenderCopyEx(r, texture, NULL, &dst, 0, 0, SDL_FLIP_NONE);
            } else {
                SDL_RenderCopyEx(r, texture, NULL, &dst, 90, 0, SDL_FLIP_NONE);
            }
        } else {
            SDL_SetRenderDrawColor(r, 0,0,0,255);
            SDL_RenderFillRect(r, &dst);
        }
//        }
}

void Enemy::handle_events(SDL_Event event, Aim aim, Bullet& bullet, Particles& particles){
    switch (event.type)
    {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_w:
                    if(!aim.isAiming()){
                        closer();
                    }
                break;
                case SDLK_d:
                    mov(1);
                break;

                case SDLK_a:
                    mov(0);
                break;
            }

        break;

            case SDL_MOUSEBUTTONDOWN:
                if(!buttonPressed){
                    buttonPressed = true;
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        if(aim.isAiming() == true){
                            zoom();
                        }
                        if(aim.isAiming() == false){
                            dezoom();
                        }
                    }
                    if(event.button.button == SDL_BUTTON_LEFT){
                        if(aim.getBullets() > 0){
                            if(isInside(bullet)){
                                kill();
                                bullet.change_state();

                                //particles.split(event.button.x-10,event.button.y-15,event.button.x+10,enemies[i]->getYmax(), 1,1);
                                particles.split(getX(),getY(),getXmax(),getYmax(), 2,2);

                                particles.activate();
                            }



                        }
                        dezoom();

                    }
                }
            break;


        case SDL_MOUSEBUTTONUP:
            buttonPressed = false;
        break;
    }
}
