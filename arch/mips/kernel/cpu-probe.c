macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/bugs.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
multiline_comment|/*&n; * Not all of the MIPS CPUs have the &quot;wait&quot; instruction available. Moreover,&n; * the implementation of the &quot;wait&quot; feature differs between CPU families. This&n; * points to the function that implements CPU specific wait.&n; * The wait instruction stops the pipeline and reduces the power consumption of&n; * the CPU very much.&n; */
DECL|variable|cpu_wait
r_void
(paren
op_star
id|cpu_wait
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|function|r3081_wait
r_static
r_void
id|r3081_wait
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cfg
op_assign
id|read_c0_conf
c_func
(paren
)paren
suffix:semicolon
id|write_c0_conf
c_func
(paren
id|cfg
op_or
id|R30XX_CONF_HALT
)paren
suffix:semicolon
)brace
DECL|function|r39xx_wait
r_static
r_void
id|r39xx_wait
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cfg
op_assign
id|read_c0_conf
c_func
(paren
)paren
suffix:semicolon
id|write_c0_conf
c_func
(paren
id|cfg
op_or
id|TX39_CONF_HALT
)paren
suffix:semicolon
)brace
DECL|function|r4k_wait
r_static
r_void
id|r4k_wait
c_func
(paren
r_void
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
)brace
DECL|function|au1k_wait
r_void
id|au1k_wait
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PM
multiline_comment|/* using the wait instruction makes CP0 counter unusable */
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
macro_line|#else
id|__asm__
c_func
(paren
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|check_wait
r_static
r_inline
r_void
id|check_wait
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_mips
op_star
id|c
op_assign
op_amp
id|current_cpu_data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Checking for &squot;wait&squot; instruction... &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;cputype
)paren
(brace
r_case
id|CPU_R3081
suffix:colon
r_case
id|CPU_R3081E
suffix:colon
id|cpu_wait
op_assign
id|r3081_wait
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; available.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_TX3927
suffix:colon
id|cpu_wait
op_assign
id|r39xx_wait
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; available.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_R4200
suffix:colon
multiline_comment|/*&t;case CPU_R4300: */
r_case
id|CPU_R4600
suffix:colon
r_case
id|CPU_R4640
suffix:colon
r_case
id|CPU_R4650
suffix:colon
r_case
id|CPU_R4700
suffix:colon
r_case
id|CPU_R5000
suffix:colon
r_case
id|CPU_NEVADA
suffix:colon
r_case
id|CPU_RM7000
suffix:colon
r_case
id|CPU_TX49XX
suffix:colon
r_case
id|CPU_4KC
suffix:colon
r_case
id|CPU_4KEC
suffix:colon
r_case
id|CPU_4KSC
suffix:colon
r_case
id|CPU_5KC
suffix:colon
multiline_comment|/*&t;case CPU_20KC:*/
id|cpu_wait
op_assign
id|r4k_wait
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; available.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_AU1000
suffix:colon
r_case
id|CPU_AU1100
suffix:colon
r_case
id|CPU_AU1500
suffix:colon
id|cpu_wait
op_assign
id|au1k_wait
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; available.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot; unavailable.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|check_bugs
r_void
id|__init
id|check_bugs
c_func
(paren
r_void
)paren
(brace
id|check_wait
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe whether cpu has config register by trying to play with&n; * alternate cache bit and see whether it matters.&n; * It&squot;s used by cpu_probe to distinguish between R3000A and R3081.&n; */
DECL|function|cpu_has_confreg
r_static
r_inline
r_int
id|cpu_has_confreg
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CPU_R3000
r_extern
r_int
r_int
id|r3k_cache_size
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|size1
comma
id|size2
suffix:semicolon
r_int
r_int
id|cfg
op_assign
id|read_c0_conf
c_func
(paren
)paren
suffix:semicolon
id|size1
op_assign
id|r3k_cache_size
c_func
(paren
id|ST0_ISC
)paren
suffix:semicolon
id|write_c0_conf
c_func
(paren
id|cfg
op_xor
id|R30XX_CONF_AC
)paren
suffix:semicolon
id|size2
op_assign
id|r3k_cache_size
c_func
(paren
id|ST0_ISC
)paren
suffix:semicolon
id|write_c0_conf
c_func
(paren
id|cfg
)paren
suffix:semicolon
r_return
id|size1
op_ne
id|size2
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Get the FPU Implementation/Revision.&n; */
DECL|function|cpu_get_fpu_id
r_static
r_inline
r_int
r_int
id|cpu_get_fpu_id
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
comma
id|fpu_id
suffix:semicolon
id|tmp
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|__enable_fpu
c_func
(paren
)paren
suffix:semicolon
id|fpu_id
op_assign
id|read_32bit_cp1_register
c_func
(paren
id|CP1_REVISION
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|fpu_id
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the CPU has an FPU the official way.&n; */
DECL|function|__cpu_has_fpu
r_static
r_inline
r_int
id|__cpu_has_fpu
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
id|cpu_get_fpu_id
c_func
(paren
)paren
op_amp
l_int|0xff00
)paren
op_ne
id|FPIR_IMP_NONE
)paren
suffix:semicolon
)brace
DECL|macro|R4K_OPTS
mdefine_line|#define R4K_OPTS (MIPS_CPU_TLB | MIPS_CPU_4KEX | MIPS_CPU_4KTLB &bslash;&n;&t;&t;| MIPS_CPU_COUNTER | MIPS_CPU_CACHE_CDEX)
DECL|function|cpu_probe
id|__init
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_mips
op_star
id|c
op_assign
op_amp
id|current_cpu_data
suffix:semicolon
r_int
r_int
id|config0
op_assign
id|read_c0_config
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|config1
suffix:semicolon
id|c-&gt;processor_id
op_assign
id|PRID_IMP_UNKNOWN
suffix:semicolon
id|c-&gt;fpu_id
op_assign
id|FPIR_IMP_NONE
suffix:semicolon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_if
c_cond
(paren
id|config0
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
(brace
multiline_comment|/* MIPS32 or MIPS64 compliant CPU. Read Config 1 register. */
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_4KEX
op_or
id|MIPS_CPU_4KTLB
op_or
id|MIPS_CPU_COUNTER
op_or
id|MIPS_CPU_DIVEC
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|config1
op_assign
id|read_c0_config1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config1
op_amp
(paren
l_int|1
op_lshift
l_int|3
)paren
)paren
id|c-&gt;options
op_or_assign
id|MIPS_CPU_WATCH
suffix:semicolon
r_if
c_cond
(paren
id|config1
op_amp
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
id|c-&gt;options
op_or_assign
id|MIPS_CPU_MIPS16
suffix:semicolon
r_if
c_cond
(paren
id|config1
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
id|c-&gt;options
op_or_assign
id|MIPS_CPU_EJTAG
suffix:semicolon
r_if
c_cond
(paren
id|config1
op_amp
l_int|1
)paren
(brace
id|c-&gt;options
op_or_assign
id|MIPS_CPU_FPU
suffix:semicolon
id|c-&gt;options
op_or_assign
id|MIPS_CPU_32FPR
suffix:semicolon
)brace
id|c-&gt;scache.flags
op_assign
id|MIPS_CACHE_NOT_PRESENT
suffix:semicolon
id|c-&gt;tlbsize
op_assign
(paren
(paren
id|config1
op_rshift
l_int|25
)paren
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
suffix:semicolon
)brace
id|c-&gt;processor_id
op_assign
id|read_c0_prid
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff0000
)paren
(brace
r_case
id|PRID_COMP_LEGACY
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff00
)paren
(brace
r_case
id|PRID_IMP_R2000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R2000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_I
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_NOFPUEX
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
r_if
c_cond
(paren
id|__cpu_has_fpu
c_func
(paren
)paren
)paren
id|c-&gt;options
op_or_assign
id|MIPS_CPU_FPU
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R3000
suffix:colon
r_if
c_cond
(paren
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff
)paren
op_eq
id|PRID_REV_R3000A
)paren
r_if
c_cond
(paren
id|cpu_has_confreg
c_func
(paren
)paren
)paren
id|c-&gt;cputype
op_assign
id|CPU_R3081E
suffix:semicolon
r_else
id|c-&gt;cputype
op_assign
id|CPU_R3000A
suffix:semicolon
r_else
id|c-&gt;cputype
op_assign
id|CPU_R3000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_I
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_NOFPUEX
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
r_if
c_cond
(paren
id|__cpu_has_fpu
c_func
(paren
)paren
)paren
id|c-&gt;options
op_or_assign
id|MIPS_CPU_FPU
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4000
suffix:colon
r_if
c_cond
(paren
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff
)paren
op_ge
id|PRID_REV_R4400
)paren
id|c-&gt;cputype
op_assign
id|CPU_R4400SC
suffix:semicolon
r_else
id|c-&gt;cputype
op_assign
id|CPU_R4000SC
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_WATCH
op_or
id|MIPS_CPU_VCE
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_VR41XX
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xf0
)paren
(brace
macro_line|#ifndef CONFIG_VR4181
r_case
id|PRID_REV_VR4111
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_VR4111
suffix:semicolon
r_break
suffix:semicolon
macro_line|#else
r_case
id|PRID_REV_VR4181
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_VR4181
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PRID_REV_VR4121
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_VR4121
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_REV_VR4122
suffix:colon
r_if
c_cond
(paren
(paren
id|c-&gt;processor_id
op_amp
l_int|0xf
)paren
OL
l_int|0x3
)paren
id|c-&gt;cputype
op_assign
id|CPU_VR4122
suffix:semicolon
r_else
id|c-&gt;cputype
op_assign
id|CPU_VR4181A
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_REV_VR4131
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_VR4131
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Unexpected CPU of NEC VR4100 series&bslash;n&quot;
)paren
suffix:semicolon
id|c-&gt;cputype
op_assign
id|CPU_VR41XX
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4300
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R4300
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4600
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R4600
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
id|PRID_IMP_R4650
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * This processor doesn&squot;t have an MMU, so it&squot;s not&n;&t;&t;&t; * &quot;real easy&quot; to run Linux on it. It is left purely&n;&t;&t;&t; * for documentation.  Commented out because it shares&n;&t;&t;&t; * it&squot;s c0_prid id number with the TX3900.&n;&t;&t;&t; */
id|c-&gt;cputype
op_assign
id|CPU_R4650
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PRID_IMP_TX39
suffix:colon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_I
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;processor_id
op_amp
l_int|0xf0
)paren
op_eq
(paren
id|PRID_REV_TX3927
op_amp
l_int|0xf0
)paren
)paren
(brace
id|c-&gt;cputype
op_assign
id|CPU_TX3927
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff
)paren
(brace
r_case
id|PRID_REV_TX3912
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_TX3912
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_REV_TX3922
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_TX3922
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4700
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R4700
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_TX49
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_TX49XX
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_III
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R5000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R5000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R5432
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R5432
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_WATCH
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R5500
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R5500
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_WATCH
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_NEVADA
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_NEVADA
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_DIVEC
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R6000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R6000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_II
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R6000A
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R6000A
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_II
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_RM7000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_RM7000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|R4K_OPTS
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Undocumented RM7000:  Bit 29 in the info register of&n;&t;&t;&t; * the RM7000 v2.0 indicates if the TLB has 48 or 64&n;&t;&t;&t; * entries.&n;&t;&t;&t; *&n;&t;&t;&t; * 29      1 =&gt;    64 entry JTLB&n;&t;&t;&t; *         0 =&gt;    48 entry JTLB&n;&t;&t;&t; */
id|c-&gt;tlbsize
op_assign
(paren
id|read_c0_info
c_func
(paren
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
ques
c_cond
l_int|64
suffix:colon
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R8000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R8000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_4KEX
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|384
suffix:semicolon
multiline_comment|/* has weird TLB: 3-way x 128 */
r_break
suffix:semicolon
r_case
id|PRID_IMP_R10000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R10000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_4KEX
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_COUNTER
op_or
id|MIPS_CPU_WATCH
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R12000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_R12000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_IV
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_4KEX
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
op_or
id|MIPS_CPU_COUNTER
op_or
id|MIPS_CPU_WATCH
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PRID_COMP_MIPS
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff00
)paren
(brace
r_case
id|PRID_IMP_4KC
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_4KC
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_4KEC
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_4KEC
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_4KSC
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_4KSC
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_5KC
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_5KC
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M64
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_20KC
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_20KC
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M64
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PRID_COMP_ALCHEMY
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff00
)paren
(brace
r_case
id|PRID_IMP_AU1_REV1
suffix:colon
r_case
id|PRID_IMP_AU1_REV2
suffix:colon
r_switch
c_cond
(paren
(paren
id|c-&gt;processor_id
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|0
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_AU1000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_AU1500
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_AU1100
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown Au Core!&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M32
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PRID_COMP_SIBYTE
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff00
)paren
(brace
r_case
id|PRID_IMP_SB1
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_SB1
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M64
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_4KEX
op_or
id|MIPS_CPU_COUNTER
op_or
id|MIPS_CPU_DIVEC
op_or
id|MIPS_CPU_MCHECK
op_or
id|MIPS_CPU_EJTAG
op_or
id|MIPS_CPU_WATCH
op_or
id|MIPS_CPU_LLSC
suffix:semicolon
macro_line|#ifndef CONFIG_SB1_PASS_1_WORKAROUNDS
multiline_comment|/* FPU in pass1 is known to have issues. */
id|c-&gt;options
op_or_assign
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_32FPR
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PRID_COMP_SANDCRAFT
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;processor_id
op_amp
l_int|0xff00
)paren
(brace
r_case
id|PRID_IMP_SR71000
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_SR71000
suffix:semicolon
id|c-&gt;isa_level
op_assign
id|MIPS_CPU_ISA_M64
suffix:semicolon
id|c-&gt;options
op_assign
id|MIPS_CPU_TLB
op_or
id|MIPS_CPU_4KEX
op_or
id|MIPS_CPU_4KTLB
op_or
id|MIPS_CPU_FPU
op_or
id|MIPS_CPU_COUNTER
op_or
id|MIPS_CPU_MCHECK
suffix:semicolon
id|c-&gt;scache.ways
op_assign
l_int|8
suffix:semicolon
id|c-&gt;tlbsize
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|c-&gt;cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
id|c-&gt;tlbsize
op_assign
(paren
(paren
id|config1
op_rshift
l_int|25
)paren
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;options
op_amp
id|MIPS_CPU_FPU
)paren
id|c-&gt;fpu_id
op_assign
id|cpu_get_fpu_id
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cpu_report
id|__init
r_void
id|cpu_report
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_mips
op_star
id|c
op_assign
op_amp
id|current_cpu_data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU revision is: %08x&bslash;n&quot;
comma
id|c-&gt;processor_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;options
op_amp
id|MIPS_CPU_FPU
)paren
id|printk
c_func
(paren
l_string|&quot;FPU revision is: %08x&bslash;n&quot;
comma
id|c-&gt;fpu_id
)paren
suffix:semicolon
)brace
eof
