multiline_comment|/*&n;    Written 1994 by David C. Davies.&n;&n;    Copyright 1994 David C. Davies. This software may be used and distributed&n;    according to the terms of the GNU Public License, incorporated herein by&n;    reference.&n;*/
multiline_comment|/*&n;** I/O addresses. Note that the 2k buffer option is not supported in&n;** this driver.&n;*/
DECL|macro|DEPCA_NICSR
mdefine_line|#define DEPCA_NICSR ioaddr+0x00   /* Network interface CSR */
DECL|macro|DEPCA_RBI
mdefine_line|#define DEPCA_RBI   ioaddr+0x02   /* RAM buffer index (2k buffer mode) */
DECL|macro|DEPCA_DATA
mdefine_line|#define DEPCA_DATA  ioaddr+0x04   /* LANCE registers&squot; data port */
DECL|macro|DEPCA_ADDR
mdefine_line|#define DEPCA_ADDR  ioaddr+0x06   /* LANCE registers&squot; address port */
DECL|macro|DEPCA_HBASE
mdefine_line|#define DEPCA_HBASE ioaddr+0x08   /* EISA high memory base address reg. */
DECL|macro|DEPCA_PROM
mdefine_line|#define DEPCA_PROM  ioaddr+0x0c   /* Ethernet address ROM data port */
DECL|macro|DEPCA_CNFG
mdefine_line|#define DEPCA_CNFG  ioaddr+0x0c   /* EISA Configuration port */
DECL|macro|DEPCA_RBSA
mdefine_line|#define DEPCA_RBSA  ioaddr+0x0e   /* RAM buffer starting address (2k buff.) */
multiline_comment|/*&n;** These are LANCE registers addressable through DEPCA_ADDR &n;*/
DECL|macro|CSR0
mdefine_line|#define CSR0       0
DECL|macro|CSR1
mdefine_line|#define CSR1       1
DECL|macro|CSR2
mdefine_line|#define CSR2       2
DECL|macro|CSR3
mdefine_line|#define CSR3       3
multiline_comment|/* &n;** NETWORK INTERFACE CSR (NI_CSR) bit definitions &n;*/
DECL|macro|TO
mdefine_line|#define TO       &t;0x0100&t;/* Time Out for remote boot */
DECL|macro|SHE
mdefine_line|#define SHE      &t;0x0080  /* SHadow memory Enable */
DECL|macro|BS
mdefine_line|#define BS       &t;0x0040  /* Bank Select */
DECL|macro|BUF
mdefine_line|#define BUF      &t;0x0020&t;/* BUFfer size (1-&gt;32k, 0-&gt;64k) */
DECL|macro|RBE
mdefine_line|#define RBE      &t;0x0010&t;/* Remote Boot Enable (1-&gt;net boot) */
DECL|macro|AAC
mdefine_line|#define AAC      &t;0x0008  /* Address ROM Address Counter (1-&gt;enable) */
DECL|macro|_128KB
mdefine_line|#define _128KB      &t;0x0008  /* 128kB Network RAM (1-&gt;enable) */
DECL|macro|IM
mdefine_line|#define IM       &t;0x0004&t;/* Interrupt Mask (1-&gt;mask) */
DECL|macro|IEN
mdefine_line|#define IEN      &t;0x0002&t;/* Interrupt tristate ENable (1-&gt;enable) */
DECL|macro|LED
mdefine_line|#define LED      &t;0x0001&t;/* LED control */
multiline_comment|/* &n;** Control and Status Register 0 (CSR0) bit definitions &n;*/
DECL|macro|ERR
mdefine_line|#define ERR     &t;0x8000 &t;/* Error summary */
DECL|macro|BABL
mdefine_line|#define BABL    &t;0x4000 &t;/* Babble transmitter timeout error  */
DECL|macro|CERR
mdefine_line|#define CERR    &t;0x2000 &t;/* Collision Error */
DECL|macro|MISS
mdefine_line|#define MISS    &t;0x1000 &t;/* Missed packet */
DECL|macro|MERR
mdefine_line|#define MERR    &t;0x0800 &t;/* Memory Error */
DECL|macro|RINT
mdefine_line|#define RINT    &t;0x0400 &t;/* Receiver Interrupt */
DECL|macro|TINT
mdefine_line|#define TINT    &t;0x0200 &t;/* Transmit Interrupt */
DECL|macro|IDON
mdefine_line|#define IDON    &t;0x0100 &t;/* Initialization Done */
DECL|macro|INTR
mdefine_line|#define INTR    &t;0x0080 &t;/* Interrupt Flag */
DECL|macro|INEA
mdefine_line|#define INEA    &t;0x0040 &t;/* Interrupt Enable */
DECL|macro|RXON
mdefine_line|#define RXON    &t;0x0020 &t;/* Receiver on */
DECL|macro|TXON
mdefine_line|#define TXON    &t;0x0010 &t;/* Transmitter on */
DECL|macro|TDMD
mdefine_line|#define TDMD    &t;0x0008 &t;/* Transmit Demand */
DECL|macro|STOP
mdefine_line|#define STOP    &t;0x0004 &t;/* Stop */
DECL|macro|STRT
mdefine_line|#define STRT    &t;0x0002 &t;/* Start */
DECL|macro|INIT
mdefine_line|#define INIT    &t;0x0001 &t;/* Initialize */
DECL|macro|INTM
mdefine_line|#define INTM            0xff00  /* Interrupt Mask */
DECL|macro|INTE
mdefine_line|#define INTE            0xfff0  /* Interrupt Enable */
multiline_comment|/*&n;** CONTROL AND STATUS REGISTER 3 (CSR3)&n;*/
DECL|macro|BSWP
mdefine_line|#define BSWP    &t;0x0004&t;/* Byte SWaP */
DECL|macro|ACON
mdefine_line|#define ACON    &t;0x0002&t;/* ALE control */
DECL|macro|BCON
mdefine_line|#define BCON    &t;0x0001&t;/* Byte CONtrol */
multiline_comment|/*&n;** Initialization Block Mode Register &n;*/
DECL|macro|PROM
mdefine_line|#define PROM       &t;0x8000 &t;/* Promiscuous Mode */
DECL|macro|EMBA
mdefine_line|#define EMBA       &t;0x0080&t;/* Enable Modified Back-off Algorithm */
DECL|macro|INTL
mdefine_line|#define INTL       &t;0x0040 &t;/* Internal Loopback */
DECL|macro|DRTY
mdefine_line|#define DRTY       &t;0x0020 &t;/* Disable Retry */
DECL|macro|COLL
mdefine_line|#define COLL       &t;0x0010 &t;/* Force Collision */
DECL|macro|DTCR
mdefine_line|#define DTCR       &t;0x0008 &t;/* Disable Transmit CRC */
DECL|macro|LOOP
mdefine_line|#define LOOP       &t;0x0004 &t;/* Loopback */
DECL|macro|DTX
mdefine_line|#define DTX        &t;0x0002 &t;/* Disable the Transmitter */
DECL|macro|DRX
mdefine_line|#define DRX        &t;0x0001 &t;/* Disable the Receiver */
multiline_comment|/*&n;** Receive Message Descriptor 1 (RMD1) bit definitions. &n;*/
DECL|macro|R_OWN
mdefine_line|#define R_OWN       0x80000000 &t;/* Owner bit 0 = host, 1 = lance */
DECL|macro|R_ERR
mdefine_line|#define R_ERR     &t;0x4000 &t;/* Error Summary */
DECL|macro|R_FRAM
mdefine_line|#define R_FRAM    &t;0x2000 &t;/* Framing Error */
DECL|macro|R_OFLO
mdefine_line|#define R_OFLO    &t;0x1000 &t;/* Overflow Error */
DECL|macro|R_CRC
mdefine_line|#define R_CRC     &t;0x0800 &t;/* CRC Error */
DECL|macro|R_BUFF
mdefine_line|#define R_BUFF    &t;0x0400 &t;/* Buffer Error */
DECL|macro|R_STP
mdefine_line|#define R_STP     &t;0x0200 &t;/* Start of Packet */
DECL|macro|R_ENP
mdefine_line|#define R_ENP     &t;0x0100 &t;/* End of Packet */
multiline_comment|/*&n;** Transmit Message Descriptor 1 (TMD1) bit definitions. &n;*/
DECL|macro|T_OWN
mdefine_line|#define T_OWN       0x80000000 &t;/* Owner bit 0 = host, 1 = lance */
DECL|macro|T_ERR
mdefine_line|#define T_ERR     &t;0x4000 &t;/* Error Summary */
DECL|macro|T_ADD_FCS
mdefine_line|#define T_ADD_FCS &t;0x2000 &t;/* More the 1 retry needed to Xmit */
DECL|macro|T_MORE
mdefine_line|#define T_MORE    &t;0x1000&t;/* &gt;1 retry to transmit packet */
DECL|macro|T_ONE
mdefine_line|#define T_ONE     &t;0x0800 &t;/* 1 try needed to transmit the packet */
DECL|macro|T_DEF
mdefine_line|#define T_DEF     &t;0x0400 &t;/* Deferred */
DECL|macro|T_STP
mdefine_line|#define T_STP       0x02000000 &t;/* Start of Packet */
DECL|macro|T_ENP
mdefine_line|#define T_ENP       0x01000000&t;/* End of Packet */
DECL|macro|T_FLAGS
mdefine_line|#define T_FLAGS     0xff000000  /* TX Flags Field */
multiline_comment|/*&n;** Transmit Message Descriptor 3 (TMD3) bit definitions.&n;*/
DECL|macro|TMD3_BUFF
mdefine_line|#define TMD3_BUFF    0x8000&t;/* BUFFer error */
DECL|macro|TMD3_UFLO
mdefine_line|#define TMD3_UFLO    0x4000&t;/* UnderFLOw error */
DECL|macro|TMD3_RES
mdefine_line|#define TMD3_RES     0x2000&t;/* REServed */
DECL|macro|TMD3_LCOL
mdefine_line|#define TMD3_LCOL    0x1000&t;/* Late COLlision */
DECL|macro|TMD3_LCAR
mdefine_line|#define TMD3_LCAR    0x0800&t;/* Loss of CARrier */
DECL|macro|TMD3_RTRY
mdefine_line|#define TMD3_RTRY    0x0400&t;/* ReTRY error */
multiline_comment|/* &n;** EISA configuration Register (CNFG) bit definitions &n;*/
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT       &t;0x0100&t;/* 0:2.5 mins, 1: 30 secs */
DECL|macro|REMOTE
mdefine_line|#define REMOTE      &t;0x0080  /* Remote Boot Enable -&gt; 1 */
DECL|macro|IRQ11
mdefine_line|#define IRQ11       &t;0x0040  /* Enable -&gt; 1 */
DECL|macro|IRQ10
mdefine_line|#define IRQ10    &t;0x0020&t;/* Enable -&gt; 1 */
DECL|macro|IRQ9
mdefine_line|#define IRQ9    &t;0x0010&t;/* Enable -&gt; 1 */
DECL|macro|IRQ5
mdefine_line|#define IRQ5      &t;0x0008  /* Enable -&gt; 1 */
DECL|macro|BUFF
mdefine_line|#define BUFF     &t;0x0004&t;/* 0: 64kB or 128kB, 1: 32kB */
DECL|macro|PADR16
mdefine_line|#define PADR16   &t;0x0002&t;/* RAM on 64kB boundary */
DECL|macro|PADR17
mdefine_line|#define PADR17    &t;0x0001&t;/* RAM on 128kB boundary */
multiline_comment|/*&n;** Miscellaneous&n;*/
DECL|macro|HASH_TABLE_LEN
mdefine_line|#define HASH_TABLE_LEN   64           /* Bits */
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS        0x003f       /* 6 LS bits */
DECL|macro|MASK_INTERRUPTS
mdefine_line|#define MASK_INTERRUPTS   1
DECL|macro|UNMASK_INTERRUPTS
mdefine_line|#define UNMASK_INTERRUPTS 0
DECL|macro|EISA_EN
mdefine_line|#define EISA_EN         0x0001        /* Enable EISA bus buffers */
DECL|macro|EISA_ID
mdefine_line|#define EISA_ID         iobase+0x0080 /* ID long word for EISA card */
DECL|macro|EISA_CTRL
mdefine_line|#define EISA_CTRL       iobase+0x0084 /* Control word for EISA card */
multiline_comment|/*&n;** Include the IOCTL stuff&n;*/
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|DEPCAIOCTL
mdefine_line|#define&t;DEPCAIOCTL&t;SIOCDEVPRIVATE
DECL|struct|depca_ioctl
r_struct
id|depca_ioctl
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
DECL|macro|DEPCA_GET_HWADDR
mdefine_line|#define DEPCA_GET_HWADDR&t;0x01 /* Get the hardware address */
DECL|macro|DEPCA_SET_HWADDR
mdefine_line|#define DEPCA_SET_HWADDR&t;0x02 /* Get the hardware address */
DECL|macro|DEPCA_SET_PROM
mdefine_line|#define DEPCA_SET_PROM  &t;0x03 /* Set Promiscuous Mode */
DECL|macro|DEPCA_CLR_PROM
mdefine_line|#define DEPCA_CLR_PROM  &t;0x04 /* Clear Promiscuous Mode */
DECL|macro|DEPCA_SAY_BOO
mdefine_line|#define DEPCA_SAY_BOO&t;        0x05 /* Say &quot;Boo!&quot; to the kernel log file */
DECL|macro|DEPCA_GET_MCA
mdefine_line|#define DEPCA_GET_MCA   &t;0x06 /* Get a multicast address */
DECL|macro|DEPCA_SET_MCA
mdefine_line|#define DEPCA_SET_MCA   &t;0x07 /* Set a multicast address */
DECL|macro|DEPCA_CLR_MCA
mdefine_line|#define DEPCA_CLR_MCA    &t;0x08 /* Clear a multicast address */
DECL|macro|DEPCA_MCA_EN
mdefine_line|#define DEPCA_MCA_EN    &t;0x09 /* Enable a multicast address group */
DECL|macro|DEPCA_GET_STATS
mdefine_line|#define DEPCA_GET_STATS  &t;0x0a /* Get the driver statistics */
DECL|macro|DEPCA_CLR_STATS
mdefine_line|#define DEPCA_CLR_STATS &t;0x0b /* Zero out the driver statistics */
DECL|macro|DEPCA_GET_REG
mdefine_line|#define DEPCA_GET_REG   &t;0x0c /* Get the Register contents */
DECL|macro|DEPCA_SET_REG
mdefine_line|#define DEPCA_SET_REG   &t;0x0d /* Set the Register contents */
DECL|macro|DEPCA_DUMP
mdefine_line|#define DEPCA_DUMP              0x0f /* Dump the DEPCA Status */
eof
