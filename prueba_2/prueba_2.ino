#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

const int sensorPin= A0;
void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  int value = analogRead(sensorPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10; 
  Serial.print(celsius);
  Serial.println(" C");
  delay(1000);
  if (celsius < 20 ) {

    Serial.println("Mandando mensaje");
    TembooChoreo SendSMSChoreo;

    // Invoke the Temboo client
    SendSMSChoreo.begin();

    // Set Temboo account credentials
    SendSMSChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendSMSChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendSMSChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    SendSMSChoreo.addInput("AuthToken", "5c582b1593093a71678c0cb02b236020");
    SendSMSChoreo.addInput("To", "+573138675183");
    SendSMSChoreo.addInput("From", "+17605306946");
    SendSMSChoreo.addInput("Body", "Muy frio!! " + String(celsius) + " C" + " Abrígate y concéntrate");
    SendSMSChoreo.addInput("AccountSID", "AC87d462151b3882ddaa6ddae78c579843");
    
    // Identify the Choreo to run
    SendSMSChoreo.setChoreo("/Library/Twilio/SMSMessages/SendSMS");
    
    // Run the Choreo; when results are available, print them to serial
    SendSMSChoreo.run();
    
    while(SendSMSChoreo.available()) {
      char c = SendSMSChoreo.read();
      Serial.print(c);
    }
    SendSMSChoreo.close();
  }
  if (celsius > 25 ) {

    Serial.println("Mandando mensaje");
    TembooChoreo SendSMSChoreo;

    // Invoke the Temboo client
    SendSMSChoreo.begin();

    // Set Temboo account credentials
    SendSMSChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendSMSChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendSMSChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    SendSMSChoreo.addInput("AuthToken", "5c582b1593093a71678c0cb02b236020");
    SendSMSChoreo.addInput("To", "+573138675183");
    SendSMSChoreo.addInput("From", "+17605306946");
    SendSMSChoreo.addInput("Body", "Que calor!! " + String(celsius) + " C" + " Estamos bajando la temperatura. Relajate y estudia.");
    SendSMSChoreo.addInput("AccountSID", "AC87d462151b3882ddaa6ddae78c579843");
    
    // Identify the Choreo to run
    SendSMSChoreo.setChoreo("/Library/Twilio/SMSMessages/SendSMS");
    
    // Run the Choreo; when results are available, print them to serial
    SendSMSChoreo.run();
    
    while(SendSMSChoreo.available()) {
      char c = SendSMSChoreo.read();
      Serial.print(c);
    }
    SendSMSChoreo.close();
  }

  delay(3000); // wait 30 seconds between SendSMS calls
}
