macro_line|#ifndef __PPC64_MMU_CONTEXT_H
DECL|macro|__PPC64_MMU_CONTEXT_H
mdefine_line|#define __PPC64_MMU_CONTEXT_H
macro_line|#include &lt;linux/spinlock.h&gt;&t;
macro_line|#include &lt;linux/kernel.h&gt;&t;
macro_line|#include &lt;linux/mm.h&gt;&t;
macro_line|#include &lt;asm/mmu.h&gt;&t;
macro_line|#include &lt;asm/ppcdebug.h&gt;&t;
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
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT&t;&t;0
DECL|macro|FIRST_USER_CONTEXT
mdefine_line|#define FIRST_USER_CONTEXT&t;0x10    /* First 16 reserved for kernel */
DECL|macro|LAST_USER_CONTEXT
mdefine_line|#define LAST_USER_CONTEXT&t;0x8000  /* Same as PID_MAX for now... */
DECL|macro|NUM_USER_CONTEXT
mdefine_line|#define NUM_USER_CONTEXT&t;(LAST_USER_CONTEXT-FIRST_USER_CONTEXT)
multiline_comment|/* Choose whether we want to implement our context&n; * number allocator as a LIFO or FIFO queue.&n; */
macro_line|#if 1
DECL|macro|MMU_CONTEXT_LIFO
mdefine_line|#define MMU_CONTEXT_LIFO
macro_line|#else
DECL|macro|MMU_CONTEXT_FIFO
mdefine_line|#define MMU_CONTEXT_FIFO
macro_line|#endif
DECL|struct|mmu_context_queue_t
r_struct
id|mmu_context_queue_t
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|elements
id|mm_context_t
id|elements
(braket
id|LAST_USER_CONTEXT
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|mmu_context_queue_t
id|mmu_context_queue
suffix:semicolon
r_static
r_inline
r_void
DECL|function|enter_lazy_tlb
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
multiline_comment|/*&n; * The context number queue has underflowed.&n; * Meaning: we tried to push a context number that was freed&n; * back onto the context queue and the queue was already full.&n; */
r_static
r_inline
r_void
DECL|function|mmu_context_underflow
id|mmu_context_underflow
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mmu_context_underflow&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;mmu_context_underflow&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the context for a new address space.&n; */
r_static
r_inline
r_int
DECL|function|init_new_context
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
(brace
r_int
id|head
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* This does the right thing across a fork (I hope) */
r_int
r_int
id|low_hpages
op_assign
id|mm-&gt;context
op_amp
id|CONTEXT_LOW_HPAGES
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mmu_context_queue.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmu_context_queue.size
op_le
l_int|0
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mmu_context_queue.lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|head
op_assign
id|mmu_context_queue.head
suffix:semicolon
id|mm-&gt;context
op_assign
id|mmu_context_queue.elements
(braket
id|head
)braket
suffix:semicolon
id|mm-&gt;context
op_or_assign
id|low_hpages
suffix:semicolon
id|head
op_assign
(paren
id|head
OL
id|LAST_USER_CONTEXT
op_minus
l_int|1
)paren
ques
c_cond
id|head
op_plus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|mmu_context_queue.head
op_assign
id|head
suffix:semicolon
id|mmu_context_queue.size
op_decrement
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mmu_context_queue.lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We&squot;re finished using the context for an address space.&n; */
r_static
r_inline
r_void
DECL|function|destroy_context
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
id|index
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mmu_context_queue.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmu_context_queue.size
op_ge
id|NUM_USER_CONTEXT
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mmu_context_queue.lock
comma
id|flags
)paren
suffix:semicolon
id|mmu_context_underflow
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef MMU_CONTEXT_LIFO
id|index
op_assign
id|mmu_context_queue.head
suffix:semicolon
id|index
op_assign
(paren
id|index
OG
l_int|0
)paren
ques
c_cond
id|index
op_minus
l_int|1
suffix:colon
id|LAST_USER_CONTEXT
op_minus
l_int|1
suffix:semicolon
id|mmu_context_queue.head
op_assign
id|index
suffix:semicolon
macro_line|#else
id|index
op_assign
id|mmu_context_queue.tail
suffix:semicolon
id|index
op_assign
(paren
id|index
OL
id|LAST_USER_CONTEXT
op_minus
l_int|1
)paren
ques
c_cond
id|index
op_plus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|mmu_context_queue.tail
op_assign
id|index
suffix:semicolon
macro_line|#endif
id|mmu_context_queue.size
op_increment
suffix:semicolon
id|mmu_context_queue.elements
(braket
id|index
)braket
op_assign
id|mm-&gt;context
op_amp
op_complement
id|CONTEXT_LOW_HPAGES
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mmu_context_queue.lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_void
id|flush_stab
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
id|flush_stab
c_func
(paren
id|tsk
comma
id|next
)paren
suffix:semicolon
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
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;do { } while (0)
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|macro|activate_mm
mdefine_line|#define activate_mm(active_mm, mm) &bslash;&n;&t;switch_mm(active_mm, mm, current);
DECL|macro|VSID_RANDOMIZER
mdefine_line|#define VSID_RANDOMIZER 42470972311
DECL|macro|VSID_MASK
mdefine_line|#define VSID_MASK&t;0xfffffffff
multiline_comment|/* This is only valid for kernel (including vmalloc, imalloc and bolted) EA&squot;s&n; */
r_static
r_inline
r_int
r_int
DECL|function|get_kernel_vsid
id|get_kernel_vsid
c_func
(paren
r_int
r_int
id|ea
)paren
(brace
r_int
r_int
id|ordinal
comma
id|vsid
suffix:semicolon
id|ordinal
op_assign
(paren
(paren
(paren
id|ea
op_rshift
l_int|28
)paren
op_amp
l_int|0x1fffff
)paren
op_star
id|LAST_USER_CONTEXT
)paren
op_or
(paren
id|ea
op_rshift
l_int|60
)paren
suffix:semicolon
id|vsid
op_assign
(paren
id|ordinal
op_star
id|VSID_RANDOMIZER
)paren
op_amp
id|VSID_MASK
suffix:semicolon
id|ifppcdebug
c_func
(paren
id|PPCDBG_HTABSTRESS
)paren
(brace
multiline_comment|/* For debug, this path creates a very poor vsid distribuition.&n;&t;&t; * A user program can access virtual addresses in the form&n;&t;&t; * 0x0yyyyxxxx000 where yyyy = xxxx to cause multiple mappings&n;&t;&t; * to hash to the same page table group.&n;&t;&t; */
id|ordinal
op_assign
(paren
(paren
id|ea
op_rshift
l_int|28
)paren
op_amp
l_int|0x1fff
)paren
op_or
(paren
id|ea
op_rshift
l_int|44
)paren
suffix:semicolon
id|vsid
op_assign
id|ordinal
op_amp
id|VSID_MASK
suffix:semicolon
)brace
r_return
id|vsid
suffix:semicolon
)brace
multiline_comment|/* This is only valid for user EA&squot;s (user EA&squot;s do not exceed 2^41 (EADDR_SIZE))&n; */
r_static
r_inline
r_int
r_int
DECL|function|get_vsid
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
r_int
r_int
id|ordinal
comma
id|vsid
suffix:semicolon
id|context
op_and_assign
op_complement
id|CONTEXT_LOW_HPAGES
suffix:semicolon
id|ordinal
op_assign
(paren
(paren
(paren
id|ea
op_rshift
l_int|28
)paren
op_amp
l_int|0x1fffff
)paren
op_star
id|LAST_USER_CONTEXT
)paren
op_or
id|context
suffix:semicolon
id|vsid
op_assign
(paren
id|ordinal
op_star
id|VSID_RANDOMIZER
)paren
op_amp
id|VSID_MASK
suffix:semicolon
id|ifppcdebug
c_func
(paren
id|PPCDBG_HTABSTRESS
)paren
(brace
multiline_comment|/* See comment above. */
id|ordinal
op_assign
(paren
(paren
id|ea
op_rshift
l_int|28
)paren
op_amp
l_int|0x1fff
)paren
op_or
(paren
id|context
op_lshift
l_int|16
)paren
suffix:semicolon
id|vsid
op_assign
id|ordinal
op_amp
id|VSID_MASK
suffix:semicolon
)brace
r_return
id|vsid
suffix:semicolon
)brace
macro_line|#endif /* __PPC64_MMU_CONTEXT_H */
eof
