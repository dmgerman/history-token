multiline_comment|/*&n; * arch/v850/kernel/anna.c -- Anna V850E2 evaluation chip/board&n; *&n; *  Copyright (C) 2002  NEC Corporation&n; *  Copyright (C) 2002  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/nb85e_timer_d.h&gt;
macro_line|#include &lt;asm/nb85e_uart.h&gt;
macro_line|#include &quot;mach.h&quot;
multiline_comment|/* SRAM and SDRAM are vaguely contiguous (with a hole in between; see&n;   mach_reserve_bootmem for details), so just use both as one big area.  */
DECL|macro|RAM_START
mdefine_line|#define RAM_START &t;SRAM_ADDR
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(SDRAM_ADDR + SDRAM_SIZE)
r_static
r_void
id|anna_led_tick
(paren
r_void
)paren
suffix:semicolon
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
id|ANNA_ILBEN
op_assign
l_int|0
suffix:semicolon
id|ANNA_CSC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0x402F
suffix:semicolon
id|ANNA_CSC
c_func
(paren
l_int|1
)paren
op_assign
l_int|0x4000
suffix:semicolon
id|ANNA_BPC
op_assign
l_int|0
suffix:semicolon
id|ANNA_BSC
op_assign
l_int|0xAAAA
suffix:semicolon
id|ANNA_BEC
op_assign
l_int|0
suffix:semicolon
id|ANNA_BHC
op_assign
l_int|0x00FF
suffix:semicolon
multiline_comment|/* icache all memory, dcache none */
id|ANNA_BCT
c_func
(paren
l_int|0
)paren
op_assign
l_int|0xB088
suffix:semicolon
id|ANNA_BCT
c_func
(paren
l_int|1
)paren
op_assign
l_int|0x0008
suffix:semicolon
id|ANNA_DWC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0x0027
suffix:semicolon
id|ANNA_DWC
c_func
(paren
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
id|ANNA_BCC
op_assign
l_int|0x0006
suffix:semicolon
id|ANNA_ASC
op_assign
l_int|0
suffix:semicolon
id|ANNA_LBS
op_assign
l_int|0x0089
suffix:semicolon
id|ANNA_SCR3
op_assign
l_int|0x21A9
suffix:semicolon
id|ANNA_RFS3
op_assign
l_int|0x8121
suffix:semicolon
id|nb85e_intc_disable_irqs
(paren
)paren
suffix:semicolon
)brace
DECL|function|mach_setup
r_void
id|__init
id|mach_setup
(paren
r_char
op_star
op_star
id|cmdline
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: %s&bslash;n&quot;
l_string|&quot;Platform: %s&bslash;n&quot;
comma
id|CPU_MODEL_LONG
comma
id|PLATFORM_LONG
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_V850E_NB85E_UART_CONSOLE
id|nb85e_uart_cons_init
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|ANNA_PORT_PM
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Make all LED pins output pins.  */
id|mach_tick
op_assign
id|anna_led_tick
suffix:semicolon
)brace
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
DECL|function|mach_reserve_bootmem
r_void
id|__init
id|mach_reserve_bootmem
(paren
)paren
(brace
multiline_comment|/* The space between SRAM and SDRAM is filled with duplicate&n;&t;   images of SRAM.  Prevent the kernel from using them.  */
id|reserve_bootmem
(paren
id|SRAM_ADDR
op_plus
id|SRAM_SIZE
comma
id|SDRAM_ADDR
op_minus
(paren
id|SRAM_ADDR
op_plus
id|SRAM_SIZE
)paren
)paren
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
DECL|function|mach_sched_init
r_void
id|__init
id|mach_sched_init
(paren
r_struct
id|irqaction
op_star
id|timer_action
)paren
(brace
multiline_comment|/* Start hardware timer.  */
id|nb85e_timer_d_configure
(paren
l_int|0
comma
id|HZ
)paren
suffix:semicolon
multiline_comment|/* Install timer interrupt handler.  */
id|setup_irq
(paren
id|IRQ_INTCMD
c_func
(paren
l_int|0
)paren
comma
id|timer_action
)paren
suffix:semicolon
)brace
DECL|variable|irq_inits
r_static
r_struct
id|nb85e_intc_irq_init
id|irq_inits
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;IRQ&quot;
comma
l_int|0
comma
id|NUM_MACH_IRQS
comma
l_int|1
comma
l_int|7
)brace
comma
(brace
l_string|&quot;PIN&quot;
comma
id|IRQ_INTP
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTP_NUM
comma
l_int|1
comma
l_int|4
)brace
comma
(brace
l_string|&quot;CCC&quot;
comma
id|IRQ_INTCCC
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTCCC_NUM
comma
l_int|1
comma
l_int|5
)brace
comma
(brace
l_string|&quot;CMD&quot;
comma
id|IRQ_INTCMD
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTCMD_NUM
comma
l_int|1
comma
l_int|5
)brace
comma
(brace
l_string|&quot;DMA&quot;
comma
id|IRQ_INTDMA
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTDMA_NUM
comma
l_int|1
comma
l_int|2
)brace
comma
(brace
l_string|&quot;DMXER&quot;
comma
id|IRQ_INTDMXER
comma
l_int|1
comma
l_int|1
comma
l_int|2
)brace
comma
(brace
l_string|&quot;SRE&quot;
comma
id|IRQ_INTSRE
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTSRE_NUM
comma
l_int|3
comma
l_int|3
)brace
comma
(brace
l_string|&quot;SR&quot;
comma
id|IRQ_INTSR
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTSR_NUM
comma
l_int|3
comma
l_int|4
)brace
comma
(brace
l_string|&quot;ST&quot;
comma
id|IRQ_INTST
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTST_NUM
comma
l_int|3
comma
l_int|5
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NUM_IRQ_INITS
mdefine_line|#define NUM_IRQ_INITS ((sizeof irq_inits / sizeof irq_inits[0]) - 1)
DECL|variable|hw_itypes
r_static
r_struct
id|hw_interrupt_type
id|hw_itypes
(braket
id|NUM_IRQ_INITS
)braket
suffix:semicolon
DECL|function|mach_init_irqs
r_void
id|__init
id|mach_init_irqs
(paren
r_void
)paren
(brace
id|nb85e_intc_init_irq_types
(paren
id|irq_inits
comma
id|hw_itypes
)paren
suffix:semicolon
)brace
DECL|function|machine_restart
r_void
id|machine_restart
(paren
r_char
op_star
id|__unused
)paren
(brace
macro_line|#ifdef CONFIG_RESET_GUARD
id|disable_reset_guard
(paren
)paren
suffix:semicolon
macro_line|#endif
id|asm
(paren
l_string|&quot;jmp r0&quot;
)paren
suffix:semicolon
multiline_comment|/* Jump to the reset vector.  */
)brace
DECL|function|machine_halt
r_void
id|machine_halt
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_RESET_GUARD
id|disable_reset_guard
(paren
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_disable
(paren
)paren
suffix:semicolon
multiline_comment|/* Ignore all interrupts.  */
id|ANNA_PORT_IO
c_func
(paren
l_int|0
)paren
op_assign
l_int|0xAA
suffix:semicolon
multiline_comment|/* Note that we halted.  */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|asm
(paren
l_string|&quot;halt; nop; nop; nop; nop; nop&quot;
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
(paren
r_void
)paren
(brace
id|machine_halt
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Called before configuring an on-chip UART.  */
DECL|function|anna_uart_pre_configure
r_void
id|anna_uart_pre_configure
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
multiline_comment|/* The Anna connects some general-purpose I/O pins on the CPU to&n;&t;   the RTS/CTS lines of UART 1&squot;s serial connection.  I/O pins P07&n;&t;   and P37 are RTS and CTS respectively.  */
r_if
c_cond
(paren
id|chan
op_eq
l_int|1
)paren
(brace
id|ANNA_PORT_PM
c_func
(paren
l_int|0
)paren
op_and_assign
op_complement
l_int|0x80
suffix:semicolon
multiline_comment|/* P07 in output mode */
id|ANNA_PORT_PM
c_func
(paren
l_int|3
)paren
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* P37 in input mode */
)brace
)brace
multiline_comment|/* Minimum and maximum bounds for the moving upper LED boundary in the&n;   clock tick display.  We can&squot;t use the last bit because it&squot;s used for&n;   UART0&squot;s CTS output.  */
DECL|macro|MIN_MAX_POS
mdefine_line|#define MIN_MAX_POS 0
DECL|macro|MAX_MAX_POS
mdefine_line|#define MAX_MAX_POS 6
multiline_comment|/* There are MAX_MAX_POS^2 - MIN_MAX_POS^2 cycles in the animation, so if&n;   we pick 6 and 0 as above, we get 49 cycles, which is when divided into&n;   the standard 100 value for HZ, gives us an almost 1s total time.  */
DECL|macro|TICKS_PER_FRAME
mdefine_line|#define TICKS_PER_FRAME &bslash;&n;&t;(HZ / (MAX_MAX_POS * MAX_MAX_POS - MIN_MAX_POS * MIN_MAX_POS))
DECL|function|anna_led_tick
r_static
r_void
id|anna_led_tick
(paren
)paren
(brace
r_static
r_int
id|counter
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|counter
op_eq
id|TICKS_PER_FRAME
)paren
(brace
r_static
r_int
id|pos
op_assign
l_int|0
comma
id|max_pos
op_assign
id|MAX_MAX_POS
comma
id|dir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dir
OG
l_int|0
op_logical_and
id|pos
op_eq
id|max_pos
)paren
(brace
id|dir
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|max_pos
op_eq
id|MIN_MAX_POS
)paren
id|max_pos
op_assign
id|MAX_MAX_POS
suffix:semicolon
r_else
id|max_pos
op_decrement
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dir
OL
l_int|0
op_logical_and
id|pos
op_eq
l_int|0
)paren
id|dir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|dir
op_le
id|max_pos
)paren
(brace
multiline_comment|/* Each bit of port 0 has a LED. */
id|clear_bit
(paren
id|pos
comma
op_amp
id|ANNA_PORT_IO
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|pos
op_add_assign
id|dir
suffix:semicolon
id|set_bit
(paren
id|pos
comma
op_amp
id|ANNA_PORT_IO
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
id|counter
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
