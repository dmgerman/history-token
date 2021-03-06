multiline_comment|/*&n; *  linux/arch/m32r/kernel/setup_usrv.c&n; *&n; *  Setup routines for MITSUBISHI uServer&n; *&n; *  Copyright (c) 2001, 2002, 2003  Hiroyuki Kondo, Hirokazu Takata,&n; *                                  Hitoshi Yamamoto&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|irq2port
mdefine_line|#define irq2port(x) (M32R_ICU_CR1_PORTL + ((x - 1) * sizeof(unsigned long)))
macro_line|#if !defined(CONFIG_SMP)
r_typedef
r_struct
(brace
DECL|member|icucr
r_int
r_int
id|icucr
suffix:semicolon
multiline_comment|/* ICU Control Register */
DECL|typedef|icu_data_t
)brace
id|icu_data_t
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|variable|icu_data
id|icu_data_t
id|icu_data
(braket
id|M32700UT_NUM_CPU_IRQ
)braket
suffix:semicolon
DECL|function|disable_mappi_irq
r_static
r_void
id|disable_mappi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
comma
id|data
suffix:semicolon
id|port
op_assign
id|irq2port
c_func
(paren
id|irq
)paren
suffix:semicolon
id|data
op_assign
id|icu_data
(braket
id|irq
)braket
dot
id|icucr
op_or
id|M32R_ICUCR_ILEVEL7
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|enable_mappi_irq
r_static
r_void
id|enable_mappi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
comma
id|data
suffix:semicolon
id|port
op_assign
id|irq2port
c_func
(paren
id|irq
)paren
suffix:semicolon
id|data
op_assign
id|icu_data
(braket
id|irq
)braket
dot
id|icucr
op_or
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ILEVEL6
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|mask_and_ack_mappi
r_static
r_void
id|mask_and_ack_mappi
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_mappi_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_mappi_irq
r_static
r_void
id|end_mappi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_mappi_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|startup_mappi_irq
r_static
r_int
r_int
id|startup_mappi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_mappi_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shutdown_mappi_irq
r_static
r_void
id|shutdown_mappi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
suffix:semicolon
id|port
op_assign
id|irq2port
c_func
(paren
id|irq
)paren
suffix:semicolon
id|outl
c_func
(paren
id|M32R_ICUCR_ILEVEL7
comma
id|port
)paren
suffix:semicolon
)brace
DECL|variable|mappi_irq_type
r_static
r_struct
id|hw_interrupt_type
id|mappi_irq_type
op_assign
(brace
l_string|&quot;M32700-IRQ&quot;
comma
id|startup_mappi_irq
comma
id|shutdown_mappi_irq
comma
id|enable_mappi_irq
comma
id|disable_mappi_irq
comma
id|mask_and_ack_mappi
comma
id|end_mappi_irq
)brace
suffix:semicolon
multiline_comment|/*&n; * Interrupt Control Unit of PLD on M32700UT (Level 2)&n; */
DECL|macro|irq2pldirq
mdefine_line|#define irq2pldirq(x)&t;&t;((x) - M32700UT_PLD_IRQ_BASE)
DECL|macro|pldirq2port
mdefine_line|#define pldirq2port(x)&t;&t;(unsigned long)((int)PLD_ICUCR1 + &bslash;&n;&t;&t;&t;&t; (((x) - 1) * sizeof(unsigned short)))
r_typedef
r_struct
(brace
DECL|member|icucr
r_int
r_int
id|icucr
suffix:semicolon
multiline_comment|/* ICU Control Register */
DECL|typedef|pld_icu_data_t
)brace
id|pld_icu_data_t
suffix:semicolon
DECL|variable|pld_icu_data
r_static
id|pld_icu_data_t
id|pld_icu_data
(braket
id|M32700UT_NUM_PLD_IRQ
)braket
suffix:semicolon
DECL|function|disable_m32700ut_pld_irq
r_static
r_void
id|disable_m32700ut_pld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
comma
id|data
suffix:semicolon
r_int
r_int
id|pldirq
suffix:semicolon
id|pldirq
op_assign
id|irq2pldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|pldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|data
op_assign
id|pld_icu_data
(braket
id|pldirq
)braket
dot
id|icucr
op_or
id|PLD_ICUCR_ILEVEL7
suffix:semicolon
id|outw
c_func
(paren
id|data
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|enable_m32700ut_pld_irq
r_static
r_void
id|enable_m32700ut_pld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
comma
id|data
suffix:semicolon
r_int
r_int
id|pldirq
suffix:semicolon
id|pldirq
op_assign
id|irq2pldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|pldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|data
op_assign
id|pld_icu_data
(braket
id|pldirq
)braket
dot
id|icucr
op_or
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ILEVEL6
suffix:semicolon
id|outw
c_func
(paren
id|data
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|mask_and_ack_m32700ut_pld
r_static
r_void
id|mask_and_ack_m32700ut_pld
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_m32700ut_pld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_m32700ut_pld_irq
r_static
r_void
id|end_m32700ut_pld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_pld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|end_mappi_irq
c_func
(paren
id|M32R_IRQ_INT1
)paren
suffix:semicolon
)brace
DECL|function|startup_m32700ut_pld_irq
r_static
r_int
r_int
id|startup_m32700ut_pld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_pld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shutdown_m32700ut_pld_irq
r_static
r_void
id|shutdown_m32700ut_pld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
suffix:semicolon
r_int
r_int
id|pldirq
suffix:semicolon
id|pldirq
op_assign
id|irq2pldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|pldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|outw
c_func
(paren
id|PLD_ICUCR_ILEVEL7
comma
id|port
)paren
suffix:semicolon
)brace
DECL|variable|m32700ut_pld_irq_type
r_static
r_struct
id|hw_interrupt_type
id|m32700ut_pld_irq_type
op_assign
(brace
l_string|&quot;USRV-PLD-IRQ&quot;
comma
id|startup_m32700ut_pld_irq
comma
id|shutdown_m32700ut_pld_irq
comma
id|enable_m32700ut_pld_irq
comma
id|disable_m32700ut_pld_irq
comma
id|mask_and_ack_m32700ut_pld
comma
id|end_m32700ut_pld_irq
)brace
suffix:semicolon
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|once
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|once
)paren
r_return
suffix:semicolon
r_else
id|once
op_increment
suffix:semicolon
multiline_comment|/* MFT2 : system timer */
id|irq_desc
(braket
id|M32R_IRQ_MFT2
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_MFT2
)braket
dot
id|handler
op_assign
op_amp
id|mappi_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_MFT2
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_MFT2
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_MFT2
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
suffix:semicolon
id|disable_mappi_irq
c_func
(paren
id|M32R_IRQ_MFT2
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_M32R_SIO)
multiline_comment|/* SIO0_R : uart receive data */
id|irq_desc
(braket
id|M32R_IRQ_SIO0_R
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO0_R
)braket
dot
id|handler
op_assign
op_amp
id|mappi_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO0_R
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO0_R
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_SIO0_R
)braket
dot
id|icucr
op_assign
l_int|0
suffix:semicolon
id|disable_mappi_irq
c_func
(paren
id|M32R_IRQ_SIO0_R
)paren
suffix:semicolon
multiline_comment|/* SIO0_S : uart send data */
id|irq_desc
(braket
id|M32R_IRQ_SIO0_S
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO0_S
)braket
dot
id|handler
op_assign
op_amp
id|mappi_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO0_S
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO0_S
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_SIO0_S
)braket
dot
id|icucr
op_assign
l_int|0
suffix:semicolon
id|disable_mappi_irq
c_func
(paren
id|M32R_IRQ_SIO0_S
)paren
suffix:semicolon
multiline_comment|/* SIO1_R : uart receive data */
id|irq_desc
(braket
id|M32R_IRQ_SIO1_R
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO1_R
)braket
dot
id|handler
op_assign
op_amp
id|mappi_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO1_R
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO1_R
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_SIO1_R
)braket
dot
id|icucr
op_assign
l_int|0
suffix:semicolon
id|disable_mappi_irq
c_func
(paren
id|M32R_IRQ_SIO1_R
)paren
suffix:semicolon
multiline_comment|/* SIO1_S : uart send data */
id|irq_desc
(braket
id|M32R_IRQ_SIO1_S
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO1_S
)braket
dot
id|handler
op_assign
op_amp
id|mappi_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO1_S
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_SIO1_S
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_SIO1_S
)braket
dot
id|icucr
op_assign
l_int|0
suffix:semicolon
id|disable_mappi_irq
c_func
(paren
id|M32R_IRQ_SIO1_S
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_SERIAL_M32R_SIO */
multiline_comment|/* INT#67-#71: CFC#0 IREQ on PLD */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CONFIG_CFC_NUM
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|PLD_IRQ_CF0
op_plus
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CF0
op_plus
id|i
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CF0
op_plus
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CF0
op_plus
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* disable nested irq */
id|pld_icu_data
(braket
id|irq2pldirq
c_func
(paren
id|PLD_IRQ_CF0
op_plus
id|i
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_ISMOD01
suffix:semicolon
multiline_comment|/* &squot;L&squot; level sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_CF0
op_plus
id|i
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SERIAL_8250) || defined(CONFIG_SERIAL_8250_MODULE)
multiline_comment|/* INT#76: 16552D#0 IREQ on PLD */
id|irq_desc
(braket
id|PLD_IRQ_UART0
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_UART0
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_UART0
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_UART0
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* disable nested irq */
id|pld_icu_data
(braket
id|irq2pldirq
c_func
(paren
id|PLD_IRQ_UART0
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_ISMOD03
suffix:semicolon
multiline_comment|/* &squot;H&squot; level sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_UART0
)paren
suffix:semicolon
multiline_comment|/* INT#77: 16552D#1 IREQ on PLD */
id|irq_desc
(braket
id|PLD_IRQ_UART1
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_UART1
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_UART1
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_UART1
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* disable nested irq */
id|pld_icu_data
(braket
id|irq2pldirq
c_func
(paren
id|PLD_IRQ_UART1
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_ISMOD03
suffix:semicolon
multiline_comment|/* &squot;H&squot; level sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_UART1
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SERIAL_8250 || CONFIG_SERIAL_8250_MODULE */
macro_line|#if defined(CONFIG_IDC_AK4524) || defined(CONFIG_IDC_AK4524_MODULE)
multiline_comment|/* INT#80: AK4524 IREQ on PLD */
id|irq_desc
(braket
id|PLD_IRQ_SNDINT
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SNDINT
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SNDINT
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SNDINT
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* disable nested irq */
id|pld_icu_data
(braket
id|irq2pldirq
c_func
(paren
id|PLD_IRQ_SNDINT
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_ISMOD01
suffix:semicolon
multiline_comment|/* &squot;L&squot; level sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_SNDINT
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_IDC_AK4524 || CONFIG_IDC_AK4524_MODULE */
multiline_comment|/*&n;&t; * INT1# is used for UART, MMC, CF Controller in FPGA.&n;&t; * We enable it here.&n;&t; */
id|icu_data
(braket
id|M32R_IRQ_INT1
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_ISMOD11
suffix:semicolon
id|enable_mappi_irq
c_func
(paren
id|M32R_IRQ_INT1
)paren
suffix:semicolon
)brace
eof
