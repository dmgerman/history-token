multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2002-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_RW_MMR_H
DECL|macro|_ASM_IA64_SN_RW_MMR_H
mdefine_line|#define _ASM_IA64_SN_RW_MMR_H
multiline_comment|/*&n; * This file contains macros used to access MMR registers via&n; * uncached physical addresses.&n; * &t;pio_phys_read_mmr  - read an MMR&n; * &t;pio_phys_write_mmr - write an MMR&n; * &t;pio_atomic_phys_write_mmrs - atomically write 1 or 2 MMRs with psr.ic=0&n; *&t;&t;Second MMR will be skipped if address is NULL&n; *&n; * Addresses passed to these routines should be uncached physical addresses&n; * ie., 0x80000....&n; */
r_extern
r_inline
r_int
DECL|function|pio_phys_read_mmr
id|pio_phys_read_mmr
c_func
(paren
r_volatile
r_int
op_star
id|mmr
)paren
(brace
r_int
id|val
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r2=psr;;&quot;
l_string|&quot;rsm psr.i | psr.dt;;&quot;
l_string|&quot;srlz.i;;&quot;
l_string|&quot;ld8.acq %0=[%1];;&quot;
l_string|&quot;mov psr.l=r2;;&quot;
l_string|&quot;srlz.i;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mmr
)paren
suffix:colon
l_string|&quot;r2&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|pio_phys_write_mmr
id|pio_phys_write_mmr
c_func
(paren
r_volatile
r_int
op_star
id|mmr
comma
r_int
id|val
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;mov r2=psr;;&quot;
l_string|&quot;rsm psr.i | psr.dt;;&quot;
l_string|&quot;srlz.i;;&quot;
l_string|&quot;st8.rel [%0]=%1;;&quot;
l_string|&quot;mov psr.l=r2;;&quot;
l_string|&quot;srlz.i;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|mmr
)paren
comma
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r2&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_extern
r_inline
r_void
DECL|function|pio_atomic_phys_write_mmrs
id|pio_atomic_phys_write_mmrs
c_func
(paren
r_volatile
r_int
op_star
id|mmr1
comma
r_int
id|val1
comma
r_volatile
r_int
op_star
id|mmr2
comma
r_int
id|val2
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;mov r2=psr;;&quot;
l_string|&quot;rsm psr.i | psr.dt | psr.ic;;&quot;
l_string|&quot;cmp.ne p9,p0=%2,r0;&quot;
l_string|&quot;srlz.i;;&quot;
l_string|&quot;st8.rel [%0]=%1;&quot;
l_string|&quot;(p9) st8.rel [%2]=%3;;&quot;
l_string|&quot;mov psr.l=r2;;&quot;
l_string|&quot;srlz.i;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|mmr1
)paren
comma
l_string|&quot;r&quot;
(paren
id|val1
)paren
comma
l_string|&quot;r&quot;
(paren
id|mmr2
)paren
comma
l_string|&quot;r&quot;
(paren
id|val2
)paren
suffix:colon
l_string|&quot;p9&quot;
comma
l_string|&quot;r2&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_SN_RW_MMR_H */
eof
