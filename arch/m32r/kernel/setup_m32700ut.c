multiline_comment|/*&n; *  linux/arch/m32r/kernel/setup_m32700ut.c&n; *&n; *  Setup routines for MITSUBISHI M32700UT Board&n; *&n; *  Copyright (c) 2002 &t;Hiroyuki Kondo, Hirokazu Takata,&n; *                      Hitoshi Yamamoto, Takeo Takahashi&n; *&n; *  This file is subject to the terms and conditions of the GNU General&n; *  Public License.  See the file &quot;COPYING&quot; in the main directory of this&n; *  archive for more details.&n; *&n; *  $Id: setup_m32700ut.c,v 1.6 2003/11/27 10:18:49 takeo Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * M32700 Interrupt Control Unit (Level 1)&n; */
DECL|macro|irq2port
mdefine_line|#define irq2port(x) (M32R_ICU_CR1_PORTL + ((x - 1) * sizeof(unsigned long)))
macro_line|#ifndef CONFIG_SMP
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
r_static
id|icu_data_t
id|icu_data
(braket
id|M32700UT_NUM_CPU_IRQ
)braket
suffix:semicolon
DECL|function|disable_m32700ut_irq
r_static
r_void
id|disable_m32700ut_irq
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
DECL|function|enable_m32700ut_irq
r_static
r_void
id|enable_m32700ut_irq
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
DECL|function|mask_and_ack_m32700ut
r_static
r_void
id|mask_and_ack_m32700ut
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_m32700ut_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_m32700ut_irq
r_static
r_void
id|end_m32700ut_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|startup_m32700ut_irq
r_static
r_int
r_int
id|startup_m32700ut_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|shutdown_m32700ut_irq
r_static
r_void
id|shutdown_m32700ut_irq
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
DECL|variable|m32700ut_irq_type
r_static
r_struct
id|hw_interrupt_type
id|m32700ut_irq_type
op_assign
(brace
l_string|&quot;M32700UT-IRQ&quot;
comma
id|startup_m32700ut_irq
comma
id|shutdown_m32700ut_irq
comma
id|enable_m32700ut_irq
comma
id|disable_m32700ut_irq
comma
id|mask_and_ack_m32700ut
comma
id|end_m32700ut_irq
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
singleline_comment|//&t;disable_m32700ut_irq(M32R_IRQ_INT1);
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
singleline_comment|//&t;enable_m32700ut_irq(M32R_IRQ_INT1);
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
singleline_comment|//&t;mask_and_ack_m32700ut(M32R_IRQ_INT1);
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
id|end_m32700ut_irq
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
(paren
l_int|0
)paren
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
singleline_comment|//&t;shutdown_m32700ut_irq(M32R_IRQ_INT1);
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
l_string|&quot;M32700UT-PLD-IRQ&quot;
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
multiline_comment|/*&n; * Interrupt Control Unit of PLD on M32700UT-LAN (Level 2)&n; */
DECL|macro|irq2lanpldirq
mdefine_line|#define irq2lanpldirq(x)&t;((x) - M32700UT_LAN_PLD_IRQ_BASE)
DECL|macro|lanpldirq2port
mdefine_line|#define lanpldirq2port(x)&t;(unsigned long)((int)M32700UT_LAN_ICUCR1 + &bslash;&n;&t;&t;&t;&t; (((x) - 1) * sizeof(unsigned short)))
DECL|variable|lanpld_icu_data
r_static
id|pld_icu_data_t
id|lanpld_icu_data
(braket
id|M32700UT_NUM_LAN_PLD_IRQ
)braket
suffix:semicolon
DECL|function|disable_m32700ut_lanpld_irq
r_static
r_void
id|disable_m32700ut_lanpld_irq
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
id|irq2lanpldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|lanpldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|data
op_assign
id|lanpld_icu_data
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
DECL|function|enable_m32700ut_lanpld_irq
r_static
r_void
id|enable_m32700ut_lanpld_irq
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
id|irq2lanpldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|lanpldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|data
op_assign
id|lanpld_icu_data
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
DECL|function|mask_and_ack_m32700ut_lanpld
r_static
r_void
id|mask_and_ack_m32700ut_lanpld
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_m32700ut_lanpld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_m32700ut_lanpld_irq
r_static
r_void
id|end_m32700ut_lanpld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_lanpld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|end_m32700ut_irq
c_func
(paren
id|M32R_IRQ_INT0
)paren
suffix:semicolon
)brace
DECL|function|startup_m32700ut_lanpld_irq
r_static
r_int
r_int
id|startup_m32700ut_lanpld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_lanpld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|shutdown_m32700ut_lanpld_irq
r_static
r_void
id|shutdown_m32700ut_lanpld_irq
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
id|irq2lanpldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|lanpldirq2port
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
DECL|variable|m32700ut_lanpld_irq_type
r_static
r_struct
id|hw_interrupt_type
id|m32700ut_lanpld_irq_type
op_assign
(brace
l_string|&quot;M32700UT-PLD-LAN-IRQ&quot;
comma
id|startup_m32700ut_lanpld_irq
comma
id|shutdown_m32700ut_lanpld_irq
comma
id|enable_m32700ut_lanpld_irq
comma
id|disable_m32700ut_lanpld_irq
comma
id|mask_and_ack_m32700ut_lanpld
comma
id|end_m32700ut_lanpld_irq
)brace
suffix:semicolon
multiline_comment|/*&n; * Interrupt Control Unit of PLD on M32700UT-LCD (Level 2)&n; */
DECL|macro|irq2lcdpldirq
mdefine_line|#define irq2lcdpldirq(x)&t;((x) - M32700UT_LCD_PLD_IRQ_BASE)
DECL|macro|lcdpldirq2port
mdefine_line|#define lcdpldirq2port(x)&t;(unsigned long)((int)M32700UT_LCD_ICUCR1 + &bslash;&n;&t;&t;&t;&t; (((x) - 1) * sizeof(unsigned short)))
DECL|variable|lcdpld_icu_data
r_static
id|pld_icu_data_t
id|lcdpld_icu_data
(braket
id|M32700UT_NUM_LCD_PLD_IRQ
)braket
suffix:semicolon
DECL|function|disable_m32700ut_lcdpld_irq
r_static
r_void
id|disable_m32700ut_lcdpld_irq
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
id|irq2lcdpldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|lcdpldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|data
op_assign
id|lcdpld_icu_data
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
DECL|function|enable_m32700ut_lcdpld_irq
r_static
r_void
id|enable_m32700ut_lcdpld_irq
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
id|irq2lcdpldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|lcdpldirq2port
c_func
(paren
id|pldirq
)paren
suffix:semicolon
id|data
op_assign
id|lcdpld_icu_data
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
DECL|function|mask_and_ack_m32700ut_lcdpld
r_static
r_void
id|mask_and_ack_m32700ut_lcdpld
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_m32700ut_lcdpld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_m32700ut_lcdpld_irq
r_static
r_void
id|end_m32700ut_lcdpld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_lcdpld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|end_m32700ut_irq
c_func
(paren
id|M32R_IRQ_INT2
)paren
suffix:semicolon
)brace
DECL|function|startup_m32700ut_lcdpld_irq
r_static
r_int
r_int
id|startup_m32700ut_lcdpld_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_m32700ut_lcdpld_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|shutdown_m32700ut_lcdpld_irq
r_static
r_void
id|shutdown_m32700ut_lcdpld_irq
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
id|irq2lcdpldirq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|port
op_assign
id|lcdpldirq2port
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
DECL|variable|m32700ut_lcdpld_irq_type
r_static
r_struct
id|hw_interrupt_type
id|m32700ut_lcdpld_irq_type
op_assign
(brace
l_string|&quot;M32700UT-PLD-LCD-IRQ&quot;
comma
id|startup_m32700ut_lcdpld_irq
comma
id|shutdown_m32700ut_lcdpld_irq
comma
id|enable_m32700ut_lcdpld_irq
comma
id|disable_m32700ut_lcdpld_irq
comma
id|mask_and_ack_m32700ut_lcdpld
comma
id|end_m32700ut_lcdpld_irq
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
macro_line|#ifdef CONFIG_M32R_SMC91111
multiline_comment|/* INT#0: LAN controller on M32700UT-LAN (SMC91C111)*/
id|irq_desc
(braket
id|M32700UT_LAN_IRQ_LAN
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32700UT_LAN_IRQ_LAN
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_lanpld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32700UT_LAN_IRQ_LAN
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32700UT_LAN_IRQ_LAN
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* disable nested irq */
id|lanpld_icu_data
(braket
id|irq2lanpldirq
c_func
(paren
id|M32700UT_LAN_IRQ_LAN
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD02
suffix:semicolon
multiline_comment|/* &quot;H&quot; edge sense */
id|disable_m32700ut_lanpld_irq
c_func
(paren
id|M32700UT_LAN_IRQ_LAN
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_M32R_SMC91111 */
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
id|m32700ut_irq_type
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
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_MFT2
)paren
suffix:semicolon
multiline_comment|/* SIO0 : receive */
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
id|m32700ut_irq_type
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
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_SIO0_R
)paren
suffix:semicolon
multiline_comment|/* SIO0 : send */
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
id|m32700ut_irq_type
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
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_SIO0_S
)paren
suffix:semicolon
multiline_comment|/* SIO1 : receive */
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
id|m32700ut_irq_type
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
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_SIO1_R
)paren
suffix:semicolon
multiline_comment|/* SIO1 : send */
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
id|m32700ut_irq_type
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
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_SIO1_S
)paren
suffix:semicolon
multiline_comment|/* DMA1 : */
id|irq_desc
(braket
id|M32R_IRQ_DMA1
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_DMA1
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_DMA1
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_DMA1
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_DMA1
)braket
dot
id|icucr
op_assign
l_int|0
suffix:semicolon
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_DMA1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_M32R_PLDSIO
multiline_comment|/* INT#1: SIO0 Receive on PLD */
id|irq_desc
(braket
id|PLD_IRQ_SIO0_RCV
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SIO0_RCV
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SIO0_RCV
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SIO0_RCV
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
id|PLD_IRQ_SIO0_RCV
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD03
suffix:semicolon
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_SIO0_RCV
)paren
suffix:semicolon
multiline_comment|/* INT#1: SIO0 Send on PLD */
id|irq_desc
(braket
id|PLD_IRQ_SIO0_SND
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SIO0_SND
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SIO0_SND
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_SIO0_SND
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
id|PLD_IRQ_SIO0_SND
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD03
suffix:semicolon
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_SIO0_SND
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_SERIAL_M32R_PLDSIO */
macro_line|#if defined(CONFIG_M32R_CFC)
multiline_comment|/* INT#1: CFC IREQ on PLD */
id|irq_desc
(braket
id|PLD_IRQ_CFIREQ
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFIREQ
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFIREQ
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFIREQ
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
id|PLD_IRQ_CFIREQ
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD01
suffix:semicolon
multiline_comment|/* &squot;L&squot; level sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_CFIREQ
)paren
suffix:semicolon
multiline_comment|/* INT#1: CFC Insert on PLD */
id|irq_desc
(braket
id|PLD_IRQ_CFC_INSERT
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFC_INSERT
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFC_INSERT
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFC_INSERT
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
id|PLD_IRQ_CFC_INSERT
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD00
suffix:semicolon
multiline_comment|/* &squot;L&squot; edge sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_CFC_INSERT
)paren
suffix:semicolon
multiline_comment|/* INT#1: CFC Eject on PLD */
id|irq_desc
(braket
id|PLD_IRQ_CFC_EJECT
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFC_EJECT
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_pld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFC_EJECT
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|PLD_IRQ_CFC_EJECT
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
id|PLD_IRQ_CFC_EJECT
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD02
suffix:semicolon
multiline_comment|/* &squot;H&squot; edge sense */
id|disable_m32700ut_pld_irq
c_func
(paren
id|PLD_IRQ_CFC_EJECT
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_M32R_CFC */
multiline_comment|/*&n;&t; * INT0# is used for LAN, DIO&n;&t; * We enable it here.&n;&t; */
id|icu_data
(braket
id|M32R_IRQ_INT0
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD11
suffix:semicolon
id|enable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_INT0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * INT1# is used for UART, MMC, CF Controller in FPGA.&n;&t; * We enable it here.&n;&t; */
id|icu_data
(braket
id|M32R_IRQ_INT1
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD11
suffix:semicolon
id|enable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_INT1
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_USB)
id|outw
c_func
(paren
id|USBCR_OTGS
comma
id|USBCR
)paren
suffix:semicolon
multiline_comment|/* USBCR: non-OTG */
id|irq_desc
(braket
id|M32700UT_LCD_IRQ_USB_INT1
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32700UT_LCD_IRQ_USB_INT1
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_lcdpld_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32700UT_LCD_IRQ_USB_INT1
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32700UT_LCD_IRQ_USB_INT1
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|lcdpld_icu_data
(braket
id|irq2lcdpldirq
c_func
(paren
id|M32700UT_LCD_IRQ_USB_INT1
)paren
)braket
dot
id|icucr
op_assign
id|PLD_ICUCR_IEN
op_or
id|PLD_ICUCR_ISMOD01
suffix:semicolon
multiline_comment|/* &quot;L&quot; level sense */
id|disable_m32700ut_lcdpld_irq
c_func
(paren
id|M32700UT_LCD_IRQ_USB_INT1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * INT2# is used for BAT, USB, AUDIO&n;&t; * We enable it here.&n;&t; */
id|icu_data
(braket
id|M32R_IRQ_INT2
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD01
suffix:semicolon
id|enable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_INT2
)paren
suffix:semicolon
singleline_comment|//#if defined(CONFIG_M32R_AR_VGA)
multiline_comment|/*&n;&t; * INT3# is used for AR&n;&t; */
id|irq_desc
(braket
id|M32R_IRQ_INT3
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT3
)braket
dot
id|handler
op_assign
op_amp
id|m32700ut_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT3
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT3
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_INT3
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD10
suffix:semicolon
id|disable_m32700ut_irq
c_func
(paren
id|M32R_IRQ_INT3
)paren
suffix:semicolon
singleline_comment|//#endif&t;/* CONFIG_M32R_ARV */
)brace
eof
