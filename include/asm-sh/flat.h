multiline_comment|/*&n; * include/asm-sh/flat.h&n; *&n; * uClinux flat-format executables&n; *&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive for&n; * more details.&n; */
macro_line|#ifndef __ASM_SH_FLAT_H
DECL|macro|__ASM_SH_FLAT_H
mdefine_line|#define __ASM_SH_FLAT_H
DECL|macro|flat_stack_align
mdefine_line|#define&t;flat_stack_align(sp)&t;&t;&t;/* nothing needed */
DECL|macro|flat_argvp_envp_on_stack
mdefine_line|#define&t;flat_argvp_envp_on_stack()&t;&t;1
DECL|macro|flat_old_ram_flag
mdefine_line|#define&t;flat_old_ram_flag(flags)&t;&t;(flags)
DECL|macro|flat_reloc_valid
mdefine_line|#define&t;flat_reloc_valid(reloc, size)&t;&t;((reloc) &lt;= (size))
DECL|macro|flat_get_addr_from_rp
mdefine_line|#define&t;flat_get_addr_from_rp(rp, relval)&t;get_unaligned(rp)
DECL|macro|flat_put_addr_at_rp
mdefine_line|#define&t;flat_put_addr_at_rp(rp, val, relval)&t;put_unaligned(val,rp)
DECL|macro|flat_get_relocate_addr
mdefine_line|#define&t;flat_get_relocate_addr(rel)&t;&t;(rel)
macro_line|#endif /* __ASM_SH_FLAT_H */
eof
