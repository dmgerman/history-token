multiline_comment|/*&n; *  include/asm-mips/tx3912.h&n; *&n; *  Copyright (C) 2001 Steven J. Hill (sjhill@realitydiluted.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Registers for TMPR3912/05 and PR31700 processors&n; */
macro_line|#ifndef _TX3912_H_
DECL|macro|_TX3912_H_
mdefine_line|#define _TX3912_H_
multiline_comment|/*****************************************************************************&n; *&t;Clock Subsystem                                                      *&n; *&t;---------------                                                      *&n; *&t;Chapter 6 in Philips PR31700 and Toshiba TMPR3905/12 User Manuals    *&n; *****************************************************************************/
DECL|macro|TX3912_CLK_CTRL
mdefine_line|#define TX3912_CLK_CTRL&t;&t;&t;&t;&t;0x01c0
multiline_comment|/*&n; * Clock control register values&n; */
DECL|macro|TX3912_CLK_CTRL_CHICLKDIV_MASK
mdefine_line|#define TX3912_CLK_CTRL_CHICLKDIV_MASK&t;&t;&t;0xff000000
DECL|macro|TX3912_CLK_CTRL_ENCLKTEST
mdefine_line|#define TX3912_CLK_CTRL_ENCLKTEST&t;&t;&t;0x00800000
DECL|macro|TX3912_CLK_CTRL_CLKTESTSELSIB
mdefine_line|#define TX3912_CLK_CTRL_CLKTESTSELSIB&t;&t;&t;0x00400000
DECL|macro|TX3912_CLK_CTRL_CHIMCLKSEL
mdefine_line|#define TX3912_CLK_CTRL_CHIMCLKSEL&t;&t;&t;0x00200000
DECL|macro|TX3912_CLK_CTRL_CHICLKDIR
mdefine_line|#define TX3912_CLK_CTRL_CHICLKDIR&t;&t;&t;0x00100000
DECL|macro|TX3912_CLK_CTRL_ENCHIMCLK
mdefine_line|#define TX3912_CLK_CTRL_ENCHIMCLK&t;&t;&t;0x00080000
DECL|macro|TX3912_CLK_CTRL_ENVIDCLK
mdefine_line|#define TX3912_CLK_CTRL_ENVIDCLK&t;&t;&t;0x00040000
DECL|macro|TX3912_CLK_CTRL_ENMBUSCLK
mdefine_line|#define TX3912_CLK_CTRL_ENMBUSCLK&t;&t;&t;0x00020000
DECL|macro|TX3912_CLK_CTRL_ENSPICLK
mdefine_line|#define TX3912_CLK_CTRL_ENSPICLK&t;&t;&t;0x00010000
DECL|macro|TX3912_CLK_CTRL_ENTIMERCLK
mdefine_line|#define TX3912_CLK_CTRL_ENTIMERCLK&t;&t;&t;0x00008000
DECL|macro|TX3912_CLK_CTRL_ENFASTTIMERCLK
mdefine_line|#define TX3912_CLK_CTRL_ENFASTTIMERCLK&t;&t;&t;0x00004000
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIR
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIR&t;&t;&t;0x00002000
DECL|macro|TX3912_CLK_CTRL_reserved1
mdefine_line|#define TX3912_CLK_CTRL_reserved1&t;&t;&t;0x00001000
DECL|macro|TX3912_CLK_CTRL_ENSIBMCLK
mdefine_line|#define TX3912_CLK_CTRL_ENSIBMCLK&t;&t;&t;0x00000800
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_6
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_6&t;&t;&t;0x00000600
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_5
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_5&t;&t;&t;0x00000500
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_4
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_4&t;&t;&t;0x00000400
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_3
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_3&t;&t;&t;0x00000300
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_2
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_2&t;&t;&t;0x00000200
DECL|macro|TX3912_CLK_CTRL_SIBMCLKDIV_1
mdefine_line|#define TX3912_CLK_CTRL_SIBMCLKDIV_1&t;&t;&t;0x00000100
DECL|macro|TX3912_CLK_CTRL_CSERSEL
mdefine_line|#define TX3912_CLK_CTRL_CSERSEL&t;&t;&t;&t;0x00000080
DECL|macro|TX3912_CLK_CTRL_CSERDIV_6
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_6&t;&t;&t;0x00000060
DECL|macro|TX3912_CLK_CTRL_CSERDIV_5
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_5&t;&t;&t;0x00000050
DECL|macro|TX3912_CLK_CTRL_CSERDIV_4
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_4&t;&t;&t;0x00000040
DECL|macro|TX3912_CLK_CTRL_CSERDIV_3
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_3&t;&t;&t;0x00000030
DECL|macro|TX3912_CLK_CTRL_CSERDIV_2
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_2&t;&t;&t;0x00000020
DECL|macro|TX3912_CLK_CTRL_CSERDIV_1
mdefine_line|#define TX3912_CLK_CTRL_CSERDIV_1&t;&t;&t;0x00000010
DECL|macro|TX3912_CLK_CTRL_ENCSERCLK
mdefine_line|#define TX3912_CLK_CTRL_ENCSERCLK&t;&t;&t;0x00000008
DECL|macro|TX3912_CLK_CTRL_ENIRCLK
mdefine_line|#define TX3912_CLK_CTRL_ENIRCLK&t;&t;&t;&t;0x00000004
DECL|macro|TX3912_CLK_CTRL_ENUARTACLK
mdefine_line|#define TX3912_CLK_CTRL_ENUARTACLK&t;&t;&t;0x00000002
DECL|macro|TX3912_CLK_CTRL_ENUARTBCLK
mdefine_line|#define TX3912_CLK_CTRL_ENUARTBCLK&t;&t;&t;0x00000001
multiline_comment|/*****************************************************************************&n; *&t;Interrupt Subsystem                                                  *&n; *&t;-------------------                                                  *&n; *&t;Chapter 8 in Philips PR31700 and Toshiba TMPR3905/12 User Manuals    *&n; *****************************************************************************/
DECL|macro|TX3912_INT1_CLEAR
mdefine_line|#define TX3912_INT1_CLEAR&t;&t;&t;&t;0x0100
DECL|macro|TX3912_INT2_CLEAR
mdefine_line|#define TX3912_INT2_CLEAR&t;&t;&t;&t;0x0104
DECL|macro|TX3912_INT3_CLEAR
mdefine_line|#define TX3912_INT3_CLEAR&t;&t;&t;&t;0x0108
DECL|macro|TX3912_INT4_CLEAR
mdefine_line|#define TX3912_INT4_CLEAR&t;&t;&t;&t;0x010c
DECL|macro|TX3912_INT5_CLEAR
mdefine_line|#define TX3912_INT5_CLEAR&t;&t;&t;&t;0x0110
DECL|macro|TX3912_INT1_ENABLE
mdefine_line|#define TX3912_INT1_ENABLE&t;&t;&t;&t;0x0118
DECL|macro|TX3912_INT2_ENABLE
mdefine_line|#define TX3912_INT2_ENABLE&t;&t;&t;&t;0x011c
DECL|macro|TX3912_INT3_ENABLE
mdefine_line|#define TX3912_INT3_ENABLE&t;&t;&t;&t;0x0120
DECL|macro|TX3912_INT4_ENABLE
mdefine_line|#define TX3912_INT4_ENABLE&t;&t;&t;&t;0x0124
DECL|macro|TX3912_INT5_ENABLE
mdefine_line|#define TX3912_INT5_ENABLE&t;&t;&t;&t;0x0128
DECL|macro|TX3912_INT6_ENABLE
mdefine_line|#define TX3912_INT6_ENABLE&t;&t;&t;&t;0x012c
DECL|macro|TX3912_INT1_STATUS
mdefine_line|#define TX3912_INT1_STATUS&t;&t;&t;&t;0x0100
DECL|macro|TX3912_INT2_STATUS
mdefine_line|#define TX3912_INT2_STATUS&t;&t;&t;&t;0x0104
DECL|macro|TX3912_INT3_STATUS
mdefine_line|#define TX3912_INT3_STATUS&t;&t;&t;&t;0x0108
DECL|macro|TX3912_INT4_STATUS
mdefine_line|#define TX3912_INT4_STATUS&t;&t;&t;&t;0x010c
DECL|macro|TX3912_INT5_STATUS
mdefine_line|#define TX3912_INT5_STATUS&t;&t;&t;&t;0x0110
DECL|macro|TX3912_INT6_STATUS
mdefine_line|#define TX3912_INT6_STATUS&t;&t;&t;&t;0x0114
multiline_comment|/*&n; * Interrupt 2 register values&n; */
DECL|macro|TX3912_INT2_UARTARXINT
mdefine_line|#define TX3912_INT2_UARTARXINT&t;&t;&t;&t;0x80000000
DECL|macro|TX3912_INT2_UARTARXOVERRUNINT
mdefine_line|#define TX3912_INT2_UARTARXOVERRUNINT&t;&t;&t;0x40000000
DECL|macro|TX3912_INT2_UARTAFRAMEERRINT
mdefine_line|#define TX3912_INT2_UARTAFRAMEERRINT&t;&t;&t;0x20000000
DECL|macro|TX3912_INT2_UARTABREAKINT
mdefine_line|#define TX3912_INT2_UARTABREAKINT&t;&t;&t;0x10000000
DECL|macro|TX3912_INT2_UARTAPARITYINT
mdefine_line|#define TX3912_INT2_UARTAPARITYINT&t;&t;&t;0x08000000
DECL|macro|TX3912_INT2_UARTATXINT
mdefine_line|#define TX3912_INT2_UARTATXINT&t;&t;&t;&t;0x04000000
DECL|macro|TX3912_INT2_UARTATXOVERRUNINT
mdefine_line|#define TX3912_INT2_UARTATXOVERRUNINT&t;&t;&t;0x02000000
DECL|macro|TX3912_INT2_UARTAEMPTYINT
mdefine_line|#define TX3912_INT2_UARTAEMPTYINT&t;&t;&t;0x01000000
DECL|macro|TX3912_INT2_UARTADMAFULLINT
mdefine_line|#define TX3912_INT2_UARTADMAFULLINT&t;&t;&t;0x00800000
DECL|macro|TX3912_INT2_UARTADMAHALFINT
mdefine_line|#define TX3912_INT2_UARTADMAHALFINT&t;&t;&t;0x00400000
DECL|macro|TX3912_INT2_UARTBRXINT
mdefine_line|#define TX3912_INT2_UARTBRXINT&t;&t;&t;&t;0x00200000
DECL|macro|TX3912_INT2_UARTBRXOVERRUNINT
mdefine_line|#define TX3912_INT2_UARTBRXOVERRUNINT&t;&t;&t;0x00100000
DECL|macro|TX3912_INT2_UARTBFRAMEERRINT
mdefine_line|#define TX3912_INT2_UARTBFRAMEERRINT&t;&t;&t;0x00080000
DECL|macro|TX3912_INT2_UARTBBREAKINT
mdefine_line|#define TX3912_INT2_UARTBBREAKINT&t;&t;&t;0x00040000
DECL|macro|TX3912_INT2_UARTBPARITYINT
mdefine_line|#define TX3912_INT2_UARTBPARITYINT&t;&t;&t;0x00020000
DECL|macro|TX3912_INT2_UARTBTXINT
mdefine_line|#define TX3912_INT2_UARTBTXINT&t;&t;&t;&t;0x00010000
DECL|macro|TX3912_INT2_UARTBTXOVERRUNINT
mdefine_line|#define TX3912_INT2_UARTBTXOVERRUNINT&t;&t;&t;0x00008000
DECL|macro|TX3912_INT2_UARTBEMPTYINT
mdefine_line|#define TX3912_INT2_UARTBEMPTYINT&t;&t;&t;0x00004000
DECL|macro|TX3912_INT2_UARTBDMAFULLINT
mdefine_line|#define TX3912_INT2_UARTBDMAFULLINT&t;&t;&t;0x00002000
DECL|macro|TX3912_INT2_UARTBDMAHALFINT
mdefine_line|#define TX3912_INT2_UARTBDMAHALFINT&t;&t;&t;0x00001000
DECL|macro|TX3912_INT2_UARTA_RX_BITS
mdefine_line|#define TX3912_INT2_UARTA_RX_BITS&t;&t;&t;0xf8000000
DECL|macro|TX3912_INT2_UARTA_TX_BITS
mdefine_line|#define TX3912_INT2_UARTA_TX_BITS&t;&t;&t;0x07c00000
DECL|macro|TX3912_INT2_UARTB_RX_BITS
mdefine_line|#define TX3912_INT2_UARTB_RX_BITS&t;&t;&t;0x003e0000
DECL|macro|TX3912_INT2_UARTB_TX_BITS
mdefine_line|#define TX3912_INT2_UARTB_TX_BITS&t;&t;&t;0x0001f000
multiline_comment|/*&n; * Interrupt 5 register values&n; */
DECL|macro|TX3912_INT5_RTCINT
mdefine_line|#define TX3912_INT5_RTCINT&t;&t;&t;&t;0x80000000
DECL|macro|TX3912_INT5_ALARMINT
mdefine_line|#define TX3912_INT5_ALARMINT&t;&t;&t;&t;0x40000000
DECL|macro|TX3912_INT5_PERINT
mdefine_line|#define TX3912_INT5_PERINT&t;&t;&t;&t;0x20000000
DECL|macro|TX3912_INT5_STPTIMERINT
mdefine_line|#define TX3912_INT5_STPTIMERINT&t;&t;&t;&t;0x10000000
DECL|macro|TX3912_INT5_POSPWRINT
mdefine_line|#define TX3912_INT5_POSPWRINT&t;&t;&t;&t;0x08000000
DECL|macro|TX3912_INT5_NEGPWRINT
mdefine_line|#define TX3912_INT5_NEGPWRINT&t;&t;&t;&t;0x04000000
DECL|macro|TX3912_INT5_POSPWROKINT
mdefine_line|#define TX3912_INT5_POSPWROKINT&t;&t;&t;&t;0x02000000
DECL|macro|TX3912_INT5_NEGPWROKINT
mdefine_line|#define TX3912_INT5_NEGPWROKINT&t;&t;&t;&t;0x01000000
DECL|macro|TX3912_INT5_POSONBUTINT
mdefine_line|#define TX3912_INT5_POSONBUTINT&t;&t;&t;&t;0x00800000
DECL|macro|TX3912_INT5_NEGONBUTINT
mdefine_line|#define TX3912_INT5_NEGONBUTINT&t;&t;&t;&t;0x00400000
DECL|macro|TX3912_INT5_SPIBUFAVAILINT
mdefine_line|#define TX3912_INT5_SPIBUFAVAILINT&t;&t;&t;0x00200000
DECL|macro|TX3912_INT5_SPIERRINT
mdefine_line|#define TX3912_INT5_SPIERRINT&t;&t;&t;&t;0x00100000
DECL|macro|TX3912_INT5_SPIRCVINT
mdefine_line|#define TX3912_INT5_SPIRCVINT&t;&t;&t;&t;0x00080000
DECL|macro|TX3912_INT5_SPIEMPTYINT
mdefine_line|#define TX3912_INT5_SPIEMPTYINT&t;&t;&t;&t;0x00040000
DECL|macro|TX3912_INT5_IRCONSMINT
mdefine_line|#define TX3912_INT5_IRCONSMINT&t;&t;&t;&t;0x00020000
DECL|macro|TX3912_INT5_CARSTINT
mdefine_line|#define TX3912_INT5_CARSTINT&t;&t;&t;&t;0x00010000
DECL|macro|TX3912_INT5_POSCARINT
mdefine_line|#define TX3912_INT5_POSCARINT&t;&t;&t;&t;0x00008000
DECL|macro|TX3912_INT5_NEGCARINT
mdefine_line|#define TX3912_INT5_NEGCARINT&t;&t;&t;&t;0x00004000
DECL|macro|TX3912_INT5_IOPOSINT6
mdefine_line|#define TX3912_INT5_IOPOSINT6&t;&t;&t;&t;0x00002000
DECL|macro|TX3912_INT5_IOPOSINT5
mdefine_line|#define TX3912_INT5_IOPOSINT5&t;&t;&t;&t;0x00001000
DECL|macro|TX3912_INT5_IOPOSINT4
mdefine_line|#define TX3912_INT5_IOPOSINT4&t;&t;&t;&t;0x00000800
DECL|macro|TX3912_INT5_IOPOSINT3
mdefine_line|#define TX3912_INT5_IOPOSINT3&t;&t;&t;&t;0x00000400
DECL|macro|TX3912_INT5_IOPOSINT2
mdefine_line|#define TX3912_INT5_IOPOSINT2&t;&t;&t;&t;0x00000200
DECL|macro|TX3912_INT5_IOPOSINT1
mdefine_line|#define TX3912_INT5_IOPOSINT1&t;&t;&t;&t;0x00000100
DECL|macro|TX3912_INT5_IOPOSINT0
mdefine_line|#define TX3912_INT5_IOPOSINT0&t;&t;&t;&t;0x00000080
DECL|macro|TX3912_INT5_IONEGINT6
mdefine_line|#define TX3912_INT5_IONEGINT6&t;&t;&t;&t;0x00000040
DECL|macro|TX3912_INT5_IONEGINT5
mdefine_line|#define TX3912_INT5_IONEGINT5&t;&t;&t;&t;0x00000020
DECL|macro|TX3912_INT5_IONEGINT4
mdefine_line|#define TX3912_INT5_IONEGINT4&t;&t;&t;&t;0x00000010
DECL|macro|TX3912_INT5_IONEGINT3
mdefine_line|#define TX3912_INT5_IONEGINT3&t;&t;&t;&t;0x00000008
DECL|macro|TX3912_INT5_IONEGINT2
mdefine_line|#define TX3912_INT5_IONEGINT2&t;&t;&t;&t;0x00000004
DECL|macro|TX3912_INT5_IONEGINT1
mdefine_line|#define TX3912_INT5_IONEGINT1&t;&t;&t;&t;0x00000002
DECL|macro|TX3912_INT5_IONEGINT0
mdefine_line|#define TX3912_INT5_IONEGINT0&t;&t;&t;&t;0x00000001
multiline_comment|/*&n; * Interrupt 6 status register values&n; */
DECL|macro|TX3912_INT6_STATUS_IRQHIGH
mdefine_line|#define TX3912_INT6_STATUS_IRQHIGH&t;&t;&t;0x80000000
DECL|macro|TX3912_INT6_STATUS_IRQLOW
mdefine_line|#define TX3912_INT6_STATUS_IRQLOW&t;&t;&t;0x40000000
DECL|macro|TX3912_INT6_STATUS_reserved6
mdefine_line|#define TX3912_INT6_STATUS_reserved6&t;&t;&t;0x3fffffc0
DECL|macro|TX3912_INT6_STATUS_INTVEC_POSNEGPWROKINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_POSNEGPWROKINT&t;0x0000003c
DECL|macro|TX3912_INT6_STATUS_INTVEC_ALARMINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_ALARMINT&t;&t;0x00000038
DECL|macro|TX3912_INT6_STATUS_INTVEC_PERINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_PERINT&t;&t;0x00000034
DECL|macro|TX3912_INT6_STATUS_INTVEC_reserved5
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_reserved5&t;&t;0x00000030
DECL|macro|TX3912_INT6_STATUS_INTVEC_UARTARXINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_UARTARXINT&t;&t;0x0000002c
DECL|macro|TX3912_INT6_STATUS_INTVEC_UARTBRXINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_UARTBRXINT&t;&t;0x00000028
DECL|macro|TX3912_INT6_STATUS_INTVEC_reserved4
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_reserved4&t;&t;0x00000024
DECL|macro|TX3912_INT6_STATUS_INTVEC_IOPOSINT65
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_IOPOSINT65&t;&t;0x00000020
DECL|macro|TX3912_INT6_STATUS_INTVEC_reserved3
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_reserved3&t;&t;0x0000001c
DECL|macro|TX3912_INT6_STATUS_INTVEC_IONEGINT65
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_IONEGINT65&t;&t;0x00000018
DECL|macro|TX3912_INT6_STATUS_INTVEC_reserved2
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_reserved2&t;&t;0x00000014
DECL|macro|TX3912_INT6_STATUS_INTVEC_SNDDMACNTINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_SNDDMACNTINT&t;&t;0x00000010
DECL|macro|TX3912_INT6_STATUS_INTVEC_TELDMACNTINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_TELDMACNTINT&t;&t;0x0000000c
DECL|macro|TX3912_INT6_STATUS_INTVEC_CHIDMACNTINT
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_CHIDMACNTINT&t;&t;0x00000008
DECL|macro|TX3912_INT6_STATUS_INTVEC_IOPOSNEGINT0
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_IOPOSNEGINT0&t;&t;0x00000004
DECL|macro|TX3912_INT6_STATUS_INTVEC_STDHANDLER
mdefine_line|#define TX3912_INT6_STATUS_INTVEC_STDHANDLER&t;&t;0x00000000
DECL|macro|TX3912_INT6_STATUS_reserved1
mdefine_line|#define TX3912_INT6_STATUS_reserved1&t;&t;&t;0x00000003
multiline_comment|/*&n; * Interrupt 6 enable register values&n; */
DECL|macro|TX3912_INT6_ENABLE_reserved5
mdefine_line|#define TX3912_INT6_ENABLE_reserved5&t;&t;&t;0xfff80000
DECL|macro|TX3912_INT6_ENABLE_GLOBALEN
mdefine_line|#define TX3912_INT6_ENABLE_GLOBALEN&t;&t;&t;0x00040000
DECL|macro|TX3912_INT6_ENABLE_IRQPRITEST
mdefine_line|#define TX3912_INT6_ENABLE_IRQPRITEST&t;&t;&t;0x00020000
DECL|macro|TX3912_INT6_ENABLE_IRQTEST
mdefine_line|#define TX3912_INT6_ENABLE_IRQTEST&t;&t;&t;0x00010000
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_POSNEGPWROKINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_POSNEGPWROKINT&t;0x00008000
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_ALARMINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_ALARMINT&t;0x00004000
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_PERINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_PERINT&t;&t;0x00002000
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_reserved4
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_reserved4&t;0x00001000
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_UARTARXINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_UARTARXINT&t;0x00000800
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_UARTBRXINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_UARTBRXINT&t;0x00000400
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_reserved3
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_reserved3&t;0x00000200
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_IOPOSINT65
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_IOPOSINT65&t;0x00000100
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_reserved2
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_reserved2&t;0x00000080
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_IONEGINT65
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_IONEGINT65&t;0x00000040
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_reserved1
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_reserved1&t;0x00000020
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_SNDDMACNTINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_SNDDMACNTINT&t;0x00000010
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_TELDMACNTINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_TELDMACNTINT&t;0x00000008
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_CHIDMACNTINT
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_CHIDMACNTINT&t;0x00000004
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_IOPOSNEGINT0
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_IOPOSNEGINT0&t;0x00000002
DECL|macro|TX3912_INT6_ENABLE_PRIORITYMASK_STDHANDLER
mdefine_line|#define TX3912_INT6_ENABLE_PRIORITYMASK_STDHANDLER&t;0x00000001
DECL|macro|TX3912_INT6_ENABLE_HIGH_PRIORITY
mdefine_line|#define TX3912_INT6_ENABLE_HIGH_PRIORITY&t;&t;0x0000ffff
multiline_comment|/*****************************************************************************&n; *&t;Power Subsystem                                                      *&n; *&t;---------------                                                      *&n; *&t;Chapter 11 in Philips PR31700 User Manual                            *&n; *&t;Chapter 12 in Toshiba TMPR3905/12 User Manual                        *&n; *****************************************************************************/
DECL|macro|TX3912_POWER_CTRL
mdefine_line|#define TX3912_POWER_CTRL&t;&t;&t;&t;0x01c4
multiline_comment|/*&n; * Power control register values&n; */
DECL|macro|TX3912_POWER_CTRL_ONBUTN
mdefine_line|#define TX3912_POWER_CTRL_ONBUTN&t;&t;&t;0x80000000
DECL|macro|TX3912_POWER_CTRL_PWRINT
mdefine_line|#define TX3912_POWER_CTRL_PWRINT&t;&t;&t;0x40000000
DECL|macro|TX3912_POWER_CTRL_PWROK
mdefine_line|#define TX3912_POWER_CTRL_PWROK&t;&t;&t;&t;0x20000000
DECL|macro|TX3912_POWER_CTRL_VIDRF_MASK
mdefine_line|#define TX3912_POWER_CTRL_VIDRF_MASK&t;&t;&t;0x18000000
DECL|macro|TX3912_POWER_CTRL_SLOWBUS
mdefine_line|#define TX3912_POWER_CTRL_SLOWBUS&t;&t;&t;0x04000000
DECL|macro|TX3912_POWER_CTRL_DIVMOD
mdefine_line|#define TX3912_POWER_CTRL_DIVMOD&t;&t;&t;0x02000000
DECL|macro|TX3912_POWER_CTRL_reserved2
mdefine_line|#define TX3912_POWER_CTRL_reserved2&t;&t;&t;0x01ff0000
DECL|macro|TX3912_POWER_CTRL_STPTIMERVAL_MASK
mdefine_line|#define TX3912_POWER_CTRL_STPTIMERVAL_MASK&t;&t;0x0000f000
DECL|macro|TX3912_POWER_CTRL_ENSTPTIMER
mdefine_line|#define TX3912_POWER_CTRL_ENSTPTIMER&t;&t;&t;0x00000800
DECL|macro|TX3912_POWER_CTRL_ENFORCESHUTDWN
mdefine_line|#define TX3912_POWER_CTRL_ENFORCESHUTDWN&t;&t;0x00000400
DECL|macro|TX3912_POWER_CTRL_FORCESHUTDWN
mdefine_line|#define TX3912_POWER_CTRL_FORCESHUTDWN&t;&t;&t;0x00000200
DECL|macro|TX3912_POWER_CTRL_FORCESHUTDWNOCC
mdefine_line|#define TX3912_POWER_CTRL_FORCESHUTDWNOCC&t;&t;0x00000100
DECL|macro|TX3912_POWER_CTRL_SELC2MS
mdefine_line|#define TX3912_POWER_CTRL_SELC2MS&t;&t;&t;0x00000080
DECL|macro|TX3912_POWER_CTRL_reserved1
mdefine_line|#define TX3912_POWER_CTRL_reserved1&t;&t;&t;0x00000040
DECL|macro|TX3912_POWER_CTRL_BPDBVCC3
mdefine_line|#define TX3912_POWER_CTRL_BPDBVCC3&t;&t;&t;0x00000020
DECL|macro|TX3912_POWER_CTRL_STOPCPU
mdefine_line|#define TX3912_POWER_CTRL_STOPCPU&t;&t;&t;0x00000010
DECL|macro|TX3912_POWER_CTRL_DBNCONBUTN
mdefine_line|#define TX3912_POWER_CTRL_DBNCONBUTN&t;&t;&t;0x00000008
DECL|macro|TX3912_POWER_CTRL_COLDSTART
mdefine_line|#define TX3912_POWER_CTRL_COLDSTART&t;&t;&t;0x00000004
DECL|macro|TX3912_POWER_CTRL_PWRCS
mdefine_line|#define TX3912_POWER_CTRL_PWRCS&t;&t;&t;&t;0x00000002
DECL|macro|TX3912_POWER_CTRL_VCCON
mdefine_line|#define TX3912_POWER_CTRL_VCCON&t;&t;&t;&t;0x00000001
multiline_comment|/*****************************************************************************&n; *&t;Timer Subsystem                                                      *&n; *&t;---------------                                                      *&n; *&t;Chapter 14 in Philips PR31700 User Manual                            *&n; *&t;Chapter 15 in Toshiba TMPR3905/12 User Manual                        *&n; *****************************************************************************/
DECL|macro|TX3912_RTC_HIGH
mdefine_line|#define TX3912_RTC_HIGH&t;&t;&t;&t;&t;0x0140
DECL|macro|TX3912_RTC_LOW
mdefine_line|#define TX3912_RTC_LOW&t;&t;&t;&t;&t;0x0144
DECL|macro|TX3912_RTC_ALARM_HIGH
mdefine_line|#define TX3912_RTC_ALARM_HIGH&t;&t;&t;&t;0x0148
DECL|macro|TX3912_RTC_ALARM_LOW
mdefine_line|#define TX3912_RTC_ALARM_LOW&t;&t;&t;&t;0x014c
DECL|macro|TX3912_TIMER_CTRL
mdefine_line|#define TX3912_TIMER_CTRL&t;&t;&t;&t;0x0150
DECL|macro|TX3912_TIMER_PERIOD
mdefine_line|#define TX3912_TIMER_PERIOD&t;&t;&t;&t;0x0154
multiline_comment|/*&n; * Timer control register values&n; */
DECL|macro|TX3912_TIMER_CTRL_FREEZEPRE
mdefine_line|#define TX3912_TIMER_CTRL_FREEZEPRE&t;&t;&t;0x00000080
DECL|macro|TX3912_TIMER_CTRL_FREEZERTC
mdefine_line|#define TX3912_TIMER_CTRL_FREEZERTC&t;&t;&t;0x00000040
DECL|macro|TX3912_TIMER_CTRL_FREEZETIMER
mdefine_line|#define TX3912_TIMER_CTRL_FREEZETIMER&t;&t;&t;0x00000020
DECL|macro|TX3912_TIMER_CTRL_ENPERTIMER
mdefine_line|#define TX3912_TIMER_CTRL_ENPERTIMER&t;&t;&t;0x00000010
DECL|macro|TX3912_TIMER_CTRL_RTCCLEAR
mdefine_line|#define TX3912_TIMER_CTRL_RTCCLEAR&t;&t;&t;0x00000008
DECL|macro|TX3912_TIMER_CTRL_TESTC8MS
mdefine_line|#define TX3912_TIMER_CTRL_TESTC8MS&t;&t;&t;0x00000004
DECL|macro|TX3912_TIMER_CTRL_ENTESTCLK
mdefine_line|#define TX3912_TIMER_CTRL_ENTESTCLK&t;&t;&t;0x00000002
DECL|macro|TX3912_TIMER_CTRL_ENRTCTST
mdefine_line|#define TX3912_TIMER_CTRL_ENRTCTST&t;&t;&t;0x00000001
multiline_comment|/*&n; * The periodic timer has granularity of 868 nanoseconds which&n; * results in a count of (1.152 x 10^6 / 100) in order to achieve&n; * a 10 millisecond periodic system clock.&n; */
DECL|macro|TX3912_SYS_TIMER_VALUE
mdefine_line|#define TX3912_SYS_TIMER_VALUE&t;&t;&t;&t;(1152000/HZ)
multiline_comment|/*****************************************************************************&n; *&t;UART Subsystem                                                       *&n; *&t;--------------                                                       *&n; *&t;Chapter 15 in Philips PR31700 User Manual                            *&n; *&t;Chapter 16 in Toshiba TMPR3905/12 User Manual                        *&n; *****************************************************************************/
DECL|macro|TX3912_UARTA_CTRL1
mdefine_line|#define TX3912_UARTA_CTRL1&t;&t;&t;&t;0x00b0
DECL|macro|TX3912_UARTA_CTRL2
mdefine_line|#define TX3912_UARTA_CTRL2&t;&t;&t;&t;0x00b4
DECL|macro|TX3912_UARTA_DMA_CTRL1
mdefine_line|#define TX3912_UARTA_DMA_CTRL1&t;&t;&t;&t;0x00b8
DECL|macro|TX3912_UARTA_DMA_CTRL2
mdefine_line|#define TX3912_UARTA_DMA_CTRL2&t;&t;&t;&t;0x00bc
DECL|macro|TX3912_UARTA_DMA_CNT
mdefine_line|#define TX3912_UARTA_DMA_CNT&t;&t;&t;&t;0x00c0
DECL|macro|TX3912_UARTA_DATA
mdefine_line|#define TX3912_UARTA_DATA&t;&t;&t;&t;0x00c4
DECL|macro|TX3912_UARTB_CTRL1
mdefine_line|#define TX3912_UARTB_CTRL1&t;&t;&t;&t;0x00c8
DECL|macro|TX3912_UARTB_CTRL2
mdefine_line|#define TX3912_UARTB_CTRL2&t;&t;&t;&t;0x00cc
DECL|macro|TX3912_UARTB_DMA_CTRL1
mdefine_line|#define TX3912_UARTB_DMA_CTRL1&t;&t;&t;&t;0x00d0
DECL|macro|TX3912_UARTB_DMA_CTRL2
mdefine_line|#define TX3912_UARTB_DMA_CTRL2&t;&t;&t;&t;0x00d4
DECL|macro|TX3912_UARTB_DMA_CNT
mdefine_line|#define TX3912_UARTB_DMA_CNT&t;&t;&t;&t;0x00d8
DECL|macro|TX3912_UARTB_DATA
mdefine_line|#define TX3912_UARTB_DATA&t;&t;&t;&t;0x00dc
multiline_comment|/*&n; * UART Control Register 1 values&n; */
DECL|macro|TX3912_UART_CTRL1_UARTON
mdefine_line|#define TX3912_UART_CTRL1_UARTON&t;&t;&t;0x80000000
DECL|macro|TX3912_UART_CTRL1_EMPTY
mdefine_line|#define TX3912_UART_CTRL1_EMPTY&t;&t;&t;&t;0x40000000
DECL|macro|TX3912_UART_CTRL1_PRXHOLDFULL
mdefine_line|#define TX3912_UART_CTRL1_PRXHOLDFULL&t;&t;&t;0x20000000
DECL|macro|TX3912_UART_CTRL1_RXHOLDFULL
mdefine_line|#define TX3912_UART_CTRL1_RXHOLDFULL&t;&t;&t;0x10000000
DECL|macro|TX3912_UART_CTRL1_reserved1
mdefine_line|#define TX3912_UART_CTRL1_reserved1&t;&t;&t;0x0fff0000
DECL|macro|TX3912_UART_CTRL1_ENDMARX
mdefine_line|#define TX3912_UART_CTRL1_ENDMARX&t;&t;&t;0x00008000
DECL|macro|TX3912_UART_CTRL1_ENDMATX
mdefine_line|#define TX3912_UART_CTRL1_ENDMATX&t;&t;&t;0x00004000
DECL|macro|TX3912_UART_CTRL1_TESTMODE
mdefine_line|#define TX3912_UART_CTRL1_TESTMODE&t;&t;&t;0x00002000
DECL|macro|TX3912_UART_CTRL1_ENBREAKHALT
mdefine_line|#define TX3912_UART_CTRL1_ENBREAKHALT&t;&t;&t;0x00001000
DECL|macro|TX3912_UART_CTRL1_ENDMATEST
mdefine_line|#define TX3912_UART_CTRL1_ENDMATEST&t;&t;&t;0x00000800
DECL|macro|TX3912_UART_CTRL1_ENDMALOOP
mdefine_line|#define TX3912_UART_CTRL1_ENDMALOOP&t;&t;&t;0x00000400
DECL|macro|TX3912_UART_CTRL1_PULSEOPT1
mdefine_line|#define TX3912_UART_CTRL1_PULSEOPT1&t;&t;&t;0x00000200
DECL|macro|TX3912_UART_CTRL1_PULSEOPT1
mdefine_line|#define TX3912_UART_CTRL1_PULSEOPT1&t;&t;&t;0x00000100
DECL|macro|TX3912_UART_CTRL1_DTINVERT
mdefine_line|#define TX3912_UART_CTRL1_DTINVERT&t;&t;&t;0x00000080
DECL|macro|TX3912_UART_CTRL1_DISTXD
mdefine_line|#define TX3912_UART_CTRL1_DISTXD&t;&t;&t;0x00000040
DECL|macro|TX3912_UART_CTRL1_TWOSTOP
mdefine_line|#define TX3912_UART_CTRL1_TWOSTOP&t;&t;&t;0x00000020
DECL|macro|TX3912_UART_CTRL1_LOOPBACK
mdefine_line|#define TX3912_UART_CTRL1_LOOPBACK&t;&t;&t;0x00000010
DECL|macro|TX3912_UART_CTRL1_BIT_7
mdefine_line|#define TX3912_UART_CTRL1_BIT_7&t;&t;&t;&t;0x00000008
DECL|macro|TX3912_UART_CTRL1_EVENPARITY
mdefine_line|#define TX3912_UART_CTRL1_EVENPARITY&t;&t;&t;0x00000004
DECL|macro|TX3912_UART_CTRL1_ENPARITY
mdefine_line|#define TX3912_UART_CTRL1_ENPARITY&t;&t;&t;0x00000002
DECL|macro|TX3912_UART_CTRL1_ENUART
mdefine_line|#define TX3912_UART_CTRL1_ENUART&t;&t;&t;0x00000001
multiline_comment|/*&n; * UART Control Register 2 values&n; */
DECL|macro|TX3912_UART_CTRL2_B230400
mdefine_line|#define TX3912_UART_CTRL2_B230400&t;&t;&t;0x0000&t;/*   0 */
DECL|macro|TX3912_UART_CTRL2_B115200
mdefine_line|#define TX3912_UART_CTRL2_B115200&t;&t;&t;0x0001&t;/*   1 */
DECL|macro|TX3912_UART_CTRL2_B76800
mdefine_line|#define TX3912_UART_CTRL2_B76800&t;&t;&t;0x0002&t;/*   2 */
DECL|macro|TX3912_UART_CTRL2_B57600
mdefine_line|#define TX3912_UART_CTRL2_B57600&t;&t;&t;0x0003&t;/*   3 */
DECL|macro|TX3912_UART_CTRL2_B38400
mdefine_line|#define TX3912_UART_CTRL2_B38400&t;&t;&t;0x0005&t;/*   5 */
DECL|macro|TX3912_UART_CTRL2_B19200
mdefine_line|#define TX3912_UART_CTRL2_B19200&t;&t;&t;0x000b&t;/*  11 */
DECL|macro|TX3912_UART_CTRL2_B9600
mdefine_line|#define TX3912_UART_CTRL2_B9600&t;&t;&t;&t;0x0016&t;/*  22 */
DECL|macro|TX3912_UART_CTRL2_B4800
mdefine_line|#define TX3912_UART_CTRL2_B4800&t;&t;&t;&t;0x002f&t;/*  47 */
DECL|macro|TX3912_UART_CTRL2_B2400
mdefine_line|#define TX3912_UART_CTRL2_B2400&t;&t;&t;&t;0x005f&t;/*  95 */
DECL|macro|TX3912_UART_CTRL2_B1200
mdefine_line|#define TX3912_UART_CTRL2_B1200&t;&t;&t;&t;0x00bf&t;/* 191 */
DECL|macro|TX3912_UART_CTRL2_B600
mdefine_line|#define TX3912_UART_CTRL2_B600&t;&t;&t;&t;0x017f&t;/* 383 */
DECL|macro|TX3912_UART_CTRL2_B300
mdefine_line|#define TX3912_UART_CTRL2_B300&t;&t;&t;&t;0x02ff&t;/* 767 */
multiline_comment|/*****************************************************************************&n; *&t;Video Subsystem                                                      *&n; *&t;---------------                                                      *&n; *&t;Chapter 16 in Philips PR31700 User Manual                            *&n; *&t;Chapter 17 in Toshiba TMPR3905/12 User Manual                        *&n; *****************************************************************************/
DECL|macro|TX3912_VIDEO_CTRL1
mdefine_line|#define TX3912_VIDEO_CTRL1&t;&t;&t;&t;0x0028
DECL|macro|TX3912_VIDEO_CTRL2
mdefine_line|#define TX3912_VIDEO_CTRL2&t;&t;&t;&t;0x002c
DECL|macro|TX3912_VIDEO_CTRL3
mdefine_line|#define TX3912_VIDEO_CTRL3&t;&t;&t;&t;0x0030
DECL|macro|TX3912_VIDEO_CTRL4
mdefine_line|#define TX3912_VIDEO_CTRL4&t;&t;&t;&t;0x0034
DECL|macro|TX3912_VIDEO_CTRL5
mdefine_line|#define TX3912_VIDEO_CTRL5&t;&t;&t;&t;0x0038
DECL|macro|TX3912_VIDEO_CTRL6
mdefine_line|#define TX3912_VIDEO_CTRL6&t;&t;&t;&t;0x003c
DECL|macro|TX3912_VIDEO_CTRL7
mdefine_line|#define TX3912_VIDEO_CTRL7&t;&t;&t;&t;0x0040
DECL|macro|TX3912_VIDEO_CTRL8
mdefine_line|#define TX3912_VIDEO_CTRL8&t;&t;&t;&t;0x0044
DECL|macro|TX3912_VIDEO_CTRL9
mdefine_line|#define TX3912_VIDEO_CTRL9&t;&t;&t;&t;0x0048
DECL|macro|TX3912_VIDEO_CTRL10
mdefine_line|#define TX3912_VIDEO_CTRL10&t;&t;&t;&t;0x004c
DECL|macro|TX3912_VIDEO_CTRL11
mdefine_line|#define TX3912_VIDEO_CTRL11&t;&t;&t;&t;0x0050
DECL|macro|TX3912_VIDEO_CTRL12
mdefine_line|#define TX3912_VIDEO_CTRL12&t;&t;&t;&t;0x0054
DECL|macro|TX3912_VIDEO_CTRL13
mdefine_line|#define TX3912_VIDEO_CTRL13&t;&t;&t;&t;0x0058
DECL|macro|TX3912_VIDEO_CTRL14
mdefine_line|#define TX3912_VIDEO_CTRL14&t;&t;&t;&t;0x005c
multiline_comment|/*&n; * Video Control Register 1 values&n; */
DECL|macro|TX3912_VIDEO_CTRL1_LINECNT
mdefine_line|#define TX3912_VIDEO_CTRL1_LINECNT&t;&t;&t;0xffc00000
DECL|macro|TX3912_VIDEO_CTRL1_LOADDLY
mdefine_line|#define TX3912_VIDEO_CTRL1_LOADDLY&t;&t;&t;0x00200000
DECL|macro|TX3912_VIDEO_CTRL1_BAUDVAL
mdefine_line|#define TX3912_VIDEO_CTRL1_BAUDVAL&t;&t;&t;0x001f0000
DECL|macro|TX3912_VIDEO_CTRL1_VIDDONEVAL
mdefine_line|#define TX3912_VIDEO_CTRL1_VIDDONEVAL&t;&t;&t;0x0000fe00
DECL|macro|TX3912_VIDEO_CTRL1_ENFREEZEFRAME
mdefine_line|#define TX3912_VIDEO_CTRL1_ENFREEZEFRAME&t;&t;0x00000100
DECL|macro|TX3912_VIDEO_CTRL1_BITSEL_MASK
mdefine_line|#define TX3912_VIDEO_CTRL1_BITSEL_MASK&t;&t;&t;0x000000c0
DECL|macro|TX3912_VIDEO_CTRL1_BITSEL_8BIT_COLOR
mdefine_line|#define TX3912_VIDEO_CTRL1_BITSEL_8BIT_COLOR&t;&t;0x000000c0
DECL|macro|TX3912_VIDEO_CTRL1_BITSEL_4BIT_GRAY
mdefine_line|#define TX3912_VIDEO_CTRL1_BITSEL_4BIT_GRAY&t;&t;0x00000080
DECL|macro|TX3912_VIDEO_CTRL1_BITSEL_2BIT_GRAY
mdefine_line|#define TX3912_VIDEO_CTRL1_BITSEL_2BIT_GRAY&t;&t;0x00000040
DECL|macro|TX3912_VIDEO_CTRL1_DISPSPLIT
mdefine_line|#define TX3912_VIDEO_CTRL1_DISPSPLIT&t;&t;&t;0x00000020
DECL|macro|TX3912_VIDEO_CTRL1_DISP8
mdefine_line|#define TX3912_VIDEO_CTRL1_DISP8&t;&t;&t;0x00000010
DECL|macro|TX3912_VIDEO_CTRL1_DFMODE
mdefine_line|#define TX3912_VIDEO_CTRL1_DFMODE&t;&t;&t;0x00000008
DECL|macro|TX3912_VIDEO_CTRL1_INVVID
mdefine_line|#define TX3912_VIDEO_CTRL1_INVVID&t;&t;&t;0x00000004
DECL|macro|TX3912_VIDEO_CTRL1_DISPON
mdefine_line|#define TX3912_VIDEO_CTRL1_DISPON&t;&t;&t;0x00000002
DECL|macro|TX3912_VIDEO_CTRL1_ENVID
mdefine_line|#define TX3912_VIDEO_CTRL1_ENVID&t;&t;&t;0x00000001
macro_line|#endif&t;/* _TX3912_H_ */
eof
