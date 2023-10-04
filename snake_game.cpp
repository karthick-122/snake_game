#include<iostream>
#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
#include<conio.h>
class cordinates
{
    public:
    int x;
    int y;
    cordinates()
    {

    }
    cordinates(int _y,int _x)
    {
        x =_x;
        y = _y;
    }
};
enum direction{STOP =0,UP,DOWN,LEFT,RIGHT};
class snake_game
{
    int score;
    bool game_over;
    cordinates snake_head;
    cordinates fruit;
    const int with = 40;
    const int height = 20;
    direction dir;
    queue<cordinates> qq;
    vector<vector<int>> snake_positions ;

public:

 void set_score();
 int get_score();
 void set_game_over();
 bool get_game_over();
 void set_random_fruit();
 void print_grid();
 snake_game();
 void get_input();
 void set_direction(direction);
 void logic();



};


void snake_game:: set_score()
{
    score +=10;
}
int snake_game:: get_score()
{
    return score;
}
void snake_game:: set_game_over()
{
    game_over = true;
}
bool snake_game:: get_game_over()
{
    return game_over;
}
void snake_game:: set_random_fruit()
{
    srand(time(0));
    fruit.x = (rand()%with-3)  +2;//1 : with-1
    fruit.y = (rand()%height-3) +2;

}

 snake_game::  snake_game()
 {
        score = 0;
        game_over = false;
        dir = STOP;
        set_random_fruit();
        snake_head.x = with/2;
        snake_head.y = height/2;

        for (int y = 0; y < height; y++)
        {
            vector<int>temp;
            for(int x =0;x<with;x++)
            {

                temp.push_back(0);
            }
            snake_positions.push_back(temp);
        }
        snake_positions[height/2][with/2]=1;
        cordinates temp(height/2,with/2);
        qq.push(temp);


        while(!game_over)
        {
            print_grid();
            _sleep(200);
            get_input();
            logic();
        }
 }


 void  snake_game:: print_grid()
 {
    system("cls");
  // getch();
  // clrscr();

    for(int y = 0;y<height;y++)
    {
        for(int x= 0;x<with;x++)
        {

             if(fruit.x==x&&fruit.y==y)
            {
                cout<<"F";
            }
            else if(x==snake_head.x && y==snake_head.y)
            {
                cout<<"S";
            }
           else if(snake_positions[y][x]==1)
          {
                cout<<"o";
           }
            else if(y==0||y==height-1)
            cout<<"#";
            else if(x==0||x==with-1)
             cout<<"#";
             else
             cout<<" ";
        }
        cout<<endl;
    }

    cout<<"Score : "<<score;

 }

void snake_game:: get_input()
{

    if(_kbhit())
    {
        switch (_getch())
        {
            case '8':
            set_direction(UP);
            break;
            case '5':
            set_direction(DOWN);
            break;
            case '4':
            set_direction(LEFT);
            break;
            case '6':
            set_direction(RIGHT);
            break;
            case ' ':
            set_game_over();
            break;
            case'0':
            set_random_fruit();
            break;
            default :
            break;
        }
    }

}

void snake_game::set_direction(direction d)
{
    if(dir==UP && d==DOWN || dir==DOWN && d==UP || dir == LEFT && d ==RIGHT || dir ==RIGHT && d ==LEFT)
     return;
    dir = d;
}


void snake_game::logic()
{
    switch(dir)
    {
        case UP:
         snake_head.y--;
         break;
        case DOWN:
         snake_head.y++;
         break;
        case LEFT:
         snake_head.x--;
         break;
        case RIGHT:
         snake_head.x++;
         break;
        default:
         break;
    }
    if(snake_head.y<=0||snake_head.y>=height ||snake_head.x<=0||snake_head.x>=with)
    {
        set_game_over();
    }

    if(fruit.x==snake_head.x && fruit.y==snake_head.y)// for tail follow up
    {

        cordinates temp(fruit.y,fruit.x);
        qq.push(temp);
        snake_positions[fruit.y][fruit.x] =1;
        set_score();
         set_random_fruit();
    }
    else
    {

       cordinates erase = qq.front();
         qq.pop();
        snake_positions[erase.y][erase.x] =0;
        erase.x = snake_head.x;
        erase.y = snake_head.y;


     if(snake_positions[snake_head.y][snake_head.x]==1)//if tail is there in current head game over
    {
    cout<<endl<<"---- ho no i hit my tail ----"<<endl;
       set_game_over();
    }



        snake_positions[snake_head.y][snake_head.x] =1;
        qq.push(erase);

    }

    /*if(snake_positions[snake_head.y][snake_head.x]==1)
    {
    cout<<" im im ";
       set_game_over();
    }*/
}


int main()
{
    snake_game snk;
   // snk.print_grid();
    return 0;

}
