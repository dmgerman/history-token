multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_MODULE_H
DECL|macro|_ASM_IA64_SN_MODULE_H
mdefine_line|#define _ASM_IA64_SN_MODULE_H
macro_line|#ifdef&t;__cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/systeminfo.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/ksys/elsc.h&gt;
DECL|macro|MODULE_MAX
mdefine_line|#define MODULE_MAX&t;&t;&t;128
DECL|macro|MODULE_MAX_NODES
mdefine_line|#define MODULE_MAX_NODES&t;&t;2
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
multiline_comment|/*&n; *&t;Module id format&n; *&n; *&t;31-16&t;Rack ID (encoded class, group, number - 16-bit unsigned int)&n; *&t; 15-8&t;Brick type (8-bit ascii character)&n; *&t;  7-0&t;Bay (brick position in rack (0-63) - 8-bit unsigned int)&n; *&n; */
multiline_comment|/*&n; * Macros for getting the brick type&n; */
DECL|macro|MODULE_BTYPE_MASK
mdefine_line|#define MODULE_BTYPE_MASK&t;0xff00
DECL|macro|MODULE_BTYPE_SHFT
mdefine_line|#define MODULE_BTYPE_SHFT&t;8
DECL|macro|MODULE_GET_BTYPE
mdefine_line|#define MODULE_GET_BTYPE(_m)&t;(((_m) &amp; MODULE_BTYPE_MASK) &gt;&gt; MODULE_BTYPE_SHFT)
DECL|macro|MODULE_BT_TO_CHAR
mdefine_line|#define MODULE_BT_TO_CHAR(_b)&t;((char)(_b))
DECL|macro|MODULE_GET_BTCHAR
mdefine_line|#define MODULE_GET_BTCHAR(_m)&t;(MODULE_BT_TO_CHAR(MODULE_GET_BTYPE(_m)))
multiline_comment|/*&n; * Macros for getting the rack ID.&n; */
DECL|macro|MODULE_RACK_MASK
mdefine_line|#define MODULE_RACK_MASK&t;0xffff0000
DECL|macro|MODULE_RACK_SHFT
mdefine_line|#define MODULE_RACK_SHFT&t;16
DECL|macro|MODULE_GET_RACK
mdefine_line|#define MODULE_GET_RACK(_m)&t;(((_m) &amp; MODULE_RACK_MASK) &gt;&gt; MODULE_RACK_SHFT)
multiline_comment|/*&n; * Macros for getting the brick position&n; */
DECL|macro|MODULE_BPOS_MASK
mdefine_line|#define MODULE_BPOS_MASK&t;0x00ff
DECL|macro|MODULE_BPOS_SHFT
mdefine_line|#define MODULE_BPOS_SHFT&t;0
DECL|macro|MODULE_GET_BPOS
mdefine_line|#define MODULE_GET_BPOS(_m)&t;(((_m) &amp; MODULE_BPOS_MASK) &gt;&gt; MODULE_BPOS_SHFT)
multiline_comment|/*&n; * Macros for constructing moduleid_t&squot;s&n; */
DECL|macro|RBT_TO_MODULE
mdefine_line|#define RBT_TO_MODULE(_r, _b, _t) ((_r) &lt;&lt; MODULE_RACK_SHFT | &bslash;&n;&t;&t;&t;&t;   (_b) &lt;&lt; MODULE_BPOS_SHFT | &bslash;&n;&t;&t;&t;&t;   (_t) &lt;&lt; MODULE_BTYPE_SHFT)
multiline_comment|/*&n; * Macros for encoding and decoding rack IDs&n; * A rack number consists of three parts:&n; *   class (0==CPU/mixed, 1==I/O), group, number&n; *&n; * Rack number is stored just as it is displayed on the screen:&n; * a 3-decimal-digit number.&n; */
DECL|macro|RACK_CLASS_DVDR
mdefine_line|#define RACK_CLASS_DVDR&t;&t;100
DECL|macro|RACK_GROUP_DVDR
mdefine_line|#define RACK_GROUP_DVDR&t;&t;10
DECL|macro|RACK_NUM_DVDR
mdefine_line|#define RACK_NUM_DVDR&t;&t;1
DECL|macro|RACK_CREATE_RACKID
mdefine_line|#define RACK_CREATE_RACKID(_c, _g, _n)&t;((_c) * RACK_CLASS_DVDR +&t;&bslash;&n;&t;(_g) * RACK_GROUP_DVDR + (_n) * RACK_NUM_DVDR)
DECL|macro|RACK_GET_CLASS
mdefine_line|#define RACK_GET_CLASS(_r)              ((_r) / RACK_CLASS_DVDR)
DECL|macro|RACK_GET_GROUP
mdefine_line|#define RACK_GET_GROUP(_r)              (((_r) - RACK_GET_CLASS(_r) *   &bslash;&n;            RACK_CLASS_DVDR) / RACK_GROUP_DVDR)
DECL|macro|RACK_GET_NUM
mdefine_line|#define RACK_GET_NUM(_r)                (((_r) - RACK_GET_CLASS(_r) *   &bslash;&n;            RACK_CLASS_DVDR - RACK_GET_GROUP(_r) *      &bslash;&n;            RACK_GROUP_DVDR) / RACK_NUM_DVDR)
multiline_comment|/*&n; * Macros for encoding and decoding rack IDs&n; * A rack number consists of three parts:&n; *   class&t;1 bit, 0==CPU/mixed, 1==I/O&n; *   group&t;2 bits for CPU/mixed, 3 bits for I/O&n; *   number&t;3 bits for CPU/mixed, 2 bits for I/O (1 based)&n; */
DECL|macro|RACK_GROUP_BITS
mdefine_line|#define RACK_GROUP_BITS(_r)&t;(RACK_GET_CLASS(_r) ? 3 : 2)
DECL|macro|RACK_NUM_BITS
mdefine_line|#define RACK_NUM_BITS(_r)&t;(RACK_GET_CLASS(_r) ? 2 : 3)
DECL|macro|RACK_CLASS_MASK
mdefine_line|#define RACK_CLASS_MASK(_r)&t;0x20
DECL|macro|RACK_CLASS_SHFT
mdefine_line|#define RACK_CLASS_SHFT(_r)&t;5
DECL|macro|RACK_ADD_CLASS
mdefine_line|#define RACK_ADD_CLASS(_r, _c)&t;&bslash;&n;&t;((_r) |= (_c) &lt;&lt; RACK_CLASS_SHFT(_r) &amp; RACK_CLASS_MASK(_r))
DECL|macro|RACK_GROUP_SHFT
mdefine_line|#define RACK_GROUP_SHFT(_r)&t;RACK_NUM_BITS(_r)
DECL|macro|RACK_GROUP_MASK
mdefine_line|#define RACK_GROUP_MASK(_r)&t;&bslash;&n;&t;( (((unsigned)1&lt;&lt;RACK_GROUP_BITS(_r)) - 1) &lt;&lt; RACK_GROUP_SHFT(_r) )
DECL|macro|RACK_ADD_GROUP
mdefine_line|#define RACK_ADD_GROUP(_r, _g)&t;&bslash;&n;&t;((_r) |= (_g) &lt;&lt; RACK_GROUP_SHFT(_r) &amp; RACK_GROUP_MASK(_r))
DECL|macro|RACK_NUM_SHFT
mdefine_line|#define RACK_NUM_SHFT(_r)&t;0
DECL|macro|RACK_NUM_MASK
mdefine_line|#define RACK_NUM_MASK(_r)&t;&bslash;&n;&t;( (((unsigned)1&lt;&lt;RACK_NUM_BITS(_r)) - 1) &lt;&lt; RACK_NUM_SHFT(_r) )
DECL|macro|RACK_ADD_NUM
mdefine_line|#define RACK_ADD_NUM(_r, _n)&t;&bslash;&n;&t;((_r) |= ((_n) - 1) &lt;&lt; RACK_NUM_SHFT(_r) &amp; RACK_NUM_MASK(_r))
multiline_comment|/*&n; * Brick type definitions&n; */
DECL|macro|MAX_BRICK_TYPES
mdefine_line|#define MAX_BRICK_TYPES         256 /* brick type is stored as uchar */
r_extern
r_char
id|brick_types
(braket
)braket
suffix:semicolon
DECL|macro|MODULE_CBRICK
mdefine_line|#define MODULE_CBRICK           0
DECL|macro|MODULE_RBRICK
mdefine_line|#define MODULE_RBRICK           1
DECL|macro|MODULE_IBRICK
mdefine_line|#define MODULE_IBRICK           2
DECL|macro|MODULE_KBRICK
mdefine_line|#define MODULE_KBRICK           3
DECL|macro|MODULE_XBRICK
mdefine_line|#define MODULE_XBRICK           4
DECL|macro|MODULE_DBRICK
mdefine_line|#define MODULE_DBRICK           5
DECL|macro|MODULE_PBRICK
mdefine_line|#define MODULE_PBRICK           6
DECL|macro|MODULE_NBRICK
mdefine_line|#define MODULE_NBRICK           7
DECL|macro|MODULE_PEBRICK
mdefine_line|#define MODULE_PEBRICK          8
DECL|macro|MODULE_PXBRICK
mdefine_line|#define MODULE_PXBRICK          9
DECL|macro|MODULE_IXBRICK
mdefine_line|#define MODULE_IXBRICK          10
multiline_comment|/*&n; * Moduleid_t comparison macros&n; */
multiline_comment|/* Don&squot;t compare the brick type:  only the position is significant */
DECL|macro|MODULE_CMP
mdefine_line|#define MODULE_CMP(_m1, _m2)    (((_m1)&amp;(MODULE_RACK_MASK|MODULE_BPOS_MASK)) -&bslash;&n;                                 ((_m2)&amp;(MODULE_RACK_MASK|MODULE_BPOS_MASK)))
DECL|macro|MODULE_MATCH
mdefine_line|#define MODULE_MATCH(_m1, _m2)  (MODULE_CMP((_m1),(_m2)) == 0)
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
DECL|member|geoid
id|geoid_t
id|geoid
(braket
id|MODULE_MAX_NODES
)braket
suffix:semicolon
r_struct
(brace
DECL|member|moduleid
r_char
id|moduleid
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|io
)brace
id|io
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
multiline_comment|/* System serial number info (used by SN1) */
DECL|member|sys_snum
r_char
id|sys_snum
(braket
id|MAX_SERIAL_NUM_SIZE
)braket
suffix:semicolon
DECL|member|sys_snum_valid
r_int
id|sys_snum_valid
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
r_int
id|get_kmod_sys_snum
c_func
(paren
id|cmoduleid_t
id|cmod
comma
r_char
op_star
id|snum
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
macro_line|#endif /* _ASM_IA64_SN_MODULE_H */
eof
