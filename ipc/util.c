multiline_comment|/*&n; * linux/ipc/util.c&n; * Copyright (C) 1992 Krishna Balasubramanian&n; *&n; * Sep 1997 - Call suser() last after &quot;normal&quot; permission checks so we&n; *            get BSD style process accounting right.&n; *            Occurs in several places in the IPC code.&n; *            Chris Evans, &lt;chris@ferret.lmh.ox.ac.uk&gt;&n; * Nov 1999 - ipc helper functions, unified SMP locking&n; *&t;      Manfred Spraul &lt;manfreds@colorfullife.com&gt;&n; * Oct 2002 - One lock per IPC id. RCU ipc_free for lock-free grow_ary().&n; *            Mingming Cao &lt;cmm@us.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#if defined(CONFIG_SYSVIPC)
macro_line|#include &quot;util.h&quot;
multiline_comment|/**&n; *&t;ipc_init&t;-&t;initialise IPC subsystem&n; *&n; *&t;The various system5 IPC resources (semaphores, messages and shared&n; *&t;memory are initialised&n; */
DECL|function|ipc_init
r_static
r_int
id|__init
id|ipc_init
c_func
(paren
r_void
)paren
(brace
id|sem_init
c_func
(paren
)paren
suffix:semicolon
id|msg_init
c_func
(paren
)paren
suffix:semicolon
id|shm_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ipc_init
id|__initcall
c_func
(paren
id|ipc_init
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;ipc_init_ids&t;&t;-&t;initialise IPC identifiers&n; *&t;@ids: Identifier set&n; *&t;@size: Number of identifiers&n; *&n; *&t;Given a size for the ipc identifier range (limited below IPCMNI)&n; *&t;set up the sequence range to use then allocate and initialise the&n; *&t;array itself. &n; */
DECL|function|ipc_init_ids
r_void
id|__init
id|ipc_init_ids
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|size
)paren
(brace
r_int
id|i
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|ids-&gt;sem
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|IPCMNI
)paren
(brace
id|size
op_assign
id|IPCMNI
suffix:semicolon
)brace
id|ids-&gt;size
op_assign
id|size
suffix:semicolon
id|ids-&gt;in_use
op_assign
l_int|0
suffix:semicolon
id|ids-&gt;max_id
op_assign
op_minus
l_int|1
suffix:semicolon
id|ids-&gt;seq
op_assign
l_int|0
suffix:semicolon
(brace
r_int
id|seq_limit
op_assign
id|INT_MAX
op_div
id|SEQ_MULTIPLIER
suffix:semicolon
r_if
c_cond
(paren
id|seq_limit
OG
id|USHRT_MAX
)paren
(brace
id|ids-&gt;seq_max
op_assign
id|USHRT_MAX
suffix:semicolon
)brace
r_else
id|ids-&gt;seq_max
op_assign
id|seq_limit
suffix:semicolon
)brace
id|ids-&gt;entries
op_assign
id|ipc_rcu_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipc_id
)paren
op_star
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ids-&gt;entries
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipc_init_ids() failed, ipc service disabled.&bslash;n&quot;
)paren
suffix:semicolon
id|ids-&gt;size
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ids-&gt;size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ids-&gt;entries
(braket
id|i
)braket
dot
id|p
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;ipc_findkey&t;-&t;find a key in an ipc identifier set&t;&n; *&t;@ids: Identifier set&n; *&t;@key: The key to find&n; *&t;&n; *&t;Requires ipc_ids.sem locked.&n; *&t;Returns the identifier if found or -1 if not.&n; */
DECL|function|ipc_findkey
r_int
id|ipc_findkey
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
id|key_t
id|key
)paren
(brace
r_int
id|id
suffix:semicolon
r_struct
id|kern_ipc_perm
op_star
id|p
suffix:semicolon
r_int
id|max_id
op_assign
id|ids-&gt;max_id
suffix:semicolon
multiline_comment|/*&n;&t; * read_barrier_depends is not needed here&n;&t; * since ipc_ids.sem is held&n;&t; */
r_for
c_loop
(paren
id|id
op_assign
l_int|0
suffix:semicolon
id|id
op_le
id|max_id
suffix:semicolon
id|id
op_increment
)paren
(brace
id|p
op_assign
id|ids-&gt;entries
(braket
id|id
)braket
dot
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|key
op_eq
id|p-&gt;key
)paren
r_return
id|id
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Requires ipc_ids.sem locked&n; */
DECL|function|grow_ary
r_static
r_int
id|grow_ary
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|newsize
)paren
(brace
r_struct
id|ipc_id
op_star
r_new
suffix:semicolon
r_struct
id|ipc_id
op_star
id|old
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|newsize
OG
id|IPCMNI
)paren
(brace
id|newsize
op_assign
id|IPCMNI
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newsize
op_le
id|ids-&gt;size
)paren
(brace
r_return
id|newsize
suffix:semicolon
)brace
r_new
op_assign
id|ipc_rcu_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipc_id
)paren
op_star
id|newsize
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
id|ids-&gt;size
suffix:semicolon
)brace
id|memcpy
c_func
(paren
r_new
comma
id|ids-&gt;entries
comma
r_sizeof
(paren
r_struct
id|ipc_id
)paren
op_star
id|ids-&gt;size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ids-&gt;size
suffix:semicolon
id|i
OL
id|newsize
suffix:semicolon
id|i
op_increment
)paren
(brace
r_new
(braket
id|i
)braket
dot
id|p
op_assign
l_int|NULL
suffix:semicolon
)brace
id|old
op_assign
id|ids-&gt;entries
suffix:semicolon
id|i
op_assign
id|ids-&gt;size
suffix:semicolon
multiline_comment|/*&n;&t; * before setting the ids-&gt;entries to the new array, there must be a&n;&t; * smp_wmb() to make sure the memcpyed contents of the new array are&n;&t; * visible before the new array becomes visible.&n;&t; */
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevent seeing new array uninitialized. */
id|ids-&gt;entries
op_assign
r_new
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevent indexing into old array based on new size. */
id|ids-&gt;size
op_assign
id|newsize
suffix:semicolon
id|ipc_rcu_free
c_func
(paren
id|old
comma
r_sizeof
(paren
r_struct
id|ipc_id
)paren
op_star
id|i
)paren
suffix:semicolon
r_return
id|ids-&gt;size
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc_addid &t;-&t;add an IPC identifier&n; *&t;@ids: IPC identifier set&n; *&t;@new: new IPC permission set&n; *&t;@size: new size limit for the id array&n; *&n; *&t;Add an entry &squot;new&squot; to the IPC arrays. The permissions object is&n; *&t;initialised and the first free entry is set up and the id assigned&n; *&t;is returned. The list is returned in a locked state on success.&n; *&t;On failure the list is not locked and -1 is returned.&n; *&n; *&t;Called with ipc_ids.sem held.&n; */
DECL|function|ipc_addid
r_int
id|ipc_addid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_struct
id|kern_ipc_perm
op_star
r_new
comma
r_int
id|size
)paren
(brace
r_int
id|id
suffix:semicolon
id|size
op_assign
id|grow_ary
c_func
(paren
id|ids
comma
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * read_barrier_depends() is not needed here since&n;&t; * ipc_ids.sem is held&n;&t; */
r_for
c_loop
(paren
id|id
op_assign
l_int|0
suffix:semicolon
id|id
OL
id|size
suffix:semicolon
id|id
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ids-&gt;entries
(braket
id|id
)braket
dot
id|p
op_eq
l_int|NULL
)paren
(brace
r_goto
id|found
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
id|found
suffix:colon
id|ids-&gt;in_use
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|id
OG
id|ids-&gt;max_id
)paren
id|ids-&gt;max_id
op_assign
id|id
suffix:semicolon
r_new
op_member_access_from_pointer
id|cuid
op_assign
r_new
op_member_access_from_pointer
id|uid
op_assign
id|current-&gt;euid
suffix:semicolon
r_new
op_member_access_from_pointer
id|gid
op_assign
r_new
op_member_access_from_pointer
id|cgid
op_assign
id|current-&gt;egid
suffix:semicolon
r_new
op_member_access_from_pointer
id|seq
op_assign
id|ids-&gt;seq
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ids-&gt;seq
OG
id|ids-&gt;seq_max
)paren
(brace
id|ids-&gt;seq
op_assign
l_int|0
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_new
op_member_access_from_pointer
id|deleted
op_assign
l_int|0
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|ids-&gt;entries
(braket
id|id
)braket
dot
id|p
op_assign
r_new
suffix:semicolon
r_return
id|id
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc_rmid&t;-&t;remove an IPC identifier&n; *&t;@ids: identifier set&n; *&t;@id: Identifier to remove&n; *&n; *&t;The identifier must be valid, and in use. The kernel will panic if&n; *&t;fed an invalid identifier. The entry is removed and internal&n; *&t;variables recomputed. The object associated with the identifier&n; *&t;is returned.&n; *&t;ipc_ids.sem and the spinlock for this ID is hold before this function&n; *&t;is called, and remain locked on the exit.&n; */
DECL|function|ipc_rmid
r_struct
id|kern_ipc_perm
op_star
id|ipc_rmid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
(brace
r_struct
id|kern_ipc_perm
op_star
id|p
suffix:semicolon
r_int
id|lid
op_assign
id|id
op_mod
id|SEQ_MULTIPLIER
suffix:semicolon
r_if
c_cond
(paren
id|lid
op_ge
id|ids-&gt;size
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * do not need a read_barrier_depends() here to force ordering&n;&t; * on Alpha, since the ipc_ids.sem is held.&n;&t; */
id|p
op_assign
id|ids-&gt;entries
(braket
id|lid
)braket
dot
id|p
suffix:semicolon
id|ids-&gt;entries
(braket
id|lid
)braket
dot
id|p
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|ids-&gt;in_use
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|lid
op_eq
id|ids-&gt;max_id
)paren
(brace
r_do
(brace
id|lid
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|lid
op_eq
op_minus
l_int|1
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|ids-&gt;entries
(braket
id|lid
)braket
dot
id|p
op_eq
l_int|NULL
)paren
suffix:semicolon
id|ids-&gt;max_id
op_assign
id|lid
suffix:semicolon
)brace
id|p-&gt;deleted
op_assign
l_int|1
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc_alloc&t;-&t;allocate ipc space&n; *&t;@size: size desired&n; *&n; *&t;Allocate memory from the appropriate pools and return a pointer to it.&n; *&t;NULL is returned if the allocation fails&n; */
DECL|function|ipc_alloc
r_void
op_star
id|ipc_alloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|out
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|PAGE_SIZE
)paren
(brace
id|out
op_assign
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
r_else
id|out
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc_free        -       free ipc space&n; *&t;@ptr: pointer returned by ipc_alloc&n; *&t;@size: size of block&n; *&n; *&t;Free a block created with ipc_alloc. The caller must know the size&n; *&t;used in the allocation call.&n; */
DECL|function|ipc_free
r_void
id|ipc_free
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
OG
id|PAGE_SIZE
)paren
(brace
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
r_else
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
DECL|struct|ipc_rcu_kmalloc
r_struct
id|ipc_rcu_kmalloc
(brace
DECL|member|rcu
r_struct
id|rcu_head
id|rcu
suffix:semicolon
multiline_comment|/* &quot;void *&quot; makes sure alignment of following data is sane. */
DECL|member|data
r_void
op_star
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipc_rcu_vmalloc
r_struct
id|ipc_rcu_vmalloc
(brace
DECL|member|rcu
r_struct
id|rcu_head
id|rcu
suffix:semicolon
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
multiline_comment|/* &quot;void *&quot; makes sure alignment of following data is sane. */
DECL|member|data
r_void
op_star
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|rcu_use_vmalloc
r_static
r_inline
r_int
id|rcu_use_vmalloc
c_func
(paren
r_int
id|size
)paren
(brace
multiline_comment|/* Too big for a single page? */
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|ipc_rcu_kmalloc
)paren
op_plus
id|size
OG
id|PAGE_SIZE
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc_rcu_alloc&t;-&t;allocate ipc and rcu space &n; *&t;@size: size desired&n; *&n; *&t;Allocate memory for the rcu header structure +  the object.&n; *&t;Returns the pointer to the object.&n; *&t;NULL is returned if the allocation fails. &n; */
DECL|function|ipc_rcu_alloc
r_void
op_star
id|ipc_rcu_alloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|out
suffix:semicolon
multiline_comment|/* &n;&t; * We prepend the allocation with the rcu struct, and&n;&t; * workqueue if necessary (for vmalloc). &n;&t; */
r_if
c_cond
(paren
id|rcu_use_vmalloc
c_func
(paren
id|size
)paren
)paren
(brace
id|out
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipc_rcu_vmalloc
)paren
op_plus
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
id|out
op_add_assign
r_sizeof
(paren
r_struct
id|ipc_rcu_vmalloc
)paren
suffix:semicolon
)brace
r_else
(brace
id|out
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipc_rcu_kmalloc
)paren
op_plus
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
id|out
op_add_assign
r_sizeof
(paren
r_struct
id|ipc_rcu_kmalloc
)paren
suffix:semicolon
)brace
r_return
id|out
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc_schedule_free&t;- free ipc + rcu space&n; * &n; * Since RCU callback function is called in bh,&n; * we need to defer the vfree to schedule_work&n; */
DECL|function|ipc_schedule_free
r_static
r_void
id|ipc_schedule_free
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|ipc_rcu_vmalloc
op_star
id|free
op_assign
id|arg
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|free-&gt;work
comma
id|vfree
comma
id|free
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|free-&gt;work
)paren
suffix:semicolon
)brace
DECL|function|ipc_rcu_free
r_void
id|ipc_rcu_free
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|rcu_use_vmalloc
c_func
(paren
id|size
)paren
)paren
(brace
r_struct
id|ipc_rcu_vmalloc
op_star
id|free
suffix:semicolon
id|free
op_assign
id|ptr
op_minus
r_sizeof
(paren
op_star
id|free
)paren
suffix:semicolon
id|call_rcu
c_func
(paren
op_amp
id|free-&gt;rcu
comma
id|ipc_schedule_free
comma
id|free
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|ipc_rcu_kmalloc
op_star
id|free
suffix:semicolon
id|free
op_assign
id|ptr
op_minus
r_sizeof
(paren
op_star
id|free
)paren
suffix:semicolon
multiline_comment|/* kfree takes a &quot;const void *&quot; so gcc warns.  So we cast. */
id|call_rcu
c_func
(paren
op_amp
id|free-&gt;rcu
comma
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|kfree
comma
id|free
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;ipcperms&t;-&t;check IPC permissions&n; *&t;@ipcp: IPC permission set&n; *&t;@flag: desired permission set.&n; *&n; *&t;Check user, group, other permissions for access&n; *&t;to ipc resources. return 0 if allowed&n; */
DECL|function|ipcperms
r_int
id|ipcperms
(paren
r_struct
id|kern_ipc_perm
op_star
id|ipcp
comma
r_int
id|flag
)paren
(brace
multiline_comment|/* flag will most probably be 0 or S_...UGO from &lt;linux/stat.h&gt; */
r_int
id|requested_mode
comma
id|granted_mode
suffix:semicolon
id|requested_mode
op_assign
(paren
id|flag
op_rshift
l_int|6
)paren
op_or
(paren
id|flag
op_rshift
l_int|3
)paren
op_or
id|flag
suffix:semicolon
id|granted_mode
op_assign
id|ipcp-&gt;mode
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;euid
op_eq
id|ipcp-&gt;cuid
op_logical_or
id|current-&gt;euid
op_eq
id|ipcp-&gt;uid
)paren
id|granted_mode
op_rshift_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in_group_p
c_func
(paren
id|ipcp-&gt;cgid
)paren
op_logical_or
id|in_group_p
c_func
(paren
id|ipcp-&gt;gid
)paren
)paren
id|granted_mode
op_rshift_assign
l_int|3
suffix:semicolon
multiline_comment|/* is there some bit set in requested_mode but not in granted_mode? */
r_if
c_cond
(paren
(paren
id|requested_mode
op_amp
op_complement
id|granted_mode
op_amp
l_int|0007
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_OWNER
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|security_ipc_permission
c_func
(paren
id|ipcp
comma
id|flag
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Functions to convert between the kern_ipc_perm structure and the&n; * old/new ipc_perm structures&n; */
multiline_comment|/**&n; *&t;kernel_to_ipc64_perm&t;-&t;convert kernel ipc permissions to user&n; *&t;@in: kernel permissions&n; *&t;@out: new style IPC permissions&n; *&n; *&t;Turn the kernel object &squot;in&squot; into a set of permissions descriptions&n; *&t;for returning to userspace (out).&n; */
DECL|function|kernel_to_ipc64_perm
r_void
id|kernel_to_ipc64_perm
(paren
r_struct
id|kern_ipc_perm
op_star
id|in
comma
r_struct
id|ipc64_perm
op_star
id|out
)paren
(brace
id|out-&gt;key
op_assign
id|in-&gt;key
suffix:semicolon
id|out-&gt;uid
op_assign
id|in-&gt;uid
suffix:semicolon
id|out-&gt;gid
op_assign
id|in-&gt;gid
suffix:semicolon
id|out-&gt;cuid
op_assign
id|in-&gt;cuid
suffix:semicolon
id|out-&gt;cgid
op_assign
id|in-&gt;cgid
suffix:semicolon
id|out-&gt;mode
op_assign
id|in-&gt;mode
suffix:semicolon
id|out-&gt;seq
op_assign
id|in-&gt;seq
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ipc64_perm_to_ipc_perm&t;-&t;convert old ipc permissions to new&n; *&t;@in: new style IPC permissions&n; *&t;@out: old style IPC permissions&n; *&n; *&t;Turn the new style permissions object in into a compatibility&n; *&t;object and store it into the &squot;out&squot; pointer.&n; */
DECL|function|ipc64_perm_to_ipc_perm
r_void
id|ipc64_perm_to_ipc_perm
(paren
r_struct
id|ipc64_perm
op_star
id|in
comma
r_struct
id|ipc_perm
op_star
id|out
)paren
(brace
id|out-&gt;key
op_assign
id|in-&gt;key
suffix:semicolon
id|out-&gt;uid
op_assign
id|NEW_TO_OLD_UID
c_func
(paren
id|in-&gt;uid
)paren
suffix:semicolon
id|out-&gt;gid
op_assign
id|NEW_TO_OLD_GID
c_func
(paren
id|in-&gt;gid
)paren
suffix:semicolon
id|out-&gt;cuid
op_assign
id|NEW_TO_OLD_UID
c_func
(paren
id|in-&gt;cuid
)paren
suffix:semicolon
id|out-&gt;cgid
op_assign
id|NEW_TO_OLD_GID
c_func
(paren
id|in-&gt;cgid
)paren
suffix:semicolon
id|out-&gt;mode
op_assign
id|in-&gt;mode
suffix:semicolon
id|out-&gt;seq
op_assign
id|in-&gt;seq
suffix:semicolon
)brace
multiline_comment|/*&n; * So far only shm_get_stat() calls ipc_get() via shm_get(), so ipc_get()&n; * is called with shm_ids.sem locked.  Since grow_ary() is also called with&n; * shm_ids.sem down(for Shared Memory), there is no need to add read &n; * barriers here to gurantee the writes in grow_ary() are seen in order &n; * here (for Alpha).&n; *&n; * However ipc_get() itself does not necessary require ipc_ids.sem down. So&n; * if in the future ipc_get() is used by other places without ipc_ids.sem&n; * down, then ipc_get() needs read memery barriers as ipc_lock() does.&n; */
DECL|function|ipc_get
r_struct
id|kern_ipc_perm
op_star
id|ipc_get
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
(brace
r_struct
id|kern_ipc_perm
op_star
id|out
suffix:semicolon
r_int
id|lid
op_assign
id|id
op_mod
id|SEQ_MULTIPLIER
suffix:semicolon
r_if
c_cond
(paren
id|lid
op_ge
id|ids-&gt;size
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|out
op_assign
id|ids-&gt;entries
(braket
id|lid
)braket
dot
id|p
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|ipc_lock
r_struct
id|kern_ipc_perm
op_star
id|ipc_lock
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
(brace
r_struct
id|kern_ipc_perm
op_star
id|out
suffix:semicolon
r_int
id|lid
op_assign
id|id
op_mod
id|SEQ_MULTIPLIER
suffix:semicolon
r_struct
id|ipc_id
op_star
id|entries
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lid
op_ge
id|ids-&gt;size
)paren
(brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Note: The following two read barriers are corresponding&n;&t; * to the two write barriers in grow_ary(). They guarantee &n;&t; * the writes are seen in the same order on the read side. &n;&t; * smp_rmb() has effect on all CPUs.  read_barrier_depends() &n;&t; * is used if there are data dependency between two reads, and &n;&t; * has effect only on Alpha.&n;&t; */
id|smp_rmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* prevent indexing old array with new size */
id|entries
op_assign
id|ids-&gt;entries
suffix:semicolon
id|read_barrier_depends
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*prevent seeing new array unitialized */
id|out
op_assign
id|entries
(braket
id|lid
)braket
dot
id|p
suffix:semicolon
r_if
c_cond
(paren
id|out
op_eq
l_int|NULL
)paren
(brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|out-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* ipc_rmid() may have already freed the ID while ipc_lock&n;&t; * was spinning: here verify that the structure is still valid&n;&t; */
r_if
c_cond
(paren
id|out-&gt;deleted
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|out-&gt;lock
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|out
suffix:semicolon
)brace
DECL|function|ipc_unlock
r_void
id|ipc_unlock
c_func
(paren
r_struct
id|kern_ipc_perm
op_star
id|perm
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|perm-&gt;lock
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ipc_buildid
r_int
id|ipc_buildid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
comma
r_int
id|seq
)paren
(brace
r_return
id|SEQ_MULTIPLIER
op_star
id|seq
op_plus
id|id
suffix:semicolon
)brace
DECL|function|ipc_checkid
r_int
id|ipc_checkid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_struct
id|kern_ipc_perm
op_star
id|ipcp
comma
r_int
id|uid
)paren
(brace
r_if
c_cond
(paren
id|uid
op_div
id|SEQ_MULTIPLIER
op_ne
id|ipcp-&gt;seq
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if !defined(__ia64__) &amp;&amp; !defined(__x86_64__)
multiline_comment|/**&n; *&t;ipc_parse_version&t;-&t;IPC call version&n; *&t;@cmd: pointer to command&n; *&n; *&t;Return IPC_64 for new style IPC and IPC_OLD for old style IPC. &n; *&t;The cmd value is turned from an encoding command and version into&n; *&t;just the command code.&n; */
DECL|function|ipc_parse_version
r_int
id|ipc_parse_version
(paren
r_int
op_star
id|cmd
)paren
(brace
r_if
c_cond
(paren
op_star
id|cmd
op_amp
id|IPC_64
)paren
(brace
op_star
id|cmd
op_xor_assign
id|IPC_64
suffix:semicolon
r_return
id|IPC_64
suffix:semicolon
)brace
r_else
(brace
r_return
id|IPC_OLD
suffix:semicolon
)brace
)brace
macro_line|#endif /* __ia64__ */
macro_line|#else
multiline_comment|/*&n; * Dummy functions when SYSV IPC isn&squot;t configured&n; */
DECL|function|copy_semundo
r_int
id|copy_semundo
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_sem
r_void
id|exit_sem
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|sys_semget
id|asmlinkage
r_int
id|sys_semget
(paren
id|key_t
id|key
comma
r_int
id|nsems
comma
r_int
id|semflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_semop
id|asmlinkage
r_int
id|sys_semop
(paren
r_int
id|semid
comma
r_struct
id|sembuf
op_star
id|sops
comma
r_int
id|nsops
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_semtimedop
id|asmlinkage
r_int
id|sys_semtimedop
c_func
(paren
r_int
id|semid
comma
r_struct
id|sembuf
op_star
id|sops
comma
r_int
id|nsops
comma
r_const
r_struct
id|timespec
op_star
id|timeout
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_semctl
id|asmlinkage
r_int
id|sys_semctl
(paren
r_int
id|semid
comma
r_int
id|semnum
comma
r_int
id|cmd
comma
r_union
id|semun
id|arg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgget
id|asmlinkage
r_int
id|sys_msgget
(paren
id|key_t
id|key
comma
r_int
id|msgflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgsnd
id|asmlinkage
r_int
id|sys_msgsnd
(paren
r_int
id|msqid
comma
r_struct
id|msgbuf
op_star
id|msgp
comma
r_int
id|msgsz
comma
r_int
id|msgflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgrcv
id|asmlinkage
r_int
id|sys_msgrcv
(paren
r_int
id|msqid
comma
r_struct
id|msgbuf
op_star
id|msgp
comma
r_int
id|msgsz
comma
r_int
id|msgtyp
comma
r_int
id|msgflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgctl
id|asmlinkage
r_int
id|sys_msgctl
(paren
r_int
id|msqid
comma
r_int
id|cmd
comma
r_struct
id|msqid_ds
op_star
id|buf
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmget
id|asmlinkage
r_int
id|sys_shmget
(paren
id|key_t
id|key
comma
r_int
id|size
comma
r_int
id|shmflag
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmat
id|asmlinkage
r_int
id|sys_shmat
(paren
r_int
id|shmid
comma
r_char
op_star
id|shmaddr
comma
r_int
id|shmflg
comma
id|ulong
op_star
id|addr
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmdt
id|asmlinkage
r_int
id|sys_shmdt
(paren
r_char
op_star
id|shmaddr
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmctl
id|asmlinkage
r_int
id|sys_shmctl
(paren
r_int
id|shmid
comma
r_int
id|cmd
comma
r_struct
id|shmid_ds
op_star
id|buf
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SYSVIPC */
eof
