multiline_comment|/*&n; *  drivers/s390/cio/airq.c&n; *   S/390 common I/O routines -- support for adapter interruptions&n; *&n; *   $Revision: 1.11 $&n; *&n; *    Copyright (C) 1999-2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t;      IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;airq.h&quot;
DECL|variable|adapter_lock
r_static
id|spinlock_t
id|adapter_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|adapter_handler
r_static
id|adapter_int_handler_t
id|adapter_handler
suffix:semicolon
multiline_comment|/*&n; * register for adapter interrupts&n; *&n; * With HiperSockets the zSeries architecture provides for&n; *  means of adapter interrups, pseudo I/O interrupts that are&n; *  not tied to an I/O subchannel, but to an adapter. However,&n; *  it doesn&squot;t disclose the info how to enable/disable them, but&n; *  to recognize them only. Perhaps we should consider them&n; *  being shared interrupts, and thus build a linked list&n; *  of adapter handlers ... to be evaluated ...&n; */
r_int
DECL|function|s390_register_adapter_interrupt
id|s390_register_adapter_interrupt
(paren
id|adapter_int_handler_t
id|handler
)paren
(brace
r_int
id|ret
suffix:semicolon
r_char
id|dbf_txt
(braket
l_int|15
)braket
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
l_string|&quot;rgaint&quot;
)paren
suffix:semicolon
id|spin_lock
(paren
op_amp
id|adapter_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handler
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|adapter_handler
)paren
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_else
(brace
id|adapter_handler
op_assign
id|handler
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
(paren
op_amp
id|adapter_lock
)paren
suffix:semicolon
id|sprintf
(paren
id|dbf_txt
comma
l_string|&quot;ret:%d&quot;
comma
id|ret
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
id|dbf_txt
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_int
DECL|function|s390_unregister_adapter_interrupt
id|s390_unregister_adapter_interrupt
(paren
id|adapter_int_handler_t
id|handler
)paren
(brace
r_int
id|ret
suffix:semicolon
r_char
id|dbf_txt
(braket
l_int|15
)braket
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
l_string|&quot;urgaint&quot;
)paren
suffix:semicolon
id|spin_lock
(paren
op_amp
id|adapter_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handler
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|handler
op_ne
id|adapter_handler
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|adapter_handler
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
(paren
op_amp
id|adapter_lock
)paren
suffix:semicolon
id|sprintf
(paren
id|dbf_txt
comma
l_string|&quot;ret:%d&quot;
comma
id|ret
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
id|dbf_txt
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_void
DECL|function|do_adapter_IO
id|do_adapter_IO
(paren
r_void
)paren
(brace
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
l_string|&quot;doaio&quot;
)paren
suffix:semicolon
id|spin_lock
(paren
op_amp
id|adapter_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adapter_handler
)paren
(paren
op_star
id|adapter_handler
)paren
(paren
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|adapter_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|s390_register_adapter_interrupt
id|EXPORT_SYMBOL
(paren
id|s390_register_adapter_interrupt
)paren
suffix:semicolon
DECL|variable|s390_unregister_adapter_interrupt
id|EXPORT_SYMBOL
(paren
id|s390_unregister_adapter_interrupt
)paren
suffix:semicolon
eof
