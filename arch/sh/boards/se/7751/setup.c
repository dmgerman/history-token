multiline_comment|/* &n; * linux/arch/sh/kernel/setup_7751se.c&n; *&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * Hitachi SolutionEngine Support.&n; *&n; * Modified for 7751 Solution Engine by&n; * Ian da Silva and Jeremy Siegel, 2001.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/se7751/se7751.h&gt;
macro_line|#ifdef CONFIG_SH_KGDB
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Configure the Super I/O chip&n; */
macro_line|#if 0
multiline_comment|/* Leftover code from regular Solution Engine, for reference. */
multiline_comment|/* The SH7751 Solution Engine has a different SuperIO. */
r_static
r_void
id|__init
id|smsc_config
c_func
(paren
r_int
id|index
comma
r_int
id|data
)paren
(brace
id|outb_p
c_func
(paren
id|index
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
comma
id|DATA_PORT
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
id|init_smsc
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
id|CONFIG_ENTER
comma
id|CONFIG_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|CONFIG_ENTER
comma
id|CONFIG_PORT
)paren
suffix:semicolon
multiline_comment|/* FDC */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_FDC
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|6
)paren
suffix:semicolon
multiline_comment|/* IRQ6 */
multiline_comment|/* IDE1 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_IDE1
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|14
)paren
suffix:semicolon
multiline_comment|/* IRQ14 */
multiline_comment|/* AUXIO (GPIO): to use IDE1 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_AUXIO
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|GPIO46_INDEX
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* nIOROP */
id|smsc_config
c_func
(paren
id|GPIO47_INDEX
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* nIOWOP */
multiline_comment|/* COM1 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_COM1
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_HI_INDEX
comma
l_int|0x03
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_LO_INDEX
comma
l_int|0xf8
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* IRQ4 */
multiline_comment|/* COM2 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_COM2
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_HI_INDEX
comma
l_int|0x02
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_LO_INDEX
comma
l_int|0xf8
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* IRQ3 */
multiline_comment|/* RTC */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_RTC
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* IRQ8 */
multiline_comment|/* XXX: PARPORT, KBD, and MOUSE will come here... */
id|outb_p
c_func
(paren
id|CONFIG_EXIT
comma
id|CONFIG_PORT
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;7751 SolutionEngine&quot;
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SH_KGDB
r_static
r_int
id|kgdb_uart_setup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|kgdb_uart_sermap
r_static
r_struct
id|kgdb_sermap
id|kgdb_uart_sermap
op_assign
(brace
l_string|&quot;ttyS&quot;
comma
l_int|0
comma
id|kgdb_uart_setup
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|platform_setup
r_void
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Call init_smsc() replacement to set up SuperIO. */
multiline_comment|/* XXX: RTC setting comes here */
macro_line|#ifdef CONFIG_SH_KGDB
id|kgdb_register_sermap
c_func
(paren
op_amp
id|kgdb_uart_sermap
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*********************************************************************&n; * Currently a hack (e.g. does not interact well w/serial.c, lots of *&n; * hardcoded stuff) but may be useful if SCI/F needs debugging.      *&n; * Mostly copied from x86 code (see files asm-i386/kgdb_local.h and  *&n; * arch/i386/lib/kgdb_serial.c).                                     *&n; *********************************************************************/
macro_line|#ifdef CONFIG_SH_KGDB
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
DECL|macro|COM1_PORT
mdefine_line|#define COM1_PORT 0x3f8  /* Base I/O address */
DECL|macro|COM1_IRQ
mdefine_line|#define COM1_IRQ  4      /* IRQ not used yet */
DECL|macro|COM2_PORT
mdefine_line|#define COM2_PORT 0x2f8  /* Base I/O address */
DECL|macro|COM2_IRQ
mdefine_line|#define COM2_IRQ  3      /* IRQ not used yet */
DECL|macro|SB_CLOCK
mdefine_line|#define SB_CLOCK 1843200 /* Serial baud clock */
DECL|macro|SB_BASE
mdefine_line|#define SB_BASE (SB_CLOCK/16)
DECL|macro|SB_MCR
mdefine_line|#define SB_MCR UART_MCR_OUT2 | UART_MCR_DTR | UART_MCR_RTS
DECL|struct|uart_port
r_struct
id|uart_port
(brace
DECL|member|base
r_int
id|base
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UART_NPORTS
mdefine_line|#define UART_NPORTS 2
DECL|variable|uart_ports
r_struct
id|uart_port
id|uart_ports
(braket
)braket
op_assign
(brace
(brace
id|COM1_PORT
)brace
comma
(brace
id|COM2_PORT
)brace
comma
)brace
suffix:semicolon
DECL|variable|kgdb_uart_port
r_struct
id|uart_port
op_star
id|kgdb_uart_port
suffix:semicolon
DECL|macro|UART_IN
mdefine_line|#define UART_IN(reg)&t;inb_p(kgdb_uart_port-&gt;base + reg)
DECL|macro|UART_OUT
mdefine_line|#define UART_OUT(reg,v)&t;outb_p((v), kgdb_uart_port-&gt;base + reg)
multiline_comment|/* Basic read/write functions for the UART */
DECL|macro|UART_LSR_RXCERR
mdefine_line|#define UART_LSR_RXCERR    (UART_LSR_BI | UART_LSR_FE | UART_LSR_PE)
DECL|function|kgdb_uart_getchar
r_static
r_int
id|kgdb_uart_getchar
c_func
(paren
r_void
)paren
(brace
r_int
id|lsr
suffix:semicolon
r_int
id|c
op_assign
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|c
op_eq
op_minus
l_int|1
)paren
(brace
id|lsr
op_assign
id|UART_IN
c_func
(paren
id|UART_LSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsr
op_amp
id|UART_LSR_DR
)paren
id|c
op_assign
id|UART_IN
c_func
(paren
id|UART_RX
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lsr
op_amp
id|UART_LSR_RXCERR
)paren
)paren
id|c
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|c
suffix:semicolon
)brace
DECL|function|kgdb_uart_putchar
r_static
r_void
id|kgdb_uart_putchar
c_func
(paren
r_int
id|c
)paren
(brace
r_while
c_loop
(paren
(paren
id|UART_IN
c_func
(paren
id|UART_LSR
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|UART_OUT
c_func
(paren
id|UART_TX
comma
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize UART to configured/requested values.&n; * (But we don&squot;t interrupts yet, or interact w/serial.c)&n; */
DECL|function|kgdb_uart_setup
r_static
r_int
id|kgdb_uart_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|port
suffix:semicolon
r_int
id|lcr
op_assign
l_int|0
suffix:semicolon
r_int
id|bdiv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|kgdb_portnum
op_ge
id|UART_NPORTS
)paren
(brace
id|KGDB_PRINTK
c_func
(paren
l_string|&quot;uart port %d invalid.&bslash;n&quot;
comma
id|kgdb_portnum
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|kgdb_uart_port
op_assign
op_amp
id|uart_ports
(braket
id|kgdb_portnum
)braket
suffix:semicolon
multiline_comment|/* Init sequence from gdb_hook_interrupt */
id|UART_IN
c_func
(paren
id|UART_RX
)paren
suffix:semicolon
id|UART_OUT
c_func
(paren
id|UART_IER
comma
l_int|0
)paren
suffix:semicolon
id|UART_IN
c_func
(paren
id|UART_RX
)paren
suffix:semicolon
multiline_comment|/* Serial driver comments say */
id|UART_IN
c_func
(paren
id|UART_IIR
)paren
suffix:semicolon
multiline_comment|/* this clears interrupt regs */
id|UART_IN
c_func
(paren
id|UART_MSR
)paren
suffix:semicolon
multiline_comment|/* Figure basic LCR values */
r_switch
c_cond
(paren
id|kgdb_bits
)paren
(brace
r_case
l_char|&squot;7&squot;
suffix:colon
id|lcr
op_or_assign
id|UART_LCR_WLEN7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
l_char|&squot;8&squot;
suffix:colon
id|lcr
op_or_assign
id|UART_LCR_WLEN8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|kgdb_parity
)paren
(brace
r_case
l_char|&squot;O&squot;
suffix:colon
id|lcr
op_or_assign
id|UART_LCR_PARITY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;E&squot;
suffix:colon
id|lcr
op_or_assign
(paren
id|UART_LCR_PARITY
op_or
id|UART_LCR_EPAR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Figure the baud rate divisor */
id|bdiv
op_assign
(paren
id|SB_BASE
op_div
id|kgdb_baud
)paren
suffix:semicolon
multiline_comment|/* Set the baud rate and LCR values */
id|UART_OUT
c_func
(paren
id|UART_LCR
comma
(paren
id|lcr
op_or
id|UART_LCR_DLAB
)paren
)paren
suffix:semicolon
id|UART_OUT
c_func
(paren
id|UART_DLL
comma
(paren
id|bdiv
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|UART_OUT
c_func
(paren
id|UART_DLM
comma
(paren
(paren
id|bdiv
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|UART_OUT
c_func
(paren
id|UART_LCR
comma
id|lcr
)paren
suffix:semicolon
multiline_comment|/* Set the MCR */
id|UART_OUT
c_func
(paren
id|UART_MCR
comma
id|SB_MCR
)paren
suffix:semicolon
multiline_comment|/* Turn off FIFOs for now */
id|UART_OUT
c_func
(paren
id|UART_FCR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Setup complete: initialize function pointers */
id|kgdb_getchar
op_assign
id|kgdb_uart_getchar
suffix:semicolon
id|kgdb_putchar
op_assign
id|kgdb_uart_putchar
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SH_KGDB */
eof
