multiline_comment|/*&n; *    in2000.h -  Linux device driver definitions for the&n; *                Always IN2000 ISA SCSI card.&n; *&n; *    IMPORTANT: This file is for version 1.33 - 26/Aug/1998&n; *&n; * Copyright (c) 1996 John Shifflett, GeoLog Consulting&n; *    john@geolog.com&n; *    jshiffle@netcom.com&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; */
macro_line|#ifndef IN2000_H
DECL|macro|IN2000_H
mdefine_line|#define IN2000_H
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|PROC_INTERFACE
mdefine_line|#define PROC_INTERFACE     /* add code for /proc/scsi/in2000/xxx interface */
macro_line|#ifdef  PROC_INTERFACE
DECL|macro|PROC_STATISTICS
mdefine_line|#define PROC_STATISTICS    /* add code for keeping various real time stats */
macro_line|#endif
DECL|macro|SYNC_DEBUG
mdefine_line|#define SYNC_DEBUG         /* extra info on sync negotiation printed */
DECL|macro|DEBUGGING_ON
mdefine_line|#define DEBUGGING_ON       /* enable command-line debugging bitmask */
DECL|macro|DEBUG_DEFAULTS
mdefine_line|#define DEBUG_DEFAULTS 0   /* default bitmask - change from command-line */
macro_line|#ifdef __i386__
DECL|macro|FAST_READ_IO
mdefine_line|#define FAST_READ_IO       /* No problems with these on my machine */
DECL|macro|FAST_WRITE_IO
mdefine_line|#define FAST_WRITE_IO
macro_line|#endif
macro_line|#ifdef DEBUGGING_ON
DECL|macro|DB
mdefine_line|#define DB(f,a) if (hostdata-&gt;args &amp; (f)) a;
DECL|macro|CHECK_NULL
mdefine_line|#define CHECK_NULL(p,s) /* if (!(p)) {printk(&quot;&bslash;n&quot;); while (1) printk(&quot;NP:%s&bslash;r&quot;,(s));} */
macro_line|#else
DECL|macro|DB
mdefine_line|#define DB(f,a)
DECL|macro|CHECK_NULL
mdefine_line|#define CHECK_NULL(p,s)
macro_line|#endif
DECL|macro|uchar
mdefine_line|#define uchar unsigned char
DECL|macro|read1_io
mdefine_line|#define read1_io(a)     (inb(hostdata-&gt;io_base+(a)))
DECL|macro|read2_io
mdefine_line|#define read2_io(a)     (inw(hostdata-&gt;io_base+(a)))
DECL|macro|write1_io
mdefine_line|#define write1_io(b,a)  (outb((b),hostdata-&gt;io_base+(a)))
DECL|macro|write2_io
mdefine_line|#define write2_io(w,a)  (outw((w),hostdata-&gt;io_base+(a)))
macro_line|#ifdef __i386__
multiline_comment|/* These inline assembly defines are derived from a patch&n; * sent to me by Bill Earnest. He&squot;s done a lot of very&n; * valuable thinking, testing, and coding during his effort&n; * to squeeze more speed out of this driver. I really think&n; * that we are doing IO at close to the maximum now with&n; * the fifo. (And yes, insw uses &squot;edi&squot; while outsw uses&n; * &squot;esi&squot;. Thanks Bill!)&n; */
DECL|macro|FAST_READ2_IO
mdefine_line|#define FAST_READ2_IO()    &bslash;&n;({ &bslash;&n;int __dummy_1,__dummy_2; &bslash;&n;   __asm__ __volatile__ (&quot;&bslash;n &bslash;&n;   cld                    &bslash;n &bslash;&n;   orl %%ecx, %%ecx       &bslash;n &bslash;&n;   jz 1f                  &bslash;n &bslash;&n;   rep                    &bslash;n &bslash;&n;   insw (%%dx),%%es:(%%edi) &bslash;n &bslash;&n;1: &quot;                       &bslash;&n;   : &quot;=D&quot; (sp) ,&quot;=c&quot; (__dummy_1) ,&quot;=d&quot; (__dummy_2)  /* output */   &bslash;&n;   : &quot;2&quot; (f), &quot;0&quot; (sp), &quot;1&quot; (i)  /* input */    &bslash;&n;   );       /* trashed */ &bslash;&n;})
DECL|macro|FAST_WRITE2_IO
mdefine_line|#define FAST_WRITE2_IO()   &bslash;&n;({ &bslash;&n;int __dummy_1,__dummy_2; &bslash;&n;   __asm__ __volatile__ (&quot;&bslash;n &bslash;&n;   cld                    &bslash;n &bslash;&n;   orl %%ecx, %%ecx       &bslash;n &bslash;&n;   jz 1f                  &bslash;n &bslash;&n;   rep                    &bslash;n &bslash;&n;   outsw %%ds:(%%esi),(%%dx) &bslash;n &bslash;&n;1: &quot;                       &bslash;&n;   : &quot;=S&quot; (sp) ,&quot;=c&quot; (__dummy_1) ,&quot;=d&quot; (__dummy_2)/* output */   &bslash;&n;   : &quot;2&quot; (f), &quot;0&quot; (sp), &quot;1&quot; (i)  /* input */    &bslash;&n;   );       /* trashed */ &bslash;&n;})
macro_line|#endif
multiline_comment|/* IN2000 io_port offsets */
DECL|macro|IO_WD_ASR
mdefine_line|#define IO_WD_ASR       0x00     /* R - 3393 auxstat reg */
DECL|macro|ASR_INT
mdefine_line|#define     ASR_INT        0x80
DECL|macro|ASR_LCI
mdefine_line|#define     ASR_LCI        0x40
DECL|macro|ASR_BSY
mdefine_line|#define     ASR_BSY        0x20
DECL|macro|ASR_CIP
mdefine_line|#define     ASR_CIP        0x10
DECL|macro|ASR_PE
mdefine_line|#define     ASR_PE         0x02
DECL|macro|ASR_DBR
mdefine_line|#define     ASR_DBR        0x01
DECL|macro|IO_WD_ADDR
mdefine_line|#define IO_WD_ADDR      0x00     /* W - 3393 address reg */
DECL|macro|IO_WD_DATA
mdefine_line|#define IO_WD_DATA      0x01     /* R/W - rest of 3393 regs */
DECL|macro|IO_FIFO
mdefine_line|#define IO_FIFO         0x02     /* R/W - in2000 dual-port fifo (16 bits) */
DECL|macro|IN2000_FIFO_SIZE
mdefine_line|#define IN2000_FIFO_SIZE   2048  /*    fifo capacity in bytes */
DECL|macro|IO_CARD_RESET
mdefine_line|#define IO_CARD_RESET   0x03     /* W - in2000 start master reset */
DECL|macro|IO_FIFO_COUNT
mdefine_line|#define IO_FIFO_COUNT   0x04     /* R - in2000 fifo counter */
DECL|macro|IO_FIFO_WRITE
mdefine_line|#define IO_FIFO_WRITE   0x05     /* W - clear fifo counter, start write */
DECL|macro|IO_FIFO_READ
mdefine_line|#define IO_FIFO_READ    0x07     /* W - start fifo read */
DECL|macro|IO_LED_OFF
mdefine_line|#define IO_LED_OFF      0x08     /* W - turn off in2000 activity LED */
DECL|macro|IO_SWITCHES
mdefine_line|#define IO_SWITCHES     0x08     /* R - read in2000 dip switch */
DECL|macro|SW_ADDR0
mdefine_line|#define     SW_ADDR0       0x01  /*    bit 0 = bit 0 of index to io addr */
DECL|macro|SW_ADDR1
mdefine_line|#define     SW_ADDR1       0x02  /*    bit 1 = bit 1 of index io addr */
DECL|macro|SW_DISINT
mdefine_line|#define     SW_DISINT      0x04  /*    bit 2 true if ints disabled */
DECL|macro|SW_INT0
mdefine_line|#define     SW_INT0        0x08  /*    bit 3 = bit 0 of index to interrupt */
DECL|macro|SW_INT1
mdefine_line|#define     SW_INT1        0x10  /*    bit 4 = bit 1 of index to interrupt */
DECL|macro|SW_INT_SHIFT
mdefine_line|#define     SW_INT_SHIFT   3     /*    shift right this amount to right justify int bits */
DECL|macro|SW_SYNC_DOS5
mdefine_line|#define     SW_SYNC_DOS5   0x20  /*    bit 5 used by Always BIOS */
DECL|macro|SW_FLOPPY
mdefine_line|#define     SW_FLOPPY      0x40  /*    bit 6 true if floppy enabled */
DECL|macro|SW_BIT7
mdefine_line|#define     SW_BIT7        0x80  /*    bit 7 hardwired true (ground) */
DECL|macro|IO_LED_ON
mdefine_line|#define IO_LED_ON       0x09     /* W - turn on in2000 activity LED */
DECL|macro|IO_HARDWARE
mdefine_line|#define IO_HARDWARE     0x0a     /* R - read in2000 hardware rev, stop reset */
DECL|macro|IO_INTR_MASK
mdefine_line|#define IO_INTR_MASK    0x0c     /* W - in2000 interrupt mask reg */
DECL|macro|IMASK_WD
mdefine_line|#define     IMASK_WD       0x01  /*    WD33c93 interrupt mask */
DECL|macro|IMASK_FIFO
mdefine_line|#define     IMASK_FIFO     0x02  /*    FIFO interrupt mask */
multiline_comment|/* wd register names */
DECL|macro|WD_OWN_ID
mdefine_line|#define WD_OWN_ID    0x00
DECL|macro|WD_CONTROL
mdefine_line|#define WD_CONTROL   0x01
DECL|macro|WD_TIMEOUT_PERIOD
mdefine_line|#define WD_TIMEOUT_PERIOD  0x02
DECL|macro|WD_CDB_1
mdefine_line|#define WD_CDB_1     0x03
DECL|macro|WD_CDB_2
mdefine_line|#define WD_CDB_2     0x04
DECL|macro|WD_CDB_3
mdefine_line|#define WD_CDB_3     0x05
DECL|macro|WD_CDB_4
mdefine_line|#define WD_CDB_4     0x06
DECL|macro|WD_CDB_5
mdefine_line|#define WD_CDB_5     0x07
DECL|macro|WD_CDB_6
mdefine_line|#define WD_CDB_6     0x08
DECL|macro|WD_CDB_7
mdefine_line|#define WD_CDB_7     0x09
DECL|macro|WD_CDB_8
mdefine_line|#define WD_CDB_8     0x0a
DECL|macro|WD_CDB_9
mdefine_line|#define WD_CDB_9     0x0b
DECL|macro|WD_CDB_10
mdefine_line|#define WD_CDB_10    0x0c
DECL|macro|WD_CDB_11
mdefine_line|#define WD_CDB_11    0x0d
DECL|macro|WD_CDB_12
mdefine_line|#define WD_CDB_12    0x0e
DECL|macro|WD_TARGET_LUN
mdefine_line|#define WD_TARGET_LUN      0x0f
DECL|macro|WD_COMMAND_PHASE
mdefine_line|#define WD_COMMAND_PHASE   0x10
DECL|macro|WD_SYNCHRONOUS_TRANSFER
mdefine_line|#define WD_SYNCHRONOUS_TRANSFER  0x11
DECL|macro|WD_TRANSFER_COUNT_MSB
mdefine_line|#define WD_TRANSFER_COUNT_MSB 0x12
DECL|macro|WD_TRANSFER_COUNT
mdefine_line|#define WD_TRANSFER_COUNT  0x13
DECL|macro|WD_TRANSFER_COUNT_LSB
mdefine_line|#define WD_TRANSFER_COUNT_LSB 0x14
DECL|macro|WD_DESTINATION_ID
mdefine_line|#define WD_DESTINATION_ID  0x15
DECL|macro|WD_SOURCE_ID
mdefine_line|#define WD_SOURCE_ID    0x16
DECL|macro|WD_SCSI_STATUS
mdefine_line|#define WD_SCSI_STATUS     0x17
DECL|macro|WD_COMMAND
mdefine_line|#define WD_COMMAND      0x18
DECL|macro|WD_DATA
mdefine_line|#define WD_DATA      0x19
DECL|macro|WD_QUEUE_TAG
mdefine_line|#define WD_QUEUE_TAG    0x1a
DECL|macro|WD_AUXILIARY_STATUS
mdefine_line|#define WD_AUXILIARY_STATUS   0x1f
multiline_comment|/* WD commands */
DECL|macro|WD_CMD_RESET
mdefine_line|#define WD_CMD_RESET    0x00
DECL|macro|WD_CMD_ABORT
mdefine_line|#define WD_CMD_ABORT    0x01
DECL|macro|WD_CMD_ASSERT_ATN
mdefine_line|#define WD_CMD_ASSERT_ATN  0x02
DECL|macro|WD_CMD_NEGATE_ACK
mdefine_line|#define WD_CMD_NEGATE_ACK  0x03
DECL|macro|WD_CMD_DISCONNECT
mdefine_line|#define WD_CMD_DISCONNECT  0x04
DECL|macro|WD_CMD_RESELECT
mdefine_line|#define WD_CMD_RESELECT    0x05
DECL|macro|WD_CMD_SEL_ATN
mdefine_line|#define WD_CMD_SEL_ATN     0x06
DECL|macro|WD_CMD_SEL
mdefine_line|#define WD_CMD_SEL      0x07
DECL|macro|WD_CMD_SEL_ATN_XFER
mdefine_line|#define WD_CMD_SEL_ATN_XFER   0x08
DECL|macro|WD_CMD_SEL_XFER
mdefine_line|#define WD_CMD_SEL_XFER    0x09
DECL|macro|WD_CMD_RESEL_RECEIVE
mdefine_line|#define WD_CMD_RESEL_RECEIVE  0x0a
DECL|macro|WD_CMD_RESEL_SEND
mdefine_line|#define WD_CMD_RESEL_SEND  0x0b
DECL|macro|WD_CMD_WAIT_SEL_RECEIVE
mdefine_line|#define WD_CMD_WAIT_SEL_RECEIVE 0x0c
DECL|macro|WD_CMD_TRANS_ADDR
mdefine_line|#define WD_CMD_TRANS_ADDR  0x18
DECL|macro|WD_CMD_TRANS_INFO
mdefine_line|#define WD_CMD_TRANS_INFO  0x20
DECL|macro|WD_CMD_TRANSFER_PAD
mdefine_line|#define WD_CMD_TRANSFER_PAD   0x21
DECL|macro|WD_CMD_SBT_MODE
mdefine_line|#define WD_CMD_SBT_MODE    0x80
multiline_comment|/* SCSI Bus Phases */
DECL|macro|PHS_DATA_OUT
mdefine_line|#define PHS_DATA_OUT    0x00
DECL|macro|PHS_DATA_IN
mdefine_line|#define PHS_DATA_IN     0x01
DECL|macro|PHS_COMMAND
mdefine_line|#define PHS_COMMAND     0x02
DECL|macro|PHS_STATUS
mdefine_line|#define PHS_STATUS      0x03
DECL|macro|PHS_MESS_OUT
mdefine_line|#define PHS_MESS_OUT    0x06
DECL|macro|PHS_MESS_IN
mdefine_line|#define PHS_MESS_IN     0x07
multiline_comment|/* Command Status Register definitions */
multiline_comment|/* reset state interrupts */
DECL|macro|CSR_RESET
mdefine_line|#define CSR_RESET    0x00
DECL|macro|CSR_RESET_AF
mdefine_line|#define CSR_RESET_AF    0x01
multiline_comment|/* successful completion interrupts */
DECL|macro|CSR_RESELECT
mdefine_line|#define CSR_RESELECT    0x10
DECL|macro|CSR_SELECT
mdefine_line|#define CSR_SELECT      0x11
DECL|macro|CSR_SEL_XFER_DONE
mdefine_line|#define CSR_SEL_XFER_DONE  0x16
DECL|macro|CSR_XFER_DONE
mdefine_line|#define CSR_XFER_DONE      0x18
multiline_comment|/* paused or aborted interrupts */
DECL|macro|CSR_MSGIN
mdefine_line|#define CSR_MSGIN    0x20
DECL|macro|CSR_SDP
mdefine_line|#define CSR_SDP         0x21
DECL|macro|CSR_SEL_ABORT
mdefine_line|#define CSR_SEL_ABORT      0x22
DECL|macro|CSR_RESEL_ABORT
mdefine_line|#define CSR_RESEL_ABORT    0x25
DECL|macro|CSR_RESEL_ABORT_AM
mdefine_line|#define CSR_RESEL_ABORT_AM 0x27
DECL|macro|CSR_ABORT
mdefine_line|#define CSR_ABORT    0x28
multiline_comment|/* terminated interrupts */
DECL|macro|CSR_INVALID
mdefine_line|#define CSR_INVALID     0x40
DECL|macro|CSR_UNEXP_DISC
mdefine_line|#define CSR_UNEXP_DISC     0x41
DECL|macro|CSR_TIMEOUT
mdefine_line|#define CSR_TIMEOUT     0x42
DECL|macro|CSR_PARITY
mdefine_line|#define CSR_PARITY      0x43
DECL|macro|CSR_PARITY_ATN
mdefine_line|#define CSR_PARITY_ATN     0x44
DECL|macro|CSR_BAD_STATUS
mdefine_line|#define CSR_BAD_STATUS     0x45
DECL|macro|CSR_UNEXP
mdefine_line|#define CSR_UNEXP    0x48
multiline_comment|/* service required interrupts */
DECL|macro|CSR_RESEL
mdefine_line|#define CSR_RESEL    0x80
DECL|macro|CSR_RESEL_AM
mdefine_line|#define CSR_RESEL_AM    0x81
DECL|macro|CSR_DISC
mdefine_line|#define CSR_DISC     0x85
DECL|macro|CSR_SRV_REQ
mdefine_line|#define CSR_SRV_REQ     0x88
multiline_comment|/* Own ID/CDB Size register */
DECL|macro|OWNID_EAF
mdefine_line|#define OWNID_EAF    0x08
DECL|macro|OWNID_EHP
mdefine_line|#define OWNID_EHP    0x10
DECL|macro|OWNID_RAF
mdefine_line|#define OWNID_RAF    0x20
DECL|macro|OWNID_FS_8
mdefine_line|#define OWNID_FS_8   0x00
DECL|macro|OWNID_FS_12
mdefine_line|#define OWNID_FS_12  0x40
DECL|macro|OWNID_FS_16
mdefine_line|#define OWNID_FS_16  0x80
multiline_comment|/* Control register */
DECL|macro|CTRL_HSP
mdefine_line|#define CTRL_HSP     0x01
DECL|macro|CTRL_HA
mdefine_line|#define CTRL_HA      0x02
DECL|macro|CTRL_IDI
mdefine_line|#define CTRL_IDI     0x04
DECL|macro|CTRL_EDI
mdefine_line|#define CTRL_EDI     0x08
DECL|macro|CTRL_HHP
mdefine_line|#define CTRL_HHP     0x10
DECL|macro|CTRL_POLLED
mdefine_line|#define CTRL_POLLED  0x00
DECL|macro|CTRL_BURST
mdefine_line|#define CTRL_BURST   0x20
DECL|macro|CTRL_BUS
mdefine_line|#define CTRL_BUS     0x40
DECL|macro|CTRL_DMA
mdefine_line|#define CTRL_DMA     0x80
multiline_comment|/* Timeout Period register */
DECL|macro|TIMEOUT_PERIOD_VALUE
mdefine_line|#define TIMEOUT_PERIOD_VALUE  20    /* results in 200 ms. */
multiline_comment|/* Synchronous Transfer Register */
DECL|macro|STR_FSS
mdefine_line|#define STR_FSS      0x80
multiline_comment|/* Destination ID register */
DECL|macro|DSTID_DPD
mdefine_line|#define DSTID_DPD    0x40
DECL|macro|DATA_OUT_DIR
mdefine_line|#define DATA_OUT_DIR 0
DECL|macro|DATA_IN_DIR
mdefine_line|#define DATA_IN_DIR  1
DECL|macro|DSTID_SCC
mdefine_line|#define DSTID_SCC    0x80
multiline_comment|/* Source ID register */
DECL|macro|SRCID_MASK
mdefine_line|#define SRCID_MASK   0x07
DECL|macro|SRCID_SIV
mdefine_line|#define SRCID_SIV    0x08
DECL|macro|SRCID_DSP
mdefine_line|#define SRCID_DSP    0x20
DECL|macro|SRCID_ES
mdefine_line|#define SRCID_ES     0x40
DECL|macro|SRCID_ER
mdefine_line|#define SRCID_ER     0x80
DECL|macro|ILLEGAL_STATUS_BYTE
mdefine_line|#define ILLEGAL_STATUS_BYTE   0xff
DECL|macro|DEFAULT_SX_PER
mdefine_line|#define DEFAULT_SX_PER     500   /* (ns) fairly safe */
DECL|macro|DEFAULT_SX_OFF
mdefine_line|#define DEFAULT_SX_OFF     0     /* aka async */
DECL|macro|OPTIMUM_SX_PER
mdefine_line|#define OPTIMUM_SX_PER     252   /* (ns) best we can do (mult-of-4) */
DECL|macro|OPTIMUM_SX_OFF
mdefine_line|#define OPTIMUM_SX_OFF     12    /* size of in2000 fifo */
DECL|struct|sx_period
r_struct
id|sx_period
(brace
DECL|member|period_ns
r_int
r_int
id|period_ns
suffix:semicolon
DECL|member|reg_value
id|uchar
id|reg_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|IN2000_hostdata
r_struct
id|IN2000_hostdata
(brace
DECL|member|next
r_struct
id|Scsi_Host
op_star
id|next
suffix:semicolon
DECL|member|chip
id|uchar
id|chip
suffix:semicolon
multiline_comment|/* what kind of wd33c93 chip? */
DECL|member|microcode
id|uchar
id|microcode
suffix:semicolon
multiline_comment|/* microcode rev if &squot;B&squot; */
DECL|member|io_base
r_int
r_int
id|io_base
suffix:semicolon
multiline_comment|/* IO port base */
DECL|member|dip_switch
r_int
r_int
id|dip_switch
suffix:semicolon
multiline_comment|/* dip switch settings */
DECL|member|hrev
r_int
r_int
id|hrev
suffix:semicolon
multiline_comment|/* hardware revision of card */
DECL|member|busy
r_volatile
id|uchar
id|busy
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* index = target, bit = lun */
DECL|member|input_Q
r_volatile
id|Scsi_Cmnd
op_star
id|input_Q
suffix:semicolon
multiline_comment|/* commands waiting to be started */
DECL|member|selecting
r_volatile
id|Scsi_Cmnd
op_star
id|selecting
suffix:semicolon
multiline_comment|/* trying to select this command */
DECL|member|connected
r_volatile
id|Scsi_Cmnd
op_star
id|connected
suffix:semicolon
multiline_comment|/* currently connected command */
DECL|member|disconnected_Q
r_volatile
id|Scsi_Cmnd
op_star
id|disconnected_Q
suffix:semicolon
multiline_comment|/* commands waiting for reconnect */
DECL|member|state
id|uchar
id|state
suffix:semicolon
multiline_comment|/* what we are currently doing */
DECL|member|fifo
id|uchar
id|fifo
suffix:semicolon
multiline_comment|/* what the FIFO is up to */
DECL|member|level2
id|uchar
id|level2
suffix:semicolon
multiline_comment|/* extent to which Level-2 commands are used */
DECL|member|disconnect
id|uchar
id|disconnect
suffix:semicolon
multiline_comment|/* disconnect/reselect policy */
DECL|member|args
r_int
r_int
id|args
suffix:semicolon
multiline_comment|/* set from command-line argument */
DECL|member|incoming_msg
id|uchar
id|incoming_msg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* filled during message_in phase */
DECL|member|incoming_ptr
r_int
id|incoming_ptr
suffix:semicolon
multiline_comment|/* mainly used with EXTENDED messages */
DECL|member|outgoing_msg
id|uchar
id|outgoing_msg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* send this during next message_out */
DECL|member|outgoing_len
r_int
id|outgoing_len
suffix:semicolon
multiline_comment|/* length of outgoing message */
DECL|member|default_sx_per
r_int
r_int
id|default_sx_per
suffix:semicolon
multiline_comment|/* default transfer period for SCSI bus */
DECL|member|sync_xfer
id|uchar
id|sync_xfer
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* sync_xfer reg settings per target */
DECL|member|sync_stat
id|uchar
id|sync_stat
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* status of sync negotiation per target */
DECL|member|sync_off
id|uchar
id|sync_off
suffix:semicolon
multiline_comment|/* bit mask: don&squot;t use sync with these targets */
macro_line|#ifdef PROC_INTERFACE
DECL|member|proc
id|uchar
id|proc
suffix:semicolon
multiline_comment|/* bit mask: what&squot;s in proc output */
macro_line|#ifdef PROC_STATISTICS
DECL|member|cmd_cnt
r_int
r_int
id|cmd_cnt
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* # of commands issued per target */
DECL|member|int_cnt
r_int
r_int
id|int_cnt
suffix:semicolon
multiline_comment|/* # of interrupts serviced */
DECL|member|disc_allowed_cnt
r_int
r_int
id|disc_allowed_cnt
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* # of disconnects allowed per target */
DECL|member|disc_done_cnt
r_int
r_int
id|disc_done_cnt
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* # of disconnects done per target*/
macro_line|#endif
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* defines for hostdata-&gt;chip */
DECL|macro|C_WD33C93
mdefine_line|#define C_WD33C93       0
DECL|macro|C_WD33C93A
mdefine_line|#define C_WD33C93A      1
DECL|macro|C_WD33C93B
mdefine_line|#define C_WD33C93B      2
DECL|macro|C_UNKNOWN_CHIP
mdefine_line|#define C_UNKNOWN_CHIP  100
multiline_comment|/* defines for hostdata-&gt;state */
DECL|macro|S_UNCONNECTED
mdefine_line|#define S_UNCONNECTED         0
DECL|macro|S_SELECTING
mdefine_line|#define S_SELECTING           1
DECL|macro|S_RUNNING_LEVEL2
mdefine_line|#define S_RUNNING_LEVEL2      2
DECL|macro|S_CONNECTED
mdefine_line|#define S_CONNECTED           3
DECL|macro|S_PRE_TMP_DISC
mdefine_line|#define S_PRE_TMP_DISC        4
DECL|macro|S_PRE_CMP_DISC
mdefine_line|#define S_PRE_CMP_DISC        5
multiline_comment|/* defines for hostdata-&gt;fifo */
DECL|macro|FI_FIFO_UNUSED
mdefine_line|#define FI_FIFO_UNUSED        0
DECL|macro|FI_FIFO_READING
mdefine_line|#define FI_FIFO_READING       1
DECL|macro|FI_FIFO_WRITING
mdefine_line|#define FI_FIFO_WRITING       2
multiline_comment|/* defines for hostdata-&gt;level2 */
multiline_comment|/* NOTE: only the first 3 are trustworthy at this point -&n; * having trouble when more than 1 device is reading/writing&n; * at the same time...&n; */
DECL|macro|L2_NONE
mdefine_line|#define L2_NONE      0  /* no combination commands - we get lots of ints */
DECL|macro|L2_SELECT
mdefine_line|#define L2_SELECT    1  /* start with SEL_ATN_XFER, but never resume it */
DECL|macro|L2_BASIC
mdefine_line|#define L2_BASIC     2  /* resume after STATUS ints &amp; RDP messages */
DECL|macro|L2_DATA
mdefine_line|#define L2_DATA      3  /* resume after DATA_IN/OUT ints */
DECL|macro|L2_MOST
mdefine_line|#define L2_MOST      4  /* resume after anything except a RESELECT int */
DECL|macro|L2_RESELECT
mdefine_line|#define L2_RESELECT  5  /* resume after everything, including RESELECT ints */
DECL|macro|L2_ALL
mdefine_line|#define L2_ALL       6  /* always resume */
multiline_comment|/* defines for hostdata-&gt;disconnect */
DECL|macro|DIS_NEVER
mdefine_line|#define DIS_NEVER    0
DECL|macro|DIS_ADAPTIVE
mdefine_line|#define DIS_ADAPTIVE 1
DECL|macro|DIS_ALWAYS
mdefine_line|#define DIS_ALWAYS   2
multiline_comment|/* defines for hostdata-&gt;args */
DECL|macro|DB_TEST
mdefine_line|#define DB_TEST               1&lt;&lt;0
DECL|macro|DB_FIFO
mdefine_line|#define DB_FIFO               1&lt;&lt;1
DECL|macro|DB_QUEUE_COMMAND
mdefine_line|#define DB_QUEUE_COMMAND      1&lt;&lt;2
DECL|macro|DB_EXECUTE
mdefine_line|#define DB_EXECUTE            1&lt;&lt;3
DECL|macro|DB_INTR
mdefine_line|#define DB_INTR               1&lt;&lt;4
DECL|macro|DB_TRANSFER
mdefine_line|#define DB_TRANSFER           1&lt;&lt;5
DECL|macro|DB_MASK
mdefine_line|#define DB_MASK               0x3f
DECL|macro|A_NO_SCSI_RESET
mdefine_line|#define A_NO_SCSI_RESET       1&lt;&lt;15
multiline_comment|/* defines for hostdata-&gt;sync_xfer[] */
DECL|macro|SS_UNSET
mdefine_line|#define SS_UNSET     0
DECL|macro|SS_FIRST
mdefine_line|#define SS_FIRST     1
DECL|macro|SS_WAITING
mdefine_line|#define SS_WAITING   2
DECL|macro|SS_SET
mdefine_line|#define SS_SET       3
multiline_comment|/* defines for hostdata-&gt;proc */
DECL|macro|PR_VERSION
mdefine_line|#define PR_VERSION   1&lt;&lt;0
DECL|macro|PR_INFO
mdefine_line|#define PR_INFO      1&lt;&lt;1
DECL|macro|PR_STATISTICS
mdefine_line|#define PR_STATISTICS 1&lt;&lt;2
DECL|macro|PR_CONNECTED
mdefine_line|#define PR_CONNECTED 1&lt;&lt;3
DECL|macro|PR_INPUTQ
mdefine_line|#define PR_INPUTQ    1&lt;&lt;4
DECL|macro|PR_DISCQ
mdefine_line|#define PR_DISCQ     1&lt;&lt;5
DECL|macro|PR_TEST
mdefine_line|#define PR_TEST      1&lt;&lt;6
DECL|macro|PR_STOP
mdefine_line|#define PR_STOP      1&lt;&lt;7
macro_line|#include &lt;linux/version.h&gt;
macro_line|# include &lt;linux/init.h&gt;
macro_line|# include &lt;linux/spinlock.h&gt;
DECL|macro|in2000__INITFUNC
macro_line|# define in2000__INITFUNC(function) __initfunc(function)
DECL|macro|in2000__INIT
macro_line|# define in2000__INIT __init
DECL|macro|in2000__INITDATA
macro_line|# define in2000__INITDATA __initdata
DECL|macro|CLISPIN_LOCK
macro_line|# define CLISPIN_LOCK(host,flags)   spin_lock_irqsave(host-&gt;host_lock, flags)
DECL|macro|CLISPIN_UNLOCK
macro_line|# define CLISPIN_UNLOCK(host,flags) spin_unlock_irqrestore(host-&gt;host_lock, &bslash;&n;&t;&t;&t;&t;&t;&t;&t;   flags)
r_int
id|in2000_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
id|in2000__INIT
suffix:semicolon
r_int
id|in2000_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|in2000_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_void
id|in2000_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
id|in2000__INIT
suffix:semicolon
r_int
id|in2000_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|in2000_biosparam
c_func
(paren
r_struct
id|scsi_disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|in2000_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|IN2000_CAN_Q
mdefine_line|#define IN2000_CAN_Q    16
DECL|macro|IN2000_SG
mdefine_line|#define IN2000_SG       SG_ALL
DECL|macro|IN2000_CPL
mdefine_line|#define IN2000_CPL      2
DECL|macro|IN2000_HOST_ID
mdefine_line|#define IN2000_HOST_ID  7
DECL|macro|IN2000
mdefine_line|#define IN2000 {  proc_name:       &quot;in2000&quot;,&t;&t;/* name of /proc/scsi directory entry */ &bslash;&n;                  proc_info:       in2000_proc_info,    /* pointer to proc info function */ &bslash;&n;                  name:            &quot;Always IN2000&quot;,     /* device name */ &bslash;&n;                  detect:          in2000_detect,       /* returns number of in2000&squot;s found */ &bslash;&n;                  queuecommand:    in2000_queuecommand, /* queue scsi command, don&squot;t wait */ &bslash;&n;                  abort:           in2000_abort,        /* abort current command */ &bslash;&n;                  reset:           in2000_reset,        /* reset scsi bus */ &bslash;&n;                  bios_param:      in2000_biosparam,    /* figures out BIOS parameters for lilo, etc */ &bslash;&n;                  can_queue:       IN2000_CAN_Q,        /* max commands we can queue up */ &bslash;&n;                  this_id:         IN2000_HOST_ID,      /* host-adapter scsi id */ &bslash;&n;                  sg_tablesize:    IN2000_SG,           /* scatter-gather table size */ &bslash;&n;                  cmd_per_lun:     IN2000_CPL,          /* commands per lun */ &bslash;&n;                  use_clustering:  DISABLE_CLUSTERING,  /* ENABLE_CLUSTERING may speed things up */ &bslash;&n;                }
macro_line|#endif /* IN2000_H */
eof
