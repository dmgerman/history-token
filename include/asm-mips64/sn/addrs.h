multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 1999, 2000 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SN_ADDRS_H
DECL|macro|_ASM_SN_ADDRS_H
mdefine_line|#define _ASM_SN_ADDRS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if _LANGUAGE_C
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif /* _LANGUAGE_C */
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/sn/kldir.h&gt;
macro_line|#if defined(CONFIG_SGI_IP27)
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
macro_line|#elif defined(CONFIG_SGI_IP35)
macro_line|#include &lt;asm/sn/sn1/addrs.h&gt;
macro_line|#endif
macro_line|#if _LANGUAGE_C
macro_line|#if defined(CONFIG_SGI_IO)&t;/* FIXME */
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST&t;&t;(__psunsigned_t)
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST&t;&t;(__uint64_t)
macro_line|#else&t;/* CONFIG_SGI_IO */
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST&t;&t;(unsigned long)
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST&t;&t;(unsigned long)
macro_line|#endif&t;/* CONFIG_SGI_IO */
DECL|macro|HUBREG_CAST
mdefine_line|#define HUBREG_CAST&t;&t;(volatile hubreg_t *)
macro_line|#elif _LANGUAGE_ASSEMBLY
DECL|macro|PS_UINT_CAST
mdefine_line|#define PS_UINT_CAST
DECL|macro|UINT64_CAST
mdefine_line|#define UINT64_CAST
DECL|macro|HUBREG_CAST
mdefine_line|#define HUBREG_CAST
macro_line|#endif
DECL|macro|NASID_GET_META
mdefine_line|#define NASID_GET_META(_n)&t;((_n) &gt;&gt; NASID_LOCAL_BITS)
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|NASID_GET_LOCAL
mdefine_line|#define NASID_GET_LOCAL(_n)&t;((_n) &amp; 0xf)
macro_line|#endif
DECL|macro|NASID_MAKE
mdefine_line|#define NASID_MAKE(_m, _l)&t;(((_m) &lt;&lt; NASID_LOCAL_BITS) | (_l))
DECL|macro|NODE_ADDRSPACE_MASK
mdefine_line|#define NODE_ADDRSPACE_MASK&t;(NODE_ADDRSPACE_SIZE - 1)
DECL|macro|TO_NODE_ADDRSPACE
mdefine_line|#define TO_NODE_ADDRSPACE(_pa)&t;(UINT64_CAST (_pa) &amp; NODE_ADDRSPACE_MASK)
DECL|macro|CHANGE_ADDR_NASID
mdefine_line|#define CHANGE_ADDR_NASID(_pa, _nasid)&t;&bslash;&n;&t;&t;((UINT64_CAST (_pa) &amp; ~NASID_MASK) | &bslash;&n;&t;&t; (UINT64_CAST(_nasid) &lt;&lt;  NASID_SHFT))
multiline_comment|/*&n; * The following macros are used to index to the beginning of a specific&n; * node&squot;s address space.&n; */
DECL|macro|NODE_OFFSET
mdefine_line|#define NODE_OFFSET(_n)&t;&t;(UINT64_CAST (_n) &lt;&lt; NODE_SIZE_BITS)
DECL|macro|NODE_CAC_BASE
mdefine_line|#define NODE_CAC_BASE(_n)&t;(CAC_BASE   + NODE_OFFSET(_n))
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
mdefine_line|#define TO_NODE_CAC(_n, _x)&t;(NODE_CAC_BASE(_n)   | ((_x) &amp; TO_PHYS_MASK))
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
mdefine_line|#define SWIN_SIZE&t;&t;(UINT64_CAST 1 &lt;&lt; 24)
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
multiline_comment|/*&n; * The following define the major position-independent aliases used&n; * in SN.&n; *&t;UALIAS -- 256MB in size, reads in the UALIAS result in&n; *&t;&t;&t;uncached references to the memory of the reader&squot;s node.&n; *&t;CPU_UALIAS -- 128kb in size, the bottom part of UALIAS is flipped&n; *&t;&t;&t;depending on which CPU does the access to provide&n; *&t;&t;&t;all CPUs with unique uncached memory at low addresses.&n; *&t;LBOOT  -- 256MB in size, reads in the LBOOT area result in&n; *&t;&t;&t;uncached references to the local hub&squot;s boot prom and&n; *&t;&t;&t;other directory-bus connected devices.&n; *&t;IALIAS -- 8MB in size, reads in the IALIAS result in uncached&n; *&t;&t;&t;references to the local hub&squot;s registers.&n; */
DECL|macro|UALIAS_BASE
mdefine_line|#define UALIAS_BASE&t;&t;HSPEC_BASE
DECL|macro|UALIAS_SIZE
mdefine_line|#define UALIAS_SIZE&t;&t;0x10000000&t;/* 256 Megabytes */
DECL|macro|UALIAS_LIMIT
mdefine_line|#define UALIAS_LIMIT&t;&t;(UALIAS_BASE + UALIAS_SIZE)
multiline_comment|/*&n; * The bottom of ualias space is flipped depending on whether you&squot;re&n; * processor 0 or 1 within a node.&n; */
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|UALIAS_FLIP_BASE
mdefine_line|#define UALIAS_FLIP_BASE&t;UALIAS_BASE
DECL|macro|UALIAS_FLIP_SIZE
mdefine_line|#define UALIAS_FLIP_SIZE&t;0x20000
DECL|macro|UALIAS_FLIP_BIT
mdefine_line|#define UALIAS_FLIP_BIT&t;&t;0x10000
DECL|macro|UALIAS_FLIP_ADDR
mdefine_line|#define UALIAS_FLIP_ADDR(_x)&t;(cputoslice(smp_processor_id()) ? &bslash;&n;&t;&t;&t;&t; (_x) ^ UALIAS_FLIP_BIT : (_x))
DECL|macro|LBOOT_BASE
mdefine_line|#define LBOOT_BASE&t;&t;(HSPEC_BASE + 0x10000000)
DECL|macro|LBOOT_SIZE
mdefine_line|#define LBOOT_SIZE&t;&t;0x10000000
DECL|macro|LBOOT_LIMIT
mdefine_line|#define LBOOT_LIMIT&t;&t;(LBOOT_BASE + LBOOT_SIZE)
DECL|macro|LBOOT_STRIDE
mdefine_line|#define LBOOT_STRIDE&t;&t;0&t;&t;/* IP27 has only one CPU PROM */
macro_line|#endif
DECL|macro|HUB_REGISTER_WIDGET
mdefine_line|#define&t;HUB_REGISTER_WIDGET&t;1
DECL|macro|IALIAS_BASE
mdefine_line|#define IALIAS_BASE&t;&t;NODE_SWIN_BASE(0, HUB_REGISTER_WIDGET)
DECL|macro|IALIAS_SIZE
mdefine_line|#define IALIAS_SIZE&t;&t;0x800000&t;/* 8 Megabytes */
DECL|macro|IS_IALIAS
mdefine_line|#define IS_IALIAS(_a)&t;&t;(((_a) &gt;= IALIAS_BASE) &amp;&amp;&t;&t;&bslash;&n;&t;&t;&t;&t; ((_a) &lt; (IALIAS_BASE + IALIAS_SIZE)))
multiline_comment|/*&n; * Macro for referring to Hub&squot;s RBOOT space&n; */
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|RBOOT_SIZE
mdefine_line|#define RBOOT_SIZE&t;&t;0x10000000&t;/* 256 Megabytes */
DECL|macro|NODE_RBOOT_BASE
mdefine_line|#define NODE_RBOOT_BASE(_n)&t;(NODE_HSPEC_BASE(_n) + 0x30000000)
DECL|macro|NODE_RBOOT_LIMIT
mdefine_line|#define NODE_RBOOT_LIMIT(_n)&t;(NODE_RBOOT_BASE(_n) + RBOOT_SIZE)
macro_line|#endif
multiline_comment|/*&n; * Macros for referring the Hub&squot;s back door space&n; *&n; *   These macros correctly process addresses in any node&squot;s space.&n; *   WARNING: They won&squot;t work in assembler.&n; *&n; *   BDDIR_ENTRY_LO returns the address of the low double-word of the dir&n; *                  entry corresponding to a physical (Cac or Uncac) address.&n; *   BDDIR_ENTRY_HI returns the address of the high double-word of the entry.&n; *   BDPRT_ENTRY    returns the address of the double-word protection entry&n; *                  corresponding to the page containing the physical address.&n; *   BDPRT_ENTRY_S  Stores the value into the protection entry.&n; *   BDPRT_ENTRY_L  Load the value from the protection entry.&n; *   BDECC_ENTRY    returns the address of the ECC byte corresponding to a&n; *                  double-word at a specified physical address.&n; *   BDECC_ENTRY_H  returns the address of the two ECC bytes corresponding to a&n; *                  quad-word at a specified physical address.&n; */
DECL|macro|NODE_BDOOR_BASE
mdefine_line|#define NODE_BDOOR_BASE(_n)&t;(NODE_HSPEC_BASE(_n) + (NODE_ADDRSPACE_SIZE/2))
DECL|macro|NODE_BDECC_BASE
mdefine_line|#define NODE_BDECC_BASE(_n)&t;(NODE_BDOOR_BASE(_n))
DECL|macro|NODE_BDDIR_BASE
mdefine_line|#define NODE_BDDIR_BASE(_n)&t;(NODE_BDOOR_BASE(_n) + (NODE_ADDRSPACE_SIZE/4))
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|BDDIR_ENTRY_LO
mdefine_line|#define BDDIR_ENTRY_LO(_pa)&t;((HSPEC_BASE +&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&t;  NODE_ADDRSPACE_SIZE * 3 / 4 +&t;&t;      &bslash;&n;&t;&t;&t;&t;  0x200)&t;&t;&t;&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa)&t; &amp; NASID_MASK&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 2 &amp; BDDIR_UPPER_MASK  | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 3 &amp; 0x1f &lt;&lt; 4)
DECL|macro|BDDIR_ENTRY_HI
mdefine_line|#define BDDIR_ENTRY_HI(_pa)&t;((HSPEC_BASE +&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&t;  NODE_ADDRSPACE_SIZE * 3 / 4 +&t;&t;      &bslash;&n;&t;&t;&t;&t;  0x208)&t;&t;&t;&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa)&t; &amp; NASID_MASK&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 2 &amp; BDDIR_UPPER_MASK  | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 3 &amp; 0x1f &lt;&lt; 4)
DECL|macro|BDPRT_ENTRY
mdefine_line|#define BDPRT_ENTRY(_pa, _rgn)&t;((HSPEC_BASE +&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&t;  NODE_ADDRSPACE_SIZE * 3 / 4)&t;&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa)&t; &amp; NASID_MASK&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 2 &amp; BDDIR_UPPER_MASK  | &bslash;&n;&t;&t;&t;&t; (_rgn) &lt;&lt; 3)
DECL|macro|BDPRT_ENTRY_ADDR
mdefine_line|#define BDPRT_ENTRY_ADDR(_pa,_rgn) (BDPRT_ENTRY((_pa),(_rgn)))
DECL|macro|BDPRT_ENTRY_S
mdefine_line|#define BDPRT_ENTRY_S(_pa,_rgn,_val) (*(__psunsigned_t *)BDPRT_ENTRY((_pa),(_rgn))=(_val))
DECL|macro|BDPRT_ENTRY_L
mdefine_line|#define BDPRT_ENTRY_L(_pa,_rgn)&t;(*(__psunsigned_t *)BDPRT_ENTRY((_pa),(_rgn)))
DECL|macro|BDECC_ENTRY
mdefine_line|#define BDECC_ENTRY(_pa)&t;((HSPEC_BASE +&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;&t;  NODE_ADDRSPACE_SIZE / 2)&t;&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa)&t; &amp; NASID_MASK&t;    | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 2 &amp; BDECC_UPPER_MASK  | &bslash;&n;&t;&t;&t;&t; UINT64_CAST (_pa) &gt;&gt; 3 &amp; 3)
multiline_comment|/*&n; * Macro to convert a back door directory or protection address into the&n; *   raw physical address of the associated cache line or protection page.&n; */
DECL|macro|BDADDR_IS_DIR
mdefine_line|#define BDADDR_IS_DIR(_ba)&t;((UINT64_CAST  (_ba) &amp; 0x200) != 0)
DECL|macro|BDADDR_IS_PRT
mdefine_line|#define BDADDR_IS_PRT(_ba)&t;((UINT64_CAST  (_ba) &amp; 0x200) == 0)
DECL|macro|BDDIR_TO_MEM
mdefine_line|#define BDDIR_TO_MEM(_ba)&t;(UINT64_CAST  (_ba) &amp; NASID_MASK            | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST (_ba) &amp; BDDIR_UPPER_MASK)&lt;&lt;2  | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST (_ba) &amp; 0x1f &lt;&lt; 4) &lt;&lt; 3)
DECL|macro|BDPRT_TO_MEM
mdefine_line|#define BDPRT_TO_MEM(_ba) &t;(UINT64_CAST  (_ba) &amp; NASID_MASK&t;    | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST (_ba) &amp; BDDIR_UPPER_MASK)&lt;&lt;2)
DECL|macro|BDECC_TO_MEM
mdefine_line|#define BDECC_TO_MEM(_ba)&t;(UINT64_CAST  (_ba) &amp; NASID_MASK&t;    | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST (_ba) &amp; BDECC_UPPER_MASK)&lt;&lt;2  | &bslash;&n;&t;&t;&t;&t; (UINT64_CAST (_ba) &amp; 3) &lt;&lt; 3)
macro_line|#endif /* CONFIG_SGI_IP27 */
multiline_comment|/*&n; * The following macros produce the correct base virtual address for&n; * the hub registers.  The LOCAL_HUB_* macros produce the appropriate&n; * address for the local registers.  The REMOTE_HUB_* macro produce&n; * the address for the specified hub&squot;s registers.  The intent is&n; * that the appropriate PI, MD, NI, or II register would be substituted&n; * for _x.&n; */
macro_line|#ifdef _STANDALONE
multiline_comment|/* DO NOT USE THESE DIRECTLY IN THE KERNEL. SEE BELOW. */
DECL|macro|LOCAL_HUB
mdefine_line|#define LOCAL_HUB(_x)&t;&t;(HUBREG_CAST (IALIAS_BASE + (_x)))
DECL|macro|REMOTE_HUB
mdefine_line|#define REMOTE_HUB(_n, _x)&t;(HUBREG_CAST (NODE_SWIN_BASE(_n, 1) +&t;&bslash;&n;&t;&t;&t;&t;&t;      0x800000 + (_x)))
macro_line|#endif /* _STANDALONE */
multiline_comment|/*&n; * WARNING:&n; *&t;When certain Hub chip workaround are defined, it&squot;s not sufficient&n; *&t;to dereference the *_HUB_ADDR() macros.  You should instead use&n; *&t;HUB_L() and HUB_S() if you must deal with pointers to hub registers.&n; *&t;Otherwise, the recommended approach is to use *_HUB_L() and *_HUB_S().&n; *&t;They&squot;re always safe.&n; */
DECL|macro|LOCAL_HUB_ADDR
mdefine_line|#define LOCAL_HUB_ADDR(_x)&t;(HUBREG_CAST (IALIAS_BASE + (_x)))
DECL|macro|REMOTE_HUB_ADDR
mdefine_line|#define REMOTE_HUB_ADDR(_n, _x)&t;(HUBREG_CAST (NODE_SWIN_BASE(_n, 1) +&t;&bslash;&n;&t;&t;&t;&t;&t;      0x800000 + (_x)))
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|REMOTE_HUB_PI_ADDR
mdefine_line|#define REMOTE_HUB_PI_ADDR(_n, _sn, _x)&t;(HUBREG_CAST (NODE_SWIN_BASE(_n, 1) +&t;&bslash;&n;&t;&t;&t;&t;&t;      0x800000 + (_x)))
macro_line|#endif /* CONFIG_SGI_IP27 */
macro_line|#if _LANGUAGE_C
DECL|macro|HUB_L
mdefine_line|#define HUB_L(_a)&t;&t;&t;*(_a)
DECL|macro|HUB_S
mdefine_line|#define&t;HUB_S(_a, _d)&t;&t;&t;*(_a) = (_d)
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
macro_line|#endif /* _LANGUAGE_C */
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
DECL|macro|EX_HANDLER_OFFSET
mdefine_line|#define EX_HANDLER_OFFSET(slice) ((slice) &lt;&lt; 16)
DECL|macro|EX_HANDLER_ADDR
mdefine_line|#define EX_HANDLER_ADDR(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;PHYS_TO_K0(NODE_OFFSET(nasid) | EX_HANDLER_OFFSET(slice))
DECL|macro|EX_HANDLER_SIZE
mdefine_line|#define EX_HANDLER_SIZE&t;&t;0x0400
DECL|macro|EX_FRAME_OFFSET
mdefine_line|#define EX_FRAME_OFFSET(slice)&t;((slice) &lt;&lt; 16 | 0x400)
DECL|macro|EX_FRAME_ADDR
mdefine_line|#define EX_FRAME_ADDR(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;PHYS_TO_K0(NODE_OFFSET(nasid) | EX_FRAME_OFFSET(slice))
DECL|macro|EX_FRAME_SIZE
mdefine_line|#define EX_FRAME_SIZE&t;&t;0x0c00
DECL|macro|ARCS_SPB_OFFSET
mdefine_line|#define ARCS_SPB_OFFSET&t;&t;0x1000
DECL|macro|ARCS_SPB_ADDR
mdefine_line|#define ARCS_SPB_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;PHYS_TO_K0(NODE_OFFSET(nasid) | ARCS_SPB_OFFSET)
DECL|macro|ARCS_SPB_SIZE
mdefine_line|#define ARCS_SPB_SIZE&t;&t;0x0400
macro_line|#ifdef _STANDALONE
DECL|macro|ARCS_TVECTOR_OFFSET
mdefine_line|#define ARCS_TVECTOR_OFFSET&t;0x2800
DECL|macro|ARCS_PVECTOR_OFFSET
mdefine_line|#define ARCS_PVECTOR_OFFSET&t;0x2c00
multiline_comment|/*&n; * These addresses are used by the master CPU to install the transfer&n; * and private vectors.  All others use the SPB to find them.&n; */
DECL|macro|TVADDR
mdefine_line|#define TVADDR&t;(NODE_CAC_BASE(get_nasid()) + ARCS_TVECTOR_OFFSET)
DECL|macro|PVADDR
mdefine_line|#define PVADDR&t;(NODE_CAC_BASE(get_nasid()) + ARCS_PVECTOR_OFFSET)
macro_line|#endif /* _STANDALONE */
DECL|macro|KLDIR_OFFSET
mdefine_line|#define KLDIR_OFFSET&t;&t;0x2000
DECL|macro|KLDIR_ADDR
mdefine_line|#define KLDIR_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_UNCAC((nasid), KLDIR_OFFSET)
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
macro_line|#if _LANGUAGE_C
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
DECL|macro|LAUNCH_OFFSET
mdefine_line|#define LAUNCH_OFFSET(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;(KLD_LAUNCH(nasid)-&gt;offset +&t;&t;&t;&t;&t;&bslash;&n;&t; KLD_LAUNCH(nasid)-&gt;stride * (slice))
DECL|macro|LAUNCH_ADDR
mdefine_line|#define LAUNCH_ADDR(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_UNCAC((nasid), LAUNCH_OFFSET(nasid, slice))
DECL|macro|LAUNCH_SIZE
mdefine_line|#define LAUNCH_SIZE(nasid)&t;KLD_LAUNCH(nasid)-&gt;size
DECL|macro|NMI_OFFSET
mdefine_line|#define NMI_OFFSET(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;(KLD_NMI(nasid)-&gt;offset +&t;&t;&t;&t;&t;&bslash;&n;&t; KLD_NMI(nasid)-&gt;stride * (slice))
DECL|macro|NMI_ADDR
mdefine_line|#define NMI_ADDR(nasid, slice)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_UNCAC((nasid), NMI_OFFSET(nasid, slice))
DECL|macro|NMI_SIZE
mdefine_line|#define NMI_SIZE(nasid)&t;KLD_NMI(nasid)-&gt;size
DECL|macro|KLCONFIG_OFFSET
mdefine_line|#define KLCONFIG_OFFSET(nasid)&t;KLD_KLCONFIG(nasid)-&gt;offset
DECL|macro|KLCONFIG_ADDR
mdefine_line|#define KLCONFIG_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_UNCAC((nasid), KLCONFIG_OFFSET(nasid))
DECL|macro|KLCONFIG_SIZE
mdefine_line|#define KLCONFIG_SIZE(nasid)&t;KLD_KLCONFIG(nasid)-&gt;size
DECL|macro|GDA_ADDR
mdefine_line|#define GDA_ADDR(nasid)&t;&t;KLD_GDA(nasid)-&gt;pointer
DECL|macro|GDA_SIZE
mdefine_line|#define GDA_SIZE(nasid)&t;&t;KLD_GDA(nasid)-&gt;size
DECL|macro|SYMMON_STK_OFFSET
mdefine_line|#define SYMMON_STK_OFFSET(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;(KLD_SYMMON_STK(nasid)-&gt;offset +&t;&t;&t;&t;&bslash;&n;&t; KLD_SYMMON_STK(nasid)-&gt;stride * (slice))
DECL|macro|SYMMON_STK_STRIDE
mdefine_line|#define SYMMON_STK_STRIDE(nasid)&t;KLD_SYMMON_STK(nasid)-&gt;stride
DECL|macro|SYMMON_STK_ADDR
mdefine_line|#define SYMMON_STK_ADDR(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_CAC((nasid), SYMMON_STK_OFFSET(nasid, slice))
DECL|macro|SYMMON_STK_SIZE
mdefine_line|#define SYMMON_STK_SIZE(nasid)&t;KLD_SYMMON_STK(nasid)-&gt;stride
DECL|macro|SYMMON_STK_END
mdefine_line|#define SYMMON_STK_END(nasid)&t;(SYMMON_STK_ADDR(nasid, 0) + KLD_SYMMON_STK(nasid)-&gt;size)
multiline_comment|/* loading symmon 4k below UNIX. the arcs loader needs the topaddr for a&n; * relocatable program&n; */
DECL|macro|UNIX_DEBUG_LOADADDR
mdefine_line|#define&t;UNIX_DEBUG_LOADADDR&t;0x300000
DECL|macro|SYMMON_LOADADDR
mdefine_line|#define&t;SYMMON_LOADADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE(nasid, PHYS_TO_K0(UNIX_DEBUG_LOADADDR - 0x1000))
DECL|macro|FREEMEM_OFFSET
mdefine_line|#define FREEMEM_OFFSET(nasid)&t;KLD_FREEMEM(nasid)-&gt;offset
DECL|macro|FREEMEM_ADDR
mdefine_line|#define FREEMEM_ADDR(nasid)&t;SYMMON_STK_END(nasid)
multiline_comment|/*&n; * XXX&n; * Fix this. FREEMEM_ADDR should be aware of if symmon is loaded.&n; * Also, it should take into account what prom thinks to be a safe&n; * address&n;&t;PHYS_TO_K0(NODE_OFFSET(nasid) + FREEMEM_OFFSET(nasid))&n; */
DECL|macro|FREEMEM_SIZE
mdefine_line|#define FREEMEM_SIZE(nasid)&t;KLD_FREEMEM(nasid)-&gt;size
DECL|macro|PI_ERROR_OFFSET
mdefine_line|#define PI_ERROR_OFFSET(nasid)&t;KLD_PI_ERROR(nasid)-&gt;offset
DECL|macro|PI_ERROR_ADDR
mdefine_line|#define PI_ERROR_ADDR(nasid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TO_NODE_UNCAC((nasid), PI_ERROR_OFFSET(nasid))
DECL|macro|PI_ERROR_SIZE
mdefine_line|#define PI_ERROR_SIZE(nasid)&t;KLD_PI_ERROR(nasid)-&gt;size
DECL|macro|NODE_OFFSET_TO_K0
mdefine_line|#define NODE_OFFSET_TO_K0(_nasid, _off)&t;&t;&t;&t;&t;&bslash;&n;&t;PHYS_TO_K0((NODE_OFFSET(_nasid) + (_off)) | K0BASE)
DECL|macro|NODE_OFFSET_TO_K1
mdefine_line|#define NODE_OFFSET_TO_K1(_nasid, _off)&t;&t;&t;&t;&t;&bslash;&n;&t;TO_UNCAC((NODE_OFFSET(_nasid) + (_off)) | K1BASE)
DECL|macro|K0_TO_NODE_OFFSET
mdefine_line|#define K0_TO_NODE_OFFSET(_k0addr)&t;&t;&t;&t;&t;&bslash;&n;&t;((__psunsigned_t)(_k0addr) &amp; NODE_ADDRSPACE_MASK)
DECL|macro|KERN_VARS_ADDR
mdefine_line|#define KERN_VARS_ADDR(nasid)&t;KLD_KERN_VARS(nasid)-&gt;pointer
DECL|macro|KERN_VARS_SIZE
mdefine_line|#define KERN_VARS_SIZE(nasid)&t;KLD_KERN_VARS(nasid)-&gt;size
DECL|macro|KERN_XP_ADDR
mdefine_line|#define&t;KERN_XP_ADDR(nasid)&t;KLD_KERN_XP(nasid)-&gt;pointer
DECL|macro|KERN_XP_SIZE
mdefine_line|#define&t;KERN_XP_SIZE(nasid)&t;KLD_KERN_XP(nasid)-&gt;size
DECL|macro|GPDA_ADDR
mdefine_line|#define GPDA_ADDR(nasid)&t;TO_NODE_CAC(nasid, GPDA_OFFSET)
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* _ASM_SN_ADDRS_H */
eof
