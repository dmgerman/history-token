multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Declarations of procedures and variables shared between files&n; * in arch/ppc/mm/.&n; * &n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;asm/tlbflush.h&gt;
r_extern
r_void
id|mapin_ram
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|bat_mapin_ram
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|map_page
c_func
(paren
r_int
r_int
id|va
comma
r_int
r_int
id|pa
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|setbat
c_func
(paren
r_int
id|index
comma
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|reserve_phys_mem
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|__map_without_bats
suffix:semicolon
r_extern
r_int
r_int
id|ioremap_base
suffix:semicolon
r_extern
r_int
r_int
id|ioremap_bot
suffix:semicolon
r_extern
r_int
r_int
id|rtas_data
comma
id|rtas_size
suffix:semicolon
r_extern
r_int
r_int
id|total_memory
suffix:semicolon
r_extern
r_int
r_int
id|total_lowmem
suffix:semicolon
r_extern
r_int
id|mem_init_done
suffix:semicolon
r_extern
id|PTE
op_star
id|Hash
comma
op_star
id|Hash_end
suffix:semicolon
r_extern
r_int
r_int
id|Hash_size
comma
id|Hash_mask
suffix:semicolon
multiline_comment|/* ...and now those things that may be slightly different between processor&n; * architectures.  -- Dan&n; */
macro_line|#if defined(CONFIG_8xx)
DECL|macro|flush_HPTE
mdefine_line|#define flush_HPTE(X, va, pg)&t;_tlbie(va)
DECL|macro|MMU_init_hw
mdefine_line|#define MMU_init_hw()&t;&t;do { } while(0)
macro_line|#elif defined(CONFIG_4xx)
DECL|macro|flush_HPTE
mdefine_line|#define flush_HPTE(X, va, pg)&t;_tlbie(va)
r_extern
r_void
id|MMU_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* anything except 4xx or 8xx */
r_extern
r_void
id|MMU_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Be careful....this needs to be updated if we ever encounter 603 SMPs,&n; * which includes all new 82xx processors.  We need tlbie/tlbsync here&n; * in that case (I think). -- Dan.&n; */
DECL|function|flush_HPTE
r_static
r_inline
r_void
id|flush_HPTE
c_func
(paren
r_int
id|context
comma
r_int
r_int
id|va
comma
r_int
r_int
id|pdval
)paren
(brace
r_if
c_cond
(paren
(paren
id|Hash
op_ne
l_int|0
)paren
op_logical_and
(paren
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_HPTE_TABLE
)paren
)paren
id|flush_hash_pages
c_func
(paren
l_int|0
comma
id|va
comma
id|pdval
comma
l_int|1
)paren
suffix:semicolon
r_else
id|_tlbie
c_func
(paren
id|va
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
