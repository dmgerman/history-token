multiline_comment|/*======================================================================&n;&n;  $Id: slram.c,v 1.32 2004/11/16 18:29:01 dwmw2 Exp $&n;&n;  This driver provides a method to access memory not used by the kernel&n;  itself (i.e. if the kernel commandline mem=xxx is used). To actually&n;  use slram at least mtdblock or mtdchar is required (for block or&n;  character device access).&n;&n;  Usage:&n;&n;  if compiled as loadable module:&n;    modprobe slram map=&lt;name&gt;,&lt;start&gt;,&lt;end/offset&gt;&n;  if statically linked into the kernel use the following kernel cmd.line&n;    slram=&lt;name&gt;,&lt;start&gt;,&lt;end/offset&gt;&n;&n;  &lt;name&gt;: name of the device that will be listed in /proc/mtd&n;  &lt;start&gt;: start of the memory region, decimal or hex (0xabcdef)&n;  &lt;end/offset&gt;: end of the memory region. It&squot;s possible to use +0x1234&n;                to specify the offset instead of the absolute address&n;    &n;  NOTE:&n;  With slram it&squot;s only possible to map a contigous memory region. Therfore&n;  if there&squot;s a device mapped somewhere in the region specified slram will&n;  fail to load (see kernel log if modprobe fails).&n;&n;  -&n;  &n;  Jochen Schaeuble &lt;psionic@psionic.de&gt;&n;&n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
DECL|macro|SLRAM_MAX_DEVICES_PARAMS
mdefine_line|#define SLRAM_MAX_DEVICES_PARAMS 6&t;&t;/* 3 parameters / device */
DECL|macro|T
mdefine_line|#define T(fmt, args...) printk(KERN_DEBUG fmt, ## args)
DECL|macro|E
mdefine_line|#define E(fmt, args...) printk(KERN_NOTICE fmt, ## args)
DECL|struct|slram_priv
r_typedef
r_struct
id|slram_priv
(brace
DECL|member|start
id|u_char
op_star
id|start
suffix:semicolon
DECL|member|end
id|u_char
op_star
id|end
suffix:semicolon
DECL|typedef|slram_priv_t
)brace
id|slram_priv_t
suffix:semicolon
DECL|struct|slram_mtd_list
r_typedef
r_struct
id|slram_mtd_list
(brace
DECL|member|mtdinfo
r_struct
id|mtd_info
op_star
id|mtdinfo
suffix:semicolon
DECL|member|next
r_struct
id|slram_mtd_list
op_star
id|next
suffix:semicolon
DECL|typedef|slram_mtd_list_t
)brace
id|slram_mtd_list_t
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|map
r_static
r_char
op_star
id|map
(braket
id|SLRAM_MAX_DEVICES_PARAMS
)braket
suffix:semicolon
macro_line|#else
DECL|variable|map
r_static
r_char
op_star
id|map
suffix:semicolon
macro_line|#endif
id|MODULE_PARM
c_func
(paren
id|map
comma
l_string|&quot;3-&quot;
id|__MODULE_STRING
c_func
(paren
id|SLRAM_MAX_DEVICES_PARAMS
)paren
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|map
comma
l_string|&quot;List of memory regions to map. &bslash;&quot;map=&lt;name&gt;, &lt;start&gt;, &lt;length / end&gt;&bslash;&quot;&quot;
)paren
suffix:semicolon
DECL|variable|slram_mtdlist
r_static
id|slram_mtd_list_t
op_star
id|slram_mtdlist
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|slram_erase
c_func
(paren
r_struct
id|mtd_info
op_star
comma
r_struct
id|erase_info
op_star
)paren
suffix:semicolon
r_static
r_int
id|slram_point
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|loff_t
comma
r_int
comma
r_int
op_star
comma
id|u_char
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
id|slram_unpoint
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|u_char
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|slram_read
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|loff_t
comma
r_int
comma
r_int
op_star
comma
id|u_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|slram_write
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|loff_t
comma
r_int
comma
r_int
op_star
comma
r_const
id|u_char
op_star
)paren
suffix:semicolon
DECL|function|slram_erase
r_static
r_int
id|slram_erase
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|erase_info
op_star
id|instr
)paren
(brace
id|slram_priv_t
op_star
id|priv
op_assign
id|mtd-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|instr-&gt;addr
op_plus
id|instr-&gt;len
OG
id|mtd-&gt;size
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|priv-&gt;start
op_plus
id|instr-&gt;addr
comma
l_int|0xff
comma
id|instr-&gt;len
)paren
suffix:semicolon
multiline_comment|/* This&squot;ll catch a few races. Free the thing before returning :) &n;&t; * I don&squot;t feel at all ashamed. This kind of thing is possible anyway&n;&t; * with flash, but unlikely.&n;&t; */
id|instr-&gt;state
op_assign
id|MTD_ERASE_DONE
suffix:semicolon
id|mtd_erase_callback
c_func
(paren
id|instr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slram_point
r_static
r_int
id|slram_point
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
op_star
id|mtdbuf
)paren
(brace
id|slram_priv_t
op_star
id|priv
op_assign
(paren
id|slram_priv_t
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
op_star
id|mtdbuf
op_assign
id|priv-&gt;start
op_plus
id|from
suffix:semicolon
op_star
id|retlen
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slram_unpoint
r_static
r_void
id|slram_unpoint
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|addr
comma
id|loff_t
id|from
comma
r_int
id|len
)paren
(brace
)brace
DECL|function|slram_read
r_static
r_int
id|slram_read
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
(brace
id|slram_priv_t
op_star
id|priv
op_assign
(paren
id|slram_priv_t
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|priv-&gt;start
op_plus
id|from
comma
id|len
)paren
suffix:semicolon
op_star
id|retlen
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|slram_write
r_static
r_int
id|slram_write
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
(brace
id|slram_priv_t
op_star
id|priv
op_assign
(paren
id|slram_priv_t
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
id|memcpy
c_func
(paren
id|priv-&gt;start
op_plus
id|to
comma
id|buf
comma
id|len
)paren
suffix:semicolon
op_star
id|retlen
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|register_device
r_static
r_int
id|register_device
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|start
comma
r_int
r_int
id|length
)paren
(brace
id|slram_mtd_list_t
op_star
op_star
id|curmtd
suffix:semicolon
id|curmtd
op_assign
op_amp
id|slram_mtdlist
suffix:semicolon
r_while
c_loop
(paren
op_star
id|curmtd
)paren
(brace
id|curmtd
op_assign
op_amp
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
op_star
id|curmtd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|slram_mtd_list_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|curmtd
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: Cannot allocate new MTD device.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mtd_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
)paren
(brace
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mtd_info
)paren
)paren
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|slram_priv_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
(brace
id|kfree
c_func
(paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
)paren
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
id|slram_priv_t
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: Cannot allocate new MTD device.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
(paren
id|slram_priv_t
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|start
op_assign
id|ioremap
c_func
(paren
id|start
comma
id|length
)paren
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: ioremap failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
(paren
(paren
id|slram_priv_t
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|end
op_assign
(paren
(paren
id|slram_priv_t
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|start
op_plus
id|length
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;name
op_assign
id|name
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;size
op_assign
id|length
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;flags
op_assign
id|MTD_CLEAR_BITS
op_or
id|MTD_SET_BITS
op_or
id|MTD_WRITEB_WRITEABLE
op_or
id|MTD_VOLATILE
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;erase
op_assign
id|slram_erase
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;point
op_assign
id|slram_point
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;unpoint
op_assign
id|slram_unpoint
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;read
op_assign
id|slram_read
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;write
op_assign
id|slram_write
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;type
op_assign
id|MTD_RAM
suffix:semicolon
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;erasesize
op_assign
l_int|0x0
suffix:semicolon
r_if
c_cond
(paren
id|add_mtd_device
c_func
(paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: Failed to register new device&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
(paren
id|slram_priv_t
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|start
)paren
suffix:semicolon
id|kfree
c_func
(paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|T
c_func
(paren
l_string|&quot;slram: Registered device %s from %luKiB to %luKiB&bslash;n&quot;
comma
id|name
comma
(paren
id|start
op_div
l_int|1024
)paren
comma
(paren
(paren
id|start
op_plus
id|length
)paren
op_div
l_int|1024
)paren
)paren
suffix:semicolon
id|T
c_func
(paren
l_string|&quot;slram: Mapped from 0x%p to 0x%p&bslash;n&quot;
comma
(paren
(paren
id|slram_priv_t
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|start
comma
(paren
(paren
id|slram_priv_t
op_star
)paren
(paren
op_star
id|curmtd
)paren
op_member_access_from_pointer
id|mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_devices
r_static
r_void
id|unregister_devices
c_func
(paren
r_void
)paren
(brace
id|slram_mtd_list_t
op_star
id|nextitem
suffix:semicolon
r_while
c_loop
(paren
id|slram_mtdlist
)paren
(brace
id|nextitem
op_assign
id|slram_mtdlist-&gt;next
suffix:semicolon
id|del_mtd_device
c_func
(paren
id|slram_mtdlist-&gt;mtdinfo
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
(paren
id|slram_priv_t
op_star
)paren
id|slram_mtdlist-&gt;mtdinfo-&gt;priv
)paren
op_member_access_from_pointer
id|start
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slram_mtdlist-&gt;mtdinfo-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slram_mtdlist-&gt;mtdinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slram_mtdlist
)paren
suffix:semicolon
id|slram_mtdlist
op_assign
id|nextitem
suffix:semicolon
)brace
)brace
DECL|function|handle_unit
r_static
r_int
r_int
id|handle_unit
c_func
(paren
r_int
r_int
id|value
comma
r_char
op_star
id|unit
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|unit
op_eq
l_char|&squot;M&squot;
)paren
op_logical_or
(paren
op_star
id|unit
op_eq
l_char|&squot;m&squot;
)paren
)paren
(brace
r_return
id|value
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
op_star
id|unit
op_eq
l_char|&squot;K&squot;
)paren
op_logical_or
(paren
op_star
id|unit
op_eq
l_char|&squot;k&squot;
)paren
)paren
(brace
r_return
id|value
op_star
l_int|1024
suffix:semicolon
)brace
r_return
id|value
suffix:semicolon
)brace
DECL|function|parse_cmdline
r_static
r_int
id|parse_cmdline
c_func
(paren
r_char
op_star
id|devname
comma
r_char
op_star
id|szstart
comma
r_char
op_star
id|szlength
)paren
(brace
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|devstart
suffix:semicolon
r_int
r_int
id|devlength
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|devname
)paren
op_logical_or
(paren
op_logical_neg
id|szstart
)paren
op_logical_or
(paren
op_logical_neg
id|szlength
)paren
)paren
(brace
id|unregister_devices
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|devstart
op_assign
id|simple_strtoul
c_func
(paren
id|szstart
comma
op_amp
id|buffer
comma
l_int|0
)paren
suffix:semicolon
id|devstart
op_assign
id|handle_unit
c_func
(paren
id|devstart
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|szlength
)paren
op_ne
l_char|&squot;+&squot;
)paren
(brace
id|devlength
op_assign
id|simple_strtoul
c_func
(paren
id|szlength
comma
op_amp
id|buffer
comma
l_int|0
)paren
suffix:semicolon
id|devlength
op_assign
id|handle_unit
c_func
(paren
id|devlength
comma
id|buffer
)paren
op_minus
id|devstart
suffix:semicolon
)brace
r_else
(brace
id|devlength
op_assign
id|simple_strtoul
c_func
(paren
id|szlength
op_plus
l_int|1
comma
op_amp
id|buffer
comma
l_int|0
)paren
suffix:semicolon
id|devlength
op_assign
id|handle_unit
c_func
(paren
id|devlength
comma
id|buffer
)paren
suffix:semicolon
)brace
id|T
c_func
(paren
l_string|&quot;slram: devname=%s, devstart=0x%lx, devlength=0x%lx&bslash;n&quot;
comma
id|devname
comma
id|devstart
comma
id|devlength
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|devstart
OL
l_int|0
)paren
op_logical_or
(paren
id|devlength
OL
l_int|0
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: Illegal start / length parameter.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|devstart
op_assign
id|register_device
c_func
(paren
id|devname
comma
id|devstart
comma
id|devlength
)paren
)paren
)paren
(brace
id|unregister_devices
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|devstart
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|mtd_slram_setup
r_static
r_int
id|__init
id|mtd_slram_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|map
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;slram=&quot;
comma
id|mtd_slram_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|function|init_slram
r_static
r_int
id|init_slram
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|devname
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifndef MODULE
r_char
op_star
id|devstart
suffix:semicolon
r_char
op_star
id|devlength
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: not enough parameters.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|map
)paren
(brace
id|devname
op_assign
id|devstart
op_assign
id|devlength
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|devname
op_assign
id|strsep
c_func
(paren
op_amp
id|map
comma
l_string|&quot;,&quot;
)paren
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: No devicename specified.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|T
c_func
(paren
l_string|&quot;slram: devname = %s&bslash;n&quot;
comma
id|devname
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|map
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|devstart
op_assign
id|strsep
c_func
(paren
op_amp
id|map
comma
l_string|&quot;,&quot;
)paren
)paren
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: No devicestart specified.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|T
c_func
(paren
l_string|&quot;slram: devstart = %s&bslash;n&quot;
comma
id|devstart
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|map
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|devlength
op_assign
id|strsep
c_func
(paren
op_amp
id|map
comma
l_string|&quot;,&quot;
)paren
)paren
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: No devicelength / -end specified.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|T
c_func
(paren
l_string|&quot;slram: devlength = %s&bslash;n&quot;
comma
id|devlength
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_cmdline
c_func
(paren
id|devname
comma
id|devstart
comma
id|devlength
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
macro_line|#else
r_int
id|count
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
(paren
id|map
(braket
id|count
)braket
)paren
op_logical_and
(paren
id|count
OL
id|SLRAM_MAX_DEVICES_PARAMS
)paren
suffix:semicolon
id|count
op_increment
)paren
(brace
)brace
r_if
c_cond
(paren
(paren
id|count
op_mod
l_int|3
op_ne
l_int|0
)paren
op_logical_or
(paren
id|count
op_eq
l_int|0
)paren
)paren
(brace
id|E
c_func
(paren
l_string|&quot;slram: not enough parameters.&bslash;n&quot;
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|count
op_div
l_int|3
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|devname
op_assign
id|map
(braket
id|i
op_star
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|parse_cmdline
c_func
(paren
id|devname
comma
id|map
(braket
id|i
op_star
l_int|3
op_plus
l_int|1
)braket
comma
id|map
(braket
id|i
op_star
l_int|3
op_plus
l_int|2
)braket
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
macro_line|#endif /* !MODULE */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_slram
r_static
r_void
id|__exit
id|cleanup_slram
c_func
(paren
r_void
)paren
(brace
id|unregister_devices
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|init_slram
id|module_init
c_func
(paren
id|init_slram
)paren
suffix:semicolon
DECL|variable|cleanup_slram
id|module_exit
c_func
(paren
id|cleanup_slram
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jochen Schaeuble &lt;psionic@psionic.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD driver for uncached system RAM&quot;
)paren
suffix:semicolon
eof
