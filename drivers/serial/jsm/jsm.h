multiline_comment|/************************************************************************&n; * Copyright 2003 Digi International (www.digi.com)&n; *&n; * Copyright (C) 2004 IBM Corporation. All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED; without even the&n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR&n; * PURPOSE.  See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 * Temple Place - Suite 330, Boston,&n; * MA  02111-1307, USA.&n; *&n; * Contact Information:&n; * Scott H Kilau &lt;Scott_Kilau@digi.com&gt;&n; * Wendy Xiong   &lt;wendyx@us.ltcfwd.linux.ibm.com&gt;&n; *&n; ***********************************************************************/
macro_line|#ifndef __JSM_DRIVER_H
DECL|macro|__JSM_DRIVER_H
mdefine_line|#define __JSM_DRIVER_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;&t;/* To pick up the varions Linux types */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/*&n; * Debugging levels can be set using debug insmod variable&n; * They can also be compiled out completely.&n; */
r_enum
(brace
DECL|enumerator|DBG_INIT
id|DBG_INIT
op_assign
l_int|0x01
comma
DECL|enumerator|DBG_BASIC
id|DBG_BASIC
op_assign
l_int|0x02
comma
DECL|enumerator|DBG_CORE
id|DBG_CORE
op_assign
l_int|0x04
comma
DECL|enumerator|DBG_OPEN
id|DBG_OPEN
op_assign
l_int|0x08
comma
DECL|enumerator|DBG_CLOSE
id|DBG_CLOSE
op_assign
l_int|0x10
comma
DECL|enumerator|DBG_READ
id|DBG_READ
op_assign
l_int|0x20
comma
DECL|enumerator|DBG_WRITE
id|DBG_WRITE
op_assign
l_int|0x40
comma
DECL|enumerator|DBG_IOCTL
id|DBG_IOCTL
op_assign
l_int|0x80
comma
DECL|enumerator|DBG_PROC
id|DBG_PROC
op_assign
l_int|0x100
comma
DECL|enumerator|DBG_PARAM
id|DBG_PARAM
op_assign
l_int|0x200
comma
DECL|enumerator|DBG_PSCAN
id|DBG_PSCAN
op_assign
l_int|0x400
comma
DECL|enumerator|DBG_EVENT
id|DBG_EVENT
op_assign
l_int|0x800
comma
DECL|enumerator|DBG_DRAIN
id|DBG_DRAIN
op_assign
l_int|0x1000
comma
DECL|enumerator|DBG_MSIGS
id|DBG_MSIGS
op_assign
l_int|0x2000
comma
DECL|enumerator|DBG_MGMT
id|DBG_MGMT
op_assign
l_int|0x4000
comma
DECL|enumerator|DBG_INTR
id|DBG_INTR
op_assign
l_int|0x8000
comma
DECL|enumerator|DBG_CARR
id|DBG_CARR
op_assign
l_int|0x10000
comma
)brace
suffix:semicolon
DECL|macro|jsm_printk
mdefine_line|#define jsm_printk(nlevel, klevel, pdev, fmt, args...)&t;&bslash;&n;&t;if ((DBG_##nlevel &amp; jsm_debug))&t;&t;&t;&bslash;&n;&t;dev_printk(KERN_##klevel, pdev-&gt;dev, fmt, ## args)
DECL|macro|MAXPORTS
mdefine_line|#define MAXPORTS&t;8
DECL|macro|MAX_STOPS_SENT
mdefine_line|#define MAX_STOPS_SENT&t;5
multiline_comment|/* Board type definitions */
DECL|macro|T_NEO
mdefine_line|#define T_NEO&t;&t;0000
DECL|macro|T_CLASSIC
mdefine_line|#define T_CLASSIC&t;0001
DECL|macro|T_PCIBUS
mdefine_line|#define T_PCIBUS&t;0400
multiline_comment|/* Board State Definitions */
DECL|macro|BD_RUNNING
mdefine_line|#define BD_RUNNING&t;0x0
DECL|macro|BD_REASON
mdefine_line|#define BD_REASON&t;0x7f
DECL|macro|BD_NOTFOUND
mdefine_line|#define BD_NOTFOUND&t;0x1
DECL|macro|BD_NOIOPORT
mdefine_line|#define BD_NOIOPORT&t;0x2
DECL|macro|BD_NOMEM
mdefine_line|#define BD_NOMEM&t;0x3
DECL|macro|BD_NOBIOS
mdefine_line|#define BD_NOBIOS&t;0x4
DECL|macro|BD_NOFEP
mdefine_line|#define BD_NOFEP&t;0x5
DECL|macro|BD_FAILED
mdefine_line|#define BD_FAILED&t;0x6
DECL|macro|BD_ALLOCATED
mdefine_line|#define BD_ALLOCATED&t;0x7
DECL|macro|BD_TRIBOOT
mdefine_line|#define BD_TRIBOOT&t;0x8
DECL|macro|BD_BADKME
mdefine_line|#define BD_BADKME&t;0x80
multiline_comment|/* 4 extra for alignment play space */
DECL|macro|WRITEBUFLEN
mdefine_line|#define WRITEBUFLEN&t;((4096) + 4)
DECL|macro|MYFLIPLEN
mdefine_line|#define MYFLIPLEN&t;N_TTY_BUF_SIZE
DECL|macro|JSM_VERSION
mdefine_line|#define JSM_VERSION&t;&quot;jsm: 1.1-1-INKERNEL&quot;
DECL|macro|JSM_PARTNUM
mdefine_line|#define JSM_PARTNUM&t;&quot;40002438_A-INKERNEL&quot;
multiline_comment|/*&n; * All the possible states the driver can be while being loaded.&n; */
r_enum
(brace
DECL|enumerator|DRIVER_INITIALIZED
id|DRIVER_INITIALIZED
op_assign
l_int|0
comma
DECL|enumerator|DRIVER_READY
id|DRIVER_READY
)brace
suffix:semicolon
multiline_comment|/*&n; * All the possible states the board can be while booting up.&n; */
r_enum
(brace
DECL|enumerator|BOARD_FAILED
id|BOARD_FAILED
op_assign
l_int|0
comma
DECL|enumerator|BOARD_FOUND
id|BOARD_FOUND
comma
DECL|enumerator|BOARD_READY
id|BOARD_READY
)brace
suffix:semicolon
DECL|struct|board_id
r_struct
id|board_id
(brace
DECL|member|name
id|u8
op_star
id|name
suffix:semicolon
DECL|member|maxports
id|u32
id|maxports
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|jsm_board
suffix:semicolon
r_struct
id|jsm_channel
suffix:semicolon
multiline_comment|/************************************************************************&n; * Per board operations structure&t;&t;&t;&t;&t;*&n; ************************************************************************/
DECL|struct|board_ops
r_struct
id|board_ops
(brace
DECL|member|intr
id|irqreturn_t
(paren
op_star
id|intr
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|voidbrd
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|uart_init
r_void
(paren
op_star
id|uart_init
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|uart_off
r_void
(paren
op_star
id|uart_off
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|param
r_void
(paren
op_star
id|param
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|assert_modem_signals
r_void
(paren
op_star
id|assert_modem_signals
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|flush_uart_write
r_void
(paren
op_star
id|flush_uart_write
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|flush_uart_read
r_void
(paren
op_star
id|flush_uart_read
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|disable_receiver
r_void
(paren
op_star
id|disable_receiver
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|enable_receiver
r_void
(paren
op_star
id|enable_receiver
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|send_break
r_void
(paren
op_star
id|send_break
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|clear_break
r_void
(paren
op_star
id|clear_break
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
comma
r_int
)paren
suffix:semicolon
DECL|member|send_start_character
r_void
(paren
op_star
id|send_start_character
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|send_stop_character
r_void
(paren
op_star
id|send_stop_character
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|copy_data_from_queue_to_uart
r_void
(paren
op_star
id|copy_data_from_queue_to_uart
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|get_uart_bytes_left
id|u32
(paren
op_star
id|get_uart_bytes_left
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
DECL|member|send_immediate_char
r_void
(paren
op_star
id|send_immediate_char
)paren
(paren
r_struct
id|jsm_channel
op_star
id|ch
comma
r_int
r_char
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Per-board information&n; */
DECL|struct|jsm_board
r_struct
id|jsm_board
(brace
DECL|member|boardnum
r_int
id|boardnum
suffix:semicolon
multiline_comment|/* Board number: 0-32 */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* Type of board */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Product Name */
DECL|member|rev
id|u8
id|rev
suffix:semicolon
multiline_comment|/* PCI revision ID */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|maxports
id|u32
id|maxports
suffix:semicolon
multiline_comment|/* MAX ports this board can handle */
DECL|member|bd_lock
id|spinlock_t
id|bd_lock
suffix:semicolon
multiline_comment|/* Used to protect board */
DECL|member|bd_intr_lock
id|spinlock_t
id|bd_intr_lock
suffix:semicolon
multiline_comment|/* Used to protect the poller tasklet and&n;&t;&t;&t;&t;&t; * the interrupt routine from each other.&n;&t;&t;&t;&t;&t; */
DECL|member|state
id|u32
id|state
suffix:semicolon
multiline_comment|/* State of card. */
DECL|member|state_wait
id|wait_queue_head_t
id|state_wait
suffix:semicolon
multiline_comment|/* Place to sleep on for state change */
DECL|member|nasync
id|u32
id|nasync
suffix:semicolon
multiline_comment|/* Number of ports on card */
DECL|member|irq
id|u32
id|irq
suffix:semicolon
multiline_comment|/* Interrupt request number */
DECL|member|intr_count
id|u64
id|intr_count
suffix:semicolon
multiline_comment|/* Count of interrupts */
DECL|member|membase
id|u64
id|membase
suffix:semicolon
multiline_comment|/* Start of base memory of the card */
DECL|member|membase_end
id|u64
id|membase_end
suffix:semicolon
multiline_comment|/* End of base memory of the card */
DECL|member|re_map_membase
id|u8
id|__iomem
op_star
id|re_map_membase
suffix:semicolon
multiline_comment|/* Remapped memory of the card */
DECL|member|iobase
id|u64
id|iobase
suffix:semicolon
multiline_comment|/* Start of io base of the card */
DECL|member|iobase_end
id|u64
id|iobase_end
suffix:semicolon
multiline_comment|/* End of io base of the card */
DECL|member|bd_uart_offset
id|u32
id|bd_uart_offset
suffix:semicolon
multiline_comment|/* Space between each UART */
DECL|member|channels
r_struct
id|jsm_channel
op_star
id|channels
(braket
id|MAXPORTS
)braket
suffix:semicolon
multiline_comment|/* array of pointers to our channels. */
DECL|member|flipbuf
r_char
op_star
id|flipbuf
suffix:semicolon
multiline_comment|/* Our flip buffer, alloced if board is found */
DECL|member|dpatype
id|u16
id|dpatype
suffix:semicolon
multiline_comment|/* The board &quot;type&quot;, as defined by DPA */
DECL|member|dpastatus
id|u16
id|dpastatus
suffix:semicolon
multiline_comment|/* The board &quot;status&quot;, as defined by DPA */
DECL|member|bd_dividend
id|u32
id|bd_dividend
suffix:semicolon
multiline_comment|/* Board/UARTs specific dividend */
DECL|member|bd_ops
r_struct
id|board_ops
op_star
id|bd_ops
suffix:semicolon
DECL|member|jsm_board_entry
r_struct
id|list_head
id|jsm_board_entry
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/************************************************************************&n; * Device flag definitions for ch_flags.&n; ************************************************************************/
DECL|macro|CH_PRON
mdefine_line|#define CH_PRON&t;&t;0x0001&t;&t;/* Printer on string&t;&t;*/
DECL|macro|CH_STOP
mdefine_line|#define CH_STOP&t;&t;0x0002&t;&t;/* Output is stopped&t;&t;*/
DECL|macro|CH_STOPI
mdefine_line|#define CH_STOPI&t;0x0004&t;&t;/* Input is stopped&t;&t;*/
DECL|macro|CH_CD
mdefine_line|#define CH_CD&t;&t;0x0008&t;&t;/* Carrier is present&t;&t;*/
DECL|macro|CH_FCAR
mdefine_line|#define CH_FCAR&t;&t;0x0010&t;&t;/* Carrier forced on&t;&t;*/
DECL|macro|CH_HANGUP
mdefine_line|#define CH_HANGUP&t;0x0020&t;&t;/* Hangup received&t;&t;*/
DECL|macro|CH_RECEIVER_OFF
mdefine_line|#define CH_RECEIVER_OFF&t;0x0040&t;&t;/* Receiver is off&t;&t;*/
DECL|macro|CH_OPENING
mdefine_line|#define CH_OPENING&t;0x0080&t;&t;/* Port in fragile open state&t;*/
DECL|macro|CH_CLOSING
mdefine_line|#define CH_CLOSING&t;0x0100&t;&t;/* Port in fragile close state&t;*/
DECL|macro|CH_FIFO_ENABLED
mdefine_line|#define CH_FIFO_ENABLED 0x0200&t;&t;/* Port has FIFOs enabled&t;*/
DECL|macro|CH_TX_FIFO_EMPTY
mdefine_line|#define CH_TX_FIFO_EMPTY 0x0400&t;&t;/* TX Fifo is completely empty&t;*/
DECL|macro|CH_TX_FIFO_LWM
mdefine_line|#define CH_TX_FIFO_LWM&t;0x0800&t;&t;/* TX Fifo is below Low Water&t;*/
DECL|macro|CH_BREAK_SENDING
mdefine_line|#define CH_BREAK_SENDING 0x1000&t;&t;/* Break is being sent&t;&t;*/
DECL|macro|CH_LOOPBACK
mdefine_line|#define CH_LOOPBACK 0x2000&t;&t;/* Channel is in lookback mode&t;*/
DECL|macro|CH_FLIPBUF_IN_USE
mdefine_line|#define CH_FLIPBUF_IN_USE 0x4000&t;/* Channel&squot;s flipbuf is in use&t;*/
DECL|macro|CH_BAUD0
mdefine_line|#define CH_BAUD0&t;0x08000&t;&t;/* Used for checking B0 transitions */
multiline_comment|/* Our Read/Error/Write queue sizes */
DECL|macro|RQUEUEMASK
mdefine_line|#define RQUEUEMASK&t;0x1FFF&t;&t;/* 8 K - 1 */
DECL|macro|EQUEUEMASK
mdefine_line|#define EQUEUEMASK&t;0x1FFF&t;&t;/* 8 K - 1 */
DECL|macro|WQUEUEMASK
mdefine_line|#define WQUEUEMASK&t;0x0FFF&t;&t;/* 4 K - 1 */
DECL|macro|RQUEUESIZE
mdefine_line|#define RQUEUESIZE&t;(RQUEUEMASK + 1)
DECL|macro|EQUEUESIZE
mdefine_line|#define EQUEUESIZE&t;RQUEUESIZE
DECL|macro|WQUEUESIZE
mdefine_line|#define WQUEUESIZE&t;(WQUEUEMASK + 1)
multiline_comment|/************************************************************************&n; * Channel information structure.&n; ************************************************************************/
DECL|struct|jsm_channel
r_struct
id|jsm_channel
(brace
DECL|member|uart_port
r_struct
id|uart_port
id|uart_port
suffix:semicolon
DECL|member|ch_bd
r_struct
id|jsm_board
op_star
id|ch_bd
suffix:semicolon
multiline_comment|/* Board structure pointer&t;*/
DECL|member|ch_lock
id|spinlock_t
id|ch_lock
suffix:semicolon
multiline_comment|/* provide for serialization */
DECL|member|ch_flags_wait
id|wait_queue_head_t
id|ch_flags_wait
suffix:semicolon
DECL|member|ch_portnum
id|u32
id|ch_portnum
suffix:semicolon
multiline_comment|/* Port number, 0 offset.&t;*/
DECL|member|ch_open_count
id|u32
id|ch_open_count
suffix:semicolon
multiline_comment|/* open count&t;&t;&t;*/
DECL|member|ch_flags
id|u32
id|ch_flags
suffix:semicolon
multiline_comment|/* Channel flags&t;&t;*/
DECL|member|ch_close_delay
id|u64
id|ch_close_delay
suffix:semicolon
multiline_comment|/* How long we should drop RTS/DTR for */
DECL|member|ch_cpstime
id|u64
id|ch_cpstime
suffix:semicolon
multiline_comment|/* Time for CPS calculations&t;*/
DECL|member|ch_c_iflag
id|tcflag_t
id|ch_c_iflag
suffix:semicolon
multiline_comment|/* channel iflags&t;&t;*/
DECL|member|ch_c_cflag
id|tcflag_t
id|ch_c_cflag
suffix:semicolon
multiline_comment|/* channel cflags&t;&t;*/
DECL|member|ch_c_oflag
id|tcflag_t
id|ch_c_oflag
suffix:semicolon
multiline_comment|/* channel oflags&t;&t;*/
DECL|member|ch_c_lflag
id|tcflag_t
id|ch_c_lflag
suffix:semicolon
multiline_comment|/* channel lflags&t;&t;*/
DECL|member|ch_stopc
id|u8
id|ch_stopc
suffix:semicolon
multiline_comment|/* Stop character&t;&t;*/
DECL|member|ch_startc
id|u8
id|ch_startc
suffix:semicolon
multiline_comment|/* Start character&t;&t;*/
DECL|member|ch_old_baud
id|u32
id|ch_old_baud
suffix:semicolon
multiline_comment|/* Cache of the current baud */
DECL|member|ch_custom_speed
id|u32
id|ch_custom_speed
suffix:semicolon
multiline_comment|/* Custom baud, if set */
DECL|member|ch_wopen
id|u32
id|ch_wopen
suffix:semicolon
multiline_comment|/* Waiting for open process cnt */
DECL|member|ch_mostat
id|u8
id|ch_mostat
suffix:semicolon
multiline_comment|/* FEP output modem status&t;*/
DECL|member|ch_mistat
id|u8
id|ch_mistat
suffix:semicolon
multiline_comment|/* FEP input modem status&t;*/
DECL|member|ch_neo_uart
r_struct
id|neo_uart_struct
id|__iomem
op_star
id|ch_neo_uart
suffix:semicolon
multiline_comment|/* Pointer to the &quot;mapped&quot; UART struct */
DECL|member|ch_cached_lsr
id|u8
id|ch_cached_lsr
suffix:semicolon
multiline_comment|/* Cached value of the LSR register */
DECL|member|ch_rqueue
id|u8
op_star
id|ch_rqueue
suffix:semicolon
multiline_comment|/* Our read queue buffer - malloc&squot;ed */
DECL|member|ch_r_head
id|u16
id|ch_r_head
suffix:semicolon
multiline_comment|/* Head location of the read queue */
DECL|member|ch_r_tail
id|u16
id|ch_r_tail
suffix:semicolon
multiline_comment|/* Tail location of the read queue */
DECL|member|ch_equeue
id|u8
op_star
id|ch_equeue
suffix:semicolon
multiline_comment|/* Our error queue buffer - malloc&squot;ed */
DECL|member|ch_e_head
id|u16
id|ch_e_head
suffix:semicolon
multiline_comment|/* Head location of the error queue */
DECL|member|ch_e_tail
id|u16
id|ch_e_tail
suffix:semicolon
multiline_comment|/* Tail location of the error queue */
DECL|member|ch_wqueue
id|u8
op_star
id|ch_wqueue
suffix:semicolon
multiline_comment|/* Our write queue buffer - malloc&squot;ed */
DECL|member|ch_w_head
id|u16
id|ch_w_head
suffix:semicolon
multiline_comment|/* Head location of the write queue */
DECL|member|ch_w_tail
id|u16
id|ch_w_tail
suffix:semicolon
multiline_comment|/* Tail location of the write queue */
DECL|member|ch_rxcount
id|u64
id|ch_rxcount
suffix:semicolon
multiline_comment|/* total of data received so far */
DECL|member|ch_txcount
id|u64
id|ch_txcount
suffix:semicolon
multiline_comment|/* total of data transmitted so far */
DECL|member|ch_r_tlevel
id|u8
id|ch_r_tlevel
suffix:semicolon
multiline_comment|/* Receive Trigger level */
DECL|member|ch_t_tlevel
id|u8
id|ch_t_tlevel
suffix:semicolon
multiline_comment|/* Transmit Trigger level */
DECL|member|ch_r_watermark
id|u8
id|ch_r_watermark
suffix:semicolon
multiline_comment|/* Receive Watermark */
DECL|member|ch_stops_sent
id|u32
id|ch_stops_sent
suffix:semicolon
multiline_comment|/* How many times I have sent a stop character&n;&t;&t;&t;&t;&t; * to try to stop the other guy sending.&n;&t;&t;&t;&t;&t; */
DECL|member|ch_err_parity
id|u64
id|ch_err_parity
suffix:semicolon
multiline_comment|/* Count of parity errors on channel */
DECL|member|ch_err_frame
id|u64
id|ch_err_frame
suffix:semicolon
multiline_comment|/* Count of framing errors on channel */
DECL|member|ch_err_break
id|u64
id|ch_err_break
suffix:semicolon
multiline_comment|/* Count of breaks on channel */
DECL|member|ch_err_overrun
id|u64
id|ch_err_overrun
suffix:semicolon
multiline_comment|/* Count of overruns on channel */
DECL|member|ch_xon_sends
id|u64
id|ch_xon_sends
suffix:semicolon
multiline_comment|/* Count of xons transmitted */
DECL|member|ch_xoff_sends
id|u64
id|ch_xoff_sends
suffix:semicolon
multiline_comment|/* Count of xoffs transmitted */
)brace
suffix:semicolon
multiline_comment|/************************************************************************&n; * Per channel/port NEO UART structure&t;&t;&t;&t;&t;*&n; ************************************************************************&n; *&t;&t;Base Structure Entries Usage Meanings to Host&t;&t;*&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; *&t;W = read write&t;&t;R = read only&t;&t;&t;&t;*&n; *&t;&t;&t;U = Unused.&t;&t;&t;&t;&t;*&n; ************************************************************************/
DECL|struct|neo_uart_struct
r_struct
id|neo_uart_struct
(brace
DECL|member|txrx
id|u8
id|txrx
suffix:semicolon
multiline_comment|/* WR&t;RHR/THR - Holding Reg */
DECL|member|ier
id|u8
id|ier
suffix:semicolon
multiline_comment|/* WR&t;IER - Interrupt Enable Reg */
DECL|member|isr_fcr
id|u8
id|isr_fcr
suffix:semicolon
multiline_comment|/* WR&t;ISR/FCR - Interrupt Status Reg/Fifo Control Reg */
DECL|member|lcr
id|u8
id|lcr
suffix:semicolon
multiline_comment|/* WR&t;LCR - Line Control Reg */
DECL|member|mcr
id|u8
id|mcr
suffix:semicolon
multiline_comment|/* WR&t;MCR - Modem Control Reg */
DECL|member|lsr
id|u8
id|lsr
suffix:semicolon
multiline_comment|/* WR&t;LSR - Line Status Reg */
DECL|member|msr
id|u8
id|msr
suffix:semicolon
multiline_comment|/* WR&t;MSR - Modem Status Reg */
DECL|member|spr
id|u8
id|spr
suffix:semicolon
multiline_comment|/* WR&t;SPR - Scratch Pad Reg */
DECL|member|fctr
id|u8
id|fctr
suffix:semicolon
multiline_comment|/* WR&t;FCTR - Feature Control Reg */
DECL|member|efr
id|u8
id|efr
suffix:semicolon
multiline_comment|/* WR&t;EFR - Enhanced Function Reg */
DECL|member|tfifo
id|u8
id|tfifo
suffix:semicolon
multiline_comment|/* WR&t;TXCNT/TXTRG - Transmit FIFO Reg */
DECL|member|rfifo
id|u8
id|rfifo
suffix:semicolon
multiline_comment|/* WR&t;RXCNT/RXTRG - Recieve FIFO Reg */
DECL|member|xoffchar1
id|u8
id|xoffchar1
suffix:semicolon
multiline_comment|/* WR&t;XOFF 1 - XOff Character 1 Reg */
DECL|member|xoffchar2
id|u8
id|xoffchar2
suffix:semicolon
multiline_comment|/* WR&t;XOFF 2 - XOff Character 2 Reg */
DECL|member|xonchar1
id|u8
id|xonchar1
suffix:semicolon
multiline_comment|/* WR&t;XON 1 - Xon Character 1 Reg */
DECL|member|xonchar2
id|u8
id|xonchar2
suffix:semicolon
multiline_comment|/* WR&t;XON 2 - XOn Character 2 Reg */
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|0x2ff
op_minus
l_int|0x200
)braket
suffix:semicolon
multiline_comment|/* U&t;Reserved by Exar */
DECL|member|txrxburst
id|u8
id|txrxburst
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* RW&t;64 bytes of RX/TX FIFO Data */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|0x37f
op_minus
l_int|0x340
)braket
suffix:semicolon
multiline_comment|/* U&t;Reserved by Exar */
DECL|member|rxburst_with_errors
id|u8
id|rxburst_with_errors
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* R&t;64 bytes of RX FIFO Data + LSR */
)brace
suffix:semicolon
multiline_comment|/* Where to read the extended interrupt register (32bits instead of 8bits) */
DECL|macro|UART_17158_POLL_ADDR_OFFSET
mdefine_line|#define&t;UART_17158_POLL_ADDR_OFFSET&t;0x80
multiline_comment|/*&n; * These are the redefinitions for the FCTR on the XR17C158, since&n; * Exar made them different than their earlier design. (XR16C854)&n; */
multiline_comment|/* These are only applicable when table D is selected */
DECL|macro|UART_17158_FCTR_RTS_NODELAY
mdefine_line|#define UART_17158_FCTR_RTS_NODELAY&t;0x00
DECL|macro|UART_17158_FCTR_RTS_4DELAY
mdefine_line|#define UART_17158_FCTR_RTS_4DELAY&t;0x01
DECL|macro|UART_17158_FCTR_RTS_6DELAY
mdefine_line|#define UART_17158_FCTR_RTS_6DELAY&t;0x02
DECL|macro|UART_17158_FCTR_RTS_8DELAY
mdefine_line|#define UART_17158_FCTR_RTS_8DELAY&t;0x03
DECL|macro|UART_17158_FCTR_RTS_12DELAY
mdefine_line|#define UART_17158_FCTR_RTS_12DELAY&t;0x12
DECL|macro|UART_17158_FCTR_RTS_16DELAY
mdefine_line|#define UART_17158_FCTR_RTS_16DELAY&t;0x05
DECL|macro|UART_17158_FCTR_RTS_20DELAY
mdefine_line|#define UART_17158_FCTR_RTS_20DELAY&t;0x13
DECL|macro|UART_17158_FCTR_RTS_24DELAY
mdefine_line|#define UART_17158_FCTR_RTS_24DELAY&t;0x06
DECL|macro|UART_17158_FCTR_RTS_28DELAY
mdefine_line|#define UART_17158_FCTR_RTS_28DELAY&t;0x14
DECL|macro|UART_17158_FCTR_RTS_32DELAY
mdefine_line|#define UART_17158_FCTR_RTS_32DELAY&t;0x07
DECL|macro|UART_17158_FCTR_RTS_36DELAY
mdefine_line|#define UART_17158_FCTR_RTS_36DELAY&t;0x16
DECL|macro|UART_17158_FCTR_RTS_40DELAY
mdefine_line|#define UART_17158_FCTR_RTS_40DELAY&t;0x08
DECL|macro|UART_17158_FCTR_RTS_44DELAY
mdefine_line|#define UART_17158_FCTR_RTS_44DELAY&t;0x09
DECL|macro|UART_17158_FCTR_RTS_48DELAY
mdefine_line|#define UART_17158_FCTR_RTS_48DELAY&t;0x10
DECL|macro|UART_17158_FCTR_RTS_52DELAY
mdefine_line|#define UART_17158_FCTR_RTS_52DELAY&t;0x11
DECL|macro|UART_17158_FCTR_RTS_IRDA
mdefine_line|#define UART_17158_FCTR_RTS_IRDA&t;0x10
DECL|macro|UART_17158_FCTR_RS485
mdefine_line|#define UART_17158_FCTR_RS485&t;&t;0x20
DECL|macro|UART_17158_FCTR_TRGA
mdefine_line|#define UART_17158_FCTR_TRGA&t;&t;0x00
DECL|macro|UART_17158_FCTR_TRGB
mdefine_line|#define UART_17158_FCTR_TRGB&t;&t;0x40
DECL|macro|UART_17158_FCTR_TRGC
mdefine_line|#define UART_17158_FCTR_TRGC&t;&t;0x80
DECL|macro|UART_17158_FCTR_TRGD
mdefine_line|#define UART_17158_FCTR_TRGD&t;&t;0xC0
multiline_comment|/* 17158 trigger table selects.. */
DECL|macro|UART_17158_FCTR_BIT6
mdefine_line|#define UART_17158_FCTR_BIT6&t;&t;0x40
DECL|macro|UART_17158_FCTR_BIT7
mdefine_line|#define UART_17158_FCTR_BIT7&t;&t;0x80
multiline_comment|/* 17158 TX/RX memmapped buffer offsets */
DECL|macro|UART_17158_RX_FIFOSIZE
mdefine_line|#define UART_17158_RX_FIFOSIZE&t;&t;64
DECL|macro|UART_17158_TX_FIFOSIZE
mdefine_line|#define UART_17158_TX_FIFOSIZE&t;&t;64
multiline_comment|/* 17158 Extended IIR&squot;s */
DECL|macro|UART_17158_IIR_RDI_TIMEOUT
mdefine_line|#define UART_17158_IIR_RDI_TIMEOUT&t;0x0C&t;/* Receiver data TIMEOUT */
DECL|macro|UART_17158_IIR_XONXOFF
mdefine_line|#define UART_17158_IIR_XONXOFF&t;&t;0x10&t;/* Received an XON/XOFF char */
DECL|macro|UART_17158_IIR_HWFLOW_STATE_CHANGE
mdefine_line|#define UART_17158_IIR_HWFLOW_STATE_CHANGE 0x20&t;/* CTS/DSR or RTS/DTR state change */
DECL|macro|UART_17158_IIR_FIFO_ENABLED
mdefine_line|#define UART_17158_IIR_FIFO_ENABLED&t;0xC0&t;/* 16550 FIFOs are Enabled */
multiline_comment|/*&n; * These are the extended interrupts that get sent&n; * back to us from the UART&squot;s 32bit interrupt register&n; */
DECL|macro|UART_17158_RX_LINE_STATUS
mdefine_line|#define UART_17158_RX_LINE_STATUS&t;0x1&t;/* RX Ready */
DECL|macro|UART_17158_RXRDY_TIMEOUT
mdefine_line|#define UART_17158_RXRDY_TIMEOUT&t;0x2&t;/* RX Ready Timeout */
DECL|macro|UART_17158_TXRDY
mdefine_line|#define UART_17158_TXRDY&t;&t;0x3&t;/* TX Ready */
DECL|macro|UART_17158_MSR
mdefine_line|#define UART_17158_MSR&t;&t;&t;0x4&t;/* Modem State Change */
DECL|macro|UART_17158_TX_AND_FIFO_CLR
mdefine_line|#define UART_17158_TX_AND_FIFO_CLR&t;0x40&t;/* Transmitter Holding Reg Empty */
DECL|macro|UART_17158_RX_FIFO_DATA_ERROR
mdefine_line|#define UART_17158_RX_FIFO_DATA_ERROR&t;0x80&t;/* UART detected an RX FIFO Data error */
multiline_comment|/*&n; * These are the EXTENDED definitions for the 17C158&squot;s Interrupt&n; * Enable Register.&n; */
DECL|macro|UART_17158_EFR_ECB
mdefine_line|#define UART_17158_EFR_ECB&t;0x10&t;/* Enhanced control bit */
DECL|macro|UART_17158_EFR_IXON
mdefine_line|#define UART_17158_EFR_IXON&t;0x2&t;/* Receiver compares Xon1/Xoff1 */
DECL|macro|UART_17158_EFR_IXOFF
mdefine_line|#define UART_17158_EFR_IXOFF&t;0x8&t;/* Transmit Xon1/Xoff1 */
DECL|macro|UART_17158_EFR_RTSDTR
mdefine_line|#define UART_17158_EFR_RTSDTR&t;0x40&t;/* Auto RTS/DTR Flow Control Enable */
DECL|macro|UART_17158_EFR_CTSDSR
mdefine_line|#define UART_17158_EFR_CTSDSR&t;0x80&t;/* Auto CTS/DSR Flow COntrol Enable */
DECL|macro|UART_17158_XOFF_DETECT
mdefine_line|#define UART_17158_XOFF_DETECT&t;0x1&t;/* Indicates whether chip saw an incoming XOFF char */
DECL|macro|UART_17158_XON_DETECT
mdefine_line|#define UART_17158_XON_DETECT&t;0x2&t;/* Indicates whether chip saw an incoming XON char */
DECL|macro|UART_17158_IER_RSVD1
mdefine_line|#define UART_17158_IER_RSVD1&t;0x10&t;/* Reserved by Exar */
DECL|macro|UART_17158_IER_XOFF
mdefine_line|#define UART_17158_IER_XOFF&t;0x20&t;/* Xoff Interrupt Enable */
DECL|macro|UART_17158_IER_RTSDTR
mdefine_line|#define UART_17158_IER_RTSDTR&t;0x40&t;/* Output Interrupt Enable */
DECL|macro|UART_17158_IER_CTSDSR
mdefine_line|#define UART_17158_IER_CTSDSR&t;0x80&t;/* Input Interrupt Enable */
DECL|macro|PCI_DEVICE_NEO_2DB9_PCI_NAME
mdefine_line|#define PCI_DEVICE_NEO_2DB9_PCI_NAME&t;&t;&quot;Neo 2 - DB9 Universal PCI&quot;
DECL|macro|PCI_DEVICE_NEO_2DB9PRI_PCI_NAME
mdefine_line|#define PCI_DEVICE_NEO_2DB9PRI_PCI_NAME&t;&t;&quot;Neo 2 - DB9 Universal PCI - Powered Ring Indicator&quot;
DECL|macro|PCI_DEVICE_NEO_2RJ45_PCI_NAME
mdefine_line|#define PCI_DEVICE_NEO_2RJ45_PCI_NAME&t;&t;&quot;Neo 2 - RJ45 Universal PCI&quot;
DECL|macro|PCI_DEVICE_NEO_2RJ45PRI_PCI_NAME
mdefine_line|#define PCI_DEVICE_NEO_2RJ45PRI_PCI_NAME&t;&quot;Neo 2 - RJ45 Universal PCI - Powered Ring Indicator&quot;
multiline_comment|/*&n; * Our Global Variables.&n; */
r_extern
r_struct
id|uart_driver
id|jsm_uart_driver
suffix:semicolon
r_extern
r_struct
id|board_ops
id|jsm_neo_ops
suffix:semicolon
r_extern
r_int
id|jsm_debug
suffix:semicolon
r_extern
r_int
id|jsm_rawreadok
suffix:semicolon
r_extern
r_int
id|jsm_driver_state
suffix:semicolon
multiline_comment|/* The state of the driver&t;*/
r_extern
r_char
op_star
id|jsm_driver_state_text
(braket
)braket
suffix:semicolon
multiline_comment|/* Array of driver state text */
r_extern
id|spinlock_t
id|jsm_board_head_lock
suffix:semicolon
r_extern
r_struct
id|list_head
id|jsm_board_head
suffix:semicolon
multiline_comment|/*************************************************************************&n; *&n; * Prototypes for non-static functions used in more than one module&n; *&n; *************************************************************************/
r_int
id|jsm_tty_write
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
r_int
id|jsm_tty_init
c_func
(paren
r_struct
id|jsm_board
op_star
)paren
suffix:semicolon
r_int
id|jsm_uart_port_init
c_func
(paren
r_struct
id|jsm_board
op_star
)paren
suffix:semicolon
r_int
id|jsm_remove_uart_port
c_func
(paren
r_struct
id|jsm_board
op_star
)paren
suffix:semicolon
r_void
id|jsm_input
c_func
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
r_void
id|jsm_carrier
c_func
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
r_void
id|jsm_check_queue_flow_control
c_func
(paren
r_struct
id|jsm_channel
op_star
id|ch
)paren
suffix:semicolon
r_void
id|jsm_create_driver_sysfiles
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_void
id|jsm_remove_driver_sysfiles
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
