multiline_comment|/* $Id: jade.h,v 1.3.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * JADE specific defines&n; *&n; * Author       Roland Klabunde&n; * Copyright    by Roland Klabunde   &lt;R.Klabunde@Berkom.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/* All Registers original Siemens Spec  */
macro_line|#ifndef&t;__JADE_H__
DECL|macro|__JADE_H__
mdefine_line|#define&t;__JADE_H__
multiline_comment|/* Special registers for access to indirect accessible JADE regs */
DECL|macro|DIRECT_IO_JADE
mdefine_line|#define&t;DIRECT_IO_JADE&t;0x0000&t;/* Jade direct io access area */
DECL|macro|COMM_JADE
mdefine_line|#define&t;COMM_JADE&t;0x0040&t;/* Jade communication area */&t;   &t;
multiline_comment|/********************************************************************/
multiline_comment|/* JADE-HDLC registers         &t;&t;&t;&t;&t;&t;&t;&t;&t;    */
multiline_comment|/********************************************************************/
DECL|macro|jade_HDLC_RFIFO
mdefine_line|#define jade_HDLC_RFIFO&t;   &t;&t;&t;&t;0x00&t;&t;&t;&t;   /* R */
DECL|macro|jade_HDLC_XFIFO
mdefine_line|#define jade_HDLC_XFIFO&t;   &t;&t;&t;&t;0x00&t;&t;&t;&t;   /* W */
DECL|macro|jade_HDLC_STAR
mdefine_line|#define&t;jade_HDLC_STAR&t;   &t;&t;&t;&t;0x20&t;&t;&t;&t;   /* R */
DECL|macro|jadeSTAR_XDOV
mdefine_line|#define&t;jadeSTAR_XDOV&t;&t;&t;&t;0x80
DECL|macro|jadeSTAR_XFW
mdefine_line|#define&t;jadeSTAR_XFW &t;&t;&t;&t;0x40 /* Does not work*/
DECL|macro|jadeSTAR_XCEC
mdefine_line|#define&t;jadeSTAR_XCEC &t;&t;&t;&t;0x20
DECL|macro|jadeSTAR_RCEC
mdefine_line|#define&t;jadeSTAR_RCEC&t;&t;&t;&t;0x10
DECL|macro|jadeSTAR_BSY
mdefine_line|#define&t;jadeSTAR_BSY &t;&t;&t;&t;0x08
DECL|macro|jadeSTAR_RNA
mdefine_line|#define&t;jadeSTAR_RNA &t;&t;&t;&t;0x04
DECL|macro|jadeSTAR_STR
mdefine_line|#define&t;jadeSTAR_STR &t;&t;&t;&t;0x02
DECL|macro|jadeSTAR_STX
mdefine_line|#define&t;jadeSTAR_STX&t;&t;&t;&t;0x01
DECL|macro|jade_HDLC_XCMD
mdefine_line|#define&t;jade_HDLC_XCMD&t;   &t;&t;&t;&t;0x20&t;&t;&t;&t;   /* W */
DECL|macro|jadeXCMD_XF
mdefine_line|#define&t;jadeXCMD_XF&t;&t;&t;&t;0x80
DECL|macro|jadeXCMD_XME
mdefine_line|#define&t;jadeXCMD_XME&t;&t;&t;&t;0x40
DECL|macro|jadeXCMD_XRES
mdefine_line|#define&t;jadeXCMD_XRES&t;&t;&t;&t;0x20
DECL|macro|jadeXCMD_STX
mdefine_line|#define&t;jadeXCMD_STX&t;&t;&t;&t;0x01
DECL|macro|jade_HDLC_RSTA
mdefine_line|#define&t;jade_HDLC_RSTA&t;   &t;&t;&t;&t;0x21&t;&t;&t;&t;   /* R */
DECL|macro|jadeRSTA_VFR
mdefine_line|#define&t;jadeRSTA_VFR&t;&t;&t;&t;0x80
DECL|macro|jadeRSTA_RDO
mdefine_line|#define&t;jadeRSTA_RDO&t;&t;&t;&t;0x40
DECL|macro|jadeRSTA_CRC
mdefine_line|#define&t;jadeRSTA_CRC&t;&t;&t;&t;0x20
DECL|macro|jadeRSTA_RAB
mdefine_line|#define&t;jadeRSTA_RAB&t;&t;&t;&t;0x10
DECL|macro|jadeRSTA_MASK
mdefine_line|#define&t;jadeRSTA_MASK&t;&t;&t;   &t;0xF0
DECL|macro|jade_HDLC_MODE
mdefine_line|#define&t;jade_HDLC_MODE&t;&t;&t;&t;&t;0x22&t;&t;&t;&t;   /* RW*/
DECL|macro|jadeMODE_TMO
mdefine_line|#define&t;jadeMODE_TMO&t;&t;&t;&t;0x80
DECL|macro|jadeMODE_RAC
mdefine_line|#define&t;jadeMODE_RAC&t;&t;&t;&t;0x40
DECL|macro|jadeMODE_XAC
mdefine_line|#define&t;jadeMODE_XAC&t;&t;&t;&t;0x20
DECL|macro|jadeMODE_TLP
mdefine_line|#define&t;jadeMODE_TLP&t;&t;&t;&t;0x10
DECL|macro|jadeMODE_ERFS
mdefine_line|#define&t;jadeMODE_ERFS&t;&t;&t;&t;0x02
DECL|macro|jadeMODE_ETFS
mdefine_line|#define&t;jadeMODE_ETFS&t;&t;&t;&t;0x01
DECL|macro|jade_HDLC_RBCH
mdefine_line|#define&t;jade_HDLC_RBCH&t;&t;&t;&t;&t;0x24&t;&t;&t;&t;   /* R */
DECL|macro|jade_HDLC_RBCL
mdefine_line|#define&t;jade_HDLC_RBCL&t; &t;&t;&t;&t;0x25&t;&t;&t;&t;   /* R */
DECL|macro|jade_HDLC_RCMD
mdefine_line|#define&t;jade_HDLC_RCMD&t; &t;&t;&t;&t;0x25&t;&t;&t;&t;   /* W */
DECL|macro|jadeRCMD_RMC
mdefine_line|#define&t;jadeRCMD_RMC &t;&t;&t;&t;0x80
DECL|macro|jadeRCMD_RRES
mdefine_line|#define&t;jadeRCMD_RRES&t;&t;&t;&t;0x40
DECL|macro|jadeRCMD_RMD
mdefine_line|#define&t;jadeRCMD_RMD&t;&t;&t;&t;0x20
DECL|macro|jadeRCMD_STR
mdefine_line|#define&t;jadeRCMD_STR&t;&t;&t;&t;0x02
DECL|macro|jade_HDLC_CCR0
mdefine_line|#define&t;jade_HDLC_CCR0&t;&t;&t;&t;&t;0x26&t;&t;&t;&t;   /* RW*/
DECL|macro|jadeCCR0_PU
mdefine_line|#define&t;jadeCCR0_PU  &t;&t;&t;&t;0x80
DECL|macro|jadeCCR0_ITF
mdefine_line|#define&t;jadeCCR0_ITF&t;&t;&t;&t;0x40
DECL|macro|jadeCCR0_C32
mdefine_line|#define&t;jadeCCR0_C32&t;&t;&t;&t;0x20
DECL|macro|jadeCCR0_CRL
mdefine_line|#define&t;jadeCCR0_CRL&t;&t;&t;&t;0x10
DECL|macro|jadeCCR0_RCRC
mdefine_line|#define&t;jadeCCR0_RCRC&t;&t;&t;&t;0x08
DECL|macro|jadeCCR0_XCRC
mdefine_line|#define&t;jadeCCR0_XCRC&t;&t;&t;&t;0x04
DECL|macro|jadeCCR0_RMSB
mdefine_line|#define&t;jadeCCR0_RMSB&t;&t;&t;&t;0x02
DECL|macro|jadeCCR0_XMSB
mdefine_line|#define&t;jadeCCR0_XMSB&t;&t;&t;&t;0x01
DECL|macro|jade_HDLC_CCR1
mdefine_line|#define&t;jade_HDLC_CCR1&t;&t;&t;&t;&t;0x27&t;&t;&t;&t;   /* RW*/
DECL|macro|jadeCCR1_RCS0
mdefine_line|#define&t;jadeCCR1_RCS0&t;&t;&t;&t;0x80
DECL|macro|jadeCCR1_RCONT
mdefine_line|#define&t;jadeCCR1_RCONT&t;&t;&t;&t;0x40
DECL|macro|jadeCCR1_RFDIS
mdefine_line|#define&t;jadeCCR1_RFDIS&t;&t;&t;&t;0x20
DECL|macro|jadeCCR1_XCS0
mdefine_line|#define&t;jadeCCR1_XCS0&t;&t;&t;&t;0x10
DECL|macro|jadeCCR1_XCONT
mdefine_line|#define&t;jadeCCR1_XCONT&t;&t;&t;&t;0x08
DECL|macro|jadeCCR1_XFDIS
mdefine_line|#define&t;jadeCCR1_XFDIS&t;&t;&t;&t;0x04
DECL|macro|jade_HDLC_TSAR
mdefine_line|#define&t;jade_HDLC_TSAR&t;&t;&t;&t;&t;0x28&t;&t;&t;&t;   /* RW*/
DECL|macro|jade_HDLC_TSAX
mdefine_line|#define&t;jade_HDLC_TSAX&t;&t;&t;&t;&t;0x29&t;&t;&t;&t;   /* RW*/
DECL|macro|jade_HDLC_RCCR
mdefine_line|#define&t;jade_HDLC_RCCR&t;&t;&t;&t;&t;0x2A&t;&t;&t;&t;   /* RW*/
DECL|macro|jade_HDLC_XCCR
mdefine_line|#define&t;jade_HDLC_XCCR&t;&t;&t;&t;&t;0x2B&t;&t;&t;&t;   /* RW*/
DECL|macro|jade_HDLC_ISR
mdefine_line|#define&t;jade_HDLC_ISR &t;&t;&t;&t;&t;0x2C&t;&t;&t;&t;   /* R */
DECL|macro|jade_HDLC_IMR
mdefine_line|#define&t;jade_HDLC_IMR &t;&t;&t;&t;&t;0x2C&t;&t;&t;&t;   /* W */
DECL|macro|jadeISR_RME
mdefine_line|#define&t;jadeISR_RME&t;&t;&t;&t;&t;0x80
DECL|macro|jadeISR_RPF
mdefine_line|#define&t;jadeISR_RPF&t;&t;&t;&t;&t;0x40
DECL|macro|jadeISR_RFO
mdefine_line|#define&t;jadeISR_RFO&t;&t;&t;&t;&t;0x20
DECL|macro|jadeISR_XPR
mdefine_line|#define&t;jadeISR_XPR&t;&t;&t;&t;&t;0x10
DECL|macro|jadeISR_XDU
mdefine_line|#define&t;jadeISR_XDU&t;&t;&t;&t;&t;0x08
DECL|macro|jadeISR_ALLS
mdefine_line|#define&t;jadeISR_ALLS&t;&t;&t;&t;0x04
DECL|macro|jade_INT
mdefine_line|#define jade_INT            &t;&t;&t;0x75
DECL|macro|jadeINT_HDLC1
mdefine_line|#define jadeINT_HDLC1   &t;&t;&t;0x02
DECL|macro|jadeINT_HDLC2
mdefine_line|#define jadeINT_HDLC2   &t;&t;&t;0x01
DECL|macro|jadeINT_DSP
mdefine_line|#define jadeINT_DSP&t;&t;&t;&t;0x04
DECL|macro|jade_INTR
mdefine_line|#define jade_INTR            &t;&t;&t;0x70
multiline_comment|/********************************************************************/
multiline_comment|/* Indirect accessible JADE registers of common interest&t;&t;   &t;*/
multiline_comment|/********************************************************************/
DECL|macro|jade_CHIPVERSIONNR
mdefine_line|#define&t;jade_CHIPVERSIONNR&t;&t;&t;&t;0x00 /* Does not work*/
DECL|macro|jade_HDLCCNTRACCESS
mdefine_line|#define&t;jade_HDLCCNTRACCESS&t;&t;&t;&t;0x10&t;&t;
DECL|macro|jadeINDIRECT_HAH1
mdefine_line|#define&t;jadeINDIRECT_HAH1&t;&t;&t;0x02
DECL|macro|jadeINDIRECT_HAH2
mdefine_line|#define&t;jadeINDIRECT_HAH2&t;&t;&t;0x01
DECL|macro|jade_HDLC1SERRXPATH
mdefine_line|#define&t;jade_HDLC1SERRXPATH&t;&t;&t;&t;0x1D
DECL|macro|jade_HDLC1SERTXPATH
mdefine_line|#define&t;jade_HDLC1SERTXPATH&t;&t;&t;&t;0x1E
DECL|macro|jade_HDLC2SERRXPATH
mdefine_line|#define&t;jade_HDLC2SERRXPATH&t;&t;&t;&t;0x1F
DECL|macro|jade_HDLC2SERTXPATH
mdefine_line|#define&t;jade_HDLC2SERTXPATH&t;&t;&t;&t;0x20
DECL|macro|jadeINDIRECT_SLIN1
mdefine_line|#define&t;jadeINDIRECT_SLIN1&t;&t;&t;0x10
DECL|macro|jadeINDIRECT_SLIN0
mdefine_line|#define&t;jadeINDIRECT_SLIN0&t;&t;&t;0x08
DECL|macro|jadeINDIRECT_LMOD1
mdefine_line|#define&t;jadeINDIRECT_LMOD1&t;&t;&t;0x04
DECL|macro|jadeINDIRECT_LMOD0
mdefine_line|#define&t;jadeINDIRECT_LMOD0&t;&t;&t;0x02
DECL|macro|jadeINDIRECT_HHR
mdefine_line|#define&t;jadeINDIRECT_HHR&t;&t;&t;0x01
DECL|macro|jadeINDIRECT_HHX
mdefine_line|#define&t;jadeINDIRECT_HHX&t;&t;&t;0x01
DECL|macro|jade_RXAUDIOCH1CFG
mdefine_line|#define&t;jade_RXAUDIOCH1CFG&t;&t;&t;&t;0x11
DECL|macro|jade_RXAUDIOCH2CFG
mdefine_line|#define&t;jade_RXAUDIOCH2CFG&t;&t;&t;&t;0x14
DECL|macro|jade_TXAUDIOCH1CFG
mdefine_line|#define&t;jade_TXAUDIOCH1CFG&t;&t;&t;&t;0x17
DECL|macro|jade_TXAUDIOCH2CFG
mdefine_line|#define&t;jade_TXAUDIOCH2CFG&t;&t;&t;&t;0x1A
r_extern
r_int
id|JadeVersion
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_void
id|jade_sched_event
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|event
)paren
suffix:semicolon
r_extern
r_void
id|modejade
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|mode
comma
r_int
id|bc
)paren
suffix:semicolon
r_extern
r_void
id|clear_pending_jade_ints
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|initjade
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
macro_line|#endif&t;/* __JADE_H__ */
eof
