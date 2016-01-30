
#include <Rainbowduino.h>

int VrXPin = A0;
int VrYPin = A1;

int PlayerX, PlayerY = 2;
int numberOfEnemies = 3;

// {z, x, y, hangTime}
int enemies[][4] = {{4, 0, 0, 9}, {4, 3, 3, 9}, {4, 0, 3, 9}, {4, 3, 0, 9}, {4, 1, 3, 3}, {4, 1, 3, 3}, {4, 1, 3, 3}, {4, 1, 1, 3}, {4, 3, 3, 3}, {4, 1, 2, 3}};

void setup() {
   Rb.init();
}

void loop() {

  Rb.blankDisplay(); 
  
  movePlayer();
  checkCollision();

  Rb.setPixelZXY(0, PlayerX, PlayerY, 0, 0xFF, 0); //uses R, G and B color bytes
 
  unsigned char e = 0;
  for (e = 0; e <= numberOfEnemies; e++)
  {
    //Hanging time
    enemies[e][3] = enemies[e][3] - 1;
    if (enemies[e][3] < 0)
    {
      if (enemies[e][0] == 0){
        if (numberOfEnemies < 9)
            ++numberOfEnemies;
        createNewEnemy(e); 
      }
   
      enemies[e][0] = enemies[e][0] - 1;
    } 
 
    Rb.setPixelZXY(enemies[e][0], enemies[e][1], enemies[e][2], 0, 0, 0xFF); //uses R, G and B color bytes
  }
  checkCollision();

  delay(100); 
}

void movePlayer()
{
  int VrY = map(analogRead(VrYPin), 0, 1023, -1, 1); 
  int VrX = map(analogRead(VrXPin), 0, 1023, -1, 1);
  
  PlayerX = PlayerX + VrX;
  if (PlayerX > 3)PlayerX = 3;
  if (PlayerX < 0)PlayerX = 0;
  
  PlayerY = PlayerY + VrY;
  if (PlayerY > 3)PlayerY = 3;
  if (PlayerY < 0)PlayerY = 0;
}

void checkCollision()
{
  unsigned char e = 0;
  for (e = 0; e <= numberOfEnemies; e++)
  {
    if (enemies[e][0] == 0 && enemies[e][1] == PlayerX && enemies[e][2] == PlayerY)
    {
      gameOver();
      createNewEnemy(e);
    }
  }
}

void gameOver()
{
  unsigned char x,y,z;
  for(z=0;z<4;z++)
  {
     for(y=0;y<4;y++)
     {
        for(x=0;x<4;x++)
        {
          Rb.setPixelZXY(z,x,y,random(0xFF),random(0xFF),random(0xFF));
          delay(10);
        }
     }
  } 
  numberOfEnemies = 4;
}

void createNewEnemy(int e)
{
    enemies[e][0] = 4;
    enemies[e][1] = random(0, 4);
    enemies[e][2] = random(0, 4);
    enemies[e][3] = random(1, 20);
}

