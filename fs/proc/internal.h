multiline_comment|/* internal.h: internal procfs definitions&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|struct|vmalloc_info
r_struct
id|vmalloc_info
(brace
DECL|member|used
r_int
r_int
id|used
suffix:semicolon
DECL|member|largest_chunk
r_int
r_int
id|largest_chunk
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
DECL|macro|VMALLOC_TOTAL
mdefine_line|#define VMALLOC_TOTAL (VMALLOC_END - VMALLOC_START)
r_extern
r_void
id|get_vmalloc_info
c_func
(paren
r_struct
id|vmalloc_info
op_star
id|vmi
)paren
suffix:semicolon
macro_line|#else
DECL|macro|VMALLOC_TOTAL
mdefine_line|#define VMALLOC_TOTAL 0UL
DECL|macro|get_vmalloc_info
mdefine_line|#define get_vmalloc_info(vmi)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(vmi)-&gt;used = 0;&t;&t;&t;&bslash;&n;&t;(vmi)-&gt;largest_chunk = 0;&t;&t;&bslash;&n;} while(0)
macro_line|#endif
r_extern
r_void
id|create_seq_entry
c_func
(paren
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|file_operations
op_star
id|f
)paren
suffix:semicolon
r_extern
r_int
id|proc_exe_link
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
op_star
comma
r_struct
id|vfsmount
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_tid_stat
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_tgid_stat
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_pid_status
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_pid_statm
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|function|proc_task
r_static
r_inline
r_struct
id|task_struct
op_star
id|proc_task
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|PROC_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|task
suffix:semicolon
)brace
DECL|function|proc_type
r_static
r_inline
r_int
id|proc_type
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|PROC_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|type
suffix:semicolon
)brace
eof
