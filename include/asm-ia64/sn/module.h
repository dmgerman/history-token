multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_MODULE_H
DECL|macro|_ASM_SN_MODULE_H
mdefine_line|#define _ASM_SN_MODULE_H
macro_line|#ifdef&t;__cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/systeminfo.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/ksys/elsc.h&gt;
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
macro_line|#ifdef BRINGUP /* max. number of modules?  Should be about 300.*/
DECL|macro|MODULE_MAX
mdefine_line|#define MODULE_MAX&t;&t;&t;56
macro_line|#endif /* BRINGUP */
DECL|macro|MODULE_MAX_NODES
mdefine_line|#define MODULE_MAX_NODES&t;&t;1
macro_line|#endif /* CONFIG_SGI_IP35 */
DECL|macro|MODULE_HIST_CNT
mdefine_line|#define MODULE_HIST_CNT&t;&t;&t;16
DECL|macro|MAX_MODULE_LEN
mdefine_line|#define MAX_MODULE_LEN&t;&t;&t;16
multiline_comment|/* Well-known module IDs */
DECL|macro|MODULE_UNKNOWN
mdefine_line|#define MODULE_UNKNOWN&t;&t;(-2) /* initial value of klconfig brd_module */
multiline_comment|/* #define INVALID_MODULE&t;(-1) ** generic invalid moduleid_t (arch.h) */
DECL|macro|MODULE_NOT_SET
mdefine_line|#define MODULE_NOT_SET&t;&t;0    /* module ID not set in sys ctlrs. */
multiline_comment|/* parameter for format_module_id() */
DECL|macro|MODULE_FORMAT_BRIEF
mdefine_line|#define MODULE_FORMAT_BRIEF&t;1
DECL|macro|MODULE_FORMAT_LONG
mdefine_line|#define MODULE_FORMAT_LONG&t;2
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
multiline_comment|/*&n; *&t;Module id format&n; *&n; *&t;  15-12 Brick type (enumerated)&n; *&t;   11-6&t;Rack ID&t;(encoded class, group, number)&n; *&t;    5-0 Brick position in rack (0-63)&n; */
multiline_comment|/*&n; * Macros for getting the brick type&n; */
DECL|macro|MODULE_BTYPE_MASK
mdefine_line|#define MODULE_BTYPE_MASK&t;0xf000
DECL|macro|MODULE_BTYPE_SHFT
mdefine_line|#define MODULE_BTYPE_SHFT&t;12
DECL|macro|MODULE_GET_BTYPE
mdefine_line|#define MODULE_GET_BTYPE(_m)&t;(((_m) &amp; MODULE_BTYPE_MASK) &gt;&gt; MODULE_BTYPE_SHFT)
DECL|macro|MODULE_BT_TO_CHAR
mdefine_line|#define MODULE_BT_TO_CHAR(_b)&t;(brick_types[(_b)])
DECL|macro|MODULE_GET_BTCHAR
mdefine_line|#define MODULE_GET_BTCHAR(_m)&t;(MODULE_BT_TO_CHAR(MODULE_GET_BTYPE(_m)))
multiline_comment|/*&n; * Macros for getting the rack ID.&n; */
DECL|macro|MODULE_RACK_MASK
mdefine_line|#define MODULE_RACK_MASK&t;0x0fc0
DECL|macro|MODULE_RACK_SHFT
mdefine_line|#define MODULE_RACK_SHFT&t;6
DECL|macro|MODULE_GET_RACK
mdefine_line|#define MODULE_GET_RACK(_m)&t;(((_m) &amp; MODULE_RACK_MASK) &gt;&gt; MODULE_RACK_SHFT)
multiline_comment|/*&n; * Macros for getting the brick position&n; */
DECL|macro|MODULE_BPOS_MASK
mdefine_line|#define MODULE_BPOS_MASK&t;0x003f
DECL|macro|MODULE_BPOS_SHFT
mdefine_line|#define MODULE_BPOS_SHFT&t;0
DECL|macro|MODULE_GET_BPOS
mdefine_line|#define MODULE_GET_BPOS(_m)&t;(((_m) &amp; MODULE_BPOS_MASK) &gt;&gt; MODULE_BPOS_SHFT)
multiline_comment|/*&n; * Macros for constructing moduleid_t&squot;s&n; */
DECL|macro|RBT_TO_MODULE
mdefine_line|#define RBT_TO_MODULE(_r, _b, _t) ((_r) &lt;&lt; MODULE_RACK_SHFT | &bslash;&n;&t;&t;&t;&t;   (_b) &lt;&lt; MODULE_BPOS_SHFT | &bslash;&n;&t;&t;&t;&t;   (_t) &lt;&lt; MODULE_BTYPE_SHFT)
multiline_comment|/*&n; * Macros for encoding and decoding rack IDs&n; * A rack number consists of three parts:&n; *   class&t;1 bit, 0==CPU/mixed, 1==I/O&n; *   group&t;2 bits for CPU/mixed, 3 bits for I/O&n; *   number&t;3 bits for CPU/mixed, 2 bits for I/O (1 based)&n; */
DECL|macro|RACK_GROUP_BITS
mdefine_line|#define RACK_GROUP_BITS(_r)&t;(RACK_GET_CLASS(_r) ? 3 : 2)
DECL|macro|RACK_NUM_BITS
mdefine_line|#define RACK_NUM_BITS(_r)&t;(RACK_GET_CLASS(_r) ? 2 : 3)
DECL|macro|RACK_CLASS_MASK
mdefine_line|#define RACK_CLASS_MASK(_r)&t;0x20
DECL|macro|RACK_CLASS_SHFT
mdefine_line|#define RACK_CLASS_SHFT(_r)&t;5
DECL|macro|RACK_GET_CLASS
mdefine_line|#define RACK_GET_CLASS(_r)&t;&bslash;&n;&t;(((_r) &amp; RACK_CLASS_MASK(_r)) &gt;&gt; RACK_CLASS_SHFT(_r))
DECL|macro|RACK_ADD_CLASS
mdefine_line|#define RACK_ADD_CLASS(_r, _c)&t;&bslash;&n;&t;((_r) |= (_c) &lt;&lt; RACK_CLASS_SHFT(_r) &amp; RACK_CLASS_MASK(_r))
DECL|macro|RACK_GROUP_SHFT
mdefine_line|#define RACK_GROUP_SHFT(_r)&t;RACK_NUM_BITS(_r)
DECL|macro|RACK_GROUP_MASK
mdefine_line|#define RACK_GROUP_MASK(_r)&t;&bslash;&n;&t;( (((unsigned)1&lt;&lt;RACK_GROUP_BITS(_r)) - 1) &lt;&lt; RACK_GROUP_SHFT(_r) )
DECL|macro|RACK_GET_GROUP
mdefine_line|#define RACK_GET_GROUP(_r)&t;&bslash;&n;&t;(((_r) &amp; RACK_GROUP_MASK(_r)) &gt;&gt; RACK_GROUP_SHFT(_r))
DECL|macro|RACK_ADD_GROUP
mdefine_line|#define RACK_ADD_GROUP(_r, _g)&t;&bslash;&n;&t;((_r) |= (_g) &lt;&lt; RACK_GROUP_SHFT(_r) &amp; RACK_GROUP_MASK(_r))
DECL|macro|RACK_NUM_SHFT
mdefine_line|#define RACK_NUM_SHFT(_r)&t;0
DECL|macro|RACK_NUM_MASK
mdefine_line|#define RACK_NUM_MASK(_r)&t;&bslash;&n;&t;( (((unsigned)1&lt;&lt;RACK_NUM_BITS(_r)) - 1) &lt;&lt; RACK_NUM_SHFT(_r) )
DECL|macro|RACK_GET_NUM
mdefine_line|#define RACK_GET_NUM(_r)&t;&bslash;&n;&t;( (((_r) &amp; RACK_NUM_MASK(_r)) &gt;&gt; RACK_NUM_SHFT(_r)) + 1 )
DECL|macro|RACK_ADD_NUM
mdefine_line|#define RACK_ADD_NUM(_r, _n)&t;&bslash;&n;&t;((_r) |= ((_n) - 1) &lt;&lt; RACK_NUM_SHFT(_r) &amp; RACK_NUM_MASK(_r))
multiline_comment|/*&n; * Brick type definitions&n; */
DECL|macro|MAX_BRICK_TYPES
mdefine_line|#define MAX_BRICK_TYPES&t;&t;16 /* 1 &lt;&lt; (MODULE_RACK_SHFT - MODULE_BTYPE_SHFT */
r_extern
r_char
id|brick_types
(braket
)braket
suffix:semicolon
DECL|macro|MODULE_CBRICK
mdefine_line|#define MODULE_CBRICK&t;&t;0
DECL|macro|MODULE_RBRICK
mdefine_line|#define MODULE_RBRICK&t;&t;1
DECL|macro|MODULE_IBRICK
mdefine_line|#define MODULE_IBRICK&t;&t;2
DECL|macro|MODULE_KBRICK
mdefine_line|#define MODULE_KBRICK&t;&t;3
DECL|macro|MODULE_XBRICK
mdefine_line|#define MODULE_XBRICK&t;&t;4
DECL|macro|MODULE_DBRICK
mdefine_line|#define MODULE_DBRICK&t;&t;5
DECL|macro|MODULE_PBRICK
mdefine_line|#define MODULE_PBRICK&t;&t;6
multiline_comment|/*&n; * Moduleid_t comparison macros&n; */
multiline_comment|/* Don&squot;t compare the brick type:  only the position is significant */
DECL|macro|MODULE_CMP
mdefine_line|#define MODULE_CMP(_m1, _m2)&t;(((_m1)&amp;(MODULE_RACK_MASK|MODULE_BPOS_MASK)) -&bslash;&n;&t;&t;&t;&t; ((_m2)&amp;(MODULE_RACK_MASK|MODULE_BPOS_MASK)))
DECL|macro|MODULE_MATCH
mdefine_line|#define MODULE_MATCH(_m1, _m2)&t;(MODULE_CMP((_m1),(_m2)) == 0)
macro_line|#else
multiline_comment|/*&n; * Some code that uses this macro will not be conditionally compiled.&n; */
DECL|macro|MODULE_GET_BTCHAR
mdefine_line|#define MODULE_GET_BTCHAR(_m)&t;(&squot;?&squot;)
DECL|macro|MODULE_CMP
mdefine_line|#define MODULE_CMP(_m1, _m2)&t;((_m1) - (_m2))
DECL|macro|MODULE_MATCH
mdefine_line|#define MODULE_MATCH(_m1, _m2)&t;(MODULE_CMP((_m1),(_m2)) == 0)
macro_line|#endif /* CONFIG_SGI_IP35 || CONFIG_IA64_SGI_SN1 */
DECL|typedef|module_t
r_typedef
r_struct
id|module_s
id|module_t
suffix:semicolon
DECL|struct|module_s
r_struct
id|module_s
(brace
DECL|member|id
id|moduleid_t
id|id
suffix:semicolon
multiline_comment|/* Module ID of this module        */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Lock for this structure&t;   */
multiline_comment|/* List of nodes in this module */
DECL|member|nodes
id|cnodeid_t
id|nodes
(braket
id|MODULE_MAX_NODES
)braket
suffix:semicolon
DECL|member|nodecnt
r_int
id|nodecnt
suffix:semicolon
multiline_comment|/* Number of nodes in array        */
multiline_comment|/* Fields for Module System Controller */
DECL|member|mesgpend
r_int
id|mesgpend
suffix:semicolon
multiline_comment|/* Message pending                 */
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
multiline_comment|/* Shutdown in progress            */
DECL|member|thdcnt
r_struct
id|semaphore
id|thdcnt
suffix:semicolon
multiline_comment|/* Threads finished counter        */
DECL|member|elsc
id|elsc_t
id|elsc
suffix:semicolon
DECL|member|elsclock
id|spinlock_t
id|elsclock
suffix:semicolon
DECL|member|intrhist
id|time_t
id|intrhist
(braket
id|MODULE_HIST_CNT
)braket
suffix:semicolon
DECL|member|histptr
r_int
id|histptr
suffix:semicolon
DECL|member|hbt_active
r_int
id|hbt_active
suffix:semicolon
multiline_comment|/* MSC heartbeat monitor active    */
DECL|member|hbt_last
r_uint64
id|hbt_last
suffix:semicolon
multiline_comment|/* RTC when last heartbeat sent    */
multiline_comment|/* Module serial number info */
r_union
(brace
DECL|member|snum_str
r_char
id|snum_str
(braket
id|MAX_SERIAL_NUM_SIZE
)braket
suffix:semicolon
multiline_comment|/* used by CONFIG_SGI_IP27    */
DECL|member|snum_int
r_uint64
id|snum_int
suffix:semicolon
multiline_comment|/* used by speedo */
DECL|member|snum
)brace
id|snum
suffix:semicolon
DECL|member|snum_valid
r_int
id|snum_valid
suffix:semicolon
DECL|member|disable_alert
r_int
id|disable_alert
suffix:semicolon
DECL|member|count_down
r_int
id|count_down
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* module.c */
r_extern
id|module_t
op_star
id|modules
(braket
id|MODULE_MAX
)braket
suffix:semicolon
multiline_comment|/* Indexed by cmoduleid_t   */
r_extern
r_int
id|nummodules
suffix:semicolon
macro_line|#ifndef CONFIG_IA64_SGI_IO
multiline_comment|/* Clashes with LINUX stuff */
r_extern
r_void
id|module_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
id|module_t
op_star
id|module_lookup
c_func
(paren
id|moduleid_t
id|id
)paren
suffix:semicolon
r_extern
id|elsc_t
op_star
id|get_elsc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|get_kmod_info
c_func
(paren
id|cmoduleid_t
id|cmod
comma
id|module_info_t
op_star
id|mod_info
)paren
suffix:semicolon
r_extern
r_void
id|format_module_id
c_func
(paren
r_char
op_star
id|buffer
comma
id|moduleid_t
id|m
comma
r_int
id|fmt
)paren
suffix:semicolon
r_extern
r_int
id|parse_module_id
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#ifdef&t;__cplusplus
)brace
macro_line|#endif
macro_line|#endif /* _ASM_SN_MODULE_H */
eof
