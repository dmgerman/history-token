multiline_comment|/* $Id: parport.c,v 1.7 2001/06/25 16:17:30 jonashg Exp $&n; * &n; * Elinux parallel port driver&n; * NOTE!&n; *   Since par0 shares DMA with ser2 and par 1 shares DMA with ser3&n; *   this should be handled if both are enabled at the same time.&n; *   THIS IS NOT HANDLED YET!&n; *&n; * Copyright (c) 2001 Axis Communications AB&n; * &n; * Author: Fredrik Hugosson&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/svinto.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK printk
macro_line|#else
DECL|function|DPRINTK
r_static
r_inline
r_int
id|DPRINTK
c_func
(paren
r_void
op_star
id|nothing
comma
dot
dot
dot
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Etrax100 DMAchannels:&n; * Par0 out : DMA2&n; * Par0 in  : DMA3&n; * Par1 out : DMA4&n; * Par1 in  : DMA5&n; * NOTE! par0 is shared with ser2 and par1 is shared with ser3 regarding&n; *       DMA and DMA irq&n; */
singleline_comment|//#define CONFIG_PAR0_INT 1
singleline_comment|//#define CONFIG_PAR1_INT 1
DECL|macro|SETF
mdefine_line|#define SETF(var, reg, field, val) &bslash;&n;&t;var = (var &amp; ~IO_MASK(##reg##, field)) | IO_FIELD(##reg##, field, val)
DECL|macro|SETS
mdefine_line|#define SETS(var, reg, field, val) &bslash;&n;&t;var = (var &amp; ~IO_MASK(##reg##, field)) | IO_STATE(##reg##, field, val)
DECL|struct|etrax100par_struct
r_struct
id|etrax100par_struct
(brace
multiline_comment|/* parallell port control */
DECL|member|reg_ctrl_data
r_volatile
id|u32
op_star
id|reg_ctrl_data
suffix:semicolon
multiline_comment|/* R_PARx_CTRL_DATA */
DECL|member|reg_status_data
r_const
r_volatile
id|u32
op_star
id|reg_status_data
suffix:semicolon
multiline_comment|/* R_PARx_STATUS_DATA */
DECL|member|reg_config
r_volatile
id|u32
op_star
id|reg_config
suffix:semicolon
multiline_comment|/* R_PARx_CONFIG */
DECL|member|reg_delay
r_volatile
id|u32
op_star
id|reg_delay
suffix:semicolon
multiline_comment|/* R_PARx_DELAY */
multiline_comment|/* DMA control */
DECL|member|odma
r_int
id|odma
suffix:semicolon
DECL|member|dma_irq
r_int
r_int
id|dma_irq
suffix:semicolon
multiline_comment|/* bitnr in R_IRQ_MASK2 for dmaX_descr */
DECL|member|oclrintradr
r_volatile
r_char
op_star
id|oclrintradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CLR_INTR, output */
DECL|member|ofirstadr
r_volatile
id|u32
op_star
id|ofirstadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_FIRST, output */
DECL|member|ocmdadr
r_volatile
r_char
op_star
id|ocmdadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CMD, output */
DECL|member|iclrintradr
r_volatile
r_char
op_star
id|iclrintradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CLR_INTR, input */
DECL|member|ifirstadr
r_volatile
id|u32
op_star
id|ifirstadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_FIRST, input */
DECL|member|icmdadr
r_volatile
r_char
op_star
id|icmdadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CMD, input */
multiline_comment|/* Non DMA interrupt stuff */
DECL|member|int_irq
r_int
r_int
id|int_irq
suffix:semicolon
multiline_comment|/* R_VECT_MASK_RD */
DECL|member|irq_mask_rd
r_const
r_volatile
id|u32
op_star
id|irq_mask_rd
suffix:semicolon
multiline_comment|/* R_IRQ_MASKX_RD */
DECL|member|irq_mask_clr
r_volatile
id|u32
op_star
id|irq_mask_clr
suffix:semicolon
multiline_comment|/* R_IRQ_MASKX_RD */
DECL|member|irq_read
r_const
r_volatile
id|u32
op_star
id|irq_read
suffix:semicolon
multiline_comment|/* R_IRQ_READX */
DECL|member|irq_mask_set
r_volatile
id|u32
op_star
id|irq_mask_set
suffix:semicolon
multiline_comment|/* R_IRQ_MASKX_SET */
DECL|member|irq_mask_tx
r_int
r_int
id|irq_mask_tx
suffix:semicolon
multiline_comment|/* bitmask in R_IRQ_ for tx (ready) int */
DECL|member|irq_mask_rx
r_int
r_int
id|irq_mask_rx
suffix:semicolon
multiline_comment|/* bitmask in R_IRQ_ for rx (data) int */
DECL|member|irq_mask_ecp_cmd
r_int
r_int
id|irq_mask_ecp_cmd
suffix:semicolon
multiline_comment|/* mask in R_IRQ_ for ecp_cmd int */
DECL|member|irq_mask_peri
r_int
r_int
id|irq_mask_peri
suffix:semicolon
multiline_comment|/* bitmask in R_IRQ_ for peri int */
DECL|member|portnr
r_int
id|portnr
suffix:semicolon
multiline_comment|/* ----- end of fields initialised in port_table[] below ----- */
DECL|member|port
r_struct
id|parport
op_star
id|port
suffix:semicolon
multiline_comment|/* Shadow registers */
DECL|member|reg_ctrl_data_shadow
r_volatile
r_int
r_int
id|reg_ctrl_data_shadow
suffix:semicolon
multiline_comment|/* for R_PARx_CTRL_DATA */
DECL|member|reg_config_shadow
r_volatile
r_int
r_int
id|reg_config_shadow
suffix:semicolon
multiline_comment|/* for R_PARx_CONFIG */
DECL|member|reg_delay_shadow
r_volatile
r_int
r_int
id|reg_delay_shadow
suffix:semicolon
multiline_comment|/* for R_PARx_DELAY */
)brace
suffix:semicolon
multiline_comment|/* Always have the complete structs here, even if the port is not used!&n; *  (that way we can index this by the port number)&n; */
DECL|variable|port_table
r_static
r_struct
id|etrax100par_struct
id|port_table
(braket
)braket
op_assign
(brace
(brace
id|R_PAR0_CTRL_DATA
comma
id|R_PAR0_STATUS_DATA
comma
id|R_PAR0_CONFIG
comma
id|R_PAR0_DELAY
comma
multiline_comment|/* DMA interrupt stuff */
l_int|2
comma
l_int|1U
op_lshift
l_int|4
comma
multiline_comment|/* uses DMA 2 and 3 */
id|R_DMA_CH2_CLR_INTR
comma
id|R_DMA_CH2_FIRST
comma
id|R_DMA_CH2_CMD
comma
id|R_DMA_CH3_CLR_INTR
comma
id|R_DMA_CH3_FIRST
comma
id|R_DMA_CH3_CMD
comma
multiline_comment|/* Non DMA interrupt stuff */
id|IO_BITNR
c_func
(paren
id|R_VECT_MASK_RD
comma
id|par0
)paren
comma
id|R_IRQ_MASK0_RD
comma
id|R_IRQ_MASK0_CLR
comma
id|R_IRQ_READ0
comma
id|R_IRQ_MASK0_SET
comma
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK0_RD
comma
id|par0_ready
comma
l_int|1U
)paren
comma
multiline_comment|/* tx (ready)*/
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK0_RD
comma
id|par0_data
comma
l_int|1U
)paren
comma
multiline_comment|/* rx (data)*/
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK0_RD
comma
id|par0_ecp_cmd
comma
l_int|1U
)paren
comma
multiline_comment|/* ecp_cmd */
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK0_RD
comma
id|par0_peri
comma
l_int|1U
)paren
comma
multiline_comment|/* peri */
l_int|0
)brace
comma
(brace
id|R_PAR1_CTRL_DATA
comma
id|R_PAR1_STATUS_DATA
comma
id|R_PAR1_CONFIG
comma
id|R_PAR1_DELAY
comma
multiline_comment|/* DMA interrupt stuff */
l_int|4
comma
l_int|1U
op_lshift
l_int|8
comma
multiline_comment|/* uses DMA 4 and 5 */
id|R_DMA_CH4_CLR_INTR
comma
id|R_DMA_CH4_FIRST
comma
id|R_DMA_CH4_CMD
comma
id|R_DMA_CH5_CLR_INTR
comma
id|R_DMA_CH5_FIRST
comma
id|R_DMA_CH5_CMD
comma
multiline_comment|/* Non DMA interrupt stuff */
id|IO_BITNR
c_func
(paren
id|R_VECT_MASK_RD
comma
id|par1
)paren
comma
id|R_IRQ_MASK1_RD
comma
id|R_IRQ_MASK1_CLR
comma
id|R_IRQ_READ1
comma
id|R_IRQ_MASK1_SET
comma
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK1_RD
comma
id|par1_ready
comma
l_int|1U
)paren
comma
multiline_comment|/* tx (ready)*/
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK1_RD
comma
id|par1_data
comma
l_int|1U
)paren
comma
multiline_comment|/* rx (data)*/
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK1_RD
comma
id|par1_ecp_cmd
comma
l_int|1U
)paren
comma
multiline_comment|/* ecp_cmd */
id|IO_FIELD
c_func
(paren
id|R_IRQ_MASK1_RD
comma
id|par1_peri
comma
l_int|1U
)paren
comma
multiline_comment|/* peri */
l_int|1
)brace
)brace
suffix:semicolon
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS (sizeof(port_table)/sizeof(struct etrax100par_struct))
r_static
r_void
DECL|function|parport_etrax_write_data
id|parport_etrax_write_data
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|value
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: etrax_write_data %02X&bslash;n&quot;
comma
id|p-&gt;portnum
comma
id|value
)paren
suffix:semicolon
id|SETF
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|data
comma
id|value
)paren
suffix:semicolon
op_star
id|info-&gt;reg_ctrl_data
op_assign
id|info-&gt;reg_ctrl_data_shadow
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_etrax_read_data
id|parport_etrax_read_data
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_char
id|ret
suffix:semicolon
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
id|ret
op_assign
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_STATUS_DATA
comma
id|data
comma
op_star
id|info-&gt;reg_status_data
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: etrax_read_data %02X&bslash;n&quot;
comma
id|p-&gt;portnum
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_write_control
id|parport_etrax_write_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|control
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: etrax_write_control %02x&bslash;n&quot;
comma
id|p-&gt;portnum
comma
id|control
)paren
suffix:semicolon
id|SETF
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|strb
comma
(paren
id|control
op_amp
id|PARPORT_CONTROL_STROBE
)paren
OG
l_int|0
)paren
suffix:semicolon
id|SETF
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|autofd
comma
(paren
id|control
op_amp
id|PARPORT_CONTROL_AUTOFD
)paren
OG
l_int|0
)paren
suffix:semicolon
id|SETF
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|init
comma
(paren
id|control
op_amp
id|PARPORT_CONTROL_INIT
)paren
OG
l_int|0
)paren
suffix:semicolon
id|SETF
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|seli
comma
(paren
id|control
op_amp
id|PARPORT_CONTROL_SELECT
)paren
OG
l_int|0
)paren
suffix:semicolon
op_star
id|info-&gt;reg_ctrl_data
op_assign
id|info-&gt;reg_ctrl_data_shadow
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_etrax_read_control
id|parport_etrax_read_control
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_char
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|strb
comma
id|info-&gt;reg_ctrl_data_shadow
)paren
)paren
id|ret
op_or_assign
id|PARPORT_CONTROL_STROBE
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|autofd
comma
id|info-&gt;reg_ctrl_data_shadow
)paren
)paren
id|ret
op_or_assign
id|PARPORT_CONTROL_AUTOFD
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|init
comma
id|info-&gt;reg_ctrl_data_shadow
)paren
)paren
id|ret
op_or_assign
id|PARPORT_CONTROL_INIT
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|seli
comma
id|info-&gt;reg_ctrl_data_shadow
)paren
)paren
id|ret
op_or_assign
id|PARPORT_CONTROL_SELECT
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: etrax_read_control %02x&bslash;n&quot;
comma
id|p-&gt;portnum
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_etrax_frob_control
id|parport_etrax_frob_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
(brace
r_int
r_char
id|old
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: frob_control mask %02x, value %02x&bslash;n&quot;
comma
id|p-&gt;portnum
comma
id|mask
comma
id|val
)paren
suffix:semicolon
id|old
op_assign
id|parport_etrax_read_control
c_func
(paren
id|p
)paren
suffix:semicolon
id|parport_etrax_write_control
c_func
(paren
id|p
comma
(paren
id|old
op_amp
op_complement
id|mask
)paren
op_xor
id|val
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|parport_etrax_read_status
id|parport_etrax_read_status
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_char
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_STATUS_DATA
comma
id|fault
comma
op_star
id|info-&gt;reg_status_data
)paren
)paren
id|ret
op_or_assign
id|PARPORT_STATUS_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_STATUS_DATA
comma
id|sel
comma
op_star
id|info-&gt;reg_status_data
)paren
)paren
id|ret
op_or_assign
id|PARPORT_STATUS_SELECT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_STATUS_DATA
comma
id|perr
comma
op_star
id|info-&gt;reg_status_data
)paren
)paren
id|ret
op_or_assign
id|PARPORT_STATUS_PAPEROUT
suffix:semicolon
r_if
c_cond
(paren
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_STATUS_DATA
comma
id|ack
comma
op_star
id|info-&gt;reg_status_data
)paren
)paren
id|ret
op_or_assign
id|PARPORT_STATUS_ACK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IO_EXTRACT
c_func
(paren
id|R_PAR0_STATUS_DATA
comma
id|busy
comma
op_star
id|info-&gt;reg_status_data
)paren
)paren
id|ret
op_or_assign
id|PARPORT_STATUS_BUSY
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: status register %04x&bslash;n&quot;
comma
id|p-&gt;portnum
comma
op_star
id|info-&gt;reg_status_data
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: read_status %02x&bslash;n&quot;
comma
id|p-&gt;portnum
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_enable_irq
id|parport_etrax_enable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
op_star
id|info-&gt;irq_mask_set
op_assign
id|info-&gt;irq_mask_tx
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: enable irq&bslash;n&quot;
comma
id|p-&gt;portnum
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_disable_irq
id|parport_etrax_disable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
op_star
id|info-&gt;irq_mask_clr
op_assign
id|info-&gt;irq_mask_tx
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: disable irq&bslash;n&quot;
comma
id|p-&gt;portnum
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_data_forward
id|parport_etrax_data_forward
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: forward mode&bslash;n&quot;
comma
id|p-&gt;portnum
)paren
suffix:semicolon
id|SETS
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|oe
comma
id|enable
)paren
suffix:semicolon
op_star
id|info-&gt;reg_ctrl_data
op_assign
id|info-&gt;reg_ctrl_data_shadow
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_data_reverse
id|parport_etrax_data_reverse
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
id|p-&gt;private_data
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: reverse mode&bslash;n&quot;
comma
id|p-&gt;portnum
)paren
suffix:semicolon
id|SETS
c_func
(paren
id|info-&gt;reg_ctrl_data_shadow
comma
id|R_PAR0_CTRL_DATA
comma
id|oe
comma
id|disable
)paren
suffix:semicolon
op_star
id|info-&gt;reg_ctrl_data
op_assign
id|info-&gt;reg_ctrl_data_shadow
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_init_state
id|parport_etrax_init_state
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP: parport_etrax_init_state&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_save_state
id|parport_etrax_save_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP: parport_etrax_save_state&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_restore_state
id|parport_etrax_restore_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP: parport_etrax_restore_state&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_inc_use_count
id|parport_etrax_inc_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
r_static
r_void
DECL|function|parport_etrax_dec_use_count
id|parport_etrax_dec_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
r_static
r_struct
DECL|variable|pp_etrax_ops
id|parport_operations
id|pp_etrax_ops
op_assign
(brace
id|parport_etrax_write_data
comma
id|parport_etrax_read_data
comma
id|parport_etrax_write_control
comma
id|parport_etrax_read_control
comma
id|parport_etrax_frob_control
comma
id|parport_etrax_read_status
comma
id|parport_etrax_enable_irq
comma
id|parport_etrax_disable_irq
comma
id|parport_etrax_data_forward
comma
id|parport_etrax_data_reverse
comma
id|parport_etrax_init_state
comma
id|parport_etrax_save_state
comma
id|parport_etrax_restore_state
comma
id|parport_etrax_inc_use_count
comma
id|parport_etrax_dec_use_count
comma
id|parport_ieee1284_epp_write_data
comma
id|parport_ieee1284_epp_read_data
comma
id|parport_ieee1284_epp_write_addr
comma
id|parport_ieee1284_epp_read_addr
comma
id|parport_ieee1284_ecp_write_data
comma
id|parport_ieee1284_ecp_read_data
comma
id|parport_ieee1284_ecp_write_addr
comma
id|parport_ieee1284_write_compat
comma
id|parport_ieee1284_read_nibble
comma
id|parport_ieee1284_read_byte
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|parport_etrax_interrupt
id|parport_etrax_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
op_assign
(paren
r_struct
id|etrax100par_struct
op_star
)paren
(paren
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
)paren
op_member_access_from_pointer
id|private_data
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;* E100 PP %d: Interrupt received&bslash;n&quot;
comma
(paren
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
)paren
op_member_access_from_pointer
id|portnum
)paren
suffix:semicolon
op_star
id|info-&gt;irq_mask_clr
op_assign
id|info-&gt;irq_mask_tx
suffix:semicolon
id|parport_generic_irq
c_func
(paren
id|irq
comma
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------- Initialisation code --------------------------------- */
r_static
r_void
id|__init
DECL|function|parport_etrax_show_parallel_version
id|parport_etrax_show_parallel_version
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ETRAX 100LX parallel port driver v1.0, (c) 2001 Axis Communications AB&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ETRAX_PAR0_DMA
DECL|macro|PAR0_USE_DMA
mdefine_line|#define PAR0_USE_DMA 1
macro_line|#else
DECL|macro|PAR0_USE_DMA
mdefine_line|#define PAR0_USE_DMA 0
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_PAR1_DMA
DECL|macro|PAR1_USE_DMA
mdefine_line|#define PAR1_USE_DMA 1
macro_line|#else
DECL|macro|PAR1_USE_DMA
mdefine_line|#define PAR1_USE_DMA 0
macro_line|#endif
r_static
r_void
id|__init
DECL|function|parport_etrax_init_registers
id|parport_etrax_init_registers
c_func
(paren
r_void
)paren
(brace
r_struct
id|etrax100par_struct
op_star
id|info
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|info
op_assign
id|port_table
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
comma
id|info
op_increment
)paren
(brace
macro_line|#ifndef CONFIG_ETRAX_PARALLEL_PORT0
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_ETRAX_PARALLEL_PORT1
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|info-&gt;reg_config_shadow
op_assign
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|iseli
comma
id|inv
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|iautofd
comma
id|inv
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|istrb
comma
id|inv
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|iinit
comma
id|inv
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|rle_in
comma
id|disable
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|rle_out
comma
id|disable
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|enable
comma
id|on
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|force
comma
id|off
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|ign_ack
comma
id|wait
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|oe_ack
comma
id|wait_oe
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|mode
comma
id|manual
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|0
op_logical_and
id|PAR0_USE_DMA
)paren
op_logical_or
(paren
id|i
op_eq
l_int|1
op_logical_and
id|PAR1_USE_DMA
)paren
)paren
id|info-&gt;reg_config_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|dma
comma
id|enable
)paren
suffix:semicolon
r_else
id|info-&gt;reg_config_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_PAR0_CONFIG
comma
id|dma
comma
id|disable
)paren
suffix:semicolon
op_star
id|info-&gt;reg_config
op_assign
id|info-&gt;reg_config_shadow
suffix:semicolon
id|info-&gt;reg_ctrl_data_shadow
op_assign
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|peri_int
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|oe
comma
id|enable
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|seli
comma
id|inactive
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|autofd
comma
id|inactive
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|strb
comma
id|inactive
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|init
comma
id|inactive
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|ecp_cmd
comma
id|data
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|data
comma
l_int|0
)paren
suffix:semicolon
op_star
id|info-&gt;reg_ctrl_data
op_assign
id|info-&gt;reg_ctrl_data_shadow
suffix:semicolon
multiline_comment|/* Clear peri int without setting shadow */
op_star
id|info-&gt;reg_ctrl_data
op_assign
id|info-&gt;reg_ctrl_data_shadow
op_or
id|IO_STATE
c_func
(paren
id|R_PAR0_CTRL_DATA
comma
id|peri_int
comma
id|ack
)paren
suffix:semicolon
id|info-&gt;reg_delay_shadow
op_assign
id|IO_FIELD
c_func
(paren
id|R_PAR0_DELAY
comma
id|setup
comma
l_int|5
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_PAR0_DELAY
comma
id|strobe
comma
l_int|5
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_PAR0_DELAY
comma
id|hold
comma
l_int|5
)paren
suffix:semicolon
op_star
id|info-&gt;reg_delay
op_assign
id|info-&gt;reg_delay_shadow
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ETRAX_PARALLEL_PORT0
macro_line|#ifdef CONFIG_ETRAX_PAR0_DMA
id|RESET_DMA
c_func
(paren
id|PAR0_TX_DMA_NBR
)paren
suffix:semicolon
id|WAIT_DMA
c_func
(paren
id|PAR0_TX_DMA_NBR
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_SERIAL_PORT2
id|printk
c_func
(paren
l_string|&quot; Warning - DMA clash with ser2!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* SERIAL_PORT2 */
macro_line|#endif /* DMA */
macro_line|#endif /* PORT0 */
macro_line|#ifdef CONFIG_ETRAX_PARALLEL_PORT1
macro_line|#ifdef CONFIG_ETRAX_PAR1_DMA
id|RESET_DMA
c_func
(paren
id|PAR1_TX_DMA_NBR
)paren
suffix:semicolon
id|WAIT_DMA
c_func
(paren
id|PAR1_TX_DMA_NBR
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_SERIAL_PORT3
id|printk
c_func
(paren
l_string|&quot; Warning - DMA clash with ser3!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* SERIAL_PORT3 */
macro_line|#endif /* DMA */
macro_line|#endif /* PORT1 */
)brace
r_int
id|__init
DECL|function|parport_etrax_init
id|parport_etrax_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|parport
op_star
id|p
suffix:semicolon
r_int
id|port_exists
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|etrax100par_struct
op_star
id|info
suffix:semicolon
r_const
r_char
op_star
id|names
(braket
)braket
op_assign
(brace
l_string|&quot;parallel 0 tx+rx&quot;
comma
l_string|&quot;parallel 1 tx+rx&quot;
)brace
suffix:semicolon
id|parport_etrax_show_parallel_version
c_func
(paren
)paren
suffix:semicolon
id|parport_etrax_init_registers
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|info
op_assign
id|port_table
suffix:semicolon
id|i
OL
id|NR_PORTS
suffix:semicolon
id|i
op_increment
comma
id|info
op_increment
)paren
(brace
macro_line|#ifndef CONFIG_ETRAX_PARALLEL_PORT0
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_ETRAX_PARALLEL_PORT1
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|p
op_assign
id|parport_register_port
c_func
(paren
(paren
r_int
r_int
)paren
l_int|0
comma
id|info-&gt;int_irq
comma
id|PARPORT_DMA_NONE
comma
op_amp
id|pp_etrax_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_continue
suffix:semicolon
id|info-&gt;port
op_assign
id|p
suffix:semicolon
id|p-&gt;private_data
op_assign
id|info
suffix:semicolon
multiline_comment|/* Axis FIXME: Set mode flags. */
multiline_comment|/* p-&gt;modes = PARPORT_MODE_TRISTATE | PARPORT_MODE_SAFEININT; */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|info-&gt;int_irq
comma
id|parport_etrax_interrupt
comma
id|SA_SHIRQ
comma
id|names
(braket
id|i
)braket
comma
id|p
)paren
)paren
(brace
id|parport_unregister_port
(paren
id|p
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: ETRAX 100LX port %d using irq&bslash;n&quot;
comma
id|p-&gt;name
comma
id|i
)paren
suffix:semicolon
id|parport_proc_register
c_func
(paren
id|p
)paren
suffix:semicolon
id|parport_announce_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|port_exists
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|port_exists
suffix:semicolon
)brace
r_void
id|__exit
DECL|function|parport_etrax_exit
id|parport_etrax_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|etrax100par_struct
op_star
id|info
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|info
op_assign
id|port_table
suffix:semicolon
id|i
OL
id|NR_PORTS
suffix:semicolon
id|i
op_increment
comma
id|info
op_increment
)paren
(brace
macro_line|#ifndef CONFIG_ETRAX_PARALLEL_PORT0
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_ETRAX_PARALLEL_PORT1
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|info-&gt;int_irq
op_ne
id|PARPORT_IRQ_NONE
)paren
id|free_irq
c_func
(paren
id|info-&gt;int_irq
comma
id|info-&gt;port
)paren
suffix:semicolon
id|parport_proc_unregister
c_func
(paren
id|info-&gt;port
)paren
suffix:semicolon
id|parport_unregister_port
c_func
(paren
id|info-&gt;port
)paren
suffix:semicolon
)brace
)brace
eof
