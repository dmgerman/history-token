multiline_comment|/*&n; *  drivers/char/serial_tx3912.h&n; *&n; *  Copyright (C) 1999 Harald Koerfgen&n; *  Copyright (C) 2000 Jim Pick &lt;jim@jimpick.com&gt;&n; *  Copyright (C) 2001 Steven J. Hill (sjhill@realitydiluted.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Serial driver for TMPR3912/05 and PR31700 processors&n; */
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/generic_serial.h&gt;
multiline_comment|/* UART Interrupt (Interrupt 2) bits (UARTA,UARTB) */
DECL|macro|UART_RX_INT
mdefine_line|#define UART_RX_INT         9  /* receiver holding register full  (31, 21) */
DECL|macro|UART_RXOVERRUN_INT
mdefine_line|#define UART_RXOVERRUN_INT  8  /* receiver overrun error          (30, 20) */
DECL|macro|UART_FRAMEERR_INT
mdefine_line|#define UART_FRAMEERR_INT   7  /* receiver frame error            (29, 19) */
DECL|macro|UART_BREAK_INT
mdefine_line|#define UART_BREAK_INT      6  /* received break signal           (28, 18) */
DECL|macro|UART_PARITYERR_INT
mdefine_line|#define UART_PARITYERR_INT  5  /* receiver parity error           (27, 17) */
DECL|macro|UART_TX_INT
mdefine_line|#define UART_TX_INT         4  /* transmit holding register empty (26, 16) */
DECL|macro|UART_TXOVERRUN_INT
mdefine_line|#define UART_TXOVERRUN_INT  3  /* transmit overrun error          (25, 15) */
DECL|macro|UART_EMPTY_INT
mdefine_line|#define UART_EMPTY_INT      2  /* both trans/recv regs empty      (24, 14) */
DECL|macro|UART_DMAFULL_INT
mdefine_line|#define UART_DMAFULL_INT    1  /* DMA at end of buffer            (23, 13) */
DECL|macro|UART_DMAHALF_INT
mdefine_line|#define UART_DMAHALF_INT    0  /* DMA halfway through buffer */   (22, 12) */
DECL|macro|UARTA_SHIFT
mdefine_line|#define UARTA_SHIFT        22
DECL|macro|UARTB_SHIFT
mdefine_line|#define UARTB_SHIFT        12
DECL|macro|INTTYPE
mdefine_line|#define INTTYPE(interrupttype)            (1 &lt;&lt; interrupttype)
multiline_comment|/* &n; * This driver can spew a whole lot of debugging output at you. If you&n; * need maximum performance, you should disable the DEBUG define.&n; */
DECL|macro|TX3912_UART_DEBUG
macro_line|#undef TX3912_UART_DEBUG
macro_line|#ifdef TX3912_UART_DEBUG
DECL|macro|TX3912_UART_DEBUG_OPEN
mdefine_line|#define TX3912_UART_DEBUG_OPEN&t;&t;0x00000001
DECL|macro|TX3912_UART_DEBUG_SETTING
mdefine_line|#define TX3912_UART_DEBUG_SETTING&t;0x00000002
DECL|macro|TX3912_UART_DEBUG_FLOW
mdefine_line|#define TX3912_UART_DEBUG_FLOW&t;&t;0x00000004
DECL|macro|TX3912_UART_DEBUG_MODEMSIGNALS
mdefine_line|#define TX3912_UART_DEBUG_MODEMSIGNALS&t;0x00000008
DECL|macro|TX3912_UART_DEBUG_TERMIOS
mdefine_line|#define TX3912_UART_DEBUG_TERMIOS&t;0x00000010
DECL|macro|TX3912_UART_DEBUG_TRANSMIT
mdefine_line|#define TX3912_UART_DEBUG_TRANSMIT&t;0x00000020
DECL|macro|TX3912_UART_DEBUG_RECEIVE
mdefine_line|#define TX3912_UART_DEBUG_RECEIVE&t;0x00000040
DECL|macro|TX3912_UART_DEBUG_INTERRUPTS
mdefine_line|#define TX3912_UART_DEBUG_INTERRUPTS&t;0x00000080
DECL|macro|TX3912_UART_DEBUG_PROBE
mdefine_line|#define TX3912_UART_DEBUG_PROBE&t;&t;0x00000100
DECL|macro|TX3912_UART_DEBUG_INIT
mdefine_line|#define TX3912_UART_DEBUG_INIT&t;&t;0x00000200
DECL|macro|TX3912_UART_DEBUG_CLEANUP
mdefine_line|#define TX3912_UART_DEBUG_CLEANUP&t;0x00000400
DECL|macro|TX3912_UART_DEBUG_CLOSE
mdefine_line|#define TX3912_UART_DEBUG_CLOSE&t;&t;0x00000800
DECL|macro|TX3912_UART_DEBUG_FIRMWARE
mdefine_line|#define TX3912_UART_DEBUG_FIRMWARE&t;0x00001000
DECL|macro|TX3912_UART_DEBUG_MEMTEST
mdefine_line|#define TX3912_UART_DEBUG_MEMTEST&t;0x00002000
DECL|macro|TX3912_UART_DEBUG_THROTTLE
mdefine_line|#define TX3912_UART_DEBUG_THROTTLE&t;0x00004000
DECL|macro|TX3912_UART_DEBUG_ALL
mdefine_line|#define TX3912_UART_DEBUG_ALL&t;&t;0xffffffff
DECL|variable|rs_debug
r_int
id|rs_debug
op_assign
id|TX3912_UART_DEBUG_ALL
op_amp
op_complement
id|TX3912_UART_DEBUG_TRANSMIT
suffix:semicolon
DECL|macro|rs_dprintk
mdefine_line|#define rs_dprintk(f, str...) if (rs_debug &amp; f) printk (str)
DECL|macro|func_enter
mdefine_line|#define func_enter() rs_dprintk (TX3912_UART_DEBUG_FLOW,&t;&bslash;&n;&t;&t;&t;&t;&quot;rs: enter &quot; __FUNCTION__ &quot;&bslash;n&quot;)
DECL|macro|func_exit
mdefine_line|#define func_exit() rs_dprintk (TX3912_UART_DEBUG_FLOW,&t;&bslash;&n;&t;&t;&t;&t;&quot;rs: exit &quot; __FUNCTION__ &quot;&bslash;n&quot;)
macro_line|#else
DECL|macro|rs_dprintk
mdefine_line|#define rs_dprintk(f, str...)
DECL|macro|func_enter
mdefine_line|#define func_enter()
DECL|macro|func_exit
mdefine_line|#define func_exit()
macro_line|#endif&t;/* TX3912_UART_DEBUG */
multiline_comment|/*&n; * Number of serial ports&n; */
DECL|macro|TX3912_UART_NPORTS
mdefine_line|#define TX3912_UART_NPORTS  2
multiline_comment|/*&n; * Hardware specific serial port structure&n; */
DECL|struct|rs_port
r_struct
id|rs_port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
multiline_comment|/* Must be first field! */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|intshift
r_int
id|intshift
suffix:semicolon
multiline_comment|/* Register shift */
DECL|member|shutdown_wait
r_struct
id|wait_queue
op_star
id|shutdown_wait
suffix:semicolon
DECL|member|stat_flags
r_int
id|stat_flags
suffix:semicolon
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
multiline_comment|/* Counters for 4 input IRQs */
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* XON/XOFF character */
)brace
suffix:semicolon
eof
