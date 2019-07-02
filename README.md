# SDL2ZombieSniper

I tried to make a horizon perspective in 2D with SDL2. For some reason it work fine in windows but very slow in linux (when you aim)

Later I'm going to write a makefile, for now to play it just put this in the console:
```
g++ -lSDL2 -lSDL2_image -lSDL2_ttf  Bullet.h Enemy.h Game.hpp Particles.cpp Bullet.cpp Enemy.cpp Game.cpp Particles.h main.cpp
``` 
