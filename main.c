#include "raylib.h"

#define SCREENWIDTH 1600
#define SCREENHEIGHT 900

int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Flappy");
    SetTargetFPS(60);
    
    int frame = 60;
    
    int user_x = 400;
    int user_y = 50;
    
    int jump_height = 0;
    
    int lines[1000] = {0};
    
    bool jumping = false;
    
    bool gameover = false;
    
    Vector2 block[1000];
    
    int block_y[1000] = {0};
    
    int current_block = 0;
    
    int score = 0;
    
    while(!WindowShouldClose())
    {   
        
        if(frame == 60)
        {
            frame = 0;
            block[current_block].x = 0;
            block_y[current_block] = GetRandomValue(-450, -150);
            block[current_block].y = block_y[current_block];
            lines[current_block]++;
            current_block++;
        }
        
        frame++;
        
        
        if(!gameover)
        {
            if(IsKeyPressed(KEY_SPACE))
            {
                jumping = true;
                
                jump_height = 3;
            }
            if(jumping && jump_height < 10)
            {
                jump_height++;
            }
            else
            {
                jumping = false;
                jump_height--;
            }
            user_y -= jump_height;
            
            for(int i = 0; i < current_block; i++)
            {
                block[i].x -= 4;
            }
            
            score = current_block - 5;
            if(score < 0)
            {
                score = 0;
            }
        }
        
        if(user_y >= 850 || user_y <= 0)
        {
            gameover = true;
        }
        
        
        if(user_y >= 850)
        {
            user_y = 850;
        }
        
        for(int i = 0; i <= block_y[score - 1]+600; i++)
        {
            if(user_y == i && block[score - 1].x <= -1150 && block[score - 1].x >= -1300)
            {
                gameover = true;
            }
        }
        
        for(int i = block_y[score - 1]+800; i <= 900; i++)
        {
            if(user_y == i && block[score - 1].x <= -1150 && block[score - 1].x >= -1300)
            {
                gameover = true;
            }
        }
        
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            for(int i = 0; i < current_block; i++)
            {
                DrawRectangleV((Vector2){block[i].x + 1600, block[i].y - 750}, (Vector2){100, 1350}, GREEN);
                DrawRectangleV((Vector2){block[i].x + 1600, block[i].y + 850}, (Vector2){100, 1000}, GREEN);
                DrawText(TextFormat("score : %d", score), 50, 50, 50, BLACK);
            }
            
            if(!gameover)
            {
                DrawRectangle(user_x, user_y, 50, 50,  SKYBLUE);
            }
            else
            {            
                DrawRectangle(user_x, user_y, 50, 50, RED);
            }
            
        EndDrawing();
    }
    
    return 0;
}