multiline_comment|/*&n; * arch/v850/kernel/fpga85e2c.h -- Machine-dependent defs for&n; *&t;FPGA implementation of V850E2/NA85E2C&n; *&n; *  Copyright (C) 2002,03  NEC Electronics Corporation&n; *  Copyright (C) 2002,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;mach.h&quot;
r_extern
r_void
id|memcons_setup
(paren
r_void
)paren
suffix:semicolon
DECL|macro|REG_DUMP_ADDR
mdefine_line|#define REG_DUMP_ADDR&t;&t;0x220000
r_extern
r_struct
id|irqaction
id|reg_snap_action
suffix:semicolon
multiline_comment|/* fwd decl */
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
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
r_extern
id|u32
id|_intv_end
comma
id|_intv_load_start
suffix:semicolon
multiline_comment|/* Set bus sizes: CS0 32-bit, CS1 16-bit, CS7 8-bit,&n;&t;   everything else 32-bit.  */
id|V850E2_BSC
op_assign
l_int|0x2AA6
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
op_le
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|CSDEV
c_func
(paren
id|i
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 32 bit */
multiline_comment|/* Ensure that the simulator halts on a panic, instead of going&n;&t;   into an infinite loop inside the panic function.  */
id|panic_timeout
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Move the interrupt vectors into their real location.  Note that&n;&t;   any relocations there are relative to the real location, so we&n;&t;   don&squot;t have to fix anything up.  We use a loop instead of calling&n;&t;   memcpy to keep this a leaf function (to avoid a function&n;&t;   prologue being generated).  */
id|dst
op_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* &amp;_intv_start + 0x10.  */
id|src
op_assign
op_amp
id|_intv_load_start
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
id|u32
id|t4
op_assign
id|src
(braket
l_int|4
)braket
comma
id|t5
op_assign
id|src
(braket
l_int|5
)braket
comma
id|t6
op_assign
id|src
(braket
l_int|6
)braket
comma
id|t7
op_assign
id|src
(braket
l_int|7
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
(braket
l_int|4
)braket
op_assign
id|t4
suffix:semicolon
id|dst
(braket
l_int|5
)braket
op_assign
id|t5
suffix:semicolon
id|dst
(braket
l_int|6
)braket
op_assign
id|t6
suffix:semicolon
id|dst
(braket
l_int|7
)braket
op_assign
id|t7
suffix:semicolon
id|dst
op_add_assign
l_int|8
suffix:semicolon
id|src
op_add_assign
l_int|8
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dst
OL
op_amp
id|_intv_end
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
id|memcons_setup
(paren
)paren
suffix:semicolon
multiline_comment|/* Setup up NMI0 to copy the registers to a known memory location.&n;&t;   The FGPA board has a button that produces NMI0 when pressed, so&n;&t;   this allows us to push the button, and then look at memory to see&n;&t;   what&squot;s in the registers (there&squot;s no other way to easily do so).&n;&t;   We have to use `setup_irq&squot; instead of `request_irq&squot; because it&squot;s&n;&t;   still too early to do memory allocation.  */
id|setup_irq
(paren
id|IRQ_NMI
(paren
l_int|0
)paren
comma
op_amp
id|reg_snap_action
)paren
suffix:semicolon
)brace
DECL|function|mach_get_physical_ram
r_void
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
id|ERAM_ADDR
suffix:semicolon
op_star
id|ram_len
op_assign
id|ERAM_SIZE
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
multiline_comment|/* Setup up the timer interrupt.  The FPGA peripheral control&n;&t;   registers _only_ work with single-bit writes (set1/clr1)!  */
id|__clear_bit
(paren
id|RPU_GTMC_CE_BIT
comma
op_amp
id|RPU_GTMC
)paren
suffix:semicolon
id|__clear_bit
(paren
id|RPU_GTMC_CLK_BIT
comma
op_amp
id|RPU_GTMC
)paren
suffix:semicolon
id|__set_bit
(paren
id|RPU_GTMC_CE_BIT
comma
op_amp
id|RPU_GTMC
)paren
suffix:semicolon
multiline_comment|/* We use the first RPU interrupt, which occurs every 8.192ms.  */
id|setup_irq
(paren
id|IRQ_RPU
(paren
l_int|0
)paren
comma
id|timer_action
)paren
suffix:semicolon
)brace
"&f;"
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
r_void
id|machine_halt
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|function|machine_halt
r_void
id|machine_halt
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|DWC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0x7777
suffix:semicolon
id|DWC
c_func
(paren
l_int|1
)paren
op_assign
l_int|0x7777
suffix:semicolon
id|ASC
op_assign
l_int|0xffff
suffix:semicolon
id|FLGREG
c_func
(paren
l_int|0
)paren
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Halt immediately.  */
id|asm
(paren
l_string|&quot;di; halt; nop; nop; nop; nop; nop&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
DECL|function|machine_restart
r_void
id|machine_restart
(paren
r_char
op_star
id|__unused
)paren
(brace
id|machine_halt
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
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
"&f;"
multiline_comment|/* Interrupts */
DECL|variable|irq_inits
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
l_string|&quot;RPU&quot;
comma
id|IRQ_RPU
c_func
(paren
l_int|0
)paren
comma
id|IRQ_RPU_NUM
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
DECL|macro|NUM_IRQ_INITS
mdefine_line|#define NUM_IRQ_INITS ((sizeof irq_inits / sizeof irq_inits[0]) - 1)
DECL|variable|hw_itypes
r_struct
id|hw_interrupt_type
id|hw_itypes
(braket
id|NUM_IRQ_INITS
)braket
suffix:semicolon
multiline_comment|/* Initialize interrupts.  */
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
"&f;"
multiline_comment|/* An interrupt handler that copies the registers to a known memory location,&n;   for debugging purposes.  */
DECL|function|make_reg_snap
r_static
r_void
id|make_reg_snap
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
(paren
op_star
(paren
r_int
op_star
)paren
id|REG_DUMP_ADDR
)paren
op_increment
suffix:semicolon
(paren
op_star
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|REG_DUMP_ADDR
op_plus
r_sizeof
(paren
r_int
)paren
)paren
)paren
op_assign
op_star
id|regs
suffix:semicolon
)brace
DECL|variable|reg_snap_dev_id
r_static
r_int
id|reg_snap_dev_id
suffix:semicolon
DECL|variable|reg_snap_action
r_static
r_struct
id|irqaction
id|reg_snap_action
op_assign
(brace
id|make_reg_snap
comma
l_int|0
comma
id|CPU_MASK_NONE
comma
l_string|&quot;reg_snap&quot;
comma
op_amp
id|reg_snap_dev_id
comma
l_int|0
)brace
suffix:semicolon
eof
