multiline_comment|/*&n; *  arch/mips/ddb5074/setup.c -- NEC DDB Vrc-5074 setup routines&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/nile4.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5074.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
DECL|variable|back_to_prom
r_static
r_void
(paren
op_star
id|back_to_prom
)paren
(paren
r_void
)paren
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
l_int|0xbfc00000
suffix:semicolon
DECL|function|ddb_machine_restart
r_static
r_void
id|ddb_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|u32
id|t
suffix:semicolon
multiline_comment|/* PCI cold reset */
id|t
op_assign
id|nile4_in32
c_func
(paren
id|NILE4_PCICTRL
op_plus
l_int|4
)paren
suffix:semicolon
id|t
op_or_assign
l_int|0x40000000
suffix:semicolon
id|nile4_out32
c_func
(paren
id|NILE4_PCICTRL
op_plus
l_int|4
comma
id|t
)paren
suffix:semicolon
multiline_comment|/* CPU cold reset */
id|t
op_assign
id|nile4_in32
c_func
(paren
id|NILE4_CPUSTAT
)paren
suffix:semicolon
id|t
op_or_assign
l_int|1
suffix:semicolon
id|nile4_out32
c_func
(paren
id|NILE4_CPUSTAT
comma
id|t
)paren
suffix:semicolon
multiline_comment|/* Call the PROM */
id|back_to_prom
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ddb_machine_halt
r_static
r_void
id|ddb_machine_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DDB Vrc-5074 halted.&bslash;n&quot;
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ddb_machine_power_off
r_static
r_void
id|ddb_machine_power_off
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DDB Vrc-5074 halted. Please turn off the power.&bslash;n&quot;
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_extern
r_void
id|rtc_ds1386_init
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|board_timer_setup
)paren
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
DECL|function|ddb_timer_init
r_static
r_void
id|__init
id|ddb_timer_init
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
multiline_comment|/* set the clock to 1 Hz */
id|nile4_out32
c_func
(paren
id|NILE4_T2CTRL
comma
l_int|1000000
)paren
suffix:semicolon
multiline_comment|/* enable the General-Purpose Timer */
id|nile4_out32
c_func
(paren
id|NILE4_T2CTRL
op_plus
l_int|4
comma
l_int|0x00000001
)paren
suffix:semicolon
multiline_comment|/* reset timer */
id|nile4_out32
c_func
(paren
id|NILE4_T2CNTR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* enable interrupt */
id|setup_irq
c_func
(paren
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_GPT
)paren
comma
id|irq
)paren
suffix:semicolon
id|nile4_enable_irq
c_func
(paren
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_GPT
)paren
)paren
suffix:semicolon
id|change_c0_status
c_func
(paren
id|ST0_IM
comma
id|IE_IRQ0
op_or
id|IE_IRQ1
op_or
id|IE_IRQ2
op_or
id|IE_IRQ3
op_or
id|IE_IRQ4
)paren
suffix:semicolon
)brace
DECL|function|ddb_time_init
r_static
r_void
id|__init
id|ddb_time_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we have ds1396 RTC chip */
id|rtc_ds1386_init
c_func
(paren
id|KSEG1ADDR
c_func
(paren
id|DDB_PCI_MEM_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|ddb5074_setup
r_static
r_void
id|__init
id|ddb5074_setup
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|panic_timeout
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|NILE4_PCI_IO_BASE
)paren
suffix:semicolon
id|isa_slot_offset
op_assign
id|NILE4_PCI_MEM_BASE
suffix:semicolon
id|board_timer_setup
op_assign
id|ddb_timer_init
suffix:semicolon
id|board_time_init
op_assign
id|ddb_time_init
suffix:semicolon
id|_machine_restart
op_assign
id|ddb_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|ddb_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|ddb_machine_power_off
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_BAR0
comma
l_int|0
)paren
suffix:semicolon
id|ddb_set_pmr
c_func
(paren
id|DDB_PCIINIT0
comma
id|DDB_PCICMD_IO
comma
l_int|0
comma
l_int|0x10
)paren
suffix:semicolon
id|ddb_set_pmr
c_func
(paren
id|DDB_PCIINIT1
comma
id|DDB_PCICMD_MEM
comma
id|DDB_PCI_MEM_BASE
comma
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* Reboot on panic */
id|panic_timeout
op_assign
l_int|180
suffix:semicolon
)brace
DECL|variable|ddb5074_setup
id|early_initcall
c_func
(paren
id|ddb5074_setup
)paren
suffix:semicolon
DECL|macro|USE_NILE4_SERIAL
mdefine_line|#define USE_NILE4_SERIAL&t;0
macro_line|#if USE_NILE4_SERIAL
DECL|macro|ns16550_in
mdefine_line|#define ns16550_in(reg)&t;&t;nile4_in8((reg)*8)
DECL|macro|ns16550_out
mdefine_line|#define ns16550_out(reg, val)&t;nile4_out8((reg)*8, (val))
macro_line|#else
DECL|macro|NS16550_BASE
mdefine_line|#define NS16550_BASE&t;&t;(NILE4_PCI_IO_BASE+0x03f8)
DECL|function|ns16550_in
r_static
r_inline
id|u8
id|ns16550_in
c_func
(paren
id|u32
id|reg
)paren
(brace
r_return
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|NS16550_BASE
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|ns16550_out
r_static
r_inline
r_void
id|ns16550_out
c_func
(paren
id|u32
id|reg
comma
id|u8
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|NS16550_BASE
op_plus
id|reg
)paren
op_assign
id|val
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|NS16550_RBR
mdefine_line|#define NS16550_RBR&t;&t;0
DECL|macro|NS16550_THR
mdefine_line|#define NS16550_THR&t;&t;0
DECL|macro|NS16550_DLL
mdefine_line|#define NS16550_DLL&t;&t;0
DECL|macro|NS16550_IER
mdefine_line|#define NS16550_IER&t;&t;1
DECL|macro|NS16550_DLM
mdefine_line|#define NS16550_DLM&t;&t;1
DECL|macro|NS16550_FCR
mdefine_line|#define NS16550_FCR&t;&t;2
DECL|macro|NS16550_IIR
mdefine_line|#define NS16550_IIR&t;&t;2
DECL|macro|NS16550_LCR
mdefine_line|#define NS16550_LCR&t;&t;3
DECL|macro|NS16550_MCR
mdefine_line|#define NS16550_MCR&t;&t;4
DECL|macro|NS16550_LSR
mdefine_line|#define NS16550_LSR&t;&t;5
DECL|macro|NS16550_MSR
mdefine_line|#define NS16550_MSR&t;&t;6
DECL|macro|NS16550_SCR
mdefine_line|#define NS16550_SCR&t;&t;7
DECL|macro|NS16550_LSR_DR
mdefine_line|#define NS16550_LSR_DR&t;&t;0x01&t;/* Data ready */
DECL|macro|NS16550_LSR_OE
mdefine_line|#define NS16550_LSR_OE&t;&t;0x02&t;/* Overrun */
DECL|macro|NS16550_LSR_PE
mdefine_line|#define NS16550_LSR_PE&t;&t;0x04&t;/* Parity error */
DECL|macro|NS16550_LSR_FE
mdefine_line|#define NS16550_LSR_FE&t;&t;0x08&t;/* Framing error */
DECL|macro|NS16550_LSR_BI
mdefine_line|#define NS16550_LSR_BI&t;&t;0x10&t;/* Break */
DECL|macro|NS16550_LSR_THRE
mdefine_line|#define NS16550_LSR_THRE&t;0x20&t;/* Xmit holding register empty */
DECL|macro|NS16550_LSR_TEMT
mdefine_line|#define NS16550_LSR_TEMT&t;0x40&t;/* Xmitter empty */
DECL|macro|NS16550_LSR_ERR
mdefine_line|#define NS16550_LSR_ERR&t;&t;0x80&t;/* Error */
DECL|function|_serinit
r_void
id|_serinit
c_func
(paren
r_void
)paren
(brace
macro_line|#if USE_NILE4_SERIAL
id|ns16550_out
c_func
(paren
id|NS16550_LCR
comma
l_int|0x80
)paren
suffix:semicolon
id|ns16550_out
c_func
(paren
id|NS16550_DLM
comma
l_int|0x00
)paren
suffix:semicolon
id|ns16550_out
c_func
(paren
id|NS16550_DLL
comma
l_int|0x36
)paren
suffix:semicolon
multiline_comment|/* 9600 baud */
id|ns16550_out
c_func
(paren
id|NS16550_LCR
comma
l_int|0x00
)paren
suffix:semicolon
id|ns16550_out
c_func
(paren
id|NS16550_LCR
comma
l_int|0x03
)paren
suffix:semicolon
id|ns16550_out
c_func
(paren
id|NS16550_FCR
comma
l_int|0x47
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* done by PMON */
macro_line|#endif
)brace
DECL|function|_putc
r_void
id|_putc
c_func
(paren
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|ns16550_in
c_func
(paren
id|NS16550_LSR
)paren
op_amp
id|NS16550_LSR_THRE
)paren
)paren
suffix:semicolon
id|ns16550_out
c_func
(paren
id|NS16550_THR
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|ns16550_in
c_func
(paren
id|NS16550_LSR
)paren
op_amp
id|NS16550_LSR_THRE
)paren
)paren
suffix:semicolon
id|ns16550_out
c_func
(paren
id|NS16550_THR
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|_puts
r_void
id|_puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_char
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
)paren
id|_putc
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|_getc
r_char
id|_getc
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|ns16550_in
c_func
(paren
id|NS16550_LSR
)paren
op_amp
id|NS16550_LSR_DR
)paren
)paren
suffix:semicolon
r_return
id|ns16550_in
c_func
(paren
id|NS16550_RBR
)paren
suffix:semicolon
)brace
DECL|function|_testc
r_int
id|_testc
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|ns16550_in
c_func
(paren
id|NS16550_LSR
)paren
op_amp
id|NS16550_LSR_DR
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Hexadecimal 7-segment LED&n; */
DECL|function|ddb5074_led_hex
r_void
id|ddb5074_led_hex
c_func
(paren
r_int
id|hex
)paren
(brace
id|outb
c_func
(paren
id|hex
comma
l_int|0x80
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  LEDs D2 and D3, connected to the GPIO pins of the PMU in the ALi M1543&n; */
DECL|variable|pci_pmu
r_struct
id|pci_dev
op_star
id|pci_pmu
op_assign
l_int|NULL
suffix:semicolon
DECL|function|ddb5074_led_d2
r_void
id|ddb5074_led_d2
c_func
(paren
r_int
id|on
)paren
(brace
id|u8
id|t
suffix:semicolon
r_if
c_cond
(paren
id|pci_pmu
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|pci_pmu
comma
l_int|0x7e
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|t
op_and_assign
l_int|0x7f
suffix:semicolon
r_else
id|t
op_or_assign
l_int|0x80
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pci_pmu
comma
l_int|0x7e
comma
id|t
)paren
suffix:semicolon
)brace
)brace
DECL|function|ddb5074_led_d3
r_void
id|ddb5074_led_d3
c_func
(paren
r_int
id|on
)paren
(brace
id|u8
id|t
suffix:semicolon
r_if
c_cond
(paren
id|pci_pmu
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|pci_pmu
comma
l_int|0x7e
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|t
op_and_assign
l_int|0xbf
suffix:semicolon
r_else
id|t
op_or_assign
l_int|0x40
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pci_pmu
comma
l_int|0x7e
comma
id|t
)paren
suffix:semicolon
)brace
)brace
eof
