/* RN2483_simple_receiver.ino
/*
 * weigu.lu
 * RN2483 on hardware serial
 * RN2483 needs cr + lf (\r\n): println does this
 * Serial logging on Serial (0, USB)
 * we use methods log and log_ln so we are more flexible (e.g. UDP log)
 */

#include <LoRa_RN2483_p2p.h>

RN2483_p2p myrn;

byte RN2483_PIN_RESET = 25;       // Reset pin
byte RN2483_SERIAL_NR = 2;        // 0: Serial, 1 Serial1, 2 Serial2

String lora_response, lora_data;

const byte LED_PIN = LED_BUILTIN;   // LED_BUILTIN or other pin
bool LED_LOGIC = 0;                 // positive logic: 1, negative logic: 0
const unsigned long NON_BLOCKING_DELAY_MS = 10000;
const unsigned long LED_BLINK_DELAY_MS = 100;

void setup() {
  myrn.set_serial_log(true); // enable or disable logging here
  myrn.log_ln("Hello");
  init_led();
  myrn.init(RN2483_SERIAL_NR, RN2483_PIN_RESET);
  lora_response = myrn.get_version();
  // set defaults for SX1276 (lora lib from sandeepmistry)
  myrn.set_crc("off");            // set crc
  myrn.set_freq("868000000");     // set frequency
  myrn.set_pwr("10");             // set power
  myrn.set_sf("sf7");             // set spreading factor
  myrn.set_sync("12");            // set syncbyte
  myrn.set_wdt("60000");          // set time-out limit for the radio Watchdog Timer
  myrn.log_ln("starting loop");
}

void loop() {
  myrn.receive(0);
  if (non_blocking_delay(NON_BLOCKING_DELAY_MS)) {
    blink_led_x_times(3,LED_BLINK_DELAY_MS);
  }
  yield();
}

/****** HELPER functions *************************************************/

// non blocking delay using millis(), returns true if time is up
bool non_blocking_delay(unsigned long milliseconds) {
  static unsigned long nb_delay_prev_time = 0;
  if(millis() >= nb_delay_prev_time + milliseconds) {
    nb_delay_prev_time += milliseconds;
    return true;
  }
  return false;
}

/****** LED HELPER functions *************************************************/

// initialise the build in LED and switch it on
void init_led() {
  pinMode(LED_PIN,OUTPUT);
  led_on();
}

// LED on
void led_on() {
  LED_LOGIC ? digitalWrite(LED_PIN,HIGH) : digitalWrite(LED_PIN,LOW);
}

// LED off
void led_off() {
  LED_LOGIC ? digitalWrite(LED_PIN,LOW) : digitalWrite(LED_PIN,HIGH);
}

// blink LED x times (LED was on) with delay_time_ms
void blink_led_x_times(byte x, word delay_time_ms) {
  for(byte i = 0; i < x; i++) { // Blink x times
    led_off();
    delay(delay_time_ms);
    led_on();
    delay(delay_time_ms);
  }
}
// toggle LED
void toggle_led(byte pin) {
  digitalRead(pin) ? digitalWrite(pin, LOW) : digitalWrite(pin, HIGH);
}
