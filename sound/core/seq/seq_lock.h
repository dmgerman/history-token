macro_line|#ifndef __SND_SEQ_LOCK_H
DECL|macro|__SND_SEQ_LOCK_H
mdefine_line|#define __SND_SEQ_LOCK_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_SND_DEBUG)
DECL|typedef|snd_use_lock_t
r_typedef
id|atomic_t
id|snd_use_lock_t
suffix:semicolon
multiline_comment|/* initialize lock */
DECL|macro|snd_use_lock_init
mdefine_line|#define snd_use_lock_init(lockp) atomic_set(lockp, 0)
multiline_comment|/* increment lock */
DECL|macro|snd_use_lock_use
mdefine_line|#define snd_use_lock_use(lockp) atomic_inc(lockp)
multiline_comment|/* release lock */
DECL|macro|snd_use_lock_free
mdefine_line|#define snd_use_lock_free(lockp) atomic_dec(lockp)
multiline_comment|/* wait until all locks are released */
r_void
id|snd_use_lock_sync_helper
c_func
(paren
id|snd_use_lock_t
op_star
id|lock
comma
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|snd_use_lock_sync
mdefine_line|#define snd_use_lock_sync(lockp) snd_use_lock_sync_helper(lockp, __BASE_FILE__, __LINE__)
macro_line|#else /* SMP || CONFIG_SND_DEBUG */
DECL|typedef|snd_use_lock_t
r_typedef
id|spinlock_t
id|snd_use_lock_t
suffix:semicolon
multiline_comment|/* dummy */
DECL|macro|snd_use_lock_init
mdefine_line|#define snd_use_lock_init(lockp) /**/
DECL|macro|snd_use_lock_use
mdefine_line|#define snd_use_lock_use(lockp) /**/
DECL|macro|snd_use_lock_free
mdefine_line|#define snd_use_lock_free(lockp) /**/
DECL|macro|snd_use_lock_sync
mdefine_line|#define snd_use_lock_sync(lockp) /**/
macro_line|#endif /* SMP || CONFIG_SND_DEBUG */
macro_line|#endif /* __SND_SEQ_LOCK_H */
eof
