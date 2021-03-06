multiline_comment|/*&n; * Compaq Hot Plug Controller Driver&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#ifndef _CPQPHP_NVRAM_H
DECL|macro|_CPQPHP_NVRAM_H
mdefine_line|#define _CPQPHP_NVRAM_H
macro_line|#ifndef CONFIG_HOTPLUG_PCI_COMPAQ_NVRAM
DECL|function|compaq_nvram_init
r_static
r_inline
r_void
id|compaq_nvram_init
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|compaq_nvram_load
r_static
r_inline
r_int
id|compaq_nvram_load
(paren
r_void
id|__iomem
op_star
id|rom_start
comma
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compaq_nvram_store
r_static
r_inline
r_int
id|compaq_nvram_store
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
r_extern
r_void
id|compaq_nvram_init
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
suffix:semicolon
r_extern
r_int
id|compaq_nvram_load
(paren
r_void
id|__iomem
op_star
id|rom_start
comma
r_struct
id|controller
op_star
id|ctrl
)paren
suffix:semicolon
r_extern
r_int
id|compaq_nvram_store
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
