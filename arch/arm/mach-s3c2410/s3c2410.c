multiline_comment|/* linux/arch/arm/mach-s3c2410/s3c2410.c&n; *&n; * Copyright (c) 2003,2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.simtec.co.uk/products/EB2410ITX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     16-May-2003 BJD  Created initial version&n; *     16-Aug-2003 BJD  Fixed header files and copyright, added URL&n; *     05-Sep-2003 BJD  Moved to kernel v2.6&n; *     18-Jan-2004 BJD  Added serial port configuration&n; *     21-Aug-2004 BJD  Added new struct s3c2410_board handler&n; *     28-Sep-2004 BJD  Updates for new serial port bits&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/regs-clock.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &quot;s3c2410.h&quot;
macro_line|#include &quot;cpu.h&quot;
macro_line|#include &quot;clock.h&quot;
DECL|variable|s3c2410_clock_tick_rate
r_int
id|s3c2410_clock_tick_rate
op_assign
l_int|12
op_star
l_int|1000
op_star
l_int|1000
suffix:semicolon
multiline_comment|/* current timers at 12MHz */
multiline_comment|/* serial port setup */
DECL|variable|s3c2410_uartcfgs
r_struct
id|s3c2410_uartcfg
op_star
id|s3c2410_uartcfgs
suffix:semicolon
multiline_comment|/* Initial IO mappings */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|s3c2410_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
id|IODESC_ENT
c_func
(paren
id|USBHOST
)paren
comma
id|IODESC_ENT
c_func
(paren
id|CLKPWR
)paren
comma
id|IODESC_ENT
c_func
(paren
id|LCD
)paren
comma
id|IODESC_ENT
c_func
(paren
id|UART
)paren
comma
id|IODESC_ENT
c_func
(paren
id|TIMER
)paren
comma
id|IODESC_ENT
c_func
(paren
id|ADC
)paren
comma
id|IODESC_ENT
c_func
(paren
id|WATCHDOG
)paren
)brace
suffix:semicolon
DECL|variable|s3c_uart0_resource
r_static
r_struct
id|resource
id|s3c_uart0_resource
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
id|S3C2410_PA_UART0
comma
dot
id|end
op_assign
id|S3C2410_PA_UART0
op_plus
l_int|0x3fff
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
id|IRQ_S3CUART_RX0
comma
dot
id|end
op_assign
id|IRQ_S3CUART_ERR0
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_uart1_resource
r_static
r_struct
id|resource
id|s3c_uart1_resource
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
id|S3C2410_PA_UART1
comma
dot
id|end
op_assign
id|S3C2410_PA_UART1
op_plus
l_int|0x3fff
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
id|IRQ_S3CUART_RX1
comma
dot
id|end
op_assign
id|IRQ_S3CUART_ERR1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_uart2_resource
r_static
r_struct
id|resource
id|s3c_uart2_resource
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
id|S3C2410_PA_UART2
comma
dot
id|end
op_assign
id|S3C2410_PA_UART2
op_plus
l_int|0x3fff
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
id|IRQ_S3CUART_RX2
comma
dot
id|end
op_assign
id|IRQ_S3CUART_ERR2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
multiline_comment|/* our uart devices */
DECL|variable|s3c_uart0
r_static
r_struct
id|platform_device
id|s3c_uart0
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-uart&quot;
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
id|s3c_uart0_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_uart0_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_uart1
r_static
r_struct
id|platform_device
id|s3c_uart1
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-uart&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_uart1_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_uart1_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_uart2
r_static
r_struct
id|platform_device
id|s3c_uart2
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-uart&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_uart2_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_uart2_resource
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|uart_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|s3c_uart0
comma
op_amp
id|s3c_uart1
comma
op_amp
id|s3c_uart2
)brace
suffix:semicolon
multiline_comment|/* store our uart devices for the serial driver console */
DECL|variable|s3c2410_uart_devices
r_struct
id|platform_device
op_star
id|s3c2410_uart_devices
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|s3c2410_uart_count
r_static
r_int
id|s3c2410_uart_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* uart registration process */
DECL|function|s3c2410_init_uarts
r_void
id|__init
id|s3c2410_init_uarts
c_func
(paren
r_struct
id|s3c2410_uartcfg
op_star
id|cfg
comma
r_int
id|no
)paren
(brace
r_struct
id|platform_device
op_star
id|platdev
suffix:semicolon
r_int
id|uart
suffix:semicolon
id|s3c2410_uartcfgs
op_assign
id|cfg
suffix:semicolon
multiline_comment|/* compatibility */
r_for
c_loop
(paren
id|uart
op_assign
l_int|0
suffix:semicolon
id|uart
OL
id|no
suffix:semicolon
id|uart
op_increment
comma
id|cfg
op_increment
)paren
(brace
id|platdev
op_assign
id|uart_devices
(braket
id|cfg-&gt;hwport
)braket
suffix:semicolon
id|s3c2410_uart_devices
(braket
id|uart
)braket
op_assign
id|platdev
suffix:semicolon
id|platdev-&gt;dev.platform_data
op_assign
id|cfg
suffix:semicolon
)brace
id|s3c2410_uart_count
op_assign
id|uart
suffix:semicolon
)brace
multiline_comment|/* s3c2410_map_io&n; *&n; * register the standard cpu IO areas, and any passed in from the&n; * machine specific initialisation.&n; *&n; * this function also sets the initial clock frequencies from the&n; * settings passed in&n;*/
DECL|function|s3c2410_map_io
r_void
id|__init
id|s3c2410_map_io
c_func
(paren
r_struct
id|map_desc
op_star
id|mach_desc
comma
r_int
id|mach_size
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* register our io-tables */
id|iotable_init
c_func
(paren
id|s3c2410_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|s3c2410_iodesc
)paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|mach_desc
comma
id|mach_size
)paren
suffix:semicolon
multiline_comment|/* now we&squot;ve got our machine bits initialised, work out what&n;&t; * clocks we&squot;ve got */
id|s3c24xx_fclk
op_assign
id|s3c2410_get_pll
c_func
(paren
id|__raw_readl
c_func
(paren
id|S3C2410_MPLLCON
)paren
comma
id|s3c24xx_xtal
)paren
suffix:semicolon
id|tmp
op_assign
id|__raw_readl
c_func
(paren
id|S3C2410_CLKDIVN
)paren
suffix:semicolon
multiline_comment|/* work out clock scalings */
id|s3c24xx_hclk
op_assign
id|s3c24xx_fclk
op_div
(paren
(paren
id|tmp
op_amp
id|S3C2410_CLKDIVN_HDIVN
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
suffix:semicolon
id|s3c24xx_pclk
op_assign
id|s3c24xx_hclk
op_div
(paren
(paren
id|tmp
op_amp
id|S3C2410_CLKDIVN_PDIVN
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
suffix:semicolon
multiline_comment|/* print brieft summary of clocks, etc */
id|printk
c_func
(paren
l_string|&quot;S3C2410: core %ld.%03ld MHz, memory %ld.%03ld MHz, peripheral %ld.%03ld MHz&bslash;n&quot;
comma
id|print_mhz
c_func
(paren
id|s3c24xx_fclk
)paren
comma
id|print_mhz
c_func
(paren
id|s3c24xx_hclk
)paren
comma
id|print_mhz
c_func
(paren
id|s3c24xx_pclk
)paren
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_init
r_int
id|__init
id|s3c2410_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;S3C2410: Initialising architecture&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|platform_add_devices
c_func
(paren
id|uart_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|uart_devices
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
