macro_line|#ifndef __ASM_SH_HD64461
DECL|macro|__ASM_SH_HD64461
mdefine_line|#define __ASM_SH_HD64461
multiline_comment|/*&n; *&t;$Id: hd64461.h,v 1.1 2000/06/10 21:45:48 yaegashi Exp $&n; *&t;Copyright (C) 2000 YAEGASHI Takeshi&n; *&t;Hitachi HD64461 companion chip support&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|HD64461_STBCR
mdefine_line|#define HD64461_STBCR&t;0x10000
DECL|macro|HD64461_SYSCR
mdefine_line|#define HD64461_SYSCR&t;0x10002
DECL|macro|HD64461_SCPUCR
mdefine_line|#define HD64461_SCPUCR&t;0x10004
DECL|macro|HD64461_LCDCBAR
mdefine_line|#define HD64461_LCDCBAR&t;&t;0x11000
DECL|macro|HD64461_LCDCLOR
mdefine_line|#define HD64461_LCDCLOR&t;&t;0x11002
DECL|macro|HD64461_LCDCCRR
mdefine_line|#define HD64461_LCDCCRR&t;&t;0x11004
DECL|macro|HD64461_LDR1
mdefine_line|#define&t;HD64461_LDR1&t;&t;0x11010
DECL|macro|HD64461_LDR2
mdefine_line|#define&t;HD64461_LDR2&t;&t;0x11012
DECL|macro|HD64461_LDHNCR
mdefine_line|#define&t;HD64461_LDHNCR&t;&t;0x11014
DECL|macro|HD64461_LDHNSR
mdefine_line|#define&t;HD64461_LDHNSR&t;&t;0x11016
DECL|macro|HD64461_LDVNTR
mdefine_line|#define HD64461_LDVNTR&t;&t;0x11018
DECL|macro|HD64461_LDVNDR
mdefine_line|#define HD64461_LDVNDR&t;&t;0x1101a
DECL|macro|HD64461_LDVSPR
mdefine_line|#define HD64461_LDVSPR&t;&t;0x1101c
DECL|macro|HD64461_LDR3
mdefine_line|#define HD64461_LDR3&t;&t;0x1101e
DECL|macro|HD64461_CPTWAR
mdefine_line|#define HD64461_CPTWAR&t;&t;0x11030&t;
DECL|macro|HD64461_CPTWDR
mdefine_line|#define HD64461_CPTWDR&t;&t;0x11032
DECL|macro|HD64461_CPTRAR
mdefine_line|#define HD64461_CPTRAR&t;&t;0x11034&t;
DECL|macro|HD64461_CPTRDR
mdefine_line|#define HD64461_CPTRDR&t;&t;0x11036
DECL|macro|HD64461_PCC0ISR
mdefine_line|#define HD64461_PCC0ISR         0x12000
DECL|macro|HD64461_PCC0GCR
mdefine_line|#define HD64461_PCC0GCR         0x12002
DECL|macro|HD64461_PCC0CSCR
mdefine_line|#define HD64461_PCC0CSCR        0x12004
DECL|macro|HD64461_PCC0CSCIER
mdefine_line|#define HD64461_PCC0CSCIER      0x12006
DECL|macro|HD64461_PCC0SCR
mdefine_line|#define HD64461_PCC0SCR         0x12008
DECL|macro|HD64461_PCC1ISR
mdefine_line|#define HD64461_PCC1ISR         0x12010
DECL|macro|HD64461_PCC1GCR
mdefine_line|#define HD64461_PCC1GCR         0x12012
DECL|macro|HD64461_PCC1CSCR
mdefine_line|#define HD64461_PCC1CSCR        0x12014
DECL|macro|HD64461_PCC1CSCIER
mdefine_line|#define HD64461_PCC1CSCIER      0x12016
DECL|macro|HD64461_PCC1SCR
mdefine_line|#define HD64461_PCC1SCR         0x12018
DECL|macro|HD64461_P0OCR
mdefine_line|#define HD64461_P0OCR           0x1202a
DECL|macro|HD64461_P1OCR
mdefine_line|#define HD64461_P1OCR           0x1202c
DECL|macro|HD64461_PGCR
mdefine_line|#define HD64461_PGCR            0x1202e
DECL|macro|HD64461_GPACR
mdefine_line|#define HD64461_GPACR&t;&t;0x14000
DECL|macro|HD64461_GPBCR
mdefine_line|#define HD64461_GPBCR&t;&t;0x14002
DECL|macro|HD64461_GPCCR
mdefine_line|#define HD64461_GPCCR&t;&t;0x14004
DECL|macro|HD64461_GPDCR
mdefine_line|#define HD64461_GPDCR&t;&t;0x14006
DECL|macro|HD64461_GPADR
mdefine_line|#define HD64461_GPADR&t;&t;0x14010
DECL|macro|HD64461_GPBDR
mdefine_line|#define HD64461_GPBDR&t;&t;0x14012
DECL|macro|HD64461_GPCDR
mdefine_line|#define HD64461_GPCDR&t;&t;0x14014
DECL|macro|HD64461_GPDDR
mdefine_line|#define HD64461_GPDDR&t;&t;0x14016
DECL|macro|HD64461_GPAICR
mdefine_line|#define HD64461_GPAICR&t;&t;0x14020
DECL|macro|HD64461_GPBICR
mdefine_line|#define HD64461_GPBICR&t;&t;0x14022
DECL|macro|HD64461_GPCICR
mdefine_line|#define HD64461_GPCICR&t;&t;0x14024
DECL|macro|HD64461_GPDICR
mdefine_line|#define HD64461_GPDICR&t;&t;0x14026
DECL|macro|HD64461_GPAISR
mdefine_line|#define HD64461_GPAISR&t;&t;0x14040
DECL|macro|HD64461_GPBISR
mdefine_line|#define HD64461_GPBISR&t;&t;0x14042
DECL|macro|HD64461_GPCISR
mdefine_line|#define HD64461_GPCISR&t;&t;0x14044
DECL|macro|HD64461_GPDISR
mdefine_line|#define HD64461_GPDISR&t;&t;0x14046
DECL|macro|HD64461_NIRR
mdefine_line|#define HD64461_NIRR&t;&t;0x15000
DECL|macro|HD64461_NIMR
mdefine_line|#define HD64461_NIMR&t;&t;0x15002
macro_line|#ifndef CONFIG_HD64461_IOBASE
DECL|macro|CONFIG_HD64461_IOBASE
mdefine_line|#define CONFIG_HD64461_IOBASE&t;0xb0000000
macro_line|#endif
macro_line|#ifndef CONFIG_HD64461_IRQ
DECL|macro|CONFIG_HD64461_IRQ
mdefine_line|#define CONFIG_HD64461_IRQ&t;36
macro_line|#endif
DECL|macro|HD64461_IRQBASE
mdefine_line|#define HD64461_IRQBASE&t;&t;OFFCHIP_IRQ_BASE
macro_line|#endif
eof
