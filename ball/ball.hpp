#ifndef BALL_HPP
#define BALL_HPP

class Ball
{

private:
    float x; // x spawn point ball
    float y; // y spawn point ball
    float r; // radius ball

public:
    Ball(float x, float y, float r);
    
    void setX(float x);
    void setY(float y);
    void setR(float r);

    float getX();
    float getY();
    float getR();


};

#endif /* Ball_HPP */