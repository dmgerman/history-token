macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* What kind of fucking hack is this? */
DECL|macro|MTRR_NEED_STRINGS
mdefine_line|#define MTRR_NEED_STRINGS
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &quot;mtrr.h&quot;
DECL|variable|ascii_buffer
r_static
r_char
op_star
id|ascii_buffer
suffix:semicolon
DECL|variable|ascii_buf_bytes
r_static
r_int
r_int
id|ascii_buf_bytes
suffix:semicolon
r_extern
r_int
r_int
op_star
id|usage_table
suffix:semicolon
DECL|macro|LINE_SIZE
mdefine_line|#define LINE_SIZE      80
r_static
r_int
DECL|function|mtrr_file_add
id|mtrr_file_add
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|page
)paren
(brace
r_int
id|reg
comma
id|max
suffix:semicolon
r_int
r_int
op_star
id|fcount
op_assign
id|file-&gt;private_data
suffix:semicolon
id|max
op_assign
id|num_var_ranges
suffix:semicolon
r_if
c_cond
(paren
id|fcount
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|fcount
op_assign
id|kmalloc
c_func
(paren
id|max
op_star
r_sizeof
op_star
id|fcount
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mtrr: could not allocate&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fcount
comma
l_int|0
comma
id|max
op_star
r_sizeof
op_star
id|fcount
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|fcount
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
r_if
c_cond
(paren
(paren
id|base
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|size
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;mtrr: size and base must be multiples of 4 kiB&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mtrr: size: 0x%lx  base: 0x%lx&bslash;n&quot;
comma
id|size
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|base
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|size
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
)brace
id|reg
op_assign
id|mtrr_add_page
c_func
(paren
id|base
comma
id|size
comma
id|type
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ge
l_int|0
)paren
op_increment
id|fcount
(braket
id|reg
)braket
suffix:semicolon
r_return
id|reg
suffix:semicolon
)brace
r_static
r_int
DECL|function|mtrr_file_del
id|mtrr_file_del
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|page
)paren
(brace
r_int
id|reg
suffix:semicolon
r_int
r_int
op_star
id|fcount
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
r_if
c_cond
(paren
(paren
id|base
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|size
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;mtrr: size and base must be multiples of 4 kiB&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mtrr: size: 0x%lx  base: 0x%lx&bslash;n&quot;
comma
id|size
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|base
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|size
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
)brace
id|reg
op_assign
id|mtrr_del_page
c_func
(paren
op_minus
l_int|1
comma
id|base
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|0
)paren
r_return
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|fcount
op_eq
l_int|NULL
)paren
r_return
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|fcount
(braket
id|reg
)braket
OL
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_decrement
id|fcount
(braket
id|reg
)braket
suffix:semicolon
r_return
id|reg
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|mtrr_read
id|mtrr_read
c_func
(paren
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
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_if
c_cond
(paren
op_star
id|ppos
op_ge
id|ascii_buf_bytes
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
op_plus
id|len
OG
id|ascii_buf_bytes
)paren
id|len
op_assign
id|ascii_buf_bytes
op_minus
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|ascii_buffer
op_plus
op_star
id|ppos
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|mtrr_write
id|mtrr_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
multiline_comment|/*  Format of control line:&n;    &quot;base=%Lx size=%Lx type=%s&quot;     OR:&n;    &quot;disable=%d&quot;&n;*/
(brace
r_int
id|i
comma
id|err
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
r_int
r_int
r_int
id|base
comma
id|size
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_char
id|line
(braket
id|LINE_SIZE
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*  Can&squot;t seek (pwrite) on this device  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
id|memset
c_func
(paren
id|line
comma
l_int|0
comma
id|LINE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|LINE_SIZE
)paren
id|len
op_assign
id|LINE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|line
comma
id|buf
comma
id|len
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ptr
op_assign
id|line
op_plus
id|strlen
c_func
(paren
id|line
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ptr
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_star
id|ptr
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;disable=&quot;
comma
l_int|8
)paren
)paren
(brace
id|reg
op_assign
id|simple_strtoul
c_func
(paren
id|line
op_plus
l_int|8
comma
op_amp
id|ptr
comma
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|mtrr_del_page
c_func
(paren
id|reg
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;base=&quot;
comma
l_int|5
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mtrr: no &bslash;&quot;base=&bslash;&quot; in line: &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|base
op_assign
id|simple_strtoull
c_func
(paren
id|line
op_plus
l_int|5
comma
op_amp
id|ptr
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
op_increment
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ptr
comma
l_string|&quot;size=&quot;
comma
l_int|5
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mtrr: no &bslash;&quot;size=&bslash;&quot; in line: &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|size
op_assign
id|simple_strtoull
c_func
(paren
id|ptr
op_plus
l_int|5
comma
op_amp
id|ptr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|base
op_amp
l_int|0xfff
)paren
op_logical_or
(paren
id|size
op_amp
l_int|0xfff
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mtrr: size and base must be multiples of 4 kiB&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mtrr: size: 0x%Lx  base: 0x%Lx&bslash;n&quot;
comma
id|size
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
op_increment
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ptr
comma
l_string|&quot;type=&quot;
comma
l_int|5
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mtrr: no &bslash;&quot;type=&bslash;&quot; in line: &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ptr
op_add_assign
l_int|5
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
op_increment
id|ptr
)paren
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
id|MTRR_NUM_TYPES
suffix:semicolon
op_increment
id|i
)paren
(brace
singleline_comment|//&t;&t;if (strcmp(ptr, mtrr_strings[i]))
r_continue
suffix:semicolon
id|base
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|size
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|err
op_assign
id|mtrr_add_page
c_func
(paren
(paren
r_int
r_int
)paren
id|base
comma
(paren
r_int
r_int
)paren
id|size
comma
id|i
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;mtrr: illegal type: &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|ptr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|mtrr_ioctl
id|mtrr_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
suffix:semicolon
id|mtrr_type
id|type
suffix:semicolon
r_struct
id|mtrr_sentry
id|sentry
suffix:semicolon
r_struct
id|mtrr_gentry
id|gentry
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_case
id|MTRRIOC_ADD_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_file_add
c_func
(paren
id|sentry.base
comma
id|sentry.size
comma
id|sentry.type
comma
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_SET_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_add
c_func
(paren
id|sentry.base
comma
id|sentry.size
comma
id|sentry.type
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_DEL_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_file_del
c_func
(paren
id|sentry.base
comma
id|sentry.size
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_KILL_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_del
c_func
(paren
op_minus
l_int|1
comma
id|sentry.base
comma
id|sentry.size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_GET_ENTRY
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|gentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|gentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|gentry.regnum
op_ge
id|num_var_ranges
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|gentry.regnum
comma
op_amp
id|gentry.base
comma
op_amp
id|gentry.size
comma
op_amp
id|type
)paren
suffix:semicolon
multiline_comment|/* Hide entries that go above 4GB */
r_if
c_cond
(paren
id|gentry.base
op_plus
id|gentry.size
OG
l_int|0x100000
op_logical_or
id|gentry.size
op_eq
l_int|0x100000
)paren
id|gentry.base
op_assign
id|gentry.size
op_assign
id|gentry.type
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|gentry.base
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|gentry.size
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|gentry.type
op_assign
id|type
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|gentry
comma
r_sizeof
id|gentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_ADD_PAGE_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_file_add
c_func
(paren
id|sentry.base
comma
id|sentry.size
comma
id|sentry.type
comma
l_int|1
comma
id|file
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_SET_PAGE_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_add_page
c_func
(paren
id|sentry.base
comma
id|sentry.size
comma
id|sentry.type
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_DEL_PAGE_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_file_del
c_func
(paren
id|sentry.base
comma
id|sentry.size
comma
id|file
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_KILL_PAGE_ENTRY
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|sentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|mtrr_del_page
c_func
(paren
op_minus
l_int|1
comma
id|sentry.base
comma
id|sentry.size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRRIOC_GET_PAGE_ENTRY
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|gentry
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
id|gentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|gentry.regnum
op_ge
id|num_var_ranges
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|gentry.regnum
comma
op_amp
id|gentry.base
comma
op_amp
id|gentry.size
comma
op_amp
id|type
)paren
suffix:semicolon
id|gentry.type
op_assign
id|type
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|gentry
comma
r_sizeof
id|gentry
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|mtrr_close
id|mtrr_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|i
comma
id|max
suffix:semicolon
r_int
r_int
op_star
id|fcount
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|fcount
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|max
op_assign
id|num_var_ranges
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
id|max
suffix:semicolon
op_increment
id|i
)paren
(brace
r_while
c_loop
(paren
id|fcount
(braket
id|i
)braket
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|mtrr_del
c_func
(paren
id|i
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;mtrr: reg %d not used&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
op_decrement
id|fcount
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|fcount
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mtrr_fops
r_static
r_struct
id|file_operations
id|mtrr_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|mtrr_read
comma
dot
id|write
op_assign
id|mtrr_write
comma
dot
id|ioctl
op_assign
id|mtrr_ioctl
comma
dot
id|release
op_assign
id|mtrr_close
comma
)brace
suffix:semicolon
macro_line|#  ifdef CONFIG_PROC_FS
DECL|variable|proc_root_mtrr
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_root_mtrr
suffix:semicolon
macro_line|#  endif&t;&t;&t;/*  CONFIG_PROC_FS  */
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
DECL|function|attrib_to_str
r_char
op_star
id|attrib_to_str
c_func
(paren
r_int
id|x
)paren
(brace
r_return
(paren
id|x
op_le
l_int|6
)paren
ques
c_cond
id|mtrr_strings
(braket
id|x
)braket
suffix:colon
l_string|&quot;?&quot;
suffix:semicolon
)brace
DECL|function|compute_ascii
r_void
id|compute_ascii
c_func
(paren
r_void
)paren
(brace
r_char
id|factor
suffix:semicolon
r_int
id|i
comma
id|max
suffix:semicolon
id|mtrr_type
id|type
suffix:semicolon
r_int
r_int
id|base
comma
id|size
suffix:semicolon
id|ascii_buf_bytes
op_assign
l_int|0
suffix:semicolon
id|max
op_assign
id|num_var_ranges
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|i
comma
op_amp
id|base
comma
op_amp
id|size
comma
op_amp
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
id|usage_table
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|size
OL
(paren
l_int|0x100000
op_rshift
id|PAGE_SHIFT
)paren
)paren
(brace
multiline_comment|/* less than 1MB */
id|factor
op_assign
l_char|&squot;K&squot;
suffix:semicolon
id|size
op_lshift_assign
id|PAGE_SHIFT
op_minus
l_int|10
suffix:semicolon
)brace
r_else
(brace
id|factor
op_assign
l_char|&squot;M&squot;
suffix:semicolon
id|size
op_rshift_assign
l_int|20
op_minus
id|PAGE_SHIFT
suffix:semicolon
)brace
id|sprintf
(paren
id|ascii_buffer
op_plus
id|ascii_buf_bytes
comma
l_string|&quot;reg%02i: base=0x%05lx000 (%4liMB), size=%4li%cB: %s, count=%d&bslash;n&quot;
comma
id|i
comma
id|base
comma
id|base
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
comma
id|size
comma
id|factor
comma
id|attrib_to_str
c_func
(paren
id|type
)paren
comma
id|usage_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|ascii_buf_bytes
op_add_assign
id|strlen
c_func
(paren
id|ascii_buffer
op_plus
id|ascii_buf_bytes
)paren
suffix:semicolon
)brace
)brace
id|devfs_set_file_size
c_func
(paren
id|devfs_handle
comma
id|ascii_buf_bytes
)paren
suffix:semicolon
macro_line|#  ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
id|proc_root_mtrr
)paren
id|proc_root_mtrr-&gt;size
op_assign
id|ascii_buf_bytes
suffix:semicolon
macro_line|#  endif&t;&t;&t;/*  CONFIG_PROC_FS  */
)brace
DECL|function|mtrr_if_init
r_static
r_int
id|__init
id|mtrr_if_init
c_func
(paren
r_void
)paren
(brace
r_int
id|max
op_assign
id|num_var_ranges
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ascii_buffer
op_assign
id|kmalloc
c_func
(paren
id|max
op_star
id|LINE_SIZE
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mtrr: could not allocate&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ascii_buf_bytes
op_assign
l_int|0
suffix:semicolon
id|compute_ascii
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_root_mtrr
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;mtrr&quot;
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_root_mtrr
)paren
(brace
id|proc_root_mtrr-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|proc_root_mtrr-&gt;proc_fops
op_assign
op_amp
id|mtrr_fops
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef USERSPACE_INTERFACE
id|devfs_handle
op_assign
id|devfs_register
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu/mtrr&quot;
comma
id|DEVFS_FL_DEFAULT
comma
l_int|0
comma
l_int|0
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
op_amp
id|mtrr_fops
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mtrr_if_init
id|arch_initcall
c_func
(paren
id|mtrr_if_init
)paren
suffix:semicolon
eof