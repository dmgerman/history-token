multiline_comment|/*&n; * arch/v850/kernel/as85ep1.c -- AS85EP1 V850E evaluation chip/board&n; *&n; *  Copyright (C) 2002,03  NEC Electronics Corporation&n; *  Copyright (C) 2002,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/v850e_timer_d.h&gt;
macro_line|#include &lt;asm/v850e_uart.h&gt;
macro_line|#include &quot;mach.h&quot;
multiline_comment|/* SRAM and SDRAM are vaguely contiguous (with a big hole in between; see&n;   mach_reserve_bootmem for details); use both as one big area.  */
DECL|macro|RAM_START
mdefine_line|#define RAM_START &t;SRAM_ADDR
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(SDRAM_ADDR + SDRAM_SIZE)
multiline_comment|/* The bits of this port are connected to an 8-LED bar-graph.  */
DECL|macro|LEDS_PORT
mdefine_line|#define LEDS_PORT&t;4
r_static
r_void
id|as85ep1_led_tick
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
id|_intv_copy_src_start
comma
id|_intv_copy_src_end
suffix:semicolon
r_extern
r_char
id|_intv_copy_dst_start
suffix:semicolon
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_ROM_KERNEL
r_const
id|u32
op_star
id|src
suffix:semicolon
r_register
id|u32
op_star
id|dst
id|asm
(paren
l_string|&quot;ep&quot;
)paren
suffix:semicolon
macro_line|#endif
id|AS85EP1_CSC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0x0403
suffix:semicolon
id|AS85EP1_BCT
c_func
(paren
l_int|0
)paren
op_assign
l_int|0xB8B8
suffix:semicolon
id|AS85EP1_DWC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0x0104
suffix:semicolon
id|AS85EP1_BCC
op_assign
l_int|0x0012
suffix:semicolon
id|AS85EP1_ASC
op_assign
l_int|0
suffix:semicolon
id|AS85EP1_LBS
op_assign
l_int|0x00A9
suffix:semicolon
id|AS85EP1_PORT_PMC
c_func
(paren
l_int|6
)paren
op_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/* A20-25, A0,A1 &#x1b;$BM-8z&#x1b;(B */
id|AS85EP1_PORT_PMC
c_func
(paren
l_int|7
)paren
op_assign
l_int|0x0E
suffix:semicolon
multiline_comment|/* CS1,2,3       &#x1b;$BM-8z&#x1b;(B */
id|AS85EP1_PORT_PMC
c_func
(paren
l_int|9
)paren
op_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/* D16-23        &#x1b;$BM-8z&#x1b;(B */
id|AS85EP1_PORT_PMC
c_func
(paren
l_int|10
)paren
op_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/* D24-31        &#x1b;$BM-8z&#x1b;(B */
id|AS85EP1_RFS
c_func
(paren
l_int|1
)paren
op_assign
l_int|0x800c
suffix:semicolon
id|AS85EP1_RFS
c_func
(paren
l_int|3
)paren
op_assign
l_int|0x800c
suffix:semicolon
id|AS85EP1_SCR
c_func
(paren
l_int|1
)paren
op_assign
l_int|0x20A9
suffix:semicolon
id|AS85EP1_SCR
c_func
(paren
l_int|3
)paren
op_assign
l_int|0x20A9
suffix:semicolon
macro_line|#ifndef CONFIG_ROM_KERNEL
multiline_comment|/* The early chip we have is buggy, and writing the interrupt&n;&t;   vectors into low RAM may screw up, so for non-ROM kernels, we&n;&t;   only rely on the reset vector being downloaded, and copy the&n;&t;   rest of the interrupt vectors into place here.  The specific bug&n;&t;   is that writing address N, where (N &amp; 0x10) == 0x10, will _also_&n;&t;   write to address (N - 0x10).  We avoid this (effectively) by&n;&t;   writing in 16-byte chunks backwards from the end.  */
id|AS85EP1_IRAMM
op_assign
l_int|0x3
suffix:semicolon
multiline_comment|/* &#x1b;$BFbB&quot;L?Na&#x1b;(BRAM&#x1b;$B$O!V&#x1b;(Bwrite-mode&#x1b;$B!W$K$J$j$^$9&#x1b;(B */
id|src
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
(paren
id|u32
)paren
op_amp
id|_intv_copy_src_end
op_minus
l_int|1
)paren
op_amp
op_complement
l_int|0xF
)paren
suffix:semicolon
id|dst
op_assign
(paren
id|u32
op_star
)paren
op_amp
id|_intv_copy_dst_start
op_plus
(paren
id|src
op_minus
(paren
id|u32
op_star
)paren
op_amp
id|_intv_copy_src_start
)paren
suffix:semicolon
r_do
(brace
id|u32
id|t0
op_assign
id|src
(braket
l_int|0
)braket
comma
id|t1
op_assign
id|src
(braket
l_int|1
)braket
comma
id|t2
op_assign
id|src
(braket
l_int|2
)braket
comma
id|t3
op_assign
id|src
(braket
l_int|3
)braket
suffix:semicolon
id|dst
(braket
l_int|0
)braket
op_assign
id|t0
suffix:semicolon
id|dst
(braket
l_int|1
)braket
op_assign
id|t1
suffix:semicolon
id|dst
(braket
l_int|2
)braket
op_assign
id|t2
suffix:semicolon
id|dst
(braket
l_int|3
)braket
op_assign
id|t3
suffix:semicolon
id|dst
op_sub_assign
l_int|4
suffix:semicolon
id|src
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|src
OG
(paren
id|u32
op_star
)paren
op_amp
id|_intv_copy_src_start
)paren
suffix:semicolon
id|AS85EP1_IRAMM
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* &#x1b;$BFbB&quot;L?Na&#x1b;(BRAM&#x1b;$B$O!V&#x1b;(Bread-mode&#x1b;$B!W$K$J$j$^$9&#x1b;(B */
macro_line|#endif /* !CONFIG_ROM_KERNEL */
id|v850e_intc_disable_irqs
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
id|AS85EP1_PORT_PMC
(paren
id|LEDS_PORT
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Make the LEDs port an I/O port. */
id|AS85EP1_PORT_PM
(paren
id|LEDS_PORT
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Make all the bits output pins.  */
id|mach_tick
op_assign
id|as85ep1_led_tick
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
multiline_comment|/* Convenience macros.  */
DECL|macro|SRAM_END
mdefine_line|#define SRAM_END&t;(SRAM_ADDR + SRAM_SIZE)
DECL|macro|SDRAM_END
mdefine_line|#define SDRAM_END&t;(SDRAM_ADDR + SDRAM_SIZE)
DECL|function|mach_reserve_bootmem
r_void
id|__init
id|mach_reserve_bootmem
(paren
)paren
(brace
r_extern
r_char
id|_root_fs_image_start
comma
id|_root_fs_image_end
suffix:semicolon
id|u32
id|root_fs_image_start
op_assign
(paren
id|u32
)paren
op_amp
id|_root_fs_image_start
suffix:semicolon
id|u32
id|root_fs_image_end
op_assign
(paren
id|u32
)paren
op_amp
id|_root_fs_image_end
suffix:semicolon
r_if
c_cond
(paren
id|SDRAM_ADDR
template_param
id|RAM_START
)paren
multiline_comment|/* We can&squot;t use the space between SRAM and SDRAM, so&n;&t;&t;   prevent the kernel from trying.  */
id|reserve_bootmem
(paren
id|SRAM_END
comma
id|SDRAM_ADDR
op_minus
id|SRAM_END
)paren
suffix:semicolon
multiline_comment|/* Reserve the memory used by the root filesystem image if it&squot;s&n;&t;   in RAM.  */
r_if
c_cond
(paren
id|root_fs_image_end
OG
id|root_fs_image_start
op_logical_and
id|root_fs_image_start
op_ge
id|RAM_START
op_logical_and
id|root_fs_image_start
OL
id|RAM_END
)paren
id|reserve_bootmem
(paren
id|root_fs_image_start
comma
id|root_fs_image_end
op_minus
id|root_fs_image_start
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
id|v850e_timer_d_configure
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
id|v850e_intc_irq_init
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
id|v850e_intc_init_irq_types
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
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
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
id|AS85EP1_PORT_IO
(paren
id|LEDS_PORT
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
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
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
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
multiline_comment|/* Called before configuring an on-chip UART.  */
DECL|function|as85ep1_uart_pre_configure
r_void
id|as85ep1_uart_pre_configure
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
multiline_comment|/* Make the shared uart/port pins be uart pins.  */
id|AS85EP1_PORT_PMC
c_func
(paren
l_int|3
)paren
op_or_assign
(paren
l_int|0x5
op_lshift
id|chan
)paren
suffix:semicolon
multiline_comment|/* The AS85EP1 connects some general-purpose I/O pins on the CPU to&n;&t;   the RTS/CTS lines of UART 1&squot;s serial connection.  I/O pins P53&n;&t;   and P54 are RTS and CTS respectively.  */
r_if
c_cond
(paren
id|chan
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Put P53 &amp; P54 in I/O port mode.  */
id|AS85EP1_PORT_PMC
c_func
(paren
l_int|5
)paren
op_and_assign
op_complement
l_int|0x18
suffix:semicolon
multiline_comment|/* Make P53 an output, and P54 an input.  */
id|AS85EP1_PORT_PM
c_func
(paren
l_int|5
)paren
op_or_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* Minimum and maximum bounds for the moving upper LED boundary in the&n;   clock tick display.  */
DECL|macro|MIN_MAX_POS
mdefine_line|#define MIN_MAX_POS 0
DECL|macro|MAX_MAX_POS
mdefine_line|#define MAX_MAX_POS 7
multiline_comment|/* There are MAX_MAX_POS^2 - MIN_MAX_POS^2 cycles in the animation, so if&n;   we pick 6 and 0 as above, we get 49 cycles, which is when divided into&n;   the standard 100 value for HZ, gives us an almost 1s total time.  */
DECL|macro|TICKS_PER_FRAME
mdefine_line|#define TICKS_PER_FRAME &bslash;&n;&t;(HZ / (MAX_MAX_POS * MAX_MAX_POS - MIN_MAX_POS * MIN_MAX_POS))
DECL|function|as85ep1_led_tick
r_static
r_void
id|as85ep1_led_tick
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
id|set_bit
(paren
id|pos
comma
op_amp
id|AS85EP1_PORT_IO
c_func
(paren
id|LEDS_PORT
)paren
)paren
suffix:semicolon
id|pos
op_add_assign
id|dir
suffix:semicolon
id|clear_bit
(paren
id|pos
comma
op_amp
id|AS85EP1_PORT_IO
c_func
(paren
id|LEDS_PORT
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
