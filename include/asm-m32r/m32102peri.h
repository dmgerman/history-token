multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000,2001 by Hiroyuki Kondo&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|V
r_typedef
r_void
id|V
suffix:semicolon
DECL|typedef|B
r_typedef
r_char
id|B
suffix:semicolon
DECL|typedef|S
r_typedef
r_int
id|S
suffix:semicolon
DECL|typedef|W
r_typedef
r_int
id|W
suffix:semicolon
DECL|typedef|L
r_typedef
r_int
id|L
suffix:semicolon
DECL|typedef|F
r_typedef
r_float
id|F
suffix:semicolon
DECL|typedef|D
r_typedef
r_float
id|D
suffix:semicolon
DECL|typedef|UB
r_typedef
r_int
r_char
id|UB
suffix:semicolon
DECL|typedef|US
r_typedef
r_int
r_int
id|US
suffix:semicolon
DECL|typedef|UW
r_typedef
r_int
r_int
id|UW
suffix:semicolon
DECL|typedef|UL
r_typedef
r_int
r_int
id|UL
suffix:semicolon
DECL|typedef|CUW
r_typedef
r_const
r_int
r_int
id|CUW
suffix:semicolon
multiline_comment|/*********************************&n;&n;M32102 ICU&n;&n;*********************************/
DECL|macro|ICUISTS
mdefine_line|#define&t;&t;ICUISTS&t;&t;(UW *)0xa0EFF004
DECL|macro|ICUIREQ0
mdefine_line|#define&t;&t;ICUIREQ0&t;(UW *)0xa0EFF008
DECL|macro|ICUIREQ1
mdefine_line|#define&t;&t;ICUIREQ1&t;(UW *)0xa0EFF00C
DECL|macro|ICUSBICR
mdefine_line|#define&t;&t;ICUSBICR&t;(UW *)0xa0EFF018
DECL|macro|ICUIMASK
mdefine_line|#define&t;&t;ICUIMASK&t;(UW *)0xa0EFF01C
DECL|macro|ICUCR1
mdefine_line|#define&t;&t;ICUCR1&t;&t;(UW *)0xa0EFF200&t;/* INT0 */
DECL|macro|ICUCR2
mdefine_line|#define&t;&t;ICUCR2&t;&t;(UW *)0xa0EFF204&t;/* INT1 */
DECL|macro|ICUCR3
mdefine_line|#define&t;&t;ICUCR3&t;&t;(UW *)0xa0EFF208&t;/* INT2 */
DECL|macro|ICUCR4
mdefine_line|#define&t;&t;ICUCR4&t;&t;(UW *)0xa0EFF20C&t;/* INT3 */
DECL|macro|ICUCR5
mdefine_line|#define&t;&t;ICUCR5&t;&t;(UW *)0xa0EFF210&t;/* INT4 */
DECL|macro|ICUCR6
mdefine_line|#define&t;&t;ICUCR6&t;&t;(UW *)0xa0EFF214&t;/* INT5 */
DECL|macro|ICUCR7
mdefine_line|#define&t;&t;ICUCR7&t;&t;(UW *)0xa0EFF218&t;/* INT6 */
DECL|macro|ICUCR16
mdefine_line|#define&t;&t;ICUCR16&t;&t;(UW *)0xa0EFF23C&t;/* MFT0 */
DECL|macro|ICUCR17
mdefine_line|#define&t;&t;ICUCR17&t;&t;(UW *)0xa0EFF240&t;/* MFT1 */
DECL|macro|ICUCR18
mdefine_line|#define&t;&t;ICUCR18&t;&t;(UW *)0xa0EFF244&t;/* MFT2 */
DECL|macro|ICUCR19
mdefine_line|#define&t;&t;ICUCR19&t;&t;(UW *)0xa0EFF248&t;/* MFT3 */
DECL|macro|ICUCR20
mdefine_line|#define&t;&t;ICUCR20&t;&t;(UW *)0xa0EFF24C&t;/* MFT4 */
DECL|macro|ICUCR21
mdefine_line|#define&t;&t;ICUCR21&t;&t;(UW *)0xa0EFF250&t;/* MFT5 */
DECL|macro|ICUCR32
mdefine_line|#define&t;&t;ICUCR32&t;&t;(UW *)0xa0EFF27C&t;/* DMA0 */
DECL|macro|ICUCR33
mdefine_line|#define&t;&t;ICUCR33&t;&t;(UW *)0xa0EFF280&t;/* DMA1 */
DECL|macro|ICUCR48
mdefine_line|#define&t;&t;ICUCR48&t;&t;(UW *)0xa0EFF2BC&t;/* SIO0R */
DECL|macro|ICUCR49
mdefine_line|#define&t;&t;ICUCR49&t;&t;(UW *)0xa0EFF2C0&t;/* SIO0S */
DECL|macro|ICUCR50
mdefine_line|#define&t;&t;ICUCR50&t;&t;(UW *)0xa0EFF2C4&t;/* SIO1R */
DECL|macro|ICUCR51
mdefine_line|#define&t;&t;ICUCR51&t;&t;(UW *)0xa0EFF2C8&t;/* SIO1S */
DECL|macro|ICUCR52
mdefine_line|#define&t;&t;ICUCR52&t;&t;(UW *)0xa0EFF2CC&t;/* SIO2R */
DECL|macro|ICUCR53
mdefine_line|#define&t;&t;ICUCR53&t;&t;(UW *)0xa0EFF2D0&t;/* SIO2S */
DECL|macro|ICUCR54
mdefine_line|#define&t;&t;ICUCR54&t;&t;(UW *)0xa0EFF2D4&t;/* SIO3R */
DECL|macro|ICUCR55
mdefine_line|#define&t;&t;ICUCR55&t;&t;(UW *)0xa0EFF2D8&t;/* SIO3S */
DECL|macro|ICUCR56
mdefine_line|#define&t;&t;ICUCR56&t;&t;(UW *)0xa0EFF2DC&t;/* SIO4R */
DECL|macro|ICUCR57
mdefine_line|#define&t;&t;ICUCR57&t;&t;(UW *)0xa0EFF2E0&t;/* SIO4S */
multiline_comment|/*********************************&n;&n;M32102 MFT&n;&n;*********************************/
DECL|macro|MFTCR
mdefine_line|#define&t;&t;MFTCR&t;&t;(US *)0xa0EFC002
DECL|macro|MFTRPR
mdefine_line|#define&t;&t;MFTRPR&t;&t;(UB *)0xa0EFC006
DECL|macro|MFT0MOD
mdefine_line|#define&t;&t;MFT0MOD&t;&t;(US *)0xa0EFC102
DECL|macro|MFT0BOS
mdefine_line|#define&t;&t;MFT0BOS&t;&t;(US *)0xa0EFC106
DECL|macro|MFT0CUT
mdefine_line|#define&t;&t;MFT0CUT&t;&t;(US *)0xa0EFC10A
DECL|macro|MFT0RLD
mdefine_line|#define&t;&t;MFT0RLD&t;&t;(US *)0xa0EFC10E
DECL|macro|MFT0CRLD
mdefine_line|#define&t;&t;MFT0CRLD&t;(US *)0xa0EFC112
DECL|macro|MFT1MOD
mdefine_line|#define&t;&t;MFT1MOD&t;&t;(US *)0xa0EFC202
DECL|macro|MFT1BOS
mdefine_line|#define&t;&t;MFT1BOS&t;&t;(US *)0xa0EFC206
DECL|macro|MFT1CUT
mdefine_line|#define&t;&t;MFT1CUT&t;&t;(US *)0xa0EFC20A
DECL|macro|MFT1RLD
mdefine_line|#define&t;&t;MFT1RLD&t;&t;(US *)0xa0EFC20E
DECL|macro|MFT1CRLD
mdefine_line|#define&t;&t;MFT1CRLD&t;(US *)0xa0EFC212
DECL|macro|MFT2MOD
mdefine_line|#define&t;&t;MFT2MOD&t;&t;(US *)0xa0EFC302
DECL|macro|MFT2BOS
mdefine_line|#define&t;&t;MFT2BOS&t;&t;(US *)0xa0EFC306
DECL|macro|MFT2CUT
mdefine_line|#define&t;&t;MFT2CUT&t;&t;(US *)0xa0EFC30A
DECL|macro|MFT2RLD
mdefine_line|#define&t;&t;MFT2RLD&t;&t;(US *)0xa0EFC30E
DECL|macro|MFT2CRLD
mdefine_line|#define&t;&t;MFT2CRLD&t;(US *)0xa0EFC312
DECL|macro|MFT3MOD
mdefine_line|#define&t;&t;MFT3MOD&t;&t;(US *)0xa0EFC402
DECL|macro|MFT3CUT
mdefine_line|#define&t;&t;MFT3CUT&t;&t;(US *)0xa0EFC40A
DECL|macro|MFT3RLD
mdefine_line|#define&t;&t;MFT3RLD&t;&t;(US *)0xa0EFC40E
DECL|macro|MFT3CRLD
mdefine_line|#define&t;&t;MFT3CRLD&t;(US *)0xa0EFC412
DECL|macro|MFT4MOD
mdefine_line|#define&t;&t;MFT4MOD&t;&t;(US *)0xa0EFC502
DECL|macro|MFT4CUT
mdefine_line|#define&t;&t;MFT4CUT&t;&t;(US *)0xa0EFC50A
DECL|macro|MFT4RLD
mdefine_line|#define&t;&t;MFT4RLD&t;&t;(US *)0xa0EFC50E
DECL|macro|MFT4CRLD
mdefine_line|#define&t;&t;MFT4CRLD&t;(US *)0xa0EFC512
DECL|macro|MFT5MOD
mdefine_line|#define&t;&t;MFT5MOD&t;&t;(US *)0xa0EFC602
DECL|macro|MFT5CUT
mdefine_line|#define&t;&t;MFT5CUT&t;&t;(US *)0xa0EFC60A
DECL|macro|MFT5RLD
mdefine_line|#define&t;&t;MFT5RLD&t;&t;(US *)0xa0EFC60E
DECL|macro|MFT5CRLD
mdefine_line|#define&t;&t;MFT5CRLD&t;(US *)0xa0EFC612
multiline_comment|/*********************************&n;&n;M32102 SIO&n;&n;*********************************/
DECL|macro|SIO0CR
mdefine_line|#define SIO0CR     (volatile int *)0xa0efd000
DECL|macro|SIO0MOD0
mdefine_line|#define SIO0MOD0   (volatile int *)0xa0efd004
DECL|macro|SIO0MOD1
mdefine_line|#define SIO0MOD1   (volatile int *)0xa0efd008
DECL|macro|SIO0STS
mdefine_line|#define SIO0STS    (volatile int *)0xa0efd00c
DECL|macro|SIO0IMASK
mdefine_line|#define SIO0IMASK  (volatile int *)0xa0efd010
DECL|macro|SIO0BAUR
mdefine_line|#define SIO0BAUR   (volatile int *)0xa0efd014
DECL|macro|SIO0RBAUR
mdefine_line|#define SIO0RBAUR  (volatile int *)0xa0efd018
DECL|macro|SIO0TXB
mdefine_line|#define SIO0TXB    (volatile int *)0xa0efd01c
DECL|macro|SIO0RXB
mdefine_line|#define SIO0RXB    (volatile int *)0xa0efd020
DECL|macro|SIO1CR
mdefine_line|#define SIO1CR     (volatile int *)0xa0efd100
DECL|macro|SIO1MOD0
mdefine_line|#define SIO1MOD0   (volatile int *)0xa0efd104
DECL|macro|SIO1MOD1
mdefine_line|#define SIO1MOD1   (volatile int *)0xa0efd108
DECL|macro|SIO1STS
mdefine_line|#define SIO1STS    (volatile int *)0xa0efd10c
DECL|macro|SIO1IMASK
mdefine_line|#define SIO1IMASK  (volatile int *)0xa0efd110
DECL|macro|SIO1BAUR
mdefine_line|#define SIO1BAUR   (volatile int *)0xa0efd114
DECL|macro|SIO1RBAUR
mdefine_line|#define SIO1RBAUR  (volatile int *)0xa0efd118
DECL|macro|SIO1TXB
mdefine_line|#define SIO1TXB    (volatile int *)0xa0efd11c
DECL|macro|SIO1RXB
mdefine_line|#define SIO1RXB    (volatile int *)0xa0efd120
multiline_comment|/*********************************&n;&n;M32102 PORT&n;&n;*********************************/
DECL|macro|PIEN
mdefine_line|#define&t;&t;PIEN&t;&t;(UB *)0xa0EF1003&t;/* input enable */
DECL|macro|P0DATA
mdefine_line|#define&t;&t;P0DATA&t;&t;(UB *)0xa0EF1020&t;/* data */
DECL|macro|P1DATA
mdefine_line|#define&t;&t;P1DATA&t;&t;(UB *)0xa0EF1021
DECL|macro|P2DATA
mdefine_line|#define&t;&t;P2DATA&t;&t;(UB *)0xa0EF1022
DECL|macro|P3DATA
mdefine_line|#define&t;&t;P3DATA&t;&t;(UB *)0xa0EF1023
DECL|macro|P4DATA
mdefine_line|#define&t;&t;P4DATA&t;&t;(UB *)0xa0EF1024
DECL|macro|P5DATA
mdefine_line|#define&t;&t;P5DATA&t;&t;(UB *)0xa0EF1025
DECL|macro|P6DATA
mdefine_line|#define&t;&t;P6DATA&t;&t;(UB *)0xa0EF1026
DECL|macro|P7DATA
mdefine_line|#define&t;&t;P7DATA&t;&t;(UB *)0xa0EF1027
DECL|macro|P0DIR
mdefine_line|#define&t;&t;P0DIR&t;&t;(UB *)0xa0EF1040&t;/* direction */
DECL|macro|P1DIR
mdefine_line|#define&t;&t;P1DIR&t;&t;(UB *)0xa0EF1041
DECL|macro|P2DIR
mdefine_line|#define&t;&t;P2DIR&t;&t;(UB *)0xa0EF1042
DECL|macro|P3DIR
mdefine_line|#define&t;&t;P3DIR&t;&t;(UB *)0xa0EF1043
DECL|macro|P4DIR
mdefine_line|#define&t;&t;P4DIR&t;&t;(UB *)0xa0EF1044
DECL|macro|P5DIR
mdefine_line|#define&t;&t;P5DIR&t;&t;(UB *)0xa0EF1045
DECL|macro|P6DIR
mdefine_line|#define&t;&t;P6DIR&t;&t;(UB *)0xa0EF1046
DECL|macro|P7DIR
mdefine_line|#define&t;&t;P7DIR&t;&t;(UB *)0xa0EF1047
DECL|macro|P0MOD
mdefine_line|#define&t;&t;P0MOD&t;&t;(US *)0xa0EF1060&t;/* mode control */
DECL|macro|P1MOD
mdefine_line|#define&t;&t;P1MOD&t;&t;(US *)0xa0EF1062
DECL|macro|P2MOD
mdefine_line|#define&t;&t;P2MOD&t;&t;(US *)0xa0EF1064
DECL|macro|P3MOD
mdefine_line|#define&t;&t;P3MOD&t;&t;(US *)0xa0EF1066
DECL|macro|P4MOD
mdefine_line|#define&t;&t;P4MOD&t;&t;(US *)0xa0EF1068
DECL|macro|P5MOD
mdefine_line|#define&t;&t;P5MOD&t;&t;(US *)0xa0EF106A
DECL|macro|P6MOD
mdefine_line|#define&t;&t;P6MOD&t;&t;(US *)0xa0EF106C
DECL|macro|P7MOD
mdefine_line|#define&t;&t;P7MOD&t;&t;(US *)0xa0EF106E
DECL|macro|P0ODCR
mdefine_line|#define&t;&t;P0ODCR&t;&t;(UB *)0xa0EF1080&t;/* open-drain control */
DECL|macro|P1ODCR
mdefine_line|#define&t;&t;P1ODCR&t;&t;(UB *)0xa0EF1081
DECL|macro|P2ODCR
mdefine_line|#define&t;&t;P2ODCR&t;&t;(UB *)0xa0EF1082
DECL|macro|P3ODCR
mdefine_line|#define&t;&t;P3ODCR&t;&t;(UB *)0xa0EF1083
DECL|macro|P4ODCR
mdefine_line|#define&t;&t;P4ODCR&t;&t;(UB *)0xa0EF1084
DECL|macro|P5ODCR
mdefine_line|#define&t;&t;P5ODCR&t;&t;(UB *)0xa0EF1085
DECL|macro|P6ODCR
mdefine_line|#define&t;&t;P6ODCR&t;&t;(UB *)0xa0EF1086
DECL|macro|P7ODCR
mdefine_line|#define&t;&t;P7ODCR&t;&t;(UB *)0xa0EF1087
multiline_comment|/*********************************&n;&n;M32102 Cache&n;&n;********************************/
DECL|macro|MCCR
mdefine_line|#define&t;&t;MCCR&t;(US *)0xFFFFFFFE
macro_line|#else  /* __ASSEMBLY__ */
suffix:semicolon
suffix:semicolon
DECL|variable|x80ef1000
suffix:semicolon
suffix:semicolon
id|PIO
l_int|0x80ef1000
suffix:semicolon
suffix:semicolon
DECL|macro|PIEN
mdefine_line|#define PIEN          0xa0ef1000
DECL|macro|P0DATA
mdefine_line|#define P0DATA        0xa0ef1020
DECL|macro|P1DATA
mdefine_line|#define P1DATA        0xa0ef1021
DECL|macro|P2DATA
mdefine_line|#define P2DATA        0xa0ef1022
DECL|macro|P3DATA
mdefine_line|#define P3DATA        0xa0ef1023
DECL|macro|P4DATA
mdefine_line|#define P4DATA        0xa0ef1024
DECL|macro|P5DATA
mdefine_line|#define P5DATA        0xa0ef1025
DECL|macro|P6DATA
mdefine_line|#define P6DATA        0xa0ef1026
DECL|macro|P7DATA
mdefine_line|#define P7DATA        0xa0ef1027
DECL|macro|P0DIR
mdefine_line|#define P0DIR         0xa0ef1040
DECL|macro|P1DIR
mdefine_line|#define P1DIR         0xa0ef1041
DECL|macro|P2DIR
mdefine_line|#define P2DIR         0xa0ef1042
DECL|macro|P3DIR
mdefine_line|#define P3DIR         0xa0ef1043
DECL|macro|P4DIR
mdefine_line|#define P4DIR         0xa0ef1044
DECL|macro|P5DIR
mdefine_line|#define P5DIR         0xa0ef1045
DECL|macro|P6DIR
mdefine_line|#define P6DIR         0xa0ef1046
DECL|macro|P7DIR
mdefine_line|#define P7DIR         0xa0ef1047
DECL|macro|P0MOD
mdefine_line|#define P0MOD         0xa0ef1060
DECL|macro|P1MOD
mdefine_line|#define P1MOD         0xa0ef1062
DECL|macro|P2MOD
mdefine_line|#define P2MOD         0xa0ef1064
DECL|macro|P3MOD
mdefine_line|#define P3MOD         0xa0ef1066
DECL|macro|P4MOD
mdefine_line|#define P4MOD         0xa0ef1068
DECL|macro|P5MOD
mdefine_line|#define P5MOD         0xa0ef106a
DECL|macro|P6MOD
mdefine_line|#define P6MOD         0xa0ef106c
DECL|macro|P7MOD
mdefine_line|#define P7MOD         0xa0ef106e
suffix:semicolon
DECL|macro|P0ODCR
mdefine_line|#define P0ODCR        0xa0ef1080
DECL|macro|P1ODCR
mdefine_line|#define P1ODCR        0xa0ef1081
DECL|macro|P2ODCR
mdefine_line|#define P2ODCR        0xa0ef1082
DECL|macro|P3ODCR
mdefine_line|#define P3ODCR        0xa0ef1083
DECL|macro|P4ODCR
mdefine_line|#define P4ODCR        0xa0ef1084
DECL|macro|P5ODCR
mdefine_line|#define P5ODCR        0xa0ef1085
DECL|macro|P6ODCR
mdefine_line|#define P6ODCR        0xa0ef1086
DECL|macro|P7ODCR
mdefine_line|#define P7ODCR        0xa0ef1087
suffix:semicolon
suffix:semicolon
DECL|variable|xa0ef2000
suffix:semicolon
suffix:semicolon
id|WDT
l_int|0xa0ef2000
suffix:semicolon
suffix:semicolon
DECL|macro|WDTCR
mdefine_line|#define WDTCR         0xa0ef2000
suffix:semicolon
suffix:semicolon
DECL|variable|xa0ef4000
suffix:semicolon
suffix:semicolon
id|CLK
l_int|0xa0ef4000
suffix:semicolon
suffix:semicolon
DECL|macro|CPUCLKCR
mdefine_line|#define CPUCLKCR      0xa0ef4000
DECL|macro|CLKMOD
mdefine_line|#define CLKMOD        0xa0ef4004
DECL|macro|PLLCR
mdefine_line|#define PLLCR         0xa0ef4008
suffix:semicolon
suffix:semicolon
DECL|variable|xa0ef5000
suffix:semicolon
suffix:semicolon
id|BSEL
l_int|0xa0ef5000
suffix:semicolon
suffix:semicolon
DECL|macro|BSEL0CR
mdefine_line|#define BSEL0CR       0xa0ef5000
DECL|macro|BSEL1CR
mdefine_line|#define BSEL1CR       0xa0ef5004
DECL|macro|BSEL2CR
mdefine_line|#define BSEL2CR       0xa0ef5008
DECL|macro|BSEL3CR
mdefine_line|#define BSEL3CR       0xa0ef500c
DECL|macro|BSEL4CR
mdefine_line|#define BSEL4CR       0xa0ef5010
DECL|macro|BSEL5CR
mdefine_line|#define BSEL5CR       0xa0ef5014
suffix:semicolon
suffix:semicolon
DECL|variable|xa0ef6000
suffix:semicolon
suffix:semicolon
id|SDRAMC
l_int|0xa0ef6000
suffix:semicolon
suffix:semicolon
DECL|macro|SDRF0
mdefine_line|#define SDRF0         0xa0ef6000
DECL|macro|SDRF1
mdefine_line|#define SDRF1         0xa0ef6004
DECL|macro|SDIR0
mdefine_line|#define SDIR0         0xa0ef6008
DECL|macro|SDIR1
mdefine_line|#define SDIR1         0xa0ef600c
DECL|macro|SDBR
mdefine_line|#define SDBR          0xa0ef6010
suffix:semicolon
suffix:semicolon
id|CH0
DECL|macro|SD0ADR
mdefine_line|#define SD0ADR        0xa0ef6020
DECL|macro|SD0SZ
mdefine_line|#define SD0SZ         0xa0ef6022
DECL|macro|SD0ER
mdefine_line|#define SD0ER         0xa0ef6024
DECL|macro|SD0TR
mdefine_line|#define SD0TR         0xa0ef6028
DECL|macro|SD0MOD
mdefine_line|#define SD0MOD        0xa0ef602c
suffix:semicolon
suffix:semicolon
id|CH1
DECL|macro|SD1ADR
mdefine_line|#define SD1ADR        0xa0ef6040
DECL|macro|SD1SZ
mdefine_line|#define SD1SZ         0xa0ef6042
DECL|macro|SD1ER
mdefine_line|#define SD1ER         0xa0ef6044
DECL|macro|SD1TR
mdefine_line|#define SD1TR         0xa0ef6048
DECL|macro|SD1MOD
mdefine_line|#define SD1MOD        0xa0ef604c
suffix:semicolon
suffix:semicolon
DECL|variable|xa0ef8000
suffix:semicolon
suffix:semicolon
id|DMAC
l_int|0xa0ef8000
suffix:semicolon
suffix:semicolon
DECL|macro|DMAEN
mdefine_line|#define DMAEN         0xa0ef8000
DECL|macro|DMAISTS
mdefine_line|#define DMAISTS       0xa0ef8004
DECL|macro|DMAEDET
mdefine_line|#define DMAEDET       0xa0ef8008
DECL|macro|DMAASTS
mdefine_line|#define DMAASTS       0xa0ef800c
suffix:semicolon
suffix:semicolon
id|CH0
DECL|macro|DMA0CR0
mdefine_line|#define DMA0CR0       0xa0ef8100
DECL|macro|DMA0CR1
mdefine_line|#define DMA0CR1       0xa0ef8104
DECL|macro|DMA0CSA
mdefine_line|#define DMA0CSA       0xa0ef8108
DECL|macro|DMA0RSA
mdefine_line|#define DMA0RSA       0xa0ef810c
DECL|macro|DMA0CDA
mdefine_line|#define DMA0CDA       0xa0ef8110
DECL|macro|DMA0RDA
mdefine_line|#define DMA0RDA       0xa0ef8114
DECL|macro|DMA0CBCUT
mdefine_line|#define DMA0CBCUT     0xa0ef8118
DECL|macro|DMA0RBCUT
mdefine_line|#define DMA0RBCUT     0xa0ef811c
suffix:semicolon
suffix:semicolon
id|CH1
DECL|macro|DMA1CR0
mdefine_line|#define DMA1CR0       0xa0ef8200
DECL|macro|DMA1CR1
mdefine_line|#define DMA1CR1       0xa0ef8204
DECL|macro|DMA1CSA
mdefine_line|#define DMA1CSA       0xa0ef8208
DECL|macro|DMA1RSA
mdefine_line|#define DMA1RSA       0xa0ef820c
DECL|macro|DMA1CDA
mdefine_line|#define DMA1CDA       0xa0ef8210
DECL|macro|DMA1RDA
mdefine_line|#define DMA1RDA       0xa0ef8214
DECL|macro|DMA1CBCUT
mdefine_line|#define DMA1CBCUT     0xa0ef8218
DECL|macro|DMA1RBCUT
mdefine_line|#define DMA1RBCUT     0xa0ef821c
suffix:semicolon
suffix:semicolon
DECL|variable|xa0efc000
suffix:semicolon
suffix:semicolon
id|MFT
l_int|0xa0efc000
suffix:semicolon
suffix:semicolon
DECL|macro|MFTCR
mdefine_line|#define MFTCR        0xa0efc000
DECL|macro|MFTRPR
mdefine_line|#define MFTRPR       0xa0efc004
suffix:semicolon
suffix:semicolon
id|CH0
DECL|macro|MFT0MOD
mdefine_line|#define MFT0MOD      0xa0efc100
DECL|macro|MFT0BOS
mdefine_line|#define MFT0BOS      0xa0efc104
DECL|macro|MFT0CUT
mdefine_line|#define MFT0CUT      0xa0efc108
DECL|macro|MFT0RLD
mdefine_line|#define MFT0RLD      0xa0efc10c
DECL|macro|MFT0CMPRLD
mdefine_line|#define MFT0CMPRLD   0xa0efc110
suffix:semicolon
suffix:semicolon
id|CH1
DECL|macro|MFT1MOD
mdefine_line|#define MFT1MOD      0xa0efc200
DECL|macro|MFT1BOS
mdefine_line|#define MFT1BOS      0xa0efc204
DECL|macro|MFT1CUT
mdefine_line|#define MFT1CUT      0xa0efc208
DECL|macro|MFT1RLD
mdefine_line|#define MFT1RLD      0xa0efc20c
DECL|macro|MFT1CMPRLD
mdefine_line|#define MFT1CMPRLD   0xa0efc210
suffix:semicolon
suffix:semicolon
id|CH2
DECL|macro|MFT2MOD
mdefine_line|#define MFT2MOD      0xa0efc300
DECL|macro|MFT2BOS
mdefine_line|#define MFT2BOS      0xa0efc304
DECL|macro|MFT2CUT
mdefine_line|#define MFT2CUT      0xa0efc308
DECL|macro|MFT2RLD
mdefine_line|#define MFT2RLD      0xa0efc30c
DECL|macro|MFT2CMPRLD
mdefine_line|#define MFT2CMPRLD   0xa0efc310
suffix:semicolon
suffix:semicolon
id|CH3
DECL|macro|MFT3MOD
mdefine_line|#define MFT3MOD      0xa0efc400
DECL|macro|MFT3BOS
mdefine_line|#define MFT3BOS      0xa0efc404
DECL|macro|MFT3CUT
mdefine_line|#define MFT3CUT      0xa0efc408
DECL|macro|MFT3RLD
mdefine_line|#define MFT3RLD      0xa0efc40c
DECL|macro|MFT3CMPRLD
mdefine_line|#define MFT3CMPRLD   0xa0efc410
suffix:semicolon
suffix:semicolon
id|CH4
DECL|macro|MFT4MOD
mdefine_line|#define MFT4MOD      0xa0efc500
DECL|macro|MFT4BOS
mdefine_line|#define MFT4BOS      0xa0efc504
DECL|macro|MFT4CUT
mdefine_line|#define MFT4CUT      0xa0efc508
DECL|macro|MFT4RLD
mdefine_line|#define MFT4RLD      0xa0efc50c
DECL|macro|MFT4CMPRLD
mdefine_line|#define MFT4CMPRLD   0xa0efc510
suffix:semicolon
suffix:semicolon
id|CH5
DECL|macro|MFT5MOD
mdefine_line|#define MFT5MOD      0xa0efc600
DECL|macro|MFT5BOS
mdefine_line|#define MFT5BOS      0xa0efc604
DECL|macro|MFT5CUT
mdefine_line|#define MFT5CUT      0xa0efc608
DECL|macro|MFT5RLD
mdefine_line|#define MFT5RLD      0xa0efc60c
DECL|macro|MFT5CMPRLD
mdefine_line|#define MFT5CMPRLD   0xa0efc610
suffix:semicolon
suffix:semicolon
DECL|variable|xa0efd000
suffix:semicolon
suffix:semicolon
id|SIO
l_int|0xa0efd000
suffix:semicolon
suffix:semicolon
suffix:semicolon
suffix:semicolon
id|CH0
DECL|macro|SIO0CR
mdefine_line|#define SIO0CR        0xa0efd000
DECL|macro|SIO0MOD0
mdefine_line|#define SIO0MOD0      0xa0efd004
DECL|macro|SIO0MOD1
mdefine_line|#define SIO0MOD1      0xa0efd008
DECL|macro|SIO0STS
mdefine_line|#define SIO0STS       0xa0efd00c
DECL|macro|SIO0IMASK
mdefine_line|#define SIO0IMASK     0xa0efd010
DECL|macro|SIO0BAUR
mdefine_line|#define SIO0BAUR      0xa0efd014
DECL|macro|SIO0RBAUR
mdefine_line|#define SIO0RBAUR     0xa0efd018
DECL|macro|SIO0TXB
mdefine_line|#define SIO0TXB       0xa0efd01c
DECL|macro|SIO0RXB
mdefine_line|#define SIO0RXB       0xa0efd020
suffix:semicolon
suffix:semicolon
id|CH1
DECL|macro|SIO1CR
mdefine_line|#define SIO1CR        0xa0efd100
DECL|macro|SIO1MOD0
mdefine_line|#define SIO1MOD0      0xa0efd104
DECL|macro|SIO1MOD1
mdefine_line|#define SIO1MOD1      0xa0efd108
DECL|macro|SIO1STS
mdefine_line|#define SIO1STS       0xa0efd10c
DECL|macro|SIO1IMASK
mdefine_line|#define SIO1IMASK     0xa0efd110
DECL|macro|SIO1BAUR
mdefine_line|#define SIO1BAUR      0xa0efd114
DECL|macro|SIO1RBAUR
mdefine_line|#define SIO1RBAUR     0xa0efd118
DECL|macro|SIO1TXB
mdefine_line|#define SIO1TXB       0xa0efd11c
DECL|macro|SIO1RXB
mdefine_line|#define SIO1RXB       0xa0efd120
suffix:semicolon
suffix:semicolon
id|CH2
DECL|macro|SIO2CR
mdefine_line|#define SIO2CR        0xa0efd200
DECL|macro|SIO2MOD0
mdefine_line|#define SIO2MOD0      0xa0efd204
DECL|macro|SIO2MOD1
mdefine_line|#define SIO2MOD1      0xa0efd208
DECL|macro|SIO2STS
mdefine_line|#define SIO2STS       0xa0efd20c
DECL|macro|SIO2IMASK
mdefine_line|#define SIO2IMASK     0xa0efd210
DECL|macro|SIO2BAUR
mdefine_line|#define SIO2BAUR      0xa0efd214
DECL|macro|SIO2RBAUR
mdefine_line|#define SIO2RBAUR     0xa0efd218
DECL|macro|SIO2TXB
mdefine_line|#define SIO2TXB       0xa0efd21c
DECL|macro|SIO2RXB
mdefine_line|#define SIO2RXB       0xa0efd220
suffix:semicolon
suffix:semicolon
id|CH3
DECL|macro|SIO3CR
mdefine_line|#define SIO3CR        0xa0efd300
DECL|macro|SIO3MOD0
mdefine_line|#define SIO3MOD0      0xa0efd304
DECL|macro|SIO3MOD1
mdefine_line|#define SIO3MOD1      0xa0efd308
DECL|macro|SIO3STS
mdefine_line|#define SIO3STS       0xa0efd30c
DECL|macro|SIO3IMASK
mdefine_line|#define SIO3IMASK     0xa0efd310
DECL|macro|SIO3BAUR
mdefine_line|#define SIO3BAUR      0xa0efd314
DECL|macro|SIO3RBAUR
mdefine_line|#define SIO3RBAUR     0xa0efd318
DECL|macro|SIO3TXB
mdefine_line|#define SIO3TXB       0xa0efd31c
DECL|macro|SIO3RXB
mdefine_line|#define SIO3RXB       0xa0efd320
suffix:semicolon
suffix:semicolon
id|CH4
DECL|macro|SIO4CR
mdefine_line|#define SIO4CR        0xa0efd400
DECL|macro|SIO4MOD0
mdefine_line|#define SIO4MOD0      0xa0efd404
DECL|macro|SIO4MOD1
mdefine_line|#define SIO4MOD1      0xa0efd408
DECL|macro|SIO4STS
mdefine_line|#define SIO4STS       0xa0efd40c
DECL|macro|SIO4IMASK
mdefine_line|#define SIO4IMASK     0xa0efd410
DECL|macro|SIO4BAUR
mdefine_line|#define SIO4BAUR      0xa0efd414
DECL|macro|SIO4RBAUR
mdefine_line|#define SIO4RBAUR     0xa0efd418
DECL|macro|SIO4TXB
mdefine_line|#define SIO4TXB       0xa0efd41c
DECL|macro|SIO4RXB
mdefine_line|#define SIO4RXB       0xa0efd420
suffix:semicolon
suffix:semicolon
DECL|variable|xa0eff000
suffix:semicolon
suffix:semicolon
id|ICU
l_int|0xa0eff000
suffix:semicolon
suffix:semicolon
DECL|macro|ICUISTS
mdefine_line|#define ICUISTS       0xa0eff004
DECL|macro|ICUIREQ0
mdefine_line|#define ICUIREQ0      0xa0eff008
DECL|macro|ICUIREQ1
mdefine_line|#define ICUIREQ1      0xa0eff00c
DECL|macro|ICUSBICR
mdefine_line|#define ICUSBICR      0xa0eff018
DECL|macro|ICUIMASK
mdefine_line|#define ICUIMASK      0xa0eff01c
DECL|macro|ICUCR1
mdefine_line|#define ICUCR1        0xa0eff200
DECL|macro|ICUCR2
mdefine_line|#define ICUCR2        0xa0eff204
DECL|macro|ICUCR3
mdefine_line|#define ICUCR3        0xa0eff208
DECL|macro|ICUCR4
mdefine_line|#define ICUCR4        0xa0eff20c
DECL|macro|ICUCR5
mdefine_line|#define ICUCR5        0xa0eff210
DECL|macro|ICUCR6
mdefine_line|#define ICUCR6        0xa0eff214
DECL|macro|ICUCR7
mdefine_line|#define ICUCR7        0xa0eff218
DECL|macro|ICUCR16
mdefine_line|#define ICUCR16       0xa0eff23c
DECL|macro|ICUCR17
mdefine_line|#define ICUCR17       0xa0eff240
DECL|macro|ICUCR18
mdefine_line|#define ICUCR18       0xa0eff244
DECL|macro|ICUCR19
mdefine_line|#define ICUCR19       0xa0eff248
DECL|macro|ICUCR20
mdefine_line|#define ICUCR20       0xa0eff24c
DECL|macro|ICUCR21
mdefine_line|#define ICUCR21       0xa0eff250
DECL|macro|ICUCR32
mdefine_line|#define ICUCR32       0xa0eff27c
DECL|macro|ICUCR33
mdefine_line|#define ICUCR33       0xa0eff280
DECL|macro|ICUCR48
mdefine_line|#define ICUCR48       0xa0eff2bc
DECL|macro|ICUCR49
mdefine_line|#define ICUCR49       0xa0eff2c0
DECL|macro|ICUCR50
mdefine_line|#define ICUCR50       0xa0eff2c4
DECL|macro|ICUCR51
mdefine_line|#define ICUCR51       0xa0eff2c8
DECL|macro|ICUCR52
mdefine_line|#define ICUCR52       0xa0eff2cc
DECL|macro|ICUCR53
mdefine_line|#define ICUCR53       0xa0eff2d0
DECL|macro|ICUCR54
mdefine_line|#define ICUCR54       0xa0eff2d4
DECL|macro|ICUCR55
mdefine_line|#define ICUCR55       0xa0eff2d8
DECL|macro|ICUCR56
mdefine_line|#define ICUCR56       0xa0eff2dc
DECL|macro|ICUCR57
mdefine_line|#define ICUCR57       0xa0eff2e0
suffix:semicolon
suffix:semicolon
suffix:semicolon
suffix:semicolon
id|CACHE
suffix:semicolon
suffix:semicolon
DECL|macro|MCCR
mdefine_line|#define MCCR&t;&t;  0xfffffffc
macro_line|#endif  /* __ASSEMBLY__ */
eof
