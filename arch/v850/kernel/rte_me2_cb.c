multiline_comment|/*&n; * arch/v850/kernel/rte_me2_cb.c -- Midas labs RTE-V850E/ME2-CB board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/me2.h&gt;
macro_line|#include &lt;asm/rte_me2_cb.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/v850e_intc.h&gt;
macro_line|#include &lt;asm/v850e_cache.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;mach.h&quot;
r_extern
r_int
r_int
op_star
id|_intv_start
suffix:semicolon
r_extern
r_int
r_int
op_star
id|_intv_end
suffix:semicolon
multiline_comment|/* LED access routines.  */
r_extern
r_int
id|read_leds
(paren
r_int
id|pos
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|write_leds
(paren
r_int
id|pos
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* SDRAM are almost contiguous (with a small hole in between;&n;   see mach_reserve_bootmem for details), so just use both as one big area.  */
DECL|macro|RAM_START
mdefine_line|#define RAM_START &t;SDRAM_ADDR
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(SDRAM_ADDR + SDRAM_SIZE)
DECL|function|mach_get_physical_ram
r_void
id|__init
id|mach_get_physical_ram
(paren
r_int
r_int
op_star
id|ram_start
comma
r_int
r_int
op_star
id|ram_len
)paren
(brace
op_star
id|ram_start
op_assign
id|RAM_START
suffix:semicolon
op_star
id|ram_len
op_assign
id|RAM_END
op_minus
id|RAM_START
suffix:semicolon
)brace
DECL|function|mach_gettimeofday
r_void
id|mach_gettimeofday
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
id|tv-&gt;tv_sec
op_assign
l_int|0
suffix:semicolon
id|tv-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called before configuring an on-chip UART.  */
DECL|function|rte_me2_cb_uart_pre_configure
r_void
id|rte_me2_cb_uart_pre_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
(brace
multiline_comment|/* The RTE-V850E/ME2-CB connects some general-purpose I/O&n;&t;   pins on the CPU to the RTS/CTS lines of UARTB channel 0&squot;s&n;&t;   serial connection.&n;&t;   I/O pins P21 and P22 are RTS and CTS respectively.  */
r_if
c_cond
(paren
id|chan
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Put P21 &amp; P22 in I/O port mode.  */
id|ME2_PORT2_PMC
op_and_assign
op_complement
l_int|0x6
suffix:semicolon
multiline_comment|/* Make P21 and output, and P22 an input.  */
id|ME2_PORT2_PM
op_assign
(paren
id|ME2_PORT2_PM
op_amp
op_complement
l_int|0xC
)paren
op_or
l_int|0x4
suffix:semicolon
)brace
id|me2_uart_pre_configure
(paren
id|chan
comma
id|cflags
comma
id|baud
)paren
suffix:semicolon
)brace
DECL|function|mach_init_irqs
r_void
id|__init
id|mach_init_irqs
(paren
r_void
)paren
(brace
multiline_comment|/* Initialize interrupts.  */
id|me2_init_irqs
(paren
)paren
suffix:semicolon
id|rte_me2_cb_init_irqs
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ROM_KERNEL
multiline_comment|/* Initialization for kernel in ROM.  */
DECL|function|rom_kernel_init
r_static
r_inline
id|rom_kernel_init
(paren
r_void
)paren
(brace
multiline_comment|/* If the kernel is in ROM, we have to copy any initialized data&n;&t;   from ROM into RAM.  */
r_extern
r_int
r_int
id|_data_load_start
comma
id|_sdata
comma
id|_edata
suffix:semicolon
r_register
r_int
r_int
op_star
id|src
op_assign
op_amp
id|_data_load_start
suffix:semicolon
r_register
r_int
r_int
op_star
id|dst
op_assign
op_amp
id|_sdata
comma
op_star
id|end
op_assign
op_amp
id|_edata
suffix:semicolon
r_while
c_loop
(paren
id|dst
op_ne
id|end
)paren
op_star
id|dst
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ROM_KERNEL */
DECL|function|install_interrupt_vectors
r_static
r_void
id|install_interrupt_vectors
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|p1
comma
op_star
id|p2
suffix:semicolon
id|ME2_IRAMM
op_assign
l_int|0x03
suffix:semicolon
multiline_comment|/* V850E/ME2 iRAM write mode */
multiline_comment|/* vector copy to iRAM */
id|p1
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0
suffix:semicolon
multiline_comment|/* v85x vector start */
id|p2
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|_intv_start
suffix:semicolon
r_while
c_loop
(paren
id|p2
OL
(paren
r_int
r_int
op_star
)paren
op_amp
id|_intv_end
)paren
op_star
id|p1
op_increment
op_assign
op_star
id|p2
op_increment
suffix:semicolon
id|ME2_IRAMM
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* V850E/ME2 iRAM read mode */
)brace
"&f;"
multiline_comment|/* CompactFlash */
DECL|function|cf_power_on
r_static
r_void
id|cf_power_on
(paren
r_void
)paren
(brace
multiline_comment|/* CF card detected? */
r_if
c_cond
(paren
id|CB_CF_STS0
op_amp
l_int|0x0030
)paren
r_return
suffix:semicolon
id|CB_CF_REG0
op_assign
l_int|0x0002
suffix:semicolon
multiline_comment|/* reest on */
id|mdelay
(paren
l_int|10
)paren
suffix:semicolon
id|CB_CF_REG0
op_assign
l_int|0x0003
suffix:semicolon
multiline_comment|/* power on */
id|mdelay
(paren
l_int|10
)paren
suffix:semicolon
id|CB_CF_REG0
op_assign
l_int|0x0001
suffix:semicolon
multiline_comment|/* reset off */
id|mdelay
(paren
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|cf_power_off
r_static
r_void
id|cf_power_off
(paren
r_void
)paren
(brace
id|CB_CF_REG0
op_assign
l_int|0x0003
suffix:semicolon
multiline_comment|/* power on */
id|mdelay
(paren
l_int|10
)paren
suffix:semicolon
id|CB_CF_REG0
op_assign
l_int|0x0002
suffix:semicolon
multiline_comment|/* reest on */
id|mdelay
(paren
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
id|install_interrupt_vectors
(paren
)paren
suffix:semicolon
multiline_comment|/* CS1 SDRAM instruction cache enable */
id|v850e_cache_enable
(paren
l_int|0x04
comma
l_int|0x03
comma
l_int|0
)paren
suffix:semicolon
id|rte_cb_early_init
(paren
)paren
suffix:semicolon
multiline_comment|/* CompactFlash power on */
id|cf_power_on
(paren
)paren
suffix:semicolon
macro_line|#if defined (CONFIG_ROM_KERNEL)
id|rom_kernel_init
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
"&f;"
multiline_comment|/* RTE-V850E/ME2-CB Programmable Interrupt Controller.  */
DECL|variable|cb_pic_irq_inits
r_static
r_struct
id|cb_pic_irq_init
id|cb_pic_irq_inits
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;CB_EXTTM0&quot;
comma
id|IRQ_CB_EXTTM0
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_EXTSIO&quot;
comma
id|IRQ_CB_EXTSIO
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_TOVER&quot;
comma
id|IRQ_CB_TOVER
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_GINT0&quot;
comma
id|IRQ_CB_GINT0
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_USB&quot;
comma
id|IRQ_CB_USB
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_LANC&quot;
comma
id|IRQ_CB_LANC
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_USB_VBUS_ON&quot;
comma
id|IRQ_CB_USB_VBUS_ON
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_USB_VBUS_OFF&quot;
comma
id|IRQ_CB_USB_VBUS_OFF
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_EXTTM1&quot;
comma
id|IRQ_CB_EXTTM1
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_string|&quot;CB_EXTTM2&quot;
comma
id|IRQ_CB_EXTTM2
comma
l_int|1
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NUM_CB_PIC_IRQ_INITS
mdefine_line|#define NUM_CB_PIC_IRQ_INITS  &bslash;&n;   ((sizeof cb_pic_irq_inits / sizeof cb_pic_irq_inits[0]) - 1)
DECL|variable|cb_pic_hw_itypes
r_static
r_struct
id|hw_interrupt_type
id|cb_pic_hw_itypes
(braket
id|NUM_CB_PIC_IRQ_INITS
)braket
suffix:semicolon
DECL|variable|cb_pic_active_irqs
r_static
r_int
r_char
id|cb_pic_active_irqs
op_assign
l_int|0
suffix:semicolon
DECL|function|rte_me2_cb_init_irqs
r_void
id|__init
id|rte_me2_cb_init_irqs
(paren
r_void
)paren
(brace
id|cb_pic_init_irq_types
(paren
id|cb_pic_irq_inits
comma
id|cb_pic_hw_itypes
)paren
suffix:semicolon
multiline_comment|/* Initalize on board PIC1 (not PIC0) enable */
id|CB_PIC_INT0M
op_assign
l_int|0x0000
suffix:semicolon
id|CB_PIC_INT1M
op_assign
l_int|0x0000
suffix:semicolon
id|CB_PIC_INTR
op_assign
l_int|0x0000
suffix:semicolon
id|CB_PIC_INTEN
op_or_assign
id|CB_PIC_INT1EN
suffix:semicolon
id|ME2_PORT2_PMC
op_or_assign
l_int|0x08
suffix:semicolon
multiline_comment|/* INTP23/SCK1 mode */
id|ME2_PORT2_PFC
op_and_assign
op_complement
l_int|0x08
suffix:semicolon
multiline_comment|/* INTP23 mode */
id|ME2_INTR
c_func
(paren
l_int|2
)paren
op_and_assign
op_complement
l_int|0x08
suffix:semicolon
multiline_comment|/* INTP23 falling-edge detect */
id|ME2_INTF
c_func
(paren
l_int|2
)paren
op_and_assign
op_complement
l_int|0x08
suffix:semicolon
multiline_comment|/*   &quot; */
id|rte_cb_init_irqs
(paren
)paren
suffix:semicolon
multiline_comment|/* gbus &amp;c */
)brace
multiline_comment|/* Enable interrupt handling for interrupt IRQ.  */
DECL|function|cb_pic_enable_irq
r_void
id|cb_pic_enable_irq
(paren
r_int
id|irq
)paren
(brace
id|CB_PIC_INT1M
op_or_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|CB_PIC_BASE_IRQ
)paren
suffix:semicolon
)brace
DECL|function|cb_pic_disable_irq
r_void
id|cb_pic_disable_irq
(paren
r_int
id|irq
)paren
(brace
id|CB_PIC_INT1M
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|CB_PIC_BASE_IRQ
)paren
)paren
suffix:semicolon
)brace
DECL|function|cb_pic_shutdown_irq
r_void
id|cb_pic_shutdown_irq
(paren
r_int
id|irq
)paren
(brace
id|cb_pic_disable_irq
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|cb_pic_active_irqs
op_eq
l_int|0
)paren
id|free_irq
(paren
id|IRQ_CB_PIC
comma
l_int|0
)paren
suffix:semicolon
id|CB_PIC_INT1M
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|CB_PIC_BASE_IRQ
)paren
)paren
suffix:semicolon
)brace
DECL|function|cb_pic_handle_irq
r_static
id|irqreturn_t
id|cb_pic_handle_irq
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|irqreturn_t
id|rval
op_assign
id|IRQ_NONE
suffix:semicolon
r_int
id|status
op_assign
id|CB_PIC_INTR
suffix:semicolon
r_int
id|enable
op_assign
id|CB_PIC_INT1M
suffix:semicolon
multiline_comment|/* Only pay attention to enabled interrupts.  */
id|status
op_and_assign
id|enable
suffix:semicolon
id|CB_PIC_INTEN
op_and_assign
op_complement
id|CB_PIC_INT1EN
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_int
id|mask
op_assign
l_int|1
suffix:semicolon
id|irq
op_assign
id|CB_PIC_BASE_IRQ
suffix:semicolon
r_do
(brace
multiline_comment|/* There&squot;s an active interrupt, find out which one,&n;&t;&t;&t;   and call its handler.  */
r_while
c_loop
(paren
op_logical_neg
(paren
id|status
op_amp
id|mask
)paren
)paren
(brace
id|irq
op_increment
suffix:semicolon
id|mask
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
id|mask
suffix:semicolon
id|CB_PIC_INTR
op_assign
id|mask
suffix:semicolon
multiline_comment|/* Recursively call handle_irq to handle it. */
id|handle_irq
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
id|rval
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
)paren
suffix:semicolon
)brace
id|CB_PIC_INTEN
op_or_assign
id|CB_PIC_INT1EN
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
"&f;"
DECL|function|irq_nop
r_static
r_void
id|irq_nop
(paren
r_int
id|irq
)paren
(brace
)brace
DECL|function|cb_pic_startup_irq
r_static
r_int
id|cb_pic_startup_irq
(paren
r_int
id|irq
)paren
(brace
r_int
id|rval
suffix:semicolon
r_if
c_cond
(paren
id|cb_pic_active_irqs
op_eq
l_int|0
)paren
(brace
id|rval
op_assign
id|request_irq
(paren
id|IRQ_CB_PIC
comma
id|cb_pic_handle_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;cb_pic_handler&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rval
op_ne
l_int|0
)paren
r_return
id|rval
suffix:semicolon
)brace
id|cb_pic_active_irqs
op_increment
suffix:semicolon
id|cb_pic_enable_irq
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize HW_IRQ_TYPES for INTC-controlled irqs described in array&n;   INITS (which is terminated by an entry with the name field == 0).  */
DECL|function|cb_pic_init_irq_types
r_void
id|__init
id|cb_pic_init_irq_types
(paren
r_struct
id|cb_pic_irq_init
op_star
id|inits
comma
r_struct
id|hw_interrupt_type
op_star
id|hw_irq_types
)paren
(brace
r_struct
id|cb_pic_irq_init
op_star
id|init
suffix:semicolon
r_for
c_loop
(paren
id|init
op_assign
id|inits
suffix:semicolon
id|init-&gt;name
suffix:semicolon
id|init
op_increment
)paren
(brace
r_struct
id|hw_interrupt_type
op_star
id|hwit
op_assign
id|hw_irq_types
op_increment
suffix:semicolon
id|hwit
op_member_access_from_pointer
r_typename
op_assign
id|init-&gt;name
suffix:semicolon
id|hwit-&gt;startup
op_assign
id|cb_pic_startup_irq
suffix:semicolon
id|hwit-&gt;shutdown
op_assign
id|cb_pic_shutdown_irq
suffix:semicolon
id|hwit-&gt;enable
op_assign
id|cb_pic_enable_irq
suffix:semicolon
id|hwit-&gt;disable
op_assign
id|cb_pic_disable_irq
suffix:semicolon
id|hwit-&gt;ack
op_assign
id|irq_nop
suffix:semicolon
id|hwit-&gt;end
op_assign
id|irq_nop
suffix:semicolon
multiline_comment|/* Initialize kernel IRQ infrastructure for this interrupt.  */
id|init_irq_handlers
c_func
(paren
id|init-&gt;base
comma
id|init-&gt;num
comma
id|init-&gt;interval
comma
id|hwit
)paren
suffix:semicolon
)brace
)brace
eof
