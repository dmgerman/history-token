multiline_comment|/*&n; *&t;SMP locks primitives for building ix86 locks&n; *&t;(not yet used).&n; *&n; *&t;&t;Alan Cox, alan@cymru.net, 1995&n; */
multiline_comment|/*&n; *&t;This would be much easier but far less clear and easy&n; *&t;to borrow for other processors if it was just assembler.&n; */
DECL|function|prim_spin_lock
r_extern
id|__inline__
r_void
id|prim_spin_lock
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
r_int
id|processor
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Grab the lock bit&n;&t; */
r_while
c_loop
(paren
id|lock_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|sp-&gt;lock
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Failed, but that&squot;s cos we own it!&n;&t;&t; */
r_if
c_cond
(paren
id|sp-&gt;cpu
op_eq
id|processor
)paren
(brace
id|sp-&gt;users
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Spin in the cache S state if possible&n;&t;&t; */
r_while
c_loop
(paren
id|sp-&gt;lock
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Wait for any invalidates to go off&n;&t;&t;&t; */
r_if
c_cond
(paren
id|smp_invalidate_needed
op_amp
(paren
l_int|1
op_lshift
id|processor
)paren
)paren
r_while
c_loop
(paren
id|lock_clear_bit
c_func
(paren
id|processor
comma
op_amp
id|smp_invalidate_needed
)paren
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
id|sp-&gt;spins
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Someone wrote the line, we go &squot;I&squot; and get&n;&t;&t; *&t;the cache entry. Now try to regrab&n;&t;&t; */
)brace
id|sp-&gt;users
op_increment
suffix:semicolon
id|sp-&gt;cpu
op_assign
id|processor
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Release a spin lock&n; */
DECL|function|prim_spin_unlock
r_extern
id|__inline__
r_int
id|prim_spin_unlock
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
multiline_comment|/* This is safe. The decrement is still guarded by the lock. A multilock would&n;&t;   not be safe this way */
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|sp-&gt;users
)paren
(brace
id|lock_clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|sp-&gt;lock
)paren
suffix:semicolon
id|sp-&gt;cpu
op_assign
id|NO_PROC_ID
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Non blocking lock grab&n; */
DECL|function|prim_spin_lock_nb
r_extern
id|__inline__
r_int
id|prim_spin_lock_nb
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
id|lock_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|sp-&gt;lock
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Locked already */
id|sp-&gt;users
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* We got the lock */
)brace
multiline_comment|/*&n; *&t;These wrap the locking primitives up for usage&n; */
DECL|function|spinlock
r_extern
id|__inline__
r_void
id|spinlock
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
id|sp-&gt;priority
OL
id|current-&gt;lock_order
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;lock order violation: %s (%d)&bslash;n&quot;
comma
id|sp-&gt;name
comma
id|current-&gt;lock_order
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prim_spin_lock
c_func
(paren
id|sp
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;We got a new lock. Update the priority chain&n;&t;&t; */
id|sp-&gt;oldpri
op_assign
id|current-&gt;lock_order
suffix:semicolon
id|current-&gt;lock_order
op_assign
id|sp-&gt;priority
suffix:semicolon
)brace
)brace
DECL|function|spinunlock
r_extern
id|__inline__
r_void
id|spinunlock
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;lock_order
op_ne
id|sp-&gt;priority
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;lock release order violation %s (%d)&bslash;n&quot;
comma
id|sp-&gt;name
comma
id|current-&gt;lock_order
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prim_spin_unlock
c_func
(paren
id|sp
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Update the debugging lock priority chain. We dumped&n;&t;&t; *&t;our last right to the lock.&n;&t;&t; */
id|current-&gt;lock_order
op_assign
id|sp-&gt;oldpri
suffix:semicolon
)brace
)brace
DECL|function|spintestlock
r_extern
id|__inline__
r_void
id|spintestlock
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
multiline_comment|/*&n;&t; *&t;We do no sanity checks, it&squot;s legal to optimistically&n;&t; *&t;get a lower lock.&n;&t; */
id|prim_spin_lock_nb
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
DECL|function|spintestunlock
r_extern
id|__inline__
r_void
id|spintestunlock
c_func
(paren
r_struct
id|spinlock
op_star
id|sp
)paren
(brace
multiline_comment|/*&n;&t; *&t;A testlock doesn&squot;t update the lock chain so we&n;&t; *&t;must not update it on free&n;&t; */
id|prim_spin_unlock
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
eof
