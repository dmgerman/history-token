multiline_comment|/* atm_eni.h - Driver-specific declarations of the ENI driver (for use by&n;&t;       driver-specific utilities) */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_ATM_ENI_H
DECL|macro|LINUX_ATM_ENI_H
mdefine_line|#define LINUX_ATM_ENI_H
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|struct|eni_multipliers
r_struct
id|eni_multipliers
(brace
DECL|member|tx
DECL|member|rx
r_int
id|tx
comma
id|rx
suffix:semicolon
multiline_comment|/* values are in percent and must be &gt; 100 */
)brace
suffix:semicolon
DECL|macro|ENI_MEMDUMP
mdefine_line|#define ENI_MEMDUMP     _IOW(&squot;a&squot;,ATMIOC_SARPRV,struct atmif_sioc)
multiline_comment|/* printk memory map */
DECL|macro|ENI_SETMULT
mdefine_line|#define ENI_SETMULT&t;_IOW(&squot;a&squot;,ATMIOC_SARPRV+7,struct atmif_sioc)
multiline_comment|/* set buffer multipliers */
macro_line|#endif
eof
