multiline_comment|/*&n; * mace.h - definitions for the registers in the Am79C940 MACE&n; * (Medium Access Control for Ethernet) controller.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|REG
mdefine_line|#define REG(x)&t;volatile unsigned char x; char x ## _pad[15]
DECL|struct|mace
r_struct
id|mace
(brace
id|REG
c_func
(paren
id|rcvfifo
)paren
suffix:semicolon
multiline_comment|/* receive FIFO */
id|REG
c_func
(paren
id|xmtfifo
)paren
suffix:semicolon
multiline_comment|/* transmit FIFO */
id|REG
c_func
(paren
id|xmtfc
)paren
suffix:semicolon
multiline_comment|/* transmit frame control */
id|REG
c_func
(paren
id|xmtfs
)paren
suffix:semicolon
multiline_comment|/* transmit frame status */
id|REG
c_func
(paren
id|xmtrc
)paren
suffix:semicolon
multiline_comment|/* transmit retry count */
id|REG
c_func
(paren
id|rcvfc
)paren
suffix:semicolon
multiline_comment|/* receive frame control */
id|REG
c_func
(paren
id|rcvfs
)paren
suffix:semicolon
multiline_comment|/* receive frame status (4 bytes) */
id|REG
c_func
(paren
id|fifofc
)paren
suffix:semicolon
multiline_comment|/* FIFO frame count */
id|REG
c_func
(paren
id|ir
)paren
suffix:semicolon
multiline_comment|/* interrupt register */
id|REG
c_func
(paren
id|imr
)paren
suffix:semicolon
multiline_comment|/* interrupt mask register */
id|REG
c_func
(paren
id|pr
)paren
suffix:semicolon
multiline_comment|/* poll register */
id|REG
c_func
(paren
id|biucc
)paren
suffix:semicolon
multiline_comment|/* bus interface unit config control */
id|REG
c_func
(paren
id|fifocc
)paren
suffix:semicolon
multiline_comment|/* FIFO configuration control */
id|REG
c_func
(paren
id|maccc
)paren
suffix:semicolon
multiline_comment|/* medium access control config control */
id|REG
c_func
(paren
id|plscc
)paren
suffix:semicolon
multiline_comment|/* phys layer signalling config control */
id|REG
c_func
(paren
id|phycc
)paren
suffix:semicolon
multiline_comment|/* physical configuration control */
id|REG
c_func
(paren
id|chipid_lo
)paren
suffix:semicolon
multiline_comment|/* chip ID, lsb */
id|REG
c_func
(paren
id|chipid_hi
)paren
suffix:semicolon
multiline_comment|/* chip ID, msb */
id|REG
c_func
(paren
id|iac
)paren
suffix:semicolon
multiline_comment|/* internal address config */
id|REG
c_func
(paren
id|reg19
)paren
suffix:semicolon
id|REG
c_func
(paren
id|ladrf
)paren
suffix:semicolon
multiline_comment|/* logical address filter (8 bytes) */
id|REG
c_func
(paren
id|padr
)paren
suffix:semicolon
multiline_comment|/* physical address (6 bytes) */
id|REG
c_func
(paren
id|reg22
)paren
suffix:semicolon
id|REG
c_func
(paren
id|reg23
)paren
suffix:semicolon
id|REG
c_func
(paren
id|mpc
)paren
suffix:semicolon
multiline_comment|/* missed packet count (clears when read) */
id|REG
c_func
(paren
id|reg25
)paren
suffix:semicolon
id|REG
c_func
(paren
id|rntpc
)paren
suffix:semicolon
multiline_comment|/* runt packet count (clears when read) */
id|REG
c_func
(paren
id|rcvcc
)paren
suffix:semicolon
multiline_comment|/* recv collision count (clears when read) */
id|REG
c_func
(paren
id|reg28
)paren
suffix:semicolon
id|REG
c_func
(paren
id|utr
)paren
suffix:semicolon
multiline_comment|/* user test reg */
id|REG
c_func
(paren
id|reg30
)paren
suffix:semicolon
id|REG
c_func
(paren
id|reg31
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bits in XMTFC */
DECL|macro|DRTRY
mdefine_line|#define DRTRY&t;&t;0x80&t;/* don&squot;t retry transmission after collision */
DECL|macro|DXMTFCS
mdefine_line|#define DXMTFCS&t;&t;0x08&t;/* don&squot;t append FCS to transmitted frame */
DECL|macro|AUTO_PAD_XMIT
mdefine_line|#define AUTO_PAD_XMIT&t;0x01&t;/* auto-pad short packets on transmission */
multiline_comment|/* Bits in XMTFS: only valid when XMTSV is set in PR and XMTFS */
DECL|macro|XMTSV
mdefine_line|#define XMTSV&t;&t;0x80&t;/* transmit status (i.e. XMTFS) valid */
DECL|macro|UFLO
mdefine_line|#define UFLO&t;&t;0x40&t;/* underflow - xmit fifo ran dry */
DECL|macro|LCOL
mdefine_line|#define LCOL&t;&t;0x20&t;/* late collision (transmission aborted) */
DECL|macro|MORE
mdefine_line|#define MORE&t;&t;0x10&t;/* 2 or more retries needed to xmit frame */
DECL|macro|ONE
mdefine_line|#define ONE&t;&t;0x08&t;/* 1 retry needed to xmit frame */
DECL|macro|DEFER
mdefine_line|#define DEFER&t;&t;0x04&t;/* MACE had to defer xmission (enet busy) */
DECL|macro|LCAR
mdefine_line|#define LCAR&t;&t;0x02&t;/* loss of carrier (transmission aborted) */
DECL|macro|RTRY
mdefine_line|#define RTRY&t;&t;0x01&t;/* too many retries (transmission aborted) */
multiline_comment|/* Bits in XMTRC: only valid when XMTSV is set in PR (and XMTFS) */
DECL|macro|EXDEF
mdefine_line|#define EXDEF&t;&t;0x80&t;/* had to defer for excessive time */
DECL|macro|RETRY_MASK
mdefine_line|#define RETRY_MASK&t;0x0f&t;/* number of retries (0 - 15) */
multiline_comment|/* Bits in RCVFC */
DECL|macro|LLRCV
mdefine_line|#define LLRCV&t;&t;0x08&t;/* low latency receive: early DMA request */
DECL|macro|M_RBAR
mdefine_line|#define M_RBAR&t;&t;0x04&t;/* sets function of EAM/R pin */
DECL|macro|AUTO_STRIP_RCV
mdefine_line|#define AUTO_STRIP_RCV&t;0x01&t;/* auto-strip short LLC frames on recv */
multiline_comment|/*&n; * Bits in RCVFS.  After a frame is received, four bytes of status&n; * are automatically read from this register and appended to the frame&n; * data in memory.  These are:&n; * Byte 0 and 1: message byte count and frame status&n; * Byte 2: runt packet count&n; * Byte 3: receive collision count&n; */
DECL|macro|RS_OFLO
mdefine_line|#define RS_OFLO&t;&t;0x8000&t;/* receive FIFO overflowed */
DECL|macro|RS_CLSN
mdefine_line|#define RS_CLSN&t;&t;0x4000&t;/* received frame suffered (late) collision */
DECL|macro|RS_FRAMERR
mdefine_line|#define RS_FRAMERR&t;0x2000&t;/* framing error flag */
DECL|macro|RS_FCSERR
mdefine_line|#define RS_FCSERR&t;0x1000&t;/* frame had FCS error */
DECL|macro|RS_COUNT
mdefine_line|#define RS_COUNT&t;0x0fff&t;/* mask for byte count field */
multiline_comment|/* Bits (fields) in FIFOFC */
DECL|macro|RCVFC_SH
mdefine_line|#define RCVFC_SH&t;4&t;/* receive frame count in FIFO */
DECL|macro|RCVFC_MASK
mdefine_line|#define RCVFC_MASK&t;0x0f
DECL|macro|XMTFC_SH
mdefine_line|#define XMTFC_SH&t;0&t;/* transmit frame count in FIFO */
DECL|macro|XMTFC_MASK
mdefine_line|#define XMTFC_MASK&t;0x0f
multiline_comment|/*&n; * Bits in IR and IMR.  The IR clears itself when read.&n; * Setting a bit in the IMR will disable the corresponding interrupt.&n; */
DECL|macro|JABBER
mdefine_line|#define JABBER&t;&t;0x80&t;/* jabber error - 10baseT xmission too long */
DECL|macro|BABBLE
mdefine_line|#define BABBLE&t;&t;0x40&t;/* babble - xmitter xmitting for too long */
DECL|macro|CERR
mdefine_line|#define CERR&t;&t;0x20&t;/* collision err - no SQE test (heartbeat) */
DECL|macro|RCVCCO
mdefine_line|#define RCVCCO&t;&t;0x10&t;/* RCVCC overflow */
DECL|macro|RNTPCO
mdefine_line|#define RNTPCO&t;&t;0x08&t;/* RNTPC overflow */
DECL|macro|MPCO
mdefine_line|#define MPCO&t;&t;0x04&t;/* MPC overflow */
DECL|macro|RCVINT
mdefine_line|#define RCVINT&t;&t;0x02&t;/* receive interrupt */
DECL|macro|XMTINT
mdefine_line|#define XMTINT&t;&t;0x01&t;/* transmitter interrupt */
multiline_comment|/* Bits in PR */
DECL|macro|XMTSV
mdefine_line|#define XMTSV&t;&t;0x80&t;/* XMTFS valid (same as in XMTFS) */
DECL|macro|TDTREQ
mdefine_line|#define TDTREQ&t;&t;0x40&t;/* set when xmit fifo is requesting data */
DECL|macro|RDTREQ
mdefine_line|#define RDTREQ&t;&t;0x20&t;/* set when recv fifo requests data xfer */
multiline_comment|/* Bits in BIUCC */
DECL|macro|BSWP
mdefine_line|#define BSWP&t;&t;0x40&t;/* byte swap, i.e. big-endian bus */
DECL|macro|XMTSP_4
mdefine_line|#define XMTSP_4&t;&t;0x00&t;/* start xmitting when 4 bytes in FIFO */
DECL|macro|XMTSP_16
mdefine_line|#define XMTSP_16&t;0x10&t;/* start xmitting when 16 bytes in FIFO */
DECL|macro|XMTSP_64
mdefine_line|#define XMTSP_64&t;0x20&t;/* start xmitting when 64 bytes in FIFO */
DECL|macro|XMTSP_112
mdefine_line|#define XMTSP_112&t;0x30&t;/* start xmitting when 112 bytes in FIFO */
DECL|macro|SWRST
mdefine_line|#define SWRST&t;&t;0x01&t;/* software reset */
multiline_comment|/* Bits in FIFOCC */
DECL|macro|XMTFW_8
mdefine_line|#define XMTFW_8&t;&t;0x00&t;/* xmit fifo watermark = 8 words free */
DECL|macro|XMTFW_16
mdefine_line|#define XMTFW_16&t;0x40&t;/*  16 words free */
DECL|macro|XMTFW_32
mdefine_line|#define XMTFW_32&t;0x80&t;/*  32 words free */
DECL|macro|RCVFW_16
mdefine_line|#define RCVFW_16&t;0x00&t;/* recv fifo watermark = 16 bytes avail */
DECL|macro|RCVFW_32
mdefine_line|#define RCVFW_32&t;0x10&t;/*  32 bytes avail */
DECL|macro|RCVFW_64
mdefine_line|#define RCVFW_64&t;0x20&t;/*  64 bytes avail */
DECL|macro|XMTFWU
mdefine_line|#define XMTFWU&t;&t;0x08&t;/* xmit fifo watermark update enable */
DECL|macro|RCVFWU
mdefine_line|#define RCVFWU&t;&t;0x04&t;/* recv fifo watermark update enable */
DECL|macro|XMTBRST
mdefine_line|#define XMTBRST&t;&t;0x02&t;/* enable transmit burst mode */
DECL|macro|RCVBRST
mdefine_line|#define RCVBRST&t;&t;0x01&t;/* enable receive burst mode */
multiline_comment|/* Bits in MACCC */
DECL|macro|PROM
mdefine_line|#define PROM&t;&t;0x80&t;/* promiscuous mode */
DECL|macro|DXMT2PD
mdefine_line|#define DXMT2PD&t;&t;0x40&t;/* disable xmit two-part deferral algorithm */
DECL|macro|EMBA
mdefine_line|#define EMBA&t;&t;0x20&t;/* enable modified backoff algorithm */
DECL|macro|DRCVPA
mdefine_line|#define DRCVPA&t;&t;0x08&t;/* disable receiving physical address */
DECL|macro|DRCVBC
mdefine_line|#define DRCVBC&t;&t;0x04&t;/* disable receiving broadcasts */
DECL|macro|ENXMT
mdefine_line|#define ENXMT&t;&t;0x02&t;/* enable transmitter */
DECL|macro|ENRCV
mdefine_line|#define ENRCV&t;&t;0x01&t;/* enable receiver */
multiline_comment|/* Bits in PLSCC */
DECL|macro|XMTSEL
mdefine_line|#define XMTSEL&t;&t;0x08&t;/* select DO+/DO- state when idle */
DECL|macro|PORTSEL_AUI
mdefine_line|#define PORTSEL_AUI&t;0x00&t;/* select AUI port */
DECL|macro|PORTSEL_10T
mdefine_line|#define PORTSEL_10T&t;0x02&t;/* select 10Base-T port */
DECL|macro|PORTSEL_DAI
mdefine_line|#define PORTSEL_DAI&t;0x04&t;/* select DAI port */
DECL|macro|PORTSEL_GPSI
mdefine_line|#define PORTSEL_GPSI&t;0x06&t;/* select GPSI port */
DECL|macro|ENPLSIO
mdefine_line|#define ENPLSIO&t;&t;0x01&t;/* enable optional PLS I/O pins */
multiline_comment|/* Bits in PHYCC */
DECL|macro|LNKFL
mdefine_line|#define LNKFL&t;&t;0x80&t;/* reports 10Base-T link failure */
DECL|macro|DLNKTST
mdefine_line|#define DLNKTST&t;&t;0x40&t;/* disable 10Base-T link test */
DECL|macro|REVPOL
mdefine_line|#define REVPOL&t;&t;0x20&t;/* 10Base-T receiver polarity reversed */
DECL|macro|DAPC
mdefine_line|#define DAPC&t;&t;0x10&t;/* disable auto receiver polarity correction */
DECL|macro|LRT
mdefine_line|#define LRT&t;&t;0x08&t;/* low receive threshold for long links */
DECL|macro|ASEL
mdefine_line|#define ASEL&t;&t;0x04&t;/* auto-select AUI or 10Base-T port */
DECL|macro|RWAKE
mdefine_line|#define RWAKE&t;&t;0x02&t;/* remote wake function */
DECL|macro|AWAKE
mdefine_line|#define AWAKE&t;&t;0x01&t;/* auto wake function */
multiline_comment|/* Bits in IAC */
DECL|macro|ADDRCHG
mdefine_line|#define ADDRCHG&t;&t;0x80&t;/* request address change */
DECL|macro|PHYADDR
mdefine_line|#define PHYADDR&t;&t;0x04&t;/* access physical address */
DECL|macro|LOGADDR
mdefine_line|#define LOGADDR&t;&t;0x02&t;/* access multicast filter */
multiline_comment|/* Bits in UTR */
DECL|macro|RTRE
mdefine_line|#define RTRE&t;&t;0x80&t;/* reserved test register enable. DON&squot;T SET. */
DECL|macro|RTRD
mdefine_line|#define RTRD&t;&t;0x40&t;/* reserved test register disable.  Sticky */
DECL|macro|RPAC
mdefine_line|#define RPAC&t;&t;0x20&t;/* accept runt packets */
DECL|macro|FCOLL
mdefine_line|#define FCOLL&t;&t;0x10&t;/* force collision */
DECL|macro|RCVFCSE
mdefine_line|#define RCVFCSE&t;&t;0x08&t;/* receive FCS enable */
DECL|macro|LOOP_NONE
mdefine_line|#define LOOP_NONE&t;0x00&t;/* no loopback */
DECL|macro|LOOP_EXT
mdefine_line|#define LOOP_EXT&t;0x02&t;/* external loopback */
DECL|macro|LOOP_INT
mdefine_line|#define LOOP_INT&t;0x04&t;/* internal loopback, excludes MENDEC */
DECL|macro|LOOP_MENDEC
mdefine_line|#define LOOP_MENDEC&t;0x06&t;/* internal loopback, includes MENDEC */
eof
