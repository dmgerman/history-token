multiline_comment|/*&n; * Per-blockgroup locking for ext2 and ext3.&n; *&n; * Simple hashed spinlocking.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * We want a power-of-two.  Is there a better way than this?&n; */
macro_line|#if NR_CPUS &gt;= 32
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;128
macro_line|#elif NR_CPUS &gt;= 16
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;64
macro_line|#elif NR_CPUS &gt;= 8
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;32
macro_line|#elif NR_CPUS &gt;= 4
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;16
macro_line|#elif NR_CPUS &gt;= 2
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;8
macro_line|#else
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;4
macro_line|#endif
macro_line|#else&t;/* CONFIG_SMP */
DECL|macro|NR_BG_LOCKS
mdefine_line|#define NR_BG_LOCKS&t;1
macro_line|#endif&t;/* CONFIG_SMP */
DECL|struct|bgl_lock
r_struct
id|bgl_lock
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|variable|____cacheline_aligned_in_smp
)brace
id|____cacheline_aligned_in_smp
suffix:semicolon
DECL|struct|blockgroup_lock
r_struct
id|blockgroup_lock
(brace
DECL|member|locks
r_struct
id|bgl_lock
id|locks
(braket
id|NR_BG_LOCKS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|bgl_lock_init
r_static
r_inline
r_void
id|bgl_lock_init
c_func
(paren
r_struct
id|blockgroup_lock
op_star
id|bgl
)paren
(brace
r_int
id|i
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
id|NR_BG_LOCKS
suffix:semicolon
id|i
op_increment
)paren
id|spin_lock_init
c_func
(paren
op_amp
id|bgl-&gt;locks
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The accessor is a macro so we can embed a blockgroup_lock into different&n; * superblock types&n; */
DECL|macro|sb_bgl_lock
mdefine_line|#define sb_bgl_lock(sb, block_group) &bslash;&n;&t;(&amp;(sb)-&gt;s_blockgroup_lock.locks[(block_group) &amp; (NR_BG_LOCKS-1)].lock)
eof
