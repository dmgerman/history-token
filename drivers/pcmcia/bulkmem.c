multiline_comment|/*======================================================================&n;&n;    PCMCIA Bulk Memory Services&n;&n;    bulkmem.c 1.38 2000/09/25 19:29:51&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
DECL|macro|IN_CARD_SERVICES
mdefine_line|#define IN_CARD_SERVICES
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
macro_line|#ifdef DEBUG
r_extern
r_int
id|pc_debug
suffix:semicolon
DECL|macro|cs_socket_name
mdefine_line|#define cs_socket_name(skt)&t;((skt)-&gt;dev.class_id)
DECL|macro|ds_dbg
mdefine_line|#define ds_dbg(skt, lvl, fmt, arg...) do {&t;&t;&bslash;&n;&t;if (pc_debug &gt;= lvl)&t;&t;&t;&t;&bslash;&n;&t;&t;printk(KERN_DEBUG &quot;ds: %s: &quot; fmt, &t;&bslash;&n;&t;&t;       cs_socket_name(skt) , ## arg);&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|ds_dbg
mdefine_line|#define ds_dbg(lvl, fmt, arg...) do { } while (0)
macro_line|#endif
multiline_comment|/*======================================================================&n;&n;    This stuff is used by Card Services to initialize the table of&n;    region info used for subsequent calls to GetFirstRegion and&n;    GetNextRegion.&n;    &n;======================================================================*/
DECL|function|setup_regions
r_static
r_void
id|setup_regions
c_func
(paren
id|client_handle_t
id|handle
comma
r_int
id|attr
comma
id|memory_handle_t
op_star
id|list
)paren
(brace
r_int
id|i
comma
id|code
comma
id|has_jedec
comma
id|has_geo
suffix:semicolon
id|u_int
id|offset
suffix:semicolon
id|cistpl_device_t
id|device
suffix:semicolon
id|cistpl_jedec_t
id|jedec
suffix:semicolon
id|cistpl_device_geo_t
id|geo
suffix:semicolon
id|memory_handle_t
id|r
suffix:semicolon
id|ds_dbg
c_func
(paren
id|SOCKET
c_func
(paren
id|handle
)paren
comma
l_int|1
comma
l_string|&quot;setup_regions(0x%p, %d, 0x%p)&bslash;n&quot;
comma
id|handle
comma
id|attr
comma
id|list
)paren
suffix:semicolon
id|code
op_assign
(paren
id|attr
)paren
ques
c_cond
id|CISTPL_DEVICE_A
suffix:colon
id|CISTPL_DEVICE
suffix:semicolon
r_if
c_cond
(paren
id|read_tuple
c_func
(paren
id|handle
comma
id|code
comma
op_amp
id|device
)paren
op_ne
id|CS_SUCCESS
)paren
r_return
suffix:semicolon
id|code
op_assign
(paren
id|attr
)paren
ques
c_cond
id|CISTPL_JEDEC_A
suffix:colon
id|CISTPL_JEDEC_C
suffix:semicolon
id|has_jedec
op_assign
(paren
id|read_tuple
c_func
(paren
id|handle
comma
id|code
comma
op_amp
id|jedec
)paren
op_eq
id|CS_SUCCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_jedec
op_logical_and
(paren
id|device.ndev
op_ne
id|jedec.nid
)paren
)paren
(brace
id|ds_dbg
c_func
(paren
id|SOCKET
c_func
(paren
id|handle
)paren
comma
l_int|0
comma
l_string|&quot;Device info does not match JEDEC info.&bslash;n&quot;
)paren
suffix:semicolon
id|has_jedec
op_assign
l_int|0
suffix:semicolon
)brace
id|code
op_assign
(paren
id|attr
)paren
ques
c_cond
id|CISTPL_DEVICE_GEO_A
suffix:colon
id|CISTPL_DEVICE_GEO
suffix:semicolon
id|has_geo
op_assign
(paren
id|read_tuple
c_func
(paren
id|handle
comma
id|code
comma
op_amp
id|geo
)paren
op_eq
id|CS_SUCCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_geo
op_logical_and
(paren
id|device.ndev
op_ne
id|geo.ngeo
)paren
)paren
(brace
id|ds_dbg
c_func
(paren
id|SOCKET
c_func
(paren
id|handle
)paren
comma
l_int|0
comma
l_string|&quot;Device info does not match geometry tuple.&bslash;n&quot;
)paren
suffix:semicolon
id|has_geo
op_assign
l_int|0
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
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
id|device.ndev
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|device.dev
(braket
id|i
)braket
dot
id|type
op_ne
id|CISTPL_DTYPE_NULL
)paren
op_logical_and
(paren
id|device.dev
(braket
id|i
)braket
dot
id|size
op_ne
l_int|0
)paren
)paren
(brace
id|r
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|r
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;cs: setup_regions: kmalloc failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|r-&gt;region_magic
op_assign
id|REGION_MAGIC
suffix:semicolon
id|r-&gt;state
op_assign
l_int|0
suffix:semicolon
id|r-&gt;dev_info
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|r-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
id|r-&gt;info.Attributes
op_assign
(paren
id|attr
)paren
ques
c_cond
id|REGION_TYPE_AM
suffix:colon
l_int|0
suffix:semicolon
id|r-&gt;info.CardOffset
op_assign
id|offset
suffix:semicolon
id|r-&gt;info.RegionSize
op_assign
id|device.dev
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|r-&gt;info.AccessSpeed
op_assign
id|device.dev
(braket
id|i
)braket
dot
id|speed
suffix:semicolon
r_if
c_cond
(paren
id|has_jedec
)paren
(brace
id|r-&gt;info.JedecMfr
op_assign
id|jedec.id
(braket
id|i
)braket
dot
id|mfr
suffix:semicolon
id|r-&gt;info.JedecInfo
op_assign
id|jedec.id
(braket
id|i
)braket
dot
id|info
suffix:semicolon
)brace
r_else
id|r-&gt;info.JedecMfr
op_assign
id|r-&gt;info.JedecInfo
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|has_geo
)paren
(brace
id|r-&gt;info.BlockSize
op_assign
id|geo.geo
(braket
id|i
)braket
dot
id|buswidth
op_star
id|geo.geo
(braket
id|i
)braket
dot
id|erase_block
op_star
id|geo.geo
(braket
id|i
)braket
dot
id|interleave
suffix:semicolon
id|r-&gt;info.PartMultiple
op_assign
id|r-&gt;info.BlockSize
op_star
id|geo.geo
(braket
id|i
)braket
dot
id|partition
suffix:semicolon
)brace
r_else
id|r-&gt;info.BlockSize
op_assign
id|r-&gt;info.PartMultiple
op_assign
l_int|1
suffix:semicolon
id|r-&gt;info.next
op_assign
op_star
id|list
suffix:semicolon
op_star
id|list
op_assign
id|r
suffix:semicolon
)brace
id|offset
op_add_assign
id|device.dev
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
)brace
multiline_comment|/* setup_regions */
multiline_comment|/*======================================================================&n;&n;    This is tricky.  When get_first_region() is called by Driver&n;    Services, we initialize the region info table in the socket&n;    structure.  When it is called by an MTD, we can just scan the&n;    table for matching entries.&n;    &n;======================================================================*/
DECL|function|match_region
r_static
r_int
id|match_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|memory_handle_t
id|list
comma
id|region_info_t
op_star
id|match
)paren
(brace
r_while
c_loop
(paren
id|list
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|handle-&gt;Attributes
op_amp
id|INFO_MTD_CLIENT
)paren
op_logical_or
(paren
id|strcmp
c_func
(paren
id|handle-&gt;dev_info
comma
id|list-&gt;dev_info
)paren
op_eq
l_int|0
)paren
)paren
(brace
op_star
id|match
op_assign
id|list-&gt;info
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
id|list
op_assign
id|list-&gt;info.next
suffix:semicolon
)brace
r_return
id|CS_NO_MORE_ITEMS
suffix:semicolon
)brace
multiline_comment|/* match_region */
DECL|function|pcmcia_get_first_region
r_int
id|pcmcia_get_first_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|handle-&gt;Attributes
op_amp
id|INFO_MASTER_CLIENT
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|s-&gt;state
op_amp
id|SOCKET_REGION_INFO
)paren
)paren
)paren
(brace
id|setup_regions
c_func
(paren
id|handle
comma
l_int|0
comma
op_amp
id|s-&gt;c_region
)paren
suffix:semicolon
id|setup_regions
c_func
(paren
id|handle
comma
l_int|1
comma
op_amp
id|s-&gt;a_region
)paren
suffix:semicolon
id|s-&gt;state
op_or_assign
id|SOCKET_REGION_INFO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rgn-&gt;Attributes
op_amp
id|REGION_TYPE_AM
)paren
r_return
id|match_region
c_func
(paren
id|handle
comma
id|s-&gt;a_region
comma
id|rgn
)paren
suffix:semicolon
r_else
r_return
id|match_region
c_func
(paren
id|handle
comma
id|s-&gt;c_region
comma
id|rgn
)paren
suffix:semicolon
)brace
multiline_comment|/* get_first_region */
DECL|variable|pcmcia_get_first_region
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_first_region
)paren
suffix:semicolon
DECL|function|pcmcia_get_next_region
r_int
id|pcmcia_get_next_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
(brace
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|match_region
c_func
(paren
id|handle
comma
id|rgn-&gt;next
comma
id|rgn
)paren
suffix:semicolon
)brace
multiline_comment|/* get_next_region */
DECL|variable|pcmcia_get_next_region
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_next_region
)paren
suffix:semicolon
eof
