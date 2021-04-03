#include "Arduino.h"
#include "LoRa_RN2483_p2p.h"


/****** INIT functions ****************************************************/

// initialise RN2483 with RESET pin
void RN2483_p2p::init(byte rn_interface_number, byte PIN_RESET) {
  RN2483_p2p::rn_serial_interface = rn_interface_number;
  RN2483_p2p::PIN_RESET = PIN_RESET;
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.begin(9600);
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.begin(9600);
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.begin(9600);
  }
  pinMode(RN2483_p2p::PIN_RESET,OUTPUT);
  digitalWrite(RN2483_p2p::PIN_RESET,LOW); // Reset RN2483 (not needed)
  delay(500);
  digitalWrite(RN2483_p2p::PIN_RESET,HIGH);
  delay(300);                              //wait for the RN2483 startup message
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.flush();
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.flush();
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.flush();
  }
  autobaud();    // adapt baudrate
  mac_pause();   // switch of WAN stack

  log_ln("RN2483 initalized!");
}

/****** GETTER functions ******************************************************/

// get logger flag for Serial
bool RN2483_p2p::get_serial_log() { return RN2483_p2p::enable_serial_log; }

// get firmware version
String RN2483_p2p::get_version() {
  return RN2483_p2p::get_sys("ver");
}

// get automatic frequency correction bandwidth
String RN2483_p2p::get_afcbw() {
  return RN2483_p2p::get_radio("afcbw");
}

// get bitrate
String RN2483_p2p::get_bitrate() {
  return RN2483_p2p::get_radio("bitrate");
}

// get radio bandwidth
String RN2483_p2p::get_bw() {
  return RN2483_p2p::get_radio("bw");
}

// get coding rate
String RN2483_p2p::get_cr() {
  return RN2483_p2p::get_radio("cr");
}

// get crc
String RN2483_p2p::get_crc() {
  return RN2483_p2p::get_radio("crc");
}

// get fdev
String RN2483_p2p::get_fdev() {
  return RN2483_p2p::get_radio("fdev");
}

// get frequency
String RN2483_p2p::get_freq() {
  return RN2483_p2p::get_radio("freq");
}

// get if IQ inversion is used
String RN2483_p2p::get_iqi() {
  return RN2483_p2p::get_radio("iqi");
}

// get mode
String RN2483_p2p::get_mod() {
  return RN2483_p2p::get_radio("mod");
}

// get prlen
String RN2483_p2p::get_prlen() {
  return RN2483_p2p::get_radio("prlen");
}

// get power
String RN2483_p2p::get_pwr() {
  return RN2483_p2p::get_radio("pwr");
}

// get operational receive bandwidth
String RN2483_p2p::get_rxbw() {
  return RN2483_p2p::get_radio("rxbw");
}

// get spreading factor
String RN2483_p2p::get_sf() {
  return RN2483_p2p::get_radio("sf");
}

// get signal-to-noise ratio
String RN2483_p2p::get_snr() {
  return RN2483_p2p::get_radio("snr");
}

// get syncbyte
String RN2483_p2p::get_sync() {
  return RN2483_p2p::get_radio("sync");
}

// get time-out limit for the radio Watchdog Timer
String RN2483_p2p::get_wdt() {
  return RN2483_p2p::get_radio("wdt");
}

/****** SETTER functions *******************************************************/

// set logger flag for Serial
void RN2483_p2p::set_serial_log(bool flag) {
  RN2483_p2p::enable_serial_log = flag;
  if (flag) {
    Serial_debug.begin(115200);
    delay(1000);
    Serial_debug.println("\n\rLogging initialised!");
  }
}


// set automatic frequency correction bandwidth
void RN2483_p2p::set_afcbw(String l_afcbw) {
  RN2483_p2p::set_radio("afcbw",l_afcbw);
}

// set bitrate
void RN2483_p2p::set_bitrate(String l_bitrate) {
RN2483_p2p::set_radio("bitrate",l_bitrate);
}

// set radio bandwidth
void RN2483_p2p::set_bw(String l_bw) {
  RN2483_p2p::set_radio("bw",l_bw);
}

// set coding rate
void RN2483_p2p::set_cr(String l_cr) {
  RN2483_p2p::set_radio("cr",l_cr);
}

// set crc
void RN2483_p2p::set_crc(String l_crc) {
  RN2483_p2p::set_radio("crc",l_crc);
}

// set fdev
void RN2483_p2p::set_fdev(String l_fdev) {
  RN2483_p2p::set_radio("fdev",l_fdev);
}

// set frequency
void RN2483_p2p::set_freq(String l_freq) {
  RN2483_p2p::set_radio("freq",l_freq);
}

// set if IQ inversion is used
void RN2483_p2p::set_iqi(String l_iqi) {
  RN2483_p2p::set_radio("iqi",l_iqi);
}

// set mode
void RN2483_p2p::set_mod(String l_mod) {
  RN2483_p2p::set_radio("mod",l_mod);
}

// set prlen
void RN2483_p2p::set_prlen(String l_prlen) {
  RN2483_p2p::set_radio("prlen",l_prlen);
}

// set power
void RN2483_p2p::set_pwr(String l_pwr) {
  RN2483_p2p::set_radio("pwr",l_pwr);
}

// set operational receive bandwidth
void RN2483_p2p::set_rxbw(String l_rxbw) {
  RN2483_p2p::set_radio("rxbw",l_rxbw);
}

// set spreading factor
void RN2483_p2p::set_sf(String l_sf) {
  RN2483_p2p::set_radio("sf",l_sf);
}

// set syncbyte
void RN2483_p2p::set_sync(String l_sync) {
  RN2483_p2p::set_radio("sync",l_sync);
}

// set time-out limit for the radio Watchdog Timer
void RN2483_p2p::set_wdt(String l_wdt) {
    RN2483_p2p::set_radio("wdt",l_wdt);
}

// factory reset
void RN2483_p2p::factory_reset() {
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.println("sys factoryRESET");
    Serial.println();
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.println("sys factoryRESET");
    Serial1.println();
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.println("sys factoryRESET");
    Serial2.println();
  }
  log_ln("Factory Reset!");
  autobaud();
}

/****** SENDING and RECEIVING functions ***********************************/
// send String (function measures time)
void RN2483_p2p::send(String l_data) {
  unsigned long t1, t2;
  String lora_response;
  byte len = l_data.length();
  char *mytext = (char *)l_data.c_str();
  char hex_text[strlen(mytext)*2];  // C-string with double length
  cstring_2_hex_cstring(mytext, hex_text);
  String lora_data = String(hex_text);
  lora_data = lora_data.substring(0,len*2);
  log("Sending \"");
  log(l_data);
  log("\" as Hex: ");
  log(lora_data);
  log("  ");
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.print("radio tx ");
    Serial.println(lora_data);
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.print("radio tx ");
    Serial1.println(lora_data);
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.print("radio tx ");
    Serial2.println(lora_data);
  }
  t1 = millis();
  if (RN2483_p2p::rn_serial_interface == 0) {
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    lora_response = Serial2.readStringUntil('\n');
  }
  log(lora_response);
  log("  ");
  if (RN2483_p2p::rn_serial_interface == 0) {
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    lora_response = Serial2.readStringUntil('\n');
  }
  t2 = millis();
  log_ln(lora_response);
  log("time to send in ms: ");
  t2 = t2-t1;
  log_ln(String(t2));
}

// receive String
void RN2483_p2p::receive(unsigned int rx_win_size) {
  unsigned long t1, t2;
  String lora_response;
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.print("radio rx ");
    Serial.println(String(rx_win_size));
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.print("radio rx ");
    Serial1.println(String(rx_win_size));
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.print("radio rx ");
    Serial2.println(String(rx_win_size));
  }
  t1 = millis();
  if (RN2483_p2p::rn_serial_interface == 0) {
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    lora_response = Serial2.readStringUntil('\n');
  }
//  log("1: ");
//  log(lora_response);
  if (RN2483_p2p::rn_serial_interface == 0) {
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    lora_response = Serial2.readStringUntil('\n');
  }
  t2 = millis();
  if (lora_response.substring(0,8)=="radio_rx") {
    log("  ");
    log(lora_response);
    log("  ");
    log("time to receive in ms: ");
    t2 = t2-t1;
    log_ln(String(t2));
  }

}

/****** HELPER functions **************************************************/

// Transmit correct sequence to trigger autobauding feature.
// RN2483 takes the same bitrate as the sender
void RN2483_p2p::autobaud() {
  String lora_response;
  log("Autobaud! ");
  lora_response = "";
  while (lora_response=="") {
    if (RN2483_p2p::rn_serial_interface == 0) {
      Serial.write((byte)0x00);
      Serial.write(0x55);
      Serial.println();
      Serial.println("sys get ver");
      lora_response = Serial.readStringUntil('\n');
    }
    if (RN2483_p2p::rn_serial_interface == 1) {
      Serial1.write((byte)0x00);
      Serial1.write(0x55);
      Serial1.println();
      Serial1.println("sys get ver");
      lora_response = Serial1.readStringUntil('\n');
    }
    if (RN2483_p2p::rn_serial_interface == 2) {
      Serial2.write((byte)0x00);
      Serial2.write(0x55);
      Serial2.println();
      Serial2.println("sys get ver");
      lora_response = Serial2.readStringUntil('\n');
    }
    log(".");
  }
  if (RN2483_p2p::rn_serial_interface == 0) {
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    lora_response = Serial2.readStringUntil('\n');
  }
  log_ln("done!");
}

// mac pause: no WAN only LoRa
void RN2483_p2p::mac_pause() {
  String lora_response;
  if (RN2483_p2p::rn_serial_interface == 0) Serial.println("mac pause");
  if (RN2483_p2p::rn_serial_interface == 1) Serial1.println("mac pause");
  if (RN2483_p2p::rn_serial_interface == 2) Serial2.println("mac pause");
  if (RN2483_p2p::rn_serial_interface == 0) {
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    lora_response = Serial2.readStringUntil('\n');
  }
  log("mac_pause: ");
  log_ln(lora_response);
}

// convert a C-string to C-string with hex values
void RN2483_p2p::cstring_2_hex_cstring(char text[], char hextext[]) {
  for (byte i=0; i<strlen(text); i++) {
    hextext[i*2] = (text[i] >> 4) & 0x0F; // high nibble
    hextext[i*2] <= 9 ? hextext[i*2] += 0x30 : hextext[i*2] += 0x37;
    hextext[i*2+1] = text[i] & 0x0F;      // low nibble
    hextext[i*2+1] <= 9 ? hextext[i*2+1] += 0x30 : hextext[i*2+1] += 0x37;
  }
}

/****** LOGGING functions *************************************************/

// print log line to Serial debug
void RN2483_p2p::log(String message) {
  if (RN2483_p2p::enable_serial_log) {
    Serial_debug.print(message);
  }
}

// print linefeed to Serial debug
void RN2483_p2p::log_ln() {
  if (RN2483_p2p::enable_serial_log) {
      Serial_debug.println();
  }
}

// print log line with linefeed to Serial debug
void RN2483_p2p::log_ln(String message) {
  if (RN2483_p2p::enable_serial_log) {
      Serial_debug.println(message);
  }
}



/****** PRIVATE functions *************************************************/

void RN2483_p2p::set_radio(String what, String l_what) {
  String lora_response;
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.print("radio set ");
    Serial.print(what);
    Serial.print(' ');
    Serial.println(l_what);
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.print("radio set ");
    Serial1.print(what);
    Serial1.print(' ');
    Serial1.println(l_what);
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.print("radio set ");
    Serial2.print(what);
    Serial2.print(' ');
    Serial2.println(l_what);
    lora_response = Serial2.readStringUntil('\n');
  }
  log("set ");
  log(what);
  log(" to ");
  log(l_what);
  log(": ");
  log_ln(lora_response);
}

String RN2483_p2p::get_radio(String what) {
  String lora_response;
  if (RN2483_p2p::rn_serial_interface == 0) {
    while (Serial.available()) { // clear buffer
      Serial.read();
    }
    Serial.print("radio get ");
    Serial.println(what);
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    while (Serial1.available()) { // clear buffer
      Serial1.read();
    }
    Serial1.print("radio get ");
    Serial1.println(what);
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    while (Serial2.available()) { // clear buffer
      Serial2.read();
    }
    Serial2.print("radio get ");
    Serial2.println(what);
    lora_response = Serial2.readStringUntil('\n');
  }
  log("getting ");
  log(what);
  log(": ");
  log_ln(lora_response);
  return lora_response;
}

String RN2483_p2p::get_sys(String what) {
  String lora_response;
  if (RN2483_p2p::rn_serial_interface == 0) {
    Serial.print("sys get ");
    Serial.println(what);
    lora_response = Serial.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 1) {
    Serial1.print("sys get ");
    Serial1.println(what);
    lora_response = Serial1.readStringUntil('\n');
  }
  if (RN2483_p2p::rn_serial_interface == 2) {
    Serial2.print("sys get ");
    Serial2.println(what);
    lora_response = Serial2.readStringUntil('\n');
  }
  log("getting ");
  log(what);
  log(": ");
  log_ln(lora_response);
  return lora_response;
}

