macro_line|#include &lt;linux/percpu_counter.h&gt;
DECL|function|percpu_counter_mod
r_void
id|percpu_counter_mod
c_func
(paren
r_struct
id|percpu_counter
op_star
id|fbc
comma
r_int
id|amount
)paren
(brace
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_int
id|count
op_assign
id|fbc-&gt;counters
(braket
id|cpu
)braket
dot
id|count
suffix:semicolon
id|count
op_add_assign
id|amount
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|FBC_BATCH
op_logical_or
id|count
op_le
op_minus
id|FBC_BATCH
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|fbc-&gt;lock
)paren
suffix:semicolon
id|fbc-&gt;count
op_add_assign
id|count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|fbc-&gt;lock
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
)brace
id|fbc-&gt;counters
(braket
id|cpu
)braket
dot
id|count
op_assign
id|count
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
eof
