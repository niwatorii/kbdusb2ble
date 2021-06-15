#include <usbhid.h>


class HIDConsCtrlRptParser : public HIDReportParser {
public:
        
        // Method should be defined here if virtual.
        virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};



void HIDConsCtrlRptParser::Parse(USBHID *hid, bool is_rpt_id __attribute__((unused)), uint8_t len, uint8_t *buf) {
        
}