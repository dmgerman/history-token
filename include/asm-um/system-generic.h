macro_line|#ifndef __UM_SYSTEM_GENERIC_H
DECL|macro|__UM_SYSTEM_GENERIC_H
mdefine_line|#define __UM_SYSTEM_GENERIC_H
macro_line|#include &quot;asm/arch/system.h&quot;
DECL|macro|switch_to
macro_line|#undef switch_to
DECL|macro|local_irq_save
macro_line|#undef local_irq_save
DECL|macro|local_irq_restore
macro_line|#undef local_irq_restore
DECL|macro|local_irq_disable
macro_line|#undef local_irq_disable
DECL|macro|local_irq_enable
macro_line|#undef local_irq_enable
DECL|macro|local_save_flags
macro_line|#undef local_save_flags
DECL|macro|local_irq_restore
macro_line|#undef local_irq_restore
DECL|macro|local_irq_enable
macro_line|#undef local_irq_enable
DECL|macro|local_irq_disable
macro_line|#undef local_irq_disable
DECL|macro|local_irq_save
macro_line|#undef local_irq_save
DECL|macro|irqs_disabled
macro_line|#undef irqs_disabled
r_extern
r_void
op_star
id|switch_to
c_func
(paren
r_void
op_star
id|prev
comma
r_void
op_star
id|next
comma
r_void
op_star
id|last
)paren
suffix:semicolon
r_extern
r_int
id|get_signals
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|set_signals
c_func
(paren
r_int
id|enable
)paren
suffix:semicolon
r_extern
r_int
id|get_signals
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|block_signals
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unblock_signals
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags) do { (flags) = get_signals(); } while(0)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags) do { set_signals(flags); } while(0)
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags) do { local_save_flags(flags); &bslash;&n;                                   local_irq_disable(); } while(0)
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() unblock_signals()
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() block_signals()
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()                 &bslash;&n;({                                      &bslash;&n;        unsigned long flags;            &bslash;&n;        local_save_flags(flags);        &bslash;&n;        (flags == 0);                   &bslash;&n;})
macro_line|#endif
eof
