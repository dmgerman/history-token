multiline_comment|/*&n; *  Do sleep inside a spin-lock&n; *  Copyright (c) 1999 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;seq_lock.h&quot;
macro_line|#if defined(__SMP__) || defined(CONFIG_SND_DEBUG)
multiline_comment|/* (interruptible) sleep_on during the specified spinlock */
DECL|function|snd_seq_sleep_in_lock
r_void
id|snd_seq_sleep_in_lock
c_func
(paren
id|wait_queue_head_t
op_star
id|p
comma
id|spinlock_t
op_star
id|lock
)paren
(brace
id|wait_queue_t
id|wait
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|p
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|lock
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|p
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/* (interruptible) sleep_on with timeout during the specified spinlock */
DECL|function|snd_seq_sleep_timeout_in_lock
r_int
id|snd_seq_sleep_timeout_in_lock
c_func
(paren
id|wait_queue_head_t
op_star
id|p
comma
id|spinlock_t
op_star
id|lock
comma
r_int
id|timeout
)paren
(brace
id|wait_queue_t
id|wait
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|p
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|timeout
op_assign
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
id|lock
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
id|p
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|timeout
suffix:semicolon
)brace
multiline_comment|/* wait until all locks are released */
DECL|function|snd_use_lock_sync_helper
r_void
id|snd_use_lock_sync_helper
c_func
(paren
id|snd_use_lock_t
op_star
id|lockp
comma
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
(brace
r_int
id|max_count
op_assign
l_int|5
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
id|lockp
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;seq_lock: lock trouble [counter = %d] in %s:%d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
id|lockp
)paren
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
id|lockp
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|max_count
op_eq
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;seq_lock: timeout [%d left] in %s:%d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
id|lockp
)paren
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|max_count
op_decrement
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
