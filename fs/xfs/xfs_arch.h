multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ARCH_H__
DECL|macro|__XFS_ARCH_H__
mdefine_line|#define __XFS_ARCH_H__
macro_line|#ifndef XFS_BIG_INUMS
macro_line|# error XFS_BIG_INUMS must be defined true or false
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|__BYTE_ORDER
macro_line|# define __BYTE_ORDER&t;__LITTLE_ENDIAN
macro_line|#endif
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|__BYTE_ORDER
macro_line|# define __BYTE_ORDER&t;__BIG_ENDIAN
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/* do we need conversion? */
DECL|macro|ARCH_NOCONVERT
mdefine_line|#define ARCH_NOCONVERT 1
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|ARCH_CONVERT
macro_line|# define ARCH_CONVERT&t;0
macro_line|#else
DECL|macro|ARCH_CONVERT
macro_line|# define ARCH_CONVERT&t;ARCH_NOCONVERT
macro_line|#endif
multiline_comment|/* generic swapping macros */
macro_line|#ifndef HAVE_SWABMACROS
DECL|macro|INT_SWAP16
mdefine_line|#define INT_SWAP16(type,var) ((typeof(type))(__swab16((__u16)(var))))
DECL|macro|INT_SWAP32
mdefine_line|#define INT_SWAP32(type,var) ((typeof(type))(__swab32((__u32)(var))))
DECL|macro|INT_SWAP64
mdefine_line|#define INT_SWAP64(type,var) ((typeof(type))(__swab64((__u64)(var))))
macro_line|#endif
DECL|macro|INT_SWAP
mdefine_line|#define INT_SWAP(type, var) &bslash;&n;    ((sizeof(type) == 8) ? INT_SWAP64(type,var) : &bslash;&n;    ((sizeof(type) == 4) ? INT_SWAP32(type,var) : &bslash;&n;    ((sizeof(type) == 2) ? INT_SWAP16(type,var) : &bslash;&n;    (var))))
multiline_comment|/*&n; * get and set integers from potentially unaligned locations&n; */
DECL|macro|INT_GET_UNALIGNED_16_BE
mdefine_line|#define INT_GET_UNALIGNED_16_BE(pointer) &bslash;&n;   ((__u16)((((__u8*)(pointer))[0] &lt;&lt; 8) | (((__u8*)(pointer))[1])))
DECL|macro|INT_SET_UNALIGNED_16_BE
mdefine_line|#define INT_SET_UNALIGNED_16_BE(pointer,value) &bslash;&n;    { &bslash;&n;&t;((__u8*)(pointer))[0] = (((value) &gt;&gt; 8) &amp; 0xff); &bslash;&n;&t;((__u8*)(pointer))[1] = (((value)     ) &amp; 0xff); &bslash;&n;    }
multiline_comment|/* define generic INT_ macros */
DECL|macro|INT_GET
mdefine_line|#define INT_GET(reference,arch) &bslash;&n;    (((arch) == ARCH_NOCONVERT) &bslash;&n;&t;? &bslash;&n;&t;    (reference) &bslash;&n;&t;: &bslash;&n;&t;    INT_SWAP((reference),(reference)) &bslash;&n;    )
multiline_comment|/* does not return a value */
DECL|macro|INT_SET
mdefine_line|#define INT_SET(reference,arch,valueref) &bslash;&n;    (__builtin_constant_p(valueref) ? &bslash;&n;&t;(void)( (reference) = ( ((arch) != ARCH_NOCONVERT) ? (INT_SWAP((reference),(valueref))) : (valueref)) ) : &bslash;&n;&t;(void)( &bslash;&n;&t;    ((reference) = (valueref)), &bslash;&n;&t;    ( ((arch) != ARCH_NOCONVERT) ? (reference) = INT_SWAP((reference),(reference)) : 0 ) &bslash;&n;&t;) &bslash;&n;    )
multiline_comment|/* does not return a value */
DECL|macro|INT_MOD_EXPR
mdefine_line|#define INT_MOD_EXPR(reference,arch,code) &bslash;&n;    (((arch) == ARCH_NOCONVERT) &bslash;&n;&t;? &bslash;&n;&t;    (void)((reference) code) &bslash;&n;&t;: &bslash;&n;&t;    (void)( &bslash;&n;&t;&t;(reference) = INT_GET((reference),arch) , &bslash;&n;&t;&t;((reference) code), &bslash;&n;&t;&t;INT_SET(reference, arch, reference) &bslash;&n;&t;    ) &bslash;&n;    )
multiline_comment|/* does not return a value */
DECL|macro|INT_MOD
mdefine_line|#define INT_MOD(reference,arch,delta) &bslash;&n;    (void)( &bslash;&n;&t;INT_MOD_EXPR(reference,arch,+=(delta)) &bslash;&n;    )
multiline_comment|/*&n; * INT_COPY - copy a value between two locations with the&n; *&t;      _same architecture_ but _potentially different sizes_&n; *&n; *&t;    if the types of the two parameters are equal or they are&n; *&t;&t;in native architecture, a simple copy is done&n; *&n; *&t;    otherwise, architecture conversions are done&n; *&n; */
multiline_comment|/* does not return a value */
DECL|macro|INT_COPY
mdefine_line|#define INT_COPY(dst,src,arch) &bslash;&n;    ( &bslash;&n;&t;((sizeof(dst) == sizeof(src)) || ((arch) == ARCH_NOCONVERT)) &bslash;&n;&t;    ? &bslash;&n;&t;&t;(void)((dst) = (src)) &bslash;&n;&t;    : &bslash;&n;&t;&t;INT_SET(dst, arch, INT_GET(src, arch)) &bslash;&n;    )
multiline_comment|/*&n; * INT_XLATE - copy a value in either direction between two locations&n; *&t;       with different architectures&n; *&n; *&t;&t;    dir &lt; 0&t;- copy from memory to buffer (native to arch)&n; *&t;&t;    dir &gt; 0&t;- copy from buffer to memory (arch to native)&n; */
multiline_comment|/* does not return a value */
DECL|macro|INT_XLATE
mdefine_line|#define INT_XLATE(buf,mem,dir,arch) {&bslash;&n;    ASSERT(dir); &bslash;&n;    if (dir&gt;0) { &bslash;&n;&t;(mem)=INT_GET(buf, arch); &bslash;&n;    } else { &bslash;&n;&t;INT_SET(buf, arch, mem); &bslash;&n;    } &bslash;&n;}
multiline_comment|/*&n; * In directories inode numbers are stored as unaligned arrays of unsigned&n; * 8bit integers on disk.&n; *&n; * For v1 directories or v2 directories that contain inode numbers that&n; * do not fit into 32bit the array has eight members, but the first member&n; * is always zero:&n; *&n; *  |unused|48-55|40-47|32-39|24-31|16-23| 8-15| 0- 7|&n; *&n; * For v2 directories that only contain entries with inode numbers that fit&n; * into 32bits a four-member array is used:&n; *&n; *  |24-31|16-23| 8-15| 0- 7|&n; */
DECL|macro|XFS_GET_DIR_INO4
mdefine_line|#define XFS_GET_DIR_INO4(di) &bslash;&n;&t;(((u32)(di).i[0] &lt;&lt; 24) | ((di).i[1] &lt;&lt; 16) | ((di).i[2] &lt;&lt; 8) | ((di).i[3]))
DECL|macro|XFS_PUT_DIR_INO4
mdefine_line|#define XFS_PUT_DIR_INO4(from, di) &bslash;&n;do { &bslash;&n;&t;(di).i[0] = (((from) &amp; 0xff000000ULL) &gt;&gt; 24); &bslash;&n;&t;(di).i[1] = (((from) &amp; 0x00ff0000ULL) &gt;&gt; 16); &bslash;&n;&t;(di).i[2] = (((from) &amp; 0x0000ff00ULL) &gt;&gt; 8); &bslash;&n;&t;(di).i[3] = ((from) &amp; 0x000000ffULL); &bslash;&n;} while (0)
DECL|macro|XFS_DI_HI
mdefine_line|#define XFS_DI_HI(di) &bslash;&n;&t;(((u32)(di).i[1] &lt;&lt; 16) | ((di).i[2] &lt;&lt; 8) | ((di).i[3]))
DECL|macro|XFS_DI_LO
mdefine_line|#define XFS_DI_LO(di) &bslash;&n;&t;(((u32)(di).i[4] &lt;&lt; 24) | ((di).i[5] &lt;&lt; 16) | ((di).i[6] &lt;&lt; 8) | ((di).i[7]))
DECL|macro|XFS_GET_DIR_INO8
mdefine_line|#define XFS_GET_DIR_INO8(di)        &bslash;&n;&t;(((xfs_ino_t)XFS_DI_LO(di) &amp; 0xffffffffULL) | &bslash;&n;&t; ((xfs_ino_t)XFS_DI_HI(di) &lt;&lt; 32))
DECL|macro|XFS_PUT_DIR_INO8
mdefine_line|#define XFS_PUT_DIR_INO8(from, di) &bslash;&n;do { &bslash;&n;&t;(di).i[0] = 0; &bslash;&n;&t;(di).i[1] = (((from) &amp; 0x00ff000000000000ULL) &gt;&gt; 48); &bslash;&n;&t;(di).i[2] = (((from) &amp; 0x0000ff0000000000ULL) &gt;&gt; 40); &bslash;&n;&t;(di).i[3] = (((from) &amp; 0x000000ff00000000ULL) &gt;&gt; 32); &bslash;&n;&t;(di).i[4] = (((from) &amp; 0x00000000ff000000ULL) &gt;&gt; 24); &bslash;&n;&t;(di).i[5] = (((from) &amp; 0x0000000000ff0000ULL) &gt;&gt; 16); &bslash;&n;&t;(di).i[6] = (((from) &amp; 0x000000000000ff00ULL) &gt;&gt; 8); &bslash;&n;&t;(di).i[7] = ((from) &amp; 0x00000000000000ffULL); &bslash;&n;} while (0)
macro_line|#endif&t;/* __XFS_ARCH_H__ */
eof
