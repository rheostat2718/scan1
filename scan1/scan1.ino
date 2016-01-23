

#define BAUDRATE 115200
#define BUFFER_LENGTH 256

#include <stdio.h>
#include <Wire.h>


char clearSerialInput(void);

char buf[BUFFER_LENGTH];
char ibuf[BUFFER_LENGTH];
char * cp;
char wflag;

void setup()
{
  Wire.begin();
  cp = buf;
  Serial.begin(BAUDRATE);
  delay(100);
  
  
}


void loop()
{
  int error, address;
  int n;

  sprintf(buf,"Starting New Scan...%c%c",0x0d,0x0a);
  Serial.println(buf);

  n = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    Wire.write(address);
    error = Wire.endTransmission();
	
	if (error == 0)
	{
	    sprintf(buf,"Address 0x%02x : error code %d", address, error);
	    Serial.println(buf);
	    
	    
	}	    
	
	
    
    if (error == 0)      
    {
        n++;
    }
  }
  
  if (n == 0)
  {
	  
	sprintf(buf,"No devices found (n=%d)",n);
    Serial.println(buf);
  }
  else
  {
    	  
	sprintf(buf,"%d devices found",n);
    Serial.println(buf);
  }
  

  wflag = 0;
  while (wflag == 0)
  {
    if (Serial.available())
    {
      wflag = 1; // Wait for Input Flag is set to 1, so you can exit WAIT LOOP
      clearSerialInput();
    }
	delay(250);
  }

  //delay(5000);
}


char clearSerialInput(void)
{
	int c;
	c = 0;
	
	while (Serial.available() )
	{
		
		ibuf[c]=Serial.read(); // While there are new characters in serial input buffer
							   // read them into ibuf (INPUT_BUFFER);
		
		c=c+1;				   // Increment Character Counter, counts the # of characters in STRING
							   // NOT including NULL CHARACTER;
	}
	
	if (c > 0)
	{
		ibuf[c]=0; // Null Terminate String
		return 1; // Clear Bytes from Serial Input Buffer
	}
	else
	{
		ibuf[0]=0; // Null Terminate First Character of Input Buffer (NULL String)
		return 0; // Nothing in Serial Input Buffer to Clear
	}
        return 0;
}