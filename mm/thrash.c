multiline_comment|/*&n; * mm/thrash.c&n; *&n; * Copyright (C) 2004, Red Hat, Inc.&n; * Copyright (C) 2004, Rik van Riel &lt;riel@redhat.com&gt;&n; * Released under the GPL, see the file COPYING for details.&n; *&n; * Simple token based thrashing protection, using the algorithm&n; * described in:  http://www.cs.wm.edu/~sjiang/token.pdf&n; */
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
DECL|variable|swap_token_lock
r_static
id|spinlock_t
id|swap_token_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|swap_token_timeout
r_static
r_int
r_int
id|swap_token_timeout
suffix:semicolon
DECL|variable|swap_token_check
r_int
r_int
id|swap_token_check
suffix:semicolon
DECL|variable|swap_token_mm
r_struct
id|mm_struct
op_star
id|swap_token_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
DECL|macro|SWAP_TOKEN_CHECK_INTERVAL
mdefine_line|#define SWAP_TOKEN_CHECK_INTERVAL (HZ * 2)
DECL|macro|SWAP_TOKEN_TIMEOUT
mdefine_line|#define SWAP_TOKEN_TIMEOUT (HZ * 300)
DECL|variable|swap_token_default_timeout
r_int
r_int
id|swap_token_default_timeout
op_assign
id|SWAP_TOKEN_TIMEOUT
suffix:semicolon
multiline_comment|/*&n; * Take the token away if the process had no page faults&n; * in the last interval, or if it has held the token for&n; * too long.&n; */
DECL|macro|SWAP_TOKEN_ENOUGH_RSS
mdefine_line|#define SWAP_TOKEN_ENOUGH_RSS 1
DECL|macro|SWAP_TOKEN_TIMED_OUT
mdefine_line|#define SWAP_TOKEN_TIMED_OUT 2
DECL|function|should_release_swap_token
r_static
r_int
id|should_release_swap_token
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm-&gt;recent_pagein
)paren
id|ret
op_assign
id|SWAP_TOKEN_ENOUGH_RSS
suffix:semicolon
r_else
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|swap_token_timeout
)paren
)paren
id|ret
op_assign
id|SWAP_TOKEN_TIMED_OUT
suffix:semicolon
id|mm-&gt;recent_pagein
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to grab the swapout protection token.  We only try to&n; * grab it once every TOKEN_CHECK_INTERVAL, both to prevent&n; * SMP lock contention and to check that the process that held&n; * the token before is no longer thrashing.&n; */
DECL|function|grab_swap_token
r_void
id|grab_swap_token
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_int
id|reason
suffix:semicolon
multiline_comment|/* We have the token. Let others know we still need it. */
r_if
c_cond
(paren
id|has_swap_token
c_func
(paren
id|current-&gt;mm
)paren
)paren
(brace
id|current-&gt;mm-&gt;recent_pagein
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|swap_token_check
)paren
)paren
(brace
multiline_comment|/* Can&squot;t get swapout protection if we exceed our RSS limit. */
singleline_comment|// if (current-&gt;mm-&gt;rss &gt; current-&gt;mm-&gt;rlimit_rss)
singleline_comment|//&t;return;
multiline_comment|/* ... or if we recently held the token. */
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|current-&gt;mm-&gt;swap_token_time
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|swap_token_lock
)paren
)paren
r_return
suffix:semicolon
id|swap_token_check
op_assign
id|jiffies
op_plus
id|SWAP_TOKEN_CHECK_INTERVAL
suffix:semicolon
id|mm
op_assign
id|swap_token_mm
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reason
op_assign
id|should_release_swap_token
c_func
(paren
id|mm
)paren
)paren
)paren
(brace
r_int
r_int
id|eligible
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|reason
op_eq
id|SWAP_TOKEN_TIMED_OUT
)paren
(brace
id|eligible
op_add_assign
id|swap_token_default_timeout
suffix:semicolon
)brace
id|mm-&gt;swap_token_time
op_assign
id|eligible
suffix:semicolon
id|swap_token_timeout
op_assign
id|jiffies
op_plus
id|swap_token_default_timeout
suffix:semicolon
id|swap_token_mm
op_assign
id|current-&gt;mm
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|swap_token_lock
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Called on process exit. */
DECL|function|__put_swap_token
r_void
id|__put_swap_token
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|swap_token_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|mm
op_eq
id|swap_token_mm
)paren
)paren
(brace
id|swap_token_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|swap_token_check
op_assign
id|jiffies
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|swap_token_lock
)paren
suffix:semicolon
)brace
eof
