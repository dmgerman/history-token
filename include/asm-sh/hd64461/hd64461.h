macro_line|#ifndef __ASM_SH_HD64461
DECL|macro|__ASM_SH_HD64461
mdefine_line|#define __ASM_SH_HD64461
multiline_comment|/*&n; *&t;$Id: hd64461.h,v 1.5 2004/03/16 00:07:51 lethal Exp $&n; *&t;Copyright (C) 2000 YAEGASHI Takeshi&n; *&t;Hitachi HD64461 companion chip support&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Constants for PCMCIA mappings */
DECL|macro|HD64461_PCC_WINDOW
mdefine_line|#define HD64461_PCC_WINDOW&t;0x01000000
DECL|macro|HD64461_PCC0_BASE
mdefine_line|#define HD64461_PCC0_BASE&t;0xb8000000&t;/* area 6 */
DECL|macro|HD64461_PCC0_ATTR
mdefine_line|#define HD64461_PCC0_ATTR&t;(HD64461_PCC0_BASE)
DECL|macro|HD64461_PCC0_COMM
mdefine_line|#define HD64461_PCC0_COMM&t;(HD64461_PCC0_BASE+HD64461_PCC_WINDOW)
DECL|macro|HD64461_PCC0_IO
mdefine_line|#define HD64461_PCC0_IO&t;&t;(HD64461_PCC0_BASE+2*HD64461_PCC_WINDOW)
DECL|macro|HD64461_PCC1_BASE
mdefine_line|#define HD64461_PCC1_BASE&t;0xb4000000&t;/* area 5 */
DECL|macro|HD64461_PCC1_ATTR
mdefine_line|#define HD64461_PCC1_ATTR&t;(HD64461_PCC1_BASE)
DECL|macro|HD64461_PCC1_COMM
mdefine_line|#define HD64461_PCC1_COMM&t;(HD64461_PCC1_BASE+HD64461_PCC_WINDOW)
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
DECL|macro|HD64461_STBCR_SURTST
mdefine_line|#define HD64461_STBCR_SURTST&t;&t;&t;0x0001
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
multiline_comment|/* PC Card Controller Registers */
DECL|macro|HD64461_PCC0ISR
mdefine_line|#define HD64461_PCC0ISR         0x12000 /* socket 0 interface status */
DECL|macro|HD64461_PCC0GCR
mdefine_line|#define HD64461_PCC0GCR         0x12002 /* socket 0 general control */
DECL|macro|HD64461_PCC0CSCR
mdefine_line|#define HD64461_PCC0CSCR        0x12004 /* socket 0 card status change */
DECL|macro|HD64461_PCC0CSCIER
mdefine_line|#define HD64461_PCC0CSCIER      0x12006 /* socket 0 card status change interrupt enable */
DECL|macro|HD64461_PCC0SCR
mdefine_line|#define HD64461_PCC0SCR         0x12008 /* socket 0 software control */
DECL|macro|HD64461_PCC1ISR
mdefine_line|#define HD64461_PCC1ISR         0x12010 /* socket 1 interface status */
DECL|macro|HD64461_PCC1GCR
mdefine_line|#define HD64461_PCC1GCR         0x12012 /* socket 1 general control */
DECL|macro|HD64461_PCC1CSCR
mdefine_line|#define HD64461_PCC1CSCR        0x12014 /* socket 1 card status change */
DECL|macro|HD64461_PCC1CSCIER
mdefine_line|#define HD64461_PCC1CSCIER      0x12016 /* socket 1 card status change interrupt enable */
DECL|macro|HD64461_PCC1SCR
mdefine_line|#define HD64461_PCC1SCR         0x12018 /* socket 1 software control */
multiline_comment|/* PCC Interface Status Register */
DECL|macro|HD64461_PCCISR_READY
mdefine_line|#define HD64461_PCCISR_READY&t;&t;0x80&t;/* card ready */
DECL|macro|HD64461_PCCISR_MWP
mdefine_line|#define HD64461_PCCISR_MWP&t;&t;0x40&t;/* card write-protected */
DECL|macro|HD64461_PCCISR_VS2
mdefine_line|#define HD64461_PCCISR_VS2&t;&t;0x20&t;/* voltage select pin 2 */
DECL|macro|HD64461_PCCISR_VS1
mdefine_line|#define HD64461_PCCISR_VS1&t;&t;0x10&t;/* voltage select pin 1 */
DECL|macro|HD64461_PCCISR_CD2
mdefine_line|#define HD64461_PCCISR_CD2&t;&t;0x08&t;/* card detect 2 */
DECL|macro|HD64461_PCCISR_CD1
mdefine_line|#define HD64461_PCCISR_CD1&t;&t;0x04&t;/* card detect 1 */
DECL|macro|HD64461_PCCISR_BVD2
mdefine_line|#define HD64461_PCCISR_BVD2&t;&t;0x02&t;/* battery 1 */
DECL|macro|HD64461_PCCISR_BVD1
mdefine_line|#define HD64461_PCCISR_BVD1&t;&t;0x01&t;/* battery 1 */
DECL|macro|HD64461_PCCISR_PCD_MASK
mdefine_line|#define HD64461_PCCISR_PCD_MASK&t;&t;0x0c    /* card detect */
DECL|macro|HD64461_PCCISR_BVD_MASK
mdefine_line|#define HD64461_PCCISR_BVD_MASK&t;0x03    /* battery voltage */
DECL|macro|HD64461_PCCISR_BVD_BATGOOD
mdefine_line|#define HD64461_PCCISR_BVD_BATGOOD&t;0x03    /* battery good */
DECL|macro|HD64461_PCCISR_BVD_BATWARN
mdefine_line|#define HD64461_PCCISR_BVD_BATWARN&t;0x01    /* battery low warning */
DECL|macro|HD64461_PCCISR_BVD_BATDEAD1
mdefine_line|#define HD64461_PCCISR_BVD_BATDEAD1&t;0x02    /* battery dead */
DECL|macro|HD64461_PCCISR_BVD_BATDEAD2
mdefine_line|#define HD64461_PCCISR_BVD_BATDEAD2&t;0x00    /* battery dead */
multiline_comment|/* PCC General Control Register */
DECL|macro|HD64461_PCCGCR_DRVE
mdefine_line|#define HD64461_PCCGCR_DRVE&t;&t;0x80    /* output drive */
DECL|macro|HD64461_PCCGCR_PCCR
mdefine_line|#define HD64461_PCCGCR_PCCR&t;&t;0x40    /* PC card reset */
DECL|macro|HD64461_PCCGCR_PCCT
mdefine_line|#define HD64461_PCCGCR_PCCT&t;&t;0x20    /* PC card type, 1=IO&amp;mem, 0=mem */
DECL|macro|HD64461_PCCGCR_VCC0
mdefine_line|#define HD64461_PCCGCR_VCC0&t;&t;0x10    /* voltage control pin VCC0SEL0 */
DECL|macro|HD64461_PCCGCR_PMMOD
mdefine_line|#define HD64461_PCCGCR_PMMOD&t;&t;0x08    /* memory mode */
DECL|macro|HD64461_PCCGCR_PA25
mdefine_line|#define HD64461_PCCGCR_PA25&t;&t;0x04    /* pin A25 */
DECL|macro|HD64461_PCCGCR_PA24
mdefine_line|#define HD64461_PCCGCR_PA24&t;&t;0x02    /* pin A24 */
DECL|macro|HD64461_PCCGCR_REG
mdefine_line|#define HD64461_PCCGCR_REG&t;&t;0x01    /* pin PCC0REG# */
multiline_comment|/* PCC Card Status Change Register */
DECL|macro|HD64461_PCCCSCR_SCDI
mdefine_line|#define HD64461_PCCCSCR_SCDI&t;&t;0x80    /* sw card detect intr */
DECL|macro|HD64461_PCCCSCR_SRV1
mdefine_line|#define HD64461_PCCCSCR_SRV1&t;&t;0x40    /* reserved */
DECL|macro|HD64461_PCCCSCR_IREQ
mdefine_line|#define HD64461_PCCCSCR_IREQ&t;&t;0x20    /* IREQ intr req */
DECL|macro|HD64461_PCCCSCR_SC
mdefine_line|#define HD64461_PCCCSCR_SC&t;&t;0x10    /* STSCHG (status change) pin */
DECL|macro|HD64461_PCCCSCR_CDC
mdefine_line|#define HD64461_PCCCSCR_CDC&t;&t;0x08    /* CD (card detect) change */
DECL|macro|HD64461_PCCCSCR_RC
mdefine_line|#define HD64461_PCCCSCR_RC&t;&t;0x04    /* READY change */
DECL|macro|HD64461_PCCCSCR_BW
mdefine_line|#define HD64461_PCCCSCR_BW&t;&t;0x02    /* battery warning change */
DECL|macro|HD64461_PCCCSCR_BD
mdefine_line|#define HD64461_PCCCSCR_BD&t;&t;0x01    /* battery dead change */
multiline_comment|/* PCC Card Status Change Interrupt Enable Register */
DECL|macro|HD64461_PCCCSCIER_CRE
mdefine_line|#define HD64461_PCCCSCIER_CRE&t;&t;0x80    /* change reset enable */
DECL|macro|HD64461_PCCCSCIER_IREQE_MASK
mdefine_line|#define HD64461_PCCCSCIER_IREQE_MASK   &t;0x60   /* IREQ enable */
DECL|macro|HD64461_PCCCSCIER_IREQE_DISABLED
mdefine_line|#define HD64461_PCCCSCIER_IREQE_DISABLED&t;0x00   /* IREQ disabled */
DECL|macro|HD64461_PCCCSCIER_IREQE_LEVEL
mdefine_line|#define HD64461_PCCCSCIER_IREQE_LEVEL  &t;0x20   /* IREQ level-triggered */
DECL|macro|HD64461_PCCCSCIER_IREQE_FALLING
mdefine_line|#define HD64461_PCCCSCIER_IREQE_FALLING&t;0x40   /* IREQ falling-edge-trig */
DECL|macro|HD64461_PCCCSCIER_IREQE_RISING
mdefine_line|#define HD64461_PCCCSCIER_IREQE_RISING &t;0x60   /* IREQ rising-edge-trig */
DECL|macro|HD64461_PCCCSCIER_SCE
mdefine_line|#define HD64461_PCCCSCIER_SCE&t;&t;0x10    /* status change enable */
DECL|macro|HD64461_PCCCSCIER_CDE
mdefine_line|#define HD64461_PCCCSCIER_CDE&t;&t;0x08    /* card detect change enable */
DECL|macro|HD64461_PCCCSCIER_RE
mdefine_line|#define HD64461_PCCCSCIER_RE&t;&t;0x04    /* ready change enable */
DECL|macro|HD64461_PCCCSCIER_BWE
mdefine_line|#define HD64461_PCCCSCIER_BWE&t;&t;0x02    /* battery warn change enable */
DECL|macro|HD64461_PCCCSCIER_BDE
mdefine_line|#define HD64461_PCCCSCIER_BDE&t;&t;0x01    /* battery dead change enable*/
multiline_comment|/* PCC Software Control Register */
DECL|macro|HD64461_PCCSCR_VCC1
mdefine_line|#define HD64461_PCCSCR_VCC1&t;&t;0x02&t;/* voltage control pin 1 */
DECL|macro|HD64461_PCCSCR_SWP
mdefine_line|#define HD64461_PCCSCR_SWP&t;&t;0x01    /* write protect */
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
DECL|macro|HD64461_IRQ_UART
mdefine_line|#define HD64461_IRQ_UART    &t;(HD64461_IRQBASE+5)
DECL|macro|HD64461_IRQ_IRDA
mdefine_line|#define HD64461_IRQ_IRDA    &t;(HD64461_IRQBASE+6)
DECL|macro|HD64461_IRQ_TMU1
mdefine_line|#define HD64461_IRQ_TMU1   &t;(HD64461_IRQBASE+9)
DECL|macro|HD64461_IRQ_TMU0
mdefine_line|#define HD64461_IRQ_TMU0  &t;(HD64461_IRQBASE+10)
DECL|macro|HD64461_IRQ_GPIO
mdefine_line|#define HD64461_IRQ_GPIO    &t;(HD64461_IRQBASE+11)
DECL|macro|HD64461_IRQ_AFE
mdefine_line|#define HD64461_IRQ_AFE     &t;(HD64461_IRQBASE+12)
DECL|macro|HD64461_IRQ_PCC1
mdefine_line|#define HD64461_IRQ_PCC1 &t;(HD64461_IRQBASE+13)
DECL|macro|HD64461_IRQ_PCC0
mdefine_line|#define HD64461_IRQ_PCC0 &t;(HD64461_IRQBASE+14)
macro_line|#endif
eof
