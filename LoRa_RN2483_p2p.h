/* RN2483 LoRa p2p (no WAN)
 *
 * weigu.lu
 *
 * Hardware Serial (default Serial1) is used to connect to the R2482
 *
 * RN2483 needs cr + lf (\r\n): println does this
 * The mac pause command must be called before any radio transmission
 * or reception, even if no MAC operations have been initiated before.
 */

/* this are the variables if we want to change the default radio settings (in brackets)
 * https://ww1.microchip.com/downloads/en/DeviceDoc/ \
 * RN2483-LoRa-Technology-Module-Command-Reference-User-Guide-DS40001784G.pdf
 * afcbw     value used by the automatic frequency correction bandwidth (41.7)
 * bitrate   frequency shift keying (FSK) bit rate (50000)
 * bw        value used for the radio bandwidth (125)
 * cr        coding rate used by the radio (4/5)
 * crc       if a CRC header is to be used (on)
 * fdev      frequency deviation allowed by the end device (25000)
 * freq      current operation frequency for the radio (868100000)
 * iqi       if IQ inversion is used (off)
 * mod       module Modulation mode (lora)
 * prlen     preamble length used during transmissions (8)
 * pwr       output power level used by the radio during transmission (1)
 * rxbw      operational receive bandwidth (25)
 * sf        requested spreading factor (SF) for transmission (sf12)
 * snr       signal-to-noise ratio (only get)
 * sync      sync word used (only set (one byte))
 * wdt       time-out limit for the radio Watchdog Timer (15000)
 */




#ifndef RN2483_LORA_P2P_h
#define RN2483_LORA_P2P_h

#define Serial_debug  Serial

// default values after factory reset
const String afcbw   = "41.7";
const String bitrate = "50000";
const String bt      = "0.5";
const String bw      = "125";
const String cr      = "4/5";
const String crc     = "on";
const String fdev    = "25000";
const String freq    = "868100000";  // from 863000000 to 870000000
const String iqi     = "off";
const String mod     = "lora";
const String prlen   = "8";
const String pwr     = "0";          // from -3 to 15 (max should be 14dBm).
const String rxbw    = "25";
const String sf      = "sf12";       // sf7,sf8,sf9,sf10,sf11 or sf12.
const String sync    = "10";
const String wdt     = "15000";


class RN2483_p2p {
  public:
    /****** INIT functions ****************************************************/
    void init(byte rn_interface_number, byte PIN_RESET); // init + RESET pin
    /****** GETTER functions **************************************************/
    bool get_serial_log();                  // get logger flag for serial debug
    String get_version();                   // get firmware version
    String get_afcbw();                     // get auto freq corr bandwidth
    String get_bitrate();                   // get bitrate
    String get_bw();                        // get radio bandwidth
    String get_cr();                        // get coding rate
    String get_crc();                       // get crc
    String get_fdev();                      // get fdev
    String get_freq();                      // get frequency
    String get_iqi();                       // get if IQ inversion is used
    String get_mod();                       // get mode
    String get_prlen();                     // get prlen
    String get_pwr();                       // get power
    String get_rxbw();                      // get operational receive bandwidth
    String get_sf();                        // get spreading factor
    String get_snr();                       // set signal-to-noise ratio
    String get_sync();                      // get syncbyte
    String get_wdt();                       // get timeout limit Watchdog Timer
    /****** SETTER functions **************************************************/
    void set_serial_log(bool flag);         // set logger flag for serial debug
    void set_afcbw(String l_afcbw = afcbw); // set auto freq corr bandwidth
    void set_bitrate(String l_bitrate = bitrate); // set bitrate
    void set_bw(String l_bw = bw);          // set radio bandwidth
    void set_cr(String l_cr = cr);          // set coding rate
    void set_crc(String l_crc = crc);       // set crc
    void set_fdev(String l_fdev = fdev);    // set fdev
    void set_freq(String l_freq = freq);    // set frequency
    void set_iqi(String l_iqi = iqi);       // set if IQ inversion is used
    void set_mod(String l_mod = mod);       // set mode
    void set_prlen(String l_prlen = prlen); // set prlen
    void set_pwr(String l_pwr = pwr);       // set power
    void set_rxbw(String l_rxbw = rxbw);    // set op. receive bandwidth
    void set_sf(String l_sf = sf);          // set spreading factor
    void set_sync(String l_sync = sync);    // set syncbyte
    void set_wdt(String l_wdt = wdt);       // set time-out limit Watchdog
    void factory_reset(); //factory reset
    /****** SENDING and RECEIVING functions ***********************************/
    void send(String l_data);               // send String (also measures time)
    void receive(unsigned int rx_win_size); // receive String
    /****** HELPER functions **************************************************/
    void autobaud();                        // set same bitrate as the sender
    void mac_pause();                       // mac pause: no WAN only LoRa
    void cstring_2_hex_cstring(char text[], char hextext[]);
    /****** LOGGING functions *************************************************/
    // print log line to Serial and/or remote UDP port
    void log(String message);
    void log_ln();
    void log_ln(String message);



  private:
    byte rn_serial_interface = 1;
    byte PIN_RESET = 0;
    bool enable_serial_log = false;
    /****** PRIVATE functions *************************************************/
    void set_radio(String what, String l_what);
    String get_radio(String what);
    String get_sys(String what);


};

#endif // RN2483_LORA_P2P_h
