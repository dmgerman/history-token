multiline_comment|/* $Id: w6692.h,v 1.2 2000/06/26 08:59:15 keil Exp $&n; *&n; * w6692.h   Winbond W6692 specific defines&n; *&n; * Author       Petr Novak &lt;petr.novak@i.cz&gt;&n; *&n; * This file is (c) under GNU PUBLIC LICENSE&n; *&n; */
multiline_comment|/* map W6692 functions to ISAC functions */
DECL|macro|readW6692
mdefine_line|#define readW6692&t;readisac
DECL|macro|writeW6692
mdefine_line|#define writeW6692&t;writeisac
DECL|macro|readW6692fifo
mdefine_line|#define&t;readW6692fifo&t;readisacfifo
DECL|macro|writeW6692fifo
mdefine_line|#define&t;writeW6692fifo&t;writeisacfifo
multiline_comment|/* B-channel FIFO read/write routines */
DECL|macro|READW6692BFIFO
mdefine_line|#define READW6692BFIFO(cs,bchan,ptr,count) &bslash;&n;&t;insb(cs-&gt;hw.w6692.iobase+W_B_RFIFO+(bchan?0x40:0),ptr,count)
DECL|macro|WRITEW6692BFIFO
mdefine_line|#define WRITEW6692BFIFO(cs,bchan,ptr,count) &bslash;&n;&t;outsb(cs-&gt;hw.w6692.iobase+W_B_XFIFO+(bchan?0x40:0),ptr,count)
multiline_comment|/* Specifications of W6692 registers */
DECL|macro|W_D_RFIFO
mdefine_line|#define W_D_RFIFO&t;0x00&t;/* R */
DECL|macro|W_D_XFIFO
mdefine_line|#define W_D_XFIFO&t;0x04&t;/* W */
DECL|macro|W_D_CMDR
mdefine_line|#define W_D_CMDR&t;0x08&t;/* W */
DECL|macro|W_D_MODE
mdefine_line|#define W_D_MODE&t;0x0c&t;/* R/W */
DECL|macro|W_D_TIMR
mdefine_line|#define W_D_TIMR&t;0x10&t;/* R/W */
DECL|macro|W_ISTA
mdefine_line|#define W_ISTA&t;&t;0x14&t;/* R_clr */
DECL|macro|W_IMASK
mdefine_line|#define W_IMASK&t;&t;0x18&t;/* R/W */
DECL|macro|W_D_EXIR
mdefine_line|#define W_D_EXIR&t;0x1c&t;/* R_clr */
DECL|macro|W_D_EXIM
mdefine_line|#define W_D_EXIM&t;0x20&t;/* R/W */
DECL|macro|W_D_STAR
mdefine_line|#define W_D_STAR&t;0x24&t;/* R */
DECL|macro|W_D_RSTA
mdefine_line|#define W_D_RSTA&t;0x28&t;/* R */
DECL|macro|W_D_SAM
mdefine_line|#define W_D_SAM&t;&t;0x2c&t;/* R/W */
DECL|macro|W_D_SAP1
mdefine_line|#define W_D_SAP1&t;0x30&t;/* R/W */
DECL|macro|W_D_SAP2
mdefine_line|#define W_D_SAP2&t;0x34&t;/* R/W */
DECL|macro|W_D_TAM
mdefine_line|#define W_D_TAM&t;&t;0x38&t;/* R/W */
DECL|macro|W_D_TEI1
mdefine_line|#define W_D_TEI1&t;0x3c&t;/* R/W */
DECL|macro|W_D_TEI2
mdefine_line|#define W_D_TEI2&t;0x40&t;/* R/W */
DECL|macro|W_D_RBCH
mdefine_line|#define W_D_RBCH&t;0x44&t;/* R */
DECL|macro|W_D_RBCL
mdefine_line|#define W_D_RBCL&t;0x48&t;/* R */
DECL|macro|W_TIMR2
mdefine_line|#define W_TIMR2&t;&t;0x4c&t;/* W */
DECL|macro|W_L1_RC
mdefine_line|#define W_L1_RC&t;&t;0x50&t;/* R/W */
DECL|macro|W_D_CTL
mdefine_line|#define W_D_CTL&t;&t;0x54&t;/* R/W */
DECL|macro|W_CIR
mdefine_line|#define W_CIR&t;&t;0x58&t;/* R */
DECL|macro|W_CIX
mdefine_line|#define W_CIX&t;&t;0x5c&t;/* W */
DECL|macro|W_SQR
mdefine_line|#define W_SQR&t;&t;0x60&t;/* R */
DECL|macro|W_SQX
mdefine_line|#define W_SQX&t;&t;0x64&t;/* W */
DECL|macro|W_PCTL
mdefine_line|#define W_PCTL&t;&t;0x68&t;/* R/W */
DECL|macro|W_MOR
mdefine_line|#define W_MOR&t;&t;0x6c&t;/* R */
DECL|macro|W_MOX
mdefine_line|#define W_MOX&t;&t;0x70&t;/* R/W */
DECL|macro|W_MOSR
mdefine_line|#define W_MOSR&t;&t;0x74&t;/* R_clr */
DECL|macro|W_MOCR
mdefine_line|#define W_MOCR&t;&t;0x78&t;/* R/W */
DECL|macro|W_GCR
mdefine_line|#define W_GCR&t;&t;0x7c&t;/* R/W */
DECL|macro|W_B_RFIFO
mdefine_line|#define&t;W_B_RFIFO&t;0x80&t;/* R */
DECL|macro|W_B_XFIFO
mdefine_line|#define&t;W_B_XFIFO&t;0x84&t;/* W */
DECL|macro|W_B_CMDR
mdefine_line|#define&t;W_B_CMDR&t;0x88&t;/* W */
DECL|macro|W_B_MODE
mdefine_line|#define&t;W_B_MODE&t;0x8c&t;/* R/W */
DECL|macro|W_B_EXIR
mdefine_line|#define&t;W_B_EXIR&t;0x90&t;/* R_clr */
DECL|macro|W_B_EXIM
mdefine_line|#define&t;W_B_EXIM&t;0x94&t;/* R/W */
DECL|macro|W_B_STAR
mdefine_line|#define&t;W_B_STAR&t;0x98&t;/* R */
DECL|macro|W_B_ADM1
mdefine_line|#define&t;W_B_ADM1&t;0x9c&t;/* R/W */
DECL|macro|W_B_ADM2
mdefine_line|#define&t;W_B_ADM2&t;0xa0&t;/* R/W */
DECL|macro|W_B_ADR1
mdefine_line|#define&t;W_B_ADR1&t;0xa4&t;/* R/W */
DECL|macro|W_B_ADR2
mdefine_line|#define&t;W_B_ADR2&t;0xa8&t;/* R/W */
DECL|macro|W_B_RBCL
mdefine_line|#define&t;W_B_RBCL&t;0xac&t;/* R */
DECL|macro|W_B_RBCH
mdefine_line|#define&t;W_B_RBCH&t;0xb0&t;/* R */
DECL|macro|W_XADDR
mdefine_line|#define W_XADDR&t;&t;0xf4&t;/* R/W */
DECL|macro|W_XDATA
mdefine_line|#define W_XDATA&t;&t;0xf8&t;/* R/W */
DECL|macro|W_EPCTL
mdefine_line|#define W_EPCTL&t;&t;0xfc&t;/* W */
multiline_comment|/* W6692 register bits */
DECL|macro|W_D_CMDR_XRST
mdefine_line|#define&t;W_D_CMDR_XRST&t;0x01
DECL|macro|W_D_CMDR_XME
mdefine_line|#define&t;W_D_CMDR_XME&t;0x02
DECL|macro|W_D_CMDR_XMS
mdefine_line|#define&t;W_D_CMDR_XMS&t;0x08
DECL|macro|W_D_CMDR_STT
mdefine_line|#define&t;W_D_CMDR_STT&t;0x10
DECL|macro|W_D_CMDR_RRST
mdefine_line|#define&t;W_D_CMDR_RRST&t;0x40
DECL|macro|W_D_CMDR_RACK
mdefine_line|#define&t;W_D_CMDR_RACK&t;0x80
DECL|macro|W_D_MODE_RLP
mdefine_line|#define&t;W_D_MODE_RLP&t;0x01
DECL|macro|W_D_MODE_DLP
mdefine_line|#define&t;W_D_MODE_DLP&t;0x02
DECL|macro|W_D_MODE_MFD
mdefine_line|#define&t;W_D_MODE_MFD&t;0x04
DECL|macro|W_D_MODE_TEE
mdefine_line|#define&t;W_D_MODE_TEE&t;0x08
DECL|macro|W_D_MODE_TMS
mdefine_line|#define&t;W_D_MODE_TMS&t;0x10
DECL|macro|W_D_MODE_RACT
mdefine_line|#define&t;W_D_MODE_RACT&t;0x40
DECL|macro|W_D_MODE_MMS
mdefine_line|#define&t;W_D_MODE_MMS&t;0x80
DECL|macro|W_INT_B2_EXI
mdefine_line|#define W_INT_B2_EXI&t;0x01
DECL|macro|W_INT_B1_EXI
mdefine_line|#define W_INT_B1_EXI&t;0x02
DECL|macro|W_INT_D_EXI
mdefine_line|#define W_INT_D_EXI&t;0x04
DECL|macro|W_INT_XINT0
mdefine_line|#define W_INT_XINT0&t;0x08
DECL|macro|W_INT_XINT1
mdefine_line|#define W_INT_XINT1&t;0x10
DECL|macro|W_INT_D_XFR
mdefine_line|#define W_INT_D_XFR&t;0x20
DECL|macro|W_INT_D_RME
mdefine_line|#define W_INT_D_RME&t;0x40
DECL|macro|W_INT_D_RMR
mdefine_line|#define W_INT_D_RMR&t;0x80
DECL|macro|W_D_EXI_WEXP
mdefine_line|#define W_D_EXI_WEXP&t;0x01
DECL|macro|W_D_EXI_TEXP
mdefine_line|#define W_D_EXI_TEXP&t;0x02
DECL|macro|W_D_EXI_ISC
mdefine_line|#define W_D_EXI_ISC&t;0x04
DECL|macro|W_D_EXI_MOC
mdefine_line|#define W_D_EXI_MOC&t;0x08
DECL|macro|W_D_EXI_TIN2
mdefine_line|#define W_D_EXI_TIN2&t;0x10
DECL|macro|W_D_EXI_XCOL
mdefine_line|#define W_D_EXI_XCOL&t;0x20
DECL|macro|W_D_EXI_XDUN
mdefine_line|#define W_D_EXI_XDUN&t;0x40
DECL|macro|W_D_EXI_RDOV
mdefine_line|#define W_D_EXI_RDOV&t;0x80
DECL|macro|W_D_STAR_DRDY
mdefine_line|#define&t;W_D_STAR_DRDY&t;0x10
DECL|macro|W_D_STAR_XBZ
mdefine_line|#define&t;W_D_STAR_XBZ&t;0x20
DECL|macro|W_D_STAR_XDOW
mdefine_line|#define&t;W_D_STAR_XDOW&t;0x80
DECL|macro|W_D_RSTA_RMB
mdefine_line|#define W_D_RSTA_RMB&t;0x10
DECL|macro|W_D_RSTA_CRCE
mdefine_line|#define W_D_RSTA_CRCE&t;0x20
DECL|macro|W_D_RSTA_RDOV
mdefine_line|#define W_D_RSTA_RDOV&t;0x40
DECL|macro|W_D_CTL_SRST
mdefine_line|#define W_D_CTL_SRST&t;0x20
DECL|macro|W_CIR_SCC
mdefine_line|#define W_CIR_SCC&t;0x80
DECL|macro|W_CIR_ICC
mdefine_line|#define W_CIR_ICC&t;0x40
DECL|macro|W_CIR_COD_MASK
mdefine_line|#define W_CIR_COD_MASK&t;0x0f
DECL|macro|W_B_CMDR_XRST
mdefine_line|#define&t;W_B_CMDR_XRST&t;0x01
DECL|macro|W_B_CMDR_XME
mdefine_line|#define&t;W_B_CMDR_XME&t;0x02
DECL|macro|W_B_CMDR_XMS
mdefine_line|#define&t;W_B_CMDR_XMS&t;0x04
DECL|macro|W_B_CMDR_RACT
mdefine_line|#define&t;W_B_CMDR_RACT&t;0x20
DECL|macro|W_B_CMDR_RRST
mdefine_line|#define&t;W_B_CMDR_RRST&t;0x40
DECL|macro|W_B_CMDR_RACK
mdefine_line|#define&t;W_B_CMDR_RACK&t;0x80
DECL|macro|W_B_MODE_FTS0
mdefine_line|#define&t;W_B_MODE_FTS0&t;0x01
DECL|macro|W_B_MODE_FTS1
mdefine_line|#define&t;W_B_MODE_FTS1&t;0x02
DECL|macro|W_B_MODE_SW56
mdefine_line|#define&t;W_B_MODE_SW56&t;0x04
DECL|macro|W_B_MODE_BSW0
mdefine_line|#define&t;W_B_MODE_BSW0&t;0x08
DECL|macro|W_B_MODE_BSW1
mdefine_line|#define&t;W_B_MODE_BSW1&t;0x10
DECL|macro|W_B_MODE_EPCM
mdefine_line|#define&t;W_B_MODE_EPCM&t;0x20
DECL|macro|W_B_MODE_ITF
mdefine_line|#define&t;W_B_MODE_ITF&t;0x40
DECL|macro|W_B_MODE_MMS
mdefine_line|#define&t;W_B_MODE_MMS&t;0x80
DECL|macro|W_B_EXI_XDUN
mdefine_line|#define&t;W_B_EXI_XDUN&t;0x01
DECL|macro|W_B_EXI_XFR
mdefine_line|#define&t;W_B_EXI_XFR&t;0x02
DECL|macro|W_B_EXI_RDOV
mdefine_line|#define&t;W_B_EXI_RDOV&t;0x10
DECL|macro|W_B_EXI_RME
mdefine_line|#define&t;W_B_EXI_RME&t;0x20
DECL|macro|W_B_EXI_RMR
mdefine_line|#define&t;W_B_EXI_RMR&t;0x40
DECL|macro|W_B_STAR_XBZ
mdefine_line|#define&t;W_B_STAR_XBZ&t;0x01
DECL|macro|W_B_STAR_XDOW
mdefine_line|#define&t;W_B_STAR_XDOW&t;0x04
DECL|macro|W_B_STAR_RMB
mdefine_line|#define&t;W_B_STAR_RMB&t;0x10
DECL|macro|W_B_STAR_CRCE
mdefine_line|#define&t;W_B_STAR_CRCE&t;0x20
DECL|macro|W_B_STAR_RDOV
mdefine_line|#define&t;W_B_STAR_RDOV&t;0x40
DECL|macro|W_B_RBCH_LOV
mdefine_line|#define&t;W_B_RBCH_LOV&t;0x20
multiline_comment|/* W6692 Layer1 commands */
DECL|macro|W_L1CMD_ECK
mdefine_line|#define&t;W_L1CMD_ECK&t;0x00
DECL|macro|W_L1CMD_RST
mdefine_line|#define W_L1CMD_RST&t;0x01
DECL|macro|W_L1CMD_SCP
mdefine_line|#define W_L1CMD_SCP&t;0x04
DECL|macro|W_L1CMD_SSP
mdefine_line|#define W_L1CMD_SSP&t;0x02
DECL|macro|W_L1CMD_AR8
mdefine_line|#define W_L1CMD_AR8&t;0x08
DECL|macro|W_L1CMD_AR10
mdefine_line|#define W_L1CMD_AR10&t;0x09
DECL|macro|W_L1CMD_EAL
mdefine_line|#define W_L1CMD_EAL&t;0x0a
DECL|macro|W_L1CMD_DRC
mdefine_line|#define W_L1CMD_DRC&t;0x0f
multiline_comment|/* W6692 Layer1 indications */
DECL|macro|W_L1IND_CE
mdefine_line|#define W_L1IND_CE&t;0x07
DECL|macro|W_L1IND_DRD
mdefine_line|#define W_L1IND_DRD&t;0x00
DECL|macro|W_L1IND_LD
mdefine_line|#define W_L1IND_LD&t;0x04
DECL|macro|W_L1IND_ARD
mdefine_line|#define W_L1IND_ARD&t;0x08
DECL|macro|W_L1IND_TI
mdefine_line|#define W_L1IND_TI&t;0x0a
DECL|macro|W_L1IND_ATI
mdefine_line|#define W_L1IND_ATI&t;0x0b
DECL|macro|W_L1IND_AI8
mdefine_line|#define W_L1IND_AI8&t;0x0c
DECL|macro|W_L1IND_AI10
mdefine_line|#define W_L1IND_AI10&t;0x0d
DECL|macro|W_L1IND_CD
mdefine_line|#define W_L1IND_CD&t;0x0f
multiline_comment|/* FIFO thresholds */
DECL|macro|W_D_FIFO_THRESH
mdefine_line|#define W_D_FIFO_THRESH&t;64
DECL|macro|W_B_FIFO_THRESH
mdefine_line|#define W_B_FIFO_THRESH&t;64
eof
