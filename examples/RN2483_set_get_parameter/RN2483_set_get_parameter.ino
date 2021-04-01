/* RN2483_set_get_parameter.ino
 *
 * weigu.lu
 * RN2483 on hardware serial
 * RN2483 needs cr + lf (\r\n): println does this
 * Serial logging is Serial (0, USB)
 * we use methods log and log_ln so we are more flexible (e.g. UDP log)
 */

#include <LoRa_RN2483_p2p.h>

RN2483_p2p myrn;

byte RN2483_PIN_RESET = 25; // Reset pin
byte RN2483_SERIAL_NR = 2;  // 0: Serial, 1 Serial1, 2 Serial2

String lora_response, lora_data;

void setup() {
  myrn.set_serial_log(true);          // enable or disable Serial logging here
  myrn.log_ln("Hello");
  myrn.init(RN2483_SERIAL_NR, RN2483_PIN_RESET);
  myrn.factory_reset();
  delay(3000);
  myrn.init(RN2483_SERIAL_NR, RN2483_PIN_RESET);
  lora_response = myrn.get_version();
  lora_response = myrn.get_afcbw();   // get automatic frequency correction bandwidth
  lora_response = myrn.get_bitrate(); // get bitrate
  lora_response = myrn.get_bw();      // get radio bandwidth
  lora_response = myrn.get_cr();      // get coding rate
  lora_response = myrn.get_crc();     // get crc
  lora_response = myrn.get_fdev();    // get fdev
  lora_response = myrn.get_freq();    // get frequency
  lora_response = myrn.get_iqi();     // get if IQ inversion is used
  lora_response = myrn.get_mod();     // get mode
  lora_response = myrn.get_prlen();   // get prlen
  lora_response = myrn.get_pwr();     // get power
  lora_response = myrn.get_rxbw();    // get operational receive bandwidth
  lora_response = myrn.get_sf();      // get spreading factor
  lora_response = myrn.get_snr();     // set signal-to-noise ratio
  lora_response = myrn.get_sync();    // get syncbyte
  lora_response = myrn.get_wdt();     // get time-out limit for the radio Watchdog Timer
  // the following set methods are only for demonstration
  // default values are set
  myrn.set_afcbw();     // set auto freq corr bandwidth
  myrn.set_bitrate();   // set bitrate
  myrn.set_bw();        // set radio bandwidth
  myrn.set_cr();        // set coding rate
  myrn.set_crc();       // set crc
  myrn.set_fdev();      // set fdev
  myrn.set_freq();      // set frequency
  myrn.set_iqi();       // set if IQ inversion is used
  myrn.set_mod();       // set mode
  myrn.set_prlen();     // set prlen
  myrn.set_pwr("1");    // set power
  myrn.set_rxbw();      // set operational receive bandwidth
  myrn.set_sf("sf7");   // set spreading factor
  //myrn.set_sync();    // set syncbyte
  myrn.set_wdt("60000");     // set time-out limit for the radio Watchdog Timer

  myrn.log_ln("starting loop");

}

void loop() {
  delay(1000);
}
