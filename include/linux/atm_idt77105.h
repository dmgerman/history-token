multiline_comment|/* atm_idt77105.h - Driver-specific declarations of the IDT77105 driver (for&n; * use by driver-specific utilities) */
multiline_comment|/* Written 1999 by Greg Banks &lt;gnb@linuxfan.com&gt;. Copied from atm_suni.h. */
macro_line|#ifndef LINUX_ATM_IDT77105_H
DECL|macro|LINUX_ATM_IDT77105_H
mdefine_line|#define LINUX_ATM_IDT77105_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
multiline_comment|/*&n; * Structure for IDT77105_GETSTAT and IDT77105_GETSTATZ ioctls.&n; * Pointed to by `arg&squot; in atmif_sioc.&n; */
DECL|struct|idt77105_stats
r_struct
id|idt77105_stats
(brace
DECL|member|symbol_errors
id|__u32
id|symbol_errors
suffix:semicolon
multiline_comment|/* wire symbol errors */
DECL|member|tx_cells
id|__u32
id|tx_cells
suffix:semicolon
multiline_comment|/* cells transmitted */
DECL|member|rx_cells
id|__u32
id|rx_cells
suffix:semicolon
multiline_comment|/* cells received */
DECL|member|rx_hec_errors
id|__u32
id|rx_hec_errors
suffix:semicolon
multiline_comment|/* Header Error Check errors on receive */
)brace
suffix:semicolon
DECL|macro|IDT77105_GETSTAT
mdefine_line|#define IDT77105_GETSTAT&t;_IOW(&squot;a&squot;,ATMIOC_PHYPRV+2,struct atmif_sioc)&t;/* get stats */
DECL|macro|IDT77105_GETSTATZ
mdefine_line|#define IDT77105_GETSTATZ&t;_IOW(&squot;a&squot;,ATMIOC_PHYPRV+3,struct atmif_sioc)&t;/* get stats and zero */
macro_line|#endif
eof
