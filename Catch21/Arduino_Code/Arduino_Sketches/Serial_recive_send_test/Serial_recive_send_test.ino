/* This sketch waits for incoming serial data to be present
and then sends a message serially.
After Serial.println() is a call to Serial.read() to remove
the received byte from the input queue. If you send more than
one byte to the Arduino, you'll get more than one response sent
back at you.
*/
int in= 0; 
char charIn;
void setup()
{
Serial.begin(9600);
}
 
void loop()
{
if (Serial.available() > 0)
{
charIn = Serial.read();
in = charIn - 48;
delay(1000);
Serial.print("Hello! You sendt the number ");
Serial.print(in);
Serial.println("!");

}
}
