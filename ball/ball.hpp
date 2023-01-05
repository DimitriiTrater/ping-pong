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
    
    void SetX(float x);
    void SetY(float y);
    void SetR(float r);

    float GetX();
    float GetY();
    float GetR();


};

#endif /* Ball_HPP */