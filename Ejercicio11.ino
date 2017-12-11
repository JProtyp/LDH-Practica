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

#define BUTTON_PIN  3  // Arduino Digital I/O pin number for button 
#define BUTTON_PIN2  5  // Arduino Digital I/O pin number for button 
#define CHILD_ID 1   // Id of the sensor child
#define CHILD_ID2 2   // Id of the sensor child

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
}

void presentation()  {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Button", "1.0");

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


