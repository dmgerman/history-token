macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|task_mem
r_char
op_star
id|task_mem
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
r_int
id|data
comma
id|text
comma
id|lib
suffix:semicolon
id|data
op_assign
id|mm-&gt;total_vm
op_minus
id|mm-&gt;shared_vm
op_minus
id|mm-&gt;stack_vm
suffix:semicolon
id|text
op_assign
(paren
id|mm-&gt;end_code
op_minus
id|mm-&gt;start_code
)paren
op_rshift
l_int|10
suffix:semicolon
id|lib
op_assign
(paren
id|mm-&gt;exec_vm
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
op_minus
id|text
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;VmSize:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmLck:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmRSS:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmData:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmStk:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmExe:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmLib:&bslash;t%8lu kB&bslash;n&quot;
comma
(paren
id|mm-&gt;total_vm
op_minus
id|mm-&gt;reserved_vm
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|mm-&gt;locked_vm
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|mm-&gt;rss
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|data
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|mm-&gt;stack_vm
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|text
comma
id|lib
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|task_vsize
r_int
r_int
id|task_vsize
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_return
id|PAGE_SIZE
op_star
id|mm-&gt;total_vm
suffix:semicolon
)brace
DECL|function|task_statm
r_int
id|task_statm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
op_star
id|shared
comma
r_int
op_star
id|text
comma
r_int
op_star
id|data
comma
r_int
op_star
id|resident
)paren
(brace
op_star
id|shared
op_assign
id|mm-&gt;shared_vm
suffix:semicolon
op_star
id|text
op_assign
(paren
id|mm-&gt;end_code
op_minus
id|mm-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
op_star
id|data
op_assign
id|mm-&gt;total_vm
op_minus
id|mm-&gt;shared_vm
op_minus
op_star
id|text
suffix:semicolon
op_star
id|resident
op_assign
id|mm-&gt;rss
suffix:semicolon
r_return
id|mm-&gt;total_vm
suffix:semicolon
)brace
DECL|function|show_map
r_static
r_int
id|show_map
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|map
op_assign
id|v
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|map-&gt;vm_file
suffix:semicolon
r_int
id|flags
op_assign
id|map-&gt;vm_flags
suffix:semicolon
r_int
r_int
id|ino
op_assign
l_int|0
suffix:semicolon
id|dev_t
id|dev
op_assign
l_int|0
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|map-&gt;vm_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_sb-&gt;s_dev
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%08lx-%08lx %c%c%c%c %08lx %02x:%02x %lu %n&quot;
comma
id|map-&gt;vm_start
comma
id|map-&gt;vm_end
comma
id|flags
op_amp
id|VM_READ
ques
c_cond
l_char|&squot;r&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|flags
op_amp
id|VM_WRITE
ques
c_cond
l_char|&squot;w&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|flags
op_amp
id|VM_EXEC
ques
c_cond
l_char|&squot;x&squot;
suffix:colon
l_char|&squot;-&squot;
comma
id|flags
op_amp
id|VM_MAYSHARE
ques
c_cond
l_char|&squot;s&squot;
suffix:colon
l_char|&squot;p&squot;
comma
id|map-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
comma
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
comma
id|ino
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;vm_file
)paren
(brace
id|len
op_assign
l_int|25
op_plus
r_sizeof
(paren
r_void
op_star
)paren
op_star
l_int|6
op_minus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|1
)paren
id|len
op_assign
l_int|1
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%*c&quot;
comma
id|len
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|seq_path
c_func
(paren
id|m
comma
id|file-&gt;f_vfsmnt
comma
id|file-&gt;f_dentry
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|m
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|m_start
r_static
r_void
op_star
id|m_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|task
)paren
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|map
suffix:semicolon
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_return
l_int|NULL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|map
op_assign
id|mm-&gt;mmap
suffix:semicolon
r_while
c_loop
(paren
id|l
op_decrement
op_logical_and
id|map
)paren
id|map
op_assign
id|map-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
op_minus
l_int|1
)paren
id|map
op_assign
id|get_gate_vma
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
r_return
id|map
suffix:semicolon
)brace
DECL|function|m_stop
r_static
r_void
id|m_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|map
op_assign
id|v
suffix:semicolon
r_if
c_cond
(paren
id|map
op_logical_and
id|map
op_ne
id|get_gate_vma
c_func
(paren
id|task
)paren
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|map-&gt;vm_mm
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
DECL|function|m_next
r_static
r_void
op_star
id|m_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|map
op_assign
id|v
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;vm_next
)paren
r_return
id|map-&gt;vm_next
suffix:semicolon
id|m_stop
c_func
(paren
id|m
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_ne
id|get_gate_vma
c_func
(paren
id|task
)paren
)paren
r_return
id|get_gate_vma
c_func
(paren
id|task
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|proc_pid_maps_op
r_struct
id|seq_operations
id|proc_pid_maps_op
op_assign
(brace
dot
id|start
op_assign
id|m_start
comma
dot
id|next
op_assign
id|m_next
comma
dot
id|stop
op_assign
id|m_stop
comma
dot
id|show
op_assign
id|show_map
)brace
suffix:semicolon
eof
