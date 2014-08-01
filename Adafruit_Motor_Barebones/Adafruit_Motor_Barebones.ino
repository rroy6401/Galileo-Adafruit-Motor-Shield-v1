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
//int DIR_LATCH_Pin = 12; //Register clock. Needs to be pulled high to set the output to the new shift register values, This must be pulled high directly after SRCLK has gone LOW again.
int RCLK_Pin = 12;// Alternate pin Assignment if easier to remember
//int PWM2A = 11; //Motor 1 Enable 
//int PWM1B = 10; //Servo 1 Signal
//int PWM1A = 9; //Servo 2 Signal
//int DIR_SER_Pin = 8;// The Serial Clock
int SER_Pin = 8;// Alternate
//int DIR_EN = 7; // Shift Register Enable. 
//int PWM0A = 6; //Motor 4 Enable
//int PWM0B = 5; //Motor 3 Enable
//int DIR_CLK_Pin = 4; // 
int SRCLK_Pin = 4; //Alternate

//int SER_Pin = 8;   //pin 14 on the 75HC595
//int RCLK_Pin = 9;  //pin 12 on the 75HC595
//int SRCLK_Pin = 10; //pin 11 on the 75HC595


//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void setup(){
  Serial.begin(9600);
  Serial.println("Let's begin!");
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


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

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}


void loop(){
  
  //Motor 1  
  setRegisterPin(3, HIGH); //A
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
