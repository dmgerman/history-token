multiline_comment|/* $Id: sbi.h,v 1.2 1998/03/09 14:04:48 jj Exp $&n; * sbi.h:  SBI (Sbus Interface on sun4d) definitions&n; *&n; * Copyright (C) 1997 Jakub Jelinek &lt;jj@sunsite.mff.cuni.cz&gt;&n; */
macro_line|#ifndef _SPARC_SBI_H
DECL|macro|_SPARC_SBI_H
mdefine_line|#define _SPARC_SBI_H
macro_line|#include &lt;asm/obio.h&gt;
multiline_comment|/* SBI */
DECL|struct|sbi_regs
r_struct
id|sbi_regs
(brace
DECL|member|cid
multiline_comment|/* 0x0000 */
id|u32
id|cid
suffix:semicolon
multiline_comment|/* Component ID */
DECL|member|ctl
multiline_comment|/* 0x0004 */
id|u32
id|ctl
suffix:semicolon
multiline_comment|/* Control */
DECL|member|status
multiline_comment|/* 0x0008 */
id|u32
id|status
suffix:semicolon
multiline_comment|/* Status */
DECL|member|_unused1
id|u32
id|_unused1
suffix:semicolon
DECL|member|cfg0
multiline_comment|/* 0x0010 */
id|u32
id|cfg0
suffix:semicolon
multiline_comment|/* Slot0 config reg */
DECL|member|cfg1
multiline_comment|/* 0x0014 */
id|u32
id|cfg1
suffix:semicolon
multiline_comment|/* Slot1 config reg */
DECL|member|cfg2
multiline_comment|/* 0x0018 */
id|u32
id|cfg2
suffix:semicolon
multiline_comment|/* Slot2 config reg */
DECL|member|cfg3
multiline_comment|/* 0x001c */
id|u32
id|cfg3
suffix:semicolon
multiline_comment|/* Slot3 config reg */
DECL|member|stb0
multiline_comment|/* 0x0020 */
id|u32
id|stb0
suffix:semicolon
multiline_comment|/* Streaming buf control for slot 0 */
DECL|member|stb1
multiline_comment|/* 0x0024 */
id|u32
id|stb1
suffix:semicolon
multiline_comment|/* Streaming buf control for slot 1 */
DECL|member|stb2
multiline_comment|/* 0x0028 */
id|u32
id|stb2
suffix:semicolon
multiline_comment|/* Streaming buf control for slot 2 */
DECL|member|stb3
multiline_comment|/* 0x002c */
id|u32
id|stb3
suffix:semicolon
multiline_comment|/* Streaming buf control for slot 3 */
DECL|member|intr_state
multiline_comment|/* 0x0030 */
id|u32
id|intr_state
suffix:semicolon
multiline_comment|/* Interrupt state */
DECL|member|intr_tid
multiline_comment|/* 0x0034 */
id|u32
id|intr_tid
suffix:semicolon
multiline_comment|/* Interrupt target ID */
DECL|member|intr_diag
multiline_comment|/* 0x0038 */
id|u32
id|intr_diag
suffix:semicolon
multiline_comment|/* Interrupt diagnostics */
)brace
suffix:semicolon
DECL|macro|SBI_CID
mdefine_line|#define SBI_CID&t;&t;&t;0x02800000
DECL|macro|SBI_CTL
mdefine_line|#define SBI_CTL&t;&t;&t;0x02800004
DECL|macro|SBI_STATUS
mdefine_line|#define SBI_STATUS&t;&t;0x02800008
DECL|macro|SBI_CFG0
mdefine_line|#define SBI_CFG0&t;&t;0x02800010
DECL|macro|SBI_CFG1
mdefine_line|#define SBI_CFG1&t;&t;0x02800014
DECL|macro|SBI_CFG2
mdefine_line|#define SBI_CFG2&t;&t;0x02800018
DECL|macro|SBI_CFG3
mdefine_line|#define SBI_CFG3&t;&t;0x0280001c
DECL|macro|SBI_STB0
mdefine_line|#define SBI_STB0&t;&t;0x02800020
DECL|macro|SBI_STB1
mdefine_line|#define SBI_STB1&t;&t;0x02800024
DECL|macro|SBI_STB2
mdefine_line|#define SBI_STB2&t;&t;0x02800028
DECL|macro|SBI_STB3
mdefine_line|#define SBI_STB3&t;&t;0x0280002c
DECL|macro|SBI_INTR_STATE
mdefine_line|#define SBI_INTR_STATE&t;&t;0x02800030
DECL|macro|SBI_INTR_TID
mdefine_line|#define SBI_INTR_TID&t;&t;0x02800034
DECL|macro|SBI_INTR_DIAG
mdefine_line|#define SBI_INTR_DIAG&t;&t;0x02800038
multiline_comment|/* Burst bits for 8, 16, 32, 64 are in cfgX registers at bits 2, 3, 4, 5 respectively */
DECL|macro|SBI_CFG_BURST_MASK
mdefine_line|#define SBI_CFG_BURST_MASK&t;0x0000001e
multiline_comment|/* How to make devid from sbi no */
DECL|macro|SBI2DEVID
mdefine_line|#define SBI2DEVID(sbino) ((sbino&lt;&lt;4)|2)
multiline_comment|/* intr_state has 4 bits for slots 0 .. 3 and these bits are repeated for each sbus irq level&n; *&n; *&t;&t;   +-------+-------+-------+-------+-------+-------+-------+-------+&n; *  SBUS IRQ LEVEL |   7   |   6   |   5   |   4   |   3   |   2   |   1   |       |&n; *&t;&t;   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ Reser |&n; *  SLOT #         |3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|  ved  |&n; *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-------+&n; *  Bits           31      27      23      19      15      11      7       3      0&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|function|acquire_sbi
r_extern
id|__inline__
r_int
id|acquire_sbi
c_func
(paren
r_int
id|devid
comma
r_int
id|mask
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;swapa [%2] %3, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ECSR_DEV_BASE
c_func
(paren
id|devid
)paren
op_or
id|SBI_INTR_STATE
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|release_sbi
r_extern
id|__inline__
r_void
id|release_sbi
c_func
(paren
r_int
id|devid
comma
r_int
id|mask
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sta %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ECSR_DEV_BASE
c_func
(paren
id|devid
)paren
op_or
id|SBI_INTR_STATE
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_sbi_tid
r_extern
id|__inline__
r_void
id|set_sbi_tid
c_func
(paren
r_int
id|devid
comma
r_int
id|targetid
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sta %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|targetid
)paren
comma
l_string|&quot;r&quot;
(paren
id|ECSR_DEV_BASE
c_func
(paren
id|devid
)paren
op_or
id|SBI_INTR_TID
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_sbi_ctl
r_extern
id|__inline__
r_int
id|get_sbi_ctl
c_func
(paren
r_int
id|devid
comma
r_int
id|cfgno
)paren
(brace
r_int
id|cfg
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lda [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cfg
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|ECSR_DEV_BASE
c_func
(paren
id|devid
)paren
op_or
id|SBI_CFG0
)paren
op_plus
(paren
id|cfgno
op_lshift
l_int|2
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
r_return
id|cfg
suffix:semicolon
)brace
DECL|function|set_sbi_ctl
r_extern
id|__inline__
r_void
id|set_sbi_ctl
c_func
(paren
r_int
id|devid
comma
r_int
id|cfgno
comma
r_int
id|cfg
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sta %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|cfg
)paren
comma
l_string|&quot;r&quot;
(paren
(paren
id|ECSR_DEV_BASE
c_func
(paren
id|devid
)paren
op_or
id|SBI_CFG0
)paren
op_plus
(paren
id|cfgno
op_lshift
l_int|2
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* !(_SPARC_SBI_H) */
eof
