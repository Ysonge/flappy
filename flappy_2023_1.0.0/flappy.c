#include "raylib.h"

struct user {
    int x;
    int y;
    int score;
} user;

struct block {
    int x;
    int y;
} block;

int main (void) {
    
    const int ScreenWidth = 1920;
    const int ScreenHeight = 1080;
    
    InitWindow(ScreenWidth, ScreenHeight, "flappy");
    SetTargetFPS(60);
    
    ToggleFullscreen();
    
    user.x = 192;
    user.y = 490;
    user.score = 0;
    
    Image ball = LoadImage("resources/point.png");
    Texture2D point = LoadTextureFromImage(ball);
    UnloadImage(ball);
    
    struct block blocks[10000] = {0};
    
    int gravity = 0;
    
    bool gameover = false;
    
    int frame = 0;
        
    int counting = 0;
    
    while(frame < 180) {
        BeginDrawing();
            
            ClearBackground(RAYWHITE);

            if(frame < 60) {
                DrawText("3", 910, 490, 100, BLACK);
            } else if(frame < 120) {
                DrawText("2", 910, 490, 100, BLACK);
            } else {
                DrawText("1", 910, 490, 100, BLACK);
            }
            
        EndDrawing();   
    
        frame++;
        
    }
        
    frame = 0;
    
    while(!WindowShouldClose() && !gameover){
    
        frame++;
        if(119 < frame && counting <= 9999){
            frame = 0;
            blocks[counting].x = 1920;
            blocks[counting].y = GetRandomValue(100,  980);
            counting++;
        }
        for (int i = 0; i < counting; i++) {
            blocks[i].x -= 5;
        }
        
        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            gravity = 20;
        }
        else {
            gravity -= 2;
        }
        
        user.y -= gravity;
        
        if(user.y <= 0) {
            user.y = 0;
            gameover = true;
        }
        if(980 <= user.y) {
            user.y = 980;
            gameover = true;
        }
        
        for (int i = 0; i < counting; i++) {
            if(user.x <= blocks[i].x && user.y<= blocks[i].y && user.x + 100 >= blocks[i].x && user.y + 100 >= blocks[i].y ) {
                user.score++;
                blocks[i].x = -50;
                blocks[i].y = -50;
            }
        }
        
        if(user.score == 10000) {
            break;
        }
        
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            
            DrawText(TextFormat("score : %i", user.score), 10, 10, 100, BLACK);
            
            for(int i = 0; i < counting; i++) {
                if(counting <= 9999) {
                    DrawTexture(point, blocks[i].x, blocks[i].y, WHITE);
                } else {
                    DrawTexture(point, blocks[i].x, blocks[i].y, RED);
                }
            }
            
            DrawRectangle(user.x, user.y, 100, 100, BLACK);
            
        EndDrawing();
        
    }
    
    while(!WindowShouldClose()){
        
        BeginDrawing();
    
            ClearBackground(RAYWHITE);
            
            if(user.score == 10000) {
                DrawText("YOU WIN", 740, 440, 100, BLACK);
            } else {
                
                DrawRectangle(user.x, user.y, 100, 100, RED);
                
                for(int i = 0; i < counting; i++) {
                    if(counting <= 9999) {
                        DrawTexture(point, blocks[i].x, blocks[i].y, WHITE);
                    } else {
                        DrawTexture(point, blocks[i].x, blocks[i].y, RED);
                    }
                }
                
                DrawText(TextFormat("your score : %i", user.score), 640, 440, 100, BLACK);
                
            }
        
        EndDrawing();
        
    }
    
}