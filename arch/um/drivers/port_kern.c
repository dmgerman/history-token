multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/irq.h&quot;
macro_line|#include &quot;linux/spinlock.h&quot;
macro_line|#include &quot;linux/errno.h&quot;
macro_line|#include &quot;asm/atomic.h&quot;
macro_line|#include &quot;asm/semaphore.h&quot;
macro_line|#include &quot;asm/errno.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;irq_kern.h&quot;
macro_line|#include &quot;port.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|struct|port_list
r_struct
id|port_list
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|wait_count
id|atomic_t
id|wait_count
suffix:semicolon
DECL|member|has_connection
r_int
id|has_connection
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pending
r_struct
id|list_head
id|pending
suffix:semicolon
DECL|member|connections
r_struct
id|list_head
id|connections
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|port_dev
r_struct
id|port_dev
(brace
DECL|member|port
r_struct
id|port_list
op_star
id|port
suffix:semicolon
DECL|member|helper_pid
r_int
id|helper_pid
suffix:semicolon
DECL|member|telnetd_pid
r_int
id|telnetd_pid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|connection
r_struct
id|connection
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|helper_pid
r_int
id|helper_pid
suffix:semicolon
DECL|member|socket
r_int
id|socket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|telnetd_pid
r_int
id|telnetd_pid
suffix:semicolon
DECL|member|port
r_struct
id|port_list
op_star
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|function|pipe_interrupt
r_static
id|irqreturn_t
id|pipe_interrupt
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
id|connection
op_star
id|conn
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
id|conn-&gt;socket
(braket
l_int|0
)braket
comma
op_amp
id|conn-&gt;helper_pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
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
id|IRQ_NONE
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pipe_interrupt : os_rcv_fd returned %d&bslash;n&quot;
comma
op_minus
id|fd
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|conn-&gt;fd
)paren
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|conn-&gt;list
)paren
suffix:semicolon
id|conn-&gt;fd
op_assign
id|fd
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|conn-&gt;list
comma
op_amp
id|conn-&gt;port-&gt;connections
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|conn-&gt;port-&gt;sem
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|macro|NO_WAITER_MSG
mdefine_line|#define NO_WAITER_MSG &bslash;&n;    &quot;****&bslash;n&quot; &bslash;&n;    &quot;There are currently no UML consoles waiting for port connections.&bslash;n&quot; &bslash;&n;    &quot;Either disconnect from one to make it available or activate some more&bslash;n&quot; &bslash;&n;    &quot;by enabling more consoles in the UML /etc/inittab.&bslash;n&quot; &bslash;&n;    &quot;****&bslash;n&quot;
DECL|function|port_accept
r_static
r_int
id|port_accept
c_func
(paren
r_struct
id|port_list
op_star
id|port
)paren
(brace
r_struct
id|connection
op_star
id|conn
suffix:semicolon
r_int
id|fd
comma
id|socket
(braket
l_int|2
)braket
comma
id|pid
comma
id|ret
op_assign
l_int|0
suffix:semicolon
id|fd
op_assign
id|port_connection
c_func
(paren
id|port-&gt;fd
comma
id|socket
comma
op_amp
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ne
op_minus
id|EAGAIN
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;port_accept : port_connection &quot;
l_string|&quot;returned %d&bslash;n&quot;
comma
op_minus
id|fd
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
id|conn
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|conn
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;port_accept : failed to allocate &quot;
l_string|&quot;connection&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
op_star
id|conn
op_assign
(paren
(paren
r_struct
id|connection
)paren
(brace
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|conn-&gt;list
)paren
comma
dot
id|fd
op_assign
id|fd
comma
dot
id|socket
op_assign
(brace
id|socket
(braket
l_int|0
)braket
comma
id|socket
(braket
l_int|1
)braket
)brace
comma
dot
id|telnetd_pid
op_assign
id|pid
comma
dot
id|port
op_assign
id|port
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|um_request_irq
c_func
(paren
id|TELNETD_IRQ
comma
id|socket
(braket
l_int|0
)braket
comma
id|IRQ_READ
comma
id|pipe_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;telnetd&quot;
comma
id|conn
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;port_accept : failed to get IRQ for &quot;
l_string|&quot;telnetd&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|port-&gt;wait_count
)paren
op_eq
l_int|0
)paren
(brace
id|os_write_file
c_func
(paren
id|fd
comma
id|NO_WAITER_MSG
comma
r_sizeof
(paren
id|NO_WAITER_MSG
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;No one waiting for port&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|conn-&gt;list
comma
op_amp
id|port-&gt;pending
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|conn
)paren
suffix:semicolon
id|out_close
suffix:colon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ne
op_minus
l_int|1
)paren
(brace
id|os_kill_process
c_func
(paren
id|pid
comma
l_int|1
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ports_sem
id|DECLARE_MUTEX
c_func
(paren
id|ports_sem
)paren
suffix:semicolon
DECL|variable|ports
r_struct
id|list_head
id|ports
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|ports
)paren
suffix:semicolon
DECL|function|port_work_proc
r_void
id|port_work_proc
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_struct
id|port_list
op_star
id|port
suffix:semicolon
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|ports
)paren
(brace
id|port
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|port_list
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;has_connection
)paren
(brace
r_continue
suffix:semicolon
)brace
id|reactivate_fd
c_func
(paren
id|port-&gt;fd
comma
id|ACCEPT_IRQ
)paren
suffix:semicolon
r_while
c_loop
(paren
id|port_accept
c_func
(paren
id|port
)paren
)paren
(brace
suffix:semicolon
)brace
id|port-&gt;has_connection
op_assign
l_int|0
suffix:semicolon
)brace
)def_block
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
id|DECLARE_WORK
c_func
(paren
id|port_work
comma
id|port_work_proc
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|port_interrupt
r_static
id|irqreturn_t
id|port_interrupt
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
id|port_list
op_star
id|port
op_assign
id|data
suffix:semicolon
id|port-&gt;has_connection
op_assign
l_int|1
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|port_work
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|port_data
r_void
op_star
id|port_data
c_func
(paren
r_int
id|port_num
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|port_list
op_star
id|port
suffix:semicolon
r_struct
id|port_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ports_sem
)paren
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|ports
)paren
(brace
id|port
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|port_list
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;port
op_eq
id|port_num
)paren
(brace
r_goto
id|found
suffix:semicolon
)brace
)brace
)def_block
id|port
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|port_list
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Allocation of port list failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|fd
op_assign
id|port_listen_fd
c_func
(paren
id|port_num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;binding to port %d failed, errno = %d&bslash;n&quot;
comma
id|port_num
comma
op_minus
id|fd
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|um_request_irq
c_func
(paren
id|ACCEPT_IRQ
comma
id|fd
comma
id|IRQ_READ
comma
id|port_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;port&quot;
comma
id|port
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to get IRQ for port %d&bslash;n&quot;
comma
id|port_num
)paren
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
op_star
id|port
op_assign
(paren
(paren
r_struct
id|port_list
)paren
(brace
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|port-&gt;list
)paren
comma
dot
id|wait_count
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
comma
dot
id|has_connection
op_assign
l_int|0
comma
dot
id|sem
op_assign
id|__SEMAPHORE_INITIALIZER
c_func
(paren
id|port-&gt;sem
comma
l_int|0
)paren
comma
dot
id|port
op_assign
id|port_num
comma
dot
id|fd
op_assign
id|fd
comma
dot
id|pending
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|port-&gt;pending
)paren
comma
dot
id|connections
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|port-&gt;connections
)paren
)brace
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|port-&gt;lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|port-&gt;list
comma
op_amp
id|ports
)paren
suffix:semicolon
id|found
suffix:colon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|port_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Allocation of port device entry failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
op_star
id|dev
op_assign
(paren
(paren
r_struct
id|port_dev
)paren
(brace
dot
id|port
op_assign
id|port
comma
dot
id|helper_pid
op_assign
op_minus
l_int|1
comma
dot
id|telnetd_pid
op_assign
op_minus
l_int|1
)brace
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
id|out_close
suffix:colon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|ports_sem
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|function|port_wait
r_int
id|port_wait
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|port_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_struct
id|connection
op_star
id|conn
suffix:semicolon
r_struct
id|port_list
op_star
id|port
op_assign
id|dev-&gt;port
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|port-&gt;wait_count
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|fd
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|port-&gt;sem
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|port-&gt;lock
)paren
suffix:semicolon
id|conn
op_assign
id|list_entry
c_func
(paren
id|port-&gt;connections.next
comma
r_struct
id|connection
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|conn-&gt;list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|port-&gt;lock
)paren
suffix:semicolon
id|os_shutdown_socket
c_func
(paren
id|conn-&gt;socket
(braket
l_int|0
)braket
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|conn-&gt;socket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_shutdown_socket
c_func
(paren
id|conn-&gt;socket
(braket
l_int|1
)braket
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|conn-&gt;socket
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* This is done here because freeing an IRQ can&squot;t be done&n;&t;&t; * within the IRQ handler.  So, pipe_interrupt always ups&n;&t;&t; * the semaphore regardless of whether it got a successful&n;&t;&t; * connection.  Then we loop here throwing out failed &n;&t;&t; * connections until a good one is found.&n;&t;&t; */
id|free_irq_by_irq_and_dev
c_func
(paren
id|TELNETD_IRQ
comma
id|conn
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|TELNETD_IRQ
comma
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn-&gt;fd
op_ge
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
id|os_close_file
c_func
(paren
id|conn-&gt;fd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conn
)paren
suffix:semicolon
)brace
id|fd
op_assign
id|conn-&gt;fd
suffix:semicolon
id|dev-&gt;helper_pid
op_assign
id|conn-&gt;helper_pid
suffix:semicolon
id|dev-&gt;telnetd_pid
op_assign
id|conn-&gt;telnetd_pid
suffix:semicolon
id|kfree
c_func
(paren
id|conn
)paren
suffix:semicolon
id|out
suffix:colon
id|atomic_dec
c_func
(paren
op_amp
id|port-&gt;wait_count
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|port_remove_dev
r_void
id|port_remove_dev
c_func
(paren
r_void
op_star
id|d
)paren
(brace
r_struct
id|port_dev
op_star
id|dev
op_assign
id|d
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;helper_pid
op_ne
op_minus
l_int|1
)paren
(brace
id|os_kill_process
c_func
(paren
id|dev-&gt;helper_pid
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;telnetd_pid
op_ne
op_minus
l_int|1
)paren
(brace
id|os_kill_process
c_func
(paren
id|dev-&gt;telnetd_pid
comma
l_int|1
)paren
suffix:semicolon
)brace
id|dev-&gt;helper_pid
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;telnetd_pid
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|port_kern_free
r_void
id|port_kern_free
c_func
(paren
r_void
op_star
id|d
)paren
(brace
r_struct
id|port_dev
op_star
id|dev
op_assign
id|d
suffix:semicolon
id|port_remove_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|free_port
r_static
r_void
id|free_port
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|port_list
op_star
id|port
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|ports
)paren
(brace
id|port
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|port_list
comma
id|list
)paren
suffix:semicolon
id|free_irq_by_fd
c_func
(paren
id|port-&gt;fd
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|port-&gt;fd
)paren
suffix:semicolon
)brace
)def_block
)brace
DECL|variable|free_port
id|__uml_exitcall
c_func
(paren
id|free_port
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
