multiline_comment|/*&n; * include/asm-v850/v850e2_cache_cache.h -- Cache control for V850E2&n; * &t;cache memories&n; *&n; *  Copyright (C) 2003  NEC Electronics Corporation&n; *  Copyright (C) 2003  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_V850E2_CACHE_H__
DECL|macro|__V850_V850E2_CACHE_H__
mdefine_line|#define __V850_V850E2_CACHE_H__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Cache control registers.  */
multiline_comment|/* Bus Transaction Control */
DECL|macro|V850E2_CACHE_BTSC_ADDR
mdefine_line|#define V850E2_CACHE_BTSC_ADDR&t;0xFFFFF070
DECL|macro|V850E2_CACHE_BTSC
mdefine_line|#define V850E2_CACHE_BTSC &t;(*(volatile u16 *)V850E2_CACHE_BTSC_ADDR)
DECL|macro|V850E2_CACHE_BTSC_ICM
mdefine_line|#define V850E2_CACHE_BTSC_ICM&t;0x0001 /* icache enable */
DECL|macro|V850E2_CACHE_BTSC_DCM0
mdefine_line|#define V850E2_CACHE_BTSC_DCM0&t;0x0004 /* dcache enable, bit 0 */
DECL|macro|V850E2_CACHE_BTSC_DCM1
mdefine_line|#define V850E2_CACHE_BTSC_DCM1&t;0x0008 /* dcache enable, bit 1 */
DECL|macro|V850E2_CACHE_BTSC_DCM_WT
mdefine_line|#define V850E2_CACHE_BTSC_DCM_WT&t;&t;      /* write-through */ &bslash;&n;&t;&t;&t;V850E2_CACHE_BTSC_DCM0
macro_line|#ifdef CONFIG_V850E2_V850E2S
DECL|macro|V850E2_CACHE_BTSC_DCM_WB_NO_ALLOC
macro_line|# define V850E2_CACHE_BTSC_DCM_WB_NO_ALLOC    /* write-back, non-alloc */ &bslash;&n;&t;&t;&t;V850E2_CACHE_BTSC_DCM1&t;
DECL|macro|V850E2_CACHE_BTSC_DCM_WB_ALLOC
macro_line|# define V850E2_CACHE_BTSC_DCM_WB_ALLOC&t;      /* write-back, non-alloc */ &bslash;&n;&t;&t;&t;(V850E2_CACHE_BTSC_DCM1 | V850E2_CACHE_BTSC_DCM0)
DECL|macro|V850E2_CACHE_BTSC_ISEQ
macro_line|# define V850E2_CACHE_BTSC_ISEQ&t;0x0010 /* icache `address sequence mode&squot; */
DECL|macro|V850E2_CACHE_BTSC_DSEQ
macro_line|# define V850E2_CACHE_BTSC_DSEQ&t;0x0020 /* dcache `address sequence mode&squot; */
DECL|macro|V850E2_CACHE_BTSC_IRFC
macro_line|# define V850E2_CACHE_BTSC_IRFC&t;0x0030
DECL|macro|V850E2_CACHE_BTSC_ILCD
macro_line|# define V850E2_CACHE_BTSC_ILCD&t;0x4000
DECL|macro|V850E2_CACHE_BTSC_VABE
macro_line|# define V850E2_CACHE_BTSC_VABE&t;0x8000
macro_line|#endif /* CONFIG_V850E2_V850E2S */
multiline_comment|/* Cache operation start address register (low-bits).  */
DECL|macro|V850E2_CACHE_CADL_ADDR
mdefine_line|#define V850E2_CACHE_CADL_ADDR&t;0xFFFFF074
DECL|macro|V850E2_CACHE_CADL
mdefine_line|#define V850E2_CACHE_CADL &t;(*(volatile u16 *)V850E2_CACHE_CADL_ADDR)
multiline_comment|/* Cache operation start address register (high-bits).  */
DECL|macro|V850E2_CACHE_CADH_ADDR
mdefine_line|#define V850E2_CACHE_CADH_ADDR&t;0xFFFFF076
DECL|macro|V850E2_CACHE_CADH
mdefine_line|#define V850E2_CACHE_CADH &t;(*(volatile u16 *)V850E2_CACHE_CADH_ADDR)
multiline_comment|/* Cache operation count register.  */
DECL|macro|V850E2_CACHE_CCNT_ADDR
mdefine_line|#define V850E2_CACHE_CCNT_ADDR&t;0xFFFFF078
DECL|macro|V850E2_CACHE_CCNT
mdefine_line|#define V850E2_CACHE_CCNT &t;(*(volatile u16 *)V850E2_CACHE_CCNT_ADDR)
multiline_comment|/* Cache operation specification register.  */
DECL|macro|V850E2_CACHE_COPR_ADDR
mdefine_line|#define V850E2_CACHE_COPR_ADDR&t;0xFFFFF07A
DECL|macro|V850E2_CACHE_COPR
mdefine_line|#define V850E2_CACHE_COPR &t;(*(volatile u16 *)V850E2_CACHE_COPR_ADDR)
DECL|macro|V850E2_CACHE_COPR_STRT
mdefine_line|#define V850E2_CACHE_COPR_STRT&t;0x0001 /* start cache operation */
DECL|macro|V850E2_CACHE_COPR_LBSL
mdefine_line|#define V850E2_CACHE_COPR_LBSL&t;0x0100 /* 0 = icache, 1 = dcache */
DECL|macro|V850E2_CACHE_COPR_WSLE
mdefine_line|#define V850E2_CACHE_COPR_WSLE&t;0x0200 /* operate on cache way */
DECL|macro|V850E2_CACHE_COPR_WSL
mdefine_line|#define V850E2_CACHE_COPR_WSL(way) ((way) * 0x0400) /* way select */
DECL|macro|V850E2_CACHE_COPR_CFC
mdefine_line|#define V850E2_CACHE_COPR_CFC(op)  ((op)  * 0x1000) /* cache function code */
multiline_comment|/* Size of a cache line in bytes.  */
DECL|macro|V850E2_CACHE_LINE_SIZE_BITS
mdefine_line|#define V850E2_CACHE_LINE_SIZE_BITS&t;4
DECL|macro|V850E2_CACHE_LINE_SIZE
mdefine_line|#define V850E2_CACHE_LINE_SIZE&t;&t;(1 &lt;&lt; V850E2_CACHE_LINE_SIZE_BITS)
multiline_comment|/* The size of each cache `way&squot; in lines.  */
DECL|macro|V850E2_CACHE_WAY_SIZE
mdefine_line|#define V850E2_CACHE_WAY_SIZE&t;&t;256
multiline_comment|/* For &lt;asm/cache.h&gt; */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;&t;V850E2_CACHE_LINE_SIZE
macro_line|#endif /* __V850_V850E2_CACHE_H__ */
eof
