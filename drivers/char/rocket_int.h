multiline_comment|/*&n; * rocket_int.h --- internal header file for rocket.c&n; *&n; * Written by Theodore Ts&squot;o, Copyright 1997.&n; *&n; * Portions of this file are....&n; * &n; * Copyright 1994 Comtrol Corporation.    All Rights Reserved.&n; * &n; * The following source code is subject to Comtrol Corporation&squot;s&n; * Developer&squot;s License Agreement.&n; * &n; * This source code is protected by United States copyright law and &n; * international copyright treaties.&n; * &n; * This source code may only be used to develop software products that&n; * will operate with Comtrol brand hardware.&n; * &n; * You may not reproduce nor distribute this source code in its original&n; * form but must produce a derivative work which includes portions of&n; * this source code only.&n; * &n; * The portions of this source code which you use in your derivative&n; * work must bear Comtrol&squot;s copyright notice:&n; * &n; * &t;&t;Copyright 1994 Comtrol Corporation.&n; * &n; */
multiline_comment|/*&n; * Begin Comtrol-provided headers, et. al.&n; */
multiline_comment|/*&n;&t;user definitions for Rocket Toolkit&n;&n;&t;The following typedefs and defines must be established&n;&t;depending on the platform the toolkit is being used&n;&t;with.&n;&n;*/
multiline_comment|/************************************************************&n;The following sets up the world for use with Linux&n;************************************************************/
macro_line|#include &lt;asm/io.h&gt;
DECL|typedef|Byte_t
r_typedef
r_int
r_char
id|Byte_t
suffix:semicolon
DECL|typedef|ByteIO_t
r_typedef
r_int
r_int
id|ByteIO_t
suffix:semicolon
DECL|typedef|Word_t
r_typedef
r_int
r_int
id|Word_t
suffix:semicolon
DECL|typedef|WordIO_t
r_typedef
r_int
r_int
id|WordIO_t
suffix:semicolon
DECL|typedef|DWord_t
r_typedef
r_int
r_int
id|DWord_t
suffix:semicolon
DECL|typedef|DWordIO_t
r_typedef
r_int
r_int
id|DWordIO_t
suffix:semicolon
DECL|macro|sOutB
mdefine_line|#define sOutB(a, b) outb_p(b, a)
DECL|macro|sOutW
mdefine_line|#define sOutW(a, b) outw_p(b, a)
DECL|macro|sOutDW
mdefine_line|#define sOutDW(a, b) outl_p(b, a)
DECL|macro|sInB
mdefine_line|#define sInB(a) (inb_p(a))
DECL|macro|sInW
mdefine_line|#define sInW(a) (inw_p(a))
DECL|macro|sOutStrW
mdefine_line|#define sOutStrW(port, addr, count) outsw(port, addr, count)
DECL|macro|sInStrW
mdefine_line|#define sInStrW(port, addr, count) insw(port, addr, count)
DECL|macro|CTL_SIZE
mdefine_line|#define CTL_SIZE 4
DECL|macro|AIOP_CTL_SIZE
mdefine_line|#define AIOP_CTL_SIZE 4
DECL|macro|CHAN_AIOP_SIZE
mdefine_line|#define CHAN_AIOP_SIZE 8
DECL|macro|MAX_PORTS_PER_AIOP
mdefine_line|#define MAX_PORTS_PER_AIOP 8
DECL|macro|MAX_AIOPS_PER_BOARD
mdefine_line|#define MAX_AIOPS_PER_BOARD 4
DECL|macro|MAX_PORTS_PER_BOARD
mdefine_line|#define MAX_PORTS_PER_BOARD 32
multiline_comment|/* Bus type ID */
DECL|macro|isISA
mdefine_line|#define&t;isISA&t;0
DECL|macro|isPCI
mdefine_line|#define&t;isPCI&t;1
DECL|macro|isMC
mdefine_line|#define&t;isMC&t;2
multiline_comment|/* Controller ID numbers */
DECL|macro|CTLID_NULL
mdefine_line|#define CTLID_NULL  -1              /* no controller exists */
DECL|macro|CTLID_0001
mdefine_line|#define CTLID_0001  0x0001          /* controller release 1 */
multiline_comment|/* AIOP ID numbers, identifies AIOP type implementing channel */
DECL|macro|AIOPID_NULL
mdefine_line|#define AIOPID_NULL -1              /* no AIOP or channel exists */
DECL|macro|AIOPID_0001
mdefine_line|#define AIOPID_0001 0x0001          /* AIOP release 1 */
DECL|macro|NULLDEV
mdefine_line|#define NULLDEV -1                  /* identifies non-existant device */
DECL|macro|NULLCTL
mdefine_line|#define NULLCTL -1                  /* identifies non-existant controller */
DECL|macro|NULLCTLPTR
mdefine_line|#define NULLCTLPTR (CONTROLLER_T *)0 /* identifies non-existant controller */
DECL|macro|NULLAIOP
mdefine_line|#define NULLAIOP -1                 /* identifies non-existant AIOP */
DECL|macro|NULLCHAN
mdefine_line|#define NULLCHAN -1                 /* identifies non-existant channel */
multiline_comment|/************************************************************************&n; Global Register Offsets - Direct Access - Fixed values&n;************************************************************************/
DECL|macro|_CMD_REG
mdefine_line|#define _CMD_REG   0x38   /* Command Register            8    Write */
DECL|macro|_INT_CHAN
mdefine_line|#define _INT_CHAN  0x39   /* Interrupt Channel Register  8    Read */
DECL|macro|_INT_MASK
mdefine_line|#define _INT_MASK  0x3A   /* Interrupt Mask Register     8    Read / Write */
DECL|macro|_UNUSED
mdefine_line|#define _UNUSED    0x3B   /* Unused                      8 */
DECL|macro|_INDX_ADDR
mdefine_line|#define _INDX_ADDR 0x3C   /* Index Register Address      16   Write */
DECL|macro|_INDX_DATA
mdefine_line|#define _INDX_DATA 0x3E   /* Index Register Data         8/16 Read / Write */
multiline_comment|/************************************************************************&n; Channel Register Offsets for 1st channel in AIOP - Direct Access&n;************************************************************************/
DECL|macro|_TD0
mdefine_line|#define _TD0       0x00  /* Transmit Data               16   Write */
DECL|macro|_RD0
mdefine_line|#define _RD0       0x00  /* Receive Data                16   Read */
DECL|macro|_CHN_STAT0
mdefine_line|#define _CHN_STAT0 0x20  /* Channel Status              8/16 Read / Write */
DECL|macro|_FIFO_CNT0
mdefine_line|#define _FIFO_CNT0 0x10  /* Transmit/Receive FIFO Count 16   Read */
DECL|macro|_INT_ID0
mdefine_line|#define _INT_ID0   0x30  /* Interrupt Identification    8    Read */
multiline_comment|/************************************************************************&n; Tx Control Register Offsets - Indexed - External - Fixed&n;************************************************************************/
DECL|macro|_TX_ENBLS
mdefine_line|#define _TX_ENBLS  0x980    /* Tx Processor Enables Register 8 Read / Write */
DECL|macro|_TXCMP1
mdefine_line|#define _TXCMP1    0x988    /* Transmit Compare Value #1     8 Read / Write */
DECL|macro|_TXCMP2
mdefine_line|#define _TXCMP2    0x989    /* Transmit Compare Value #2     8 Read / Write */
DECL|macro|_TXREP1B1
mdefine_line|#define _TXREP1B1  0x98A    /* Tx Replace Value #1 - Byte 1  8 Read / Write */
DECL|macro|_TXREP1B2
mdefine_line|#define _TXREP1B2  0x98B    /* Tx Replace Value #1 - Byte 2  8 Read / Write */
DECL|macro|_TXREP2
mdefine_line|#define _TXREP2    0x98C    /* Transmit Replace Value #2     8 Read / Write */
multiline_comment|/************************************************************************&n;Memory Controller Register Offsets - Indexed - External - Fixed&n;************************************************************************/
DECL|macro|_RX_FIFO
mdefine_line|#define _RX_FIFO    0x000    /* Rx FIFO */
DECL|macro|_TX_FIFO
mdefine_line|#define _TX_FIFO    0x800    /* Tx FIFO */
DECL|macro|_RXF_OUTP
mdefine_line|#define _RXF_OUTP   0x990    /* Rx FIFO OUT pointer        16 Read / Write */
DECL|macro|_RXF_INP
mdefine_line|#define _RXF_INP    0x992    /* Rx FIFO IN pointer         16 Read / Write */
DECL|macro|_TXF_OUTP
mdefine_line|#define _TXF_OUTP   0x994    /* Tx FIFO OUT pointer        8  Read / Write */
DECL|macro|_TXF_INP
mdefine_line|#define _TXF_INP    0x995    /* Tx FIFO IN pointer         8  Read / Write */
DECL|macro|_TXP_CNT
mdefine_line|#define _TXP_CNT    0x996    /* Tx Priority Count          8  Read / Write */
DECL|macro|_TXP_PNTR
mdefine_line|#define _TXP_PNTR   0x997    /* Tx Priority Pointer        8  Read / Write */
DECL|macro|PRI_PEND
mdefine_line|#define PRI_PEND    0x80     /* Priority data pending (bit7, Tx pri cnt) */
DECL|macro|TXFIFO_SIZE
mdefine_line|#define TXFIFO_SIZE 255      /* size of Tx FIFO */
DECL|macro|RXFIFO_SIZE
mdefine_line|#define RXFIFO_SIZE 1023     /* size of Rx FIFO */
multiline_comment|/************************************************************************&n;Tx Priority Buffer - Indexed - External - Fixed&n;************************************************************************/
DECL|macro|_TXP_BUF
mdefine_line|#define _TXP_BUF    0x9C0    /* Tx Priority Buffer  32  Bytes   Read / Write */
DECL|macro|TXP_SIZE
mdefine_line|#define TXP_SIZE    0x20     /* 32 bytes */
multiline_comment|/************************************************************************&n;Channel Register Offsets - Indexed - Internal - Fixed&n;************************************************************************/
DECL|macro|_TX_CTRL
mdefine_line|#define _TX_CTRL    0xFF0    /* Transmit Control               16  Write */
DECL|macro|_RX_CTRL
mdefine_line|#define _RX_CTRL    0xFF2    /* Receive Control                 8  Write */
DECL|macro|_BAUD
mdefine_line|#define _BAUD       0xFF4    /* Baud Rate                      16  Write */
DECL|macro|_CLK_PRE
mdefine_line|#define _CLK_PRE    0xFF6    /* Clock Prescaler                 8  Write */
macro_line|#if 0
mdefine_line|#define CLOCK_PRESC 0x14          /* ?????? new mod 4 (divide by 5) prescale */
mdefine_line|#define BRD50             9215
mdefine_line|#define BRD75             6143  
mdefine_line|#define BRD110            4188
mdefine_line|#define BRD134            3438
mdefine_line|#define BRD150            3071
mdefine_line|#define BRD200            2303
mdefine_line|#define BRD300            1535
mdefine_line|#define BRD600            767
mdefine_line|#define BRD1200           383
mdefine_line|#define BRD1800           255
mdefine_line|#define BRD2000           229
mdefine_line|#define BRD2400           191
mdefine_line|#define BRD3600           127
mdefine_line|#define BRD4800           95
mdefine_line|#define BRD7200           63
mdefine_line|#define BRD9600           47
mdefine_line|#define BRD14400          31 
mdefine_line|#define BRD19200          23
mdefine_line|#define BRD38400          11
mdefine_line|#define BRD57600          7
mdefine_line|#define BRD76800          5
mdefine_line|#define BRD115200         3
mdefine_line|#define BRD230400         1
mdefine_line|#define BRD460800&t;  0
macro_line|#endif
macro_line|#if 0
multiline_comment|/* Old clock prescale definition and baud rates associated with it */
mdefine_line|#define CLOCK_PRESC 0x19            /* mod 9 (divide by 10) prescale */
mdefine_line|#define BRD50             4607
mdefine_line|#define BRD75             3071
mdefine_line|#define BRD110            2094
mdefine_line|#define BRD134            1712
mdefine_line|#define BRD150            1535
mdefine_line|#define BRD200            1151
mdefine_line|#define BRD300            767
mdefine_line|#define BRD600            383
mdefine_line|#define BRD1200           191
mdefine_line|#define BRD1800           127
mdefine_line|#define BRD2000           114
mdefine_line|#define BRD2400           95
mdefine_line|#define BRD3600           64
mdefine_line|#define BRD4800           47
mdefine_line|#define BRD7200           31
mdefine_line|#define BRD9600           23
mdefine_line|#define BRD14400          15
mdefine_line|#define BRD19200          11
mdefine_line|#define BRD38400          5
mdefine_line|#define BRD57600          3
mdefine_line|#define BRD76800          2
mdefine_line|#define BRD115200         1
mdefine_line|#define BRD230400         0
macro_line|#endif
DECL|macro|STMBREAK
mdefine_line|#define STMBREAK   0x08        /* BREAK */
DECL|macro|STMFRAME
mdefine_line|#define STMFRAME   0x04        /* framing error */
DECL|macro|STMRCVROVR
mdefine_line|#define STMRCVROVR 0x02        /* receiver over run error */
DECL|macro|STMPARITY
mdefine_line|#define STMPARITY  0x01        /* parity error */
DECL|macro|STMERROR
mdefine_line|#define STMERROR   (STMBREAK | STMFRAME | STMPARITY)
DECL|macro|STMBREAKH
mdefine_line|#define STMBREAKH   0x800      /* BREAK */
DECL|macro|STMFRAMEH
mdefine_line|#define STMFRAMEH   0x400      /* framing error */
DECL|macro|STMRCVROVRH
mdefine_line|#define STMRCVROVRH 0x200      /* receiver over run error */
DECL|macro|STMPARITYH
mdefine_line|#define STMPARITYH  0x100      /* parity error */
DECL|macro|STMERRORH
mdefine_line|#define STMERRORH   (STMBREAKH | STMFRAMEH | STMPARITYH)
DECL|macro|CTS_ACT
mdefine_line|#define CTS_ACT   0x20        /* CTS input asserted */
DECL|macro|DSR_ACT
mdefine_line|#define DSR_ACT   0x10        /* DSR input asserted */
DECL|macro|CD_ACT
mdefine_line|#define CD_ACT    0x08        /* CD input asserted */
DECL|macro|TXFIFOMT
mdefine_line|#define TXFIFOMT  0x04        /* Tx FIFO is empty */
DECL|macro|TXSHRMT
mdefine_line|#define TXSHRMT   0x02        /* Tx shift register is empty */
DECL|macro|RDA
mdefine_line|#define RDA       0x01        /* Rx data available */
DECL|macro|DRAINED
mdefine_line|#define DRAINED (TXFIFOMT | TXSHRMT)  /* indicates Tx is drained */
DECL|macro|STATMODE
mdefine_line|#define STATMODE  0x8000      /* status mode enable bit */
DECL|macro|RXFOVERFL
mdefine_line|#define RXFOVERFL 0x2000      /* receive FIFO overflow */
DECL|macro|RX2MATCH
mdefine_line|#define RX2MATCH  0x1000      /* receive compare byte 2 match */
DECL|macro|RX1MATCH
mdefine_line|#define RX1MATCH  0x0800      /* receive compare byte 1 match */
DECL|macro|RXBREAK
mdefine_line|#define RXBREAK   0x0400      /* received BREAK */
DECL|macro|RXFRAME
mdefine_line|#define RXFRAME   0x0200      /* received framing error */
DECL|macro|RXPARITY
mdefine_line|#define RXPARITY  0x0100      /* received parity error */
DECL|macro|STATERROR
mdefine_line|#define STATERROR (RXBREAK | RXFRAME | RXPARITY)
DECL|macro|CTSFC_EN
mdefine_line|#define CTSFC_EN  0x80        /* CTS flow control enable bit */
DECL|macro|RTSTOG_EN
mdefine_line|#define RTSTOG_EN 0x40        /* RTS toggle enable bit */
DECL|macro|TXINT_EN
mdefine_line|#define TXINT_EN  0x10        /* transmit interrupt enable */
DECL|macro|STOP2
mdefine_line|#define STOP2     0x08        /* enable 2 stop bits (0 = 1 stop) */
DECL|macro|PARITY_EN
mdefine_line|#define PARITY_EN 0x04        /* enable parity (0 = no parity) */
DECL|macro|EVEN_PAR
mdefine_line|#define EVEN_PAR  0x02        /* even parity (0 = odd parity) */
DECL|macro|DATA8BIT
mdefine_line|#define DATA8BIT  0x01        /* 8 bit data (0 = 7 bit data) */
DECL|macro|SETBREAK
mdefine_line|#define SETBREAK  0x10        /* send break condition (must clear) */
DECL|macro|LOCALLOOP
mdefine_line|#define LOCALLOOP 0x08        /* local loopback set for test */
DECL|macro|SET_DTR
mdefine_line|#define SET_DTR   0x04        /* assert DTR */
DECL|macro|SET_RTS
mdefine_line|#define SET_RTS   0x02        /* assert RTS */
DECL|macro|TX_ENABLE
mdefine_line|#define TX_ENABLE 0x01        /* enable transmitter */
DECL|macro|RTSFC_EN
mdefine_line|#define RTSFC_EN  0x40        /* RTS flow control enable */
DECL|macro|RXPROC_EN
mdefine_line|#define RXPROC_EN 0x20        /* receive processor enable */
DECL|macro|TRIG_NO
mdefine_line|#define TRIG_NO   0x00        /* Rx FIFO trigger level 0 (no trigger) */
DECL|macro|TRIG_1
mdefine_line|#define TRIG_1    0x08        /* trigger level 1 char */
DECL|macro|TRIG_1_2
mdefine_line|#define TRIG_1_2  0x10        /* trigger level 1/2 */
DECL|macro|TRIG_7_8
mdefine_line|#define TRIG_7_8  0x18        /* trigger level 7/8 */
DECL|macro|TRIG_MASK
mdefine_line|#define TRIG_MASK 0x18        /* trigger level mask */
DECL|macro|SRCINT_EN
mdefine_line|#define SRCINT_EN 0x04        /* special Rx condition interrupt enable */
DECL|macro|RXINT_EN
mdefine_line|#define RXINT_EN  0x02        /* Rx interrupt enable */
DECL|macro|MCINT_EN
mdefine_line|#define MCINT_EN  0x01        /* modem change interrupt enable */
DECL|macro|RXF_TRIG
mdefine_line|#define RXF_TRIG  0x20        /* Rx FIFO trigger level interrupt */
DECL|macro|TXFIFO_MT
mdefine_line|#define TXFIFO_MT 0x10        /* Tx FIFO empty interrupt */
DECL|macro|SRC_INT
mdefine_line|#define SRC_INT   0x08        /* special receive condition interrupt */
DECL|macro|DELTA_CD
mdefine_line|#define DELTA_CD  0x04        /* CD change interrupt */
DECL|macro|DELTA_CTS
mdefine_line|#define DELTA_CTS 0x02        /* CTS change interrupt */
DECL|macro|DELTA_DSR
mdefine_line|#define DELTA_DSR 0x01        /* DSR change interrupt */
DECL|macro|REP1W2_EN
mdefine_line|#define REP1W2_EN 0x10        /* replace byte 1 with 2 bytes enable */
DECL|macro|IGN2_EN
mdefine_line|#define IGN2_EN   0x08        /* ignore byte 2 enable */
DECL|macro|IGN1_EN
mdefine_line|#define IGN1_EN   0x04        /* ignore byte 1 enable */
DECL|macro|COMP2_EN
mdefine_line|#define COMP2_EN  0x02        /* compare byte 2 enable */
DECL|macro|COMP1_EN
mdefine_line|#define COMP1_EN  0x01        /* compare byte 1 enable */
DECL|macro|RESET_ALL
mdefine_line|#define RESET_ALL 0x80        /* reset AIOP (all channels) */
DECL|macro|TXOVERIDE
mdefine_line|#define TXOVERIDE 0x40        /* Transmit software off override */
DECL|macro|RESETUART
mdefine_line|#define RESETUART 0x20        /* reset channel&squot;s UART */
DECL|macro|RESTXFCNT
mdefine_line|#define RESTXFCNT 0x10        /* reset channel&squot;s Tx FIFO count register */
DECL|macro|RESRXFCNT
mdefine_line|#define RESRXFCNT 0x08        /* reset channel&squot;s Rx FIFO count register */
DECL|macro|INTSTAT0
mdefine_line|#define INTSTAT0  0x01        /* AIOP 0 interrupt status */
DECL|macro|INTSTAT1
mdefine_line|#define INTSTAT1  0x02        /* AIOP 1 interrupt status */
DECL|macro|INTSTAT2
mdefine_line|#define INTSTAT2  0x04        /* AIOP 2 interrupt status */
DECL|macro|INTSTAT3
mdefine_line|#define INTSTAT3  0x08        /* AIOP 3 interrupt status */
DECL|macro|INTR_EN
mdefine_line|#define INTR_EN   0x08        /* allow interrupts to host */
DECL|macro|INT_STROB
mdefine_line|#define INT_STROB 0x04        /* strobe and clear interrupt line (EOI) */
multiline_comment|/**************************************************************************&n; MUDBAC remapped for PCI&n;**************************************************************************/
DECL|macro|_CFG_INT_PCI
mdefine_line|#define _CFG_INT_PCI  0x40
DECL|macro|_PCI_INT_FUNC
mdefine_line|#define _PCI_INT_FUNC 0x3A
DECL|macro|PCI_STROB
mdefine_line|#define PCI_STROB 0x2000        /* bit 13 of int aiop register */
DECL|macro|INTR_EN_PCI
mdefine_line|#define INTR_EN_PCI   0x0010        /* allow interrupts to host */
DECL|macro|CHAN3_EN
mdefine_line|#define CHAN3_EN  0x08        /* enable AIOP 3 */
DECL|macro|CHAN2_EN
mdefine_line|#define CHAN2_EN  0x04        /* enable AIOP 2 */
DECL|macro|CHAN1_EN
mdefine_line|#define CHAN1_EN  0x02        /* enable AIOP 1 */
DECL|macro|CHAN0_EN
mdefine_line|#define CHAN0_EN  0x01        /* enable AIOP 0 */
DECL|macro|FREQ_DIS
mdefine_line|#define FREQ_DIS  0x00
DECL|macro|FREQ_274HZ
mdefine_line|#define FREQ_274HZ 0x60
DECL|macro|FREQ_137HZ
mdefine_line|#define FREQ_137HZ 0x50
DECL|macro|FREQ_69HZ
mdefine_line|#define FREQ_69HZ  0x40
DECL|macro|FREQ_34HZ
mdefine_line|#define FREQ_34HZ  0x30
DECL|macro|FREQ_17HZ
mdefine_line|#define FREQ_17HZ  0x20
DECL|macro|FREQ_9HZ
mdefine_line|#define FREQ_9HZ   0x10
DECL|macro|PERIODIC_ONLY
mdefine_line|#define PERIODIC_ONLY 0x80    /* only PERIODIC interrupt */
DECL|macro|CHANINT_EN
mdefine_line|#define CHANINT_EN 0x0100           /* flags to enable/disable channel ints */
DECL|macro|RDATASIZE
mdefine_line|#define RDATASIZE 72
DECL|macro|RREGDATASIZE
mdefine_line|#define RREGDATASIZE 52
multiline_comment|/* Controller level information structure */
r_typedef
r_struct
(brace
DECL|member|CtlID
r_int
id|CtlID
suffix:semicolon
DECL|member|CtlNum
r_int
id|CtlNum
suffix:semicolon
DECL|member|BusType
r_int
id|BusType
suffix:semicolon
DECL|member|PCIIO
id|WordIO_t
id|PCIIO
suffix:semicolon
DECL|member|MBaseIO
id|ByteIO_t
id|MBaseIO
suffix:semicolon
DECL|member|MReg1IO
id|ByteIO_t
id|MReg1IO
suffix:semicolon
DECL|member|MReg2IO
id|ByteIO_t
id|MReg2IO
suffix:semicolon
DECL|member|MReg3IO
id|ByteIO_t
id|MReg3IO
suffix:semicolon
DECL|member|MReg2
id|Byte_t
id|MReg2
suffix:semicolon
DECL|member|MReg3
id|Byte_t
id|MReg3
suffix:semicolon
DECL|member|NumAiop
r_int
id|NumAiop
suffix:semicolon
DECL|member|AiopIO
id|WordIO_t
id|AiopIO
(braket
id|AIOP_CTL_SIZE
)braket
suffix:semicolon
DECL|member|AiopIntChanIO
id|ByteIO_t
id|AiopIntChanIO
(braket
id|AIOP_CTL_SIZE
)braket
suffix:semicolon
DECL|member|AiopID
r_int
id|AiopID
(braket
id|AIOP_CTL_SIZE
)braket
suffix:semicolon
DECL|member|AiopNumChan
r_int
id|AiopNumChan
(braket
id|AIOP_CTL_SIZE
)braket
suffix:semicolon
DECL|typedef|CONTROLLER_T
)brace
id|CONTROLLER_T
suffix:semicolon
DECL|typedef|CONTROLLER_t
r_typedef
id|CONTROLLER_T
id|CONTROLLER_t
suffix:semicolon
multiline_comment|/* Channel level information structure */
r_typedef
r_struct
(brace
DECL|member|CtlP
id|CONTROLLER_T
op_star
id|CtlP
suffix:semicolon
DECL|member|AiopNum
r_int
id|AiopNum
suffix:semicolon
DECL|member|ChanID
r_int
id|ChanID
suffix:semicolon
DECL|member|ChanNum
r_int
id|ChanNum
suffix:semicolon
DECL|member|Cmd
id|ByteIO_t
id|Cmd
suffix:semicolon
DECL|member|IntChan
id|ByteIO_t
id|IntChan
suffix:semicolon
DECL|member|IntMask
id|ByteIO_t
id|IntMask
suffix:semicolon
DECL|member|IndexAddr
id|DWordIO_t
id|IndexAddr
suffix:semicolon
DECL|member|IndexData
id|WordIO_t
id|IndexData
suffix:semicolon
DECL|member|TxRxData
id|WordIO_t
id|TxRxData
suffix:semicolon
DECL|member|ChanStat
id|WordIO_t
id|ChanStat
suffix:semicolon
DECL|member|TxRxCount
id|WordIO_t
id|TxRxCount
suffix:semicolon
DECL|member|IntID
id|ByteIO_t
id|IntID
suffix:semicolon
DECL|member|TxFIFO
id|Word_t
id|TxFIFO
suffix:semicolon
DECL|member|TxFIFOPtrs
id|Word_t
id|TxFIFOPtrs
suffix:semicolon
DECL|member|RxFIFO
id|Word_t
id|RxFIFO
suffix:semicolon
DECL|member|RxFIFOPtrs
id|Word_t
id|RxFIFOPtrs
suffix:semicolon
DECL|member|TxPrioCnt
id|Word_t
id|TxPrioCnt
suffix:semicolon
DECL|member|TxPrioPtr
id|Word_t
id|TxPrioPtr
suffix:semicolon
DECL|member|TxPrioBuf
id|Word_t
id|TxPrioBuf
suffix:semicolon
DECL|member|R
id|Byte_t
id|R
(braket
id|RREGDATASIZE
)braket
suffix:semicolon
DECL|member|BaudDiv
id|Byte_t
id|BaudDiv
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|TxControl
id|Byte_t
id|TxControl
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|RxControl
id|Byte_t
id|RxControl
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|TxEnables
id|Byte_t
id|TxEnables
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|TxCompare
id|Byte_t
id|TxCompare
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|TxReplace1
id|Byte_t
id|TxReplace1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|TxReplace2
id|Byte_t
id|TxReplace2
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|CHANNEL_T
)brace
id|CHANNEL_T
suffix:semicolon
DECL|typedef|CHANNEL_t
r_typedef
id|CHANNEL_T
id|CHANNEL_t
suffix:semicolon
DECL|typedef|CHANPTR_T
r_typedef
id|CHANNEL_T
op_star
id|CHANPTR_T
suffix:semicolon
multiline_comment|/***************************************************************************&n;Function: sClrBreak&n;Purpose:  Stop sending a transmit BREAK signal&n;Call:     sClrBreak(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sClrBreak
mdefine_line|#define sClrBreak(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] &amp;= ~SETBREAK; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sClrDTR&n;Purpose:  Clr the DTR output&n;Call:     sClrDTR(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sClrDTR
mdefine_line|#define sClrDTR(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] &amp;= ~SET_DTR; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sClrRTS&n;Purpose:  Clr the RTS output&n;Call:     sClrRTS(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sClrRTS
mdefine_line|#define sClrRTS(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] &amp;= ~SET_RTS; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sClrTxXOFF&n;Purpose:  Clear any existing transmit software flow control off condition&n;Call:     sClrTxXOFF(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sClrTxXOFF
mdefine_line|#define sClrTxXOFF(ChP) &bslash;&n;{ &bslash;&n;   sOutB((ChP)-&gt;Cmd,TXOVERIDE | (Byte_t)(ChP)-&gt;ChanNum); &bslash;&n;   sOutB((ChP)-&gt;Cmd,(Byte_t)(ChP)-&gt;ChanNum); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sCtlNumToCtlPtr&n;Purpose:  Convert a controller number to controller structure pointer&n;Call:     sCtlNumToCtlPtr(CtlNum)&n;          int CtlNum; Controller number&n;Return:   CONTROLLER_T *: Ptr to controller structure&n;*/
DECL|macro|sCtlNumToCtlPtr
mdefine_line|#define sCtlNumToCtlPtr(CTLNUM) &amp;sController[CTLNUM]
multiline_comment|/***************************************************************************&n;Function: sControllerEOI&n;Purpose:  Strobe the MUDBAC&squot;s End Of Interrupt bit.&n;Call:     sControllerEOI(CtlP)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;*/
DECL|macro|sControllerEOI
mdefine_line|#define sControllerEOI(CTLP) sOutB((CTLP)-&gt;MReg2IO,(CTLP)-&gt;MReg2 | INT_STROB)
multiline_comment|/***************************************************************************&n;Function: sPCIControllerEOI&n;Purpose:  Strobe the PCI End Of Interrupt bit.&n;Call:     sPCIControllerEOI(CtlP)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;*/
DECL|macro|sPCIControllerEOI
mdefine_line|#define sPCIControllerEOI(CTLP) sOutW((CTLP)-&gt;PCIIO, PCI_STROB)
multiline_comment|/***************************************************************************&n;Function: sDisAiop&n;Purpose:  Disable I/O access to an AIOP&n;Call:     sDisAiop(CltP)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;          int AiopNum; Number of AIOP on controller&n;*/
DECL|macro|sDisAiop
mdefine_line|#define sDisAiop(CTLP,AIOPNUM) &bslash;&n;{ &bslash;&n;   (CTLP)-&gt;MReg3 &amp;= sBitMapClrTbl[AIOPNUM]; &bslash;&n;   sOutB((CTLP)-&gt;MReg3IO,(CTLP)-&gt;MReg3); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sDisCTSFlowCtl&n;Purpose:  Disable output flow control using CTS&n;Call:     sDisCTSFlowCtl(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sDisCTSFlowCtl
mdefine_line|#define sDisCTSFlowCtl(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] &amp;= ~CTSFC_EN; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sDisIXANY&n;Purpose:  Disable IXANY Software Flow Control&n;Call:     sDisIXANY(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sDisIXANY
mdefine_line|#define sDisIXANY(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x0e] = 0x86; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x0c]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: DisParity&n;Purpose:  Disable parity&n;Call:     sDisParity(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: Function sSetParity() can be used in place of functions sEnParity(),&n;          sDisParity(), sSetOddParity(), and sSetEvenParity().&n;*/
DECL|macro|sDisParity
mdefine_line|#define sDisParity(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] &amp;= ~PARITY_EN; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sDisRxFIFO&n;Purpose:  Disable Rx FIFO&n;Call:     sDisRxFIFO(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sDisRxFIFO
mdefine_line|#define sDisRxFIFO(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x32] = 0x0a; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x30]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sDisRxStatusMode&n;Purpose:  Disable the Rx status mode&n;Call:     sDisRxStatusMode(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: This takes the channel out of the receive status mode.  All&n;          subsequent reads of receive data using sReadRxWord() will return&n;          two data bytes.&n;*/
DECL|macro|sDisRxStatusMode
mdefine_line|#define sDisRxStatusMode(ChP) sOutW((ChP)-&gt;ChanStat,0)
multiline_comment|/***************************************************************************&n;Function: sDisTransmit&n;Purpose:  Disable transmit&n;Call:     sDisTransmit(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;          This disables movement of Tx data from the Tx FIFO into the 1 byte&n;          Tx buffer.  Therefore there could be up to a 2 byte latency&n;          between the time sDisTransmit() is called and the transmit buffer&n;          and transmit shift register going completely empty.&n;*/
DECL|macro|sDisTransmit
mdefine_line|#define sDisTransmit(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] &amp;= ~TX_ENABLE; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sDisTxSoftFlowCtl&n;Purpose:  Disable Tx Software Flow Control&n;Call:     sDisTxSoftFlowCtl(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sDisTxSoftFlowCtl
mdefine_line|#define sDisTxSoftFlowCtl(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x06] = 0x8a; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x04]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnAiop&n;Purpose:  Enable I/O access to an AIOP&n;Call:     sEnAiop(CltP)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;          int AiopNum; Number of AIOP on controller&n;*/
DECL|macro|sEnAiop
mdefine_line|#define sEnAiop(CTLP,AIOPNUM) &bslash;&n;{ &bslash;&n;   (CTLP)-&gt;MReg3 |= sBitMapSetTbl[AIOPNUM]; &bslash;&n;   sOutB((CTLP)-&gt;MReg3IO,(CTLP)-&gt;MReg3); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnCTSFlowCtl&n;Purpose:  Enable output flow control using CTS&n;Call:     sEnCTSFlowCtl(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sEnCTSFlowCtl
mdefine_line|#define sEnCTSFlowCtl(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] |= CTSFC_EN; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnIXANY&n;Purpose:  Enable IXANY Software Flow Control&n;Call:     sEnIXANY(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sEnIXANY
mdefine_line|#define sEnIXANY(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x0e] = 0x21; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x0c]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: EnParity&n;Purpose:  Enable parity&n;Call:     sEnParity(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: Function sSetParity() can be used in place of functions sEnParity(),&n;          sDisParity(), sSetOddParity(), and sSetEvenParity().&n;&n;Warnings: Before enabling parity odd or even parity should be chosen using&n;          functions sSetOddParity() or sSetEvenParity().&n;*/
DECL|macro|sEnParity
mdefine_line|#define sEnParity(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] |= PARITY_EN; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnRxFIFO&n;Purpose:  Enable Rx FIFO&n;Call:     sEnRxFIFO(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sEnRxFIFO
mdefine_line|#define sEnRxFIFO(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x32] = 0x08; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x30]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnRxProcessor&n;Purpose:  Enable the receive processor&n;Call:     sEnRxProcessor(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: This function is used to start the receive processor.  When&n;          the channel is in the reset state the receive processor is not&n;          running.  This is done to prevent the receive processor from&n;          executing invalid microcode instructions prior to the&n;          downloading of the microcode.&n;&n;Warnings: This function must be called after valid microcode has been&n;          downloaded to the AIOP, and it must not be called before the&n;          microcode has been downloaded.&n;*/
DECL|macro|sEnRxProcessor
mdefine_line|#define sEnRxProcessor(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;RxControl[2] |= RXPROC_EN; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;RxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnRxStatusMode&n;Purpose:  Enable the Rx status mode&n;Call:     sEnRxStatusMode(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: This places the channel in the receive status mode.  All subsequent&n;          reads of receive data using sReadRxWord() will return a data byte&n;          in the low word and a status byte in the high word.&n;&n;*/
DECL|macro|sEnRxStatusMode
mdefine_line|#define sEnRxStatusMode(ChP) sOutW((ChP)-&gt;ChanStat,STATMODE)
multiline_comment|/***************************************************************************&n;Function: sEnTransmit&n;Purpose:  Enable transmit&n;Call:     sEnTransmit(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sEnTransmit
mdefine_line|#define sEnTransmit(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] |= TX_ENABLE; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sEnTxSoftFlowCtl&n;Purpose:  Enable Tx Software Flow Control&n;Call:     sEnTxSoftFlowCtl(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sEnTxSoftFlowCtl
mdefine_line|#define sEnTxSoftFlowCtl(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x06] = 0xc5; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x04]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sGetAiopIntStatus&n;Purpose:  Get the AIOP interrupt status&n;Call:     sGetAiopIntStatus(CtlP,AiopNum)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;          int AiopNum; AIOP number&n;Return:   Byte_t: The AIOP interrupt status.  Bits 0 through 7&n;                         represent channels 0 through 7 respectively.  If a&n;                         bit is set that channel is interrupting.&n;*/
DECL|macro|sGetAiopIntStatus
mdefine_line|#define sGetAiopIntStatus(CTLP,AIOPNUM) sInB((CTLP)-&gt;AiopIntChanIO[AIOPNUM])
multiline_comment|/***************************************************************************&n;Function: sGetAiopNumChan&n;Purpose:  Get the number of channels supported by an AIOP&n;Call:     sGetAiopNumChan(CtlP,AiopNum)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;          int AiopNum; AIOP number&n;Return:   int: The number of channels supported by the AIOP&n;*/
DECL|macro|sGetAiopNumChan
mdefine_line|#define sGetAiopNumChan(CTLP,AIOPNUM) (CTLP)-&gt;AiopNumChan[AIOPNUM]
multiline_comment|/***************************************************************************&n;Function: sGetChanIntID&n;Purpose:  Get a channel&squot;s interrupt identification byte&n;Call:     sGetChanIntID(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   Byte_t: The channel interrupt ID.  Can be any&n;             combination of the following flags:&n;                RXF_TRIG:     Rx FIFO trigger level interrupt&n;                TXFIFO_MT:    Tx FIFO empty interrupt&n;                SRC_INT:      Special receive condition interrupt&n;                DELTA_CD:     CD change interrupt&n;                DELTA_CTS:    CTS change interrupt&n;                DELTA_DSR:    DSR change interrupt&n;*/
DECL|macro|sGetChanIntID
mdefine_line|#define sGetChanIntID(ChP) (sInB((ChP)-&gt;IntID) &amp; (RXF_TRIG | TXFIFO_MT | SRC_INT | DELTA_CD | DELTA_CTS | DELTA_DSR))
multiline_comment|/***************************************************************************&n;Function: sGetChanNum&n;Purpose:  Get the number of a channel within an AIOP&n;Call:     sGetChanNum(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   int: Channel number within AIOP, or NULLCHAN if channel does&n;               not exist.&n;*/
DECL|macro|sGetChanNum
mdefine_line|#define sGetChanNum(ChP) (ChP)-&gt;ChanNum
multiline_comment|/***************************************************************************&n;Function: sGetChanStatus&n;Purpose:  Get the channel status&n;Call:     sGetChanStatus(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   Word_t: The channel status.  Can be any combination of&n;             the following flags:&n;                LOW BYTE FLAGS&n;                CTS_ACT:      CTS input asserted&n;                DSR_ACT:      DSR input asserted&n;                CD_ACT:       CD input asserted&n;                TXFIFOMT:     Tx FIFO is empty&n;                TXSHRMT:      Tx shift register is empty&n;                RDA:          Rx data available&n;&n;                HIGH BYTE FLAGS&n;                STATMODE:     status mode enable bit&n;                RXFOVERFL:    receive FIFO overflow&n;                RX2MATCH:     receive compare byte 2 match&n;                RX1MATCH:     receive compare byte 1 match&n;                RXBREAK:      received BREAK&n;                RXFRAME:      received framing error&n;                RXPARITY:     received parity error&n;Warnings: This function will clear the high byte flags in the Channel&n;          Status Register.&n;*/
DECL|macro|sGetChanStatus
mdefine_line|#define sGetChanStatus(ChP) sInW((ChP)-&gt;ChanStat)
multiline_comment|/***************************************************************************&n;Function: sGetChanStatusLo&n;Purpose:  Get the low byte only of the channel status&n;Call:     sGetChanStatusLo(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   Byte_t: The channel status low byte.  Can be any combination&n;             of the following flags:&n;                CTS_ACT:      CTS input asserted&n;                DSR_ACT:      DSR input asserted&n;                CD_ACT:       CD input asserted&n;                TXFIFOMT:     Tx FIFO is empty&n;                TXSHRMT:      Tx shift register is empty&n;                RDA:          Rx data available&n;*/
DECL|macro|sGetChanStatusLo
mdefine_line|#define sGetChanStatusLo(ChP) sInB((ByteIO_t)(ChP)-&gt;ChanStat)
multiline_comment|/***************************************************************************&n;Function: sGetControllerIntStatus&n;Purpose:  Get the controller interrupt status&n;Call:     sGetControllerIntStatus(CtlP)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;Return:   Byte_t: The controller interrupt status in the lower 4&n;                         bits.  Bits 0 through 3 represent AIOP&squot;s 0&n;                         through 3 respectively.  If a bit is set that&n;                         AIOP is interrupting.  Bits 4 through 7 will&n;                         always be cleared.&n;*/
DECL|macro|sGetControllerIntStatus
mdefine_line|#define sGetControllerIntStatus(CTLP) (sInB((CTLP)-&gt;MReg1IO) &amp; 0x0f)
multiline_comment|/***************************************************************************&n;Function: sPCIGetControllerIntStatus&n;Purpose:  Get the controller interrupt status&n;Call:     sPCIGetControllerIntStatus(CtlP)&n;          CONTROLLER_T *CtlP; Ptr to controller structure&n;Return:   unsigned char: The controller interrupt status in the lower 4&n;                         bits and bit 4.  Bits 0 through 3 represent AIOP&squot;s 0&n;                         through 3 respectively. Bit 4 is set if the int &n;&t;&t;&t; was generated from periodic. If a bit is set the&n;&t;&t;&t; AIOP is interrupting.&n;*/
DECL|macro|sPCIGetControllerIntStatus
mdefine_line|#define sPCIGetControllerIntStatus(CTLP) ((sInW((CTLP)-&gt;PCIIO) &gt;&gt; 8) &amp; 0x1f)
multiline_comment|/***************************************************************************&n;&n;Function: sGetRxCnt&n;Purpose:  Get the number of data bytes in the Rx FIFO&n;Call:     sGetRxCnt(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   int: The number of data bytes in the Rx FIFO.&n;Comments: Byte read of count register is required to obtain Rx count.&n;&n;*/
DECL|macro|sGetRxCnt
mdefine_line|#define sGetRxCnt(ChP) sInW((ChP)-&gt;TxRxCount)
multiline_comment|/***************************************************************************&n;Function: sGetTxCnt&n;Purpose:  Get the number of data bytes in the Tx FIFO&n;Call:     sGetTxCnt(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   Byte_t: The number of data bytes in the Tx FIFO.&n;Comments: Byte read of count register is required to obtain Tx count.&n;&n;*/
DECL|macro|sGetTxCnt
mdefine_line|#define sGetTxCnt(ChP) sInB((ByteIO_t)(ChP)-&gt;TxRxCount)
multiline_comment|/*****************************************************************************&n;Function: sGetTxRxDataIO&n;Purpose:  Get the I/O address of a channel&squot;s TxRx Data register&n;Call:     sGetTxRxDataIO(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Return:   WordIO_t: I/O address of a channel&squot;s TxRx Data register&n;*/
DECL|macro|sGetTxRxDataIO
mdefine_line|#define sGetTxRxDataIO(ChP) (ChP)-&gt;TxRxData
multiline_comment|/***************************************************************************&n;Function: sInitChanDefaults&n;Purpose:  Initialize a channel structure to it&squot;s default state.&n;Call:     sInitChanDefaults(ChP)&n;          CHANNEL_T *ChP; Ptr to the channel structure&n;Comments: This function must be called once for every channel structure&n;          that exists before any other SSCI calls can be made.&n;&n;*/
DECL|macro|sInitChanDefaults
mdefine_line|#define sInitChanDefaults(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;CtlP = NULLCTLPTR; &bslash;&n;   (ChP)-&gt;AiopNum = NULLAIOP; &bslash;&n;   (ChP)-&gt;ChanID = AIOPID_NULL; &bslash;&n;   (ChP)-&gt;ChanNum = NULLCHAN; &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sResetAiopByNum&n;Purpose:  Reset the AIOP by number&n;Call:     sResetAiopByNum(CTLP,AIOPNUM)&n;&t;CONTROLLER_T CTLP; Ptr to controller structure&n;&t;AIOPNUM; AIOP index &n;*/
DECL|macro|sResetAiopByNum
mdefine_line|#define sResetAiopByNum(CTLP,AIOPNUM) &bslash;&n;{ &bslash;&n;   sOutB((CTLP)-&gt;AiopIO[(AIOPNUM)]+_CMD_REG,RESET_ALL); &bslash;&n;   sOutB((CTLP)-&gt;AiopIO[(AIOPNUM)]+_CMD_REG,0x0); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSendBreak&n;Purpose:  Send a transmit BREAK signal&n;Call:     sSendBreak(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSendBreak
mdefine_line|#define sSendBreak(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] |= SETBREAK; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetBaud&n;Purpose:  Set baud rate&n;Call:     sSetBaud(ChP,Divisor)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;          Word_t Divisor; 16 bit baud rate divisor for channel&n;*/
DECL|macro|sSetBaud
mdefine_line|#define sSetBaud(ChP,DIVISOR) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;BaudDiv[2] = (Byte_t)(DIVISOR); &bslash;&n;   (ChP)-&gt;BaudDiv[3] = (Byte_t)((DIVISOR) &gt;&gt; 8); &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;BaudDiv[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetData7&n;Purpose:  Set data bits to 7&n;Call:     sSetData7(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSetData7
mdefine_line|#define sSetData7(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] &amp;= ~DATA8BIT; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetData8&n;Purpose:  Set data bits to 8&n;Call:     sSetData8(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSetData8
mdefine_line|#define sSetData8(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] |= DATA8BIT; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetDTR&n;Purpose:  Set the DTR output&n;Call:     sSetDTR(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSetDTR
mdefine_line|#define sSetDTR(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] |= SET_DTR; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetEvenParity&n;Purpose:  Set even parity&n;Call:     sSetEvenParity(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: Function sSetParity() can be used in place of functions sEnParity(),&n;          sDisParity(), sSetOddParity(), and sSetEvenParity().&n;&n;Warnings: This function has no effect unless parity is enabled with function&n;          sEnParity().&n;*/
DECL|macro|sSetEvenParity
mdefine_line|#define sSetEvenParity(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] |= EVEN_PAR; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetOddParity&n;Purpose:  Set odd parity&n;Call:     sSetOddParity(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: Function sSetParity() can be used in place of functions sEnParity(),&n;          sDisParity(), sSetOddParity(), and sSetEvenParity().&n;&n;Warnings: This function has no effect unless parity is enabled with function&n;          sEnParity().&n;*/
DECL|macro|sSetOddParity
mdefine_line|#define sSetOddParity(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] &amp;= ~EVEN_PAR; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetRTS&n;Purpose:  Set the RTS output&n;Call:     sSetRTS(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSetRTS
mdefine_line|#define sSetRTS(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[3] |= SET_RTS; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetRxTrigger&n;Purpose:  Set the Rx FIFO trigger level&n;Call:     sSetRxProcessor(ChP,Level)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;          Byte_t Level; Number of characters in Rx FIFO at which the&n;             interrupt will be generated.  Can be any of the following flags:&n;&n;             TRIG_NO:   no trigger&n;             TRIG_1:    1 character in FIFO&n;             TRIG_1_2:  FIFO 1/2 full&n;             TRIG_7_8:  FIFO 7/8 full&n;Comments: An interrupt will be generated when the trigger level is reached&n;          only if function sEnInterrupt() has been called with flag&n;          RXINT_EN set.  The RXF_TRIG flag in the Interrupt Idenfification&n;          register will be set whenever the trigger level is reached&n;          regardless of the setting of RXINT_EN.&n;&n;*/
DECL|macro|sSetRxTrigger
mdefine_line|#define sSetRxTrigger(ChP,LEVEL) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;RxControl[2] &amp;= ~TRIG_MASK; &bslash;&n;   (ChP)-&gt;RxControl[2] |= LEVEL; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;RxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetStop1&n;Purpose:  Set stop bits to 1&n;Call:     sSetStop1(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSetStop1
mdefine_line|#define sSetStop1(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] &amp;= ~STOP2; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetStop2&n;Purpose:  Set stop bits to 2&n;Call:     sSetStop2(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;*/
DECL|macro|sSetStop2
mdefine_line|#define sSetStop2(ChP) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;TxControl[2] |= STOP2; &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;TxControl[0]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetTxXOFFChar&n;Purpose:  Set the Tx XOFF flow control character&n;Call:     sSetTxXOFFChar(ChP,Ch)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;          Byte_t Ch; The value to set the Tx XOFF character to&n;*/
DECL|macro|sSetTxXOFFChar
mdefine_line|#define sSetTxXOFFChar(ChP,CH) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x07] = (CH); &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x04]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sSetTxXONChar&n;Purpose:  Set the Tx XON flow control character&n;Call:     sSetTxXONChar(ChP,Ch)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;          Byte_t Ch; The value to set the Tx XON character to&n;*/
DECL|macro|sSetTxXONChar
mdefine_line|#define sSetTxXONChar(ChP,CH) &bslash;&n;{ &bslash;&n;   (ChP)-&gt;R[0x0b] = (CH); &bslash;&n;   sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0x08]); &bslash;&n;}
multiline_comment|/***************************************************************************&n;Function: sStartRxProcessor&n;Purpose:  Start a channel&squot;s receive processor&n;Call:     sStartRxProcessor(ChP)&n;          CHANNEL_T *ChP; Ptr to channel structure&n;Comments: This function is used to start a Rx processor after it was&n;          stopped with sStopRxProcessor() or sStopSWInFlowCtl().  It&n;          will restart both the Rx processor and software input flow control.&n;&n;*/
DECL|macro|sStartRxProcessor
mdefine_line|#define sStartRxProcessor(ChP) sOutDW((ChP)-&gt;IndexAddr,*(DWord_t *)&amp;(ChP)-&gt;R[0])
multiline_comment|/***************************************************************************&n;Function: sWriteTxByte&n;Purpose:  Write a transmit data byte to a channel.&n;          ByteIO_t io: Channel transmit register I/O address.  This can&n;                           be obtained with sGetTxRxDataIO().&n;          Byte_t Data; The transmit data byte.&n;Warnings: This function writes the data byte without checking to see if&n;          sMaxTxSize is exceeded in the Tx FIFO.&n;*/
DECL|macro|sWriteTxByte
mdefine_line|#define sWriteTxByte(IO,DATA) sOutB(IO,DATA)
r_int
id|sInitController
c_func
(paren
id|CONTROLLER_T
op_star
id|CtlP
comma
r_int
id|CtlNum
comma
id|ByteIO_t
id|MudbacIO
comma
id|ByteIO_t
op_star
id|AiopIOList
comma
r_int
id|AiopIOListSize
comma
r_int
id|IRQNum
comma
id|Byte_t
id|Frequency
comma
r_int
id|PeriodicOnly
)paren
suffix:semicolon
r_int
id|sPCIInitController
c_func
(paren
id|CONTROLLER_T
op_star
id|CtlP
comma
r_int
id|CtlNum
comma
id|ByteIO_t
op_star
id|AiopIOList
comma
r_int
id|AiopIOListSize
comma
r_int
id|IRQNum
comma
id|Byte_t
id|Frequency
comma
r_int
id|PeriodicOnly
)paren
suffix:semicolon
r_int
id|sReadAiopID
c_func
(paren
id|ByteIO_t
id|io
)paren
suffix:semicolon
r_int
id|sReadAiopNumChan
c_func
(paren
id|WordIO_t
id|io
)paren
suffix:semicolon
r_int
id|sInitChan
c_func
(paren
id|CONTROLLER_T
op_star
id|CtlP
comma
id|CHANNEL_T
op_star
id|ChP
comma
r_int
id|AiopNum
comma
r_int
id|ChanNum
)paren
suffix:semicolon
id|Byte_t
id|sGetRxErrStatus
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
)paren
suffix:semicolon
r_void
id|sStopRxProcessor
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
)paren
suffix:semicolon
r_void
id|sStopSWInFlowCtl
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
)paren
suffix:semicolon
r_void
id|sFlushRxFIFO
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
)paren
suffix:semicolon
r_void
id|sFlushTxFIFO
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
)paren
suffix:semicolon
r_int
id|sWriteTxPrioByte
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
comma
id|Byte_t
id|Data
)paren
suffix:semicolon
r_void
id|sEnInterrupts
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
comma
id|Word_t
id|Flags
)paren
suffix:semicolon
r_void
id|sDisInterrupts
c_func
(paren
id|CHANNEL_T
op_star
id|ChP
comma
id|Word_t
id|Flags
)paren
suffix:semicolon
r_extern
id|Byte_t
id|R
(braket
id|RDATASIZE
)braket
suffix:semicolon
r_extern
id|CONTROLLER_T
id|sController
(braket
id|CTL_SIZE
)braket
suffix:semicolon
r_extern
id|Byte_t
id|sIRQMap
(braket
l_int|16
)braket
suffix:semicolon
r_extern
id|Byte_t
id|sBitMapClrTbl
(braket
l_int|8
)braket
suffix:semicolon
r_extern
id|Byte_t
id|sBitMapSetTbl
(braket
l_int|8
)braket
suffix:semicolon
r_extern
r_int
id|sClockPrescale
suffix:semicolon
multiline_comment|/*&n; * Begin Linux specific definitions for the Rocketport driver&n; *&n; * This code is Copyright Theodore Ts&squot;o, 1995-1997&n; */
DECL|struct|r_port
r_struct
id|r_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|board
r_int
id|board
suffix:colon
l_int|2
suffix:semicolon
DECL|member|aiop
r_int
id|aiop
suffix:colon
l_int|2
suffix:semicolon
DECL|member|chan
r_int
id|chan
suffix:colon
l_int|3
suffix:semicolon
DECL|member|ctlp
id|CONTROLLER_t
op_star
id|ctlp
suffix:semicolon
DECL|member|channel
id|CHANNEL_t
id|channel
suffix:semicolon
DECL|member|closing_wait
r_int
id|closing_wait
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|intmask
r_int
id|intmask
suffix:semicolon
DECL|member|xmit_fifo_room
r_int
id|xmit_fifo_room
suffix:semicolon
multiline_comment|/* room in xmit fifo */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|cd_status
r_int
id|cd_status
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|cps
r_int
id|cps
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RPORT_MAGIC
mdefine_line|#define RPORT_MAGIC 0x525001
DECL|macro|NUM_BOARDS
mdefine_line|#define NUM_BOARDS 8
DECL|macro|MAX_RP_PORTS
mdefine_line|#define MAX_RP_PORTS (32*NUM_BOARDS)
multiline_comment|/*&n; * The size of the xmit buffer is 1 page, or 4096 bytes&n; */
DECL|macro|XMIT_BUF_SIZE
mdefine_line|#define XMIT_BUF_SIZE 4096
multiline_comment|/* number of characters left in xmit buffer before we ask for more */
DECL|macro|WAKEUP_CHARS
mdefine_line|#define WAKEUP_CHARS 256
multiline_comment|/* Internal flags used only by the rocketport driver */
DECL|macro|ROCKET_INITIALIZED
mdefine_line|#define ROCKET_INITIALIZED&t;0x80000000 /* Port is active */
DECL|macro|ROCKET_CLOSING
mdefine_line|#define ROCKET_CLOSING&t;&t;0x40000000 /* Serial port is closing */
DECL|macro|ROCKET_NORMAL_ACTIVE
mdefine_line|#define ROCKET_NORMAL_ACTIVE&t;0x20000000 /* Normal port is active */
DECL|macro|ROCKET_CALLOUT_ACTIVE
mdefine_line|#define ROCKET_CALLOUT_ACTIVE&t;0x10000000 /* Callout port is active */
multiline_comment|/*&n; * tty subtypes&n; *&n; */
DECL|macro|SERIAL_TYPE_NORMAL
mdefine_line|#define SERIAL_TYPE_NORMAL 1
DECL|macro|SERIAL_TYPE_CALLOUT
mdefine_line|#define SERIAL_TYPE_CALLOUT 2
multiline_comment|/*&n; * Assigned major numbers for the Comtrol Rocketport&n; */
DECL|macro|TTY_ROCKET_MAJOR
mdefine_line|#define TTY_ROCKET_MAJOR&t;46
DECL|macro|CUA_ROCKET_MAJOR
mdefine_line|#define CUA_ROCKET_MAJOR&t;47
multiline_comment|/*&n; * Utility function.&n; */
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a) &lt; (b) ? (a) : (b))
macro_line|#endif
macro_line|#ifdef PCI_VENDOR_ID_RP
DECL|macro|PCI_VENDOR_ID_RP
macro_line|#undef PCI_VENDOR_ID_RP
DECL|macro|PCI_DEVICE_ID_RP8OCTA
macro_line|#undef PCI_DEVICE_ID_RP8OCTA
DECL|macro|PCI_DEVICE_ID_RP8INTF
macro_line|#undef PCI_DEVICE_ID_RP8INTF
DECL|macro|PCI_DEVICE_ID_RP16INTF
macro_line|#undef PCI_DEVICE_ID_RP16INTF
DECL|macro|PCI_DEVICE_ID_RP32INTF
macro_line|#undef PCI_DEVICE_ID_RP32INTF
macro_line|#endif
DECL|macro|PCI_VENDOR_ID_RP
mdefine_line|#define PCI_VENDOR_ID_RP&t;&t;0x11fe
DECL|macro|PCI_DEVICE_ID_RP32INTF
mdefine_line|#define PCI_DEVICE_ID_RP32INTF&t;&t;0x0001
DECL|macro|PCI_DEVICE_ID_RP8INTF
mdefine_line|#define PCI_DEVICE_ID_RP8INTF&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_RP16INTF
mdefine_line|#define PCI_DEVICE_ID_RP16INTF&t;&t;0x0003
DECL|macro|PCI_DEVICE_ID_RP8OCTA
mdefine_line|#define PCI_DEVICE_ID_RP8OCTA&t;&t;0x0005
macro_line|#ifndef PCI_DEVICE_ID_RP4QUAD
DECL|macro|PCI_DEVICE_ID_RP4QUAD
mdefine_line|#define PCI_DEVICE_ID_RP4QUAD&t;&t;0x0004
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_RP8J
DECL|macro|PCI_DEVICE_ID_RP8J
mdefine_line|#define PCI_DEVICE_ID_RP8J&t;&t;0x0006
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_RPP4
DECL|macro|PCI_DEVICE_ID_RPP4
mdefine_line|#define PCI_DEVICE_ID_RPP4&t;&t;0x000A
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_RPP8
DECL|macro|PCI_DEVICE_ID_RPP8
mdefine_line|#define PCI_DEVICE_ID_RPP8&t;&t;0x000B
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_RP8M
DECL|macro|PCI_DEVICE_ID_RP8M
mdefine_line|#define PCI_DEVICE_ID_RP8M&t;&t;0x000C
macro_line|#endif&t;
eof
