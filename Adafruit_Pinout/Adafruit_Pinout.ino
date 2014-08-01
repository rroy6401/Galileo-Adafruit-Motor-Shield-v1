/*
A barebones sketch for use with the Adafruit Motor Shield v1. Allowing you to bypass the 
library or use with a Galileo
CAUTION: Do not use Adafruit Motor Shield v2, the pin mapping is completely different! 
You could damage your Galileo, Arduino, or shield!
Credit goes to Bildr.org for their awesome shift register tutorial and the basic shift register code
*/

/*
Shift Register Pin Out Reference
QA = Motor 3A
QB = Motor 2A
QC = Motor 1A
QD = Motor 1B
QE = Motor 2B
QF = Motor 4A
QG = Motor 3B
QH = Motor 4B
*/
// Pin Assignments
#define DIR_LATCH 12 //Register clock. Needs to be pulled high to set the output to the new shift register values, This must be pulled high directly after SRCLK has gone LOW again.
#define RCLK 12// Alternate pin Assignment if easier to remember
#define PWM2A 11 //Motor 1 Enable 
#define PWM1B 10 //Servo 1 Signal
#define PWM1A 9 //Servo 2 Signal
#define DIR_SER 8// The Serial Clock
#define SER 8// Alternate
#define DIR_EN 7 // Shift Register Enable. 
#define PWM0A 6 //Motor 4 Enable
#define PWM0B 5 //Motor 3 Enable
#define DIR_CLK 4 // 
#define SCK 4 //Alternate

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void setup(){
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SCK, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
}               


//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SCK, LOW);

    int val = registers[i];

    digitalWrite(SER, val);
    digitalWrite(SCK, HIGH);

  }
  digitalWrite(RCLK, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}


void loop(){

  //Motor 1  
  setRegisterPin(3, LOW); //A
  setRegisterPin(4, LOW); //B
  
  //Motor 2
  setRegisterPin(2, LOW); //A
  setRegisterPin(5, LOW); //B
  
  //Motor 3
  setRegisterPin(1, LOW); //A
  setRegisterPin(7, LOW); //B
  
  //Motor 4
  setRegisterPin(6, LOW); //A
  setRegisterPin(8, LOW); //B

  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}
