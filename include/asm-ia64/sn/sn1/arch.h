multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_ARCH_H
DECL|macro|_ASM_IA64_SN_SN1_ARCH_H
mdefine_line|#define _ASM_IA64_SN_SN1_ARCH_H
macro_line|#if defined(N_MODE)
macro_line|#error &quot;ERROR constants defined only for M-mode&quot;
macro_line|#endif
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|CPUS_PER_NODE
mdefine_line|#define CPUS_PER_NODE           4       /* CPUs on a single hub */
DECL|macro|CPUS_PER_SUBNODE
mdefine_line|#define CPUS_PER_SUBNODE        2       /* CPUs on a single hub PI */
multiline_comment|/*&n; * This is the maximum number of NASIDS that can be present in a system.&n; * This include ALL nodes in ALL partitions connected via NUMALINK.&n; * (Highest NASID plus one.)&n; */
DECL|macro|MAX_NASIDS
mdefine_line|#define MAX_NASIDS              128
multiline_comment|/*&n; * This is the maximum number of nodes that can be part of a kernel.&n; * Effectively, it&squot;s the maximum number of compact node ids (cnodeid_t).&n; * This is not necessarily the same as MAX_NASIDS.&n; */
DECL|macro|MAX_COMPACT_NODES
mdefine_line|#define MAX_COMPACT_NODES       128
multiline_comment|/*&n; * MAX_REGIONS refers to the maximum number of hardware partitioned regions.&n; */
DECL|macro|MAX_REGIONS
mdefine_line|#define&t;MAX_REGIONS&t;&t;64
DECL|macro|MAX_NONPREMIUM_REGIONS
mdefine_line|#define MAX_NONPREMIUM_REGIONS  16
DECL|macro|MAX_PREMIUM_REGIONS
mdefine_line|#define MAX_PREMIUM_REGIONS     MAX_REGIONS
multiline_comment|/*&n; * Slot constants for IP35&n; */
DECL|macro|MAX_MEM_SLOTS
mdefine_line|#define MAX_MEM_SLOTS    8                     /* max slots per node */
macro_line|#if defined(N_MODE)
macro_line|#error &quot;N-mode not supported&quot;
macro_line|#endif
DECL|macro|SLOT_SHIFT
mdefine_line|#define SLOT_SHIFT              (30)
DECL|macro|SLOT_MIN_MEM_SIZE
mdefine_line|#define SLOT_MIN_MEM_SIZE       (64*1024*1024)
multiline_comment|/*&n; * MAX_PARITIONS refers to the maximum number of logically defined &n; * partitions the system can support.&n; */
DECL|macro|MAX_PARTITIONS
mdefine_line|#define MAX_PARTITIONS&t;&t;MAX_REGIONS
DECL|macro|NASID_MASK_BYTES
mdefine_line|#define NASID_MASK_BYTES&t;((MAX_NASIDS + 7) / 8)
multiline_comment|/*&n; * New stuff in here from Irix sys/pfdat.h.&n; */
DECL|macro|SLOT_PFNSHIFT
mdefine_line|#define SLOT_PFNSHIFT           (SLOT_SHIFT - PAGE_SHIFT)
DECL|macro|PFN_NASIDSHFT
mdefine_line|#define PFN_NASIDSHFT           (NASID_SHFT - PAGE_SHIFT)
DECL|macro|slot_getbasepfn
mdefine_line|#define slot_getbasepfn(node,slot)  (mkpfn(COMPACT_TO_NASID_NODEID(node), slot&lt;&lt;SLOT_PFNSHIFT))
DECL|macro|mkpfn
mdefine_line|#define mkpfn(nasid, off)       (((pfn_t)(nasid) &lt;&lt; PFN_NASIDSHFT) | (off))
multiline_comment|/*&n; * two PIs per bedrock, two CPUs per PI&n; */
DECL|macro|NUM_SUBNODES
mdefine_line|#define NUM_SUBNODES&t;2
DECL|macro|SUBNODE_SHFT
mdefine_line|#define SUBNODE_SHFT&t;1
DECL|macro|SUBNODE_MASK
mdefine_line|#define SUBNODE_MASK&t;(0x1 &lt;&lt; SUBNODE_SHFT)
DECL|macro|LOCALCPU_SHFT
mdefine_line|#define LOCALCPU_SHFT&t;0
DECL|macro|LOCALCPU_MASK
mdefine_line|#define LOCALCPU_MASK&t;(0x1 &lt;&lt; LOCALCPU_SHFT)
DECL|macro|SUBNODE
mdefine_line|#define SUBNODE(slice)&t;(((slice) &amp; SUBNODE_MASK) &gt;&gt; SUBNODE_SHFT)
DECL|macro|LOCALCPU
mdefine_line|#define LOCALCPU(slice)&t;(((slice) &amp; LOCALCPU_MASK) &gt;&gt; LOCALCPU_SHFT)
DECL|macro|TO_SLICE
mdefine_line|#define TO_SLICE(subn, local)&t;(((subn) &lt;&lt; SUBNODE_SHFT) | &bslash;&n;&t;&t;&t;&t; ((local) &lt;&lt; LOCALCPU_SHFT))
macro_line|#endif /* _ASM_IA64_SN_SN1_ARCH_H */
eof
