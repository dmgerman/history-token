macro_line|#ifndef _PPC64_PACA_H
DECL|macro|_PPC64_PACA_H
mdefine_line|#define _PPC64_PACA_H
multiline_comment|/*&n; * include/asm-ppc64/paca.h&n; *&n; * This control block defines the PACA which defines the processor &n; * specific data for each logical processor on the system.  &n; * There are some pointers defined that are utilized by PLIC.&n; *&n; * C 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include&t;&lt;linux/config.h&gt;
macro_line|#include&t;&lt;asm/types.h&gt;
macro_line|#include&t;&lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include&t;&lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#include&t;&lt;asm/mmu.h&gt;
r_extern
r_struct
id|paca_struct
id|paca
(braket
)braket
suffix:semicolon
r_register
r_struct
id|paca_struct
op_star
id|local_paca
id|asm
c_func
(paren
l_string|&quot;r13&quot;
)paren
suffix:semicolon
DECL|macro|get_paca
mdefine_line|#define get_paca()&t;local_paca
r_struct
id|task_struct
suffix:semicolon
r_struct
id|ItLpQueue
suffix:semicolon
multiline_comment|/*&n; * Defines the layout of the paca.&n; *&n; * This structure is not directly accessed by firmware or the service&n; * processor except for the first two pointers that point to the&n; * ItLpPaca area and the ItLpRegSave area for this CPU.  Both the&n; * ItLpPaca and ItLpRegSave objects are currently contained within the&n; * PACA but they do not need to be.&n; */
DECL|struct|paca_struct
r_struct
id|paca_struct
(brace
multiline_comment|/*&n;&t; * Because hw_cpu_id, unlike other paca fields, is accessed&n;&t; * routinely from other CPUs (from the IRQ code), we stick to&n;&t; * read-only (after boot) fields in the first cacheline to&n;&t; * avoid cacheline bouncing.&n;&t; */
multiline_comment|/*&n;&t; * MAGIC: These first two pointers can&squot;t be moved - they&squot;re&n;&t; * accessed by the firmware&n;&t; */
DECL|member|lppaca_ptr
r_struct
id|ItLpPaca
op_star
id|lppaca_ptr
suffix:semicolon
multiline_comment|/* Pointer to LpPaca for PLIC */
DECL|member|reg_save_ptr
r_struct
id|ItLpRegSave
op_star
id|reg_save_ptr
suffix:semicolon
multiline_comment|/* Pointer to LpRegSave for PLIC */
multiline_comment|/*&n;&t; * MAGIC: the spinlock functions in arch/ppc64/lib/locks.c&n;&t; * load lock_token and paca_index with a single lwz&n;&t; * instruction.  They must travel together and be properly&n;&t; * aligned.&n;&t; */
DECL|member|lock_token
id|u16
id|lock_token
suffix:semicolon
multiline_comment|/* Constant 0x8000, used in locks */
DECL|member|paca_index
id|u16
id|paca_index
suffix:semicolon
multiline_comment|/* Logical processor number */
DECL|member|default_decr
id|u32
id|default_decr
suffix:semicolon
multiline_comment|/* Default decrementer value */
DECL|member|lpqueue_ptr
r_struct
id|ItLpQueue
op_star
id|lpqueue_ptr
suffix:semicolon
multiline_comment|/* LpQueue handled by this CPU */
DECL|member|kernel_toc
id|u64
id|kernel_toc
suffix:semicolon
multiline_comment|/* Kernel TOC address */
DECL|member|stab_real
id|u64
id|stab_real
suffix:semicolon
multiline_comment|/* Absolute address of segment table */
DECL|member|stab_addr
id|u64
id|stab_addr
suffix:semicolon
multiline_comment|/* Virtual address of segment table */
DECL|member|emergency_sp
r_void
op_star
id|emergency_sp
suffix:semicolon
multiline_comment|/* pointer to emergency stack */
DECL|member|hw_cpu_id
id|u16
id|hw_cpu_id
suffix:semicolon
multiline_comment|/* Physical processor number */
DECL|member|cpu_start
id|u8
id|cpu_start
suffix:semicolon
multiline_comment|/* At startup, processor spins until */
multiline_comment|/* this becomes non-zero. */
multiline_comment|/*&n;&t; * Now, starting in cacheline 2, the exception save areas&n;&t; */
DECL|member|exgen
id|u64
id|exgen
(braket
l_int|8
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|0x80
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* used for most interrupts/exceptions */
DECL|member|exmc
id|u64
id|exmc
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* used for machine checks */
DECL|member|exslb
id|u64
id|exslb
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* used for SLB/segment table misses&n;&t;&t;&t;&t; * on the linear mapping */
DECL|member|context
id|mm_context_t
id|context
suffix:semicolon
DECL|member|slb_cache
id|u16
id|slb_cache
(braket
id|SLB_CACHE_ENTRIES
)braket
suffix:semicolon
DECL|member|slb_cache_ptr
id|u16
id|slb_cache_ptr
suffix:semicolon
multiline_comment|/*&n;&t; * then miscellaneous read-write fields&n;&t; */
DECL|member|__current
r_struct
id|task_struct
op_star
id|__current
suffix:semicolon
multiline_comment|/* Pointer to current */
DECL|member|kstack
id|u64
id|kstack
suffix:semicolon
multiline_comment|/* Saved Kernel stack addr */
DECL|member|stab_rr
id|u64
id|stab_rr
suffix:semicolon
multiline_comment|/* stab/slb round-robin counter */
DECL|member|next_jiffy_update_tb
id|u64
id|next_jiffy_update_tb
suffix:semicolon
multiline_comment|/* TB value for next jiffy update */
DECL|member|saved_r1
id|u64
id|saved_r1
suffix:semicolon
multiline_comment|/* r1 save for RTAS calls */
DECL|member|saved_msr
id|u64
id|saved_msr
suffix:semicolon
multiline_comment|/* MSR saved here by enter_rtas */
DECL|member|lpevent_count
id|u32
id|lpevent_count
suffix:semicolon
multiline_comment|/* lpevents processed  */
DECL|member|proc_enabled
id|u8
id|proc_enabled
suffix:semicolon
multiline_comment|/* irq soft-enable flag */
multiline_comment|/* not yet used */
DECL|member|exdsi
id|u64
id|exdsi
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* used for linear mapping hash table misses */
multiline_comment|/*&n;&t; * iSeries structure which the hypervisor knows about -&n;&t; * this structure should not cross a page boundary.&n;&t; * The vpa_init/register_vpa call is now known to fail if the&n;&t; * lppaca structure crosses a page boundary.&n;&t; * The lppaca is also used on POWER5 pSeries boxes.&n;&t; * The lppaca is 640 bytes long, and cannot readily change&n;&t; * since the hypervisor knows its layout, so a 1kB&n;&t; * alignment will suffice to ensure that it doesn&squot;t&n;&t; * cross a page boundary.&n;&t; */
DECL|member|lppaca
r_struct
id|ItLpPaca
id|lppaca
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|0x400
)paren
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|member|reg_save
r_struct
id|ItLpRegSave
id|reg_save
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* _PPC64_PACA_H */
eof
