#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(38,16,2);

const int numButtons = 6;
const int buttonPins[numButtons] = {11, 12, 13 , A0, A1, A2}; 

int buttonStates[numButtons] = {HIGH};
int lastButtonStates[numButtons] = {HIGH};
int buttonCounters[numButtons] = {0};

char k[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};


 
byte rpins[4]={2,3,4,5};
byte cpins[4]={6,7,8,9};
char myk;
Keypad mypad (makeKeymap(k),rpins,cpins,4,4);
char pass[]={'1','3','4','5'};
char upass[sizeof(pass)]={0};
byte counter=0,j=0;

void reslcd(){
 lcd.home();
 lcd.clear();
 lcd.print("Enter password");
 lcd.setCursor(0,1);
}

void setup() {
  pinMode(10,OUTPUT);
  pinMode(11,INPUT_PULLUP);
 lcd.init();
 lcd.backlight();
 for (int i = 0; i < numButtons; ++i) {
 pinMode(buttonPins[i], INPUT_PULLUP);
   }
   
 reslcd();

}
void loop() {
  myk=mypad.getKey();
  if(myk=='D'){
    lcd.clear();  
    lcd.home();
    for(j=0;j<sizeof(upass);j++){
      if(upass[j]!=pass[j])break;}
  if((j==sizeof(upass))&&(counter==0)){
  counter=-1;
  lcd.clear();
  lcd.home();
  lcd.print("User authorized");
  digitalWrite(10,1);
  delay(3000);
  digitalWrite(10,0);
  reslcd();
  }
  else {
  counter=-1;
  lcd.clear();
  lcd.home();
  lcd.print("Wrong password");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter your finger");
  delay(2000);
  reslcd();
  }  
  }
  else if(myk){
    *(upass+counter)=myk;
    lcd.print("*");
    counter=(counter>=3)?-1:counter;
 	counter++; 
  }
    for (int i = 0; i < numButtons; ++i) {
    buttonStates[i] = digitalRead(buttonPins[i]);

    if (buttonStates[i] == LOW && lastButtonStates[i] == HIGH) {
      buttonCounters[i]++;
      updateLCD(i);
    }

    lastButtonStates[i] = buttonStates[i];
  }
}

void updateLCD(int buttonIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The ID is : ");
  lcd.print(buttonIndex + 1);  
  delay(1000);
}
