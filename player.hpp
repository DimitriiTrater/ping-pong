#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
private:
    float x;
    float y;
    float w;
    float h;
public:
    Player(float x, float y);
    void setX(float x);
    void setY(float y);

    float getX();
    float getY();

};
#endif /* PLAYER_HPP */