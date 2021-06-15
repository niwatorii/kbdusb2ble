
#if !defined(__HIDRPTDESCPSR_H__)
#define __HIDRPTDESCPSR_H__

#include <usbhid.h>

#define REPORT_DESC_MEM_NUM 8   //Number of Report Descriptor memory 

struct ConsumerCtrlBitManager{
        uint16_t plynpus;        //play and pause
        uint16_t stop;           //stop
        uint16_t scnptrk;        //scan previous track
        uint16_t scnntrk;        //scan next track
        uint16_t mute;           //mute
        uint16_t voldec;         //Volume Decrement
        uint16_t volinc;         //Volume Increment
};


class HIDReportDescParser : public USBReadParser {
public:
        typedef void (*UsagePageFunc)(uint16_t usage);

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

        static void PrintValue(uint8_t *p, uint8_t len);
        static void PrintByteValue(uint8_t data);

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


        uint8_t rptId; //* Report ID
        uint8_t useMin; //* Usage Minimum
        uint8_t useMax; //* Usage Maximum
        uint8_t fieldCount; //* Number of field being currently processed

        void OnInputItem(uint8_t itm); //* Method which is called every time Input item is found

        uint8_t bNumIface;      //*
        uint16_t maxRptDescLen; //*
        bool fNewIface = true;


        ConsumerCtrlBitManager csmCtrkBitMgr;   //*

public:

        uint8_t **ppRptDescBufs; //2D-array to store the Report Descriptor Buffers
        // uint8_t *rptDescType;  //Array to store the Report Descriptor type
        uint8_t *pLatestBuf;

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
        fieldCount(0),
        bNumIface(1),
        maxRptDescLen(0)
        {
                theBuffer.pValue = varBuffer;
                valParser.Initialize(&theBuffer);
                theSkipper.Initialize(&theBuffer);
        };
        
        HIDReportDescParser(uint8_t numiface, uint16_t maxlen) :
        itemParseState(0),
        itemSize(0),
        itemPrefix(0),
        rptSize(0),
        rptCount(0),
        pfUsage(NULL),
        rptId(0),
        useMin(0),
        useMax(0),
        fieldCount(0),
        bNumIface(numiface),
        maxRptDescLen(maxlen)
        {
                theBuffer.pValue = varBuffer;
                valParser.Initialize(&theBuffer);
                theSkipper.Initialize(&theBuffer);

                if (bNumIface && maxRptDescLen){
                        //Dynamically allocate pRptDescBufs, based on bNumIface and maxRptDescLen 
                        ppRptDescBufs = new uint8_t*[bNumIface];
                        for (int i = 0; i < bNumIface; i++){
                                ppRptDescBufs[i] = new uint8_t[maxRptDescLen];
                        }
                } else {
                        ppRptDescBufs = 0;
                }
        };

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
