multiline_comment|/*&n; * include/asm-ppc/mpc52xx_psc.h&n; * &n; * Definitions of consts/structs to drive the Freescale MPC52xx OnChip&n; * PSCs. Theses are shared between multiple drivers since a PSC can be&n; * UART, AC97, IR, I2S, ... So this header is in asm-ppc.&n; *&n; *&n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Based/Extracted from some header of the 2.4 originally written by &n; * Dale Farnsworth &lt;dfarnsworth@mvista.com&gt; &n; *&n; * Copyright (C) 2004 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; * Copyright (C) 2003 MontaVista, Software, Inc.&n; *&n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#ifndef __ASM_MPC52xx_PSC_H__
DECL|macro|__ASM_MPC52xx_PSC_H__
mdefine_line|#define __ASM_MPC52xx_PSC_H__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Max number of PSCs */
DECL|macro|MPC52xx_PSC_MAXNUM
mdefine_line|#define MPC52xx_PSC_MAXNUM&t;6
multiline_comment|/* Programmable Serial Controller (PSC) status register bits */
DECL|macro|MPC52xx_PSC_SR_CDE
mdefine_line|#define MPC52xx_PSC_SR_CDE&t;0x0080
DECL|macro|MPC52xx_PSC_SR_RXRDY
mdefine_line|#define MPC52xx_PSC_SR_RXRDY&t;0x0100
DECL|macro|MPC52xx_PSC_SR_RXFULL
mdefine_line|#define MPC52xx_PSC_SR_RXFULL&t;0x0200
DECL|macro|MPC52xx_PSC_SR_TXRDY
mdefine_line|#define MPC52xx_PSC_SR_TXRDY&t;0x0400
DECL|macro|MPC52xx_PSC_SR_TXEMP
mdefine_line|#define MPC52xx_PSC_SR_TXEMP&t;0x0800
DECL|macro|MPC52xx_PSC_SR_OE
mdefine_line|#define MPC52xx_PSC_SR_OE&t;0x1000
DECL|macro|MPC52xx_PSC_SR_PE
mdefine_line|#define MPC52xx_PSC_SR_PE&t;0x2000
DECL|macro|MPC52xx_PSC_SR_FE
mdefine_line|#define MPC52xx_PSC_SR_FE&t;0x4000
DECL|macro|MPC52xx_PSC_SR_RB
mdefine_line|#define MPC52xx_PSC_SR_RB&t;0x8000
multiline_comment|/* PSC Command values */
DECL|macro|MPC52xx_PSC_RX_ENABLE
mdefine_line|#define MPC52xx_PSC_RX_ENABLE&t;&t;0x0001
DECL|macro|MPC52xx_PSC_RX_DISABLE
mdefine_line|#define MPC52xx_PSC_RX_DISABLE&t;&t;0x0002
DECL|macro|MPC52xx_PSC_TX_ENABLE
mdefine_line|#define MPC52xx_PSC_TX_ENABLE&t;&t;0x0004
DECL|macro|MPC52xx_PSC_TX_DISABLE
mdefine_line|#define MPC52xx_PSC_TX_DISABLE&t;&t;0x0008
DECL|macro|MPC52xx_PSC_SEL_MODE_REG_1
mdefine_line|#define MPC52xx_PSC_SEL_MODE_REG_1&t;0x0010
DECL|macro|MPC52xx_PSC_RST_RX
mdefine_line|#define MPC52xx_PSC_RST_RX&t;&t;0x0020
DECL|macro|MPC52xx_PSC_RST_TX
mdefine_line|#define MPC52xx_PSC_RST_TX&t;&t;0x0030
DECL|macro|MPC52xx_PSC_RST_ERR_STAT
mdefine_line|#define MPC52xx_PSC_RST_ERR_STAT&t;0x0040
DECL|macro|MPC52xx_PSC_RST_BRK_CHG_INT
mdefine_line|#define MPC52xx_PSC_RST_BRK_CHG_INT&t;0x0050
DECL|macro|MPC52xx_PSC_START_BRK
mdefine_line|#define MPC52xx_PSC_START_BRK&t;&t;0x0060
DECL|macro|MPC52xx_PSC_STOP_BRK
mdefine_line|#define MPC52xx_PSC_STOP_BRK&t;&t;0x0070
multiline_comment|/* PSC TxRx FIFO status bits */
DECL|macro|MPC52xx_PSC_RXTX_FIFO_ERR
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_ERR&t;0x0040
DECL|macro|MPC52xx_PSC_RXTX_FIFO_UF
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_UF&t;0x0020
DECL|macro|MPC52xx_PSC_RXTX_FIFO_OF
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_OF&t;0x0010
DECL|macro|MPC52xx_PSC_RXTX_FIFO_FR
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_FR&t;0x0008
DECL|macro|MPC52xx_PSC_RXTX_FIFO_FULL
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_FULL&t;0x0004
DECL|macro|MPC52xx_PSC_RXTX_FIFO_ALARM
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_ALARM&t;0x0002
DECL|macro|MPC52xx_PSC_RXTX_FIFO_EMPTY
mdefine_line|#define MPC52xx_PSC_RXTX_FIFO_EMPTY&t;0x0001
multiline_comment|/* PSC interrupt mask bits */
DECL|macro|MPC52xx_PSC_IMR_TXRDY
mdefine_line|#define MPC52xx_PSC_IMR_TXRDY&t;&t;0x0100
DECL|macro|MPC52xx_PSC_IMR_RXRDY
mdefine_line|#define MPC52xx_PSC_IMR_RXRDY&t;&t;0x0200
DECL|macro|MPC52xx_PSC_IMR_DB
mdefine_line|#define MPC52xx_PSC_IMR_DB&t;&t;0x0400
DECL|macro|MPC52xx_PSC_IMR_IPC
mdefine_line|#define MPC52xx_PSC_IMR_IPC&t;&t;0x8000
multiline_comment|/* PSC input port change bit */
DECL|macro|MPC52xx_PSC_CTS
mdefine_line|#define MPC52xx_PSC_CTS&t;&t;&t;0x01
DECL|macro|MPC52xx_PSC_DCD
mdefine_line|#define MPC52xx_PSC_DCD&t;&t;&t;0x02
DECL|macro|MPC52xx_PSC_D_CTS
mdefine_line|#define MPC52xx_PSC_D_CTS&t;&t;0x10
DECL|macro|MPC52xx_PSC_D_DCD
mdefine_line|#define MPC52xx_PSC_D_DCD&t;&t;0x20
multiline_comment|/* PSC mode fields */
DECL|macro|MPC52xx_PSC_MODE_5_BITS
mdefine_line|#define MPC52xx_PSC_MODE_5_BITS&t;&t;&t;0x00
DECL|macro|MPC52xx_PSC_MODE_6_BITS
mdefine_line|#define MPC52xx_PSC_MODE_6_BITS&t;&t;&t;0x01
DECL|macro|MPC52xx_PSC_MODE_7_BITS
mdefine_line|#define MPC52xx_PSC_MODE_7_BITS&t;&t;&t;0x02
DECL|macro|MPC52xx_PSC_MODE_8_BITS
mdefine_line|#define MPC52xx_PSC_MODE_8_BITS&t;&t;&t;0x03
DECL|macro|MPC52xx_PSC_MODE_BITS_MASK
mdefine_line|#define MPC52xx_PSC_MODE_BITS_MASK&t;&t;0x03
DECL|macro|MPC52xx_PSC_MODE_PAREVEN
mdefine_line|#define MPC52xx_PSC_MODE_PAREVEN&t;&t;0x00
DECL|macro|MPC52xx_PSC_MODE_PARODD
mdefine_line|#define MPC52xx_PSC_MODE_PARODD&t;&t;&t;0x04
DECL|macro|MPC52xx_PSC_MODE_PARFORCE
mdefine_line|#define MPC52xx_PSC_MODE_PARFORCE&t;&t;0x08
DECL|macro|MPC52xx_PSC_MODE_PARNONE
mdefine_line|#define MPC52xx_PSC_MODE_PARNONE&t;&t;0x10
DECL|macro|MPC52xx_PSC_MODE_ERR
mdefine_line|#define MPC52xx_PSC_MODE_ERR&t;&t;&t;0x20
DECL|macro|MPC52xx_PSC_MODE_FFULL
mdefine_line|#define MPC52xx_PSC_MODE_FFULL&t;&t;&t;0x40
DECL|macro|MPC52xx_PSC_MODE_RXRTS
mdefine_line|#define MPC52xx_PSC_MODE_RXRTS&t;&t;&t;0x80
DECL|macro|MPC52xx_PSC_MODE_ONE_STOP_5_BITS
mdefine_line|#define MPC52xx_PSC_MODE_ONE_STOP_5_BITS&t;0x00
DECL|macro|MPC52xx_PSC_MODE_ONE_STOP
mdefine_line|#define MPC52xx_PSC_MODE_ONE_STOP&t;&t;0x07
DECL|macro|MPC52xx_PSC_MODE_TWO_STOP
mdefine_line|#define MPC52xx_PSC_MODE_TWO_STOP&t;&t;0x0f
DECL|macro|MPC52xx_PSC_RFNUM_MASK
mdefine_line|#define MPC52xx_PSC_RFNUM_MASK&t;0x01ff
multiline_comment|/* Structure of the hardware registers */
DECL|struct|mpc52xx_psc
r_struct
id|mpc52xx_psc
(brace
DECL|member|mode
id|u8
id|mode
suffix:semicolon
multiline_comment|/* PSC + 0x00 */
DECL|member|reserved0
id|u8
id|reserved0
(braket
l_int|3
)braket
suffix:semicolon
r_union
(brace
multiline_comment|/* PSC + 0x04 */
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|clock_select
id|u16
id|clock_select
suffix:semicolon
DECL|member|sr_csr
)brace
id|sr_csr
suffix:semicolon
DECL|macro|mpc52xx_psc_status
mdefine_line|#define mpc52xx_psc_status&t;sr_csr.status
DECL|macro|mpc52xx_psc_clock_select
mdefine_line|#define mpc52xx_psc_clock_select sr_csr.clock_select
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|command
id|u8
id|command
suffix:semicolon
multiline_comment|/* PSC + 0x08 */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
r_union
(brace
multiline_comment|/* PSC + 0x0c */
DECL|member|buffer_8
id|u8
id|buffer_8
suffix:semicolon
DECL|member|buffer_16
id|u16
id|buffer_16
suffix:semicolon
DECL|member|buffer_32
id|u32
id|buffer_32
suffix:semicolon
DECL|member|buffer
)brace
id|buffer
suffix:semicolon
DECL|macro|mpc52xx_psc_buffer_8
mdefine_line|#define mpc52xx_psc_buffer_8&t;buffer.buffer_8
DECL|macro|mpc52xx_psc_buffer_16
mdefine_line|#define mpc52xx_psc_buffer_16&t;buffer.buffer_16
DECL|macro|mpc52xx_psc_buffer_32
mdefine_line|#define mpc52xx_psc_buffer_32&t;buffer.buffer_32
r_union
(brace
multiline_comment|/* PSC + 0x10 */
DECL|member|ipcr
id|u8
id|ipcr
suffix:semicolon
DECL|member|acr
id|u8
id|acr
suffix:semicolon
DECL|member|ipcr_acr
)brace
id|ipcr_acr
suffix:semicolon
DECL|macro|mpc52xx_psc_ipcr
mdefine_line|#define mpc52xx_psc_ipcr&t;ipcr_acr.ipcr
DECL|macro|mpc52xx_psc_acr
mdefine_line|#define mpc52xx_psc_acr&t;&t;ipcr_acr.acr
DECL|member|reserved3
id|u8
id|reserved3
(braket
l_int|3
)braket
suffix:semicolon
r_union
(brace
multiline_comment|/* PSC + 0x14 */
DECL|member|isr
id|u16
id|isr
suffix:semicolon
DECL|member|imr
id|u16
id|imr
suffix:semicolon
DECL|member|isr_imr
)brace
id|isr_imr
suffix:semicolon
DECL|macro|mpc52xx_psc_isr
mdefine_line|#define mpc52xx_psc_isr&t;&t;isr_imr.isr
DECL|macro|mpc52xx_psc_imr
mdefine_line|#define mpc52xx_psc_imr&t;&t;isr_imr.imr
DECL|member|reserved4
id|u16
id|reserved4
suffix:semicolon
DECL|member|ctur
id|u8
id|ctur
suffix:semicolon
multiline_comment|/* PSC + 0x18 */
DECL|member|reserved5
id|u8
id|reserved5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ctlr
id|u8
id|ctlr
suffix:semicolon
multiline_comment|/* PSC + 0x1c */
DECL|member|reserved6
id|u8
id|reserved6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ccr
id|u16
id|ccr
suffix:semicolon
multiline_comment|/* PSC + 0x20 */
DECL|member|reserved7
id|u8
id|reserved7
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|ivr
id|u8
id|ivr
suffix:semicolon
multiline_comment|/* PSC + 0x30 */
DECL|member|reserved8
id|u8
id|reserved8
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ip
id|u8
id|ip
suffix:semicolon
multiline_comment|/* PSC + 0x34 */
DECL|member|reserved9
id|u8
id|reserved9
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|op1
id|u8
id|op1
suffix:semicolon
multiline_comment|/* PSC + 0x38 */
DECL|member|reserved10
id|u8
id|reserved10
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|op0
id|u8
id|op0
suffix:semicolon
multiline_comment|/* PSC + 0x3c */
DECL|member|reserved11
id|u8
id|reserved11
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|sicr
id|u32
id|sicr
suffix:semicolon
multiline_comment|/* PSC + 0x40 */
DECL|member|ircr1
id|u8
id|ircr1
suffix:semicolon
multiline_comment|/* PSC + 0x44 */
DECL|member|reserved13
id|u8
id|reserved13
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ircr2
id|u8
id|ircr2
suffix:semicolon
multiline_comment|/* PSC + 0x44 */
DECL|member|reserved14
id|u8
id|reserved14
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irsdr
id|u8
id|irsdr
suffix:semicolon
multiline_comment|/* PSC + 0x4c */
DECL|member|reserved15
id|u8
id|reserved15
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irmdr
id|u8
id|irmdr
suffix:semicolon
multiline_comment|/* PSC + 0x50 */
DECL|member|reserved16
id|u8
id|reserved16
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irfdr
id|u8
id|irfdr
suffix:semicolon
multiline_comment|/* PSC + 0x54 */
DECL|member|reserved17
id|u8
id|reserved17
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rfnum
id|u16
id|rfnum
suffix:semicolon
multiline_comment|/* PSC + 0x58 */
DECL|member|reserved18
id|u16
id|reserved18
suffix:semicolon
DECL|member|tfnum
id|u16
id|tfnum
suffix:semicolon
multiline_comment|/* PSC + 0x5c */
DECL|member|reserved19
id|u16
id|reserved19
suffix:semicolon
DECL|member|rfdata
id|u32
id|rfdata
suffix:semicolon
multiline_comment|/* PSC + 0x60 */
DECL|member|rfstat
id|u16
id|rfstat
suffix:semicolon
multiline_comment|/* PSC + 0x64 */
DECL|member|reserved20
id|u16
id|reserved20
suffix:semicolon
DECL|member|rfcntl
id|u8
id|rfcntl
suffix:semicolon
multiline_comment|/* PSC + 0x68 */
DECL|member|reserved21
id|u8
id|reserved21
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|rfalarm
id|u16
id|rfalarm
suffix:semicolon
multiline_comment|/* PSC + 0x6e */
DECL|member|reserved22
id|u16
id|reserved22
suffix:semicolon
DECL|member|rfrptr
id|u16
id|rfrptr
suffix:semicolon
multiline_comment|/* PSC + 0x72 */
DECL|member|reserved23
id|u16
id|reserved23
suffix:semicolon
DECL|member|rfwptr
id|u16
id|rfwptr
suffix:semicolon
multiline_comment|/* PSC + 0x76 */
DECL|member|reserved24
id|u16
id|reserved24
suffix:semicolon
DECL|member|rflrfptr
id|u16
id|rflrfptr
suffix:semicolon
multiline_comment|/* PSC + 0x7a */
DECL|member|reserved25
id|u16
id|reserved25
suffix:semicolon
DECL|member|rflwfptr
id|u16
id|rflwfptr
suffix:semicolon
multiline_comment|/* PSC + 0x7e */
DECL|member|tfdata
id|u32
id|tfdata
suffix:semicolon
multiline_comment|/* PSC + 0x80 */
DECL|member|tfstat
id|u16
id|tfstat
suffix:semicolon
multiline_comment|/* PSC + 0x84 */
DECL|member|reserved26
id|u16
id|reserved26
suffix:semicolon
DECL|member|tfcntl
id|u8
id|tfcntl
suffix:semicolon
multiline_comment|/* PSC + 0x88 */
DECL|member|reserved27
id|u8
id|reserved27
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|tfalarm
id|u16
id|tfalarm
suffix:semicolon
multiline_comment|/* PSC + 0x8e */
DECL|member|reserved28
id|u16
id|reserved28
suffix:semicolon
DECL|member|tfrptr
id|u16
id|tfrptr
suffix:semicolon
multiline_comment|/* PSC + 0x92 */
DECL|member|reserved29
id|u16
id|reserved29
suffix:semicolon
DECL|member|tfwptr
id|u16
id|tfwptr
suffix:semicolon
multiline_comment|/* PSC + 0x96 */
DECL|member|reserved30
id|u16
id|reserved30
suffix:semicolon
DECL|member|tflrfptr
id|u16
id|tflrfptr
suffix:semicolon
multiline_comment|/* PSC + 0x9a */
DECL|member|reserved31
id|u16
id|reserved31
suffix:semicolon
DECL|member|tflwfptr
id|u16
id|tflwfptr
suffix:semicolon
multiline_comment|/* PSC + 0x9e */
)brace
suffix:semicolon
macro_line|#endif  /* __ASM_MPC52xx_PSC_H__ */
eof
