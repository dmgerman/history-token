multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1992-1999,2001-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_ADDRS_H
DECL|macro|_ASM_IA64_SN_ADDRS_H
mdefine_line|#define _ASM_IA64_SN_ADDRS_H
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
multiline_comment|/*&n; *  Memory/SHUB Address Format:&n; *  +-+---------+--+--------------+&n; *  |0|  NASID  |AS| NodeOffset   |&n; *  +-+---------+--+--------------+&n; *&n; *  NASID: (low NASID bit is 0) Memory and SHUB MMRs&n; *   AS: 2-bit Address Space Identifier. Used only if low NASID bit is 0&n; *     00: Local Resources and MMR space&n; *           Top bit of NodeOffset&n; *               0: Local resources space&n; *                  node id:&n; *                        0: IA64/NT compatibility space&n; *                        2: Local MMR Space&n; *                        4: Local memory, regardless of local node id&n; *               1: Global MMR space&n; *     01: GET space.&n; *     10: AMO space.&n; *     11: Cacheable memory space.&n; *&n; *   NodeOffset: byte offset&n; *&n; *&n; *  TIO address format:&n; *  +-+----------+--+--------------+&n; *  |0|  NASID   |AS| Nodeoffset   |&n; *  +-+----------+--+--------------+&n; *&n; *  NASID: (low NASID bit is 1) TIO&n; *   AS: 2-bit Chiplet Identifier&n; *     00: TIO LB (Indicates TIO MMR access.)&n; *     01: TIO ICE (indicates coretalk space access.)&n; * &n; *   NodeOffset: top bit must be set.&n; *&n; *&n; * Note that in both of the above address formats, the low&n; * NASID bit indicates if the reference is to the SHUB or TIO MMRs.&n; */
multiline_comment|/*&n; * Define basic shift &amp; mask constants for manipulating NASIDs and AS values.&n; */
DECL|macro|NASID_BITMASK
mdefine_line|#define NASID_BITMASK&t;&t;(pda-&gt;nasid_bitmask)
DECL|macro|NASID_SHIFT
mdefine_line|#define NASID_SHIFT&t;&t;(pda-&gt;nasid_shift)
DECL|macro|AS_SHIFT
mdefine_line|#define AS_SHIFT&t;&t;(pda-&gt;as_shift)
DECL|macro|AS_BITMASK
mdefine_line|#define AS_BITMASK&t;&t;0x3UL
DECL|macro|NASID_MASK
mdefine_line|#define NASID_MASK              ((u64)NASID_BITMASK &lt;&lt; NASID_SHIFT)
DECL|macro|AS_MASK
mdefine_line|#define AS_MASK&t;&t;&t;((u64)AS_BITMASK &lt;&lt; AS_SHIFT)
DECL|macro|REGION_BITS
mdefine_line|#define REGION_BITS&t;&t;0xe000000000000000UL
multiline_comment|/*&n; * AS values. These are the same on both SHUB1 &amp; SHUB2.&n; */
DECL|macro|AS_GET_VAL
mdefine_line|#define AS_GET_VAL&t;&t;1UL
DECL|macro|AS_AMO_VAL
mdefine_line|#define AS_AMO_VAL&t;&t;2UL
DECL|macro|AS_CAC_VAL
mdefine_line|#define AS_CAC_VAL&t;&t;3UL
DECL|macro|AS_GET_SPACE
mdefine_line|#define AS_GET_SPACE&t;&t;(AS_GET_VAL &lt;&lt; AS_SHIFT)
DECL|macro|AS_AMO_SPACE
mdefine_line|#define AS_AMO_SPACE&t;&t;(AS_AMO_VAL &lt;&lt; AS_SHIFT)
DECL|macro|AS_CAC_SPACE
mdefine_line|#define AS_CAC_SPACE&t;&t;(AS_CAC_VAL &lt;&lt; AS_SHIFT)
multiline_comment|/*&n; * Base addresses for various address ranges.&n; */
DECL|macro|CACHED
mdefine_line|#define CACHED&t;&t;&t;0xe000000000000000UL
DECL|macro|UNCACHED
mdefine_line|#define UNCACHED                0xc000000000000000UL
DECL|macro|UNCACHED_PHYS
mdefine_line|#define UNCACHED_PHYS           0x8000000000000000UL
multiline_comment|/* &n; * Virtual Mode Local &amp; Global MMR space.  &n; */
DECL|macro|SH1_LOCAL_MMR_OFFSET
mdefine_line|#define SH1_LOCAL_MMR_OFFSET&t;0x8000000000UL
DECL|macro|SH2_LOCAL_MMR_OFFSET
mdefine_line|#define SH2_LOCAL_MMR_OFFSET&t;0x0200000000UL
DECL|macro|LOCAL_MMR_OFFSET
mdefine_line|#define LOCAL_MMR_OFFSET&t;(is_shub2() ? SH2_LOCAL_MMR_OFFSET : SH1_LOCAL_MMR_OFFSET)
DECL|macro|LOCAL_MMR_SPACE
mdefine_line|#define LOCAL_MMR_SPACE&t;&t;(UNCACHED | LOCAL_MMR_OFFSET)
DECL|macro|LOCAL_PHYS_MMR_SPACE
mdefine_line|#define LOCAL_PHYS_MMR_SPACE&t;(UNCACHED_PHYS | LOCAL_MMR_OFFSET)
DECL|macro|SH1_GLOBAL_MMR_OFFSET
mdefine_line|#define SH1_GLOBAL_MMR_OFFSET&t;0x0800000000UL
DECL|macro|SH2_GLOBAL_MMR_OFFSET
mdefine_line|#define SH2_GLOBAL_MMR_OFFSET&t;0x0300000000UL
DECL|macro|GLOBAL_MMR_OFFSET
mdefine_line|#define GLOBAL_MMR_OFFSET&t;(is_shub2() ? SH2_GLOBAL_MMR_OFFSET : SH1_GLOBAL_MMR_OFFSET)
DECL|macro|GLOBAL_MMR_SPACE
mdefine_line|#define GLOBAL_MMR_SPACE&t;(UNCACHED | GLOBAL_MMR_OFFSET)
multiline_comment|/*&n; * Physical mode addresses&n; */
DECL|macro|GLOBAL_PHYS_MMR_SPACE
mdefine_line|#define GLOBAL_PHYS_MMR_SPACE&t;(UNCACHED_PHYS | GLOBAL_MMR_OFFSET)
multiline_comment|/*&n; * Clear region &amp; AS bits.&n; */
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;&t;(~(REGION_BITS | AS_MASK))
multiline_comment|/*&n; * Misc NASID manipulation.&n; */
DECL|macro|NASID_SPACE
mdefine_line|#define NASID_SPACE(n)&t;&t;((u64)(n) &lt;&lt; NASID_SHIFT)
DECL|macro|REMOTE_ADDR
mdefine_line|#define REMOTE_ADDR(n,a)&t;(NASID_SPACE(n) | (a))
DECL|macro|NODE_OFFSET
mdefine_line|#define NODE_OFFSET(x)&t;&t;((x) &amp; (NODE_ADDRSPACE_SIZE - 1))
DECL|macro|NODE_ADDRSPACE_SIZE
mdefine_line|#define NODE_ADDRSPACE_SIZE     (1UL &lt;&lt; AS_SHIFT)
DECL|macro|NASID_GET
mdefine_line|#define NASID_GET(x)&t;&t;(int) (((u64) (x) &gt;&gt; NASID_SHIFT) &amp; NASID_BITMASK)
DECL|macro|LOCAL_MMR_ADDR
mdefine_line|#define LOCAL_MMR_ADDR(a)&t;(LOCAL_MMR_SPACE | (a))
DECL|macro|GLOBAL_MMR_ADDR
mdefine_line|#define GLOBAL_MMR_ADDR(n,a)&t;(GLOBAL_MMR_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GLOBAL_MMR_PHYS_ADDR
mdefine_line|#define GLOBAL_MMR_PHYS_ADDR(n,a) (GLOBAL_PHYS_MMR_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GLOBAL_CAC_ADDR
mdefine_line|#define GLOBAL_CAC_ADDR(n,a)&t;(CAC_BASE | REMOTE_ADDR(n,a))
DECL|macro|CHANGE_NASID
mdefine_line|#define CHANGE_NASID(n,x)&t;((void *)(((u64)(x) &amp; ~NASID_MASK) | NASID_SPACE(n)))
multiline_comment|/* non-II mmr&squot;s start at top of big window space (4G) */
DECL|macro|BWIN_TOP
mdefine_line|#define BWIN_TOP&t;&t;0x0000000100000000UL
multiline_comment|/*&n; * general address defines&n; */
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;(CACHED   | AS_CAC_SPACE)
DECL|macro|AMO_BASE
mdefine_line|#define AMO_BASE&t;&t;(UNCACHED | AS_AMO_SPACE)
DECL|macro|GET_BASE
mdefine_line|#define GET_BASE&t;&t;(CACHED   | AS_GET_SPACE)
multiline_comment|/*&n; * Convert Memory addresses between various addressing modes.&n; */
DECL|macro|TO_PHYS
mdefine_line|#define TO_PHYS(x)&t;&t;(TO_PHYS_MASK &amp; (x))
DECL|macro|TO_CAC
mdefine_line|#define TO_CAC(x)&t;&t;(CAC_BASE     | TO_PHYS(x))
DECL|macro|TO_AMO
mdefine_line|#define TO_AMO(x)&t;&t;(AMO_BASE     | TO_PHYS(x))
DECL|macro|TO_GET
mdefine_line|#define TO_GET(x)&t;&t;(GET_BASE     | TO_PHYS(x))
multiline_comment|/*&n; * Covert from processor physical address to II/TIO physical address:&n; *&t;II - squeeze out the AS bits&n; *&t;TIO- requires a chiplet id in bits 38-39.  For DMA to memory,&n; *           the chiplet id is zero.  If we implement TIO-TIO dma, we might need&n; *           to insert a chiplet id into this macro.  However, it is our belief&n; *           right now that this chiplet id will be ICE, which is also zero.&n; */
DECL|macro|PHYS_TO_TIODMA
mdefine_line|#define PHYS_TO_TIODMA(x)&t;( (((u64)(x) &amp; NASID_MASK) &lt;&lt; 2) | NODE_OFFSET(x))
DECL|macro|PHYS_TO_DMA
mdefine_line|#define PHYS_TO_DMA(x)          ( (((u64)(x) &amp; NASID_MASK) &gt;&gt; 2) | NODE_OFFSET(x))
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|BWIN_SIZE_BITS
mdefine_line|#define BWIN_SIZE_BITS&t;&t;&t;29&t;/* big window size: 512M */
DECL|macro|TIO_BWIN_SIZE_BITS
mdefine_line|#define TIO_BWIN_SIZE_BITS&t;&t;30&t;/* big window size: 1G */
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(n, w)&t;&t;((w == 0) ? NODE_BWIN_BASE((n), SWIN0_BIGWIN) &bslash;&n;&t;&t;: RAW_NODE_SWIN_BASE(n, w))
DECL|macro|NODE_IO_BASE
mdefine_line|#define NODE_IO_BASE(n)&t;&t;&t;(GLOBAL_MMR_SPACE | NASID_SPACE(n))
DECL|macro|BWIN_SIZE
mdefine_line|#define BWIN_SIZE&t;&t;&t;(1UL &lt;&lt; BWIN_SIZE_BITS)
DECL|macro|NODE_BWIN_BASE0
mdefine_line|#define NODE_BWIN_BASE0(n)&t;&t;(NODE_IO_BASE(n) + BWIN_SIZE)
DECL|macro|NODE_BWIN_BASE
mdefine_line|#define NODE_BWIN_BASE(n, w)&t;&t;(NODE_BWIN_BASE0(n) + ((u64) (w) &lt;&lt; BWIN_SIZE_BITS))
DECL|macro|RAW_NODE_SWIN_BASE
mdefine_line|#define RAW_NODE_SWIN_BASE(n, w)&t;(NODE_IO_BASE(n) + ((u64) (w) &lt;&lt; SWIN_SIZE_BITS))
DECL|macro|BWIN_WIDGET_MASK
mdefine_line|#define BWIN_WIDGET_MASK&t;&t;0x7
DECL|macro|BWIN_WINDOWNUM
mdefine_line|#define BWIN_WINDOWNUM(x)&t;&t;(((x) &gt;&gt; BWIN_SIZE_BITS) &amp; BWIN_WIDGET_MASK)
DECL|macro|TIO_BWIN_WINDOW_SELECT_MASK
mdefine_line|#define TIO_BWIN_WINDOW_SELECT_MASK&t;0x7
DECL|macro|TIO_BWIN_WINDOWNUM
mdefine_line|#define TIO_BWIN_WINDOWNUM(x)&t;&t;(((x) &gt;&gt; TIO_BWIN_SIZE_BITS) &amp; TIO_BWIN_WINDOW_SELECT_MASK)
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|SWIN_SIZE_BITS
mdefine_line|#define SWIN_SIZE_BITS&t;&t;&t;24
DECL|macro|SWIN_WIDGET_MASK
mdefine_line|#define&t;SWIN_WIDGET_MASK&t;&t;0xF
DECL|macro|TIO_SWIN_SIZE_BITS
mdefine_line|#define TIO_SWIN_SIZE_BITS&t;&t;28
DECL|macro|TIO_SWIN_SIZE
mdefine_line|#define TIO_SWIN_SIZE&t;&t;&t;(1UL &lt;&lt; TIO_SWIN_SIZE_BITS)
DECL|macro|TIO_SWIN_WIDGET_MASK
mdefine_line|#define TIO_SWIN_WIDGET_MASK&t;&t;0x3
multiline_comment|/*&n; * Convert smallwindow address to xtalk address.&n; *&n; * &squot;addr&squot; can be physical or virtual address, but will be converted&n; * to Xtalk address in the range 0 -&gt; SWINZ_SIZEMASK&n; */
DECL|macro|SWIN_WIDGETNUM
mdefine_line|#define&t;SWIN_WIDGETNUM(x)&t;&t;(((x)  &gt;&gt; SWIN_SIZE_BITS) &amp; SWIN_WIDGET_MASK)
DECL|macro|TIO_SWIN_WIDGETNUM
mdefine_line|#define TIO_SWIN_WIDGETNUM(x)&t;&t;(((x)  &gt;&gt; TIO_SWIN_SIZE_BITS) &amp; TIO_SWIN_WIDGET_MASK)
multiline_comment|/*&n; * The following macros produce the correct base virtual address for&n; * the hub registers. The REMOTE_HUB_* macro produce&n; * the address for the specified hub&squot;s registers.  The intent is&n; * that the appropriate PI, MD, NI, or II register would be substituted&n; * for x.&n; *&n; *   WARNING:&n; *&t;When certain Hub chip workaround are defined, it&squot;s not sufficient&n; *&t;to dereference the *_HUB_ADDR() macros.  You should instead use&n; *&t;HUB_L() and HUB_S() if you must deal with pointers to hub registers.&n; *&t;Otherwise, the recommended approach is to use *_HUB_L() and *_HUB_S().&n; *&t;They&squot;re always safe.&n; */
DECL|macro|REMOTE_HUB_ADDR
mdefine_line|#define REMOTE_HUB_ADDR(n,x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((n &amp; 1) ?&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* TIO: */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((volatile u64 *)(GLOBAL_MMR_ADDR(n,x)))&t;&t;&t;&bslash;&n;&t;: /* SHUB: */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((x) &amp; BWIN_TOP) ? ((volatile u64 *)(GLOBAL_MMR_ADDR(n,x)))&bslash;&n;&t;: ((volatile u64 *)(NODE_SWIN_BASE(n,1) + 0x800000 + (x)))))
DECL|macro|HUB_L
mdefine_line|#define HUB_L(x)&t;&t;&t;(*((volatile typeof(*x) *)x))
DECL|macro|HUB_S
mdefine_line|#define&t;HUB_S(x,d)&t;&t;&t;(*((volatile typeof(*x) *)x) = (d))
DECL|macro|REMOTE_HUB_L
mdefine_line|#define REMOTE_HUB_L(n, a)&t;&t;HUB_L(REMOTE_HUB_ADDR((n), (a)))
DECL|macro|REMOTE_HUB_S
mdefine_line|#define REMOTE_HUB_S(n, a, d)&t;&t;HUB_S(REMOTE_HUB_ADDR((n), (a)), (d))
macro_line|#endif /* _ASM_IA64_SN_ADDRS_H */
eof
