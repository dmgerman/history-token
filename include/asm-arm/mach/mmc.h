multiline_comment|/*&n; *  linux/include/asm-arm/mach/mmc.h&n; */
macro_line|#ifndef ASMARM_MACH_MMC_H
DECL|macro|ASMARM_MACH_MMC_H
mdefine_line|#define ASMARM_MACH_MMC_H
macro_line|#include &lt;linux/mmc/protocol.h&gt;
DECL|struct|mmc_platform_data
r_struct
id|mmc_platform_data
(brace
DECL|member|ocr_mask
r_int
r_int
id|ocr_mask
suffix:semicolon
multiline_comment|/* available voltages */
DECL|member|translate_vdd
id|u32
(paren
op_star
id|translate_vdd
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
DECL|member|status
r_int
r_int
(paren
op_star
id|status
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
