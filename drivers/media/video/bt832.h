multiline_comment|/* Bt832 CMOS Camera Video Processor (VP)&n;&n; The Bt832 CMOS Camera Video Processor chip connects a Quartsight CMOS &n;  color digital camera directly to video capture devices via an 8-bit,&n;  4:2:2 YUV or YCrCb video interface.&n;&n; i2c adresses: 0x88 or 0x8a&n; */
multiline_comment|/* The 64 registers: */
singleline_comment|// Input Processor
DECL|macro|BT832_OFFSET
mdefine_line|#define BT832_OFFSET 0
DECL|macro|BT832_RCOMP
mdefine_line|#define BT832_RCOMP&t;1
DECL|macro|BT832_G1COMP
mdefine_line|#define BT832_G1COMP&t;2
DECL|macro|BT832_G2COMP
mdefine_line|#define BT832_G2COMP&t;3
DECL|macro|BT832_BCOMP
mdefine_line|#define BT832_BCOMP&t;4
singleline_comment|// Exposures:
DECL|macro|BT832_FINEH
mdefine_line|#define BT832_FINEH&t;5
DECL|macro|BT832_FINEL
mdefine_line|#define BT832_FINEL&t;6
DECL|macro|BT832_COARSEH
mdefine_line|#define BT832_COARSEH&t;7
DECL|macro|BT832_COARSEL
mdefine_line|#define BT832_COARSEL   8
DECL|macro|BT832_CAMGAIN
mdefine_line|#define BT832_CAMGAIN&t;9
singleline_comment|// Main Processor:
DECL|macro|BT832_M00
mdefine_line|#define BT832_M00&t;10
DECL|macro|BT832_M01
mdefine_line|#define BT832_M01&t;11
DECL|macro|BT832_M02
mdefine_line|#define BT832_M02&t;12
DECL|macro|BT832_M10
mdefine_line|#define BT832_M10&t;13
DECL|macro|BT832_M11
mdefine_line|#define BT832_M11&t;14
DECL|macro|BT832_M12
mdefine_line|#define BT832_M12&t;15
DECL|macro|BT832_M20
mdefine_line|#define BT832_M20&t;16
DECL|macro|BT832_M21
mdefine_line|#define BT832_M21&t;17
DECL|macro|BT832_M22
mdefine_line|#define BT832_M22&t;18
DECL|macro|BT832_APCOR
mdefine_line|#define BT832_APCOR&t;19
DECL|macro|BT832_GAMCOR
mdefine_line|#define BT832_GAMCOR&t;20
singleline_comment|// Level Accumulator Inputs
DECL|macro|BT832_VPCONTROL2
mdefine_line|#define BT832_VPCONTROL2&t;21
DECL|macro|BT832_ZONECODE0
mdefine_line|#define BT832_ZONECODE0&t;22
DECL|macro|BT832_ZONECODE1
mdefine_line|#define BT832_ZONECODE1&t;23
DECL|macro|BT832_ZONECODE2
mdefine_line|#define BT832_ZONECODE2&t;24
DECL|macro|BT832_ZONECODE3
mdefine_line|#define BT832_ZONECODE3&t;25
singleline_comment|// Level Accumulator Outputs:
DECL|macro|BT832_RACC
mdefine_line|#define BT832_RACC&t;26
DECL|macro|BT832_GACC
mdefine_line|#define BT832_GACC&t;27
DECL|macro|BT832_BACC
mdefine_line|#define BT832_BACC&t;28
DECL|macro|BT832_BLACKACC
mdefine_line|#define BT832_BLACKACC&t;29
DECL|macro|BT832_EXP_AGC
mdefine_line|#define BT832_EXP_AGC&t;30
DECL|macro|BT832_LACC0
mdefine_line|#define BT832_LACC0&t;31
DECL|macro|BT832_LACC1
mdefine_line|#define BT832_LACC1&t;32
DECL|macro|BT832_LACC2
mdefine_line|#define BT832_LACC2&t;33
DECL|macro|BT832_LACC3
mdefine_line|#define BT832_LACC3&t;34
DECL|macro|BT832_LACC4
mdefine_line|#define BT832_LACC4&t;35
DECL|macro|BT832_LACC5
mdefine_line|#define BT832_LACC5&t;36
DECL|macro|BT832_LACC6
mdefine_line|#define BT832_LACC6&t;37
DECL|macro|BT832_LACC7
mdefine_line|#define BT832_LACC7&t;38
singleline_comment|// System:
DECL|macro|BT832_VP_CONTROL0
mdefine_line|#define BT832_VP_CONTROL0&t;39
DECL|macro|BT832_VP_CONTROL1
mdefine_line|#define BT832_VP_CONTROL1&t;40
DECL|macro|BT832_THRESH
mdefine_line|#define BT832_THRESH&t;41
DECL|macro|BT832_VP_TESTCONTROL0
mdefine_line|#define BT832_VP_TESTCONTROL0&t;42
DECL|macro|BT832_VP_DMCODE
mdefine_line|#define BT832_VP_DMCODE&t;43
DECL|macro|BT832_ACB_CONFIG
mdefine_line|#define BT832_ACB_CONFIG&t;44
DECL|macro|BT832_ACB_GNBASE
mdefine_line|#define BT832_ACB_GNBASE&t;45
DECL|macro|BT832_ACB_MU
mdefine_line|#define BT832_ACB_MU&t;46
DECL|macro|BT832_CAM_TEST0
mdefine_line|#define BT832_CAM_TEST0&t;47
DECL|macro|BT832_AEC_CONFIG
mdefine_line|#define BT832_AEC_CONFIG&t;48
DECL|macro|BT832_AEC_TL
mdefine_line|#define BT832_AEC_TL&t;49
DECL|macro|BT832_AEC_TC
mdefine_line|#define BT832_AEC_TC&t;50
DECL|macro|BT832_AEC_TH
mdefine_line|#define BT832_AEC_TH&t;51
singleline_comment|// Status:
DECL|macro|BT832_VP_STATUS
mdefine_line|#define BT832_VP_STATUS&t;52
DECL|macro|BT832_VP_LINECOUNT
mdefine_line|#define BT832_VP_LINECOUNT&t;53
DECL|macro|BT832_CAM_DEVICEL
mdefine_line|#define BT832_CAM_DEVICEL&t;54 
singleline_comment|// e.g. 0x19
DECL|macro|BT832_CAM_DEVICEH
mdefine_line|#define BT832_CAM_DEVICEH&t;55 
singleline_comment|// e.g. 0x40  == 0x194 Mask0, 0x194 = 404 decimal (VVL-404 camera)
DECL|macro|BT832_CAM_STATUS
mdefine_line|#define BT832_CAM_STATUS&t;&t;56
DECL|macro|BT832_56_CAMERA_PRESENT
mdefine_line|#define BT832_56_CAMERA_PRESENT 0x20
singleline_comment|//Camera Setups:
DECL|macro|BT832_CAM_SETUP0
mdefine_line|#define BT832_CAM_SETUP0&t;57
DECL|macro|BT832_CAM_SETUP1
mdefine_line|#define BT832_CAM_SETUP1&t;58
DECL|macro|BT832_CAM_SETUP2
mdefine_line|#define BT832_CAM_SETUP2&t;59
DECL|macro|BT832_CAM_SETUP3
mdefine_line|#define BT832_CAM_SETUP3&t;60
singleline_comment|// System:
DECL|macro|BT832_DEFCOR
mdefine_line|#define BT832_DEFCOR&t;&t;61
DECL|macro|BT832_VP_TESTCONTROL1
mdefine_line|#define BT832_VP_TESTCONTROL1&t;62
DECL|macro|BT832_DEVICE_ID
mdefine_line|#define BT832_DEVICE_ID&t;&t;63
DECL|macro|BT832_DEVICE_ID__31
macro_line|# define BT832_DEVICE_ID__31&t;&t;0x31 
singleline_comment|// Bt832 has ID 0x31
multiline_comment|/* STMicroelectronivcs VV5404 camera module &n;   i2c: 0x20: sensor address&n;   i2c: 0xa0: eeprom for ccd defect map&n; */
DECL|macro|VV5404_device_h
mdefine_line|#define VV5404_device_h&t;&t;0x00  
singleline_comment|// 0x19
DECL|macro|VV5404_device_l
mdefine_line|#define VV5404_device_l&t;&t;0x01  
singleline_comment|// 0x40
DECL|macro|VV5404_status0
mdefine_line|#define VV5404_status0&t;&t;0x02
DECL|macro|VV5404_linecountc
mdefine_line|#define VV5404_linecountc&t;0x03 
singleline_comment|// current line counter
DECL|macro|VV5404_linecountl
mdefine_line|#define VV5404_linecountl&t;0x04
DECL|macro|VV5404_setup0
mdefine_line|#define VV5404_setup0&t;&t;0x10
DECL|macro|VV5404_setup1
mdefine_line|#define VV5404_setup1&t;&t;0x11
DECL|macro|VV5404_setup2
mdefine_line|#define VV5404_setup2&t;&t;0x12
DECL|macro|VV5404_setup4
mdefine_line|#define VV5404_setup4&t;&t;0x14
DECL|macro|VV5404_setup5
mdefine_line|#define VV5404_setup5&t;&t;0x15
DECL|macro|VV5404_fine_h
mdefine_line|#define VV5404_fine_h&t;&t;0x20  
singleline_comment|// fine exposure
DECL|macro|VV5404_fine_l
mdefine_line|#define VV5404_fine_l&t;&t;0x21
DECL|macro|VV5404_coarse_h
mdefine_line|#define VV5404_coarse_h&t;&t;0x22  
singleline_comment|//coarse exposure
DECL|macro|VV5404_coarse_l
mdefine_line|#define VV5404_coarse_l&t;&t;0x23
DECL|macro|VV5404_gain
mdefine_line|#define VV5404_gain&t;&t;0x24 
singleline_comment|// ADC pre-amp gain setting
DECL|macro|VV5404_clk_div
mdefine_line|#define VV5404_clk_div&t;&t;0x25
DECL|macro|VV5404_cr
mdefine_line|#define VV5404_cr&t;&t;0x76 
singleline_comment|// control register
DECL|macro|VV5404_as0
mdefine_line|#define VV5404_as0&t;&t;0x77 
singleline_comment|// ADC setup register
singleline_comment|// IOCTL
DECL|macro|BT832_HEXDUMP
mdefine_line|#define BT832_HEXDUMP   _IOR(&squot;b&squot;,1,int)
DECL|macro|BT832_REATTACH
mdefine_line|#define BT832_REATTACH&t;_IOR(&squot;b&squot;,2,int)
multiline_comment|/* from BT8x8VXD/capdrv/dialogs.cpp */
multiline_comment|/*&n;typedef enum { SVI, Logitech, Rockwell } CAMERA;&n;&n;static COMBOBOX_ENTRY gwCameraOptions[] =&n;{&n;   { SVI,      &quot;Silicon Vision 512N&quot; },&n;   { Logitech, &quot;Logitech VideoMan 1.3&quot;  },&n;   { Rockwell, &quot;Rockwell QuartzSight PCI 1.0&quot;   }&n;};&n;&n;// SRAM table values&n;//===========================================================================&n;typedef enum { TGB_NTSC624, TGB_NTSC780, TGB_NTSC858, TGB_NTSC392 } TimeGenByte;&n;&n;BYTE SRAMTable[][ 60 ] =&n;{&n;   // TGB_NTSC624&n;   {&n;      0x33, // size of table = 51&n;      0x0E, 0xC0, 0x00, 0x00, 0x90, 0x02, 0x03, 0x10, 0x03, 0x06,&n;      0x10, 0x04, 0x12, 0x12, 0x05, 0x02, 0x13, 0x04, 0x19, 0x00,&n;      0x04, 0x39, 0x00, 0x06, 0x59, 0x08, 0x03, 0x85, 0x08, 0x07,&n;      0x03, 0x50, 0x00, 0x91, 0x40, 0x00, 0x11, 0x01, 0x01, 0x4D,&n;      0x0D, 0x02, 0x03, 0x11, 0x01, 0x05, 0x37, 0x00, 0x37, 0x21, 0x00&n;   },&n;   // TGB_NTSC780&n;   {&n;      0x33, // size of table = 51&n;      0x0e, 0xc0, 0x00, 0x00, 0x90, 0xe2, 0x03, 0x10, 0x03, 0x06,&n;      0x10, 0x34, 0x12, 0x12, 0x65, 0x02, 0x13, 0x24, 0x19, 0x00,&n;      0x24, 0x39, 0x00, 0x96, 0x59, 0x08, 0x93, 0x85, 0x08, 0x97,&n;      0x03, 0x50, 0x50, 0xaf, 0x40, 0x30, 0x5f, 0x01, 0xf1, 0x7f,&n;      0x0d, 0xf2, 0x03, 0x11, 0xf1, 0x05, 0x37, 0x30, 0x85, 0x21, 0x50&n;   },&n;   // TGB_NTSC858&n;   {&n;      0x33, // size of table = 51&n;      0x0c, 0xc0, 0x00, 0x00, 0x90, 0xc2, 0x03, 0x10, 0x03, 0x06,&n;      0x10, 0x34, 0x12, 0x12, 0x65, 0x02, 0x13, 0x24, 0x19, 0x00,&n;      0x24, 0x39, 0x00, 0x96, 0x59, 0x08, 0x93, 0x83, 0x08, 0x97,&n;      0x03, 0x50, 0x30, 0xc0, 0x40, 0x30, 0x86, 0x01, 0x01, 0xa6,&n;      0x0d, 0x62, 0x03, 0x11, 0x61, 0x05, 0x37, 0x30, 0xac, 0x21, 0x50&n;   },&n;   // TGB_NTSC392&n;   // This table has been modified to be used for Fusion Rev D&n;   {&n;      0x2A, // size of table = 42&n;      0x06, 0x08, 0x04, 0x0a, 0xc0, 0x00, 0x18, 0x08, 0x03, 0x24,&n;      0x08, 0x07, 0x02, 0x90, 0x02, 0x08, 0x10, 0x04, 0x0c, 0x10,&n;      0x05, 0x2c, 0x11, 0x04, 0x55, 0x48, 0x00, 0x05, 0x50, 0x00,&n;      0xbf, 0x0c, 0x02, 0x2f, 0x3d, 0x00, 0x2f, 0x3f, 0x00, 0xc3,&n;      0x20, 0x00&n;   }&n;};&n;&n;//===========================================================================&n;// This is the structure of the camera specifications&n;//===========================================================================&n;typedef struct tag_cameraSpec&n;{&n;   SignalFormat signal;       // which digital signal format the camera has&n;   VideoFormat  vidFormat;    // video standard&n;   SyncVideoRef syncRef;      // which sync video reference is used&n;   State        syncOutput;   // enable sync output for sync video input?&n;   DecInputClk  iClk;         // which input clock is used&n;   TimeGenByte  tgb;          // which timing generator byte does the camera use&n;   int          HReset;       // select 64, 48, 32, or 16 CLKx1 for HReset&n;   PLLFreq      pllFreq;      // what synthesized frequency to set PLL to&n;   VSIZEPARMS   vSize;        // video size the camera produces&n;   int          lineCount;    // expected total number of half-line per frame - 1&n;   BOOL         interlace;    // interlace signal?&n;} CameraSpec;&n;&n;//===========================================================================&n;// &lt;UPDATE REQUIRED&gt;&n;// Camera specifications database. Update this table whenever camera spec&n;// has been changed or added/deleted supported camera models&n;//===========================================================================&n;static CameraSpec dbCameraSpec[ N_CAMERAOPTIONS ] =&n;{  // Silicon Vision 512N&n;   { Signal_CCIR656, VFormat_NTSC, VRef_alignedCb, Off, DecClk_GPCLK, TGB_NTSC624, 64, KHz19636,&n;      // Clkx1_HACTIVE, Clkx1_HDELAY, VActive, VDelay, linesPerField; lineCount, Interlace&n;   {         512,           0x64,       480,    0x13,      240 },         0,       TRUE&n;   },&n;   // Logitech VideoMan 1.3&n;   { Signal_CCIR656, VFormat_NTSC, VRef_alignedCb, Off, DecClk_GPCLK, TGB_NTSC780, 64, KHz24545,&n;      // Clkx1_HACTIVE, Clkx1_HDELAY, VActive, VDelay, linesPerField; lineCount, Interlace&n;      {      640,           0x80,       480,    0x1A,      240 },         0,       TRUE&n;   },&n;   // Rockwell QuartzSight&n;   // Note: Fusion Rev D (rev ID 0x02) and later supports 16 pixels for HReset which is preferable.&n;   //       Use 32 for earlier version of hardware. Clkx1_HDELAY also changed from 0x27 to 0x20.&n;   { Signal_CCIR656, VFormat_NTSC, VRef_alignedCb, Off, DecClk_GPCLK, TGB_NTSC392, 16, KHz28636,&n;      // Clkx1_HACTIVE, Clkx1_HDELAY, VActive, VDelay, linesPerField; lineCount, Interlace&n;      {      352,           0x20,       576,    0x08,      288 },       607,       FALSE&n;   }&n;};&n;*/
multiline_comment|/*&n;The corresponding APIs required to be invoked are:&n;SetConnector( ConCamera, TRUE/FALSE );&n;SetSignalFormat( spec.signal );&n;SetVideoFormat( spec.vidFormat );&n;SetSyncVideoRef( spec.syncRef );&n;SetEnableSyncOutput( spec.syncOutput );&n;SetTimGenByte( SRAMTable[ spec.tgb ], SRAMTableSize[ spec.tgb ] );&n;SetHReset( spec.HReset );&n;SetPLL( spec.pllFreq );&n;SetDecInputClock( spec.iClk );&n;SetVideoInfo( spec.vSize );&n;SetTotalLineCount( spec.lineCount );&n;SetInterlaceMode( spec.interlace );&n;*/
multiline_comment|/* from web:&n; Video Sampling&n;Digital video is a sampled form of analog video. The most common sampling schemes in use today are:&n;                  Pixel Clock   Horiz    Horiz    Vert&n;                   Rate         Total    Active&n;NTSC square pixel  12.27 MHz    780      640      525&n;NTSC CCIR-601      13.5  MHz    858      720      525&n;NTSC 4FSc          14.32 MHz    910      768      525&n;PAL  square pixel  14.75 MHz    944      768      625&n;PAL  CCIR-601      13.5  MHz    864      720      625&n;PAL  4FSc          17.72 MHz   1135      948      625&n;&n;For the CCIR-601 standards, the sampling is based on a static orthogonal sampling grid. The luminance component (Y) is sampled at 13.5 MHz, while the two color difference signals, Cr and Cb are sampled at half that, or 6.75 MHz. The Cr and Cb samples are colocated with alternate Y samples, and they are taken at the same position on each line, such that one sample is coincident with the 50% point of the falling edge of analog sync. The samples are coded to either 8 or 10 bits per component.&n;*/
multiline_comment|/* from DScaler:*/
multiline_comment|/*&n;//===========================================================================&n;// CCIR656 Digital Input Support: The tables were taken from DScaler proyect&n;//&n;// 13 Dec 2000 - Michael Eskin, Conexant Systems - Initial version&n;//&n;&n;//===========================================================================&n;// Timing generator SRAM table values for CCIR601 720x480 NTSC&n;//===========================================================================&n;// For NTSC CCIR656 &n;BYTE BtCard::SRAMTable_NTSC[] =&n;{&n;    // SRAM Timing Table for NTSC&n;    0x0c, 0xc0, 0x00, &n;    0x00, 0x90, 0xc2, &n;    0x03, 0x10, 0x03, &n;    0x06, 0x10, 0x34, &n;    0x12, 0x12, 0x65, &n;    0x02, 0x13, 0x24, &n;    0x19, 0x00, 0x24, &n;    0x39, 0x00, 0x96, &n;    0x59, 0x08, 0x93, &n;    0x83, 0x08, 0x97,&n;    0x03, 0x50, 0x30, &n;    0xc0, 0x40, 0x30, &n;    0x86, 0x01, 0x01, &n;    0xa6, 0x0d, 0x62, &n;    0x03, 0x11, 0x61, &n;    0x05, 0x37, 0x30, &n;    0xac, 0x21, 0x50&n;};&n;&n;//===========================================================================&n;// Timing generator SRAM table values for CCIR601 720x576 NTSC&n;//===========================================================================&n;// For PAL CCIR656&n;BYTE BtCard::SRAMTable_PAL[] =&n;{&n;    // SRAM Timing Table for PAL&n;    0x36, 0x11, 0x01,&n;    0x00, 0x90, 0x02,&n;    0x05, 0x10, 0x04,&n;    0x16, 0x14, 0x05,&n;    0x11, 0x00, 0x04,&n;    0x12, 0xc0, 0x00,&n;    0x31, 0x00, 0x06,&n;    0x51, 0x08, 0x03,&n;    0x89, 0x08, 0x07,&n;    0xc0, 0x44, 0x00,&n;    0x81, 0x01, 0x01,&n;    0xa9, 0x0d, 0x02,&n;    0x02, 0x50, 0x03,&n;    0x37, 0x3d, 0x00,&n;    0xaf, 0x21, 0x00,&n;};&n;*/
eof
