multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/errno.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;asm/semaphore.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;xterm.h&quot;
DECL|struct|xterm_wait
r_struct
id|xterm_wait
(brace
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|new_fd
r_int
id|new_fd
suffix:semicolon
)brace
suffix:semicolon
DECL|function|xterm_interrupt
r_static
r_void
id|xterm_interrupt
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
id|regs
)paren
(brace
r_struct
id|xterm_wait
op_star
id|xterm
op_assign
id|data
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|os_rcv_fd
c_func
(paren
id|xterm-&gt;fd
comma
op_amp
id|xterm-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_return
suffix:semicolon
)brace
id|xterm-&gt;new_fd
op_assign
id|fd
suffix:semicolon
id|up
c_func
(paren
op_amp
id|xterm-&gt;sem
)paren
suffix:semicolon
)brace
DECL|function|xterm_fd
r_int
id|xterm_fd
c_func
(paren
r_int
id|socket
comma
r_int
op_star
id|pid_out
)paren
(brace
r_struct
id|xterm_wait
op_star
id|data
suffix:semicolon
r_int
id|err
comma
id|ret
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xterm_fd - failed to allocate semaphore&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
op_star
id|data
op_assign
(paren
(paren
r_struct
id|xterm_wait
)paren
(brace
id|sem
suffix:colon
id|__SEMAPHORE_INITIALIZER
c_func
(paren
id|data-&gt;sem
comma
l_int|0
)paren
comma
id|fd
suffix:colon
id|socket
comma
id|pid
suffix:colon
op_minus
l_int|1
comma
id|new_fd
suffix:colon
op_minus
l_int|1
)brace
)paren
suffix:semicolon
id|err
op_assign
id|um_request_irq
c_func
(paren
id|XTERM_IRQ
comma
id|socket
comma
id|IRQ_READ
comma
id|xterm_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;xterm&quot;
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to get IRQ for xterm, err = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|data-&gt;sem
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|XTERM_IRQ
comma
id|data
)paren
suffix:semicolon
id|ret
op_assign
id|data-&gt;new_fd
suffix:semicolon
op_star
id|pid_out
op_assign
id|data-&gt;pid
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
