int sensitivity = 5; //lower values will make it more sensitive and higher values will make it less sensitive
int ledPin=9,currentPeople = 0;

int sensor1[] = {6,5};
int sensor2[] = {2,3};
int sensor1Initial;
int sensor2Initial;

String sequence = "";

int timeoutCounter = 0;

void setup() {
  //Setup code
  Serial.begin(9600);

  delay(500);
  sensor1Initial = measureDistance(sensor1);
  sensor2Initial = measureDistance(sensor2);
}

void loop() {
  //Read ultrasonic sensors
  int sensor1Val = measureDistance(sensor1);
  int sensor2Val = measureDistance(sensor2);
  
  //Process the data
  if(sensor1Val < sensor1Initial - 30 && sequence.charAt(0) != '1'){
    sequence += "1";
  }else if(sensor2Val < sensor2Initial - 30 && sequence.charAt(0) != '2'){
    sequence += "2";
  }
  
  if(sequence.equals("12")){
    currentPeople++;  
    sequence="";
    delay(500);
  }else if(sequence.equals("21") && currentPeople > 0){
    currentPeople--;  
    sequence="";
    delay(500);
  }

  //Resets the sequence if it is invalid or timeouts
  if(sequence.length() > 2 || sequence.equals("11") || sequence.equals("22") || timeoutCounter > 200){
    sequence="";  
  }

  if(sequence.length() == 1){ //
    timeoutCounter++;
  }else{
    timeoutCounter=0;
  }
  if(currentPeople>0)
    digitalWrite(ledPin,HIGH);
  else
    digitalWrite(ledPin,LOW);
  Serial.print("Count= ");
  Serial.println(currentPeople);
 

}

int measureDistance(int a[]) {
  pinMode(a[1], OUTPUT);
  digitalWrite(a[1], LOW);
  delayMicroseconds(2);
  digitalWrite(a[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(a[1], LOW);
  pinMode(a[0], INPUT);
  long duration = pulseIn(a[0], HIGH, 100000);
  return duration / 29 / 2;
}
