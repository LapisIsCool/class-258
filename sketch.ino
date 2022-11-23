#include <ezButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//  button objects
ezButton button1(13);
ezButton button2(33);
ezButton button3(14);
ezButton button4(27);
ezButton button5(26);

int vote1 = 0, vote2 = 0, vote3 = 0, vote4 = 0;

int buttonState = 0;

int flag = 0;

int voting_completed = 0;

void setup()
{
  Serial.begin(9600);

  button1.setDebounceTime(25);
  button2.setDebounceTime(25);
  button3.setDebounceTime(25);
  button4.setDebounceTime(25);
  button5.setDebounceTime(25);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  };

  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);         // set text size
  oled.setTextColor(WHITE);    // set text color

  oled.setCursor(2, 5); 
  oled.println("Start");       // set position to display
  oled.setCursor(2, 21); 
  oled.println("voting..");   
  oled.display();             // display on OLED
  delay(2000);
}

void loop() {

  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();

   if (flag == 0) {
   // set text
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);         // set text size
    oled.setTextColor(WHITE);    // set text color

    oled.setCursor(2, 0);       // set position to display
    oled.println("A - Green ");
    oled.setCursor(2, 16);       // set position to display
    oled.println("B - Yellow");
    oled.setCursor(2, 32);       // set position to display
    oled.println("C - Red");     // display on OLED
    oled.setCursor(2, 48);       // set position to display
    oled.println("D - Orange");
    oled.display();
    flag=1;
  }

  if (voting_completed == 0 && flag==1) {
    if (button1.isPressed()) {
      vote1++;
      // Serial.println(vote1);
    }
    else if (button2.isPressed()) {
      vote2++;
      // Serial.println(vote2);
    }
    else if (button3.isPressed()) {
      vote3++;
      // Serial.println(vote3);
    }
    else if (button4.isPressed()) {
      vote4++;
      // Serial.println(vote4);
    }
    else if (button5.isPressed()) {
      voting_completed = 1;
      show_votes();
    }
  }

  delay(10);
}

void show_votes(){
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);

  oled.setCursor(2,0);
  oled.print("A'");
  oled.setCursor(50,0);
  oled.print(vote1);

  oled.setCursor(2,16);
  oled.print("B'");
  oled.setCursor(50,16);
  oled.print(vote2);

  oled.setCursor(2,32);
  oled.print("C'");
  oled.setCursor(50,32);
  oled.print(vote3);

  oled.setCursor(2,48);
  oled.print("D'");
  oled.setCursor(50,48);
  oled.print(vote4);

  oled.display();
  delay(5000);

  winner();
}

void winner(){
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(32,28);

  if ((vote1>vote2 && vote1>vote3 && vote1>vote4)){
    oled.print("A WON");
  }
  else if ((vote2>vote1 && vote2>vote3 && vote2>vote4)){
    oled.print("B WON");
  }
  else if ((vote3>vote1 && vote3>vote2 && vote3>vote4)){
    oled.print("C WON");
  }
  else if ((vote4>vote1 && vote4>vote2 && vote4>vote3)){
    oled.print("D WON");
  }
  else {
    oled.print("TIE");
  }

  oled.display();
  delay(1000);
}