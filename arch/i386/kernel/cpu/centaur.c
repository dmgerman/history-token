macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;cpu.h&quot;
macro_line|#ifdef CONFIG_X86_OOSTORE
DECL|function|power2
r_static
id|u32
id|__init
id|power2
c_func
(paren
id|u32
id|x
)paren
(brace
id|u32
id|s
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|s
op_le
id|x
)paren
(brace
id|s
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|s
op_rshift_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set up an actual MCR&n; */
DECL|function|centaur_mcr_insert
r_static
r_void
id|__init
id|centaur_mcr_insert
c_func
(paren
r_int
id|reg
comma
id|u32
id|base
comma
id|u32
id|size
comma
r_int
id|key
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
id|hi
op_assign
id|base
op_amp
op_complement
l_int|0xFFF
suffix:semicolon
id|lo
op_assign
op_complement
(paren
id|size
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Size is a power of 2 so this makes a mask */
id|lo
op_and_assign
op_complement
l_int|0xFFF
suffix:semicolon
multiline_comment|/* Remove the ctrl value bits */
id|lo
op_or_assign
id|key
suffix:semicolon
multiline_comment|/* Attribute we wish to set */
id|wrmsr
c_func
(paren
id|reg
op_plus
id|MSR_IDT_MCR0
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|mtrr_centaur_report_mcr
c_func
(paren
id|reg
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
multiline_comment|/* Tell the mtrr driver */
)brace
multiline_comment|/*&n; *&t;Figure what we can cover with MCR&squot;s&n; *&n; *&t;Shortcut: We know you can&squot;t put 4Gig of RAM on a winchip&n; */
DECL|function|ramtop
r_static
id|u32
id|__init
id|ramtop
c_func
(paren
r_void
)paren
multiline_comment|/* 16388 */
(brace
r_int
id|i
suffix:semicolon
id|u32
id|top
op_assign
l_int|0
suffix:semicolon
id|u32
id|clip
op_assign
l_int|0xFFFFFFFFUL
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
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
OG
l_int|0xFFFFFFFFUL
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Don&squot;t MCR over reserved space. Ignore the ISA hole&n;&t;&t; *&t;we frob around that catastrophy already&n;&t;&t; */
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
op_eq
id|E820_RESERVED
)paren
(brace
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_ge
l_int|0x100000UL
op_logical_and
id|e820.map
(braket
id|i
)braket
dot
id|addr
OL
id|clip
)paren
(brace
id|clip
op_assign
id|e820.map
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|start
op_assign
id|e820.map
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|end
op_assign
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|e820.map
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|top
)paren
id|top
op_assign
id|end
suffix:semicolon
)brace
multiline_comment|/* Everything below &squot;top&squot; should be RAM except for the ISA hole.&n;&t;   Because of the limited MCR&squot;s we want to map NV/ACPI into our&n;&t;   MCR range for gunk in RAM &n;&t;   &n;&t;   Clip might cause us to MCR insufficient RAM but that is an&n;&t;   acceptable failure mode and should only bite obscure boxes with&n;&t;   a VESA hole at 15Mb&n;&t;   &n;&t;   The second case Clip sometimes kicks in is when the EBDA is marked&n;&t;   as reserved. Again we fail safe with reasonable results&n;&t;*/
r_if
c_cond
(paren
id|top
OG
id|clip
)paren
(brace
id|top
op_assign
id|clip
suffix:semicolon
)brace
r_return
id|top
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Compute a set of MCR&squot;s to give maximum coverage&n; */
DECL|function|centaur_mcr_compute
r_static
r_int
id|__init
id|centaur_mcr_compute
c_func
(paren
r_int
id|nr
comma
r_int
id|key
)paren
(brace
id|u32
id|mem
op_assign
id|ramtop
c_func
(paren
)paren
suffix:semicolon
id|u32
id|root
op_assign
id|power2
c_func
(paren
id|mem
)paren
suffix:semicolon
id|u32
id|base
op_assign
id|root
suffix:semicolon
id|u32
id|top
op_assign
id|root
suffix:semicolon
id|u32
id|floor
op_assign
l_int|0
suffix:semicolon
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ct
OL
id|nr
)paren
(brace
id|u32
id|fspace
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Find the largest block we will fill going upwards&n;&t;&t; */
id|u32
id|high
op_assign
id|power2
c_func
(paren
id|mem
op_minus
id|top
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Find the largest block we will fill going downwards&n;&t;&t; */
id|u32
id|low
op_assign
id|base
op_div
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Don&squot;t fill below 1Mb going downwards as there&n;&t;&t; *&t;is an ISA hole in the way.&n;&t;&t; */
r_if
c_cond
(paren
id|base
op_le
l_int|1024
op_star
l_int|1024
)paren
(brace
id|low
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;See how much space we could cover by filling below&n;&t;&t; *&t;the ISA hole&n;&t;&t; */
r_if
c_cond
(paren
id|floor
op_eq
l_int|0
)paren
(brace
id|fspace
op_assign
l_int|512
op_star
l_int|1024
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|floor
op_eq
l_int|512
op_star
l_int|1024
)paren
(brace
id|fspace
op_assign
l_int|128
op_star
l_int|1024
suffix:semicolon
)brace
multiline_comment|/* And forget ROM space */
multiline_comment|/*&n;&t;&t; *&t;Now install the largest coverage we get&n;&t;&t; */
r_if
c_cond
(paren
id|fspace
OG
id|high
op_logical_and
id|fspace
OG
id|low
)paren
(brace
id|centaur_mcr_insert
c_func
(paren
id|ct
comma
id|floor
comma
id|fspace
comma
id|key
)paren
suffix:semicolon
id|floor
op_add_assign
id|fspace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|high
OG
id|low
)paren
(brace
id|centaur_mcr_insert
c_func
(paren
id|ct
comma
id|top
comma
id|high
comma
id|key
)paren
suffix:semicolon
id|top
op_add_assign
id|high
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|low
OG
l_int|0
)paren
(brace
id|base
op_sub_assign
id|low
suffix:semicolon
id|centaur_mcr_insert
c_func
(paren
id|ct
comma
id|base
comma
id|low
comma
id|key
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
id|ct
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;We loaded ct values. We now need to set the mask. The caller&n;&t; *&t;must do this bit.&n;&t; */
r_return
id|ct
suffix:semicolon
)brace
DECL|function|centaur_create_optimal_mcr
r_static
r_void
id|__init
id|centaur_create_optimal_mcr
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate up to 6 mcrs to mark as much of ram as possible&n;&t; *&t;as write combining and weak write ordered.&n;&t; *&n;&t; *&t;To experiment with: Linux never uses stack operations for &n;&t; *&t;mmio spaces so we could globally enable stack operation wc&n;&t; *&n;&t; *&t;Load the registers with type 31 - full write combining, all&n;&t; *&t;writes weakly ordered.&n;&t; */
r_int
id|used
op_assign
id|centaur_mcr_compute
c_func
(paren
l_int|6
comma
l_int|31
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Wipe unused MCRs&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|used
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR0
op_plus
id|i
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|winchip2_create_optimal_mcr
r_static
r_void
id|__init
id|winchip2_create_optimal_mcr
c_func
(paren
r_void
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate up to 6 mcrs to mark as much of ram as possible&n;&t; *&t;as write combining, weak store ordered.&n;&t; *&n;&t; *&t;Load the registers with type 25&n;&t; *&t;&t;8&t;-&t;weak write ordering&n;&t; *&t;&t;16&t;-&t;weak read ordering&n;&t; *&t;&t;1&t;-&t;write combining&n;&t; */
r_int
id|used
op_assign
id|centaur_mcr_compute
c_func
(paren
l_int|6
comma
l_int|25
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Mark the registers we are using.&n;&t; */
id|rdmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
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
id|used
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lo
op_or_assign
l_int|1
op_lshift
(paren
l_int|9
op_plus
id|i
)paren
suffix:semicolon
)brace
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Wipe unused MCRs&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|used
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR0
op_plus
id|i
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Handle the MCR key on the Winchip 2.&n; */
DECL|function|winchip2_unprotect_mcr
r_static
r_void
id|__init
id|winchip2_unprotect_mcr
c_func
(paren
r_void
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
id|u32
id|key
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
l_int|0x1C0
suffix:semicolon
multiline_comment|/* blank bits 8-6 */
id|key
op_assign
(paren
id|lo
op_rshift
l_int|17
)paren
op_amp
l_int|7
suffix:semicolon
id|lo
op_or_assign
id|key
op_lshift
l_int|6
suffix:semicolon
multiline_comment|/* replace with unlock key */
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
)brace
DECL|function|winchip2_protect_mcr
r_static
r_void
id|__init
id|winchip2_protect_mcr
c_func
(paren
r_void
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
l_int|0x1C0
suffix:semicolon
multiline_comment|/* blank bits 8-6 */
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|init_centaur
r_static
r_void
id|__init
id|init_centaur
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_enum
(brace
id|ECX8
op_assign
l_int|1
op_lshift
l_int|1
comma
id|EIERRINT
op_assign
l_int|1
op_lshift
l_int|2
comma
id|DPM
op_assign
l_int|1
op_lshift
l_int|3
comma
id|DMCE
op_assign
l_int|1
op_lshift
l_int|4
comma
id|DSTPCLK
op_assign
l_int|1
op_lshift
l_int|5
comma
id|ELINEAR
op_assign
l_int|1
op_lshift
l_int|6
comma
id|DSMC
op_assign
l_int|1
op_lshift
l_int|7
comma
id|DTLOCK
op_assign
l_int|1
op_lshift
l_int|8
comma
id|EDCTLB
op_assign
l_int|1
op_lshift
l_int|8
comma
id|EMMX
op_assign
l_int|1
op_lshift
l_int|9
comma
id|DPDC
op_assign
l_int|1
op_lshift
l_int|11
comma
id|EBRPRED
op_assign
l_int|1
op_lshift
l_int|12
comma
id|DIC
op_assign
l_int|1
op_lshift
l_int|13
comma
id|DDC
op_assign
l_int|1
op_lshift
l_int|14
comma
id|DNA
op_assign
l_int|1
op_lshift
l_int|15
comma
id|ERETSTK
op_assign
l_int|1
op_lshift
l_int|16
comma
id|E2MMX
op_assign
l_int|1
op_lshift
l_int|19
comma
id|EAMD3D
op_assign
l_int|1
op_lshift
l_int|20
comma
)brace
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
id|u32
id|fcr_set
op_assign
l_int|0
suffix:semicolon
id|u32
id|fcr_clr
op_assign
l_int|0
suffix:semicolon
id|u32
id|lo
comma
id|hi
comma
id|newlo
suffix:semicolon
id|u32
id|aa
comma
id|bb
comma
id|cc
comma
id|dd
suffix:semicolon
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
r_switch
c_cond
(paren
id|c-&gt;x86
)paren
(brace
r_case
l_int|5
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|4
suffix:colon
id|name
op_assign
l_string|&quot;C6&quot;
suffix:semicolon
id|fcr_set
op_assign
id|ECX8
op_or
id|DSMC
op_or
id|EDCTLB
op_or
id|EMMX
op_or
id|ERETSTK
suffix:semicolon
id|fcr_clr
op_assign
id|DPDC
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Disabling bugged TSC.&bslash;n&quot;
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|X86_FEATURE_TSC
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_OOSTORE
id|centaur_create_optimal_mcr
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Enable&n;&t;&t;&t;&t;&t;write combining on non-stack, non-string&n;&t;&t;&t;&t;&t;write combining on string, all types&n;&t;&t;&t;&t;&t;weak write ordering &n;&t;&t;&t;&t;&t;&n;&t;&t;&t;&t;   The C6 original lacks weak read order &n;&t;&t;&t;&t;   &n;&t;&t;&t;&t;   Note 0x120 is write only on Winchip 1 */
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
l_int|0x01F0001F
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;x86_mask
)paren
(brace
r_default
suffix:colon
id|name
op_assign
l_string|&quot;2&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
dot
dot
dot
l_int|9
suffix:colon
id|name
op_assign
l_string|&quot;2A&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
dot
dot
dot
l_int|15
suffix:colon
id|name
op_assign
l_string|&quot;2B&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fcr_set
op_assign
id|ECX8
op_or
id|DSMC
op_or
id|DTLOCK
op_or
id|EMMX
op_or
id|EBRPRED
op_or
id|ERETSTK
op_or
id|E2MMX
op_or
id|EAMD3D
suffix:semicolon
id|fcr_clr
op_assign
id|DPDC
suffix:semicolon
macro_line|#ifdef CONFIG_X86_OOSTORE
id|winchip2_unprotect_mcr
c_func
(paren
)paren
suffix:semicolon
id|winchip2_create_optimal_mcr
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
multiline_comment|/* Enable&n;&t;&t;&t;&t;&t;write combining on non-stack, non-string&n;&t;&t;&t;&t;&t;write combining on string, all types&n;&t;&t;&t;&t;&t;weak write ordering &n;&t;&t;&t;&t;*/
id|lo
op_or_assign
l_int|31
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|winchip2_protect_mcr
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|name
op_assign
l_string|&quot;3&quot;
suffix:semicolon
id|fcr_set
op_assign
id|ECX8
op_or
id|DSMC
op_or
id|DTLOCK
op_or
id|EMMX
op_or
id|EBRPRED
op_or
id|ERETSTK
op_or
id|E2MMX
op_or
id|EAMD3D
suffix:semicolon
id|fcr_clr
op_assign
id|DPDC
suffix:semicolon
macro_line|#ifdef CONFIG_X86_OOSTORE
id|winchip2_unprotect_mcr
c_func
(paren
)paren
suffix:semicolon
id|winchip2_create_optimal_mcr
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
multiline_comment|/* Enable&n;&t;&t;&t;&t;&t;write combining on non-stack, non-string&n;&t;&t;&t;&t;&t;write combining on string, all types&n;&t;&t;&t;&t;&t;weak write ordering &n;&t;&t;&t;&t;*/
id|lo
op_or_assign
l_int|31
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IDT_MCR_CTRL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|winchip2_protect_mcr
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|name
op_assign
l_string|&quot;4&quot;
suffix:semicolon
multiline_comment|/* no info on the WC4 yet */
r_break
suffix:semicolon
r_default
suffix:colon
id|name
op_assign
l_string|&quot;??&quot;
suffix:semicolon
)brace
id|rdmsr
c_func
(paren
id|MSR_IDT_FCR1
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|newlo
op_assign
(paren
id|lo
op_or
id|fcr_set
)paren
op_amp
(paren
op_complement
id|fcr_clr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newlo
op_ne
id|lo
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Centaur FCR was 0x%X now 0x%X&bslash;n&quot;
comma
id|lo
comma
id|newlo
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IDT_FCR1
comma
id|newlo
comma
id|hi
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Centaur FCR is 0x%X&bslash;n&quot;
comma
id|lo
)paren
suffix:semicolon
)brace
multiline_comment|/* Emulate MTRRs using Centaur&squot;s MCR. */
id|set_bit
c_func
(paren
id|X86_FEATURE_CENTAUR_MCR
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
multiline_comment|/* Report CX8 */
id|set_bit
c_func
(paren
id|X86_FEATURE_CX8
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
multiline_comment|/* Set 3DNow! on Winchip 2 and above. */
r_if
c_cond
(paren
id|c-&gt;x86_model
op_ge
l_int|8
)paren
id|set_bit
c_func
(paren
id|X86_FEATURE_3DNOW
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
multiline_comment|/* See if we can find out some more. */
r_if
c_cond
(paren
id|cpuid_eax
c_func
(paren
l_int|0x80000000
)paren
op_ge
l_int|0x80000005
)paren
(brace
multiline_comment|/* Yes, we can. */
id|cpuid
c_func
(paren
l_int|0x80000005
comma
op_amp
id|aa
comma
op_amp
id|bb
comma
op_amp
id|cc
comma
op_amp
id|dd
)paren
suffix:semicolon
multiline_comment|/* Add L1 data and code cache sizes. */
id|c-&gt;x86_cache_size
op_assign
(paren
id|cc
op_rshift
l_int|24
)paren
op_plus
(paren
id|dd
op_rshift
l_int|24
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|c-&gt;x86_model_id
comma
l_string|&quot;WinChip %s&quot;
comma
id|name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|6
dot
dot
dot
l_int|8
suffix:colon
multiline_comment|/* Cyrix III family */
id|rdmsr
(paren
id|MSR_VIA_FCR
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Report CX8 &amp; enable PGE */
id|wrmsr
(paren
id|MSR_VIA_FCR
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|X86_FEATURE_CX8
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|X86_FEATURE_3DNOW
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
id|get_model_name
c_func
(paren
id|c
)paren
suffix:semicolon
id|display_cacheinfo
c_func
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|centaur_size_cache
r_static
r_int
r_int
id|centaur_size_cache
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
multiline_comment|/* VIA C3 CPUs (670-68F) need further shifting. */
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
(paren
id|c-&gt;x86_model
op_eq
l_int|7
)paren
op_logical_or
(paren
id|c-&gt;x86_model
op_eq
l_int|8
)paren
)paren
)paren
id|size
op_rshift_assign
l_int|8
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|centaur_cpu_dev
id|__initdata
op_assign
(brace
id|c_vendor
suffix:colon
l_string|&quot;Centaur&quot;
comma
id|c_ident
suffix:colon
(brace
l_string|&quot;CentaurHauls&quot;
)brace
comma
id|c_init
suffix:colon
id|init_centaur
comma
id|c_size_cache
suffix:colon
id|centaur_size_cache
comma
)brace
suffix:semicolon
DECL|function|centaur_init_cpu
r_int
id|__init
id|centaur_init_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_CENTAUR
)braket
op_assign
op_amp
id|centaur_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//early_arch_initcall(centaur_init_cpu);
eof