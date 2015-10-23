///////////////////////////////////////////////////////////////////
// Sadness's Memory Orb                                          //
//                                                               //
// The movie "Inside Out" featured colorful characters: Joy,     //
// Sadness, Anger, Disgust, and Fear. When a memory was created, //
// an orb of the emotions experienced would appear in their      //
// color: Yellow for Joy, Blue for Sadness, Red for Anger, Green //
// for Disgust, and Purple for Fear.                             //
//                                                               //
// This project is a mood orb based on the movie's memory orbs.  //
// A temperature sensor is touched, signalling the Arduino, and  //
// a color is produced from the range of emotions using a RGB    //
// LED wired to the signal. It works much in the same way a mood //
// ring does.                                                    //
//                                                               //
// AUTHOR: Brittany McGarr                                       //
// Inside Out and the emotion characters are copyright of Pixar  //
///////////////////////////////////////////////////////////////////

// Analog Pin (Temperature sensor input)
int temperaturePin = 0;

// Digital Pins (RGB signal outputs)
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int yellowPin = 12;

// Low-read LEDs swap High/Low values
const boolean ON = HIGH;
const boolean OFF = LOW;

// Setup function for initialization
void setup() {
    // Initialize pins
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    
    // Setup serial connection baud rate for debugging
    Serial.begin(9600); 
}

// Main loop
void loop() {
    // Read from the sensor
    float temperature = getVoltage(temperaturePin);
    
    // Convert from voltage values to Fahrenheit temp with roundoff
    temperature = (((temperature - 0.5) * 100) * 1.8) + 32;
    
    // Print the temperature found to serial console
    Serial.println(temperature);
    
    // Put a delay in to keep from rapid flickering (5 sec)
    delay(2000);
    
    // Set the color based on the input
    setColor(temperature);
}

// Functions

// Get the voltage and compute to millivolts in 1024 base range
float getVoltage(int pin) {
    return (analogRead(pin) * 0.004882814); 
}

// Set the color based on read temperature
void setColor(float temperature) {
    // SADNESS
    if((temperature >= 75.5) && (temperature <= 78.0)) {
        digitalWrite(redPin, OFF);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, ON);
        digitalWrite(yellowPin, OFF);
       
        Serial.println("Sadness"); 
    }
    // FEAR
    else if((temperature > 78.0) && (temperature <= 79.0)) {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, ON);
        digitalWrite(yellowPin, OFF);
        
        Serial.println("Fear");
    }
    // DISGUST
    else if((temperature > 79.0) && (temperature <= 79.5)) {
        digitalWrite(redPin, OFF);
        digitalWrite(greenPin, ON);
        digitalWrite(bluePin, OFF);
        digitalWrite(yellowPin, OFF);
        
        Serial.println("Disgust");
    }
    // JOY
    else if((temperature > 79.5) && (temperature <= 82.0)) {
        digitalWrite(redPin, OFF);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, OFF);
        digitalWrite(yellowPin, ON);
        
        Serial.println("JOY!");
    }
    // ANGER
    else if((temperature > 82.0) && (temperature <= 90.0)) {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, OFF);
        digitalWrite(yellowPin, OFF);
       
        Serial.println("Anger"); 
    }
    // Default
    else {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, ON);
        digitalWrite(bluePin, ON);
        digitalWrite(yellowPin, OFF);
    }
}
