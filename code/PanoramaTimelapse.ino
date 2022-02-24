#include <LiquidCrystal.h>
#include "Servo.h"


Servo myServo;
float angle = 0;

//ServoTimer2 myServo;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //Angabe der erforderlichen Pins
 
// erstellen einiger Variablen
int Taster = 0;
int Analogwert = 0;
#define Tasterrechts 0
#define Tasteroben 1
#define Tasterunten 2
#define Tasterlinks 3
#define Tasterselect 4
#define KeinTaster 5

 
// Ab hier wird ein neuer Programmblock mit dem Namen "Tasterstatus" erstellt. Hier wird ausschließlich geprüft, welcher Taster gedrückt ist.
int Tasterstatus()
{
Analogwert = analogRead(A0); // Auslesen der Taster am Analogen Pin A0.
if (Analogwert > 1000) return KeinTaster;
if (Analogwert < 50) return Tasterrechts;
if (Analogwert < 195) return Tasteroben;
if (Analogwert < 380) return Tasterunten;
if (Analogwert < 555) return Tasterlinks;
if (Analogwert < 790) return Tasterselect;
 
return KeinTaster; // Ausgabe wenn kein Taster gedrückt wurde.
}
// Hier wird der Programmblock "Tasterstatus" abeschlossen.

unsigned long initializingTime = 0;
int numberOfShots = 0;
int targetShots = 5;
int interval = 7;
int targetAngle = 90;
float teiler = 0;

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void setup()
{
// init LCD display
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0);
// print welcome screen))
lcd.print("Benjis Panorama");
lcd.setCursor(0, 1);
lcd.print("Timelapse");
delay(2000);
lcd.clear();


myServo.attach(3);
myServo.write(angle);
delay(150);

  
//lcd.begin(16, 2); // Starten der Programmbibliothek.
lcd.setCursor(0,0); // Angabe des Cursorstartpunktes oben links.
lcd.print("Interval [s]"); // Ausgabe des Textes "Nachricht".


lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
lcd.print(interval); // Ausgabe des Textes "Nachricht".

int weiter = 0;
if ( weiter == 0 ) {
  
}
while (weiter == 0) {
  lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
  Taster = Tasterstatus();
  switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
  {
  case Tasteroben:
  {
  interval = interval + 1 ;
  delay(200);
  lcd.print(interval);
  break;
  }
  case Tasterunten:
  {
  interval = interval - 1 ;
  delay(200);
  lcd.print(interval);
  break;
  }
  case Tasterrechts: // Wenn die rechte Taste gedrückt wurde...
  {
  lcd.print("Weiter ...  "); //Erscheint diese Zeile. Die Leerzeichen hinter dem Text sorgen dafür, dass der vorherige Text in der Zeile gelöscht wird.
  weiter = 1;
  break;
  }
  case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
  {
  resetFunc();  //call reset
  break;
  }
}
}

delay(500);
lcd.clear();



lcd.setCursor(0,0); // Angabe des Cursorstartpunktes oben links.
lcd.print("Angle [Degree]"); // Ausgabe des Textes "Nachricht".

lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
lcd.print(targetAngle); // Ausgabe des Textes "Nachricht".

weiter = 0;

while (weiter == 0) {
  lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
  Taster = Tasterstatus();
  switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
  {
  case Tasteroben:
  {
  targetAngle = targetAngle + 5 ;
  delay(200);
  lcd.print(targetAngle);
  break;
  }
  case Tasterunten:
  {
  targetAngle = targetAngle - 5 ;
  delay(200);
  lcd.print(targetAngle);
  break;
  }
  case Tasterrechts: // Wenn die rechte Taste gedrückt wurde...
  {
  lcd.print("Weiter ...  "); //Erscheint diese Zeile. Die Leerzeichen hinter dem Text sorgen dafür, dass der vorherige Text in der Zeile gelöscht wird.
  weiter = 1;
  break;
  }
  case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
  {
  resetFunc();  //call reset
  break;
  }
}
}

delay(500);
lcd.clear();



lcd.setCursor(0,0); // Angabe des Cursorstartpunktes oben links.
lcd.print("Shots [#]"); // Ausgabe des Textes "Nachricht".

lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
lcd.print(targetShots); // Ausgabe des Textes "Nachricht".

weiter = 0;

while (weiter == 0) {
  lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
  Taster = Tasterstatus();
  switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
  {
  case Tasteroben:
  {
  targetShots = targetShots + 5 ;
  delay(200);
  lcd.print(targetShots);
  break;
  }
  case Tasterunten:
  {
  targetShots = targetShots - 5 ;
  delay(200);
  lcd.print(targetShots);
  break;
  }
  case Tasterrechts: // Wenn die rechte Taste gedrückt wurde...
  {
  lcd.clear();
  lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
  lcd.print("Start ...  "); //Erscheint diese Zeile. Die Leerzeichen hinter dem Text sorgen dafür, dass der vorherige Text in der Zeile gelöscht wird.
  weiter = 1;
  break;
  }
  case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
  {
  resetFunc();  //call reset
  break;
  }
}
}



pinMode(12, OUTPUT);          // initialize output pin for camera release

teiler = targetAngle / (targetShots-1);


delay(1000);
lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
lcd.print("Start ..     ");

delay(1000);
lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
lcd.print("Start .      ");

delay(1000);
lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
lcd.print("Start        ");
delay(1000);


lcd.clear();
}


 
void loop()
{

Taster = Tasterstatus();
lcd.setCursor(0,1); // Angabe des Cursorstartpunktes oben links.
switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
{
  case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
    {
    resetFunc();  //call reset
    lcd.print("Reset ...");
    delay(1000);
    break;
    }
}

lcd.setCursor(0,0); // Bewegt den Cursor and die Stelle "0" in Zeile 2.
lcd.print("Running ...");

lcd.setCursor(0,1); // Bewegt den Cursor and die Stelle "0" in Zeile 2.
numberOfShots = numberOfShots + 1;

digitalWrite(12, HIGH);
delay(1100); // Ausgleich für genutzte Kamera
lcd.print(numberOfShots);

delay((interval/2) * 1000 - 1100); // Ausgleich wieder abziehen
digitalWrite(12, LOW);

if (numberOfShots < targetShots) {
  angle = angle + teiler;
  myServo.write(angle);
  delay((interval/2) * 1000);
} 
else {
  lcd.clear();
  lcd.setCursor(0,1); // Bewegt den Cursor and die Stelle "0" in Zeile 2.
  lcd.print("Finished :)");
  delay(2000);
  
  for (angle; angle >= 0; angle -= 1) {
    myServo.write(angle);
    delay(20);
  }
  resetFunc();
}

} //Loop beenden
