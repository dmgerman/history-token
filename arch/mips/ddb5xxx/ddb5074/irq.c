multiline_comment|/*&n; *  arch/mips/ddb5074/irq.c -- NEC DDB Vrc-5074 interrupt routines&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq_cpu.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/nile4.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5074.h&gt;
r_extern
id|asmlinkage
r_void
id|ddbIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|irq_cascade
r_static
r_struct
id|irqaction
id|irq_cascade
op_assign
(brace
id|no_action
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|macro|M1543_PNP_CONFIG
mdefine_line|#define M1543_PNP_CONFIG&t;0x03f0&t;/* PnP Config Port */
DECL|macro|M1543_PNP_INDEX
mdefine_line|#define M1543_PNP_INDEX&t;&t;0x03f0&t;/* PnP Index Port */
DECL|macro|M1543_PNP_DATA
mdefine_line|#define M1543_PNP_DATA&t;&t;0x03f1&t;/* PnP Data Port */
DECL|macro|M1543_PNP_ALT_CONFIG
mdefine_line|#define M1543_PNP_ALT_CONFIG&t;0x0370&t;/* Alternative PnP Config Port */
DECL|macro|M1543_PNP_ALT_INDEX
mdefine_line|#define M1543_PNP_ALT_INDEX&t;0x0370&t;/* Alternative PnP Index Port */
DECL|macro|M1543_PNP_ALT_DATA
mdefine_line|#define M1543_PNP_ALT_DATA&t;0x0371&t;/* Alternative PnP Data Port */
DECL|macro|M1543_INT1_MASTER_CTRL
mdefine_line|#define M1543_INT1_MASTER_CTRL&t;0x0020&t;/* INT_1 (master) Control Register */
DECL|macro|M1543_INT1_MASTER_MASK
mdefine_line|#define M1543_INT1_MASTER_MASK&t;0x0021&t;/* INT_1 (master) Mask Register */
DECL|macro|M1543_INT1_SLAVE_CTRL
mdefine_line|#define M1543_INT1_SLAVE_CTRL&t;0x00a0&t;/* INT_1 (slave) Control Register */
DECL|macro|M1543_INT1_SLAVE_MASK
mdefine_line|#define M1543_INT1_SLAVE_MASK&t;0x00a1&t;/* INT_1 (slave) Mask Register */
DECL|macro|M1543_INT1_MASTER_ELCR
mdefine_line|#define M1543_INT1_MASTER_ELCR&t;0x04d0&t;/* INT_1 (master) Edge/Level Control */
DECL|macro|M1543_INT1_SLAVE_ELCR
mdefine_line|#define M1543_INT1_SLAVE_ELCR&t;0x04d1&t;/* INT_1 (slave) Edge/Level Control */
DECL|function|m1543_irq_setup
r_static
r_void
id|m1543_irq_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *  The ALI M1543 has 13 interrupt inputs, IRQ1..IRQ13.  Not all&n;&t; *  the possible IO sources in the M1543 are in use by us.  We will&n;&t; *  use the following mapping:&n;&t; *&n;&t; *      IRQ1  - keyboard (default set by M1543)&n;&t; *      IRQ3  - reserved for UART B (default set by M1543) (note that&n;&t; *              the schematics for the DDB Vrc-5074 board seem to&n;&t; *              indicate that IRQ3 is connected to the DS1386&n;&t; *              watchdog timer interrupt output so we might have&n;&t; *              a conflict)&n;&t; *      IRQ4  - reserved for UART A (default set by M1543)&n;&t; *      IRQ5  - parallel (default set by M1543)&n;&t; *      IRQ8  - DS1386 time of day (RTC) interrupt&n;&t; *      IRQ12 - mouse&n;&t; */
multiline_comment|/*&n;&t; *  Assing mouse interrupt to IRQ12&n;&t; */
multiline_comment|/* Enter configuration mode */
id|outb
c_func
(paren
l_int|0x51
comma
id|M1543_PNP_CONFIG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x23
comma
id|M1543_PNP_CONFIG
)paren
suffix:semicolon
multiline_comment|/* Select logical device 7 (Keyboard) */
id|outb
c_func
(paren
l_int|0x07
comma
id|M1543_PNP_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x07
comma
id|M1543_PNP_DATA
)paren
suffix:semicolon
multiline_comment|/* Select IRQ12 */
id|outb
c_func
(paren
l_int|0x72
comma
id|M1543_PNP_INDEX
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0c
comma
id|M1543_PNP_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x30
comma
id|M1543_PNP_INDEX
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;device 7, 0x30: %02x&bslash;n&quot;
comma
id|inb
c_func
(paren
id|M1543_PNP_DATA
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x70
comma
id|M1543_PNP_INDEX
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;device 7, 0x70: %02x&bslash;n&quot;
comma
id|inb
c_func
(paren
id|M1543_PNP_DATA
)paren
)paren
suffix:semicolon
multiline_comment|/* Leave configration mode */
id|outb
c_func
(paren
l_int|0xbb
comma
id|M1543_PNP_CONFIG
)paren
suffix:semicolon
)brace
DECL|function|ddb_local0_irqdispatch
r_void
id|ddb_local0_irqdispatch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|mask
suffix:semicolon
r_int
id|nile4_irq
suffix:semicolon
id|mask
op_assign
id|nile4_get_irq_stat
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Handle the timer interrupt first */
macro_line|#if 0
r_if
c_cond
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|NILE4_INT_GPT
)paren
)paren
(brace
id|do_IRQ
c_func
(paren
id|nile4_to_irq
c_func
(paren
id|NILE4_INT_GPT
)paren
comma
id|regs
)paren
suffix:semicolon
id|mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|NILE4_INT_GPT
)paren
suffix:semicolon
)brace
macro_line|#endif
r_for
c_loop
(paren
id|nile4_irq
op_assign
l_int|0
suffix:semicolon
id|mask
suffix:semicolon
id|nile4_irq
op_increment
comma
id|mask
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|nile4_irq
op_eq
id|NILE4_INT_INTE
)paren
(brace
r_int
id|i8259_irq
suffix:semicolon
id|nile4_clear_irq
c_func
(paren
id|NILE4_INT_INTE
)paren
suffix:semicolon
id|i8259_irq
op_assign
id|nile4_i8259_iack
c_func
(paren
)paren
suffix:semicolon
id|do_IRQ
c_func
(paren
id|i8259_irq
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
id|do_IRQ
c_func
(paren
id|nile4_to_irq
c_func
(paren
id|nile4_irq
)paren
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
DECL|function|ddb_local1_irqdispatch
r_void
id|ddb_local1_irqdispatch
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ddb_local1_irqdispatch called&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ddb_buserror_irq
r_void
id|ddb_buserror_irq
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ddb_buserror_irq called&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ddb_8254timer_irq
r_void
id|ddb_8254timer_irq
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ddb_8254timer_irq called&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ddb_irq_setup
r_void
id|__init
id|ddb_irq_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_KGDB
r_if
c_cond
(paren
id|remote_debug
)paren
id|set_debug_traps
c_func
(paren
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* you may move this line to whereever you want :-) */
macro_line|#endif
multiline_comment|/* setup cascade interrupts */
id|setup_irq
c_func
(paren
id|NILE4_IRQ_BASE
op_plus
id|NILE4_INT_INTE
comma
op_amp
id|irq_cascade
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|CPU_IRQ_BASE
op_plus
id|CPU_NILE4_CASCADE
comma
op_amp
id|irq_cascade
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|ddbIRQ
)paren
suffix:semicolon
id|nile4_irq_setup
c_func
(paren
id|NILE4_IRQ_BASE
)paren
suffix:semicolon
id|m1543_irq_setup
c_func
(paren
)paren
suffix:semicolon
id|init_i8259_irqs
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU_IRQ_BASE: %d&bslash;n&quot;
comma
id|CPU_IRQ_BASE
)paren
suffix:semicolon
id|mips_cpu_irq_init
c_func
(paren
id|CPU_IRQ_BASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;enabling 8259 cascade&bslash;n&quot;
)paren
suffix:semicolon
id|ddb5074_led_hex
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Enable the interrupt cascade */
id|nile4_enable_irq
c_func
(paren
id|NILE4_IRQ_BASE
op_plus
id|IRQ_I8259_CASCADE
)paren
suffix:semicolon
)brace
eof
