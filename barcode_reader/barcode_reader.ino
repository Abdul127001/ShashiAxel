
int count = 0; 

void setup()
{
  Serial.begin(9600); 
}

void loop()
{
  
  if(Serial.available()) // Check if there is Incoming Data in the Serial Buffer.
  {
    count = 0; // Reset count to zero
    while(Serial.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
    {
      char input = Serial.read(); // Read 1 Byte of data and store it in a character variable
      Serial.print(input); // Print the Byte
      count++; // Increment the Byte count after every Byte Read
      delay(5); // A small delay 
    }
    Serial.println();
  }
}
