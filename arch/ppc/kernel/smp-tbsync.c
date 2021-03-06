multiline_comment|/*&n; * Smp timebase synchronization for ppc.&n; *&n; * Copyright (C) 2003 Samuel Rydh (samuel@ibrium.se)&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/time.h&gt;
DECL|macro|NUM_ITER
mdefine_line|#define NUM_ITER&t;&t;300
r_enum
(brace
DECL|enumerator|kExit
DECL|enumerator|kSetAndTest
DECL|enumerator|kTest
id|kExit
op_assign
l_int|0
comma
id|kSetAndTest
comma
id|kTest
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|tbu
r_volatile
r_int
id|tbu
suffix:semicolon
DECL|member|tbl
r_volatile
r_int
id|tbl
suffix:semicolon
DECL|member|mark
r_volatile
r_int
id|mark
suffix:semicolon
DECL|member|cmd
r_volatile
r_int
id|cmd
suffix:semicolon
DECL|member|handshake
r_volatile
r_int
id|handshake
suffix:semicolon
DECL|member|filler
r_int
id|filler
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ack
r_volatile
r_int
id|ack
suffix:semicolon
DECL|member|filler2
r_int
id|filler2
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|race_result
r_volatile
r_int
id|race_result
suffix:semicolon
DECL|variable|tbsync
)brace
op_star
id|tbsync
suffix:semicolon
DECL|variable|running
r_static
r_volatile
r_int
id|running
suffix:semicolon
r_static
r_void
id|__devinit
DECL|function|enter_contest
id|enter_contest
c_func
(paren
r_int
id|mark
comma
r_int
id|add
)paren
(brace
r_while
c_loop
(paren
(paren
r_int
)paren
(paren
id|get_tbl
c_func
(paren
)paren
op_minus
id|mark
)paren
OL
l_int|0
)paren
(brace
id|tbsync-&gt;race_result
op_assign
id|add
suffix:semicolon
)brace
)brace
r_void
id|__devinit
DECL|function|smp_generic_take_timebase
id|smp_generic_take_timebase
c_func
(paren
r_void
)paren
(brace
r_int
id|cmd
comma
id|tbl
comma
id|tbu
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|running
)paren
(brace
suffix:semicolon
)brace
id|rmb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|tbsync-&gt;ack
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|tbsync-&gt;handshake
)paren
(brace
suffix:semicolon
)brace
id|rmb
c_func
(paren
)paren
suffix:semicolon
id|cmd
op_assign
id|tbsync-&gt;cmd
suffix:semicolon
id|tbl
op_assign
id|tbsync-&gt;tbl
suffix:semicolon
id|tbu
op_assign
id|tbsync-&gt;tbu
suffix:semicolon
id|tbsync-&gt;ack
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|kExit
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|kSetAndTest
)paren
(brace
r_while
c_loop
(paren
id|tbsync-&gt;handshake
)paren
(brace
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;mttbl %0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tbl
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mttbu %0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tbu
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|tbsync-&gt;handshake
)paren
(brace
suffix:semicolon
)brace
)brace
id|enter_contest
c_func
(paren
id|tbsync-&gt;mark
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|start_contest
id|start_contest
c_func
(paren
r_int
id|cmd
comma
r_int
id|offset
comma
r_int
id|num
)paren
(brace
r_int
id|i
comma
id|tbu
comma
id|tbl
comma
id|mark
comma
id|score
op_assign
l_int|0
suffix:semicolon
id|tbsync-&gt;cmd
op_assign
id|cmd
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|3
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
)paren
(brace
id|tbl
op_assign
id|get_tbl
c_func
(paren
)paren
op_plus
l_int|400
suffix:semicolon
id|tbsync-&gt;tbu
op_assign
id|tbu
op_assign
id|get_tbu
c_func
(paren
)paren
suffix:semicolon
id|tbsync-&gt;tbl
op_assign
id|tbl
op_plus
id|offset
suffix:semicolon
id|tbsync-&gt;mark
op_assign
id|mark
op_assign
id|tbl
op_plus
l_int|400
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|tbsync-&gt;handshake
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|tbsync-&gt;ack
)paren
(brace
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
r_int
)paren
(paren
id|get_tbl
c_func
(paren
)paren
op_minus
id|tbl
)paren
op_le
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|tbsync-&gt;handshake
op_assign
l_int|0
suffix:semicolon
id|enter_contest
c_func
(paren
id|mark
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|tbsync-&gt;ack
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tbsync-&gt;tbu
op_ne
id|get_tbu
c_func
(paren
)paren
op_logical_or
(paren
(paren
id|tbsync-&gt;tbl
op_xor
id|get_tbl
c_func
(paren
)paren
)paren
op_amp
l_int|0x80000000
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_increment
OG
l_int|0
)paren
(brace
id|score
op_add_assign
id|tbsync-&gt;race_result
suffix:semicolon
)brace
)brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|score
suffix:semicolon
)brace
r_void
id|__devinit
DECL|function|smp_generic_give_timebase
id|smp_generic_give_timebase
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|score
comma
id|score2
comma
id|old
comma
id|min
op_assign
l_int|0
comma
id|max
op_assign
l_int|5000
comma
id|offset
op_assign
l_int|1000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Synchronizing timebase&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* if this fails then this kernel won&squot;t work anyway... */
id|tbsync
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tbsync
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|tbsync
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tbsync
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|running
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|tbsync-&gt;ack
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* binary search */
r_for
c_loop
(paren
id|old
op_assign
op_minus
l_int|1
suffix:semicolon
id|old
op_ne
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|min
op_plus
id|max
)paren
op_div
l_int|2
)paren
(brace
id|score
op_assign
id|start_contest
c_func
(paren
id|kSetAndTest
comma
id|offset
comma
id|NUM_ITER
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;score %d, offset %d&bslash;n&quot;
comma
id|score
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|score
OG
l_int|0
)paren
(brace
id|max
op_assign
id|offset
suffix:semicolon
)brace
r_else
id|min
op_assign
id|offset
suffix:semicolon
id|old
op_assign
id|offset
suffix:semicolon
)brace
id|score
op_assign
id|start_contest
c_func
(paren
id|kSetAndTest
comma
id|min
comma
id|NUM_ITER
)paren
suffix:semicolon
id|score2
op_assign
id|start_contest
c_func
(paren
id|kSetAndTest
comma
id|max
comma
id|NUM_ITER
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Min %d (score %d), Max %d (score %d)&bslash;n&quot;
comma
id|min
comma
id|score
comma
id|max
comma
id|score2
)paren
suffix:semicolon
id|score
op_assign
id|abs
c_func
(paren
id|score
)paren
suffix:semicolon
id|score2
op_assign
id|abs
c_func
(paren
id|score2
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|score
OL
id|score2
)paren
ques
c_cond
id|min
suffix:colon
id|max
suffix:semicolon
multiline_comment|/* guard against inaccurate mttb */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|start_contest
c_func
(paren
id|kSetAndTest
comma
id|offset
comma
id|NUM_ITER
op_div
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|score2
op_assign
id|start_contest
c_func
(paren
id|kTest
comma
id|offset
comma
id|NUM_ITER
)paren
)paren
OL
l_int|0
)paren
(brace
id|score2
op_assign
op_minus
id|score2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|score2
op_le
id|score
op_logical_or
id|score2
OL
l_int|20
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Final offset: %d (%d/%d)&bslash;n&quot;
comma
id|offset
comma
id|score2
comma
id|NUM_ITER
)paren
suffix:semicolon
multiline_comment|/* exiting */
id|tbsync-&gt;cmd
op_assign
id|kExit
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|tbsync-&gt;handshake
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|tbsync-&gt;ack
)paren
(brace
suffix:semicolon
)brace
id|tbsync-&gt;handshake
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|tbsync
)paren
suffix:semicolon
id|tbsync
op_assign
l_int|NULL
suffix:semicolon
id|running
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* all done */
id|smp_tb_synchronized
op_assign
l_int|1
suffix:semicolon
)brace
eof
