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

// Sample ambient temperature
float sampleTemp = 0.00;

// Low-read LEDs swap High/Low values
const boolean ON = LOW;
const boolean OFF = HIGH;

// Setup function for initialization
void setup() {
    // Initialize pins
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    
    // Setup serial connection baud rate for debugging
    Serial.begin(9600); 
    
    // Take sample of ambient temperature at startup
    // Accounts for cold, fall night
    sampleTemp = getAverage();
    
    // Print out the sample temperature
    Serial.println("Sample Temperature:");
    Serial.println(sampleTemp);
}

// Main loop
void loop() {
    // Read from the sensor
    float temperature = getAverage();
    
    // Print the temperature found to serial console
    Serial.println(temperature - sampleTemp);
    
    // Set the color based on the input
    setColor(temperature - sampleTemp);
}

// Functions

// Get a random sample since temperatures fluctuate
float getAverage() {
    float sample = 0.00;
    float average = 0.00;
    
    for(int count = 0.00; count < 5; count++) {
        sample = getVoltage(temperaturePin);
        sample = (((sample - 0.5) * 100) * 1.8) + 32;
        average += sample;
        
        delay(1000);
    } 
    average /= 5.00;
    
    return average;
}

// Get the voltage and compute to millivolts in 1024 base range
float getVoltage(int pin) {
    return (analogRead(pin) * 0.004882814); 
}

// Set the color based on read temperature
void setColor(float temperature) {
    // SADNESS
    if((temperature >= 0.50) && (temperature <= 2.50)) {
        digitalWrite(redPin, OFF);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, ON);
        digitalWrite(yellowPin, ON);
       
        Serial.println("Sadness"); 
    }
    // FEAR
    else if((temperature > 3.00) && (temperature <= 4.00)) {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, ON);
        digitalWrite(yellowPin, ON);
        
        Serial.println("Fear");
    }
    // DISGUST
    else if((temperature > 4.00) && (temperature <= 4.50)) {
        digitalWrite(redPin, OFF);
        digitalWrite(greenPin, ON);
        digitalWrite(bluePin, OFF);
        digitalWrite(yellowPin, ON);
        
        Serial.println("Disgust");
    }
    // JOY
    else if((temperature > 4.50) && (temperature <= 8.00)) {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, ON);
        digitalWrite(bluePin, OFF);
        digitalWrite(yellowPin, OFF);
        
        Serial.println("JOY!");
    }
    // ANGER
    else if((temperature > 8.00) && (temperature <= 12.00)) {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, OFF);
        digitalWrite(bluePin, OFF);
        digitalWrite(yellowPin, ON);
       
        Serial.println("Anger"); 
    }
    // Default
    else {
        digitalWrite(redPin, ON);
        digitalWrite(greenPin, ON);
        digitalWrite(bluePin, ON);
        digitalWrite(yellowPin, ON);
    }
}
