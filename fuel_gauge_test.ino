
//  This code was written to test the fuel gauge in isolation. The desired fuel quantity (normally received from fsx) is entered by the user on the arduino ide serial terminal.
 
static float fsxFuel = 0;                               // fuel quantity (Kg) received from FSX, for testing purposes emulated by entering a value on serial terminal
static int fuelPwm = 0;                                 // fuel quantity pwm value (0 - 255)
const int fuelPin = 3;                                  // fuel gauge connected to Arduino pin 3

void setup() 
{
  pinMode(fuelPin, OUTPUT);                             // configure fuel gauge pin as an output
  Serial.begin(9600);                                   // setup serial communication
  Serial.println("Enter fuel quantity 0 - 1500 Kg?");   // prompt user for a fuel quantity value
}

void loop()
{
  if (Serial.available())                               // check if any serial input received and if so then...
    {
    fsxFuel = Serial.parseFloat();                      // get serial input as a floating point number
    fsxFuel = constrain(fsxFuel, 0, 1500);              // limit the entered fuel quantity to a value between 0 and 1500 Kg
    }

    fuelPwm = int(fsxFuel*0.1157+72.596);               //calculate pwm value for fuel quantity to indicate, i.e. multiply by scaling factor and add offset to empty
    analogWrite(fuelPin,fuelPwm);                       //write pwm value to fuel gauge
}
