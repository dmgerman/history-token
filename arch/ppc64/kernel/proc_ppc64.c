multiline_comment|/*&n; * arch/ppc64/kernel/proc_ppc64.c&n; *&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
r_static
id|loff_t
id|page_map_seek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|off
comma
r_int
id|whence
)paren
suffix:semicolon
r_static
id|ssize_t
id|page_map_read
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
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
r_int
id|page_map_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
DECL|variable|page_map_fops
r_static
r_struct
id|file_operations
id|page_map_fops
op_assign
(brace
dot
id|llseek
op_assign
id|page_map_seek
comma
dot
id|read
op_assign
id|page_map_read
comma
dot
id|mmap
op_assign
id|page_map_mmap
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* routines for /proc/ppc64/ofdt */
r_static
id|ssize_t
id|ofdt_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|proc_ppc64_create_ofdt
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|do_remove_node
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|do_add_node
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|release_prop_list
c_func
(paren
r_const
r_struct
id|property
op_star
)paren
suffix:semicolon
r_static
r_struct
id|property
op_star
id|new_property
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_int
comma
r_const
r_int
r_char
op_star
comma
r_struct
id|property
op_star
)paren
suffix:semicolon
r_static
r_char
op_star
id|parse_next_property
c_func
(paren
r_char
op_star
comma
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
op_star
comma
r_int
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|variable|ofdt_fops
r_static
r_struct
id|file_operations
id|ofdt_fops
op_assign
(brace
dot
id|write
op_assign
id|ofdt_write
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * NOTE: since paca data is always in flux the values will never be a&n; * consistant set.&n; */
DECL|function|proc_create_paca
r_static
r_void
id|__init
id|proc_create_paca
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
r_int
id|num
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_struct
id|paca_struct
op_star
id|lpaca
op_assign
id|paca
op_plus
id|num
suffix:semicolon
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%02x&quot;
comma
id|num
)paren
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
id|buf
comma
id|S_IRUSR
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
id|lpaca
suffix:semicolon
id|ent-&gt;size
op_assign
l_int|4096
suffix:semicolon
id|ent-&gt;proc_fops
op_assign
op_amp
id|page_map_fops
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Create the ppc64 and ppc64/rtas directories early. This allows us to&n; * assume that they have been previously created in drivers.&n; */
DECL|function|proc_ppc64_create
r_static
r_int
id|__init
id|proc_ppc64_create
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|root
suffix:semicolon
id|root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;ppc64&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_PSERIES
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_mkdir
c_func
(paren
l_string|&quot;rtas&quot;
comma
id|root
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_symlink
c_func
(paren
l_string|&quot;rtas&quot;
comma
l_int|NULL
comma
l_string|&quot;ppc64/rtas&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_ppc64_create
id|core_initcall
c_func
(paren
id|proc_ppc64_create
)paren
suffix:semicolon
DECL|function|proc_ppc64_init
r_static
r_int
id|__init
id|proc_ppc64_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|pde
suffix:semicolon
id|pde
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/naca&quot;
comma
id|S_IRUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pde
)paren
r_return
l_int|1
suffix:semicolon
id|pde-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|pde-&gt;data
op_assign
id|naca
suffix:semicolon
id|pde-&gt;size
op_assign
l_int|4096
suffix:semicolon
id|pde-&gt;proc_fops
op_assign
op_amp
id|page_map_fops
suffix:semicolon
id|pde
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/systemcfg&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pde
)paren
r_return
l_int|1
suffix:semicolon
id|pde-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|pde-&gt;data
op_assign
id|systemcfg
suffix:semicolon
id|pde-&gt;size
op_assign
l_int|4096
suffix:semicolon
id|pde-&gt;proc_fops
op_assign
op_amp
id|page_map_fops
suffix:semicolon
multiline_comment|/* /proc/ppc64/paca/XX -- raw paca contents.  Only readable to root */
id|pde
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;ppc64/paca&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pde
)paren
r_return
l_int|1
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
id|proc_create_paca
c_func
(paren
id|pde
comma
id|i
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_PSERIES
r_if
c_cond
(paren
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_PSERIES
)paren
)paren
id|proc_ppc64_create_ofdt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_ppc64_init
id|__initcall
c_func
(paren
id|proc_ppc64_init
)paren
suffix:semicolon
DECL|function|page_map_seek
r_static
id|loff_t
id|page_map_seek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|off
comma
r_int
id|whence
)paren
(brace
id|loff_t
r_new
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|whence
)paren
(brace
r_case
l_int|0
suffix:colon
r_new
op_assign
id|off
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_new
op_assign
id|file-&gt;f_pos
op_plus
id|off
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_new
op_assign
id|dp-&gt;size
op_plus
id|off
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
template_param
id|dp-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
(paren
id|file-&gt;f_pos
op_assign
r_new
)paren
suffix:semicolon
)brace
DECL|function|page_map_read
r_static
id|ssize_t
id|page_map_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
id|simple_read_from_buffer
c_func
(paren
id|buf
comma
id|nbytes
comma
id|ppos
comma
id|dp-&gt;data
comma
id|dp-&gt;size
)paren
suffix:semicolon
)brace
DECL|function|page_map_mmap
r_static
r_int
id|page_map_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_SHM
op_or
id|VM_LOCKED
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
OG
id|dp-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|__pa
c_func
(paren
id|dp-&gt;data
)paren
comma
id|dp-&gt;size
comma
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* create /proc/ppc64/ofdt write-only by root */
DECL|function|proc_ppc64_create_ofdt
r_static
r_void
id|proc_ppc64_create_ofdt
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/ofdt&quot;
comma
id|S_IWUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|ent-&gt;size
op_assign
l_int|0
suffix:semicolon
id|ent-&gt;proc_fops
op_assign
op_amp
id|ofdt_fops
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * ofdt_write - perform operations on the Open Firmware device tree&n; *&n; * @file: not used&n; * @buf: command and arguments&n; * @count: size of the command buffer&n; * @off: not used&n; *&n; * Operations supported at this time are addition and removal of&n; * whole nodes along with their properties.  Operations on individual&n; * properties are not implemented (yet).&n; */
DECL|function|ofdt_write
r_static
id|ssize_t
id|ofdt_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|kbuf
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|kbuf
op_assign
id|kmalloc
c_func
(paren
id|count
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kbuf
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|rv
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|kbuf
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|tmp
op_assign
id|strchr
c_func
(paren
id|kbuf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|rv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
op_star
id|tmp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|kbuf
comma
l_string|&quot;add_node&quot;
)paren
)paren
id|rv
op_assign
id|do_add_node
c_func
(paren
id|tmp
comma
id|count
op_minus
(paren
id|tmp
op_minus
id|kbuf
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|kbuf
comma
l_string|&quot;remove_node&quot;
)paren
)paren
id|rv
op_assign
id|do_remove_node
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_else
id|rv
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|rv
ques
c_cond
id|rv
suffix:colon
id|count
suffix:semicolon
)brace
DECL|function|do_remove_node
r_static
r_int
id|do_remove_node
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
id|rv
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node
op_assign
id|of_find_node_by_path
c_func
(paren
id|buf
)paren
)paren
)paren
id|rv
op_assign
id|of_remove_node
c_func
(paren
id|node
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|do_add_node
r_static
r_int
id|do_add_node
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|bufsize
)paren
(brace
r_char
op_star
id|path
comma
op_star
id|end
comma
op_star
id|name
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_struct
id|property
op_star
id|prop
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
op_star
id|value
suffix:semicolon
r_int
id|length
comma
id|rv
op_assign
l_int|0
suffix:semicolon
id|end
op_assign
id|buf
op_plus
id|bufsize
suffix:semicolon
id|path
op_assign
id|buf
suffix:semicolon
id|buf
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|buf
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|buf
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|np
op_assign
id|of_find_node_by_path
c_func
(paren
id|path
)paren
)paren
)paren
(brace
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* rv = build_prop_list(tmp, bufsize - (tmp - buf), &amp;proplist); */
r_while
c_loop
(paren
id|buf
OL
id|end
op_logical_and
(paren
id|buf
op_assign
id|parse_next_property
c_func
(paren
id|buf
comma
id|end
comma
op_amp
id|name
comma
op_amp
id|length
comma
op_amp
id|value
)paren
)paren
)paren
(brace
r_struct
id|property
op_star
id|last
op_assign
id|prop
suffix:semicolon
id|prop
op_assign
id|new_property
c_func
(paren
id|name
comma
id|length
comma
id|value
comma
id|last
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prop
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|prop
op_assign
id|last
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|rv
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|rv
op_assign
id|of_add_node
c_func
(paren
id|path
comma
id|prop
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|rv
)paren
id|release_prop_list
c_func
(paren
id|prop
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|new_property
r_static
r_struct
id|property
op_star
id|new_property
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_int
id|length
comma
r_const
r_int
r_char
op_star
id|value
comma
r_struct
id|property
op_star
id|last
)paren
(brace
r_struct
id|property
op_star
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_member_access_from_pointer
id|name
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|cleanup
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
r_new
op_member_access_from_pointer
id|value
op_assign
id|kmalloc
c_func
(paren
id|length
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|cleanup
suffix:semicolon
id|strcpy
c_func
(paren
r_new
op_member_access_from_pointer
id|name
comma
id|name
)paren
suffix:semicolon
id|memcpy
c_func
(paren
r_new
op_member_access_from_pointer
id|value
comma
id|value
comma
id|length
)paren
suffix:semicolon
op_star
(paren
(paren
(paren
r_char
op_star
)paren
r_new
op_member_access_from_pointer
id|value
)paren
op_plus
id|length
)paren
op_assign
l_int|0
suffix:semicolon
r_new
op_member_access_from_pointer
id|length
op_assign
id|length
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
id|last
suffix:semicolon
r_return
r_new
suffix:semicolon
id|cleanup
suffix:colon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|name
)paren
id|kfree
c_func
(paren
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|value
)paren
id|kfree
c_func
(paren
r_new
op_member_access_from_pointer
id|value
)paren
suffix:semicolon
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * parse_next_property - process the next property from raw input buffer&n; * @buf: input buffer, must be nul-terminated&n; * @end: end of the input buffer + 1, for validation&n; * @name: return value; set to property name in buf&n; * @length: return value; set to length of value&n; * @value: return value; set to the property value in buf&n; *&n; * Note that the caller must make copies of the name and value returned,&n; * this function does no allocation or copying of the data.  Return value&n; * is set to the next name in buf, or NULL on error.&n; */
DECL|function|parse_next_property
r_static
r_char
op_star
id|parse_next_property
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|end
comma
r_char
op_star
op_star
id|name
comma
r_int
op_star
id|length
comma
r_int
r_char
op_star
op_star
id|value
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
op_star
id|name
op_assign
id|buf
suffix:semicolon
id|tmp
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;property parse failed in %s at line %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|tmp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|tmp
op_ge
id|end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;property parse failed in %s at line %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* now we&squot;re on the length */
op_star
id|length
op_assign
op_minus
l_int|1
suffix:semicolon
op_star
id|length
op_assign
id|simple_strtoul
c_func
(paren
id|tmp
comma
op_amp
id|tmp
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|length
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;property parse failed in %s at line %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|tmp
op_ne
l_char|&squot; &squot;
op_logical_or
op_increment
id|tmp
op_ge
id|end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;property parse failed in %s at line %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* now we&squot;re on the value */
op_star
id|value
op_assign
id|tmp
suffix:semicolon
id|tmp
op_add_assign
op_star
id|length
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;property parse failed in %s at line %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tmp
OL
id|end
op_logical_and
op_star
id|tmp
op_ne
l_char|&squot; &squot;
op_logical_and
op_star
id|tmp
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;property parse failed in %s at line %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|tmp
op_increment
suffix:semicolon
multiline_comment|/* and now we should be on the next name, or the end */
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|release_prop_list
r_static
r_void
id|release_prop_list
c_func
(paren
r_const
r_struct
id|property
op_star
id|prop
)paren
(brace
r_struct
id|property
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|prop
suffix:semicolon
id|prop
op_assign
id|next
)paren
(brace
id|next
op_assign
id|prop-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|prop-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|prop-&gt;value
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|prop
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* defined(CONFIG_PPC_PSERIES) */
eof
