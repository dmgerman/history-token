multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/badge4.c&n; *&n; * BadgePAD 4 specific initialization&n; *&n; *   Tim Connors &lt;connors@hpl.hp.com&gt;&n; *   Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; *&n; * Copyright (C) 2002 Hewlett-Packard Company&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/arch/badge4.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|sa1111_resources
r_static
r_struct
id|resource
id|sa1111_resources
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
id|BADGE4_SA1111_BASE
comma
dot
id|end
op_assign
id|BADGE4_SA1111_BASE
op_plus
l_int|0x00001fff
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
id|BADGE4_IRQ_GPIO_SA1111
comma
dot
id|end
op_assign
id|BADGE4_IRQ_GPIO_SA1111
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa1111_dmamask
r_static
id|u64
id|sa1111_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|sa1111_device
r_static
r_struct
id|platform_device
id|sa1111_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa1111&quot;
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
id|dma_mask
op_assign
op_amp
id|sa1111_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffff
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa1111_resources
)paren
comma
dot
id|resource
op_assign
id|sa1111_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|sa1111_device
comma
)brace
suffix:semicolon
DECL|function|badge4_sa1111_init
r_static
r_int
id|__init
id|badge4_sa1111_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Ensure that the memory bus request/grant signals are setup,&n;&t; * and the grant is held in its inactive state&n;&t; */
id|sa1110_mb_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Probe for SA1111.&n;&t; */
r_return
id|platform_add_devices
c_func
(paren
id|devices
comma
id|ARRAY_SIZE
c_func
(paren
id|devices
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * 1 x Intel 28F320C3 Advanced+ Boot Block Flash (32 Mi bit)&n; *   Eight 4 KiW Parameter Bottom Blocks (64 KiB)&n; *   Sixty-three 32 KiW Main Blocks (4032 Ki b)&n; *&n; * &lt;or&gt;&n; *&n; * 1 x Intel 28F640C3 Advanced+ Boot Block Flash (64 Mi bit)&n; *   Eight 4 KiW Parameter Bottom Blocks (64 KiB)&n; *   One-hundred-twenty-seven 32 KiW Main Blocks (8128 Ki b)&n; */
DECL|variable|badge4_partitions
r_static
r_struct
id|mtd_partition
id|badge4_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;BLOB boot loader&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|0x0000A000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;params&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|size
op_assign
l_int|0x00006000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;root&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
)brace
)brace
suffix:semicolon
DECL|variable|badge4_flash_data
r_static
r_struct
id|flash_platform_data
id|badge4_flash_data
op_assign
(brace
dot
id|map_name
op_assign
l_string|&quot;cfi_probe&quot;
comma
dot
id|parts
op_assign
id|badge4_partitions
comma
dot
id|nr_parts
op_assign
id|ARRAY_SIZE
c_func
(paren
id|badge4_partitions
)paren
comma
)brace
suffix:semicolon
DECL|variable|badge4_flash_resource
r_static
r_struct
id|resource
id|badge4_flash_resource
op_assign
(brace
dot
id|start
op_assign
id|SA1100_CS0_PHYS
comma
dot
id|end
op_assign
id|SA1100_CS0_PHYS
op_plus
id|SZ_64M
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|five_v_on
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|function|five_v_on_setup
r_static
r_int
id|__init
id|five_v_on_setup
c_func
(paren
r_char
op_star
id|ignore
)paren
(brace
id|five_v_on
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;five_v_on&quot;
comma
id|five_v_on_setup
)paren
suffix:semicolon
DECL|function|badge4_init
r_static
r_int
id|__init
id|badge4_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_badge4
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* LCD */
id|GPCR
op_assign
(paren
id|BADGE4_GPIO_LGP2
op_or
id|BADGE4_GPIO_LGP3
op_or
id|BADGE4_GPIO_LGP4
op_or
id|BADGE4_GPIO_LGP5
op_or
id|BADGE4_GPIO_LGP6
op_or
id|BADGE4_GPIO_LGP7
op_or
id|BADGE4_GPIO_LGP8
op_or
id|BADGE4_GPIO_LGP9
op_or
id|BADGE4_GPIO_GPA_VID
op_or
id|BADGE4_GPIO_GPB_VID
op_or
id|BADGE4_GPIO_GPC_VID
)paren
suffix:semicolon
id|GPDR
op_and_assign
op_complement
id|BADGE4_GPIO_INT_VID
suffix:semicolon
id|GPDR
op_or_assign
(paren
id|BADGE4_GPIO_LGP2
op_or
id|BADGE4_GPIO_LGP3
op_or
id|BADGE4_GPIO_LGP4
op_or
id|BADGE4_GPIO_LGP5
op_or
id|BADGE4_GPIO_LGP6
op_or
id|BADGE4_GPIO_LGP7
op_or
id|BADGE4_GPIO_LGP8
op_or
id|BADGE4_GPIO_LGP9
op_or
id|BADGE4_GPIO_GPA_VID
op_or
id|BADGE4_GPIO_GPB_VID
op_or
id|BADGE4_GPIO_GPC_VID
)paren
suffix:semicolon
multiline_comment|/* SDRAM SPD i2c */
id|GPCR
op_assign
(paren
id|BADGE4_GPIO_SDSDA
op_or
id|BADGE4_GPIO_SDSCL
)paren
suffix:semicolon
id|GPDR
op_or_assign
(paren
id|BADGE4_GPIO_SDSDA
op_or
id|BADGE4_GPIO_SDSCL
)paren
suffix:semicolon
multiline_comment|/* uart */
id|GPCR
op_assign
(paren
id|BADGE4_GPIO_UART_HS1
op_or
id|BADGE4_GPIO_UART_HS2
)paren
suffix:semicolon
id|GPDR
op_or_assign
(paren
id|BADGE4_GPIO_UART_HS1
op_or
id|BADGE4_GPIO_UART_HS2
)paren
suffix:semicolon
multiline_comment|/* CPLD muxsel0 input for mux/adc chip select */
id|GPCR
op_assign
id|BADGE4_GPIO_MUXSEL0
suffix:semicolon
id|GPDR
op_or_assign
id|BADGE4_GPIO_MUXSEL0
suffix:semicolon
multiline_comment|/* test points: J5, J6 as inputs, J7 outputs */
id|GPDR
op_and_assign
op_complement
(paren
id|BADGE4_GPIO_TESTPT_J5
op_or
id|BADGE4_GPIO_TESTPT_J6
)paren
suffix:semicolon
id|GPCR
op_assign
id|BADGE4_GPIO_TESTPT_J7
suffix:semicolon
id|GPDR
op_or_assign
id|BADGE4_GPIO_TESTPT_J7
suffix:semicolon
multiline_comment|/* 5V supply rail. */
id|GPCR
op_assign
id|BADGE4_GPIO_PCMEN5V
suffix:semicolon
multiline_comment|/* initially off */
id|GPDR
op_or_assign
id|BADGE4_GPIO_PCMEN5V
suffix:semicolon
multiline_comment|/* CPLD sdram type inputs; set up by blob */
singleline_comment|//GPDR |= (BADGE4_GPIO_SDTYP1 | BADGE4_GPIO_SDTYP0);
id|printk
c_func
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: SDRAM CPLD typ1=%d typ0=%d&bslash;n&quot;
comma
op_logical_neg
op_logical_neg
(paren
id|GPLR
op_amp
id|BADGE4_GPIO_SDTYP1
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|GPLR
op_amp
id|BADGE4_GPIO_SDTYP0
)paren
)paren
suffix:semicolon
multiline_comment|/* SA1111 reset pin; set up by blob */
singleline_comment|//GPSR  = BADGE4_GPIO_SA1111_NRST;
singleline_comment|//GPDR |= BADGE4_GPIO_SA1111_NRST;
multiline_comment|/* power management cruft */
id|PGSR
op_assign
l_int|0
suffix:semicolon
id|PWER
op_assign
l_int|0
suffix:semicolon
id|PCFR
op_assign
l_int|0
suffix:semicolon
id|PSDR
op_assign
l_int|0
suffix:semicolon
id|PWER
op_or_assign
id|PWER_GPIO26
suffix:semicolon
multiline_comment|/* wake up on an edge from TESTPT_J5 */
id|PWER
op_or_assign
id|PWER_RTC
suffix:semicolon
multiline_comment|/* wake up if rtc fires */
multiline_comment|/* drive sa1111_nrst during sleep */
id|PGSR
op_or_assign
id|BADGE4_GPIO_SA1111_NRST
suffix:semicolon
multiline_comment|/* drive CPLD as is during sleep */
id|PGSR
op_or_assign
(paren
id|GPLR
op_amp
(paren
id|BADGE4_GPIO_SDTYP0
op_or
id|BADGE4_GPIO_SDTYP1
)paren
)paren
suffix:semicolon
multiline_comment|/* Now bring up the SA-1111. */
id|ret
op_assign
id|badge4_sa1111_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: SA-1111 initialization failed (%d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* maybe turn on 5v0 from the start */
id|badge4_set_5V
c_func
(paren
id|BADGE4_5V_INITIALLY
comma
id|five_v_on
)paren
suffix:semicolon
id|sa11x0_set_flash_data
c_func
(paren
op_amp
id|badge4_flash_data
comma
op_amp
id|badge4_flash_resource
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|badge4_init
id|arch_initcall
c_func
(paren
id|badge4_init
)paren
suffix:semicolon
DECL|variable|badge4_5V_bitmap
r_static
r_int
id|badge4_5V_bitmap
op_assign
l_int|0
suffix:semicolon
DECL|function|badge4_set_5V
r_void
id|badge4_set_5V
c_func
(paren
r_int
id|subsystem
comma
r_int
id|on
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|old_5V_bitmap
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|old_5V_bitmap
op_assign
id|badge4_5V_bitmap
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
id|badge4_5V_bitmap
op_or_assign
id|subsystem
suffix:semicolon
)brace
r_else
(brace
id|badge4_5V_bitmap
op_and_assign
op_complement
id|subsystem
suffix:semicolon
)brace
multiline_comment|/* detect on-&gt;off and off-&gt;on transitions */
r_if
c_cond
(paren
(paren
op_logical_neg
id|old_5V_bitmap
)paren
op_logical_and
(paren
id|badge4_5V_bitmap
)paren
)paren
(brace
multiline_comment|/* was off, now on */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: enabling 5V supply rail&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|GPSR
op_assign
id|BADGE4_GPIO_PCMEN5V
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|old_5V_bitmap
)paren
op_logical_and
(paren
op_logical_neg
id|badge4_5V_bitmap
)paren
)paren
(brace
multiline_comment|/* was on, now off */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: disabling 5V supply rail&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|GPCR
op_assign
id|BADGE4_GPIO_PCMEN5V
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|badge4_set_5V
id|EXPORT_SYMBOL
c_func
(paren
id|badge4_set_5V
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|badge4_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*  virtual    physical    length    type */
(brace
l_int|0xf1000000
comma
l_int|0x08000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* SRAM  bank 1 */
(brace
l_int|0xf2000000
comma
l_int|0x10000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* SRAM  bank 2 */
(brace
l_int|0xf4000000
comma
l_int|0x48000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
multiline_comment|/* SA-1111      */
)brace
suffix:semicolon
r_static
r_void
DECL|function|badge4_uart_pm
id|badge4_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|badge4_port_fns
id|__initdata
op_assign
(brace
singleline_comment|//.get_mctrl&t;= badge4_get_mctrl,
singleline_comment|//.set_mctrl&t;= badge4_set_mctrl,
dot
id|pm
op_assign
id|badge4_uart_pm
comma
)brace
suffix:semicolon
DECL|function|badge4_map_io
r_static
r_void
id|__init
id|badge4_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|badge4_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|badge4_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|badge4_port_fns
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|BADGE4
comma
l_string|&quot;Hewlett-Packard Laboratories BadgePAD 4&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|MAPIO
c_func
(paren
id|badge4_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|sa1100_timer
comma
id|MACHINE_END
eof
