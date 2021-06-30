const int Relay[3] = {7,6,5}; // define pins
const unsigned long SECOND = 1000;
const unsigned long FIVESECONDS = 5000;
const unsigned long HOUR = 3600*SECOND;
const unsigned long DAY = 24*HOUR;
unsigned long time1 = 0;
int iter = 0;
byte pattern[3][3] = { 0,1,1,   1,0,1,   1,1,0 };                  
bool OFF = HIGH;
bool ON  = LOW; 
bool runOnStartup = true;  //  <---  TRUE makes the relay function trigger BEFORE the initial interval (when the arduino is reset/powered up)   |---  FALSE makes the relay function trigger AFTER the initial interval                  
void setup() {
  for(int i=0; i<3; i++)
  {
    pinMode(Relay[i], OUTPUT);// set pin as output 
    digitalWrite(Relay[i], HIGH); // set all relay off 
  }
   Serial.begin(9600);
   Serial.println(".");
   Serial.println(".");
   Serial.println(".");
   // Run once to start!
}
void loop() {
  unsigned long currentMillis = millis();
  if( runOnStartup == true ){
    runOnStartup = false;
    time1 = currentMillis;  // SET THE LAST RUN TIME
    runRelays();
    debugRelayText();
    iter = ( iter + 1 ) % 3;   
  }
  if( currentMillis - time1 >= FIVESECONDS ){  //  <-------  CHANGE THE TIME VALUE TO WHATEVER YOU WANT...
    //  ONE PERIOD HAS ELAPSED
    time1 = currentMillis;  // SET THE LAST RUN TIME
    runRelays();
    debugRelayText();
    iter = ( iter + 1 ) % 3;
  }   
}
void runRelays(){
  // uses iter to determine states
  for( int i = 0; i < 3; i++ ){
    digitalWrite(Relay[i],pattern[iter][i]);
  }
}
void debugRelayText(){
  // uses iter to determine states
  Serial.print(" Iteration = ");
  Serial.print( iter );
  Serial.print("  <|  ");
  for( int i = 0; i < 3; i++ ){
    Serial.print("Relay ");
    Serial.print(i);
    Serial.print(" = ");
    if( pattern[iter][i] == ON ){
      Serial.print( " ON  " );
    }else{
      Serial.print( "OFF  ");
    }
  }
  Serial.println("|>");  
}
