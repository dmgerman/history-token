multiline_comment|/*&n; *&t;$Id: proc.c,v 1.13 1998/05/12 07:36:07 mj Exp $&n; *&n; *&t;Procfs interface for the PCI bus.&n; *&n; *&t;Copyright (c) 1997--1999 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|variable|proc_initialized
r_static
r_int
id|proc_initialized
suffix:semicolon
multiline_comment|/* = 0 */
r_static
id|loff_t
DECL|function|proc_bus_pci_lseek
id|proc_bus_pci_lseek
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
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
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
id|inode-&gt;i_size
op_plus
id|off
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
template_param
id|inode-&gt;i_size
)paren
r_new
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
id|file-&gt;f_pos
op_assign
r_new
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|proc_bus_pci_read
id|proc_bus_pci_read
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
r_const
r_struct
id|inode
op_star
id|ino
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_const
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|ino
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
r_int
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
r_int
id|cnt
comma
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * Normal users can read only the standardized portion of the&n;&t; * configuration space as several chips lock up when trying to read&n;&t; * undefined locations (think of Intel PIIX4 as a typical example).&n;&t; */
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
id|size
op_assign
id|dev-&gt;cfg_size
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
id|size
op_assign
l_int|128
suffix:semicolon
r_else
id|size
op_assign
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|size
)paren
id|nbytes
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|nbytes
OG
id|size
)paren
id|nbytes
op_assign
id|size
op_minus
id|pos
suffix:semicolon
id|cnt
op_assign
id|nbytes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|cnt
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|1
)paren
op_logical_and
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|3
)paren
op_logical_and
id|cnt
OG
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|cpu_to_le16
c_func
(paren
id|val
)paren
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cnt
op_ge
l_int|4
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|val
)paren
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|4
suffix:semicolon
id|pos
op_add_assign
l_int|4
suffix:semicolon
id|cnt
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
op_ge
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|cpu_to_le16
c_func
(paren
id|val
)paren
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|proc_bus_pci_write
id|proc_bus_pci_write
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
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_const
r_struct
id|inode
op_star
id|ino
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_const
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|ino
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
id|size
op_assign
id|dev-&gt;cfg_size
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|size
)paren
id|nbytes
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|nbytes
OG
id|size
)paren
id|nbytes
op_assign
id|size
op_minus
id|pos
suffix:semicolon
id|cnt
op_assign
id|nbytes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|cnt
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|1
)paren
op_logical_and
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|pos
comma
id|val
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|3
)paren
op_logical_and
id|cnt
OG
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|pos
comma
id|le16_to_cpu
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cnt
op_ge
l_int|4
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|pos
comma
id|le32_to_cpu
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|4
suffix:semicolon
id|pos
op_add_assign
l_int|4
suffix:semicolon
id|cnt
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
op_ge
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|pos
comma
id|le16_to_cpu
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|pos
comma
id|val
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
DECL|struct|pci_filp_private
r_struct
id|pci_filp_private
(brace
DECL|member|mmap_state
r_enum
id|pci_mmap_state
id|mmap_state
suffix:semicolon
DECL|member|write_combine
r_int
id|write_combine
suffix:semicolon
)brace
suffix:semicolon
DECL|function|proc_bus_pci_ioctl
r_static
r_int
id|proc_bus_pci_ioctl
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
r_const
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
macro_line|#ifdef HAVE_PCI_MMAP
r_struct
id|pci_filp_private
op_star
id|fpriv
op_assign
id|file-&gt;private_data
suffix:semicolon
macro_line|#endif /* HAVE_PCI_MMAP */
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|PCIIOC_CONTROLLER
suffix:colon
id|ret
op_assign
id|pci_domain_nr
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef HAVE_PCI_MMAP
r_case
id|PCIIOC_MMAP_IS_IO
suffix:colon
id|fpriv-&gt;mmap_state
op_assign
id|pci_mmap_io
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCIIOC_MMAP_IS_MEM
suffix:colon
id|fpriv-&gt;mmap_state
op_assign
id|pci_mmap_mem
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCIIOC_WRITE_COMBINE
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|fpriv-&gt;write_combine
op_assign
l_int|1
suffix:semicolon
r_else
id|fpriv-&gt;write_combine
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* HAVE_PCI_MMAP */
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef HAVE_PCI_MMAP
DECL|function|proc_bus_pci_mmap
r_static
r_int
id|proc_bus_pci_mmap
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
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_const
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
r_struct
id|pci_filp_private
op_star
id|fpriv
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|ret
op_assign
id|pci_mmap_page_range
c_func
(paren
id|dev
comma
id|vma
comma
id|fpriv-&gt;mmap_state
comma
id|fpriv-&gt;write_combine
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_bus_pci_open
r_static
r_int
id|proc_bus_pci_open
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
id|pci_filp_private
op_star
id|fpriv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fpriv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpriv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|fpriv-&gt;mmap_state
op_assign
id|pci_mmap_io
suffix:semicolon
id|fpriv-&gt;write_combine
op_assign
l_int|0
suffix:semicolon
id|file-&gt;private_data
op_assign
id|fpriv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_bus_pci_release
r_static
r_int
id|proc_bus_pci_release
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
id|kfree
c_func
(paren
id|file-&gt;private_data
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
macro_line|#endif /* HAVE_PCI_MMAP */
DECL|variable|proc_bus_pci_operations
r_static
r_struct
id|file_operations
id|proc_bus_pci_operations
op_assign
(brace
dot
id|llseek
op_assign
id|proc_bus_pci_lseek
comma
dot
id|read
op_assign
id|proc_bus_pci_read
comma
dot
id|write
op_assign
id|proc_bus_pci_write
comma
dot
id|ioctl
op_assign
id|proc_bus_pci_ioctl
comma
macro_line|#ifdef HAVE_PCI_MMAP
dot
id|open
op_assign
id|proc_bus_pci_open
comma
dot
id|release
op_assign
id|proc_bus_pci_release
comma
dot
id|mmap
op_assign
id|proc_bus_pci_mmap
comma
macro_line|#ifdef HAVE_ARCH_PCI_GET_UNMAPPED_AREA
dot
id|get_unmapped_area
op_assign
id|get_pci_unmapped_area
comma
macro_line|#endif /* HAVE_ARCH_PCI_GET_UNMAPPED_AREA */
macro_line|#endif /* HAVE_PCI_MMAP */
)brace
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|macro|LONG_FORMAT
mdefine_line|#define LONG_FORMAT &quot;&bslash;t%08lx&quot;
macro_line|#else
DECL|macro|LONG_FORMAT
mdefine_line|#define LONG_FORMAT &quot;&bslash;t%16lx&quot;
macro_line|#endif
multiline_comment|/* iterator */
DECL|function|pci_seq_start
r_static
r_void
op_star
id|pci_seq_start
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
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|loff_t
id|n
op_assign
op_star
id|pos
suffix:semicolon
id|dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_goto
m_exit
suffix:semicolon
)brace
m_exit
suffix:colon
r_return
id|dev
suffix:semicolon
)brace
DECL|function|pci_seq_next
r_static
r_void
op_star
id|pci_seq_next
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
id|pci_dev
op_star
id|dev
op_assign
id|v
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
id|dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|function|pci_seq_stop
r_static
r_void
id|pci_seq_stop
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
r_if
c_cond
(paren
id|v
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|v
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_device
r_static
r_int
id|show_device
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
r_const
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|v
suffix:semicolon
r_const
r_struct
id|pci_driver
op_star
id|drv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|drv
op_assign
id|pci_dev_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%02x%02x&bslash;t%04x%04x&bslash;t%x&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Here should be 7 and not PCI_NUM_RESOURCES as we need to preserve compatibility */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
id|LONG_FORMAT
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_or
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|PCI_REGION_FLAG_MASK
)paren
)paren
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
id|LONG_FORMAT
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
OL
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
ques
c_cond
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_minus
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_plus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|m
comma
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s&quot;
comma
id|drv-&gt;name
)paren
suffix:semicolon
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
DECL|variable|proc_bus_pci_devices_op
r_static
r_struct
id|seq_operations
id|proc_bus_pci_devices_op
op_assign
(brace
dot
id|start
op_assign
id|pci_seq_start
comma
dot
id|next
op_assign
id|pci_seq_next
comma
dot
id|stop
op_assign
id|pci_seq_stop
comma
dot
id|show
op_assign
id|show_device
)brace
suffix:semicolon
DECL|variable|proc_bus_pci_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_bus_pci_dir
suffix:semicolon
DECL|function|pci_proc_attach_device
r_int
id|pci_proc_attach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
comma
op_star
id|e
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_initialized
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|de
op_assign
id|bus-&gt;procdir
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_name_bus
c_func
(paren
id|name
comma
id|bus
)paren
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
id|de
op_assign
id|bus-&gt;procdir
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|proc_bus_pci_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x.%x&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|e
op_assign
id|dev-&gt;procent
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|e-&gt;proc_fops
op_assign
op_amp
id|proc_bus_pci_operations
suffix:semicolon
id|e-&gt;data
op_assign
id|dev
suffix:semicolon
id|e-&gt;size
op_assign
id|dev-&gt;cfg_size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_detach_device
r_int
id|pci_proc_detach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
r_if
c_cond
(paren
(paren
id|e
op_assign
id|dev-&gt;procent
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|e-&gt;count
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|e-&gt;name
comma
id|dev-&gt;bus-&gt;procdir
)paren
suffix:semicolon
id|dev-&gt;procent
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_attach_bus
r_int
id|pci_proc_attach_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|de
op_assign
id|bus-&gt;procdir
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_initialized
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
(brace
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
id|de
op_assign
id|bus-&gt;procdir
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|proc_bus_pci_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_detach_bus
r_int
id|pci_proc_detach_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|de
op_assign
id|bus-&gt;procdir
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
id|remove_proc_entry
c_func
(paren
id|de-&gt;name
comma
id|proc_bus_pci_dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI_LEGACY_PROC
multiline_comment|/*&n; *  Backward compatible /proc/pci interface.&n; */
multiline_comment|/*&n; * Convert some of the configuration space registers of the device at&n; * address (bus,devfn) into a string (possibly several lines each).&n; * The configuration string is stored starting at buf[len].  If the&n; * string would exceed the size of the buffer (SIZE), 0 is returned.&n; */
DECL|function|show_dev_config
r_static
r_int
id|show_dev_config
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
id|pci_dev
op_star
id|dev
op_assign
id|v
suffix:semicolon
r_struct
id|pci_dev
op_star
id|first_dev
suffix:semicolon
r_struct
id|pci_driver
op_star
id|drv
suffix:semicolon
id|u32
id|class_rev
suffix:semicolon
r_int
r_char
id|latency
comma
id|min_gnt
comma
id|max_lat
comma
op_star
r_class
suffix:semicolon
r_int
id|reg
suffix:semicolon
id|first_dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
id|first_dev
)paren
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;PCI devices found:&bslash;n&quot;
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|first_dev
)paren
suffix:semicolon
id|drv
op_assign
id|pci_dev_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|class_rev
)paren
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|latency
)paren
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_MIN_GNT
comma
op_amp
id|min_gnt
)paren
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_MAX_LAT
comma
op_amp
id|max_lat
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;  Bus %2d, device %3d, function %2d:&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_class
op_assign
id|pci_class_name
c_func
(paren
id|class_rev
op_rshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
r_class
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;    %s&quot;
comma
r_class
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;    Class %04x&quot;
comma
id|class_rev
op_rshift
l_int|16
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_NAMES
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;: %s&quot;
comma
id|dev-&gt;pretty_name
)paren
suffix:semicolon
macro_line|#else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;: PCI device %04x:%04x&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; (rev %d).&bslash;n&quot;
comma
id|class_rev
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;      IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|latency
op_logical_or
id|min_gnt
op_logical_or
id|max_lat
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;      Master Capable.  &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|latency
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Latency=%d.  &quot;
comma
id|latency
)paren
suffix:semicolon
r_else
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;No bursts.  &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|min_gnt
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Min Gnt=%d.&quot;
comma
id|min_gnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_lat
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Max Lat=%d.&quot;
comma
id|max_lat
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|m
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|reg
op_assign
l_int|0
suffix:semicolon
id|reg
OL
l_int|6
suffix:semicolon
id|reg
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|dev-&gt;resource
op_plus
id|reg
suffix:semicolon
r_int
r_int
id|base
comma
id|end
comma
id|flags
suffix:semicolon
id|base
op_assign
id|res-&gt;start
suffix:semicolon
id|end
op_assign
id|res-&gt;end
suffix:semicolon
id|flags
op_assign
id|res-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;      I/O at 0x%lx [0x%lx].&bslash;n&quot;
comma
id|base
comma
id|end
)paren
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
op_star
id|pref
comma
op_star
id|type
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_MEM_PREFETCH
)paren
id|pref
op_assign
l_string|&quot;P&quot;
suffix:semicolon
r_else
id|pref
op_assign
l_string|&quot;Non-p&quot;
suffix:semicolon
r_switch
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
(brace
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_32
suffix:colon
id|type
op_assign
l_string|&quot;32 bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_1M
suffix:colon
id|type
op_assign
l_string|&quot;20 bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_64
suffix:colon
id|type
op_assign
l_string|&quot;64 bit&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;      %srefetchable %s memory at &quot;
l_string|&quot;0x%lx [0x%lx].&bslash;n&quot;
comma
id|pref
comma
id|type
comma
id|base
comma
id|end
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_pci_op
r_static
r_struct
id|seq_operations
id|proc_pci_op
op_assign
(brace
dot
id|start
op_assign
id|pci_seq_start
comma
dot
id|next
op_assign
id|pci_seq_next
comma
dot
id|stop
op_assign
id|pci_seq_stop
comma
dot
id|show
op_assign
id|show_dev_config
)brace
suffix:semicolon
DECL|function|proc_pci_open
r_static
r_int
id|proc_pci_open
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
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|proc_pci_op
)paren
suffix:semicolon
)brace
DECL|variable|proc_pci_operations
r_static
r_struct
id|file_operations
id|proc_pci_operations
op_assign
(brace
dot
id|open
op_assign
id|proc_pci_open
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
DECL|function|legacy_proc_init
r_static
r_void
id|legacy_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;pci&quot;
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
id|proc_pci_operations
suffix:semicolon
)brace
macro_line|#else
DECL|function|legacy_proc_init
r_static
r_void
id|legacy_proc_init
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PCI_LEGACY_PROC */
DECL|function|proc_bus_pci_dev_open
r_static
r_int
id|proc_bus_pci_dev_open
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
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|proc_bus_pci_devices_op
)paren
suffix:semicolon
)brace
DECL|variable|proc_bus_pci_dev_operations
r_static
r_struct
id|file_operations
id|proc_bus_pci_dev_operations
op_assign
(brace
dot
id|open
op_assign
id|proc_bus_pci_dev_open
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
DECL|function|pci_proc_init
r_static
r_int
id|__init
id|pci_proc_init
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|proc_bus_pci_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;pci&quot;
comma
id|proc_bus
)paren
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;devices&quot;
comma
l_int|0
comma
id|proc_bus_pci_dir
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
id|proc_bus_pci_dev_operations
suffix:semicolon
id|proc_initialized
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pci_proc_attach_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|legacy_proc_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_proc_init
id|__initcall
c_func
(paren
id|pci_proc_init
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG
DECL|variable|pci_proc_attach_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_proc_attach_device
)paren
suffix:semicolon
DECL|variable|pci_proc_attach_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_proc_attach_bus
)paren
suffix:semicolon
DECL|variable|pci_proc_detach_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_proc_detach_bus
)paren
suffix:semicolon
macro_line|#endif
eof
