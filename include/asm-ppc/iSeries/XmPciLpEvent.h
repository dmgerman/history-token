macro_line|#ifndef&t;__XMPCILPEVENT_H__
DECL|macro|__XMPCILPEVENT_H__
mdefine_line|#define&t;__XMPCILPEVENT_H__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_int
id|XmPciLpEvent_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ppc_irq_dispatch_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|irq
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __XMPCILPEVENT_H__ */
eof
