multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI IP27 specific setup.&n; *&n; * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SN_SN0_ARCH_H
DECL|macro|_ASM_SN_SN0_ARCH_H
mdefine_line|#define _ASM_SN_SN0_ARCH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef SABLE
macro_line|#ifndef SN0XXL  /* 128 cpu SMP max */
multiline_comment|/*&n; * This is the maximum number of nodes that can be part of a kernel.&n; * Effectively, it&squot;s the maximum number of compact node ids (cnodeid_t).&n; */
DECL|macro|MAX_COMPACT_NODES
mdefine_line|#define MAX_COMPACT_NODES       64
multiline_comment|/*&n; * MAXCPUS refers to the maximum number of CPUs in a single kernel.&n; * This is not necessarily the same as MAXNODES * CPUS_PER_NODE&n; */
DECL|macro|MAXCPUS
mdefine_line|#define MAXCPUS                 128
macro_line|#else /* SN0XXL system */
DECL|macro|MAX_COMPACT_NODES
mdefine_line|#define MAX_COMPACT_NODES       128
DECL|macro|MAXCPUS
mdefine_line|#define MAXCPUS                 256
macro_line|#endif /* SN0XXL */
multiline_comment|/*&n; * This is the maximum number of NASIDS that can be present in a system.&n; * (Highest NASID plus one.)&n; */
DECL|macro|MAX_NASIDS
mdefine_line|#define MAX_NASIDS&t;&t;256
multiline_comment|/*&n; * MAX_REGIONS refers to the maximum number of hardware partitioned regions.&n; */
DECL|macro|MAX_REGIONS
mdefine_line|#define&t;MAX_REGIONS&t;&t;64
DECL|macro|MAX_NONPREMIUM_REGIONS
mdefine_line|#define MAX_NONPREMIUM_REGIONS  16
DECL|macro|MAX_PREMIUM_REGIONS
mdefine_line|#define MAX_PREMIUM_REGIONS     MAX_REGIONS
multiline_comment|/*&n; * MAX_PARITIONS refers to the maximum number of logically defined &n; * partitions the system can support.&n; */
DECL|macro|MAX_PARTITIONS
mdefine_line|#define MAX_PARTITIONS&t;&t;MAX_REGIONS
macro_line|#else
DECL|macro|MAX_COMPACT_NODES
mdefine_line|#define MAX_COMPACT_NODES&t;4
DECL|macro|MAX_NASIDS
mdefine_line|#define MAX_NASIDS&t;&t;4
DECL|macro|MAXCPUS
mdefine_line|#define MAXCPUS&t;&t;&t;8
macro_line|#endif
DECL|macro|NASID_MASK_BYTES
mdefine_line|#define NASID_MASK_BYTES&t;((MAX_NASIDS + 7) / 8)
multiline_comment|/*&n; * Slot constants for SN0&n; */
macro_line|#ifdef CONFIG_SGI_SN0_N_MODE
DECL|macro|MAX_MEM_SLOTS
mdefine_line|#define MAX_MEM_SLOTS   16                      /* max slots per node */
macro_line|#else /* !CONFIG_SGI_SN0_N_MODE, assume M_MODE */
DECL|macro|MAX_MEM_SLOTS
mdefine_line|#define MAX_MEM_SLOTS   32                      /* max slots per node */
macro_line|#endif /* defined(N_MODE) */
macro_line|#if SABLE_RTL
DECL|macro|SLOT_SHIFT
mdefine_line|#define SLOT_SHIFT      &t;(28)
DECL|macro|SLOT_MIN_MEM_SIZE
mdefine_line|#define SLOT_MIN_MEM_SIZE&t;(16*1024*1024)
macro_line|#else
DECL|macro|SLOT_SHIFT
mdefine_line|#define SLOT_SHIFT      &t;(27)
DECL|macro|SLOT_MIN_MEM_SIZE
mdefine_line|#define SLOT_MIN_MEM_SIZE&t;(32*1024*1024)
macro_line|#endif
macro_line|#endif /* _ASM_SN_SN0_ARCH_H */
eof
