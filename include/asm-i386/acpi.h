multiline_comment|/*&n; *  asm-i386/acpi.h&n; *&n; *  Copyright (C) 2001 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef _ASM_ACPI_H
DECL|macro|_ASM_ACPI_H
mdefine_line|#define _ASM_ACPI_H
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_ACPI_BOOT
multiline_comment|/* Fixmap pages to reserve for ACPI boot-time tables (see fixmap.h) */
DECL|macro|FIX_ACPI_PAGES
mdefine_line|#define FIX_ACPI_PAGES&t;&t;4
r_extern
r_int
id|acpi_mp_config
suffix:semicolon
r_char
op_star
id|__acpi_map_table
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|acpi_find_rsdp
(paren
r_int
r_int
op_star
id|phys_addr
)paren
suffix:semicolon
r_extern
r_int
id|acpi_parse_madt
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|acpi_boot_init
(paren
r_char
op_star
id|cmdline
)paren
suffix:semicolon
macro_line|#else
DECL|macro|acpi_mp_config
mdefine_line|#define acpi_mp_config 0
macro_line|#endif /*CONFIG_ACPI_BOOT*/
macro_line|#ifdef CONFIG_ACPI_PCI
r_int
id|acpi_get_interrupt_model
(paren
r_int
op_star
id|type
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_PCI*/
macro_line|#ifdef CONFIG_ACPI_SLEEP
r_extern
r_int
r_int
id|saved_eip
suffix:semicolon
r_extern
r_int
r_int
id|saved_esp
suffix:semicolon
r_extern
r_int
r_int
id|saved_ebp
suffix:semicolon
r_extern
r_int
r_int
id|saved_ebx
suffix:semicolon
r_extern
r_int
r_int
id|saved_esi
suffix:semicolon
r_extern
r_int
r_int
id|saved_edi
suffix:semicolon
DECL|function|acpi_save_register_state
r_static
r_inline
r_void
id|acpi_save_register_state
c_func
(paren
r_int
r_int
id|return_point
)paren
(brace
id|saved_eip
op_assign
id|return_point
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%esp,(%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_esp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ebp,(%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_ebp
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ebx,(%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_ebx
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%edi,(%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_edi
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%esi,(%0)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|saved_esi
)paren
)paren
suffix:semicolon
)brace
DECL|macro|acpi_restore_register_state
mdefine_line|#define acpi_restore_register_state()&t;do {} while (0)
multiline_comment|/* routines for saving/restoring kernel state */
r_extern
r_int
id|acpi_save_state_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|acpi_save_state_disk
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|acpi_restore_state_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|acpi_wakeup_address
suffix:semicolon
multiline_comment|/* early initialization routine */
r_extern
r_void
id|acpi_reserve_bootmem
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_SLEEP*/
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*_ASM_ACPI_H*/
eof
