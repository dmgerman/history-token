singleline_comment|// don&squot;t do this unless you have the right hardware!
DECL|macro|TRIGGERABLE_HBA
mdefine_line|#define TRIGGERABLE_HBA 0
macro_line|#if TRIGGERABLE_HBA
r_void
id|TriggerHBA
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|macro|TriggerHBA
mdefine_line|#define TriggerHBA(x, y)
macro_line|#endif
eof
