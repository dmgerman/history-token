macro_line|#ifndef&t;__ISERIES_IRQ_H__
DECL|macro|__ISERIES_IRQ_H__
mdefine_line|#define&t;__ISERIES_IRQ_H__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_void
id|iSeries_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|iSeries_allocate_IRQ
c_func
(paren
id|HvBusNumber
comma
id|HvSubBusNumber
comma
id|HvAgentId
)paren
suffix:semicolon
r_int
id|iSeries_assign_IRQ
c_func
(paren
r_int
comma
id|HvBusNumber
comma
id|HvSubBusNumber
comma
id|HvAgentId
)paren
suffix:semicolon
r_void
id|iSeries_activate_IRQs
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|XmPciLpEvent_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __ISERIES_IRQ_H__ */
eof
