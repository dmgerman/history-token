macro_line|#ifndef __LINUX_DCACHE_H
DECL|macro|__LINUX_DCACHE_H
mdefine_line|#define __LINUX_DCACHE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;asm/page.h&gt;&t;&t;&t;/* for BUG() */
multiline_comment|/*&n; * linux/include/linux/dcache.h&n; *&n; * Dirent cache data structures&n; *&n; * (C) Copyright 1997 Thomas Schoebel-Theuer,&n; * with heavy changes by Linus Torvalds&n; */
DECL|macro|IS_ROOT
mdefine_line|#define IS_ROOT(x) ((x) == (x)-&gt;d_parent)
multiline_comment|/*&n; * &quot;quick string&quot; -- eases parameter passing, but more importantly&n; * saves &quot;metadata&quot; about the string (ie length and the hash).&n; */
DECL|struct|qstr
r_struct
id|qstr
(brace
DECL|member|name
r_const
r_int
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|hash
r_int
r_int
id|hash
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dentry_stat_t
r_struct
id|dentry_stat_t
(brace
DECL|member|nr_dentry
r_int
id|nr_dentry
suffix:semicolon
DECL|member|nr_unused
r_int
id|nr_unused
suffix:semicolon
DECL|member|age_limit
r_int
id|age_limit
suffix:semicolon
multiline_comment|/* age in seconds */
DECL|member|want_pages
r_int
id|want_pages
suffix:semicolon
multiline_comment|/* pages requested by system */
DECL|member|dummy
r_int
id|dummy
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dentry_stat_t
id|dentry_stat
suffix:semicolon
multiline_comment|/* Name hashing routines. Initial hash value */
multiline_comment|/* Hash courtesy of the R5 hash in reiserfs modulo sign bits */
DECL|macro|init_name_hash
mdefine_line|#define init_name_hash()&t;&t;0
multiline_comment|/* partial hash update function. Assume roughly 4 bits per character */
DECL|function|partial_name_hash
r_static
id|__inline__
r_int
r_int
id|partial_name_hash
c_func
(paren
r_int
r_int
id|c
comma
r_int
r_int
id|prevhash
)paren
(brace
r_return
(paren
id|prevhash
op_plus
(paren
id|c
op_lshift
l_int|4
)paren
op_plus
(paren
id|c
op_rshift
l_int|4
)paren
)paren
op_star
l_int|11
suffix:semicolon
)brace
multiline_comment|/* Finally: cut down the number of bits to a int value (and try to avoid losing bits) */
DECL|function|end_name_hash
r_static
id|__inline__
r_int
r_int
id|end_name_hash
c_func
(paren
r_int
r_int
id|hash
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|hash
suffix:semicolon
)brace
multiline_comment|/* Compute the hash for a name string. */
DECL|function|full_name_hash
r_static
id|__inline__
r_int
r_int
id|full_name_hash
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|hash
op_assign
id|init_name_hash
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
op_star
id|name
op_increment
comma
id|hash
)paren
suffix:semicolon
r_return
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
)brace
DECL|macro|DNAME_INLINE_LEN
mdefine_line|#define DNAME_INLINE_LEN 16
DECL|struct|dentry
r_struct
id|dentry
(brace
DECL|member|d_count
id|atomic_t
id|d_count
suffix:semicolon
DECL|member|d_flags
r_int
r_int
id|d_flags
suffix:semicolon
DECL|member|d_inode
r_struct
id|inode
op_star
id|d_inode
suffix:semicolon
multiline_comment|/* Where the name belongs to - NULL is negative */
DECL|member|d_parent
r_struct
id|dentry
op_star
id|d_parent
suffix:semicolon
multiline_comment|/* parent directory */
DECL|member|d_hash
r_struct
id|list_head
id|d_hash
suffix:semicolon
multiline_comment|/* lookup hash list */
DECL|member|d_lru
r_struct
id|list_head
id|d_lru
suffix:semicolon
multiline_comment|/* d_count = 0 LRU list */
DECL|member|d_child
r_struct
id|list_head
id|d_child
suffix:semicolon
multiline_comment|/* child of parent list */
DECL|member|d_subdirs
r_struct
id|list_head
id|d_subdirs
suffix:semicolon
multiline_comment|/* our children */
DECL|member|d_alias
r_struct
id|list_head
id|d_alias
suffix:semicolon
multiline_comment|/* inode alias list */
DECL|member|d_mounted
r_int
id|d_mounted
suffix:semicolon
DECL|member|d_name
r_struct
id|qstr
id|d_name
suffix:semicolon
DECL|member|d_time
r_int
r_int
id|d_time
suffix:semicolon
multiline_comment|/* used by d_revalidate */
DECL|member|d_op
r_struct
id|dentry_operations
op_star
id|d_op
suffix:semicolon
DECL|member|d_sb
r_struct
id|super_block
op_star
id|d_sb
suffix:semicolon
multiline_comment|/* The root of the dentry tree */
DECL|member|d_vfs_flags
r_int
r_int
id|d_vfs_flags
suffix:semicolon
DECL|member|d_fsdata
r_void
op_star
id|d_fsdata
suffix:semicolon
multiline_comment|/* fs-specific data */
DECL|member|d_iname
r_int
r_char
id|d_iname
(braket
id|DNAME_INLINE_LEN
)braket
suffix:semicolon
multiline_comment|/* small names */
)brace
suffix:semicolon
DECL|struct|dentry_operations
r_struct
id|dentry_operations
(brace
DECL|member|d_revalidate
r_int
(paren
op_star
id|d_revalidate
)paren
(paren
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|d_hash
r_int
(paren
op_star
id|d_hash
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|d_compare
r_int
(paren
op_star
id|d_compare
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|d_delete
r_int
(paren
op_star
id|d_delete
)paren
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|member|d_release
r_void
(paren
op_star
id|d_release
)paren
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|member|d_iput
r_void
(paren
op_star
id|d_iput
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* the dentry parameter passed to d_hash and d_compare is the parent&n; * directory of the entries to be compared. It is used in case these&n; * functions need any directory specific information for determining&n; * equivalency classes.  Using the dentry itself might not work, as it&n; * might be a negative dentry which has no information associated with&n; * it */
multiline_comment|/*&n;locking rules:&n;&t;&t;big lock&t;dcache_lock&t;may block&n;d_revalidate:&t;no&t;&t;no&t;&t;yes&n;d_hash&t;&t;no&t;&t;no&t;&t;yes&n;d_compare:&t;no&t;&t;yes&t;&t;no&n;d_delete:&t;no&t;&t;yes&t;&t;no&n;d_release:&t;no&t;&t;no&t;&t;yes&n;d_iput:&t;&t;no&t;&t;no&t;&t;yes&n; */
multiline_comment|/* d_flags entries */
DECL|macro|DCACHE_AUTOFS_PENDING
mdefine_line|#define DCACHE_AUTOFS_PENDING 0x0001    /* autofs: &quot;under construction&quot; */
DECL|macro|DCACHE_NFSFS_RENAMED
mdefine_line|#define DCACHE_NFSFS_RENAMED  0x0002    /* this dentry has been &quot;silly&n;&t;&t;&t;&t;&t; * renamed&quot; and has to be&n;&t;&t;&t;&t;&t; * deleted on the last dput()&n;&t;&t;&t;&t;&t; */
DECL|macro|DCACHE_DISCONNECTED
mdefine_line|#define&t;DCACHE_DISCONNECTED 0x0004
multiline_comment|/* This dentry is possibly not currently connected to the dcache tree,&n;      * in which case its parent will either be itself, or will have this&n;      * flag as well.  nfsd will not use a dentry with this bit set, but will&n;      * first endeavour to clear the bit either by discovering that it is&n;      * connected, or by performing lookup operations.   Any filesystem which&n;      * supports nfsd_operations MUST have a lookup function which, if it finds&n;      * a directory inode with a DCACHE_DISCONNECTED dentry, will d_move&n;      * that dentry into place and return that dentry rather than the passed one,&n;      * typically using d_splice_alias.&n;      */
DECL|macro|DCACHE_REFERENCED
mdefine_line|#define DCACHE_REFERENCED&t;0x0008  /* Recently used, don&squot;t discard. */
r_extern
id|spinlock_t
id|dcache_lock
suffix:semicolon
r_extern
id|rwlock_t
id|dparent_lock
suffix:semicolon
multiline_comment|/**&n; * d_drop - drop a dentry&n; * @dentry: dentry to drop&n; *&n; * d_drop() unhashes the entry from the parent&n; * dentry hashes, so that it won&squot;t be found through&n; * a VFS lookup any more. Note that this is different&n; * from deleting the dentry - d_delete will try to&n; * mark the dentry negative if possible, giving a&n; * successful _negative_ lookup, while d_drop will&n; * just make the cache lookup fail.&n; *&n; * d_drop() is used mainly for stuff that wants&n; * to invalidate a dentry for some reason (NFS&n; * timeouts or autofs deletes).&n; */
DECL|function|d_drop
r_static
id|__inline__
r_void
id|d_drop
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dentry-&gt;d_hash
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dentry-&gt;d_hash
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
DECL|function|dname_external
r_static
id|__inline__
r_int
id|dname_external
c_func
(paren
r_struct
id|dentry
op_star
id|d
)paren
(brace
r_return
id|d-&gt;d_name.name
op_ne
id|d-&gt;d_iname
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the low-level FS interfaces to the dcache..&n; */
r_extern
r_void
id|d_instantiate
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|d_delete
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* allocate/de-allocate */
r_extern
r_struct
id|dentry
op_star
id|d_alloc
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|d_alloc_anon
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|d_splice_alias
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|shrink_dcache_sb
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|shrink_dcache_parent
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|shrink_dcache_anon
c_func
(paren
r_struct
id|list_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|d_invalidate
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|macro|shrink_dcache
mdefine_line|#define shrink_dcache() prune_dcache(0)
r_struct
id|zone_struct
suffix:semicolon
multiline_comment|/* dcache memory management */
r_extern
r_int
id|shrink_dcache_memory
c_func
(paren
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|prune_dcache
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* icache memory management (defined in linux/fs/inode.c) */
r_extern
r_int
id|shrink_icache_memory
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|prune_icache
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* quota cache memory management (defined in linux/fs/dquot.c) */
r_extern
r_int
id|shrink_dqcache_memory
c_func
(paren
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* only used at mount-time */
r_extern
r_struct
id|dentry
op_star
id|d_alloc_root
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* &lt;clickety&gt;-&lt;click&gt; the ramfs-type tree */
r_extern
r_void
id|d_genocide
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|d_find_alias
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|d_prune_aliases
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* test whether we have any submounts in a subdir tree */
r_extern
r_int
id|have_submounts
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This adds the entry to the hash queues.&n; */
r_extern
r_void
id|d_rehash
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * d_add - add dentry to hash queues&n; * @entry: dentry to add&n; * @inode: The inode to attach to this dentry&n; *&n; * This adds the entry to the hash queues and initializes @inode.&n; * The entry was actually filled in earlier during d_alloc().&n; */
DECL|function|d_add
r_static
id|__inline__
r_void
id|d_add
c_func
(paren
r_struct
id|dentry
op_star
id|entry
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|d_instantiate
c_func
(paren
id|entry
comma
id|inode
)paren
suffix:semicolon
id|d_rehash
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/* used for rename() and baskets */
r_extern
r_void
id|d_move
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* appendix may either be NULL or be used for transname suffixes */
r_extern
r_struct
id|dentry
op_star
id|d_lookup
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
multiline_comment|/* validate &quot;insecure&quot; dentry pointer */
r_extern
r_int
id|d_validate
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|__d_path
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|vfsmount
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Allocation counts.. */
multiline_comment|/**&n; *&t;dget, dget_locked&t;-&t;get a reference to a dentry&n; *&t;@dentry: dentry to get a reference to&n; *&n; *&t;Given a dentry or %NULL pointer increment the reference count&n; *&t;if appropriate and return the dentry. A dentry will not be &n; *&t;destroyed when it has references. dget() should never be&n; *&t;called for dentries with zero reference counter. For these cases&n; *&t;(preferably none, functions in dcache.c are sufficient for normal&n; *&t;needs and they take necessary precautions) you should hold dcache_lock&n; *&t;and call dget_locked() instead of dget().&n; */
DECL|function|dget
r_static
id|__inline__
r_struct
id|dentry
op_star
id|dget
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
id|dentry
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|dentry-&gt;d_count
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dentry-&gt;d_count
)paren
suffix:semicolon
)brace
r_return
id|dentry
suffix:semicolon
)brace
r_extern
r_struct
id|dentry
op_star
id|dget_locked
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;d_unhashed -&t;is dentry hashed&n; *&t;@dentry: entry to check&n; *&n; *&t;Returns true if the dentry passed is not currently hashed.&n; */
DECL|function|d_unhashed
r_static
id|__inline__
r_int
id|d_unhashed
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
id|list_empty
c_func
(paren
op_amp
id|dentry-&gt;d_hash
)paren
suffix:semicolon
)brace
r_extern
r_void
id|dput
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|function|d_mountpoint
r_static
id|__inline__
r_int
id|d_mountpoint
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
id|dentry-&gt;d_mounted
suffix:semicolon
)brace
r_extern
r_struct
id|vfsmount
op_star
id|lookup_mnt
c_func
(paren
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_DCACHE_H */
eof
