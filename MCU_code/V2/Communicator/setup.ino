void setup() {
  // begin
  Serial.begin(9600);
  Serial1.begin (9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  lcd.begin(16, 2);

  // Set parseInt timeout
  Serial.setTimeout(100);
  Serial1.setTimeout(100);
  Serial2.setTimeout(100);
  Serial3.setTimeout(100);
  
  // Phone connection
  Serial.println("Please connect to the cepllphone");
  if (1){
    while (Serial2.available()<=0) {
      lcd.setCursor(0,0);
      lcd.print("Pls Connect to");
      lcd.setCursor(0,1);
      lcd.print("Phone");
    }
    if(Serial2.available()) {
      char in =Serial2.read();
      if(in == '@') {
        unsigned long mtime= millis();
        int amsec=0,asec=0,ami=0,ahr=0;
        if (mtime%1000>0){
          asec=mtime/1000;
          amsec=mtime-1000*asec;
          if (asec%60>0){
            ami=asec/60;
            asec=asec-ami*60;
            if (ami%60>0){
              ahr=ami/60;
              ami=ami-ahr*60;
            }
          }
        }
        int year = Serial2.parseInt();
        int month = Serial2.parseInt();
        int date = Serial2.parseInt();
        int hr = Serial2.parseInt();
        fixhr = hr - ahr;
        int mi = Serial2.parseInt();
        fixmi = mi - ami;
        int sec = Serial2.parseInt();
        fixsec = sec - asec;
        int msec = Serial2.parseInt();
        int fixmsec = msec - asec;
        fileName = String(year)+'-'+String(month)+'-'+String(date)+".txt";
        lcd.clear();
        String dateS=String(year)+'/'+String(month)+'/'+String(date)+' ';
        String timeS=String(hr)+':'+String(mi)+':'+String(sec)+'.'+String(msec);
        lcd.setCursor(0,0);
        lcd.print(dateS);
        lcd.setCursor(0,1);
        lcd.print(timeS);
        Serial.print(dateS);
        Serial.println(timeS);
        delay(1000);
      }
    }
  }
  
  //--------------------------initialize----------------------------
  if (1){
    delay(50);
    lcd.setCursor(0,0); // set cursor at first line first alphabet
    lcd.print("Initializing");
    Serial.println("Initializing");
    delay(100);
    lcd.print(".");
    delay(100);
    lcd.print(".");
    delay(100);
    lcd.println(".");
    delay(100);
    Serial.println("lcd OK");
}
  //------------------------- Set up all ----------------------
   //--SD Card Check--
    randomSeed(analogRead(A1));
    lcd.setCursor(0,1); // set cursor at first line first alphabet
    lcd.print("                  ");
    lcd.setCursor(0,1);
    lcd.print("SD");
    delay(100);
    lcd.print(".");
    delay(100);
    lcd.print(".");
    Serial2.print("SC");//SD Card Checking
    int a =0;
    if (!SD.begin(4/*CS port*/)) {
      Serial.println("SD err <I>");
      Serial2.print("SI"); //Please insert SD Card
      lcd.print("err");
      delay(500);
      a++;
      if (a<=5) return;
      else {
        while(1) {
          Serial.print("Please Restart");
          lcd.setCursor(0,0);
          lcd.print("Please Restart");
        }
      }
    }
    else {
     //Write 
      int randomNo= random (0,10000);
      file = SD.open("test.txt", FILE_WRITE);
      if (file) {
        file.println(randomNo);
        Serial.println("SD(W) OK");
        Serial2.print("SO"); //SD OK
        file.close();
      }
      else {
        lcd.print("err");
        Serial.println("SD err <W>");
        Serial2.print("SW"); //SD Writting Error
      }
     //Read
      file = SD.open("test.txt");
      if (file) {
        Serial.println("SD(R) OK");
        if (file.parseInt()==randomNo){
          Serial.println("SD ALL SET");
          lcd.print("ALL SET");
          delay(500);
        }
        file.close();
        SD.remove("test.txt");
      }
      else {
        lcd.print("err");
        Serial.println("SD Err <R>");
        Serial2.print("SR"); //SD Reading Error
      }
    // Name a file name
    if (isAlphaNumeric(fileName[1])) ;
    else {
      file = SD.open("fileNo.txt");
      int fileNo = file.parseInt();
      fileName=String(fileNo)+".TXT";
      fileNo++;
      file.close();
      SD.remove("fileNo.txt");
      file = SD.open("fileNo.txt",FILE_WRITE);
      file.println(fileNo);
      file.close();
    }
    Serial.println(fileName);
    SDWrite("SD OK");
    }
    
  //------------------------Ready to strat---------------------------------
    lcd.noBacklight();
    delay(250);
    lcd.backlight(); 
    delay(700);
    lcd.clear();
    delay(50);
    lcd.setCursor(0,1);
    lcd.print("Speed ");
    lcd.print(hv);
    lcd.setCursor(9,1);
    lcd.print(" ");
    lcd.print("km/hr");
    lcd.setCursor(0,0);
    lcd.print("LOCK");
    Serial.println("Bike LOCK");
    Serial.println("START");
    SDWrite("START");
    delay(50);
    Serial2.print("=");
}