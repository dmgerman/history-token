multiline_comment|/* $Id: md.h,v 1.1 1997/12/15 15:12:15 jj Exp $&n; * md.h: High speed xor_block operation for RAID4/5 &n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_MD_H
DECL|macro|__ASM_MD_H
mdefine_line|#define __ASM_MD_H
multiline_comment|/* #define HAVE_ARCH_XORBLOCK */
DECL|macro|MD_XORBLOCK_ALIGNMENT
mdefine_line|#define MD_XORBLOCK_ALIGNMENT&t;sizeof(long)
macro_line|#endif /* __ASM_MD_H */
macro_line|#endif /* __KERNEL__ */
eof
