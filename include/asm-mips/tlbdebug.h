multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2002 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_TLBDEBUG_H
DECL|macro|__ASM_TLBDEBUG_H
mdefine_line|#define __ASM_TLBDEBUG_H
multiline_comment|/*&n; * TLB debugging functions:&n; */
r_extern
r_void
id|dump_tlb
c_func
(paren
r_int
id|first
comma
r_int
id|last
)paren
suffix:semicolon
r_extern
r_void
id|dump_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dump_tlb_wired
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dump_tlb_addr
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|dump_tlb_nonwired
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_TLBDEBUG_H */
eof
