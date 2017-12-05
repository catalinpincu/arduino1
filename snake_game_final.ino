#include <LiquidCrystal.h>
#include <LedControl.h>
#define DATA_IN 10
#define CLK 8
#define LOAD 9
#define RS 12
#define E 11
#define DIG4 5
#define DIG5 4
#define DIG6 3
#define DIG7 2
#define SW 6
#define TIER_1 6
#define TIER_2 12
#define TIER_3 24
int score;
int level;
int snakeLength;
LedControl lc=LedControl (DATA_IN, CLK, LOAD, 0);
LiquidCrystal lcd (RS,E,DIG4,DIG5,DIG6,DIG7);
struct point{//structura cu care memorez pozitia snake-ului
  int x,y;
  inline bool operator == (point a)
  {
    if (a.x==x && a.y==y)
    return true;
    return false;
  }
  inline bool operator != (point a)
  {
    if (a.x!=x || a.y!=y)
    return true;
    return false;
  }
  inline point operator = (point a)
  {
    x=a.x;
    y=a.y;
    return a;
  }
}matrix[63],UP,DOWN,LEFT,RIGHT,currentDirection,food;

void showSnake ()//aprinde led-urile matricei dupa coordonatele date
{
    for (int i=0;i<snakeLength;i++)
      lc.setLed(0,matrix[i].x,matrix[i].y,true);
}

void gameStart ()//meniul initial in care se apasa pt a incepe jocul
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome to snake!");
    lcd.setCursor(0,1);
    lcd.print("Press to play!");
    while (digitalRead(SW))//astept input ca sa inceapa
      {}
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("     Score:");
}
point directionChanged (int xInput,int yInput,bool &change)//se verifica directia de miscare primita ca input si daca este valida 
{
    //Serial.println("entered function");
    point newDirection;
    if (xInput>600)
      {
          //Serial.println("right");
          newDirection=RIGHT;
          if (currentDirection==LEFT)
            change=false;
          else change=true;
          return newDirection;
      }
    if (xInput<400)
      {
          //Serial.println("left");
          newDirection=LEFT;
          if (currentDirection==RIGHT)
            change=false;
          else change=true;
          return newDirection;
      }
    if (yInput>600)
      {
          //Serial.println("up");
          newDirection=UP;
          if (currentDirection==DOWN)
            change=false;
          else change=true;
          return newDirection;
      }
    if (yInput<400)
      {
          //Serial.println("down");
          newDirection=DOWN;
          if (currentDirection==UP)
            change=false;
          else change=true;
          return newDirection;
      }
      change=true;
      return currentDirection;
}
bool checkCollision ()
{
    for (int i=1;i<snakeLength;i++)
        if (matrix[0]==matrix[i])
            return true;
    return false;           
}
bool checkEaten ()
{
    if (matrix[0]==food)
      {
        score++;
        return true;
      }
    return false;
}
bool checkCoordinates(point foodAux)
{
     for (int i=0;i<snakeLength;i++)
        if (matrix[i]==foodAux)
             return false;
     return true;     
}
void showFood()
{
    lc.setLed(0,food.x,food.y,true);
}
void generateFood()
{
    food.x=random(8);
    food.y=random(8);
    while (!checkCoordinates(food))
    {
      food.x=random(8);
      food.y=random(8);
    }
}
void setup() {
    randomSeed(analogRead(0));//asigurare ca este random
    pinMode(SW,INPUT);
    digitalWrite(SW,HIGH);
    Serial.begin(9600);
    lcd.begin(16,2);
    lc.shutdown(0,false);
    lc.setIntensity(0,8);
    lc.clearDisplay(0);
    score=0;
    snakeLength=3;
    level=1;
    UP.x=0;//setare directii
    UP.y=1;
    DOWN.x=0;
    DOWN.y=-1;
    LEFT.x=1;
    LEFT.y=0;
    RIGHT.x=-1;
    RIGHT.y=0;
    matrix[0].x=0;
    matrix[0].y=2;
    matrix[1].x=0;
    matrix[1].y=1;
    matrix[2].x=0;
    matrix[2].y=0;
    currentDirection=UP;
    gameStart();
    showSnake();
    generateFood();//creare cu rand a coordonatelor mancarii si verificare
    showFood();//afisarea mancarii
}
void addNewBrick()//adaugarea unei noi bucati in coada snake-ului - 4 cazuri
{
    if (currentDirection==DOWN)
    {
        matrix[snakeLength].x=matrix[snakeLength-1].x;
        matrix[snakeLength].y=matrix[snakeLength-1].y+1;
    }
    if (currentDirection==UP)
    {
        matrix[snakeLength].x=matrix[snakeLength-1].x;
        matrix[snakeLength].y=matrix[snakeLength-1].y-1;
    }
    if (currentDirection==LEFT)
    {
        matrix[snakeLength].x=matrix[snakeLength-1].x-1;
        matrix[snakeLength].y=matrix[snakeLength-1].y;
    }
    if (currentDirection==RIGHT)
    {
        matrix[snakeLength].x=matrix[snakeLength-1].x+1;
        matrix[snakeLength].y=matrix[snakeLength-1].y;
    }
    snakeLength++;
}
void restart()//repornire joc
{
    lc.clearDisplay(0);
    score=0;
    snakeLength=3;
    level=1;
    UP.x=0;
    UP.y=1;
    DOWN.x=0;
    DOWN.y=-1;
    LEFT.x=1;
    LEFT.y=0;
    RIGHT.x=-1;
    RIGHT.y=0;
    matrix[0].x=0;
    matrix[0].y=2;
    matrix[1].x=0;
    matrix[1].y=1;
    matrix[2].x=0;
    matrix[2].y=0;
    currentDirection=UP;
    gameStart();
    showSnake();
    generateFood();
    showFood();
}
void gameEnd ()//se termina jocul - afisare tier + scor + optiunea de revenire la meniu
{
    bool nextGame;
    lc.clearDisplay(0);
    //Serial.println(digitalRead(SW));
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Your score was");
    lcd.print(score);
    lcd.setCursor(0,0);
    lcd.print("Game ended!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Your tier:");
    lcd.setCursor(0,1);
    if (snakeLength<=TIER_1)
    lcd.print("Begginer!");
    else if (snakeLength>TIER_1 && snakeLength<=TIER_2)
    lcd.print("Expert!");
    else if (snakeLength>TIER_2 && snakeLength<=TIER_3)
    lcd.print("Godlike!");
    else if (snakeLength>TIER_3)
    lcd.print("Legendary!");
    delay(3000);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Press to");
    lcd.setCursor(3,1);
    lcd.print("play again");
    while(digitalRead(SW)){}
    delay(2000);
    restart();
}
void loop() {
  // put your main code here, to run repeatedly:
     lcd.setCursor(7,1);
     lcd.print(score);
     point direction;
     point newDirection;
     bool valid;
     int xInput=analogRead(A4);
     int yInput=analogRead(A5);
     //Serial.print ("x= ");
     //Serial.println (xInput);
     //Serial.print("y= ");
     //Serial.println (yInput);
     newDirection=directionChanged(xInput,yInput,valid);
     if (valid && newDirection!=currentDirection)
          currentDirection=newDirection;
     for (int i=snakeLength-1;i>0;i--)
     matrix[i]=matrix[i-1];
     matrix[0].x+=currentDirection.x;
     matrix[0].y+=currentDirection.y;
     if (matrix[0].x<0)
     matrix[0].x=7;
     if (matrix[0].x>7)
     matrix[0].x=0;
     if (matrix[0].y<0)
     matrix[0].y=7;
     if (matrix[0].y>7)
     matrix[0].y=0;
     if (checkEaten())
     {
        generateFood();
     }
     if (checkCollision())
        gameEnd();
     if (score/5>level-1)
     {
        level++;
        addNewBrick();
     }
     //Serial.println(level);
     lc.clearDisplay(0);
     showFood();
     showSnake();
     delay(60*(11-level));
}
