multiline_comment|/*&n;    Written 1994 by David C. Davies.&n;&n;    Copyright 1994 Digital Equipment Corporation.&n;&n;    This software may be used and distributed according to  the terms of the&n;    GNU Public License, incorporated herein by reference.&n;&n;    The author may    be  reached as davies@wanton.lkg.dec.com  or   Digital&n;    Equipment Corporation, 550 King Street, Littleton MA 01460.&n;&n;    =========================================================================&n;*/
multiline_comment|/*&n;** I/O Address Register Map&n;*/
DECL|macro|EWRK3_CSR
mdefine_line|#define EWRK3_CSR    iobase+0x00   /* Control and Status Register */
DECL|macro|EWRK3_CR
mdefine_line|#define EWRK3_CR     iobase+0x01   /* Control Register */
DECL|macro|EWRK3_ICR
mdefine_line|#define EWRK3_ICR    iobase+0x02   /* Interrupt Control Register */
DECL|macro|EWRK3_TSR
mdefine_line|#define EWRK3_TSR    iobase+0x03   /* Transmit Status Register */
DECL|macro|EWRK3_RSVD1
mdefine_line|#define EWRK3_RSVD1  iobase+0x04   /* RESERVED */
DECL|macro|EWRK3_RSVD2
mdefine_line|#define EWRK3_RSVD2  iobase+0x05   /* RESERVED */
DECL|macro|EWRK3_FMQ
mdefine_line|#define EWRK3_FMQ    iobase+0x06   /* Free Memory Queue */
DECL|macro|EWRK3_FMQC
mdefine_line|#define EWRK3_FMQC   iobase+0x07   /* Free Memory Queue Counter */
DECL|macro|EWRK3_RQ
mdefine_line|#define EWRK3_RQ     iobase+0x08   /* Receive Queue */
DECL|macro|EWRK3_RQC
mdefine_line|#define EWRK3_RQC    iobase+0x09   /* Receive Queue Counter */
DECL|macro|EWRK3_TQ
mdefine_line|#define EWRK3_TQ     iobase+0x0a   /* Transmit Queue */
DECL|macro|EWRK3_TQC
mdefine_line|#define EWRK3_TQC    iobase+0x0b   /* Transmit Queue Counter */
DECL|macro|EWRK3_TDQ
mdefine_line|#define EWRK3_TDQ    iobase+0x0c   /* Transmit Done Queue */
DECL|macro|EWRK3_TDQC
mdefine_line|#define EWRK3_TDQC   iobase+0x0d   /* Transmit Done Queue Counter */
DECL|macro|EWRK3_PIR1
mdefine_line|#define EWRK3_PIR1   iobase+0x0e   /* Page Index Register 1 */
DECL|macro|EWRK3_PIR2
mdefine_line|#define EWRK3_PIR2   iobase+0x0f   /* Page Index Register 2 */
DECL|macro|EWRK3_DATA
mdefine_line|#define EWRK3_DATA   iobase+0x10   /* Data Register */
DECL|macro|EWRK3_IOPR
mdefine_line|#define EWRK3_IOPR   iobase+0x11   /* I/O Page Register */
DECL|macro|EWRK3_IOBR
mdefine_line|#define EWRK3_IOBR   iobase+0x12   /* I/O Base Register */
DECL|macro|EWRK3_MPR
mdefine_line|#define EWRK3_MPR    iobase+0x13   /* Memory Page Register */
DECL|macro|EWRK3_MBR
mdefine_line|#define EWRK3_MBR    iobase+0x14   /* Memory Base Register */
DECL|macro|EWRK3_APROM
mdefine_line|#define EWRK3_APROM  iobase+0x15   /* Address PROM */
DECL|macro|EWRK3_EPROM1
mdefine_line|#define EWRK3_EPROM1 iobase+0x16   /* EEPROM Data Register 1 */
DECL|macro|EWRK3_EPROM2
mdefine_line|#define EWRK3_EPROM2 iobase+0x17   /* EEPROM Data Register 2 */
DECL|macro|EWRK3_PAR0
mdefine_line|#define EWRK3_PAR0   iobase+0x18   /* Physical Address Register 0 */
DECL|macro|EWRK3_PAR1
mdefine_line|#define EWRK3_PAR1   iobase+0x19   /* Physical Address Register 1 */
DECL|macro|EWRK3_PAR2
mdefine_line|#define EWRK3_PAR2   iobase+0x1a   /* Physical Address Register 2 */
DECL|macro|EWRK3_PAR3
mdefine_line|#define EWRK3_PAR3   iobase+0x1b   /* Physical Address Register 3 */
DECL|macro|EWRK3_PAR4
mdefine_line|#define EWRK3_PAR4   iobase+0x1c   /* Physical Address Register 4 */
DECL|macro|EWRK3_PAR5
mdefine_line|#define EWRK3_PAR5   iobase+0x1d   /* Physical Address Register 5 */
DECL|macro|EWRK3_CMR
mdefine_line|#define EWRK3_CMR    iobase+0x1e   /* Configuration/Management Register */
multiline_comment|/*&n;** Control Page Map&n;*/
DECL|macro|PAGE0_FMQ
mdefine_line|#define PAGE0_FMQ     0x000         /* Free Memory Queue */
DECL|macro|PAGE0_RQ
mdefine_line|#define PAGE0_RQ      0x080         /* Receive Queue */
DECL|macro|PAGE0_TQ
mdefine_line|#define PAGE0_TQ      0x100         /* Transmit Queue */
DECL|macro|PAGE0_TDQ
mdefine_line|#define PAGE0_TDQ     0x180         /* Transmit Done Queue */
DECL|macro|PAGE0_HTE
mdefine_line|#define PAGE0_HTE     0x200         /* Hash Table Entries */
DECL|macro|PAGE0_RSVD
mdefine_line|#define PAGE0_RSVD    0x240         /* RESERVED */
DECL|macro|PAGE0_USRD
mdefine_line|#define PAGE0_USRD    0x600         /* User Data */
multiline_comment|/*&n;** Control and Status Register bit definitions (EWRK3_CSR)&n;*/
DECL|macro|CSR_RA
mdefine_line|#define CSR_RA&t;&t;0x80&t;    /* Runt Accept */
DECL|macro|CSR_PME
mdefine_line|#define CSR_PME&t;&t;0x40&t;    /* Promiscuous Mode Enable */
DECL|macro|CSR_MCE
mdefine_line|#define CSR_MCE&t;&t;0x20&t;    /* Multicast Enable */ 
DECL|macro|CSR_TNE
mdefine_line|#define CSR_TNE&t;&t;0x08&t;    /* TX Done Queue Not Empty */
DECL|macro|CSR_RNE
mdefine_line|#define CSR_RNE&t;&t;0x04&t;    /* RX Queue Not Empty */
DECL|macro|CSR_TXD
mdefine_line|#define CSR_TXD&t;&t;0x02&t;    /* TX Disable */
DECL|macro|CSR_RXD
mdefine_line|#define CSR_RXD&t;&t;0x01&t;    /* RX Disable */
multiline_comment|/*&n;** Control Register bit definitions (EWRK3_CR)&n;*/
DECL|macro|CR_APD
mdefine_line|#define CR_APD&t;&t;0x80&t;/* Auto Port Disable */
DECL|macro|CR_PSEL
mdefine_line|#define CR_PSEL&t;&t;0x40&t;/* Port Select (0-&gt;TP port) */
DECL|macro|CR_LBCK
mdefine_line|#define CR_LBCK&t;&t;0x20&t;/* LoopBaCK enable */
DECL|macro|CR_FDUP
mdefine_line|#define CR_FDUP&t;&t;0x10&t;/* Full DUPlex enable */
DECL|macro|CR_FBUS
mdefine_line|#define CR_FBUS&t;&t;0x08&t;/* Fast BUS enable (ISA clk &gt; 8.33MHz) */
DECL|macro|CR_EN_16
mdefine_line|#define CR_EN_16&t;0x04&t;/* ENable 16 bit memory accesses */
DECL|macro|CR_LED
mdefine_line|#define CR_LED&t;&t;0x02&t;/* LED (1-&gt; turn on) */
multiline_comment|/*&n;** Interrupt Control Register bit definitions (EWRK3_ICR)&n;*/
DECL|macro|ICR_IE
mdefine_line|#define ICR_IE&t;&t;0x80&t;/* Interrupt Enable */
DECL|macro|ICR_IS
mdefine_line|#define ICR_IS&t;&t;0x60&t;/* Interrupt Selected */
DECL|macro|ICR_TNEM
mdefine_line|#define ICR_TNEM&t;0x08&t;/* TNE Mask (0-&gt;mask) */
DECL|macro|ICR_RNEM
mdefine_line|#define ICR_RNEM&t;0x04&t;/* RNE Mask (0-&gt;mask) */
DECL|macro|ICR_TXDM
mdefine_line|#define ICR_TXDM&t;0x02&t;/* TXD Mask (0-&gt;mask) */
DECL|macro|ICR_RXDM
mdefine_line|#define ICR_RXDM&t;0x01&t;/* RXD Mask (0-&gt;mask) */
multiline_comment|/*&n;** Transmit Status Register bit definitions (EWRK3_TSR)&n;*/
DECL|macro|TSR_NCL
mdefine_line|#define TSR_NCL&t;&t;0x80&t;/* No Carrier Loopback */
DECL|macro|TSR_ID
mdefine_line|#define TSR_ID&t;&t;0x40&t;/* Initially Deferred */
DECL|macro|TSR_LCL
mdefine_line|#define TSR_LCL&t;&t;0x20&t;/* Late CoLlision */
DECL|macro|TSR_ECL
mdefine_line|#define TSR_ECL&t;&t;0x10&t;/* Excessive CoLlisions */
DECL|macro|TSR_RCNTR
mdefine_line|#define TSR_RCNTR&t;0x0f&t;/* Retries CouNTeR */
multiline_comment|/*&n;** I/O Page Register bit definitions (EWRK3_IOPR)&n;*/
DECL|macro|EEPROM_INIT
mdefine_line|#define EEPROM_INIT&t;0xc0&t;/* EEPROM INIT command */
DECL|macro|EEPROM_WR_EN
mdefine_line|#define EEPROM_WR_EN&t;0xc8&t;/* EEPROM WRITE ENABLE command */
DECL|macro|EEPROM_WR
mdefine_line|#define EEPROM_WR&t;0xd0&t;/* EEPROM WRITE command */
DECL|macro|EEPROM_WR_DIS
mdefine_line|#define EEPROM_WR_DIS&t;0xd8&t;/* EEPROM WRITE DISABLE command */
DECL|macro|EEPROM_RD
mdefine_line|#define EEPROM_RD&t;0xe0&t;/* EEPROM READ command */
multiline_comment|/*&n;** I/O Base Register bit definitions (EWRK3_IOBR)&n;*/
DECL|macro|EISA_REGS_EN
mdefine_line|#define EISA_REGS_EN&t;0x20&t;/* Enable EISA ID and Control Registers */
DECL|macro|EISA_IOB
mdefine_line|#define EISA_IOB        0x1f&t;/* Compare bits for I/O Base Address */
multiline_comment|/*&n;** I/O Configuration/Management Register bit definitions (EWRK3_CMR)&n;*/
DECL|macro|CMR_RA
mdefine_line|#define CMR_RA          0x80    /* Read Ahead */
DECL|macro|CMR_WB
mdefine_line|#define CMR_WB          0x40    /* Write Behind */
DECL|macro|CMR_LINK
mdefine_line|#define CMR_LINK        0x20&t;/* 0-&gt;TP */
DECL|macro|CMR_POLARITY
mdefine_line|#define CMR_POLARITY    0x10&t;/* Informational */
DECL|macro|CMR_NO_EEPROM
mdefine_line|#define CMR_NO_EEPROM&t;0x0c&t;/* NO_EEPROM&lt;1:0&gt; pin status */
DECL|macro|CMR_HS
mdefine_line|#define CMR_HS          0x08&t;/* Hard Strapped pin status (LeMAC2) */
DECL|macro|CMR_PNP
mdefine_line|#define CMR_PNP         0x04    /* Plug &squot;n Play */
DECL|macro|CMR_DRAM
mdefine_line|#define CMR_DRAM        0x02&t;/* 0-&gt; 1DRAM, 1-&gt; 2 DRAM on board */
DECL|macro|CMR_0WS
mdefine_line|#define CMR_0WS         0x01    /* Zero Wait State */
multiline_comment|/* &n;** MAC Receive Status Register bit definitions&n;*/
DECL|macro|R_ROK
mdefine_line|#define R_ROK     &t;0x80 &t;/* Receive OK summary */
DECL|macro|R_IAM
mdefine_line|#define R_IAM     &t;0x10 &t;/* Individual Address Match */
DECL|macro|R_MCM
mdefine_line|#define R_MCM     &t;0x08 &t;/* MultiCast Match */
DECL|macro|R_DBE
mdefine_line|#define R_DBE     &t;0x04 &t;/* Dribble Bit Error */
DECL|macro|R_CRC
mdefine_line|#define R_CRC     &t;0x02 &t;/* CRC error */
DECL|macro|R_PLL
mdefine_line|#define R_PLL     &t;0x01 &t;/* Phase Lock Lost */
multiline_comment|/* &n;** MAC Transmit Control Register bit definitions&n;*/
DECL|macro|TCR_SQEE
mdefine_line|#define TCR_SQEE    &t;0x40 &t;/* SQE Enable - look for heartbeat  */
DECL|macro|TCR_SED
mdefine_line|#define TCR_SED     &t;0x20 &t;/* Stop when Error Detected */
DECL|macro|TCR_QMODE
mdefine_line|#define TCR_QMODE     &t;0x10 &t;/* Q_MODE */
DECL|macro|TCR_LAB
mdefine_line|#define TCR_LAB         0x08 &t;/* Less Aggressive Backoff */
DECL|macro|TCR_PAD
mdefine_line|#define TCR_PAD     &t;0x04 &t;/* PAD Runt Packets */
DECL|macro|TCR_IFC
mdefine_line|#define TCR_IFC     &t;0x02 &t;/* Insert Frame Check */
DECL|macro|TCR_ISA
mdefine_line|#define TCR_ISA     &t;0x01 &t;/* Insert Source Address */
multiline_comment|/* &n;** MAC Transmit Status Register bit definitions&n;*/
DECL|macro|T_VSTS
mdefine_line|#define T_VSTS    &t;0x80 &t;/* Valid STatuS */
DECL|macro|T_CTU
mdefine_line|#define T_CTU     &t;0x40 &t;/* Cut Through Used */
DECL|macro|T_SQE
mdefine_line|#define T_SQE     &t;0x20 &t;/* Signal Quality Error */
DECL|macro|T_NCL
mdefine_line|#define T_NCL     &t;0x10 &t;/* No Carrier Loopback */
DECL|macro|T_LCL
mdefine_line|#define T_LCL           0x08 &t;/* Late Collision */
DECL|macro|T_ID
mdefine_line|#define T_ID      &t;0x04 &t;/* Initially Deferred */
DECL|macro|T_COLL
mdefine_line|#define T_COLL     &t;0x03 &t;/* COLLision status */
DECL|macro|T_XCOLL
mdefine_line|#define T_XCOLL         0x03    /* Excessive Collisions */
DECL|macro|T_MCOLL
mdefine_line|#define T_MCOLL         0x02    /* Multiple Collisions */
DECL|macro|T_OCOLL
mdefine_line|#define T_OCOLL         0x01    /* One Collision */
DECL|macro|T_NOCOLL
mdefine_line|#define T_NOCOLL        0x00    /* No Collisions */
DECL|macro|T_XUR
mdefine_line|#define T_XUR           0x03    /* Excessive Underruns */
DECL|macro|T_TXE
mdefine_line|#define T_TXE           0x7f    /* TX Errors */
multiline_comment|/* &n;** EISA Configuration Register bit definitions &n;*/
DECL|macro|EISA_ID
mdefine_line|#define EISA_ID       iobase + 0x0c80  /* EISA ID Registers */ 
DECL|macro|EISA_ID0
mdefine_line|#define EISA_ID0      iobase + 0x0c80  /* EISA ID Register 0 */ 
DECL|macro|EISA_ID1
mdefine_line|#define EISA_ID1      iobase + 0x0c81  /* EISA ID Register 1 */ 
DECL|macro|EISA_ID2
mdefine_line|#define EISA_ID2      iobase + 0x0c82  /* EISA ID Register 2 */ 
DECL|macro|EISA_ID3
mdefine_line|#define EISA_ID3      iobase + 0x0c83  /* EISA ID Register 3 */ 
DECL|macro|EISA_CR
mdefine_line|#define EISA_CR       iobase + 0x0c84  /* EISA Control Register */
multiline_comment|/*&n;** EEPROM BYTES&n;*/
DECL|macro|EEPROM_MEMB
mdefine_line|#define EEPROM_MEMB     0x00
DECL|macro|EEPROM_IOB
mdefine_line|#define EEPROM_IOB      0x01
DECL|macro|EEPROM_EISA_ID0
mdefine_line|#define EEPROM_EISA_ID0 0x02
DECL|macro|EEPROM_EISA_ID1
mdefine_line|#define EEPROM_EISA_ID1 0x03
DECL|macro|EEPROM_EISA_ID2
mdefine_line|#define EEPROM_EISA_ID2 0x04
DECL|macro|EEPROM_EISA_ID3
mdefine_line|#define EEPROM_EISA_ID3 0x05
DECL|macro|EEPROM_MISC0
mdefine_line|#define EEPROM_MISC0    0x06
DECL|macro|EEPROM_MISC1
mdefine_line|#define EEPROM_MISC1    0x07
DECL|macro|EEPROM_PNAME7
mdefine_line|#define EEPROM_PNAME7   0x08
DECL|macro|EEPROM_PNAME6
mdefine_line|#define EEPROM_PNAME6   0x09
DECL|macro|EEPROM_PNAME5
mdefine_line|#define EEPROM_PNAME5   0x0a
DECL|macro|EEPROM_PNAME4
mdefine_line|#define EEPROM_PNAME4   0x0b
DECL|macro|EEPROM_PNAME3
mdefine_line|#define EEPROM_PNAME3   0x0c
DECL|macro|EEPROM_PNAME2
mdefine_line|#define EEPROM_PNAME2   0x0d
DECL|macro|EEPROM_PNAME1
mdefine_line|#define EEPROM_PNAME1   0x0e
DECL|macro|EEPROM_PNAME0
mdefine_line|#define EEPROM_PNAME0   0x0f
DECL|macro|EEPROM_SWFLAGS
mdefine_line|#define EEPROM_SWFLAGS  0x10
DECL|macro|EEPROM_HWCAT
mdefine_line|#define EEPROM_HWCAT    0x11
DECL|macro|EEPROM_NETMAN2
mdefine_line|#define EEPROM_NETMAN2  0x12
DECL|macro|EEPROM_REVLVL
mdefine_line|#define EEPROM_REVLVL   0x13
DECL|macro|EEPROM_NETMAN0
mdefine_line|#define EEPROM_NETMAN0  0x14
DECL|macro|EEPROM_NETMAN1
mdefine_line|#define EEPROM_NETMAN1  0x15
DECL|macro|EEPROM_CHIPVER
mdefine_line|#define EEPROM_CHIPVER  0x16
DECL|macro|EEPROM_SETUP
mdefine_line|#define EEPROM_SETUP    0x17
DECL|macro|EEPROM_PADDR0
mdefine_line|#define EEPROM_PADDR0   0x18
DECL|macro|EEPROM_PADDR1
mdefine_line|#define EEPROM_PADDR1   0x19
DECL|macro|EEPROM_PADDR2
mdefine_line|#define EEPROM_PADDR2   0x1a
DECL|macro|EEPROM_PADDR3
mdefine_line|#define EEPROM_PADDR3   0x1b
DECL|macro|EEPROM_PADDR4
mdefine_line|#define EEPROM_PADDR4   0x1c
DECL|macro|EEPROM_PADDR5
mdefine_line|#define EEPROM_PADDR5   0x1d
DECL|macro|EEPROM_PA_CRC
mdefine_line|#define EEPROM_PA_CRC   0x1e
DECL|macro|EEPROM_CHKSUM
mdefine_line|#define EEPROM_CHKSUM   0x1f
multiline_comment|/*&n;** EEPROM bytes for checksumming&n;*/
DECL|macro|EEPROM_MAX
mdefine_line|#define EEPROM_MAX      32             /* bytes */
multiline_comment|/*&n;** EEPROM MISCELLANEOUS FLAGS&n;*/
DECL|macro|RBE_SHADOW
mdefine_line|#define RBE_SHADOW&t;0x0100&t;/* Remote Boot Enable Shadow */ 
DECL|macro|READ_AHEAD
mdefine_line|#define READ_AHEAD      0x0080  /* Read Ahead feature */
DECL|macro|IRQ_SEL2
mdefine_line|#define IRQ_SEL2        0x0070  /* IRQ line selection (LeMAC2) */
DECL|macro|IRQ_SEL
mdefine_line|#define IRQ_SEL         0x0060  /* IRQ line selection */
DECL|macro|FAST_BUS
mdefine_line|#define FAST_BUS        0x0008  /* ISA Bus speeds &gt; 8.33MHz */
DECL|macro|ENA_16
mdefine_line|#define ENA_16          0x0004  /* Enables 16 bit memory transfers */
DECL|macro|WRITE_BEHIND
mdefine_line|#define WRITE_BEHIND    0x0002  /* Write Behind feature */
DECL|macro|_0WS_ENA
mdefine_line|#define _0WS_ENA        0x0001  /* Zero Wait State Enable */
multiline_comment|/*&n;** EEPROM NETWORK MANAGEMENT FLAGS&n;*/
DECL|macro|NETMAN_POL
mdefine_line|#define NETMAN_POL      0x04    /* Polarity defeat */
DECL|macro|NETMAN_LINK
mdefine_line|#define NETMAN_LINK     0x02    /* Link defeat */
DECL|macro|NETMAN_CCE
mdefine_line|#define NETMAN_CCE      0x01    /* Custom Counters Enable */
multiline_comment|/*&n;** EEPROM SW FLAGS&n;*/
DECL|macro|SW_SQE
mdefine_line|#define SW_SQE&t;&t;0x10&t;/* Signal Quality Error */ 
DECL|macro|SW_LAB
mdefine_line|#define SW_LAB&t;&t;0x08&t;/* Less Aggressive Backoff */
DECL|macro|SW_INIT
mdefine_line|#define SW_INIT&t;&t;0x04&t;/* Initialized */
DECL|macro|SW_TIMEOUT
mdefine_line|#define SW_TIMEOUT     &t;0x02&t;/* 0:2.5 mins, 1: 30 secs */
DECL|macro|SW_REMOTE
mdefine_line|#define SW_REMOTE      &t;0x01    /* Remote Boot Enable -&gt; 1 */
multiline_comment|/*&n;** EEPROM SETUP FLAGS&n;*/
DECL|macro|SETUP_APD
mdefine_line|#define SETUP_APD&t;0x80&t;/* AutoPort Disable */
DECL|macro|SETUP_PS
mdefine_line|#define SETUP_PS&t;0x40&t;/* Port Select */
DECL|macro|SETUP_MP
mdefine_line|#define SETUP_MP&t;0x20&t;/* MultiPort */
DECL|macro|SETUP_1TP
mdefine_line|#define SETUP_1TP&t;0x10&t;/* 1 port, TP */
DECL|macro|SETUP_1COAX
mdefine_line|#define SETUP_1COAX&t;0x00&t;/* 1 port, Coax */
DECL|macro|SETUP_DRAM
mdefine_line|#define SETUP_DRAM&t;0x02&t;/* Number of DRAMS on board */
multiline_comment|/*&n;** EEPROM MANAGEMENT FLAGS&n;*/
DECL|macro|MGMT_CCE
mdefine_line|#define MGMT_CCE&t;0x01&t;/* Custom Counters Enable */
multiline_comment|/*&n;** EEPROM VERSIONS&n;*/
DECL|macro|LeMAC
mdefine_line|#define LeMAC           0x11
DECL|macro|LeMAC2
mdefine_line|#define LeMAC2          0x12
multiline_comment|/*&n;** Miscellaneous&n;*/
DECL|macro|EEPROM_WAIT_TIME
mdefine_line|#define EEPROM_WAIT_TIME 1000    /* Number of microseconds */
DECL|macro|EISA_EN
mdefine_line|#define EISA_EN         0x0001   /* Enable EISA bus buffers */
DECL|macro|HASH_TABLE_LEN
mdefine_line|#define HASH_TABLE_LEN   512     /* Bits */
DECL|macro|XCT
mdefine_line|#define XCT 0x80                 /* Transmit Cut Through */
DECL|macro|PRELOAD
mdefine_line|#define PRELOAD 16               /* 4 long words */
DECL|macro|MASK_INTERRUPTS
mdefine_line|#define MASK_INTERRUPTS   1
DECL|macro|UNMASK_INTERRUPTS
mdefine_line|#define UNMASK_INTERRUPTS 0
DECL|macro|EEPROM_OFFSET
mdefine_line|#define EEPROM_OFFSET(a) ((u_short)((u_long)(a)))
multiline_comment|/*&n;** Include the IOCTL stuff&n;*/
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|EWRK3IOCTL
mdefine_line|#define&t;EWRK3IOCTL&t;SIOCDEVPRIVATE
DECL|struct|ewrk3_ioctl
r_struct
id|ewrk3_ioctl
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
multiline_comment|/* Command to run */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of the data buffer */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to the data buffer */
)brace
suffix:semicolon
multiline_comment|/* &n;** Recognised commands for the driver &n;*/
DECL|macro|EWRK3_GET_HWADDR
mdefine_line|#define EWRK3_GET_HWADDR&t;0x01 /* Get the hardware address */
DECL|macro|EWRK3_SET_HWADDR
mdefine_line|#define EWRK3_SET_HWADDR&t;0x02 /* Get the hardware address */
DECL|macro|EWRK3_SET_PROM
mdefine_line|#define EWRK3_SET_PROM  &t;0x03 /* Set Promiscuous Mode */
DECL|macro|EWRK3_CLR_PROM
mdefine_line|#define EWRK3_CLR_PROM  &t;0x04 /* Clear Promiscuous Mode */
DECL|macro|EWRK3_SAY_BOO
mdefine_line|#define EWRK3_SAY_BOO&t;        0x05 /* Say &quot;Boo!&quot; to the kernel log file */
DECL|macro|EWRK3_GET_MCA
mdefine_line|#define EWRK3_GET_MCA   &t;0x06 /* Get a multicast address */
DECL|macro|EWRK3_SET_MCA
mdefine_line|#define EWRK3_SET_MCA   &t;0x07 /* Set a multicast address */
DECL|macro|EWRK3_CLR_MCA
mdefine_line|#define EWRK3_CLR_MCA    &t;0x08 /* Clear a multicast address */
DECL|macro|EWRK3_MCA_EN
mdefine_line|#define EWRK3_MCA_EN    &t;0x09 /* Enable a multicast address group */
DECL|macro|EWRK3_GET_STATS
mdefine_line|#define EWRK3_GET_STATS  &t;0x0a /* Get the driver statistics */
DECL|macro|EWRK3_CLR_STATS
mdefine_line|#define EWRK3_CLR_STATS &t;0x0b /* Zero out the driver statistics */
DECL|macro|EWRK3_GET_CSR
mdefine_line|#define EWRK3_GET_CSR   &t;0x0c /* Get the CSR Register contents */
DECL|macro|EWRK3_SET_CSR
mdefine_line|#define EWRK3_SET_CSR   &t;0x0d /* Set the CSR Register contents */
DECL|macro|EWRK3_GET_EEPROM
mdefine_line|#define EWRK3_GET_EEPROM   &t;0x0e /* Get the EEPROM contents */
DECL|macro|EWRK3_SET_EEPROM
mdefine_line|#define EWRK3_SET_EEPROM&t;0x0f /* Set the EEPROM contents */
DECL|macro|EWRK3_GET_CMR
mdefine_line|#define EWRK3_GET_CMR   &t;0x10 /* Get the CMR Register contents */
DECL|macro|EWRK3_CLR_TX_CUT_THRU
mdefine_line|#define EWRK3_CLR_TX_CUT_THRU  &t;0x11 /* Clear the TX cut through mode */
DECL|macro|EWRK3_SET_TX_CUT_THRU
mdefine_line|#define EWRK3_SET_TX_CUT_THRU&t;0x12 /* Set the TX cut through mode */
eof
