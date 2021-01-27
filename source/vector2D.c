#include "vector2D.h"

Vector2D createVector2D(float px, float py)
{
    Vector2D res = {px, py};
    return res;
}

float getVector2DLength(Vector2D* vec)
{
    return sqrt((vec->x*vec->x)+(vec->y*vec->y));
}

Vector2D getVector2DNormalized(Vector2D* vec)
{
    float len = getVector2DLength(vec);

    Vector2D res = {vec->x/len, vec->y/len};

    return res;
}

Vector2D getVector2DFromAngleAndLength(float angle, float len)
{
    Vector2D res;
    res.x = cos(angle) * len;
    res.y = sin(angle) * len;
    return res;
}


int sign(float num)
{
    if (num < 0)
        return -1;
    else
        return 1;
}
