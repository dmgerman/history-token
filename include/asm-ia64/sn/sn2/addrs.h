multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN2_ADDRS_H
DECL|macro|_ASM_IA64_SN_SN2_ADDRS_H
mdefine_line|#define _ASM_IA64_SN_SN2_ADDRS_H
multiline_comment|/* McKinley Address Format:&n; *&n; *   4 4       3 3  3 3&n; *   9 8       8 7  6 5             0&n; *  +-+---------+----+--------------+&n; *  |0| Node ID | AS | Node Offset  |&n; *  +-+---------+----+--------------+&n; *&n; *   Node ID: If bit 38 = 1, is ICE, else is SHUB&n; *   AS: Address Space Identifier. Used only if bit 38 = 0.&n; *     b&squot;00: Local Resources and MMR space&n; *           bit 35&n; *               0: Local resources space&n; *                  node id:&n; *                        0: IA64/NT compatibility space&n; *                        2: Local MMR Space&n; *                        4: Local memory, regardless of local node id&n; *               1: Global MMR space&n; *     b&squot;01: GET space.&n; *     b&squot;10: AMO space.&n; *     b&squot;11: Cacheable memory space.&n; *&n; *   NodeOffset: byte offset&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|union|ia64_sn2_pa
r_typedef
r_union
id|ia64_sn2_pa
(brace
r_struct
(brace
DECL|member|off
r_int
r_int
id|off
suffix:colon
l_int|36
suffix:semicolon
DECL|member|as
r_int
r_int
id|as
suffix:colon
l_int|2
suffix:semicolon
DECL|member|nasid
r_int
r_int
id|nasid
suffix:colon
l_int|11
suffix:semicolon
DECL|member|fill
r_int
r_int
id|fill
suffix:colon
l_int|15
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|l
r_int
r_int
id|l
suffix:semicolon
DECL|member|p
r_void
op_star
id|p
suffix:semicolon
DECL|typedef|ia64_sn2_pa_t
)brace
id|ia64_sn2_pa_t
suffix:semicolon
macro_line|#endif
DECL|macro|TO_PHYS_MASK
mdefine_line|#define TO_PHYS_MASK&t;&t;0x0001ffcfffffffff&t;/* Note - clear AS bits */
multiline_comment|/* Regions determined by AS */
DECL|macro|LOCAL_MMR_SPACE
mdefine_line|#define LOCAL_MMR_SPACE&t;&t;0xc000008000000000&t;/* Local MMR space */
DECL|macro|LOCAL_MEM_SPACE
mdefine_line|#define LOCAL_MEM_SPACE&t;&t;0xc000010000000000&t;/* Local Memory space */
DECL|macro|GLOBAL_MMR_SPACE
mdefine_line|#define GLOBAL_MMR_SPACE&t;0xc000000800000000&t;/* Global MMR space */
DECL|macro|GET_SPACE
mdefine_line|#define GET_SPACE&t;&t;0xc000001000000000&t;/* GET space */
DECL|macro|AMO_SPACE
mdefine_line|#define AMO_SPACE&t;&t;0xc000002000000000&t;/* AMO space */
DECL|macro|CACHEABLE_MEM_SPACE
mdefine_line|#define CACHEABLE_MEM_SPACE&t;0xe000003000000000&t;/* Cacheable memory space */
DECL|macro|UNCACHED
mdefine_line|#define UNCACHED                0xc000000000000000      /* UnCacheable memory space */
multiline_comment|/* SN2 address macros */
DECL|macro|NID_SHFT
mdefine_line|#define NID_SHFT&t;&t;38
DECL|macro|LOCAL_MMR_ADDR
mdefine_line|#define LOCAL_MMR_ADDR(a)&t;(UNCACHED | LOCAL_MMR_SPACE | (a))
DECL|macro|LOCAL_MEM_ADDR
mdefine_line|#define LOCAL_MEM_ADDR(a)&t;(LOCAL_MEM_SPACE | (a))
DECL|macro|REMOTE_ADDR
mdefine_line|#define REMOTE_ADDR(n,a)&t;((((unsigned long)(n))&lt;&lt;NID_SHFT) | (a))
DECL|macro|GLOBAL_MMR_ADDR
mdefine_line|#define GLOBAL_MMR_ADDR(n,a)&t;(UNCACHED | GLOBAL_MMR_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GET_ADDR
mdefine_line|#define GET_ADDR(n,a)&t;&t;(GET_SPACE | REMOTE_ADDR(n,a))
DECL|macro|AMO_ADDR
mdefine_line|#define AMO_ADDR(n,a)&t;&t;(UNCACHED | AMO_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GLOBAL_MEM_ADDR
mdefine_line|#define GLOBAL_MEM_ADDR(n,a)&t;(CACHEABLE_MEM_SPACE | REMOTE_ADDR(n,a))
multiline_comment|/* non-II mmr&squot;s start at top of big window space (4G) */
DECL|macro|BWIN_TOP
mdefine_line|#define BWIN_TOP&t;&t;0x0000000100000000
multiline_comment|/*&n; * general address defines - for code common to SN0/SN1/SN2&n; */
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;CACHEABLE_MEM_SPACE&t;&t;&t;/* cacheable memory space */
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;(UNCACHED | GLOBAL_MMR_SPACE)&t;&t;/* lower 4G maps II&squot;s XIO space */
DECL|macro|AMO_BASE
mdefine_line|#define AMO_BASE&t;&t;(UNCACHED | AMO_SPACE)&t;&t;&t;/* fetch &amp; op space */
DECL|macro|MSPEC_BASE
mdefine_line|#define MSPEC_BASE&t;&t;AMO_BASE&t;&t;&t;&t;/* fetch &amp; op space */
DECL|macro|UNCAC_BASE
mdefine_line|#define UNCAC_BASE&t;&t;(UNCACHED | CACHEABLE_MEM_SPACE)&t;/* uncached global memory */
DECL|macro|GET_BASE
mdefine_line|#define GET_BASE&t;&t;GET_SPACE&t;&t;&t;&t;/* momentarily coherent remote mem. */
DECL|macro|CALIAS_BASE
mdefine_line|#define CALIAS_BASE             LOCAL_CACHEABLE_BASE&t;&t;&t;/* cached node-local memory */
DECL|macro|UALIAS_BASE
mdefine_line|#define UALIAS_BASE             (UNCACHED | LOCAL_CACHEABLE_BASE)&t;/* uncached node-local memory */
DECL|macro|TO_PHYS
mdefine_line|#define TO_PHYS(x)              (              ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_CAC
mdefine_line|#define TO_CAC(x)               (CAC_BASE    | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_UNCAC
mdefine_line|#define TO_UNCAC(x)             (UNCAC_BASE  | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_MSPEC
mdefine_line|#define TO_MSPEC(x)             (MSPEC_BASE  | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_GET
mdefine_line|#define TO_GET(x)&t;&t;(GET_BASE    | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_CALIAS
mdefine_line|#define TO_CALIAS(x)            (CALIAS_BASE | TO_NODE_ADDRSPACE(x))
DECL|macro|TO_UALIAS
mdefine_line|#define TO_UALIAS(x)            (UALIAS_BASE | TO_NODE_ADDRSPACE(x))
DECL|macro|NODE_SIZE_BITS
mdefine_line|#define NODE_SIZE_BITS&t;&t;36&t;/* node offset : bits &lt;35:0&gt; */
DECL|macro|BWIN_SIZE_BITS
mdefine_line|#define BWIN_SIZE_BITS&t;&t;29&t;/* big window size: 512M */
DECL|macro|NASID_BITS
mdefine_line|#define NASID_BITS&t;&t;11&t;/* bits &lt;48:38&gt; */
DECL|macro|NASID_BITMASK
mdefine_line|#define NASID_BITMASK&t;&t;(0x7ffULL)
DECL|macro|NASID_SHFT
mdefine_line|#define NASID_SHFT&t;&t;NID_SHFT
DECL|macro|NASID_META_BITS
mdefine_line|#define NASID_META_BITS&t;&t;0&t;/* ???? */
DECL|macro|NASID_LOCAL_BITS
mdefine_line|#define NASID_LOCAL_BITS&t;7&t;/* same router as SN1 */
DECL|macro|NODE_ADDRSPACE_SIZE
mdefine_line|#define NODE_ADDRSPACE_SIZE     (UINT64_CAST 1 &lt;&lt; NODE_SIZE_BITS)
DECL|macro|NASID_MASK
mdefine_line|#define NASID_MASK              (UINT64_CAST NASID_BITMASK &lt;&lt; NASID_SHFT)
DECL|macro|NASID_GET
mdefine_line|#define NASID_GET(_pa)          (int) ((UINT64_CAST (_pa) &gt;&gt;            &bslash;&n;                                        NASID_SHFT) &amp; NASID_BITMASK)
DECL|macro|CHANGE_NASID
mdefine_line|#define CHANGE_NASID(n,x)&t;({ia64_sn2_pa_t _v; _v.l = (long) (x); _v.f.nasid = n; _v.p;})
macro_line|#ifndef __ASSEMBLY__
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(nasid, widget)                                   &bslash;&n;        ((widget == 0) ? NODE_BWIN_BASE((nasid), SWIN0_BIGWIN)          &bslash;&n;        : RAW_NODE_SWIN_BASE(nasid, widget))
macro_line|#else
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(nasid, widget) &bslash;&n;     (NODE_IO_BASE(nasid) + (UINT64_CAST (widget) &lt;&lt; SWIN_SIZE_BITS))
DECL|macro|LOCAL_SWIN_BASE
mdefine_line|#define LOCAL_SWIN_BASE(widget) &bslash;&n;&t;(UNCACHED | LOCAL_MMR_SPACE | ((UINT64_CAST (widget) &lt;&lt; SWIN_SIZE_BITS)))
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|BWIN_INDEX_BITS
mdefine_line|#define BWIN_INDEX_BITS         3
DECL|macro|BWIN_SIZE
mdefine_line|#define BWIN_SIZE               (UINT64_CAST 1 &lt;&lt; BWIN_SIZE_BITS)
DECL|macro|BWIN_SIZEMASK
mdefine_line|#define BWIN_SIZEMASK           (BWIN_SIZE - 1)
DECL|macro|BWIN_WIDGET_MASK
mdefine_line|#define BWIN_WIDGET_MASK        0x7
DECL|macro|NODE_BWIN_BASE0
mdefine_line|#define NODE_BWIN_BASE0(nasid)  (NODE_IO_BASE(nasid) + BWIN_SIZE)
DECL|macro|NODE_BWIN_BASE
mdefine_line|#define NODE_BWIN_BASE(nasid, bigwin)   (NODE_BWIN_BASE0(nasid) +       &bslash;&n;                        (UINT64_CAST (bigwin) &lt;&lt; BWIN_SIZE_BITS))
DECL|macro|BWIN_WIDGETADDR
mdefine_line|#define BWIN_WIDGETADDR(addr)   ((addr) &amp; BWIN_SIZEMASK)
DECL|macro|BWIN_WINDOWNUM
mdefine_line|#define BWIN_WINDOWNUM(addr)    (((addr) &gt;&gt; BWIN_SIZE_BITS) &amp; BWIN_WIDGET_MASK)
multiline_comment|/*&n; * Verify if addr belongs to large window address of node with &quot;nasid&quot;&n; *&n; *&n; * NOTE: &quot;addr&quot; is expected to be XKPHYS address, and NOT physical&n; * address&n; *&n; *&n; */
DECL|macro|NODE_BWIN_ADDR
mdefine_line|#define NODE_BWIN_ADDR(nasid, addr)     &bslash;&n;                (((addr) &gt;= NODE_BWIN_BASE0(nasid)) &amp;&amp; &bslash;&n;                 ((addr) &lt; (NODE_BWIN_BASE(nasid, HUB_NUM_BIG_WINDOW) + &bslash;&n;                                BWIN_SIZE)))
macro_line|#endif&t;/* _ASM_IA64_SN_SN2_ADDRS_H */
eof
