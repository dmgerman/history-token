multiline_comment|/*&n; *    $Id: zorro.c,v 1.1.2.1 1998/06/07 23:21:02 geert Exp $&n; *&n; *    Zorro Bus Services&n; *&n; *    Copyright (C) 1995-2000 Geert Uytterhoeven&n; *&n; *    This file is subject to the terms and conditions of the GNU General Public&n; *    License.  See the file COPYING in the main directory of this archive&n; *    for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
multiline_comment|/*&n;     *  Zorro Expansion Devices&n;     */
DECL|variable|zorro_num_autocon
id|u_int
id|zorro_num_autocon
op_assign
l_int|0
suffix:semicolon
DECL|variable|zorro_autocon
r_struct
id|zorro_dev
id|zorro_autocon
(braket
id|ZORRO_NUM_AUTO
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Zorro Bus Resources&n;     *  Order _does_ matter! (see code below)&n;     */
DECL|variable|zorro_res
r_static
r_struct
id|resource
id|zorro_res
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/* Zorro II regions (on Zorro II/III) */
(brace
l_string|&quot;Zorro II exp&quot;
comma
l_int|0x00e80000
comma
l_int|0x00efffff
)brace
comma
(brace
l_string|&quot;Zorro II mem&quot;
comma
l_int|0x00200000
comma
l_int|0x009fffff
)brace
comma
multiline_comment|/* Zorro III regions (on Zorro III only) */
(brace
l_string|&quot;Zorro III exp&quot;
comma
l_int|0xff000000
comma
l_int|0xffffffff
)brace
comma
(brace
l_string|&quot;Zorro III cfg&quot;
comma
l_int|0x40000000
comma
l_int|0x7fffffff
)brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_int
id|zorro_num_res
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;     *  Find Zorro Devices&n;     */
DECL|function|zorro_find_device
r_struct
id|zorro_dev
op_star
id|zorro_find_device
c_func
(paren
id|zorro_id
id|id
comma
r_struct
id|zorro_dev
op_star
id|from
)paren
(brace
r_struct
id|zorro_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|from
ques
c_cond
id|from
op_plus
l_int|1
suffix:colon
op_amp
id|zorro_autocon
(braket
l_int|0
)braket
suffix:semicolon
id|dev
OL
id|zorro_autocon
op_plus
id|zorro_num_autocon
suffix:semicolon
id|dev
op_increment
)paren
r_if
c_cond
(paren
id|id
op_eq
id|ZORRO_WILDCARD
op_logical_or
id|id
op_eq
id|dev-&gt;id
)paren
r_return
id|dev
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Bitmask indicating portions of available Zorro II RAM that are unused&n;     *  by the system. Every bit represents a 64K chunk, for a maximum of 8MB&n;     *  (128 chunks, physical 0x00200000-0x009fffff).&n;     *&n;     *  If you want to use (= allocate) portions of this RAM, you should clear&n;     *  the corresponding bits.&n;     *&n;     *  Possible uses:&n;     *      - z2ram device&n;     *      - SCSI DMA bounce buffers&n;     *&n;     *  FIXME: use the normal resource management&n;     */
DECL|variable|zorro_unused_z2ram
id|u32
id|zorro_unused_z2ram
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|mark_region
r_static
r_void
id|__init
id|mark_region
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|flag
)paren
(brace
r_if
c_cond
(paren
id|flag
)paren
id|start
op_add_assign
id|Z2RAM_CHUNKMASK
suffix:semicolon
r_else
id|end
op_add_assign
id|Z2RAM_CHUNKMASK
suffix:semicolon
id|start
op_and_assign
op_complement
id|Z2RAM_CHUNKMASK
suffix:semicolon
id|end
op_and_assign
op_complement
id|Z2RAM_CHUNKMASK
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
id|Z2RAM_START
op_logical_or
id|start
op_ge
id|Z2RAM_END
)paren
r_return
suffix:semicolon
id|start
op_assign
id|start
OL
id|Z2RAM_START
ques
c_cond
l_int|0x00000000
suffix:colon
id|start
op_minus
id|Z2RAM_START
suffix:semicolon
id|end
op_assign
id|end
OG
id|Z2RAM_END
ques
c_cond
id|Z2RAM_SIZE
suffix:colon
id|end
op_minus
id|Z2RAM_START
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|u32
id|chunk
op_assign
id|start
op_rshift
id|Z2RAM_CHUNKSHIFT
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
id|set_bit
c_func
(paren
id|chunk
comma
id|zorro_unused_z2ram
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|chunk
comma
id|zorro_unused_z2ram
)paren
suffix:semicolon
id|start
op_add_assign
id|Z2RAM_CHUNKSIZE
suffix:semicolon
)brace
)brace
DECL|function|zorro_find_parent_resource
r_static
r_struct
id|resource
id|__init
op_star
id|zorro_find_parent_resource
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_int
id|i
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
id|zorro_num_res
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|z-&gt;resource.start
op_ge
id|zorro_res
(braket
id|i
)braket
dot
id|start
op_logical_and
id|z-&gt;resource.end
op_le
id|zorro_res
(braket
id|i
)braket
dot
id|end
)paren
r_return
op_amp
id|zorro_res
(braket
id|i
)braket
suffix:semicolon
r_return
op_amp
id|iomem_resource
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialization&n;     */
DECL|function|zorro_init
r_void
id|__init
id|zorro_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|zorro_dev
op_star
id|dev
suffix:semicolon
id|u_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Zorro: Probing AutoConfig expansion devices: %d device%s&bslash;n&quot;
comma
id|zorro_num_autocon
comma
id|zorro_num_autocon
op_eq
l_int|1
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
multiline_comment|/* Request the resources */
id|zorro_num_res
op_assign
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO3
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|2
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
id|zorro_num_res
suffix:semicolon
id|i
op_increment
)paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|zorro_res
(braket
id|i
)braket
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
id|zorro_num_autocon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
op_amp
id|zorro_autocon
(braket
id|i
)braket
suffix:semicolon
id|dev-&gt;id
op_assign
(paren
id|dev-&gt;rom.er_Manufacturer
op_lshift
l_int|16
)paren
op_or
(paren
id|dev-&gt;rom.er_Product
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;id
op_eq
id|ZORRO_PROD_GVP_EPC_BASE
)paren
(brace
multiline_comment|/* GVP quirk */
r_int
r_int
id|magic
op_assign
id|dev-&gt;resource.start
op_plus
l_int|0x8000
suffix:semicolon
id|dev-&gt;id
op_or_assign
op_star
(paren
id|u16
op_star
)paren
id|ZTWO_VADDR
c_func
(paren
id|magic
)paren
op_amp
id|GVP_PRODMASK
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;Zorro device %08x&quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
id|zorro_name_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;resource.name
op_assign
id|dev-&gt;name
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
id|zorro_find_parent_resource
c_func
(paren
id|dev
)paren
comma
op_amp
id|dev-&gt;resource
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Zorro: Address space collision on device %s &quot;
l_string|&quot;[%lx:%lx]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;resource.start
comma
id|dev-&gt;resource.end
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark all available Zorro II memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|zorro_num_autocon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
op_amp
id|zorro_autocon
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;rom.er_Type
op_amp
id|ERTF_MEMLIST
)paren
id|mark_region
c_func
(paren
id|dev-&gt;resource.start
comma
id|dev-&gt;resource.end
op_plus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Unmark all used Zorro II memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|m68k_num_memory
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
OL
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
id|mark_region
c_func
(paren
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
comma
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
op_plus
id|m68k_memory
(braket
id|i
)braket
dot
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|zorro_find_device
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_find_device
)paren
suffix:semicolon
DECL|variable|zorro_unused_z2ram
id|EXPORT_SYMBOL
c_func
(paren
id|zorro_unused_z2ram
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
