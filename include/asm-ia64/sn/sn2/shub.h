multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN2_SHUB_H
DECL|macro|_ASM_IA64_SN_SN2_SHUB_H
mdefine_line|#define _ASM_IA64_SN_SN2_SHUB_H
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;&t;&t;/* shub mmr addresses and formats */
macro_line|#include &lt;asm/sn/sn2/shub_md.h&gt;&t;
macro_line|#include &lt;asm/sn/sn2/shubio.h&gt;&t;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/sn/sn2/shub_mmr_t.h&gt;&t;&t;/* shub mmr struct defines */
macro_line|#endif
multiline_comment|/*&n; * Junk Bus Address Space&n; *   The junk bus is used to access the PROM, LED&squot;s, and UART. It&squot;s &n; *   accessed through the local block MMR space. The data path is&n; *   16 bits wide. This space requires address bits 31-27 to be set, and&n; *   is further divided by address bits 26:15.&n; *   The LED addresses are write-only. To read the LEDs, you need to use&n; *   SH_JUNK_BUS_LED0-3, defined in shub_mmr.h&n; *&t;&t;&n; */
DECL|macro|SH_REAL_JUNK_BUS_LED0
mdefine_line|#define SH_REAL_JUNK_BUS_LED0           0x7fed00000
DECL|macro|SH_REAL_JUNK_BUS_LED1
mdefine_line|#define SH_REAL_JUNK_BUS_LED1           0x7fed10000
DECL|macro|SH_REAL_JUNK_BUS_LED2
mdefine_line|#define SH_REAL_JUNK_BUS_LED2           0x7fed20000
DECL|macro|SH_REAL_JUNK_BUS_LED3
mdefine_line|#define SH_REAL_JUNK_BUS_LED3           0x7fed30000
DECL|macro|SH_JUNK_BUS_UART0
mdefine_line|#define SH_JUNK_BUS_UART0               0x7fed40000
DECL|macro|SH_JUNK_BUS_UART1
mdefine_line|#define SH_JUNK_BUS_UART1               0x7fed40008
DECL|macro|SH_JUNK_BUS_UART2
mdefine_line|#define SH_JUNK_BUS_UART2               0x7fed40010
DECL|macro|SH_JUNK_BUS_UART3
mdefine_line|#define SH_JUNK_BUS_UART3               0x7fed40018
DECL|macro|SH_JUNK_BUS_UART4
mdefine_line|#define SH_JUNK_BUS_UART4               0x7fed40020
DECL|macro|SH_JUNK_BUS_UART5
mdefine_line|#define SH_JUNK_BUS_UART5               0x7fed40028
DECL|macro|SH_JUNK_BUS_UART6
mdefine_line|#define SH_JUNK_BUS_UART6               0x7fed40030
DECL|macro|SH_JUNK_BUS_UART7
mdefine_line|#define SH_JUNK_BUS_UART7               0x7fed40038
macro_line|#endif /* _ASM_IA64_SN_SN2_SHUB_H */
eof
