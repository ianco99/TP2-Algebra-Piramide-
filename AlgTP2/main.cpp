#include "raylib.h"
#include "vectors.h"
#include <iostream>
#include <vector>

void main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "p");

    Camera3D camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f }; 
    camera.target = { 0.0f, 0.0f, 0.0f };      
    camera.up = { 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;   

    Vector3 Position = { 0.0f, 0.0f, 0.0f };
    Vector2 ScreenPosition = { 0.0f, 0.0f };


    SetTargetFPS(60);  

    Vector3 v = { GetRandomValue(0,5),GetRandomValue(0,5), GetRandomValue(0,5)};

    std::vector<block> pyramid;

    block Block;
    Block.start = { 0,0,0 };
    Block.A = CreateVectorA(Block.start, v);
    Block.B = CreateTemporalVectorB(Block.A, Block.start);
    Block.C = CreateVectorC(Block.A, Block.B, 10, Block.start);
    Block.B = CreateVectorB(Block.A, Block.C, Block.start);

    pyramid.push_back(Block);


    float magC = GetMag(Block.start, Block.C);
    float mag = GetMag(Block.start, Block.A);
    float newMag = mag - (magC * 2);

    block cube;
    cube.start = { 0,0,0 };
    cube.C = Block.C;
    cube.A = { (Block.A.x / mag) * magC, (Block.A.y / mag) * magC, (Block.A.z / mag) * magC };
    cube.B = { (Block.B.x / mag) * magC, (Block.B.y / mag) * magC, (Block.B.z / mag) * magC };

    int i = 0;

    while (newMag > magC * 2)
    { 
        mag = GetMag(pyramid[i].start, pyramid[i].A);
        newMag = mag - (magC * 2);

        

        Block.start = moveStart(cube, pyramid[i].start);

        Block.A.x = (((pyramid[i].A.x - pyramid[i].start.x) / mag) * newMag) + Block.start.x;
        Block.A.y = (((pyramid[i].A.y - pyramid[i].start.y) / mag) * newMag) + Block.start.y;
        Block.A.z = (((pyramid[i].A.z - pyramid[i].start.z) / mag) * newMag) + Block.start.z;

        Block.B.x = (((pyramid[i].B.x - pyramid[i].start.x) / mag) * newMag) + Block.start.x;
        Block.B.y = (((pyramid[i].B.y - pyramid[i].start.y) / mag) * newMag) + Block.start.y;
        Block.B.z = (((pyramid[i].B.z - pyramid[i].start.z) / mag) * newMag) + Block.start.z;

        Block.C.x = pyramid[i].C.x + Block.start.x - pyramid[i].start.x;
        Block.C.y = pyramid[i].C.y + Block.start.y - pyramid[i].start.y;
        Block.C.z = pyramid[i].C.z + Block.start.z - pyramid[i].start.z;

        pyramid.push_back(Block);
        i++;
    }

    float area = 0;
    float perimetro = 0;
    float volumen = 0;
  
    for (int i = 0; i < pyramid.size(); i++)
    {
        perimetro += ((GetMag(pyramid[i].start, pyramid[i].A) * 2) + (GetMag(pyramid[i].start, pyramid[i].B)) * 2) * 2;
        perimetro += ((GetMag(pyramid[i].start, pyramid[i].A) * 2) + (GetMag(pyramid[i].start, pyramid[i].C)) * 2) * 4;

        area += (GetMag(pyramid[i].start, pyramid[i].A) * GetMag(pyramid[i].start, pyramid[i].B)) * 2;
        area += (GetMag(pyramid[i].start, pyramid[i].A) * GetMag(pyramid[i].start, pyramid[i].C)) * 4;

        volumen += GetMag(pyramid[i].start, pyramid[i].A) * GetMag(pyramid[i].start, pyramid[i].B) * GetMag(pyramid[i].start, pyramid[i].C);
    }
    

    std::cout << "Area: " << area << std::endl;
    std::cout << "perimetro: " << perimetro << std::endl;
    std::cout << "volumen: " << volumen << std::endl;
    
    while (!WindowShouldClose())        
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        ClearBackground(BLACK);

        ScreenPosition = GetWorldToScreen({ Position.x, Position.y + 2.5f, Position.z }, camera);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        for (int i = 0; i < pyramid.size(); i++)
        {
            drawBlock(pyramid[i].A, pyramid[i].B, pyramid[i].C, pyramid[i].start);
        }

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
       
    }

    
    CloseWindow();
}

