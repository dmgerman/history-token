multiline_comment|/*&n; *  linux/arch/arm/mach-clps7500/core.c&n; *&n; *  Copyright (C) 1998 Russell King&n; *  Copyright (C) 1999 Nexus Electronics Ltd&n; *&n; * Extra MM routines for CL7500 architecture&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|function|cl7500_ack_irq_a
r_static
r_void
id|cl7500_ack_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|mask
comma
id|IOMD_IRQCLRA
)paren
suffix:semicolon
)brace
DECL|function|cl7500_mask_irq_a
r_static
r_void
id|cl7500_mask_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
)brace
DECL|function|cl7500_unmask_irq_a
r_static
r_void
id|cl7500_unmask_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
)brace
DECL|variable|clps7500_a_chip
r_static
r_struct
id|irqchip
id|clps7500_a_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_ack_irq_a
comma
dot
id|mask
op_assign
id|cl7500_mask_irq_a
comma
dot
id|unmask
op_assign
id|cl7500_unmask_irq_a
comma
)brace
suffix:semicolon
DECL|function|cl7500_mask_irq_b
r_static
r_void
id|cl7500_mask_irq_b
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKB
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKB
)paren
suffix:semicolon
)brace
DECL|function|cl7500_unmask_irq_b
r_static
r_void
id|cl7500_unmask_irq_b
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKB
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_IRQMASKB
)paren
suffix:semicolon
)brace
DECL|variable|clps7500_b_chip
r_static
r_struct
id|irqchip
id|clps7500_b_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_mask_irq_b
comma
dot
id|mask
op_assign
id|cl7500_mask_irq_b
comma
dot
id|unmask
op_assign
id|cl7500_unmask_irq_b
comma
)brace
suffix:semicolon
DECL|function|cl7500_mask_irq_c
r_static
r_void
id|cl7500_mask_irq_c
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKC
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKC
)paren
suffix:semicolon
)brace
DECL|function|cl7500_unmask_irq_c
r_static
r_void
id|cl7500_unmask_irq_c
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKC
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_IRQMASKC
)paren
suffix:semicolon
)brace
DECL|variable|clps7500_c_chip
r_static
r_struct
id|irqchip
id|clps7500_c_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_mask_irq_c
comma
dot
id|mask
op_assign
id|cl7500_mask_irq_c
comma
dot
id|unmask
op_assign
id|cl7500_unmask_irq_c
comma
)brace
suffix:semicolon
DECL|function|cl7500_mask_irq_d
r_static
r_void
id|cl7500_mask_irq_d
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKD
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKD
)paren
suffix:semicolon
)brace
DECL|function|cl7500_unmask_irq_d
r_static
r_void
id|cl7500_unmask_irq_d
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKD
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_IRQMASKD
)paren
suffix:semicolon
)brace
DECL|variable|clps7500_d_chip
r_static
r_struct
id|irqchip
id|clps7500_d_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_mask_irq_d
comma
dot
id|mask
op_assign
id|cl7500_mask_irq_d
comma
dot
id|unmask
op_assign
id|cl7500_unmask_irq_d
comma
)brace
suffix:semicolon
DECL|function|cl7500_mask_irq_dma
r_static
r_void
id|cl7500_mask_irq_dma
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_DMAMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_DMAMASK
)paren
suffix:semicolon
)brace
DECL|function|cl7500_unmask_irq_dma
r_static
r_void
id|cl7500_unmask_irq_dma
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_DMAMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_DMAMASK
)paren
suffix:semicolon
)brace
DECL|variable|clps7500_dma_chip
r_static
r_struct
id|irqchip
id|clps7500_dma_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_mask_irq_dma
comma
dot
id|mask
op_assign
id|cl7500_mask_irq_dma
comma
dot
id|unmask
op_assign
id|cl7500_unmask_irq_dma
comma
)brace
suffix:semicolon
DECL|function|cl7500_mask_irq_fiq
r_static
r_void
id|cl7500_mask_irq_fiq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_FIQMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_FIQMASK
)paren
suffix:semicolon
)brace
DECL|function|cl7500_unmask_irq_fiq
r_static
r_void
id|cl7500_unmask_irq_fiq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_FIQMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_FIQMASK
)paren
suffix:semicolon
)brace
DECL|variable|clps7500_fiq_chip
r_static
r_struct
id|irqchip
id|clps7500_fiq_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_mask_irq_fiq
comma
dot
id|mask
op_assign
id|cl7500_mask_irq_fiq
comma
dot
id|unmask
op_assign
id|cl7500_unmask_irq_fiq
comma
)brace
suffix:semicolon
DECL|function|cl7500_no_action
r_static
r_void
id|cl7500_no_action
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|variable|clps7500_no_chip
r_static
r_struct
id|irqchip
id|clps7500_no_chip
op_assign
(brace
dot
id|ack
op_assign
id|cl7500_no_action
comma
dot
id|mask
op_assign
id|cl7500_no_action
comma
dot
id|unmask
op_assign
id|cl7500_no_action
comma
)brace
suffix:semicolon
DECL|variable|irq_isa
r_static
r_struct
id|irqaction
id|irq_isa
op_assign
(brace
id|no_action
comma
l_int|0
comma
id|CPU_MASK_NONE
comma
l_string|&quot;isa&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|clps7500_init_irq
r_static
r_void
id|__init
id|clps7500_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
comma
id|flags
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_IRQMASKB
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_FIQMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_DMAMASK
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|flags
op_assign
id|IRQF_VALID
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_le
l_int|6
op_logical_or
(paren
id|irq
op_ge
l_int|9
op_logical_and
id|irq
op_le
l_int|15
)paren
op_logical_or
(paren
id|irq
op_ge
l_int|48
op_logical_and
id|irq
op_le
l_int|55
)paren
)paren
id|flags
op_or_assign
id|IRQF_PROBE
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|7
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_a_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
dot
dot
dot
l_int|15
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_b_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
dot
dot
dot
l_int|22
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_dma_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
dot
dot
dot
l_int|31
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_c_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|40
dot
dot
dot
l_int|47
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_d_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48
dot
dot
dot
l_int|55
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_no_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|64
dot
dot
dot
l_int|72
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|clps7500_fiq_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|setup_irq
c_func
(paren
id|IRQ_ISA
comma
op_amp
id|irq_isa
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|cl7500_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IO space&t;*/
(brace
id|ISA_BASE
comma
id|ISA_START
comma
id|ISA_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* ISA space&t;*/
(brace
id|FLASH_BASE
comma
id|FLASH_START
comma
id|FLASH_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Flash&t;*/
(brace
id|LED_BASE
comma
id|LED_START
comma
id|LED_SIZE
comma
id|MT_DEVICE
)brace
multiline_comment|/* LED&t;&t;*/
)brace
suffix:semicolon
DECL|function|clps7500_map_io
r_static
r_void
id|__init
id|clps7500_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|cl7500_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|cl7500_io_desc
)paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|ioctime_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ioc_timer_gettimeoffset
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|irqreturn_t
DECL|function|clps7500_timer_interrupt
id|clps7500_timer_interrupt
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
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* Why not using do_leds interface?? */
(brace
multiline_comment|/* Twinkle the lights. */
r_static
r_int
id|count
comma
id|state
op_assign
l_int|0xff00
suffix:semicolon
r_if
c_cond
(paren
id|count
op_decrement
op_eq
l_int|0
)paren
(brace
id|state
op_xor_assign
l_int|0x100
suffix:semicolon
id|count
op_assign
l_int|25
suffix:semicolon
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|LED_ADDRESS
)paren
op_assign
id|state
suffix:semicolon
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|clps7500_timer_irq
r_static
r_struct
id|irqaction
id|clps7500_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CLPS7500 Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|clps7500_timer_interrupt
)brace
suffix:semicolon
multiline_comment|/*&n; * Set up timer interrupt.&n; */
DECL|function|clps7500_timer_init
r_static
r_void
id|__init
id|clps7500_timer_init
c_func
(paren
r_void
)paren
(brace
id|ioctime_init
c_func
(paren
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_TIMER
comma
op_amp
id|clps7500_timer_irq
)paren
suffix:semicolon
)brace
r_static
r_struct
id|clps7500_timer
op_assign
(brace
dot
id|init
op_assign
id|clps7500_timer_init
comma
dot
id|offset
op_assign
id|ioc_timer_gettimeoffset
comma
)brace
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|CLPS7500
comma
l_string|&quot;CL-PS7500&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Philip Blundell&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0x03000000
comma
l_int|0xe0000000
)paren
id|MAPIO
c_func
(paren
id|clps7500_map_io
)paren
id|INITIRQ
c_func
(paren
id|clps7500_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|clps7500_timer
comma
id|MACHINE_END
eof
