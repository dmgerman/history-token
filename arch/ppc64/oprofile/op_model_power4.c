multiline_comment|/*&n; * Copyright (C) 2004 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
DECL|macro|dbg
mdefine_line|#define dbg(args...)
macro_line|#include &quot;op_impl.h&quot;
DECL|variable|reset_value
r_static
r_int
r_int
id|reset_value
(braket
id|OP_MAX_COUNTER
)braket
suffix:semicolon
DECL|variable|num_counters
r_static
r_int
id|num_counters
suffix:semicolon
DECL|variable|oprofile_running
r_static
r_int
id|oprofile_running
suffix:semicolon
DECL|variable|mmcra_has_sihv
r_static
r_int
id|mmcra_has_sihv
suffix:semicolon
multiline_comment|/* mmcr values are set in power4_reg_setup, used in power4_cpu_setup */
DECL|variable|mmcr0_val
r_static
id|u32
id|mmcr0_val
suffix:semicolon
DECL|variable|mmcr1_val
r_static
id|u64
id|mmcr1_val
suffix:semicolon
DECL|variable|mmcra_val
r_static
id|u32
id|mmcra_val
suffix:semicolon
multiline_comment|/*&n; * Since we do not have an NMI, backtracing through spinlocks is&n; * only a best guess. In light of this, allow it to be disabled at&n; * runtime.&n; */
DECL|variable|backtrace_spinlocks
r_static
r_int
id|backtrace_spinlocks
suffix:semicolon
DECL|function|power4_reg_setup
r_static
r_void
id|power4_reg_setup
c_func
(paren
r_struct
id|op_counter_config
op_star
id|ctr
comma
r_struct
id|op_system_config
op_star
id|sys
comma
r_int
id|num_ctrs
)paren
(brace
r_int
id|i
suffix:semicolon
id|num_counters
op_assign
id|num_ctrs
suffix:semicolon
multiline_comment|/*&n;&t; * SIHV / SIPR bits are only implemented on POWER4+ (GQ) and above.&n;&t; * However we disable it on all POWER4 until we verify it works&n;&t; * (I was seeing some strange behaviour last time I tried).&n;&t; *&n;&t; * It has been verified to work on POWER5 so we enable it there.&n;&t; */
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_MMCRA_SIHV
)paren
)paren
id|mmcra_has_sihv
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * The performance counter event settings are given in the mmcr0,&n;&t; * mmcr1 and mmcra values passed from the user in the&n;&t; * op_system_config structure (sys variable).&n;&t; */
id|mmcr0_val
op_assign
id|sys-&gt;mmcr0
suffix:semicolon
id|mmcr1_val
op_assign
id|sys-&gt;mmcr1
suffix:semicolon
id|mmcra_val
op_assign
id|sys-&gt;mmcra
suffix:semicolon
id|backtrace_spinlocks
op_assign
id|sys-&gt;backtrace_spinlocks
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
id|reset_value
(braket
id|i
)braket
op_assign
l_int|0x80000000UL
op_minus
id|ctr
(braket
id|i
)braket
dot
id|count
suffix:semicolon
multiline_comment|/* setup user and kernel profiling */
r_if
c_cond
(paren
id|sys-&gt;enable_kernel
)paren
id|mmcr0_val
op_and_assign
op_complement
id|MMCR0_KERNEL_DISABLE
suffix:semicolon
r_else
id|mmcr0_val
op_or_assign
id|MMCR0_KERNEL_DISABLE
suffix:semicolon
r_if
c_cond
(paren
id|sys-&gt;enable_user
)paren
id|mmcr0_val
op_and_assign
op_complement
id|MMCR0_PROBLEM_DISABLE
suffix:semicolon
r_else
id|mmcr0_val
op_or_assign
id|MMCR0_PROBLEM_DISABLE
suffix:semicolon
)brace
r_extern
r_void
id|ppc64_enable_pmcs
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|power4_cpu_setup
r_static
r_void
id|power4_cpu_setup
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
r_int
id|mmcr0
op_assign
id|mmcr0_val
suffix:semicolon
r_int
r_int
id|mmcra
op_assign
id|mmcra_val
suffix:semicolon
id|ppc64_enable_pmcs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set the freeze bit */
id|mmcr0
op_or_assign
id|MMCR0_FC
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
id|mmcr0
op_or_assign
id|MMCR0_FCM1
op_or
id|MMCR0_PMXE
op_or
id|MMCR0_FCECE
suffix:semicolon
id|mmcr0
op_or_assign
id|MMCR0_PMC1CE
op_or
id|MMCR0_PMCjCE
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR1
comma
id|mmcr1_val
)paren
suffix:semicolon
id|mmcra
op_or_assign
id|MMCRA_SAMPLE_ENABLE
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCRA
comma
id|mmcra
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;setup on cpu %d, mmcr0 %lx&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mfspr
c_func
(paren
id|SPRN_MMCR0
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;setup on cpu %d, mmcr1 %lx&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mfspr
c_func
(paren
id|SPRN_MMCR1
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;setup on cpu %d, mmcra %lx&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mfspr
c_func
(paren
id|SPRN_MMCRA
)paren
)paren
suffix:semicolon
)brace
DECL|function|power4_start
r_static
r_void
id|power4_start
c_func
(paren
r_struct
id|op_counter_config
op_star
id|ctr
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|mmcr0
suffix:semicolon
multiline_comment|/* set the PMM bit (see comment below) */
id|mtmsrd
c_func
(paren
id|mfmsr
c_func
(paren
)paren
op_or
id|MSR_PMM
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|ctr
(braket
id|i
)braket
dot
id|enabled
)paren
(brace
id|ctr_write
c_func
(paren
id|i
comma
id|reset_value
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctr_write
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|mmcr0
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCR0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We must clear the PMAO bit on some (GQ) chips. Just do it&n;&t; * all the time&n;&t; */
id|mmcr0
op_and_assign
op_complement
id|MMCR0_PMAO
suffix:semicolon
multiline_comment|/*&n;&t; * now clear the freeze bit, counting will not start until we&n;&t; * rfid from this excetion, because only at that point will&n;&t; * the PMM bit be cleared&n;&t; */
id|mmcr0
op_and_assign
op_complement
id|MMCR0_FC
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
id|oprofile_running
op_assign
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;start on cpu %d, mmcr0 %x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mmcr0
)paren
suffix:semicolon
)brace
DECL|function|power4_stop
r_static
r_void
id|power4_stop
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mmcr0
suffix:semicolon
multiline_comment|/* freeze counters */
id|mmcr0
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCR0
)paren
suffix:semicolon
id|mmcr0
op_or_assign
id|MMCR0_FC
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
id|oprofile_running
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;stop on cpu %d, mmcr0 %x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mmcr0
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Fake functions used by canonicalize_pc */
DECL|function|hypervisor_bucket
r_static
r_void
id|__attribute_used__
id|hypervisor_bucket
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|rtas_bucket
r_static
r_void
id|__attribute_used__
id|rtas_bucket
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|kernel_unknown_bucket
r_static
r_void
id|__attribute_used__
id|kernel_unknown_bucket
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|check_spinlock_pc
r_static
r_int
r_int
id|check_spinlock_pc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|profile_pc
)paren
(brace
r_int
r_int
id|pc
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If both the SIAR (sampled instruction) and the perfmon exception&n;&t; * occurred in a spinlock region then we account the sample to the&n;&t; * calling function. This isnt 100% correct, we really need soft&n;&t; * IRQ disable so we always get the perfmon exception at the&n;&t; * point at which the SIAR is set.&n;&t; */
r_if
c_cond
(paren
id|backtrace_spinlocks
op_logical_and
id|in_lock_functions
c_func
(paren
id|pc
)paren
op_logical_and
id|in_lock_functions
c_func
(paren
id|profile_pc
)paren
)paren
r_return
id|regs-&gt;link
suffix:semicolon
r_else
r_return
id|profile_pc
suffix:semicolon
)brace
multiline_comment|/*&n; * On GQ and newer the MMCRA stores the HV and PR bits at the time&n; * the SIAR was sampled. We use that to work out if the SIAR was sampled in&n; * the hypervisor, our exception vectors or RTAS.&n; */
DECL|function|get_pc
r_static
r_int
r_int
id|get_pc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pc
op_assign
id|mfspr
c_func
(paren
id|SPRN_SIAR
)paren
suffix:semicolon
r_int
r_int
id|mmcra
suffix:semicolon
multiline_comment|/* Cant do much about it */
r_if
c_cond
(paren
op_logical_neg
id|mmcra_has_sihv
)paren
r_return
id|check_spinlock_pc
c_func
(paren
id|regs
comma
id|pc
)paren
suffix:semicolon
id|mmcra
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCRA
)paren
suffix:semicolon
multiline_comment|/* Were we in the hypervisor? */
r_if
c_cond
(paren
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES_LPAR
)paren
op_logical_and
(paren
id|mmcra
op_amp
id|MMCRA_SIHV
)paren
)paren
multiline_comment|/* function descriptor madness */
r_return
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|hypervisor_bucket
)paren
suffix:semicolon
multiline_comment|/* We were in userspace, nothing to do */
r_if
c_cond
(paren
id|mmcra
op_amp
id|MMCRA_SIPR
)paren
r_return
id|pc
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_RTAS
multiline_comment|/* Were we in RTAS? */
r_if
c_cond
(paren
id|pc
op_ge
id|rtas.base
op_logical_and
id|pc
OL
(paren
id|rtas.base
op_plus
id|rtas.size
)paren
)paren
multiline_comment|/* function descriptor madness */
r_return
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|rtas_bucket
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Were we in our exception vectors or SLB real mode miss handler? */
r_if
c_cond
(paren
id|pc
OL
l_int|0x1000000UL
)paren
r_return
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|pc
)paren
suffix:semicolon
multiline_comment|/* Not sure where we were */
r_if
c_cond
(paren
id|pc
OL
id|KERNELBASE
)paren
multiline_comment|/* function descriptor madness */
r_return
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|kernel_unknown_bucket
)paren
suffix:semicolon
r_return
id|check_spinlock_pc
c_func
(paren
id|regs
comma
id|pc
)paren
suffix:semicolon
)brace
DECL|function|get_kernel
r_static
r_int
id|get_kernel
c_func
(paren
r_int
r_int
id|pc
)paren
(brace
r_int
id|is_kernel
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mmcra_has_sihv
)paren
(brace
id|is_kernel
op_assign
(paren
id|pc
op_ge
id|KERNELBASE
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|mmcra
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCRA
)paren
suffix:semicolon
id|is_kernel
op_assign
(paren
(paren
id|mmcra
op_amp
id|MMCRA_SIPR
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|is_kernel
suffix:semicolon
)brace
DECL|function|power4_handle_interrupt
r_static
r_void
id|power4_handle_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|op_counter_config
op_star
id|ctr
)paren
(brace
r_int
r_int
id|pc
suffix:semicolon
r_int
id|is_kernel
suffix:semicolon
r_int
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|mmcr0
suffix:semicolon
id|pc
op_assign
id|get_pc
c_func
(paren
id|regs
)paren
suffix:semicolon
id|is_kernel
op_assign
id|get_kernel
c_func
(paren
id|pc
)paren
suffix:semicolon
multiline_comment|/* set the PMM bit (see comment below) */
id|mtmsrd
c_func
(paren
id|mfmsr
c_func
(paren
)paren
op_or
id|MSR_PMM
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
id|val
op_assign
id|ctr_read
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|oprofile_running
op_logical_and
id|ctr
(braket
id|i
)braket
dot
id|enabled
)paren
(brace
id|oprofile_add_pc
c_func
(paren
id|pc
comma
id|is_kernel
comma
id|i
)paren
suffix:semicolon
id|ctr_write
c_func
(paren
id|i
comma
id|reset_value
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctr_write
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
id|mmcr0
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCR0
)paren
suffix:semicolon
multiline_comment|/* reset the perfmon trigger */
id|mmcr0
op_or_assign
id|MMCR0_PMXE
suffix:semicolon
multiline_comment|/*&n;&t; * We must clear the PMAO bit on some (GQ) chips. Just do it&n;&t; * all the time&n;&t; */
id|mmcr0
op_and_assign
op_complement
id|MMCR0_PMAO
suffix:semicolon
multiline_comment|/*&n;&t; * now clear the freeze bit, counting will not start until we&n;&t; * rfid from this exception, because only at that point will&n;&t; * the PMM bit be cleared&n;&t; */
id|mmcr0
op_and_assign
op_complement
id|MMCR0_FC
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
)brace
DECL|variable|op_model_power4
r_struct
id|op_ppc64_model
id|op_model_power4
op_assign
(brace
dot
id|reg_setup
op_assign
id|power4_reg_setup
comma
dot
id|cpu_setup
op_assign
id|power4_cpu_setup
comma
dot
id|start
op_assign
id|power4_start
comma
dot
id|stop
op_assign
id|power4_stop
comma
dot
id|handle_interrupt
op_assign
id|power4_handle_interrupt
comma
)brace
suffix:semicolon
eof
