multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;sigio.h&quot;
macro_line|#include &quot;irq_user.h&quot;
DECL|variable|sigio_irq_fd
r_static
r_int
id|sigio_irq_fd
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|sigio_interrupt
r_void
id|sigio_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
(brace
id|read_sigio_fd
c_func
(paren
id|sigio_irq_fd
)paren
suffix:semicolon
id|reactivate_fd
c_func
(paren
id|sigio_irq_fd
comma
id|SIGIO_WRITE_IRQ
)paren
suffix:semicolon
)brace
DECL|function|write_sigio_irq
r_int
id|write_sigio_irq
c_func
(paren
r_int
id|fd
)paren
(brace
r_if
c_cond
(paren
id|um_request_irq
c_func
(paren
id|SIGIO_WRITE_IRQ
comma
id|fd
comma
id|IRQ_READ
comma
id|sigio_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;write sigio&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;write_sigio_irq : um_request_irq failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|sigio_irq_fd
op_assign
id|fd
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
