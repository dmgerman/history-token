macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
DECL|variable|message
r_static
id|__initdata
r_char
op_star
id|message
suffix:semicolon
DECL|function|error
r_static
r_void
id|__init
id|error
c_func
(paren
r_char
op_star
id|x
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|message
)paren
id|message
op_assign
id|x
suffix:semicolon
)brace
DECL|function|malloc
r_static
r_void
id|__init
op_star
id|malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|free
r_static
r_void
id|__init
id|free
c_func
(paren
r_void
op_star
id|where
)paren
(brace
id|kfree
c_func
(paren
id|where
)paren
suffix:semicolon
)brace
multiline_comment|/* link hash */
DECL|struct|hash
r_static
r_struct
id|hash
(brace
DECL|member|ino
DECL|member|minor
DECL|member|major
r_int
id|ino
comma
id|minor
comma
id|major
suffix:semicolon
DECL|member|next
r_struct
id|hash
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|head
)brace
op_star
id|head
(braket
l_int|32
)braket
suffix:semicolon
DECL|function|hash
r_static
r_inline
r_int
id|hash
c_func
(paren
r_int
id|major
comma
r_int
id|minor
comma
r_int
id|ino
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|ino
op_plus
id|minor
op_plus
(paren
id|major
op_lshift
l_int|3
)paren
suffix:semicolon
id|tmp
op_add_assign
id|tmp
op_rshift
l_int|5
suffix:semicolon
r_return
id|tmp
op_amp
l_int|31
suffix:semicolon
)brace
DECL|function|find_link
r_static
r_char
id|__init
op_star
id|find_link
c_func
(paren
r_int
id|major
comma
r_int
id|minor
comma
r_int
id|ino
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|hash
op_star
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|head
op_plus
id|hash
c_func
(paren
id|major
comma
id|minor
comma
id|ino
)paren
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|ino
op_ne
id|ino
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|minor
op_ne
id|minor
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|major
op_ne
id|major
)paren
r_continue
suffix:semicolon
r_return
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|name
suffix:semicolon
)brace
id|q
op_assign
(paren
r_struct
id|hash
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hash
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
id|panic
c_func
(paren
l_string|&quot;can&squot;t allocate link hash entry&quot;
)paren
suffix:semicolon
id|q-&gt;ino
op_assign
id|ino
suffix:semicolon
id|q-&gt;minor
op_assign
id|minor
suffix:semicolon
id|q-&gt;major
op_assign
id|major
suffix:semicolon
id|q-&gt;name
op_assign
id|name
suffix:semicolon
id|q-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|p
op_assign
id|q
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|free_hash
r_static
r_void
id|__init
id|free_hash
c_func
(paren
r_void
)paren
(brace
r_struct
id|hash
op_star
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|head
suffix:semicolon
id|p
OL
id|head
op_plus
l_int|32
suffix:semicolon
id|p
op_increment
)paren
(brace
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
id|q
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|q-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* cpio header parsing */
DECL|variable|ino
DECL|variable|major
DECL|variable|minor
DECL|variable|nlink
r_static
id|__initdata
r_int
r_int
id|ino
comma
id|major
comma
id|minor
comma
id|nlink
suffix:semicolon
DECL|variable|mode
r_static
id|__initdata
id|mode_t
id|mode
suffix:semicolon
DECL|variable|body_len
DECL|variable|name_len
r_static
id|__initdata
r_int
r_int
id|body_len
comma
id|name_len
suffix:semicolon
DECL|variable|uid
r_static
id|__initdata
id|uid_t
id|uid
suffix:semicolon
DECL|variable|gid
r_static
id|__initdata
id|gid_t
id|gid
suffix:semicolon
DECL|variable|rdev
r_static
id|__initdata
r_int
id|rdev
suffix:semicolon
DECL|function|parse_header
r_static
r_void
id|__init
id|parse_header
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_int
r_int
id|parsed
(braket
l_int|12
)braket
suffix:semicolon
r_char
id|buf
(braket
l_int|9
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|buf
(braket
l_int|8
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|s
op_add_assign
l_int|6
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
comma
id|s
op_add_assign
l_int|8
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|s
comma
l_int|8
)paren
suffix:semicolon
id|parsed
(braket
id|i
)braket
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
)brace
id|ino
op_assign
id|parsed
(braket
l_int|0
)braket
suffix:semicolon
id|mode
op_assign
id|parsed
(braket
l_int|1
)braket
suffix:semicolon
id|uid
op_assign
id|parsed
(braket
l_int|2
)braket
suffix:semicolon
id|gid
op_assign
id|parsed
(braket
l_int|3
)braket
suffix:semicolon
id|nlink
op_assign
id|parsed
(braket
l_int|4
)braket
suffix:semicolon
id|body_len
op_assign
id|parsed
(braket
l_int|6
)braket
suffix:semicolon
id|major
op_assign
id|parsed
(braket
l_int|7
)braket
suffix:semicolon
id|minor
op_assign
id|parsed
(braket
l_int|8
)braket
suffix:semicolon
id|rdev
op_assign
id|new_encode_dev
c_func
(paren
id|MKDEV
c_func
(paren
id|parsed
(braket
l_int|9
)braket
comma
id|parsed
(braket
l_int|10
)braket
)paren
)paren
suffix:semicolon
id|name_len
op_assign
id|parsed
(braket
l_int|11
)braket
suffix:semicolon
)brace
multiline_comment|/* FSM */
DECL|enum|state
r_static
id|__initdata
r_enum
id|state
(brace
DECL|enumerator|Start
id|Start
comma
DECL|enumerator|Collect
id|Collect
comma
DECL|enumerator|GotHeader
id|GotHeader
comma
DECL|enumerator|SkipIt
id|SkipIt
comma
DECL|enumerator|GotName
id|GotName
comma
DECL|enumerator|CopyFile
id|CopyFile
comma
DECL|enumerator|GotSymlink
id|GotSymlink
comma
DECL|enumerator|Reset
id|Reset
DECL|variable|state
DECL|variable|next_state
)brace
id|state
comma
id|next_state
suffix:semicolon
DECL|variable|victim
r_static
id|__initdata
r_char
op_star
id|victim
suffix:semicolon
DECL|variable|count
r_static
id|__initdata
r_int
id|count
suffix:semicolon
DECL|variable|this_header
DECL|variable|next_header
r_static
id|__initdata
id|loff_t
id|this_header
comma
id|next_header
suffix:semicolon
DECL|variable|dry_run
r_static
id|__initdata
r_int
id|dry_run
suffix:semicolon
DECL|function|eat
r_static
r_inline
r_void
id|eat
c_func
(paren
r_int
id|n
)paren
(brace
id|victim
op_add_assign
id|n
suffix:semicolon
id|this_header
op_add_assign
id|n
suffix:semicolon
id|count
op_sub_assign
id|n
suffix:semicolon
)brace
DECL|macro|N_ALIGN
mdefine_line|#define N_ALIGN(len) ((((len) + 1) &amp; ~3) + 2)
DECL|variable|collected
r_static
id|__initdata
r_char
op_star
id|collected
suffix:semicolon
DECL|variable|remains
r_static
id|__initdata
r_int
id|remains
suffix:semicolon
DECL|variable|collect
r_static
id|__initdata
r_char
op_star
id|collect
suffix:semicolon
DECL|function|read_into
r_static
r_void
id|__init
id|read_into
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_enum
id|state
id|next
)paren
(brace
r_if
c_cond
(paren
id|count
op_ge
id|size
)paren
(brace
id|collected
op_assign
id|victim
suffix:semicolon
id|eat
c_func
(paren
id|size
)paren
suffix:semicolon
id|state
op_assign
id|next
suffix:semicolon
)brace
r_else
(brace
id|collect
op_assign
id|collected
op_assign
id|buf
suffix:semicolon
id|remains
op_assign
id|size
suffix:semicolon
id|next_state
op_assign
id|next
suffix:semicolon
id|state
op_assign
id|Collect
suffix:semicolon
)brace
)brace
DECL|variable|header_buf
DECL|variable|symlink_buf
DECL|variable|name_buf
r_static
id|__initdata
r_char
op_star
id|header_buf
comma
op_star
id|symlink_buf
comma
op_star
id|name_buf
suffix:semicolon
DECL|function|do_start
r_static
r_int
id|__init
id|do_start
c_func
(paren
r_void
)paren
(brace
id|read_into
c_func
(paren
id|header_buf
comma
l_int|110
comma
id|GotHeader
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_collect
r_static
r_int
id|__init
id|do_collect
c_func
(paren
r_void
)paren
(brace
r_int
id|n
op_assign
id|remains
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|n
)paren
id|n
op_assign
id|count
suffix:semicolon
id|memcpy
c_func
(paren
id|collect
comma
id|victim
comma
id|n
)paren
suffix:semicolon
id|eat
c_func
(paren
id|n
)paren
suffix:semicolon
id|collect
op_add_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|remains
op_sub_assign
id|n
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|state
op_assign
id|next_state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_header
r_static
r_int
id|__init
id|do_header
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|collected
comma
l_string|&quot;070701&quot;
comma
l_int|6
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;no cpio magic&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|parse_header
c_func
(paren
id|collected
)paren
suffix:semicolon
id|next_header
op_assign
id|this_header
op_plus
id|N_ALIGN
c_func
(paren
id|name_len
)paren
op_plus
id|body_len
suffix:semicolon
id|next_header
op_assign
(paren
id|next_header
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|dry_run
)paren
(brace
id|read_into
c_func
(paren
id|name_buf
comma
id|N_ALIGN
c_func
(paren
id|name_len
)paren
comma
id|GotName
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|state
op_assign
id|SkipIt
suffix:semicolon
r_if
c_cond
(paren
id|name_len
op_le
l_int|0
op_logical_or
id|name_len
OG
id|PATH_MAX
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|body_len
OG
id|PATH_MAX
)paren
r_return
l_int|0
suffix:semicolon
id|collect
op_assign
id|collected
op_assign
id|symlink_buf
suffix:semicolon
id|remains
op_assign
id|N_ALIGN
c_func
(paren
id|name_len
)paren
op_plus
id|body_len
suffix:semicolon
id|next_state
op_assign
id|GotSymlink
suffix:semicolon
id|state
op_assign
id|Collect
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
op_logical_or
op_logical_neg
id|body_len
)paren
id|read_into
c_func
(paren
id|name_buf
comma
id|N_ALIGN
c_func
(paren
id|name_len
)paren
comma
id|GotName
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_skip
r_static
r_int
id|__init
id|do_skip
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|this_header
op_plus
id|count
OL
id|next_header
)paren
(brace
id|eat
c_func
(paren
id|count
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|eat
c_func
(paren
id|next_header
op_minus
id|this_header
)paren
suffix:semicolon
id|state
op_assign
id|next_state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|do_reset
r_static
r_int
id|__init
id|do_reset
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|count
op_logical_and
op_star
id|victim
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|eat
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_logical_and
(paren
id|this_header
op_amp
l_int|3
)paren
)paren
id|error
c_func
(paren
l_string|&quot;broken padding&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|maybe_link
r_static
r_int
id|__init
id|maybe_link
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|nlink
op_ge
l_int|2
)paren
(brace
r_char
op_star
id|old
op_assign
id|find_link
c_func
(paren
id|major
comma
id|minor
comma
id|ino
comma
id|collected
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
)paren
r_return
(paren
id|sys_link
c_func
(paren
id|old
comma
id|collected
)paren
OL
l_int|0
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|wfd
r_static
id|__initdata
r_int
id|wfd
suffix:semicolon
DECL|function|do_name
r_static
r_int
id|__init
id|do_name
c_func
(paren
r_void
)paren
(brace
id|state
op_assign
id|SkipIt
suffix:semicolon
id|next_state
op_assign
id|Reset
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|collected
comma
l_string|&quot;TRAILER!!!&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|free_hash
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dry_run
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|maybe_link
c_func
(paren
)paren
op_ge
l_int|0
)paren
(brace
id|wfd
op_assign
id|sys_open
c_func
(paren
id|collected
comma
id|O_WRONLY
op_or
id|O_CREAT
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wfd
op_ge
l_int|0
)paren
(brace
id|sys_fchown
c_func
(paren
id|wfd
comma
id|uid
comma
id|gid
)paren
suffix:semicolon
id|sys_fchmod
c_func
(paren
id|wfd
comma
id|mode
)paren
suffix:semicolon
id|state
op_assign
id|CopyFile
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
id|sys_mkdir
c_func
(paren
id|collected
comma
id|mode
)paren
suffix:semicolon
id|sys_chown
c_func
(paren
id|collected
comma
id|uid
comma
id|gid
)paren
suffix:semicolon
id|sys_chmod
c_func
(paren
id|collected
comma
id|mode
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISCHR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISFIFO
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISSOCK
c_func
(paren
id|mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|maybe_link
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
id|sys_mknod
c_func
(paren
id|collected
comma
id|mode
comma
id|rdev
)paren
suffix:semicolon
id|sys_chown
c_func
(paren
id|collected
comma
id|uid
comma
id|gid
)paren
suffix:semicolon
id|sys_chmod
c_func
(paren
id|collected
comma
id|mode
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_copy
r_static
r_int
id|__init
id|do_copy
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|count
op_ge
id|body_len
)paren
(brace
id|sys_write
c_func
(paren
id|wfd
comma
id|victim
comma
id|body_len
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|wfd
)paren
suffix:semicolon
id|eat
c_func
(paren
id|body_len
)paren
suffix:semicolon
id|state
op_assign
id|SkipIt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|sys_write
c_func
(paren
id|wfd
comma
id|victim
comma
id|count
)paren
suffix:semicolon
id|body_len
op_sub_assign
id|count
suffix:semicolon
id|eat
c_func
(paren
id|count
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|do_symlink
r_static
r_int
id|__init
id|do_symlink
c_func
(paren
r_void
)paren
(brace
id|collected
(braket
id|N_ALIGN
c_func
(paren
id|name_len
)paren
op_plus
id|body_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|sys_symlink
c_func
(paren
id|collected
op_plus
id|N_ALIGN
c_func
(paren
id|name_len
)paren
comma
id|collected
)paren
suffix:semicolon
id|sys_lchown
c_func
(paren
id|collected
comma
id|uid
comma
id|gid
)paren
suffix:semicolon
id|state
op_assign
id|SkipIt
suffix:semicolon
id|next_state
op_assign
id|Reset
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|actions
r_static
id|__initdata
r_int
(paren
op_star
id|actions
(braket
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
(braket
id|Start
)braket
op_assign
id|do_start
comma
(braket
id|Collect
)braket
op_assign
id|do_collect
comma
(braket
id|GotHeader
)braket
op_assign
id|do_header
comma
(braket
id|SkipIt
)braket
op_assign
id|do_skip
comma
(braket
id|GotName
)braket
op_assign
id|do_name
comma
(braket
id|CopyFile
)braket
op_assign
id|do_copy
comma
(braket
id|GotSymlink
)braket
op_assign
id|do_symlink
comma
(braket
id|Reset
)braket
op_assign
id|do_reset
comma
)brace
suffix:semicolon
DECL|function|write_buffer
r_static
r_int
id|__init
id|write_buffer
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|count
op_assign
id|len
suffix:semicolon
id|victim
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|actions
(braket
id|state
)braket
(paren
)paren
)paren
suffix:semicolon
r_return
id|len
op_minus
id|count
suffix:semicolon
)brace
DECL|function|flush_buffer
r_static
r_void
id|__init
id|flush_buffer
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|written
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|written
op_assign
id|write_buffer
c_func
(paren
id|buf
comma
id|len
)paren
)paren
OL
id|len
op_logical_and
op_logical_neg
id|message
)paren
(brace
r_char
id|c
op_assign
id|buf
(braket
id|written
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|buf
op_add_assign
id|written
suffix:semicolon
id|len
op_sub_assign
id|written
suffix:semicolon
id|state
op_assign
id|Start
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_int|0
)paren
(brace
id|buf
op_add_assign
id|written
suffix:semicolon
id|len
op_sub_assign
id|written
suffix:semicolon
id|state
op_assign
id|Reset
suffix:semicolon
)brace
r_else
id|error
c_func
(paren
l_string|&quot;junk in compressed archive&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * gzip declarations&n; */
DECL|macro|OF
mdefine_line|#define OF(args)  args
macro_line|#ifndef memzero
DECL|macro|memzero
mdefine_line|#define memzero(s, n)     memset ((s), 0, (n))
macro_line|#endif
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
suffix:semicolon
DECL|typedef|ulg
r_typedef
r_int
r_int
id|ulg
suffix:semicolon
DECL|macro|WSIZE
mdefine_line|#define WSIZE 0x8000    /* window size--must be a power of two, and */
multiline_comment|/*  at least 32K for zip&squot;s deflate method */
DECL|variable|inbuf
r_static
id|uch
op_star
id|inbuf
suffix:semicolon
DECL|variable|window
r_static
id|uch
op_star
id|window
suffix:semicolon
DECL|variable|insize
r_static
r_int
id|insize
suffix:semicolon
multiline_comment|/* valid bytes in inbuf */
DECL|variable|inptr
r_static
r_int
id|inptr
suffix:semicolon
multiline_comment|/* index of next byte to be processed in inbuf */
DECL|variable|outcnt
r_static
r_int
id|outcnt
suffix:semicolon
multiline_comment|/* bytes in output buffer */
DECL|variable|bytes_out
r_static
r_int
id|bytes_out
suffix:semicolon
DECL|macro|get_byte
mdefine_line|#define get_byte()  (inptr &lt; insize ? inbuf[inptr++] : -1)
multiline_comment|/* Diagnostic functions (stubbed out) */
DECL|macro|Assert
mdefine_line|#define Assert(cond,msg)
DECL|macro|Trace
mdefine_line|#define Trace(x)
DECL|macro|Tracev
mdefine_line|#define Tracev(x)
DECL|macro|Tracevv
mdefine_line|#define Tracevv(x)
DECL|macro|Tracec
mdefine_line|#define Tracec(c,x)
DECL|macro|Tracecv
mdefine_line|#define Tracecv(c,x)
DECL|macro|STATIC
mdefine_line|#define STATIC static
DECL|macro|INIT
mdefine_line|#define INIT __init
r_static
r_void
id|__init
id|flush_window
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
id|error
c_func
(paren
r_char
op_star
id|m
)paren
suffix:semicolon
r_static
r_void
id|__init
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
id|__init
id|gzip_release
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
macro_line|#include &quot;../lib/inflate.c&quot;
DECL|function|gzip_mark
r_static
r_void
id|__init
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
id|ptr
)paren
(brace
)brace
DECL|function|gzip_release
r_static
r_void
id|__init
id|gzip_release
c_func
(paren
r_void
op_star
op_star
id|ptr
)paren
(brace
)brace
multiline_comment|/* ===========================================================================&n; * Write the output window window[0..outcnt-1] and update crc and bytes_out.&n; * (Used for the decompressed data only.)&n; */
DECL|function|flush_window
r_static
r_void
id|__init
id|flush_window
c_func
(paren
r_void
)paren
(brace
id|ulg
id|c
op_assign
id|crc
suffix:semicolon
multiline_comment|/* temporary variable */
r_int
id|n
suffix:semicolon
id|uch
op_star
id|in
comma
id|ch
suffix:semicolon
id|flush_buffer
c_func
(paren
id|window
comma
id|outcnt
)paren
suffix:semicolon
id|in
op_assign
id|window
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|outcnt
suffix:semicolon
id|n
op_increment
)paren
(brace
id|ch
op_assign
op_star
id|in
op_increment
suffix:semicolon
id|c
op_assign
id|crc_32_tab
(braket
(paren
(paren
r_int
)paren
id|c
op_xor
id|ch
)paren
op_amp
l_int|0xff
)braket
op_xor
(paren
id|c
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|crc
op_assign
id|c
suffix:semicolon
id|bytes_out
op_add_assign
(paren
id|ulg
)paren
id|outcnt
suffix:semicolon
id|outcnt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|unpack_to_rootfs
r_static
r_char
op_star
id|__init
id|unpack_to_rootfs
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|check_only
)paren
(brace
r_int
id|written
suffix:semicolon
id|dry_run
op_assign
id|check_only
suffix:semicolon
id|header_buf
op_assign
id|malloc
c_func
(paren
l_int|110
)paren
suffix:semicolon
id|symlink_buf
op_assign
id|malloc
c_func
(paren
id|PATH_MAX
op_plus
id|N_ALIGN
c_func
(paren
id|PATH_MAX
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|name_buf
op_assign
id|malloc
c_func
(paren
id|N_ALIGN
c_func
(paren
id|PATH_MAX
)paren
)paren
suffix:semicolon
id|window
op_assign
id|malloc
c_func
(paren
id|WSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|window
op_logical_or
op_logical_neg
id|header_buf
op_logical_or
op_logical_neg
id|symlink_buf
op_logical_or
op_logical_neg
id|name_buf
)paren
id|panic
c_func
(paren
l_string|&quot;can&squot;t allocate buffers&quot;
)paren
suffix:semicolon
id|state
op_assign
id|Start
suffix:semicolon
id|this_header
op_assign
l_int|0
suffix:semicolon
id|message
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|message
op_logical_and
id|len
)paren
(brace
id|loff_t
id|saved_offset
op_assign
id|this_header
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buf
op_eq
l_char|&squot;0&squot;
op_logical_and
op_logical_neg
(paren
id|this_header
op_amp
l_int|3
)paren
)paren
(brace
id|state
op_assign
id|Start
suffix:semicolon
id|written
op_assign
id|write_buffer
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
id|buf
op_add_assign
id|written
suffix:semicolon
id|len
op_sub_assign
id|written
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|buf
)paren
(brace
id|buf
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
id|this_header
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|this_header
op_assign
l_int|0
suffix:semicolon
id|insize
op_assign
id|len
suffix:semicolon
id|inbuf
op_assign
id|buf
suffix:semicolon
id|inptr
op_assign
l_int|0
suffix:semicolon
id|outcnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* bytes in output buffer */
id|bytes_out
op_assign
l_int|0
suffix:semicolon
id|crc
op_assign
(paren
id|ulg
)paren
l_int|0xffffffffL
suffix:semicolon
multiline_comment|/* shift register contents */
id|makecrc
c_func
(paren
)paren
suffix:semicolon
id|gunzip
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_ne
id|Reset
)paren
id|error
c_func
(paren
l_string|&quot;junk in gzipped archive&quot;
)paren
suffix:semicolon
id|this_header
op_assign
id|saved_offset
op_plus
id|inptr
suffix:semicolon
id|buf
op_add_assign
id|inptr
suffix:semicolon
id|len
op_sub_assign
id|inptr
suffix:semicolon
)brace
id|free
c_func
(paren
id|window
)paren
suffix:semicolon
id|free
c_func
(paren
id|name_buf
)paren
suffix:semicolon
id|free
c_func
(paren
id|symlink_buf
)paren
suffix:semicolon
id|free
c_func
(paren
id|header_buf
)paren
suffix:semicolon
r_return
id|message
suffix:semicolon
)brace
r_extern
r_char
id|__initramfs_start
(braket
)braket
comma
id|__initramfs_end
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#endif
DECL|function|populate_rootfs
r_void
id|__init
id|populate_rootfs
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|err
op_assign
id|unpack_to_rootfs
c_func
(paren
id|__initramfs_start
comma
id|__initramfs_end
op_minus
id|__initramfs_start
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|panic
c_func
(paren
id|err
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
r_int
id|fd
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;checking if image is initramfs...&quot;
)paren
suffix:semicolon
id|err
op_assign
id|unpack_to_rootfs
c_func
(paren
(paren
r_char
op_star
)paren
id|initrd_start
comma
id|initrd_end
op_minus
id|initrd_start
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; it is&bslash;n&quot;
)paren
suffix:semicolon
id|unpack_to_rootfs
c_func
(paren
(paren
r_char
op_star
)paren
id|initrd_start
comma
id|initrd_end
op_minus
id|initrd_start
comma
l_int|0
)paren
suffix:semicolon
id|free_initrd_mem
c_func
(paren
id|initrd_start
comma
id|initrd_end
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;it isn&squot;t (%s); looks like an initrd&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
l_string|&quot;/initrd.image&quot;
comma
id|O_WRONLY
op_or
id|O_CREAT
comma
l_int|700
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
id|sys_write
c_func
(paren
id|fd
comma
(paren
r_char
op_star
)paren
id|initrd_start
comma
id|initrd_end
op_minus
id|initrd_start
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|free_initrd_mem
c_func
(paren
id|initrd_start
comma
id|initrd_end
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
eof
