#pragma once

#include <math.h>

typedef struct 
{
    float x, y;
} Vector2D;

float getVector2DLength(Vector2D* vec);

int sign(float num);

Vector2D createVector2D(float px, float py);
Vector2D getVector2DNormalized(Vector2D* vec);
Vector2D getVector2DFromAngleAndLength(float angle, float len);
