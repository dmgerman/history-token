multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_MODULE_H
DECL|macro|_ASM_IA64_SN_MODULE_H
mdefine_line|#define _ASM_IA64_SN_MODULE_H
multiline_comment|/* parameter for format_module_id() */
DECL|macro|MODULE_FORMAT_BRIEF
mdefine_line|#define MODULE_FORMAT_BRIEF&t;1
DECL|macro|MODULE_FORMAT_LONG
mdefine_line|#define MODULE_FORMAT_LONG&t;2
DECL|macro|MODULE_FORMAT_LCD
mdefine_line|#define MODULE_FORMAT_LCD&t;3
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
multiline_comment|/*&n; * Macros for encoding and decoding rack IDs&n; * A rack number consists of three parts:&n; *   class (0==CPU/mixed, 1==I/O), group, number&n; *&n; * Rack number is stored just as it is displayed on the screen:&n; * a 3-decimal-digit number.&n; */
DECL|macro|RACK_CLASS_DVDR
mdefine_line|#define RACK_CLASS_DVDR         100
DECL|macro|RACK_GROUP_DVDR
mdefine_line|#define RACK_GROUP_DVDR         10
DECL|macro|RACK_NUM_DVDR
mdefine_line|#define RACK_NUM_DVDR           1
DECL|macro|RACK_CREATE_RACKID
mdefine_line|#define RACK_CREATE_RACKID(_c, _g, _n)  ((_c) * RACK_CLASS_DVDR +       &bslash;&n;        (_g) * RACK_GROUP_DVDR + (_n) * RACK_NUM_DVDR)
DECL|macro|RACK_GET_CLASS
mdefine_line|#define RACK_GET_CLASS(_r)              ((_r) / RACK_CLASS_DVDR)
DECL|macro|RACK_GET_GROUP
mdefine_line|#define RACK_GET_GROUP(_r)              (((_r) - RACK_GET_CLASS(_r) *   &bslash;&n;            RACK_CLASS_DVDR) / RACK_GROUP_DVDR)
DECL|macro|RACK_GET_NUM
mdefine_line|#define RACK_GET_NUM(_r)                (((_r) - RACK_GET_CLASS(_r) *   &bslash;&n;            RACK_CLASS_DVDR - RACK_GET_GROUP(_r) *      &bslash;&n;            RACK_GROUP_DVDR) / RACK_NUM_DVDR)
multiline_comment|/*&n; * Macros for encoding and decoding rack IDs&n; * A rack number consists of three parts:&n; *   class      1 bit, 0==CPU/mixed, 1==I/O&n; *   group      2 bits for CPU/mixed, 3 bits for I/O&n; *   number     3 bits for CPU/mixed, 2 bits for I/O (1 based)&n; */
DECL|macro|RACK_GROUP_BITS
mdefine_line|#define RACK_GROUP_BITS(_r)     (RACK_GET_CLASS(_r) ? 3 : 2)
DECL|macro|RACK_NUM_BITS
mdefine_line|#define RACK_NUM_BITS(_r)       (RACK_GET_CLASS(_r) ? 2 : 3)
DECL|macro|RACK_CLASS_MASK
mdefine_line|#define RACK_CLASS_MASK(_r)     0x20
DECL|macro|RACK_CLASS_SHFT
mdefine_line|#define RACK_CLASS_SHFT(_r)     5
DECL|macro|RACK_ADD_CLASS
mdefine_line|#define RACK_ADD_CLASS(_r, _c)  &bslash;&n;        ((_r) |= (_c) &lt;&lt; RACK_CLASS_SHFT(_r) &amp; RACK_CLASS_MASK(_r))
DECL|macro|RACK_GROUP_SHFT
mdefine_line|#define RACK_GROUP_SHFT(_r)     RACK_NUM_BITS(_r)
DECL|macro|RACK_GROUP_MASK
mdefine_line|#define RACK_GROUP_MASK(_r)     &bslash;&n;        ( (((unsigned)1&lt;&lt;RACK_GROUP_BITS(_r)) - 1) &lt;&lt; RACK_GROUP_SHFT(_r) )
DECL|macro|RACK_ADD_GROUP
mdefine_line|#define RACK_ADD_GROUP(_r, _g)  &bslash;&n;        ((_r) |= (_g) &lt;&lt; RACK_GROUP_SHFT(_r) &amp; RACK_GROUP_MASK(_r))
DECL|macro|RACK_NUM_SHFT
mdefine_line|#define RACK_NUM_SHFT(_r)       0
DECL|macro|RACK_NUM_MASK
mdefine_line|#define RACK_NUM_MASK(_r)       &bslash;&n;        ( (((unsigned)1&lt;&lt;RACK_NUM_BITS(_r)) - 1) &lt;&lt; RACK_NUM_SHFT(_r) )
DECL|macro|RACK_ADD_NUM
mdefine_line|#define RACK_ADD_NUM(_r, _n)    &bslash;&n;        ((_r) |= ((_n) - 1) &lt;&lt; RACK_NUM_SHFT(_r) &amp; RACK_NUM_MASK(_r))
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
DECL|macro|MODULE_CGBRICK
mdefine_line|#define MODULE_CGBRICK&t;&t;11
DECL|macro|MODULE_OPUSBRICK
mdefine_line|#define MODULE_OPUSBRICK        12
DECL|macro|MODULE_SABRICK
mdefine_line|#define MODULE_SABRICK&t;&t;13&t;/* TIO BringUp Brick */
DECL|macro|MODULE_IABRICK
mdefine_line|#define MODULE_IABRICK&t;&t;14
DECL|macro|MODULE_PABRICK
mdefine_line|#define MODULE_PABRICK&t;&t;15
DECL|macro|MODULE_GABRICK
mdefine_line|#define MODULE_GABRICK&t;&t;16
DECL|macro|MODULE_OPUS_TIO
mdefine_line|#define MODULE_OPUS_TIO&t;&t;17&t;/* OPUS TIO Riser */
r_extern
r_char
id|brick_types
(braket
)braket
suffix:semicolon
r_extern
r_void
id|format_module_id
c_func
(paren
r_char
op_star
comma
id|moduleid_t
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_MODULE_H */
eof
