multiline_comment|/*********************************************************************&n; *                &n; * Filename:      toshoboe.h&n; * Version:       0.1&n; * Description:   Driver for the Toshiba OBOE (or type-O)&n; *                FIR Chipset. &n; * Status:        Experimental.&n; * Author:        James McKenzie &lt;james@fishsoup.dhs.org&gt;&n; * Created at:    Sat May 8  12:35:27 1999&n; * &n; *     Copyright (c) 1999-2000 James McKenzie, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither James McKenzie nor Cambridge University admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; *     Applicable Models : Libretto 100CT. and many more&n; *&n; ********************************************************************/
macro_line|#ifndef TOSHOBOE_H
DECL|macro|TOSHOBOE_H
mdefine_line|#define TOSHOBOE_H
multiline_comment|/* Registers */
multiline_comment|/*Receive and transmit task registers (read only) */
DECL|macro|OBOE_RCVT
mdefine_line|#define OBOE_RCVT&t;(0x00+(self-&gt;base))
DECL|macro|OBOE_XMTT
mdefine_line|#define OBOE_XMTT&t;(0x01+(self-&gt;base))
DECL|macro|OBOE_XMTT_OFFSET
mdefine_line|#define OBOE_XMTT_OFFSET&t;0x40
multiline_comment|/*Page pointers to the TaskFile structure */
DECL|macro|OBOE_TFP2
mdefine_line|#define OBOE_TFP2&t;(0x02+(self-&gt;base))
DECL|macro|OBOE_TFP0
mdefine_line|#define OBOE_TFP0&t;(0x04+(self-&gt;base))
DECL|macro|OBOE_TFP1
mdefine_line|#define OBOE_TFP1&t;(0x05+(self-&gt;base))
multiline_comment|/*Dunno */
DECL|macro|OBOE_REG_3
mdefine_line|#define OBOE_REG_3&t;(0x03+(self-&gt;base))
multiline_comment|/*Number of tasks to use in Xmit and Recv queues */
DECL|macro|OBOE_NTR
mdefine_line|#define OBOE_NTR&t;(0x07+(self-&gt;base))
DECL|macro|OBOE_NTR_XMIT4
mdefine_line|#define OBOE_NTR_XMIT4&t;0x00
DECL|macro|OBOE_NTR_XMIT8
mdefine_line|#define OBOE_NTR_XMIT8&t;0x10
DECL|macro|OBOE_NTR_XMIT16
mdefine_line|#define OBOE_NTR_XMIT16&t;0x30
DECL|macro|OBOE_NTR_XMIT32
mdefine_line|#define OBOE_NTR_XMIT32&t;0x70
DECL|macro|OBOE_NTR_XMIT64
mdefine_line|#define OBOE_NTR_XMIT64&t;0xf0
DECL|macro|OBOE_NTR_RECV4
mdefine_line|#define OBOE_NTR_RECV4&t;0x00
DECL|macro|OBOE_NTR_RECV8
mdefine_line|#define OBOE_NTR_RECV8&t;0x01
DECL|macro|OBOE_NTR_RECV6
mdefine_line|#define OBOE_NTR_RECV6&t;0x03
DECL|macro|OBOE_NTR_RECV32
mdefine_line|#define OBOE_NTR_RECV32&t;0x07
DECL|macro|OBOE_NTR_RECV64
mdefine_line|#define OBOE_NTR_RECV64&t;0x0f
multiline_comment|/* Dunno */
DECL|macro|OBOE_REG_9
mdefine_line|#define OBOE_REG_9&t;(0x09+(self-&gt;base))
multiline_comment|/* Interrupt Status Register */
DECL|macro|OBOE_ISR
mdefine_line|#define OBOE_ISR&t;(0x0c+(self-&gt;base))
DECL|macro|OBOE_ISR_TXDONE
mdefine_line|#define OBOE_ISR_TXDONE&t;0x80
DECL|macro|OBOE_ISR_RXDONE
mdefine_line|#define OBOE_ISR_RXDONE&t;0x40
DECL|macro|OBOE_ISR_20
mdefine_line|#define OBOE_ISR_20&t;0x20
DECL|macro|OBOE_ISR_10
mdefine_line|#define OBOE_ISR_10&t;0x10
DECL|macro|OBOE_ISR_8
mdefine_line|#define OBOE_ISR_8&t;0x08         /*This is collision or parity or something */
DECL|macro|OBOE_ISR_4
mdefine_line|#define OBOE_ISR_4&t;0x08
DECL|macro|OBOE_ISR_2
mdefine_line|#define OBOE_ISR_2&t;0x08
DECL|macro|OBOE_ISR_1
mdefine_line|#define OBOE_ISR_1&t;0x08
multiline_comment|/*Dunno */
DECL|macro|OBOE_REG_D
mdefine_line|#define OBOE_REG_D&t;(0x0d+(self-&gt;base))
multiline_comment|/*Register Lock Register */
DECL|macro|OBOE_LOCK
mdefine_line|#define OBOE_LOCK&t;((self-&gt;base)+0x0e)
multiline_comment|/*Speed control registers */
DECL|macro|OBOE_PMDL
mdefine_line|#define OBOE_PMDL&t;(0x10+(self-&gt;base))
DECL|macro|OBOE_PMDL_SIR
mdefine_line|#define OBOE_PMDL_SIR&t;0x18
DECL|macro|OBOE_PMDL_MIR
mdefine_line|#define OBOE_PMDL_MIR&t;0xa0
DECL|macro|OBOE_PMDL_FIR
mdefine_line|#define OBOE_PMDL_FIR&t;0x40
DECL|macro|OBOE_SMDL
mdefine_line|#define OBOE_SMDL&t;(0x18+(self-&gt;base))
DECL|macro|OBOE_SMDL_SIR
mdefine_line|#define OBOE_SMDL_SIR&t;0x20
DECL|macro|OBOE_SMDL_MIR
mdefine_line|#define OBOE_SMDL_MIR&t;0x01
DECL|macro|OBOE_SMDL_FIR
mdefine_line|#define OBOE_SMDL_FIR&t;0x0f
DECL|macro|OBOE_UDIV
mdefine_line|#define OBOE_UDIV&t;(0x19+(self-&gt;base))
multiline_comment|/*Dunno */
DECL|macro|OBOE_REG_11
mdefine_line|#define OBOE_REG_11&t;(0x11+(self-&gt;base))
multiline_comment|/*Chip Reset Register */
DECL|macro|OBOE_RST
mdefine_line|#define OBOE_RST&t;(0x15+(self-&gt;base))
DECL|macro|OBOE_RST_WRAP
mdefine_line|#define OBOE_RST_WRAP&t;0x8
multiline_comment|/*Dunno */
DECL|macro|OBOE_REG_1A
mdefine_line|#define OBOE_REG_1A&t;(0x1a+(self-&gt;base))
DECL|macro|OBOE_REG_1B
mdefine_line|#define OBOE_REG_1B&t;(0x1b+(self-&gt;base))
multiline_comment|/* The PCI ID of the OBOE chip */
macro_line|#ifndef PCI_DEVICE_ID_FIR701
DECL|macro|PCI_DEVICE_ID_FIR701
mdefine_line|#define PCI_DEVICE_ID_FIR701 &t;0x0701
macro_line|#endif
DECL|typedef|dword
r_typedef
r_int
r_int
id|dword
suffix:semicolon
DECL|typedef|word
r_typedef
r_int
r_int
r_int
id|word
suffix:semicolon
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
DECL|typedef|Paddr
r_typedef
id|dword
id|Paddr
suffix:semicolon
DECL|struct|OboeTask
r_struct
id|OboeTask
(brace
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OBOE_NTASKS
mdefine_line|#define OBOE_NTASKS 64
DECL|struct|OboeTaskFile
r_struct
id|OboeTaskFile
(brace
DECL|member|recv
r_struct
id|OboeTask
id|recv
(braket
id|OBOE_NTASKS
)braket
suffix:semicolon
DECL|member|xmit
r_struct
id|OboeTask
id|xmit
(braket
id|OBOE_NTASKS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OBOE_TASK_BUF_LEN
mdefine_line|#define OBOE_TASK_BUF_LEN (sizeof(struct OboeTaskFile) &lt;&lt; 1)
multiline_comment|/*These set the number of slots in use */
DECL|macro|TX_SLOTS
mdefine_line|#define TX_SLOTS&t;4
DECL|macro|RX_SLOTS
mdefine_line|#define RX_SLOTS&t;4
multiline_comment|/* You need also to change this, toshiba uses 4,8 and 4,4 */
multiline_comment|/* It makes no difference if you are only going to use ONETASK mode */
multiline_comment|/* remember each buffer use XX_BUF_SZ more _PHYSICAL_ memory */
DECL|macro|OBOE_NTR_VAL
mdefine_line|#define OBOE_NTR_VAL &t;(OBOE_NTR_XMIT4 | OBOE_NTR_RECV4)
DECL|struct|toshoboe_cb
r_struct
id|toshoboe_cb
(brace
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are binded to */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS capabilities for this device */
DECL|member|io
id|chipio_t
id|io
suffix:semicolon
multiline_comment|/* IrDA controller information */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/*PCI device */
DECL|member|base
r_int
id|base
suffix:semicolon
multiline_comment|/*IO base */
DECL|member|txpending
r_int
id|txpending
suffix:semicolon
multiline_comment|/*how many tx&squot;s are pending */
DECL|member|txs
DECL|member|rxs
r_int
id|txs
comma
id|rxs
suffix:semicolon
multiline_comment|/*Which slots are we at  */
DECL|member|taskfilebuf
r_void
op_star
id|taskfilebuf
suffix:semicolon
multiline_comment|/*The unaligned taskfile buffer */
DECL|member|taskfile
r_struct
id|OboeTaskFile
op_star
id|taskfile
suffix:semicolon
multiline_comment|/*The taskfile   */
DECL|member|xmit_bufs
r_void
op_star
id|xmit_bufs
(braket
id|TX_SLOTS
)braket
suffix:semicolon
multiline_comment|/*The buffers   */
DECL|member|recv_bufs
r_void
op_star
id|recv_bufs
(braket
id|RX_SLOTS
)braket
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|stopped
r_int
id|stopped
suffix:semicolon
multiline_comment|/*Stopped by some or other APM stuff*/
)brace
suffix:semicolon
macro_line|#endif
eof
