multiline_comment|/*&n; * linux/fs/seq_file.c&n; *&n; * helper functions for making syntetic files from sequences of records.&n; * initial implementation -- AV, Oct 2001.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/**&n; *&t;seq_open -&t;initialize sequential file&n; *&t;@file: file we initialize&n; *&t;@op: method table describing the sequence&n; *&n; *&t;seq_open() sets @file, associating it with a sequence described&n; *&t;by @op.  @op-&gt;start() sets the iterator up and returns the first&n; *&t;element of sequence. @op-&gt;stop() shuts it down.  @op-&gt;next()&n; *&t;returns the next element of sequence.  @op-&gt;show() prints element&n; *&t;into the buffer.  In case of error -&gt;start() and -&gt;next() return&n; *&t;ERR_PTR(error).  In the end of sequence they return %NULL. -&gt;show()&n; *&t;returns 0 in case of success and negative number in case of error.&n; */
DECL|function|seq_open
r_int
id|seq_open
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|seq_operations
op_star
id|op
)paren
(brace
r_struct
id|seq_file
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|p-&gt;sem
comma
l_int|1
)paren
suffix:semicolon
id|p-&gt;op
op_assign
id|op
suffix:semicolon
id|file-&gt;private_data
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;seq_read -&t;-&gt;read() method for sequential files.&n; *&t;@file, @buf, @size, @ppos: see file_operations method&n; *&n; *&t;Ready-made -&gt;f_op-&gt;read()&n; */
DECL|function|seq_read
id|ssize_t
id|seq_read
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
id|size
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|seq_file
op_star
id|m
op_assign
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
id|loff_t
id|pos
suffix:semicolon
r_int
id|n
suffix:semicolon
r_void
op_star
id|p
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
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
id|EPIPE
suffix:semicolon
id|down
c_func
(paren
op_amp
id|m-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* grab buffer if we didn&squot;t have one */
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;buf
)paren
(brace
id|m-&gt;buf
op_assign
id|kmalloc
c_func
(paren
id|m-&gt;size
op_assign
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;buf
)paren
r_goto
id|Enomem
suffix:semicolon
)brace
multiline_comment|/* if not empty - flush it first */
r_if
c_cond
(paren
id|m-&gt;count
)paren
(brace
id|n
op_assign
id|min
c_func
(paren
id|m-&gt;count
comma
id|size
)paren
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|m-&gt;buf
op_plus
id|m-&gt;from
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|Efault
suffix:semicolon
id|m-&gt;count
op_sub_assign
id|n
suffix:semicolon
id|m-&gt;from
op_add_assign
id|n
suffix:semicolon
id|size
op_sub_assign
id|n
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
id|copied
op_add_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;count
)paren
id|m-&gt;index
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_goto
id|Done
suffix:semicolon
)brace
multiline_comment|/* we need at least one record in buffer */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|pos
op_assign
id|m-&gt;index
suffix:semicolon
id|p
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|start
c_func
(paren
id|m
comma
op_amp
id|pos
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
r_break
suffix:semicolon
id|err
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|show
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;count
OL
id|m-&gt;size
)paren
r_goto
id|Fill
suffix:semicolon
id|m-&gt;op
op_member_access_from_pointer
id|stop
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|m-&gt;buf
)paren
suffix:semicolon
id|m-&gt;buf
op_assign
id|kmalloc
c_func
(paren
id|m-&gt;size
op_lshift_assign
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;buf
)paren
r_goto
id|Enomem
suffix:semicolon
id|m-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
id|m-&gt;op
op_member_access_from_pointer
id|stop
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
id|m-&gt;count
op_assign
l_int|0
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Fill
suffix:colon
multiline_comment|/* they want more? let&squot;s try to get some more */
r_while
c_loop
(paren
id|m-&gt;count
OL
id|size
)paren
(brace
r_int
id|offs
op_assign
id|m-&gt;count
suffix:semicolon
id|loff_t
id|next
op_assign
id|pos
suffix:semicolon
id|p
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|next
c_func
(paren
id|m
comma
id|p
comma
op_amp
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|err
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|show
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_or
id|m-&gt;count
op_eq
id|m-&gt;size
)paren
(brace
id|m-&gt;count
op_assign
id|offs
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pos
op_assign
id|next
suffix:semicolon
)brace
id|m-&gt;op
op_member_access_from_pointer
id|stop
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
id|n
op_assign
id|min
c_func
(paren
id|m-&gt;count
comma
id|size
)paren
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|m-&gt;buf
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|Efault
suffix:semicolon
id|copied
op_add_assign
id|n
suffix:semicolon
id|m-&gt;count
op_sub_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;count
)paren
id|m-&gt;from
op_assign
id|n
suffix:semicolon
r_else
id|pos
op_increment
suffix:semicolon
id|m-&gt;index
op_assign
id|pos
suffix:semicolon
id|Done
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|copied
)paren
id|copied
op_assign
id|err
suffix:semicolon
r_else
op_star
id|ppos
op_add_assign
id|copied
suffix:semicolon
id|up
c_func
(paren
op_amp
id|m-&gt;sem
)paren
suffix:semicolon
r_return
id|copied
suffix:semicolon
id|Enomem
suffix:colon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Efault
suffix:colon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
DECL|function|traverse
r_static
r_int
id|traverse
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
id|offset
)paren
(brace
id|loff_t
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|p
suffix:semicolon
id|m-&gt;index
op_assign
l_int|0
suffix:semicolon
id|m-&gt;count
op_assign
id|m-&gt;from
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;buf
)paren
(brace
id|m-&gt;buf
op_assign
id|kmalloc
c_func
(paren
id|m-&gt;size
op_assign
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|p
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|start
c_func
(paren
id|m
comma
op_amp
id|m-&gt;index
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
r_break
suffix:semicolon
id|error
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|show
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;count
op_eq
id|m-&gt;size
)paren
r_goto
id|Eoverflow
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|m-&gt;count
OG
id|offset
)paren
(brace
id|m-&gt;from
op_assign
id|offset
op_minus
id|pos
suffix:semicolon
id|m-&gt;count
op_sub_assign
id|m-&gt;from
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pos
op_add_assign
id|m-&gt;count
suffix:semicolon
id|m-&gt;count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_eq
id|offset
)paren
(brace
id|m-&gt;index
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|p
op_assign
id|m-&gt;op
op_member_access_from_pointer
id|next
c_func
(paren
id|m
comma
id|p
comma
op_amp
id|m-&gt;index
)paren
suffix:semicolon
)brace
id|m-&gt;op
op_member_access_from_pointer
id|stop
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|Eoverflow
suffix:colon
id|m-&gt;op
op_member_access_from_pointer
id|stop
c_func
(paren
id|m
comma
id|p
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|m-&gt;buf
)paren
suffix:semicolon
id|m-&gt;buf
op_assign
id|kmalloc
c_func
(paren
id|m-&gt;size
op_lshift_assign
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_return
op_logical_neg
id|m-&gt;buf
ques
c_cond
op_minus
id|ENOMEM
suffix:colon
op_minus
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;seq_lseek -&t;-&gt;llseek() method for sequential files.&n; *&t;@file, @offset, @origin: see file_operations method&n; *&n; *&t;Ready-made -&gt;f_op-&gt;llseek()&n; */
DECL|function|seq_lseek
id|loff_t
id|seq_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_struct
id|seq_file
op_star
id|m
op_assign
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|m-&gt;sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_break
suffix:semicolon
id|retval
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
r_while
c_loop
(paren
(paren
id|retval
op_assign
id|traverse
c_func
(paren
id|m
comma
id|offset
)paren
)paren
op_eq
op_minus
id|EAGAIN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
multiline_comment|/* with extreme perjudice... */
id|file-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
id|m-&gt;index
op_assign
l_int|0
suffix:semicolon
id|m-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
)brace
)brace
)brace
id|up
c_func
(paren
op_amp
id|m-&gt;sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;seq_release -&t;free the structures associated with sequential file.&n; *&t;@file: file in question&n; *&t;@inode: file-&gt;f_dentry-&gt;d_inode&n; *&n; *&t;Frees the structures associated with sequential file; can be used&n; *&t;as -&gt;f_op-&gt;release() if you don&squot;t have private data to destroy.&n; */
DECL|function|seq_release
r_int
id|seq_release
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
)paren
(brace
r_struct
id|seq_file
op_star
id|m
op_assign
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|kfree
c_func
(paren
id|m-&gt;buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|m
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;seq_escape -&t;print string into buffer, escaping some characters&n; *&t;@m:&t;target buffer&n; *&t;@s:&t;string&n; *&t;@esc:&t;set of characters that need escaping&n; *&n; *&t;Puts string into buffer, replacing each occurrence of character from&n; *&t;@esc with usual octal escape.  Returns 0 in case of success, -1 - in&n; *&t;case of overflow.&n; */
DECL|function|seq_escape
r_int
id|seq_escape
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_const
r_char
op_star
id|s
comma
r_const
r_char
op_star
id|esc
)paren
(brace
r_char
op_star
id|end
op_assign
id|m-&gt;buf
op_plus
id|m-&gt;size
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_char
id|c
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|m-&gt;buf
op_plus
id|m-&gt;count
suffix:semicolon
(paren
id|c
op_assign
op_star
id|s
)paren
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
id|p
OL
id|end
suffix:semicolon
id|s
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
id|esc
comma
id|c
)paren
)paren
(brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_plus
l_int|3
OL
id|end
)paren
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
(paren
(paren
id|c
op_amp
l_int|0300
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
(paren
(paren
id|c
op_amp
l_int|070
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
(paren
id|c
op_amp
l_int|07
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|m-&gt;count
op_assign
id|m-&gt;size
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|m-&gt;count
op_assign
id|p
op_minus
id|m-&gt;buf
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|seq_printf
r_int
id|seq_printf
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_const
r_char
op_star
id|f
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;count
OL
id|m-&gt;size
)paren
(brace
id|va_start
c_func
(paren
id|args
comma
id|f
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|m-&gt;buf
op_plus
id|m-&gt;count
comma
id|m-&gt;size
op_minus
id|m-&gt;count
comma
id|f
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;count
op_plus
id|len
OL
id|m-&gt;size
)paren
(brace
id|m-&gt;count
op_add_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|m-&gt;count
op_assign
id|m-&gt;size
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|single_start
r_static
r_void
op_star
id|single_start
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_return
l_int|NULL
op_plus
(paren
op_star
id|pos
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|single_next
r_static
r_void
op_star
id|single_next
c_func
(paren
r_struct
id|seq_file
op_star
id|p
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
op_increment
op_star
id|pos
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|single_stop
r_static
r_void
id|single_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|function|single_open
r_int
id|single_open
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
(paren
op_star
id|show
)paren
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|seq_operations
op_star
id|op
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|op
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|res
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|op
)paren
(brace
id|op-&gt;start
op_assign
id|single_start
suffix:semicolon
id|op-&gt;next
op_assign
id|single_next
suffix:semicolon
id|op-&gt;stop
op_assign
id|single_stop
suffix:semicolon
id|op-&gt;show
op_assign
id|show
suffix:semicolon
id|res
op_assign
id|seq_open
c_func
(paren
id|file
comma
id|op
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(paren
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
)paren
op_member_access_from_pointer
r_private
op_assign
id|data
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|op
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|single_release
r_int
id|single_release
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
)paren
(brace
r_struct
id|seq_operations
op_star
id|op
op_assign
(paren
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
)paren
op_member_access_from_pointer
id|op
suffix:semicolon
r_int
id|res
op_assign
id|seq_release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|op
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
eof
