multiline_comment|/*&n; * Linux/SPARC PROM Configuration Driver&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; * Copyright (C) 1996 Eddie C. Dost  (ecd@skynet.be)&n; *&n; * This character device driver allows user programs to access the&n; * PROM device tree. It is compatible with the SunOS /dev/openprom&n; * driver and the NetBSD /dev/openprom driver. The SunOS eeprom&n; * utility works without any modifications.&n; *&n; * The driver uses a minor number under the misc device major. The&n; * file read/write mode determines the type of access to the PROM.&n; * Interrupts are disabled whenever the driver calls into the PROM for&n; * sanity&squot;s sake.&n; */
multiline_comment|/* This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; */
DECL|macro|PROMLIB_INTERNAL
mdefine_line|#define PROMLIB_INTERNAL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/openpromio.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#endif
multiline_comment|/* Private data kept by the driver for each descriptor. */
DECL|struct|openprom_private_data
r_typedef
r_struct
id|openprom_private_data
(brace
DECL|member|current_node
r_int
id|current_node
suffix:semicolon
multiline_comment|/* Current node for SunOS ioctls. */
DECL|member|lastnode
r_int
id|lastnode
suffix:semicolon
multiline_comment|/* Last valid node used by BSD ioctls. */
DECL|typedef|DATA
)brace
id|DATA
suffix:semicolon
multiline_comment|/* ID of the PROM node containing all of the EEPROM options. */
DECL|variable|options_node
r_static
r_int
id|options_node
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Copy an openpromio structure into kernel space from user space.&n; * This routine does error checking to make sure that all memory&n; * accesses are within bounds. A pointer to the allocated openpromio&n; * structure will be placed in &quot;*opp_p&quot;. Return value is the length&n; * of the user supplied buffer.&n; */
DECL|function|copyin
r_static
r_int
id|copyin
c_func
(paren
r_struct
id|openpromio
op_star
id|info
comma
r_struct
id|openpromio
op_star
op_star
id|opp_p
)paren
(brace
r_int
id|bufsize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_or
op_logical_neg
id|opp_p
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|bufsize
comma
op_amp
id|info-&gt;oprom_size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|bufsize
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* If the bufsize is too large, just limit it.&n;&t; * Fix from Jason Rappleye.&n;&t; */
r_if
c_cond
(paren
id|bufsize
OG
id|OPROMMAXPARAM
)paren
id|bufsize
op_assign
id|OPROMMAXPARAM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|opp_p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_plus
id|bufsize
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
op_star
id|opp_p
comma
l_int|0
comma
r_sizeof
(paren
r_int
)paren
op_plus
id|bufsize
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
(paren
op_star
id|opp_p
)paren
op_member_access_from_pointer
id|oprom_array
comma
op_amp
id|info-&gt;oprom_array
comma
id|bufsize
)paren
)paren
(brace
id|kfree
c_func
(paren
op_star
id|opp_p
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|bufsize
suffix:semicolon
)brace
DECL|function|getstrings
r_static
r_int
id|getstrings
c_func
(paren
r_struct
id|openpromio
op_star
id|info
comma
r_struct
id|openpromio
op_star
op_star
id|opp_p
)paren
(brace
r_int
id|n
comma
id|bufsize
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_or
op_logical_neg
id|opp_p
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|opp_p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_plus
id|OPROMMAXPARAM
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
op_star
id|opp_p
comma
l_int|0
comma
r_sizeof
(paren
r_int
)paren
op_plus
id|OPROMMAXPARAM
op_plus
l_int|1
)paren
suffix:semicolon
(paren
op_star
id|opp_p
)paren
op_member_access_from_pointer
id|oprom_size
op_assign
l_int|0
suffix:semicolon
id|n
op_assign
id|bufsize
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|n
OL
l_int|2
)paren
op_logical_and
(paren
id|bufsize
OL
id|OPROMMAXPARAM
)paren
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
op_amp
id|info-&gt;oprom_array
(braket
id|bufsize
)braket
)paren
)paren
(brace
id|kfree
c_func
(paren
op_star
id|opp_p
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|n
op_increment
suffix:semicolon
(paren
op_star
id|opp_p
)paren
op_member_access_from_pointer
id|oprom_array
(braket
id|bufsize
op_increment
)braket
op_assign
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
(brace
id|kfree
c_func
(paren
op_star
id|opp_p
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|bufsize
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy an openpromio structure in kernel space back to user space.&n; */
DECL|function|copyout
r_static
r_int
id|copyout
c_func
(paren
r_void
op_star
id|info
comma
r_struct
id|openpromio
op_star
id|opp
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|info
comma
id|opp
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;SunOS and Solaris /dev/openprom ioctl calls.&n; */
DECL|function|openprom_sunos_ioctl
r_static
r_int
id|openprom_sunos_ioctl
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
comma
r_int
id|node
)paren
(brace
id|DATA
op_star
id|data
op_assign
(paren
id|DATA
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_char
id|buffer
(braket
id|OPROMMAXPARAM
op_plus
l_int|1
)braket
comma
op_star
id|buf
suffix:semicolon
r_struct
id|openpromio
op_star
id|opp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|bufsize
comma
id|len
comma
id|error
op_assign
l_int|0
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
r_static
r_int
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|OPROMSETOPT
)paren
id|bufsize
op_assign
id|getstrings
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|opp
)paren
suffix:semicolon
r_else
id|bufsize
op_assign
id|copyin
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|opp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bufsize
OL
l_int|0
)paren
r_return
id|bufsize
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|OPROMGETOPT
suffix:colon
r_case
id|OPROMGETPROP
suffix:colon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproplen
c_func
(paren
id|node
comma
id|opp-&gt;oprom_array
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
op_logical_or
id|len
OG
id|bufsize
)paren
(brace
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
id|opp-&gt;oprom_array
comma
id|buffer
comma
id|bufsize
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|opp-&gt;oprom_array
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
id|opp-&gt;oprom_array
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|opp-&gt;oprom_size
op_assign
id|len
suffix:semicolon
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
r_sizeof
(paren
r_int
)paren
op_plus
id|bufsize
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMNXTOPT
suffix:colon
r_case
id|OPROMNXTPROP
suffix:colon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|buf
op_assign
id|prom_nextprop
c_func
(paren
id|node
comma
id|opp-&gt;oprom_array
comma
id|buffer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
op_logical_or
id|len
op_plus
l_int|1
OG
id|bufsize
)paren
(brace
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|opp-&gt;oprom_array
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|opp-&gt;oprom_array
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|opp-&gt;oprom_size
op_assign
op_increment
id|len
suffix:semicolon
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
r_sizeof
(paren
r_int
)paren
op_plus
id|bufsize
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMSETOPT
suffix:colon
r_case
id|OPROMSETOPT2
suffix:colon
id|buf
op_assign
id|opp-&gt;oprom_array
op_plus
id|strlen
c_func
(paren
id|opp-&gt;oprom_array
)paren
op_plus
l_int|1
suffix:semicolon
id|len
op_assign
id|opp-&gt;oprom_array
op_plus
id|bufsize
op_minus
id|buf
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|error
op_assign
id|prom_setprop
c_func
(paren
id|options_node
comma
id|opp-&gt;oprom_array
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMNEXT
suffix:colon
r_case
id|OPROMCHILD
suffix:colon
r_case
id|OPROMSETCUR
suffix:colon
r_if
c_cond
(paren
id|bufsize
OL
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|node
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|opp-&gt;oprom_array
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|OPROMNEXT
suffix:colon
id|node
op_assign
id|__prom_getsibling
c_func
(paren
id|node
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMCHILD
suffix:colon
id|node
op_assign
id|__prom_getchild
c_func
(paren
id|node
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMSETCUR
suffix:colon
r_break
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|data-&gt;current_node
op_assign
id|node
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|opp-&gt;oprom_array
)paren
op_assign
id|node
suffix:semicolon
id|opp-&gt;oprom_size
op_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
id|bufsize
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMPCI2NODE
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|bufsize
op_ge
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|pcidev_cookie
op_star
id|pcp
suffix:semicolon
id|pdev
op_assign
id|pci_find_slot
(paren
(paren
(paren
r_int
op_star
)paren
id|opp-&gt;oprom_array
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|opp-&gt;oprom_array
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pcp
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
id|pcp
op_ne
l_int|NULL
op_logical_and
id|pcp-&gt;prom_node
op_ne
op_minus
l_int|1
op_logical_and
id|pcp-&gt;prom_node
)paren
(brace
id|node
op_assign
id|pcp-&gt;prom_node
suffix:semicolon
id|data-&gt;current_node
op_assign
id|node
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|opp-&gt;oprom_array
)paren
op_assign
id|node
suffix:semicolon
id|opp-&gt;oprom_size
op_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
id|bufsize
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_break
suffix:semicolon
r_case
id|OPROMPATH2NODE
suffix:colon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|node
op_assign
id|prom_finddevice
c_func
(paren
id|opp-&gt;oprom_array
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|data-&gt;current_node
op_assign
id|node
suffix:semicolon
op_star
(paren
(paren
r_int
op_star
)paren
id|opp-&gt;oprom_array
)paren
op_assign
id|node
suffix:semicolon
id|opp-&gt;oprom_size
op_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
id|bufsize
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMGETBOOTARGS
suffix:colon
id|buf
op_assign
id|saved_command_line
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|bufsize
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|opp-&gt;oprom_array
comma
id|buf
)paren
suffix:semicolon
id|opp-&gt;oprom_size
op_assign
id|len
suffix:semicolon
id|error
op_assign
id|copyout
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|opp
comma
id|bufsize
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPROMU2P
suffix:colon
r_case
id|OPROMGETCONS
suffix:colon
r_case
id|OPROMGETFBNAME
suffix:colon
r_if
c_cond
(paren
id|cnt
op_increment
OL
l_int|10
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;openprom_sunos_ioctl: unimplemented ioctl&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|cnt
op_increment
OL
l_int|10
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;openprom_sunos_ioctl: cmd 0x%X, arg 0x%lX&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|opp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* Return nonzero if a specific node is in the PROM device tree. */
DECL|function|intree
r_static
r_int
id|intree
c_func
(paren
r_int
id|root
comma
r_int
id|node
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|root
op_ne
l_int|0
suffix:semicolon
id|root
op_assign
id|prom_getsibling
c_func
(paren
id|root
)paren
)paren
r_if
c_cond
(paren
id|root
op_eq
id|node
op_logical_or
id|intree
c_func
(paren
id|prom_getchild
c_func
(paren
id|root
)paren
comma
id|node
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return nonzero if a specific node is &quot;valid&quot;. */
DECL|function|goodnode
r_static
r_int
id|goodnode
c_func
(paren
r_int
id|n
comma
id|DATA
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|n
op_eq
id|data-&gt;lastnode
op_logical_or
id|n
op_eq
id|prom_root_node
op_logical_or
id|n
op_eq
id|options_node
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
op_logical_or
id|n
op_eq
op_minus
l_int|1
op_logical_or
op_logical_neg
id|intree
c_func
(paren
id|prom_root_node
comma
id|n
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|data-&gt;lastnode
op_assign
id|n
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Copy in a whole string from userspace into kernelspace. */
DECL|function|copyin_string
r_static
r_int
id|copyin_string
c_func
(paren
r_char
op_star
id|user
comma
r_int
id|len
comma
r_char
op_star
op_star
id|ptr
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
op_logical_or
id|len
op_plus
l_int|1
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|tmp
comma
id|user
comma
id|len
)paren
)paren
(brace
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|tmp
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|ptr
op_assign
id|tmp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;NetBSD /dev/openprom ioctl calls.&n; */
DECL|function|openprom_bsd_ioctl
r_static
r_int
id|openprom_bsd_ioctl
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
id|DATA
op_star
id|data
op_assign
(paren
id|DATA
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|opiocdesc
id|op
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|error
comma
id|node
comma
id|len
suffix:semicolon
r_char
op_star
id|str
comma
op_star
id|tmp
suffix:semicolon
r_char
id|buffer
(braket
l_int|64
)braket
suffix:semicolon
r_static
r_int
id|cnt
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|OPIOCGET
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|op
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|op
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|goodnode
c_func
(paren
id|op.op_nodeid
comma
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|copyin_string
c_func
(paren
id|op.op_name
comma
id|op.op_namelen
comma
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|prom_getproplen
c_func
(paren
id|op.op_nodeid
comma
id|str
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|op.op_buflen
)paren
(brace
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|op.op_buflen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
multiline_comment|/* Verified by the above copy_from_user */
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|op
comma
r_sizeof
(paren
id|op
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|prom_getproperty
c_func
(paren
id|op.op_nodeid
comma
id|str
comma
id|tmp
comma
id|len
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|tmp
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|op
comma
r_sizeof
(paren
id|op
)paren
)paren
op_ne
l_int|0
op_logical_or
id|copy_to_user
c_func
(paren
id|op.op_buf
comma
id|tmp
comma
id|len
)paren
op_ne
l_int|0
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
r_case
id|OPIOCNEXTPROP
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|op
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|op
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|goodnode
c_func
(paren
id|op.op_nodeid
comma
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|copyin_string
c_func
(paren
id|op.op_name
comma
id|op.op_namelen
comma
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|tmp
op_assign
id|prom_nextprop
c_func
(paren
id|op.op_nodeid
comma
id|str
comma
id|buffer
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|op.op_buflen
)paren
id|len
op_assign
id|op.op_buflen
suffix:semicolon
r_else
id|op.op_buflen
op_assign
id|len
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|op.op_buflen
op_assign
l_int|0
suffix:semicolon
)brace
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|op
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|op.op_buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|error
op_assign
id|__copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|op
comma
r_sizeof
(paren
id|op
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|__copy_to_user
c_func
(paren
id|op.op_buf
comma
id|tmp
comma
id|len
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
r_case
id|OPIOCSET
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|op
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|op
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|goodnode
c_func
(paren
id|op.op_nodeid
comma
id|data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|copyin_string
c_func
(paren
id|op.op_name
comma
id|op.op_namelen
comma
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|copyin_string
c_func
(paren
id|op.op_buf
comma
id|op.op_buflen
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|len
op_assign
id|prom_setprop
c_func
(paren
id|op.op_nodeid
comma
id|str
comma
id|tmp
comma
id|op.op_buflen
op_plus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
id|op.op_buflen
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|kfree
c_func
(paren
id|str
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPIOCGETOPTNODE
suffix:colon
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
id|options_node
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPIOCGETNEXT
suffix:colon
r_case
id|OPIOCGETCHILD
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|node
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|OPIOCGETNEXT
)paren
id|node
op_assign
id|__prom_getsibling
c_func
(paren
id|node
)paren
suffix:semicolon
r_else
id|node
op_assign
id|__prom_getchild
c_func
(paren
id|node
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|node
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|cnt
op_increment
OL
l_int|10
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;openprom_bsd_ioctl: cmd 0x%X&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Handoff control to the correct ioctl handler.&n; */
DECL|function|openprom_ioctl
r_static
r_int
id|openprom_ioctl
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
id|DATA
op_star
id|data
op_assign
(paren
id|DATA
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_static
r_int
id|cnt
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|OPROMGETOPT
suffix:colon
r_case
id|OPROMNXTOPT
suffix:colon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|openprom_sunos_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|options_node
)paren
suffix:semicolon
r_case
id|OPROMSETOPT
suffix:colon
r_case
id|OPROMSETOPT2
suffix:colon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|openprom_sunos_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|options_node
)paren
suffix:semicolon
r_case
id|OPROMNEXT
suffix:colon
r_case
id|OPROMCHILD
suffix:colon
r_case
id|OPROMGETPROP
suffix:colon
r_case
id|OPROMNXTPROP
suffix:colon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|openprom_sunos_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|data-&gt;current_node
)paren
suffix:semicolon
r_case
id|OPROMU2P
suffix:colon
r_case
id|OPROMGETCONS
suffix:colon
r_case
id|OPROMGETFBNAME
suffix:colon
r_case
id|OPROMGETBOOTARGS
suffix:colon
r_case
id|OPROMSETCUR
suffix:colon
r_case
id|OPROMPCI2NODE
suffix:colon
r_case
id|OPROMPATH2NODE
suffix:colon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|openprom_sunos_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_case
id|OPIOCGET
suffix:colon
r_case
id|OPIOCNEXTPROP
suffix:colon
r_case
id|OPIOCGETOPTNODE
suffix:colon
r_case
id|OPIOCGETNEXT
suffix:colon
r_case
id|OPIOCGETCHILD
suffix:colon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_return
id|openprom_bsd_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|OPIOCSET
suffix:colon
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_return
id|openprom_bsd_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|cnt
op_increment
OL
l_int|10
)paren
id|printk
c_func
(paren
l_string|&quot;openprom_ioctl: cmd 0x%X, arg 0x%lX&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|openprom_open
r_static
r_int
id|openprom_open
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
id|DATA
op_star
id|data
suffix:semicolon
id|data
op_assign
(paren
id|DATA
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|DATA
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|data-&gt;current_node
op_assign
id|prom_root_node
suffix:semicolon
id|data-&gt;lastnode
op_assign
id|prom_root_node
suffix:semicolon
id|file-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|openprom_release
r_static
r_int
id|openprom_release
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|openprom_fops
r_static
r_struct
id|file_operations
id|openprom_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|ioctl
op_assign
id|openprom_ioctl
comma
dot
id|open
op_assign
id|openprom_open
comma
dot
id|release
op_assign
id|openprom_release
comma
)brace
suffix:semicolon
DECL|variable|openprom_dev
r_static
r_struct
id|miscdevice
id|openprom_dev
op_assign
(brace
id|SUN_OPENPROM_MINOR
comma
l_string|&quot;openprom&quot;
comma
op_amp
id|openprom_fops
)brace
suffix:semicolon
DECL|function|openprom_init
r_static
r_int
id|__init
id|openprom_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|misc_register
c_func
(paren
op_amp
id|openprom_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;openprom: unable to get misc minor&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|options_node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|options_node
op_assign
id|prom_searchsiblings
c_func
(paren
id|options_node
comma
l_string|&quot;options&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|options_node
op_eq
l_int|0
op_logical_or
id|options_node
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;openprom: unable to find options node&bslash;n&quot;
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|openprom_dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|openprom_cleanup
r_static
r_void
id|__exit
id|openprom_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|openprom_dev
)paren
suffix:semicolon
)brace
DECL|variable|openprom_init
id|module_init
c_func
(paren
id|openprom_init
)paren
suffix:semicolon
DECL|variable|openprom_cleanup
id|module_exit
c_func
(paren
id|openprom_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
