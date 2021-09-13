
#if !defined(__HIDRPTDESCPSR_H__)
#define __HIDRPTDESCPSR_H__

#include <usbhid.h>

#define REPORT_DESC_MEM_NUM 8   //Number of Report Descriptor memory 

#define CC_SCAN_NEXT_TRACK              0x00B5
#define CC_SCAN_PREVIOUS_TRACK          0x00B6
#define CC_STOP                         0x00B7
#define CC_PLAY_OR_PAUSE                0x00CD
#define CC_MUTE                         0x00E2
#define CC_VOLUME_INCREMENT             0x00E9
#define CC_VOLUME_DECREMENT             0x00EA
#define CC_AL_EMAIL_READER              0x018A
#define CC_AL_CALCULATOR                0x0192
#define CC_AL_LOCAL_MACHINE_BROWSER     0x0194
#define CC_AL_INTERNET_BROWSER          0x0196
struct HIDKeyboardConsumerControl8{
        uint8_t ScanNextTrack;         //*Transport Control: scan next track
        uint8_t ScanPreviousTrack;     //*Transport Control: scan previous track
        uint8_t Stop;                  //*Transport Control: stop    
        uint8_t PlayOrPause;           //*Transport Control: play and pause    
        uint8_t Mute;                  //*Audio Control: mute
        uint8_t VolumeIncrement;       //*Audio Control:Volume Increment
        uint8_t VolumeDecrement;       //*Audio Control: Volume Decrement
        uint8_t ALEMail;               //*Application Launch: Email Reader
        uint8_t ALCalculator;          //*Application Launch: Caliculator
        uint8_t ALLocalMachineBrowser; //*Application Launch: Local Machine Browser
        uint8_t ALInternetBrowser;     //*Application Launch: Internet Browser
};
struct HIDKeyboardConsumerControl16{
        uint16_t ScanNextTrack;         //*Transport Control: scan next track
        uint16_t ScanPreviousTrack;     //*Transport Control: scan previous track
        uint16_t Stop;                  //*Transport Control: stop    
        uint16_t PlayOrPause;           //*Transport Control: play and pause    
        uint16_t Mute;                  //*Audio Control: mute
        uint16_t VolumeIncrement;       //*Audio Control:Volume Increment
        uint16_t VolumeDecrement;       //*Audio Control: Volume Decrement
        uint16_t ALEMail;               //*Application Launch: Email Reader
        uint16_t ALCalculator;          //*Application Launch: Caliculator
        uint16_t ALLocalMachineBrowser; //*Application Launch: Local Machine Browser
        uint16_t ALInternetBrowser;     //*Application Launch: Internet Browser
};

union ReportTypeFlags {
        uint8_t byte;
        struct flag_bit_ {
                bool reserved   : 5;    //*Not Used;
                bool consctrl   : 1;    //*Flag: Consumer Controls
                bool keyboard   : 1;    //*Flag: keyboard
                bool mouse      : 1;    //*Flag: mouse
        }flag_bit;
};


class HIDReportDescParser : public USBReadParser {
public:
        typedef void (*UsagePageFunc)(uint16_t usage);
        typedef uint8_t (*UsgTypFunc)(uint16_t usage);  //* Func pointer Usage Type Function

        static void PrintGenericDesktopPageUsage(uint16_t usage);
        static void PrintSimulationControlsPageUsage(uint16_t usage);
        static void PrintVRControlsPageUsage(uint16_t usage);
        static void PrintSportsControlsPageUsage(uint16_t usage);
        static void PrintGameControlsPageUsage(uint16_t usage);
        static void PrintGenericDeviceControlsPageUsage(uint16_t usage);
        static void PrintLEDPageUsage(uint16_t usage);
        static void PrintButtonPageUsage(uint16_t usage);
        static void PrintOrdinalPageUsage(uint16_t usage);
        static void PrintTelephonyPageUsage(uint16_t usage);
        static void PrintConsumerPageUsage(uint16_t usage);
        static void PrintDigitizerPageUsage(uint16_t usage);
        static void PrintAlphanumDisplayPageUsage(uint16_t usage);
        static void PrintMedicalInstrumentPageUsage(uint16_t usage);

        static uint8_t getGenericDesktopPageType(uint16_t usage);
        static uint8_t getConsumerPageUsageType(uint16_t usage);        //* in usgTypFuncs

        static void PrintValue(uint8_t *p, uint8_t len);
        static void PrintByteValue(uint16_t data);

        static void PrintItemTitle(uint8_t prefix);

        static const char * const usagePageTitles0[];
        static const char * const usagePageTitles1[];
        static const char * const genDesktopTitles0[];
        static const char * const genDesktopTitles1[];
        static const char * const genDesktopTitles2[];
        static const char * const genDesktopTitles3[];
        static const char * const genDesktopTitles4[];
        static const char * const simuTitles0[];
        static const char * const simuTitles1[];
        static const char * const simuTitles2[];
        static const char * const vrTitles0[];
        static const char * const vrTitles1[];
        static const char * const sportsCtrlTitles0[];
        static const char * const sportsCtrlTitles1[];
        static const char * const sportsCtrlTitles2[];
        static const char * const gameTitles0[];
        static const char * const gameTitles1[];
        static const char * const genDevCtrlTitles[];
        static const char * const ledTitles[];
        static const char * const telTitles0[];
        static const char * const telTitles1[];
        static const char * const telTitles2[];
        static const char * const telTitles3[];
        static const char * const telTitles4[];
        static const char * const telTitles5[];
        static const char * const consTitles0[];
        static const char * const consTitles1[];
        static const char * const consTitles2[];
        static const char * const consTitles3[];
        static const char * const consTitles4[];
        static const char * const consTitles5[];
        static const char * const consTitles6[];
        static const char * const consTitles7[];
        static const char * const consTitles8[];
        static const char * const consTitles9[];
        static const char * const consTitlesA[];
        static const char * const consTitlesB[];
        static const char * const consTitlesC[];
        static const char * const consTitlesD[];
        static const char * const consTitlesE[];
        static const char * const digitTitles0[];
        static const char * const digitTitles1[];
        static const char * const digitTitles2[];
        static const char * const aplphanumTitles0[];
        static const char * const aplphanumTitles1[];
        static const char * const aplphanumTitles2[];
        static const char * const medInstrTitles0[];
        static const char * const medInstrTitles1[];
        static const char * const medInstrTitles2[];
        static const char * const medInstrTitles3[];
        static const char * const medInstrTitles4[];

        
        /***/
        static const uint8_t genDesktopTypes0[];       //*
        static const uint8_t genDesktopTypes1[];       //*
        static const uint8_t genDesktopTypes2[];       //*
        static const uint8_t genDesktopTypes3[];       //*
        static const uint8_t genDesktopTypes4[];       //*

        static const uint8_t consTypes0[];      //*
        static const uint8_t consTypes1[];      //*
        static const uint8_t consTypes2[];      //*
        static const uint8_t consTypes3[];      //*
        static const uint8_t consTypes4[];      //*
        static const uint8_t consTypes5[];      //*
        static const uint8_t consTypes6[];      //*
        static const uint8_t consTypes7[];      //*
        static const uint8_t consTypes8[];      //*
        static const uint8_t consTypes9[];      //*
        static const uint8_t consTypesA[];      //*
        static const uint8_t consTypesB[];      //*
        static const uint8_t consTypesC[];      //*
        static const uint8_t consTypesD[];      //*
        static const uint8_t consTypesE[];      //*

protected:
        static UsagePageFunc usagePageFunctions[];
        static UsgTypFunc usgTypFuncs[];        //*

        MultiValueBuffer theBuffer;
        MultiByteValueParser valParser;
        ByteSkipper theSkipper;
        uint8_t varBuffer[sizeof (USB_CONFIGURATION_DESCRIPTOR)];

        uint8_t itemParseState; // Item parser state variable
        uint8_t itemSize; // Item size
        uint8_t itemPrefix; // Item prefix (first byte)
        uint8_t rptSize; // Report Size
        uint8_t rptCount; // Report Count

        uint16_t totalSize; // Report size in bits

        // Method should be defined here if virtual.
        virtual uint8_t ParseItem(uint8_t **pp, uint16_t *pcntdn);

        UsagePageFunc pfUsage;

        static void PrintUsagePage(uint16_t page);
        void SetUsagePage(uint16_t page);


        ReportTypeFlags rptTypFlags;        //*Report Type Flags. Mouse, Keyboard or ConsumerControl

        uint16_t tmpUsgBuf[512];        //* temporary Usage Buffer
        uint16_t tmpBitCnt;     //* Bit Count for tmpUsgBuf using in ItemParser
        uint16_t tmpUsgPg;

        uint8_t desCoLayer;   //*Collection Layer of Report Descriptor 

        uint8_t rptId; //* Report ID
        uint8_t useMin; //* Usage Minimum
        uint8_t useMax; //* Usage Maximum
        uint8_t fieldCount; //* Number of field being currently processed

        void OnCollectionItem(uint8_t itm);     //* Method which is called every time Collection item is found
        void OnEndpointIten(uint8_t itm);     //* Method which is called every time Collection item is found
        void OnInputItem(uint8_t itm); //* Method which is called every time Input item is found
        void OnOutputItem(uint8_t itm); //* Method which is called every time Output item is found


        uint16_t rptDescLen; //*
        bool fNewIface = true;  //*
        bool fFinishParse = false;      //*

        UsgTypFunc pfUsgTyp; //*

        void BufParserConstructor(const uint16_t (&usgary)[512]);

public:

        HIDKeyboardConsumerControl8 HIDKbdCnsCtrlRptID;
        HIDKeyboardConsumerControl16 HIDKbdCnsCtrl;
        
        uint8_t *pRptDescBufs; //Array to store the Report Descriptor Buffers
        // uint8_t *rptDescType;  //Array to store the Report Descriptor type
        uint8_t *pLatestBuf;    //*

        void OutputRptDescPrs(bool show_input, bool show_output, uint8_t input_rpdid, uint8_t output_rptid);

        HIDReportDescParser() :
        itemParseState(0),
        itemSize(0),
        itemPrefix(0),
        rptSize(0),
        rptCount(0),
        pfUsage(NULL),
        rptId(0),
        useMin(0),
        useMax(0),
        fieldCount(0)
        {
                theBuffer.pValue = varBuffer;
                valParser.Initialize(&theBuffer);
                theSkipper.Initialize(&theBuffer);
        };

        void GetRptBufPrs();
        void ChkRptDesc(ReportTypeFlags &rptypflag);

        void Parse(const uint16_t len, const uint8_t *pbuf, const uint16_t &offset);

        enum {
                enErrorSuccess = 0
                , enErrorIncomplete // value or record is partialy read in buffer
                , enErrorBufferTooSmall
        };


        void StoreRptDescBuf(const uint8_t iface, const uint8_t *pBuf);
};

#endif // __HIDRPTDESCPSR_H__


//***************************************************************************************************************************************************
