

   /* This should turn the led on pin 11 on if the button connected to pin 12 is pushed.
      Should also function to send a HIGH signal to second board when jumper is moved. */
#define INPUT_PIN 10    /*  Receiver pin from another Arduino*/
const int tosecondarduino = 7; /*  Sending PIN to second Arduino*/
//const int tosecondarduino = 8;

int test = 0;   
void setup() {

   pinMode (tosecondarduino, OUTPUT);         /* Output PIN for second Arduino*/ 
   pinMode(2, OUTPUT);                      /* LED */ 
//   pinMode(3, OUTPUT); 
//   pinMode(4, OUTPUT); 
   pinMode(INPUT_PIN, INPUT_PULLUP);        
}

void loop() {
  digitalWrite (tosecondarduino,LOW);         /*  Sending signal regularly*/
  if(test==1)
  {
    digitalWrite(2, LOW); 
    test--;
  }
    while(digitalRead(INPUT_PIN) != LOW) 
  { 
    if(test==0)
    {
      test++;
    }
    digitalWrite(2, HIGH);
  }
    digitalWrite(2, LOW);
//  if (digitalRead(10) == HIGH) digitalWrite(2, HIGH);
//  else digitalWrite(2, LOW);                  
}



