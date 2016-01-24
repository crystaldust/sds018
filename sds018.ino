/*
 * Reading PM2.5 and PM10 with SDS018( http://inovafitness.com/product-39.html ).
 * 
 * Author: crystaldust
 * Email:  juzhenatpku@gmail.com
 * Date:   2016/1/24
 */
void setup() {
  // Serial0 for console log, Serial1 for conmmunication with the device.
  // This is tested in a Arduino Mega 2560, which provides more than one serial port.
  // For uno, drop the console log and use Serial0 as the device conmmunication channel.
  Serial.begin( 9600 );
  Serial1.begin( 9600, SERIAL_8N1 );
}

void loop() {
  uint8_t mData = 0;
  uint8_t mPkt[10] = {0};
  uint8_t mCheck = 0;
  while( Serial1.available() > 0 ) {
    for( int i=0; i<10; ++i ) {
      mPkt[i] = Serial1.read();
      Serial.println( mPkt[i], HEX );
    }
    if( 0xC0 == mPkt[1] ) {
      // Read dust density.
      // Check
      uint8_t sum = 0;
      for( int i=2; i<=7; ++i ) {
        sum += mPkt[i];
      }
      if( sum == mPkt[8] ) {
        uint8_t pm25Low   = mPkt[2];
        uint8_t pm25High  = mPkt[3];
        uint8_t pm10Low   = mPkt[4];
        uint8_t pm10High  = mPkt[5];
  
        float pm25 = ( ( pm25High * 256 ) + pm25Low ) / 10;
        float pm10 = ( ( pm10High * 256 ) + pm10Low ) / 10;
        
        Serial.print( "PM2.5: " );
        Serial.print( pm25 );
        Serial.print( "\nPM10 :" );
        Serial.print( pm10 );
        Serial.println();
      }
    }
    
    Serial1.flush();
  }
  delay( 1000 );
}
