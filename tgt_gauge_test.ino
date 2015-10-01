
//  This code was written to test the tgt gauge in isolation. The desired temperature (normally received from fsx) is entered by the user on the arduino ide serial terminal.
 
static float fsxTgt = 0;                                // tgt received from FSX, for testing purposes emulated by entering a value on serial terminal
static int tgtPwm = 0;                                  // tgt pwm value (0 - 255)
const int tgtPin = 5;                                   // tgt gauge connected to Arduino pin 5

void setup() 
{
  pinMode(tgtPin, OUTPUT);                              // configure tgt gauge pin as an output
  Serial.begin(9600);                                   // setup serial communication
  Serial.println("Enter tgt 0 - 800 degrees C?");       // prompt user for a tgt value
}

void loop()
{
  if (Serial.available())                               // check if any serial input received and if so then...
    {
    fsxTgt = Serial.parseFloat();                       // get serial input as a floating point number
    fsxTgt = constrain(fsxTgt, 0, 900);                 // limit the entered temperature to a value between 0 and 900 degrees C
    }

    tgtPwm = int(fsxTgt*0.25);                          //calculate pwm value for temperature to indicate, i.e. multiply by scaling factor
    analogWrite(tgtPin,tgtPwm);                         //write pwm value to tgt gauge
}
