macro_line|#ifndef __V850_MMU_CONTEXT_H__
DECL|macro|__V850_MMU_CONTEXT_H__
mdefine_line|#define __V850_MMU_CONTEXT_H__
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;((void)0)
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;0
DECL|macro|switch_mm
mdefine_line|#define switch_mm(prev,next,tsk)&t;((void)0)
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;&t;do { } while (0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev,next)&t;&t;((void)0)
DECL|macro|enter_lazy_tlb
mdefine_line|#define enter_lazy_tlb(mm,tsk)&t;&t;((void)0)
macro_line|#endif /* __V850_MMU_CONTEXT_H__ */
eof
