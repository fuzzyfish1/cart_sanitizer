/*
set up our pins
*/
int extledpin = 5;
int bumperpin = 2;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(extledpin,OUTPUT);
  pinMode(bumperpin,INPUT);
  digitalWrite(LED_BUILTIN, HIGH);

}

void loop() {

  if(digitalRead(bumperpin) == HIGH){
    digitalWrite(extledpin,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
  }
  else{
    digitalWrite(extledpin,LOW);
    digitalWrite(LED_BUILTIN,LOW);  
  }

 
}
