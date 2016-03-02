multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000,2003 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (c) 2002 NEC Corp.&n; * Copyright (c) 2002 Erich Focht &lt;efocht@ess.nec.de&gt;&n; * Copyright (c) 2002 Kimio Suganuma &lt;k-suganuma@da.jp.nec.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_MMZONE_H
DECL|macro|_ASM_IA64_MMZONE_H
mdefine_line|#define _ASM_IA64_MMZONE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/meminit.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#ifdef CONFIG_IA64_DIG /* DIG systems are small */
DECL|macro|MAX_PHYSNODE_ID
macro_line|# define MAX_PHYSNODE_ID&t;8
DECL|macro|NR_NODES
macro_line|# define NR_NODES&t;&t;8
DECL|macro|NR_NODE_MEMBLKS
macro_line|# define NR_NODE_MEMBLKS&t;(NR_NODES * 8)
macro_line|#else /* sn2 is the biggest case, so we use that if !DIG */
DECL|macro|MAX_PHYSNODE_ID
macro_line|# define MAX_PHYSNODE_ID&t;2048
DECL|macro|NR_NODES
macro_line|# define NR_NODES&t;&t;256
DECL|macro|NR_NODE_MEMBLKS
macro_line|# define NR_NODE_MEMBLKS&t;(NR_NODES * 4)
macro_line|#endif
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(((pfn) &lt; max_low_pfn) &amp;&amp; ia64_pfn_valid(pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long) (page - vmem_map))
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(vmem_map + (pfn))
macro_line|#else /* CONFIG_DISCONTIGMEM */
DECL|macro|NR_NODE_MEMBLKS
macro_line|# define NR_NODE_MEMBLKS&t;4
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_IA64_MMZONE_H */
eof
