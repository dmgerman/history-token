multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Defines of the Malta board specific address-MAP, registers, etc.&n; */
macro_line|#ifndef __ASM_MIPS_MALTA_H
DECL|macro|__ASM_MIPS_MALTA_H
mdefine_line|#define __ASM_MIPS_MALTA_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/gt64120/gt64120.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Malta I/O ports base address for the Galileo GT64120 and Algorithmics&n; * Bonito system controllers.&n; */
DECL|macro|MALTA_GT_PORT_BASE
mdefine_line|#define MALTA_GT_PORT_BASE      get_gt_port_base(GT_PCI0IOLD_OFS)
DECL|macro|MALTA_BONITO_PORT_BASE
mdefine_line|#define MALTA_BONITO_PORT_BASE  (KSEG1ADDR(0x1fd00000))
DECL|macro|MALTA_MSC_PORT_BASE
mdefine_line|#define MALTA_MSC_PORT_BASE     get_msc_port_base(MSC01_PCI_SC2PIOBASL)
DECL|function|get_gt_port_base
r_static
r_inline
r_int
r_int
id|get_gt_port_base
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|GT_READ
c_func
(paren
id|reg
comma
id|addr
)paren
suffix:semicolon
r_return
id|KSEG1ADDR
c_func
(paren
(paren
id|addr
op_amp
l_int|0xffff
)paren
op_lshift
l_int|21
)paren
suffix:semicolon
)brace
DECL|function|get_msc_port_base
r_static
r_inline
r_int
r_int
id|get_msc_port_base
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|MSC_READ
c_func
(paren
id|reg
comma
id|addr
)paren
suffix:semicolon
r_return
id|KSEG1ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Malta RTC-device indirect register access.&n; */
DECL|macro|MALTA_RTC_ADR_REG
mdefine_line|#define MALTA_RTC_ADR_REG       0x70
DECL|macro|MALTA_RTC_DAT_REG
mdefine_line|#define MALTA_RTC_DAT_REG       0x71
multiline_comment|/*&n; * Malta SMSC FDC37M817 Super I/O Controller register.&n; */
DECL|macro|SMSC_CONFIG_REG
mdefine_line|#define SMSC_CONFIG_REG&t;&t;0x3f0
DECL|macro|SMSC_DATA_REG
mdefine_line|#define SMSC_DATA_REG&t;&t;0x3f1
DECL|macro|SMSC_CONFIG_DEVNUM
mdefine_line|#define SMSC_CONFIG_DEVNUM&t;0x7
DECL|macro|SMSC_CONFIG_ACTIVATE
mdefine_line|#define SMSC_CONFIG_ACTIVATE&t;0x30
DECL|macro|SMSC_CONFIG_ENTER
mdefine_line|#define SMSC_CONFIG_ENTER&t;0x55
DECL|macro|SMSC_CONFIG_EXIT
mdefine_line|#define SMSC_CONFIG_EXIT&t;0xaa
DECL|macro|SMSC_CONFIG_DEVNUM_FLOPPY
mdefine_line|#define SMSC_CONFIG_DEVNUM_FLOPPY     0
DECL|macro|SMSC_CONFIG_ACTIVATE_ENABLE
mdefine_line|#define SMSC_CONFIG_ACTIVATE_ENABLE   1
DECL|macro|SMSC_WRITE
mdefine_line|#define SMSC_WRITE(x,a)     outb(x,a)
DECL|macro|MALTA_JMPRS_REG
mdefine_line|#define MALTA_JMPRS_REG&t;&t;(KSEG1ADDR(0x1f000210))
macro_line|#endif /* __ASM_MIPS_MALTA_H */
eof
