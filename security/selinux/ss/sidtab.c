multiline_comment|/*&n; * Implementation of the SID table type.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;flask.h&quot;
macro_line|#include &quot;security.h&quot;
macro_line|#include &quot;sidtab.h&quot;
DECL|macro|SIDTAB_HASH
mdefine_line|#define SIDTAB_HASH(sid) &bslash;&n;(sid &amp; SIDTAB_HASH_MASK)
DECL|macro|INIT_SIDTAB_LOCK
mdefine_line|#define INIT_SIDTAB_LOCK(s) spin_lock_init(&amp;s-&gt;lock)
DECL|macro|SIDTAB_LOCK
mdefine_line|#define SIDTAB_LOCK(s) spin_lock_irq(&amp;s-&gt;lock)
DECL|macro|SIDTAB_UNLOCK
mdefine_line|#define SIDTAB_UNLOCK(s) spin_unlock_irq(&amp;s-&gt;lock)
DECL|function|sidtab_init
r_int
id|sidtab_init
c_func
(paren
r_struct
id|sidtab
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
id|s-&gt;htable
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
(paren
id|s-&gt;htable
)paren
)paren
op_star
id|SIDTAB_SIZE
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;htable
)paren
r_return
op_minus
id|ENOMEM
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
id|SIDTAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|s-&gt;htable
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;nel
op_assign
l_int|0
suffix:semicolon
id|s-&gt;next_sid
op_assign
l_int|1
suffix:semicolon
id|s-&gt;shutdown
op_assign
l_int|0
suffix:semicolon
id|INIT_SIDTAB_LOCK
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sidtab_insert
r_int
id|sidtab_insert
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
id|u32
id|sid
comma
r_struct
id|context
op_star
id|context
)paren
(brace
r_int
id|hvalue
comma
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|prev
comma
op_star
id|cur
comma
op_star
id|newnode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|hvalue
op_assign
id|SIDTAB_HASH
c_func
(paren
id|sid
)paren
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|cur
op_assign
id|s-&gt;htable
(braket
id|hvalue
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
op_logical_and
id|sid
OG
id|cur-&gt;sid
)paren
(brace
id|prev
op_assign
id|cur
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cur
op_logical_and
id|sid
op_eq
id|cur-&gt;sid
)paren
(brace
id|rc
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|newnode
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|newnode
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newnode
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|newnode-&gt;sid
op_assign
id|sid
suffix:semicolon
r_if
c_cond
(paren
id|context_cpy
c_func
(paren
op_amp
id|newnode-&gt;context
comma
id|context
)paren
)paren
(brace
id|kfree
c_func
(paren
id|newnode
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
)paren
(brace
id|newnode-&gt;next
op_assign
id|prev-&gt;next
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|prev-&gt;next
op_assign
id|newnode
suffix:semicolon
)brace
r_else
(brace
id|newnode-&gt;next
op_assign
id|s-&gt;htable
(braket
id|hvalue
)braket
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|s-&gt;htable
(braket
id|hvalue
)braket
op_assign
id|newnode
suffix:semicolon
)brace
id|s-&gt;nel
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sid
op_ge
id|s-&gt;next_sid
)paren
id|s-&gt;next_sid
op_assign
id|sid
op_plus
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|sidtab_remove
r_int
id|sidtab_remove
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
id|u32
id|sid
)paren
(brace
r_int
id|hvalue
comma
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|cur
comma
op_star
id|last
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
(brace
id|rc
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|hvalue
op_assign
id|SIDTAB_HASH
c_func
(paren
id|sid
)paren
suffix:semicolon
id|last
op_assign
l_int|NULL
suffix:semicolon
id|cur
op_assign
id|s-&gt;htable
(braket
id|hvalue
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
op_logical_and
id|sid
OG
id|cur-&gt;sid
)paren
(brace
id|last
op_assign
id|cur
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cur
op_eq
l_int|NULL
op_logical_or
id|sid
op_ne
id|cur-&gt;sid
)paren
(brace
id|rc
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last
op_eq
l_int|NULL
)paren
id|s-&gt;htable
(braket
id|hvalue
)braket
op_assign
id|cur-&gt;next
suffix:semicolon
r_else
id|last-&gt;next
op_assign
id|cur-&gt;next
suffix:semicolon
id|context_destroy
c_func
(paren
op_amp
id|cur-&gt;context
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cur
)paren
suffix:semicolon
id|s-&gt;nel
op_decrement
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|sidtab_search
r_struct
id|context
op_star
id|sidtab_search
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
id|u32
id|sid
)paren
(brace
r_int
id|hvalue
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|cur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
l_int|NULL
suffix:semicolon
id|hvalue
op_assign
id|SIDTAB_HASH
c_func
(paren
id|sid
)paren
suffix:semicolon
id|cur
op_assign
id|s-&gt;htable
(braket
id|hvalue
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
op_logical_and
id|sid
OG
id|cur-&gt;sid
)paren
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|cur
op_eq
l_int|NULL
op_logical_or
id|sid
op_ne
id|cur-&gt;sid
)paren
(brace
multiline_comment|/* Remap invalid SIDs to the unlabeled SID. */
id|sid
op_assign
id|SECINITSID_UNLABELED
suffix:semicolon
id|hvalue
op_assign
id|SIDTAB_HASH
c_func
(paren
id|sid
)paren
suffix:semicolon
id|cur
op_assign
id|s-&gt;htable
(braket
id|hvalue
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
op_logical_and
id|sid
OG
id|cur-&gt;sid
)paren
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cur
op_logical_or
id|sid
op_ne
id|cur-&gt;sid
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
op_amp
id|cur-&gt;context
suffix:semicolon
)brace
DECL|function|sidtab_map
r_int
id|sidtab_map
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_int
(paren
op_star
id|apply
)paren
(paren
id|u32
id|sid
comma
r_struct
id|context
op_star
id|context
comma
r_void
op_star
id|args
)paren
comma
r_void
op_star
id|args
)paren
(brace
r_int
id|i
comma
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|cur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_goto
id|out
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
id|SIDTAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cur
op_assign
id|s-&gt;htable
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
)paren
(brace
id|rc
op_assign
id|apply
c_func
(paren
id|cur-&gt;sid
comma
op_amp
id|cur-&gt;context
comma
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|sidtab_map_remove_on_error
r_void
id|sidtab_map_remove_on_error
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_int
(paren
op_star
id|apply
)paren
(paren
id|u32
id|sid
comma
r_struct
id|context
op_star
id|context
comma
r_void
op_star
id|args
)paren
comma
r_void
op_star
id|args
)paren
(brace
r_int
id|i
comma
id|ret
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|last
comma
op_star
id|cur
comma
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
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
id|SIDTAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|last
op_assign
l_int|NULL
suffix:semicolon
id|cur
op_assign
id|s-&gt;htable
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
)paren
(brace
id|ret
op_assign
id|apply
c_func
(paren
id|cur-&gt;sid
comma
op_amp
id|cur-&gt;context
comma
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_if
c_cond
(paren
id|last
)paren
(brace
id|last-&gt;next
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|s-&gt;htable
(braket
id|i
)braket
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
id|temp
op_assign
id|cur
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
id|context_destroy
c_func
(paren
op_amp
id|temp-&gt;context
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|temp
)paren
suffix:semicolon
id|s-&gt;nel
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|last
op_assign
id|cur
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
)brace
r_return
suffix:semicolon
)brace
DECL|function|sidtab_search_context
r_static
r_inline
id|u32
id|sidtab_search_context
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_struct
id|context
op_star
id|context
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|cur
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
id|SIDTAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cur
op_assign
id|s-&gt;htable
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|context_cmp
c_func
(paren
op_amp
id|cur-&gt;context
comma
id|context
)paren
)paren
r_return
id|cur-&gt;sid
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sidtab_context_to_sid
r_int
id|sidtab_context_to_sid
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_struct
id|context
op_star
id|context
comma
id|u32
op_star
id|out_sid
)paren
(brace
id|u32
id|sid
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
op_star
id|out_sid
op_assign
id|SECSID_NULL
suffix:semicolon
id|sid
op_assign
id|sidtab_search_context
c_func
(paren
id|s
comma
id|context
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sid
)paren
(brace
id|SIDTAB_LOCK
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* Rescan now that we hold the lock. */
id|sid
op_assign
id|sidtab_search_context
c_func
(paren
id|s
comma
id|context
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sid
)paren
r_goto
id|unlock_out
suffix:semicolon
multiline_comment|/* No SID exists for the context.  Allocate a new one. */
r_if
c_cond
(paren
id|s-&gt;next_sid
op_eq
id|UINT_MAX
op_logical_or
id|s-&gt;shutdown
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|unlock_out
suffix:semicolon
)brace
id|sid
op_assign
id|s-&gt;next_sid
op_increment
suffix:semicolon
id|ret
op_assign
id|sidtab_insert
c_func
(paren
id|s
comma
id|sid
comma
id|context
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|s-&gt;next_sid
op_decrement
suffix:semicolon
id|unlock_out
suffix:colon
id|SIDTAB_UNLOCK
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
op_star
id|out_sid
op_assign
id|sid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sidtab_hash_eval
r_void
id|sidtab_hash_eval
c_func
(paren
r_struct
id|sidtab
op_star
id|h
comma
r_char
op_star
id|tag
)paren
(brace
r_int
id|i
comma
id|chain_len
comma
id|slots_used
comma
id|max_chain_len
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|cur
suffix:semicolon
id|slots_used
op_assign
l_int|0
suffix:semicolon
id|max_chain_len
op_assign
l_int|0
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
id|SIDTAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cur
op_assign
id|h-&gt;htable
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cur
)paren
(brace
id|slots_used
op_increment
suffix:semicolon
id|chain_len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cur
)paren
(brace
id|chain_len
op_increment
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chain_len
OG
id|max_chain_len
)paren
id|max_chain_len
op_assign
id|chain_len
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  %d entries and %d/%d buckets used, longest &quot;
l_string|&quot;chain length %d&bslash;n&quot;
comma
id|tag
comma
id|h-&gt;nel
comma
id|slots_used
comma
id|SIDTAB_SIZE
comma
id|max_chain_len
)paren
suffix:semicolon
)brace
DECL|function|sidtab_destroy
r_void
id|sidtab_destroy
c_func
(paren
r_struct
id|sidtab
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sidtab_node
op_star
id|cur
comma
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
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
id|SIDTAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cur
op_assign
id|s-&gt;htable
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
)paren
(brace
id|temp
op_assign
id|cur
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
id|context_destroy
c_func
(paren
op_amp
id|temp-&gt;context
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|temp
)paren
suffix:semicolon
)brace
id|s-&gt;htable
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|s-&gt;htable
)paren
suffix:semicolon
id|s-&gt;htable
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;nel
op_assign
l_int|0
suffix:semicolon
id|s-&gt;next_sid
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|sidtab_set
r_void
id|sidtab_set
c_func
(paren
r_struct
id|sidtab
op_star
id|dst
comma
r_struct
id|sidtab
op_star
id|src
)paren
(brace
id|SIDTAB_LOCK
c_func
(paren
id|src
)paren
suffix:semicolon
id|dst-&gt;htable
op_assign
id|src-&gt;htable
suffix:semicolon
id|dst-&gt;nel
op_assign
id|src-&gt;nel
suffix:semicolon
id|dst-&gt;next_sid
op_assign
id|src-&gt;next_sid
suffix:semicolon
id|dst-&gt;shutdown
op_assign
l_int|0
suffix:semicolon
id|SIDTAB_UNLOCK
c_func
(paren
id|src
)paren
suffix:semicolon
)brace
DECL|function|sidtab_shutdown
r_void
id|sidtab_shutdown
c_func
(paren
r_struct
id|sidtab
op_star
id|s
)paren
(brace
id|SIDTAB_LOCK
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;shutdown
op_assign
l_int|1
suffix:semicolon
id|SIDTAB_UNLOCK
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
eof
