enum SystemState{
  IDLE,
  DOOR_BROKEN,
  ROOM_MOTION
};

const int IR_PIN = 2;
const int PIR_PIN = 3;

SystemState currState = IDLE;

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  bool irBlocked = (digitalRead(IR_PIN) == LOW);
  bool pirMotion = (digitalRead(PIR_PIN) == HIGH);

  switch(currState){
    
    case IDLE:
              if(irBlocked) currState = DOOR_BROKEN;
              else if(pirMotion) currState = ROOM_MOTION;
              break;

    case DOOR_BROKEN:
              if(pirMotion){
                Serial.println("VALID ENTRY!");
                currState = IDLE;
                while(digitalRead(PIR_PIN) == HIGH) {
                  delay(100); .
                }  
              } 
              break;

    case ROOM_MOTION:
              if(irBlocked){
                Serial.println("VALID EXIT!");
                currState = IDLE;
                while(digitalRead(PIR_PIN) == HIGH) {
                  delay(100); .
                }    
              }
              break;
  }

}
