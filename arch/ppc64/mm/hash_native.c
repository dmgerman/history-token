multiline_comment|/*&n; * native hashtable management.&n; *&n; * SMP scalability work:&n; *    Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; * &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
DECL|macro|HPTE_LOCK_BIT
mdefine_line|#define HPTE_LOCK_BIT 3
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|native_tlbie_lock
)paren
suffix:semicolon
DECL|function|native_lock_hpte
r_static
r_inline
r_void
id|native_lock_hpte
c_func
(paren
id|HPTE
op_star
id|hptep
)paren
(brace
r_int
r_int
op_star
id|word
op_assign
op_amp
id|hptep-&gt;dw0.dword0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|HPTE_LOCK_BIT
comma
id|word
)paren
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|HPTE_LOCK_BIT
comma
id|word
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|native_unlock_hpte
r_static
r_inline
r_void
id|native_unlock_hpte
c_func
(paren
id|HPTE
op_star
id|hptep
)paren
(brace
r_int
r_int
op_star
id|word
op_assign
op_amp
id|hptep-&gt;dw0.dword0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;lwsync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|HPTE_LOCK_BIT
comma
id|word
)paren
suffix:semicolon
)brace
DECL|function|native_hpte_insert
r_int
id|native_hpte_insert
c_func
(paren
r_int
r_int
id|hpte_group
comma
r_int
r_int
id|va
comma
r_int
r_int
id|prpn
comma
r_int
id|secondary
comma
r_int
r_int
id|hpteflags
comma
r_int
id|bolted
comma
r_int
id|large
)paren
(brace
r_int
r_int
id|arpn
op_assign
id|physRpn_to_absRpn
c_func
(paren
id|prpn
)paren
suffix:semicolon
id|HPTE
op_star
id|hptep
op_assign
id|htab_address
op_plus
id|hpte_group
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
id|HPTE
id|lhpte
suffix:semicolon
r_int
id|i
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
id|HPTES_PER_GROUP
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dw0.v
)paren
(brace
multiline_comment|/* retry with lock held */
id|native_lock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dw0.v
)paren
r_break
suffix:semicolon
id|native_unlock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
)brace
id|hptep
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|HPTES_PER_GROUP
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|lhpte.dw1.dword1
op_assign
l_int|0
suffix:semicolon
id|lhpte.dw1.dw1.rpn
op_assign
id|arpn
suffix:semicolon
id|lhpte.dw1.flags.flags
op_assign
id|hpteflags
suffix:semicolon
id|lhpte.dw0.dword0
op_assign
l_int|0
suffix:semicolon
id|lhpte.dw0.dw0.avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
id|lhpte.dw0.dw0.h
op_assign
id|secondary
suffix:semicolon
id|lhpte.dw0.dw0.bolted
op_assign
id|bolted
suffix:semicolon
id|lhpte.dw0.dw0.v
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
(brace
id|lhpte.dw0.dw0.l
op_assign
l_int|1
suffix:semicolon
id|lhpte.dw0.dw0.avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
)brace
id|hptep-&gt;dw1.dword1
op_assign
id|lhpte.dw1.dword1
suffix:semicolon
multiline_comment|/* Guarantee the second dword is visible before the valid bit */
id|__asm__
id|__volatile__
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now set the first dword including the valid bit&n;&t; * NOTE: this also unlocks the hpte&n;&t; */
id|hptep-&gt;dw0.dword0
op_assign
id|lhpte.dw0.dword0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ptesync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|i
op_or
(paren
id|secondary
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|native_hpte_remove
r_static
r_int
id|native_hpte_remove
c_func
(paren
r_int
r_int
id|hpte_group
)paren
(brace
id|HPTE
op_star
id|hptep
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|slot_offset
suffix:semicolon
multiline_comment|/* pick a random entry to start at */
id|slot_offset
op_assign
id|mftb
c_func
(paren
)paren
op_amp
l_int|0x7
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
id|HPTES_PER_GROUP
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hptep
op_assign
id|htab_address
op_plus
id|hpte_group
op_plus
id|slot_offset
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
r_if
c_cond
(paren
id|dw0.v
op_logical_and
op_logical_neg
id|dw0.bolted
)paren
(brace
multiline_comment|/* retry with lock held */
id|native_lock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
r_if
c_cond
(paren
id|dw0.v
op_logical_and
op_logical_neg
id|dw0.bolted
)paren
r_break
suffix:semicolon
id|native_unlock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
)brace
id|slot_offset
op_increment
suffix:semicolon
id|slot_offset
op_and_assign
l_int|0x7
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|HPTES_PER_GROUP
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Invalidate the hpte. NOTE: this also unlocks it */
id|hptep-&gt;dw0.dword0
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|set_pp_bit
r_static
r_inline
r_void
id|set_pp_bit
c_func
(paren
r_int
r_int
id|pp
comma
id|HPTE
op_star
id|addr
)paren
(brace
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
op_amp
id|addr-&gt;dw1.dword1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldarx&t;%0,0,%3&bslash;n&bslash;&n;&t;&t;rldimi&t;%0,%2,0,61&bslash;n&bslash;&n;&t;&t;stdcx.&t;%0,0,%3&bslash;n&bslash;&n;&t;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|pp
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Only works on small pages. Yes its ugly to have to check each slot in&n; * the group but we only use this during bootup.&n; */
DECL|function|native_hpte_find
r_static
r_int
id|native_hpte_find
c_func
(paren
r_int
r_int
id|vpn
)paren
(brace
id|HPTE
op_star
id|hptep
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|slot
op_assign
(paren
id|hash
op_amp
id|htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
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
id|HPTES_PER_GROUP
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hptep
op_assign
id|htab_address
op_plus
id|slot
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dw0.avpn
op_eq
(paren
id|vpn
op_rshift
l_int|11
)paren
)paren
op_logical_and
id|dw0.v
op_logical_and
(paren
id|dw0.h
op_eq
id|j
)paren
)paren
(brace
multiline_comment|/* HPTE matches */
r_if
c_cond
(paren
id|j
)paren
id|slot
op_assign
op_minus
id|slot
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
op_increment
id|slot
suffix:semicolon
)brace
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|native_hpte_updatepp
r_static
r_int
id|native_hpte_updatepp
c_func
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|newpp
comma
r_int
r_int
id|va
comma
r_int
id|large
comma
r_int
id|local
)paren
(brace
id|HPTE
op_star
id|hptep
op_assign
id|htab_address
op_plus
id|slot
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
r_int
r_int
id|avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
id|native_lock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
multiline_comment|/* Even if we miss, we need to invalidate the TLB */
r_if
c_cond
(paren
(paren
id|dw0.avpn
op_ne
id|avpn
)paren
op_logical_or
op_logical_neg
id|dw0.v
)paren
(brace
id|native_unlock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|set_pp_bit
c_func
(paren
id|newpp
comma
id|hptep
)paren
suffix:semicolon
id|native_unlock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure it is out of the tlb too */
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_TLBIEL
)paren
op_logical_and
op_logical_neg
id|large
op_logical_and
id|local
)paren
(brace
id|tlbiel
c_func
(paren
id|va
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|lock_tlbie
op_assign
op_logical_neg
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_LOCKLESS_TLBIE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_lock
c_func
(paren
op_amp
id|native_tlbie_lock
)paren
suffix:semicolon
id|tlbie
c_func
(paren
id|va
comma
id|large
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_unlock
c_func
(paren
op_amp
id|native_tlbie_lock
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Update the page protection bits. Intended to be used to create&n; * guard pages for kernel data structures on pages which are bolted&n; * in the HPT. Assumes pages being operated on will not be stolen.&n; * Does not work on large pages.&n; *&n; * No need to lock here because we should be the only user.&n; */
DECL|function|native_hpte_updateboltedpp
r_static
r_void
id|native_hpte_updateboltedpp
c_func
(paren
r_int
r_int
id|newpp
comma
r_int
r_int
id|ea
)paren
(brace
r_int
r_int
id|vsid
comma
id|va
comma
id|vpn
comma
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|slot
suffix:semicolon
id|HPTE
op_star
id|hptep
suffix:semicolon
r_int
id|lock_tlbie
op_assign
op_logical_neg
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_LOCKLESS_TLBIE
)paren
suffix:semicolon
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
id|va
op_assign
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|ea
op_amp
l_int|0x0fffffff
)paren
suffix:semicolon
id|vpn
op_assign
id|va
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|slot
op_assign
id|native_hpte_find
c_func
(paren
id|vpn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
op_minus
l_int|1
)paren
id|panic
c_func
(paren
l_string|&quot;could not find page to bolt&bslash;n&quot;
)paren
suffix:semicolon
id|hptep
op_assign
id|htab_address
op_plus
id|slot
suffix:semicolon
id|set_pp_bit
c_func
(paren
id|newpp
comma
id|hptep
)paren
suffix:semicolon
multiline_comment|/* Ensure it is out of the tlb too */
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_lock_irqsave
c_func
(paren
op_amp
id|native_tlbie_lock
comma
id|flags
)paren
suffix:semicolon
id|tlbie
c_func
(paren
id|va
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|native_tlbie_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|native_hpte_invalidate
r_static
r_void
id|native_hpte_invalidate
c_func
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|va
comma
r_int
id|large
comma
r_int
id|local
)paren
(brace
id|HPTE
op_star
id|hptep
op_assign
id|htab_address
op_plus
id|slot
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
r_int
r_int
id|avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|lock_tlbie
op_assign
op_logical_neg
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_LOCKLESS_TLBIE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|native_lock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
multiline_comment|/* Even if we miss, we need to invalidate the TLB */
r_if
c_cond
(paren
(paren
id|dw0.avpn
op_ne
id|avpn
)paren
op_logical_or
op_logical_neg
id|dw0.v
)paren
(brace
id|native_unlock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Invalidate the hpte. NOTE: this also unlocks it */
id|hptep-&gt;dw0.dword0
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Invalidate the tlb */
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_TLBIEL
)paren
op_logical_and
op_logical_neg
id|large
op_logical_and
id|local
)paren
(brace
id|tlbiel
c_func
(paren
id|va
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_lock
c_func
(paren
op_amp
id|native_tlbie_lock
)paren
suffix:semicolon
id|tlbie
c_func
(paren
id|va
comma
id|large
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_unlock
c_func
(paren
op_amp
id|native_tlbie_lock
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|native_flush_hash_range
r_static
r_void
id|native_flush_hash_range
c_func
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|number
comma
r_int
id|local
)paren
(brace
r_int
r_int
id|vsid
comma
id|vpn
comma
id|va
comma
id|hash
comma
id|secondary
comma
id|slot
comma
id|flags
comma
id|avpn
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|HPTE
op_star
id|hptep
suffix:semicolon
id|Hpte_dword0
id|dw0
suffix:semicolon
r_struct
id|ppc64_tlb_batch
op_star
id|batch
op_assign
op_amp
id|__get_cpu_var
c_func
(paren
id|ppc64_tlb_batch
)paren
suffix:semicolon
multiline_comment|/* XXX fix for large ptes */
r_int
r_int
id|large
op_assign
l_int|0
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|j
op_assign
l_int|0
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
id|number
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|batch-&gt;addr
(braket
id|i
)braket
op_ge
id|USER_START
)paren
op_logical_and
(paren
id|batch-&gt;addr
(braket
id|i
)braket
op_le
id|USER_END
)paren
)paren
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|context
comma
id|batch-&gt;addr
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|batch-&gt;addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|va
op_assign
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|batch-&gt;addr
(braket
id|i
)braket
op_amp
l_int|0x0fffffff
)paren
suffix:semicolon
id|batch-&gt;vaddr
(braket
id|j
)braket
op_assign
id|va
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|vpn
op_assign
id|va
op_rshift
id|HPAGE_SHIFT
suffix:semicolon
r_else
id|vpn
op_assign
id|va
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|hash
op_assign
id|hpt_hash
c_func
(paren
id|vpn
comma
id|large
)paren
suffix:semicolon
id|secondary
op_assign
(paren
id|pte_val
c_func
(paren
id|batch-&gt;pte
(braket
id|i
)braket
)paren
op_amp
id|_PAGE_SECONDARY
)paren
op_rshift
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|secondary
)paren
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
id|slot
op_assign
(paren
id|hash
op_amp
id|htab_hash_mask
)paren
op_star
id|HPTES_PER_GROUP
suffix:semicolon
id|slot
op_add_assign
(paren
id|pte_val
c_func
(paren
id|batch-&gt;pte
(braket
id|i
)braket
)paren
op_amp
id|_PAGE_GROUP_IX
)paren
op_rshift
l_int|12
suffix:semicolon
id|hptep
op_assign
id|htab_address
op_plus
id|slot
suffix:semicolon
id|avpn
op_assign
id|va
op_rshift
l_int|23
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|avpn
op_and_assign
op_complement
l_int|0x1UL
suffix:semicolon
id|native_lock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
id|dw0
op_assign
id|hptep-&gt;dw0.dw0
suffix:semicolon
multiline_comment|/* Even if we miss, we need to invalidate the TLB */
r_if
c_cond
(paren
(paren
id|dw0.avpn
op_ne
id|avpn
)paren
op_logical_or
op_logical_neg
id|dw0.v
)paren
(brace
id|native_unlock_hpte
c_func
(paren
id|hptep
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Invalidate the hpte. NOTE: this also unlocks it */
id|hptep-&gt;dw0.dword0
op_assign
l_int|0
suffix:semicolon
)brace
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_TLBIEL
)paren
op_logical_and
op_logical_neg
id|large
op_logical_and
id|local
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;ptesync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
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
id|j
suffix:semicolon
id|i
op_increment
)paren
id|__tlbiel
c_func
(paren
id|batch-&gt;vaddr
(braket
id|i
)braket
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ptesync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|lock_tlbie
op_assign
op_logical_neg
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_LOCKLESS_TLBIE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_lock
c_func
(paren
op_amp
id|native_tlbie_lock
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ptesync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
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
id|j
suffix:semicolon
id|i
op_increment
)paren
id|__tlbie
c_func
(paren
id|batch-&gt;vaddr
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;eieio; tlbsync; ptesync&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_tlbie
)paren
id|spin_unlock
c_func
(paren
op_amp
id|native_tlbie_lock
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* Disable TLB batching on nighthawk */
DECL|function|tlb_batching_enabled
r_static
r_inline
r_int
id|tlb_batching_enabled
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|root
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_int
id|enabled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
(brace
r_const
r_char
op_star
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|model
comma
l_string|&quot;IBM,9076-N81&quot;
)paren
)paren
id|enabled
op_assign
l_int|0
suffix:semicolon
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
)brace
r_return
id|enabled
suffix:semicolon
)brace
macro_line|#else
DECL|function|tlb_batching_enabled
r_static
r_inline
r_int
id|tlb_batching_enabled
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|hpte_init_native
r_void
id|hpte_init_native
c_func
(paren
r_void
)paren
(brace
id|ppc_md.hpte_invalidate
op_assign
id|native_hpte_invalidate
suffix:semicolon
id|ppc_md.hpte_updatepp
op_assign
id|native_hpte_updatepp
suffix:semicolon
id|ppc_md.hpte_updateboltedpp
op_assign
id|native_hpte_updateboltedpp
suffix:semicolon
id|ppc_md.hpte_insert
op_assign
id|native_hpte_insert
suffix:semicolon
id|ppc_md.hpte_remove
op_assign
id|native_hpte_remove
suffix:semicolon
r_if
c_cond
(paren
id|tlb_batching_enabled
c_func
(paren
)paren
)paren
id|ppc_md.flush_hash_range
op_assign
id|native_flush_hash_range
suffix:semicolon
id|htab_finish_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
