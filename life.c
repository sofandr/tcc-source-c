/*
ѕровер€лось на raylib-4.2.0
D:\bin\tcc>tcc.exe -v 
tcc version 0.9.27 (i386 Windows) 
D:\bin\tcc\tcc.exe -vvv -ID:/bin/tcc/include/raylib42 -llibraylib42 -run life.c

≈сть Ђвселенна€ї, представленна€ в виде квадрата, разбитого на квадратные
же пол€. ѕоле может быть пустым, либо на нЄм может жить клетка.  аждый
Ђденьї игры рассчитываетс€ новое поколение клеток по следующим правилам:

на пустом поле, р€дом с которым ровно 3 живые клетки, зарождаетс€ нова€ клетка;
если у живой клетки есть 2 или 3 живые соседки, эта клетка продолжает жить;
если соседей меньше 2 или больше 3, клетка умирает (от Ђодиночестваї или от ЂперенаселЄнностиї соответственно).
*/

#include <stdio.h>
#include <time.h>
#include <raylib.h>



#define screenWidth 800
#define screenHeight 800
#define rez 10

int life[screenWidth/rez][screenHeight/rez];
int life_new[screenWidth/rez][screenHeight/rez];

int *plife = life[0];
int *plife_new = life_new[0];
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
	SetRandomSeed(time(NULL)); 
	//printf("time(NULL) %d\n", time(NULL));


    for (int k=0; k < ((screenWidth/rez)*(screenHeight/rez)); k++)
    {
    	plife[k] =  GetRandomValue(0, 1);
    	plife_new[k] =  plife[k];
    	//printf("plife %d = %d\n", k, plife[k]);
    }


    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
	

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

             Color color;


/*
             for (int x=rez; x<screenWidth-rez; x+=rez)
             {
             	for (int y=rez; y<screenHeight-rez; y+=rez)
             	{

    	           color.r = GetRandomValue(0, 255); color.g = GetRandomValue(0, 255); color.b = GetRandomValue(0, 255); color.a = 255;
             	   DrawRectangle(x, y, rez, rez, color); 
             	}
             }
*/



			for (int k=0; k<screenWidth/rez; k++)
			{
			life[k][0]     = GetRandomValue(0, 1);  life[k][screenHeight/rez-1]  = GetRandomValue(0, 1);
			life_new[k][0] = GetRandomValue(0, 1);  life_new[k][screenHeight/rez-1]  = GetRandomValue(0, 1);
			}


			for (int j=0; j<screenHeight/rez; j++)
			{
			life[0][j] = GetRandomValue(0, 1);     life[screenWidth/rez-1][j] = GetRandomValue(0, 1);
			life_new[0][j] = GetRandomValue(0, 1); life_new[screenWidth/rez-1][j] = GetRandomValue(0, 1);
			}

             for (int k=1; k<screenWidth/rez; k++)
             {
             	for (int j=1; j<screenHeight/rez; j++)
             	{   
             	
             		int count_life = 0;
             	    // восемь клеток вокруг
             	     count_life = 
             	     life[k-1][j-1] +   
             	     life[k][j-1]   +
             	     life[k+1][j-1] +
             	     life[k+1][j]   +
             	     life[k+1][j+1] +
             	     life[k][j+1]   + 
             	     life[k-1][j+1] + 
             	     life[k-1][j];

             	     //если соседей меньше 2 или больше 3, клетка умирает 
                     //если у живой клетки есть 2 или 3 живые соседки, эта клетка продолжает жить
                     if (life_new[k][j]==1) 
                     {
                        if ( count_life < 2 || count_life > 3) 
                        {
                         life_new[k][j] = 0;
                        }                     
                     }

                     // на пустом поле, р€дом с которым ровно 3 живые клетки, зарождаетс€ нова€ клетка;
                     if (life_new[k][j]==0) 
                     {
                        if ( count_life == 3 ) 
                        {
                         life_new[k][j] = 1;
                        }                     
                     }


              	} 
             }

    for (int k=0; k < ((screenWidth/rez)*(screenHeight/rez)); k++)
    {
    	plife[k] = plife_new[k];
    }


             for (int x=0; x<screenWidth/rez; x++)
             {
             	for (int y=0; y<screenHeight/rez; y++)
             	{   
             	   
             	   if (life[x][y]==1) 
             	   {
               	   color.r = 0; color.g = GetRandomValue(0, 255); color.b = 0; color.a = 255;
             	   DrawRectangle(x*rez, y*rez, rez, rez, color); 
             	   }

             	} 
             }

             //

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        DrawRectangle(4, 4, 100, 40, (Color){0,0,0,255}); 
        DrawFPS(10, 10);
         
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}