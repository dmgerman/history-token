macro_line|#ifndef __ASM_I8259_H__
DECL|macro|__ASM_I8259_H__
mdefine_line|#define __ASM_I8259_H__
r_extern
r_int
r_int
id|cached_irq_mask
suffix:semicolon
DECL|macro|__byte
mdefine_line|#define __byte(x,y) &t;(((unsigned char *) &amp;(y))[x])
DECL|macro|cached_21
mdefine_line|#define cached_21&t;(__byte(0, cached_irq_mask))
DECL|macro|cached_A1
mdefine_line|#define cached_A1&t;(__byte(1, cached_irq_mask))
r_extern
id|spinlock_t
id|i8259A_lock
suffix:semicolon
r_extern
r_void
id|init_8259A
c_func
(paren
r_int
id|auto_eoi
)paren
suffix:semicolon
r_extern
r_void
id|enable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|disable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
r_int
id|startup_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif&t;/* __ASM_I8259_H__ */
eof
