multiline_comment|/*&n; * Copyright (c) 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN1
DECL|macro|MACHVEC_PLATFORM_NAME
mdefine_line|#define MACHVEC_PLATFORM_NAME&t;&t;sn1
DECL|macro|MACHVEC_PLATFORM_HEADER
mdefine_line|#define MACHVEC_PLATFORM_HEADER&t;&t;&lt;asm/machvec_sn1.h&gt;
macro_line|#else CONFIG_IA64_SGI_SN1
DECL|macro|MACHVEC_PLATFORM_NAME
mdefine_line|#define MACHVEC_PLATFORM_NAME&t;&t;sn2
DECL|macro|MACHVEC_PLATFORM_HEADER
mdefine_line|#define MACHVEC_PLATFORM_HEADER&t;&t;&lt;asm/machvec_sn2.h&gt;
macro_line|#else
macro_line|#error &quot;unknown platform&quot;
macro_line|#endif
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
r_void
op_star
id|sn_mk_io_addr_MACRO
id|dma_addr_t
id|sn_pci_map_single_MACRO
r_int
id|sn_pci_map_sg_MACRO
r_int
r_int
id|sn_virt_to_phys_MACRO
r_void
op_star
id|sn_phys_to_virt_MACRO
eof
