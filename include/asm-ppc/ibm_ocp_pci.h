multiline_comment|/*&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM_OCP_PCI_H__
DECL|macro|__ASM_IBM_OCP_PCI_H__
mdefine_line|#define __ASM_IBM_OCP_PCI_H__
multiline_comment|/* PCI 32 */
DECL|struct|pmm_regs
r_struct
id|pmm_regs
(brace
DECL|member|la
id|u32
id|la
suffix:semicolon
DECL|member|ma
id|u32
id|ma
suffix:semicolon
DECL|member|pcila
id|u32
id|pcila
suffix:semicolon
DECL|member|pciha
id|u32
id|pciha
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcil0_regs
r_typedef
r_struct
id|pcil0_regs
(brace
DECL|member|pmm
r_struct
id|pmm_regs
id|pmm
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ptm1ms
id|u32
id|ptm1ms
suffix:semicolon
DECL|member|ptm1la
id|u32
id|ptm1la
suffix:semicolon
DECL|member|ptm2ms
id|u32
id|ptm2ms
suffix:semicolon
DECL|member|ptm2la
id|u32
id|ptm2la
suffix:semicolon
DECL|typedef|pci0_t
)brace
id|pci0_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBM_OCP_PCI_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
