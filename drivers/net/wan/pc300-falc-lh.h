multiline_comment|/*&n; * falc.h&t;Description of the Siemens FALC T1/E1 framer.&n; *&n; * Author:&t;Ivan Passos &lt;ivan@cyclades.com&gt;&n; *&n; * Copyright:&t;(c) 2000-2001 Cyclades Corp.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; * $Log: falc-lh.h,v $&n; * Revision 3.1  2001/06/15 12:41:10  regina&n; * upping major version number&n; *&n; * Revision 1.1.1.1  2001/06/13 20:24:47  daniela&n; * PC300 initial CVS version (3.4.0-pre1)&n; *&n; * Revision 1.1 2000/05/15 ivan&n; * Included DJA bits for the LIM2 register.&n; *&n; * Revision 1.0 2000/02/22 ivan&n; * Initial version.&n; *&n; */
macro_line|#ifndef _FALC_LH_H
DECL|macro|_FALC_LH_H
mdefine_line|#define _FALC_LH_H
DECL|macro|NUM_OF_T1_CHANNELS
mdefine_line|#define NUM_OF_T1_CHANNELS&t;24
DECL|macro|NUM_OF_E1_CHANNELS
mdefine_line|#define NUM_OF_E1_CHANNELS&t;32
multiline_comment|/*&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;  FALC Register Bits (Transmit Mode)  &lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt; */
multiline_comment|/* CMDR (Command Register)&n;   ---------------- E1 &amp; T1 ------------------------------ */
DECL|macro|CMDR_RMC
mdefine_line|#define CMDR_RMC&t;0x80
DECL|macro|CMDR_RRES
mdefine_line|#define CMDR_RRES&t;0x40
DECL|macro|CMDR_XREP
mdefine_line|#define CMDR_XREP&t;0x20
DECL|macro|CMDR_XRES
mdefine_line|#define CMDR_XRES&t;0x10
DECL|macro|CMDR_XHF
mdefine_line|#define CMDR_XHF&t;0x08
DECL|macro|CMDR_XTF
mdefine_line|#define CMDR_XTF&t;0x04
DECL|macro|CMDR_XME
mdefine_line|#define CMDR_XME&t;0x02
DECL|macro|CMDR_SRES
mdefine_line|#define CMDR_SRES&t;0x01
multiline_comment|/* MODE (Mode Register)&n;   ----------------- E1 &amp; T1 ----------------------------- */
DECL|macro|MODE_MDS2
mdefine_line|#define MODE_MDS2&t;0x80
DECL|macro|MODE_MDS1
mdefine_line|#define MODE_MDS1&t;0x40
DECL|macro|MODE_MDS0
mdefine_line|#define MODE_MDS0&t;0x20
DECL|macro|MODE_BRAC
mdefine_line|#define MODE_BRAC&t;0x10
DECL|macro|MODE_HRAC
mdefine_line|#define MODE_HRAC&t;0x08
multiline_comment|/* IPC (Interrupt Port Configuration)&n;   ----------------- E1 &amp; T1 ----------------------------- */
DECL|macro|IPC_VIS
mdefine_line|#define IPC_VIS&t;&t;0x80
DECL|macro|IPC_SCI
mdefine_line|#define IPC_SCI&t;&t;0x04
DECL|macro|IPC_IC1
mdefine_line|#define IPC_IC1&t;&t;0x02
DECL|macro|IPC_IC0
mdefine_line|#define IPC_IC0&t;&t;0x01
multiline_comment|/* CCR1 (Common Configuration Register 1)&n;   ----------------- E1 &amp; T1 ----------------------------- */
DECL|macro|CCR1_SFLG
mdefine_line|#define CCR1_SFLG       0x80
DECL|macro|CCR1_XTS16RA
mdefine_line|#define CCR1_XTS16RA    0x40
DECL|macro|CCR1_BRM
mdefine_line|#define CCR1_BRM        0x40
DECL|macro|CCR1_CASSYM
mdefine_line|#define CCR1_CASSYM     0x20
DECL|macro|CCR1_EDLX
mdefine_line|#define CCR1_EDLX       0x20
DECL|macro|CCR1_EITS
mdefine_line|#define CCR1_EITS       0x10
DECL|macro|CCR1_ITF
mdefine_line|#define CCR1_ITF        0x08
DECL|macro|CCR1_RFT1
mdefine_line|#define CCR1_RFT1       0x02
DECL|macro|CCR1_RFT0
mdefine_line|#define CCR1_RFT0       0x01
multiline_comment|/* CCR3 (Common Configuration Register 3)&n;   ---------------- E1 &amp; T1 ------------------------------ */
DECL|macro|CCR3_PRE1
mdefine_line|#define CCR3_PRE1       0x80
DECL|macro|CCR3_PRE0
mdefine_line|#define CCR3_PRE0       0x40
DECL|macro|CCR3_EPT
mdefine_line|#define CCR3_EPT        0x20
DECL|macro|CCR3_RADD
mdefine_line|#define CCR3_RADD       0x10
DECL|macro|CCR3_RCRC
mdefine_line|#define CCR3_RCRC       0x04
DECL|macro|CCR3_XCRC
mdefine_line|#define CCR3_XCRC       0x02
multiline_comment|/* RTR1-4 (Receive Timeslot Register 1-4)&n;   ---------------- E1 &amp; T1 ------------------------------ */
DECL|macro|RTR1_TS0
mdefine_line|#define RTR1_TS0        0x80
DECL|macro|RTR1_TS1
mdefine_line|#define RTR1_TS1        0x40
DECL|macro|RTR1_TS2
mdefine_line|#define RTR1_TS2        0x20
DECL|macro|RTR1_TS3
mdefine_line|#define RTR1_TS3        0x10
DECL|macro|RTR1_TS4
mdefine_line|#define RTR1_TS4        0x08
DECL|macro|RTR1_TS5
mdefine_line|#define RTR1_TS5        0x04
DECL|macro|RTR1_TS6
mdefine_line|#define RTR1_TS6        0x02
DECL|macro|RTR1_TS7
mdefine_line|#define RTR1_TS7        0x01
DECL|macro|RTR2_TS8
mdefine_line|#define RTR2_TS8        0x80
DECL|macro|RTR2_TS9
mdefine_line|#define RTR2_TS9        0x40
DECL|macro|RTR2_TS10
mdefine_line|#define RTR2_TS10       0x20
DECL|macro|RTR2_TS11
mdefine_line|#define RTR2_TS11       0x10
DECL|macro|RTR2_TS12
mdefine_line|#define RTR2_TS12       0x08
DECL|macro|RTR2_TS13
mdefine_line|#define RTR2_TS13       0x04
DECL|macro|RTR2_TS14
mdefine_line|#define RTR2_TS14       0x02
DECL|macro|RTR2_TS15
mdefine_line|#define RTR2_TS15       0x01
DECL|macro|RTR3_TS16
mdefine_line|#define RTR3_TS16       0x80
DECL|macro|RTR3_TS17
mdefine_line|#define RTR3_TS17       0x40
DECL|macro|RTR3_TS18
mdefine_line|#define RTR3_TS18       0x20
DECL|macro|RTR3_TS19
mdefine_line|#define RTR3_TS19       0x10
DECL|macro|RTR3_TS20
mdefine_line|#define RTR3_TS20       0x08
DECL|macro|RTR3_TS21
mdefine_line|#define RTR3_TS21       0x04
DECL|macro|RTR3_TS22
mdefine_line|#define RTR3_TS22       0x02
DECL|macro|RTR3_TS23
mdefine_line|#define RTR3_TS23       0x01
DECL|macro|RTR4_TS24
mdefine_line|#define RTR4_TS24       0x80
DECL|macro|RTR4_TS25
mdefine_line|#define RTR4_TS25       0x40
DECL|macro|RTR4_TS26
mdefine_line|#define RTR4_TS26       0x20
DECL|macro|RTR4_TS27
mdefine_line|#define RTR4_TS27       0x10
DECL|macro|RTR4_TS28
mdefine_line|#define RTR4_TS28       0x08
DECL|macro|RTR4_TS29
mdefine_line|#define RTR4_TS29       0x04
DECL|macro|RTR4_TS30
mdefine_line|#define RTR4_TS30       0x02
DECL|macro|RTR4_TS31
mdefine_line|#define RTR4_TS31       0x01
multiline_comment|/* TTR1-4 (Transmit Timeslot Register 1-4)&n;   ---------------- E1 &amp; T1 ------------------------------ */
DECL|macro|TTR1_TS0
mdefine_line|#define TTR1_TS0        0x80
DECL|macro|TTR1_TS1
mdefine_line|#define TTR1_TS1        0x40
DECL|macro|TTR1_TS2
mdefine_line|#define TTR1_TS2        0x20
DECL|macro|TTR1_TS3
mdefine_line|#define TTR1_TS3        0x10
DECL|macro|TTR1_TS4
mdefine_line|#define TTR1_TS4        0x08
DECL|macro|TTR1_TS5
mdefine_line|#define TTR1_TS5        0x04
DECL|macro|TTR1_TS6
mdefine_line|#define TTR1_TS6        0x02
DECL|macro|TTR1_TS7
mdefine_line|#define TTR1_TS7        0x01
DECL|macro|TTR2_TS8
mdefine_line|#define TTR2_TS8        0x80
DECL|macro|TTR2_TS9
mdefine_line|#define TTR2_TS9        0x40
DECL|macro|TTR2_TS10
mdefine_line|#define TTR2_TS10       0x20
DECL|macro|TTR2_TS11
mdefine_line|#define TTR2_TS11       0x10
DECL|macro|TTR2_TS12
mdefine_line|#define TTR2_TS12       0x08
DECL|macro|TTR2_TS13
mdefine_line|#define TTR2_TS13       0x04
DECL|macro|TTR2_TS14
mdefine_line|#define TTR2_TS14       0x02
DECL|macro|TTR2_TS15
mdefine_line|#define TTR2_TS15       0x01
DECL|macro|TTR3_TS16
mdefine_line|#define TTR3_TS16       0x80
DECL|macro|TTR3_TS17
mdefine_line|#define TTR3_TS17       0x40
DECL|macro|TTR3_TS18
mdefine_line|#define TTR3_TS18       0x20
DECL|macro|TTR3_TS19
mdefine_line|#define TTR3_TS19       0x10
DECL|macro|TTR3_TS20
mdefine_line|#define TTR3_TS20       0x08
DECL|macro|TTR3_TS21
mdefine_line|#define TTR3_TS21       0x04
DECL|macro|TTR3_TS22
mdefine_line|#define TTR3_TS22       0x02
DECL|macro|TTR3_TS23
mdefine_line|#define TTR3_TS23       0x01
DECL|macro|TTR4_TS24
mdefine_line|#define TTR4_TS24       0x80
DECL|macro|TTR4_TS25
mdefine_line|#define TTR4_TS25       0x40
DECL|macro|TTR4_TS26
mdefine_line|#define TTR4_TS26       0x20
DECL|macro|TTR4_TS27
mdefine_line|#define TTR4_TS27       0x10
DECL|macro|TTR4_TS28
mdefine_line|#define TTR4_TS28       0x08
DECL|macro|TTR4_TS29
mdefine_line|#define TTR4_TS29       0x04
DECL|macro|TTR4_TS30
mdefine_line|#define TTR4_TS30       0x02
DECL|macro|TTR4_TS31
mdefine_line|#define TTR4_TS31       0x01
multiline_comment|/* IMR0-4 (Interrupt Mask Register 0-4)&n;&n;   ----------------- E1 &amp; T1 ----------------------------- */
DECL|macro|IMR0_RME
mdefine_line|#define IMR0_RME        0x80
DECL|macro|IMR0_RFS
mdefine_line|#define IMR0_RFS        0x40
DECL|macro|IMR0_T8MS
mdefine_line|#define IMR0_T8MS       0x20
DECL|macro|IMR0_ISF
mdefine_line|#define IMR0_ISF        0x20
DECL|macro|IMR0_RMB
mdefine_line|#define IMR0_RMB        0x10
DECL|macro|IMR0_CASC
mdefine_line|#define IMR0_CASC       0x08
DECL|macro|IMR0_RSC
mdefine_line|#define IMR0_RSC        0x08
DECL|macro|IMR0_CRC6
mdefine_line|#define IMR0_CRC6       0x04
DECL|macro|IMR0_CRC4
mdefine_line|#define IMR0_CRC4       0x04
DECL|macro|IMR0_PDEN
mdefine_line|#define IMR0_PDEN&t;0x02
DECL|macro|IMR0_RPF
mdefine_line|#define IMR0_RPF        0x01
DECL|macro|IMR1_CASE
mdefine_line|#define IMR1_CASE       0x80
DECL|macro|IMR1_RDO
mdefine_line|#define IMR1_RDO        0x40
DECL|macro|IMR1_ALLS
mdefine_line|#define IMR1_ALLS       0x20
DECL|macro|IMR1_XDU
mdefine_line|#define IMR1_XDU        0x10
DECL|macro|IMR1_XMB
mdefine_line|#define IMR1_XMB        0x08
DECL|macro|IMR1_XLSC
mdefine_line|#define IMR1_XLSC       0x02
DECL|macro|IMR1_XPR
mdefine_line|#define IMR1_XPR        0x01
DECL|macro|IMR1_LLBSC
mdefine_line|#define IMR1_LLBSC&t;0x80
DECL|macro|IMR2_FAR
mdefine_line|#define IMR2_FAR        0x80
DECL|macro|IMR2_LFA
mdefine_line|#define IMR2_LFA        0x40
DECL|macro|IMR2_MFAR
mdefine_line|#define IMR2_MFAR       0x20
DECL|macro|IMR2_T400MS
mdefine_line|#define IMR2_T400MS     0x10
DECL|macro|IMR2_LMFA
mdefine_line|#define IMR2_LMFA       0x10
DECL|macro|IMR2_AIS
mdefine_line|#define IMR2_AIS        0x08
DECL|macro|IMR2_LOS
mdefine_line|#define IMR2_LOS        0x04
DECL|macro|IMR2_RAR
mdefine_line|#define IMR2_RAR        0x02
DECL|macro|IMR2_RA
mdefine_line|#define IMR2_RA         0x01
DECL|macro|IMR3_ES
mdefine_line|#define IMR3_ES         0x80
DECL|macro|IMR3_SEC
mdefine_line|#define IMR3_SEC        0x40
DECL|macro|IMR3_LMFA16
mdefine_line|#define IMR3_LMFA16     0x20
DECL|macro|IMR3_AIS16
mdefine_line|#define IMR3_AIS16      0x10
DECL|macro|IMR3_RA16
mdefine_line|#define IMR3_RA16       0x08
DECL|macro|IMR3_API
mdefine_line|#define IMR3_API        0x04
DECL|macro|IMR3_XSLP
mdefine_line|#define IMR3_XSLP       0x20
DECL|macro|IMR3_XSLN
mdefine_line|#define IMR3_XSLN       0x10
DECL|macro|IMR3_LLBSC
mdefine_line|#define IMR3_LLBSC      0x08
DECL|macro|IMR3_XRS
mdefine_line|#define IMR3_XRS        0x04
DECL|macro|IMR3_SLN
mdefine_line|#define IMR3_SLN        0x02
DECL|macro|IMR3_SLP
mdefine_line|#define IMR3_SLP        0x01
DECL|macro|IMR4_LFA
mdefine_line|#define IMR4_LFA        0x80
DECL|macro|IMR4_FER
mdefine_line|#define IMR4_FER        0x40
DECL|macro|IMR4_CER
mdefine_line|#define IMR4_CER        0x20
DECL|macro|IMR4_AIS
mdefine_line|#define IMR4_AIS        0x10
DECL|macro|IMR4_LOS
mdefine_line|#define IMR4_LOS        0x08
DECL|macro|IMR4_CVE
mdefine_line|#define IMR4_CVE        0x04
DECL|macro|IMR4_SLIP
mdefine_line|#define IMR4_SLIP       0x02
DECL|macro|IMR4_EBE
mdefine_line|#define IMR4_EBE        0x01
multiline_comment|/* FMR0-5 for E1 and T1  (Framer Mode Register ) */
DECL|macro|FMR0_XC1
mdefine_line|#define FMR0_XC1        0x80
DECL|macro|FMR0_XC0
mdefine_line|#define FMR0_XC0        0x40
DECL|macro|FMR0_RC1
mdefine_line|#define FMR0_RC1        0x20
DECL|macro|FMR0_RC0
mdefine_line|#define FMR0_RC0        0x10
DECL|macro|FMR0_EXTD
mdefine_line|#define FMR0_EXTD       0x08
DECL|macro|FMR0_ALM
mdefine_line|#define FMR0_ALM        0x04
DECL|macro|E1_FMR0_FRS
mdefine_line|#define E1_FMR0_FRS     0x02
DECL|macro|T1_FMR0_FRS
mdefine_line|#define T1_FMR0_FRS     0x08
DECL|macro|FMR0_SRAF
mdefine_line|#define FMR0_SRAF       0x04
DECL|macro|FMR0_EXLS
mdefine_line|#define FMR0_EXLS       0x02
DECL|macro|FMR0_SIM
mdefine_line|#define FMR0_SIM        0x01
DECL|macro|FMR1_MFCS
mdefine_line|#define FMR1_MFCS       0x80
DECL|macro|FMR1_AFR
mdefine_line|#define FMR1_AFR        0x40
DECL|macro|FMR1_ENSA
mdefine_line|#define FMR1_ENSA       0x20
DECL|macro|FMR1_CTM
mdefine_line|#define FMR1_CTM        0x80
DECL|macro|FMR1_SIGM
mdefine_line|#define FMR1_SIGM       0x40
DECL|macro|FMR1_EDL
mdefine_line|#define FMR1_EDL        0x20
DECL|macro|FMR1_PMOD
mdefine_line|#define FMR1_PMOD       0x10
DECL|macro|FMR1_XFS
mdefine_line|#define FMR1_XFS        0x08
DECL|macro|FMR1_CRC
mdefine_line|#define FMR1_CRC        0x08
DECL|macro|FMR1_ECM
mdefine_line|#define FMR1_ECM        0x04
DECL|macro|FMR1_IMOD
mdefine_line|#define FMR1_IMOD       0x02
DECL|macro|FMR1_XAIS
mdefine_line|#define FMR1_XAIS       0x01
DECL|macro|FMR2_RFS1
mdefine_line|#define FMR2_RFS1       0x80
DECL|macro|FMR2_RFS0
mdefine_line|#define FMR2_RFS0       0x40
DECL|macro|FMR2_MCSP
mdefine_line|#define FMR2_MCSP&t;0x40
DECL|macro|FMR2_RTM
mdefine_line|#define FMR2_RTM        0x20
DECL|macro|FMR2_SSP
mdefine_line|#define FMR2_SSP        0x20
DECL|macro|FMR2_DAIS
mdefine_line|#define FMR2_DAIS       0x10
DECL|macro|FMR2_SAIS
mdefine_line|#define FMR2_SAIS       0x08
DECL|macro|FMR2_PLB
mdefine_line|#define FMR2_PLB        0x04
DECL|macro|FMR2_AXRA
mdefine_line|#define FMR2_AXRA       0x02
DECL|macro|FMR2_ALMF
mdefine_line|#define FMR2_ALMF       0x01
DECL|macro|FMR2_EXZE
mdefine_line|#define FMR2_EXZE       0x01
DECL|macro|LOOP_RTM
mdefine_line|#define LOOP_RTM&t;0x40
DECL|macro|LOOP_SFM
mdefine_line|#define LOOP_SFM&t;0x40
DECL|macro|LOOP_ECLB
mdefine_line|#define LOOP_ECLB&t;0x20
DECL|macro|LOOP_CLA
mdefine_line|#define LOOP_CLA&t;0x1f
multiline_comment|/*--------------------- E1 ----------------------------*/
DECL|macro|FMR3_XLD
mdefine_line|#define FMR3_XLD&t;0x20
DECL|macro|FMR3_XLU
mdefine_line|#define FMR3_XLU&t;0x10
multiline_comment|/*--------------------- T1 ----------------------------*/
DECL|macro|FMR4_AIS3
mdefine_line|#define FMR4_AIS3       0x80
DECL|macro|FMR4_TM
mdefine_line|#define FMR4_TM         0x40
DECL|macro|FMR4_XRA
mdefine_line|#define FMR4_XRA        0x20
DECL|macro|FMR4_SSC1
mdefine_line|#define FMR4_SSC1       0x10
DECL|macro|FMR4_SSC0
mdefine_line|#define FMR4_SSC0       0x08
DECL|macro|FMR4_AUTO
mdefine_line|#define FMR4_AUTO       0x04
DECL|macro|FMR4_FM1
mdefine_line|#define FMR4_FM1        0x02
DECL|macro|FMR4_FM0
mdefine_line|#define FMR4_FM0        0x01
DECL|macro|FMR5_SRS
mdefine_line|#define FMR5_SRS        0x80
DECL|macro|FMR5_EIBR
mdefine_line|#define FMR5_EIBR       0x40
DECL|macro|FMR5_XLD
mdefine_line|#define FMR5_XLD        0x20
DECL|macro|FMR5_XLU
mdefine_line|#define FMR5_XLU        0x10
multiline_comment|/* LOOP (Channel Loop Back)&n;&n;   ------------------ E1 &amp; T1 ---------------------------- */
DECL|macro|LOOP_SFM
mdefine_line|#define LOOP_SFM        0x40
DECL|macro|LOOP_ECLB
mdefine_line|#define LOOP_ECLB       0x20
DECL|macro|LOOP_CLA4
mdefine_line|#define LOOP_CLA4       0x10
DECL|macro|LOOP_CLA3
mdefine_line|#define LOOP_CLA3       0x08
DECL|macro|LOOP_CLA2
mdefine_line|#define LOOP_CLA2       0x04
DECL|macro|LOOP_CLA1
mdefine_line|#define LOOP_CLA1       0x02
DECL|macro|LOOP_CLA0
mdefine_line|#define LOOP_CLA0       0x01
multiline_comment|/* XSW (Transmit Service Word Pulseframe)&n;&n;   ------------------- E1 --------------------------- */
DECL|macro|XSW_XSIS
mdefine_line|#define XSW_XSIS        0x80
DECL|macro|XSW_XTM
mdefine_line|#define XSW_XTM         0x40
DECL|macro|XSW_XRA
mdefine_line|#define XSW_XRA         0x20
DECL|macro|XSW_XY0
mdefine_line|#define XSW_XY0         0x10
DECL|macro|XSW_XY1
mdefine_line|#define XSW_XY1         0x08
DECL|macro|XSW_XY2
mdefine_line|#define XSW_XY2         0x04
DECL|macro|XSW_XY3
mdefine_line|#define XSW_XY3         0x02
DECL|macro|XSW_XY4
mdefine_line|#define XSW_XY4         0x01
multiline_comment|/* XSP (Transmit Spare Bits)&n;&n;   ------------------- E1 --------------------------- */
DECL|macro|XSP_XAP
mdefine_line|#define XSP_XAP         0x80
DECL|macro|XSP_CASEN
mdefine_line|#define XSP_CASEN       0x40
DECL|macro|XSP_TT0
mdefine_line|#define XSP_TT0         0x20
DECL|macro|XSP_EBP
mdefine_line|#define XSP_EBP         0x10
DECL|macro|XSP_AXS
mdefine_line|#define XSP_AXS         0x08
DECL|macro|XSP_XSIF
mdefine_line|#define XSP_XSIF        0x04
DECL|macro|XSP_XS13
mdefine_line|#define XSP_XS13        0x02
DECL|macro|XSP_XS15
mdefine_line|#define XSP_XS15        0x01
multiline_comment|/* XC0/1 (Transmit Control 0/1)&n;   ------------------ E1 &amp; T1 ---------------------------- */
DECL|macro|XC0_SA8E
mdefine_line|#define XC0_SA8E        0x80
DECL|macro|XC0_SA7E
mdefine_line|#define XC0_SA7E        0x40
DECL|macro|XC0_SA6E
mdefine_line|#define XC0_SA6E        0x20
DECL|macro|XC0_SA5E
mdefine_line|#define XC0_SA5E        0x10
DECL|macro|XC0_SA4E
mdefine_line|#define XC0_SA4E        0x08
DECL|macro|XC0_BRM
mdefine_line|#define XC0_BRM         0x80
DECL|macro|XC0_MFBS
mdefine_line|#define XC0_MFBS        0x40
DECL|macro|XC0_SFRZ
mdefine_line|#define XC0_SFRZ        0x10
DECL|macro|XC0_XCO2
mdefine_line|#define XC0_XCO2        0x04
DECL|macro|XC0_XCO1
mdefine_line|#define XC0_XCO1        0x02
DECL|macro|XC0_XCO0
mdefine_line|#define XC0_XCO0        0x01
DECL|macro|XC1_XTO5
mdefine_line|#define XC1_XTO5        0x20
DECL|macro|XC1_XTO4
mdefine_line|#define XC1_XTO4        0x10
DECL|macro|XC1_XTO3
mdefine_line|#define XC1_XTO3        0x08
DECL|macro|XC1_XTO2
mdefine_line|#define XC1_XTO2        0x04
DECL|macro|XC1_XTO1
mdefine_line|#define XC1_XTO1        0x02
DECL|macro|XC1_XTO0
mdefine_line|#define XC1_XTO0        0x01
multiline_comment|/* RC0/1 (Receive Control 0/1)&n;   ------------------ E1 &amp; T1 ---------------------------- */
DECL|macro|RC0_SICS
mdefine_line|#define RC0_SICS        0x40
DECL|macro|RC0_CRCI
mdefine_line|#define RC0_CRCI        0x20
DECL|macro|RC0_XCRCI
mdefine_line|#define RC0_XCRCI       0x10
DECL|macro|RC0_RDIS
mdefine_line|#define RC0_RDIS        0x08
DECL|macro|RC0_RCO2
mdefine_line|#define RC0_RCO2        0x04
DECL|macro|RC0_RCO1
mdefine_line|#define RC0_RCO1        0x02
DECL|macro|RC0_RCO0
mdefine_line|#define RC0_RCO0        0x01
DECL|macro|RC1_SWD
mdefine_line|#define RC1_SWD         0x80
DECL|macro|RC1_ASY4
mdefine_line|#define RC1_ASY4        0x40
DECL|macro|RC1_RRAM
mdefine_line|#define RC1_RRAM        0x40
DECL|macro|RC1_RTO5
mdefine_line|#define RC1_RTO5        0x20
DECL|macro|RC1_RTO4
mdefine_line|#define RC1_RTO4        0x10
DECL|macro|RC1_RTO3
mdefine_line|#define RC1_RTO3        0x08
DECL|macro|RC1_RTO2
mdefine_line|#define RC1_RTO2        0x04
DECL|macro|RC1_RTO1
mdefine_line|#define RC1_RTO1        0x02
DECL|macro|RC1_RTO0
mdefine_line|#define RC1_RTO0        0x01
multiline_comment|/* XPM0-2 (Transmit Pulse Mask 0-2)&n;   --------------------- E1 &amp; T1 ------------------------- */
DECL|macro|XPM0_XP12
mdefine_line|#define XPM0_XP12       0x80
DECL|macro|XPM0_XP11
mdefine_line|#define XPM0_XP11       0x40
DECL|macro|XPM0_XP10
mdefine_line|#define XPM0_XP10       0x20
DECL|macro|XPM0_XP04
mdefine_line|#define XPM0_XP04       0x10
DECL|macro|XPM0_XP03
mdefine_line|#define XPM0_XP03       0x08
DECL|macro|XPM0_XP02
mdefine_line|#define XPM0_XP02       0x04
DECL|macro|XPM0_XP01
mdefine_line|#define XPM0_XP01       0x02
DECL|macro|XPM0_XP00
mdefine_line|#define XPM0_XP00       0x01
DECL|macro|XPM1_XP30
mdefine_line|#define XPM1_XP30       0x80
DECL|macro|XPM1_XP24
mdefine_line|#define XPM1_XP24       0x40
DECL|macro|XPM1_XP23
mdefine_line|#define XPM1_XP23       0x20
DECL|macro|XPM1_XP22
mdefine_line|#define XPM1_XP22       0x10
DECL|macro|XPM1_XP21
mdefine_line|#define XPM1_XP21       0x08
DECL|macro|XPM1_XP20
mdefine_line|#define XPM1_XP20       0x04
DECL|macro|XPM1_XP14
mdefine_line|#define XPM1_XP14       0x02
DECL|macro|XPM1_XP13
mdefine_line|#define XPM1_XP13       0x01
DECL|macro|XPM2_XLHP
mdefine_line|#define XPM2_XLHP       0x80
DECL|macro|XPM2_XLT
mdefine_line|#define XPM2_XLT        0x40
DECL|macro|XPM2_DAXLT
mdefine_line|#define XPM2_DAXLT      0x20
DECL|macro|XPM2_XP34
mdefine_line|#define XPM2_XP34       0x08
DECL|macro|XPM2_XP33
mdefine_line|#define XPM2_XP33       0x04
DECL|macro|XPM2_XP32
mdefine_line|#define XPM2_XP32       0x02
DECL|macro|XPM2_XP31
mdefine_line|#define XPM2_XP31       0x01
multiline_comment|/* TSWM (Transparent Service Word Mask)&n;   ------------------ E1 ---------------------------- */
DECL|macro|TSWM_TSIS
mdefine_line|#define TSWM_TSIS       0x80
DECL|macro|TSWM_TSIF
mdefine_line|#define TSWM_TSIF       0x40
DECL|macro|TSWM_TRA
mdefine_line|#define TSWM_TRA        0x20
DECL|macro|TSWM_TSA4
mdefine_line|#define TSWM_TSA4       0x10
DECL|macro|TSWM_TSA5
mdefine_line|#define TSWM_TSA5       0x08
DECL|macro|TSWM_TSA6
mdefine_line|#define TSWM_TSA6       0x04
DECL|macro|TSWM_TSA7
mdefine_line|#define TSWM_TSA7       0x02
DECL|macro|TSWM_TSA8
mdefine_line|#define TSWM_TSA8       0x01
multiline_comment|/* IDLE &lt;Idle Channel Code Register&gt;&n;&n;   ------------------ E1 &amp; T1 ----------------------- */
DECL|macro|IDLE_IDL7
mdefine_line|#define IDLE_IDL7       0x80
DECL|macro|IDLE_IDL6
mdefine_line|#define IDLE_IDL6       0x40
DECL|macro|IDLE_IDL5
mdefine_line|#define IDLE_IDL5       0x20
DECL|macro|IDLE_IDL4
mdefine_line|#define IDLE_IDL4       0x10
DECL|macro|IDLE_IDL3
mdefine_line|#define IDLE_IDL3       0x08
DECL|macro|IDLE_IDL2
mdefine_line|#define IDLE_IDL2       0x04
DECL|macro|IDLE_IDL1
mdefine_line|#define IDLE_IDL1       0x02
DECL|macro|IDLE_IDL0
mdefine_line|#define IDLE_IDL0       0x01
multiline_comment|/* XSA4-8 &lt;Transmit SA4-8 Register(Read/Write) &gt;&n;   -------------------E1 ----------------------------- */
DECL|macro|XSA4_XS47
mdefine_line|#define XSA4_XS47       0x80
DECL|macro|XSA4_XS46
mdefine_line|#define XSA4_XS46       0x40
DECL|macro|XSA4_XS45
mdefine_line|#define XSA4_XS45       0x20
DECL|macro|XSA4_XS44
mdefine_line|#define XSA4_XS44       0x10
DECL|macro|XSA4_XS43
mdefine_line|#define XSA4_XS43       0x08
DECL|macro|XSA4_XS42
mdefine_line|#define XSA4_XS42       0x04
DECL|macro|XSA4_XS41
mdefine_line|#define XSA4_XS41       0x02
DECL|macro|XSA4_XS40
mdefine_line|#define XSA4_XS40       0x01
DECL|macro|XSA5_XS57
mdefine_line|#define XSA5_XS57       0x80
DECL|macro|XSA5_XS56
mdefine_line|#define XSA5_XS56       0x40
DECL|macro|XSA5_XS55
mdefine_line|#define XSA5_XS55       0x20
DECL|macro|XSA5_XS54
mdefine_line|#define XSA5_XS54       0x10
DECL|macro|XSA5_XS53
mdefine_line|#define XSA5_XS53       0x08
DECL|macro|XSA5_XS52
mdefine_line|#define XSA5_XS52       0x04
DECL|macro|XSA5_XS51
mdefine_line|#define XSA5_XS51       0x02
DECL|macro|XSA5_XS50
mdefine_line|#define XSA5_XS50       0x01
DECL|macro|XSA6_XS67
mdefine_line|#define XSA6_XS67       0x80
DECL|macro|XSA6_XS66
mdefine_line|#define XSA6_XS66       0x40
DECL|macro|XSA6_XS65
mdefine_line|#define XSA6_XS65       0x20
DECL|macro|XSA6_XS64
mdefine_line|#define XSA6_XS64       0x10
DECL|macro|XSA6_XS63
mdefine_line|#define XSA6_XS63       0x08
DECL|macro|XSA6_XS62
mdefine_line|#define XSA6_XS62       0x04
DECL|macro|XSA6_XS61
mdefine_line|#define XSA6_XS61       0x02
DECL|macro|XSA6_XS60
mdefine_line|#define XSA6_XS60       0x01
DECL|macro|XSA7_XS77
mdefine_line|#define XSA7_XS77       0x80
DECL|macro|XSA7_XS76
mdefine_line|#define XSA7_XS76       0x40
DECL|macro|XSA7_XS75
mdefine_line|#define XSA7_XS75       0x20
DECL|macro|XSA7_XS74
mdefine_line|#define XSA7_XS74       0x10
DECL|macro|XSA7_XS73
mdefine_line|#define XSA7_XS73       0x08
DECL|macro|XSA7_XS72
mdefine_line|#define XSA7_XS72       0x04
DECL|macro|XSA7_XS71
mdefine_line|#define XSA7_XS71       0x02
DECL|macro|XSA7_XS70
mdefine_line|#define XSA7_XS70       0x01
DECL|macro|XSA8_XS87
mdefine_line|#define XSA8_XS87       0x80
DECL|macro|XSA8_XS86
mdefine_line|#define XSA8_XS86       0x40
DECL|macro|XSA8_XS85
mdefine_line|#define XSA8_XS85       0x20
DECL|macro|XSA8_XS84
mdefine_line|#define XSA8_XS84       0x10
DECL|macro|XSA8_XS83
mdefine_line|#define XSA8_XS83       0x08
DECL|macro|XSA8_XS82
mdefine_line|#define XSA8_XS82       0x04
DECL|macro|XSA8_XS81
mdefine_line|#define XSA8_XS81       0x02
DECL|macro|XSA8_XS80
mdefine_line|#define XSA8_XS80       0x01
multiline_comment|/* XDL1-3 (Transmit DL-Bit Register1-3 (read/write))&n;   ----------------------- T1 --------------------- */
DECL|macro|XDL1_XDL17
mdefine_line|#define XDL1_XDL17      0x80
DECL|macro|XDL1_XDL16
mdefine_line|#define XDL1_XDL16      0x40
DECL|macro|XDL1_XDL15
mdefine_line|#define XDL1_XDL15      0x20
DECL|macro|XDL1_XDL14
mdefine_line|#define XDL1_XDL14      0x10
DECL|macro|XDL1_XDL13
mdefine_line|#define XDL1_XDL13      0x08
DECL|macro|XDL1_XDL12
mdefine_line|#define XDL1_XDL12      0x04
DECL|macro|XDL1_XDL11
mdefine_line|#define XDL1_XDL11      0x02
DECL|macro|XDL1_XDL10
mdefine_line|#define XDL1_XDL10      0x01
DECL|macro|XDL2_XDL27
mdefine_line|#define XDL2_XDL27      0x80
DECL|macro|XDL2_XDL26
mdefine_line|#define XDL2_XDL26      0x40
DECL|macro|XDL2_XDL25
mdefine_line|#define XDL2_XDL25      0x20
DECL|macro|XDL2_XDL24
mdefine_line|#define XDL2_XDL24      0x10
DECL|macro|XDL2_XDL23
mdefine_line|#define XDL2_XDL23      0x08
DECL|macro|XDL2_XDL22
mdefine_line|#define XDL2_XDL22      0x04
DECL|macro|XDL2_XDL21
mdefine_line|#define XDL2_XDL21      0x02
DECL|macro|XDL2_XDL20
mdefine_line|#define XDL2_XDL20      0x01
DECL|macro|XDL3_XDL37
mdefine_line|#define XDL3_XDL37      0x80
DECL|macro|XDL3_XDL36
mdefine_line|#define XDL3_XDL36      0x40
DECL|macro|XDL3_XDL35
mdefine_line|#define XDL3_XDL35      0x20
DECL|macro|XDL3_XDL34
mdefine_line|#define XDL3_XDL34      0x10
DECL|macro|XDL3_XDL33
mdefine_line|#define XDL3_XDL33      0x08
DECL|macro|XDL3_XDL32
mdefine_line|#define XDL3_XDL32      0x04
DECL|macro|XDL3_XDL31
mdefine_line|#define XDL3_XDL31      0x02
DECL|macro|XDL3_XDL30
mdefine_line|#define XDL3_XDL30      0x01
multiline_comment|/* ICB1-4 (Idle Channel Register 1-4)&n;   ------------------ E1 ---------------------------- */
DECL|macro|E1_ICB1_IC0
mdefine_line|#define E1_ICB1_IC0&t;0x80
DECL|macro|E1_ICB1_IC1
mdefine_line|#define E1_ICB1_IC1&t;0x40
DECL|macro|E1_ICB1_IC2
mdefine_line|#define E1_ICB1_IC2&t;0x20
DECL|macro|E1_ICB1_IC3
mdefine_line|#define E1_ICB1_IC3&t;0x10
DECL|macro|E1_ICB1_IC4
mdefine_line|#define E1_ICB1_IC4&t;0x08
DECL|macro|E1_ICB1_IC5
mdefine_line|#define E1_ICB1_IC5&t;0x04
DECL|macro|E1_ICB1_IC6
mdefine_line|#define E1_ICB1_IC6&t;0x02
DECL|macro|E1_ICB1_IC7
mdefine_line|#define E1_ICB1_IC7&t;0x01
DECL|macro|E1_ICB2_IC8
mdefine_line|#define E1_ICB2_IC8&t;0x80
DECL|macro|E1_ICB2_IC9
mdefine_line|#define E1_ICB2_IC9&t;0x40
DECL|macro|E1_ICB2_IC10
mdefine_line|#define E1_ICB2_IC10&t;0x20
DECL|macro|E1_ICB2_IC11
mdefine_line|#define E1_ICB2_IC11&t;0x10
DECL|macro|E1_ICB2_IC12
mdefine_line|#define E1_ICB2_IC12&t;0x08
DECL|macro|E1_ICB2_IC13
mdefine_line|#define E1_ICB2_IC13&t;0x04
DECL|macro|E1_ICB2_IC14
mdefine_line|#define E1_ICB2_IC14&t;0x02
DECL|macro|E1_ICB2_IC15
mdefine_line|#define E1_ICB2_IC15&t;0x01
DECL|macro|E1_ICB3_IC16
mdefine_line|#define E1_ICB3_IC16&t;0x80
DECL|macro|E1_ICB3_IC17
mdefine_line|#define E1_ICB3_IC17&t;0x40
DECL|macro|E1_ICB3_IC18
mdefine_line|#define E1_ICB3_IC18&t;0x20
DECL|macro|E1_ICB3_IC19
mdefine_line|#define E1_ICB3_IC19&t;0x10
DECL|macro|E1_ICB3_IC20
mdefine_line|#define E1_ICB3_IC20&t;0x08
DECL|macro|E1_ICB3_IC21
mdefine_line|#define E1_ICB3_IC21&t;0x04
DECL|macro|E1_ICB3_IC22
mdefine_line|#define E1_ICB3_IC22&t;0x02
DECL|macro|E1_ICB3_IC23
mdefine_line|#define E1_ICB3_IC23&t;0x01
DECL|macro|E1_ICB4_IC24
mdefine_line|#define E1_ICB4_IC24&t;0x80
DECL|macro|E1_ICB4_IC25
mdefine_line|#define E1_ICB4_IC25&t;0x40
DECL|macro|E1_ICB4_IC26
mdefine_line|#define E1_ICB4_IC26&t;0x20
DECL|macro|E1_ICB4_IC27
mdefine_line|#define E1_ICB4_IC27&t;0x10
DECL|macro|E1_ICB4_IC28
mdefine_line|#define E1_ICB4_IC28&t;0x08
DECL|macro|E1_ICB4_IC29
mdefine_line|#define E1_ICB4_IC29&t;0x04
DECL|macro|E1_ICB4_IC30
mdefine_line|#define E1_ICB4_IC30&t;0x02
DECL|macro|E1_ICB4_IC31
mdefine_line|#define E1_ICB4_IC31&t;0x01
multiline_comment|/* ICB1-4 (Idle Channel Register 1-4)&n;   ------------------ T1 ---------------------------- */
DECL|macro|T1_ICB1_IC1
mdefine_line|#define T1_ICB1_IC1&t;0x80
DECL|macro|T1_ICB1_IC2
mdefine_line|#define T1_ICB1_IC2&t;0x40
DECL|macro|T1_ICB1_IC3
mdefine_line|#define T1_ICB1_IC3&t;0x20
DECL|macro|T1_ICB1_IC4
mdefine_line|#define T1_ICB1_IC4&t;0x10
DECL|macro|T1_ICB1_IC5
mdefine_line|#define T1_ICB1_IC5&t;0x08
DECL|macro|T1_ICB1_IC6
mdefine_line|#define T1_ICB1_IC6&t;0x04
DECL|macro|T1_ICB1_IC7
mdefine_line|#define T1_ICB1_IC7&t;0x02
DECL|macro|T1_ICB1_IC8
mdefine_line|#define T1_ICB1_IC8&t;0x01
DECL|macro|T1_ICB2_IC9
mdefine_line|#define T1_ICB2_IC9&t;0x80
DECL|macro|T1_ICB2_IC10
mdefine_line|#define T1_ICB2_IC10&t;0x40
DECL|macro|T1_ICB2_IC11
mdefine_line|#define T1_ICB2_IC11&t;0x20
DECL|macro|T1_ICB2_IC12
mdefine_line|#define T1_ICB2_IC12&t;0x10
DECL|macro|T1_ICB2_IC13
mdefine_line|#define T1_ICB2_IC13&t;0x08
DECL|macro|T1_ICB2_IC14
mdefine_line|#define T1_ICB2_IC14&t;0x04
DECL|macro|T1_ICB2_IC15
mdefine_line|#define T1_ICB2_IC15&t;0x02
DECL|macro|T1_ICB2_IC16
mdefine_line|#define T1_ICB2_IC16&t;0x01
DECL|macro|T1_ICB3_IC17
mdefine_line|#define T1_ICB3_IC17&t;0x80
DECL|macro|T1_ICB3_IC18
mdefine_line|#define T1_ICB3_IC18&t;0x40
DECL|macro|T1_ICB3_IC19
mdefine_line|#define T1_ICB3_IC19&t;0x20
DECL|macro|T1_ICB3_IC20
mdefine_line|#define T1_ICB3_IC20&t;0x10
DECL|macro|T1_ICB3_IC21
mdefine_line|#define T1_ICB3_IC21&t;0x08
DECL|macro|T1_ICB3_IC22
mdefine_line|#define T1_ICB3_IC22&t;0x04
DECL|macro|T1_ICB3_IC23
mdefine_line|#define T1_ICB3_IC23&t;0x02
DECL|macro|T1_ICB3_IC24
mdefine_line|#define T1_ICB3_IC24&t;0x01
multiline_comment|/* FMR3 (Framer Mode Register 3)&n;   --------------------E1------------------------ */
DECL|macro|FMR3_CMI
mdefine_line|#define FMR3_CMI        0x08
DECL|macro|FMR3_SYNSA
mdefine_line|#define FMR3_SYNSA      0x04
DECL|macro|FMR3_CFRZ
mdefine_line|#define FMR3_CFRZ       0x02
DECL|macro|FMR3_EXTIW
mdefine_line|#define FMR3_EXTIW      0x01
multiline_comment|/* CCB1-3 (Clear Channel Register)&n;   ------------------- T1 ----------------------- */
DECL|macro|CCB1_CH1
mdefine_line|#define CCB1_CH1        0x80
DECL|macro|CCB1_CH2
mdefine_line|#define CCB1_CH2        0x40
DECL|macro|CCB1_CH3
mdefine_line|#define CCB1_CH3        0x20
DECL|macro|CCB1_CH4
mdefine_line|#define CCB1_CH4        0x10
DECL|macro|CCB1_CH5
mdefine_line|#define CCB1_CH5        0x08
DECL|macro|CCB1_CH6
mdefine_line|#define CCB1_CH6        0x04
DECL|macro|CCB1_CH7
mdefine_line|#define CCB1_CH7        0x02
DECL|macro|CCB1_CH8
mdefine_line|#define CCB1_CH8        0x01
DECL|macro|CCB2_CH9
mdefine_line|#define CCB2_CH9        0x80
DECL|macro|CCB2_CH10
mdefine_line|#define CCB2_CH10       0x40
DECL|macro|CCB2_CH11
mdefine_line|#define CCB2_CH11       0x20
DECL|macro|CCB2_CH12
mdefine_line|#define CCB2_CH12       0x10
DECL|macro|CCB2_CH13
mdefine_line|#define CCB2_CH13       0x08
DECL|macro|CCB2_CH14
mdefine_line|#define CCB2_CH14       0x04
DECL|macro|CCB2_CH15
mdefine_line|#define CCB2_CH15       0x02
DECL|macro|CCB2_CH16
mdefine_line|#define CCB2_CH16       0x01
DECL|macro|CCB3_CH17
mdefine_line|#define CCB3_CH17       0x80
DECL|macro|CCB3_CH18
mdefine_line|#define CCB3_CH18       0x40
DECL|macro|CCB3_CH19
mdefine_line|#define CCB3_CH19       0x20
DECL|macro|CCB3_CH20
mdefine_line|#define CCB3_CH20       0x10
DECL|macro|CCB3_CH21
mdefine_line|#define CCB3_CH21       0x08
DECL|macro|CCB3_CH22
mdefine_line|#define CCB3_CH22       0x04
DECL|macro|CCB3_CH23
mdefine_line|#define CCB3_CH23       0x02
DECL|macro|CCB3_CH24
mdefine_line|#define CCB3_CH24       0x01
multiline_comment|/* LIM0/1 (Line Interface Mode 0/1)&n;   ------------------- E1 &amp; T1 --------------------------- */
DECL|macro|LIM0_XFB
mdefine_line|#define LIM0_XFB        0x80
DECL|macro|LIM0_XDOS
mdefine_line|#define LIM0_XDOS       0x40
DECL|macro|LIM0_SCL1
mdefine_line|#define LIM0_SCL1       0x20
DECL|macro|LIM0_SCL0
mdefine_line|#define LIM0_SCL0       0x10
DECL|macro|LIM0_EQON
mdefine_line|#define LIM0_EQON       0x08
DECL|macro|LIM0_ELOS
mdefine_line|#define LIM0_ELOS       0x04
DECL|macro|LIM0_LL
mdefine_line|#define LIM0_LL         0x02
DECL|macro|LIM0_MAS
mdefine_line|#define LIM0_MAS        0x01
DECL|macro|LIM1_EFSC
mdefine_line|#define LIM1_EFSC       0x80
DECL|macro|LIM1_RIL2
mdefine_line|#define LIM1_RIL2       0x40
DECL|macro|LIM1_RIL1
mdefine_line|#define LIM1_RIL1       0x20
DECL|macro|LIM1_RIL0
mdefine_line|#define LIM1_RIL0       0x10
DECL|macro|LIM1_DCOC
mdefine_line|#define LIM1_DCOC       0x08
DECL|macro|LIM1_JATT
mdefine_line|#define LIM1_JATT       0x04
DECL|macro|LIM1_RL
mdefine_line|#define LIM1_RL         0x02
DECL|macro|LIM1_DRS
mdefine_line|#define LIM1_DRS        0x01
multiline_comment|/* PCDR (Pulse Count Detection Register(Read/Write))&n;   ------------------ E1 &amp; T1 ------------------------- */
DECL|macro|PCDR_PCD7
mdefine_line|#define PCDR_PCD7&t;0x80
DECL|macro|PCDR_PCD6
mdefine_line|#define PCDR_PCD6&t;0x40
DECL|macro|PCDR_PCD5
mdefine_line|#define PCDR_PCD5&t;0x20
DECL|macro|PCDR_PCD4
mdefine_line|#define PCDR_PCD4&t;0x10
DECL|macro|PCDR_PCD3
mdefine_line|#define PCDR_PCD3&t;0x08
DECL|macro|PCDR_PCD2
mdefine_line|#define PCDR_PCD2&t;0x04
DECL|macro|PCDR_PCD1
mdefine_line|#define PCDR_PCD1&t;0x02
DECL|macro|PCDR_PCD0
mdefine_line|#define PCDR_PCD0&t;0x01
DECL|macro|PCRR_PCR7
mdefine_line|#define PCRR_PCR7&t;0x80
DECL|macro|PCRR_PCR6
mdefine_line|#define PCRR_PCR6&t;0x40
DECL|macro|PCRR_PCR5
mdefine_line|#define PCRR_PCR5&t;0x20
DECL|macro|PCRR_PCR4
mdefine_line|#define PCRR_PCR4&t;0x10
DECL|macro|PCRR_PCR3
mdefine_line|#define PCRR_PCR3&t;0x08
DECL|macro|PCRR_PCR2
mdefine_line|#define PCRR_PCR2&t;0x04
DECL|macro|PCRR_PCR1
mdefine_line|#define PCRR_PCR1&t;0x02
DECL|macro|PCRR_PCR0
mdefine_line|#define PCRR_PCR0&t;0x01
multiline_comment|/* LIM2 (Line Interface Mode 2)&n;&n;   ------------------ E1 &amp; T1 ---------------------------- */
DECL|macro|LIM2_DJA2
mdefine_line|#define LIM2_DJA2&t;0x20
DECL|macro|LIM2_DJA1
mdefine_line|#define LIM2_DJA1&t;0x10
DECL|macro|LIM2_LOS2
mdefine_line|#define LIM2_LOS2&t;0x02
DECL|macro|LIM2_LOS1
mdefine_line|#define LIM2_LOS1&t;0x01
multiline_comment|/* LCR1 (Loop Code Register 1) */
DECL|macro|LCR1_EPRM
mdefine_line|#define LCR1_EPRM&t;0x80
DECL|macro|LCR1_XPRBS
mdefine_line|#define&t;LCR1_XPRBS&t;0x40
multiline_comment|/* SIC1 (System Interface Control 1) */
DECL|macro|SIC1_SRSC
mdefine_line|#define SIC1_SRSC&t;0x80
DECL|macro|SIC1_RBS1
mdefine_line|#define SIC1_RBS1&t;0x20
DECL|macro|SIC1_RBS0
mdefine_line|#define SIC1_RBS0&t;0x10
DECL|macro|SIC1_SXSC
mdefine_line|#define SIC1_SXSC&t;0x08
DECL|macro|SIC1_XBS1
mdefine_line|#define SIC1_XBS1&t;0x02
DECL|macro|SIC1_XBS0
mdefine_line|#define SIC1_XBS0&t;0x01
multiline_comment|/* DEC (Disable Error Counter)&n;   ------------------ E1 &amp; T1 ---------------------------- */
DECL|macro|DEC_DCEC3
mdefine_line|#define DEC_DCEC3       0x20
DECL|macro|DEC_DBEC
mdefine_line|#define DEC_DBEC        0x10
DECL|macro|DEC_DCEC1
mdefine_line|#define DEC_DCEC1       0x08
DECL|macro|DEC_DCEC
mdefine_line|#define DEC_DCEC        0x08
DECL|macro|DEC_DEBC
mdefine_line|#define DEC_DEBC        0x04
DECL|macro|DEC_DCVC
mdefine_line|#define DEC_DCVC        0x02
DECL|macro|DEC_DFEC
mdefine_line|#define DEC_DFEC        0x01
multiline_comment|/* FALC Register Bits (Receive Mode)&n;   ---------------------------------------------------------------------------- */
multiline_comment|/* FRS0/1 (Framer Receive Status Register 0/1)&n;   ----------------- E1 &amp; T1 ---------------------------------- */
DECL|macro|FRS0_LOS
mdefine_line|#define FRS0_LOS        0x80
DECL|macro|FRS0_AIS
mdefine_line|#define FRS0_AIS        0x40
DECL|macro|FRS0_LFA
mdefine_line|#define FRS0_LFA        0x20
DECL|macro|FRS0_RRA
mdefine_line|#define FRS0_RRA        0x10
DECL|macro|FRS0_API
mdefine_line|#define FRS0_API        0x08
DECL|macro|FRS0_NMF
mdefine_line|#define FRS0_NMF        0x04
DECL|macro|FRS0_LMFA
mdefine_line|#define FRS0_LMFA       0x02
DECL|macro|FRS0_FSRF
mdefine_line|#define FRS0_FSRF       0x01
DECL|macro|FRS1_TS16RA
mdefine_line|#define FRS1_TS16RA     0x40
DECL|macro|FRS1_TS16LOS
mdefine_line|#define FRS1_TS16LOS    0x20
DECL|macro|FRS1_TS16AIS
mdefine_line|#define FRS1_TS16AIS    0x10
DECL|macro|FRS1_TS16LFA
mdefine_line|#define FRS1_TS16LFA    0x08
DECL|macro|FRS1_EXZD
mdefine_line|#define FRS1_EXZD       0x80
DECL|macro|FRS1_LLBDD
mdefine_line|#define FRS1_LLBDD      0x10
DECL|macro|FRS1_LLBAD
mdefine_line|#define FRS1_LLBAD      0x08
DECL|macro|FRS1_XLS
mdefine_line|#define FRS1_XLS        0x02
DECL|macro|FRS1_XLO
mdefine_line|#define FRS1_XLO        0x01
DECL|macro|FRS1_PDEN
mdefine_line|#define FRS1_PDEN&t;0x40
multiline_comment|/* FRS2/3 (Framer Receive Status Register 2/3)&n;   ----------------- T1 ---------------------------------- */
DECL|macro|FRS2_ESC2
mdefine_line|#define FRS2_ESC2       0x80
DECL|macro|FRS2_ESC1
mdefine_line|#define FRS2_ESC1       0x40
DECL|macro|FRS2_ESC0
mdefine_line|#define FRS2_ESC0       0x20
DECL|macro|FRS3_FEH5
mdefine_line|#define FRS3_FEH5       0x20
DECL|macro|FRS3_FEH4
mdefine_line|#define FRS3_FEH4       0x10
DECL|macro|FRS3_FEH3
mdefine_line|#define FRS3_FEH3       0x08
DECL|macro|FRS3_FEH2
mdefine_line|#define FRS3_FEH2       0x04
DECL|macro|FRS3_FEH1
mdefine_line|#define FRS3_FEH1       0x02
DECL|macro|FRS3_FEH0
mdefine_line|#define FRS3_FEH0       0x01
multiline_comment|/* RSW (Receive Service Word Pulseframe)&n;   ----------------- E1 ------------------------------ */
DECL|macro|RSW_RSI
mdefine_line|#define RSW_RSI         0x80
DECL|macro|RSW_RRA
mdefine_line|#define RSW_RRA         0x20
DECL|macro|RSW_RYO
mdefine_line|#define RSW_RYO         0x10
DECL|macro|RSW_RY1
mdefine_line|#define RSW_RY1         0x08
DECL|macro|RSW_RY2
mdefine_line|#define RSW_RY2         0x04
DECL|macro|RSW_RY3
mdefine_line|#define RSW_RY3         0x02
DECL|macro|RSW_RY4
mdefine_line|#define RSW_RY4         0x01
multiline_comment|/* RSP (Receive Spare Bits / Additional Status)&n;   ---------------- E1 ------------------------------- */
DECL|macro|RSP_SI1
mdefine_line|#define RSP_SI1         0x80
DECL|macro|RSP_SI2
mdefine_line|#define RSP_SI2         0x40
DECL|macro|RSP_LLBDD
mdefine_line|#define RSP_LLBDD&t;0x10
DECL|macro|RSP_LLBAD
mdefine_line|#define RSP_LLBAD&t;0x08
DECL|macro|RSP_RSIF
mdefine_line|#define RSP_RSIF        0x04
DECL|macro|RSP_RS13
mdefine_line|#define RSP_RS13        0x02
DECL|macro|RSP_RS15
mdefine_line|#define RSP_RS15        0x01
multiline_comment|/* FECL (Framing Error Counter)&n;   ---------------- E1 &amp; T1 -------------------------- */
DECL|macro|FECL_FE7
mdefine_line|#define FECL_FE7        0x80
DECL|macro|FECL_FE6
mdefine_line|#define FECL_FE6        0x40
DECL|macro|FECL_FE5
mdefine_line|#define FECL_FE5        0x20
DECL|macro|FECL_FE4
mdefine_line|#define FECL_FE4        0x10
DECL|macro|FECL_FE3
mdefine_line|#define FECL_FE3        0x08
DECL|macro|FECL_FE2
mdefine_line|#define FECL_FE2        0x04
DECL|macro|FECL_FE1
mdefine_line|#define FECL_FE1        0x02
DECL|macro|FECL_FE0
mdefine_line|#define FECL_FE0        0x01
DECL|macro|FECH_FE15
mdefine_line|#define FECH_FE15       0x80
DECL|macro|FECH_FE14
mdefine_line|#define FECH_FE14       0x40
DECL|macro|FECH_FE13
mdefine_line|#define FECH_FE13       0x20
DECL|macro|FECH_FE12
mdefine_line|#define FECH_FE12       0x10
DECL|macro|FECH_FE11
mdefine_line|#define FECH_FE11       0x08
DECL|macro|FECH_FE10
mdefine_line|#define FECH_FE10       0x04
DECL|macro|FECH_FE9
mdefine_line|#define FECH_FE9        0x02
DECL|macro|FECH_FE8
mdefine_line|#define FECH_FE8        0x01
multiline_comment|/* CVCl (Code Violation Counter)&n;   ----------------- E1 ------------------------- */
DECL|macro|CVCL_CV7
mdefine_line|#define CVCL_CV7        0x80
DECL|macro|CVCL_CV6
mdefine_line|#define CVCL_CV6        0x40
DECL|macro|CVCL_CV5
mdefine_line|#define CVCL_CV5        0x20
DECL|macro|CVCL_CV4
mdefine_line|#define CVCL_CV4        0x10
DECL|macro|CVCL_CV3
mdefine_line|#define CVCL_CV3        0x08
DECL|macro|CVCL_CV2
mdefine_line|#define CVCL_CV2        0x04
DECL|macro|CVCL_CV1
mdefine_line|#define CVCL_CV1        0x02
DECL|macro|CVCL_CV0
mdefine_line|#define CVCL_CV0        0x01
DECL|macro|CVCH_CV15
mdefine_line|#define CVCH_CV15       0x80
DECL|macro|CVCH_CV14
mdefine_line|#define CVCH_CV14       0x40
DECL|macro|CVCH_CV13
mdefine_line|#define CVCH_CV13       0x20
DECL|macro|CVCH_CV12
mdefine_line|#define CVCH_CV12       0x10
DECL|macro|CVCH_CV11
mdefine_line|#define CVCH_CV11       0x08
DECL|macro|CVCH_CV10
mdefine_line|#define CVCH_CV10       0x04
DECL|macro|CVCH_CV9
mdefine_line|#define CVCH_CV9        0x02
DECL|macro|CVCH_CV8
mdefine_line|#define CVCH_CV8        0x01
multiline_comment|/* CEC1-3L (CRC Error Counter)&n;   ------------------ E1 ----------------------------- */
DECL|macro|CEC1L_CR7
mdefine_line|#define CEC1L_CR7       0x80
DECL|macro|CEC1L_CR6
mdefine_line|#define CEC1L_CR6       0x40
DECL|macro|CEC1L_CR5
mdefine_line|#define CEC1L_CR5       0x20
DECL|macro|CEC1L_CR4
mdefine_line|#define CEC1L_CR4       0x10
DECL|macro|CEC1L_CR3
mdefine_line|#define CEC1L_CR3       0x08
DECL|macro|CEC1L_CR2
mdefine_line|#define CEC1L_CR2       0x04
DECL|macro|CEC1L_CR1
mdefine_line|#define CEC1L_CR1       0x02
DECL|macro|CEC1L_CR0
mdefine_line|#define CEC1L_CR0       0x01
DECL|macro|CEC1H_CR15
mdefine_line|#define CEC1H_CR15      0x80
DECL|macro|CEC1H_CR14
mdefine_line|#define CEC1H_CR14      0x40
DECL|macro|CEC1H_CR13
mdefine_line|#define CEC1H_CR13      0x20
DECL|macro|CEC1H_CR12
mdefine_line|#define CEC1H_CR12      0x10
DECL|macro|CEC1H_CR11
mdefine_line|#define CEC1H_CR11      0x08
DECL|macro|CEC1H_CR10
mdefine_line|#define CEC1H_CR10      0x04
DECL|macro|CEC1H_CR9
mdefine_line|#define CEC1H_CR9       0x02
DECL|macro|CEC1H_CR8
mdefine_line|#define CEC1H_CR8       0x01
DECL|macro|CEC2L_CR7
mdefine_line|#define CEC2L_CR7       0x80
DECL|macro|CEC2L_CR6
mdefine_line|#define CEC2L_CR6       0x40
DECL|macro|CEC2L_CR5
mdefine_line|#define CEC2L_CR5       0x20
DECL|macro|CEC2L_CR4
mdefine_line|#define CEC2L_CR4       0x10
DECL|macro|CEC2L_CR3
mdefine_line|#define CEC2L_CR3       0x08
DECL|macro|CEC2L_CR2
mdefine_line|#define CEC2L_CR2       0x04
DECL|macro|CEC2L_CR1
mdefine_line|#define CEC2L_CR1       0x02
DECL|macro|CEC2L_CR0
mdefine_line|#define CEC2L_CR0       0x01
DECL|macro|CEC2H_CR15
mdefine_line|#define CEC2H_CR15      0x80
DECL|macro|CEC2H_CR14
mdefine_line|#define CEC2H_CR14      0x40
DECL|macro|CEC2H_CR13
mdefine_line|#define CEC2H_CR13      0x20
DECL|macro|CEC2H_CR12
mdefine_line|#define CEC2H_CR12      0x10
DECL|macro|CEC2H_CR11
mdefine_line|#define CEC2H_CR11      0x08
DECL|macro|CEC2H_CR10
mdefine_line|#define CEC2H_CR10      0x04
DECL|macro|CEC2H_CR9
mdefine_line|#define CEC2H_CR9       0x02
DECL|macro|CEC2H_CR8
mdefine_line|#define CEC2H_CR8       0x01
DECL|macro|CEC3L_CR7
mdefine_line|#define CEC3L_CR7       0x80
DECL|macro|CEC3L_CR6
mdefine_line|#define CEC3L_CR6       0x40
DECL|macro|CEC3L_CR5
mdefine_line|#define CEC3L_CR5       0x20
DECL|macro|CEC3L_CR4
mdefine_line|#define CEC3L_CR4       0x10
DECL|macro|CEC3L_CR3
mdefine_line|#define CEC3L_CR3       0x08
DECL|macro|CEC3L_CR2
mdefine_line|#define CEC3L_CR2       0x04
DECL|macro|CEC3L_CR1
mdefine_line|#define CEC3L_CR1       0x02
DECL|macro|CEC3L_CR0
mdefine_line|#define CEC3L_CR0       0x01
DECL|macro|CEC3H_CR15
mdefine_line|#define CEC3H_CR15      0x80
DECL|macro|CEC3H_CR14
mdefine_line|#define CEC3H_CR14      0x40
DECL|macro|CEC3H_CR13
mdefine_line|#define CEC3H_CR13      0x20
DECL|macro|CEC3H_CR12
mdefine_line|#define CEC3H_CR12      0x10
DECL|macro|CEC3H_CR11
mdefine_line|#define CEC3H_CR11      0x08
DECL|macro|CEC3H_CR10
mdefine_line|#define CEC3H_CR10      0x04
DECL|macro|CEC3H_CR9
mdefine_line|#define CEC3H_CR9       0x02
DECL|macro|CEC3H_CR8
mdefine_line|#define CEC3H_CR8       0x01
multiline_comment|/* CECL (CRC Error Counter)&n;&n;   ------------------ T1 ----------------------------- */
DECL|macro|CECL_CR7
mdefine_line|#define CECL_CR7        0x80
DECL|macro|CECL_CR6
mdefine_line|#define CECL_CR6        0x40
DECL|macro|CECL_CR5
mdefine_line|#define CECL_CR5        0x20
DECL|macro|CECL_CR4
mdefine_line|#define CECL_CR4        0x10
DECL|macro|CECL_CR3
mdefine_line|#define CECL_CR3        0x08
DECL|macro|CECL_CR2
mdefine_line|#define CECL_CR2        0x04
DECL|macro|CECL_CR1
mdefine_line|#define CECL_CR1        0x02
DECL|macro|CECL_CR0
mdefine_line|#define CECL_CR0        0x01
DECL|macro|CECH_CR15
mdefine_line|#define CECH_CR15       0x80
DECL|macro|CECH_CR14
mdefine_line|#define CECH_CR14       0x40
DECL|macro|CECH_CR13
mdefine_line|#define CECH_CR13       0x20
DECL|macro|CECH_CR12
mdefine_line|#define CECH_CR12       0x10
DECL|macro|CECH_CR11
mdefine_line|#define CECH_CR11       0x08
DECL|macro|CECH_CR10
mdefine_line|#define CECH_CR10       0x04
DECL|macro|CECH_CR9
mdefine_line|#define CECH_CR9        0x02
DECL|macro|CECH_CR8
mdefine_line|#define CECH_CR8        0x01
multiline_comment|/* EBCL (E Bit Error Counter)&n;   ------------------- E1 &amp; T1 ------------------------- */
DECL|macro|EBCL_EB7
mdefine_line|#define EBCL_EB7        0x80
DECL|macro|EBCL_EB6
mdefine_line|#define EBCL_EB6        0x40
DECL|macro|EBCL_EB5
mdefine_line|#define EBCL_EB5        0x20
DECL|macro|EBCL_EB4
mdefine_line|#define EBCL_EB4        0x10
DECL|macro|EBCL_EB3
mdefine_line|#define EBCL_EB3        0x08
DECL|macro|EBCL_EB2
mdefine_line|#define EBCL_EB2        0x04
DECL|macro|EBCL_EB1
mdefine_line|#define EBCL_EB1        0x02
DECL|macro|EBCL_EB0
mdefine_line|#define EBCL_EB0        0x01
DECL|macro|EBCH_EB15
mdefine_line|#define EBCH_EB15       0x80
DECL|macro|EBCH_EB14
mdefine_line|#define EBCH_EB14       0x40
DECL|macro|EBCH_EB13
mdefine_line|#define EBCH_EB13       0x20
DECL|macro|EBCH_EB12
mdefine_line|#define EBCH_EB12       0x10
DECL|macro|EBCH_EB11
mdefine_line|#define EBCH_EB11       0x08
DECL|macro|EBCH_EB10
mdefine_line|#define EBCH_EB10       0x04
DECL|macro|EBCH_EB9
mdefine_line|#define EBCH_EB9        0x02
DECL|macro|EBCH_EB8
mdefine_line|#define EBCH_EB8        0x01
multiline_comment|/* RSA4-8 (Receive Sa4-8-Bit Register)&n;   -------------------- E1 --------------------------- */
DECL|macro|RSA4_RS47
mdefine_line|#define RSA4_RS47       0x80
DECL|macro|RSA4_RS46
mdefine_line|#define RSA4_RS46       0x40
DECL|macro|RSA4_RS45
mdefine_line|#define RSA4_RS45       0x20
DECL|macro|RSA4_RS44
mdefine_line|#define RSA4_RS44       0x10
DECL|macro|RSA4_RS43
mdefine_line|#define RSA4_RS43       0x08
DECL|macro|RSA4_RS42
mdefine_line|#define RSA4_RS42       0x04
DECL|macro|RSA4_RS41
mdefine_line|#define RSA4_RS41       0x02
DECL|macro|RSA4_RS40
mdefine_line|#define RSA4_RS40       0x01
DECL|macro|RSA5_RS57
mdefine_line|#define RSA5_RS57       0x80
DECL|macro|RSA5_RS56
mdefine_line|#define RSA5_RS56       0x40
DECL|macro|RSA5_RS55
mdefine_line|#define RSA5_RS55       0x20
DECL|macro|RSA5_RS54
mdefine_line|#define RSA5_RS54       0x10
DECL|macro|RSA5_RS53
mdefine_line|#define RSA5_RS53       0x08
DECL|macro|RSA5_RS52
mdefine_line|#define RSA5_RS52       0x04
DECL|macro|RSA5_RS51
mdefine_line|#define RSA5_RS51       0x02
DECL|macro|RSA5_RS50
mdefine_line|#define RSA5_RS50       0x01
DECL|macro|RSA6_RS67
mdefine_line|#define RSA6_RS67       0x80
DECL|macro|RSA6_RS66
mdefine_line|#define RSA6_RS66       0x40
DECL|macro|RSA6_RS65
mdefine_line|#define RSA6_RS65       0x20
DECL|macro|RSA6_RS64
mdefine_line|#define RSA6_RS64       0x10
DECL|macro|RSA6_RS63
mdefine_line|#define RSA6_RS63       0x08
DECL|macro|RSA6_RS62
mdefine_line|#define RSA6_RS62       0x04
DECL|macro|RSA6_RS61
mdefine_line|#define RSA6_RS61       0x02
DECL|macro|RSA6_RS60
mdefine_line|#define RSA6_RS60       0x01
DECL|macro|RSA7_RS77
mdefine_line|#define RSA7_RS77       0x80
DECL|macro|RSA7_RS76
mdefine_line|#define RSA7_RS76       0x40
DECL|macro|RSA7_RS75
mdefine_line|#define RSA7_RS75       0x20
DECL|macro|RSA7_RS74
mdefine_line|#define RSA7_RS74       0x10
DECL|macro|RSA7_RS73
mdefine_line|#define RSA7_RS73       0x08
DECL|macro|RSA7_RS72
mdefine_line|#define RSA7_RS72       0x04
DECL|macro|RSA7_RS71
mdefine_line|#define RSA7_RS71       0x02
DECL|macro|RSA7_RS70
mdefine_line|#define RSA7_RS70       0x01
DECL|macro|RSA8_RS87
mdefine_line|#define RSA8_RS87       0x80
DECL|macro|RSA8_RS86
mdefine_line|#define RSA8_RS86       0x40
DECL|macro|RSA8_RS85
mdefine_line|#define RSA8_RS85       0x20
DECL|macro|RSA8_RS84
mdefine_line|#define RSA8_RS84       0x10
DECL|macro|RSA8_RS83
mdefine_line|#define RSA8_RS83       0x08
DECL|macro|RSA8_RS82
mdefine_line|#define RSA8_RS82       0x04
DECL|macro|RSA8_RS81
mdefine_line|#define RSA8_RS81       0x02
DECL|macro|RSA8_RS80
mdefine_line|#define RSA8_RS80       0x01
multiline_comment|/* RSA6S (Receive Sa6 Bit Status Register)&n;   ------------------------ T1 ------------------------- */
DECL|macro|RSA6S_SX
mdefine_line|#define RSA6S_SX        0x20
DECL|macro|RSA6S_SF
mdefine_line|#define RSA6S_SF        0x10
DECL|macro|RSA6S_SE
mdefine_line|#define RSA6S_SE        0x08
DECL|macro|RSA6S_SC
mdefine_line|#define RSA6S_SC        0x04
DECL|macro|RSA6S_SA
mdefine_line|#define RSA6S_SA        0x02
DECL|macro|RSA6S_S8
mdefine_line|#define RSA6S_S8        0x01
multiline_comment|/* RDL1-3 Receive DL-Bit Register1-3)&n;   ------------------------ T1 ------------------------- */
DECL|macro|RDL1_RDL17
mdefine_line|#define RDL1_RDL17      0x80
DECL|macro|RDL1_RDL16
mdefine_line|#define RDL1_RDL16      0x40
DECL|macro|RDL1_RDL15
mdefine_line|#define RDL1_RDL15      0x20
DECL|macro|RDL1_RDL14
mdefine_line|#define RDL1_RDL14      0x10
DECL|macro|RDL1_RDL13
mdefine_line|#define RDL1_RDL13      0x08
DECL|macro|RDL1_RDL12
mdefine_line|#define RDL1_RDL12      0x04
DECL|macro|RDL1_RDL11
mdefine_line|#define RDL1_RDL11      0x02
DECL|macro|RDL1_RDL10
mdefine_line|#define RDL1_RDL10      0x01
DECL|macro|RDL2_RDL27
mdefine_line|#define RDL2_RDL27      0x80
DECL|macro|RDL2_RDL26
mdefine_line|#define RDL2_RDL26      0x40
DECL|macro|RDL2_RDL25
mdefine_line|#define RDL2_RDL25      0x20
DECL|macro|RDL2_RDL24
mdefine_line|#define RDL2_RDL24      0x10
DECL|macro|RDL2_RDL23
mdefine_line|#define RDL2_RDL23      0x08
DECL|macro|RDL2_RDL22
mdefine_line|#define RDL2_RDL22      0x04
DECL|macro|RDL2_RDL21
mdefine_line|#define RDL2_RDL21      0x02
DECL|macro|RDL2_RDL20
mdefine_line|#define RDL2_RDL20      0x01
DECL|macro|RDL3_RDL37
mdefine_line|#define RDL3_RDL37      0x80
DECL|macro|RDL3_RDL36
mdefine_line|#define RDL3_RDL36      0x40
DECL|macro|RDL3_RDL35
mdefine_line|#define RDL3_RDL35      0x20
DECL|macro|RDL3_RDL34
mdefine_line|#define RDL3_RDL34      0x10
DECL|macro|RDL3_RDL33
mdefine_line|#define RDL3_RDL33      0x08
DECL|macro|RDL3_RDL32
mdefine_line|#define RDL3_RDL32      0x04
DECL|macro|RDL3_RDL31
mdefine_line|#define RDL3_RDL31      0x02
DECL|macro|RDL3_RDL30
mdefine_line|#define RDL3_RDL30      0x01
multiline_comment|/* SIS (Signaling Status Register)&n;&n;   -------------------- E1 &amp; T1 -------------------------- */
DECL|macro|SIS_XDOV
mdefine_line|#define SIS_XDOV        0x80
DECL|macro|SIS_XFW
mdefine_line|#define SIS_XFW         0x40
DECL|macro|SIS_XREP
mdefine_line|#define SIS_XREP        0x20
DECL|macro|SIS_RLI
mdefine_line|#define SIS_RLI         0x08
DECL|macro|SIS_CEC
mdefine_line|#define SIS_CEC         0x04
DECL|macro|SIS_BOM
mdefine_line|#define SIS_BOM         0x01
multiline_comment|/* RSIS (Receive Signaling Status Register)&n;&n;   -------------------- E1 &amp; T1 --------------------------- */
DECL|macro|RSIS_VFR
mdefine_line|#define RSIS_VFR        0x80
DECL|macro|RSIS_RDO
mdefine_line|#define RSIS_RDO        0x40
DECL|macro|RSIS_CRC16
mdefine_line|#define RSIS_CRC16      0x20
DECL|macro|RSIS_RAB
mdefine_line|#define RSIS_RAB        0x10
DECL|macro|RSIS_HA1
mdefine_line|#define RSIS_HA1        0x08
DECL|macro|RSIS_HA0
mdefine_line|#define RSIS_HA0        0x04
DECL|macro|RSIS_HFR
mdefine_line|#define RSIS_HFR        0x02
DECL|macro|RSIS_LA
mdefine_line|#define RSIS_LA         0x01
multiline_comment|/* RBCL/H (Receive Byte Count Low/High)&n;&n;   ------------------- E1 &amp; T1 ----------------------- */
DECL|macro|RBCL_RBC7
mdefine_line|#define RBCL_RBC7       0x80
DECL|macro|RBCL_RBC6
mdefine_line|#define RBCL_RBC6       0x40
DECL|macro|RBCL_RBC5
mdefine_line|#define RBCL_RBC5       0x20
DECL|macro|RBCL_RBC4
mdefine_line|#define RBCL_RBC4       0x10
DECL|macro|RBCL_RBC3
mdefine_line|#define RBCL_RBC3       0x08
DECL|macro|RBCL_RBC2
mdefine_line|#define RBCL_RBC2       0x04
DECL|macro|RBCL_RBC1
mdefine_line|#define RBCL_RBC1       0x02
DECL|macro|RBCL_RBC0
mdefine_line|#define RBCL_RBC0       0x01
DECL|macro|RBCH_OV
mdefine_line|#define RBCH_OV         0x10
DECL|macro|RBCH_RBC11
mdefine_line|#define RBCH_RBC11      0x08
DECL|macro|RBCH_RBC10
mdefine_line|#define RBCH_RBC10      0x04
DECL|macro|RBCH_RBC9
mdefine_line|#define RBCH_RBC9       0x02
DECL|macro|RBCH_RBC8
mdefine_line|#define RBCH_RBC8       0x01
multiline_comment|/* ISR1-3  (Interrupt Status Register 1-3)&n;&n;   ------------------ E1 &amp; T1 ------------------------------ */
DECL|macro|FISR0_RME
mdefine_line|#define  FISR0_RME&t;0x80
DECL|macro|FISR0_RFS
mdefine_line|#define  FISR0_RFS&t;0x40
DECL|macro|FISR0_T8MS
mdefine_line|#define  FISR0_T8MS&t;0x20
DECL|macro|FISR0_ISF
mdefine_line|#define  FISR0_ISF&t;0x20
DECL|macro|FISR0_RMB
mdefine_line|#define  FISR0_RMB&t;0x10
DECL|macro|FISR0_CASC
mdefine_line|#define  FISR0_CASC&t;0x08
DECL|macro|FISR0_RSC
mdefine_line|#define  FISR0_RSC&t;0x08
DECL|macro|FISR0_CRC6
mdefine_line|#define  FISR0_CRC6&t;0x04
DECL|macro|FISR0_CRC4
mdefine_line|#define  FISR0_CRC4&t;0x04
DECL|macro|FISR0_PDEN
mdefine_line|#define  FISR0_PDEN&t;0x02
DECL|macro|FISR0_RPF
mdefine_line|#define  FISR0_RPF&t;0x01
DECL|macro|FISR1_CASE
mdefine_line|#define  FISR1_CASE&t;0x80
DECL|macro|FISR1_LLBSC
mdefine_line|#define  FISR1_LLBSC&t;0x80
DECL|macro|FISR1_RDO
mdefine_line|#define  FISR1_RDO&t;0x40
DECL|macro|FISR1_ALLS
mdefine_line|#define  FISR1_ALLS&t;0x20
DECL|macro|FISR1_XDU
mdefine_line|#define  FISR1_XDU&t;0x10
DECL|macro|FISR1_XMB
mdefine_line|#define  FISR1_XMB&t;0x08
DECL|macro|FISR1_XLSC
mdefine_line|#define  FISR1_XLSC&t;0x02
DECL|macro|FISR1_XPR
mdefine_line|#define  FISR1_XPR&t;0x01
DECL|macro|FISR2_FAR
mdefine_line|#define  FISR2_FAR&t;0x80
DECL|macro|FISR2_LFA
mdefine_line|#define  FISR2_LFA&t;0x40
DECL|macro|FISR2_MFAR
mdefine_line|#define  FISR2_MFAR&t;0x20
DECL|macro|FISR2_T400MS
mdefine_line|#define  FISR2_T400MS&t;0x10
DECL|macro|FISR2_LMFA
mdefine_line|#define  FISR2_LMFA&t;0x10
DECL|macro|FISR2_AIS
mdefine_line|#define  FISR2_AIS&t;0x08
DECL|macro|FISR2_LOS
mdefine_line|#define  FISR2_LOS&t;0x04
DECL|macro|FISR2_RAR
mdefine_line|#define  FISR2_RAR&t;0x02
DECL|macro|FISR2_RA
mdefine_line|#define  FISR2_RA&t;0x01
DECL|macro|FISR3_ES
mdefine_line|#define  FISR3_ES&t;0x80
DECL|macro|FISR3_SEC
mdefine_line|#define  FISR3_SEC&t;0x40
DECL|macro|FISR3_LMFA16
mdefine_line|#define  FISR3_LMFA16&t;0x20
DECL|macro|FISR3_AIS16
mdefine_line|#define  FISR3_AIS16&t;0x10
DECL|macro|FISR3_RA16
mdefine_line|#define  FISR3_RA16&t;0x08
DECL|macro|FISR3_API
mdefine_line|#define  FISR3_API&t;0x04
DECL|macro|FISR3_XSLP
mdefine_line|#define  FISR3_XSLP&t;0x20
DECL|macro|FISR3_XSLN
mdefine_line|#define  FISR3_XSLN&t;0x10
DECL|macro|FISR3_LLBSC
mdefine_line|#define  FISR3_LLBSC&t;0x08
DECL|macro|FISR3_XRS
mdefine_line|#define  FISR3_XRS&t;0x04
DECL|macro|FISR3_SLN
mdefine_line|#define  FISR3_SLN&t;0x02
DECL|macro|FISR3_SLP
mdefine_line|#define  FISR3_SLP&t;0x01
multiline_comment|/* GIS  (Global Interrupt Status Register)&n;&n;   --------------------- E1 &amp; T1 --------------------- */
DECL|macro|GIS_ISR3
mdefine_line|#define  GIS_ISR3&t;0x08
DECL|macro|GIS_ISR2
mdefine_line|#define  GIS_ISR2&t;0x04
DECL|macro|GIS_ISR1
mdefine_line|#define  GIS_ISR1&t;0x02
DECL|macro|GIS_ISR0
mdefine_line|#define  GIS_ISR0&t;0x01
multiline_comment|/* VSTR  (Version Status Register)&n;&n;   --------------------- E1 &amp; T1 --------------------- */
DECL|macro|VSTR_VN3
mdefine_line|#define  VSTR_VN3&t;0x08
DECL|macro|VSTR_VN2
mdefine_line|#define  VSTR_VN2&t;0x04
DECL|macro|VSTR_VN1
mdefine_line|#define  VSTR_VN1&t;0x02
DECL|macro|VSTR_VN0
mdefine_line|#define  VSTR_VN0&t;0x01
multiline_comment|/*&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;  Local Control Structures  &lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt; */
multiline_comment|/* Write-only Registers (E1/T1 control mode write registers) */
DECL|macro|XFIFOH
mdefine_line|#define XFIFOH&t;0x00&t;&t;/* Tx FIFO High Byte */
DECL|macro|XFIFOL
mdefine_line|#define XFIFOL&t;0x01&t;&t;/* Tx FIFO Low Byte */
DECL|macro|CMDR
mdefine_line|#define CMDR&t;0x02&t;&t;/* Command Reg */
DECL|macro|DEC
mdefine_line|#define DEC&t;0x60&t;&t;/* Disable Error Counter */
DECL|macro|TEST2
mdefine_line|#define TEST2&t;0x62&t;&t;/* Manuf. Test Reg 2 */
DECL|macro|XS
mdefine_line|#define XS(nbr)&t;(0x70 + (nbr))&t;/* Tx CAS Reg (0 to 15) */
multiline_comment|/* Read-write Registers (E1/T1 status mode read registers) */
DECL|macro|MODE
mdefine_line|#define MODE&t;0x03&t;/* Mode Reg */
DECL|macro|RAH1
mdefine_line|#define RAH1&t;0x04&t;/* Receive Address High 1 */
DECL|macro|RAH2
mdefine_line|#define RAH2&t;0x05&t;/* Receive Address High 2 */
DECL|macro|RAL1
mdefine_line|#define RAL1&t;0x06&t;/* Receive Address Low 1 */
DECL|macro|RAL2
mdefine_line|#define RAL2&t;0x07&t;/* Receive Address Low 2 */
DECL|macro|IPC
mdefine_line|#define IPC&t;0x08&t;/* Interrupt Port Configuration */
DECL|macro|CCR1
mdefine_line|#define CCR1&t;0x09&t;/* Common Configuration Reg 1 */
DECL|macro|CCR3
mdefine_line|#define CCR3&t;0x0A&t;/* Common Configuration Reg 3 */
DECL|macro|PRE
mdefine_line|#define PRE&t;0x0B&t;/* Preamble Reg */
DECL|macro|RTR1
mdefine_line|#define RTR1&t;0x0C&t;/* Receive Timeslot Reg 1 */
DECL|macro|RTR2
mdefine_line|#define RTR2&t;0x0D&t;/* Receive Timeslot Reg 2 */
DECL|macro|RTR3
mdefine_line|#define RTR3&t;0x0E&t;/* Receive Timeslot Reg 3 */
DECL|macro|RTR4
mdefine_line|#define RTR4&t;0x0F&t;/* Receive Timeslot Reg 4 */
DECL|macro|TTR1
mdefine_line|#define TTR1&t;0x10&t;/* Transmit Timeslot Reg 1 */
DECL|macro|TTR2
mdefine_line|#define TTR2&t;0x11&t;/* Transmit Timeslot Reg 2 */
DECL|macro|TTR3
mdefine_line|#define TTR3&t;0x12&t;/* Transmit Timeslot Reg 3 */
DECL|macro|TTR4
mdefine_line|#define TTR4&t;0x13&t;/* Transmit Timeslot Reg 4 */
DECL|macro|IMR0
mdefine_line|#define IMR0&t;0x14&t;/* Interrupt Mask Reg 0 */
DECL|macro|IMR1
mdefine_line|#define IMR1&t;0x15&t;/* Interrupt Mask Reg 1 */
DECL|macro|IMR2
mdefine_line|#define IMR2&t;0x16&t;/* Interrupt Mask Reg 2 */
DECL|macro|IMR3
mdefine_line|#define IMR3&t;0x17&t;/* Interrupt Mask Reg 3 */
DECL|macro|IMR4
mdefine_line|#define IMR4&t;0x18&t;/* Interrupt Mask Reg 4 */
DECL|macro|IMR5
mdefine_line|#define IMR5&t;0x19&t;/* Interrupt Mask Reg 5 */
DECL|macro|FMR0
mdefine_line|#define FMR0&t;0x1A&t;/* Framer Mode Reigster 0 */
DECL|macro|FMR1
mdefine_line|#define FMR1&t;0x1B&t;/* Framer Mode Reigster 1 */
DECL|macro|FMR2
mdefine_line|#define FMR2&t;0x1C&t;/* Framer Mode Reigster 2 */
DECL|macro|LOOP
mdefine_line|#define LOOP&t;0x1D&t;/* Channel Loop Back */
DECL|macro|XSW
mdefine_line|#define XSW&t;0x1E&t;/* Transmit Service Word */
DECL|macro|FMR4
mdefine_line|#define FMR4&t;0x1E&t;/* Framer Mode Reg 4 */
DECL|macro|XSP
mdefine_line|#define XSP&t;0x1F&t;/* Transmit Spare Bits */
DECL|macro|FMR5
mdefine_line|#define FMR5&t;0x1F&t;/* Framer Mode Reg 5 */
DECL|macro|XC0
mdefine_line|#define XC0&t;0x20&t;/* Transmit Control 0 */
DECL|macro|XC1
mdefine_line|#define XC1&t;0x21&t;/* Transmit Control 1 */
DECL|macro|RC0
mdefine_line|#define RC0&t;0x22&t;/* Receive Control 0 */
DECL|macro|RC1
mdefine_line|#define RC1&t;0x23&t;/* Receive Control 1 */
DECL|macro|XPM0
mdefine_line|#define XPM0&t;0x24&t;/* Transmit Pulse Mask 0 */
DECL|macro|XPM1
mdefine_line|#define XPM1&t;0x25&t;/* Transmit Pulse Mask 1 */
DECL|macro|XPM2
mdefine_line|#define XPM2&t;0x26&t;/* Transmit Pulse Mask 2 */
DECL|macro|TSWM
mdefine_line|#define TSWM&t;0x27&t;/* Transparent Service Word Mask */
DECL|macro|TEST1
mdefine_line|#define TEST1&t;0x28&t;/* Manuf. Test Reg 1 */
DECL|macro|IDLE
mdefine_line|#define IDLE&t;0x29&t;/* Idle Channel Code */
DECL|macro|XSA4
mdefine_line|#define XSA4    0x2A&t;/* Transmit SA4 Bit Reg */
DECL|macro|XDL1
mdefine_line|#define XDL1&t;0x2A&t;/* Transmit DL-Bit Reg 2 */
DECL|macro|XSA5
mdefine_line|#define XSA5    0x2B&t;/* Transmit SA4 Bit Reg */
DECL|macro|XDL2
mdefine_line|#define XDL2&t;0x2B&t;/* Transmit DL-Bit Reg 2 */
DECL|macro|XSA6
mdefine_line|#define XSA6    0x2C&t;/* Transmit SA4 Bit Reg */
DECL|macro|XDL3
mdefine_line|#define XDL3&t;0x2C&t;/* Transmit DL-Bit Reg 2 */
DECL|macro|XSA7
mdefine_line|#define XSA7    0x2D&t;/* Transmit SA4 Bit Reg */
DECL|macro|CCB1
mdefine_line|#define CCB1&t;0x2D&t;/* Clear Channel Reg 1 */
DECL|macro|XSA8
mdefine_line|#define XSA8    0x2E&t;/* Transmit SA4 Bit Reg */
DECL|macro|CCB2
mdefine_line|#define CCB2&t;0x2E&t;/* Clear Channel Reg 2 */
DECL|macro|FMR3
mdefine_line|#define FMR3&t;0x2F&t;/* Framer Mode Reg. 3 */
DECL|macro|CCB3
mdefine_line|#define CCB3&t;0x2F&t;/* Clear Channel Reg 3 */
DECL|macro|ICB1
mdefine_line|#define ICB1&t;0x30&t;/* Idle Channel Reg 1 */
DECL|macro|ICB2
mdefine_line|#define ICB2&t;0x31&t;/* Idle Channel Reg 2 */
DECL|macro|ICB3
mdefine_line|#define ICB3&t;0x32&t;/* Idle Channel Reg 3 */
DECL|macro|ICB4
mdefine_line|#define ICB4&t;0x33&t;/* Idle Channel Reg 4 */
DECL|macro|LIM0
mdefine_line|#define LIM0&t;0x34&t;/* Line Interface Mode 0 */
DECL|macro|LIM1
mdefine_line|#define LIM1&t;0x35&t;/* Line Interface Mode 1 */
DECL|macro|PCDR
mdefine_line|#define PCDR&t;0x36&t;/* Pulse Count Detection */
DECL|macro|PCRR
mdefine_line|#define PCRR&t;0x37&t;/* Pulse Count Recovery */
DECL|macro|LIM2
mdefine_line|#define LIM2&t;0x38&t;/* Line Interface Mode Reg 2 */
DECL|macro|LCR1
mdefine_line|#define LCR1&t;0x39&t;/* Loop Code Reg 1 */
DECL|macro|LCR2
mdefine_line|#define LCR2&t;0x3A&t;/* Loop Code Reg 2 */
DECL|macro|LCR3
mdefine_line|#define LCR3&t;0x3B&t;/* Loop Code Reg 3 */
DECL|macro|SIC1
mdefine_line|#define SIC1&t;0x3C&t;/* System Interface Control 1 */
multiline_comment|/* Read-only Registers (E1/T1 control mode read registers) */
DECL|macro|RFIFOH
mdefine_line|#define RFIFOH&t;0x00&t;&t;/* Receive FIFO */
DECL|macro|RFIFOL
mdefine_line|#define RFIFOL&t;0x01&t;&t;/* Receive FIFO */
DECL|macro|FRS0
mdefine_line|#define FRS0&t;0x4C&t;&t;/* Framer Receive Status 0 */
DECL|macro|FRS1
mdefine_line|#define FRS1&t;0x4D&t;&t;/* Framer Receive Status 1 */
DECL|macro|RSW
mdefine_line|#define RSW&t;0x4E&t;&t;/* Receive Service Word */
DECL|macro|FRS2
mdefine_line|#define FRS2&t;0x4E&t;&t;/* Framer Receive Status 2 */
DECL|macro|RSP
mdefine_line|#define RSP&t;0x4F&t;&t;/* Receive Spare Bits */
DECL|macro|FRS3
mdefine_line|#define FRS3&t;0x4F&t;&t;/* Framer Receive Status 3 */
DECL|macro|FECL
mdefine_line|#define FECL&t;0x50&t;&t;/* Framing Error Counter */
DECL|macro|FECH
mdefine_line|#define FECH&t;0x51&t;&t;/* Framing Error Counter */
DECL|macro|CVCL
mdefine_line|#define CVCL&t;0x52&t;&t;/* Code Violation Counter */
DECL|macro|CVCH
mdefine_line|#define CVCH&t;0x53&t;&t;/* Code Violation Counter */
DECL|macro|CECL
mdefine_line|#define CECL&t;0x54&t;&t;/* CRC Error Counter 1 */
DECL|macro|CECH
mdefine_line|#define CECH&t;0x55&t;&t;/* CRC Error Counter 1 */
DECL|macro|EBCL
mdefine_line|#define EBCL&t;0x56&t;&t;/* E-Bit Error Counter */
DECL|macro|EBCH
mdefine_line|#define EBCH&t;0x57&t;&t;/* E-Bit Error Counter */
DECL|macro|BECL
mdefine_line|#define BECL&t;0x58&t;&t;/* Bit Error Counter Low */
DECL|macro|BECH
mdefine_line|#define BECH&t;0x59&t;&t;/* Bit Error Counter Low */
DECL|macro|CEC3
mdefine_line|#define CEC3&t;0x5A&t;&t;/* CRC Error Counter 3 (16-bit) */
DECL|macro|RSA4
mdefine_line|#define RSA4&t;0x5C&t;&t;/* Receive SA4 Bit Reg */
DECL|macro|RDL1
mdefine_line|#define RDL1&t;0x5C&t;&t;/* Receive DL-Bit Reg 1 */
DECL|macro|RSA5
mdefine_line|#define RSA5&t;0x5D&t;&t;/* Receive SA5 Bit Reg */
DECL|macro|RDL2
mdefine_line|#define RDL2&t;0x5D&t;&t;/* Receive DL-Bit Reg 2 */
DECL|macro|RSA6
mdefine_line|#define RSA6&t;0x5E&t;&t;/* Receive SA6 Bit Reg */
DECL|macro|RDL3
mdefine_line|#define RDL3&t;0x5E&t;&t;/* Receive DL-Bit Reg 3 */
DECL|macro|RSA7
mdefine_line|#define RSA7&t;0x5F&t;&t;/* Receive SA7 Bit Reg */
DECL|macro|RSA8
mdefine_line|#define RSA8&t;0x60&t;&t;/* Receive SA8 Bit Reg */
DECL|macro|RSA6S
mdefine_line|#define RSA6S&t;0x61&t;&t;/* Receive SA6 Bit Status Reg */
DECL|macro|TSR0
mdefine_line|#define TSR0&t;0x62&t;&t;/* Manuf. Test Reg 0 */
DECL|macro|TSR1
mdefine_line|#define TSR1&t;0x63&t;&t;/* Manuf. Test Reg 1 */
DECL|macro|SIS
mdefine_line|#define SIS&t;0x64&t;&t;/* Signaling Status Reg */
DECL|macro|RSIS
mdefine_line|#define RSIS&t;0x65&t;&t;/* Receive Signaling Status Reg */
DECL|macro|RBCL
mdefine_line|#define RBCL&t;0x66&t;&t;/* Receive Byte Control */
DECL|macro|RBCH
mdefine_line|#define RBCH&t;0x67&t;&t;/* Receive Byte Control */
DECL|macro|FISR0
mdefine_line|#define FISR0&t;0x68&t;&t;/* Interrupt Status Reg 0 */
DECL|macro|FISR1
mdefine_line|#define FISR1&t;0x69&t;&t;/* Interrupt Status Reg 1 */
DECL|macro|FISR2
mdefine_line|#define FISR2&t;0x6A&t;&t;/* Interrupt Status Reg 2 */
DECL|macro|FISR3
mdefine_line|#define FISR3&t;0x6B&t;&t;/* Interrupt Status Reg 3 */
DECL|macro|GIS
mdefine_line|#define GIS&t;0x6E&t;&t;/* Global Interrupt Status */
DECL|macro|VSTR
mdefine_line|#define VSTR&t;0x6F&t;&t;/* Version Status */
DECL|macro|RS
mdefine_line|#define RS(nbr)&t;(0x70 + (nbr))&t;/* Rx CAS Reg (0 to 15) */
macro_line|#endif&t;/* _FALC_LH_H */
eof
