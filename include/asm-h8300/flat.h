multiline_comment|/*&n; * include/asm-h8300/flat.h -- uClinux flat-format executables&n; */
macro_line|#ifndef __H8300_FLAT_H__
DECL|macro|__H8300_FLAT_H__
mdefine_line|#define __H8300_FLAT_H__
DECL|macro|flat_stack_align
mdefine_line|#define&t;flat_stack_align(sp)&t;&t;&t;/* nothing needed */
DECL|macro|flat_argvp_envp_on_stack
mdefine_line|#define&t;flat_argvp_envp_on_stack()&t;&t;1
DECL|macro|flat_old_ram_flag
mdefine_line|#define&t;flat_old_ram_flag(flags)&t;&t;1
DECL|macro|flat_reloc_valid
mdefine_line|#define&t;flat_reloc_valid(reloc, size)&t;&t;((reloc) &lt;= (size))
multiline_comment|/*&n; * on the H8 a couple of the relocations have an instruction in the&n; * top byte.  As there can only be 24bits of address space,  we just&n; * always preserve that 8bits at the top,  when it isn&squot;t an instruction&n; * is is 0 (davidm@snapgear.com)&n; */
DECL|macro|flat_get_relocate_addr
mdefine_line|#define&t;flat_get_relocate_addr(rel)&t;&t;(rel)
DECL|macro|flat_get_addr_from_rp
mdefine_line|#define flat_get_addr_from_rp(rp, relval)       (get_unaligned(rp) &amp; 0x0ffffff)
DECL|macro|flat_put_addr_at_rp
mdefine_line|#define flat_put_addr_at_rp(rp, addr, rel) &bslash;&n;&t;put_unaligned (((*(char *)(rp)) &lt;&lt; 24) | ((addr) &amp; 0x00ffffff), rp)
macro_line|#endif /* __H8300_FLAT_H__ */
eof
