multiline_comment|/*&n; * arch/v850/kernel/sim85e2c.c -- Machine-specific stuff for&n; *&t;V850E2 RTL simulator&n; *&n; *  Copyright (C) 2002  NEC Corporation&n; *  Copyright (C) 2002  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
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
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
r_extern
r_int
id|panic_timeout
suffix:semicolon
multiline_comment|/* Don&squot;t stop the simulator at `halt&squot; instructions.  */
id|NOTHAL
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* The sim85e2c simulator tracks `undefined&squot; values, so to make&n;&t;   debugging easier, we begin by zeroing out all otherwise&n;&t;   undefined registers.  This is not strictly necessary.&n;&n;&t;   The registers we zero are:&n;&t;       Every GPR except:&n;&t;           stack-pointer (r3)&n;&t;&t;   task-pointer (r16)&n;&t;&t;   our return addr (r31)&n;&t;       Every system register (SPR) that we know about except for&n;&t;       the PSW (SPR 5), which we zero except for the&n;&t;       disable-interrupts bit.&n;&t;*/
multiline_comment|/* GPRs */
id|asm
r_volatile
(paren
l_string|&quot;             mov r0, r1 ; mov r0, r2              &quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r0, r4 ; mov r0, r5 ; mov r0, r6 ; mov r0, r7 &quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r0, r8 ; mov r0, r9 ; mov r0, r10; mov r0, r11&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r0, r12; mov r0, r13; mov r0, r14; mov r0, r15&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;             mov r0, r17; mov r0, r18; mov r0, r19&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r0, r20; mov r0, r21; mov r0, r22; mov r0, r23&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r0, r24; mov r0, r25; mov r0, r26; mov r0, r27&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r0, r28; mov r0, r29; mov r0, r30&quot;
)paren
suffix:semicolon
multiline_comment|/* SPRs */
id|asm
r_volatile
(paren
l_string|&quot;ldsr r0, 0;  ldsr r0, 1;  ldsr r0, 2;  ldsr r0, 3&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ldsr r0, 4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;addi 0x20, r0, r1; ldsr r1, 5&quot;
)paren
suffix:semicolon
multiline_comment|/* PSW */
id|asm
r_volatile
(paren
l_string|&quot;ldsr r0, 16; ldsr r0, 17; ldsr r0, 18; ldsr r0, 19&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ldsr r0, 20&quot;
)paren
suffix:semicolon
multiline_comment|/* Turn on the caches.  */
id|NA85E2C_CACHE_BTSC
op_or_assign
(paren
id|NA85E2C_CACHE_BTSC_ICM
op_or
id|NA85E2C_CACHE_BTSC_DCM0
)paren
suffix:semicolon
id|NA85E2C_BUSM_BHC
op_assign
l_int|0xFFFF
suffix:semicolon
multiline_comment|/* Ensure that the simulator halts on a panic, instead of going&n;&t;   into an infinite loop inside the panic function.  */
id|panic_timeout
op_assign
op_minus
l_int|1
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
l_string|&quot;CPU: NEC V850E2 (sim85e2c simulator)&bslash;n&quot;
)paren
suffix:semicolon
id|memcons_setup
(paren
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
multiline_comment|/* There are 3 possible areas we can use:&n;&t;     IRAM (1MB) is fast for instruction fetches, but slow for data&n;&t;     DRAM (1020KB) is fast for data, but slow for instructions&n;&t;     ERAM is cached, so should be fast for both insns and data,&n;&t;          _but_ currently only supports write-through caching, so&n;&t;&t;  writes are slow.&n;&t;   Since there&squot;s really no area that&squot;s good for general kernel&n;&t;   use, we use DRAM -- it won&squot;t be good for user programs&n;&t;   (which will be loaded into kernel allocated memory), but&n;&t;   currently we&squot;re more concerned with testing the kernel.  */
op_star
id|ram_start
op_assign
id|DRAM_ADDR
suffix:semicolon
op_star
id|ram_len
op_assign
id|R0_RAM_ADDR
op_minus
id|DRAM_ADDR
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
multiline_comment|/* The simulator actually cycles through all interrupts&n;&t;   periodically.  We just pay attention to IRQ0, which gives us&n;&t;   1/64 the rate of the periodic interrupts.  */
id|setup_irq
(paren
l_int|0
comma
id|timer_action
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
"&f;"
multiline_comment|/* Interrupts */
DECL|variable|irq_inits
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
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|hw_itypes
r_struct
id|hw_interrupt_type
id|hw_itypes
(braket
l_int|1
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
id|nb85e_intc_init_irq_types
(paren
id|irq_inits
comma
id|hw_itypes
)paren
suffix:semicolon
)brace
"&f;"
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
id|SIMFIN
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Halt immediately.  */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
)brace
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
id|machine_halt
(paren
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
eof
