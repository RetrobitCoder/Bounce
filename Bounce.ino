/*
  Pong like game where you play as two dogs chasing a ball
  that is bounced back and forth.

  setup function is at the top, loop function is at the bottom

  author: Zachariah Falgout
*/
#include <Arduboy.h>
#include "bitmaps.h"

#define PAUSED 1
#define PLAY 2
#define RESET 3
#define MENU 4
#define CREDITS 5
#define OPTIONS 6
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 20
#define BALL_RADIUS 2
#define CORGI_PADDLE 1
#define DASCH_PADDLE 2
#define DOG_PADDLE 3

byte paddle1 = DOG_PADDLE;
byte paddle2 = DOG_PADDLE;
byte x1 = 0;
byte x2 = WIDTH-PADDLE_WIDTH;
byte y1 = 20;
byte y2 = 20;
byte pDir1 = 1;
byte pDir2 = 1;
byte ballX = WIDTH/2;
byte ballY = HEIGHT/2;
byte xDir = 0;
byte yDir = 0;
byte bSpeed = 1;
byte p1Score = 0;
byte p2Score = 0;
bool start = false;
byte menuSelect = 1;
byte optionSelect = 1;
byte opt1 = 0;
byte opt2 = 0;
byte opt3 = 0;
byte pause_key = 0;
unsigned char state = PLAY;
unsigned int hits = 0;
unsigned int sound[] = {256, 2048};
bool soundOn = true;

Arduboy ab;

//initial setup
void setup() 
{
  ab.begin();
  ab.initRandomSeed();
  ab.audio.on();
  ab.tunes.initChannel(PIN_SPEAKER_1);
  ab.tunes.initChannel(PIN_SPEAKER_2);

  state = MENU;
  drawMenu();
}

//draw the options screen, and recording which options are selected
void drawOptions()
{
  ab.clear();
  ab.setCursor(WIDTH/2-24, 1);
  ab.print("Paddle1");
  ab.setCursor(10, 11);
  ab.print("Dog Corgi Dasch");
  ab.setCursor(WIDTH/2-24, 21);
  ab.print("Paddle2");
  ab.setCursor(10, 31);
  ab.print("Dog Corgi Dasch");
  ab.setCursor(0, 41);
  ab.print("Sound:");
  ab.setCursor(38, 41);
  ab.print("ON   OFF");
  ab.setCursor(WIDTH/2-30, 55);
  ab.print("B to exit");

  switch(optionSelect)
  {
    case 1:
      ab.drawRect(8, 9, 21, 12, WHITE);
      break;
    case 2:
      ab.drawRect(31, 9, 33, 12, WHITE);
      break;
    case 3:
      ab.drawRect(67, 9, 34, 12, WHITE);
      break;
    case 4:
      ab.drawRect(8, 29, 21, 12, WHITE);
      break;
    case 5:
      ab.drawRect(31, 29, 33, 12, WHITE);
      break;
    case 6:
      ab.drawRect(67, 29, 34, 12, WHITE);
      break;
    case 7:
      ab.drawRect(36, 39, 15, 12, WHITE);
      break;
    case 8:
      ab.drawRect(66, 39, 21, 12, WHITE);
      break;
  }

  switch(opt1)
  {
    case 1:
      ab.drawRect(8, 9, 21, 12, WHITE);
      break;
    case 2:
      ab.drawRect(31, 9, 33, 12, WHITE);
      break;
    case 3:
      ab.drawRect(67, 9, 34, 12, WHITE);
      break;
  }

  switch(opt2)
  {
    case 1:
      ab.drawRect(8, 29, 21, 12, WHITE);
      break;
    case 2:
      ab.drawRect(31, 29, 33, 12, WHITE);
      break;
    case 3:
      ab.drawRect(67, 29, 34, 12, WHITE);
      break;  
  }

  switch(opt3)
  {
    case 1:
      ab.drawRect(36, 39, 15, 12, WHITE);
      break;
    case 2:
      ab.drawRect(66, 39, 21, 12, WHITE);
      break;
  }
  
  ab.display();
}

//handles when input is given on option screen
void moveOptionSelect()
{
  if(ab.pressed(LEFT_BUTTON))
  {
    if(optionSelect > 1) optionSelect--;
  }

  if(ab.pressed(RIGHT_BUTTON))
  {
    if(optionSelect < 8) optionSelect++;
  }
  
  if(ab.pressed(UP_BUTTON))
  {
    if(optionSelect < 9 && optionSelect > 6) optionSelect = 4;
    else if(optionSelect < 7 && optionSelect > 3) optionSelect = 1;
  }

  if(ab.pressed(DOWN_BUTTON))
  {
    if(optionSelect < 4) optionSelect = 4;
    else if(optionSelect < 7) optionSelect = 7;
  }

  if(ab.pressed(A_BUTTON))
  {
      switch(optionSelect)
      {
        case 1:
          paddle1 = DOG_PADDLE;
          opt1 = 1;
          break;
        case 2:
          paddle1 = CORGI_PADDLE;
          opt1 = 2;
          break;
        case 3:
          paddle1 = DASCH_PADDLE;
          opt1 = 3;
          break;
        case 4:
          paddle2 = DOG_PADDLE;
          opt2 = 1;
          break;
        case 5:
          paddle2 = CORGI_PADDLE;
          opt2 = 2;
          break;
        case 6:
          paddle2 = DASCH_PADDLE;
          opt2 = 3;
          break;
        case 7:
          soundOn = true;
          opt3 = 1;
          break;
        case 8:
          soundOn = false;
          opt3 = 2;
          break;
      }
  }
}

//draw the credits screen
void drawCredits()
{  
  ab.clear();
  ab.setCursor(WIDTH/2-32, 1);
  ab.print("Developed By");
  ab.setCursor(WIDTH/2-48, 11);
  ab.print("Zachariah Falgout");
  ab.setCursor(WIDTH/2-18, 21);
  ab.print("Art By");
  ab.setCursor(WIDTH/2-12, 31);
  ab.print("LENZ");
  ab.setCursor(WIDTH/2-48, 41);
  ab.print("Zachariah Falgout");
  ab.setCursor(WIDTH/2-30, 55);
  ab.print("B to exit");
  ab.display();
}

//draw the menu screen
void drawMenu()
{
  ab.clear();
  ab.drawSlowXYBitmap(0,0, title, WIDTH, HEIGHT, WHITE);
  
  ab.setCursor(4, 55);
  ab.print("PLAY");
  ab.setCursor(32, 55);
  ab.print("OPTIONS");
  ab.setCursor(78, 55);
  ab.print("CREDITS");

  if(menuSelect == 1) ab.drawRect(2, 53, 28, 11, WHITE);
  else if(menuSelect == 2) ab.drawRect(30, 53, 45, 11, WHITE);
  else ab.drawRect(76, 53, 45, 11, WHITE);
  ab.display();
}

//handles when input is given on menu screen 
void moveMenuSelect()
{
  if(ab.pressed(LEFT_BUTTON))
  {
    if(menuSelect > 1) menuSelect--;
  }

  if(ab.pressed(RIGHT_BUTTON))
  {
    if(menuSelect < 3) menuSelect++;
  }
}

//draw player scores
void drawScores()
{
  ab.setCursor(WIDTH/4-4, 3);
  ab.print(p1Score);
  ab.setCursor(3*WIDTH/4, 3);
  ab.print(p2Score);
}

//draw the border lines top and bottom screen, also draws middle circle
void drawBorders()
{
  ab.drawLine(0,0,WIDTH,0,WHITE);
  ab.drawLine(0,HEIGHT-1, WIDTH, HEIGHT-1, WHITE);
  ab.drawLine(WIDTH/2, 0, WIDTH/2, HEIGHT-1, WHITE);
  ab.drawCircle(WIDTH/2, HEIGHT/2, 35, WHITE);
}

//handles moving the paddles
void movePaddles()
{
  if(ab.pressed(UP_BUTTON))
  {
    y1--;
    pDir1 = 1;
  }
  if(ab.pressed(DOWN_BUTTON))
  {
    y1++;
    pDir1 = -1;
  }
  if(y1 == 0) y1 = 1;
  else if(y1+PADDLE_HEIGHT > HEIGHT) y1 = HEIGHT-PADDLE_HEIGHT;

  if(ab.pressed(B_BUTTON))
  {
    y2--;
    pDir2 = 1;
  }
  if(ab.pressed(A_BUTTON))
  {
    y2++;
    pDir2 = -1;
  }
  if(y2 == 0) y2 = 1;
  else if(y2+PADDLE_HEIGHT > HEIGHT) y2 = HEIGHT-PADDLE_HEIGHT;
}

//draws the paddle, can use the different dog paddles
void drawPaddles()
{
  switch(paddle1)
  {
    case DOG_PADDLE:
      if(pDir1 == 1) ab.drawSlowXYBitmap(x1, y1, dogPaddleUp, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      else ab.drawSlowXYBitmap(x1, y1, dogPaddleDown, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      break;
    case CORGI_PADDLE:
      if(pDir1 == 1) ab.drawSlowXYBitmap(x1, y1, corgiPaddleUp, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      else ab.drawSlowXYBitmap(x1, y1, corgiPaddleDown, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      break;
    case DASCH_PADDLE:
      if(pDir1 == 1) ab.drawSlowXYBitmap(x1, y1, daschPaddleUp, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      else ab.drawSlowXYBitmap(x1, y1, daschPaddleDown, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      break;
  }
  
  switch(paddle2)
  {
    case DOG_PADDLE:
      if(pDir2 == 1) ab.drawSlowXYBitmap(x2, y2, dogPaddleUp, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      else ab.drawSlowXYBitmap(x2, y2, dogPaddleDown, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      break;
    case CORGI_PADDLE:
      if(pDir2 == 1) ab.drawSlowXYBitmap(x2, y2, corgiPaddleUp, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      else ab.drawSlowXYBitmap(x2, y2, corgiPaddleDown, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      break;
    case DASCH_PADDLE:
      if(pDir2 == 1) ab.drawSlowXYBitmap(x2, y2, daschPaddleUp, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      else ab.drawSlowXYBitmap(x2, y2, daschPaddleDown, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
      break;
  }

}

//handles playing the dog "bark" when ball hits paddle
void playTone(int pos)
{
  if(soundOn)
  {
    ab.tunes.tone(sound[pos], 20);
    if(pos == 0)
    {
      delay(30);
      playTone(1);
    }
  }
}

//handles changing variables related to the ball hitting the paddle
void paddleHit(byte Speed, byte bStep)
{
  if(hits % 4 == 0) bSpeed++;
  if(bSpeed > 4) bSpeed = 4;
  xDir = Speed;
  ballX += bStep;
  playTone(0);
  hits++;
}

//detect if ball has hit a wall or a panel, if not increment score start new round
void detectCol()
{
  if(ballY-BALL_RADIUS == 0 || ballY+BALL_RADIUS == HEIGHT) yDir = -yDir;

  else if(ballX-BALL_RADIUS <= x1+PADDLE_WIDTH && ballX-BALL_RADIUS >= x1)
  {
    if(ballY-BALL_RADIUS <= y1+PADDLE_HEIGHT && ballY-BALL_RADIUS >= y1) paddleHit(bSpeed, 2);
    else if(ballY+BALL_RADIUS <= y1+PADDLE_HEIGHT && ballY+BALL_RADIUS >= y1) paddleHit(bSpeed, 2);

    if(ballY-BALL_RADIUS == y1 || ballY-BALL_RADIUS == y1+PADDLE_HEIGHT
      || ballY+BALL_RADIUS == y1 || ballY+BALL_RADIUS == y1+PADDLE_HEIGHT) yDir = -yDir;
  }

  else if(ballX+BALL_RADIUS <= x2+PADDLE_WIDTH && ballX+BALL_RADIUS >= x2)
  {
    if(ballY-BALL_RADIUS <= y2+PADDLE_HEIGHT && ballY-BALL_RADIUS >= y2) paddleHit(-bSpeed, -2);
    else if(ballY+BALL_RADIUS <= y2+PADDLE_HEIGHT && ballY+BALL_RADIUS >= y2) paddleHit(-bSpeed, -2);

    if(ballY-BALL_RADIUS == y2 || ballY-BALL_RADIUS == y2+PADDLE_HEIGHT
      || ballY+BALL_RADIUS == y2 || ballY+BALL_RADIUS == y2+PADDLE_HEIGHT) yDir = -yDir;
  }

  else if(ballX-BALL_RADIUS < 0)
  {
    if(p2Score == 255) p2Score = 0;
    p2Score++;
    start = !start;
  }
  else if(ballX+BALL_RADIUS > WIDTH)
  {
    if(p1Score == 255) p1Score = 0;
    p1Score++;
    start = !start;
  }
}

//handles moving the ball
void moveBall()
{ 
  if(start)
  {
    if(random(2) == 0) xDir = 1;
    else xDir = -1;
    if(random(2) == 0) yDir = 1;
    else yDir = -1;
    start = !start;
    ballX = WIDTH/2;
    ballY = HEIGHT/2;
    bSpeed = 1;
    draw();
    delay(400);
  }
  detectCol();
  ballX += xDir;
  ballY += yDir;
}

//draws the ball
void drawBall()
{
  ab.drawCircle(ballX, ballY, BALL_RADIUS, WHITE);
}

//handles callign all draw functions
void draw()
{  
  ab.clear();
  drawBorders();
  drawScores();
  drawPaddles();
  drawBall();
  ab.display();   
}

//handles pause state
void pause()
{
  if(pause_key == 1) state = PLAY;
  ab.setCursor(WIDTH/2 - 14, HEIGHT/2);
  ab.print("PAUSED");
  ab.display();
}

//handles play state
void play()
{
  if(pause_key == 1) state = PAUSED;
  else
  {
    draw(); 
    movePaddles();
    moveBall();
  }
}

//handles resetting the game
void reset()
{
  p1Score = 0;
  p2Score = 0;
  start = true;
  state = PLAY;
  hits = 0;
  x1 = 0;
  x2 = WIDTH-PADDLE_WIDTH;
  y1 = 20;
  y2 = 20;
}

//handles the option state
void options()
{
  if(ab.everyXFrames(4)) moveOptionSelect();
  drawOptions();
}

//handles the menu state
void menu()
{ 
  if(ab.pressed(A_BUTTON))
  {
    switch(menuSelect)
    {
      case 1://play
        state = RESET;
        break;
      case 2://options
        state = OPTIONS;
        break;
      default://credits
        state = CREDITS;
        break;
    }
  }
  if(ab.everyXFrames(2)) moveMenuSelect();
  drawMenu();
}

//loop that runs the game
void loop() 
{
  if(!(ab.nextFrame())) return;
  
  if(ab.pressed(RIGHT_BUTTON) || ab.pressed(LEFT_BUTTON)) pause_key++;
  else pause_key = 0;

  if(ab.pressed(LEFT_BUTTON+B_BUTTON) && state != MENU && state != CREDITS && state != OPTIONS) state = RESET;
  if(ab.pressed(LEFT_BUTTON + RIGHT_BUTTON)) state = MENU;
  if(state == CREDITS && ab.pressed(B_BUTTON)) state = MENU;
  else if(state == OPTIONS && ab.pressed(B_BUTTON)) state = MENU;
  
  switch(state)
  {
    case PLAY:
      play();
      break;
    case PAUSED:
      pause();
      break;
    case RESET:
      reset();
      break;
    case CREDITS:
      drawCredits();
      break;
    case OPTIONS:
      options();
      break;
    default:
      menu();
      break;
  }
}
