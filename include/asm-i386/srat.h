multiline_comment|/*&n; * Some of the code in this file has been gleaned from the 64 bit &n; * discontigmem support code base.&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to Pat Gaughen &lt;gone@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_SRAT_H_
DECL|macro|_ASM_SRAT_H_
mdefine_line|#define _ASM_SRAT_H_
multiline_comment|/*&n; * each element in pfnnode_map represents 256 MB (2^28) of pages.&n; * so, to represent 64GB we need 256 elements.&n; */
DECL|macro|MAX_ELEMENTS
mdefine_line|#define MAX_ELEMENTS 256
DECL|macro|PFN_TO_ELEMENT
mdefine_line|#define PFN_TO_ELEMENT(pfn) ((pfn)&gt;&gt;(28 - PAGE_SHIFT))
r_extern
r_int
id|pfnnode_map
(braket
)braket
suffix:semicolon
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn) ({ pfnnode_map[PFN_TO_ELEMENT(pfn)]; })
DECL|macro|pfn_to_pgdat
mdefine_line|#define pfn_to_pgdat(pfn) NODE_DATA(pfn_to_nid(pfn))
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(pa) pfn_to_nid(pa &gt;&gt; PAGE_SHIFT)
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES&t;&t;8
r_extern
r_void
id|get_memcfg_from_srat
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|get_zholes_size
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|get_memcfg_numa
mdefine_line|#define get_memcfg_numa() get_memcfg_from_srat()
macro_line|#endif /* _ASM_SRAT_H_ */
eof
