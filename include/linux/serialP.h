multiline_comment|/*&n; * Private header file for the (dumb) serial driver&n; *&n; * Copyright (C) 1997 by Theodore Ts&squot;o.&n; * &n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; */
macro_line|#ifndef _LINUX_SERIALP_H
DECL|macro|_LINUX_SERIALP_H
mdefine_line|#define _LINUX_SERIALP_H
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|struct|serial_state
r_struct
id|serial_state
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|revision
r_int
id|revision
suffix:semicolon
multiline_comment|/* Chip revision (950) */
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|iomem_base
id|u8
op_star
id|iomem_base
suffix:semicolon
DECL|member|iomem_reg_shift
id|u16
id|iomem_reg_shift
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before closing */
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
DECL|member|io_type
r_int
id|io_type
suffix:semicolon
DECL|member|info
r_struct
id|async_struct
op_star
id|info
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|async_struct
r_struct
id|async_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|state
r_struct
id|serial_state
op_star
id|state
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|quot
r_int
id|quot
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character */
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|IER
r_int
id|IER
suffix:semicolon
multiline_comment|/* Interrupt Enable Register */
DECL|member|MCR
r_int
id|MCR
suffix:semicolon
multiline_comment|/* Modem control register */
DECL|member|LCR
r_int
id|LCR
suffix:semicolon
multiline_comment|/* Line control register */
DECL|member|ACR
r_int
id|ACR
suffix:semicolon
multiline_comment|/* 16950 Additional Control Reg. */
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|last_active
r_int
r_int
id|last_active
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|xmit
r_struct
id|circ_buf
id|xmit
suffix:semicolon
DECL|member|xmit_lock
id|spinlock_t
id|xmit_lock
suffix:semicolon
DECL|member|iomem_base
id|u8
op_star
id|iomem_base
suffix:semicolon
DECL|member|iomem_reg_shift
id|u16
id|iomem_reg_shift
suffix:semicolon
DECL|member|io_type
r_int
id|io_type
suffix:semicolon
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|tlet
r_struct
id|tasklet_struct
id|tlet
suffix:semicolon
macro_line|#ifdef DECLARE_WAITQUEUE
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|delta_msr_wait
id|wait_queue_head_t
id|delta_msr_wait
suffix:semicolon
macro_line|#else&t;
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
DECL|member|delta_msr_wait
r_struct
id|wait_queue
op_star
id|delta_msr_wait
suffix:semicolon
macro_line|#endif&t;
DECL|member|next_port
r_struct
id|async_struct
op_star
id|next_port
suffix:semicolon
multiline_comment|/* For the linked list */
DECL|member|prev_port
r_struct
id|async_struct
op_star
id|prev_port
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CONFIGURED_SERIAL_PORT
mdefine_line|#define CONFIGURED_SERIAL_PORT(info) ((info)-&gt;port || ((info)-&gt;iomem_base))
DECL|macro|SERIAL_MAGIC
mdefine_line|#define SERIAL_MAGIC 0x5301
DECL|macro|SSTATE_MAGIC
mdefine_line|#define SSTATE_MAGIC 0x5302
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|RS_EVENT_WRITE_WAKEUP
mdefine_line|#define RS_EVENT_WRITE_WAKEUP&t;0
multiline_comment|/*&n; * Multiport serial configuration structure --- internal structure&n; */
DECL|struct|rs_multiport_struct
r_struct
id|rs_multiport_struct
(brace
DECL|member|port1
r_int
id|port1
suffix:semicolon
DECL|member|mask1
DECL|member|match1
r_int
r_char
id|mask1
comma
id|match1
suffix:semicolon
DECL|member|port2
r_int
id|port2
suffix:semicolon
DECL|member|mask2
DECL|member|match2
r_int
r_char
id|mask2
comma
id|match2
suffix:semicolon
DECL|member|port3
r_int
id|port3
suffix:semicolon
DECL|member|mask3
DECL|member|match3
r_int
r_char
id|mask3
comma
id|match3
suffix:semicolon
DECL|member|port4
r_int
id|port4
suffix:semicolon
DECL|member|mask4
DECL|member|match4
r_int
r_char
id|mask4
comma
id|match4
suffix:semicolon
DECL|member|port_monitor
r_int
id|port_monitor
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(__alpha__) &amp;&amp; !defined(CONFIG_PCI)
multiline_comment|/*&n; * Digital did something really horribly wrong with the OUT1 and OUT2&n; * lines on at least some ALPHA&squot;s.  The failure mode is that if either&n; * is cleared, the machine locks up with endless interrupts.&n; *&n; * This is still used by arch/mips/au1000/common/serial.c for some weird&n; * reason (mips != alpha!)&n; */
DECL|macro|ALPHA_KLUDGE_MCR
mdefine_line|#define ALPHA_KLUDGE_MCR  (UART_MCR_OUT2 | UART_MCR_OUT1)
macro_line|#elif defined(CONFIG_SBC8560)
multiline_comment|/*&n; * WindRiver did something similarly broken on their SBC8560 board. The&n; * UART tristates its IRQ output while OUT2 is clear, but they pulled&n; * the interrupt line _up_ instead of down, so if we register the IRQ&n; * while the UART is in that state, we die in an IRQ storm. */
DECL|macro|ALPHA_KLUDGE_MCR
mdefine_line|#define ALPHA_KLUDGE_MCR (UART_MCR_OUT2)
macro_line|#else
DECL|macro|ALPHA_KLUDGE_MCR
mdefine_line|#define ALPHA_KLUDGE_MCR 0
macro_line|#endif
multiline_comment|/*&n; * Definitions for PCI support.&n; */
DECL|macro|SPCI_FL_BASE_MASK
mdefine_line|#define SPCI_FL_BASE_MASK&t;0x0007
DECL|macro|SPCI_FL_BASE0
mdefine_line|#define SPCI_FL_BASE0&t;0x0000
DECL|macro|SPCI_FL_BASE1
mdefine_line|#define SPCI_FL_BASE1&t;0x0001
DECL|macro|SPCI_FL_BASE2
mdefine_line|#define SPCI_FL_BASE2&t;0x0002
DECL|macro|SPCI_FL_BASE3
mdefine_line|#define SPCI_FL_BASE3&t;0x0003
DECL|macro|SPCI_FL_BASE4
mdefine_line|#define SPCI_FL_BASE4&t;0x0004
DECL|macro|SPCI_FL_GET_BASE
mdefine_line|#define SPCI_FL_GET_BASE(x)&t;(x &amp; SPCI_FL_BASE_MASK)
DECL|macro|SPCI_FL_IRQ_MASK
mdefine_line|#define SPCI_FL_IRQ_MASK       (0x0007 &lt;&lt; 4)
DECL|macro|SPCI_FL_IRQBASE0
mdefine_line|#define SPCI_FL_IRQBASE0       (0x0000 &lt;&lt; 4)
DECL|macro|SPCI_FL_IRQBASE1
mdefine_line|#define SPCI_FL_IRQBASE1       (0x0001 &lt;&lt; 4)
DECL|macro|SPCI_FL_IRQBASE2
mdefine_line|#define SPCI_FL_IRQBASE2       (0x0002 &lt;&lt; 4)
DECL|macro|SPCI_FL_IRQBASE3
mdefine_line|#define SPCI_FL_IRQBASE3       (0x0003 &lt;&lt; 4)
DECL|macro|SPCI_FL_IRQBASE4
mdefine_line|#define SPCI_FL_IRQBASE4       (0x0004 &lt;&lt; 4)
DECL|macro|SPCI_FL_GET_IRQBASE
mdefine_line|#define SPCI_FL_GET_IRQBASE(x)        ((x &amp; SPCI_FL_IRQ_MASK) &gt;&gt; 4)
multiline_comment|/* Use successive BARs (PCI base address registers), &n;   else use offset into some specified BAR */
DECL|macro|SPCI_FL_BASE_TABLE
mdefine_line|#define SPCI_FL_BASE_TABLE&t;0x0100
multiline_comment|/* Use successive entries in the irq resource table */
DECL|macro|SPCI_FL_IRQ_TABLE
mdefine_line|#define SPCI_FL_IRQ_TABLE&t;0x0200
multiline_comment|/* Use the irq resource table instead of dev-&gt;irq */
DECL|macro|SPCI_FL_IRQRESOURCE
mdefine_line|#define SPCI_FL_IRQRESOURCE&t;0x0400
multiline_comment|/* Use the Base address register size to cap number of ports */
DECL|macro|SPCI_FL_REGION_SZ_CAP
mdefine_line|#define SPCI_FL_REGION_SZ_CAP&t;0x0800
multiline_comment|/* Do not use irq sharing for this device */
DECL|macro|SPCI_FL_NO_SHIRQ
mdefine_line|#define SPCI_FL_NO_SHIRQ&t;0x1000
multiline_comment|/* This is a PNP device */
DECL|macro|SPCI_FL_ISPNP
mdefine_line|#define SPCI_FL_ISPNP&t;&t;0x2000
DECL|macro|SPCI_FL_PNPDEFAULT
mdefine_line|#define SPCI_FL_PNPDEFAULT&t;(SPCI_FL_IRQRESOURCE|SPCI_FL_ISPNP)
macro_line|#endif /* _LINUX_SERIAL_H */
eof
