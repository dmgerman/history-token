macro_line|#ifndef S390_CIO_H
DECL|macro|S390_CIO_H
mdefine_line|#define S390_CIO_H
r_extern
r_int
id|s390_start_IO
(paren
r_int
id|irq
comma
multiline_comment|/* IRQ */
id|ccw1_t
op_star
id|cpa
comma
multiline_comment|/* logical channel prog addr */
r_int
r_int
id|user_intparm
comma
multiline_comment|/* interruption parameter */
id|__u8
id|lpm
comma
multiline_comment|/* logical path mask */
r_int
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|cancel_IO
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|enable_cpu_sync_isc
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|disable_cpu_sync_isc
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|cons_dev
suffix:semicolon
r_extern
r_int
id|s390_process_IRQ
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif
eof
