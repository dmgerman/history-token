multiline_comment|/*&n; *  asm-ia64/acpi.h&n; *&n; *  Copyright (C) 1999 VA Linux Systems&n; *  Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *  Copyright (C) 2000,2001 J.I. Lee &lt;jung-ik.lee@intel.com&gt;&n; *  Copyright (C) 2001,2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef _ASM_ACPI_H
DECL|macro|_ASM_ACPI_H
mdefine_line|#define _ASM_ACPI_H
macro_line|#ifdef __KERNEL__
DECL|macro|__acpi_map_table
mdefine_line|#define __acpi_map_table(phys_addr, size) __va(phys_addr)
r_const
r_char
op_star
id|acpi_get_sysname
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_boot_init
(paren
r_char
op_star
id|cdline
)paren
suffix:semicolon
r_int
id|acpi_find_rsdp
(paren
r_int
r_int
op_star
id|phys_addr
)paren
suffix:semicolon
r_int
id|acpi_request_vector
(paren
id|u32
id|int_type
)paren
suffix:semicolon
r_int
id|acpi_get_prt
(paren
r_struct
id|pci_vector_struct
op_star
op_star
id|vectors
comma
r_int
op_star
id|count
)paren
suffix:semicolon
r_int
id|acpi_get_interrupt_model
c_func
(paren
r_int
op_star
id|type
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|NODE_ARRAY_INDEX
mdefine_line|#define NODE_ARRAY_INDEX(x)&t;((x) / 8)&t;/* 8 bits/char */
DECL|macro|NODE_ARRAY_OFFSET
mdefine_line|#define NODE_ARRAY_OFFSET(x)&t;((x) % 8)&t;/* 8 bits/char */
DECL|macro|MAX_PXM_DOMAINS
mdefine_line|#define MAX_PXM_DOMAINS&t;&t;(256)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*_ASM_ACPI_H*/
eof
