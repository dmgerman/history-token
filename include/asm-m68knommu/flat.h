multiline_comment|/*&n; * include/asm-m68knommu/flat.h -- uClinux flat-format executables&n; */
macro_line|#ifndef __M68KNOMMU_FLAT_H__
DECL|macro|__M68KNOMMU_FLAT_H__
mdefine_line|#define __M68KNOMMU_FLAT_H__
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
macro_line|#endif /* __M68KNOMMU_FLAT_H__ */
eof
