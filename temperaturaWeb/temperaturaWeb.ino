#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h> 
BridgeServer server;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}
void loop() {
  BridgeClient client = server.accept();
  if (client) {
    String command = client.readString();
    command.trim();
    if (command == "temperature") {
      int value = analogRead(A0);
    float millivolts = (value / 1023.0) * 5000;
    float celsius = millivolts / 10; 
      client.print(celsius);
    }
    client.stop();
  }
  delay(50);
}
