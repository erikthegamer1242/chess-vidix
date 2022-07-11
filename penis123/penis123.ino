#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS 5
#define TFT_DC 21
int x_pokazivac =0 ,y_pokazivac = 0,  ud = 35, lr = 34,  UD , LR,x_stari,y_stari,A=32,B=33,a,b,x,y;
bool drop = false;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

char board[8][8] = {{'R', 'H', 'C', 'Q', 'K', 'C', 'H', 'R'},
          {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
          {'r', 'h', 'c', 'q', 'k', 'c', 'h', 'r'}};

void draw() {
   tft.drawRect(40, 0, 240, 240, ILI9341_WHITE);

  for(int i = 30; i < 240; i+=30) {
    tft.drawFastVLine(i + 40, 0, 240, ILI9341_RED);
  }
  for(int i = 30; i < 240; i+=30) {
    tft.drawFastHLine(40, i, 240, ILI9341_RED);
  }
  int boardX=0;
  int boardY=0;

  for(int j = 0; j < 240; j+=30) {
    for(int i = 0; i < 240; i+=30) {
        tft.setCursor(48 + i ,j + 5);
        tft.print(board[boardY][boardX]);
        boardX++;
    }
    boardX = 0;
    boardY++;
  }
}

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(3.5);
  tft.setCursor(0, 105);
  pinMode(ud,INPUT_PULLUP);
  pinMode(lr,INPUT_PULLUP);
  pinMode(A,INPUT_PULLUP);
  pinMode(B,INPUT_PULLUP);
  draw();
  Serial.begin(9600);
}

void loop() {
  tft.drawRect((40 + x_pokazivac * 30)+1, (y_pokazivac * 30)+ 1,28, 28, ILI9341_BLUE);
  LR = analogRead(lr);
  UD = analogRead(ud);
  a = digitalRead(A);
  b = digitalRead(B);
  delay(150);
  if(a==LOW)
  {
    x=x_pokazivac;
    y=y_pokazivac;
    Serial.print(x);
    Serial.println(y);
    tft.drawRect((40 + x_pokazivac * 30), (y_pokazivac * 30),30, 30, ILI9341_WHITE);
    drop = true;
  }
  if(drop == true && b==LOW)
  {
    board[y_pokazivac][x_pokazivac] = board[y][x];
    board[y][x] =' ';
    Serial.print(x_pokazivac);
    Serial.println(y_pokazivac);
    tft.fillRect((40 + x * 30)+1, (y * 30) + 1 ,28, 28, ILI9341_BLACK);
    draw();
    drop = false;
  }
  if(UD > 4090)
  {
     y_pokazivac--;
     tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
  }
    
  else if(UD > 1700)
  {
    y_pokazivac++;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
  }
    
  if(LR > 4090)
  {
    x_pokazivac--;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
  }
    
  else if(LR >1700)
  {
    x_pokazivac++;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
  }
   x_stari = x_pokazivac;
   y_stari = y_pokazivac;
}
