macro_line|#ifndef S390_AINTERRUPT_H
DECL|macro|S390_AINTERRUPT_H
mdefine_line|#define S390_AINTERRUPT_H
DECL|typedef|adapter_int_handler_t
r_typedef
r_int
(paren
op_star
id|adapter_int_handler_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|s390_register_adapter_interrupt
c_func
(paren
id|adapter_int_handler_t
id|handler
)paren
suffix:semicolon
r_extern
r_int
id|s390_unregister_adapter_interrupt
c_func
(paren
id|adapter_int_handler_t
id|handler
)paren
suffix:semicolon
r_extern
r_void
id|do_adapter_IO
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
