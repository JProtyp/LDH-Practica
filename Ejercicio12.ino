/** 
 *  * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik Ekblad
 * 
 * DESCRIPTION
 * Example sketch for a "light switch" where you can control light or something 
 * else from both HA controller and a local physical button 
 * (connected between digital pin 3 and GND).
 * This node also works as a repeader for other nodes
 * http://www.mysensors.org/build/relay
 */ 

// Enable debug prints to serial monitor
#define MY_DEBUG 

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

#define MY_RF24_CHANNEL 89
// To set the node ID
#define MY_NODE_ID 12
// Enabled repeater feature for this node
#define MY_REPEATER_FEATURE

#include <SPI.h>
#include <MySensors.h>
#include <Bounce2.h>

#define RELAY_PIN  4  // Arduino Digital I/O pin number for relay 
#define BUTTON_PIN  3  // Arduino Digital I/O pin number for button 
#define RELAY_PIN2  6  // Arduino Digital I/O pin number for relay 
#define BUTTON_PIN2  5  // Arduino Digital I/O pin number for button 
#define CHILD_ID 1   // Id of the sensor child
#define CHILD_ID2 2   // Id of the sensor child
#define RELAY_ON 1
#define RELAY_OFF 0

Bounce debouncer = Bounce(); 
Bounce debouncer2 = Bounce(); 
int oldValue=0;
int oldValue2=0;
bool state;

MyMessage msg(CHILD_ID,V_LIGHT);
MyMessage msg2(CHILD_ID2,V_LIGHT);

void setup()  
{  
  // Setup the button
  pinMode(BUTTON_PIN,INPUT);
  // Activate internal pull-up
  digitalWrite(BUTTON_PIN,HIGH);
    // Setup the button
  pinMode(BUTTON_PIN2,INPUT);
  // Activate internal pull-up
  digitalWrite(BUTTON_PIN2,HIGH);

  // After setting up the button, setup debouncer
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5);
  debouncer2.attach(BUTTON_PIN2);
  debouncer2.interval(5);

  // Make sure relays are off when starting up
  digitalWrite(RELAY_PIN, RELAY_OFF);
  // Then set relay pins in output mode
  pinMode(RELAY_PIN, OUTPUT);  
    // Make sure relays are off when starting up
  digitalWrite(RELAY_PIN2, RELAY_OFF);
  // Then set relay pins in output mode
  pinMode(RELAY_PIN2, OUTPUT);    

  // Set relay to last known state (using eeprom storage) 
  state = loadState(CHILD_ID);
  digitalWrite(RELAY_PIN, state?RELAY_ON:RELAY_OFF);
    // Set relay to last known state (using eeprom storage) 
  state = loadState(CHILD_ID2);
  digitalWrite(RELAY_PIN2, state?RELAY_ON:RELAY_OFF);
}

void presentation()  {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Relay & Button", "1.0");

  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID, S_LIGHT); 
  present(CHILD_ID2, S_LIGHT);
}

/*
*  Example on how to asynchronously check for new messages from gw
*/
void loop() 
{
  debouncer.update();
  debouncer2.update();
  // Get the update value
  int value = debouncer.read();
  if (value != oldValue && value==0) {
      send(msg.set(state?false:true), true); // Send new state and request ack back
  }
  oldValue = value;
  int value2 = debouncer2.read();
  if (value2 != oldValue2 && value2==0) {
      send(msg2.set(state?false:true), true); // Send new state and request ack back
  }
  oldValue2 = value2;
} 

void receive(const MyMessage &message) {
  // We only expect one type of message from controller. But we better check anyway.
  if (message.isAck()) {
     Serial.println("This is an ack from gateway");
  }

  if (message.type == V_LIGHT) {
     // Change relay state
     state = message.getBool();
     switch (message.sensor){
        case (1):
        digitalWrite(RELAY_PIN, state?RELAY_ON:RELAY_OFF);
        break;
        case(2):
        digitalWrite(RELAY_PIN2, state?RELAY_ON:RELAY_OFF);
        break;
        default:
        break;
     }
     
     // Store state in eeprom
     saveState(CHILD_ID, state);

     // Write some debug info
     Serial.print("Incoming change for sensor:");
     Serial.print(message.sensor);
     Serial.print(", New status: ");
     Serial.println(message.getBool());
   } 
}
