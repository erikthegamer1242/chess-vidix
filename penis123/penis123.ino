#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#define TFT_CS 5
#define TFT_DC 21
#define TFT_MEDIUMAQUAMARINE 0x6675
#define TFT_ROYALBLUE 0x435C
#define TFT_LIGHTGREEN 0x9772
#define TFT_GREEN2 0x0400
#define TFT_GREEN  0x07E0 
#define TFT_RED 0xF800
#define TFT_Tamni_Kvadratic 0x6982
#define TFT_Svjetli_Kvadratic 0xF693
#define TFT_WHITE 0xFFFF
#define TFT_BLACK 0x6969
#define TFT_Tamni_Kvadratic 0x6982
#define TFT_Svjetli_Kvadratic 0xF693

int x_pokazivac =0 ,y_pokazivac = 0,  ud = 35, lr = 34,  UD , LR,x_stari,y_stari,A=32,B=33,a,b,x,y, restart = 27, redraw=39;
bool drop = false,zastave;
int ilegalno = 0;
bool na_potezu = false;
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
int return_color(int x, int y) {
  if((x + y) % 2 == 0) return 0xF693;
  else return 0x6982;

  
}

const uint8_t fig[6][32] PROGMEM={
{0x0, 0x0,  0x0,  0x0,  0x0,  0x0,  0x3,  0xC0, 0x7,  0xE0, 0x7,  0xE0, 0x3,  0xC0, 0x3,  0xC0,
0x7,  0xE0, 0x3,  0xC0, 0x3,  0xC0, 0x7,  0xE0, 0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0, 0x0,  0x0}, 
{0x0, 0x0,  0x3,  0x40, 0x7,  0xE0, 0xF,  0xF0, 0x1F, 0xF8, 0x3F, 0xFC, 0x39, 0xFC, 0x33, 0xFC,
0x7,  0xFC, 0xF,  0xF8, 0xF,  0xF0, 0x7,  0xE0, 0x3,  0xC0, 0x7,  0xE0, 0x1F, 0xF8, 0x0,  0x0}, 
{0x1, 0x80, 0x3,  0xC0, 0x1,  0x80, 0xF,  0xF0, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8,
0x1F, 0xF8, 0x1F, 0xF8, 0xF,  0xF0, 0x7,  0xE0, 0x3,  0xC0, 0x31, 0x8C, 0x7F, 0xFE, 0x0,  0x0}, 
{0x0, 0x0,  0x19, 0x98, 0x1F, 0xF8, 0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0,
0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0, 0xF,  0xF0, 0x1F, 0xF8, 0x1F, 0xF8, 0x0,  0x0},
{0x19, 0x98, 0xD9, 0x9B, 0xD9, 0x9B, 0xD9, 0x9B, 0x6D, 0xB6, 0x6D, 0xB6, 0x6D, 0xB6, 0x35, 0xAC,
0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x1F, 0xF8, 0xF,  0xF0, 0xF,  0xF0, 0x1F, 0xF8, 0x0,  0x0},
{0x1, 0x80, 0x1,  0x80, 0x79, 0x9E, 0x7D, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x7F, 0xFE, 0x3F, 0xFC, 0x3F, 0xFC, 0x1F, 0xF8, 0xF,  0xF0, 0xF,  0xF0, 0x1F, 0xF8, 0x0,  0x0} 
};

void drawBitmap(int16_t x, int16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) {tft.drawPixel(x+i*1.4, y+j*1.4, color);}
    }
  }
}

void draw() {
  tft.setRotation(3);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(3.5);
  tft.setCursor(0, 105);
  tft.fillRect(0, 0, 319, 239, ILI9341_BLACK);
  tft.drawRect(40, 0, 240, 240, ILI9341_WHITE);

  for(int i = 30; i < 240; i+=30) {
    tft.drawFastVLine(i + 40, 0, 240, ILI9341_RED);
      
  }
  bool zas = false;
  for(int i = 30; i < 240; i+=30) {
    tft.drawFastHLine(40, i, 240, ILI9341_RED);

    //tft.fillRect(i + 40, 0, 30, 30, ILI9341_BLACK);
  }
 // for(int i=30;i < 
  int boardX=0;
  int boardY=0;
  for(int i = 0; i < 240; i+=30)
  {
    zas = !zas;
    for(int j = 0; j < 240; j+=30)
    {
     if(zas == true)
      {
        tft.fillRect(j + 40, i, 30, 30, TFT_Svjetli_Kvadratic);
        zas = false;
      }
    else
      {
        tft.fillRect(j + 40, i, 30, 30, TFT_Tamni_Kvadratic);
         zas = true;
      }
    }
  }

  for(int j = 0; j < 240; j+=30) {
    for(int i = 0; i < 240; i+=30) {
        //tft.setCursor(48 + i ,j + 5);
        //tft.print(board[boardY][boardX]);
        if(board[boardY][boardX] == 'p') {
           drawBitmap(45 + i,j + 5,&fig[0][0], 15 , 15,TFT_WHITE); 
        }
        if(board[boardY][boardX] == 'h') {
           drawBitmap(45 + i,j + 5,&fig[1][0], 15 , 15,TFT_WHITE); 
        }
        if(board[boardY][boardX] == 'c') {
           drawBitmap(45 + i,j + 5,&fig[2][0], 15 , 15,TFT_WHITE); 
        }
        if(board[boardY][boardX] == 'r') {
           drawBitmap(45 + i,j + 5,&fig[3][0], 15 , 15,TFT_WHITE); 
        }
        if(board[boardY][boardX] == 'q') {
           drawBitmap(45 + i,j + 5,&fig[4][0], 15 , 15,TFT_WHITE); 
        }
        if(board[boardY][boardX] == 'k') {
           drawBitmap(45 + i,j + 5,&fig[5][0], 15 , 15,TFT_WHITE); 
        }
        if(board[boardY][boardX] == 'P') {
           drawBitmap(45 + i,j + 5,&fig[0][0], 15 , 15,TFT_BLACK); 
        }
        if(board[boardY][boardX] == 'H') {
           drawBitmap(45 + i,j + 5,&fig[1][0], 15 , 15,TFT_BLACK); 
        }
        if(board[boardY][boardX] == 'C') {
           drawBitmap(45 + i,j + 5,&fig[2][0], 15 , 15,TFT_BLACK); 
        }
        if(board[boardY][boardX] == 'R') {
           drawBitmap(45 + i,j + 5,&fig[3][0], 15 , 15,TFT_BLACK); 
        }
        if(board[boardY][boardX] == 'Q') {
           drawBitmap(45 + i,j + 5,&fig[4][0], 15 , 15,TFT_BLACK); 
        }
        if(board[boardY][boardX] == 'K') {
           drawBitmap(45 + i,j + 5,&fig[5][0], 15 , 15,TFT_BLACK); 
        }
        boardX++;
    }
    boardX = 0;
    boardY++;
  }
}

char meni_crni()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_BLACK);
  tft.fillRoundRect(41, 61, 8*30-1, 4*30-1, 19, TFT_RED);
  tft.drawRect(41, 91, 60-1, 2*30-1, TFT_RED);
  tft.drawRect(101, 91, 60-1, 2*30-1, TFT_RED);
  tft.drawRect(161, 91, 60-1, 2*30-1, TFT_RED);
  tft.drawRect(221, 91, 60-1, 2*30-1, TFT_RED);
  tft.setTextSize(4);
  tft.setCursor(60, 105);
  tft.print("H");
  tft.setCursor(120, 105);
  tft.print("C");
  tft.setCursor(180, 105);
  tft.print("R");
  tft.setCursor(240, 105);
  tft.print("Q");
  int var=300;
  while (digitalRead(A)!=LOW)
  {
    analogRead(lr);
    if(analogRead(lr)>1650&& analogRead(lr)<4000)
    {
      var+=100;
      delay(300);
      if(var>400)
      {
        var=100;
      }
    }
    //4090
    else if(analogRead(lr)>4000)
    {
      var-=100;
      delay(300);
      if(var<100)
      {
        var=400;
      }
    }
    if(var==100)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(43, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(103, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(163, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(223, 93, 60-5, 2*30-5, ILI9341_BLACK);
    }
    
    if(var==200)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(43, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(103, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(163, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(223, 93, 60-5, 2*30-5, ILI9341_BLACK);
    }
    
    if(var==300)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(43, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(103, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(163, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(223, 93, 60-5, 2*30-5, ILI9341_BLACK);
    }

    if(var==400)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(43, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(103, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(163, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(223, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
    }
  }
  if(var==400)
  {
    return 'Q';
  }
  if(var==300)
  {
    return 'R';
  }
  if(var==200)
  {
    return 'C';
  }
  if(var==100)
  {
    return 'H';
  }
  
}

char meni_bijeli()
{
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE);
  tft.fillRoundRect(41, 61, 8*30-1, 4*30-1, 19, TFT_RED);
  tft.drawRect(41, 91, 60-1, 2*30-1, TFT_RED);
  tft.drawRect(101, 91, 60-1, 2*30-1, TFT_RED);
  tft.drawRect(161, 91, 60-1, 2*30-1, TFT_RED);
  tft.drawRect(221, 91, 60-1, 2*30-1, TFT_RED);
  tft.setTextSize(4);
  tft.setCursor(60, 105);
  tft.print("H");
  tft.setCursor(120, 105);
  tft.print("C");
  tft.setCursor(180, 105);
  tft.print("R");
  tft.setCursor(240, 105);
  tft.print("Q");
  int var=300;
  while (digitalRead(A)!=LOW)
  {
    analogRead(lr);
    if(analogRead(lr)>1650&& analogRead(lr)<4000)
    {
      var+=100;
      delay(300);
      if(var>400)
      {
        var=100;
      }
    }
    //4090
    else if(analogRead(lr)>4000)
    {
      var-=100;
      delay(300);
      if(var<100)
      {
        var=400;
      }
    }
    if(var==100)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(43, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(103, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(163, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(223, 93, 60-5, 2*30-5, ILI9341_BLACK);
    }
    
    if(var==200)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(43, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(103, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(163, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(223, 93, 60-5, 2*30-5, ILI9341_BLACK);
    }
    
    if(var==300)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(43, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(103, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(163, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(223, 93, 60-5, 2*30-5, ILI9341_BLACK);
    }

    if(var==400)
    {
        tft.drawRect(42, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(43, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(102, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(103, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(162, 92, 60-3, 2*30-3, ILI9341_BLACK);
        tft.drawRect(163, 93, 60-5, 2*30-5, ILI9341_BLACK);
        
        tft.drawRect(222, 92, 60-3, 2*30-3, TFT_LIGHTGREEN);
        tft.drawRect(223, 93, 60-5, 2*30-5, TFT_LIGHTGREEN);
    }
  }
  if(var==400)
  {
    return 'q';
  }
  if(var==300)
  {
    return 'r';
  }
  if(var==200)
  {
    return 'c';
  }
  if(var==100)
  {
    return 'h';
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

//konj
void konj(int row_to, int row_from, int column_to, int column_from)
{
  if(na_potezu == true) na_potezu = false;
  else na_potezu = true;
  Serial.println(na_potezu);
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
        if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && toLowerCase(board[row_to][column_to_int])!='k')
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
        else if(toLowerCase(board[row_to][column_to_int])=='k') ilegalno = 1;
        if(ilegalno == 0) logika_za_crtanje(row_to, row_from, column_to, column_from);
    }
    else if(abs(column_from-column_to)==2 && abs(row_from-row_to)==1)
    {
      if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && toLowerCase(board[row_to][column_to_int])!='k')
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
      else if(isUpperCase(board[row_to][column_to_int]) > 0) ilegalno = 1;
      if(ilegalno == 0) logika_za_crtanje(row_to, row_from, column_to, column_from);
    }  
    else 
    ilegalno=1;
  }
}

//pijuni
void pijuni(int row_to, int row_from, int column_to, int column_from) {
  if(na_potezu == true) na_potezu = false;   else na_potezu = true;
  Serial.println(na_potezu);
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;



  // crni pijuni
  if(board[row_from][column_from_int] == 'p')
  {
    if (row_from == 6 && row_to > 3 && column_from == column_to && board[row_to][column_to] == ' ' && board[5][column_to] == ' ') 
    {
      logika_za_crtanje(row_to, row_from, column_to, column_from);
    } 
    else if (row_from != 6 && column_from == column_to && board[row_to][column_to] == ' ' && row_to!=0) 
    {
      if (row_from == row_to + 1)
        logika_za_crtanje(row_to, row_from, column_to, column_from);
      else
        ilegalno = 1;
    } 
    else if (row_to == 0 && row_from == 1)
    {
        board[row_to][column_to_int] = meni_crni();
        board[row_from][column_from_int] = ' ';
    }

    else
      ilegalno = 1;
    //jedenje crni jede 
    if((row_from-row_to==1) && abs(column_to-column_from)==1)
    {
      if(isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k')
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
        logika_za_crtanje(row_to, row_from, column_to, column_from);
        ilegalno = 0;
      }
    }
  }
  // bijeli pijuni
  if(board[row_from][column_from_int] == 'P')
  {
    if (row_from == 1 && row_to < 4 && column_from == column_to &&
      board[row_to][column_to] == ' ' && board[2][column_to] == ' ') 
    {
      logika_za_crtanje(row_to, row_from, column_to, column_from);
    } 
    else if (row_from != 1 && column_from == column_to &&
      board[row_to][column_to] == ' ') 
    {
      if (row_from == row_to - 1)
        logika_za_crtanje(row_to, row_from, column_to, column_from);
      else
        ilegalno = 1;
    } 
    else if (row_to == 7 && row_from == 6)
    {
        board[row_to][column_to_int] = meni_bijeli();
        board[row_from][column_from_int] = ' ';
    }
    else
      ilegalno = 1;
    //bjeli jede 
    if((row_from-row_to==-1) && abs(column_to-column_from)==1)
    {
      if(isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K')
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
        logika_za_crtanje(row_to, row_from, column_to, column_from);
        ilegalno = 0;
      }
    }
  }
}

//lovac
void lovac(int row_to, int row_from, int column_to, int column_from)
{
  if(na_potezu == true) na_potezu = false;   else na_potezu = true;
  Serial.println(na_potezu);
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;
  int moze=1, moze_jest=0;

  if (abs(row_from - row_to) == abs(column_from_int - column_to_int))
  {
//      for (int i = row_from; i != row_to;)
//      {
////          for (int j = column_from_int; j != column_to_int;)
//          {
//              if (row_from > row_to)
//                  i--;
//              else
//                  i++;
//              if (column_from_int > column_to_int)
//                  j--;
//              else
//                  j++;
//              if (board[i][j] != ' ')
//                  moze = 0;
//              if ((abs(i - row_to) == 1 && abs(j - column_to_int) == 1) && (isUpperCase(board[row_from][column_from_int]) >= 1 && isLowerCase(board[row_to][column_to_int]) >= 1) || (isLowerCase(board[row_from][column_from_int]) >= 1 && isUpperCase(board[row_to][column_to_int]) >= 1))
//              {
//                 moze_jest = 1;
//              }
//          }
//      }

    moze_jest = 0,moze=0;
    int j=row_from,i=column_from;
    Serial.print(row_to);
    Serial.print(column_to_int);
      for(int c=0;c<8;c++){
         if (j > row_to)
            j--;
        else if(j < row_to)
            j++;
        if (i > column_to_int)
            i--;
        else if (i < column_to_int)
            i++;
        if(board[j][i] !=' ' &&  j!=row_to && i!=column_to_int)
        {
          moze=0;
          break;
        }     
          if(j == row_to && i==column_to_int)
         {
          if(board[row_to][column_to_int]==' ')
          {
            moze = 1;
          
            break;
          }
          else if(isUpperCase(board[row_from][column_from_int])!=isUpperCase(board[row_to][column_to_int]))
          {
            moze = 1;
            moze_jest = 1;
            break;
          }
          else
            break;
         }
      }
                  if (moze == 1 && moze_jest ==0)
      {
          logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
      

      if (moze_jest)
      {
     //Crni jede
      if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int] != 'K')
      {
          for (int i = 0; i < 2; i++)
          {
              for (int j = 0; j < 8; j++)
              {
                  if (crni_jede[i][j] == ' ')
                  {
                      crni_jede[i][j] = board[row_to][column_to_int];
                      board[row_to][column_to_int] = ' ';
                  }
              }
          }
          logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
      //Bijeli jede
      if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int] != 'k')
      {
          for (int i = 0; i < 2; i++)
          {
              for (int j = 0; j < 8; j++)
              {
                  if (bijeli_jede[i][j] == ' ')
                  {
                      bijeli_jede[i][j] = board[row_to][column_to_int];
                      board[row_to][column_to_int] = ' ';
                  }
              }
          }
          logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
  }
  }
  else
      ilegalno = 1;
}

void kula(int row_to, int row_from, int column_to, int column_from)
{
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;
  int moze = 1;
  
    if(column_to_int == column_from_int && row_to != row_from) 
    {
        if ((isUpperCase(board[row_from][column_from_int]) >= 1 && isUpperCase(board[row_to][column_to_int]) >= 1) || (isLowerCase(board[row_from][column_from_int]) >= 1 && isLowerCase(board[row_to][column_to_int]) >= 1))
        {
            ilegalno = 1;
            moze = 0;
        }
        if(row_from - row_to > 0) //Gore
        {
        for(int i = row_from-1; i>=row_to; i--)
        {
          if(board[i][column_to_int] != ' ') 
          {
            if(i!=row_to)
            {
              moze=0;
            }
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
            
            else 
            moze=0;
          }
        }
      }
      else if(row_from - row_to < 0) //Dolje
      {
        for(int i = row_from+1; i<=row_to; i++)
        {
          if(board[i][column_to_int] != ' ') 
          {
            if(i!=row_to)
            {
              moze=0;
            }
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
            }
            //else moze=0;
          }
        }
    }
    else if(column_to_int != column_from_int && row_to == row_from) 
    {
       if ((isUpperCase(board[row_from][column_from_int]) > 0 && isUpperCase(board[row_to][column_to_int]) > 0) || (isLowerCase(board[row_from][column_from_int]) > 0 && isLowerCase(board[row_to][column_to_int]) > 0))
       {
           ilegalno = 1;
           moze = 0;
       }
      else if(column_from_int - column_to_int > 0) //Lijevo
      {
        for(int i = column_from_int-1; i>=column_to_int; i--)
        {
          if(board[row_to][i] != ' ') 
          {
           if(i!=column_to_int)
            {
              moze=0;
            }
              
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
          }
        }
      }
      else if(column_from_int - column_to_int < 0) //Desno
      {
        for(int i = column_from_int+1; i<=column_to_int; i++)
        {
          if(board[row_to][i] != ' ') 
          {
            if(i!=column_to_int) moze=0;           
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
          }
        }
      }
      
    }
    else
    {
      moze=0;
      ilegalno=1;
    }
  if(moze == 1) 
  {
    if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0)
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
    logika_za_crtanje(row_to, row_from, column_to, column_from);
  }
  else
  {
    moze = 1;
    ilegalno = 1;
  }
}
//kralj
void kralj(int row_to, int row_from, int column_to, int column_from)
{
  if(na_potezu == true) na_potezu = false;   else na_potezu = true;
  Serial.println(na_potezu);
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;
  int moze=1;
  if(board[row_from][column_from_int] == 'K' || board[row_from][column_from_int] == 'k')
  {
    if(abs(row_from-row_to)<=1 && abs(column_from-column_to)<=1)
    {
      if(board[row_to][column_to_int]==' ')
      {
      if(board[row_from][column_from_int]=='k')
      {
        if(board[row_to+1][column_to_int]=='K')
          moze=0;
        if(board[row_to+1][column_to_int+1]=='K')
          moze=0;
        if(board[row_to+1][column_to_int-1]=='K')
          moze=0;
        if(board[row_to][column_to_int+1]=='K')
          moze=0;
        if(board[row_to-1][column_to_int+1]=='K')
          moze=0;
        if(board[row_to-1][column_to_int-1]=='K')
          moze=0;
        if(board[row_to-1][column_to_int]=='K')
          moze=0;
        if(board[row_to][column_to_int-1]=='K')
          moze=0;
      }
      if(board[row_from][column_from_int]=='K')
      {
        if(board[row_to+1][column_to_int]=='k')
          moze=0;
        if(board[row_to+1][column_to_int+1]=='k')
          moze=0;
        if(board[row_to+1][column_to_int-1]=='k')
          moze=0;
        if(board[row_to][column_to_int+1]=='k')
          moze=0;
        if(board[row_to-1][column_to_int+1]=='k')
          moze=0;
        if(board[row_to-1][column_to_int-1]=='k')
          moze=0;
        if(board[row_to-1][column_to_int]=='k')
          moze=0;
        if(board[row_to][column_to_int-1]=='k')
          moze=0;
      }
      if(moze==1)
        logika_za_crtanje(row_to, row_from, column_to, column_from);
      else
        ilegalno=1;
    }
    else if(isUpperCase (board[row_from][column_from_int])!= isUpperCase (board[row_to][column_to_int]))
    {
      moze=1;
      if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
              logika_za_crtanje(row_to, row_from, column_to, column_from);
    }
      
   }
  }
 }
}
}
  
        


void kraljica(int row_to, int row_from, int column_to, int column_from)
{
  if(na_potezu == true) na_potezu = false;   else na_potezu = true;
  Serial.println(na_potezu);
  int column_to_int = 0, column_from_int = 0;
  column_to_int = column_to;
  column_from_int = column_from;
  int moze = 1;

  //kula u kraljici
    if(column_to_int == column_from_int && row_to != row_from) 
    {
        if ((isUpperCase(board[row_from][column_from_int]) >= 1 && isUpperCase(board[row_to][column_to_int]) >= 1) || (isLowerCase(board[row_from][column_from_int]) >= 1 && isLowerCase(board[row_to][column_to_int]) >= 1))
        {
            ilegalno = 1;
            moze = 0;
        }
        if(row_from - row_to > 0) //Gore
        {
        for(int i = row_from-1; i>=row_to; i--)
        {
          if(board[i][column_to_int] != ' ') 
          {
            if(i!=row_to)
            {
              moze=0;
            }
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
            
            else 
            moze=0;
          }
        }
      }
      else if(row_from - row_to < 0) //Dolje
      {
        for(int i = row_from+1; i<=row_to; i++)
        {
          if(board[i][column_to_int] != ' ') 
          {
            if(i!=row_to)
            {
              moze=0;
            }
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
            }
            //else moze=0;
          }
        }
    }
    else if(column_to_int != column_from_int && row_to == row_from) 
    {
       if ((isUpperCase(board[row_from][column_from_int]) > 0 && isUpperCase(board[row_to][column_to_int]) > 0) || (isLowerCase(board[row_from][column_from_int]) > 0 && isLowerCase(board[row_to][column_to_int]) > 0))
       {
           ilegalno = 1;
           moze = 0;
       }
      else if(column_from_int - column_to_int > 0) //Lijevo
      {
        for(int i = column_from_int-1; i>=column_to_int; i--)
        {
          if(board[row_to][i] != ' ') 
          {
           if(i!=column_to_int)
            {
              moze=0;
            }
              
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
          }
        }
      }
      else if(column_from_int - column_to_int < 0) //Desno
      {
        for(int i = column_from_int+1; i<=column_to_int; i++)
        {
          if(board[row_to][i] != ' ') 
          {
            if(i!=column_to_int) moze=0;           
              if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='K' && moze==1)
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
              if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int]!='k' && moze==1)
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
          }
        }
      }
      
    }
    else
    {
      moze=0;
      ilegalno=1;
    }
  if(moze == 1) 
  {
    if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0)
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
    logika_za_crtanje(row_to, row_from, column_to, column_from);
  }
  else
  {
    moze = 1;
    ilegalno = 1;
  }

  //lovac u kraljici
  if (abs(row_from - row_to) == abs(column_from_int - column_to_int))
  {
//      for (int i = row_from; i != row_to;)
//      {
////          for (int j = column_from_int; j != column_to_int;)
//          {
//              if (row_from > row_to)
//                  i--;
//              else
//                  i++;
//              if (column_from_int > column_to_int)
//                  j--;
//              else
//                  j++;
//              if (board[i][j] != ' ')
//                  moze = 0;
//              if ((abs(i - row_to) == 1 && abs(j - column_to_int) == 1) && (isUpperCase(board[row_from][column_from_int]) >= 1 && isLowerCase(board[row_to][column_to_int]) >= 1) || (isLowerCase(board[row_from][column_from_int]) >= 1 && isUpperCase(board[row_to][column_to_int]) >= 1))
//              {
//                 moze_jest = 1;
//              }
//          }
//      }

    int moze_jest = 0,moze=0;
    int j=row_from,i=column_from;
    Serial.print(row_to);
    Serial.print(column_to_int);
      for(int c=0;c<8;c++){
          Serial.println(i);
          Serial.println(j);
         if (j > row_to)
            j--;
        else if(j < row_to)
            j++;
        if (i > column_to_int)
            i--;
        else if (i < column_to_int)
            i++;
        if(board[j][i] !=' ' &&  j!=row_to && i!=column_to_int)
        {
          moze=0;
            Serial.println("Skacem");
          break;
        }     
          if(j == row_to && i==column_to_int)
         {
          Serial.println("da");
          if(board[row_to][column_to_int]==' ')
          {
            moze = 1;
          
            break;
          }
          else if(isUpperCase(board[row_from][column_from_int])!=isUpperCase(board[row_to][column_to_int]))
          {
            moze = 1;
            moze_jest = 1;
            break;
          }
          else
            break;
         }
      }
                  if (moze == 1 && moze_jest ==0)
      {
          logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
      

      if (moze_jest)
      {
     //Crni jede
      if (isUpperCase(board[row_to][column_to_int]) > 0 && isLowerCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int] != 'K')
      {
          for (int i = 0; i < 2; i++)
          {
              for (int j = 0; j < 8; j++)
              {
                  if (crni_jede[i][j] == ' ')
                  {
                      crni_jede[i][j] = board[row_to][column_to_int];
                      board[row_to][column_to_int] = ' ';
                  }
              }
          }
          logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
      //Bijeli jede
      if (isLowerCase(board[row_to][column_to_int]) > 0 && isUpperCase(board[row_from][column_from_int]) > 0 && board[row_to][column_to_int] != 'k')
      {
          for (int i = 0; i < 2; i++)
          {
              for (int j = 0; j < 8; j++)
              {
                  if (bijeli_jede[i][j] == ' ')
                  {
                      bijeli_jede[i][j] = board[row_to][column_to_int];
                      board[row_to][column_to_int] = ' ';
                  }
              }
          }
          logika_za_crtanje(row_to, row_from, column_to, column_from);
      }
  }
  }

}

void whichFigure(int column_to, int column_from, int row_to, int row_from) {
    if ((board[row_from][column_from] == 'p' && na_potezu == 0) || (board[row_from][column_from] == 'P' && na_potezu == 1)) { Serial.println("pijun"); pijuni(row_to, row_from, column_to, column_from); }
    else if ((board[row_from][column_from] == 'r' && na_potezu == 0) || (board[row_from][column_from] == 'R' &&  na_potezu == 1)){ Serial.println("kula"); kula(row_to, row_from, column_to, column_from);}
    else if ((board[row_from][column_from] == 'h' && na_potezu == 0) || (board[row_from][column_from] == 'H' &&  na_potezu == 1)){ Serial.println("konj"); konj(row_to, row_from, column_to, column_from);}
    else if ((board[row_from][column_from] == 'c' && na_potezu == 0) || (board[row_from][column_from] == 'C' &&  na_potezu == 1)){ Serial.println("lovac"); lovac(row_to, row_from, column_to, column_from);}
    else if ((board[row_from][column_from] == 'k' && na_potezu == 0) || (board[row_from][column_from] == 'K' &&  na_potezu == 1)){ Serial.println("kralj"); kralj(row_to, row_from, column_to, column_from);}
    else if ((board[row_from][column_from] == 'q' && na_potezu == 0) || (board[row_from][column_from] == 'Q' &&  na_potezu == 1)){ Serial.println("kraljica"); kraljica(row_to, row_from, column_to, column_from);}
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
     tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, return_color(x_stari,y_stari));
     tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, return_color(x_stari,y_stari));
  }
    
  else if(UD > 1700 && y_pokazivac!=7 && UD < 4000)
  {
    y_pokazivac++;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, return_color(x_stari,y_stari));
    tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, return_color(x_stari,y_stari));
  }
    
  if(LR > 4090 && x_pokazivac!=0)
  {
    x_pokazivac--;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, return_color(x_stari,y_stari));
    tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, return_color(x_stari,y_stari));
  }
    
  else if(LR >1700 && x_pokazivac!=7 && LR <4000)
  {
    x_pokazivac++;
    tft.drawRect((40 + x_stari * 30)+1, (y_stari * 30) + 1 ,28, 28, return_color(x_stari,y_stari));
    tft.drawRect((40 + x_stari * 30)+2, (y_stari * 30)+ 2,26, 26, return_color(x_stari,y_stari));
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
   ilegalno = 0;
}
