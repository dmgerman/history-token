macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;cpu.h&quot;
multiline_comment|/*&n; *&t;B step AMD K6 before B 9730xxxx have hardware bugs that can cause&n; *&t;misexecution of code under Linux. Owners of such processors should&n; *&t;contact AMD for precise details and a CPU swap.&n; *&n; *&t;See&t;http://www.multimania.com/poulot/k6bug.html&n; *&t;&t;http://www.amd.com/K6/k6docs/revgd.html&n; *&n; *&t;The following test is erm.. interesting. AMD neglected to up&n; *&t;the chip setting when fixing the bug but they also tweaked some&n; *&t;performance at the same time..&n; */
r_extern
r_void
id|vide
c_func
(paren
r_void
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.align 4&bslash;nvide: ret&quot;
)paren
suffix:semicolon
DECL|function|init_amd
r_static
r_void
id|__init
id|init_amd
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|u32
id|l
comma
id|h
suffix:semicolon
r_int
id|mbytes
op_assign
id|num_physpages
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
r_int
id|r
suffix:semicolon
multiline_comment|/*&n;&t; *&t;FIXME: We should handle the K5 here. Set up the write&n;&t; *&t;range and also turn on MSR 83 bits 4 and 31 (write alloc,&n;&t; *&t;no bus pipeline)&n;&t; */
multiline_comment|/* Bit 31 in normal CPUID used for nonstandard 3DNow ID;&n;&t;   3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway */
id|clear_bit
c_func
(paren
l_int|0
op_star
l_int|32
op_plus
l_int|31
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
id|r
op_assign
id|get_model_name
c_func
(paren
id|c
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;x86
)paren
(brace
r_case
l_int|5
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86_model
OL
l_int|6
)paren
(brace
multiline_comment|/* Based on AMD doc 20734R - June 2000 */
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|0
)paren
(brace
id|clear_bit
c_func
(paren
id|X86_FEATURE_APIC
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|X86_FEATURE_PGE
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|6
op_logical_and
id|c-&gt;x86_mask
op_eq
l_int|1
)paren
(brace
r_const
r_int
id|K6_BUG_LOOP
op_assign
l_int|1000000
suffix:semicolon
r_int
id|n
suffix:semicolon
r_void
(paren
op_star
id|f_vide
)paren
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|d
comma
id|d2
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AMD K6 stepping B detected - &quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * It looks like AMD fixed the 2.6.2 bug and improved indirect &n;&t;&t;&t;&t; * calls at the same time.&n;&t;&t;&t;&t; */
id|n
op_assign
id|K6_BUG_LOOP
suffix:semicolon
id|f_vide
op_assign
id|vide
suffix:semicolon
id|rdtscl
c_func
(paren
id|d
)paren
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
id|f_vide
c_func
(paren
)paren
suffix:semicolon
id|rdtscl
c_func
(paren
id|d2
)paren
suffix:semicolon
id|d
op_assign
id|d2
op_minus
id|d
suffix:semicolon
multiline_comment|/* Knock these two lines out if it debugs out ok */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;K6 BUG %ld %d (Report these if test report is incorrect)&bslash;n&quot;
comma
id|d
comma
l_int|20
op_star
id|K6_BUG_LOOP
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AMD K6 stepping B detected - &quot;
)paren
suffix:semicolon
multiline_comment|/* -- cut here -- */
r_if
c_cond
(paren
id|d
OG
l_int|20
op_star
id|K6_BUG_LOOP
)paren
id|printk
c_func
(paren
l_string|&quot;system stability may be impaired when more than 32 MB are used.&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;probably OK (after B9730xxxx).&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Please see http://www.mygale.com/~poulot/k6bug.html&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* K6 with old style WHCR */
r_if
c_cond
(paren
id|c-&gt;x86_model
OL
l_int|8
op_logical_or
(paren
id|c-&gt;x86_model
op_eq
l_int|8
op_logical_and
id|c-&gt;x86_mask
OL
l_int|8
)paren
)paren
(brace
multiline_comment|/* We can only write allocate on the low 508Mb */
r_if
c_cond
(paren
id|mbytes
OG
l_int|508
)paren
(brace
id|mbytes
op_assign
l_int|508
suffix:semicolon
)brace
id|rdmsr
c_func
(paren
id|MSR_K6_WHCR
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|l
op_amp
l_int|0x0000FFFF
)paren
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|l
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
op_or
(paren
(paren
id|mbytes
op_div
l_int|4
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K6_WHCR
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enabling old style K6 write allocation for %d Mb&bslash;n&quot;
comma
id|mbytes
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c-&gt;x86_model
op_eq
l_int|8
op_logical_and
id|c-&gt;x86_mask
OG
l_int|7
)paren
op_logical_or
id|c-&gt;x86_model
op_eq
l_int|9
op_logical_or
id|c-&gt;x86_model
op_eq
l_int|13
)paren
(brace
multiline_comment|/* The more serious chips .. */
r_if
c_cond
(paren
id|mbytes
OG
l_int|4092
)paren
(brace
id|mbytes
op_assign
l_int|4092
suffix:semicolon
)brace
id|rdmsr
c_func
(paren
id|MSR_K6_WHCR
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|l
op_amp
l_int|0xFFFF0000
)paren
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|l
op_assign
(paren
(paren
id|mbytes
op_rshift
l_int|2
)paren
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K6_WHCR
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enabling new style K6 write allocation for %d Mb&bslash;n&quot;
comma
id|mbytes
)paren
suffix:semicolon
)brace
multiline_comment|/*  Set MTRR capability flag if appropriate */
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|13
op_logical_or
id|c-&gt;x86_model
op_eq
l_int|9
op_logical_or
(paren
id|c-&gt;x86_model
op_eq
l_int|8
op_logical_and
id|c-&gt;x86_mask
op_ge
l_int|8
)paren
)paren
id|set_bit
c_func
(paren
id|X86_FEATURE_K6_MTRR
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* An Athlon/Duron */
multiline_comment|/* Bit 15 of Athlon specific MSR 15, needs to be 0&n; &t;&t;&t; * to enable SSE on Palomino/Morgan CPU&squot;s.&n;&t;&t;&t; * If the BIOS didn&squot;t enable it already, enable it&n;&t;&t;&t; * here.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|6
op_logical_or
id|c-&gt;x86_model
op_eq
l_int|7
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_XMM
comma
id|c-&gt;x86_capability
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enabling disabled K7/SSE Support.&bslash;n&quot;
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_K7_HWCR
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|l
op_and_assign
op_complement
l_int|0x00008000
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K7_HWCR
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|X86_FEATURE_XMM
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
id|display_cacheinfo
c_func
(paren
id|c
)paren
suffix:semicolon
singleline_comment|//&t;return r;
)brace
DECL|function|amd_size_cache
r_static
r_int
r_int
id|amd_size_cache
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
comma
r_int
r_int
id|size
)paren
(brace
multiline_comment|/* AMD errata T13 (order #21922) */
r_if
c_cond
(paren
(paren
id|c-&gt;x86
op_eq
l_int|6
)paren
)paren
(brace
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|3
op_logical_and
id|c-&gt;x86_mask
op_eq
l_int|0
)paren
multiline_comment|/* Duron Rev A0 */
id|size
op_assign
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|4
op_logical_and
(paren
id|c-&gt;x86_mask
op_eq
l_int|0
op_logical_or
id|c-&gt;x86_mask
op_eq
l_int|1
)paren
)paren
multiline_comment|/* Tbird rev A1/A2 */
id|size
op_assign
l_int|256
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|amd_cpu_dev
id|__initdata
op_assign
(brace
dot
id|c_vendor
op_assign
l_string|&quot;AMD&quot;
comma
dot
id|c_ident
op_assign
(brace
l_string|&quot;AuthenticAMD&quot;
)brace
comma
id|c_models
suffix:colon
(brace
(brace
id|X86_VENDOR_AMD
comma
l_int|4
comma
(brace
(braket
l_int|3
)braket
l_string|&quot;486 DX/2&quot;
comma
(braket
l_int|7
)braket
l_string|&quot;486 DX/2-WB&quot;
comma
(braket
l_int|8
)braket
l_string|&quot;486 DX/4&quot;
comma
(braket
l_int|9
)braket
l_string|&quot;486 DX/4-WB&quot;
comma
(braket
l_int|14
)braket
l_string|&quot;Am5x86-WT&quot;
comma
(braket
l_int|15
)braket
l_string|&quot;Am5x86-WB&quot;
)brace
)brace
comma
)brace
comma
dot
id|c_init
op_assign
id|init_amd
comma
dot
id|c_identify
op_assign
id|generic_identify
comma
dot
id|c_size_cache
op_assign
id|amd_size_cache
comma
)brace
suffix:semicolon
DECL|function|amd_init_cpu
r_int
id|__init
id|amd_init_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_AMD
)braket
op_assign
op_amp
id|amd_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//early_arch_initcall(amd_init_cpu);
eof
