multiline_comment|/*&n; * arch/v850/kernel/sim85e2.c -- Machine-specific stuff for&n; *&t;V850E2 RTL simulator&n; *&n; *  Copyright (C) 2002,03  NEC Electronics Corporation&n; *  Copyright (C) 2002,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;mach.h&quot;
multiline_comment|/* There are 4 possible areas we can use:&n;&n;     IRAM (1MB) is fast for instruction fetches, but slow for data&n;     DRAM (1020KB) is fast for data, but slow for instructions&n;     ERAM is cached, so should be fast for both insns and data&n;     SDRAM is external DRAM, similar to ERAM&n;*/
DECL|macro|INIT_MEMC_FOR_SDRAM
mdefine_line|#define INIT_MEMC_FOR_SDRAM
DECL|macro|USE_SDRAM_AREA
mdefine_line|#define USE_SDRAM_AREA
DECL|macro|KERNEL_IN_SDRAM_AREA
mdefine_line|#define KERNEL_IN_SDRAM_AREA
DECL|macro|DCACHE_MODE
mdefine_line|#define DCACHE_MODE&t;V850E2_CACHE_BTSC_DCM_WT
multiline_comment|/*#define DCACHE_MODE&t;V850E2_CACHE_BTSC_DCM_WB_ALLOC*/
macro_line|#ifdef USE_SDRAM_AREA
DECL|macro|RAM_START
mdefine_line|#define RAM_START &t;SDRAM_ADDR
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(SDRAM_ADDR + SDRAM_SIZE)
macro_line|#else
multiline_comment|/* When we use DRAM, we need to account for the fact that the end of it is&n;   used for R0_RAM.  */
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;DRAM_ADDR
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;R0_RAM_ADDR
macro_line|#endif
r_extern
r_void
id|memcons_setup
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef KERNEL_IN_SDRAM_AREA
DECL|macro|EARLY_INIT_SECTION_ATTR
mdefine_line|#define EARLY_INIT_SECTION_ATTR __attribute__ ((section (&quot;.early.text&quot;)))
macro_line|#else
DECL|macro|EARLY_INIT_SECTION_ATTR
mdefine_line|#define EARLY_INIT_SECTION_ATTR __init
macro_line|#endif
DECL|function|mach_early_init
r_void
id|EARLY_INIT_SECTION_ATTR
id|mach_early_init
(paren
r_void
)paren
(brace
multiline_comment|/* The sim85e2 simulator tracks `undefined&squot; values, so to make&n;&t;   debugging easier, we begin by zeroing out all otherwise&n;&t;   undefined registers.  This is not strictly necessary.&n;&n;&t;   The registers we zero are:&n;&t;       Every GPR except:&n;&t;           stack-pointer (r3)&n;&t;&t;   task-pointer (r16)&n;&t;&t;   our return addr (r31)&n;&t;       Every system register (SPR) that we know about except for&n;&t;       the PSW (SPR 5), which we zero except for the&n;&t;       disable-interrupts bit.&n;&t;*/
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
macro_line|#ifdef INIT_MEMC_FOR_SDRAM
multiline_comment|/* Settings for SDRAM controller.  */
id|V850E2_VSWC
op_assign
l_int|0x0042
suffix:semicolon
id|V850E2_BSC
op_assign
l_int|0x9286
suffix:semicolon
id|V850E2_BCT
c_func
(paren
l_int|0
)paren
op_assign
l_int|0xb000
suffix:semicolon
multiline_comment|/* was: 0 */
id|V850E2_BCT
c_func
(paren
l_int|1
)paren
op_assign
l_int|0x000b
suffix:semicolon
id|V850E2_ASC
op_assign
l_int|0
suffix:semicolon
id|V850E2_LBS
op_assign
l_int|0xa9aa
suffix:semicolon
multiline_comment|/* was: 0xaaaa */
id|V850E2_LBC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|V850E2_LBC
c_func
(paren
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* was: 0x3 */
id|V850E2_BCC
op_assign
l_int|0
suffix:semicolon
id|V850E2_RFS
c_func
(paren
l_int|4
)paren
op_assign
l_int|0x800a
suffix:semicolon
multiline_comment|/* was: 0xf109 */
id|V850E2_SCR
c_func
(paren
l_int|4
)paren
op_assign
l_int|0x2091
suffix:semicolon
multiline_comment|/* was: 0x20a1 */
id|V850E2_RFS
c_func
(paren
l_int|3
)paren
op_assign
l_int|0x800c
suffix:semicolon
id|V850E2_SCR
c_func
(paren
l_int|3
)paren
op_assign
l_int|0x20a1
suffix:semicolon
id|V850E2_DWC
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|V850E2_DWC
c_func
(paren
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if 0
macro_line|#ifdef CONFIG_V850E2_SIM85E2S
multiline_comment|/* Turn on the caches.  */
id|V850E2_CACHE_BTSC
op_assign
id|V850E2_CACHE_BTSC_ICM
op_or
id|DCACHE_MODE
suffix:semicolon
id|V850E2_BHC
op_assign
l_int|0x1010
suffix:semicolon
macro_line|#elif CONFIG_V850E2_SIM85E2C
id|V850E2_CACHE_BTSC
op_or_assign
(paren
id|V850E2_CACHE_BTSC_ICM
op_or
id|V850E2_CACHE_BTSC_DCM0
)paren
suffix:semicolon
id|V850E2_BUSM_BHC
op_assign
l_int|0xFFFF
suffix:semicolon
macro_line|#endif
macro_line|#else
id|V850E2_BHC
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Don&squot;t stop the simulator at `halt&squot; instructions.  */
id|SIM85E2_NOTHAL
op_assign
l_int|1
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
id|v850e_intc_init_irq_types
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
id|SIM85E2_SIMFIN
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
eof
