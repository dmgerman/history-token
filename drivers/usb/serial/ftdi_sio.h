multiline_comment|/*&n; * Definitions for the FTDI USB Single Port Serial Converter - &n; * known as FTDI_SIO (Serial Input/Output application of the chipset) &n; *&n; * The example I have is known as the USC-1000 which is available from&n; * http://www.dse.co.nz - cat no XH4214 It looks similar to this:&n; * http://www.dansdata.com/usbser.htm but I can&squot;t be sure There are other&n; * USC-1000s which don&squot;t look like my device though so beware!&n; *&n; * The device is based on the FTDI FT8U100AX chip. It has a DB25 on one side, &n; * USB on the other.&n; *&n; * Thanx to FTDI (http://www.ftdi.co.uk) for so kindly providing details&n; * of the protocol required to talk to the device and ongoing assistence&n; * during development.&n; *&n; * Bill Ryder - bryder@sgi.com formerly of Silicon Graphics, Inc.- wrote the &n; * FTDI_SIO implementation.&n; *&n; * Philipp G&#xfffd;hring - pg@futureware.at - added the Device ID of the USB relais&n; * from Rudolf Gugler&n; *&n; */
DECL|macro|FTDI_VID
mdefine_line|#define FTDI_VID&t;0x0403&t;/* Vendor Id */
DECL|macro|FTDI_SIO_PID
mdefine_line|#define FTDI_SIO_PID&t;0x8372&t;/* Product Id SIO application of 8U100AX  */
DECL|macro|FTDI_8U232AM_PID
mdefine_line|#define FTDI_8U232AM_PID 0x6001 /* Similar device to SIO above */
DECL|macro|FTDI_8U232AM_ALT_PID
mdefine_line|#define FTDI_8U232AM_ALT_PID 0x6006 /* FTDI&squot;s alternate PID for above */
DECL|macro|FTDI_8U2232C_PID
mdefine_line|#define FTDI_8U2232C_PID 0x6010 /* Dual channel device */
DECL|macro|FTDI_RELAIS_PID
mdefine_line|#define FTDI_RELAIS_PID&t;0xFA10  /* Relais device from Rudolf Gugler */
DECL|macro|FTDI_NF_RIC_VID
mdefine_line|#define FTDI_NF_RIC_VID&t;0x0DCD&t;/* Vendor Id */
DECL|macro|FTDI_NF_RIC_PID
mdefine_line|#define FTDI_NF_RIC_PID&t;0x0001&t;/* Product Id */
multiline_comment|/* www.irtrans.de device */
DECL|macro|FTDI_IRTRANS_PID
mdefine_line|#define FTDI_IRTRANS_PID 0xFC60 /* Product Id */
multiline_comment|/* www.crystalfontz.com devices - thanx for providing free devices for evaluation ! */
multiline_comment|/* they use the ftdi chipset for the USB interface and the vendor id is the same */
DECL|macro|FTDI_XF_632_PID
mdefine_line|#define FTDI_XF_632_PID 0xFC08&t;/* 632: 16x2 Character Display */
DECL|macro|FTDI_XF_634_PID
mdefine_line|#define FTDI_XF_634_PID 0xFC09&t;/* 634: 20x4 Character Display */
DECL|macro|FTDI_XF_547_PID
mdefine_line|#define FTDI_XF_547_PID 0xFC0A&t;/* 547: Two line Display */
DECL|macro|FTDI_XF_633_PID
mdefine_line|#define FTDI_XF_633_PID 0xFC0B&t;/* 633: 16x2 Character Display with Keys */
DECL|macro|FTDI_XF_631_PID
mdefine_line|#define FTDI_XF_631_PID 0xFC0C&t;/* 631: 20x2 Character Display */
DECL|macro|FTDI_XF_635_PID
mdefine_line|#define FTDI_XF_635_PID 0xFC0D&t;/* 635: 20x4 Character Display */
DECL|macro|FTDI_XF_640_PID
mdefine_line|#define FTDI_XF_640_PID 0xFC0E&t;/* 640: Two line Display */
DECL|macro|FTDI_XF_642_PID
mdefine_line|#define FTDI_XF_642_PID 0xFC0F&t;/* 642: Two line Display */
multiline_comment|/* Video Networks Limited / Homechoice in the UK use an ftdi-based device for their 1Mb */
multiline_comment|/* broadband internet service.  The following PID is exhibited by the usb device supplied */
multiline_comment|/* (the VID is the standard ftdi vid (FTDI_VID) */
DECL|macro|FTDI_VNHCPCUSB_D_PID
mdefine_line|#define FTDI_VNHCPCUSB_D_PID 0xfe38 /* Product Id */
multiline_comment|/*&n; * The following are the values for the Matrix Orbital LCD displays,&n; * which are the FT232BM ( similar to the 8U232AM )&n; */
DECL|macro|FTDI_MTXORB_0_PID
mdefine_line|#define FTDI_MTXORB_0_PID      0xFA00  /* Matrix Orbital Product Id */
DECL|macro|FTDI_MTXORB_1_PID
mdefine_line|#define FTDI_MTXORB_1_PID      0xFA01  /* Matrix Orbital Product Id */
DECL|macro|FTDI_MTXORB_2_PID
mdefine_line|#define FTDI_MTXORB_2_PID      0xFA02  /* Matrix Orbital Product Id */
DECL|macro|FTDI_MTXORB_3_PID
mdefine_line|#define FTDI_MTXORB_3_PID      0xFA03  /* Matrix Orbital Product Id */
DECL|macro|FTDI_MTXORB_4_PID
mdefine_line|#define FTDI_MTXORB_4_PID      0xFA04  /* Matrix Orbital Product Id */
DECL|macro|FTDI_MTXORB_5_PID
mdefine_line|#define FTDI_MTXORB_5_PID      0xFA05  /* Matrix Orbital Product Id */
DECL|macro|FTDI_MTXORB_6_PID
mdefine_line|#define FTDI_MTXORB_6_PID      0xFA06  /* Matrix Orbital Product Id */
multiline_comment|/* Interbiometrics USB I/O Board */
multiline_comment|/* Developed for Interbiometrics by Rudolf Gugler */
DECL|macro|INTERBIOMETRICS_VID
mdefine_line|#define INTERBIOMETRICS_VID              0x1209
DECL|macro|INTERBIOMETRICS_IOBOARD_PID
mdefine_line|#define INTERBIOMETRICS_IOBOARD_PID      0x1002
DECL|macro|INTERBIOMETRICS_MINI_IOBOARD_PID
mdefine_line|#define INTERBIOMETRICS_MINI_IOBOARD_PID 0x1006
multiline_comment|/*&n; * The following are the values for the Perle Systems&n; * UltraPort USB serial converters&n; */
DECL|macro|FTDI_PERLE_ULTRAPORT_PID
mdefine_line|#define FTDI_PERLE_ULTRAPORT_PID 0xF0C0&t;/* Perle UltraPort Product Id */
multiline_comment|/*&n; * The following are the values for the Sealevel SeaLINK+ adapters.&n; * (Original list sent by Tuan Hoang.  Ian Abbott renamed the macros and&n; * removed some PIDs that don&squot;t seem to match any existing products.)&n; */
DECL|macro|SEALEVEL_VID
mdefine_line|#define SEALEVEL_VID&t;&t;0x0c52&t;/* Sealevel Vendor ID */
DECL|macro|SEALEVEL_2101_PID
mdefine_line|#define SEALEVEL_2101_PID&t;0x2101&t;/* SeaLINK+232 (2101/2105) */
DECL|macro|SEALEVEL_2102_PID
mdefine_line|#define SEALEVEL_2102_PID&t;0x2102&t;/* SeaLINK+485 (2102) */
DECL|macro|SEALEVEL_2103_PID
mdefine_line|#define SEALEVEL_2103_PID&t;0x2103&t;/* SeaLINK+232I (2103) */
DECL|macro|SEALEVEL_2104_PID
mdefine_line|#define SEALEVEL_2104_PID&t;0x2104&t;/* SeaLINK+485I (2104) */
DECL|macro|SEALEVEL_2201_1_PID
mdefine_line|#define SEALEVEL_2201_1_PID&t;0x2211&t;/* SeaPORT+2/232 (2201) Port 1 */
DECL|macro|SEALEVEL_2201_2_PID
mdefine_line|#define SEALEVEL_2201_2_PID&t;0x2221&t;/* SeaPORT+2/232 (2201) Port 2 */
DECL|macro|SEALEVEL_2202_1_PID
mdefine_line|#define SEALEVEL_2202_1_PID&t;0x2212&t;/* SeaPORT+2/485 (2202) Port 1 */
DECL|macro|SEALEVEL_2202_2_PID
mdefine_line|#define SEALEVEL_2202_2_PID&t;0x2222&t;/* SeaPORT+2/485 (2202) Port 2 */
DECL|macro|SEALEVEL_2203_1_PID
mdefine_line|#define SEALEVEL_2203_1_PID&t;0x2213&t;/* SeaPORT+2 (2203) Port 1 */
DECL|macro|SEALEVEL_2203_2_PID
mdefine_line|#define SEALEVEL_2203_2_PID&t;0x2223&t;/* SeaPORT+2 (2203) Port 2 */
DECL|macro|SEALEVEL_2401_1_PID
mdefine_line|#define SEALEVEL_2401_1_PID&t;0x2411&t;/* SeaPORT+4/232 (2401) Port 1 */
DECL|macro|SEALEVEL_2401_2_PID
mdefine_line|#define SEALEVEL_2401_2_PID&t;0x2421&t;/* SeaPORT+4/232 (2401) Port 2 */
DECL|macro|SEALEVEL_2401_3_PID
mdefine_line|#define SEALEVEL_2401_3_PID&t;0x2431&t;/* SeaPORT+4/232 (2401) Port 3 */
DECL|macro|SEALEVEL_2401_4_PID
mdefine_line|#define SEALEVEL_2401_4_PID&t;0x2441&t;/* SeaPORT+4/232 (2401) Port 4 */
DECL|macro|SEALEVEL_2402_1_PID
mdefine_line|#define SEALEVEL_2402_1_PID&t;0x2412&t;/* SeaPORT+4/485 (2402) Port 1 */
DECL|macro|SEALEVEL_2402_2_PID
mdefine_line|#define SEALEVEL_2402_2_PID&t;0x2422&t;/* SeaPORT+4/485 (2402) Port 2 */
DECL|macro|SEALEVEL_2402_3_PID
mdefine_line|#define SEALEVEL_2402_3_PID&t;0x2432&t;/* SeaPORT+4/485 (2402) Port 3 */
DECL|macro|SEALEVEL_2402_4_PID
mdefine_line|#define SEALEVEL_2402_4_PID&t;0x2442&t;/* SeaPORT+4/485 (2402) Port 4 */
DECL|macro|SEALEVEL_2403_1_PID
mdefine_line|#define SEALEVEL_2403_1_PID&t;0x2413&t;/* SeaPORT+4 (2403) Port 1 */
DECL|macro|SEALEVEL_2403_2_PID
mdefine_line|#define SEALEVEL_2403_2_PID&t;0x2423&t;/* SeaPORT+4 (2403) Port 2 */
DECL|macro|SEALEVEL_2403_3_PID
mdefine_line|#define SEALEVEL_2403_3_PID&t;0x2433&t;/* SeaPORT+4 (2403) Port 3 */
DECL|macro|SEALEVEL_2403_4_PID
mdefine_line|#define SEALEVEL_2403_4_PID&t;0x2443&t;/* SeaPORT+4 (2403) Port 4 */
DECL|macro|SEALEVEL_2801_1_PID
mdefine_line|#define SEALEVEL_2801_1_PID&t;0X2811&t;/* SeaLINK+8/232 (2801) Port 1 */
DECL|macro|SEALEVEL_2801_2_PID
mdefine_line|#define SEALEVEL_2801_2_PID&t;0X2821&t;/* SeaLINK+8/232 (2801) Port 2 */
DECL|macro|SEALEVEL_2801_3_PID
mdefine_line|#define SEALEVEL_2801_3_PID&t;0X2831&t;/* SeaLINK+8/232 (2801) Port 3 */
DECL|macro|SEALEVEL_2801_4_PID
mdefine_line|#define SEALEVEL_2801_4_PID&t;0X2841&t;/* SeaLINK+8/232 (2801) Port 4 */
DECL|macro|SEALEVEL_2801_5_PID
mdefine_line|#define SEALEVEL_2801_5_PID&t;0X2851&t;/* SeaLINK+8/232 (2801) Port 5 */
DECL|macro|SEALEVEL_2801_6_PID
mdefine_line|#define SEALEVEL_2801_6_PID&t;0X2861&t;/* SeaLINK+8/232 (2801) Port 6 */
DECL|macro|SEALEVEL_2801_7_PID
mdefine_line|#define SEALEVEL_2801_7_PID&t;0X2871&t;/* SeaLINK+8/232 (2801) Port 7 */
DECL|macro|SEALEVEL_2801_8_PID
mdefine_line|#define SEALEVEL_2801_8_PID&t;0X2881&t;/* SeaLINK+8/232 (2801) Port 8 */
DECL|macro|SEALEVEL_2802_1_PID
mdefine_line|#define SEALEVEL_2802_1_PID&t;0X2812&t;/* SeaLINK+8/485 (2802) Port 1 */
DECL|macro|SEALEVEL_2802_2_PID
mdefine_line|#define SEALEVEL_2802_2_PID&t;0X2822&t;/* SeaLINK+8/485 (2802) Port 2 */
DECL|macro|SEALEVEL_2802_3_PID
mdefine_line|#define SEALEVEL_2802_3_PID&t;0X2832&t;/* SeaLINK+8/485 (2802) Port 3 */
DECL|macro|SEALEVEL_2802_4_PID
mdefine_line|#define SEALEVEL_2802_4_PID&t;0X2842&t;/* SeaLINK+8/485 (2802) Port 4 */
DECL|macro|SEALEVEL_2802_5_PID
mdefine_line|#define SEALEVEL_2802_5_PID&t;0X2852&t;/* SeaLINK+8/485 (2802) Port 5 */
DECL|macro|SEALEVEL_2802_6_PID
mdefine_line|#define SEALEVEL_2802_6_PID&t;0X2862&t;/* SeaLINK+8/485 (2802) Port 6 */
DECL|macro|SEALEVEL_2802_7_PID
mdefine_line|#define SEALEVEL_2802_7_PID&t;0X2872&t;/* SeaLINK+8/485 (2802) Port 7 */
DECL|macro|SEALEVEL_2802_8_PID
mdefine_line|#define SEALEVEL_2802_8_PID&t;0X2882&t;/* SeaLINK+8/485 (2802) Port 8 */
DECL|macro|SEALEVEL_2803_1_PID
mdefine_line|#define SEALEVEL_2803_1_PID&t;0X2813&t;/* SeaLINK+8 (2803) Port 1 */
DECL|macro|SEALEVEL_2803_2_PID
mdefine_line|#define SEALEVEL_2803_2_PID&t;0X2823 &t;/* SeaLINK+8 (2803) Port 2 */
DECL|macro|SEALEVEL_2803_3_PID
mdefine_line|#define SEALEVEL_2803_3_PID&t;0X2833 &t;/* SeaLINK+8 (2803) Port 3 */
DECL|macro|SEALEVEL_2803_4_PID
mdefine_line|#define SEALEVEL_2803_4_PID&t;0X2843 &t;/* SeaLINK+8 (2803) Port 4 */
DECL|macro|SEALEVEL_2803_5_PID
mdefine_line|#define SEALEVEL_2803_5_PID&t;0X2853 &t;/* SeaLINK+8 (2803) Port 5 */
DECL|macro|SEALEVEL_2803_6_PID
mdefine_line|#define SEALEVEL_2803_6_PID&t;0X2863 &t;/* SeaLINK+8 (2803) Port 6 */
DECL|macro|SEALEVEL_2803_7_PID
mdefine_line|#define SEALEVEL_2803_7_PID&t;0X2873 &t;/* SeaLINK+8 (2803) Port 7 */
DECL|macro|SEALEVEL_2803_8_PID
mdefine_line|#define SEALEVEL_2803_8_PID&t;0X2883 &t;/* SeaLINK+8 (2803) Port 8 */
multiline_comment|/*&n; * DSS-20 Sync Station for Sony Ericsson P800&n; */
DECL|macro|FTDI_DSS20_PID
mdefine_line|#define FTDI_DSS20_PID          0xFC82  
multiline_comment|/*&n; * Home Electronics (www.home-electro.com) USB gadgets&n; */
DECL|macro|FTDI_HE_TIRA1_PID
mdefine_line|#define FTDI_HE_TIRA1_PID&t;0xFA78&t;/* Tira-1 IR tranceiver */
multiline_comment|/* USB-UIRT - An infrared receiver and transmitter using the 8U232AM chip */
multiline_comment|/* http://home.earthlink.net/~jrhees/USBUIRT/index.htm */
DECL|macro|FTDI_USB_UIRT_PID
mdefine_line|#define FTDI_USB_UIRT_PID&t;0xF850&t;/* Product Id */
multiline_comment|/* ELV USB Module UO100 (PID sent by Stefan Frings) */
DECL|macro|FTDI_ELV_UO100_PID
mdefine_line|#define FTDI_ELV_UO100_PID&t;0xFB58&t;/* Product Id */
multiline_comment|/*&n; * Definitions for ID TECH (www.idt-net.com) devices&n; */
DECL|macro|IDTECH_VID
mdefine_line|#define IDTECH_VID&t;&t;0x0ACD&t;/* ID TECH Vendor ID */
DECL|macro|IDTECH_IDT1221U_PID
mdefine_line|#define IDTECH_IDT1221U_PID&t;0x0300&t;/* IDT1221U USB to RS-232 adapter */
multiline_comment|/*&n; * Definitions for Omnidirectional Control Technology, Inc. devices&n; */
DECL|macro|OCT_VID
mdefine_line|#define OCT_VID&t;&t;&t;0x0B39&t;/* OCT vendor ID */
multiline_comment|/* Note: OCT US101 is also rebadged as Dick Smith Electronics (NZ) XH6381 */
multiline_comment|/* Also rebadged as SIIG Inc. model US2308 */
DECL|macro|OCT_US101_PID
mdefine_line|#define OCT_US101_PID&t;&t;0x0421&t;/* OCT US101 USB to RS-232 */
multiline_comment|/* an infrared receiver for user access control with IR tags */
DECL|macro|FTDI_PIEGROUP_PID
mdefine_line|#define FTDI_PIEGROUP_PID&t;0xF208&t;/* Product Id */
multiline_comment|/*&n; * Protego product ids&n; */
DECL|macro|PROTEGO_SPECIAL_1
mdefine_line|#define PROTEGO_SPECIAL_1&t;0xFC70&t;/* special/unknown device */
DECL|macro|PROTEGO_R2X0
mdefine_line|#define PROTEGO_R2X0&t;&t;0xFC71&t;/* R200-USB TRNG unit (R210, R220, and R230) */
DECL|macro|PROTEGO_SPECIAL_3
mdefine_line|#define PROTEGO_SPECIAL_3&t;0xFC72&t;/* special/unknown device */
DECL|macro|PROTEGO_SPECIAL_4
mdefine_line|#define PROTEGO_SPECIAL_4&t;0xFC73&t;/* special/unknown device */
multiline_comment|/*&n; * Gude Analog- und Digitalsysteme GmbH&n; */
DECL|macro|FTDI_GUDEADS_E808_PID
mdefine_line|#define FTDI_GUDEADS_E808_PID    0xE808
DECL|macro|FTDI_GUDEADS_E809_PID
mdefine_line|#define FTDI_GUDEADS_E809_PID    0xE809
DECL|macro|FTDI_GUDEADS_E80A_PID
mdefine_line|#define FTDI_GUDEADS_E80A_PID    0xE80A
DECL|macro|FTDI_GUDEADS_E80B_PID
mdefine_line|#define FTDI_GUDEADS_E80B_PID    0xE80B
DECL|macro|FTDI_GUDEADS_E80C_PID
mdefine_line|#define FTDI_GUDEADS_E80C_PID    0xE80C
DECL|macro|FTDI_GUDEADS_E80D_PID
mdefine_line|#define FTDI_GUDEADS_E80D_PID    0xE80D
DECL|macro|FTDI_GUDEADS_E80E_PID
mdefine_line|#define FTDI_GUDEADS_E80E_PID    0xE80E
DECL|macro|FTDI_GUDEADS_E80F_PID
mdefine_line|#define FTDI_GUDEADS_E80F_PID    0xE80F
DECL|macro|FTDI_GUDEADS_E888_PID
mdefine_line|#define FTDI_GUDEADS_E888_PID    0xE888  /* Expert ISDN Control USB */
DECL|macro|FTDI_GUDEADS_E889_PID
mdefine_line|#define FTDI_GUDEADS_E889_PID    0xE889  /* USB RS-232 OptoBridge */
DECL|macro|FTDI_GUDEADS_E88A_PID
mdefine_line|#define FTDI_GUDEADS_E88A_PID    0xE88A
DECL|macro|FTDI_GUDEADS_E88B_PID
mdefine_line|#define FTDI_GUDEADS_E88B_PID    0xE88B
DECL|macro|FTDI_GUDEADS_E88C_PID
mdefine_line|#define FTDI_GUDEADS_E88C_PID    0xE88C
DECL|macro|FTDI_GUDEADS_E88D_PID
mdefine_line|#define FTDI_GUDEADS_E88D_PID    0xE88D
DECL|macro|FTDI_GUDEADS_E88E_PID
mdefine_line|#define FTDI_GUDEADS_E88E_PID    0xE88E
DECL|macro|FTDI_GUDEADS_E88F_PID
mdefine_line|#define FTDI_GUDEADS_E88F_PID    0xE88F
multiline_comment|/*&n; * Linx Technologies product ids&n; */
DECL|macro|LINX_SDMUSBQSS_PID
mdefine_line|#define LINX_SDMUSBQSS_PID&t;0xF448&t;/* Linx SDM-USB-QS-S */
DECL|macro|LINX_MASTERDEVEL2_PID
mdefine_line|#define LINX_MASTERDEVEL2_PID   0xF449   /* Linx Master Development 2.0 */
DECL|macro|LINX_FUTURE_0_PID
mdefine_line|#define LINX_FUTURE_0_PID   0xF44A   /* Linx future device */
DECL|macro|LINX_FUTURE_1_PID
mdefine_line|#define LINX_FUTURE_1_PID   0xF44B   /* Linx future device */
DECL|macro|LINX_FUTURE_2_PID
mdefine_line|#define LINX_FUTURE_2_PID   0xF44C   /* Linx future device */
multiline_comment|/* CCS Inc. ICDU/ICDU40 product ID - the FT232BM is used in an in-circuit-debugger */
multiline_comment|/* unit for PIC16&squot;s/PIC18&squot;s */
DECL|macro|FTDI_CCSICDU20_0_PID
mdefine_line|#define FTDI_CCSICDU20_0_PID    0xF9D0     
DECL|macro|FTDI_CCSICDU40_1_PID
mdefine_line|#define FTDI_CCSICDU40_1_PID    0xF9D1     
multiline_comment|/* Inside Accesso contactless reader (http://www.insidefr.com) */
DECL|macro|INSIDE_ACCESSO
mdefine_line|#define INSIDE_ACCESSO&t;&t;0xFAD0
multiline_comment|/*&n; * Intrepid Control Systems (http://www.intrepidcs.com/) ValueCAN and NeoVI&n; */
DECL|macro|INTREPID_VID
mdefine_line|#define INTREPID_VID&t;&t;0x093C
DECL|macro|INTREPID_VALUECAN_PID
mdefine_line|#define INTREPID_VALUECAN_PID&t;0x0601
DECL|macro|INTREPID_NEOVI_PID
mdefine_line|#define INTREPID_NEOVI_PID&t;0x0701
multiline_comment|/*&n; * Falcom Wireless Communications GmbH&n; */
DECL|macro|FALCOM_VID
mdefine_line|#define FALCOM_VID&t;&t;0x0F94&t;/* Vendor Id */
DECL|macro|FALCOM_TWIST_PID
mdefine_line|#define FALCOM_TWIST_PID&t;0x0001&t;/* Falcom Twist USB GPRS modem */
multiline_comment|/*&n; * SUUNTO product ids&n; */
DECL|macro|FTDI_SUUNTO_SPORTS_PID
mdefine_line|#define FTDI_SUUNTO_SPORTS_PID&t;0xF680&t;/* Suunto Sports instrument */
multiline_comment|/*&n; * Definitions for B&amp;B Electronics products.&n; */
DECL|macro|BANDB_VID
mdefine_line|#define BANDB_VID&t;&t;0x0856&t;/* B&amp;B Electronics Vendor ID */
DECL|macro|BANDB_USOTL4_PID
mdefine_line|#define BANDB_USOTL4_PID&t;0xAC01&t;/* USOTL4 Isolated RS-485 Converter */
DECL|macro|BANDB_USTL4_PID
mdefine_line|#define BANDB_USTL4_PID&t;&t;0xAC02&t;/* USTL4 RS-485 Converter */
DECL|macro|BANDB_USO9ML2_PID
mdefine_line|#define BANDB_USO9ML2_PID&t;0xAC03&t;/* USO9ML2 Isolated RS-232 Converter */
multiline_comment|/*&n; * RM Michaelides CANview USB (http://www.rmcan.com)&n; * CAN filedbus interface adapter, addad by port GmbH www.port.de)&n; */
DECL|macro|FTDI_RM_VID
mdefine_line|#define FTDI_RM_VID&t;&t;0x0403&t;/* Vendor  Id */
DECL|macro|FTDI_RMCANVIEW_PID
mdefine_line|#define FTDI_RMCANVIEW_PID&t;0xfd60&t;/* Product Id */
multiline_comment|/*&n; * EVER Eco Pro UPS (http://www.ever.com.pl/)&n; */
DECL|macro|EVER_ECO_PRO_CDS
mdefine_line|#define&t;EVER_ECO_PRO_CDS&t;0xe520&t;/* RS-232 converter */
multiline_comment|/* Commands */
DECL|macro|FTDI_SIO_RESET
mdefine_line|#define FTDI_SIO_RESET &t;&t;0 /* Reset the port */
DECL|macro|FTDI_SIO_MODEM_CTRL
mdefine_line|#define FTDI_SIO_MODEM_CTRL &t;1 /* Set the modem control register */
DECL|macro|FTDI_SIO_SET_FLOW_CTRL
mdefine_line|#define FTDI_SIO_SET_FLOW_CTRL&t;2 /* Set flow control register */
DECL|macro|FTDI_SIO_SET_BAUD_RATE
mdefine_line|#define FTDI_SIO_SET_BAUD_RATE&t;3 /* Set baud rate */
DECL|macro|FTDI_SIO_SET_DATA
mdefine_line|#define FTDI_SIO_SET_DATA&t;4 /* Set the data characteristics of the port */
DECL|macro|FTDI_SIO_GET_MODEM_STATUS
mdefine_line|#define FTDI_SIO_GET_MODEM_STATUS&t;5 /* Retrieve current value of modern status register */
DECL|macro|FTDI_SIO_SET_EVENT_CHAR
mdefine_line|#define FTDI_SIO_SET_EVENT_CHAR&t;6 /* Set the event character */
DECL|macro|FTDI_SIO_SET_ERROR_CHAR
mdefine_line|#define FTDI_SIO_SET_ERROR_CHAR&t;7 /* Set the error character */
DECL|macro|FTDI_SIO_SET_LATENCY_TIMER
mdefine_line|#define FTDI_SIO_SET_LATENCY_TIMER&t;9 /* Set the latency timer */
DECL|macro|FTDI_SIO_GET_LATENCY_TIMER
mdefine_line|#define FTDI_SIO_GET_LATENCY_TIMER&t;10 /* Get the latency timer */
multiline_comment|/* Port interface code for FT2232C */
DECL|macro|INTERFACE_A
mdefine_line|#define INTERFACE_A&t;&t;1
DECL|macro|INTERFACE_B
mdefine_line|#define INTERFACE_B&t;&t;2
multiline_comment|/*&n; *   BmRequestType:  1100 0000b&n; *   bRequest:       FTDI_E2_READ&n; *   wValue:         0&n; *   wIndex:         Address of word to read&n; *   wLength:        2&n; *   Data:           Will return a word of data from E2Address&n; *&n; */
multiline_comment|/* Port Identifier Table */
DECL|macro|PIT_DEFAULT
mdefine_line|#define PIT_DEFAULT &t;&t;0 /* SIOA */
DECL|macro|PIT_SIOA
mdefine_line|#define PIT_SIOA&t;&t;1 /* SIOA */
multiline_comment|/* The device this driver is tested with one has only one port */
DECL|macro|PIT_SIOB
mdefine_line|#define PIT_SIOB&t;&t;2 /* SIOB */
DECL|macro|PIT_PARALLEL
mdefine_line|#define PIT_PARALLEL&t;&t;3 /* Parallel */
multiline_comment|/* FTDI_SIO_RESET */
DECL|macro|FTDI_SIO_RESET_REQUEST
mdefine_line|#define FTDI_SIO_RESET_REQUEST FTDI_SIO_RESET
DECL|macro|FTDI_SIO_RESET_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_RESET_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_RESET_SIO
mdefine_line|#define FTDI_SIO_RESET_SIO 0
DECL|macro|FTDI_SIO_RESET_PURGE_RX
mdefine_line|#define FTDI_SIO_RESET_PURGE_RX 1
DECL|macro|FTDI_SIO_RESET_PURGE_TX
mdefine_line|#define FTDI_SIO_RESET_PURGE_TX 2
multiline_comment|/*&n; * BmRequestType:  0100 0000B&n; * bRequest:       FTDI_SIO_RESET&n; * wValue:         Control Value &n; *                   0 = Reset SIO&n; *                   1 = Purge RX buffer&n; *                   2 = Purge TX buffer&n; * wIndex:         Port&n; * wLength:        0&n; * Data:           None&n; *&n; * The Reset SIO command has this effect:&n; *&n; *    Sets flow control set to &squot;none&squot;&n; *    Event char = $0D&n; *    Event trigger = disabled&n; *    Purge RX buffer&n; *    Purge TX buffer&n; *    Clear DTR&n; *    Clear RTS&n; *    baud and data format not reset&n; *&n; * The Purge RX and TX buffer commands affect nothing except the buffers&n; *&n;   */
multiline_comment|/* FTDI_SIO_SET_BAUDRATE */
DECL|macro|FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_BAUDRATE_REQUEST
mdefine_line|#define FTDI_SIO_SET_BAUDRATE_REQUEST 3
multiline_comment|/*&n; * BmRequestType:  0100 0000B&n; * bRequest:       FTDI_SIO_SET_BAUDRATE&n; * wValue:         BaudDivisor value - see below&n; * wIndex:         Port&n; * wLength:        0&n; * Data:           None&n; * The BaudDivisor values are calculated as follows:&n; * - BaseClock is either 12000000 or 48000000 depending on the device. FIXME: I wish&n; *   I knew how to detect old chips to select proper base clock!&n; * - BaudDivisor is a fixed point number encoded in a funny way.&n; *   (--WRONG WAY OF THINKING--)&n; *   BaudDivisor is a fixed point number encoded with following bit weighs:&n; *   (-2)(-1)(13..0). It is a radical with a denominator of 4, so values&n; *   end with 0.0 (00...), 0.25 (10...), 0.5 (01...), and 0.75 (11...).&n; *   (--THE REALITY--)&n; *   The both-bits-set has quite different meaning from 0.75 - the chip designers&n; *   have decided it to mean 0.125 instead of 0.75.&n; *   This info looked up in FTDI application note &quot;FT8U232 DEVICES &bslash; Data Rates&n; *   and Flow Control Consideration for USB to RS232&quot;.&n; * - BaudDivisor = (BaseClock / 16) / BaudRate, where the (=) operation should&n; *   automagically re-encode the resulting value to take fractions into consideration.&n; * As all values are integers, some bit twiddling is in order:&n; *   BaudDivisor = (BaseClock / 16 / BaudRate) |&n; *   (((BaseClock / 2 / BaudRate) &amp; 4) ? 0x4000    // 0.5&n; *    : ((BaseClock / 2 / BaudRate) &amp; 2) ? 0x8000  // 0.25&n; *    : ((BaseClock / 2 / BaudRate) &amp; 1) ? 0xc000  // 0.125&n; *    : 0)&n; *&n; * For the FT232BM, a 17th divisor bit was introduced to encode the multiples&n; * of 0.125 missing from the FT8U232AM.  Bits 16 to 14 are coded as follows&n; * (the first four codes are the same as for the FT8U232AM, where bit 16 is&n; * always 0):&n; *   000 - add .000 to divisor&n; *   001 - add .500 to divisor&n; *   010 - add .250 to divisor&n; *   011 - add .125 to divisor&n; *   100 - add .375 to divisor&n; *   101 - add .625 to divisor&n; *   110 - add .750 to divisor&n; *   111 - add .875 to divisor&n; * Bits 15 to 0 of the 17-bit divisor are placed in the urb value.  Bit 16 is &n; * placed in bit 0 of the urb index.&n; *&n; * Note that there are a couple of special cases to support the highest baud&n; * rates.  If the calculated divisor value is 1, this needs to be replaced with&n; * 0.  Additionally for the FT232BM, if the calculated divisor value is 0x4001&n; * (1.5), this needs to be replaced with 0x0001 (1) (but this divisor value is&n; * not supported by the FT8U232AM).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SIO
id|SIO
op_assign
l_int|1
comma
DECL|enumerator|FT8U232AM
id|FT8U232AM
op_assign
l_int|2
comma
DECL|enumerator|FT232BM
id|FT232BM
op_assign
l_int|3
comma
DECL|enumerator|FT2232C
id|FT2232C
op_assign
l_int|4
comma
DECL|typedef|ftdi_chip_type_t
)brace
id|ftdi_chip_type_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|ftdi_sio_b300
id|ftdi_sio_b300
op_assign
l_int|0
comma
DECL|enumerator|ftdi_sio_b600
id|ftdi_sio_b600
op_assign
l_int|1
comma
DECL|enumerator|ftdi_sio_b1200
id|ftdi_sio_b1200
op_assign
l_int|2
comma
DECL|enumerator|ftdi_sio_b2400
id|ftdi_sio_b2400
op_assign
l_int|3
comma
DECL|enumerator|ftdi_sio_b4800
id|ftdi_sio_b4800
op_assign
l_int|4
comma
DECL|enumerator|ftdi_sio_b9600
id|ftdi_sio_b9600
op_assign
l_int|5
comma
DECL|enumerator|ftdi_sio_b19200
id|ftdi_sio_b19200
op_assign
l_int|6
comma
DECL|enumerator|ftdi_sio_b38400
id|ftdi_sio_b38400
op_assign
l_int|7
comma
DECL|enumerator|ftdi_sio_b57600
id|ftdi_sio_b57600
op_assign
l_int|8
comma
DECL|enumerator|ftdi_sio_b115200
id|ftdi_sio_b115200
op_assign
l_int|9
DECL|typedef|FTDI_SIO_baudrate_t
)brace
id|FTDI_SIO_baudrate_t
suffix:semicolon
multiline_comment|/*&n; * The ftdi_8U232AM_xxMHz_byyy constants have been removed. The encoded divisor values&n; * are calculated internally.&n; */
DECL|macro|FTDI_SIO_SET_DATA_REQUEST
mdefine_line|#define FTDI_SIO_SET_DATA_REQUEST FTDI_SIO_SET_DATA
DECL|macro|FTDI_SIO_SET_DATA_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_DATA_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_DATA_PARITY_NONE
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_NONE (0x0 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_ODD
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_ODD (0x1 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_EVEN
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_EVEN (0x2 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_MARK
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_MARK (0x3 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_SPACE
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_SPACE (0x4 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_STOP_BITS_1
mdefine_line|#define FTDI_SIO_SET_DATA_STOP_BITS_1 (0x0 &lt;&lt; 11 )
DECL|macro|FTDI_SIO_SET_DATA_STOP_BITS_15
mdefine_line|#define FTDI_SIO_SET_DATA_STOP_BITS_15 (0x1 &lt;&lt; 11 )
DECL|macro|FTDI_SIO_SET_DATA_STOP_BITS_2
mdefine_line|#define FTDI_SIO_SET_DATA_STOP_BITS_2 (0x2 &lt;&lt; 11 )
DECL|macro|FTDI_SIO_SET_BREAK
mdefine_line|#define FTDI_SIO_SET_BREAK (0x1 &lt;&lt; 14)
multiline_comment|/* FTDI_SIO_SET_DATA */
multiline_comment|/*&n; * BmRequestType:  0100 0000B &n; * bRequest:       FTDI_SIO_SET_DATA&n; * wValue:         Data characteristics (see below)&n; * wIndex:         Port&n; * wLength:        0&n; * Data:           No&n; *&n; * Data characteristics&n; *&n; *   B0..7   Number of data bits&n; *   B8..10  Parity&n; *           0 = None&n; *           1 = Odd&n; *           2 = Even&n; *           3 = Mark&n; *           4 = Space&n; *   B11..13 Stop Bits&n; *           0 = 1&n; *           1 = 1.5&n; *           2 = 2&n; *   B14&n; *           1 = TX ON (break)&n; *           0 = TX OFF (normal state)&n; *   B15 Reserved&n; *&n; */
multiline_comment|/* FTDI_SIO_MODEM_CTRL */
DECL|macro|FTDI_SIO_SET_MODEM_CTRL_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_MODEM_CTRL_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_MODEM_CTRL_REQUEST
mdefine_line|#define FTDI_SIO_SET_MODEM_CTRL_REQUEST FTDI_SIO_MODEM_CTRL
multiline_comment|/* &n; * BmRequestType:   0100 0000B&n; * bRequest:        FTDI_SIO_MODEM_CTRL&n; * wValue:          ControlValue (see below)&n; * wIndex:          Port&n; * wLength:         0&n; * Data:            None&n; *&n; * NOTE: If the device is in RTS/CTS flow control, the RTS set by this&n; * command will be IGNORED without an error being returned&n; * Also - you can not set DTR and RTS with one control message&n; */
DECL|macro|FTDI_SIO_SET_DTR_MASK
mdefine_line|#define FTDI_SIO_SET_DTR_MASK 0x1
DECL|macro|FTDI_SIO_SET_DTR_HIGH
mdefine_line|#define FTDI_SIO_SET_DTR_HIGH ( 1 | ( FTDI_SIO_SET_DTR_MASK  &lt;&lt; 8))
DECL|macro|FTDI_SIO_SET_DTR_LOW
mdefine_line|#define FTDI_SIO_SET_DTR_LOW  ( 0 | ( FTDI_SIO_SET_DTR_MASK  &lt;&lt; 8))
DECL|macro|FTDI_SIO_SET_RTS_MASK
mdefine_line|#define FTDI_SIO_SET_RTS_MASK 0x2
DECL|macro|FTDI_SIO_SET_RTS_HIGH
mdefine_line|#define FTDI_SIO_SET_RTS_HIGH ( 2 | ( FTDI_SIO_SET_RTS_MASK &lt;&lt; 8 ))
DECL|macro|FTDI_SIO_SET_RTS_LOW
mdefine_line|#define FTDI_SIO_SET_RTS_LOW ( 0 | ( FTDI_SIO_SET_RTS_MASK &lt;&lt; 8 ))
multiline_comment|/*&n; * ControlValue&n; * B0    DTR state&n; *          0 = reset&n; *          1 = set&n; * B1    RTS state&n; *          0 = reset&n; *          1 = set&n; * B2..7 Reserved&n; * B8    DTR state enable&n; *          0 = ignore&n; *          1 = use DTR state&n; * B9    RTS state enable&n; *          0 = ignore&n; *          1 = use RTS state&n; * B10..15 Reserved&n; */
multiline_comment|/* FTDI_SIO_SET_FLOW_CTRL */
DECL|macro|FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_FLOW_CTRL_REQUEST
mdefine_line|#define FTDI_SIO_SET_FLOW_CTRL_REQUEST FTDI_SIO_SET_FLOW_CTRL
DECL|macro|FTDI_SIO_DISABLE_FLOW_CTRL
mdefine_line|#define FTDI_SIO_DISABLE_FLOW_CTRL 0x0 
DECL|macro|FTDI_SIO_RTS_CTS_HS
mdefine_line|#define FTDI_SIO_RTS_CTS_HS (0x1 &lt;&lt; 8)
DECL|macro|FTDI_SIO_DTR_DSR_HS
mdefine_line|#define FTDI_SIO_DTR_DSR_HS (0x2 &lt;&lt; 8)
DECL|macro|FTDI_SIO_XON_XOFF_HS
mdefine_line|#define FTDI_SIO_XON_XOFF_HS (0x4 &lt;&lt; 8)
multiline_comment|/*&n; *   BmRequestType:  0100 0000b&n; *   bRequest:       FTDI_SIO_SET_FLOW_CTRL&n; *   wValue:         Xoff/Xon&n; *   wIndex:         Protocol/Port - hIndex is protocl / lIndex is port&n; *   wLength:        0 &n; *   Data:           None&n; *&n; * hIndex protocol is:&n; *   B0 Output handshaking using RTS/CTS&n; *       0 = disabled&n; *       1 = enabled&n; *   B1 Output handshaking using DTR/DSR&n; *       0 = disabled&n; *       1 = enabled&n; *   B2 Xon/Xoff handshaking&n; *       0 = disabled&n; *       1 = enabled&n; *&n; * A value of zero in the hIndex field disables handshaking&n; *&n; * If Xon/Xoff handshaking is specified, the hValue field should contain the XOFF character &n; * and the lValue field contains the XON character.&n; */
multiline_comment|/*&n; * FTDI_SIO_GET_LATENCY_TIMER&n; *&n; * Set the timeout interval. The FTDI collects data from the slave&n; * device, transmitting it to the host when either A) 62 bytes are&n; * received, or B) the timeout interval has elapsed and the buffer&n; * contains at least 1 byte.  Setting this value to a small number&n; * can dramatically improve performance for applications which send&n; * small packets, since the default value is 16ms.&n; */
DECL|macro|FTDI_SIO_GET_LATENCY_TIMER_REQUEST
mdefine_line|#define  FTDI_SIO_GET_LATENCY_TIMER_REQUEST FTDI_SIO_GET_LATENCY_TIMER
DECL|macro|FTDI_SIO_GET_LATENCY_TIMER_REQUEST_TYPE
mdefine_line|#define  FTDI_SIO_GET_LATENCY_TIMER_REQUEST_TYPE 0xC0
multiline_comment|/* &n; *  BmRequestType:   1100 0000b&n; *  bRequest:        FTDI_SIO_GET_LATENCY_TIMER&n; *  wValue:          0&n; *  wIndex:          Port&n; *  wLength:         0&n; *  Data:            latency (on return)&n; */
multiline_comment|/* &n; * FTDI_SIO_SET_LATENCY_TIMER&n; *&n; * Set the timeout interval. The FTDI collects data from the slave&n; * device, transmitting it to the host when either A) 62 bytes are&n; * received, or B) the timeout interval has elapsed and the buffer&n; * contains at least 1 byte.  Setting this value to a small number&n; * can dramatically improve performance for applications which send&n; * small packets, since the default value is 16ms.&n; */
DECL|macro|FTDI_SIO_SET_LATENCY_TIMER_REQUEST
mdefine_line|#define  FTDI_SIO_SET_LATENCY_TIMER_REQUEST FTDI_SIO_SET_LATENCY_TIMER
DECL|macro|FTDI_SIO_SET_LATENCY_TIMER_REQUEST_TYPE
mdefine_line|#define  FTDI_SIO_SET_LATENCY_TIMER_REQUEST_TYPE 0x40
multiline_comment|/* &n; *  BmRequestType:   0100 0000b&n; *  bRequest:        FTDI_SIO_SET_LATENCY_TIMER&n; *  wValue:          Latency (milliseconds)&n; *  wIndex:          Port&n; *  wLength:         0&n; *  Data:            None&n; *&n; * wValue:&n; *   B0..7   Latency timer&n; *   B8..15  0&n; *&n; */
multiline_comment|/*&n; * FTDI_SIO_SET_EVENT_CHAR &n; *&n; * Set the special event character for the specified communications port.&n; * If the device sees this character it will immediately return the&n; * data read so far - rather than wait 40ms or until 62 bytes are read&n; * which is what normally happens.&n; */
DECL|macro|FTDI_SIO_SET_EVENT_CHAR_REQUEST
mdefine_line|#define  FTDI_SIO_SET_EVENT_CHAR_REQUEST FTDI_SIO_SET_EVENT_CHAR
DECL|macro|FTDI_SIO_SET_EVENT_CHAR_REQUEST_TYPE
mdefine_line|#define  FTDI_SIO_SET_EVENT_CHAR_REQUEST_TYPE 0x40
multiline_comment|/* &n; *  BmRequestType:   0100 0000b&n; *  bRequest:        FTDI_SIO_SET_EVENT_CHAR&n; *  wValue:          EventChar&n; *  wIndex:          Port&n; *  wLength:         0&n; *  Data:            None&n; *&n; * wValue:&n; *   B0..7   Event Character&n; *   B8      Event Character Processing&n; *             0 = disabled&n; *             1 = enabled&n; *   B9..15  Reserved&n; *&n; */
multiline_comment|/* FTDI_SIO_SET_ERROR_CHAR */
multiline_comment|/* Set the parity error replacement character for the specified communications port */
multiline_comment|/* &n; *  BmRequestType:  0100 0000b&n; *  bRequest:       FTDI_SIO_SET_EVENT_CHAR&n; *  wValue:         Error Char&n; *  wIndex:         Port&n; *  wLength:        0&n; *  Data:           None&n; *&n; *Error Char&n; *  B0..7  Error Character&n; *  B8     Error Character Processing&n; *           0 = disabled&n; *           1 = enabled&n; *  B9..15 Reserved&n; *&n; */
multiline_comment|/* FTDI_SIO_GET_MODEM_STATUS */
multiline_comment|/* Retreive the current value of the modem status register */
DECL|macro|FTDI_SIO_GET_MODEM_STATUS_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_GET_MODEM_STATUS_REQUEST_TYPE 0xc0
DECL|macro|FTDI_SIO_GET_MODEM_STATUS_REQUEST
mdefine_line|#define FTDI_SIO_GET_MODEM_STATUS_REQUEST FTDI_SIO_GET_MODEM_STATUS
DECL|macro|FTDI_SIO_CTS_MASK
mdefine_line|#define FTDI_SIO_CTS_MASK 0x10
DECL|macro|FTDI_SIO_DSR_MASK
mdefine_line|#define FTDI_SIO_DSR_MASK 0x20
DECL|macro|FTDI_SIO_RI_MASK
mdefine_line|#define FTDI_SIO_RI_MASK  0x40
DECL|macro|FTDI_SIO_RLSD_MASK
mdefine_line|#define FTDI_SIO_RLSD_MASK 0x80
multiline_comment|/* &n; *   BmRequestType:   1100 0000b&n; *   bRequest:        FTDI_SIO_GET_MODEM_STATUS&n; *   wValue:          zero&n; *   wIndex:          Port&n; *   wLength:         1&n; *   Data:            Status&n; * &n; * One byte of data is returned &n; * B0..3 0&n; * B4    CTS&n; *         0 = inactive&n; *         1 = active&n; * B5    DSR&n; *         0 = inactive&n; *         1 = active&n; * B6    Ring Indicator (RI)&n; *         0 = inactive&n; *         1 = active&n; * B7    Receive Line Signal Detect (RLSD)&n; *         0 = inactive&n; *         1 = active &n; */
multiline_comment|/* Descriptors returned by the device &n; * &n; *  Device Descriptor&n; * &n; * Offset&t;Field&t;&t;Size&t;Value&t;Description&n; * 0&t;bLength&t;&t;1&t;0x12&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;1&t;0x01&t;DEVICE Descriptor Type&n; * 2&t;bcdUSB&t;&t;2&t;0x0110&t;USB Spec Release Number&n; * 4&t;bDeviceClass&t;1&t;0x00&t;Class Code&n; * 5&t;bDeviceSubClass&t;1&t;0x00&t;SubClass Code&n; * 6&t;bDeviceProtocol&t;1&t;0x00&t;Protocol Code&n; * 7&t;bMaxPacketSize0 1&t;0x08&t;Maximum packet size for endpoint 0&n; * 8&t;idVendor&t;2&t;0x0403&t;Vendor ID&n; * 10&t;idProduct&t;2&t;0x8372&t;Product ID (FTDI_SIO_PID)&n; * 12&t;bcdDevice&t;2&t;0x0001&t;Device release number&n; * 14&t;iManufacturer&t;1&t;0x01&t;Index of man. string desc&n; * 15&t;iProduct&t;1&t;0x02&t;Index of prod string desc&n; * 16&t;iSerialNumber&t;1&t;0x02&t;Index of serial nmr string desc&n; * 17&t;bNumConfigurations 1    0x01&t;Number of possible configurations&n; * &n; * Configuration Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x09&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x02&t;CONFIGURATION Descriptor Type&n; * 2&t;wTotalLength&t;&t;2&t;0x0020&t;Total length of data&n; * 4&t;bNumInterfaces&t;&t;1&t;0x01&t;Number of interfaces supported&n; * 5&t;bConfigurationValue&t;1&t;0x01&t;Argument for SetCOnfiguration() req&n; * 6&t;iConfiguration&t;&t;1&t;0x02&t;Index of config string descriptor&n; * 7&t;bmAttributes&t;&t;1&t;0x20&t;Config characteristics Remote Wakeup&n; * 8&t;MaxPower&t;&t;1&t;0x1E&t;Max power consumption&n; * &n; * Interface Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x09&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x04&t;INTERFACE Descriptor Type&n; * 2&t;bInterfaceNumber&t;1&t;0x00&t;Number of interface&n; * 3&t;bAlternateSetting&t;1&t;0x00&t;Value used to select alternate&n; * 4&t;bNumEndpoints&t;&t;1&t;0x02&t;Number of endpoints&n; * 5&t;bInterfaceClass&t;&t;1&t;0xFF&t;Class Code&n; * 6&t;bInterfaceSubClass&t;1&t;0xFF&t;Subclass Code&n; * 7&t;bInterfaceProtocol&t;1&t;0xFF&t;Protocol Code&n; * 8&t;iInterface&t;&t;1&t;0x02&t;Index of interface string description&n; * &n; * IN Endpoint Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x07&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x05&t;ENDPOINT descriptor type&n; * 2&t;bEndpointAddress&t;1&t;0x82&t;Address of endpoint&n; * 3&t;bmAttributes&t;&t;1&t;0x02&t;Endpoint attributes - Bulk&n; * 4&t;bNumEndpoints&t;&t;2&t;0x0040&t;maximum packet size&n; * 5&t;bInterval&t;&t;1&t;0x00&t;Interval for polling endpoint&n; * &n; * OUT Endpoint Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x07&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x05&t;ENDPOINT descriptor type&n; * 2&t;bEndpointAddress&t;1&t;0x02&t;Address of endpoint&n; * 3&t;bmAttributes&t;&t;1&t;0x02&t;Endpoint attributes - Bulk&n; * 4&t;bNumEndpoints&t;&t;2&t;0x0040&t;maximum packet size&n; * 5&t;bInterval&t;&t;1&t;0x00&t;Interval for polling endpoint&n; *     &n; * DATA FORMAT&n; * &n; * IN Endpoint&n; * &n; * The device reserves the first two bytes of data on this endpoint to contain the current&n; * values of the modem and line status registers. In the absence of data, the device &n; * generates a message consisting of these two status bytes every 40 ms&n; * &n; * Byte 0: Modem Status&n; * &n; * Offset&t;Description&n; * B0&t;Reserved - must be 1&n; * B1&t;Reserved - must be 0&n; * B2&t;Reserved - must be 0&n; * B3&t;Reserved - must be 0&n; * B4&t;Clear to Send (CTS)&n; * B5&t;Data Set Ready (DSR)&n; * B6&t;Ring Indicator (RI)&n; * B7&t;Receive Line Signal Detect (RLSD)&n; * &n; * Byte 1: Line Status&n; * &n; * Offset&t;Description&n; * B0&t;Data Ready (DR)&n; * B1&t;Overrun Error (OE)&n; * B2&t;Parity Error (PE)&n; * B3&t;Framing Error (FE)&n; * B4&t;Break Interrupt (BI)&n; * B5&t;Transmitter Holding Register (THRE)&n; * B6&t;Transmitter Empty (TEMT)&n; * B7&t;Error in RCVR FIFO&n; * &n; */
DECL|macro|FTDI_RS0_CTS
mdefine_line|#define FTDI_RS0_CTS&t;(1 &lt;&lt; 4)
DECL|macro|FTDI_RS0_DSR
mdefine_line|#define FTDI_RS0_DSR&t;(1 &lt;&lt; 5)
DECL|macro|FTDI_RS0_RI
mdefine_line|#define FTDI_RS0_RI&t;(1 &lt;&lt; 6)
DECL|macro|FTDI_RS0_RLSD
mdefine_line|#define FTDI_RS0_RLSD&t;(1 &lt;&lt; 7)
DECL|macro|FTDI_RS_DR
mdefine_line|#define FTDI_RS_DR  1
DECL|macro|FTDI_RS_OE
mdefine_line|#define FTDI_RS_OE (1&lt;&lt;1)
DECL|macro|FTDI_RS_PE
mdefine_line|#define FTDI_RS_PE (1&lt;&lt;2)
DECL|macro|FTDI_RS_FE
mdefine_line|#define FTDI_RS_FE (1&lt;&lt;3)
DECL|macro|FTDI_RS_BI
mdefine_line|#define FTDI_RS_BI (1&lt;&lt;4)
DECL|macro|FTDI_RS_THRE
mdefine_line|#define FTDI_RS_THRE (1&lt;&lt;5)
DECL|macro|FTDI_RS_TEMT
mdefine_line|#define FTDI_RS_TEMT (1&lt;&lt;6)
DECL|macro|FTDI_RS_FIFO
mdefine_line|#define FTDI_RS_FIFO  (1&lt;&lt;7)
multiline_comment|/*&n; * OUT Endpoint&n; * &n; * This device reserves the first bytes of data on this endpoint contain the length&n; * and port identifier of the message. For the FTDI USB Serial converter the port &n; * identifier is always 1.&n; * &n; * Byte 0: Line Status&n; * &n; * Offset&t;Description&n; * B0&t;Reserved - must be 1&n; * B1&t;Reserved - must be 0&n; * B2..7&t;Length of message - (not including Byte 0)&n; * &n; */
eof
