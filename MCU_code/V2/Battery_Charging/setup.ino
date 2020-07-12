void setup() {
  // Ask PINS to be low 
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(2,1);
  digitalWrite(3,1);
  digitalWrite(8,1);
  delay(1000);
  
  // Serial begin 
  Serial.begin(9600);
  Serial.println("");

  //Monitor begin
  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
  screen.clearDisplay();  // Clear the buffer
  screen.setTextColor(WHITE);  // Set color of the text
  screen.setFont(&FreeSans9pt7b);
  screen.setTextSize(1.05);

  screen.drawBitmap(0, 0, autobrake_logo, 128, 64, WHITE);
  screen.display();
  buzzer(50,1);
  delay(1000);
  screen.clearDisplay();
  screen.setFont(&FreeSans18pt7b);
  screen.setCursor(15,43);
  screen.print("MSBA");
  screen.display();
  buzzer(50,1);
  delay(1000);
  screen.clearDisplay();
  screen.drawBitmap(0, 0, charging_logo, 128, 64, WHITE);
  screen.display();
  buzzer(50,1);
  delay(1000);
  screen.clearDisplay();

  // Initilize the PINS for button
  pinMode(10,OUTPUT);
  digitalWrite(10,0); 
  pinMode(12,INPUT_PULLUP);

  //Say Hello
  Serial.println("Hello and thank you for using <AutoBrake Battery Charging System>");
  screen.setFont();
  screen.setCursor(0, 10); // (x,y)
  screen.setFont(&FreeSans9pt7b);
  screen.println("       Battery\n     Charging \n       System");
  screen.display();
  buzzer(50,1);
  delay(1000);
  screen.clearDisplay();
  
  //Request for method
  screen.clearDisplay();
  screen.setCursor(0, 15); // (x,y)
  screen.setFont(&FreeSans9pt7b);
  screen.println("Please Select :");
  Serial.println("Please select a function below");
  screen.setFont(&FreeSansBold9pt7b);
  screen.println("1. Get Voltage");
  Serial.println("1. Get battery voltage");
  screen.setFont(&FreeSans9pt7b);
  screen.println("2. Charge\n");
  Serial.println("2. Let battery charge");
  screen.display();
  buzzer(50,1);
  buzzer(150,1);
  delay(500);


  
}
