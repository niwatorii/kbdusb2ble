#include <M5Stack.h>
// #include <SPI.h>
#include <hidcomposite.h>
#include <hidboot.h>
#include <usbhub.h>
// #include <hidescriptorparser.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
// #ifdef dobogusinclude
// #include <spi4teensy3.h>
// #endif
#include <SPI.h>

#include "lib/hidreportdescparser.h"
// #include "hidconsctrlrptparser.h"

// #include <BleKeyboard.h>

// BleKeyboard bleKeyboard;

// Override HIDComposite to be able to select which interface we want to hook into
class HIDSelector : public HIDComposite
{
public:

    uint8_t keyboard_iface;
    uint8_t mouse_iface;
    uint8_t consctrl_iface;
    
    HIDSelector(USB *p) : HIDComposite(p) {};

    uint8_t OnInitSuccessful();

protected:

    void ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf); // Called by the HIDComposite library
    bool SelectInterface(uint8_t iface, uint8_t proto);
    
};

uint8_t HIDSelector::OnInitSuccessful()
{

  // HexDumper<USBReadParser, uint16_t, uint16_t>    Hex;
  // ReportDescParser                                Rpt;
  E_Notify(PSTR("\r\nbNumIface:"),0x80);
  E_Notify(bNumIface, 0x80);
  E_Notify(PSTR(" MaxHIDRptDescLen:"),0x80);
  E_Notify((uint8_t)maxHIDRptDescLen, 0x80);
  E_Notify(PSTR("\r\n"),0x80);
  delay(1000);
  HIDReportDescParser HidRptDescPsr; //*

  // GetReportDescr(0, &Hex);
  uint16_t rptype;

  for (int i = 0; i < bNumIface; i++){
    GetReportDescr(i, &HidRptDescPsr);
    HidRptDescPsr.ChkRptDesc(rptype);
    E_Notify(PSTR("\r\nRecieved RptTyp: "), 0x80);
    D_PrintHex<uint16_t > (rptype, 0x80);
    E_Notify(PSTR("\r\n"), 0x80);
  }
  
  return 0;
}

// Return true for the interface we want to hook into
bool HIDSelector::SelectInterface(uint8_t iface, uint8_t proto)
{

  static uint8_t other_iface_count = 0;

  if (proto ==1){
    
    E_Notify(PSTR("Keyboard is available\r\n"), 0x80);
    E_Notify(PSTR("iface:"), 0x80);
    E_Notify(iface, 0x80);
    E_Notify(PSTR(", proto:"), 0x80);
    E_Notify(PSTR(proto), 0x80);
    E_Notify(PSTR(";\r\n"), 0x80);
    M5.Lcd.println("Keyboard is available");

    if (keyboard_iface)
    keyboard_iface = iface;
    return true;
  } else if (proto == 2){
    E_Notify(PSTR("Mouse is available"), 0x80);
    E_Notify(PSTR("iface:"),0x80);
    E_Notify(iface, 0x80);
    E_Notify(PSTR(", proto:"), 0x80);
    E_Notify(proto, 0x80);
    E_Notify(PSTR(";\r\n"), 0x80);
    M5.Lcd.println("Mouse is available");

    mouse_iface = iface;
    return true;
  } else {
    other_iface_count++;
    E_Notify(PSTR("Other Interface "), 0x80);
    Serial.println(other_iface_count);
    E_Notify(PSTR("iface:"), 0x80);
    E_Notify(iface, 0x80);
    E_Notify(PSTR(", proto:"), 0x80);
    E_Notify(proto, 0x80);
    E_Notify(PSTR(";\r\n"), 0x80);
    M5.Lcd.print("Other Interface ");
    M5.Lcd.println(other_iface_count);
    return true;
  }

  return false;
}

// Will be called for all HID data received from the USB interface
void HIDSelector::ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf) {
#if 1
  if (len && buf)  {
    Notify(PSTR("\r\n"), 0x80);
    for (uint8_t i = 0; i < len; i++) {
      D_PrintHex<uint8_t > (buf[i], 0x80);
      Notify(PSTR(" "), 0x80);
    }
  }
  E_Notify(PSTR("ep:"), 0x80);
  PrintHex<uint8_t>(ep, 0x80);
  E_Notify(PSTR(";\r\n"), 0x80);
#endif
}

USB     Usb;
//USBHub     Hub(&Usb);
// HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
HIDSelector    hidSelector(&Usb);


bool flag_informed = false;
uint16_t counter = 0;



void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  
  M5.begin(true, false, true, false);
  M5.Power.begin();
  
  E_Notify(PSTR("Start"), 0x80);
  M5.Lcd.println("Start");

  // bleKeyboard.begin();


  if (Usb.Init() == -1)
    E_Notify(PSTR("OSC did not start."), 0x80);

  // Set this to higher values to enable more debug information
  // minimum 0x00, maximum 0xff, default 0x80
  UsbDEBUGlvl = 0xff;

  //Setting Report Parser


  delay( 200 );

}

void loop()
{
  Usb.Task();


  // if(counter <= 1000){
  //   if(bleKeyboard.isConnected() && !flag_informed) {
  //       E_Notify(PSTR("BLE is connected...");
  //       flag_informed = true;
  //   } else if(!bleKeyboard.isConnected() && !flag_informed){
  //     E_Notify(PSTR("BLE is NOT connected...");
  //       flag_informed = true;
  //   }
  // } else {
  //   counter = 0;
  //   flag_informed = false;
  // }
}