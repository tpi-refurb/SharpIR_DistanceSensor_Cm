#include <SharpIR.h>

#define IR_PIN        A0         // Blue wire connects to analog pin A0
#define LED_PIN       13         // LED connects to digital pin 13
#define BUZZER_PIN    3          // Buzzer connects to digital pin 3
#define MIN_DISTANCE  20         // Minimum distance to notify
#define MODEL         1080

boolean done = false;


//SharpIR sharp(IR_PIN, 25, 93, MODEL);
SharpIR sharp(IR_PIN,  MODEL);
// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

void setup() {
  Serial.begin(9600);
  pinMode (IR_PIN, INPUT);
  pinMode (BUZZER_PIN, OUTPUT);
  pinMode (LED_PIN, OUTPUT);
}

void loop() {
  if (done == false) {                                      // it only runs the loop once
    unsigned long consume_time1 = millis();                 // takes the time before the loop on the library begins

    int distance_val = sharp.distance();                    // this returns the distance to the object you're measuring
    Serial.print("Mean distance: ");                        // returns it to the serial monitor
    Serial.println(distance_val);

    notify(distance_val);

    unsigned long consume_time2 = millis() - consume_time1; // the following gives you the time taken to get the measurement
    Serial.print("Time taken (ms): ");
    Serial.println(consume_time2);
    done = true;
  } else {
    done = false;
  }
}

void notify(int distance_value) {
  if (distance_value <= MIN_DISTANCE) {                     //if the distance value is less than and equal 20, the object is within a few inches
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

