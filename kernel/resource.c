multiline_comment|/*&n; *&t;linux/kernel/resource.c&n; *&n; * Copyright (C) 1999&t;Linus Torvalds&n; * Copyright (C) 1999&t;Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; * Arbitrary resource management.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|ioport_resource
r_struct
id|resource
id|ioport_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PCI IO&quot;
comma
dot
id|start
op_assign
l_int|0x0000
comma
dot
id|end
op_assign
id|IO_SPACE_LIMIT
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|ioport_resource
id|EXPORT_SYMBOL
c_func
(paren
id|ioport_resource
)paren
suffix:semicolon
DECL|variable|iomem_resource
r_struct
id|resource
id|iomem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PCI mem&quot;
comma
dot
id|start
op_assign
l_int|0UL
comma
dot
id|end
op_assign
op_complement
l_int|0UL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|iomem_resource
id|EXPORT_SYMBOL
c_func
(paren
id|iomem_resource
)paren
suffix:semicolon
DECL|variable|resource_lock
r_static
id|rwlock_t
id|resource_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|enumerator|MAX_IORES_LEVEL
r_enum
(brace
id|MAX_IORES_LEVEL
op_assign
l_int|5
)brace
suffix:semicolon
DECL|function|r_next
r_static
r_void
op_star
id|r_next
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
id|resource
op_star
id|p
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
id|p-&gt;child
)paren
r_return
id|p-&gt;child
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|p-&gt;sibling
op_logical_and
id|p-&gt;parent
)paren
id|p
op_assign
id|p-&gt;parent
suffix:semicolon
r_return
id|p-&gt;sibling
suffix:semicolon
)brace
DECL|function|r_start
r_static
r_void
op_star
id|r_start
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
id|resource
op_star
id|p
op_assign
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
id|loff_t
id|l
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|p-&gt;child
suffix:semicolon
id|p
op_logical_and
id|l
OL
op_star
id|pos
suffix:semicolon
id|p
op_assign
id|r_next
c_func
(paren
id|m
comma
id|p
comma
op_amp
id|l
)paren
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|r_stop
r_static
r_void
id|r_stop
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
id|read_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
)brace
DECL|function|r_show
r_static
r_int
id|r_show
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
id|resource
op_star
id|root
op_assign
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|resource
op_star
id|r
op_assign
id|v
comma
op_star
id|p
suffix:semicolon
r_int
id|width
op_assign
id|root-&gt;end
OL
l_int|0x10000
ques
c_cond
l_int|4
suffix:colon
l_int|8
suffix:semicolon
r_int
id|depth
suffix:semicolon
r_for
c_loop
(paren
id|depth
op_assign
l_int|0
comma
id|p
op_assign
id|r
suffix:semicolon
id|depth
OL
id|MAX_IORES_LEVEL
suffix:semicolon
id|depth
op_increment
comma
id|p
op_assign
id|p-&gt;parent
)paren
r_if
c_cond
(paren
id|p-&gt;parent
op_eq
id|root
)paren
r_break
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%*s%0*lx-%0*lx : %s&bslash;n&quot;
comma
id|depth
op_star
l_int|2
comma
l_string|&quot;&quot;
comma
id|width
comma
id|r-&gt;start
comma
id|width
comma
id|r-&gt;end
comma
id|r-&gt;name
ques
c_cond
id|r-&gt;name
suffix:colon
l_string|&quot;&lt;BAD&gt;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|resource_op
r_struct
id|seq_operations
id|resource_op
op_assign
(brace
dot
id|start
op_assign
id|r_start
comma
dot
id|next
op_assign
id|r_next
comma
dot
id|stop
op_assign
id|r_stop
comma
dot
id|show
op_assign
id|r_show
comma
)brace
suffix:semicolon
DECL|function|ioports_open
r_static
r_int
id|ioports_open
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
r_int
id|res
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|resource_op
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
r_struct
id|seq_file
op_star
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
op_amp
id|ioport_resource
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|iomem_open
r_static
r_int
id|iomem_open
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
r_int
id|res
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|resource_op
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
r_struct
id|seq_file
op_star
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m
op_member_access_from_pointer
r_private
op_assign
op_amp
id|iomem_resource
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|variable|proc_ioports_operations
r_static
r_struct
id|file_operations
id|proc_ioports_operations
op_assign
(brace
dot
id|open
op_assign
id|ioports_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|variable|proc_iomem_operations
r_static
r_struct
id|file_operations
id|proc_iomem_operations
op_assign
(brace
dot
id|open
op_assign
id|iomem_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|function|ioresources_init
r_static
r_int
id|__init
id|ioresources_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ioports&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_ioports_operations
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;iomem&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_iomem_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ioresources_init
id|__initcall
c_func
(paren
id|ioresources_init
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/* Return the conflict entry if you can&squot;t request it */
DECL|function|__request_resource
r_static
r_struct
id|resource
op_star
id|__request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
(brace
r_int
r_int
id|start
op_assign
r_new
op_member_access_from_pointer
id|start
suffix:semicolon
r_int
r_int
id|end
op_assign
r_new
op_member_access_from_pointer
id|end
suffix:semicolon
r_struct
id|resource
op_star
id|tmp
comma
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_return
id|root
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|root-&gt;start
)paren
r_return
id|root
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|root-&gt;end
)paren
r_return
id|root
suffix:semicolon
id|p
op_assign
op_amp
id|root-&gt;child
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
op_logical_or
id|tmp-&gt;start
OG
id|end
)paren
(brace
r_new
op_member_access_from_pointer
id|sibling
op_assign
id|tmp
suffix:semicolon
op_star
id|p
op_assign
r_new
suffix:semicolon
r_new
op_member_access_from_pointer
id|parent
op_assign
id|root
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|tmp-&gt;sibling
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;end
OL
id|start
)paren
r_continue
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
)brace
DECL|function|__release_resource
r_static
r_int
id|__release_resource
c_func
(paren
r_struct
id|resource
op_star
id|old
)paren
(brace
r_struct
id|resource
op_star
id|tmp
comma
op_star
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|old-&gt;parent-&gt;child
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
id|old
)paren
(brace
op_star
id|p
op_assign
id|tmp-&gt;sibling
suffix:semicolon
id|old-&gt;parent
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|tmp-&gt;sibling
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|request_resource
r_int
id|request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
(brace
r_struct
id|resource
op_star
id|conflict
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|conflict
op_assign
id|__request_resource
c_func
(paren
id|root
comma
r_new
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|conflict
ques
c_cond
op_minus
id|EBUSY
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|request_resource
id|EXPORT_SYMBOL
c_func
(paren
id|request_resource
)paren
suffix:semicolon
DECL|function|____request_resource
r_struct
id|resource
op_star
id|____request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
(brace
r_struct
id|resource
op_star
id|conflict
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|conflict
op_assign
id|__request_resource
c_func
(paren
id|root
comma
r_new
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|conflict
suffix:semicolon
)brace
DECL|variable|____request_resource
id|EXPORT_SYMBOL
c_func
(paren
id|____request_resource
)paren
suffix:semicolon
DECL|function|release_resource
r_int
id|release_resource
c_func
(paren
r_struct
id|resource
op_star
id|old
)paren
(brace
r_int
id|retval
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|retval
op_assign
id|__release_resource
c_func
(paren
id|old
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|release_resource
id|EXPORT_SYMBOL
c_func
(paren
id|release_resource
)paren
suffix:semicolon
multiline_comment|/*&n; * Find empty slot in the resource tree given range and alignment.&n; */
DECL|function|find_resource
r_static
r_int
id|find_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
comma
r_int
r_int
id|size
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
comma
r_int
r_int
id|align
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
(brace
r_struct
id|resource
op_star
id|this
op_assign
id|root-&gt;child
suffix:semicolon
r_new
op_member_access_from_pointer
id|start
op_assign
id|root-&gt;start
suffix:semicolon
multiline_comment|/*&n;&t; * Skip past an allocated resource that starts at 0, since the assignment&n;&t; * of this-&gt;start - 1 to new-&gt;end below would cause an underflow.&n;&t; */
r_if
c_cond
(paren
id|this
op_logical_and
id|this-&gt;start
op_eq
l_int|0
)paren
(brace
r_new
op_member_access_from_pointer
id|start
op_assign
id|this-&gt;end
op_plus
l_int|1
suffix:semicolon
id|this
op_assign
id|this-&gt;sibling
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|this
)paren
r_new
op_member_access_from_pointer
id|end
op_assign
id|this-&gt;start
op_minus
l_int|1
suffix:semicolon
r_else
r_new
op_member_access_from_pointer
id|end
op_assign
id|root-&gt;end
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|start
OL
id|min
)paren
r_new
op_member_access_from_pointer
id|start
op_assign
id|min
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|end
OG
id|max
)paren
r_new
op_member_access_from_pointer
id|end
op_assign
id|max
suffix:semicolon
r_new
op_member_access_from_pointer
id|start
op_assign
(paren
r_new
op_member_access_from_pointer
id|start
op_plus
id|align
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|align
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alignf
)paren
id|alignf
c_func
(paren
id|alignf_data
comma
r_new
comma
id|size
comma
id|align
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|start
OL
r_new
op_member_access_from_pointer
id|end
op_logical_and
r_new
op_member_access_from_pointer
id|end
op_minus
r_new
op_member_access_from_pointer
id|start
op_plus
l_int|1
op_ge
id|size
)paren
(brace
r_new
op_member_access_from_pointer
id|end
op_assign
r_new
op_member_access_from_pointer
id|start
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|this
)paren
r_break
suffix:semicolon
r_new
op_member_access_from_pointer
id|start
op_assign
id|this-&gt;end
op_plus
l_int|1
suffix:semicolon
id|this
op_assign
id|this-&gt;sibling
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate empty slot in the resource tree given range and alignment.&n; */
DECL|function|allocate_resource
r_int
id|allocate_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
comma
r_int
r_int
id|size
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
comma
r_int
r_int
id|align
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
(brace
r_int
id|err
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|err
op_assign
id|find_resource
c_func
(paren
id|root
comma
r_new
comma
id|size
comma
id|min
comma
id|max
comma
id|align
comma
id|alignf
comma
id|alignf_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
op_logical_and
id|__request_resource
c_func
(paren
id|root
comma
r_new
)paren
)paren
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|allocate_resource
id|EXPORT_SYMBOL
c_func
(paren
id|allocate_resource
)paren
suffix:semicolon
multiline_comment|/**&n; * insert_resource - Inserts a resource in the resource tree&n; * @parent: parent of the new resource&n; * @new: new resource to insert&n; *&n; * Returns 0 on success, -EBUSY if the resource can&squot;t be inserted.&n; *&n; * This function is equivalent of request_resource when no conflict&n; * happens. If a conflict happens, and the conflicting resources&n; * entirely fit within the range of the new resource, then the new&n; * resource is inserted and the conflicting resources become childs of&n; * the new resource.  Otherwise the new resource becomes the child of&n; * the conflicting resource&n; */
DECL|function|insert_resource
r_int
id|insert_resource
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_struct
id|resource
op_star
r_new
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|resource
op_star
id|first
comma
op_star
id|next
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|begin
suffix:colon
id|first
op_assign
id|__request_resource
c_func
(paren
id|parent
comma
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
r_goto
id|out
suffix:semicolon
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|first
op_eq
id|parent
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|first
suffix:semicolon
id|next-&gt;sibling
suffix:semicolon
id|next
op_assign
id|next-&gt;sibling
)paren
r_if
c_cond
(paren
id|next-&gt;sibling-&gt;start
OG
r_new
op_member_access_from_pointer
id|end
)paren
r_break
suffix:semicolon
multiline_comment|/* existing resource overlaps end of new resource */
r_if
c_cond
(paren
id|next-&gt;end
OG
r_new
op_member_access_from_pointer
id|end
)paren
(brace
id|parent
op_assign
id|next
suffix:semicolon
r_goto
id|begin
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
r_new
op_member_access_from_pointer
id|parent
op_assign
id|parent
suffix:semicolon
r_new
op_member_access_from_pointer
id|sibling
op_assign
id|next-&gt;sibling
suffix:semicolon
r_new
op_member_access_from_pointer
id|child
op_assign
id|first
suffix:semicolon
id|next-&gt;sibling
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|first
suffix:semicolon
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;sibling
)paren
id|next-&gt;parent
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
id|parent-&gt;child
op_eq
id|first
)paren
(brace
id|parent-&gt;child
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
id|next
op_assign
id|parent-&gt;child
suffix:semicolon
r_while
c_loop
(paren
id|next-&gt;sibling
op_ne
id|first
)paren
id|next
op_assign
id|next-&gt;sibling
suffix:semicolon
id|next-&gt;sibling
op_assign
r_new
suffix:semicolon
)brace
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|insert_resource
id|EXPORT_SYMBOL
c_func
(paren
id|insert_resource
)paren
suffix:semicolon
multiline_comment|/*&n; * Given an existing resource, change its start and size to match the&n; * arguments.  Returns -EBUSY if it can&squot;t fit.  Existing children of&n; * the resource are assumed to be immutable.&n; */
DECL|function|adjust_resource
r_int
id|adjust_resource
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|resource
op_star
id|tmp
comma
op_star
id|parent
op_assign
id|res-&gt;parent
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|start
OL
id|parent-&gt;start
)paren
op_logical_or
(paren
id|end
OG
id|parent-&gt;end
)paren
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|res-&gt;child
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;sibling
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp-&gt;start
OL
id|start
)paren
op_logical_or
(paren
id|tmp-&gt;end
OG
id|end
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res-&gt;sibling
op_logical_and
(paren
id|res-&gt;sibling-&gt;start
op_le
id|end
)paren
)paren
r_goto
id|out
suffix:semicolon
id|tmp
op_assign
id|parent-&gt;child
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|res
)paren
(brace
r_while
c_loop
(paren
id|tmp-&gt;sibling
op_ne
id|res
)paren
id|tmp
op_assign
id|tmp-&gt;sibling
suffix:semicolon
r_if
c_cond
(paren
id|start
op_le
id|tmp-&gt;end
)paren
r_goto
id|out
suffix:semicolon
)brace
id|res-&gt;start
op_assign
id|start
suffix:semicolon
id|res-&gt;end
op_assign
id|end
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|adjust_resource
id|EXPORT_SYMBOL
c_func
(paren
id|adjust_resource
)paren
suffix:semicolon
multiline_comment|/*&n; * This is compatibility stuff for IO resources.&n; *&n; * Note how this, unlike the above, knows about&n; * the IO flag meanings (busy etc).&n; *&n; * Request-region creates a new busy region.&n; *&n; * Check-region returns non-zero if the area is already busy&n; *&n; * Release-region releases a matching busy region.&n; */
DECL|function|__request_region
r_struct
id|resource
op_star
id|__request_region
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
id|res-&gt;name
op_assign
id|name
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
id|res-&gt;end
op_assign
id|start
op_plus
id|n
op_minus
l_int|1
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_BUSY
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|resource
op_star
id|conflict
suffix:semicolon
id|conflict
op_assign
id|__request_resource
c_func
(paren
id|parent
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conflict
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|conflict
op_ne
id|parent
)paren
(brace
id|parent
op_assign
id|conflict
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|conflict-&gt;flags
op_amp
id|IORESOURCE_BUSY
)paren
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/* Uhhuh, that didn&squot;t work out.. */
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
id|res
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|variable|__request_region
id|EXPORT_SYMBOL
c_func
(paren
id|__request_region
)paren
suffix:semicolon
DECL|function|__check_region
r_int
id|__deprecated
id|__check_region
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|res
op_assign
id|__request_region
c_func
(paren
id|parent
comma
id|start
comma
id|n
comma
l_string|&quot;check-region&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__check_region
id|EXPORT_SYMBOL
c_func
(paren
id|__check_region
)paren
suffix:semicolon
DECL|function|__release_region
r_void
id|__release_region
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|resource
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
id|p
op_assign
op_amp
id|parent-&gt;child
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|n
op_minus
l_int|1
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;start
op_le
id|start
op_logical_and
id|res-&gt;end
op_ge
id|end
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_BUSY
)paren
)paren
(brace
id|p
op_assign
op_amp
id|res-&gt;child
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res-&gt;start
op_ne
id|start
op_logical_or
id|res-&gt;end
op_ne
id|end
)paren
r_break
suffix:semicolon
op_star
id|p
op_assign
id|res-&gt;sibling
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|res-&gt;sibling
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Trying to free nonexistent resource &lt;%08lx-%08lx&gt;&bslash;n&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
DECL|variable|__release_region
id|EXPORT_SYMBOL
c_func
(paren
id|__release_region
)paren
suffix:semicolon
multiline_comment|/*&n; * Called from init/main.c to reserve IO ports.&n; */
DECL|macro|MAXRESERVE
mdefine_line|#define MAXRESERVE 4
DECL|function|reserve_setup
r_static
r_int
id|__init
id|reserve_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_static
r_int
id|reserved
suffix:semicolon
r_static
r_struct
id|resource
id|reserve
(braket
id|MAXRESERVE
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|io_start
comma
id|io_num
suffix:semicolon
r_int
id|x
op_assign
id|reserved
suffix:semicolon
r_if
c_cond
(paren
id|get_option
(paren
op_amp
id|str
comma
op_amp
id|io_start
)paren
op_ne
l_int|2
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|get_option
(paren
op_amp
id|str
comma
op_amp
id|io_num
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|x
OL
id|MAXRESERVE
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|reserve
op_plus
id|x
suffix:semicolon
id|res-&gt;name
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
id|res-&gt;start
op_assign
id|io_start
suffix:semicolon
id|res-&gt;end
op_assign
id|io_start
op_plus
id|io_num
op_minus
l_int|1
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_BUSY
suffix:semicolon
id|res-&gt;child
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
id|res-&gt;start
op_ge
l_int|0x10000
ques
c_cond
op_amp
id|iomem_resource
suffix:colon
op_amp
id|ioport_resource
comma
id|res
)paren
op_eq
l_int|0
)paren
id|reserved
op_assign
id|x
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;reserve=&quot;
comma
id|reserve_setup
)paren
suffix:semicolon
eof
