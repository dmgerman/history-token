multiline_comment|/* $Id: fsm.c,v 1.14.6.4 2001/09/23 22:24:47 kai Exp $&n; *&n; * Finite state machine&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; *              by Kai Germaschewski &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;isdn_fsm.h&quot;
r_int
DECL|function|fsm_new
id|fsm_new
c_func
(paren
r_struct
id|fsm
op_star
id|fsm
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|size
op_assign
r_sizeof
(paren
id|fsm_fn
)paren
op_star
id|fsm-&gt;st_cnt
op_star
id|fsm-&gt;ev_cnt
suffix:semicolon
id|fsm-&gt;jumpmatrix
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fsm-&gt;jumpmatrix
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|fsm-&gt;jumpmatrix
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fsm-&gt;fn_cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|st
op_ge
id|fsm-&gt;st_cnt
op_logical_or
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|ev
op_ge
id|fsm-&gt;ev_cnt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;FsmNew Error line %d st(%d/%d) ev(%d/%d)&bslash;n&quot;
comma
id|i
comma
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|st
comma
id|fsm-&gt;st_cnt
comma
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|ev
comma
id|fsm-&gt;ev_cnt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fsm-&gt;jumpmatrix
(braket
id|fsm-&gt;st_cnt
op_star
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|ev
op_plus
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|st
)braket
op_assign
id|fsm-&gt;fn_tbl
(braket
id|i
)braket
dot
id|fn
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|fsm_free
id|fsm_free
c_func
(paren
r_struct
id|fsm
op_star
id|fsm
)paren
(brace
id|kfree
c_func
(paren
id|fsm-&gt;jumpmatrix
)paren
suffix:semicolon
)brace
r_int
DECL|function|fsm_event
id|fsm_event
c_func
(paren
r_struct
id|fsm_inst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
id|fsm_fn
id|fn
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;state
op_ge
id|fi-&gt;fsm-&gt;st_cnt
op_logical_or
id|event
op_ge
id|fi-&gt;fsm-&gt;ev_cnt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;FsmEvent Error st(%d/%d) ev(%d/%d)&bslash;n&quot;
comma
id|fi-&gt;state
comma
id|fi-&gt;fsm-&gt;st_cnt
comma
id|event
comma
id|fi-&gt;fsm-&gt;ev_cnt
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|fn
op_assign
id|fi-&gt;fsm-&gt;jumpmatrix
(braket
id|fi-&gt;fsm-&gt;st_cnt
op_star
id|event
op_plus
id|fi-&gt;state
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
(brace
r_if
c_cond
(paren
id|fi-&gt;debug
)paren
id|fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|fi
comma
l_string|&quot;State %s Event %s no routine&quot;
comma
id|fi-&gt;fsm-&gt;st_str
(braket
id|fi-&gt;state
)braket
comma
id|fi-&gt;fsm-&gt;ev_str
(braket
id|event
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fi-&gt;debug
)paren
id|fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|fi
comma
l_string|&quot;State %s Event %s&quot;
comma
id|fi-&gt;fsm-&gt;st_str
(braket
id|fi-&gt;state
)braket
comma
id|fi-&gt;fsm-&gt;ev_str
(braket
id|event
)braket
)paren
suffix:semicolon
r_return
id|fn
c_func
(paren
id|fi
comma
id|event
comma
id|arg
)paren
suffix:semicolon
)brace
r_void
DECL|function|fsm_change_state
id|fsm_change_state
c_func
(paren
r_struct
id|fsm_inst
op_star
id|fi
comma
r_int
id|newstate
)paren
(brace
id|fi-&gt;state
op_assign
id|newstate
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;debug
)paren
id|fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|fi
comma
l_string|&quot;ChangeState %s&quot;
comma
id|fi-&gt;fsm-&gt;st_str
(braket
id|newstate
)braket
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|FsmExpireTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmExpireTimer %lx&quot;
comma
(paren
r_int
)paren
id|ft
)paren
suffix:semicolon
macro_line|#endif
id|FsmEvent
c_func
(paren
id|ft-&gt;fi
comma
id|ft-&gt;event
comma
id|ft-&gt;arg
)paren
suffix:semicolon
)brace
r_void
id|FsmInitTimer
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_struct
id|FsmTimer
op_star
id|ft
)paren
(brace
id|ft-&gt;fi
op_assign
id|fi
suffix:semicolon
id|ft-&gt;tl.function
op_assign
(paren
r_void
op_star
)paren
id|FsmExpireTimer
suffix:semicolon
id|ft-&gt;tl.data
op_assign
(paren
r_int
)paren
id|ft
suffix:semicolon
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmInitTimer %lx&quot;
comma
(paren
r_int
)paren
id|ft
)paren
suffix:semicolon
macro_line|#endif
id|init_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
)brace
r_void
id|FsmDelTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|where
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmDelTimer %lx %d&quot;
comma
(paren
r_int
)paren
id|ft
comma
id|where
)paren
suffix:semicolon
macro_line|#endif
id|del_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
)brace
r_int
id|FsmAddTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|millisec
comma
r_int
id|event
comma
r_void
op_star
id|arg
comma
r_int
id|where
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmAddTimer %lx %d %d&quot;
comma
(paren
r_int
)paren
id|ft
comma
id|millisec
comma
id|where
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;FsmAddTimer: timer already active!&bslash;n&quot;
)paren
suffix:semicolon
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmAddTimer already active!&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
id|ft-&gt;event
op_assign
id|event
suffix:semicolon
id|ft-&gt;arg
op_assign
id|arg
suffix:semicolon
id|ft-&gt;tl.expires
op_assign
id|jiffies
op_plus
(paren
id|millisec
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|FsmRestartTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|millisec
comma
r_int
id|event
comma
r_void
op_star
id|arg
comma
r_int
id|where
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmRestartTimer %lx %d %d&quot;
comma
(paren
r_int
)paren
id|ft
comma
id|millisec
comma
id|where
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
)paren
id|del_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
id|ft-&gt;event
op_assign
id|event
suffix:semicolon
id|ft-&gt;arg
op_assign
id|arg
suffix:semicolon
id|ft-&gt;tl.expires
op_assign
id|jiffies
op_plus
(paren
id|millisec
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
