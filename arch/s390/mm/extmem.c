multiline_comment|/*&n; * File...........: arch/s390/mm/extmem.c&n; * Author(s)......: Carsten Otte &lt;cotte@de.ibm.com&gt;&n; * &t;&t;    Rob M van der Heij &lt;rvdheij@nl.ibm.com&gt;&n; * &t;&t;    Steven Shultz &lt;shultzss@us.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation 2002-2004&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/extmem.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
DECL|macro|DCSS_DEBUG
mdefine_line|#define DCSS_DEBUG&t;/* Debug messages on/off */
DECL|macro|DCSS_NAME
mdefine_line|#define DCSS_NAME &quot;extmem&quot;
macro_line|#ifdef DCSS_DEBUG
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...)&t;printk(KERN_DEBUG DCSS_NAME &quot; debug:&quot; x)
macro_line|#else
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...)   do {} while (0)
macro_line|#endif
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...)&t;printk(KERN_INFO DCSS_NAME &quot; info:&quot; x)
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...)&t;printk(KERN_WARNING DCSS_NAME &quot; warning:&quot; x)
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...)&t;&t;printk(KERN_ERR DCSS_NAME &quot; error:&quot; x)
DECL|macro|DCSS_LOADSHR
mdefine_line|#define DCSS_LOADSHR    0x00
DECL|macro|DCSS_LOADNSR
mdefine_line|#define DCSS_LOADNSR    0x04
DECL|macro|DCSS_PURGESEG
mdefine_line|#define DCSS_PURGESEG   0x08
DECL|macro|DCSS_FINDSEG
mdefine_line|#define DCSS_FINDSEG    0x0c
DECL|macro|DCSS_LOADNOLY
mdefine_line|#define DCSS_LOADNOLY   0x10
DECL|macro|DCSS_SEGEXT
mdefine_line|#define DCSS_SEGEXT     0x18
DECL|macro|DCSS_FINDSEGA
mdefine_line|#define DCSS_FINDSEGA   0x0c
DECL|struct|qrange
r_struct
id|qrange
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
singleline_comment|// 3byte start address, 1 byte type
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
singleline_comment|// 3byte end address, 1 byte reserved
)brace
suffix:semicolon
DECL|struct|qout64
r_struct
id|qout64
(brace
DECL|member|segstart
r_int
id|segstart
suffix:semicolon
DECL|member|segend
r_int
id|segend
suffix:semicolon
DECL|member|segcnt
r_int
id|segcnt
suffix:semicolon
DECL|member|segrcnt
r_int
id|segrcnt
suffix:semicolon
DECL|member|range
r_struct
id|qrange
id|range
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qin64
r_struct
id|qin64
(brace
DECL|member|qopcode
r_char
id|qopcode
suffix:semicolon
DECL|member|rsrv1
r_char
id|rsrv1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|qrcode
r_char
id|qrcode
suffix:semicolon
DECL|member|rsrv2
r_char
id|rsrv2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|qname
r_char
id|qname
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|qoutptr
r_int
r_int
id|qoutptr
suffix:semicolon
DECL|member|qoutlen
r_int
r_int
id|qoutlen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dcss_segment
r_struct
id|dcss_segment
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dcss_name
r_char
id|dcss_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|start_addr
r_int
r_int
id|start_addr
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|do_nonshared
r_int
id|do_nonshared
suffix:semicolon
DECL|member|vm_segtype
r_int
r_int
id|vm_segtype
suffix:semicolon
DECL|member|range
r_struct
id|qrange
id|range
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|segcnt
r_int
id|segcnt
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dcss_lock
r_static
id|spinlock_t
id|dcss_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|dcss_list
r_static
r_struct
id|list_head
id|dcss_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|dcss_list
)paren
suffix:semicolon
DECL|variable|segtype_string
r_static
r_char
op_star
id|segtype_string
(braket
)braket
op_assign
(brace
l_string|&quot;SW&quot;
comma
l_string|&quot;EW&quot;
comma
l_string|&quot;SR&quot;
comma
l_string|&quot;ER&quot;
comma
l_string|&quot;SN&quot;
comma
l_string|&quot;EN&quot;
comma
l_string|&quot;SC&quot;
comma
l_string|&quot;EW/EN-MIXED&quot;
)brace
suffix:semicolon
r_extern
r_struct
(brace
DECL|member|addr
DECL|member|size
DECL|member|type
r_int
r_int
id|addr
comma
id|size
comma
id|type
suffix:semicolon
)brace
id|memory_chunk
(braket
id|MEMORY_CHUNKS
)braket
suffix:semicolon
multiline_comment|/*&n; * Create the 8 bytes, ebcdic VM segment name from&n; * an ascii name.&n; */
r_static
r_void
r_inline
DECL|function|dcss_mkname
id|dcss_mkname
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|dcss_name
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|name
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
id|dcss_name
(braket
id|i
)braket
op_assign
id|toupper
c_func
(paren
id|name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|dcss_name
(braket
id|i
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|ASCEBC
c_func
(paren
id|dcss_name
comma
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * search all segments in dcss_list, and return the one&n; * namend *name. If not found, return NULL.&n; */
r_static
r_struct
id|dcss_segment
op_star
DECL|function|segment_by_name
id|segment_by_name
(paren
r_char
op_star
id|name
)paren
(brace
r_char
id|dcss_name
(braket
l_int|9
)braket
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|dcss_segment
op_star
id|tmp
comma
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
id|BUG_ON
(paren
op_logical_neg
id|spin_is_locked
c_func
(paren
op_amp
id|dcss_lock
)paren
)paren
suffix:semicolon
id|dcss_mkname
(paren
id|name
comma
id|dcss_name
)paren
suffix:semicolon
id|list_for_each
(paren
id|l
comma
op_amp
id|dcss_list
)paren
(brace
id|tmp
op_assign
id|list_entry
(paren
id|l
comma
r_struct
id|dcss_segment
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|tmp-&gt;dcss_name
comma
id|dcss_name
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|retval
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform a function on a dcss segment.&n; */
r_static
r_inline
r_int
DECL|function|dcss_diag
id|dcss_diag
(paren
id|__u8
id|func
comma
r_void
op_star
id|parameter
comma
r_int
r_int
op_star
id|ret1
comma
r_int
r_int
op_star
id|ret2
)paren
(brace
r_int
r_int
id|rx
comma
id|ry
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rx
op_assign
(paren
r_int
r_int
)paren
id|parameter
suffix:semicolon
id|ry
op_assign
(paren
r_int
r_int
)paren
id|func
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#ifdef CONFIG_ARCH_S390X
l_string|&quot;   sam31&bslash;n&quot;
singleline_comment|// switch to 31 bit
l_string|&quot;   diag    %0,%1,0x64&bslash;n&quot;
l_string|&quot;   sam64&bslash;n&quot;
singleline_comment|// switch back to 64 bit
macro_line|#else
l_string|&quot;   diag    %0,%1,0x64&bslash;n&quot;
macro_line|#endif
l_string|&quot;   ipm     %2&bslash;n&quot;
l_string|&quot;   srl     %2,28&bslash;n&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|rx
)paren
comma
l_string|&quot;+d&quot;
(paren
id|ry
)paren
comma
l_string|&quot;=d&quot;
(paren
id|rc
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
op_star
id|ret1
op_assign
id|rx
suffix:semicolon
op_star
id|ret2
op_assign
id|ry
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dcss_diag_translate_rc
id|dcss_diag_translate_rc
(paren
r_int
id|vm_rc
)paren
(brace
r_if
c_cond
(paren
id|vm_rc
op_eq
l_int|44
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* do a diag to get info about a segment.&n; * fills start_address, end and vm_segtype fields&n; */
r_static
r_int
DECL|function|query_segment_type
id|query_segment_type
(paren
r_struct
id|dcss_segment
op_star
id|seg
)paren
(brace
r_struct
id|qin64
op_star
id|qin
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|qin64
)paren
comma
id|GFP_DMA
)paren
suffix:semicolon
r_struct
id|qout64
op_star
id|qout
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|qout64
)paren
comma
id|GFP_DMA
)paren
suffix:semicolon
r_int
id|diag_cc
comma
id|rc
comma
id|i
suffix:semicolon
r_int
r_int
id|dummy
comma
id|vmrc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|qin
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|qout
op_eq
l_int|NULL
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
multiline_comment|/* initialize diag input parameters */
id|qin-&gt;qopcode
op_assign
id|DCSS_FINDSEGA
suffix:semicolon
id|qin-&gt;qoutptr
op_assign
(paren
r_int
r_int
)paren
id|qout
suffix:semicolon
id|qin-&gt;qoutlen
op_assign
r_sizeof
(paren
r_struct
id|qout64
)paren
suffix:semicolon
id|memcpy
(paren
id|qin-&gt;qname
comma
id|seg-&gt;dcss_name
comma
l_int|8
)paren
suffix:semicolon
id|diag_cc
op_assign
id|dcss_diag
(paren
id|DCSS_SEGEXT
comma
id|qin
comma
op_amp
id|dummy
comma
op_amp
id|vmrc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diag_cc
OG
l_int|1
)paren
(brace
id|rc
op_assign
id|dcss_diag_translate_rc
(paren
id|vmrc
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qout-&gt;segcnt
OG
l_int|6
)paren
(brace
id|rc
op_assign
op_minus
id|ENOTSUPP
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qout-&gt;segcnt
op_eq
l_int|1
)paren
(brace
id|seg-&gt;vm_segtype
op_assign
id|qout-&gt;range
(braket
l_int|0
)braket
dot
id|start
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* multi-part segment. only one type supported here:&n;&t;&t;    - all parts are contiguous&n;&t;&t;    - all parts are either EW or EN type&n;&t;&t;    - maximum 6 parts allowed */
r_int
r_int
id|start
op_assign
id|qout-&gt;segstart
op_rshift
id|PAGE_SHIFT
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
id|qout-&gt;segcnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|qout-&gt;range
(braket
id|i
)braket
dot
id|start
op_amp
l_int|0xff
)paren
op_ne
id|SEG_TYPE_EW
)paren
op_logical_and
(paren
(paren
id|qout-&gt;range
(braket
id|i
)braket
dot
id|start
op_amp
l_int|0xff
)paren
op_ne
id|SEG_TYPE_EN
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENOTSUPP
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
op_ne
id|qout-&gt;range
(braket
id|i
)braket
dot
id|start
op_rshift
id|PAGE_SHIFT
)paren
(brace
id|rc
op_assign
op_minus
id|ENOTSUPP
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|start
op_assign
(paren
id|qout-&gt;range
(braket
id|i
)braket
dot
id|end
op_rshift
id|PAGE_SHIFT
)paren
op_plus
l_int|1
suffix:semicolon
)brace
id|seg-&gt;vm_segtype
op_assign
id|SEG_TYPE_EWEN
suffix:semicolon
)brace
multiline_comment|/* analyze diag output and update seg */
id|seg-&gt;start_addr
op_assign
id|qout-&gt;segstart
suffix:semicolon
id|seg-&gt;end
op_assign
id|qout-&gt;segend
suffix:semicolon
id|memcpy
(paren
id|seg-&gt;range
comma
id|qout-&gt;range
comma
l_int|6
op_star
r_sizeof
(paren
r_struct
id|qrange
)paren
)paren
suffix:semicolon
id|seg-&gt;segcnt
op_assign
id|qout-&gt;segcnt
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|out_free
suffix:colon
r_if
c_cond
(paren
id|qin
)paren
id|kfree
c_func
(paren
id|qin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qout
)paren
id|kfree
c_func
(paren
id|qout
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * check if the given segment collides with guest storage.&n; * returns 1 if this is the case, 0 if no collision was found&n; */
r_static
r_int
DECL|function|segment_overlaps_storage
id|segment_overlaps_storage
c_func
(paren
r_struct
id|dcss_segment
op_star
id|seg
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
template_param
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|type
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|addr
op_rshift
l_int|20
)paren
OG
(paren
id|seg-&gt;end
op_rshift
l_int|20
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|addr
op_plus
id|memory_chunk
(braket
id|i
)braket
dot
id|size
op_minus
l_int|1
)paren
op_rshift
l_int|20
)paren
OL
(paren
id|seg-&gt;start_addr
op_rshift
l_int|20
)paren
)paren
r_continue
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * check if segment collides with other segments that are currently loaded&n; * returns 1 if this is the case, 0 if no collision was found&n; */
r_static
r_int
DECL|function|segment_overlaps_others
id|segment_overlaps_others
(paren
r_struct
id|dcss_segment
op_star
id|seg
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|dcss_segment
op_star
id|tmp
suffix:semicolon
id|BUG_ON
(paren
op_logical_neg
id|spin_is_locked
c_func
(paren
op_amp
id|dcss_lock
)paren
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|dcss_list
)paren
(brace
id|tmp
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|dcss_segment
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp-&gt;start_addr
op_rshift
l_int|20
)paren
OG
(paren
id|seg-&gt;end
op_rshift
l_int|20
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp-&gt;end
op_rshift
l_int|20
)paren
OL
(paren
id|seg-&gt;start_addr
op_rshift
l_int|20
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
id|tmp
)paren
r_continue
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * check if segment exceeds the kernel mapping range (detected or set via mem=)&n; * returns 1 if this is the case, 0 if segment fits into the range&n; */
r_static
r_inline
r_int
DECL|function|segment_exceeds_range
id|segment_exceeds_range
(paren
r_struct
id|dcss_segment
op_star
id|seg
)paren
(brace
r_int
id|seg_last_pfn
op_assign
(paren
id|seg-&gt;end
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|seg_last_pfn
OG
id|max_pfn
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * get info about a segment&n; * possible return values:&n; * -ENOSYS  : we are not running on VM&n; * -EIO     : could not perform query diagnose&n; * -ENOENT  : no such segment&n; * -ENOTSUPP: multi-part segment cannot be used with linux&n; * -ENOSPC  : segment cannot be used (overlaps with storage)&n; * -ENOMEM  : out of memory&n; * 0 .. 6   : type of segment as defined in include/asm-s390/extmem.h&n; */
r_int
DECL|function|segment_type
id|segment_type
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|dcss_segment
id|seg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|dcss_mkname
c_func
(paren
id|name
comma
id|seg.dcss_name
)paren
suffix:semicolon
id|rc
op_assign
id|query_segment_type
(paren
op_amp
id|seg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
r_return
id|seg.vm_segtype
suffix:semicolon
)brace
multiline_comment|/*&n; * real segment loading function, called from segment_load&n; */
r_static
r_int
DECL|function|__segment_load
id|__segment_load
(paren
r_char
op_star
id|name
comma
r_int
id|do_nonshared
comma
r_int
r_int
op_star
id|addr
comma
r_int
r_int
op_star
id|end
)paren
(brace
r_struct
id|dcss_segment
op_star
id|seg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dcss_segment
)paren
comma
id|GFP_DMA
)paren
suffix:semicolon
r_int
id|dcss_command
comma
id|rc
comma
id|diag_cc
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dcss_mkname
(paren
id|name
comma
id|seg-&gt;dcss_name
)paren
suffix:semicolon
id|rc
op_assign
id|query_segment_type
(paren
id|seg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
r_if
c_cond
(paren
id|segment_exceeds_range
c_func
(paren
id|seg
)paren
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;segment_load: not loading segment %s - exceeds&quot;
l_string|&quot; kernel mapping range&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ERANGE
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|segment_overlaps_storage
c_func
(paren
id|seg
)paren
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;segment_load: not loading segment %s - overlaps&quot;
l_string|&quot; storage&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|segment_overlaps_others
c_func
(paren
id|seg
)paren
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;segment_load: not loading segment %s - overlaps&quot;
l_string|&quot; other segments&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_nonshared
)paren
id|dcss_command
op_assign
id|DCSS_LOADNSR
suffix:semicolon
r_else
id|dcss_command
op_assign
id|DCSS_LOADNOLY
suffix:semicolon
id|diag_cc
op_assign
id|dcss_diag
c_func
(paren
id|dcss_command
comma
id|seg-&gt;dcss_name
comma
op_amp
id|seg-&gt;start_addr
comma
op_amp
id|seg-&gt;end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diag_cc
OG
l_int|1
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;segment_load: could not load segment %s - &quot;
l_string|&quot;diag returned error (%ld)&bslash;n&quot;
comma
id|name
comma
id|seg-&gt;end
)paren
suffix:semicolon
id|rc
op_assign
id|dcss_diag_translate_rc
(paren
id|seg-&gt;end
)paren
suffix:semicolon
id|dcss_diag
c_func
(paren
id|DCSS_PURGESEG
comma
id|seg-&gt;dcss_name
comma
op_amp
id|seg-&gt;start_addr
comma
op_amp
id|seg-&gt;end
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|seg-&gt;do_nonshared
op_assign
id|do_nonshared
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|seg-&gt;ref_count
comma
l_int|1
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|seg-&gt;list
comma
op_amp
id|dcss_list
)paren
suffix:semicolon
id|rc
op_assign
id|seg-&gt;vm_segtype
suffix:semicolon
op_star
id|addr
op_assign
id|seg-&gt;start_addr
suffix:semicolon
op_star
id|end
op_assign
id|seg-&gt;end
suffix:semicolon
r_if
c_cond
(paren
id|do_nonshared
)paren
id|PRINT_INFO
(paren
l_string|&quot;segment_load: loaded segment %s range %p .. %p &quot;
l_string|&quot;type %s in non-shared mode&bslash;n&quot;
comma
id|name
comma
(paren
r_void
op_star
)paren
id|seg-&gt;start_addr
comma
(paren
r_void
op_star
)paren
id|seg-&gt;end
comma
id|segtype_string
(braket
id|seg-&gt;vm_segtype
)braket
)paren
suffix:semicolon
r_else
id|PRINT_INFO
(paren
l_string|&quot;segment_load: loaded segment %s range %p .. %p &quot;
l_string|&quot;type %s in shared mode&bslash;n&quot;
comma
id|name
comma
(paren
r_void
op_star
)paren
id|seg-&gt;start_addr
comma
(paren
r_void
op_star
)paren
id|seg-&gt;end
comma
id|segtype_string
(braket
id|seg-&gt;vm_segtype
)braket
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_free
suffix:colon
id|kfree
(paren
id|seg
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * this function loads a DCSS segment&n; * name         : name of the DCSS&n; * do_nonshared : 0 indicates that the dcss should be shared with other linux images&n; *                1 indicates that the dcss should be exclusive for this linux image&n; * addr         : will be filled with start address of the segment&n; * end          : will be filled with end address of the segment&n; * return values:&n; * -ENOSYS  : we are not running on VM&n; * -EIO     : could not perform query or load diagnose&n; * -ENOENT  : no such segment&n; * -ENOTSUPP: multi-part segment cannot be used with linux&n; * -ENOSPC  : segment cannot be used (overlaps with storage)&n; * -EBUSY   : segment can temporarily not be used (overlaps with dcss)&n; * -ERANGE  : segment cannot be used (exceeds kernel mapping range)&n; * -EPERM   : segment is currently loaded with incompatible permissions&n; * -ENOMEM  : out of memory&n; * 0 .. 6   : type of segment as defined in include/asm-s390/extmem.h&n; */
r_int
DECL|function|segment_load
id|segment_load
(paren
r_char
op_star
id|name
comma
r_int
id|do_nonshared
comma
r_int
r_int
op_star
id|addr
comma
r_int
r_int
op_star
id|end
)paren
(brace
r_struct
id|dcss_segment
op_star
id|seg
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|spin_lock
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
id|seg
op_assign
id|segment_by_name
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
l_int|NULL
)paren
id|rc
op_assign
id|__segment_load
(paren
id|name
comma
id|do_nonshared
comma
id|addr
comma
id|end
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|do_nonshared
op_eq
id|seg-&gt;do_nonshared
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|seg-&gt;ref_count
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|seg-&gt;start_addr
suffix:semicolon
op_star
id|end
op_assign
id|seg-&gt;end
suffix:semicolon
id|rc
op_assign
id|seg-&gt;vm_segtype
suffix:semicolon
)brace
r_else
(brace
op_star
id|addr
op_assign
op_star
id|end
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
id|spin_unlock
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * this function modifies the shared state of a DCSS segment. note that&n; * name         : name of the DCSS&n; * do_nonshared : 0 indicates that the dcss should be shared with other linux images&n; *                1 indicates that the dcss should be exclusive for this linux image&n; * return values:&n; * -EIO     : could not perform load diagnose (segment gone!)&n; * -ENOENT  : no such segment (segment gone!)&n; * -EAGAIN  : segment is in use by other exploiters, try later&n; * -EINVAL  : no segment with the given name is currently loaded - name invalid&n; * 0&t;    : operation succeeded&n; */
r_int
DECL|function|segment_modify_shared
id|segment_modify_shared
(paren
r_char
op_star
id|name
comma
r_int
id|do_nonshared
)paren
(brace
r_struct
id|dcss_segment
op_star
id|seg
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
r_int
id|dcss_command
comma
id|rc
comma
id|diag_cc
suffix:semicolon
id|spin_lock
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
id|seg
op_assign
id|segment_by_name
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_nonshared
op_eq
id|seg-&gt;do_nonshared
)paren
(brace
id|PRINT_INFO
(paren
l_string|&quot;segment_modify_shared: not reloading segment %s&quot;
l_string|&quot; - already in requested mode&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
id|seg-&gt;ref_count
)paren
op_ne
l_int|1
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;segment_modify_shared: not reloading segment %s - &quot;
l_string|&quot;segment is in use by other driver(s)&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|dcss_diag
c_func
(paren
id|DCSS_PURGESEG
comma
id|seg-&gt;dcss_name
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_nonshared
)paren
id|dcss_command
op_assign
id|DCSS_LOADNSR
suffix:semicolon
r_else
id|dcss_command
op_assign
id|DCSS_LOADNOLY
suffix:semicolon
id|diag_cc
op_assign
id|dcss_diag
c_func
(paren
id|dcss_command
comma
id|seg-&gt;dcss_name
comma
op_amp
id|seg-&gt;start_addr
comma
op_amp
id|seg-&gt;end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diag_cc
OG
l_int|1
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;segment_modify_shared: could not reload segment %s&quot;
l_string|&quot; - diag returned error (%ld)&bslash;n&quot;
comma
id|name
comma
id|seg-&gt;end
)paren
suffix:semicolon
id|rc
op_assign
id|dcss_diag_translate_rc
(paren
id|seg-&gt;end
)paren
suffix:semicolon
r_goto
id|out_del
suffix:semicolon
)brace
id|seg-&gt;do_nonshared
op_assign
id|do_nonshared
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
id|out_del
suffix:colon
id|list_del
c_func
(paren
op_amp
id|seg-&gt;list
)paren
suffix:semicolon
id|dcss_diag
c_func
(paren
id|DCSS_PURGESEG
comma
id|seg-&gt;dcss_name
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
id|kfree
(paren
id|seg
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Decrease the use count of a DCSS segment and remove&n; * it from the address space if nobody is using it&n; * any longer.&n; */
r_void
DECL|function|segment_unload
id|segment_unload
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_struct
id|dcss_segment
op_star
id|seg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
id|seg
op_assign
id|segment_by_name
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
l_int|NULL
)paren
(brace
id|PRINT_ERR
(paren
l_string|&quot;could not find segment %s in segment_unload, &quot;
l_string|&quot;please report to linux390@de.ibm.com&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|seg-&gt;ref_count
)paren
op_eq
l_int|0
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|seg-&gt;list
)paren
suffix:semicolon
id|dcss_diag
c_func
(paren
id|DCSS_PURGESEG
comma
id|seg-&gt;dcss_name
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|seg
)paren
suffix:semicolon
)brace
id|out_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * save segment content permanently&n; */
r_void
DECL|function|segment_save
id|segment_save
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|dcss_segment
op_star
id|seg
suffix:semicolon
r_int
id|startpfn
op_assign
l_int|0
suffix:semicolon
r_int
id|endpfn
op_assign
l_int|0
suffix:semicolon
r_char
id|cmd1
(braket
l_int|160
)braket
suffix:semicolon
r_char
id|cmd2
(braket
l_int|80
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
id|seg
op_assign
id|segment_by_name
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
l_int|NULL
)paren
(brace
id|PRINT_ERR
(paren
l_string|&quot;could not find segment %s in segment_save, please report to linux390@de.ibm.com&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|startpfn
op_assign
id|seg-&gt;start_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|endpfn
op_assign
(paren
id|seg-&gt;end
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|sprintf
c_func
(paren
id|cmd1
comma
l_string|&quot;DEFSEG %s&quot;
comma
id|name
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
id|seg-&gt;segcnt
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|cmd1
op_plus
id|strlen
c_func
(paren
id|cmd1
)paren
comma
l_string|&quot; %X-%X %s&quot;
comma
id|seg-&gt;range
(braket
id|i
)braket
dot
id|start
op_rshift
id|PAGE_SHIFT
comma
id|seg-&gt;range
(braket
id|i
)braket
dot
id|end
op_rshift
id|PAGE_SHIFT
comma
id|segtype_string
(braket
id|seg-&gt;range
(braket
id|i
)braket
dot
id|start
op_amp
l_int|0xff
)braket
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|cmd2
comma
l_string|&quot;SAVESEG %s&quot;
comma
id|name
)paren
suffix:semicolon
id|cpcmd
c_func
(paren
id|cmd1
comma
l_int|NULL
comma
l_int|80
)paren
suffix:semicolon
id|cpcmd
c_func
(paren
id|cmd2
comma
l_int|NULL
comma
l_int|80
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcss_lock
)paren
suffix:semicolon
)brace
DECL|variable|segment_load
id|EXPORT_SYMBOL
c_func
(paren
id|segment_load
)paren
suffix:semicolon
DECL|variable|segment_unload
id|EXPORT_SYMBOL
c_func
(paren
id|segment_unload
)paren
suffix:semicolon
DECL|variable|segment_save
id|EXPORT_SYMBOL
c_func
(paren
id|segment_save
)paren
suffix:semicolon
DECL|variable|segment_type
id|EXPORT_SYMBOL
c_func
(paren
id|segment_type
)paren
suffix:semicolon
DECL|variable|segment_modify_shared
id|EXPORT_SYMBOL
c_func
(paren
id|segment_modify_shared
)paren
suffix:semicolon
eof
