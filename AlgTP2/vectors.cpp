#include "raylib.h"
#include <iostream>
#include "vectors.h"

Vector3 CreateVectorA(Vector3 start, Vector3 sizexyz)
{
    Vector3 vector;

    vector.x = sizexyz.x + start.x;
    vector.y = sizexyz.y + start.y;
    vector.z = sizexyz.z + start.z;

    return vector;
}

Vector3 CreateTemporalVectorB(Vector3& vectorA, Vector3 start)
{
    Vector3 vectorB;

    vectorB.x = vectorA.z + start.x;
    vectorB.y = vectorA.y + start.y;
    vectorB.z = -vectorA.x + start.z;

    return vectorB;
}

Vector3 CreateVectorC(Vector3& vectorA, Vector3& vectorB, const float n, Vector3 start)
{
    Vector3 vectorC;
    float magnitudA = sqrt(pow(vectorA.x, 2) + pow(vectorA.y, 2) + pow(vectorA.z, 2));

    vectorC.x = ((vectorA.y * vectorB.z) - (vectorA.z * vectorB.y));
    vectorC.y = ((vectorA.z * vectorB.x) - (vectorA.x * vectorB.z));
    vectorC.z = ((vectorA.x * vectorB.y) - (vectorA.y * vectorB.x));

    float magnitudC = sqrt(pow(vectorC.x, 2) + pow(vectorC.y, 2) + pow(vectorC.z, 2));

    float normalCX = vectorC.x / magnitudC;
    float normalCY = vectorC.y / magnitudC;
    float normalCZ = vectorC.z / magnitudC;

    magnitudC = (1.0f / n) * magnitudA;

    vectorC.x = magnitudC * normalCX + start.x;
    vectorC.z = magnitudC * normalCZ + start.z;
    vectorC.y = magnitudC * normalCY + start.y;

    return vectorC;
}


Vector3 CreateVectorB(Vector3& vectorA, Vector3& vectorC, Vector3 start)
{
    Vector3 vectorB;
    float magnitudA = sqrt(pow(vectorA.x, 2) + pow(vectorA.y, 2) + pow(vectorA.z, 2));

    vectorB.x = ((vectorA.y * vectorC.z) - (vectorA.z * vectorC.y));
    vectorB.y = ((vectorA.z * vectorC.x) - (vectorA.x * vectorC.z));
    vectorB.z = ((vectorA.x * vectorC.y) - (vectorA.y * vectorC.x));

    float magnitudB = sqrt(pow(vectorB.x, 2) + pow(vectorB.y, 2) + pow(vectorB.z, 2));


    float normalBX = vectorB.x / magnitudB;
    float normalBY = vectorB.y / magnitudB;
    float normalBZ = vectorB.z / magnitudB;


    vectorB.x = magnitudA * normalBX + start.x;
    vectorB.z = magnitudA * normalBZ + start.z;
    vectorB.y = magnitudA * normalBY + start.y;

    magnitudB = sqrt(pow(vectorB.x, 2) + pow(vectorB.y, 2) + pow(vectorB.z, 2));


    return vectorB;
}


Vector3 moveStart(block cube, Vector3 oldStart)
{
    cube.start = oldStart;

    Vector3 newBlockStart;

    newBlockStart = {cube.A.x + cube.B.x + cube.C.x + cube.start.x, cube.A.y + cube.B.y + cube.C.y + cube.start.y, cube.A.z + cube.B.z + cube.C.z + cube.start.z };
   
    return newBlockStart;
}

void drawBlock(Vector3 A, Vector3 B, Vector3 C, Vector3 start)
{
    DrawLine3D(start, A, RED);
    DrawLine3D(start, B, BLUE);
    DrawLine3D(start, C, GREEN);
    DrawLine3D(A, { A.x + C.x - start.x, A.y + C.y - start.y, A.z + C.z - start.z}, WHITE);
    DrawLine3D(C, { A.x + C.x - start.x, A.y + C.y - start.y, A.z + C.z - start.z}, WHITE);
    DrawLine3D(B, { B.x + C.x - start.x, B.y + C.y - start.y, B.z + C.z - start.z }, WHITE);
    DrawLine3D(C, { B.x + C.x - start.x, B.y + C.y - start.y, B.z + C.z - start.z}, WHITE);
    DrawLine3D(A, { A.x + B.x - start.x, A.y + B.y - start.y, A.z + B.z - start.z }, WHITE);
    DrawLine3D({ A.x + C.x - start.x, A.y + C.y - start.y, A.z + C.z - start.z}, { A.x + B.x + C.x - (start.x *2), A.y + B.y + C.y - (start.y * 2), A.z + B.z + C.z - (start.z * 2) }, WHITE);
    DrawLine3D({ A.x + B.x - start.x, A.y + B.y - start.y, A.z + B.z - start.z}, { A.x + B.x + C.x - (start.x *2), A.y + B.y + C.y - (start.y * 2), A.z + B.z + C.z - (start.z * 2) }, WHITE);
    DrawLine3D(B, { A.x + B.x - start.x, A.y + B.y - start.y, A.z + B.z - start.z }, WHITE);
    DrawLine3D({ B.x + C.x - start.x, B.y + C.y - start.y, B.z + C.z - start.z}, { A.x + B.x + C.x - (start.x *2), A.y + B.y + C.y - (start.y * 2), A.z + B.z + C.z - (start.z * 2)}, WHITE);
}

float GetMag(Vector3 vectorStart, Vector3 vectorEnd)
{
    return sqrt(pow(vectorEnd.x - vectorStart.x, 2) + pow(vectorEnd.y - vectorStart.y, 2) + pow(vectorEnd.z - vectorStart.z, 2));
}