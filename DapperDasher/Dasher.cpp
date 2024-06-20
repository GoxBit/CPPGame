#include "raylib.h"

int main(){
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow( windowWidth, windowHeight, "Game");

    Texture2D scarfy = LoadTexture("./textures/scarfy.png");  
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfy.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfy.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //acceleration due to garvity (pixels/frame)/frame
    const int gravity{1};
    bool isInAir{false};
    const int jumpVelocity{-22};

    int velocity{0};

    SetTargetFPS(60);
    while( !WindowShouldClose() )
    {
        
        BeginDrawing();
        ClearBackground(RED);

        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            //rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //rectangle is in the air
            //apply gravity
            velocity += gravity;
            isInAir = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }
        
        //update position
        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, BLUE);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}