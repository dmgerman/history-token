multiline_comment|/* &n; * drivers/net/gianfar.h&n; *&n; * Gianfar Ethernet Driver&n; * Driver for FEC on MPC8540 and TSEC on MPC8540/MPC8560&n; * Based on 8260_io/fcc_enet.c&n; *&n; * Author: Andy Fleming&n; * Maintainer: Kumar Gala (kumar.gala@freescale.com)&n; *&n; * Copyright (c) 2002-2004 Freescale Semiconductor, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; *  Still left to do:&n; *      -Add support for module parameters&n; *&t;-Add support for ethtool -s&n; *&t;-Add patch for ethtool phys id&n; */
macro_line|#ifndef __GIANFAR_H
DECL|macro|__GIANFAR_H
mdefine_line|#define __GIANFAR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fsl_devices.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;gianfar_phy.h&quot;
multiline_comment|/* The maximum number of packets to be handled in one call of gfar_poll */
DECL|macro|GFAR_DEV_WEIGHT
mdefine_line|#define GFAR_DEV_WEIGHT 64
multiline_comment|/* Number of bytes to align the rx bufs to */
DECL|macro|RXBUF_ALIGNMENT
mdefine_line|#define RXBUF_ALIGNMENT 64
multiline_comment|/* The number of bytes which composes a unit for the purpose of&n; * allocating data buffers.  ie-for any given MTU, the data buffer&n; * will be the next highest multiple of 512 bytes. */
DECL|macro|INCREMENTAL_BUFFER_SIZE
mdefine_line|#define INCREMENTAL_BUFFER_SIZE 512
DECL|macro|MAC_ADDR_LEN
mdefine_line|#define MAC_ADDR_LEN 6
DECL|macro|PHY_INIT_TIMEOUT
mdefine_line|#define PHY_INIT_TIMEOUT 100000
DECL|macro|GFAR_PHY_CHANGE_TIME
mdefine_line|#define GFAR_PHY_CHANGE_TIME 2
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;%s: Gianfar Ethernet Controller Version 1.1, &quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME &quot;gfar-enet&quot;
r_extern
r_const
r_char
id|gfar_driver_name
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|gfar_driver_version
(braket
)braket
suffix:semicolon
multiline_comment|/* These need to be powers of 2 for this driver */
macro_line|#ifdef CONFIG_GFAR_NAPI
DECL|macro|DEFAULT_TX_RING_SIZE
mdefine_line|#define DEFAULT_TX_RING_SIZE&t;256
DECL|macro|DEFAULT_RX_RING_SIZE
mdefine_line|#define DEFAULT_RX_RING_SIZE&t;256
macro_line|#else
DECL|macro|DEFAULT_TX_RING_SIZE
mdefine_line|#define DEFAULT_TX_RING_SIZE    64
DECL|macro|DEFAULT_RX_RING_SIZE
mdefine_line|#define DEFAULT_RX_RING_SIZE    64
macro_line|#endif
DECL|macro|GFAR_RX_MAX_RING_SIZE
mdefine_line|#define GFAR_RX_MAX_RING_SIZE   256
DECL|macro|GFAR_TX_MAX_RING_SIZE
mdefine_line|#define GFAR_TX_MAX_RING_SIZE   256
DECL|macro|DEFAULT_RX_BUFFER_SIZE
mdefine_line|#define DEFAULT_RX_BUFFER_SIZE  1536
DECL|macro|TX_RING_MOD_MASK
mdefine_line|#define TX_RING_MOD_MASK(size) (size-1)
DECL|macro|RX_RING_MOD_MASK
mdefine_line|#define RX_RING_MOD_MASK(size) (size-1)
DECL|macro|JUMBO_BUFFER_SIZE
mdefine_line|#define JUMBO_BUFFER_SIZE 9728
DECL|macro|JUMBO_FRAME_SIZE
mdefine_line|#define JUMBO_FRAME_SIZE 9600
multiline_comment|/* Latency of interface clock in nanoseconds */
multiline_comment|/* Interface clock latency , in this case, means the &n; * time described by a value of 1 in the interrupt&n; * coalescing registers&squot; time fields.  Since those fields&n; * refer to the time it takes for 64 clocks to pass, the&n; * latencies are as such:&n; * GBIT = 125MHz =&gt; 8ns/clock =&gt; 8*64 ns / tick&n; * 100 = 25 MHz =&gt; 40ns/clock =&gt; 40*64 ns / tick&n; * 10 = 2.5 MHz =&gt; 400ns/clock =&gt; 400*64 ns / tick&n; */
DECL|macro|GFAR_GBIT_TIME
mdefine_line|#define GFAR_GBIT_TIME  512
DECL|macro|GFAR_100_TIME
mdefine_line|#define GFAR_100_TIME   2560
DECL|macro|GFAR_10_TIME
mdefine_line|#define GFAR_10_TIME    25600
DECL|macro|DEFAULT_TX_COALESCE
mdefine_line|#define DEFAULT_TX_COALESCE 1
DECL|macro|DEFAULT_TXCOUNT
mdefine_line|#define DEFAULT_TXCOUNT&t;16
DECL|macro|DEFAULT_TXTIME
mdefine_line|#define DEFAULT_TXTIME&t;400
DECL|macro|DEFAULT_RX_COALESCE
mdefine_line|#define DEFAULT_RX_COALESCE 1
DECL|macro|DEFAULT_RXCOUNT
mdefine_line|#define DEFAULT_RXCOUNT&t;16
DECL|macro|DEFAULT_RXTIME
mdefine_line|#define DEFAULT_RXTIME&t;400
DECL|macro|TBIPA_VALUE
mdefine_line|#define TBIPA_VALUE&t;&t;0x1f
DECL|macro|MIIMCFG_INIT_VALUE
mdefine_line|#define MIIMCFG_INIT_VALUE&t;0x00000007
DECL|macro|MIIMCFG_RESET
mdefine_line|#define MIIMCFG_RESET           0x80000000
DECL|macro|MIIMIND_BUSY
mdefine_line|#define MIIMIND_BUSY            0x00000001
multiline_comment|/* MAC register bits */
DECL|macro|MACCFG1_SOFT_RESET
mdefine_line|#define MACCFG1_SOFT_RESET&t;0x80000000
DECL|macro|MACCFG1_RESET_RX_MC
mdefine_line|#define MACCFG1_RESET_RX_MC&t;0x00080000
DECL|macro|MACCFG1_RESET_TX_MC
mdefine_line|#define MACCFG1_RESET_TX_MC&t;0x00040000
DECL|macro|MACCFG1_RESET_RX_FUN
mdefine_line|#define MACCFG1_RESET_RX_FUN&t;0x00020000
DECL|macro|MACCFG1_RESET_TX_FUN
mdefine_line|#define&t;MACCFG1_RESET_TX_FUN&t;0x00010000
DECL|macro|MACCFG1_LOOPBACK
mdefine_line|#define MACCFG1_LOOPBACK&t;0x00000100
DECL|macro|MACCFG1_RX_FLOW
mdefine_line|#define MACCFG1_RX_FLOW&t;&t;0x00000020
DECL|macro|MACCFG1_TX_FLOW
mdefine_line|#define MACCFG1_TX_FLOW&t;&t;0x00000010
DECL|macro|MACCFG1_SYNCD_RX_EN
mdefine_line|#define MACCFG1_SYNCD_RX_EN&t;0x00000008
DECL|macro|MACCFG1_RX_EN
mdefine_line|#define MACCFG1_RX_EN&t;&t;0x00000004
DECL|macro|MACCFG1_SYNCD_TX_EN
mdefine_line|#define MACCFG1_SYNCD_TX_EN&t;0x00000002
DECL|macro|MACCFG1_TX_EN
mdefine_line|#define MACCFG1_TX_EN&t;&t;0x00000001
DECL|macro|MACCFG2_INIT_SETTINGS
mdefine_line|#define MACCFG2_INIT_SETTINGS&t;0x00007205
DECL|macro|MACCFG2_FULL_DUPLEX
mdefine_line|#define MACCFG2_FULL_DUPLEX&t;0x00000001
DECL|macro|MACCFG2_IF
mdefine_line|#define MACCFG2_IF              0x00000300
DECL|macro|MACCFG2_MII
mdefine_line|#define MACCFG2_MII             0x00000100
DECL|macro|MACCFG2_GMII
mdefine_line|#define MACCFG2_GMII            0x00000200
DECL|macro|MACCFG2_HUGEFRAME
mdefine_line|#define MACCFG2_HUGEFRAME&t;0x00000020
DECL|macro|MACCFG2_LENGTHCHECK
mdefine_line|#define MACCFG2_LENGTHCHECK&t;0x00000010
DECL|macro|ECNTRL_INIT_SETTINGS
mdefine_line|#define ECNTRL_INIT_SETTINGS&t;0x00001000
DECL|macro|ECNTRL_TBI_MODE
mdefine_line|#define ECNTRL_TBI_MODE         0x00000020
DECL|macro|MRBLR_INIT_SETTINGS
mdefine_line|#define MRBLR_INIT_SETTINGS&t;DEFAULT_RX_BUFFER_SIZE
DECL|macro|MINFLR_INIT_SETTINGS
mdefine_line|#define MINFLR_INIT_SETTINGS&t;0x00000040
multiline_comment|/* Init to do tx snooping for buffers and descriptors */
DECL|macro|DMACTRL_INIT_SETTINGS
mdefine_line|#define DMACTRL_INIT_SETTINGS   0x000000c3
DECL|macro|DMACTRL_GRS
mdefine_line|#define DMACTRL_GRS             0x00000010
DECL|macro|DMACTRL_GTS
mdefine_line|#define DMACTRL_GTS             0x00000008
DECL|macro|TSTAT_CLEAR_THALT
mdefine_line|#define TSTAT_CLEAR_THALT       0x80000000
multiline_comment|/* Interrupt coalescing macros */
DECL|macro|IC_ICEN
mdefine_line|#define IC_ICEN&t;&t;&t;0x80000000
DECL|macro|IC_ICFT_MASK
mdefine_line|#define IC_ICFT_MASK&t;&t;0x1fe00000
DECL|macro|IC_ICFT_SHIFT
mdefine_line|#define IC_ICFT_SHIFT&t;&t;21
DECL|macro|mk_ic_icft
mdefine_line|#define mk_ic_icft(x)&t;&t;&bslash;&n;&t;(((unsigned int)x &lt;&lt; IC_ICFT_SHIFT)&amp;IC_ICFT_MASK)
DECL|macro|IC_ICTT_MASK
mdefine_line|#define IC_ICTT_MASK&t;&t;0x0000ffff
DECL|macro|mk_ic_ictt
mdefine_line|#define mk_ic_ictt(x)&t;&t;(x&amp;IC_ICTT_MASK)
DECL|macro|mk_ic_value
mdefine_line|#define mk_ic_value(count, time) (IC_ICEN | &bslash;&n;&t;&t;&t;&t;mk_ic_icft(count) | &bslash;&n;&t;&t;&t;&t;mk_ic_ictt(time))
DECL|macro|RCTRL_PROM
mdefine_line|#define RCTRL_PROM&t;&t;0x00000008
DECL|macro|RSTAT_CLEAR_RHALT
mdefine_line|#define RSTAT_CLEAR_RHALT       0x00800000
DECL|macro|IEVENT_INIT_CLEAR
mdefine_line|#define IEVENT_INIT_CLEAR&t;0xffffffff
DECL|macro|IEVENT_BABR
mdefine_line|#define IEVENT_BABR&t;&t;0x80000000
DECL|macro|IEVENT_RXC
mdefine_line|#define IEVENT_RXC&t;&t;0x40000000
DECL|macro|IEVENT_BSY
mdefine_line|#define IEVENT_BSY&t;&t;0x20000000
DECL|macro|IEVENT_EBERR
mdefine_line|#define IEVENT_EBERR&t;&t;0x10000000
DECL|macro|IEVENT_MSRO
mdefine_line|#define IEVENT_MSRO&t;&t;0x04000000
DECL|macro|IEVENT_GTSC
mdefine_line|#define IEVENT_GTSC&t;&t;0x02000000
DECL|macro|IEVENT_BABT
mdefine_line|#define IEVENT_BABT&t;&t;0x01000000
DECL|macro|IEVENT_TXC
mdefine_line|#define IEVENT_TXC&t;&t;0x00800000
DECL|macro|IEVENT_TXE
mdefine_line|#define IEVENT_TXE&t;&t;0x00400000
DECL|macro|IEVENT_TXB
mdefine_line|#define IEVENT_TXB&t;&t;0x00200000
DECL|macro|IEVENT_TXF
mdefine_line|#define IEVENT_TXF&t;&t;0x00100000
DECL|macro|IEVENT_LC
mdefine_line|#define IEVENT_LC&t;&t;0x00040000
DECL|macro|IEVENT_CRL
mdefine_line|#define IEVENT_CRL&t;&t;0x00020000
DECL|macro|IEVENT_XFUN
mdefine_line|#define IEVENT_XFUN&t;&t;0x00010000
DECL|macro|IEVENT_RXB0
mdefine_line|#define IEVENT_RXB0&t;&t;0x00008000
DECL|macro|IEVENT_GRSC
mdefine_line|#define IEVENT_GRSC&t;&t;0x00000100
DECL|macro|IEVENT_RXF0
mdefine_line|#define IEVENT_RXF0&t;&t;0x00000080
DECL|macro|IEVENT_RX_MASK
mdefine_line|#define IEVENT_RX_MASK          (IEVENT_RXB0 | IEVENT_RXF0)
DECL|macro|IEVENT_TX_MASK
mdefine_line|#define IEVENT_TX_MASK          (IEVENT_TXB | IEVENT_TXF)
DECL|macro|IEVENT_ERR_MASK
mdefine_line|#define IEVENT_ERR_MASK         &bslash;&n;(IEVENT_RXC | IEVENT_BSY | IEVENT_EBERR | IEVENT_MSRO | &bslash;&n; IEVENT_BABT | IEVENT_TXC | IEVENT_TXE | IEVENT_LC &bslash;&n; | IEVENT_CRL | IEVENT_XFUN)
DECL|macro|IMASK_INIT_CLEAR
mdefine_line|#define IMASK_INIT_CLEAR&t;0x00000000
DECL|macro|IMASK_BABR
mdefine_line|#define IMASK_BABR              0x80000000
DECL|macro|IMASK_RXC
mdefine_line|#define IMASK_RXC               0x40000000
DECL|macro|IMASK_BSY
mdefine_line|#define IMASK_BSY               0x20000000
DECL|macro|IMASK_EBERR
mdefine_line|#define IMASK_EBERR             0x10000000
DECL|macro|IMASK_MSRO
mdefine_line|#define IMASK_MSRO&t;&t;0x04000000
DECL|macro|IMASK_GRSC
mdefine_line|#define IMASK_GRSC              0x02000000
DECL|macro|IMASK_BABT
mdefine_line|#define IMASK_BABT&t;&t;0x01000000
DECL|macro|IMASK_TXC
mdefine_line|#define IMASK_TXC               0x00800000
DECL|macro|IMASK_TXEEN
mdefine_line|#define IMASK_TXEEN&t;&t;0x00400000
DECL|macro|IMASK_TXBEN
mdefine_line|#define IMASK_TXBEN&t;&t;0x00200000
DECL|macro|IMASK_TXFEN
mdefine_line|#define IMASK_TXFEN             0x00100000
DECL|macro|IMASK_LC
mdefine_line|#define IMASK_LC&t;&t;0x00040000
DECL|macro|IMASK_CRL
mdefine_line|#define IMASK_CRL&t;&t;0x00020000
DECL|macro|IMASK_XFUN
mdefine_line|#define IMASK_XFUN&t;&t;0x00010000
DECL|macro|IMASK_RXB0
mdefine_line|#define IMASK_RXB0              0x00008000
DECL|macro|IMASK_GTSC
mdefine_line|#define IMASK_GTSC              0x00000100
DECL|macro|IMASK_RXFEN0
mdefine_line|#define IMASK_RXFEN0&t;&t;0x00000080
DECL|macro|IMASK_RX_DISABLED
mdefine_line|#define IMASK_RX_DISABLED ~(IMASK_RXFEN0 | IMASK_BSY)
DECL|macro|IMASK_DEFAULT
mdefine_line|#define IMASK_DEFAULT  (IMASK_TXEEN | IMASK_TXFEN | IMASK_TXBEN | &bslash;&n;&t;&t;IMASK_RXFEN0 | IMASK_BSY | IMASK_EBERR | IMASK_BABR | &bslash;&n;&t;&t;IMASK_XFUN | IMASK_RXC | IMASK_BABT)
multiline_comment|/* Attribute fields */
multiline_comment|/* This enables rx snooping for buffers and descriptors */
macro_line|#ifdef CONFIG_GFAR_BDSTASH
DECL|macro|ATTR_BDSTASH
mdefine_line|#define ATTR_BDSTASH&t;&t;0x00000800
macro_line|#else
DECL|macro|ATTR_BDSTASH
mdefine_line|#define ATTR_BDSTASH&t;&t;0x00000000
macro_line|#endif
macro_line|#ifdef CONFIG_GFAR_BUFSTASH
DECL|macro|ATTR_BUFSTASH
mdefine_line|#define ATTR_BUFSTASH&t;&t;0x00004000
DECL|macro|STASH_LENGTH
mdefine_line|#define STASH_LENGTH&t;&t;64
macro_line|#else
DECL|macro|ATTR_BUFSTASH
mdefine_line|#define ATTR_BUFSTASH&t;&t;0x00000000
macro_line|#endif
DECL|macro|ATTR_SNOOPING
mdefine_line|#define ATTR_SNOOPING&t;&t;0x000000c0
DECL|macro|ATTR_INIT_SETTINGS
mdefine_line|#define ATTR_INIT_SETTINGS      (ATTR_SNOOPING &bslash;&n;&t;&t;| ATTR_BDSTASH | ATTR_BUFSTASH)
DECL|macro|ATTRELI_INIT_SETTINGS
mdefine_line|#define ATTRELI_INIT_SETTINGS   0x0
multiline_comment|/* TxBD status field bits */
DECL|macro|TXBD_READY
mdefine_line|#define TXBD_READY&t;&t;0x8000
DECL|macro|TXBD_PADCRC
mdefine_line|#define TXBD_PADCRC&t;&t;0x4000
DECL|macro|TXBD_WRAP
mdefine_line|#define TXBD_WRAP&t;&t;0x2000
DECL|macro|TXBD_INTERRUPT
mdefine_line|#define TXBD_INTERRUPT&t;&t;0x1000
DECL|macro|TXBD_LAST
mdefine_line|#define TXBD_LAST&t;&t;0x0800
DECL|macro|TXBD_CRC
mdefine_line|#define TXBD_CRC&t;&t;0x0400
DECL|macro|TXBD_DEF
mdefine_line|#define TXBD_DEF&t;&t;0x0200
DECL|macro|TXBD_HUGEFRAME
mdefine_line|#define TXBD_HUGEFRAME&t;&t;0x0080
DECL|macro|TXBD_LATECOLLISION
mdefine_line|#define TXBD_LATECOLLISION&t;0x0080
DECL|macro|TXBD_RETRYLIMIT
mdefine_line|#define TXBD_RETRYLIMIT&t;&t;0x0040
DECL|macro|TXBD_RETRYCOUNTMASK
mdefine_line|#define&t;TXBD_RETRYCOUNTMASK&t;0x003c
DECL|macro|TXBD_UNDERRUN
mdefine_line|#define TXBD_UNDERRUN&t;&t;0x0002
multiline_comment|/* RxBD status field bits */
DECL|macro|RXBD_EMPTY
mdefine_line|#define RXBD_EMPTY&t;&t;0x8000
DECL|macro|RXBD_RO1
mdefine_line|#define RXBD_RO1&t;&t;0x4000
DECL|macro|RXBD_WRAP
mdefine_line|#define RXBD_WRAP&t;&t;0x2000
DECL|macro|RXBD_INTERRUPT
mdefine_line|#define RXBD_INTERRUPT&t;&t;0x1000
DECL|macro|RXBD_LAST
mdefine_line|#define RXBD_LAST&t;&t;0x0800
DECL|macro|RXBD_FIRST
mdefine_line|#define RXBD_FIRST&t;&t;0x0400
DECL|macro|RXBD_MISS
mdefine_line|#define RXBD_MISS&t;&t;0x0100
DECL|macro|RXBD_BROADCAST
mdefine_line|#define RXBD_BROADCAST&t;&t;0x0080
DECL|macro|RXBD_MULTICAST
mdefine_line|#define RXBD_MULTICAST&t;&t;0x0040
DECL|macro|RXBD_LARGE
mdefine_line|#define RXBD_LARGE&t;&t;0x0020
DECL|macro|RXBD_NONOCTET
mdefine_line|#define RXBD_NONOCTET&t;&t;0x0010
DECL|macro|RXBD_SHORT
mdefine_line|#define RXBD_SHORT&t;&t;0x0008
DECL|macro|RXBD_CRCERR
mdefine_line|#define RXBD_CRCERR&t;&t;0x0004
DECL|macro|RXBD_OVERRUN
mdefine_line|#define RXBD_OVERRUN&t;&t;0x0002
DECL|macro|RXBD_TRUNCATED
mdefine_line|#define RXBD_TRUNCATED&t;&t;0x0001
DECL|macro|RXBD_STATS
mdefine_line|#define RXBD_STATS&t;&t;0x01ff
DECL|struct|txbd8
r_struct
id|txbd8
(brace
DECL|member|status
id|u16
id|status
suffix:semicolon
multiline_comment|/* Status Fields */
DECL|member|length
id|u16
id|length
suffix:semicolon
multiline_comment|/* Buffer length */
DECL|member|bufPtr
id|u32
id|bufPtr
suffix:semicolon
multiline_comment|/* Buffer Pointer */
)brace
suffix:semicolon
DECL|struct|rxbd8
r_struct
id|rxbd8
(brace
DECL|member|status
id|u16
id|status
suffix:semicolon
multiline_comment|/* Status Fields */
DECL|member|length
id|u16
id|length
suffix:semicolon
multiline_comment|/* Buffer Length */
DECL|member|bufPtr
id|u32
id|bufPtr
suffix:semicolon
multiline_comment|/* Buffer Pointer */
)brace
suffix:semicolon
DECL|struct|rmon_mib
r_struct
id|rmon_mib
(brace
DECL|member|tr64
id|u32
id|tr64
suffix:semicolon
multiline_comment|/* 0x.680 - Transmit and Receive 64-byte Frame Counter */
DECL|member|tr127
id|u32
id|tr127
suffix:semicolon
multiline_comment|/* 0x.684 - Transmit and Receive 65-127 byte Frame Counter */
DECL|member|tr255
id|u32
id|tr255
suffix:semicolon
multiline_comment|/* 0x.688 - Transmit and Receive 128-255 byte Frame Counter */
DECL|member|tr511
id|u32
id|tr511
suffix:semicolon
multiline_comment|/* 0x.68c - Transmit and Receive 256-511 byte Frame Counter */
DECL|member|tr1k
id|u32
id|tr1k
suffix:semicolon
multiline_comment|/* 0x.690 - Transmit and Receive 512-1023 byte Frame Counter */
DECL|member|trmax
id|u32
id|trmax
suffix:semicolon
multiline_comment|/* 0x.694 - Transmit and Receive 1024-1518 byte Frame Counter */
DECL|member|trmgv
id|u32
id|trmgv
suffix:semicolon
multiline_comment|/* 0x.698 - Transmit and Receive 1519-1522 byte Good VLAN Frame */
DECL|member|rbyt
id|u32
id|rbyt
suffix:semicolon
multiline_comment|/* 0x.69c - Receive Byte Counter */
DECL|member|rpkt
id|u32
id|rpkt
suffix:semicolon
multiline_comment|/* 0x.6a0 - Receive Packet Counter */
DECL|member|rfcs
id|u32
id|rfcs
suffix:semicolon
multiline_comment|/* 0x.6a4 - Receive FCS Error Counter */
DECL|member|rmca
id|u32
id|rmca
suffix:semicolon
multiline_comment|/* 0x.6a8 - Receive Multicast Packet Counter */
DECL|member|rbca
id|u32
id|rbca
suffix:semicolon
multiline_comment|/* 0x.6ac - Receive Broadcast Packet Counter */
DECL|member|rxcf
id|u32
id|rxcf
suffix:semicolon
multiline_comment|/* 0x.6b0 - Receive Control Frame Packet Counter */
DECL|member|rxpf
id|u32
id|rxpf
suffix:semicolon
multiline_comment|/* 0x.6b4 - Receive Pause Frame Packet Counter */
DECL|member|rxuo
id|u32
id|rxuo
suffix:semicolon
multiline_comment|/* 0x.6b8 - Receive Unknown OP Code Counter */
DECL|member|raln
id|u32
id|raln
suffix:semicolon
multiline_comment|/* 0x.6bc - Receive Alignment Error Counter */
DECL|member|rflr
id|u32
id|rflr
suffix:semicolon
multiline_comment|/* 0x.6c0 - Receive Frame Length Error Counter */
DECL|member|rcde
id|u32
id|rcde
suffix:semicolon
multiline_comment|/* 0x.6c4 - Receive Code Error Counter */
DECL|member|rcse
id|u32
id|rcse
suffix:semicolon
multiline_comment|/* 0x.6c8 - Receive Carrier Sense Error Counter */
DECL|member|rund
id|u32
id|rund
suffix:semicolon
multiline_comment|/* 0x.6cc - Receive Undersize Packet Counter */
DECL|member|rovr
id|u32
id|rovr
suffix:semicolon
multiline_comment|/* 0x.6d0 - Receive Oversize Packet Counter */
DECL|member|rfrg
id|u32
id|rfrg
suffix:semicolon
multiline_comment|/* 0x.6d4 - Receive Fragments Counter */
DECL|member|rjbr
id|u32
id|rjbr
suffix:semicolon
multiline_comment|/* 0x.6d8 - Receive Jabber Counter */
DECL|member|rdrp
id|u32
id|rdrp
suffix:semicolon
multiline_comment|/* 0x.6dc - Receive Drop Counter */
DECL|member|tbyt
id|u32
id|tbyt
suffix:semicolon
multiline_comment|/* 0x.6e0 - Transmit Byte Counter Counter */
DECL|member|tpkt
id|u32
id|tpkt
suffix:semicolon
multiline_comment|/* 0x.6e4 - Transmit Packet Counter */
DECL|member|tmca
id|u32
id|tmca
suffix:semicolon
multiline_comment|/* 0x.6e8 - Transmit Multicast Packet Counter */
DECL|member|tbca
id|u32
id|tbca
suffix:semicolon
multiline_comment|/* 0x.6ec - Transmit Broadcast Packet Counter */
DECL|member|txpf
id|u32
id|txpf
suffix:semicolon
multiline_comment|/* 0x.6f0 - Transmit Pause Control Frame Counter */
DECL|member|tdfr
id|u32
id|tdfr
suffix:semicolon
multiline_comment|/* 0x.6f4 - Transmit Deferral Packet Counter */
DECL|member|tedf
id|u32
id|tedf
suffix:semicolon
multiline_comment|/* 0x.6f8 - Transmit Excessive Deferral Packet Counter */
DECL|member|tscl
id|u32
id|tscl
suffix:semicolon
multiline_comment|/* 0x.6fc - Transmit Single Collision Packet Counter */
DECL|member|tmcl
id|u32
id|tmcl
suffix:semicolon
multiline_comment|/* 0x.700 - Transmit Multiple Collision Packet Counter */
DECL|member|tlcl
id|u32
id|tlcl
suffix:semicolon
multiline_comment|/* 0x.704 - Transmit Late Collision Packet Counter */
DECL|member|txcl
id|u32
id|txcl
suffix:semicolon
multiline_comment|/* 0x.708 - Transmit Excessive Collision Packet Counter */
DECL|member|tncl
id|u32
id|tncl
suffix:semicolon
multiline_comment|/* 0x.70c - Transmit Total Collision Counter */
DECL|member|res1
id|u8
id|res1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|tdrp
id|u32
id|tdrp
suffix:semicolon
multiline_comment|/* 0x.714 - Transmit Drop Frame Counter */
DECL|member|tjbr
id|u32
id|tjbr
suffix:semicolon
multiline_comment|/* 0x.718 - Transmit Jabber Frame Counter */
DECL|member|tfcs
id|u32
id|tfcs
suffix:semicolon
multiline_comment|/* 0x.71c - Transmit FCS Error Counter */
DECL|member|txcf
id|u32
id|txcf
suffix:semicolon
multiline_comment|/* 0x.720 - Transmit Control Frame Counter */
DECL|member|tovr
id|u32
id|tovr
suffix:semicolon
multiline_comment|/* 0x.724 - Transmit Oversize Frame Counter */
DECL|member|tund
id|u32
id|tund
suffix:semicolon
multiline_comment|/* 0x.728 - Transmit Undersize Frame Counter */
DECL|member|tfrg
id|u32
id|tfrg
suffix:semicolon
multiline_comment|/* 0x.72c - Transmit Fragments Frame Counter */
DECL|member|car1
id|u32
id|car1
suffix:semicolon
multiline_comment|/* 0x.730 - Carry Register One */
DECL|member|car2
id|u32
id|car2
suffix:semicolon
multiline_comment|/* 0x.734 - Carry Register Two */
DECL|member|cam1
id|u32
id|cam1
suffix:semicolon
multiline_comment|/* 0x.738 - Carry Mask Register One */
DECL|member|cam2
id|u32
id|cam2
suffix:semicolon
multiline_comment|/* 0x.73c - Carry Mask Register Two */
)brace
suffix:semicolon
DECL|struct|gfar_extra_stats
r_struct
id|gfar_extra_stats
(brace
DECL|member|kernel_dropped
id|u64
id|kernel_dropped
suffix:semicolon
DECL|member|rx_large
id|u64
id|rx_large
suffix:semicolon
DECL|member|rx_short
id|u64
id|rx_short
suffix:semicolon
DECL|member|rx_nonoctet
id|u64
id|rx_nonoctet
suffix:semicolon
DECL|member|rx_crcerr
id|u64
id|rx_crcerr
suffix:semicolon
DECL|member|rx_overrun
id|u64
id|rx_overrun
suffix:semicolon
DECL|member|rx_bsy
id|u64
id|rx_bsy
suffix:semicolon
DECL|member|rx_babr
id|u64
id|rx_babr
suffix:semicolon
DECL|member|rx_trunc
id|u64
id|rx_trunc
suffix:semicolon
DECL|member|eberr
id|u64
id|eberr
suffix:semicolon
DECL|member|tx_babt
id|u64
id|tx_babt
suffix:semicolon
DECL|member|tx_underrun
id|u64
id|tx_underrun
suffix:semicolon
DECL|member|rx_skbmissing
id|u64
id|rx_skbmissing
suffix:semicolon
DECL|member|tx_timeout
id|u64
id|tx_timeout
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GFAR_RMON_LEN
mdefine_line|#define GFAR_RMON_LEN ((sizeof(struct rmon_mib) - 16)/sizeof(u32))
DECL|macro|GFAR_EXTRA_STATS_LEN
mdefine_line|#define GFAR_EXTRA_STATS_LEN (sizeof(struct gfar_extra_stats)/sizeof(u64))
multiline_comment|/* Number of stats in the stats structure (ignore car and cam regs)*/
DECL|macro|GFAR_STATS_LEN
mdefine_line|#define GFAR_STATS_LEN (GFAR_RMON_LEN + GFAR_EXTRA_STATS_LEN)
DECL|macro|GFAR_INFOSTR_LEN
mdefine_line|#define GFAR_INFOSTR_LEN 32
DECL|struct|gfar_stats
r_struct
id|gfar_stats
(brace
DECL|member|extra
id|u64
id|extra
(braket
id|GFAR_EXTRA_STATS_LEN
)braket
suffix:semicolon
DECL|member|rmon
id|u64
id|rmon
(braket
id|GFAR_RMON_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gfar
r_struct
id|gfar
(brace
DECL|member|res1
id|u8
id|res1
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ievent
id|u32
id|ievent
suffix:semicolon
multiline_comment|/* 0x.010 - Interrupt Event Register */
DECL|member|imask
id|u32
id|imask
suffix:semicolon
multiline_comment|/* 0x.014 - Interrupt Mask Register */
DECL|member|edis
id|u32
id|edis
suffix:semicolon
multiline_comment|/* 0x.018 - Error Disabled Register */
DECL|member|res2
id|u8
id|res2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ecntrl
id|u32
id|ecntrl
suffix:semicolon
multiline_comment|/* 0x.020 - Ethernet Control Register */
DECL|member|minflr
id|u32
id|minflr
suffix:semicolon
multiline_comment|/* 0x.024 - Minimum Frame Length Register */
DECL|member|ptv
id|u32
id|ptv
suffix:semicolon
multiline_comment|/* 0x.028 - Pause Time Value Register */
DECL|member|dmactrl
id|u32
id|dmactrl
suffix:semicolon
multiline_comment|/* 0x.02c - DMA Control Register */
DECL|member|tbipa
id|u32
id|tbipa
suffix:semicolon
multiline_comment|/* 0x.030 - TBI PHY Address Register */
DECL|member|res3
id|u8
id|res3
(braket
l_int|88
)braket
suffix:semicolon
DECL|member|fifo_tx_thr
id|u32
id|fifo_tx_thr
suffix:semicolon
multiline_comment|/* 0x.08c - FIFO transmit threshold register */
DECL|member|res4
id|u8
id|res4
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fifo_tx_starve
id|u32
id|fifo_tx_starve
suffix:semicolon
multiline_comment|/* 0x.098 - FIFO transmit starve register */
DECL|member|fifo_tx_starve_shutoff
id|u32
id|fifo_tx_starve_shutoff
suffix:semicolon
multiline_comment|/* 0x.09c - FIFO transmit starve shutoff register */
DECL|member|res5
id|u8
id|res5
(braket
l_int|96
)braket
suffix:semicolon
DECL|member|tctrl
id|u32
id|tctrl
suffix:semicolon
multiline_comment|/* 0x.100 - Transmit Control Register */
DECL|member|tstat
id|u32
id|tstat
suffix:semicolon
multiline_comment|/* 0x.104 - Transmit Status Register */
DECL|member|res6
id|u8
id|res6
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|tbdlen
id|u32
id|tbdlen
suffix:semicolon
multiline_comment|/* 0x.10c - Transmit Buffer Descriptor Data Length Register */
DECL|member|txic
id|u32
id|txic
suffix:semicolon
multiline_comment|/* 0x.110 - Transmit Interrupt Coalescing Configuration Register */
DECL|member|res7
id|u8
id|res7
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ctbptr
id|u32
id|ctbptr
suffix:semicolon
multiline_comment|/* 0x.124 - Current Transmit Buffer Descriptor Pointer Register */
DECL|member|res8
id|u8
id|res8
(braket
l_int|92
)braket
suffix:semicolon
DECL|member|tbptr
id|u32
id|tbptr
suffix:semicolon
multiline_comment|/* 0x.184 - Transmit Buffer Descriptor Pointer Low Register */
DECL|member|res9
id|u8
id|res9
(braket
l_int|124
)braket
suffix:semicolon
DECL|member|tbase
id|u32
id|tbase
suffix:semicolon
multiline_comment|/* 0x.204 - Transmit Descriptor Base Address Register */
DECL|member|res10
id|u8
id|res10
(braket
l_int|168
)braket
suffix:semicolon
DECL|member|ostbd
id|u32
id|ostbd
suffix:semicolon
multiline_comment|/* 0x.2b0 - Out-of-Sequence Transmit Buffer Descriptor Register */
DECL|member|ostbdp
id|u32
id|ostbdp
suffix:semicolon
multiline_comment|/* 0x.2b4 - Out-of-Sequence Transmit Data Buffer Pointer Register */
DECL|member|res11
id|u8
id|res11
(braket
l_int|72
)braket
suffix:semicolon
DECL|member|rctrl
id|u32
id|rctrl
suffix:semicolon
multiline_comment|/* 0x.300 - Receive Control Register */
DECL|member|rstat
id|u32
id|rstat
suffix:semicolon
multiline_comment|/* 0x.304 - Receive Status Register */
DECL|member|res12
id|u8
id|res12
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rbdlen
id|u32
id|rbdlen
suffix:semicolon
multiline_comment|/* 0x.30c - RxBD Data Length Register */
DECL|member|rxic
id|u32
id|rxic
suffix:semicolon
multiline_comment|/* 0x.310 - Receive Interrupt Coalescing Configuration Register */
DECL|member|res13
id|u8
id|res13
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|crbptr
id|u32
id|crbptr
suffix:semicolon
multiline_comment|/* 0x.324 - Current Receive Buffer Descriptor Pointer */
DECL|member|res14
id|u8
id|res14
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|mrblr
id|u32
id|mrblr
suffix:semicolon
multiline_comment|/* 0x.340 - Maximum Receive Buffer Length Register */
DECL|member|res15
id|u8
id|res15
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|rbptr
id|u32
id|rbptr
suffix:semicolon
multiline_comment|/* 0x.384 - Receive Buffer Descriptor Pointer */
DECL|member|res16
id|u8
id|res16
(braket
l_int|124
)braket
suffix:semicolon
DECL|member|rbase
id|u32
id|rbase
suffix:semicolon
multiline_comment|/* 0x.404 - Receive Descriptor Base Address */
DECL|member|res17
id|u8
id|res17
(braket
l_int|248
)braket
suffix:semicolon
DECL|member|maccfg1
id|u32
id|maccfg1
suffix:semicolon
multiline_comment|/* 0x.500 - MAC Configuration 1 Register */
DECL|member|maccfg2
id|u32
id|maccfg2
suffix:semicolon
multiline_comment|/* 0x.504 - MAC Configuration 2 Register */
DECL|member|ipgifg
id|u32
id|ipgifg
suffix:semicolon
multiline_comment|/* 0x.508 - Inter Packet Gap/Inter Frame Gap Register */
DECL|member|hafdup
id|u32
id|hafdup
suffix:semicolon
multiline_comment|/* 0x.50c - Half Duplex Register */
DECL|member|maxfrm
id|u32
id|maxfrm
suffix:semicolon
multiline_comment|/* 0x.510 - Maximum Frame Length Register */
DECL|member|res18
id|u8
id|res18
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|miimcfg
id|u32
id|miimcfg
suffix:semicolon
multiline_comment|/* 0x.520 - MII Management Configuration Register */
DECL|member|miimcom
id|u32
id|miimcom
suffix:semicolon
multiline_comment|/* 0x.524 - MII Management Command Register */
DECL|member|miimadd
id|u32
id|miimadd
suffix:semicolon
multiline_comment|/* 0x.528 - MII Management Address Register */
DECL|member|miimcon
id|u32
id|miimcon
suffix:semicolon
multiline_comment|/* 0x.52c - MII Management Control Register */
DECL|member|miimstat
id|u32
id|miimstat
suffix:semicolon
multiline_comment|/* 0x.530 - MII Management Status Register */
DECL|member|miimind
id|u32
id|miimind
suffix:semicolon
multiline_comment|/* 0x.534 - MII Management Indicator Register */
DECL|member|res19
id|u8
id|res19
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ifstat
id|u32
id|ifstat
suffix:semicolon
multiline_comment|/* 0x.53c - Interface Status Register */
DECL|member|macstnaddr1
id|u32
id|macstnaddr1
suffix:semicolon
multiline_comment|/* 0x.540 - Station Address Part 1 Register */
DECL|member|macstnaddr2
id|u32
id|macstnaddr2
suffix:semicolon
multiline_comment|/* 0x.544 - Station Address Part 2 Register */
DECL|member|res20
id|u8
id|res20
(braket
l_int|312
)braket
suffix:semicolon
DECL|member|rmon
r_struct
id|rmon_mib
id|rmon
suffix:semicolon
DECL|member|res21
id|u8
id|res21
(braket
l_int|192
)braket
suffix:semicolon
DECL|member|iaddr0
id|u32
id|iaddr0
suffix:semicolon
multiline_comment|/* 0x.800 - Indivdual address register 0 */
DECL|member|iaddr1
id|u32
id|iaddr1
suffix:semicolon
multiline_comment|/* 0x.804 - Indivdual address register 1 */
DECL|member|iaddr2
id|u32
id|iaddr2
suffix:semicolon
multiline_comment|/* 0x.808 - Indivdual address register 2 */
DECL|member|iaddr3
id|u32
id|iaddr3
suffix:semicolon
multiline_comment|/* 0x.80c - Indivdual address register 3 */
DECL|member|iaddr4
id|u32
id|iaddr4
suffix:semicolon
multiline_comment|/* 0x.810 - Indivdual address register 4 */
DECL|member|iaddr5
id|u32
id|iaddr5
suffix:semicolon
multiline_comment|/* 0x.814 - Indivdual address register 5 */
DECL|member|iaddr6
id|u32
id|iaddr6
suffix:semicolon
multiline_comment|/* 0x.818 - Indivdual address register 6 */
DECL|member|iaddr7
id|u32
id|iaddr7
suffix:semicolon
multiline_comment|/* 0x.81c - Indivdual address register 7 */
DECL|member|res22
id|u8
id|res22
(braket
l_int|96
)braket
suffix:semicolon
DECL|member|gaddr0
id|u32
id|gaddr0
suffix:semicolon
multiline_comment|/* 0x.880 - Global address register 0 */
DECL|member|gaddr1
id|u32
id|gaddr1
suffix:semicolon
multiline_comment|/* 0x.884 - Global address register 1 */
DECL|member|gaddr2
id|u32
id|gaddr2
suffix:semicolon
multiline_comment|/* 0x.888 - Global address register 2 */
DECL|member|gaddr3
id|u32
id|gaddr3
suffix:semicolon
multiline_comment|/* 0x.88c - Global address register 3 */
DECL|member|gaddr4
id|u32
id|gaddr4
suffix:semicolon
multiline_comment|/* 0x.890 - Global address register 4 */
DECL|member|gaddr5
id|u32
id|gaddr5
suffix:semicolon
multiline_comment|/* 0x.894 - Global address register 5 */
DECL|member|gaddr6
id|u32
id|gaddr6
suffix:semicolon
multiline_comment|/* 0x.898 - Global address register 6 */
DECL|member|gaddr7
id|u32
id|gaddr7
suffix:semicolon
multiline_comment|/* 0x.89c - Global address register 7 */
DECL|member|res23
id|u8
id|res23
(braket
l_int|856
)braket
suffix:semicolon
DECL|member|attr
id|u32
id|attr
suffix:semicolon
multiline_comment|/* 0x.bf8 - Attributes Register */
DECL|member|attreli
id|u32
id|attreli
suffix:semicolon
multiline_comment|/* 0x.bfc - Attributes Extract Length and Extract Index Register */
DECL|member|res24
id|u8
id|res24
(braket
l_int|1024
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Struct stolen almost completely (and shamelessly) from the FCC enet source&n; * (Ok, that&squot;s not so true anymore, but there is a family resemblence)&n; * The GFAR buffer descriptors track the ring buffers.  The rx_bd_base&n; * and tx_bd_base always point to the currently available buffer.&n; * The dirty_tx tracks the current buffer that is being sent by the&n; * controller.  The cur_tx and dirty_tx are equal under both completely&n; * empty and completely full conditions.  The empty/ready indicator in&n; * the buffer descriptor determines the actual condition.&n; */
DECL|struct|gfar_private
r_struct
id|gfar_private
(brace
multiline_comment|/* pointers to arrays of skbuffs for tx and rx */
DECL|member|tx_skbuff
r_struct
id|sk_buff
op_star
op_star
id|tx_skbuff
suffix:semicolon
DECL|member|rx_skbuff
r_struct
id|sk_buff
op_star
op_star
id|rx_skbuff
suffix:semicolon
multiline_comment|/* indices pointing to the next free sbk in skb arrays */
DECL|member|skb_curtx
id|u16
id|skb_curtx
suffix:semicolon
DECL|member|skb_currx
id|u16
id|skb_currx
suffix:semicolon
multiline_comment|/* index of the first skb which hasn&squot;t been transmitted&n;&t; * yet. */
DECL|member|skb_dirtytx
id|u16
id|skb_dirtytx
suffix:semicolon
multiline_comment|/* Configuration info for the coalescing features */
DECL|member|txcoalescing
r_int
r_char
id|txcoalescing
suffix:semicolon
DECL|member|txcount
r_int
r_int
id|txcount
suffix:semicolon
DECL|member|txtime
r_int
r_int
id|txtime
suffix:semicolon
DECL|member|rxcoalescing
r_int
r_char
id|rxcoalescing
suffix:semicolon
DECL|member|rxcount
r_int
r_int
id|rxcount
suffix:semicolon
DECL|member|rxtime
r_int
r_int
id|rxtime
suffix:semicolon
multiline_comment|/* GFAR addresses */
DECL|member|rx_bd_base
r_struct
id|rxbd8
op_star
id|rx_bd_base
suffix:semicolon
multiline_comment|/* Base addresses of Rx and Tx Buffers */
DECL|member|tx_bd_base
r_struct
id|txbd8
op_star
id|tx_bd_base
suffix:semicolon
DECL|member|cur_rx
r_struct
id|rxbd8
op_star
id|cur_rx
suffix:semicolon
multiline_comment|/* Next free rx ring entry */
DECL|member|cur_tx
r_struct
id|txbd8
op_star
id|cur_tx
suffix:semicolon
multiline_comment|/* Next free ring entry */
DECL|member|dirty_tx
r_struct
id|txbd8
op_star
id|dirty_tx
suffix:semicolon
multiline_comment|/* The Ring entry to be freed. */
DECL|member|regs
r_struct
id|gfar
op_star
id|regs
suffix:semicolon
multiline_comment|/* Pointer to the GFAR memory mapped Registers */
DECL|member|phyregs
r_struct
id|gfar
op_star
id|phyregs
suffix:semicolon
DECL|member|tq
r_struct
id|work_struct
id|tq
suffix:semicolon
DECL|member|phy_info_timer
r_struct
id|timer_list
id|phy_info_timer
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* linux network statistics */
DECL|member|extra_stats
r_struct
id|gfar_extra_stats
id|extra_stats
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|rx_buffer_size
r_int
r_int
id|rx_buffer_size
suffix:semicolon
DECL|member|rx_stash_size
r_int
r_int
id|rx_stash_size
suffix:semicolon
DECL|member|tx_ring_size
r_int
r_int
id|tx_ring_size
suffix:semicolon
DECL|member|rx_ring_size
r_int
r_int
id|rx_ring_size
suffix:semicolon
DECL|member|rxcleanupq
id|wait_queue_head_t
id|rxcleanupq
suffix:semicolon
DECL|member|rxclean
r_int
r_int
id|rxclean
suffix:semicolon
multiline_comment|/* Info structure initialized by board setup code */
DECL|member|interruptTransmit
r_int
r_int
id|interruptTransmit
suffix:semicolon
DECL|member|interruptReceive
r_int
r_int
id|interruptReceive
suffix:semicolon
DECL|member|interruptError
r_int
r_int
id|interruptError
suffix:semicolon
DECL|member|einfo
r_struct
id|gianfar_platform_data
op_star
id|einfo
suffix:semicolon
DECL|member|mii_info
r_struct
id|gfar_mii_info
op_star
id|mii_info
suffix:semicolon
DECL|member|oldspeed
r_int
id|oldspeed
suffix:semicolon
DECL|member|oldduplex
r_int
id|oldduplex
suffix:semicolon
DECL|member|oldlink
r_int
id|oldlink
suffix:semicolon
)brace
suffix:semicolon
DECL|function|gfar_read
r_extern
r_inline
id|u32
id|gfar_read
c_func
(paren
r_volatile
r_int
op_star
id|addr
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|in_be32
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|gfar_write
r_extern
r_inline
r_void
id|gfar_write
c_func
(paren
r_volatile
r_int
op_star
id|addr
comma
id|u32
id|val
)paren
(brace
id|out_be32
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|ethtool_ops
op_star
id|gfar_op_array
(braket
)braket
suffix:semicolon
macro_line|#endif /* __GIANFAR_H */
eof
