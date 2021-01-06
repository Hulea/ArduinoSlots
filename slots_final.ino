#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); //rs, enable, d4, d5, d6, d7

byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
byte alien[8] = {
  B01010,
  B11111,
  B10101,
  B11111,
  B11011,
  B01110,
  B01010,
  B11011
};
byte diamond[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
byte king[8] = {
  B00000,
  B10101,
  B11111,
  B11111,
  B10101,
  B11111,
  B01010,
  B00100
};
byte dollar[8] = {
  B00100,
  B01111,
  B10100,
  B01110,
  B00101,
  B11110,
  B00100,
  B00000
};
byte crab[8] = {
  B10001,
  B10001,
  B11011,
  B01110,
  B01110,
  B11011,
  B10001,
  B10001
};
byte fill[8] = {
  B01110,
  B10001,
  B10001,
  B00010,
  B00100,
  B00100,
  B00000,
  B00100
};


const int buttonPin = 8;
const int buttonPin2 = 9;
const int buttonPin3 = 11;
const int ledPin1 = 12;
const int ledPin2 = 13;
const int buzzerPin = 10;

const int crab_value = 1;
const int heart_value = 2;
const int alien_value = 3;
const int dollar_value = 4;
const int diamond_value = 5;
const int king_value = 6;

int fill_counter = 0;
int crab_counter = 0;
int heart_counter = 0;
int alien_counter = 0;
int dollar_counter = 0;
int diamond_counter = 0;
int king_counter = 0;

volatile int score = 100;
int old_score = 0;

bool start = false;

int bet = 0;
volatile int toDouble = 0;
bool doubleStatus = false;

int global_rand_arr_index = 0;
//int random_blacks_and_reds[255] = {0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1};
int random_blacks_and_reds[255];

int fail_sound_check = 0;

void setup()
{

  pinMode(buttonPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  randomSeed(analogRead(0));

  lcd.begin(16 , 2); //Initialize 16x2 lcd
  lcd.clear();       //Clear lcd display screen

  lcd.createChar(1 , heart);
  lcd.createChar(2 , alien);
  lcd.createChar(3 , diamond);
  lcd.createChar(4 , king);
  lcd.createChar(5 , dollar);
  lcd.createChar(6 , crab);
  lcd.createChar(7 , fill);

}


void dbl(bool doubleStatus, int toDouble)
{
  //double
  int counter = 0;
  bool wrong_color = false;
  while (doubleStatus == true && counter <= 5 && digitalRead(buttonPin) == LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DOUBLE?");
    lcd.setCursor(0, 1);
    lcd.print(toDouble);

     for(int i=1;i<255;i++)
          random_blacks_and_reds[i] = random(i) % 2;


    int b_or_r = random_blacks_and_reds[global_rand_arr_index];
    //    lcd.setCursor(0, 0);
    //    lcd.print(global_rand_arr_index);
    lcd.setCursor(15, 1);
    lcd.print(b_or_r);
    delay(100);


    /////0 = red
    /////1 = black

    if (b_or_r == 0 && counter < 5)
    {
      if (digitalRead(buttonPin2) == HIGH)
      {
        counter ++;
        global_rand_arr_index++;
        toDouble += toDouble;
        digitalWrite(ledPin2, HIGH);
        tone(buzzerPin, 400);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 600);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 400);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 600);
        delay(50);
        noTone(buzzerPin);
        digitalWrite(ledPin2, LOW);
      }

      if (digitalRead(buttonPin3) == HIGH)
      {
        wrong_color = true;
        doubleStatus = false;
        digitalWrite(ledPin1, HIGH);
        tone(buzzerPin, 200);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 150);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 200);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 100);
        delay(50);
        noTone(buzzerPin);
        digitalWrite(ledPin1, LOW);
      }

    }
    else if (b_or_r == 1 && counter < 5)
    {
      if (digitalRead(buttonPin3) == HIGH)
      {
        counter++;
        global_rand_arr_index++;
        toDouble += toDouble;
        digitalWrite(ledPin2, HIGH);
        tone(buzzerPin, 400);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 600);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 400);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 600);
        delay(50);
        noTone(buzzerPin);
        digitalWrite(ledPin2, LOW);
      }

      if (digitalRead(buttonPin2) == HIGH)
      {
        wrong_color = true;
        doubleStatus = false;
        digitalWrite(ledPin1, HIGH);
        tone(buzzerPin, 200);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 150);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 200);
        delay(50);
        noTone(buzzerPin);
        tone(buzzerPin, 100);
        delay(50);
        noTone(buzzerPin);
        digitalWrite(ledPin1, LOW);
      }
    }
    else
    {
      doubleStatus = false;
    }
  }

  if (wrong_color == true)
    toDouble = 0;

  lcd.setCursor(0, 1);
  lcd.print(toDouble);

  if (toDouble < 100)
  {
    lcd.setCursor(2, 1);
    lcd.clear();
  }

  if (toDouble < 10)
  {
    lcd.setCursor(1, 1);
    lcd.clear();
  }

  if (counter == 5) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1500);
    delay(100);
    
    noTone(buzzerPin);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }

  lcd.setCursor(0, 1);
  lcd.print("+");
  lcd.print(toDouble);
  delay(1000);
  lcd.setCursor(11, 1);
  lcd.print(score);
  delay(1000);
  if (toDouble == 0) {
    score -= bet;

  }
  else score += toDouble;
  lcd.setCursor(11, 1);
  lcd.print(score);

  delay(1000);
}



void loop()
{
  if (start == false)
  {
    lcd.setCursor(0, 0);
    lcd.print("PRESS");
    lcd.setCursor(0, 1);
    lcd.print("BUTTON 1");
  }

  lcd.setCursor(9, 0);
  lcd.print(bet / 10);

  lcd.setCursor(11, 0);
  lcd.print("SCORE");
  lcd.setCursor(11, 1);
  lcd.print(score);



  if (score <= 0)
  {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(0, 1);
    lcd.print("ROLL TO REPLAY");
    delay(100);

    while (fail_sound_check <= 10)
    {
      tone(buzzerPin, 200);
      delay(50);
      noTone(buzzerPin);
      tone(buzzerPin, 100);
      delay(50);
      noTone(buzzerPin);
      fail_sound_check++;
    }


    if (digitalRead(buttonPin) == HIGH)
    {
      lcd.clear();
      score += 100;
    }

  }
  else {

    fail_sound_check = 0;
    if (digitalRead(buttonPin) == HIGH) {

      start = true;
      lcd.clear();

      lcd.setCursor(11, 0);
      lcd.print("SCORE");
      lcd.setCursor(11, 1);
      lcd.print(score);

      int prev_rand_val = 0;
      fill_counter = 0;
      crab_counter = 0;
      heart_counter = 0;
      alien_counter = 0;
      dollar_counter = 0;
      diamond_counter = 0;
      king_counter = 0;

      for (int row_i = 0; row_i <= 1; row_i++)
        for (int i = 0; i < 8; i++)
        {
          lcd.setCursor(i, row_i);

          int random_value = random(7) + 1;

          if (random_value == 1)
            heart_counter++;
          if (random_value == 2)
            alien_counter++;
          if (random_value == 3)
            diamond_counter++;
          if (random_value == 4)
            king_counter++;
          if (random_value == 5)
            dollar_counter++;
          if (random_value == 6)
            crab_counter++;
          if (random_value == 7)
            fill_counter++;

          tone(buzzerPin, 500);//mhz
          delay(25);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, HIGH);
          delay(25);
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, LOW);

          noTone(buzzerPin);
          delay(25);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, HIGH);
          delay(25);
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, LOW);

          tone(buzzerPin, 250);//mhz
          delay(25);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, HIGH);
          delay(25);
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, LOW);

          noTone(buzzerPin);
          delay(25);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, HIGH);
          delay(25);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);

          lcd.write(random_value);


        }

      //delay(1000);

      int max_aux = 0;
      int max_index = 0;

      if (heart_counter >= 5)
      {
        heart_counter += fill_counter;
        if (heart_counter > max_aux)
        {
          max_aux = heart_counter;
          max_index = heart_value;
        }
      }
      if (alien_counter >= 5)
      {
        alien_counter += fill_counter;
        if (alien_counter > max_aux)
        {
          max_aux = alien_counter;
          max_index = alien_value;
        }
      }
      if (diamond_counter >= 5)
      {
        diamond_counter += fill_counter;
        if (diamond_counter > max_aux)
        {
          max_aux = diamond_counter;
          max_index = diamond_value;
        }
      }
      if (king_counter >= 5)
      {
        king_counter += fill_counter;
        if (king_counter > max_aux)
        {
          max_aux = king_counter;
          max_index = king_value;
        }
      }
      if (dollar_counter >= 5)
      {
        dollar_counter += fill_counter;
        if (dollar_counter > max_aux)
        {
          max_aux = dollar_counter;
          max_index = dollar_value;
        }
      }
      if (crab_counter >= 5)
      {
        crab_counter += fill_counter;
        if (crab_counter > max_aux)
        {
          max_aux = crab_counter;
          max_index = crab_value;
        }
      }

      //if (max_aux != 0) {

      //score += max_aux * max_index * (bet/10);
      int toDouble = max_aux * max_index * (bet / 10);

      if (toDouble != 0)
      {
        doubleStatus = true;
        delay(4000);
        dbl(doubleStatus, toDouble);
      }
      //}
      else score -= bet;
      //score -= bet;

      lcd.setCursor(11, 0);
      lcd.print("SCORE");
      lcd.setCursor(11, 1);
      lcd.print(score);

      if (score < 100)
      {
        lcd.setCursor(13, 1);
        lcd.print(" ");
      }
      if (score < 10 && score > -1)
      {
        lcd.setCursor(12, 1);
        lcd.print(" ");
      }


    }
    else {
      // turn LED off:
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);

    }
  }





  //set bet
  if (start == false)
  {
    if (digitalRead(buttonPin2) == HIGH && (bet + 10 <= 100))
    {
      bet += 10;
      tone(buzzerPin, 600);
      delay(200);
      noTone(buzzerPin);
    }
    if (digitalRead(buttonPin3) == HIGH && (bet - 10 > 0))
    {
      bet -= 10;
      lcd.setCursor(10, 0);
      lcd.print(" ");
      tone(buzzerPin, 300);
      delay(200);
      noTone(buzzerPin);
    }
  }






}
