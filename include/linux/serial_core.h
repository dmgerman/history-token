multiline_comment|/*&n; *  linux/drivers/char/serial_core.h&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef LINUX_SERIAL_CORE_H
DECL|macro|LINUX_SERIAL_CORE_H
mdefine_line|#define LINUX_SERIAL_CORE_H
multiline_comment|/*&n; * The type definitions.  These are from Ted Ts&squot;o&squot;s serial.h&n; */
DECL|macro|PORT_UNKNOWN
mdefine_line|#define PORT_UNKNOWN&t;0
DECL|macro|PORT_8250
mdefine_line|#define PORT_8250&t;1
DECL|macro|PORT_16450
mdefine_line|#define PORT_16450&t;2
DECL|macro|PORT_16550
mdefine_line|#define PORT_16550&t;3
DECL|macro|PORT_16550A
mdefine_line|#define PORT_16550A&t;4
DECL|macro|PORT_CIRRUS
mdefine_line|#define PORT_CIRRUS&t;5
DECL|macro|PORT_16650
mdefine_line|#define PORT_16650&t;6
DECL|macro|PORT_16650V2
mdefine_line|#define PORT_16650V2&t;7
DECL|macro|PORT_16750
mdefine_line|#define PORT_16750&t;8
DECL|macro|PORT_STARTECH
mdefine_line|#define PORT_STARTECH&t;9
DECL|macro|PORT_16C950
mdefine_line|#define PORT_16C950&t;10
DECL|macro|PORT_16654
mdefine_line|#define PORT_16654&t;11
DECL|macro|PORT_16850
mdefine_line|#define PORT_16850&t;12
DECL|macro|PORT_RSA
mdefine_line|#define PORT_RSA&t;13
DECL|macro|PORT_NS16550A
mdefine_line|#define PORT_NS16550A&t;14
DECL|macro|PORT_XSCALE
mdefine_line|#define PORT_XSCALE&t;15
DECL|macro|PORT_MAX_8250
mdefine_line|#define PORT_MAX_8250&t;15&t;/* max port ID */
multiline_comment|/*&n; * ARM specific type numbers.  These are not currently guaranteed&n; * to be implemented, and will change in the future.  These are&n; * separate so any additions to the old serial.c that occur before&n; * we are merged can be easily merged here.&n; */
DECL|macro|PORT_PXA
mdefine_line|#define PORT_PXA&t;31
DECL|macro|PORT_AMBA
mdefine_line|#define PORT_AMBA&t;32
DECL|macro|PORT_CLPS711X
mdefine_line|#define PORT_CLPS711X&t;33
DECL|macro|PORT_SA1100
mdefine_line|#define PORT_SA1100&t;34
DECL|macro|PORT_UART00
mdefine_line|#define PORT_UART00&t;35
DECL|macro|PORT_21285
mdefine_line|#define PORT_21285&t;37
multiline_comment|/* Sparc type numbers.  */
DECL|macro|PORT_SUNZILOG
mdefine_line|#define PORT_SUNZILOG&t;38
DECL|macro|PORT_SUNSAB
mdefine_line|#define PORT_SUNSAB&t;39
multiline_comment|/* NEC v850.  */
DECL|macro|PORT_V850E_UART
mdefine_line|#define PORT_V850E_UART&t;40
multiline_comment|/* DZ */
DECL|macro|PORT_DZ
mdefine_line|#define PORT_DZ&t;&t;47
multiline_comment|/* Parisc type numbers. */
DECL|macro|PORT_MUX
mdefine_line|#define PORT_MUX&t;48
multiline_comment|/* Macintosh Zilog type numbers */
DECL|macro|PORT_MAC_ZILOG
mdefine_line|#define PORT_MAC_ZILOG&t;50&t;/* m68k : not yet implemented */
DECL|macro|PORT_PMAC_ZILOG
mdefine_line|#define PORT_PMAC_ZILOG&t;51
multiline_comment|/* SH-SCI */
DECL|macro|PORT_SCI
mdefine_line|#define PORT_SCI&t;52
DECL|macro|PORT_SCIF
mdefine_line|#define PORT_SCIF&t;53
DECL|macro|PORT_IRDA
mdefine_line|#define PORT_IRDA&t;54
multiline_comment|/* Samsung S3C2410 SoC and derivatives thereof */
DECL|macro|PORT_S3C2410
mdefine_line|#define PORT_S3C2410    55
multiline_comment|/* SGI IP22 aka Indy / Challenge S / Indigo 2 */
DECL|macro|PORT_IP22ZILOG
mdefine_line|#define PORT_IP22ZILOG&t;56
multiline_comment|/* Sharp LH7a40x -- an ARM9 SoC series */
DECL|macro|PORT_LH7A40X
mdefine_line|#define PORT_LH7A40X&t;57
multiline_comment|/* PPC CPM type number */
DECL|macro|PORT_CPM
mdefine_line|#define PORT_CPM        58
multiline_comment|/* MPC52xx type numbers */
DECL|macro|PORT_MPC52xx
mdefine_line|#define PORT_MPC52xx&t;59
multiline_comment|/* IBM icom */
DECL|macro|PORT_ICOM
mdefine_line|#define PORT_ICOM&t;60
multiline_comment|/* Samsung S3C2440 SoC */
DECL|macro|PORT_S3C2440
mdefine_line|#define PORT_S3C2440&t;61
multiline_comment|/* Motorola i.MX SoC */
DECL|macro|PORT_IMX
mdefine_line|#define PORT_IMX&t;62
multiline_comment|/* Marvell MPSC */
DECL|macro|PORT_MPSC
mdefine_line|#define PORT_MPSC&t;63
multiline_comment|/* TXX9 type number */
DECL|macro|PORT_TXX9
mdefine_line|#define PORT_TXX9       64
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
r_struct
id|uart_port
suffix:semicolon
r_struct
id|uart_info
suffix:semicolon
r_struct
id|serial_struct
suffix:semicolon
r_struct
id|device
suffix:semicolon
multiline_comment|/*&n; * This structure describes all the operations that can be&n; * done on the physical hardware.&n; */
DECL|struct|uart_ops
r_struct
id|uart_ops
(brace
DECL|member|tx_empty
r_int
r_int
(paren
op_star
id|tx_empty
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|set_mctrl
r_void
(paren
op_star
id|set_mctrl
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
r_int
id|mctrl
)paren
suffix:semicolon
DECL|member|get_mctrl
r_int
r_int
(paren
op_star
id|get_mctrl
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|stop_tx
r_void
(paren
op_star
id|stop_tx
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
r_int
id|tty_stop
)paren
suffix:semicolon
DECL|member|start_tx
r_void
(paren
op_star
id|start_tx
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
r_int
id|tty_start
)paren
suffix:semicolon
DECL|member|send_xchar
r_void
(paren
op_star
id|send_xchar
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_char
id|ch
)paren
suffix:semicolon
DECL|member|stop_rx
r_void
(paren
op_star
id|stop_rx
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|enable_ms
r_void
(paren
op_star
id|enable_ms
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|break_ctl
r_void
(paren
op_star
id|break_ctl
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
id|ctl
)paren
suffix:semicolon
DECL|member|startup
r_int
(paren
op_star
id|startup
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|set_termios
r_void
(paren
op_star
id|set_termios
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_struct
id|termios
op_star
r_new
comma
r_struct
id|termios
op_star
id|old
)paren
suffix:semicolon
DECL|member|pm
r_void
(paren
op_star
id|pm
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
r_int
id|state
comma
r_int
r_int
id|oldstate
)paren
suffix:semicolon
DECL|member|set_wake
r_int
(paren
op_star
id|set_wake
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
r_int
id|state
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Return a string describing the type of the port&n;&t; */
DECL|member|type
r_const
r_char
op_star
(paren
op_star
id|type
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Release IO and memory resources used by the port.&n;&t; * This includes iounmap if necessary.&n;&t; */
DECL|member|release_port
r_void
(paren
op_star
id|release_port
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Request IO and memory resources used by the port.&n;&t; * This includes iomapping the port if necessary.&n;&t; */
DECL|member|request_port
r_int
(paren
op_star
id|request_port
)paren
(paren
r_struct
id|uart_port
op_star
)paren
suffix:semicolon
DECL|member|config_port
r_void
(paren
op_star
id|config_port
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|verify_port
r_int
(paren
op_star
id|verify_port
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_struct
id|serial_struct
op_star
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|uart_port
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UART_CONFIG_TYPE
mdefine_line|#define UART_CONFIG_TYPE&t;(1 &lt;&lt; 0)
DECL|macro|UART_CONFIG_IRQ
mdefine_line|#define UART_CONFIG_IRQ&t;&t;(1 &lt;&lt; 1)
DECL|struct|uart_icount
r_struct
id|uart_icount
(brace
DECL|member|cts
id|__u32
id|cts
suffix:semicolon
DECL|member|dsr
id|__u32
id|dsr
suffix:semicolon
DECL|member|rng
id|__u32
id|rng
suffix:semicolon
DECL|member|dcd
id|__u32
id|dcd
suffix:semicolon
DECL|member|rx
id|__u32
id|rx
suffix:semicolon
DECL|member|tx
id|__u32
id|tx
suffix:semicolon
DECL|member|frame
id|__u32
id|frame
suffix:semicolon
DECL|member|overrun
id|__u32
id|overrun
suffix:semicolon
DECL|member|parity
id|__u32
id|parity
suffix:semicolon
DECL|member|brk
id|__u32
id|brk
suffix:semicolon
DECL|member|buf_overrun
id|__u32
id|buf_overrun
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|uart_port
r_struct
id|uart_port
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* port lock */
DECL|member|iobase
r_int
r_int
id|iobase
suffix:semicolon
multiline_comment|/* in/out[bwl] */
DECL|member|membase
r_int
r_char
id|__iomem
op_star
id|membase
suffix:semicolon
multiline_comment|/* read/write[bwl] */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq number */
DECL|member|uartclk
r_int
r_int
id|uartclk
suffix:semicolon
multiline_comment|/* base uart clock */
DECL|member|fifosize
r_int
r_char
id|fifosize
suffix:semicolon
multiline_comment|/* tx fifo size */
DECL|member|x_char
r_int
r_char
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff char */
DECL|member|regshift
r_int
r_char
id|regshift
suffix:semicolon
multiline_comment|/* reg offset shift */
DECL|member|iotype
r_int
r_char
id|iotype
suffix:semicolon
multiline_comment|/* io access style */
DECL|macro|UPIO_PORT
mdefine_line|#define UPIO_PORT&t;&t;(0)
DECL|macro|UPIO_HUB6
mdefine_line|#define UPIO_HUB6&t;&t;(1)
DECL|macro|UPIO_MEM
mdefine_line|#define UPIO_MEM&t;&t;(2)
DECL|macro|UPIO_MEM32
mdefine_line|#define UPIO_MEM32&t;&t;(3)
DECL|member|read_status_mask
r_int
r_int
id|read_status_mask
suffix:semicolon
multiline_comment|/* driver specific */
DECL|member|ignore_status_mask
r_int
r_int
id|ignore_status_mask
suffix:semicolon
multiline_comment|/* driver specific */
DECL|member|info
r_struct
id|uart_info
op_star
id|info
suffix:semicolon
multiline_comment|/* pointer to parent info */
DECL|member|icount
r_struct
id|uart_icount
id|icount
suffix:semicolon
multiline_comment|/* statistics */
DECL|member|cons
r_struct
id|console
op_star
id|cons
suffix:semicolon
multiline_comment|/* struct console, if any */
macro_line|#ifdef CONFIG_SERIAL_CORE_CONSOLE
DECL|member|sysrq
r_int
r_int
id|sysrq
suffix:semicolon
multiline_comment|/* sysrq timeout */
macro_line|#endif
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|UPF_FOURPORT
mdefine_line|#define UPF_FOURPORT&t;&t;(1 &lt;&lt; 1)
DECL|macro|UPF_SAK
mdefine_line|#define UPF_SAK&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|UPF_SPD_MASK
mdefine_line|#define UPF_SPD_MASK&t;&t;(0x1030)
DECL|macro|UPF_SPD_HI
mdefine_line|#define UPF_SPD_HI&t;&t;(0x0010)
DECL|macro|UPF_SPD_VHI
mdefine_line|#define UPF_SPD_VHI&t;&t;(0x0020)
DECL|macro|UPF_SPD_CUST
mdefine_line|#define UPF_SPD_CUST&t;&t;(0x0030)
DECL|macro|UPF_SPD_SHI
mdefine_line|#define UPF_SPD_SHI&t;&t;(0x1000)
DECL|macro|UPF_SPD_WARP
mdefine_line|#define UPF_SPD_WARP&t;&t;(0x1010)
DECL|macro|UPF_SKIP_TEST
mdefine_line|#define UPF_SKIP_TEST&t;&t;(1 &lt;&lt; 6)
DECL|macro|UPF_AUTO_IRQ
mdefine_line|#define UPF_AUTO_IRQ&t;&t;(1 &lt;&lt; 7)
DECL|macro|UPF_HARDPPS_CD
mdefine_line|#define UPF_HARDPPS_CD&t;&t;(1 &lt;&lt; 11)
DECL|macro|UPF_LOW_LATENCY
mdefine_line|#define UPF_LOW_LATENCY&t;&t;(1 &lt;&lt; 13)
DECL|macro|UPF_BUGGY_UART
mdefine_line|#define UPF_BUGGY_UART&t;&t;(1 &lt;&lt; 14)
DECL|macro|UPF_AUTOPROBE
mdefine_line|#define UPF_AUTOPROBE&t;&t;(1 &lt;&lt; 15)
DECL|macro|UPF_MAGIC_MULTIPLIER
mdefine_line|#define UPF_MAGIC_MULTIPLIER&t;(1 &lt;&lt; 16)
DECL|macro|UPF_BOOT_ONLYMCA
mdefine_line|#define UPF_BOOT_ONLYMCA&t;(1 &lt;&lt; 22)
DECL|macro|UPF_CONS_FLOW
mdefine_line|#define UPF_CONS_FLOW&t;&t;(1 &lt;&lt; 23)
DECL|macro|UPF_SHARE_IRQ
mdefine_line|#define UPF_SHARE_IRQ&t;&t;(1 &lt;&lt; 24)
DECL|macro|UPF_BOOT_AUTOCONF
mdefine_line|#define UPF_BOOT_AUTOCONF&t;(1 &lt;&lt; 28)
DECL|macro|UPF_IOREMAP
mdefine_line|#define UPF_IOREMAP&t;&t;(1 &lt;&lt; 31)
DECL|macro|UPF_CHANGE_MASK
mdefine_line|#define UPF_CHANGE_MASK&t;&t;(0x17fff)
DECL|macro|UPF_USR_MASK
mdefine_line|#define UPF_USR_MASK&t;&t;(UPF_SPD_MASK|UPF_LOW_LATENCY)
DECL|member|mctrl
r_int
r_int
id|mctrl
suffix:semicolon
multiline_comment|/* current modem ctrl settings */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* character-based timeout */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* port type */
DECL|member|ops
r_struct
id|uart_ops
op_star
id|ops
suffix:semicolon
DECL|member|custom_divisor
r_int
r_int
id|custom_divisor
suffix:semicolon
DECL|member|line
r_int
r_int
id|line
suffix:semicolon
multiline_comment|/* port index */
DECL|member|mapbase
r_int
r_int
id|mapbase
suffix:semicolon
multiline_comment|/* for ioremap */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* parent device */
DECL|member|hub6
r_int
r_char
id|hub6
suffix:semicolon
multiline_comment|/* this should be in the 8250 driver */
DECL|member|unused
r_int
r_char
id|unused
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the state information which is persistent across opens.&n; * The low level driver must not to touch any elements contained&n; * within.&n; */
DECL|struct|uart_state
r_struct
id|uart_state
(brace
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
multiline_comment|/* msec */
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* msec */
DECL|macro|USF_CLOSING_WAIT_INF
mdefine_line|#define USF_CLOSING_WAIT_INF&t;(0)
DECL|macro|USF_CLOSING_WAIT_NONE
mdefine_line|#define USF_CLOSING_WAIT_NONE&t;(~0U)
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|pm_state
r_int
id|pm_state
suffix:semicolon
DECL|member|info
r_struct
id|uart_info
op_star
id|info
suffix:semicolon
DECL|member|port
r_struct
id|uart_port
op_star
id|port
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UART_XMIT_SIZE
mdefine_line|#define UART_XMIT_SIZE&t;PAGE_SIZE
multiline_comment|/*&n; * This is the state information which is only valid when the port&n; * is open; it may be freed by the core driver once the device has&n; * been closed.  Either the low level driver or the core can modify&n; * stuff here.&n; */
DECL|struct|uart_info
r_struct
id|uart_info
(brace
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|xmit
r_struct
id|circ_buf
id|xmit
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n; * These are the flags that specific to info-&gt;flags, and reflect our&n; * internal state.  They can not be accessed via port-&gt;flags.  Low&n; * level drivers must not change these, but may query them instead.&n; */
DECL|macro|UIF_CHECK_CD
mdefine_line|#define UIF_CHECK_CD&t;&t;(1 &lt;&lt; 25)
DECL|macro|UIF_CTS_FLOW
mdefine_line|#define UIF_CTS_FLOW&t;&t;(1 &lt;&lt; 26)
DECL|macro|UIF_NORMAL_ACTIVE
mdefine_line|#define UIF_NORMAL_ACTIVE&t;(1 &lt;&lt; 29)
DECL|macro|UIF_INITIALIZED
mdefine_line|#define UIF_INITIALIZED&t;&t;(1 &lt;&lt; 31)
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|tlet
r_struct
id|tasklet_struct
id|tlet
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|delta_msr_wait
id|wait_queue_head_t
id|delta_msr_wait
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* number of characters left in xmit buffer before we ask for more */
DECL|macro|WAKEUP_CHARS
mdefine_line|#define WAKEUP_CHARS&t;&t;256
r_struct
id|module
suffix:semicolon
r_struct
id|tty_driver
suffix:semicolon
DECL|struct|uart_driver
r_struct
id|uart_driver
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|driver_name
r_const
r_char
op_star
id|driver_name
suffix:semicolon
DECL|member|dev_name
r_const
r_char
op_star
id|dev_name
suffix:semicolon
DECL|member|devfs_name
r_const
r_char
op_star
id|devfs_name
suffix:semicolon
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|cons
r_struct
id|console
op_star
id|cons
suffix:semicolon
multiline_comment|/*&n;&t; * these are private; the low level driver should not&n;&t; * touch these; they should be initialised to NULL&n;&t; */
DECL|member|state
r_struct
id|uart_state
op_star
id|state
suffix:semicolon
DECL|member|tty_driver
r_struct
id|tty_driver
op_star
id|tty_driver
suffix:semicolon
)brace
suffix:semicolon
r_void
id|uart_write_wakeup
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
multiline_comment|/*&n; * Baud rate helpers.&n; */
r_void
id|uart_update_timeout
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|cflag
comma
r_int
r_int
id|baud
)paren
suffix:semicolon
r_int
r_int
id|uart_get_baud_rate
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|termios
op_star
id|termios
comma
r_struct
id|termios
op_star
id|old
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
)paren
suffix:semicolon
r_int
r_int
id|uart_get_divisor
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|baud
)paren
suffix:semicolon
multiline_comment|/*&n; * Console helpers.&n; */
r_struct
id|uart_port
op_star
id|uart_get_console
c_func
(paren
r_struct
id|uart_port
op_star
id|ports
comma
r_int
id|nr
comma
r_struct
id|console
op_star
id|c
)paren
suffix:semicolon
r_void
id|uart_parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|baud
comma
r_int
op_star
id|parity
comma
r_int
op_star
id|bits
comma
r_int
op_star
id|flow
)paren
suffix:semicolon
r_int
id|uart_set_options
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|console
op_star
id|co
comma
r_int
id|baud
comma
r_int
id|parity
comma
r_int
id|bits
comma
r_int
id|flow
)paren
suffix:semicolon
r_struct
id|tty_driver
op_star
id|uart_console_device
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_int
op_star
id|index
)paren
suffix:semicolon
multiline_comment|/*&n; * Port/driver registration/removal&n; */
r_int
id|uart_register_driver
c_func
(paren
r_struct
id|uart_driver
op_star
id|uart
)paren
suffix:semicolon
r_void
id|uart_unregister_driver
c_func
(paren
r_struct
id|uart_driver
op_star
id|uart
)paren
suffix:semicolon
r_void
id|uart_unregister_port
c_func
(paren
r_struct
id|uart_driver
op_star
id|reg
comma
r_int
id|line
)paren
suffix:semicolon
r_int
id|uart_register_port
c_func
(paren
r_struct
id|uart_driver
op_star
id|reg
comma
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
r_int
id|uart_add_one_port
c_func
(paren
r_struct
id|uart_driver
op_star
id|reg
comma
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
r_int
id|uart_remove_one_port
c_func
(paren
r_struct
id|uart_driver
op_star
id|reg
comma
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
multiline_comment|/*&n; * Power Management&n; */
r_int
id|uart_suspend_port
c_func
(paren
r_struct
id|uart_driver
op_star
id|reg
comma
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
r_int
id|uart_resume_port
c_func
(paren
r_struct
id|uart_driver
op_star
id|reg
comma
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
DECL|macro|uart_circ_empty
mdefine_line|#define uart_circ_empty(circ)&t;&t;((circ)-&gt;head == (circ)-&gt;tail)
DECL|macro|uart_circ_clear
mdefine_line|#define uart_circ_clear(circ)&t;&t;((circ)-&gt;head = (circ)-&gt;tail = 0)
DECL|macro|uart_circ_chars_pending
mdefine_line|#define uart_circ_chars_pending(circ)&t;&bslash;&n;&t;(CIRC_CNT((circ)-&gt;head, (circ)-&gt;tail, UART_XMIT_SIZE))
DECL|macro|uart_circ_chars_free
mdefine_line|#define uart_circ_chars_free(circ)&t;&bslash;&n;&t;(CIRC_SPACE((circ)-&gt;head, (circ)-&gt;tail, UART_XMIT_SIZE))
DECL|macro|uart_tx_stopped
mdefine_line|#define uart_tx_stopped(port)&t;&t;&bslash;&n;&t;((port)-&gt;info-&gt;tty-&gt;stopped || (port)-&gt;info-&gt;tty-&gt;hw_stopped)
multiline_comment|/*&n; * The following are helper functions for the low level drivers.&n; */
macro_line|#ifdef SUPPORT_SYSRQ
r_static
r_inline
r_int
DECL|function|uart_handle_sysrq_char
id|uart_handle_sysrq_char
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|ch
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;sysrq
)paren
(brace
r_if
c_cond
(paren
id|ch
op_logical_and
id|time_before
c_func
(paren
id|jiffies
comma
id|port-&gt;sysrq
)paren
)paren
(brace
id|handle_sysrq
c_func
(paren
id|ch
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
id|port-&gt;sysrq
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|port-&gt;sysrq
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|uart_handle_sysrq_char
mdefine_line|#define uart_handle_sysrq_char(port,ch,regs)&t;(0)
macro_line|#endif
multiline_comment|/*&n; * We do the SysRQ and SAK checking like this...&n; */
DECL|function|uart_handle_break
r_static
r_inline
r_int
id|uart_handle_break
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_struct
id|uart_info
op_star
id|info
op_assign
id|port-&gt;info
suffix:semicolon
macro_line|#ifdef SUPPORT_SYSRQ
r_if
c_cond
(paren
id|port-&gt;cons
op_logical_and
id|port-&gt;cons-&gt;index
op_eq
id|port-&gt;line
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;sysrq
)paren
(brace
id|port-&gt;sysrq
op_assign
id|jiffies
op_plus
id|HZ
op_star
l_int|5
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|port-&gt;sysrq
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|UPF_SAK
)paren
id|do_SAK
c_func
(paren
id|info-&gt;tty
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;uart_handle_dcd_change - handle a change of carrier detect state&n; *&t;@port: uart_port structure for the open port&n; *&t;@status: new carrier detect status, nonzero if active&n; */
r_static
r_inline
r_void
DECL|function|uart_handle_dcd_change
id|uart_handle_dcd_change
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|status
)paren
(brace
r_struct
id|uart_info
op_star
id|info
op_assign
id|port-&gt;info
suffix:semicolon
id|port-&gt;icount.dcd
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_HARD_PPS
r_if
c_cond
(paren
(paren
id|port-&gt;flags
op_amp
id|UPF_HARDPPS_CD
)paren
op_logical_and
id|status
)paren
id|hardpps
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|UIF_CHECK_CD
)paren
(brace
r_if
c_cond
(paren
id|status
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|info-&gt;open_wait
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|info-&gt;tty
)paren
id|tty_hangup
c_func
(paren
id|info-&gt;tty
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;uart_handle_cts_change - handle a change of clear-to-send state&n; *&t;@port: uart_port structure for the open port&n; *&t;@status: new clear to send status, nonzero if active&n; */
r_static
r_inline
r_void
DECL|function|uart_handle_cts_change
id|uart_handle_cts_change
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_int
r_int
id|status
)paren
(brace
r_struct
id|uart_info
op_star
id|info
op_assign
id|port-&gt;info
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|info-&gt;tty
suffix:semicolon
id|port-&gt;icount.cts
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|UIF_CTS_FLOW
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;hw_stopped
)paren
(brace
r_if
c_cond
(paren
id|status
)paren
(brace
id|tty-&gt;hw_stopped
op_assign
l_int|0
suffix:semicolon
id|port-&gt;ops
op_member_access_from_pointer
id|start_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
id|uart_write_wakeup
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|tty-&gt;hw_stopped
op_assign
l_int|1
suffix:semicolon
id|port-&gt;ops
op_member_access_from_pointer
id|stop_tx
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; *&t;UART_ENABLE_MS - determine if port should enable modem status irqs&n; */
DECL|macro|UART_ENABLE_MS
mdefine_line|#define UART_ENABLE_MS(port,cflag)&t;((port)-&gt;flags &amp; UPF_HARDPPS_CD || &bslash;&n;&t;&t;&t;&t;&t; (cflag) &amp; CRTSCTS || &bslash;&n;&t;&t;&t;&t;&t; !((cflag) &amp; CLOCAL))
macro_line|#endif
macro_line|#endif /* LINUX_SERIAL_CORE_H */
eof
