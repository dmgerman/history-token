macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
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
op_assign
l_int|0
comma
id|stack
op_assign
l_int|0
comma
id|exec
op_assign
l_int|0
comma
id|lib
op_assign
l_int|0
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_int
r_int
id|len
op_assign
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
)paren
(brace
id|data
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
)paren
id|stack
op_add_assign
id|len
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
(brace
id|exec
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXECUTABLE
)paren
r_continue
suffix:semicolon
id|lib
op_add_assign
id|len
suffix:semicolon
)brace
)brace
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
id|mm-&gt;total_vm
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
op_minus
id|stack
comma
id|stack
comma
id|exec
op_minus
id|lib
comma
id|lib
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
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
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
op_star
id|resident
op_assign
id|mm-&gt;rss
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_int
id|pages
op_assign
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|size
op_add_assign
id|pages
suffix:semicolon
r_if
c_cond
(paren
id|is_vm_hugetlb_page
c_func
(paren
id|vma
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_DONTCOPY
)paren
)paren
op_star
id|shared
op_add_assign
id|pages
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|vma-&gt;shared
)paren
)paren
op_star
id|shared
op_add_assign
id|pages
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXECUTABLE
)paren
op_star
id|text
op_add_assign
id|pages
suffix:semicolon
r_else
op_star
id|data
op_add_assign
id|pages
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/*&n; * The way we support synthetic files &gt; 4K&n; * - without storing their contents in some buffer and&n; * - without walking through the entire synthetic file until we reach the&n; *   position of the requested data&n; * is to cleverly encode the current position in the file&squot;s f_pos field.&n; * There is no requirement that a read() call which returns `count&squot; bytes&n; * of data increases f_pos by exactly `count&squot;.&n; *&n; * This idea is Linus&squot; one. Bruno implemented it.&n; */
multiline_comment|/*&n; * For the /proc/&lt;pid&gt;/maps file, we use fixed length records, each containing&n; * a single line.&n; *&n; * f_pos = (number of the vma in the task-&gt;mm-&gt;mmap list) * PAGE_SIZE&n; *         + (index into the line)&n; */
multiline_comment|/* for systems with sizeof(void*) == 4: */
DECL|macro|MAPS_LINE_FORMAT4
mdefine_line|#define MAPS_LINE_FORMAT4&t;  &quot;%08lx-%08lx %s %08lx %02x:%02x %lu&quot;
DECL|macro|MAPS_LINE_MAX4
mdefine_line|#define MAPS_LINE_MAX4&t;49 /* sum of 8  1  8  1 4 1 8 1 5 1 10 1 */
multiline_comment|/* for systems with sizeof(void*) == 8: */
DECL|macro|MAPS_LINE_FORMAT8
mdefine_line|#define MAPS_LINE_FORMAT8&t;  &quot;%016lx-%016lx %s %016lx %02x:%02x %lu&quot;
DECL|macro|MAPS_LINE_MAX8
mdefine_line|#define MAPS_LINE_MAX8&t;73 /* sum of 16  1  16  1 4 1 16 1 5 1 10 1 */
DECL|macro|MAPS_LINE_FORMAT
mdefine_line|#define MAPS_LINE_FORMAT&t;(sizeof(void*) == 4 ? MAPS_LINE_FORMAT4 : MAPS_LINE_FORMAT8)
DECL|macro|MAPS_LINE_MAX
mdefine_line|#define MAPS_LINE_MAX&t;(sizeof(void*) == 4 ?  MAPS_LINE_MAX4 :  MAPS_LINE_MAX8)
DECL|function|proc_pid_maps_get_line
r_static
r_int
id|proc_pid_maps_get_line
(paren
r_char
op_star
id|buf
comma
r_struct
id|vm_area_struct
op_star
id|map
)paren
(brace
multiline_comment|/* produce the next line */
r_char
op_star
id|line
suffix:semicolon
r_char
id|str
(braket
l_int|5
)braket
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|dev_t
id|dev
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_int
id|len
suffix:semicolon
id|flags
op_assign
id|map-&gt;vm_flags
suffix:semicolon
id|str
(braket
l_int|0
)braket
op_assign
id|flags
op_amp
id|VM_READ
ques
c_cond
l_char|&squot;r&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|str
(braket
l_int|1
)braket
op_assign
id|flags
op_amp
id|VM_WRITE
ques
c_cond
l_char|&squot;w&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|str
(braket
l_int|2
)braket
op_assign
id|flags
op_amp
id|VM_EXEC
ques
c_cond
l_char|&squot;x&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|str
(braket
l_int|3
)braket
op_assign
id|flags
op_amp
id|VM_MAYSHARE
ques
c_cond
l_char|&squot;s&squot;
suffix:colon
l_char|&squot;p&squot;
suffix:semicolon
id|str
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;vm_file
op_ne
l_int|NULL
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
id|line
op_assign
id|d_path
c_func
(paren
id|map-&gt;vm_file-&gt;f_dentry
comma
id|map-&gt;vm_file-&gt;f_vfsmnt
comma
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|buf
(braket
id|PAGE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
op_sub_assign
id|MAPS_LINE_MAX
suffix:semicolon
r_if
c_cond
(paren
id|line
OL
id|buf
)paren
(brace
id|line
op_assign
id|buf
suffix:semicolon
)brace
)brace
r_else
id|line
op_assign
id|buf
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|line
comma
id|MAPS_LINE_FORMAT
comma
id|map-&gt;vm_start
comma
id|map-&gt;vm_end
comma
id|str
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;vm_file
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
id|len
suffix:semicolon
id|i
OL
id|MAPS_LINE_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|line
(braket
id|i
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
id|len
op_assign
id|buf
op_plus
id|PAGE_SIZE
op_minus
id|line
suffix:semicolon
id|memmove
c_func
(paren
id|buf
comma
id|line
comma
id|len
)paren
suffix:semicolon
)brace
r_else
id|line
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_pid_read_maps
id|ssize_t
id|proc_pid_read_maps
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|map
suffix:semicolon
r_char
op_star
id|tmp
comma
op_star
id|kbuf
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|off
comma
id|lineno
comma
id|loff
suffix:semicolon
multiline_comment|/* reject calls with out of range parameters immediately */
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
OG
id|LONG_MAX
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|off
op_assign
(paren
r_int
)paren
op_star
id|ppos
suffix:semicolon
multiline_comment|/*&n;&t; * We might sleep getting the page, so get it first.&n;&t; */
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|kbuf
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuf
)paren
r_goto
id|out
suffix:semicolon
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_goto
id|out_free1
suffix:semicolon
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|task
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_goto
id|out_free2
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
id|lineno
op_assign
l_int|0
suffix:semicolon
id|loff
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|map
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|off
OG
id|PAGE_SIZE
)paren
(brace
id|off
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
id|len
op_assign
id|proc_pid_maps_get_line
c_func
(paren
id|tmp
comma
id|map
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_plus
id|len
OG
id|count
)paren
(brace
multiline_comment|/* only partial line transfer possible */
id|len
op_assign
id|count
op_minus
id|retval
suffix:semicolon
multiline_comment|/* save the offset where the next read&n;&t;&t;&t;&t; * must start */
id|loff
op_assign
id|len
op_plus
id|off
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|kbuf
op_plus
id|retval
comma
id|tmp
op_plus
id|off
comma
id|len
)paren
suffix:semicolon
id|retval
op_add_assign
id|len
suffix:semicolon
)brace
id|off
op_assign
l_int|0
suffix:semicolon
id|next
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|loff
)paren
id|lineno
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
id|count
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|loff
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|map
op_assign
id|map-&gt;vm_next
suffix:semicolon
)brace
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
id|retval
OG
id|count
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|kbuf
comma
id|retval
)paren
)paren
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
op_star
id|ppos
op_assign
(paren
id|lineno
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|loff
suffix:semicolon
id|out_free2
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|tmp
)paren
suffix:semicolon
id|out_free1
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|kbuf
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
eof
