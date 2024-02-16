#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x26, 16, 4); // I2C address 0x27, 16 column and 2 rows
int col = 20;
int row = 4;
int playerScore = 0;
int btn = 8;
int btn_state = 0;
int playerPosRow = 3;
int playerPosCol = 3;

int enemyPosCol = 19;
int enemyPosRow = 3;

int enemyTwoPosCol = 25;
int enemyTwoPosRow = 2;

int isGameOver = false;
int gameover = false;

void(* resetFunc) (void) = 0; 
void render(){
  for(int i = 0;i<col;i++){
    lcd.setCursor(i,1);
    lcd.print("-");
  }
  
}
void Draw(){
 
  playerScore++;
  lcd.clear();
  lcd.setCursor(playerPosCol, playerPosRow);
  lcd.print("O");

 
}
void Input(){
  if(btn_state == 0){
    playerPosRow = 2;
  }
  else{
    playerPosRow = 3;
  }
}

void obstacle(){
  
  lcd.setCursor(enemyPosCol, enemyPosRow);
  enemyPosCol -= 2;
  lcd.print("@");
  lcd.setCursor(enemyTwoPosCol, enemyTwoPosRow);
  enemyTwoPosCol -= 2;
  lcd.print("@");
  if(enemyPosCol <= 0){
    enemyPosCol = 19;
  }
  if(playerPosCol == enemyPosCol && playerPosRow == enemyPosRow){
    lcd.clear();
    isGameOver = true;
  }

  if(enemyTwoPosCol <= 0){
    enemyTwoPosCol = 19;
  }
  if(playerPosCol == enemyTwoPosCol && playerPosRow == enemyTwoPosRow){
    lcd.clear();
    isGameOver = true;
  }
  }

void setup() {
  Serial.begin(9600);
  Serial.print("Hello world");
  pinMode(btn,INPUT_PULLUP);
lcd.init(); //initialize the lcd
lcd.backlight(); //open the backlight 

}
void GameOverDisplay(){
 
  for(int i = 0;i<20;i++){
    lcd.setCursor(i, 0);
    lcd.print("*");
  }
  lcd.setCursor(5, 1);
  lcd.print("GAME OVER");
  lcd.setCursor(7, 2);
  lcd.print(playerScore);
  lcd.setCursor(0, 3);
  lcd.print("Hold Btn 1sec Reset");
  gameover = true;
  if(gameover == true && btn_state == LOW){
    delay(1000);
    if(btn_state == LOW){
      resetFunc();
    }
  
  }
  
}
void loop() {
  btn_state = digitalRead(btn);
 while(!isGameOver){
   btn_state = digitalRead(btn);

  render();
  Input();
  Draw();
  obstacle();
  lcd.setCursor(0, 0);
  lcd.print(playerScore);
 }

 GameOverDisplay();
 

 
  
  
  
  
}
