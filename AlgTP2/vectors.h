#pragma once
#include "raylib.h"

struct block
{
    Vector3 start;
    Vector3 A;
    Vector3 B;
    Vector3 C;

};

Vector3 CreateVectorB(Vector3& vectorA, Vector3& vectorC, Vector3 start);

Vector3 CreateTemporalVectorB(Vector3& vectorA, Vector3 start);

Vector3 CreateVectorC(Vector3& vectorA, Vector3& vectorB, const float n, Vector3 start);

Vector3 CreateVectorA(Vector3 start, Vector3 sizexyz);

Vector3 moveStart(block cube, Vector3 oldC);

void drawBlock(Vector3 A, Vector3 B, Vector3 C, Vector3 start);

float GetMag(Vector3 vectorStart, Vector3 vectorEnd);