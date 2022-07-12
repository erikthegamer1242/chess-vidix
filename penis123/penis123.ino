#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#define TFT_CS 5
#define TFT_DC 21

int x_pokazivac =0 ,y_pokazivac = 0,  ud = 35, lr = 34,  UD , LR,x_stari,y_stari,A=32,B=33,a,b,x,y, restart=27, redraw = 39;
bool drop = false;
int ilegalno = 0;
char bijeli_jede[2][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
char crni_jede[2][8] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                       {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

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
  tft.fillRect(0,0,319,239, ILI9341_BLACK);
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

void logika_za_crtanje(int row_to, int row_from, int column_to, int column_from)

{
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;
  char temp_ploca;
  temp_ploca = board[row_from][column_from_int];
  board[row_from][column_from_int] = board[row_to][column_to_int];
  board[row_to][column_to_int] = temp_ploca;
}

void meni()
{
  tft.fillScreen(ILI9341_BLUE);
  tft.fillRoundRect(41, 61, 8*30-1, 4*30-1, 19, ILI9341_BLACK);
  tft.drawRect(41, 91, 60-1, 2*30-1, ILI9341_YELLOW);
  tft.drawRect(101, 91, 60-1, 2*30-1, ILI9341_YELLOW);
  tft.drawRect(161, 91, 60-1, 2*30-1, ILI9341_YELLOW);
  tft.drawRect(221, 91, 60-1, 2*30-1, ILI9341_YELLOW);
  tft.setTextSize(4);
  tft.setCursor(60, 105);
  tft.print(board[0][1]);
  tft.setCursor(120, 105);
  tft.print(board[0][2]);
  tft.setCursor(180, 105);
  tft.print(board[0][0]);
  tft.setCursor(240, 105);
  tft.print(board[0][3]);
}
//konj
void konj(int row_to, int row_from, int column_to, int column_from)
{
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;

  //crni konj
  if(board[row_from][column_from] == 'h')
  {
    if((abs(row_from-row_to)==2) && (abs(column_to-column_from)==1))
    {
        if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && toUpperCase(board[row_to][column_to_int])!='K')
        { 
          for( int i = 0; i<2; i++)
          {
            for(int j=0; j<8; j++) 
            {
              if(crni_jede[i][j] == ' ') 
              {
                crni_jede[i][j] = board[row_to][column_to_int];
                board[row_to][column_to_int] = ' ';
              }
            }
          } 
        }
        else if(isLowerCase(board[row_to][column_to_int]) > 0) ilegalno = 1;
        if(ilegalno == 0) logika_za_crtanje(row_to, row_from, column_to, column_from);
    }
    else if(abs(column_from-column_to)==2 && abs(row_from-row_to)==1)
    {
      if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && toUpperCase(board[row_to][column_to_int])!='K')
      { 
        for( int i = 0; i<2; i++)
        {
          for(int j=0; j<8; j++) 
          {
            if(crni_jede[i][j] == ' ') 
            {
              crni_jede[i][j] = board[row_to][column_to_int];
              board[row_to][column_to_int] = ' ';
            }
          }
        } 
      }
      else if(isLowerCase(board[row_to][column_to_int]) > 0) ilegalno = 1;
      if(ilegalno == 0) logika_za_crtanje(row_to, row_from, column_to, column_from);
    }  
    else 
    ilegalno=1;
  }
    //bijeli konj
    if(board[row_from][column_from] == 'H')
    {
      if((abs(row_from-row_to)==2) && (abs(column_to-column_from)==1))
      {
        if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && toUpperCase(board[row_to][column_to_int])!='K')
        {
          for( int i = 0; i<2; i++)
          {
            for(int j=0; j<8; j++) 
            {
              if(bijeli_jede[i][j] == ' ') 
              {
                bijeli_jede[i][j] = board[row_to][column_to_int];
                board[row_to][column_to_int] = ' ';
              }
            }
          }
        }
        else if(isLowerCase(board[row_to][column_to_int]) > 0) ilegalno = 1;
        if(ilegalno == 0) logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
    else if(abs(column_from-column_to)==2 && abs(row_from-row_to)==1)
    {
      if(board[row_to][column_to_int]==' ')
      {
        if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && toUpperCase(board[row_to][column_to_int])!='K')
        {
          for( int i = 0; i<2; i++)
          {
            for(int j=0; j<8; j++) 
            {
              if(bijeli_jede[i][j] == ' ') 
              {
                bijeli_jede[i][j] = board[row_to][column_to_int];
                board[row_to][column_to_int] = ' ';
              }
            }
          }
        }
        else if(isLowerCase(board[row_to][column_to_int]) > 0) ilegalno = 1;
        if(ilegalno == 0) logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
    }
    else 
    ilegalno=1;
  }

}


void whichFigure(int column_to, int column_from, int row_to, int row_from) {
    if (board[row_from][column_from] == 'p' || board[row_from][column_from] == 'P') Serial.println("pijuni(row_to, row_from, column_to, column_from)");
    else if (board[row_from][column_from] == 'r' || board[row_from][column_from] == 'R') Serial.println("kula(row_to, row_from, column_to, column_from)"); 
    else if (board[row_from][column_from] == 'h' || board[row_from][column_from] == 'H'){ Serial.println("konj"); Serial.println(ilegalno); konj(row_to, row_from, column_to, column_from);}
    else if (board[row_from][column_from] == 'c' || board[row_from][column_from] == 'C') Serial.println("lovac(row_to, row_from, column_to, column_from)");
    else if (board[row_from][column_from] == 'k' || board[row_from][column_from] == 'K') Serial.println("kralj(row_to, row_from, column_to, column_from)");
    else if (board[row_from][column_from] == 'q' || board[row_from][column_from] == 'Q') Serial.println("kraljica(row_to, row_from, column_to, column_from)");
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
  pinMode(restart,INPUT_PULLUP);
  pinMode(redraw,INPUT_PULLUP);
  draw();
  Serial.begin(9600);
}

void loop() {
  tft.drawRect((40 + x_pokazivac * 30)+1, (y_pokazivac * 30)+ 1,28, 28, ILI9341_BLUE);
  tft.drawRect((40 + x_pokazivac * 30)+2, (y_pokazivac * 30)+ 2,26, 26, ILI9341_BLUE);
  LR = analogRead(lr);
  UD = analogRead(ud);
  a = digitalRead(A);
  b = digitalRead(B);
  delay(150);
  
  if(a==LOW && drop==false)
  {
    x=x_pokazivac;
    y=y_pokazivac;
    Serial.print(x);
    Serial.println(y);
    if(board[y][x]!=' ')
      drop = true;
  }
  if(drop == true && b==LOW)
  {
   whichFigure(x_pokazivac, x, y_pokazivac, y);
// Debug logika za grafiku    
//    board[y_pokazivac][x_pokazivac] = board[y][x];
//    board[y][x] =' ';
//    Serial.print(x_pokazivac);
//    Serial.println(y_pokazivac);
    tft.fillRect((40 + x * 30)+1, (y * 30) + 1 ,28, 28, ILI9341_BLACK);
    draw();
    drop = false;
  }
  if(UD > 4090 && y_pokazivac!=0)
  {
     y_pokazivac--;
     tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
     tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, ILI9341_BLACK);
  }
    
  else if(UD > 1700 && y_pokazivac!=7 && UD < 4000)
  {
    y_pokazivac++;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
    tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, ILI9341_BLACK);
  }
    
  if(LR > 4090 && x_pokazivac!=0)
  {
    x_pokazivac--;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
    tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, ILI9341_BLACK);
  }
    
  else if(LR >1700 && x_pokazivac!=7 && LR <4000)
  {
    x_pokazivac++;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, ILI9341_BLACK);
    tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, ILI9341_BLACK);
  }
   x_stari = x_pokazivac;
   y_stari = y_pokazivac;
   if((x_pokazivac != x || y_pokazivac!=y)&& drop == true)
   {
    tft.drawRect((40 + x * 30)+1, (y * 30)+ 1,28, 28, ILI9341_WHITE);
    tft.drawRect((40 + x * 30)+2, (y * 30)+ 2,26, 26, ILI9341_WHITE);
   }
   if(digitalRead(restart) == LOW) {
    ESP.restart();
   }
   if(digitalRead(redraw) == LOW) {
    draw();
   }
   Serial.println(ilegalno);
   ilegalno = 0;
}
