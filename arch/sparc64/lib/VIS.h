multiline_comment|/* $Id: VIS.h,v 1.4 1999/05/25 16:52:50 jj Exp $&n; * VIS.h: High speed copy/clear operations utilizing the UltraSparc&n; *        Visual Instruction Set.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996, 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; */
multiline_comment|/* VIS code can be used for numerous copy/set operation variants.&n;&t; * It can be made to work in the kernel, one single instance,&n;&t; * for all of memcpy, copy_to_user, and copy_from_user by setting&n;&t; * the ASI src/dest globals correctly.  Furthermore it can&n;&t; * be used for kernel--&gt;kernel page copies as well, a hook label&n;&t; * is put in here just for this purpose.&n;&t; *&n;&t; * For userland, compiling this without __KERNEL__ defined makes&n;&t; * it work just fine as a generic libc bcopy and memcpy.&n;&t; * If for userland it is compiled with a 32bit gcc (but you need&n;&t; * -Wa,-Av9a), the code will just rely on lower 32bits of&n;&t; * IEU registers, if you compile it with 64bit gcc (ie. define&n;&t; * __sparc_v9__), the code will use full 64bit.&n;&t; */
macro_line|#ifndef __VIS_H
DECL|macro|__VIS_H
mdefine_line|#define __VIS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#else
DECL|macro|ASI_AIUS
mdefine_line|#define ASI_AIUS&t;&t;0x11 /* Secondary, user&t;&t;&t;&t;*/
DECL|macro|ASI_BLK_AIUS
mdefine_line|#define ASI_BLK_AIUS&t;&t;0x71 /* Secondary, user, blk ld/st&t;&t;*/
DECL|macro|ASI_P
mdefine_line|#define ASI_P&t;&t;&t;0x80 /* Primary, implicit&t;&t;&t;*/
DECL|macro|ASI_S
mdefine_line|#define ASI_S&t;&t;&t;0x81 /* Secondary, implicit&t;&t;&t;*/
DECL|macro|ASI_BLK_COMMIT_P
mdefine_line|#define ASI_BLK_COMMIT_P&t;0xe0 /* Primary, blk store commit&t;&t;*/
DECL|macro|ASI_BLK_COMMIT_S
mdefine_line|#define ASI_BLK_COMMIT_S&t;0xe1 /* Secondary, blk store commit&t;&t;*/
DECL|macro|ASI_BLK_P
mdefine_line|#define ASI_BLK_P&t;&t;0xf0 /* Primary, blk ld/st&t;&t;&t;*/
DECL|macro|ASI_BLK_S
mdefine_line|#define ASI_BLK_S&t;&t;0xf1 /* Secondary, blk ld/st&t;&t;&t;*/
DECL|macro|FPRS_FEF
mdefine_line|#define FPRS_FEF&t;&t;0x04
macro_line|#endif
multiline_comment|/* I&squot;m telling you, they really did this chip right.&n;&t; * Perhaps the SunSoft folks should visit some of the&n;&t; * people in Sun Microelectronics and start some brain&n;&t; * cell exchange program...&n;&t; */
DECL|macro|ASI_BLK_XOR
mdefine_line|#define ASI_BLK_XOR&t;&t;(ASI_P ^ ASI_BLK_P)
multiline_comment|/* Well, things get more hairy if we use ASI_AIUS as&n;&t; * USER_DS and ASI_P as KERNEL_DS, we&squot;d reach&n;&t; * commit block stores this way which is not what we want...&n;&t; */
multiline_comment|/* ASI_P-&gt;ASI_BLK_P &amp;&amp; ASI_AIUS-&gt;ASI_BLK_AIUS transitions can be done&n;&t; * as blkasi = asi | ASI_BLK_OR&n;&t; */
DECL|macro|ASI_BLK_OR
mdefine_line|#define ASI_BLK_OR&t;&t;(ASI_BLK_P &amp; ~ASI_P)
multiline_comment|/* Transition back from ASI_BLK_P-&gt;ASI_P &amp;&amp; ASI_BLK_AIUS-&gt;ASI_AIUS is&n;&t; * more complicated:&n;&t; * asi = blkasi ^ (blkasi &gt;&gt; 3) ^ ASI_BLK_XOR1&n;&t; */
DECL|macro|ASI_BLK_XOR1
mdefine_line|#define ASI_BLK_XOR1&t;&t;(ASI_BLK_P ^ (ASI_BLK_P &gt;&gt; 3) ^ ASI_P)
DECL|macro|asi_src
mdefine_line|#define&t;asi_src&t;&t;&t;%o3
DECL|macro|asi_dest
mdefine_line|#define asi_dest&t;&t;%o4
macro_line|#ifdef __KERNEL__
DECL|macro|ASI_SETSRC_BLK
mdefine_line|#define ASI_SETSRC_BLK&t;&t;wr&t;asi_src, 0, %asi;
DECL|macro|ASI_SETSRC_NOBLK
mdefine_line|#define ASI_SETSRC_NOBLK&t;wr&t;asi_src, 0, %asi;
DECL|macro|ASI_SETDST_BLK
mdefine_line|#define ASI_SETDST_BLK&t;&t;wr&t;asi_dest, 0, %asi;
DECL|macro|ASI_SETDST_NOBLK
mdefine_line|#define ASI_SETDST_NOBLK&t;wr&t;asi_dest, 0, %asi;
DECL|macro|ASIBLK
mdefine_line|#define ASIBLK&t;&t;&t;%asi
DECL|macro|ASINORMAL
mdefine_line|#define ASINORMAL&t;&t;%asi
DECL|macro|LDUB
mdefine_line|#define LDUB&t;&t;&t;lduba
DECL|macro|LDUH
mdefine_line|#define LDUH&t;&t;&t;lduha
DECL|macro|LDUW
mdefine_line|#define LDUW&t;&t;&t;lduwa
DECL|macro|LDX
mdefine_line|#define LDX&t;&t;&t;ldxa
DECL|macro|LDD
mdefine_line|#define LDD&t;&t;&t;ldda
DECL|macro|LDDF
mdefine_line|#define LDDF&t;&t;&t;ldda
DECL|macro|LDBLK
mdefine_line|#define LDBLK&t;&t;&t;ldda
DECL|macro|STB
mdefine_line|#define STB&t;&t;&t;stba
DECL|macro|STH
mdefine_line|#define STH&t;&t;&t;stha
DECL|macro|STW
mdefine_line|#define STW&t;&t;&t;stwa
DECL|macro|STD
mdefine_line|#define STD&t;&t;&t;stda
DECL|macro|STX
mdefine_line|#define STX&t;&t;&t;stxa
DECL|macro|STDF
mdefine_line|#define STDF&t;&t;&t;stda
DECL|macro|STBLK
mdefine_line|#define STBLK&t;&t;&t;stda
macro_line|#else
DECL|macro|ASI_SETSRC_BLK
mdefine_line|#define ASI_SETSRC_BLK
DECL|macro|ASI_SETSRC_NOBLK
mdefine_line|#define ASI_SETSRC_NOBLK
DECL|macro|ASI_SETDST_BLK
mdefine_line|#define ASI_SETDST_BLK
DECL|macro|ASI_SETDST_NOBLK
mdefine_line|#define ASI_SETDST_NOBLK
DECL|macro|ASI_SETDST_SPECIAL
mdefine_line|#define ASI_SETDST_SPECIAL
DECL|macro|ASIBLK
mdefine_line|#define ASIBLK&t;&t;&t;%asi
DECL|macro|ASINORMAL
mdefine_line|#define ASINORMAL
DECL|macro|LDUB
mdefine_line|#define LDUB&t;&t;&t;ldub
DECL|macro|LDUH
mdefine_line|#define LDUH&t;&t;&t;lduh
DECL|macro|LDUW
mdefine_line|#define LDUW&t;&t;&t;lduw
DECL|macro|LDD
mdefine_line|#define LDD&t;&t;&t;ldd
DECL|macro|LDX
mdefine_line|#define LDX&t;&t;&t;ldx
DECL|macro|LDDF
mdefine_line|#define LDDF&t;&t;&t;ldd
DECL|macro|LDBLK
mdefine_line|#define LDBLK&t;&t;&t;ldda
DECL|macro|STB
mdefine_line|#define STB&t;&t;&t;stb
DECL|macro|STH
mdefine_line|#define STH&t;&t;&t;sth
DECL|macro|STW
mdefine_line|#define STW&t;&t;&t;stw
DECL|macro|STD
mdefine_line|#define STD&t;&t;&t;std
DECL|macro|STX
mdefine_line|#define STX&t;&t;&t;stx
DECL|macro|STDF
mdefine_line|#define STDF&t;&t;&t;std
DECL|macro|STBLK
mdefine_line|#define STBLK&t;&t;&t;stda
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|REGS_64BIT
mdefine_line|#define REGS_64BIT
macro_line|#else
macro_line|#ifndef REGS_64BIT
macro_line|#ifdef __sparc_v9__
DECL|macro|REGS_64BIT
mdefine_line|#define REGS_64BIT
macro_line|#endif
macro_line|#endif
macro_line|#endif
macro_line|#ifndef REGS_64BIT
DECL|macro|xcc
mdefine_line|#define&t;xcc&t;icc
macro_line|#endif
macro_line|#endif
eof
