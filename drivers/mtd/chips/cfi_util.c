multiline_comment|/*&n; * Common Flash Interface support:&n; *   Generic utility functions not dependant on command set&n; *&n; * Copyright (C) 2002 Red Hat&n; * Copyright (C) 2003 STMicroelectronics Limited&n; *&n; * This code is covered by the GPL.&n; *&n; * $Id: cfi_util.c,v 1.5 2004/08/12 06:40:23 eric Exp $&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/cfi.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
r_struct
id|cfi_extquery
op_star
DECL|function|cfi_read_pri
id|cfi_read_pri
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u16
id|adr
comma
id|__u16
id|size
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|cfi_private
op_star
id|cfi
op_assign
id|map-&gt;fldrv_priv
suffix:semicolon
id|__u32
id|base
op_assign
l_int|0
suffix:semicolon
singleline_comment|// cfi-&gt;chips[0].start;
r_int
id|ofs_factor
op_assign
id|cfi-&gt;interleave
op_star
id|cfi-&gt;device_type
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|cfi_extquery
op_star
id|extp
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %s Extended Query Table at 0x%4.4X&bslash;n&quot;
comma
id|name
comma
id|adr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adr
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Switch it into Query Mode */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0x98
comma
l_int|0x55
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|extp
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|extp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to allocate memory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Read in the Extended Query Table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_int
r_char
op_star
)paren
id|extp
)paren
(braket
id|i
)braket
op_assign
id|cfi_read_query
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
id|i
)paren
op_star
id|ofs_factor
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|extp-&gt;MajorVersion
op_ne
l_char|&squot;1&squot;
op_logical_or
(paren
id|extp-&gt;MinorVersion
template_param
l_char|&squot;3&squot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Unknown %s Extended Query &quot;
l_string|&quot;version %c.%c.&bslash;n&quot;
comma
id|name
comma
id|extp-&gt;MajorVersion
comma
id|extp-&gt;MinorVersion
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|extp
)paren
suffix:semicolon
id|extp
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
multiline_comment|/* Make sure it&squot;s in read mode */
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xf0
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
id|cfi_send_gen_cmd
c_func
(paren
l_int|0xff
comma
l_int|0
comma
id|base
comma
id|map
comma
id|cfi
comma
id|cfi-&gt;device_type
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|extp
suffix:semicolon
)brace
DECL|variable|cfi_read_pri
id|EXPORT_SYMBOL
c_func
(paren
id|cfi_read_pri
)paren
suffix:semicolon
DECL|function|cfi_fixup
r_void
id|cfi_fixup
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|cfi_fixup
op_star
id|fixups
)paren
(brace
r_struct
id|map_info
op_star
id|map
op_assign
id|mtd-&gt;priv
suffix:semicolon
r_struct
id|cfi_private
op_star
id|cfi
op_assign
id|map-&gt;fldrv_priv
suffix:semicolon
r_struct
id|cfi_fixup
op_star
id|f
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|fixups
suffix:semicolon
id|f-&gt;fixup
suffix:semicolon
id|f
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|f-&gt;mfr
op_eq
id|CFI_MFR_ANY
)paren
op_logical_or
(paren
id|f-&gt;mfr
op_eq
id|cfi-&gt;mfr
)paren
)paren
op_logical_and
(paren
(paren
id|f-&gt;id
op_eq
id|CFI_ID_ANY
)paren
op_logical_or
(paren
id|f-&gt;id
op_eq
id|cfi-&gt;id
)paren
)paren
)paren
(brace
id|f
op_member_access_from_pointer
id|fixup
c_func
(paren
id|mtd
comma
id|f-&gt;param
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|cfi_fixup
id|EXPORT_SYMBOL
c_func
(paren
id|cfi_fixup
)paren
suffix:semicolon
DECL|function|cfi_varsize_frob
r_int
id|cfi_varsize_frob
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|varsize_frob_t
id|frob
comma
id|loff_t
id|ofs
comma
r_int
id|len
comma
r_void
op_star
id|thunk
)paren
(brace
r_struct
id|map_info
op_star
id|map
op_assign
id|mtd-&gt;priv
suffix:semicolon
r_struct
id|cfi_private
op_star
id|cfi
op_assign
id|map-&gt;fldrv_priv
suffix:semicolon
r_int
r_int
id|adr
suffix:semicolon
r_int
id|chipnum
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|first
suffix:semicolon
r_struct
id|mtd_erase_region_info
op_star
id|regions
op_assign
id|mtd-&gt;eraseregions
suffix:semicolon
r_if
c_cond
(paren
id|ofs
OG
id|mtd-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_plus
id|ofs
)paren
OG
id|mtd-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Check that both start and end of the requested erase are&n;&t; * aligned with the erasesize at the appropriate addresses.&n;&t; */
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Skip all erase regions which are ended before the start of &n;&t;   the requested erase. Actually, to save on the calculations,&n;&t;   we skip to the first erase region which starts after the&n;&t;   start of the requested erase, and then go back one.&n;&t;*/
r_while
c_loop
(paren
id|i
OL
id|mtd-&gt;numeraseregions
op_logical_and
id|ofs
op_ge
id|regions
(braket
id|i
)braket
dot
id|offset
)paren
id|i
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
multiline_comment|/* OK, now i is pointing at the erase region in which this &n;&t;   erase request starts. Check the start of the requested&n;&t;   erase range is aligned with the erase size which is in&n;&t;   effect here.&n;&t;*/
r_if
c_cond
(paren
id|ofs
op_amp
(paren
id|regions
(braket
id|i
)braket
dot
id|erasesize
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Remember the erase region we start on */
id|first
op_assign
id|i
suffix:semicolon
multiline_comment|/* Next, check that the end of the requested erase is aligned&n;&t; * with the erase region at that address.&n;&t; */
r_while
c_loop
(paren
id|i
OL
id|mtd-&gt;numeraseregions
op_logical_and
(paren
id|ofs
op_plus
id|len
)paren
op_ge
id|regions
(braket
id|i
)braket
dot
id|offset
)paren
id|i
op_increment
suffix:semicolon
multiline_comment|/* As before, drop back one to point at the region in which&n;&t;   the address actually falls&n;&t;*/
id|i
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ofs
op_plus
id|len
)paren
op_amp
(paren
id|regions
(braket
id|i
)braket
dot
id|erasesize
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|chipnum
op_assign
id|ofs
op_rshift
id|cfi-&gt;chipshift
suffix:semicolon
id|adr
op_assign
id|ofs
op_minus
(paren
id|chipnum
op_lshift
id|cfi-&gt;chipshift
)paren
suffix:semicolon
id|i
op_assign
id|first
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
r_int
id|chipmask
suffix:semicolon
r_int
id|size
op_assign
id|regions
(braket
id|i
)braket
dot
id|erasesize
suffix:semicolon
id|ret
op_assign
(paren
op_star
id|frob
)paren
(paren
id|map
comma
op_amp
id|cfi-&gt;chips
(braket
id|chipnum
)braket
comma
id|adr
comma
id|size
comma
id|thunk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|adr
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
id|chipmask
op_assign
(paren
l_int|1
op_lshift
id|cfi-&gt;chipshift
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|adr
op_amp
id|chipmask
)paren
op_eq
(paren
(paren
id|regions
(braket
id|i
)braket
dot
id|offset
op_plus
id|size
op_star
id|regions
(braket
id|i
)braket
dot
id|numblocks
)paren
op_amp
id|chipmask
)paren
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|adr
op_rshift
id|cfi-&gt;chipshift
)paren
(brace
id|adr
op_assign
l_int|0
suffix:semicolon
id|chipnum
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|chipnum
op_ge
id|cfi-&gt;numchips
)paren
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cfi_varsize_frob
id|EXPORT_SYMBOL
c_func
(paren
id|cfi_varsize_frob
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
