#include <PZEM004Tv30.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

PZEM004Tv30 pzem(4,5);//arduino
float voltage;
float current;
float power;
float energy;
float frequency;
float pf;
//LiquidCrystal_I2C lcd(0x27,20,4); // set the LCD address to 0x3F for a 16 chars and 2 line display

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte R1mood=0;
byte R2mood=0;
byte R3mood=0;
byte R4mood=0;


byte mood=3;
byte relly1=8;
byte relly2=7;
byte relly3=6;
byte relly4=2;
byte fclear=0;
int tms_set1=1;
int tms_set2=1;
int tms_set3=1;
int tms_set4=1;
int timeroc1=0;
int timeroc2=0;
int timeroc3=0;
int timeroc4=0;
float ti1=0.00;
float ti2=0.00;
float ti3=0.00;
float ti4=0.00;
byte O_V=0;
byte L_V=0;
byte O_C=0;
byte L_F=0;
byte O_F=0;
float L_PF1=0.90;
float L_PF2=0.85;
float L_PF3=0.80;
//Input & Button Logic
const int numOfInputs = 4;
const int inputPins[numOfInputs] = {12,11,10,9};
int inputState[numOfInputs];
int lastInputState[numOfInputs] = {LOW,LOW,LOW,LOW};
bool inputFlags[numOfInputs] = {LOW,LOW,LOW,LOW};
long lastDebounceTime[numOfInputs] = {0,0,0,0};
long debounceDelay = 5;

//LCD Menu Logic
const int numOfScreens = 16;
int currentScreen = 0;
String screens[numOfScreens][2] = {{"Over Voltage","Volts"}, {"Low Voltage","Volts"}, 
{"Over Current","Amper"},{"Low Frequency","Hz"},{"Over Frequency","Hz"}, {"LOW POWER FACTOR 1", "CosFi"}, {"LOW POWER FACTOR 2", "CosFi"}, {"LOW POWER FACTOR 3", "CosFi"},{"TMS1 SET", " "},{"TMS2 SET", " "},{"TMS3 SET", ""},{"TMS4 SET", " "},{"R1_Mood", " "},{"R2_Mood", " "},{"R3_Mood", " "},{"R4_Mood", " "}};

float parameters[numOfScreens];




void setup() {
 O_V=EEPROM.read(1);
 L_V=EEPROM.read(2);
 O_C=EEPROM.read(3);
 L_F=EEPROM.read(4);
 O_F=EEPROM.read(5);
 EEPROM.get(10,L_PF1);
 EEPROM.get(30,L_PF2);
 EEPROM.get(50,L_PF3);
 EEPROM.get(70,tms_set1);
 EEPROM.get(100,tms_set2);
 EEPROM.get(130,tms_set3);
 EEPROM.get(160,tms_set4);
 R1mood=EEPROM.read(190);
 R2mood=EEPROM.read(191);
 R3mood=EEPROM.read(192);
 R4mood=EEPROM.read(193);
 parameters[0]=float(O_V);
  parameters[1]=float(L_V);
  parameters[2]=float(O_C);
  parameters[3]=float(L_F);
  parameters[4]=float(O_F);
  parameters[5]=L_PF1;
  parameters[6]=L_PF2;
  parameters[7]=L_PF3;
  parameters[8]=tms_set1;
  parameters[9]=tms_set2;
  parameters[10]=tms_set3;
  parameters[11]=tms_set4;
  parameters[12]=R1mood;
  parameters[13]=R2mood;
  parameters[14]=R3mood;
  parameters[15]=R4mood;
    Serial.begin(115200);
//  lcd.begin();
  //lcd.init();                      // initialize the lcd 
  
  lcd.begin(20, 4);
  
//  lcd.backlight();
      lcd.clear();
       lcd.setCursor(5, 1);
       lcd.print("AMIR_ESHAQY");
      delay(2000);
      lcd.clear();
    // Uncomment in order to reset the internal energy counter
    // pzem.resetEnergy()
 for(int i = 0; i < numOfInputs; i++) {
    pinMode(inputPins[i], INPUT);
    digitalWrite(inputPins[i], HIGH); // pull-up 20k
  }
  pinMode(mood,INPUT);
  pinMode(relly1,OUTPUT);
  pinMode(relly2,OUTPUT);
  pinMode(relly3,OUTPUT);
  pinMode(relly4,OUTPUT);
  
  digitalWrite(relly4,HIGH);
  digitalWrite(relly3,HIGH);
  digitalWrite(relly2,HIGH);
  digitalWrite(relly1,HIGH);
}





///////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
  if(digitalRead(mood)==HIGH){
 
 save_eep();
 Reeding_par();
// rellay();
relay_new();
   // Serial.println();
    delay(50);
}else{ 
  fclear=0;
  setInputFlags();
  resolveInputFlags();
  }
}

void setInputFlags() {
  for(int i = 0; i < numOfInputs; i++) {
    int reading = digitalRead(inputPins[i]);
    if (reading != lastInputState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != inputState[i]) {
        inputState[i] = reading;
        if (inputState[i] == HIGH) {
          inputFlags[i] = HIGH;
        }
      }
    }
    lastInputState[i] = reading;
  }
}

void resolveInputFlags() {
  for(int i = 0; i < numOfInputs; i++) {
    if(inputFlags[i] == HIGH) {
      inputAction(i);
      inputFlags[i] = LOW;
      printScreen();
    }
  }
}

void inputAction(int input) {
  if(input == 0) {
    if (currentScreen == 0) {
      currentScreen = numOfScreens-1;
    }else{
      currentScreen--;
    }
  }else if(input == 1) {
    if (currentScreen == numOfScreens-1) {
      currentScreen = 0;
    }else{
      currentScreen++;
    }
  }else if(input == 2) {
    parameterChange(0);
  }else if(input == 3) {
    parameterChange(1);
  }
}

void parameterChange(int key) {
   if(key == 0 && currentScreen>=5&& currentScreen<=7) {
    parameters[currentScreen]=parameters[currentScreen]+0.01;
  }else if(key == 1 && currentScreen>=5&& currentScreen<=7) {
    parameters[currentScreen]=parameters[currentScreen]-0.01;
  }else if(key == 0 && currentScreen!=5) {
    parameters[currentScreen]++;
  }else if(key == 1 && currentScreen!=5) {
    parameters[currentScreen]--;}
O_V=byte(parameters[0]);
L_V=byte(parameters[1]);
O_C=byte(parameters[2]);
L_F=byte(parameters[3]);
O_F=byte(parameters[4]);
L_PF1=parameters[5];
L_PF2=parameters[6];
L_PF3=parameters[7];
tms_set1=parameters[8];
tms_set2=parameters[9];
tms_set3=parameters[10];
tms_set4=parameters[11];
R1mood=parameters[12];
R2mood=parameters[13];
R3mood=parameters[14];
R4mood=parameters[15];}

void printScreen() {
  lcd.clear();
  lcd.print(screens[currentScreen][0]);
  lcd.setCursor(0,1);
  lcd.print(parameters[currentScreen]);
  lcd.print(" ");
  lcd.print(screens[currentScreen][1]);
}
////////////////////////////pzem reeding prametr
void Reeding_par(){
  
      
  //  Serial.print("Custom Address:");
   // Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
    voltage = pzem.voltage();
    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    frequency = pzem.frequency();
    //pf = pzem.pf();
    if(pzem.pf()<0.1){
    pf=1.00;
    }else if(pzem.pf()>0.99){
    pf=0.00;
    }else{
    pf=pzem.pf();  
    }
    
   // Check if the data is valid
    if(isnan(voltage)){
        //Serial.println("Error reading voltage");
        lcd.clear();   
                lcd.setCursor(0, 1);
                lcd.print("Error readingVoltage");
    } else if (isnan(current)) {
      //  Serial.println("Error reading current");
        lcd.clear();   
                lcd.setCursor(0, 1);
                lcd.print("Error readingCurrent");
    } else if (isnan(power)) {
       // Serial.println("Error reading power");
        lcd.clear();   
               lcd.setCursor(0, 1);
               lcd.print("Error reading Power");
    } else if (isnan(energy)) {
       // Serial.println("Error reading energy");
        lcd.clear();   
               lcd.setCursor(0, 1);
               lcd.print("Error reading Energy");
    } else if (isnan(frequency)) {
       // Serial.println("Error reading frequency");
        lcd.clear();   
               lcd.setCursor(0, 1);
               lcd.print("Error Read Frequency");
    } else if (isnan(pf)) {
      //  Serial.println("Error reading power factor");
        lcd.clear();   
               lcd.setCursor(0, 1);
               lcd.print("ErrorReadPowerFactor");
    } else {
//Serial.print(x);Serial.print(",");

        // Print the values to the Serial console
        Serial.print(voltage);Serial.print(",");
      //  Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        lcd.setCursor(0,0);             lcd.print("V:");            lcd.setCursor(2,0);           lcd.print(voltage);
      //  Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print(current);Serial.print(",");
        lcd.setCursor(10,0);             lcd.print("I:");            lcd.setCursor(12,0);         lcd.print(current);
      //  Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print(power);Serial.print(",");
        lcd.setCursor(0,1);             lcd.print("W:");            lcd.setCursor(2,1);           lcd.print(power);     lcd.print("    ");
      //  Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print(energy,3);Serial.print(",");
        lcd.setCursor(10,1);            lcd.print("KWh:");          lcd.setCursor(14,1);          lcd.print(energy,3);  lcd.print(" ");
      //  Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print(frequency, 1);Serial.print(",");
        lcd.setCursor(0,2);             lcd.print("Hz:");            lcd.setCursor(3,2);           lcd.print(frequency, 1);
      //  Serial.print("PF: ");           Serial.println(pf);
      
        lcd.setCursor(10,2);            lcd.print("PF:");           
      /*   if(pf<0.1){
          
      Serial.println("1");
        lcd.setCursor(13,2);         lcd.print(1);
        pf=1;
          }else{
        Serial.println(pf);
        lcd.setCursor(13,2);         lcd.print(pf);}*/
        Serial.println(pf);
        lcd.setCursor(13,2);         lcd.print(pf);
        
        lcd.setCursor(0,3);             lcd.print("TMS1=");           lcd.print(tms_set1);       
}
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       

}
  void save_eep(){
     if(fclear==0){
  EEPROM.update(1, O_V);
  EEPROM.update(2, L_V);
  EEPROM.update(3, O_C);
  EEPROM.update(4, L_F);
  EEPROM.update(5, O_F);
  EEPROM.put(10, L_PF1);
  EEPROM.put(30, L_PF2);
  EEPROM.put(50, L_PF3);
  EEPROM.put(70,tms_set1);
  EEPROM.put(100,tms_set2);
  EEPROM.put(130,tms_set3);
  EEPROM.put(160,tms_set4);
  EEPROM.put(190,R1mood);
  EEPROM.put(191,R2mood);
  EEPROM.put(192,R3mood);
  EEPROM.put(193,R4mood);
  
  lcd.clear();
  fclear=1;}
    }
void relay_new(){
switch (R1mood) {
    case 1:
    //tms_On
    if(current>O_C){
    timeroc1++;
    ti1=(0.14*float(tms_set1))/(pow(current/float(O_C),0.02)-1);
    if(timeroc1>=ti1){
    timeroc1==ti1;
      digitalWrite(relly1,LOW);
      }
   }else{
      digitalWrite(relly1,HIGH);
       timeroc1=0;  
         }
   break;
   case 2:
      if(current>O_C){
      timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
       timeroc1=0;  
         }
    break;
    case 3:
      if(voltage>O_V){
      timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
       digitalWrite(relly1,HIGH);
       timeroc1=0;  
         }
   break;
   case 4:
    if(voltage<L_V){
        timeroc1++;
    if(timeroc1>=tms_set1){
        timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
        timeroc1=0;  
         }
  break;
  case 5:
    if(frequency<L_F){
    timeroc1++;
    if(timeroc1>=tms_set1){
       timeroc1==tms_set1;
       digitalWrite(relly1,LOW);
      }
   }else{
       digitalWrite(relly1,HIGH);
       timeroc1=0;  
         }
  break;
  case 6:
    if(frequency>O_F){
    timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
      digitalWrite(relly1,LOW);
      }
   }else{
      digitalWrite(relly1,HIGH);
      timeroc1=0;  
         }
  break;
  case 7:
    if(voltage>O_V||voltage<L_V||current>O_C||frequency<L_F||frequency>O_F){
    timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
      digitalWrite(relly1,LOW);
      }
   }else{
      digitalWrite(relly1,HIGH);
      timeroc1=0;  
         }
  break;
  case 8:
    if(pf<L_PF1){
    timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
       timeroc1=0;  
         }
  break;
  case 9:
    if(pf<L_PF2){
    timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
       timeroc1=0;  
         }
  break;
  case 10:
    if(pf<L_PF3){
    timeroc1++;
    if(timeroc1>=tms_set1){
      timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
        timeroc1=0;  
         }
  break;
  case 11:
    if(voltage>O_V||voltage<L_V){
    timeroc1++;
    if(timeroc1>=tms_set1){
        timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
        timeroc1=0;  
         }
  break;
  case 12:
    if(frequency<L_F||frequency>O_F){
    timeroc1++;
    if(timeroc1>=tms_set1){
        timeroc1==tms_set1;
        digitalWrite(relly1,LOW);
      }
   }else{
        digitalWrite(relly1,HIGH);
        timeroc1=0;  
         }
  break;
 default: 
      digitalWrite(relly1,HIGH);
  break;
  }
switch (R2mood) {
    case 1:
    //tms_On
    if(current>O_C){
    timeroc2++;
    ti2=(0.14*float(tms_set2))/(pow(current/float(O_C),0.02)-1);
    //Serial.println(tms);
    if(timeroc2>=ti2){
     timeroc2==ti2;
   // Serial.println("on erlly");
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
      break;
    case 2:
      if(current>O_C){
    timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
      break;
    case 3:
    if(voltage>O_V){
      timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 4:
    if(voltage<L_V){
      timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 5:
    if(frequency<L_F){
       timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 6:
     if(frequency>O_F){
       timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 7:
    if(voltage>O_V||voltage<L_V||current>O_C||frequency<L_F||frequency>O_F){
    timeroc2++;
    //Serial.println(tms);
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
   // Serial.println("on erlly");
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 8:
     if(pf<L_PF1){
       timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 9:
     if(pf<L_PF2){
       timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 10:
     if(pf<L_PF3){
      timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 11:
     if(voltage>O_V||voltage<L_V){
     timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
    case 12:
     if(frequency<L_F||frequency>O_F){
       timeroc2++;
    if(timeroc2>=tms_set2){
      timeroc2==tms_set2;
      digitalWrite(relly2,LOW);
      }
   }else{
      digitalWrite(relly2,HIGH);
       timeroc2=0;  
         }
  break;
 default: 
      digitalWrite(relly2,HIGH);
    break;
  }
  switch (R3mood) {
    case 1:
    //tms_On
    if(current>O_C){
    timeroc3++;
    ti3=(0.14*float(tms_set3))/(pow(current/float(O_C),0.02)-1);
    //Serial.println(tms);
    if(timeroc3>=ti3){
     timeroc3==ti3;
   // Serial.println("on erlly");
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
      break;
    case 2:
      if(current>O_C){
    timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
      break;
    case 3:
    if(voltage>O_V){
      timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 4:
    if(voltage<L_V){
      timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 5:
    if(frequency<L_F){
     timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 6:
     if(frequency>O_F){
      timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 7:
    if(voltage>O_V||voltage<L_V||current>O_C||frequency<L_F||frequency>O_F){
    timeroc3++;
    //Serial.println(tms);
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
   // Serial.println("on erlly");
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 8:
     if(pf<L_PF1){
      timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 9:
     if(pf<L_PF2){
     timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 10:
     if(pf<L_PF3){
     timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 11:
     if(voltage>O_V||voltage<L_V){
      timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
    case 12:
     if(frequency<L_F||frequency>O_F){
   timeroc3++;
    if(timeroc3>=tms_set3){
      timeroc3==tms_set3;
      digitalWrite(relly3,LOW);
      }
   }else{
      digitalWrite(relly3,HIGH);
       timeroc3=0;  
         }
  break;
 default: 
      digitalWrite(relly3,HIGH);
    break;
  }
switch (R4mood) {
    case 1:
    //tms_On
    if(current>O_C){
    timeroc4++;
    ti4=(0.14*float(tms_set4))/(pow(current/float(O_C),0.02)-1);
    //Serial.println(tms);
    if(timeroc4>=ti4){
     timeroc4==ti4;
   // Serial.println("on erlly");
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
      break;
    case 2:
      if(current>O_C){
    timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
      break;
    case 3:
    if(voltage>O_V){
    timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 4:
    if(voltage<L_V){
     timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 5:
    if(frequency<L_F){
     timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 6:
     if(frequency>O_F){
     timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 7:
    if(voltage>O_V||voltage<L_V||current>O_C||frequency<L_F||frequency>O_F){
    timeroc4++;
    //Serial.println(tms);
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
   // Serial.println("on erlly");
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 8:
     if(pf<L_PF1){
      timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 9:
     if(pf<L_PF2){
     timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 10:
     if(pf<L_PF3){
     timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 11:
     if(voltage>O_V||voltage<L_V){
      timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
    case 12:
     if(frequency<L_F||frequency>O_F){
      timeroc4++;
    if(timeroc4>=tms_set4){
      timeroc4==tms_set4;
      digitalWrite(relly4,LOW);
      }
   }else{
      digitalWrite(relly4,HIGH);
       timeroc4=0;  
         }
  break;
 default: 
      digitalWrite(relly4,HIGH);
    break;
  }
}
