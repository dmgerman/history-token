macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;cpu.h&quot;
r_extern
r_int
id|trap_init_f00f_bug
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_INTEL_USERCOPY
multiline_comment|/*&n; * Alignment at which movsl is preferred for bulk memory copies.&n; */
DECL|variable|movsl_mask
r_struct
id|movsl_mask
id|movsl_mask
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Early probe support logic for ppro memory erratum #50&n; *&n; *&t;This is called before we do cpu ident work&n; */
DECL|function|ppro_with_ram_bug
r_int
id|__init
id|ppro_with_ram_bug
c_func
(paren
r_void
)paren
(brace
r_char
id|vendor_id
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|ident
suffix:semicolon
multiline_comment|/* Must have CPUID */
r_if
c_cond
(paren
op_logical_neg
id|have_cpuid_p
c_func
(paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpuid_eax
c_func
(paren
l_int|0
)paren
OL
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must be Intel */
id|cpuid
c_func
(paren
l_int|0
comma
op_amp
id|ident
comma
(paren
r_int
op_star
)paren
op_amp
id|vendor_id
(braket
l_int|0
)braket
comma
(paren
r_int
op_star
)paren
op_amp
id|vendor_id
(braket
l_int|8
)braket
comma
(paren
r_int
op_star
)paren
op_amp
id|vendor_id
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|vendor_id
comma
l_string|&quot;IntelInside&quot;
comma
l_int|12
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|ident
op_assign
id|cpuid_eax
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Model 6 */
r_if
c_cond
(paren
(paren
(paren
id|ident
op_rshift
l_int|8
)paren
op_amp
l_int|15
)paren
op_ne
l_int|6
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Pentium Pro */
r_if
c_cond
(paren
(paren
(paren
id|ident
op_rshift
l_int|4
)paren
op_amp
l_int|15
)paren
op_ne
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ident
op_amp
l_int|15
)paren
OL
l_int|8
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Pentium Pro with Errata#50 detected. Taking evasive action.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Your Pentium Pro seems ok.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|LVL_1_INST
mdefine_line|#define LVL_1_INST&t;1
DECL|macro|LVL_1_DATA
mdefine_line|#define LVL_1_DATA&t;2
DECL|macro|LVL_2
mdefine_line|#define LVL_2&t;&t;3
DECL|macro|LVL_3
mdefine_line|#define LVL_3&t;&t;4
DECL|macro|LVL_TRACE
mdefine_line|#define LVL_TRACE&t;5
DECL|struct|_cache_table
r_struct
id|_cache_table
(brace
DECL|member|descriptor
r_int
r_char
id|descriptor
suffix:semicolon
DECL|member|cache_type
r_char
id|cache_type
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* all the cache descriptor types we care about (no TLB or trace cache entries) */
DECL|variable|__initdata
r_static
r_struct
id|_cache_table
id|cache_table
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0x06
comma
id|LVL_1_INST
comma
l_int|8
)brace
comma
(brace
l_int|0x08
comma
id|LVL_1_INST
comma
l_int|16
)brace
comma
(brace
l_int|0x0a
comma
id|LVL_1_DATA
comma
l_int|8
)brace
comma
(brace
l_int|0x0c
comma
id|LVL_1_DATA
comma
l_int|16
)brace
comma
(brace
l_int|0x22
comma
id|LVL_3
comma
l_int|512
)brace
comma
(brace
l_int|0x23
comma
id|LVL_3
comma
l_int|1024
)brace
comma
(brace
l_int|0x25
comma
id|LVL_3
comma
l_int|2048
)brace
comma
(brace
l_int|0x29
comma
id|LVL_3
comma
l_int|4096
)brace
comma
(brace
l_int|0x2c
comma
id|LVL_1_DATA
comma
l_int|32
)brace
comma
(brace
l_int|0x30
comma
id|LVL_1_INST
comma
l_int|32
)brace
comma
(brace
l_int|0x39
comma
id|LVL_2
comma
l_int|128
)brace
comma
(brace
l_int|0x3b
comma
id|LVL_2
comma
l_int|128
)brace
comma
(brace
l_int|0x3c
comma
id|LVL_2
comma
l_int|256
)brace
comma
(brace
l_int|0x41
comma
id|LVL_2
comma
l_int|128
)brace
comma
(brace
l_int|0x42
comma
id|LVL_2
comma
l_int|256
)brace
comma
(brace
l_int|0x43
comma
id|LVL_2
comma
l_int|512
)brace
comma
(brace
l_int|0x44
comma
id|LVL_2
comma
l_int|1024
)brace
comma
(brace
l_int|0x45
comma
id|LVL_2
comma
l_int|2048
)brace
comma
(brace
l_int|0x66
comma
id|LVL_1_DATA
comma
l_int|8
)brace
comma
(brace
l_int|0x67
comma
id|LVL_1_DATA
comma
l_int|16
)brace
comma
(brace
l_int|0x68
comma
id|LVL_1_DATA
comma
l_int|32
)brace
comma
(brace
l_int|0x70
comma
id|LVL_TRACE
comma
l_int|12
)brace
comma
(brace
l_int|0x71
comma
id|LVL_TRACE
comma
l_int|16
)brace
comma
(brace
l_int|0x72
comma
id|LVL_TRACE
comma
l_int|32
)brace
comma
(brace
l_int|0x79
comma
id|LVL_2
comma
l_int|128
)brace
comma
(brace
l_int|0x7a
comma
id|LVL_2
comma
l_int|256
)brace
comma
(brace
l_int|0x7b
comma
id|LVL_2
comma
l_int|512
)brace
comma
(brace
l_int|0x7c
comma
id|LVL_2
comma
l_int|1024
)brace
comma
(brace
l_int|0x82
comma
id|LVL_2
comma
l_int|256
)brace
comma
(brace
l_int|0x83
comma
id|LVL_2
comma
l_int|512
)brace
comma
(brace
l_int|0x84
comma
id|LVL_2
comma
l_int|1024
)brace
comma
(brace
l_int|0x85
comma
id|LVL_2
comma
l_int|2048
)brace
comma
(brace
l_int|0x86
comma
id|LVL_2
comma
l_int|512
)brace
comma
(brace
l_int|0x87
comma
id|LVL_2
comma
l_int|1024
)brace
comma
(brace
l_int|0x00
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * P4 Xeon errata 037 workaround.&n; * Hardware prefetcher may cause stale data to be loaded into the cache.&n; */
DECL|function|Intel_errata_workarounds
r_static
r_void
id|__init
id|Intel_errata_workarounds
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
r_int
id|lo
comma
id|hi
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;x86
op_eq
l_int|15
)paren
op_logical_and
(paren
id|c-&gt;x86_model
op_eq
l_int|1
)paren
op_logical_and
(paren
id|c-&gt;x86_mask
op_eq
l_int|1
)paren
)paren
(brace
id|rdmsr
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lo
op_amp
(paren
l_int|1
op_lshift
l_int|9
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: C0 stepping P4 Xeon detected.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: Disabling hardware prefetching (Errata 037)&bslash;n&quot;
)paren
suffix:semicolon
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/* Disable hw prefetching */
id|wrmsr
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|init_intel
r_static
r_void
id|__init
id|init_intel
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_char
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|trace
op_assign
l_int|0
comma
id|l1i
op_assign
l_int|0
comma
id|l1d
op_assign
l_int|0
comma
id|l2
op_assign
l_int|0
comma
id|l3
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Cache sizes */
macro_line|#ifdef CONFIG_X86_F00F_BUG
multiline_comment|/*&n;&t; * All current models of Pentium and Pentium with MMX technology CPUs&n;&t; * have the F0 0F bug, which lets nonprivileged users lock up the system.&n;&t; * Note that the workaround only should be initialized once...&n;&t; */
id|c-&gt;f00f_bug
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|5
)paren
(brace
r_static
r_int
id|f00f_workaround_enabled
op_assign
l_int|0
suffix:semicolon
id|c-&gt;f00f_bug
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f00f_workaround_enabled
)paren
(brace
id|trap_init_f00f_bug
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Intel Pentium with F0 0F bug - workaround enabled.&bslash;n&quot;
)paren
suffix:semicolon
id|f00f_workaround_enabled
op_assign
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|c-&gt;cpuid_level
OG
l_int|1
)paren
(brace
multiline_comment|/* supports eax=2  call */
r_int
id|i
comma
id|j
comma
id|n
suffix:semicolon
r_int
id|regs
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_char
op_star
id|dp
op_assign
(paren
r_int
r_char
op_star
)paren
id|regs
suffix:semicolon
multiline_comment|/* Number of times to iterate */
id|n
op_assign
id|cpuid_eax
c_func
(paren
l_int|2
)paren
op_amp
l_int|0xFF
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cpuid
c_func
(paren
l_int|2
comma
op_amp
id|regs
(braket
l_int|0
)braket
comma
op_amp
id|regs
(braket
l_int|1
)braket
comma
op_amp
id|regs
(braket
l_int|2
)braket
comma
op_amp
id|regs
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* If bit 31 is set, this is an unknown format */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|3
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|regs
(braket
id|j
)braket
OL
l_int|0
)paren
id|regs
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Byte 0 is level count, not a descriptor */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
r_char
id|des
op_assign
id|dp
(braket
id|j
)braket
suffix:semicolon
r_int
r_char
id|k
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* look up this descriptor in the table */
r_while
c_loop
(paren
id|cache_table
(braket
id|k
)braket
dot
id|descriptor
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cache_table
(braket
id|k
)braket
dot
id|descriptor
op_eq
id|des
)paren
(brace
r_switch
c_cond
(paren
id|cache_table
(braket
id|k
)braket
dot
id|cache_type
)paren
(brace
r_case
id|LVL_1_INST
suffix:colon
id|l1i
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_1_DATA
suffix:colon
id|l1d
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_2
suffix:colon
id|l2
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_3
suffix:colon
id|l3
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_TRACE
suffix:colon
id|trace
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|k
op_increment
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|trace
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: Trace cache: %dK uops&quot;
comma
id|trace
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|l1i
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: L1 I cache: %dK&quot;
comma
id|l1i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l1d
)paren
id|printk
c_func
(paren
l_string|&quot;, L1 D cache: %dK&bslash;n&quot;
comma
id|l1d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l2
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: L2 cache: %dK&bslash;n&quot;
comma
id|l2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l3
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: L3 cache: %dK&bslash;n&quot;
comma
id|l3
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This assumes the L3 cache is shared; it typically lives in&n;&t;&t; * the northbridge.  The L1 caches are included by the L2&n;&t;&t; * cache, and so should not be included for the purpose of&n;&t;&t; * SMP switching weights.&n;&t;&t; */
id|c-&gt;x86_cache_size
op_assign
id|l2
ques
c_cond
id|l2
suffix:colon
(paren
id|l1i
op_plus
id|l1d
)paren
suffix:semicolon
)brace
multiline_comment|/* SEP CPUID bug: Pentium Pro reports SEP but doesn&squot;t have it */
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|6
op_logical_and
id|c-&gt;x86_model
OL
l_int|3
op_logical_and
id|c-&gt;x86_mask
OL
l_int|3
)paren
id|clear_bit
c_func
(paren
id|X86_FEATURE_SEP
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
multiline_comment|/* Names for the Pentium II/Celeron processors &n;&t;   detectable only by also checking the cache size.&n;&t;   Dixon is NOT a Celeron. */
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|6
)paren
(brace
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|5
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86_mask
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|l2
op_eq
l_int|0
)paren
id|p
op_assign
l_string|&quot;Celeron (Covington)&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|l2
op_eq
l_int|256
)paren
id|p
op_assign
l_string|&quot;Mobile Pentium II (Dixon)&quot;
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|l2
op_eq
l_int|128
)paren
id|p
op_assign
l_string|&quot;Celeron (Mendocino)&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c-&gt;x86_mask
op_eq
l_int|0
op_logical_or
id|c-&gt;x86_mask
op_eq
l_int|5
)paren
id|p
op_assign
l_string|&quot;Celeron-A&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_if
c_cond
(paren
id|l2
op_eq
l_int|128
)paren
id|p
op_assign
l_string|&quot;Celeron (Coppermine)&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|p
)paren
id|strcpy
c_func
(paren
id|c-&gt;x86_model_id
comma
id|p
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_HT
r_if
c_cond
(paren
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_HT
)paren
)paren
(brace
r_extern
r_int
id|phys_proc_id
(braket
id|NR_CPUS
)braket
suffix:semicolon
id|u32
id|eax
comma
id|ebx
comma
id|ecx
comma
id|edx
suffix:semicolon
r_int
id|index_lsb
comma
id|index_msb
comma
id|tmp
suffix:semicolon
r_int
id|initial_apic_id
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|cpuid
c_func
(paren
l_int|1
comma
op_amp
id|eax
comma
op_amp
id|ebx
comma
op_amp
id|ecx
comma
op_amp
id|edx
)paren
suffix:semicolon
id|smp_num_siblings
op_assign
(paren
id|ebx
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|smp_num_siblings
op_eq
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: Hyper-Threading is disabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|smp_num_siblings
OG
l_int|1
)paren
(brace
id|index_lsb
op_assign
l_int|0
suffix:semicolon
id|index_msb
op_assign
l_int|31
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * At this point we only support two siblings per&n;&t;&t;&t; * processor package.&n;&t;&t;&t; */
DECL|macro|NR_SIBLINGS
mdefine_line|#define NR_SIBLINGS&t;2
r_if
c_cond
(paren
id|smp_num_siblings
op_ne
id|NR_SIBLINGS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;CPU: Unsupported number of the siblings %d&quot;
comma
id|smp_num_siblings
)paren
suffix:semicolon
id|smp_num_siblings
op_assign
l_int|1
suffix:semicolon
r_goto
id|too_many_siblings
suffix:semicolon
)brace
id|tmp
op_assign
id|smp_num_siblings
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|tmp
op_rshift_assign
l_int|1
suffix:semicolon
id|index_lsb
op_increment
suffix:semicolon
)brace
id|tmp
op_assign
id|smp_num_siblings
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_amp
l_int|0x80000000
)paren
op_eq
l_int|0
)paren
(brace
id|tmp
op_lshift_assign
l_int|1
suffix:semicolon
id|index_msb
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index_lsb
op_ne
id|index_msb
)paren
id|index_msb
op_increment
suffix:semicolon
id|initial_apic_id
op_assign
id|ebx
op_rshift
l_int|24
op_amp
l_int|0xff
suffix:semicolon
id|phys_proc_id
(braket
id|cpu
)braket
op_assign
id|initial_apic_id
op_rshift
id|index_msb
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: Physical Processor ID: %d&bslash;n&quot;
comma
id|phys_proc_id
(braket
id|cpu
)braket
)paren
suffix:semicolon
)brace
)brace
id|too_many_siblings
suffix:colon
macro_line|#endif
multiline_comment|/* Work around errata */
id|Intel_errata_workarounds
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_INTEL_USERCOPY
multiline_comment|/*&n;&t; * Set up the preferred alignment for movsl bulk memory moves&n;&t; */
r_switch
c_cond
(paren
id|c-&gt;x86
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 486: untested */
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* Old Pentia: untested */
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* PII/PIII only like movsl with 8-byte alignment */
id|movsl_mask.mask
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
multiline_comment|/* P4 is OK down to 8-byte alignment */
id|movsl_mask.mask
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|15
)paren
id|set_bit
c_func
(paren
id|X86_FEATURE_P4
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|6
)paren
id|set_bit
c_func
(paren
id|X86_FEATURE_P3
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
DECL|function|intel_size_cache
r_static
r_int
r_int
id|intel_size_cache
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
multiline_comment|/* Intel PIII Tualatin. This comes in two flavours.&n;&t; * One has 256kb of cache, the other 512. We have no way&n;&t; * to determine which, so we use a boottime override&n;&t; * for the 512kb model, and assume 256 otherwise.&n;&t; */
r_if
c_cond
(paren
(paren
id|c-&gt;x86
op_eq
l_int|6
)paren
op_logical_and
(paren
id|c-&gt;x86_model
op_eq
l_int|11
)paren
op_logical_and
(paren
id|size
op_eq
l_int|0
)paren
)paren
id|size
op_assign
l_int|256
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|intel_cpu_dev
id|__initdata
op_assign
(brace
dot
id|c_vendor
op_assign
l_string|&quot;Intel&quot;
comma
dot
id|c_ident
op_assign
(brace
l_string|&quot;GenuineIntel&quot;
)brace
comma
dot
id|c_models
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|X86_VENDOR_INTEL
comma
dot
id|family
op_assign
l_int|4
comma
dot
id|model_names
op_assign
(brace
(braket
l_int|0
)braket
op_assign
l_string|&quot;486 DX-25/33&quot;
comma
(braket
l_int|1
)braket
op_assign
l_string|&quot;486 DX-50&quot;
comma
(braket
l_int|2
)braket
op_assign
l_string|&quot;486 SX&quot;
comma
(braket
l_int|3
)braket
op_assign
l_string|&quot;486 DX/2&quot;
comma
(braket
l_int|4
)braket
op_assign
l_string|&quot;486 SL&quot;
comma
(braket
l_int|5
)braket
op_assign
l_string|&quot;486 SX/2&quot;
comma
(braket
l_int|7
)braket
op_assign
l_string|&quot;486 DX/2-WB&quot;
comma
(braket
l_int|8
)braket
op_assign
l_string|&quot;486 DX/4&quot;
comma
(braket
l_int|9
)braket
op_assign
l_string|&quot;486 DX/4-WB&quot;
)brace
)brace
comma
(brace
dot
id|vendor
op_assign
id|X86_VENDOR_INTEL
comma
dot
id|family
op_assign
l_int|5
comma
dot
id|model_names
op_assign
(brace
(braket
l_int|0
)braket
op_assign
l_string|&quot;Pentium 60/66 A-step&quot;
comma
(braket
l_int|1
)braket
op_assign
l_string|&quot;Pentium 60/66&quot;
comma
(braket
l_int|2
)braket
op_assign
l_string|&quot;Pentium 75 - 200&quot;
comma
(braket
l_int|3
)braket
op_assign
l_string|&quot;OverDrive PODP5V83&quot;
comma
(braket
l_int|4
)braket
op_assign
l_string|&quot;Pentium MMX&quot;
comma
(braket
l_int|7
)braket
op_assign
l_string|&quot;Mobile Pentium 75 - 200&quot;
comma
(braket
l_int|8
)braket
op_assign
l_string|&quot;Mobile Pentium MMX&quot;
)brace
)brace
comma
(brace
dot
id|vendor
op_assign
id|X86_VENDOR_INTEL
comma
dot
id|family
op_assign
l_int|6
comma
dot
id|model_names
op_assign
(brace
(braket
l_int|0
)braket
op_assign
l_string|&quot;Pentium Pro A-step&quot;
comma
(braket
l_int|1
)braket
op_assign
l_string|&quot;Pentium Pro&quot;
comma
(braket
l_int|3
)braket
op_assign
l_string|&quot;Pentium II (Klamath)&quot;
comma
(braket
l_int|4
)braket
op_assign
l_string|&quot;Pentium II (Deschutes)&quot;
comma
(braket
l_int|5
)braket
op_assign
l_string|&quot;Pentium II (Deschutes)&quot;
comma
(braket
l_int|6
)braket
op_assign
l_string|&quot;Mobile Pentium II&quot;
comma
(braket
l_int|7
)braket
op_assign
l_string|&quot;Pentium III (Katmai)&quot;
comma
(braket
l_int|8
)braket
op_assign
l_string|&quot;Pentium III (Coppermine)&quot;
comma
(braket
l_int|10
)braket
op_assign
l_string|&quot;Pentium III (Cascades)&quot;
comma
(braket
l_int|11
)braket
op_assign
l_string|&quot;Pentium III (Tualatin)&quot;
comma
)brace
)brace
comma
(brace
dot
id|vendor
op_assign
id|X86_VENDOR_INTEL
comma
dot
id|family
op_assign
l_int|15
comma
dot
id|model_names
op_assign
(brace
(braket
l_int|0
)braket
op_assign
l_string|&quot;Pentium 4 (Unknown)&quot;
comma
(braket
l_int|1
)braket
op_assign
l_string|&quot;Pentium 4 (Willamette)&quot;
comma
(braket
l_int|2
)braket
op_assign
l_string|&quot;Pentium 4 (Northwood)&quot;
comma
(braket
l_int|4
)braket
op_assign
l_string|&quot;Pentium 4 (Foster)&quot;
comma
(braket
l_int|5
)braket
op_assign
l_string|&quot;Pentium 4 (Foster)&quot;
comma
)brace
)brace
comma
)brace
comma
dot
id|c_init
op_assign
id|init_intel
comma
dot
id|c_identify
op_assign
id|generic_identify
comma
dot
id|c_size_cache
op_assign
id|intel_size_cache
comma
)brace
suffix:semicolon
DECL|function|intel_cpu_init
id|__init
r_int
id|intel_cpu_init
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_INTEL
)braket
op_assign
op_amp
id|intel_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// arch_initcall(intel_cpu_init);
eof
