multiline_comment|/*&n; * arch/sh/kernel/cpu/init.c&n; *&n; * CPU init code&n; *&n; * Copyright (C) 2002, 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_void
id|detect_cpu_and_cache_system
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Generic wrapper for command line arguments to disable on-chip&n; * peripherals (nofpu, nodsp, and so forth).&n; */
DECL|macro|onchip_setup
mdefine_line|#define onchip_setup(x)&t;&t;&t;&t;&bslash;&n;static int x##_disabled __initdata = 0;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&bslash;&n;static int __init x##_setup(char *opts)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;x##_disabled = 1;&t;&t;&t;&bslash;&n;&t;return 0;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&bslash;&n;__setup(&quot;no&quot; __stringify(x), x##_setup);
DECL|variable|fpu
id|onchip_setup
c_func
(paren
id|fpu
)paren
suffix:semicolon
DECL|variable|dsp
id|onchip_setup
c_func
(paren
id|dsp
)paren
suffix:semicolon
multiline_comment|/*&n; * Generic first-level cache init&n; */
DECL|function|cache_init
r_static
r_void
id|__init
id|cache_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ccr
comma
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|cpu_data-&gt;type
op_eq
id|CPU_SH_NONE
)paren
id|panic
c_func
(paren
l_string|&quot;Unknown CPU&quot;
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
id|ccr
op_assign
id|ctrl_inl
c_func
(paren
id|CCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the cache is already enabled .. flush it.&n;&t; */
r_if
c_cond
(paren
id|ccr
op_amp
id|CCR_CACHE_ENABLE
)paren
(brace
r_int
r_int
id|ways
comma
id|waysize
comma
id|addrstart
suffix:semicolon
id|waysize
op_assign
id|cpu_data-&gt;dcache.sets
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the OC is already in RAM mode, we only have&n;&t;&t; * half of the entries to flush..&n;&t;&t; */
r_if
c_cond
(paren
id|ccr
op_amp
id|CCR_CACHE_ORA
)paren
id|waysize
op_rshift_assign
l_int|1
suffix:semicolon
id|waysize
op_lshift_assign
id|cpu_data-&gt;dcache.entry_shift
suffix:semicolon
macro_line|#ifdef CCR_CACHE_EMODE
multiline_comment|/* If EMODE is not set, we only have 1 way to flush. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ccr
op_amp
id|CCR_CACHE_EMODE
)paren
)paren
id|ways
op_assign
l_int|1
suffix:semicolon
r_else
macro_line|#endif
id|ways
op_assign
id|cpu_data-&gt;dcache.ways
suffix:semicolon
id|addrstart
op_assign
id|CACHE_OC_ADDRESS_ARRAY
suffix:semicolon
r_do
(brace
r_int
r_int
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|addrstart
suffix:semicolon
id|addr
OL
id|addrstart
op_plus
id|waysize
suffix:semicolon
id|addr
op_add_assign
id|cpu_data-&gt;dcache.linesz
)paren
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
id|addrstart
op_add_assign
id|cpu_data-&gt;dcache.way_incr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|ways
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Default CCR values .. enable the caches&n;&t; * and invalidate them immediately..&n;&t; */
id|flags
op_assign
id|CCR_CACHE_ENABLE
op_or
id|CCR_CACHE_INVALIDATE
suffix:semicolon
macro_line|#ifdef CCR_CACHE_EMODE
multiline_comment|/* Force EMODE if possible */
r_if
c_cond
(paren
id|cpu_data-&gt;dcache.ways
OG
l_int|1
)paren
id|flags
op_or_assign
id|CCR_CACHE_EMODE
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SH_WRITETHROUGH
multiline_comment|/* Turn on Write-through caching */
id|flags
op_or_assign
id|CCR_CACHE_WT
suffix:semicolon
macro_line|#else
multiline_comment|/* .. or default to Write-back */
id|flags
op_or_assign
id|CCR_CACHE_CB
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SH_OCRAM
multiline_comment|/* Turn on OCRAM -- halve the OC */
id|flags
op_or_assign
id|CCR_CACHE_ORA
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_rshift_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|ctrl_outl
c_func
(paren
id|flags
comma
id|CCR
)paren
suffix:semicolon
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SH_DSP
DECL|function|release_dsp
r_static
r_void
id|__init
id|release_dsp
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sr
suffix:semicolon
multiline_comment|/* Clear SR.DSP bit */
id|__asm__
id|__volatile__
(paren
l_string|&quot;stc&bslash;tsr, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&bslash;t%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&bslash;t%0, sr&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_complement
id|SR_DSP
)paren
)paren
suffix:semicolon
)brace
DECL|function|dsp_init
r_static
r_void
id|__init
id|dsp_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sr
suffix:semicolon
multiline_comment|/*&n;&t; * Set the SR.DSP bit, wait for one instruction, and then read&n;&t; * back the SR value.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;stc&bslash;tsr, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&bslash;t%0, sr&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;stc&bslash;tsr, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SR_DSP
)paren
)paren
suffix:semicolon
multiline_comment|/* If the DSP bit is still set, this CPU has a DSP */
r_if
c_cond
(paren
id|sr
op_amp
id|SR_DSP
)paren
id|cpu_data-&gt;flags
op_or_assign
id|CPU_HAS_DSP
suffix:semicolon
multiline_comment|/* Now that we&squot;ve determined the DSP status, clear the DSP bit. */
id|release_dsp
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SH_DSP */
multiline_comment|/**&n; * sh_cpu_init&n; *&n; * This is our initial entry point for each CPU, and is invoked on the boot&n; * CPU prior to calling start_kernel(). For SMP, a combination of this and&n; * start_secondary() will bring up each processor to a ready state prior&n; * to hand forking the idle loop.&n; *&n; * We do all of the basic processor init here, including setting up the&n; * caches, FPU, DSP, kicking the UBC, etc. By the time start_kernel() is&n; * hit (and subsequently platform_setup()) things like determining the&n; * CPU subtype and initial configuration will all be done.&n; *&n; * Each processor family is still responsible for doing its own probing&n; * and cache configuration in detect_cpu_and_cache_system().&n; */
DECL|function|sh_cpu_init
id|asmlinkage
r_void
id|__init
id|sh_cpu_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* First, probe the CPU */
id|detect_cpu_and_cache_system
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init the cache */
id|cache_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable the FPU */
r_if
c_cond
(paren
id|fpu_disabled
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FPU Disabled&bslash;n&quot;
)paren
suffix:semicolon
id|cpu_data-&gt;flags
op_and_assign
op_complement
id|CPU_HAS_FPU
suffix:semicolon
id|disable_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* FPU initialization */
r_if
c_cond
(paren
(paren
id|cpu_data-&gt;flags
op_amp
id|CPU_HAS_FPU
)paren
)paren
(brace
id|clear_thread_flag
c_func
(paren
id|TIF_USEDFPU
)paren
suffix:semicolon
id|clear_used_math
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SH_DSP
multiline_comment|/* Probe for DSP */
id|dsp_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable the DSP */
r_if
c_cond
(paren
id|dsp_disabled
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DSP Disabled&bslash;n&quot;
)paren
suffix:semicolon
id|cpu_data-&gt;flags
op_and_assign
op_complement
id|CPU_HAS_DSP
suffix:semicolon
id|release_dsp
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_UBC_WAKEUP
multiline_comment|/*&n;&t; * Some brain-damaged loaders decided it would be a good idea to put&n;&t; * the UBC to sleep. This causes some issues when it comes to things&n;&t; * like PTRACE_SINGLESTEP or doing hardware watchpoints in GDB.  So ..&n;&t; * we wake it up and hope that all is well.&n;&t; */
id|ubc_wakeup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
