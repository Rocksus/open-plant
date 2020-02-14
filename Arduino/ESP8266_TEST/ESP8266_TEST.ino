#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

// When a command is entered in to the serial monitor on the computer
// the Arduino will relay it to the ESP8266


int LEDPIN = 13;

void setup()
{
    pinMode(LEDPIN, OUTPUT);

    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }

    // Start the software serial for communication with the ESP8266
    mySerial.begin(115200);

    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");  
}

void loop()
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() )   {  Serial.write( mySerial.read() );  }

    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  mySerial.write( Serial.read() );  }
}
