multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2001&n; *   Portions Copyright (c) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_LOCK
DECL|macro|_H_JFS_LOCK
mdefine_line|#define _H_JFS_LOCK
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; *&t;jfs_lock.h&n; */
multiline_comment|/*&n; * Conditional sleep where condition is protected by spinlock&n; *&n; * lock_cmd and unlock_cmd take and release the spinlock&n; */
DECL|macro|__SLEEP_COND
mdefine_line|#define __SLEEP_COND(wq, cond, lock_cmd, unlock_cmd)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DECLARE_WAITQUEUE(__wait, current);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&bslash;&n;&t;&t;if (cond)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;unlock_cmd;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&bslash;&n;&t;&t;lock_cmd;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&bslash;&n;} while (0)
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_LOCK */
eof
