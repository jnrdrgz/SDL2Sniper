#include "MenuItem.h"

MenuItem::MenuItem()
{
    //ctor
}


MenuItem::MenuItem(std::string t, unsigned char r, unsigned char b, unsigned char g)
{
    text = t;
    color.r = r;
    color.b = b;
    color.g = g;
    color.a = 0;
}
