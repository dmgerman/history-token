multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1992-1999,2001-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_ADDRS_H
DECL|macro|_ASM_IA64_SN_ADDRS_H
mdefine_line|#define _ASM_IA64_SN_ADDRS_H
multiline_comment|/* McKinley Address Format:&n; *&n; *   4 4       3 3  3 3&n; *   9 8       8 7  6 5             0&n; *  +-+---------+----+--------------+&n; *  |0| Node ID | AS | Node Offset  |&n; *  +-+---------+----+--------------+&n; *&n; *   Node ID: If bit 38 = 1, is ICE, else is SHUB&n; *   AS: Address Space Identifier. Used only if bit 38 = 0.&n; *     b&squot;00: Local Resources and MMR space&n; *           bit 35&n; *               0: Local resources space&n; *                  node id:&n; *                        0: IA64/NT compatibility space&n; *                        2: Local MMR Space&n; *                        4: Local memory, regardless of local node id&n; *               1: Global MMR space&n; *     b&squot;01: GET space.&n; *     b&squot;10: AMO space.&n; *     b&squot;11: Cacheable memory space.&n; *&n; *   NodeOffset: byte offset&n; */
multiline_comment|/* TIO address format:&n; *  4 4        3 3 3 3 3             0&n; *  9 8        8 7 6 5 4&n; * +-+----------+-+---+--------------+&n; * |0| Node ID  |0|CID| Node offset  |&n; * +-+----------+-+---+--------------+&n; *&n; * Node ID: if bit 38 == 1, is ICE.&n; * Bit 37: Must be zero.&n; * CID: Chiplet ID:&n; *     b&squot;01: TIO LB (Indicates TIO MMR access.)&n; *     b&squot;11: TIO ICE (indicates coretalk space access.)&n; * Node offset: byte offest.&n; */
multiline_comment|/*&n; * Note that in both of the above address formats, bit&n; * 35 set indicates that the reference is to the &n; * shub or tio MMRs.&n; */
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
mdefine_line|#define TO_PHYS_MASK&t;&t;0x0001ffcfffffffffUL&t;/* Note - clear AS bits */
multiline_comment|/* Regions determined by AS */
DECL|macro|LOCAL_MMR_SPACE
mdefine_line|#define LOCAL_MMR_SPACE&t;&t;0xc000008000000000UL&t;/* Local MMR space */
DECL|macro|LOCAL_PHYS_MMR_SPACE
mdefine_line|#define LOCAL_PHYS_MMR_SPACE&t;0x8000008000000000UL&t;/* Local PhysicalMMR space */
DECL|macro|LOCAL_MEM_SPACE
mdefine_line|#define LOCAL_MEM_SPACE&t;&t;0xc000010000000000UL&t;/* Local Memory space */
multiline_comment|/* It so happens that setting bit 35 indicates a reference to the SHUB or TIO&n; * MMR space.  &n; */
DECL|macro|GLOBAL_MMR_SPACE
mdefine_line|#define GLOBAL_MMR_SPACE&t;0xc000000800000000UL&t;/* Global MMR space */
DECL|macro|TIO_MMR_SPACE
mdefine_line|#define TIO_MMR_SPACE&t;&t;0xc000000800000000UL&t;/* TIO MMR space */
DECL|macro|ICE_MMR_SPACE
mdefine_line|#define ICE_MMR_SPACE&t;&t;0xc000000000000000UL&t;/* ICE MMR space */
DECL|macro|GLOBAL_PHYS_MMR_SPACE
mdefine_line|#define GLOBAL_PHYS_MMR_SPACE&t;0x0000000800000000UL&t;/* Global Physical MMR space */
DECL|macro|GET_SPACE
mdefine_line|#define GET_SPACE&t;&t;0xe000001000000000UL&t;/* GET space */
DECL|macro|AMO_SPACE
mdefine_line|#define AMO_SPACE&t;&t;0xc000002000000000UL&t;/* AMO space */
DECL|macro|CACHEABLE_MEM_SPACE
mdefine_line|#define CACHEABLE_MEM_SPACE&t;0xe000003000000000UL&t;/* Cacheable memory space */
DECL|macro|UNCACHED
mdefine_line|#define UNCACHED                0xc000000000000000UL&t;/* UnCacheable memory space */
DECL|macro|UNCACHED_PHYS
mdefine_line|#define UNCACHED_PHYS           0x8000000000000000UL&t;/* UnCacheable physical memory space */
DECL|macro|PHYS_MEM_SPACE
mdefine_line|#define PHYS_MEM_SPACE&t;&t;0x0000003000000000UL&t;/* physical memory space */
multiline_comment|/* SN2 address macros */
multiline_comment|/* NID_SHFT has the right value for both SHUB and TIO addresses.*/
DECL|macro|NID_SHFT
mdefine_line|#define NID_SHFT&t;&t;38
DECL|macro|LOCAL_MMR_ADDR
mdefine_line|#define LOCAL_MMR_ADDR(a)&t;(UNCACHED | LOCAL_MMR_SPACE | (a))
DECL|macro|LOCAL_MMR_PHYS_ADDR
mdefine_line|#define LOCAL_MMR_PHYS_ADDR(a)&t;(UNCACHED_PHYS | LOCAL_PHYS_MMR_SPACE | (a))
DECL|macro|LOCAL_MEM_ADDR
mdefine_line|#define LOCAL_MEM_ADDR(a)&t;(LOCAL_MEM_SPACE | (a))
DECL|macro|REMOTE_ADDR
mdefine_line|#define REMOTE_ADDR(n,a)&t;((((unsigned long)(n))&lt;&lt;NID_SHFT) | (a))
DECL|macro|GLOBAL_MMR_ADDR
mdefine_line|#define GLOBAL_MMR_ADDR(n,a)&t;(UNCACHED | GLOBAL_MMR_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GLOBAL_MMR_PHYS_ADDR
mdefine_line|#define GLOBAL_MMR_PHYS_ADDR(n,a) (UNCACHED_PHYS | GLOBAL_PHYS_MMR_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GET_ADDR
mdefine_line|#define GET_ADDR(n,a)&t;&t;(GET_SPACE | REMOTE_ADDR(n,a))
DECL|macro|AMO_ADDR
mdefine_line|#define AMO_ADDR(n,a)&t;&t;(UNCACHED | AMO_SPACE | REMOTE_ADDR(n,a))
DECL|macro|GLOBAL_MEM_ADDR
mdefine_line|#define GLOBAL_MEM_ADDR(n,a)&t;(CACHEABLE_MEM_SPACE | REMOTE_ADDR(n,a))
multiline_comment|/* non-II mmr&squot;s start at top of big window space (4G) */
DECL|macro|BWIN_TOP
mdefine_line|#define BWIN_TOP&t;&t;0x0000000100000000UL
multiline_comment|/*&n; * general address defines - for code common to SN0/SN1/SN2&n; */
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;CACHEABLE_MEM_SPACE&t;&t;&t;/* cacheable memory space */
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;(UNCACHED | GLOBAL_MMR_SPACE)&t;&t;/* lower 4G maps II&squot;s XIO space */
DECL|macro|TIO_BASE
mdefine_line|#define TIO_BASE&t;&t;(UNCACHED | ICE_MMR_SPACE)&t;&t;/* lower 4G maps TIO space */
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
DECL|macro|TIO_BWIN_SIZE_BITS
mdefine_line|#define TIO_BWIN_SIZE_BITS&t;30&t;/* big window size: 1G */
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
mdefine_line|#define NODE_ADDRSPACE_SIZE     (1UL &lt;&lt; NODE_SIZE_BITS)
DECL|macro|NASID_MASK
mdefine_line|#define NASID_MASK              ((uint64_t) NASID_BITMASK &lt;&lt; NASID_SHFT)
DECL|macro|NASID_GET
mdefine_line|#define NASID_GET(_pa)          (int) (((uint64_t) (_pa) &gt;&gt;            &bslash;&n;                                        NASID_SHFT) &amp; NASID_BITMASK)
DECL|macro|PHYS_TO_DMA
mdefine_line|#define PHYS_TO_DMA(x)          ( ((x &amp; NASID_MASK) &gt;&gt; 2) |             &bslash;&n;                                  (x &amp; (NODE_ADDRSPACE_SIZE - 1)) )
multiline_comment|/*&n; * This address requires a chiplet id in bits 38-39.  For DMA to memory,&n; * the chiplet id is zero.  If we implement TIO-TIO dma, we might need&n; * to insert a chiplet id into this macro.  However, it is our belief&n; * right now that this chiplet id will be ICE, which is also zero.&n; */
DECL|macro|PHYS_TO_TIODMA
mdefine_line|#define PHYS_TO_TIODMA(x)     ( ((x &amp; NASID_MASK) &lt;&lt; 2) |             &bslash;&n;                                 (x &amp; (NODE_ADDRSPACE_SIZE - 1)) )
DECL|macro|CHANGE_NASID
mdefine_line|#define CHANGE_NASID(n,x)&t;({ia64_sn2_pa_t _v; _v.l = (long) (x); _v.f.nasid = n; _v.p;})
macro_line|#ifndef __ASSEMBLY__
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(nasid, widget)                                   &bslash;&n;        ((widget == 0) ? NODE_BWIN_BASE((nasid), SWIN0_BIGWIN)          &bslash;&n;        : RAW_NODE_SWIN_BASE(nasid, widget))
macro_line|#else
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(nasid, widget) &bslash;&n;     (NODE_IO_BASE(nasid) + ((uint64_t) (widget) &lt;&lt; SWIN_SIZE_BITS))
DECL|macro|LOCAL_SWIN_BASE
mdefine_line|#define LOCAL_SWIN_BASE(widget) &bslash;&n;&t;(UNCACHED | LOCAL_MMR_SPACE | (((uint64_t) (widget) &lt;&lt; SWIN_SIZE_BITS)))
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|BWIN_SIZE
mdefine_line|#define BWIN_SIZE               (1UL &lt;&lt; BWIN_SIZE_BITS)
DECL|macro|BWIN_SIZEMASK
mdefine_line|#define BWIN_SIZEMASK           (BWIN_SIZE - 1)
DECL|macro|BWIN_WIDGET_MASK
mdefine_line|#define BWIN_WIDGET_MASK        0x7
DECL|macro|NODE_BWIN_BASE0
mdefine_line|#define NODE_BWIN_BASE0(nasid)  (NODE_IO_BASE(nasid) + BWIN_SIZE)
DECL|macro|NODE_BWIN_BASE
mdefine_line|#define NODE_BWIN_BASE(nasid, bigwin)   (NODE_BWIN_BASE0(nasid) +       &bslash;&n;                        ((uint64_t) (bigwin) &lt;&lt; BWIN_SIZE_BITS))
DECL|macro|BWIN_WIDGETADDR
mdefine_line|#define BWIN_WIDGETADDR(addr)   ((addr) &amp; BWIN_SIZEMASK)
DECL|macro|BWIN_WINDOWNUM
mdefine_line|#define BWIN_WINDOWNUM(addr)    (((addr) &gt;&gt; BWIN_SIZE_BITS) &amp; BWIN_WIDGET_MASK)
DECL|macro|TIO_BWIN_WINDOW_SELECT_MASK
mdefine_line|#define TIO_BWIN_WINDOW_SELECT_MASK 0x7
DECL|macro|TIO_BWIN_WINDOWNUM
mdefine_line|#define TIO_BWIN_WINDOWNUM(addr)    (((addr) &gt;&gt; TIO_BWIN_SIZE_BITS) &amp; TIO_BWIN_WINDOW_SELECT_MASK)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#endif 
multiline_comment|/*&n; * The following macros are used to index to the beginning of a specific&n; * node&squot;s address space.&n; */
DECL|macro|NODE_OFFSET
mdefine_line|#define NODE_OFFSET(_n)&t;&t;((uint64_t) (_n) &lt;&lt; NASID_SHFT)
DECL|macro|NODE_CAC_BASE
mdefine_line|#define NODE_CAC_BASE(_n)&t;(CAC_BASE  + NODE_OFFSET(_n))
DECL|macro|NODE_HSPEC_BASE
mdefine_line|#define NODE_HSPEC_BASE(_n)&t;(HSPEC_BASE + NODE_OFFSET(_n))
DECL|macro|NODE_IO_BASE
mdefine_line|#define NODE_IO_BASE(_n)&t;(IO_BASE    + NODE_OFFSET(_n))
DECL|macro|NODE_MSPEC_BASE
mdefine_line|#define NODE_MSPEC_BASE(_n)&t;(MSPEC_BASE + NODE_OFFSET(_n))
DECL|macro|NODE_UNCAC_BASE
mdefine_line|#define NODE_UNCAC_BASE(_n)&t;(UNCAC_BASE + NODE_OFFSET(_n))
DECL|macro|TO_NODE_CAC
mdefine_line|#define TO_NODE_CAC(_n, _x)&t;(NODE_CAC_BASE(_n) | ((_x) &amp; TO_PHYS_MASK))
DECL|macro|RAW_NODE_SWIN_BASE
mdefine_line|#define RAW_NODE_SWIN_BASE(nasid, widget)&t;&t;&t;&t;&bslash;&n;&t;(NODE_IO_BASE(nasid) + ((uint64_t) (widget) &lt;&lt; SWIN_SIZE_BITS))
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|SWIN_SIZE_BITS
mdefine_line|#define SWIN_SIZE_BITS&t;&t;24
DECL|macro|SWIN_SIZE
mdefine_line|#define SWIN_SIZE&t;&t;(1UL &lt;&lt; 24)
DECL|macro|SWIN_SIZEMASK
mdefine_line|#define&t;SWIN_SIZEMASK&t;&t;(SWIN_SIZE - 1)
DECL|macro|SWIN_WIDGET_MASK
mdefine_line|#define&t;SWIN_WIDGET_MASK&t;0xF
DECL|macro|TIO_SWIN_SIZE_BITS
mdefine_line|#define TIO_SWIN_SIZE_BITS&t;28
DECL|macro|TIO_SWIN_SIZE
mdefine_line|#define TIO_SWIN_SIZE&t;&t;(1UL &lt;&lt; 28)
DECL|macro|TIO_SWIN_SIZEMASK
mdefine_line|#define TIO_SWIN_SIZEMASK&t;(SWIN_SIZE - 1)
DECL|macro|TIO_SWIN_WIDGET_MASK
mdefine_line|#define TIO_SWIN_WIDGET_MASK&t;0x3
multiline_comment|/*&n; * Convert smallwindow address to xtalk address.&n; *&n; * &squot;addr&squot; can be physical or virtual address, but will be converted&n; * to Xtalk address in the range 0 -&gt; SWINZ_SIZEMASK&n; */
DECL|macro|SWIN_WIDGETNUM
mdefine_line|#define&t;SWIN_WIDGETNUM(addr)&t;(((addr)  &gt;&gt; SWIN_SIZE_BITS) &amp; SWIN_WIDGET_MASK)
DECL|macro|TIO_SWIN_WIDGETNUM
mdefine_line|#define TIO_SWIN_WIDGETNUM(addr)&t;(((addr)  &gt;&gt; TIO_SWIN_SIZE_BITS) &amp; TIO_SWIN_WIDGET_MASK)
multiline_comment|/*&n; * The following macros produce the correct base virtual address for&n; * the hub registers.  The LOCAL_HUB_* macros produce the appropriate&n; * address for the local registers.  The REMOTE_HUB_* macro produce&n; * the address for the specified hub&squot;s registers.  The intent is&n; * that the appropriate PI, MD, NI, or II register would be substituted&n; * for _x.&n; */
multiline_comment|/*&n; * SN2 has II mmr&squot;s located inside small window space.&n; * As all other non-II mmr&squot;s located at the top of big window&n; * space.&n; */
DECL|macro|REMOTE_HUB_BASE
mdefine_line|#define REMOTE_HUB_BASE(_x)&t;&t;&t;&t;&t;&t;&bslash;&n;        (UNCACHED | GLOBAL_MMR_SPACE |                                  &bslash;&n;        (((~(_x)) &amp; BWIN_TOP)&gt;&gt;8)    |                                       &bslash;&n;        (((~(_x)) &amp; BWIN_TOP)&gt;&gt;9)    | (_x))
DECL|macro|REMOTE_HUB
mdefine_line|#define REMOTE_HUB(_n, _x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((uint64_t *)(REMOTE_HUB_BASE(_x) | ((((long)(_n))&lt;&lt;NASID_SHFT))))
multiline_comment|/*&n; * WARNING:&n; *&t;When certain Hub chip workaround are defined, it&squot;s not sufficient&n; *&t;to dereference the *_HUB_ADDR() macros.  You should instead use&n; *&t;HUB_L() and HUB_S() if you must deal with pointers to hub registers.&n; *&t;Otherwise, the recommended approach is to use *_HUB_L() and *_HUB_S().&n; *&t;They&squot;re always safe.&n; */
multiline_comment|/*&n; * LOCAL_HUB_ADDR doesn&squot;t need to be changed for TIO, since, by definition,&n; * there are no &quot;local&quot; TIOs.&n; */
DECL|macro|LOCAL_HUB_ADDR
mdefine_line|#define LOCAL_HUB_ADDR(_x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((_x) &amp; BWIN_TOP) ? ((volatile uint64_t *)(LOCAL_MMR_ADDR(_x)))&t;&t;&bslash;&n;&t;: ((volatile uint64_t *)(IALIAS_BASE + (_x))))
DECL|macro|REMOTE_HUB_ADDR
mdefine_line|#define REMOTE_HUB_ADDR(_n, _x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((_n &amp; 1) ?&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* TIO: */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((volatile uint64_t *)(GLOBAL_MMR_ADDR(_n, _x)))&t;&t;&t;&t;&bslash;&n;&t;: /* SHUB: */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((_x) &amp; BWIN_TOP) ? ((volatile uint64_t *)(GLOBAL_MMR_ADDR(_n, _x)))&t;&bslash;&n;&t;: ((volatile uint64_t *)(NODE_SWIN_BASE(_n, 1) + 0x800000 + (_x)))))
macro_line|#ifndef __ASSEMBLY__
DECL|macro|HUB_L
mdefine_line|#define HUB_L(_a)&t;&t;&t;(*((volatile typeof(*_a) *)_a))
DECL|macro|HUB_S
mdefine_line|#define&t;HUB_S(_a, _d)&t;&t;&t;(*((volatile typeof(*_a) *)_a) = (_d))
DECL|macro|LOCAL_HUB_L
mdefine_line|#define LOCAL_HUB_L(_r)&t;&t;&t;HUB_L(LOCAL_HUB_ADDR(_r))
DECL|macro|LOCAL_HUB_S
mdefine_line|#define LOCAL_HUB_S(_r, _d)&t;&t;HUB_S(LOCAL_HUB_ADDR(_r), (_d))
DECL|macro|REMOTE_HUB_L
mdefine_line|#define REMOTE_HUB_L(_n, _r)&t;&t;HUB_L(REMOTE_HUB_ADDR((_n), (_r)))
DECL|macro|REMOTE_HUB_S
mdefine_line|#define REMOTE_HUB_S(_n, _r, _d)&t;HUB_S(REMOTE_HUB_ADDR((_n), (_r)), (_d))
DECL|macro|REMOTE_HUB_PI_L
mdefine_line|#define REMOTE_HUB_PI_L(_n, _sn, _r)&t;HUB_L(REMOTE_HUB_PI_ADDR((_n), (_sn), (_r)))
DECL|macro|REMOTE_HUB_PI_S
mdefine_line|#define REMOTE_HUB_PI_S(_n, _sn, _r, _d) HUB_S(REMOTE_HUB_PI_ADDR((_n), (_sn), (_r)), (_d))
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * The following macros are used to get to a hub/bridge register, given&n; * the base of the register space.&n; */
DECL|macro|HUB_REG_PTR
mdefine_line|#define HUB_REG_PTR(_base, _off)&t;&bslash;&n;&t;(volatile uint64_t *)((unsigned long)(_base) + (__psunsigned_t)(_off)))
DECL|macro|HUB_REG_PTR_L
mdefine_line|#define HUB_REG_PTR_L(_base, _off)&t;&bslash;&n;&t;HUB_L(HUB_REG_PTR((_base), (_off)))
DECL|macro|HUB_REG_PTR_S
mdefine_line|#define HUB_REG_PTR_S(_base, _off, _data)&t;&bslash;&n;&t;HUB_S(HUB_REG_PTR((_base), (_off)), (_data))
macro_line|#endif /* _ASM_IA64_SN_ADDRS_H */
eof
