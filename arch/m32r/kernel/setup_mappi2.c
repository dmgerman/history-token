multiline_comment|/*&n; *  linux/arch/m32r/kernel/setup_mappi.c&n; *&n; *  Setup routines for Renesas MAPPI-II(M3A-ZA36) Board&n; *&n; *  Copyright (c) 2001, 2002  Hiroyuki Kondo, Hirokazu Takata,&n; *                            Hitoshi Yamamoto, Mamoru Sakugawa&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
id|icu_data_t
id|icu_data
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|function|disable_mappi2_irq
r_static
r_void
id|disable_mappi2_irq
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
r_if
c_cond
(paren
(paren
id|irq
op_eq
l_int|0
)paren
op_logical_or
(paren
id|irq
op_ge
id|NR_IRQS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad irq 0x%08x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
DECL|function|enable_mappi2_irq
r_static
r_void
id|enable_mappi2_irq
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
r_if
c_cond
(paren
(paren
id|irq
op_eq
l_int|0
)paren
op_logical_or
(paren
id|irq
op_ge
id|NR_IRQS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bad irq 0x%08x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
DECL|function|mask_and_ack_mappi2
r_static
r_void
id|mask_and_ack_mappi2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_mappi2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_mappi2_irq
r_static
r_void
id|end_mappi2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_mappi2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|startup_mappi2_irq
r_static
r_int
r_int
id|startup_mappi2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_mappi2_irq
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
DECL|function|shutdown_mappi2_irq
r_static
r_void
id|shutdown_mappi2_irq
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
DECL|variable|mappi2_irq_type
r_static
r_struct
id|hw_interrupt_type
id|mappi2_irq_type
op_assign
(brace
l_string|&quot;MAPPI2-IRQ&quot;
comma
id|startup_mappi2_irq
comma
id|shutdown_mappi2_irq
comma
id|enable_mappi2_irq
comma
id|disable_mappi2_irq
comma
id|mask_and_ack_mappi2
comma
id|end_mappi2_irq
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
macro_line|#if defined(CONFIG_SMC91X)
multiline_comment|/* INT0 : LAN controller (SMC91111) */
id|irq_desc
(braket
id|M32R_IRQ_INT0
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT0
)braket
dot
id|handler
op_assign
op_amp
id|mappi2_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT0
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT0
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_INT0
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD10
suffix:semicolon
id|disable_mappi2_irq
c_func
(paren
id|M32R_IRQ_INT0
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_SMC91X */
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
id|mappi2_irq_type
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
id|disable_mappi2_irq
c_func
(paren
id|M32R_IRQ_MFT2
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_M32R_SIO
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
id|mappi2_irq_type
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
id|disable_mappi2_irq
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
id|mappi2_irq_type
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
id|disable_mappi2_irq
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
id|mappi2_irq_type
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
id|disable_mappi2_irq
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
id|mappi2_irq_type
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
id|disable_mappi2_irq
c_func
(paren
id|M32R_IRQ_SIO1_S
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_M32R_USE_DBG_CONSOLE */
macro_line|#if defined(CONFIG_USB)
multiline_comment|/* INT1 : USB Host controller interrupt */
id|irq_desc
(braket
id|M32R_IRQ_INT1
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT1
)braket
dot
id|handler
op_assign
op_amp
id|mappi2_irq_type
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT1
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|M32R_IRQ_INT1
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|icu_data
(braket
id|M32R_IRQ_INT1
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_ISMOD01
suffix:semicolon
id|disable_mappi2_irq
c_func
(paren
id|M32R_IRQ_INT1
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_USB */
multiline_comment|/* ICUCR40: CFC IREQ */
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
id|mappi2_irq_type
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
singleline_comment|//&t;icu_data[PLD_IRQ_CFIREQ].icucr = M32R_ICUCR_IEN|M32R_ICUCR_ISMOD00;
id|icu_data
(braket
id|PLD_IRQ_CFIREQ
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD01
suffix:semicolon
id|disable_mappi2_irq
c_func
(paren
id|PLD_IRQ_CFIREQ
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_M32R_CFC)
multiline_comment|/* ICUCR41: CFC Insert */
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
id|mappi2_irq_type
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
id|icu_data
(braket
id|PLD_IRQ_CFC_INSERT
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD00
suffix:semicolon
singleline_comment|//&t;icu_data[PLD_IRQ_CFC_INSERT].icucr = 0;
id|disable_mappi2_irq
c_func
(paren
id|PLD_IRQ_CFC_INSERT
)paren
suffix:semicolon
multiline_comment|/* ICUCR42: CFC Eject */
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
id|mappi2_irq_type
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
id|icu_data
(braket
id|PLD_IRQ_CFC_EJECT
)braket
dot
id|icucr
op_assign
id|M32R_ICUCR_IEN
op_or
id|M32R_ICUCR_ISMOD10
suffix:semicolon
singleline_comment|//&t;icu_data[PLD_IRQ_CFC_EJECT].icucr = 0;
id|disable_mappi2_irq
c_func
(paren
id|PLD_IRQ_CFC_EJECT
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MAPPI2_CFC */
)brace
DECL|macro|LAN_IOSTART
mdefine_line|#define LAN_IOSTART     0x300
DECL|macro|LAN_IOEND
mdefine_line|#define LAN_IOEND       0x320
DECL|variable|smc91x_resources
r_static
r_struct
id|resource
id|smc91x_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
(paren
id|LAN_IOSTART
)paren
comma
dot
id|end
op_assign
(paren
id|LAN_IOEND
)paren
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|M32R_IRQ_INT0
comma
dot
id|end
op_assign
id|M32R_IRQ_INT0
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|smc91x_device
r_static
r_struct
id|platform_device
id|smc91x_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;smc91x&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|smc91x_resources
)paren
comma
dot
id|resource
op_assign
id|smc91x_resources
comma
)brace
suffix:semicolon
DECL|function|platform_init
r_static
r_int
id|__init
id|platform_init
c_func
(paren
r_void
)paren
(brace
id|platform_device_register
c_func
(paren
op_amp
id|smc91x_device
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|platform_init
id|arch_initcall
c_func
(paren
id|platform_init
)paren
suffix:semicolon
eof
