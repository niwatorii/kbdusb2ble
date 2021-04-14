#include <M5Stack.h>
// #include <SPI.h>
#include <hidcomposite.h>
#include <hidboot.h>
#include <usbhub.h>
#include <hidescriptorparser.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
// #ifdef dobogusinclude
// #include <spi4teensy3.h>
// #endif
#include <SPI.h>

#include "hidreportdescparser.h"
#include "hidconsctrlrptparser.h"

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

    uint8_t PickReportDescr(uint8_t rpt_id, uint16_t wIndex, USBReadParser *parser);

    uint8_t OnInitSuccessful();

protected:

    void ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf); // Called by the HIDComposite library
    bool SelectInterface(uint8_t iface, uint8_t proto);
    
};

uint8_t HIDSelector::PickReportDescr(uint8_t rpt_id, uint16_t wIndex, USBReadParser *parser){

  const uint8_t constBufLen = 64;
    uint8_t buf[constBufLen];

    uint8_t rcode = pUsb->ctrlReq(bAddress, 0x00, bmREQ_HID_REPORT, USB_REQUEST_GET_DESCRIPTOR, rpt_id,
            HID_DESCRIPTOR_REPORT, wIndex, 128, constBufLen, buf, (USBReadParser*)parser);

    //return ((rcode != hrSTALL) ? rcode : 0);
    return rcode;
}

uint8_t HIDSelector::OnInitSuccessful()
{

  // HexDumper<USBReadParser, uint16_t, uint16_t>    Hex;
  ReportDescParser                                Rpt;

  // GetReportDescr(0, &Hex);

  for (int i = 0; i < bNumIface; i++){
    GetReportDescr(i, &Rpt);
    Serial.println("");
  }
  
  return 0;
}

// Return true for the interface we want to hook into
bool HIDSelector::SelectInterface(uint8_t iface, uint8_t proto)
{

  static uint8_t other_iface_count = 0;

  if (proto ==1){
    Serial.println("Keyboard is available");
    Serial.print("iface:");
    Serial.print(iface);
    Serial.print(", proto:");
    Serial.print(proto);
    Serial.println(";");
    M5.Lcd.println("Keyboard is available");

    if (keyboard_iface)
    keyboard_iface = iface;
    return true;
  } else if (proto == 2){
    Serial.println("Mouse is available");
    Serial.print("iface:");
    Serial.print(iface);
    Serial.print(", proto:");
    Serial.print(proto);
    Serial.println(";");
    M5.Lcd.println("Mouse is available");

    mouse_iface = iface;
    return true;
  } else {
    other_iface_count++;
    Serial.print("Other Interface ");
    Serial.println(other_iface_count);
    Serial.print("iface:");
    Serial.print(iface);
    Serial.print(", proto:");
    Serial.print(proto);
    Serial.println(";");
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
  Serial.print("ep:");
  PrintHex<uint8_t>(ep, 0x80);
  Serial.println(";");
#endif
}

class KbdRptParser : public KeyboardReportParser {
  protected:
    virtual uint8_t HandleLockingKeys(USBHID *hid, uint8_t key);
    virtual void OnControlKeysChanged(uint8_t before, uint8_t after);
    virtual void OnKeyDown(uint8_t mod, uint8_t key);
    virtual void OnKeyUp(uint8_t mod, uint8_t key);
    virtual void OnKeyPressed(uint8_t key);

  private:
    void PrintKey(uint8_t mod, uint8_t key);
};

uint8_t KbdRptParser::HandleLockingKeys(USBHID *hid, uint8_t key) {
  // uint8_t old_keys = kbdLockingKeys.bLeds;

  switch (key) {
    case UHS_HID_BOOT_KEY_NUM_LOCK:
      Serial.println(F("Num lock"));
      kbdLockingKeys.kbdLeds.bmNumLock = ~kbdLockingKeys.kbdLeds.bmNumLock;
      break;
    case UHS_HID_BOOT_KEY_CAPS_LOCK:
      Serial.println(F("Caps lock"));
      kbdLockingKeys.kbdLeds.bmCapsLock = ~kbdLockingKeys.kbdLeds.bmCapsLock;
      break;
    case UHS_HID_BOOT_KEY_SCROLL_LOCK:
      Serial.println(F("Scroll lock"));
      kbdLockingKeys.kbdLeds.bmScrollLock = ~kbdLockingKeys.kbdLeds.bmScrollLock;
      break;
  }

  // if (old_keys != kbdLockingKeys.bLeds && hid) {
  //   BTHID *pBTHID = reinterpret_cast<BTHID *> (hid); // A cast the other way around is done in BTHID.cpp
  //   pBTHID->setLeds(kbdLockingKeys.bLeds); // Update the LEDs on the keyboard
  // }

  return 0;
};

void KbdRptParser::PrintKey(uint8_t m, uint8_t key) {
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
  Serial.print((mod.bmLeftCtrl == 1) ? F("C") : F(" "));
  Serial.print((mod.bmLeftShift == 1) ? F("S") : F(" "));
  Serial.print((mod.bmLeftAlt == 1) ? F("A") : F(" "));
  Serial.print((mod.bmLeftGUI == 1) ? F("G") : F(" "));

  Serial.print(F(" >"));
  PrintHex<uint8_t>(key, 0x80);
  Serial.print(F("< "));

  Serial.print((mod.bmRightCtrl == 1) ? F("C") : F(" "));
  Serial.print((mod.bmRightShift == 1) ? F("S") : F(" "));
  Serial.print((mod.bmRightAlt == 1) ? F("A") : F(" "));
  Serial.println((mod.bmRightGUI == 1) ? F("G") : F(" "));
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) {
  Serial.print(F("DN "));
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  // bleKeyboard.press(mod, key);

  if (c) {
    OnKeyPressed(c);
  }
};

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key) {
  Serial.print(F("UP "));
  PrintKey(mod, key);

  // bleKeyboard.release(mod, key);
};

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {
  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl)
    Serial.println(F("LeftCtrl changed"));
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift)
    Serial.println(F("LeftShift changed"));
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt)
    Serial.println(F("LeftAlt changed"));
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI)
    Serial.println(F("LeftGUI changed"));

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl)
    Serial.println(F("RightCtrl changed"));
  if (beforeMod.bmRightShift != afterMod.bmRightShift)
    Serial.println(F("RightShift changed"));
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt)
    Serial.println(F("RightAlt changed"));
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI)
    Serial.println(F("RightGUI changed"));
};


void KbdRptParser::OnKeyPressed(uint8_t key) {
  Serial.print(F("ASCII: "));
  Serial.println((char)key);
};


USB     Usb;
//USBHub     Hub(&Usb);
// HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
HIDSelector    hidSelector(&Usb);

KbdRptParser Prs;

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
  
  Serial.println("Start");
  M5.Lcd.println("Start");

  // bleKeyboard.begin();


  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

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
  //       Serial.println("BLE is connected...");
  //       flag_informed = true;
  //   } else if(!bleKeyboard.isConnected() && !flag_informed){
  //     Serial.println("BLE is NOT connected...");
  //       flag_informed = true;
  //   }
  // } else {
  //   counter = 0;
  //   flag_informed = false;
  // }
}