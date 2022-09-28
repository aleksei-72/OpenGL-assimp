#include <src/3d/hitbox/HitBox.h>

#include <iostream>

using namespace std;

HitBox::HitBox()
{

}

HitBox::HitBox(string fname)
{
    loadFromFile(fname);
}

int HitBox::loadFromFile(std::string fname)
{
    // @TODO: implement this method
    return 0;
}
