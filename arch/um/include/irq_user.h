multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __IRQ_USER_H__
DECL|macro|__IRQ_USER_H__
mdefine_line|#define __IRQ_USER_H__
DECL|enumerator|IRQ_READ
DECL|enumerator|IRQ_WRITE
r_enum
(brace
id|IRQ_READ
comma
id|IRQ_WRITE
)brace
suffix:semicolon
r_extern
r_void
id|sigio_handler
c_func
(paren
r_int
id|sig
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|activate_fd
c_func
(paren
r_int
id|irq
comma
r_int
id|fd
comma
r_int
id|type
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|free_irq_by_irq_and_dev
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|free_irq_by_fd
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_void
id|reactivate_fd
c_func
(paren
r_int
id|fd
comma
r_int
id|irqnum
)paren
suffix:semicolon
r_extern
r_void
id|deactivate_fd
c_func
(paren
r_int
id|fd
comma
r_int
id|irqnum
)paren
suffix:semicolon
r_extern
r_void
id|forward_interrupts
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|init_irq_signals
c_func
(paren
r_int
id|on_sigstack
)paren
suffix:semicolon
r_extern
r_void
id|forward_ipi
c_func
(paren
r_int
id|fd
comma
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|free_irq_later
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_int
id|activate_ipi
c_func
(paren
r_int
id|fd
comma
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_int
r_int
id|irq_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|irq_unlock
c_func
(paren
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
