#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup(void) {
  Serial.begin(9600);
  Serial.println("NDEF Reader");
  pinMode(21, OUTPUT);
  nfc.begin();
}

void loop(void) {
  Serial.println("\nScan a NFC tag\n");

  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    if (tag.hasNdefMessage())  // every tag won't have a message
    {

      NdefMessage message = tag.getNdefMessage();

      // cycle through the records, printing some info from each
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++) {
        NdefRecord record = message.getRecord(i);
        // NdefRecord record = message[i]; // alternate syntax
        // The TNF and Type should be used to determine how your application processes the payload
        // There's no generic processing for the payload, it's returned as a byte[]
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);

        // Force the data into a String (might work depending on the content)
        // Real code should use smarter processing
        String payloadAsString = "";
        for (int c = 0; c < payloadLength; c++) {
          if (c >= 3) {
            payloadAsString += (char)payload[c];
          }
        }
        Serial.print("  Payload (as String): ");
        Serial.println(payloadAsString);
        if(payloadAsString == "ON"){
          digitalWrite(21,HIGH);
        }
         if(payloadAsString == "OFF"){
          digitalWrite(21,LOW);
        }
      }
    }
  }
  delay(3000);
}