multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1992-1999,2001-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_ADDRS_H
DECL|macro|_ASM_IA64_SN_ADDRS_H
mdefine_line|#define _ASM_IA64_SN_ADDRS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/sn2/addrs.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#endif 
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST&t;&t;(__psunsigned_t)
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST&t;&t;(uint64_t)
DECL|macro|HUBREG_CAST
mdefine_line|#define HUBREG_CAST&t;&t;(volatile mmr_t *)
macro_line|#elif __ASSEMBLY__
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST
DECL|macro|HUBREG_CAST
mdefine_line|#define HUBREG_CAST
macro_line|#endif
multiline_comment|/*&n; * The following macros are used to index to the beginning of a specific&n; * node&squot;s address space.&n; */
DECL|macro|NODE_OFFSET
mdefine_line|#define NODE_OFFSET(_n)&t;&t;(UINT64_CAST (_n) &lt;&lt; NASID_SHFT)
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
DECL|macro|TO_NODE
mdefine_line|#define TO_NODE(_n, _x)&t;&t;(NODE_OFFSET(_n)     | ((_x)&t;&t;   ))
DECL|macro|TO_NODE_CAC
mdefine_line|#define TO_NODE_CAC(_n, _x)&t;(NODE_CAC_BASE(_n) | ((_x) &amp; TO_PHYS_MASK))
DECL|macro|TO_NODE_UNCAC
mdefine_line|#define TO_NODE_UNCAC(_n, _x)&t;(NODE_UNCAC_BASE(_n) | ((_x) &amp; TO_PHYS_MASK))
DECL|macro|TO_NODE_MSPEC
mdefine_line|#define TO_NODE_MSPEC(_n, _x)&t;(NODE_MSPEC_BASE(_n) | ((_x) &amp; TO_PHYS_MASK))
DECL|macro|TO_NODE_HSPEC
mdefine_line|#define TO_NODE_HSPEC(_n, _x)&t;(NODE_HSPEC_BASE(_n) | ((_x) &amp; TO_PHYS_MASK))
DECL|macro|RAW_NODE_SWIN_BASE
mdefine_line|#define RAW_NODE_SWIN_BASE(nasid, widget)&t;&t;&t;&t;&bslash;&n;&t;(NODE_IO_BASE(nasid) + (UINT64_CAST (widget) &lt;&lt; SWIN_SIZE_BITS))
DECL|macro|WIDGETID_GET
mdefine_line|#define WIDGETID_GET(addr)&t;((unsigned char)((addr &gt;&gt; SWIN_SIZE_BITS) &amp; 0xff))
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|SWIN_SIZE_BITS
mdefine_line|#define SWIN_SIZE_BITS&t;&t;24
DECL|macro|SWIN_SIZE
mdefine_line|#define SWIN_SIZE&t;&t;(1UL&lt;&lt;24)
DECL|macro|SWIN_SIZEMASK
mdefine_line|#define&t;SWIN_SIZEMASK&t;&t;(SWIN_SIZE - 1)
DECL|macro|SWIN_WIDGET_MASK
mdefine_line|#define&t;SWIN_WIDGET_MASK&t;0xF
multiline_comment|/*&n; * Convert smallwindow address to xtalk address.&n; *&n; * &squot;addr&squot; can be physical or virtual address, but will be converted&n; * to Xtalk address in the range 0 -&gt; SWINZ_SIZEMASK&n; */
DECL|macro|SWIN_WIDGETADDR
mdefine_line|#define&t;SWIN_WIDGETADDR(addr)&t;((addr) &amp; SWIN_SIZEMASK)
DECL|macro|SWIN_WIDGETNUM
mdefine_line|#define&t;SWIN_WIDGETNUM(addr)&t;(((addr)  &gt;&gt; SWIN_SIZE_BITS) &amp; SWIN_WIDGET_MASK)
multiline_comment|/*&n; * Verify if addr belongs to small window address on node with &quot;nasid&quot;&n; *&n; *&n; * NOTE: &quot;addr&quot; is expected to be XKPHYS address, and NOT physical&n; * address&n; *&n; *&n; */
DECL|macro|NODE_SWIN_ADDR
mdefine_line|#define&t;NODE_SWIN_ADDR(nasid, addr)&t;&bslash;&n;&t;&t;(((addr) &gt;= NODE_SWIN_BASE(nasid, 0))  &amp;&amp; &bslash;&n;&t;&t; ((addr) &lt;  (NODE_SWIN_BASE(nasid, HUB_NUM_WIDGET) + SWIN_SIZE)&bslash;&n;&t;&t; ))
multiline_comment|/*&n; * The following define the major position-independent aliases used&n; * in SN.&n; *&t;LBOOT  -- 256MB in size, reads in the LBOOT area result in&n; *&t;&t;&t;uncached references to the local hub&squot;s boot prom and&n; *&t;&t;&t;other directory-bus connected devices.&n; *&t;IALIAS -- 8MB in size, reads in the IALIAS result in uncached&n; *&t;&t;&t;references to the local hub&squot;s registers.&n; */
DECL|macro|HUB_REGISTER_WIDGET
mdefine_line|#define&t;HUB_REGISTER_WIDGET&t;1
DECL|macro|IALIAS_BASE
mdefine_line|#define IALIAS_BASE&t;&t;LOCAL_SWIN_BASE(HUB_REGISTER_WIDGET)
DECL|macro|IALIAS_SIZE
mdefine_line|#define IALIAS_SIZE&t;&t;0x800000&t;/* 8 Megabytes */
DECL|macro|IS_IALIAS
mdefine_line|#define IS_IALIAS(_a)&t;&t;(((_a) &gt;= IALIAS_BASE) &amp;&amp;&t;&t;&bslash;&n;&t;&t;&t;&t; ((_a) &lt; (IALIAS_BASE + IALIAS_SIZE)))
multiline_comment|/*&n; * The following macros produce the correct base virtual address for&n; * the hub registers.  The LOCAL_HUB_* macros produce the appropriate&n; * address for the local registers.  The REMOTE_HUB_* macro produce&n; * the address for the specified hub&squot;s registers.  The intent is&n; * that the appropriate PI, MD, NI, or II register would be substituted&n; * for _x.&n; */
multiline_comment|/*&n; * SN2 has II mmr&squot;s located inside small window space.&n; * As all other non-II mmr&squot;s located at the top of big window&n; * space.&n; */
DECL|macro|LOCAL_HUB_BASE
mdefine_line|#define LOCAL_HUB_BASE(_x)&t;(LOCAL_MMR_ADDR(_x) | (((~(_x)) &amp; BWIN_TOP)&gt;&gt;8))
DECL|macro|REMOTE_HUB_BASE
mdefine_line|#define REMOTE_HUB_BASE(_x)&t;&t;&t;&t;&t;&t;&bslash;&n;        (UNCACHED | GLOBAL_MMR_SPACE |                                  &bslash;&n;        (((~(_x)) &amp; BWIN_TOP)&gt;&gt;8)    |                                       &bslash;&n;        (((~(_x)) &amp; BWIN_TOP)&gt;&gt;9)    | (_x))
DECL|macro|LOCAL_HUB
mdefine_line|#define LOCAL_HUB(_x) (HUBREG_CAST LOCAL_HUB_BASE(_x))
DECL|macro|REMOTE_HUB
mdefine_line|#define REMOTE_HUB(_n, _x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(HUBREG_CAST (REMOTE_HUB_BASE(_x) | ((((long)(_n))&lt;&lt;NASID_SHFT))))
multiline_comment|/*&n; * WARNING:&n; *&t;When certain Hub chip workaround are defined, it&squot;s not sufficient&n; *&t;to dereference the *_HUB_ADDR() macros.  You should instead use&n; *&t;HUB_L() and HUB_S() if you must deal with pointers to hub registers.&n; *&t;Otherwise, the recommended approach is to use *_HUB_L() and *_HUB_S().&n; *&t;They&squot;re always safe.&n; */
DECL|macro|LOCAL_HUB_ADDR
mdefine_line|#define LOCAL_HUB_ADDR(_x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((_x) &amp; BWIN_TOP) ? (HUBREG_CAST (LOCAL_MMR_ADDR(_x)))&t;&t;&bslash;&n;&t;: (HUBREG_CAST (IALIAS_BASE + (_x))))
DECL|macro|REMOTE_HUB_ADDR
mdefine_line|#define REMOTE_HUB_ADDR(_n, _x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((_x) &amp; BWIN_TOP) ? (HUBREG_CAST (GLOBAL_MMR_ADDR(_n, _x)))&t;&bslash;&n;&t;: (HUBREG_CAST (NODE_SWIN_BASE(_n, 1) + 0x800000 + (_x))))
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
mdefine_line|#define HUB_REG_PTR(_base, _off)&t;&bslash;&n;&t;(HUBREG_CAST ((__psunsigned_t)(_base) + (__psunsigned_t)(_off)))
DECL|macro|HUB_REG_PTR_L
mdefine_line|#define HUB_REG_PTR_L(_base, _off)&t;&bslash;&n;&t;HUB_L(HUB_REG_PTR((_base), (_off)))
DECL|macro|HUB_REG_PTR_S
mdefine_line|#define HUB_REG_PTR_S(_base, _off, _data)&t;&bslash;&n;&t;HUB_S(HUB_REG_PTR((_base), (_off)), (_data))
multiline_comment|/*&n; * Software structure locations -- permanently fixed&n; *    See diagram in kldir.h&n; */
DECL|macro|PHYS_RAMBASE
mdefine_line|#define PHYS_RAMBASE&t;&t;0x0
DECL|macro|K0_RAMBASE
mdefine_line|#define K0_RAMBASE&t;&t;PHYS_TO_K0(PHYS_RAMBASE)
DECL|macro|ARCS_SPB_OFFSET
mdefine_line|#define ARCS_SPB_OFFSET&t;&t;0x1000
DECL|macro|ARCS_SPB_ADDR
mdefine_line|#define ARCS_SPB_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;PHYS_TO_K0(NODE_OFFSET(nasid) | ARCS_SPB_OFFSET)
DECL|macro|ARCS_SPB_SIZE
mdefine_line|#define ARCS_SPB_SIZE&t;&t;0x0400
DECL|macro|KLDIR_OFFSET
mdefine_line|#define KLDIR_OFFSET&t;&t;0x2000
DECL|macro|KLDIR_ADDR
mdefine_line|#define KLDIR_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_CAC((nasid), KLDIR_OFFSET)
DECL|macro|KLDIR_SIZE
mdefine_line|#define KLDIR_SIZE&t;&t;0x0400
multiline_comment|/*&n; * Software structure locations -- indirected through KLDIR&n; *    See diagram in kldir.h&n; *&n; * Important:&t;All low memory structures must only be accessed&n; *&t;&t;uncached, except for the symmon stacks.&n; */
DECL|macro|KLI_LAUNCH
mdefine_line|#define KLI_LAUNCH&t;&t;0&t;&t;/* Dir. entries */
DECL|macro|KLI_KLCONFIG
mdefine_line|#define KLI_KLCONFIG&t;&t;1
DECL|macro|KLI_NMI
mdefine_line|#define&t;KLI_NMI&t;&t;&t;2
DECL|macro|KLI_GDA
mdefine_line|#define KLI_GDA&t;&t;&t;3
DECL|macro|KLI_FREEMEM
mdefine_line|#define KLI_FREEMEM&t;&t;4
DECL|macro|KLI_SYMMON_STK
mdefine_line|#define&t;KLI_SYMMON_STK&t;&t;5
DECL|macro|KLI_PI_ERROR
mdefine_line|#define KLI_PI_ERROR&t;&t;6
DECL|macro|KLI_KERN_VARS
mdefine_line|#define KLI_KERN_VARS&t;&t;7
DECL|macro|KLI_KERN_XP
mdefine_line|#define&t;KLI_KERN_XP&t;&t;8
DECL|macro|KLI_KERN_PARTID
mdefine_line|#define&t;KLI_KERN_PARTID&t;&t;9
macro_line|#ifndef __ASSEMBLY__
DECL|macro|KLD_BASE
mdefine_line|#define KLD_BASE(nasid)&t;&t;((kldir_ent_t *) KLDIR_ADDR(nasid))
DECL|macro|KLD_LAUNCH
mdefine_line|#define KLD_LAUNCH(nasid)&t;(KLD_BASE(nasid) + KLI_LAUNCH)
DECL|macro|KLD_NMI
mdefine_line|#define KLD_NMI(nasid)&t;&t;(KLD_BASE(nasid) + KLI_NMI)
DECL|macro|KLD_KLCONFIG
mdefine_line|#define KLD_KLCONFIG(nasid)&t;(KLD_BASE(nasid) + KLI_KLCONFIG)
DECL|macro|KLD_PI_ERROR
mdefine_line|#define KLD_PI_ERROR(nasid)&t;(KLD_BASE(nasid) + KLI_PI_ERROR)
DECL|macro|KLD_GDA
mdefine_line|#define KLD_GDA(nasid)&t;&t;(KLD_BASE(nasid) + KLI_GDA)
DECL|macro|KLD_SYMMON_STK
mdefine_line|#define KLD_SYMMON_STK(nasid)&t;(KLD_BASE(nasid) + KLI_SYMMON_STK)
DECL|macro|KLD_FREEMEM
mdefine_line|#define KLD_FREEMEM(nasid)&t;(KLD_BASE(nasid) + KLI_FREEMEM)
DECL|macro|KLD_KERN_VARS
mdefine_line|#define KLD_KERN_VARS(nasid)&t;(KLD_BASE(nasid) + KLI_KERN_VARS)
DECL|macro|KLD_KERN_XP
mdefine_line|#define&t;KLD_KERN_XP(nasid)&t;(KLD_BASE(nasid) + KLI_KERN_XP)
DECL|macro|KLD_KERN_PARTID
mdefine_line|#define&t;KLD_KERN_PARTID(nasid)&t;(KLD_BASE(nasid) + KLI_KERN_PARTID)
DECL|macro|KLCONFIG_OFFSET
mdefine_line|#define KLCONFIG_OFFSET(nasid)  ia64_sn_get_klconfig_addr(nasid)
DECL|macro|KLCONFIG_ADDR
mdefine_line|#define KLCONFIG_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_CAC((nasid), KLCONFIG_OFFSET(nasid))
DECL|macro|KLCONFIG_SIZE
mdefine_line|#define KLCONFIG_SIZE(nasid)&t;KLD_KLCONFIG(nasid)-&gt;size
DECL|macro|GDA_ADDR
mdefine_line|#define GDA_ADDR(nasid)&t;&t;KLD_GDA(nasid)-&gt;pointer
DECL|macro|GDA_SIZE
mdefine_line|#define GDA_SIZE(nasid)&t;&t;KLD_GDA(nasid)-&gt;size
DECL|macro|NODE_OFFSET_TO_K0
mdefine_line|#define NODE_OFFSET_TO_K0(_nasid, _off)&t;&t;&t;&t;&t;&bslash;&n;&t;(CACHEABLE_MEM_SPACE | NODE_OFFSET(_nasid) | (_off))
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_SN_ADDRS_H */
eof
