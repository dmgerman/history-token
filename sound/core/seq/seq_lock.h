macro_line|#ifndef __SND_SEQ_LOCK_H
DECL|macro|__SND_SEQ_LOCK_H
mdefine_line|#define __SND_SEQ_LOCK_H
macro_line|#if defined(__SMP__) || defined(CONFIG_SND_DEBUG)
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
multiline_comment|/* (interruptible) sleep_on during the specified spinlock */
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
suffix:semicolon
multiline_comment|/* (interruptible) sleep_on with timeout during the specified spinlock */
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
suffix:semicolon
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
DECL|macro|snd_seq_sleep_in_lock
mdefine_line|#define snd_seq_sleep_in_lock(p,lock)&t;interruptible_sleep_on(p)
DECL|macro|snd_seq_sleep_timeout_in_lock
mdefine_line|#define snd_seq_sleep_timeout_in_lock(p,lock,timeout)&t;interruptible_sleep_on_timeout(p,timeout)
macro_line|#endif /* SMP || CONFIG_SND_DEBUG */
macro_line|#endif /* __SND_SEQ_LOCK_H */
eof
