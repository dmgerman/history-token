macro_line|#ifndef __ASM_SH_HD64461
DECL|macro|__ASM_SH_HD64461
mdefine_line|#define __ASM_SH_HD64461
multiline_comment|/*&n; *&t;$Id: hd64461.h,v 1.4 2004/02/01 19:46:04 lethal Exp $&n; *&t;Copyright (C) 2000 YAEGASHI Takeshi&n; *&t;Hitachi HD64461 companion chip support&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|HD64461_STBCR
mdefine_line|#define HD64461_STBCR&t;0x10000
DECL|macro|HD64461_STBCR_CKIO_STBY
mdefine_line|#define HD64461_STBCR_CKIO_STBY&t;&t;&t;0x2000
DECL|macro|HD64461_STBCR_SAFECKE_IST
mdefine_line|#define HD64461_STBCR_SAFECKE_IST&t;&t;0x1000
DECL|macro|HD64461_STBCR_SLCKE_IST
mdefine_line|#define HD64461_STBCR_SLCKE_IST&t;&t;&t;0x0800
DECL|macro|HD64461_STBCR_SAFECKE_OST
mdefine_line|#define HD64461_STBCR_SAFECKE_OST&t;&t;0x0400
DECL|macro|HD64461_STBCR_SLCKE_OST
mdefine_line|#define HD64461_STBCR_SLCKE_OST&t;&t;&t;0x0200
DECL|macro|HD64461_STBCR_SMIAST
mdefine_line|#define HD64461_STBCR_SMIAST&t;&t;&t;0x0100
DECL|macro|HD64461_STBCR_SLCDST
mdefine_line|#define HD64461_STBCR_SLCDST&t;&t;&t;0x0080
DECL|macro|HD64461_STBCR_SPC0ST
mdefine_line|#define HD64461_STBCR_SPC0ST&t;&t;&t;0x0040
DECL|macro|HD64461_STBCR_SPC1ST
mdefine_line|#define HD64461_STBCR_SPC1ST&t;&t;&t;0x0020
DECL|macro|HD64461_STBCR_SAFEST
mdefine_line|#define HD64461_STBCR_SAFEST&t;&t;&t;0x0010
DECL|macro|HD64461_STBCR_STM0ST
mdefine_line|#define HD64461_STBCR_STM0ST&t;&t;&t;0x0008
DECL|macro|HD64461_STBCR_STM1ST
mdefine_line|#define HD64461_STBCR_STM1ST&t;&t;&t;0x0004
DECL|macro|HD64461_STBCR_SIRST
mdefine_line|#define HD64461_STBCR_SIRST&t;&t;&t;&t;0x0002
DECL|macro|HD64461_STBCR_SURTSD
mdefine_line|#define HD64461_STBCR_SURTSD&t;&t;&t;0x0001
DECL|macro|HD64461_SYSCR
mdefine_line|#define HD64461_SYSCR&t;0x10002
DECL|macro|HD64461_SCPUCR
mdefine_line|#define HD64461_SCPUCR&t;0x10004
DECL|macro|HD64461_LCDCBAR
mdefine_line|#define HD64461_LCDCBAR&t;&t;0x11000
DECL|macro|HD64461_LCDCLOR
mdefine_line|#define HD64461_LCDCLOR&t;&t;0x11002
DECL|macro|HD64461_LCDCCR
mdefine_line|#define HD64461_LCDCCR&t;&t;0x11004
DECL|macro|HD64461_LCDCCR_MOFF
mdefine_line|#define HD64461_LCDCCR_MOFF&t;0x80
DECL|macro|HD64461_LDR1
mdefine_line|#define&t;HD64461_LDR1&t;&t;0x11010
DECL|macro|HD64461_LDR1_DON
mdefine_line|#define&t;HD64461_LDR1_DON&t;0x01
DECL|macro|HD64461_LDR1_DINV
mdefine_line|#define&t;HD64461_LDR1_DINV&t;0x80
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
DECL|macro|HD64461_GRDOR
mdefine_line|#define HD64461_GRDOR&t;&t;0x11040
DECL|macro|HD64461_GRSCR
mdefine_line|#define HD64461_GRSCR&t;&t;0x11042
DECL|macro|HD64461_GRCFGR
mdefine_line|#define HD64461_GRCFGR&t;&t;0x11044
DECL|macro|HD64461_GRCFGR_ACCSTATUS
mdefine_line|#define HD64461_GRCFGR_ACCSTATUS&t;&t;0x10
DECL|macro|HD64461_GRCFGR_ACCRESET
mdefine_line|#define HD64461_GRCFGR_ACCRESET&t;&t;&t;0x08
DECL|macro|HD64461_GRCFGR_ACCSTART_BITBLT
mdefine_line|#define HD64461_GRCFGR_ACCSTART_BITBLT&t;0x06
DECL|macro|HD64461_GRCFGR_ACCSTART_LINE
mdefine_line|#define HD64461_GRCFGR_ACCSTART_LINE&t;0x04
DECL|macro|HD64461_GRCFGR_COLORDEPTH16
mdefine_line|#define HD64461_GRCFGR_COLORDEPTH16&t;&t;0x01
DECL|macro|HD64461_LNSARH
mdefine_line|#define HD64461_LNSARH&t;&t;0x11046
DECL|macro|HD64461_LNSARL
mdefine_line|#define HD64461_LNSARL&t;&t;0x11048
DECL|macro|HD64461_LNAXLR
mdefine_line|#define HD64461_LNAXLR&t;&t;0x1104a
DECL|macro|HD64461_LNDGR
mdefine_line|#define HD64461_LNDGR&t;&t;0x1104c
DECL|macro|HD64461_LNAXR
mdefine_line|#define HD64461_LNAXR&t;&t;0x1104e
DECL|macro|HD64461_LNERTR
mdefine_line|#define HD64461_LNERTR&t;&t;0x11050
DECL|macro|HD64461_LNMDR
mdefine_line|#define HD64461_LNMDR&t;&t;0x11052
DECL|macro|HD64461_BBTSSARH
mdefine_line|#define HD64461_BBTSSARH&t;0x11054
DECL|macro|HD64461_BBTSSARL
mdefine_line|#define HD64461_BBTSSARL&t;0x11056
DECL|macro|HD64461_BBTDSARH
mdefine_line|#define HD64461_BBTDSARH&t;0x11058
DECL|macro|HD64461_BBTDSARL
mdefine_line|#define HD64461_BBTDSARL&t;0x1105a
DECL|macro|HD64461_BBTDWR
mdefine_line|#define HD64461_BBTDWR&t;&t;0x1105c
DECL|macro|HD64461_BBTDHR
mdefine_line|#define HD64461_BBTDHR&t;&t;0x1105e
DECL|macro|HD64461_BBTPARH
mdefine_line|#define HD64461_BBTPARH&t;&t;0x11060
DECL|macro|HD64461_BBTPARL
mdefine_line|#define HD64461_BBTPARL&t;&t;0x11062
DECL|macro|HD64461_BBTMARH
mdefine_line|#define HD64461_BBTMARH&t;&t;0x11064
DECL|macro|HD64461_BBTMARL
mdefine_line|#define HD64461_BBTMARL&t;&t;0x11066
DECL|macro|HD64461_BBTROPR
mdefine_line|#define HD64461_BBTROPR&t;&t;0x11068
DECL|macro|HD64461_BBTMDR
mdefine_line|#define HD64461_BBTMDR&t;&t;0x1106a
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
DECL|macro|HD64461_IRQ_NUM
mdefine_line|#define HD64461_IRQ_NUM &t;16
macro_line|#endif
eof
