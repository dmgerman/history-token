multiline_comment|/*&n; * SDL Inc. RISCom/N2 synchronous serial card driver for Linux&n; *&n; * Copyright (C) 1998-2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; *&n; * For information see http://hq.pm.waw.pl/hdlc/&n; *&n; * Note: integrated CSU/DSU/DDS are not supported by this driver&n; *&n; * Sources of information:&n; *    Hitachi HD64570 SCA User&squot;s Manual&n; *    SDL Inc. PPP/HDLC/CISCO driver&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/hdlc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;hd64570.h&quot;
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;SDL RISCom/N2 driver version: 1.14&quot;
suffix:semicolon
DECL|variable|devname
r_static
r_const
r_char
op_star
id|devname
op_assign
l_string|&quot;RISCom/N2&quot;
suffix:semicolon
DECL|macro|USE_WINDOWSIZE
mdefine_line|#define USE_WINDOWSIZE 16384
DECL|macro|USE_BUS16BITS
mdefine_line|#define USE_BUS16BITS 1
DECL|macro|CLOCK_BASE
mdefine_line|#define CLOCK_BASE 9830400&t;/* 9.8304 MHz */
DECL|macro|MAX_PAGES
mdefine_line|#define MAX_PAGES      16&t;/* 16 RAM pages at max */
DECL|macro|MAX_RAM_SIZE
mdefine_line|#define MAX_RAM_SIZE 0x80000&t;/* 512 KB */
macro_line|#if MAX_RAM_SIZE &gt; MAX_PAGES * USE_WINDOWSIZE
DECL|macro|MAX_RAM_SIZE
macro_line|#undef MAX_RAM_SIZE
DECL|macro|MAX_RAM_SIZE
mdefine_line|#define MAX_RAM_SIZE (MAX_PAGES * USE_WINDOWSIZE)
macro_line|#endif
DECL|macro|N2_IOPORTS
mdefine_line|#define N2_IOPORTS 0x10
DECL|macro|NEED_DETECT_RAM
mdefine_line|#define NEED_DETECT_RAM
DECL|macro|MAX_TX_BUFFERS
mdefine_line|#define MAX_TX_BUFFERS 10
DECL|variable|hw
r_static
r_char
op_star
id|hw
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* pointer to hw=xxx command line string */
multiline_comment|/* RISCom/N2 Board Registers */
multiline_comment|/* PC Control Register */
DECL|macro|N2_PCR
mdefine_line|#define N2_PCR 0
DECL|macro|PCR_RUNSCA
mdefine_line|#define PCR_RUNSCA 1     /* Run 64570 */
DECL|macro|PCR_VPM
mdefine_line|#define PCR_VPM    2     /* Enable VPM - needed if using RAM above 1 MB */
DECL|macro|PCR_ENWIN
mdefine_line|#define PCR_ENWIN  4     /* Open window */
DECL|macro|PCR_BUS16
mdefine_line|#define PCR_BUS16  8     /* 16-bit bus */
multiline_comment|/* Memory Base Address Register */
DECL|macro|N2_BAR
mdefine_line|#define N2_BAR 2
multiline_comment|/* Page Scan Register  */
DECL|macro|N2_PSR
mdefine_line|#define N2_PSR 4
DECL|macro|WIN16K
mdefine_line|#define WIN16K       0x00
DECL|macro|WIN32K
mdefine_line|#define WIN32K       0x20
DECL|macro|WIN64K
mdefine_line|#define WIN64K       0x40
DECL|macro|PSR_WINBITS
mdefine_line|#define PSR_WINBITS  0x60
DECL|macro|PSR_DMAEN
mdefine_line|#define PSR_DMAEN    0x80
DECL|macro|PSR_PAGEBITS
mdefine_line|#define PSR_PAGEBITS 0x0F
multiline_comment|/* Modem Control Reg */
DECL|macro|N2_MCR
mdefine_line|#define N2_MCR 6
DECL|macro|CLOCK_OUT_PORT1
mdefine_line|#define CLOCK_OUT_PORT1 0x80
DECL|macro|CLOCK_OUT_PORT0
mdefine_line|#define CLOCK_OUT_PORT0 0x40
DECL|macro|TX422_PORT1
mdefine_line|#define TX422_PORT1     0x20
DECL|macro|TX422_PORT0
mdefine_line|#define TX422_PORT0     0x10
DECL|macro|DSR_PORT1
mdefine_line|#define DSR_PORT1       0x08
DECL|macro|DSR_PORT0
mdefine_line|#define DSR_PORT0       0x04
DECL|macro|DTR_PORT1
mdefine_line|#define DTR_PORT1       0x02
DECL|macro|DTR_PORT0
mdefine_line|#define DTR_PORT0       0x01
DECL|struct|port_s
r_typedef
r_struct
id|port_s
(brace
DECL|member|hdlc
id|hdlc_device
id|hdlc
suffix:semicolon
multiline_comment|/* HDLC device struct - must be first */
DECL|member|card
r_struct
id|card_s
op_star
id|card
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* TX lock */
DECL|member|settings
id|sync_serial_settings
id|settings
suffix:semicolon
DECL|member|valid
r_int
id|valid
suffix:semicolon
multiline_comment|/* port enabled */
DECL|member|rxpart
r_int
id|rxpart
suffix:semicolon
multiline_comment|/* partial frame received, next frame invalid*/
DECL|member|encoding
r_int
r_int
id|encoding
suffix:semicolon
DECL|member|parity
r_int
r_int
id|parity
suffix:semicolon
DECL|member|rxin
id|u16
id|rxin
suffix:semicolon
multiline_comment|/* rx ring buffer &squot;in&squot; pointer */
DECL|member|txin
id|u16
id|txin
suffix:semicolon
multiline_comment|/* tx ring buffer &squot;in&squot; and &squot;last&squot; pointers */
DECL|member|txlast
id|u16
id|txlast
suffix:semicolon
DECL|member|rxs
DECL|member|txs
DECL|member|tmc
id|u8
id|rxs
comma
id|txs
comma
id|tmc
suffix:semicolon
multiline_comment|/* SCA registers */
DECL|member|phy_node
id|u8
id|phy_node
suffix:semicolon
multiline_comment|/* physical port # - 0 or 1 */
DECL|member|log_node
id|u8
id|log_node
suffix:semicolon
multiline_comment|/* logical port # */
DECL|typedef|port_t
)brace
id|port_t
suffix:semicolon
DECL|struct|card_s
r_typedef
r_struct
id|card_s
(brace
DECL|member|winbase
id|u8
op_star
id|winbase
suffix:semicolon
multiline_comment|/* ISA window base address */
DECL|member|phy_winbase
id|u32
id|phy_winbase
suffix:semicolon
multiline_comment|/* ISA physical base address */
DECL|member|ram_size
id|u32
id|ram_size
suffix:semicolon
multiline_comment|/* number of bytes */
DECL|member|io
id|u16
id|io
suffix:semicolon
multiline_comment|/* IO Base address */
DECL|member|buff_offset
id|u16
id|buff_offset
suffix:semicolon
multiline_comment|/* offset of first buffer of first channel */
DECL|member|rx_ring_buffers
id|u16
id|rx_ring_buffers
suffix:semicolon
multiline_comment|/* number of buffers in a ring */
DECL|member|tx_ring_buffers
id|u16
id|tx_ring_buffers
suffix:semicolon
DECL|member|irq
id|u8
id|irq
suffix:semicolon
multiline_comment|/* IRQ (3-15) */
DECL|member|ports
id|port_t
id|ports
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|next_card
r_struct
id|card_s
op_star
id|next_card
suffix:semicolon
DECL|typedef|card_t
)brace
id|card_t
suffix:semicolon
DECL|variable|first_card
r_static
id|card_t
op_star
id|first_card
suffix:semicolon
DECL|variable|new_card
r_static
id|card_t
op_star
op_star
id|new_card
op_assign
op_amp
id|first_card
suffix:semicolon
DECL|macro|sca_reg
mdefine_line|#define sca_reg(reg, card) (0x8000 | (card)-&gt;io | &bslash;&n;&t;&t;&t;    ((reg) &amp; 0x0F) | (((reg) &amp; 0xF0) &lt;&lt; 6))
DECL|macro|sca_in
mdefine_line|#define sca_in(reg, card)&t;&t;inb(sca_reg(reg, card))
DECL|macro|sca_out
mdefine_line|#define sca_out(value, reg, card)&t;outb(value, sca_reg(reg, card))
DECL|macro|sca_inw
mdefine_line|#define sca_inw(reg, card)&t;&t;inw(sca_reg(reg, card))
DECL|macro|sca_outw
mdefine_line|#define sca_outw(value, reg, card)&t;outw(value, sca_reg(reg, card))
DECL|macro|port_to_card
mdefine_line|#define port_to_card(port)&t;&t;((port)-&gt;card)
DECL|macro|log_node
mdefine_line|#define log_node(port)&t;&t;&t;((port)-&gt;log_node)
DECL|macro|phy_node
mdefine_line|#define phy_node(port)&t;&t;&t;((port)-&gt;phy_node)
DECL|macro|winsize
mdefine_line|#define winsize(card)&t;&t;&t;(USE_WINDOWSIZE)
DECL|macro|winbase
mdefine_line|#define winbase(card)      &t;     &t;((card)-&gt;winbase)
DECL|macro|get_port
mdefine_line|#define get_port(card, port)&t;&t;((card)-&gt;ports[port].valid ? &bslash;&n;&t;&t;&t;&t;&t; &amp;(card)-&gt;ports[port] : NULL)
DECL|function|sca_get_page
r_static
id|__inline__
id|u8
id|sca_get_page
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
r_return
id|inb
c_func
(paren
id|card-&gt;io
op_plus
id|N2_PSR
)paren
op_amp
id|PSR_PAGEBITS
suffix:semicolon
)brace
DECL|function|openwin
r_static
id|__inline__
r_void
id|openwin
c_func
(paren
id|card_t
op_star
id|card
comma
id|u8
id|page
)paren
(brace
id|u8
id|psr
op_assign
id|inb
c_func
(paren
id|card-&gt;io
op_plus
id|N2_PSR
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|psr
op_amp
op_complement
id|PSR_PAGEBITS
)paren
op_or
id|page
comma
id|card-&gt;io
op_plus
id|N2_PSR
)paren
suffix:semicolon
)brace
DECL|function|close_windows
r_static
id|__inline__
r_void
id|close_windows
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|card-&gt;io
op_plus
id|N2_PCR
)paren
op_amp
op_complement
id|PCR_ENWIN
comma
id|card-&gt;io
op_plus
id|N2_PCR
)paren
suffix:semicolon
)brace
macro_line|#include &quot;hd6457x.c&quot;
DECL|function|n2_set_iface
r_static
r_void
id|n2_set_iface
c_func
(paren
id|port_t
op_star
id|port
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|port-&gt;card
suffix:semicolon
r_int
id|io
op_assign
id|card-&gt;io
suffix:semicolon
id|u8
id|mcr
op_assign
id|inb
c_func
(paren
id|io
op_plus
id|N2_MCR
)paren
suffix:semicolon
id|u8
id|msci
op_assign
id|get_msci
c_func
(paren
id|port
)paren
suffix:semicolon
id|u8
id|rxs
op_assign
id|port-&gt;rxs
op_amp
id|CLK_BRG_MASK
suffix:semicolon
id|u8
id|txs
op_assign
id|port-&gt;txs
op_amp
id|CLK_BRG_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|port-&gt;settings.clock_type
)paren
(brace
r_case
id|CLOCK_INT
suffix:colon
id|mcr
op_or_assign
id|port-&gt;phy_node
ques
c_cond
id|CLOCK_OUT_PORT1
suffix:colon
id|CLOCK_OUT_PORT0
suffix:semicolon
id|rxs
op_or_assign
id|CLK_BRG_RX
suffix:semicolon
multiline_comment|/* BRG output */
id|txs
op_or_assign
id|CLK_RXCLK_TX
suffix:semicolon
multiline_comment|/* RX clock */
r_break
suffix:semicolon
r_case
id|CLOCK_TXINT
suffix:colon
id|mcr
op_or_assign
id|port-&gt;phy_node
ques
c_cond
id|CLOCK_OUT_PORT1
suffix:colon
id|CLOCK_OUT_PORT0
suffix:semicolon
id|rxs
op_or_assign
id|CLK_LINE_RX
suffix:semicolon
multiline_comment|/* RXC input */
id|txs
op_or_assign
id|CLK_BRG_TX
suffix:semicolon
multiline_comment|/* BRG output */
r_break
suffix:semicolon
r_case
id|CLOCK_TXFROMRX
suffix:colon
id|mcr
op_or_assign
id|port-&gt;phy_node
ques
c_cond
id|CLOCK_OUT_PORT1
suffix:colon
id|CLOCK_OUT_PORT0
suffix:semicolon
id|rxs
op_or_assign
id|CLK_LINE_RX
suffix:semicolon
multiline_comment|/* RXC input */
id|txs
op_or_assign
id|CLK_RXCLK_TX
suffix:semicolon
multiline_comment|/* RX clock */
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Clock EXTernal */
id|mcr
op_and_assign
id|port-&gt;phy_node
ques
c_cond
op_complement
id|CLOCK_OUT_PORT1
suffix:colon
op_complement
id|CLOCK_OUT_PORT0
suffix:semicolon
id|rxs
op_or_assign
id|CLK_LINE_RX
suffix:semicolon
multiline_comment|/* RXC input */
id|txs
op_or_assign
id|CLK_LINE_TX
suffix:semicolon
multiline_comment|/* TXC input */
)brace
id|outb
c_func
(paren
id|mcr
comma
id|io
op_plus
id|N2_MCR
)paren
suffix:semicolon
id|port-&gt;rxs
op_assign
id|rxs
suffix:semicolon
id|port-&gt;txs
op_assign
id|txs
suffix:semicolon
id|sca_out
c_func
(paren
id|rxs
comma
id|msci
op_plus
id|RXS
comma
id|card
)paren
suffix:semicolon
id|sca_out
c_func
(paren
id|txs
comma
id|msci
op_plus
id|TXS
comma
id|card
)paren
suffix:semicolon
id|sca_set_port
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|n2_open
r_static
r_int
id|n2_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|port_t
op_star
id|port
op_assign
id|hdlc_to_port
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_int
id|io
op_assign
id|port-&gt;card-&gt;io
suffix:semicolon
id|u8
id|mcr
op_assign
id|inb
c_func
(paren
id|io
op_plus
id|N2_MCR
)paren
op_or
(paren
id|port-&gt;phy_node
ques
c_cond
id|TX422_PORT1
suffix:colon
id|TX422_PORT0
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
id|result
op_assign
id|hdlc_open
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|mcr
op_and_assign
id|port-&gt;phy_node
ques
c_cond
op_complement
id|DTR_PORT1
suffix:colon
op_complement
id|DTR_PORT0
suffix:semicolon
multiline_comment|/* set DTR ON */
id|outb
c_func
(paren
id|mcr
comma
id|io
op_plus
id|N2_MCR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|io
op_plus
id|N2_PCR
)paren
op_or
id|PCR_ENWIN
comma
id|io
op_plus
id|N2_PCR
)paren
suffix:semicolon
multiline_comment|/* open window */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|io
op_plus
id|N2_PSR
)paren
op_or
id|PSR_DMAEN
comma
id|io
op_plus
id|N2_PSR
)paren
suffix:semicolon
multiline_comment|/* enable dma */
id|sca_open
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|n2_set_iface
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|n2_close
r_static
r_int
id|n2_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|port_t
op_star
id|port
op_assign
id|hdlc_to_port
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_int
id|io
op_assign
id|port-&gt;card-&gt;io
suffix:semicolon
id|u8
id|mcr
op_assign
id|inb
c_func
(paren
id|io
op_plus
id|N2_MCR
)paren
op_or
(paren
id|port-&gt;phy_node
ques
c_cond
id|TX422_PORT1
suffix:colon
id|TX422_PORT0
)paren
suffix:semicolon
id|sca_close
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|mcr
op_or_assign
id|port-&gt;phy_node
ques
c_cond
id|DTR_PORT1
suffix:colon
id|DTR_PORT0
suffix:semicolon
multiline_comment|/* set DTR OFF */
id|outb
c_func
(paren
id|mcr
comma
id|io
op_plus
id|N2_MCR
)paren
suffix:semicolon
id|hdlc_close
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|n2_ioctl
r_static
r_int
id|n2_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
(brace
r_const
r_int
id|size
op_assign
r_sizeof
(paren
id|sync_serial_settings
)paren
suffix:semicolon
id|sync_serial_settings
id|new_line
comma
op_star
id|line
op_assign
id|ifr-&gt;ifr_settings.ifs_ifsu.sync
suffix:semicolon
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|port_t
op_star
id|port
op_assign
id|hdlc_to_port
c_func
(paren
id|hdlc
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HDLC_DEBUG_RINGS
r_if
c_cond
(paren
id|cmd
op_eq
id|SIOCDEVPRIVATE
)paren
(brace
id|sca_dump_rings
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCWANDEV
)paren
r_return
id|hdlc_ioctl
c_func
(paren
id|dev
comma
id|ifr
comma
id|cmd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ifr-&gt;ifr_settings.type
)paren
(brace
r_case
id|IF_GET_IFACE
suffix:colon
id|ifr-&gt;ifr_settings.type
op_assign
id|IF_IFACE_SYNC_SERIAL
suffix:semicolon
r_if
c_cond
(paren
id|ifr-&gt;ifr_settings.size
OL
id|size
)paren
(brace
id|ifr-&gt;ifr_settings.size
op_assign
id|size
suffix:semicolon
multiline_comment|/* data size wanted */
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|line
comma
op_amp
id|port-&gt;settings
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|IF_IFACE_SYNC_SERIAL
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_line
comma
id|line
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|new_line.clock_type
op_ne
id|CLOCK_EXT
op_logical_and
id|new_line.clock_type
op_ne
id|CLOCK_TXFROMRX
op_logical_and
id|new_line.clock_type
op_ne
id|CLOCK_INT
op_logical_and
id|new_line.clock_type
op_ne
id|CLOCK_TXINT
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* No such clock setting */
r_if
c_cond
(paren
id|new_line.loopback
op_ne
l_int|0
op_logical_and
id|new_line.loopback
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|port-&gt;settings
comma
op_amp
id|new_line
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Update settings */
id|n2_set_iface
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
id|hdlc_ioctl
c_func
(paren
id|dev
comma
id|ifr
comma
id|cmd
)paren
suffix:semicolon
)brace
)brace
DECL|function|n2_destroy_card
r_static
r_void
id|n2_destroy_card
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
r_int
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
l_int|2
suffix:semicolon
id|cnt
op_increment
)paren
r_if
c_cond
(paren
id|card-&gt;ports
(braket
id|cnt
)braket
dot
id|card
)paren
id|unregister_hdlc_device
c_func
(paren
op_amp
id|card-&gt;ports
(braket
id|cnt
)braket
dot
id|hdlc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;irq
)paren
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;winbase
)paren
(brace
id|iounmap
c_func
(paren
id|card-&gt;winbase
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|card-&gt;phy_winbase
comma
id|USE_WINDOWSIZE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;io
)paren
id|release_region
c_func
(paren
id|card-&gt;io
comma
id|N2_IOPORTS
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
DECL|function|n2_run
r_static
r_int
id|__init
id|n2_run
c_func
(paren
r_int
r_int
id|io
comma
r_int
r_int
id|irq
comma
r_int
r_int
id|winbase
comma
r_int
id|valid0
comma
r_int
id|valid1
)paren
(brace
id|card_t
op_star
id|card
suffix:semicolon
id|u8
id|cnt
comma
id|pcr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|io
template_param
l_int|0x3FF
op_logical_or
(paren
id|io
op_mod
id|N2_IOPORTS
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: invalid I/O port value&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
template_param
l_int|15
op_logical_or
id|irq
op_eq
l_int|6
)paren
multiline_comment|/* FIXME */
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: invalid IRQ value&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|winbase
template_param
l_int|0xFFFFF
op_logical_or
(paren
id|winbase
op_amp
l_int|0xFFF
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: invalid RAM value&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|card
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|card_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: unable to allocate memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|memset
c_func
(paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
id|card_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
id|N2_IOPORTS
comma
id|devname
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: I/O port region in use&bslash;n&quot;
)paren
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|card-&gt;io
op_assign
id|io
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
op_amp
id|sca_intr
comma
l_int|0
comma
id|devname
comma
id|card
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: could not allocate IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|card-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|winbase
comma
id|USE_WINDOWSIZE
comma
id|devname
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: could not request RAM window&bslash;n&quot;
)paren
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|card-&gt;phy_winbase
op_assign
id|winbase
suffix:semicolon
id|card-&gt;winbase
op_assign
id|ioremap
c_func
(paren
id|winbase
comma
id|USE_WINDOWSIZE
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
op_plus
id|N2_PCR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|winbase
op_rshift
l_int|12
comma
id|io
op_plus
id|N2_BAR
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|USE_WINDOWSIZE
)paren
(brace
r_case
l_int|16384
suffix:colon
id|outb
c_func
(paren
id|WIN16K
comma
id|io
op_plus
id|N2_PSR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32768
suffix:colon
id|outb
c_func
(paren
id|WIN32K
comma
id|io
op_plus
id|N2_PSR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|65536
suffix:colon
id|outb
c_func
(paren
id|WIN64K
comma
id|io
op_plus
id|N2_PSR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: invalid window size&bslash;n&quot;
)paren
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pcr
op_assign
id|PCR_ENWIN
op_or
id|PCR_VPM
op_or
(paren
id|USE_BUS16BITS
ques
c_cond
id|PCR_BUS16
suffix:colon
l_int|0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|pcr
comma
id|io
op_plus
id|N2_PCR
)paren
suffix:semicolon
id|card-&gt;ram_size
op_assign
id|sca_detect_ram
c_func
(paren
id|card
comma
id|card-&gt;winbase
comma
id|MAX_RAM_SIZE
)paren
suffix:semicolon
multiline_comment|/* number of TX + RX buffers for one port */
id|i
op_assign
id|card-&gt;ram_size
op_div
(paren
(paren
id|valid0
op_plus
id|valid1
)paren
op_star
(paren
r_sizeof
(paren
id|pkt_desc
)paren
op_plus
id|HDLC_MAX_MRU
)paren
)paren
suffix:semicolon
id|card-&gt;tx_ring_buffers
op_assign
id|min
c_func
(paren
id|i
op_div
l_int|2
comma
id|MAX_TX_BUFFERS
)paren
suffix:semicolon
id|card-&gt;rx_ring_buffers
op_assign
id|i
op_minus
id|card-&gt;tx_ring_buffers
suffix:semicolon
id|card-&gt;buff_offset
op_assign
(paren
id|valid0
op_plus
id|valid1
)paren
op_star
r_sizeof
(paren
id|pkt_desc
)paren
op_star
(paren
id|card-&gt;tx_ring_buffers
op_plus
id|card-&gt;rx_ring_buffers
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;n2: RISCom/N2 %u KB RAM, IRQ%u, &quot;
l_string|&quot;using %u TX + %u RX packets rings&bslash;n&quot;
comma
id|card-&gt;ram_size
op_div
l_int|1024
comma
id|card-&gt;irq
comma
id|card-&gt;tx_ring_buffers
comma
id|card-&gt;rx_ring_buffers
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;tx_ring_buffers
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: RAM test failed&bslash;n&quot;
)paren
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|pcr
op_or_assign
id|PCR_RUNSCA
suffix:semicolon
multiline_comment|/* run SCA */
id|outb
c_func
(paren
id|pcr
comma
id|io
op_plus
id|N2_PCR
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
op_plus
id|N2_MCR
)paren
suffix:semicolon
id|sca_init
c_func
(paren
id|card
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
l_int|2
suffix:semicolon
id|cnt
op_increment
)paren
(brace
id|port_t
op_star
id|port
op_assign
op_amp
id|card-&gt;ports
(braket
id|cnt
)braket
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|hdlc_to_dev
c_func
(paren
op_amp
id|port-&gt;hdlc
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cnt
op_eq
l_int|0
op_logical_and
op_logical_neg
id|valid0
)paren
op_logical_or
(paren
id|cnt
op_eq
l_int|1
op_logical_and
op_logical_neg
id|valid1
)paren
)paren
r_continue
suffix:semicolon
id|port-&gt;phy_node
op_assign
id|cnt
suffix:semicolon
id|port-&gt;valid
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cnt
op_eq
l_int|1
)paren
op_logical_and
id|valid0
)paren
id|port-&gt;log_node
op_assign
l_int|1
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|port-&gt;lock
)paren
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|winbase
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|winbase
op_plus
id|USE_WINDOWSIZE
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|50
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|n2_ioctl
suffix:semicolon
id|dev-&gt;open
op_assign
id|n2_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|n2_close
suffix:semicolon
id|port-&gt;hdlc.attach
op_assign
id|sca_attach
suffix:semicolon
id|port-&gt;hdlc.xmit
op_assign
id|sca_xmit
suffix:semicolon
id|port-&gt;settings.clock_type
op_assign
id|CLOCK_EXT
suffix:semicolon
r_if
c_cond
(paren
id|register_hdlc_device
c_func
(paren
op_amp
id|port-&gt;hdlc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;n2: unable to register hdlc &quot;
l_string|&quot;device&bslash;n&quot;
)paren
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|port-&gt;card
op_assign
id|card
suffix:semicolon
id|sca_init_sync_port
c_func
(paren
id|port
)paren
suffix:semicolon
multiline_comment|/* Set up SCA memory */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: RISCom/N2 node %d&bslash;n&quot;
comma
id|hdlc_to_name
c_func
(paren
op_amp
id|port-&gt;hdlc
)paren
comma
id|port-&gt;phy_node
)paren
suffix:semicolon
)brace
op_star
id|new_card
op_assign
id|card
suffix:semicolon
id|new_card
op_assign
op_amp
id|card-&gt;next_card
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|n2_init
r_static
r_int
id|__init
id|n2_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|hw
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;n2: no card initialized&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/* no parameters specified, abort */
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_do
(brace
r_int
r_int
id|io
comma
id|irq
comma
id|ram
suffix:semicolon
r_int
id|valid
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Default = both ports disabled */
id|io
op_assign
id|simple_strtoul
c_func
(paren
id|hw
comma
op_amp
id|hw
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|hw
op_increment
op_ne
l_char|&squot;,&squot;
)paren
r_break
suffix:semicolon
id|irq
op_assign
id|simple_strtoul
c_func
(paren
id|hw
comma
op_amp
id|hw
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|hw
op_increment
op_ne
l_char|&squot;,&squot;
)paren
r_break
suffix:semicolon
id|ram
op_assign
id|simple_strtoul
c_func
(paren
id|hw
comma
op_amp
id|hw
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|hw
op_increment
op_ne
l_char|&squot;,&squot;
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_star
id|hw
op_eq
l_char|&squot;0&squot;
op_logical_and
op_logical_neg
id|valid
(braket
l_int|0
)braket
)paren
id|valid
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Port 0 enabled */
r_else
r_if
c_cond
(paren
op_star
id|hw
op_eq
l_char|&squot;1&squot;
op_logical_and
op_logical_neg
id|valid
(braket
l_int|1
)braket
)paren
id|valid
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Port 1 enabled */
r_else
r_break
suffix:semicolon
id|hw
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|valid
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|valid
(braket
l_int|1
)braket
)paren
r_break
suffix:semicolon
multiline_comment|/* at least one port must be used */
r_if
c_cond
(paren
op_star
id|hw
op_eq
l_char|&squot;:&squot;
op_logical_or
op_star
id|hw
op_eq
l_char|&squot;&bslash;x0&squot;
)paren
id|n2_run
c_func
(paren
id|io
comma
id|irq
comma
id|ram
comma
id|valid
(braket
l_int|0
)braket
comma
id|valid
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|hw
op_eq
l_char|&squot;&bslash;x0&squot;
)paren
r_return
id|first_card
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|hw
op_increment
op_eq
l_char|&squot;:&squot;
)paren
(brace
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;n2: invalid hardware parameters&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|first_card
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|n2_cleanup
r_static
r_void
id|__exit
id|n2_cleanup
c_func
(paren
r_void
)paren
(brace
id|card_t
op_star
id|card
op_assign
id|first_card
suffix:semicolon
r_while
c_loop
(paren
id|card
)paren
(brace
id|card_t
op_star
id|ptr
op_assign
id|card
suffix:semicolon
id|card
op_assign
id|card-&gt;next_card
suffix:semicolon
id|n2_destroy_card
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
)brace
DECL|variable|n2_init
id|module_init
c_func
(paren
id|n2_init
)paren
suffix:semicolon
DECL|variable|n2_cleanup
id|module_exit
c_func
(paren
id|n2_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;RISCom/N2 serial port driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL v2&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|hw
comma
id|charp
comma
l_int|0444
)paren
suffix:semicolon
multiline_comment|/* hw=io,irq,ram,ports:io,irq,... */
eof
