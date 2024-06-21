#include "raylib.h"

int main(){
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow( windowWidth, windowHeight, "Game");

    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png"); 
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebpos{windowWidth, windowHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};

    int nebVel{-200};

    Texture2D scarfy = LoadTexture("./textures/scarfy.png");  
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //acceleration due to garvity (pixels/frame)/frame
    const int gravity{1'000};
    bool isInAir{false};
    const int jumpVelocity{-600};//pixels/seconf

    int velocity{0};

    int frame{0};
    float updateTime{1.0/12.0};
    float runningTime{};

    int nebFrame{0};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{};

    SetTargetFPS(60);
    while( !WindowShouldClose() )
    {
        const float dT = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            //rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity //rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        nebpos.x += nebVel * dT;
        neb2Pos.x += nebVel * dT;  

        //update position
        scarfyPos.y += velocity * dT;

        
        if(!isInAir)
        {
            runningTime += dT;
            if( runningTime >= updateTime )
            {
                runningTime = 0.0;
                scarfyRec.x = frame*scarfyRec.width;
                frame++;
                if(frame > 5)
                {
                    frame = 0;
                }
            }
        }

        nebRunningTime += dT;
        if(nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        neb2RunningTime += dT;
        if(neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if(neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }

        DrawTextureRec(nebula, nebRec, nebpos, WHITE);

        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}