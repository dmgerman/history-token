multiline_comment|/*&n; * include/linux/serial.h&n; *&n; * Copyright (C) 1992 by Theodore Ts&squot;o.&n; * &n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; */
macro_line|#ifndef _LINUX_SERIAL_H
DECL|macro|_LINUX_SERIAL_H
mdefine_line|#define _LINUX_SERIAL_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Counters of the input lines (CTS, DSR, RI, CD) interrupts&n; */
DECL|struct|async_icount
r_struct
id|async_icount
(brace
DECL|member|cts
DECL|member|dsr
DECL|member|rng
DECL|member|dcd
DECL|member|tx
DECL|member|rx
id|__u32
id|cts
comma
id|dsr
comma
id|rng
comma
id|dcd
comma
id|tx
comma
id|rx
suffix:semicolon
DECL|member|frame
DECL|member|parity
DECL|member|overrun
DECL|member|brk
id|__u32
id|frame
comma
id|parity
comma
id|overrun
comma
id|brk
suffix:semicolon
DECL|member|buf_overrun
id|__u32
id|buf_overrun
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The size of the serial xmit buffer is 1 page, or 4096 bytes&n; */
DECL|macro|SERIAL_XMIT_SIZE
mdefine_line|#define SERIAL_XMIT_SIZE PAGE_SIZE
macro_line|#endif
DECL|struct|serial_struct
r_struct
id|serial_struct
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
id|line
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
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|io_type
r_char
id|io_type
suffix:semicolon
DECL|member|reserved_char
r_char
id|reserved_char
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before closing */
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
multiline_comment|/* no longer used... */
DECL|member|iomem_base
r_int
r_char
op_star
id|iomem_base
suffix:semicolon
DECL|member|iomem_reg_shift
r_int
r_int
id|iomem_reg_shift
suffix:semicolon
DECL|member|port_high
r_int
r_int
id|port_high
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * For the close wait times, 0 means wait forever for serial port to&n; * flush its output.  65535 means don&squot;t wait at all.&n; */
DECL|macro|ASYNC_CLOSING_WAIT_INF
mdefine_line|#define ASYNC_CLOSING_WAIT_INF&t;0
DECL|macro|ASYNC_CLOSING_WAIT_NONE
mdefine_line|#define ASYNC_CLOSING_WAIT_NONE&t;65535
multiline_comment|/*&n; * These are the supported serial types.&n; */
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
mdefine_line|#define PORT_CIRRUS     5&t;/* usurped by cyclades.c */
DECL|macro|PORT_16650
mdefine_line|#define PORT_16650&t;6
DECL|macro|PORT_16650V2
mdefine_line|#define PORT_16650V2&t;7
DECL|macro|PORT_16750
mdefine_line|#define PORT_16750&t;8
DECL|macro|PORT_STARTECH
mdefine_line|#define PORT_STARTECH&t;9&t;/* usurped by cyclades.c */
DECL|macro|PORT_16C950
mdefine_line|#define PORT_16C950&t;10&t;/* Oxford Semiconductor */
DECL|macro|PORT_16654
mdefine_line|#define PORT_16654&t;11
DECL|macro|PORT_16850
mdefine_line|#define PORT_16850&t;12
DECL|macro|PORT_RSA
mdefine_line|#define PORT_RSA&t;13&t;/* RSA-DV II/S card */
DECL|macro|PORT_MAX
mdefine_line|#define PORT_MAX&t;13
DECL|macro|SERIAL_IO_PORT
mdefine_line|#define SERIAL_IO_PORT&t;0
DECL|macro|SERIAL_IO_HUB6
mdefine_line|#define SERIAL_IO_HUB6&t;1
DECL|macro|SERIAL_IO_MEM
mdefine_line|#define SERIAL_IO_MEM&t;2
DECL|macro|SERIAL_IO_GSC
mdefine_line|#define SERIAL_IO_GSC&t;3
DECL|struct|serial_uart_config
r_struct
id|serial_uart_config
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|dfl_xmit_fifo_size
r_int
id|dfl_xmit_fifo_size
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UART_CLEAR_FIFO
mdefine_line|#define UART_CLEAR_FIFO&t;&t;0x01
DECL|macro|UART_USE_FIFO
mdefine_line|#define UART_USE_FIFO&t;&t;0x02
DECL|macro|UART_STARTECH
mdefine_line|#define UART_STARTECH&t;&t;0x04
multiline_comment|/*&n; * Definitions for async_struct (and serial_struct) flags field&n; */
DECL|macro|ASYNC_HUP_NOTIFY
mdefine_line|#define ASYNC_HUP_NOTIFY 0x0001 /* Notify getty on hangups and closes &n;&t;&t;&t;&t;   on the callout port */
DECL|macro|ASYNC_FOURPORT
mdefine_line|#define ASYNC_FOURPORT  0x0002&t;/* Set OU1, OUT2 per AST Fourport settings */
DECL|macro|ASYNC_SAK
mdefine_line|#define ASYNC_SAK&t;0x0004&t;/* Secure Attention Key (Orange book) */
DECL|macro|ASYNC_SPLIT_TERMIOS
mdefine_line|#define ASYNC_SPLIT_TERMIOS 0x0008 /* Separate termios for dialin/callout */
DECL|macro|ASYNC_SPD_MASK
mdefine_line|#define ASYNC_SPD_MASK&t;0x1030
DECL|macro|ASYNC_SPD_HI
mdefine_line|#define ASYNC_SPD_HI&t;0x0010&t;/* Use 56000 instead of 38400 bps */
DECL|macro|ASYNC_SPD_VHI
mdefine_line|#define ASYNC_SPD_VHI&t;0x0020  /* Use 115200 instead of 38400 bps */
DECL|macro|ASYNC_SPD_CUST
mdefine_line|#define ASYNC_SPD_CUST&t;0x0030  /* Use user-specified divisor */
DECL|macro|ASYNC_SKIP_TEST
mdefine_line|#define ASYNC_SKIP_TEST&t;0x0040 /* Skip UART test during autoconfiguration */
DECL|macro|ASYNC_AUTO_IRQ
mdefine_line|#define ASYNC_AUTO_IRQ  0x0080 /* Do automatic IRQ during autoconfiguration */
DECL|macro|ASYNC_SESSION_LOCKOUT
mdefine_line|#define ASYNC_SESSION_LOCKOUT 0x0100 /* Lock out cua opens based on session */
DECL|macro|ASYNC_PGRP_LOCKOUT
mdefine_line|#define ASYNC_PGRP_LOCKOUT    0x0200 /* Lock out cua opens based on pgrp */
DECL|macro|ASYNC_CALLOUT_NOHUP
mdefine_line|#define ASYNC_CALLOUT_NOHUP   0x0400 /* Don&squot;t do hangups for cua device */
DECL|macro|ASYNC_HARDPPS_CD
mdefine_line|#define ASYNC_HARDPPS_CD&t;0x0800&t;/* Call hardpps when CD goes high  */
DECL|macro|ASYNC_SPD_SHI
mdefine_line|#define ASYNC_SPD_SHI&t;0x1000&t;/* Use 230400 instead of 38400 bps */
DECL|macro|ASYNC_SPD_WARP
mdefine_line|#define ASYNC_SPD_WARP&t;0x1010&t;/* Use 460800 instead of 38400 bps */
DECL|macro|ASYNC_LOW_LATENCY
mdefine_line|#define ASYNC_LOW_LATENCY 0x2000 /* Request low latency behaviour */
DECL|macro|ASYNC_BUGGY_UART
mdefine_line|#define ASYNC_BUGGY_UART  0x4000 /* This is a buggy UART, skip some safety&n;&t;&t;&t;&t;  * checks.  Note: can be dangerous! */
DECL|macro|ASYNC_AUTOPROBE
mdefine_line|#define ASYNC_AUTOPROBE&t; 0x8000 /* Port was autoprobed by PCI or PNP code */
DECL|macro|ASYNC_FLAGS
mdefine_line|#define ASYNC_FLAGS&t;0x7FFF&t;/* Possible legal async flags */
DECL|macro|ASYNC_USR_MASK
mdefine_line|#define ASYNC_USR_MASK&t;0x3430&t;/* Legal flags that non-privileged&n;&t;&t;&t;&t; * users can set or reset */
multiline_comment|/* Internal flags used only by kernel/chr_drv/serial.c */
DECL|macro|ASYNC_INITIALIZED
mdefine_line|#define ASYNC_INITIALIZED&t;0x80000000 /* Serial port was initialized */
DECL|macro|ASYNC_CALLOUT_ACTIVE
mdefine_line|#define ASYNC_CALLOUT_ACTIVE&t;0x40000000 /* Call out device is active */
DECL|macro|ASYNC_NORMAL_ACTIVE
mdefine_line|#define ASYNC_NORMAL_ACTIVE&t;0x20000000 /* Normal device is active */
DECL|macro|ASYNC_BOOT_AUTOCONF
mdefine_line|#define ASYNC_BOOT_AUTOCONF&t;0x10000000 /* Autoconfigure port on bootup */
DECL|macro|ASYNC_CLOSING
mdefine_line|#define ASYNC_CLOSING&t;&t;0x08000000 /* Serial port is closing */
DECL|macro|ASYNC_CTS_FLOW
mdefine_line|#define ASYNC_CTS_FLOW&t;&t;0x04000000 /* Do CTS flow control */
DECL|macro|ASYNC_CHECK_CD
mdefine_line|#define ASYNC_CHECK_CD&t;&t;0x02000000 /* i.e., CLOCAL */
DECL|macro|ASYNC_SHARE_IRQ
mdefine_line|#define ASYNC_SHARE_IRQ&t;&t;0x01000000 /* for multifunction cards&n;&t;&t;&t;&t;&t;     --- no longer used */
DECL|macro|ASYNC_CONS_FLOW
mdefine_line|#define ASYNC_CONS_FLOW&t;&t;0x00800000 /* flow control for console  */
DECL|macro|ASYNC_BOOT_ONLYMCA
mdefine_line|#define ASYNC_BOOT_ONLYMCA&t;0x00400000 /* Probe only if MCA bus */
DECL|macro|ASYNC_INTERNAL_FLAGS
mdefine_line|#define ASYNC_INTERNAL_FLAGS&t;0xFFC00000 /* Internal flags */
multiline_comment|/*&n; * Multiport serial configuration structure --- external structure&n; */
DECL|struct|serial_multiport_struct
r_struct
id|serial_multiport_struct
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
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
DECL|member|reserved
r_int
id|reserved
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Serial input interrupt line counters -- external structure&n; * Four lines can interrupt: CTS, DSR, RI, DCD&n; */
DECL|struct|serial_icounter_struct
r_struct
id|serial_icounter_struct
(brace
DECL|member|cts
DECL|member|dsr
DECL|member|rng
DECL|member|dcd
r_int
id|cts
comma
id|dsr
comma
id|rng
comma
id|dcd
suffix:semicolon
DECL|member|rx
DECL|member|tx
r_int
id|rx
comma
id|tx
suffix:semicolon
DECL|member|frame
DECL|member|overrun
DECL|member|parity
DECL|member|brk
r_int
id|frame
comma
id|overrun
comma
id|parity
comma
id|brk
suffix:semicolon
DECL|member|buf_overrun
r_int
id|buf_overrun
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|9
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Export to allow PCMCIA to use this - Dave Hinds */
r_extern
r_int
id|register_serial
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|unregister_serial
c_func
(paren
r_int
id|line
)paren
suffix:semicolon
multiline_comment|/* Allow complicated architectures to specify rs_table[] at run time */
r_extern
r_int
id|early_serial_setup
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI
multiline_comment|/* tty ports reserved for the ACPI serial console port and debug port */
DECL|macro|ACPI_SERIAL_CONSOLE_PORT
mdefine_line|#define ACPI_SERIAL_CONSOLE_PORT        4
DECL|macro|ACPI_SERIAL_DEBUG_PORT
mdefine_line|#define ACPI_SERIAL_DEBUG_PORT          5
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SERIAL_H */
eof
