macro_line|#ifndef ASMARM_ARCH_MMC_H
DECL|macro|ASMARM_ARCH_MMC_H
mdefine_line|#define ASMARM_ARCH_MMC_H
macro_line|#include &lt;linux/mmc/protocol.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
r_struct
id|device
suffix:semicolon
r_struct
id|mmc_host
suffix:semicolon
DECL|struct|pxamci_platform_data
r_struct
id|pxamci_platform_data
(brace
DECL|member|ocr_mask
r_int
r_int
id|ocr_mask
suffix:semicolon
multiline_comment|/* available voltages */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|device
op_star
comma
id|irqreturn_t
(paren
op_star
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|setpower
r_void
(paren
op_star
id|setpower
)paren
(paren
r_struct
id|device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|exit
r_void
(paren
op_star
m_exit
)paren
(paren
r_struct
id|device
op_star
comma
r_void
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|pxa_set_mci_info
c_func
(paren
r_struct
id|pxamci_platform_data
op_star
id|info
)paren
suffix:semicolon
macro_line|#endif
eof
