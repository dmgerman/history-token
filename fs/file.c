multiline_comment|/*&n; *  linux/fs/file.c&n; *&n; *  Copyright (C) 1998-1999, Stephen Tweedie and Bill Hawes&n; *&n; *  Manage the dynamic fd arrays in the process files_struct.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
multiline_comment|/*&n; * Allocate an fd array, using kmalloc or vmalloc.&n; * Note: the array isn&squot;t cleared at allocation time.&n; */
DECL|function|alloc_fd_array
r_struct
id|file
op_star
op_star
id|alloc_fd_array
c_func
(paren
r_int
id|num
)paren
(brace
r_struct
id|file
op_star
op_star
id|new_fds
suffix:semicolon
r_int
id|size
op_assign
id|num
op_star
r_sizeof
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|PAGE_SIZE
)paren
id|new_fds
op_assign
(paren
r_struct
id|file
op_star
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_else
id|new_fds
op_assign
(paren
r_struct
id|file
op_star
op_star
)paren
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_return
id|new_fds
suffix:semicolon
)brace
DECL|function|free_fd_array
r_void
id|free_fd_array
c_func
(paren
r_struct
id|file
op_star
op_star
id|array
comma
r_int
id|num
)paren
(brace
r_int
id|size
op_assign
id|num
op_star
r_sizeof
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|array
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;free_fd_array: array = 0 (num = %d)&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num
op_le
id|NR_OPEN_DEFAULT
)paren
multiline_comment|/* Don&squot;t free the embedded fd array! */
r_return
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
op_le
id|PAGE_SIZE
)paren
id|kfree
c_func
(paren
id|array
)paren
suffix:semicolon
r_else
id|vfree
c_func
(paren
id|array
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Expand the fd array in the files_struct.  Called with the files&n; * spinlock held for write.&n; */
DECL|function|expand_fd_array
r_int
id|expand_fd_array
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_int
id|nr
)paren
(brace
r_struct
id|file
op_star
op_star
id|new_fds
suffix:semicolon
r_int
id|error
comma
id|nfds
suffix:semicolon
id|error
op_assign
op_minus
id|EMFILE
suffix:semicolon
r_if
c_cond
(paren
id|files-&gt;max_fds
op_ge
id|NR_OPEN
op_logical_or
id|nr
op_ge
id|NR_OPEN
)paren
r_goto
id|out
suffix:semicolon
id|nfds
op_assign
id|files-&gt;max_fds
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Expand to the max in easy steps, and keep expanding it until&n;&t; * we have enough for the requested fd array size. &n;&t; */
r_do
(brace
macro_line|#if NR_OPEN_DEFAULT &lt; 256
r_if
c_cond
(paren
id|nfds
OL
l_int|256
)paren
id|nfds
op_assign
l_int|256
suffix:semicolon
r_else
macro_line|#endif
r_if
c_cond
(paren
id|nfds
OL
(paren
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|file
op_star
)paren
)paren
)paren
id|nfds
op_assign
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_else
(brace
id|nfds
op_assign
id|nfds
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|nfds
OG
id|NR_OPEN
)paren
id|nfds
op_assign
id|NR_OPEN
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|nfds
op_le
id|nr
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|new_fds
op_assign
id|alloc_fd_array
c_func
(paren
id|nfds
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_fds
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Copy the existing array and install the new pointer */
r_if
c_cond
(paren
id|nfds
OG
id|files-&gt;max_fds
)paren
(brace
r_struct
id|file
op_star
op_star
id|old_fds
suffix:semicolon
r_int
id|i
suffix:semicolon
id|old_fds
op_assign
id|xchg
c_func
(paren
op_amp
id|files-&gt;fd
comma
id|new_fds
)paren
suffix:semicolon
id|i
op_assign
id|xchg
c_func
(paren
op_amp
id|files-&gt;max_fds
comma
id|nfds
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t copy/clear the array if we are creating a new&n;&t;&t;   fd array for fork() */
r_if
c_cond
(paren
id|i
)paren
(brace
id|memcpy
c_func
(paren
id|new_fds
comma
id|old_fds
comma
id|i
op_star
r_sizeof
(paren
r_struct
id|file
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* clear the remainder of the array */
id|memset
c_func
(paren
op_amp
id|new_fds
(braket
id|i
)braket
comma
l_int|0
comma
(paren
id|nfds
op_minus
id|i
)paren
op_star
r_sizeof
(paren
r_struct
id|file
op_star
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|free_fd_array
c_func
(paren
id|old_fds
comma
id|i
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Somebody expanded the array while we slept ... */
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|free_fd_array
c_func
(paren
id|new_fds
comma
id|nfds
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate an fdset array, using kmalloc or vmalloc.&n; * Note: the array isn&squot;t cleared at allocation time.&n; */
DECL|function|alloc_fdset
id|fd_set
op_star
id|alloc_fdset
c_func
(paren
r_int
id|num
)paren
(brace
id|fd_set
op_star
id|new_fdset
suffix:semicolon
r_int
id|size
op_assign
id|num
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|PAGE_SIZE
)paren
id|new_fdset
op_assign
(paren
id|fd_set
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_else
id|new_fdset
op_assign
(paren
id|fd_set
op_star
)paren
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_return
id|new_fdset
suffix:semicolon
)brace
DECL|function|free_fdset
r_void
id|free_fdset
c_func
(paren
id|fd_set
op_star
id|array
comma
r_int
id|num
)paren
(brace
r_int
id|size
op_assign
id|num
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|num
op_le
id|__FD_SETSIZE
)paren
multiline_comment|/* Don&squot;t free an embedded fdset */
r_return
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
op_le
id|PAGE_SIZE
)paren
id|kfree
c_func
(paren
id|array
)paren
suffix:semicolon
r_else
id|vfree
c_func
(paren
id|array
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Expand the fdset in the files_struct.  Called with the files spinlock&n; * held for write.&n; */
DECL|function|expand_fdset
r_int
id|expand_fdset
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_int
id|nr
)paren
(brace
id|fd_set
op_star
id|new_openset
op_assign
l_int|NULL
comma
op_star
id|new_execset
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
comma
id|nfds
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
op_minus
id|EMFILE
suffix:semicolon
r_if
c_cond
(paren
id|files-&gt;max_fdset
op_ge
id|NR_OPEN
op_logical_or
id|nr
op_ge
id|NR_OPEN
)paren
r_goto
id|out
suffix:semicolon
id|nfds
op_assign
id|files-&gt;max_fdset
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
multiline_comment|/* Expand to the max in easy steps */
r_do
(brace
r_if
c_cond
(paren
id|nfds
OL
(paren
id|PAGE_SIZE
op_star
l_int|8
)paren
)paren
id|nfds
op_assign
id|PAGE_SIZE
op_star
l_int|8
suffix:semicolon
r_else
(brace
id|nfds
op_assign
id|nfds
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|nfds
OG
id|NR_OPEN
)paren
id|nfds
op_assign
id|NR_OPEN
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|nfds
op_le
id|nr
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|new_openset
op_assign
id|alloc_fdset
c_func
(paren
id|nfds
)paren
suffix:semicolon
id|new_execset
op_assign
id|alloc_fdset
c_func
(paren
id|nfds
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_openset
op_logical_or
op_logical_neg
id|new_execset
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Copy the existing tables and install the new pointers */
r_if
c_cond
(paren
id|nfds
OG
id|files-&gt;max_fdset
)paren
(brace
r_int
id|i
op_assign
id|files-&gt;max_fdset
op_div
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_int
id|count
op_assign
(paren
id|nfds
op_minus
id|files-&gt;max_fdset
)paren
op_div
l_int|8
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Don&squot;t copy the entire array if the current fdset is&n;&t;&t; * not yet initialised.  &n;&t;&t; */
r_if
c_cond
(paren
id|i
)paren
(brace
id|memcpy
(paren
id|new_openset
comma
id|files-&gt;open_fds
comma
id|files-&gt;max_fdset
op_div
l_int|8
)paren
suffix:semicolon
id|memcpy
(paren
id|new_execset
comma
id|files-&gt;close_on_exec
comma
id|files-&gt;max_fdset
op_div
l_int|8
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|new_openset-&gt;fds_bits
(braket
id|i
)braket
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|new_execset-&gt;fds_bits
(braket
id|i
)braket
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
id|nfds
op_assign
id|xchg
c_func
(paren
op_amp
id|files-&gt;max_fdset
comma
id|nfds
)paren
suffix:semicolon
id|new_openset
op_assign
id|xchg
c_func
(paren
op_amp
id|files-&gt;open_fds
comma
id|new_openset
)paren
suffix:semicolon
id|new_execset
op_assign
id|xchg
c_func
(paren
op_amp
id|files-&gt;close_on_exec
comma
id|new_execset
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
id|free_fdset
(paren
id|new_openset
comma
id|nfds
)paren
suffix:semicolon
id|free_fdset
(paren
id|new_execset
comma
id|nfds
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Somebody expanded the array while we slept ... */
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_openset
)paren
id|free_fdset
c_func
(paren
id|new_openset
comma
id|nfds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_execset
)paren
id|free_fdset
c_func
(paren
id|new_execset
comma
id|nfds
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|files-&gt;file_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
