//
// Created by lowIQ on 2021-06-18.
//

#ifndef BOMBERMAN_VECTOR2D_H
#define BOMBERMAN_VECTOR2D_H

#include <iostream>

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);
    Vector2D& operator=(const Vector2D& vec);

    Vector2D& operator*(const int& i);

    Vector2D& Zero();
    int Normalize(int var);


    friend std::ostream& operator<<(std::ostream& stream, const Vector2D vec);

};

#endif //BOMBERMAN_VECTOR2D_H
