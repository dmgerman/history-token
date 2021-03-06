multiline_comment|/*&n; *  linux/arch/arm/mach-ebsa110/core.c&n; *&n; *  Copyright (C) 1998-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Extra MM routines for the EBSA-110 architecture&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/serial_8250.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;&t;0xfe000000&t;/* read */
DECL|macro|IRQ_MSET
mdefine_line|#define IRQ_MSET&t;&t;0xfe000000&t;/* write */
DECL|macro|IRQ_STAT
mdefine_line|#define IRQ_STAT&t;&t;0xff000000&t;/* read */
DECL|macro|IRQ_MCLR
mdefine_line|#define IRQ_MCLR&t;&t;0xff000000&t;/* write */
DECL|function|ebsa110_mask_irq
r_static
r_void
id|ebsa110_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|__raw_writeb
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|IRQ_MCLR
)paren
suffix:semicolon
)brace
DECL|function|ebsa110_unmask_irq
r_static
r_void
id|ebsa110_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|__raw_writeb
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|IRQ_MSET
)paren
suffix:semicolon
)brace
DECL|variable|ebsa110_irq_chip
r_static
r_struct
id|irqchip
id|ebsa110_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|ebsa110_mask_irq
comma
dot
id|mask
op_assign
id|ebsa110_mask_irq
comma
dot
id|unmask
op_assign
id|ebsa110_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|ebsa110_init_irq
r_static
r_void
id|__init
id|ebsa110_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0xff
comma
id|IRQ_MCLR
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0x55
comma
id|IRQ_MSET
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0x00
comma
id|IRQ_MSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__raw_readb
c_func
(paren
id|IRQ_MASK
)paren
op_ne
l_int|0x55
)paren
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0xff
comma
id|IRQ_MCLR
)paren
suffix:semicolon
multiline_comment|/* clear all interrupt enables */
id|local_irq_restore
c_func
(paren
id|flags
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
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|ebsa110_irq_chip
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
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ebsa110_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*&n;&t; * sparse external-decode ISAIO space&n;&t; */
(brace
id|IRQ_STAT
comma
id|TRICK4_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IRQ_STAT/IRQ_MCLR */
(brace
id|IRQ_MASK
comma
id|TRICK3_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IRQ_MASK/IRQ_MSET */
(brace
id|SOFT_BASE
comma
id|TRICK1_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* SOFT_BASE */
(brace
id|PIT_BASE
comma
id|TRICK0_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* PIT_BASE */
multiline_comment|/*&n;&t; * self-decode ISAIO space&n;&t; */
(brace
id|ISAIO_BASE
comma
id|ISAIO_PHYS
comma
id|ISAIO_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|ISAMEM_BASE
comma
id|ISAMEM_PHYS
comma
id|ISAMEM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|ebsa110_map_io
r_static
r_void
id|__init
id|ebsa110_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|ebsa110_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ebsa110_io_desc
)paren
)paren
suffix:semicolon
)brace
DECL|macro|PIT_CTRL
mdefine_line|#define PIT_CTRL&t;&t;(PIT_BASE + 0x0d)
DECL|macro|PIT_T2
mdefine_line|#define PIT_T2&t;&t;&t;(PIT_BASE + 0x09)
DECL|macro|PIT_T1
mdefine_line|#define PIT_T1&t;&t;&t;(PIT_BASE + 0x05)
DECL|macro|PIT_T0
mdefine_line|#define PIT_T0&t;&t;&t;(PIT_BASE + 0x01)
multiline_comment|/*&n; * This is the rate at which your MCLK signal toggles (in Hz)&n; * This was measured on a 10 digit frequency counter sampling&n; * over 1 second.&n; */
DECL|macro|MCLK
mdefine_line|#define MCLK&t;47894000
multiline_comment|/*&n; * This is the rate at which the PIT timers get clocked&n; */
DECL|macro|CLKBY7
mdefine_line|#define CLKBY7&t;(MCLK / 7)
multiline_comment|/*&n; * This is the counter value.  We tick at 200Hz on this platform.&n; */
DECL|macro|COUNT
mdefine_line|#define COUNT&t;((CLKBY7 + (HZ / 2)) / HZ)
multiline_comment|/*&n; * Get the time offset from the system PIT.  Note that if we have missed an&n; * interrupt, then the PIT counter will roll over (ie, be negative).&n; * This actually works out to be convenient.&n; */
DECL|function|ebsa110_gettimeoffset
r_static
r_int
r_int
id|ebsa110_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
comma
id|count
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0x40
comma
id|PIT_CTRL
)paren
suffix:semicolon
id|count
op_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
suffix:semicolon
id|count
op_or_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/*&n;&t; * If count &gt; COUNT, make the number negative.&n;&t; */
r_if
c_cond
(paren
id|count
OG
id|COUNT
)paren
id|count
op_or_assign
l_int|0xffff0000
suffix:semicolon
id|offset
op_assign
id|COUNT
suffix:semicolon
id|offset
op_sub_assign
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * `offset&squot; is in units of timer counts.  Convert&n;&t; * offset to units of microseconds.&n;&t; */
id|offset
op_assign
id|offset
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
op_div
id|COUNT
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|ebsa110_timer_interrupt
id|ebsa110_timer_interrupt
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
id|u32
id|count
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* latch and read timer 1 */
id|__raw_writeb
c_func
(paren
l_int|0x40
comma
id|PIT_CTRL
)paren
suffix:semicolon
id|count
op_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
suffix:semicolon
id|count
op_or_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
op_lshift
l_int|8
suffix:semicolon
id|count
op_add_assign
id|COUNT
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|PIT_T1
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|PIT_T1
)paren
suffix:semicolon
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|ebsa110_timer_irq
r_static
r_struct
id|irqaction
id|ebsa110_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;EBSA110 Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|ebsa110_timer_interrupt
)brace
suffix:semicolon
multiline_comment|/*&n; * Set up timer interrupt.&n; */
DECL|function|ebsa110_timer_init
r_static
r_void
id|__init
id|ebsa110_timer_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Timer 1, mode 2, LSB/MSB&n;&t; */
id|__raw_writeb
c_func
(paren
l_int|0x70
comma
id|PIT_CTRL
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|COUNT
op_amp
l_int|0xff
comma
id|PIT_T1
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|COUNT
op_rshift
l_int|8
comma
id|PIT_T1
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_EBSA110_TIMER0
comma
op_amp
id|ebsa110_timer_irq
)paren
suffix:semicolon
)brace
DECL|variable|ebsa110_timer
r_static
r_struct
id|sys_timer
id|ebsa110_timer
op_assign
(brace
dot
id|init
op_assign
id|ebsa110_timer_init
comma
dot
id|offset
op_assign
id|ebsa110_gettimeoffset
comma
)brace
suffix:semicolon
DECL|variable|serial_platform_data
r_static
r_struct
id|plat_serial8250_port
id|serial_platform_data
(braket
)braket
op_assign
(brace
(brace
dot
id|iobase
op_assign
l_int|0x3f8
comma
dot
id|irq
op_assign
l_int|1
comma
dot
id|uartclk
op_assign
l_int|1843200
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|iotype
op_assign
id|UPIO_PORT
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_SKIP_TEST
comma
)brace
comma
(brace
dot
id|iobase
op_assign
l_int|0x2f8
comma
dot
id|irq
op_assign
l_int|2
comma
dot
id|uartclk
op_assign
l_int|1843200
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|iotype
op_assign
id|UPIO_PORT
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_SKIP_TEST
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|serial_device
r_static
r_struct
id|platform_device
id|serial_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial8250&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
id|serial_platform_data
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|ebsa110_init
r_static
r_int
id|__init
id|ebsa110_init
c_func
(paren
r_void
)paren
(brace
r_return
id|platform_device_register
c_func
(paren
op_amp
id|serial_device
)paren
suffix:semicolon
)brace
DECL|variable|ebsa110_init
id|arch_initcall
c_func
(paren
id|ebsa110_init
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|EBSA110
comma
l_string|&quot;EBSA110&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0xe0000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000400
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|0
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|2
)paren
id|SOFT_REBOOT
id|MAPIO
c_func
(paren
id|ebsa110_map_io
)paren
id|INITIRQ
c_func
(paren
id|ebsa110_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|ebsa110_timer
comma
id|MACHINE_END
eof
