multiline_comment|/*&n; * linux/drivers/serial/cpm_uart_cpm1.h&n; *&n; * Driver for CPM (SCC/SMC) serial ports&n; * &n; * definitions for cpm1&n; *&n; */
macro_line|#ifndef CPM_UART_CPM1_H
DECL|macro|CPM_UART_CPM1_H
mdefine_line|#define CPM_UART_CPM1_H
macro_line|#include &lt;asm/commproc.h&gt;
multiline_comment|/* defines for IRQs */
DECL|macro|SMC1_IRQ
mdefine_line|#define SMC1_IRQ&t;(CPM_IRQ_OFFSET + CPMVEC_SMC1)
DECL|macro|SMC2_IRQ
mdefine_line|#define SMC2_IRQ&t;(CPM_IRQ_OFFSET + CPMVEC_SMC2)
DECL|macro|SCC1_IRQ
mdefine_line|#define SCC1_IRQ&t;(CPM_IRQ_OFFSET + CPMVEC_SCC1)
DECL|macro|SCC2_IRQ
mdefine_line|#define SCC2_IRQ&t;(CPM_IRQ_OFFSET + CPMVEC_SCC2)
DECL|macro|SCC3_IRQ
mdefine_line|#define SCC3_IRQ&t;(CPM_IRQ_OFFSET + CPMVEC_SCC3)
DECL|macro|SCC4_IRQ
mdefine_line|#define SCC4_IRQ&t;(CPM_IRQ_OFFSET + CPMVEC_SCC4)
multiline_comment|/* the CPM address */
DECL|macro|CPM_ADDR
mdefine_line|#define CPM_ADDR&t;IMAP_ADDR
DECL|function|cpm_set_brg
r_static
r_inline
r_void
id|cpm_set_brg
c_func
(paren
r_int
id|brg
comma
r_int
id|baud
)paren
(brace
id|m8xx_cpm_setbrg
c_func
(paren
id|brg
comma
id|baud
)paren
suffix:semicolon
)brace
DECL|function|cpm_set_scc_fcr
r_static
r_inline
r_void
id|cpm_set_scc_fcr
c_func
(paren
r_volatile
id|scc_uart_t
op_star
id|sup
)paren
(brace
id|sup-&gt;scc_genscc.scc_rfcr
op_assign
id|SMC_EB
suffix:semicolon
id|sup-&gt;scc_genscc.scc_tfcr
op_assign
id|SMC_EB
suffix:semicolon
)brace
DECL|function|cpm_set_smc_fcr
r_static
r_inline
r_void
id|cpm_set_smc_fcr
c_func
(paren
r_volatile
id|smc_uart_t
op_star
id|up
)paren
(brace
id|up-&gt;smc_rfcr
op_assign
id|SMC_EB
suffix:semicolon
id|up-&gt;smc_tfcr
op_assign
id|SMC_EB
suffix:semicolon
)brace
DECL|macro|DPRAM_BASE
mdefine_line|#define DPRAM_BASE&t;((unsigned char *)&amp;cpmp-&gt;cp_dpmem[0])
macro_line|#endif
eof
