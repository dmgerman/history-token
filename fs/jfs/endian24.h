multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_ENDIAN24
DECL|macro|_H_ENDIAN24
mdefine_line|#define&t;_H_ENDIAN24
multiline_comment|/*&n; *&t;fs/jfs/endian24.h:&n; *&n; * Endian conversion for 24-byte data&n; *&n; */
DECL|macro|__swab24
mdefine_line|#define __swab24(x) &bslash;&n;({ &bslash;&n;&t;__u32 __x = (x); &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;((__x &amp; (__u32)0x000000ffUL) &lt;&lt; 16) | &bslash;&n;&t;&t; (__x &amp; (__u32)0x0000ff00UL)        | &bslash;&n;&t;&t;((__x &amp; (__u32)0x00ff0000UL) &gt;&gt; 16) )); &bslash;&n;})
macro_line|#if (defined(__KERNEL__) &amp;&amp; defined(__LITTLE_ENDIAN)) || (defined(__BYTE_ORDER) &amp;&amp; (__BYTE_ORDER == __LITTLE_ENDIAN))
DECL|macro|__cpu_to_le24
mdefine_line|#define __cpu_to_le24(x) ((__u32)(x))
DECL|macro|__le24_to_cpu
mdefine_line|#define __le24_to_cpu(x) ((__u32)(x))
macro_line|#else
DECL|macro|__cpu_to_le24
mdefine_line|#define __cpu_to_le24(x) __swab24(x)
DECL|macro|__le24_to_cpu
mdefine_line|#define __le24_to_cpu(x) __swab24(x)
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|cpu_to_le24
mdefine_line|#define cpu_to_le24 __cpu_to_le24
DECL|macro|le24_to_cpu
mdefine_line|#define le24_to_cpu __le24_to_cpu
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* !_H_ENDIAN24 */
eof
