multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef _ASM_SIBYTE_SB1250_H
DECL|macro|_ASM_SIBYTE_SB1250_H
mdefine_line|#define _ASM_SIBYTE_SB1250_H
multiline_comment|/*&n; * yymmddpp: year, month, day, patch.&n; * should sync with Makefile EXTRAVERSION&n; */
DECL|macro|SIBYTE_RELEASE
mdefine_line|#define SIBYTE_RELEASE 0x02111403
DECL|macro|SB1250_NR_IRQS
mdefine_line|#define SB1250_NR_IRQS 64
DECL|macro|SB1250_DUART_MINOR_BASE
mdefine_line|#define SB1250_DUART_MINOR_BASE&t;&t;64
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/* For revision/pass information */
macro_line|#include &lt;asm/sibyte/sb1250_scd.h&gt;
r_extern
r_int
r_int
id|sb1_pass
suffix:semicolon
r_extern
r_int
r_int
id|soc_pass
suffix:semicolon
r_extern
r_int
r_int
id|soc_type
suffix:semicolon
r_extern
r_int
r_int
id|periph_rev
suffix:semicolon
r_extern
r_int
r_int
id|zbbus_mhz
suffix:semicolon
r_extern
r_void
id|sb1250_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sb1250_gettimeoffset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sb1250_mask_irq
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|sb1250_unmask_irq
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|sb1250_smp_finish
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|AT_spin
mdefine_line|#define AT_spin &bslash;&n;&t;__asm__ __volatile__ (&t;&t;&bslash;&n;&t;&t;&quot;.set noat&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;li $at, 0&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;1: beqz $at, 1b&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;.set at&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;)
macro_line|#endif
DECL|macro|IOADDR
mdefine_line|#define IOADDR(a) (IO_BASE + (a))
macro_line|#endif
eof
