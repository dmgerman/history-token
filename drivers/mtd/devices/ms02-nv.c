multiline_comment|/*&n; *&t;Copyright (c) 2001 Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;$Id: ms02-nv.c,v 1.7 2004/07/29 14:16:45 macro Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/dec/ioasic_addrs.h&gt;
macro_line|#include &lt;asm/dec/kn02.h&gt;
macro_line|#include &lt;asm/dec/kn03.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/paccess.h&gt;
macro_line|#include &quot;ms02-nv.h&quot;
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;ms02-nv.c: v.1.0.0  13 Aug 2001  Maciej W. Rozycki.&bslash;n&quot;
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Maciej W. Rozycki &lt;macro@linux-mips.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;DEC MS02-NV NVRAM module driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Addresses we probe for an MS02-NV at.  Modules may be located&n; * at any 8MiB boundary within a 0MiB up to 112MiB range or at any 32MiB&n; * boundary within a 0MiB up to 448MiB range.  We don&squot;t support a module&n; * at 0MiB, though.&n; */
DECL|variable|__initdata
r_static
id|ulong
id|ms02nv_addrs
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x07000000
comma
l_int|0x06800000
comma
l_int|0x06000000
comma
l_int|0x05800000
comma
l_int|0x05000000
comma
l_int|0x04800000
comma
l_int|0x04000000
comma
l_int|0x03800000
comma
l_int|0x03000000
comma
l_int|0x02800000
comma
l_int|0x02000000
comma
l_int|0x01800000
comma
l_int|0x01000000
comma
l_int|0x00800000
)brace
suffix:semicolon
DECL|variable|ms02nv_name
r_static
r_const
r_char
id|ms02nv_name
(braket
)braket
op_assign
l_string|&quot;DEC MS02-NV NVRAM&quot;
suffix:semicolon
DECL|variable|ms02nv_res_diag_ram
r_static
r_const
r_char
id|ms02nv_res_diag_ram
(braket
)braket
op_assign
l_string|&quot;Diagnostic RAM&quot;
suffix:semicolon
DECL|variable|ms02nv_res_user_ram
r_static
r_const
r_char
id|ms02nv_res_user_ram
(braket
)braket
op_assign
l_string|&quot;General-purpose RAM&quot;
suffix:semicolon
DECL|variable|ms02nv_res_csr
r_static
r_const
r_char
id|ms02nv_res_csr
(braket
)braket
op_assign
l_string|&quot;Control and status register&quot;
suffix:semicolon
DECL|variable|root_ms02nv_mtd
r_static
r_struct
id|mtd_info
op_star
id|root_ms02nv_mtd
suffix:semicolon
DECL|function|ms02nv_read
r_static
r_int
id|ms02nv_read
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
r_struct
id|ms02nv_private
op_star
id|mp
op_assign
(paren
r_struct
id|ms02nv_private
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|from
op_plus
id|len
OG
id|mtd-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|mp-&gt;uaddr
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
DECL|function|ms02nv_write
r_static
r_int
id|ms02nv_write
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
r_struct
id|ms02nv_private
op_star
id|mp
op_assign
(paren
r_struct
id|ms02nv_private
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|to
op_plus
id|len
OG
id|mtd-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|mp-&gt;uaddr
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
DECL|function|ms02nv_probe_one
r_static
r_inline
id|uint
id|ms02nv_probe_one
c_func
(paren
id|ulong
id|addr
)paren
(brace
id|ms02nv_uint
op_star
id|ms02nv_diagp
suffix:semicolon
id|ms02nv_uint
op_star
id|ms02nv_magicp
suffix:semicolon
id|uint
id|ms02nv_diag
suffix:semicolon
id|uint
id|ms02nv_magic
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * The firmware writes MS02NV_ID at MS02NV_MAGIC and also&n;&t; * a diagnostic status at MS02NV_DIAG.&n;&t; */
id|ms02nv_diagp
op_assign
(paren
id|ms02nv_uint
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|addr
op_plus
id|MS02NV_DIAG
)paren
)paren
suffix:semicolon
id|ms02nv_magicp
op_assign
(paren
id|ms02nv_uint
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|addr
op_plus
id|MS02NV_MAGIC
)paren
)paren
suffix:semicolon
id|err
op_assign
id|get_dbe
c_func
(paren
id|ms02nv_magic
comma
id|ms02nv_magicp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ms02nv_magic
op_ne
id|MS02NV_ID
)paren
r_return
l_int|0
suffix:semicolon
id|ms02nv_diag
op_assign
op_star
id|ms02nv_diagp
suffix:semicolon
id|size
op_assign
(paren
id|ms02nv_diag
op_amp
id|MS02NV_DIAG_SIZE_MASK
)paren
op_lshift
id|MS02NV_DIAG_SIZE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|MS02NV_CSR
)paren
id|size
op_assign
id|MS02NV_CSR
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|ms02nv_init_one
r_static
r_int
id|__init
id|ms02nv_init_one
c_func
(paren
id|ulong
id|addr
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
r_struct
id|ms02nv_private
op_star
id|mp
suffix:semicolon
r_struct
id|resource
op_star
id|mod_res
suffix:semicolon
r_struct
id|resource
op_star
id|diag_res
suffix:semicolon
r_struct
id|resource
op_star
id|user_res
suffix:semicolon
r_struct
id|resource
op_star
id|csr_res
suffix:semicolon
id|ulong
id|fixaddr
suffix:semicolon
r_int
id|size
comma
id|fixsize
suffix:semicolon
r_static
r_int
id|version_printed
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* The module decodes 8MiB of address space. */
id|mod_res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mod_res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mod_res
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|mod_res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mod_res
)paren
)paren
suffix:semicolon
id|mod_res-&gt;name
op_assign
id|ms02nv_name
suffix:semicolon
id|mod_res-&gt;start
op_assign
id|addr
suffix:semicolon
id|mod_res-&gt;end
op_assign
id|addr
op_plus
id|MS02NV_SLOT_SIZE
op_minus
l_int|1
suffix:semicolon
id|mod_res-&gt;flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|mod_res
)paren
OL
l_int|0
)paren
r_goto
id|err_out_mod_res
suffix:semicolon
id|size
op_assign
id|ms02nv_probe_one
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_goto
id|err_out_mod_res_rel
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|version_printed
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
id|version_printed
op_assign
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|mtd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mtd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
r_goto
id|err_out_mod_res_rel
suffix:semicolon
id|memset
c_func
(paren
id|mtd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mtd
)paren
)paren
suffix:semicolon
id|mp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mp
)paren
r_goto
id|err_out_mtd
suffix:semicolon
id|memset
c_func
(paren
id|mp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mp
)paren
)paren
suffix:semicolon
id|mtd-&gt;priv
op_assign
id|mp
suffix:semicolon
id|mp-&gt;resource.module
op_assign
id|mod_res
suffix:semicolon
multiline_comment|/* Firmware&squot;s diagnostic NVRAM area. */
id|diag_res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|diag_res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|diag_res
)paren
r_goto
id|err_out_mp
suffix:semicolon
id|memset
c_func
(paren
id|diag_res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|diag_res
)paren
)paren
suffix:semicolon
id|diag_res-&gt;name
op_assign
id|ms02nv_res_diag_ram
suffix:semicolon
id|diag_res-&gt;start
op_assign
id|addr
suffix:semicolon
id|diag_res-&gt;end
op_assign
id|addr
op_plus
id|MS02NV_RAM
op_minus
l_int|1
suffix:semicolon
id|diag_res-&gt;flags
op_assign
id|IORESOURCE_BUSY
suffix:semicolon
id|request_resource
c_func
(paren
id|mod_res
comma
id|diag_res
)paren
suffix:semicolon
id|mp-&gt;resource.diag_ram
op_assign
id|diag_res
suffix:semicolon
multiline_comment|/* User-available general-purpose NVRAM area. */
id|user_res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|user_res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_res
)paren
r_goto
id|err_out_diag_res
suffix:semicolon
id|memset
c_func
(paren
id|user_res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|user_res
)paren
)paren
suffix:semicolon
id|user_res-&gt;name
op_assign
id|ms02nv_res_user_ram
suffix:semicolon
id|user_res-&gt;start
op_assign
id|addr
op_plus
id|MS02NV_RAM
suffix:semicolon
id|user_res-&gt;end
op_assign
id|addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
id|user_res-&gt;flags
op_assign
id|IORESOURCE_BUSY
suffix:semicolon
id|request_resource
c_func
(paren
id|mod_res
comma
id|user_res
)paren
suffix:semicolon
id|mp-&gt;resource.user_ram
op_assign
id|user_res
suffix:semicolon
multiline_comment|/* Control and status register. */
id|csr_res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|csr_res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|csr_res
)paren
r_goto
id|err_out_user_res
suffix:semicolon
id|memset
c_func
(paren
id|csr_res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|csr_res
)paren
)paren
suffix:semicolon
id|csr_res-&gt;name
op_assign
id|ms02nv_res_csr
suffix:semicolon
id|csr_res-&gt;start
op_assign
id|addr
op_plus
id|MS02NV_CSR
suffix:semicolon
id|csr_res-&gt;end
op_assign
id|addr
op_plus
id|MS02NV_CSR
op_plus
l_int|3
suffix:semicolon
id|csr_res-&gt;flags
op_assign
id|IORESOURCE_BUSY
suffix:semicolon
id|request_resource
c_func
(paren
id|mod_res
comma
id|csr_res
)paren
suffix:semicolon
id|mp-&gt;resource.csr
op_assign
id|csr_res
suffix:semicolon
id|mp-&gt;addr
op_assign
id|phys_to_virt
c_func
(paren
id|addr
)paren
suffix:semicolon
id|mp-&gt;size
op_assign
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * Hide the firmware&squot;s diagnostic area.  It may get destroyed&n;&t; * upon a reboot.  Take paging into account for mapping support.&n;&t; */
id|fixaddr
op_assign
(paren
id|addr
op_plus
id|MS02NV_RAM
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|fixsize
op_assign
(paren
id|size
op_minus
(paren
id|fixaddr
op_minus
id|addr
)paren
)paren
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|mp-&gt;uaddr
op_assign
id|phys_to_virt
c_func
(paren
id|fixaddr
)paren
suffix:semicolon
id|mtd-&gt;type
op_assign
id|MTD_RAM
suffix:semicolon
id|mtd-&gt;flags
op_assign
id|MTD_CAP_RAM
op_or
id|MTD_XIP
suffix:semicolon
id|mtd-&gt;size
op_assign
id|fixsize
suffix:semicolon
id|mtd-&gt;name
op_assign
(paren
r_char
op_star
)paren
id|ms02nv_name
suffix:semicolon
id|mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|mtd-&gt;read
op_assign
id|ms02nv_read
suffix:semicolon
id|mtd-&gt;write
op_assign
id|ms02nv_write
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|add_mtd_device
c_func
(paren
id|mtd
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ms02-nv: Unable to register MTD device, aborting!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out_csr_res
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mtd%d: %s at 0x%08lx, size %uMiB.&bslash;n&quot;
comma
id|mtd-&gt;index
comma
id|ms02nv_name
comma
id|addr
comma
id|size
op_rshift
l_int|20
)paren
suffix:semicolon
id|mp-&gt;next
op_assign
id|root_ms02nv_mtd
suffix:semicolon
id|root_ms02nv_mtd
op_assign
id|mtd
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_csr_res
suffix:colon
id|release_resource
c_func
(paren
id|csr_res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|csr_res
)paren
suffix:semicolon
id|err_out_user_res
suffix:colon
id|release_resource
c_func
(paren
id|user_res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|user_res
)paren
suffix:semicolon
id|err_out_diag_res
suffix:colon
id|release_resource
c_func
(paren
id|diag_res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|diag_res
)paren
suffix:semicolon
id|err_out_mp
suffix:colon
id|kfree
c_func
(paren
id|mp
)paren
suffix:semicolon
id|err_out_mtd
suffix:colon
id|kfree
c_func
(paren
id|mtd
)paren
suffix:semicolon
id|err_out_mod_res_rel
suffix:colon
id|release_resource
c_func
(paren
id|mod_res
)paren
suffix:semicolon
id|err_out_mod_res
suffix:colon
id|kfree
c_func
(paren
id|mod_res
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ms02nv_remove_one
r_static
r_void
id|__exit
id|ms02nv_remove_one
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
op_assign
id|root_ms02nv_mtd
suffix:semicolon
r_struct
id|ms02nv_private
op_star
id|mp
op_assign
(paren
r_struct
id|ms02nv_private
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
id|root_ms02nv_mtd
op_assign
id|mp-&gt;next
suffix:semicolon
id|del_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|mp-&gt;resource.csr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mp-&gt;resource.csr
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|mp-&gt;resource.user_ram
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mp-&gt;resource.user_ram
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|mp-&gt;resource.diag_ram
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mp-&gt;resource.diag_ram
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|mp-&gt;resource.module
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mp-&gt;resource.module
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
DECL|function|ms02nv_init
r_static
r_int
id|__init
id|ms02nv_init
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u32
op_star
id|csr
suffix:semicolon
id|uint
id|stride
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
r_case
id|MACH_DS5000_200
suffix:colon
id|csr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|KN02_CSR_BASE
suffix:semicolon
r_if
c_cond
(paren
op_star
id|csr
op_amp
id|KN02_CSR_BNK32M
)paren
id|stride
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_DS5000_2X0
suffix:colon
r_case
id|MACH_DS5900
suffix:colon
id|csr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|KN03_MCR_BASE
suffix:semicolon
r_if
c_cond
(paren
op_star
id|csr
op_amp
id|KN03_MCR_BNK32M
)paren
id|stride
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
r_break
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
r_sizeof
(paren
id|ms02nv_addrs
)paren
op_div
r_sizeof
(paren
op_star
id|ms02nv_addrs
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|ms02nv_init_one
c_func
(paren
id|ms02nv_addrs
(braket
id|i
)braket
op_lshift
id|stride
)paren
)paren
id|count
op_increment
suffix:semicolon
r_return
(paren
id|count
OG
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|ms02nv_cleanup
r_static
r_void
id|__exit
id|ms02nv_cleanup
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|root_ms02nv_mtd
)paren
id|ms02nv_remove_one
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|ms02nv_init
id|module_init
c_func
(paren
id|ms02nv_init
)paren
suffix:semicolon
DECL|variable|ms02nv_cleanup
id|module_exit
c_func
(paren
id|ms02nv_cleanup
)paren
suffix:semicolon
eof
