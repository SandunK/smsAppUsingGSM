#include <SoftwareSerial.h>

SoftwareSerial SIM800(3, 2); //  TX,RX

String message;

void ShowSerialData()
{
 while(SIM800.available()!=0)
   Serial.write(SIM800.read());
}

void setup()
{
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  SIM800.begin(9600);
  
}

void loop(){
  String messageGot = readSerial();
  String key, stringVal, number;

  for (int i = 0; i < messageGot.length(); i++) {
    if (messageGot.substring(i, i+1) == ":") {
      key = messageGot.substring(0, i);
      stringVal = messageGot.substring(i+1);
      break;
    }
  }

 
  if (key == "msg"){
    message=stringVal;
    Serial.println("Message received");
    //Serial.println(stringVal);

  } else if (key == "num") {
    //numbers[i]=stringVal
    String result = sendSMS(stringVal);
    //if (result){
      //Serial.println("success");
    //}
  }
  
  
  //delay(500);
  
}

String readSerial(){
  // serial read section
  String readString;
  while (Serial.available()) {
    delay(90);  //delay to allow buffer to fill 
    
    if (Serial.available() >0){
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }
  }
  if (readString.length() >0){
    //Serial.print("Arduino received: ");  
    //Serial.println(readString); //see what was received
    Serial.flush();
  }

  return readString;
}

String sendSMS(String num){
  SIM800.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  SIM800.print("AT+CMGS=\"+94"+num+"\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  SIM800.print(message);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  SIM800.print((char)26);// (required according to the datasheet)
  return "success";
}


