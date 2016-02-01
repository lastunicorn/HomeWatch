

void connect()
{
  while (!isConnected)
  {
    loggerWrite("--> Connecting...");
    digitalWrite(pinError, LOW);
    digitalWrite(pinReady, LOW);

    int gsmConnectCode ;

    if (pin == NULL || strlen(pin) == 0)
    {
      loggerWrite("Try to connect without pin.");
      gsmConnectCode = gsmAccess.begin();
    }
    else
    {
      String s = "Try to connect using pin = ";
      s += pin;
      loggerWrite(s);

      gsmConnectCode = gsmAccess.begin(pin);
    }

    String s = "Connect code: ";
    s += gsmConnectCode;
    loggerWrite(s);

    if (gsmConnectCode == GSM_READY)
    {
      digitalWrite(pinReady, HIGH);
      loggerWrite("Connected");
      isConnected = true;
    }
    else
    {
      digitalWrite(pinError, HIGH);
      loggerWrite("Not connected");
      delay(10000);
    }
  }

  loggerWrite("<--");
}

void sendSMS(char remoteNumber[20], char txtMsg[200]) {

  Serial.print("Sending message to mobile number: ");
  Serial.println(remoteNumber);

  // sms text
  Serial.println("Message:");
  Serial.println(txtMsg);

  // send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS();

  Serial.println("SMS successfully sent");
}
