multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_TYPES
DECL|macro|_H_JFS_TYPES
mdefine_line|#define&t;_H_JFS_TYPES
multiline_comment|/*&n; *&t;jfs_types.h:&n; *&n; * basic type/utility  definitions&n; *&n; * note: this header file must be the 1st include file&n; * of JFS include list in all JFS .c file.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &quot;endian24.h&quot;
multiline_comment|/*&n; * transaction and lock id&squot;s&n; */
DECL|typedef|tid_t
r_typedef
id|uint
id|tid_t
suffix:semicolon
DECL|typedef|lid_t
r_typedef
id|uint
id|lid_t
suffix:semicolon
multiline_comment|/*&n; * Almost identical to Linux&squot;s timespec, but not quite&n; */
DECL|struct|timestruc_t
r_struct
id|timestruc_t
(brace
DECL|member|tv_sec
id|u32
id|tv_sec
suffix:semicolon
DECL|member|tv_nsec
id|u32
id|tv_nsec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;handy&n; */
DECL|macro|LEFTMOSTONE
mdefine_line|#define LEFTMOSTONE&t;0x80000000
DECL|macro|HIGHORDER
mdefine_line|#define&t;HIGHORDER&t;0x80000000u&t;/* high order bit on            */
DECL|macro|ONES
mdefine_line|#define&t;ONES&t;&t;0xffffffffu&t;/* all bit on                   */
DECL|typedef|boolean_t
r_typedef
r_int
id|boolean_t
suffix:semicolon
DECL|macro|TRUE
mdefine_line|#define TRUE 1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
multiline_comment|/*&n; *&t;logical xd (lxd)&n; */
r_typedef
r_struct
(brace
DECL|member|len
r_int
id|len
suffix:colon
l_int|24
suffix:semicolon
DECL|member|off1
r_int
id|off1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|off2
id|u32
id|off2
suffix:semicolon
DECL|typedef|lxd_t
)brace
id|lxd_t
suffix:semicolon
multiline_comment|/* lxd_t field construction */
DECL|macro|LXDlength
mdefine_line|#define&t;LXDlength(lxd, length32)&t;( (lxd)-&gt;len = length32 )
DECL|macro|LXDoffset
mdefine_line|#define&t;LXDoffset(lxd, offset64)&bslash;&n;{&bslash;&n;&t;(lxd)-&gt;off1 = ((s64)offset64) &gt;&gt; 32;&bslash;&n;&t;(lxd)-&gt;off2 = (offset64) &amp; 0xffffffff;&bslash;&n;}
multiline_comment|/* lxd_t field extraction */
DECL|macro|lengthLXD
mdefine_line|#define&t;lengthLXD(lxd)&t;( (lxd)-&gt;len )
DECL|macro|offsetLXD
mdefine_line|#define&t;offsetLXD(lxd)&bslash;&n;&t;( ((s64)((lxd)-&gt;off1)) &lt;&lt; 32 | (lxd)-&gt;off2 )
multiline_comment|/* lxd list */
r_typedef
r_struct
(brace
DECL|member|maxnlxd
id|s16
id|maxnlxd
suffix:semicolon
DECL|member|nlxd
id|s16
id|nlxd
suffix:semicolon
DECL|member|lxd
id|lxd_t
op_star
id|lxd
suffix:semicolon
DECL|typedef|lxdlist_t
)brace
id|lxdlist_t
suffix:semicolon
multiline_comment|/*&n; *&t;physical xd (pxd)&n; */
r_typedef
r_struct
(brace
DECL|member|len
r_int
id|len
suffix:colon
l_int|24
suffix:semicolon
DECL|member|addr1
r_int
id|addr1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|addr2
id|u32
id|addr2
suffix:semicolon
DECL|typedef|pxd_t
)brace
id|pxd_t
suffix:semicolon
multiline_comment|/* xd_t field construction */
DECL|macro|PXDlength
mdefine_line|#define&t;PXDlength(pxd, length32)&t;((pxd)-&gt;len = __cpu_to_le24(length32))
DECL|macro|PXDaddress
mdefine_line|#define&t;PXDaddress(pxd, address64)&bslash;&n;{&bslash;&n;&t;(pxd)-&gt;addr1 = ((s64)address64) &gt;&gt; 32;&bslash;&n;&t;(pxd)-&gt;addr2 = __cpu_to_le32((address64) &amp; 0xffffffff);&bslash;&n;}
multiline_comment|/* xd_t field extraction */
DECL|macro|lengthPXD
mdefine_line|#define&t;lengthPXD(pxd)&t;__le24_to_cpu((pxd)-&gt;len)
DECL|macro|addressPXD
mdefine_line|#define&t;addressPXD(pxd)&bslash;&n;&t;( ((s64)((pxd)-&gt;addr1)) &lt;&lt; 32 | __le32_to_cpu((pxd)-&gt;addr2))
multiline_comment|/* pxd list */
r_typedef
r_struct
(brace
DECL|member|maxnpxd
id|s16
id|maxnpxd
suffix:semicolon
DECL|member|npxd
id|s16
id|npxd
suffix:semicolon
DECL|member|pxd
id|pxd_t
id|pxd
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|pxdlist_t
)brace
id|pxdlist_t
suffix:semicolon
multiline_comment|/*&n; *&t;data extent descriptor (dxd)&n; */
r_typedef
r_struct
(brace
DECL|member|flag
r_int
id|flag
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 1: flags */
DECL|member|rsrvd
r_int
id|rsrvd
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* 3: */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* 4: size in byte */
DECL|member|len
r_int
id|len
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* 3: length in unit of fsblksize */
DECL|member|addr1
r_int
id|addr1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 1: address in unit of fsblksize */
DECL|member|addr2
id|u32
id|addr2
suffix:semicolon
multiline_comment|/* 4: address in unit of fsblksize */
DECL|typedef|dxd_t
)brace
id|dxd_t
suffix:semicolon
multiline_comment|/* - 16 - */
multiline_comment|/* dxd_t flags */
DECL|macro|DXD_INDEX
mdefine_line|#define&t;DXD_INDEX&t;0x80&t;/* B+-tree index */
DECL|macro|DXD_INLINE
mdefine_line|#define&t;DXD_INLINE&t;0x40&t;/* in-line data extent */
DECL|macro|DXD_EXTENT
mdefine_line|#define&t;DXD_EXTENT&t;0x20&t;/* out-of-line single extent */
DECL|macro|DXD_FILE
mdefine_line|#define&t;DXD_FILE&t;0x10&t;/* out-of-line file (inode) */
DECL|macro|DXD_CORRUPT
mdefine_line|#define DXD_CORRUPT&t;0x08&t;/* Inconsistency detected */
multiline_comment|/* dxd_t field construction&n; *&t;Conveniently, the PXD macros work for DXD&n; */
DECL|macro|DXDlength
mdefine_line|#define&t;DXDlength&t;PXDlength
DECL|macro|DXDaddress
mdefine_line|#define&t;DXDaddress&t;PXDaddress
DECL|macro|lengthDXD
mdefine_line|#define&t;lengthDXD&t;lengthPXD
DECL|macro|addressDXD
mdefine_line|#define&t;addressDXD&t;addressPXD
multiline_comment|/*&n; *      directory entry argument&n; */
DECL|struct|component_name
r_typedef
r_struct
id|component_name
(brace
DECL|member|namlen
r_int
id|namlen
suffix:semicolon
DECL|member|name
m_wchar_t
op_star
id|name
suffix:semicolon
DECL|typedef|component_t
)brace
id|component_t
suffix:semicolon
multiline_comment|/*&n; *&t;DASD limit information - stored in directory inode&n; */
DECL|struct|dasd
r_typedef
r_struct
id|dasd
(brace
DECL|member|thresh
id|u8
id|thresh
suffix:semicolon
multiline_comment|/* Alert Threshold (in percent) */
DECL|member|delta
id|u8
id|delta
suffix:semicolon
multiline_comment|/* Alert Threshold delta (in percent)   */
DECL|member|rsrvd1
id|u8
id|rsrvd1
suffix:semicolon
DECL|member|limit_hi
id|u8
id|limit_hi
suffix:semicolon
multiline_comment|/* DASD limit (in logical blocks)       */
DECL|member|limit_lo
id|u32
id|limit_lo
suffix:semicolon
multiline_comment|/* DASD limit (in logical blocks)       */
DECL|member|rsrvd2
id|u8
id|rsrvd2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|used_hi
id|u8
id|used_hi
suffix:semicolon
multiline_comment|/* DASD usage (in logical blocks)       */
DECL|member|used_lo
id|u32
id|used_lo
suffix:semicolon
multiline_comment|/* DASD usage (in logical blocks)       */
DECL|typedef|dasd_t
)brace
id|dasd_t
suffix:semicolon
DECL|macro|DASDLIMIT
mdefine_line|#define DASDLIMIT(dasdp) &bslash;&n;&t;(((u64)((dasdp)-&gt;limit_hi) &lt;&lt; 32) + __le32_to_cpu((dasdp)-&gt;limit_lo))
DECL|macro|setDASDLIMIT
mdefine_line|#define setDASDLIMIT(dasdp, limit)&bslash;&n;{&bslash;&n;&t;(dasdp)-&gt;limit_hi = ((u64)limit) &gt;&gt; 32;&bslash;&n;&t;(dasdp)-&gt;limit_lo = __cpu_to_le32(limit);&bslash;&n;}
DECL|macro|DASDUSED
mdefine_line|#define DASDUSED(dasdp) &bslash;&n;&t;(((u64)((dasdp)-&gt;used_hi) &lt;&lt; 32) + __le32_to_cpu((dasdp)-&gt;used_lo))
DECL|macro|setDASDUSED
mdefine_line|#define setDASDUSED(dasdp, used)&bslash;&n;{&bslash;&n;&t;(dasdp)-&gt;used_hi = ((u64)used) &gt;&gt; 32;&bslash;&n;&t;(dasdp)-&gt;used_lo = __cpu_to_le32(used);&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* !_H_JFS_TYPES */
eof
