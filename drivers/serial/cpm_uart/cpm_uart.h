multiline_comment|/*&n; *  linux/drivers/serial/cpm_uart.h&n; *&n; *  Driver for CPM (SCC/SMC) serial ports&n; *&n; *  Copyright (C) 2004 Freescale Semiconductor, Inc.&n; *&n; */
macro_line|#ifndef CPM_UART_H
DECL|macro|CPM_UART_H
mdefine_line|#define CPM_UART_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_CPM2)
macro_line|#include &quot;cpm_uart_cpm2.h&quot;
macro_line|#elif defined(CONFIG_8xx)
macro_line|#include &quot;cpm_uart_cpm1.h&quot;
macro_line|#endif
DECL|macro|SERIAL_CPM_MAJOR
mdefine_line|#define SERIAL_CPM_MAJOR&t;204
DECL|macro|SERIAL_CPM_MINOR
mdefine_line|#define SERIAL_CPM_MINOR&t;46
DECL|macro|IS_SMC
mdefine_line|#define IS_SMC(pinfo) &t;&t;(pinfo-&gt;flags &amp; FLAG_SMC)
DECL|macro|IS_DISCARDING
mdefine_line|#define IS_DISCARDING(pinfo)&t;(pinfo-&gt;flags &amp; FLAG_DISCARDING)
DECL|macro|FLAG_DISCARDING
mdefine_line|#define FLAG_DISCARDING&t;0x00000004&t;/* when set, don&squot;t discard */
DECL|macro|FLAG_SMC
mdefine_line|#define FLAG_SMC&t;0x00000002
DECL|macro|FLAG_CONSOLE
mdefine_line|#define FLAG_CONSOLE&t;0x00000001
DECL|macro|UART_SMC1
mdefine_line|#define UART_SMC1&t;0
DECL|macro|UART_SMC2
mdefine_line|#define UART_SMC2&t;1
DECL|macro|UART_SCC1
mdefine_line|#define UART_SCC1&t;2
DECL|macro|UART_SCC2
mdefine_line|#define UART_SCC2&t;3
DECL|macro|UART_SCC3
mdefine_line|#define UART_SCC3&t;4
DECL|macro|UART_SCC4
mdefine_line|#define UART_SCC4&t;5
DECL|macro|UART_NR
mdefine_line|#define UART_NR&t;6
DECL|macro|RX_NUM_FIFO
mdefine_line|#define RX_NUM_FIFO&t;4
DECL|macro|RX_BUF_SIZE
mdefine_line|#define RX_BUF_SIZE&t;32
DECL|macro|TX_NUM_FIFO
mdefine_line|#define TX_NUM_FIFO&t;4
DECL|macro|TX_BUF_SIZE
mdefine_line|#define TX_BUF_SIZE&t;32
DECL|struct|uart_cpm_port
r_struct
id|uart_cpm_port
(brace
DECL|member|port
r_struct
id|uart_port
id|port
suffix:semicolon
DECL|member|rx_nrfifos
id|u16
id|rx_nrfifos
suffix:semicolon
DECL|member|rx_fifosize
id|u16
id|rx_fifosize
suffix:semicolon
DECL|member|tx_nrfifos
id|u16
id|tx_nrfifos
suffix:semicolon
DECL|member|tx_fifosize
id|u16
id|tx_fifosize
suffix:semicolon
DECL|member|smcp
id|smc_t
op_star
id|smcp
suffix:semicolon
DECL|member|smcup
id|smc_uart_t
op_star
id|smcup
suffix:semicolon
DECL|member|sccp
id|scc_t
op_star
id|sccp
suffix:semicolon
DECL|member|sccup
id|scc_uart_t
op_star
id|sccup
suffix:semicolon
DECL|member|rx_bd_base
r_volatile
id|cbd_t
op_star
id|rx_bd_base
suffix:semicolon
DECL|member|rx_cur
r_volatile
id|cbd_t
op_star
id|rx_cur
suffix:semicolon
DECL|member|tx_bd_base
r_volatile
id|cbd_t
op_star
id|tx_bd_base
suffix:semicolon
DECL|member|tx_cur
r_volatile
id|cbd_t
op_star
id|tx_cur
suffix:semicolon
DECL|member|tx_buf
r_int
r_char
op_star
id|tx_buf
suffix:semicolon
DECL|member|rx_buf
r_int
r_char
op_star
id|rx_buf
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|set_lineif
r_void
(paren
op_star
id|set_lineif
)paren
(paren
r_struct
id|uart_cpm_port
op_star
)paren
suffix:semicolon
DECL|member|brg
id|u8
id|brg
suffix:semicolon
DECL|member|dp_addr
id|uint
id|dp_addr
suffix:semicolon
DECL|member|mem_addr
r_void
op_star
id|mem_addr
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
multiline_comment|/* helpers */
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|bits
r_int
id|bits
suffix:semicolon
multiline_comment|/* Keep track of &squot;odd&squot; SMC2 wirings */
DECL|member|is_portb
r_int
id|is_portb
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|cpm_uart_port_map
(braket
id|UART_NR
)braket
suffix:semicolon
r_extern
r_int
id|cpm_uart_nr
suffix:semicolon
r_extern
r_struct
id|uart_cpm_port
id|cpm_uart_ports
(braket
id|UART_NR
)braket
suffix:semicolon
multiline_comment|/* these are located in their respective files */
r_void
id|cpm_line_cr_cmd
c_func
(paren
r_int
id|line
comma
r_int
id|cmd
)paren
suffix:semicolon
r_int
id|cpm_uart_init_portdesc
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|cpm_uart_allocbuf
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
comma
r_int
r_int
id|is_con
)paren
suffix:semicolon
r_void
id|cpm_uart_freebuf
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
r_void
id|smc1_lineif
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
r_void
id|smc2_lineif
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
r_void
id|scc1_lineif
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
r_void
id|scc2_lineif
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
r_void
id|scc3_lineif
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
r_void
id|scc4_lineif
c_func
(paren
r_struct
id|uart_cpm_port
op_star
id|pinfo
)paren
suffix:semicolon
macro_line|#endif /* CPM_UART_H */
eof
