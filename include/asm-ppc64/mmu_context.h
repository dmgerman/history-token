macro_line|#ifndef __PPC64_MMU_CONTEXT_H
DECL|macro|__PPC64_MMU_CONTEXT_H
mdefine_line|#define __PPC64_MMU_CONTEXT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;&t;
macro_line|#include &lt;linux/mm.h&gt;&t;
macro_line|#include &lt;asm/mmu.h&gt;&t;
macro_line|#include &lt;asm/cputable.h&gt;
multiline_comment|/*&n; * Copyright (C) 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * Every architecture must define this function. It&squot;s the fastest&n; * way of searching a 140-bit bitmap where the first 100 bits are&n; * unlikely to be set. It&squot;s guaranteed that at least one of the 140&n; * bits is cleared.&n; */
DECL|function|sched_find_first_bit
r_static
r_inline
r_int
id|sched_find_first_bit
c_func
(paren
r_int
r_int
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|b
(braket
l_int|0
)braket
)paren
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|b
(braket
l_int|1
)braket
)paren
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|1
)braket
)paren
op_plus
l_int|64
suffix:semicolon
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|2
)braket
)paren
op_plus
l_int|128
suffix:semicolon
)brace
DECL|function|enter_lazy_tlb
r_static
r_inline
r_void
id|enter_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
)brace
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT&t;0
DECL|macro|MAX_CONTEXT
mdefine_line|#define MAX_CONTEXT&t;(0x100000-1)
r_extern
r_int
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|switch_stab
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|switch_slb
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n; * switch_mm is the entry point called from the architecture independent&n; * code in kernel/sched.c&n; */
DECL|function|switch_mm
r_static
r_inline
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
macro_line|#ifdef CONFIG_ALTIVEC
id|asm
r_volatile
(paren
id|BEGIN_FTR_SECTION
l_string|&quot;dssall;&bslash;n&quot;
id|END_FTR_SECTION_IFSET
c_func
(paren
id|CPU_FTR_ALTIVEC
)paren
suffix:colon
suffix:colon
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|next-&gt;cpu_vm_mask
)paren
)paren
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|next-&gt;cpu_vm_mask
)paren
suffix:semicolon
multiline_comment|/* No need to flush userspace segments if the mm doesnt change */
r_if
c_cond
(paren
id|prev
op_eq
id|next
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SLB
)paren
id|switch_slb
c_func
(paren
id|tsk
comma
id|next
)paren
suffix:semicolon
r_else
id|switch_stab
c_func
(paren
id|tsk
comma
id|next
)paren
suffix:semicolon
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;do { } while (0)
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|function|activate_mm
r_static
r_inline
r_void
id|activate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|switch_mm
c_func
(paren
id|prev
comma
id|next
comma
id|current
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* VSID allocation&n; * ===============&n; *&n; * We first generate a 36-bit &quot;proto-VSID&quot;.  For kernel addresses this&n; * is equal to the ESID, for user addresses it is:&n; *&t;(context &lt;&lt; 15) | (esid &amp; 0x7fff)&n; *&n; * The two forms are distinguishable because the top bit is 0 for user&n; * addresses, whereas the top two bits are 1 for kernel addresses.&n; * Proto-VSIDs with the top two bits equal to 0b10 are reserved for&n; * now.&n; *&n; * The proto-VSIDs are then scrambled into real VSIDs with the&n; * multiplicative hash:&n; *&n; *&t;VSID = (proto-VSID * VSID_MULTIPLIER) % VSID_MODULUS&n; *&t;where&t;VSID_MULTIPLIER = 268435399 = 0xFFFFFC7&n; *&t;&t;VSID_MODULUS = 2^36-1 = 0xFFFFFFFFF&n; *&n; * This scramble is only well defined for proto-VSIDs below&n; * 0xFFFFFFFFF, so both proto-VSID and actual VSID 0xFFFFFFFFF are&n; * reserved.  VSID_MULTIPLIER is prime (the largest 28-bit prime, in&n; * fact), so in particular it is co-prime to VSID_MODULUS, making this&n; * a 1:1 scrambling function.  Because the modulus is 2^n-1 we can&n; * compute it efficiently without a divide or extra multiply (see&n; * below).&n; *&n; * This scheme has several advantages over older methods:&n; *&n; * &t;- We have VSIDs allocated for every kernel address&n; * (i.e. everything above 0xC000000000000000), except the very top&n; * segment, which simplifies several things.&n; *&n; * &t;- We allow for 15 significant bits of ESID and 20 bits of&n; * context for user addresses.  i.e. 8T (43 bits) of address space for&n; * up to 1M contexts (although the page table structure and context&n; * allocation will need changes to take advantage of this).&n; *&n; * &t;- The scramble function gives robust scattering in the hash&n; * table (at least based on some initial results).  The previous&n; * method was more susceptible to pathological cases giving excessive&n; * hash collisions.&n; */
multiline_comment|/*&n; * WARNING - If you change these you must make sure the asm&n; * implementations in slb_allocate(), do_stab_bolted and mmu.h&n; * (ASM_VSID_SCRAMBLE macro) are changed accordingly.&n; *&n; * You&squot;ll also need to change the precomputed VSID values in head.S&n; * which are used by the iSeries firmware.&n; */
DECL|function|vsid_scramble
r_static
r_inline
r_int
r_int
id|vsid_scramble
c_func
(paren
r_int
r_int
id|protovsid
)paren
(brace
macro_line|#if 0
multiline_comment|/* The code below is equivalent to this function for arguments&n;&t; * &lt; 2^VSID_BITS, which is all this should ever be called&n;&t; * with.  However gcc is not clever enough to compute the&n;&t; * modulus (2^n-1) without a second multiply. */
r_return
(paren
(paren
id|protovsid
op_star
id|VSID_MULTIPLIER
)paren
op_mod
id|VSID_MODULUS
)paren
suffix:semicolon
macro_line|#else /* 1 */
r_int
r_int
id|x
suffix:semicolon
id|x
op_assign
id|protovsid
op_star
id|VSID_MULTIPLIER
suffix:semicolon
id|x
op_assign
(paren
id|x
op_rshift
id|VSID_BITS
)paren
op_plus
(paren
id|x
op_amp
id|VSID_MODULUS
)paren
suffix:semicolon
r_return
(paren
id|x
op_plus
(paren
(paren
id|x
op_plus
l_int|1
)paren
op_rshift
id|VSID_BITS
)paren
)paren
op_amp
id|VSID_MODULUS
suffix:semicolon
macro_line|#endif /* 1 */
)brace
multiline_comment|/* This is only valid for addresses &gt;= KERNELBASE */
DECL|function|get_kernel_vsid
r_static
r_inline
r_int
r_int
id|get_kernel_vsid
c_func
(paren
r_int
r_int
id|ea
)paren
(brace
r_return
id|vsid_scramble
c_func
(paren
id|ea
op_rshift
id|SID_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/* This is only valid for user addresses (which are below 2^41) */
DECL|function|get_vsid
r_static
r_inline
r_int
r_int
id|get_vsid
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|ea
)paren
(brace
r_return
id|vsid_scramble
c_func
(paren
(paren
id|context
op_lshift
id|USER_ESID_BITS
)paren
op_or
(paren
id|ea
op_rshift
id|SID_SHIFT
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __PPC64_MMU_CONTEXT_H */
eof
