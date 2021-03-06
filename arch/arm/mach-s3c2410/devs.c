multiline_comment|/* linux/arch/arm/mach-s3c2410/devs.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Base S3C2410 platform device definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     10-Mar-2005 LCVR Changed S3C2410_{VA,SZ} to S3C24XX_{VA,SZ}&n; *     10-Feb-2005 BJD  Added camera from guillaume.gourat@nexvision.tv&n; *     29-Aug-2004 BJD  Added timers 0 through 3&n; *     29-Aug-2004 BJD  Changed index of devices we only have one of to -1&n; *     21-Aug-2004 BJD  Added IRQ_TICK to RTC resources&n; *     18-Aug-2004 BJD  Created initial version&n;*/
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
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &quot;devs.h&quot;
multiline_comment|/* Serial port registrations */
DECL|variable|s3c24xx_uart_devs
r_struct
id|platform_device
op_star
id|s3c24xx_uart_devs
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* USB Host Controller */
DECL|variable|s3c_usb_resource
r_static
r_struct
id|resource
id|s3c_usb_resource
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
id|S3C2410_PA_USBHOST
comma
dot
id|end
op_assign
id|S3C2410_PA_USBHOST
op_plus
id|S3C24XX_SZ_USBHOST
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
id|IRQ_USBH
comma
dot
id|end
op_assign
id|IRQ_USBH
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_usb_dmamask
r_static
id|u64
id|s3c_device_usb_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|s3c_device_usb
r_struct
id|platform_device
id|s3c_device_usb
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-ohci&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_usb_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_usb_resource
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|s3c_device_usb_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffffUL
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_usb
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_usb
)paren
suffix:semicolon
multiline_comment|/* LCD Controller */
DECL|variable|s3c_lcd_resource
r_static
r_struct
id|resource
id|s3c_lcd_resource
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
id|S3C2410_PA_LCD
comma
dot
id|end
op_assign
id|S3C2410_PA_LCD
op_plus
id|S3C24XX_SZ_LCD
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
id|IRQ_LCD
comma
dot
id|end
op_assign
id|IRQ_LCD
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_lcd_dmamask
r_static
id|u64
id|s3c_device_lcd_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|s3c_device_lcd
r_struct
id|platform_device
id|s3c_device_lcd
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-lcd&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_lcd_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_lcd_resource
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|s3c_device_lcd_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffffUL
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_lcd
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_lcd
)paren
suffix:semicolon
multiline_comment|/* NAND Controller */
DECL|variable|s3c_nand_resource
r_static
r_struct
id|resource
id|s3c_nand_resource
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
id|S3C2410_PA_NAND
comma
dot
id|end
op_assign
id|S3C2410_PA_NAND
op_plus
id|S3C24XX_SZ_NAND
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_nand
r_struct
id|platform_device
id|s3c_device_nand
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-nand&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_nand_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_nand_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_nand
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_nand
)paren
suffix:semicolon
multiline_comment|/* USB Device (Gadget)*/
DECL|variable|s3c_usbgadget_resource
r_static
r_struct
id|resource
id|s3c_usbgadget_resource
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
id|S3C2410_PA_USBDEV
comma
dot
id|end
op_assign
id|S3C2410_PA_USBDEV
op_plus
id|S3C24XX_SZ_USBDEV
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
id|IRQ_USBD
comma
dot
id|end
op_assign
id|IRQ_USBD
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_usbgadget
r_struct
id|platform_device
id|s3c_device_usbgadget
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-usbgadget&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_usbgadget_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_usbgadget_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_usbgadget
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_usbgadget
)paren
suffix:semicolon
multiline_comment|/* Watchdog */
DECL|variable|s3c_wdt_resource
r_static
r_struct
id|resource
id|s3c_wdt_resource
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
id|S3C2410_PA_WATCHDOG
comma
dot
id|end
op_assign
id|S3C2410_PA_WATCHDOG
op_plus
id|S3C24XX_SZ_WATCHDOG
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
id|IRQ_WDT
comma
dot
id|end
op_assign
id|IRQ_WDT
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_wdt
r_struct
id|platform_device
id|s3c_device_wdt
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-wdt&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_wdt_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_wdt_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_wdt
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_wdt
)paren
suffix:semicolon
multiline_comment|/* I2C */
DECL|variable|s3c_i2c_resource
r_static
r_struct
id|resource
id|s3c_i2c_resource
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
id|S3C2410_PA_IIC
comma
dot
id|end
op_assign
id|S3C2410_PA_IIC
op_plus
id|S3C24XX_SZ_IIC
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
id|IRQ_IIC
comma
dot
id|end
op_assign
id|IRQ_IIC
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_i2c
r_struct
id|platform_device
id|s3c_device_i2c
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-i2c&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_i2c_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_i2c_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_i2c
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_i2c
)paren
suffix:semicolon
multiline_comment|/* IIS */
DECL|variable|s3c_iis_resource
r_static
r_struct
id|resource
id|s3c_iis_resource
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
id|S3C2410_PA_IIS
comma
dot
id|end
op_assign
id|S3C2410_PA_IIS
op_plus
id|S3C24XX_SZ_IIS
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_iis_dmamask
r_static
id|u64
id|s3c_device_iis_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|s3c_device_iis
r_struct
id|platform_device
id|s3c_device_iis
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-iis&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_iis_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_iis_resource
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|s3c_device_iis_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffffUL
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_iis
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_iis
)paren
suffix:semicolon
multiline_comment|/* RTC */
DECL|variable|s3c_rtc_resource
r_static
r_struct
id|resource
id|s3c_rtc_resource
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
id|S3C2410_PA_RTC
comma
dot
id|end
op_assign
id|S3C2410_PA_RTC
op_plus
l_int|0xff
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
id|IRQ_RTC
comma
dot
id|end
op_assign
id|IRQ_RTC
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(braket
l_int|2
)braket
op_assign
(brace
dot
id|start
op_assign
id|IRQ_TICK
comma
dot
id|end
op_assign
id|IRQ_TICK
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_rtc
r_struct
id|platform_device
id|s3c_device_rtc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-rtc&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_rtc_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_rtc_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_rtc
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_rtc
)paren
suffix:semicolon
multiline_comment|/* ADC */
DECL|variable|s3c_adc_resource
r_static
r_struct
id|resource
id|s3c_adc_resource
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
id|S3C2410_PA_ADC
comma
dot
id|end
op_assign
id|S3C2410_PA_ADC
op_plus
id|S3C24XX_SZ_ADC
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
id|IRQ_TC
comma
dot
id|end
op_assign
id|IRQ_ADC
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_adc
r_struct
id|platform_device
id|s3c_device_adc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-adc&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_adc_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_adc_resource
comma
)brace
suffix:semicolon
multiline_comment|/* SDI */
DECL|variable|s3c_sdi_resource
r_static
r_struct
id|resource
id|s3c_sdi_resource
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
id|S3C2410_PA_SDI
comma
dot
id|end
op_assign
id|S3C2410_PA_SDI
op_plus
id|S3C24XX_SZ_SDI
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
id|IRQ_SDI
comma
dot
id|end
op_assign
id|IRQ_SDI
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_sdi
r_struct
id|platform_device
id|s3c_device_sdi
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-sdi&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_sdi_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_sdi_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_sdi
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_sdi
)paren
suffix:semicolon
multiline_comment|/* SPI (0) */
DECL|variable|s3c_spi0_resource
r_static
r_struct
id|resource
id|s3c_spi0_resource
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
id|S3C2410_PA_SPI
comma
dot
id|end
op_assign
id|S3C2410_PA_SPI
op_plus
l_int|0x1f
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
id|IRQ_SPI0
comma
dot
id|end
op_assign
id|IRQ_SPI0
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_spi0
r_struct
id|platform_device
id|s3c_device_spi0
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-spi&quot;
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
id|s3c_spi0_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_spi0_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_spi0
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_spi0
)paren
suffix:semicolon
multiline_comment|/* SPI (1) */
DECL|variable|s3c_spi1_resource
r_static
r_struct
id|resource
id|s3c_spi1_resource
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
id|S3C2410_PA_SPI
op_plus
l_int|0x20
comma
dot
id|end
op_assign
id|S3C2410_PA_SPI
op_plus
l_int|0x20
op_plus
l_int|0x1f
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
id|IRQ_SPI1
comma
dot
id|end
op_assign
id|IRQ_SPI1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_spi1
r_struct
id|platform_device
id|s3c_device_spi1
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-spi&quot;
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
id|s3c_spi1_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_spi1_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_spi1
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_spi1
)paren
suffix:semicolon
multiline_comment|/* pwm timer blocks */
DECL|variable|s3c_timer0_resource
r_static
r_struct
id|resource
id|s3c_timer0_resource
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
id|S3C2410_PA_TIMER
op_plus
l_int|0x0C
comma
dot
id|end
op_assign
id|S3C2410_PA_TIMER
op_plus
l_int|0x0C
op_plus
l_int|0xB
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
id|IRQ_TIMER0
comma
dot
id|end
op_assign
id|IRQ_TIMER0
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_timer0
r_struct
id|platform_device
id|s3c_device_timer0
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-timer&quot;
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
id|s3c_timer0_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_timer0_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_timer0
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_timer0
)paren
suffix:semicolon
multiline_comment|/* timer 1 */
DECL|variable|s3c_timer1_resource
r_static
r_struct
id|resource
id|s3c_timer1_resource
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
id|S3C2410_PA_TIMER
op_plus
l_int|0x18
comma
dot
id|end
op_assign
id|S3C2410_PA_TIMER
op_plus
l_int|0x23
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
id|IRQ_TIMER1
comma
dot
id|end
op_assign
id|IRQ_TIMER1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_timer1
r_struct
id|platform_device
id|s3c_device_timer1
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-timer&quot;
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
id|s3c_timer1_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_timer1_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_timer1
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_timer1
)paren
suffix:semicolon
multiline_comment|/* timer 2 */
DECL|variable|s3c_timer2_resource
r_static
r_struct
id|resource
id|s3c_timer2_resource
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
id|S3C2410_PA_TIMER
op_plus
l_int|0x24
comma
dot
id|end
op_assign
id|S3C2410_PA_TIMER
op_plus
l_int|0x2F
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
id|IRQ_TIMER2
comma
dot
id|end
op_assign
id|IRQ_TIMER2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_timer2
r_struct
id|platform_device
id|s3c_device_timer2
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-timer&quot;
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
id|s3c_timer2_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_timer2_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_timer2
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_timer2
)paren
suffix:semicolon
multiline_comment|/* timer 3 */
DECL|variable|s3c_timer3_resource
r_static
r_struct
id|resource
id|s3c_timer3_resource
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
id|S3C2410_PA_TIMER
op_plus
l_int|0x30
comma
dot
id|end
op_assign
id|S3C2410_PA_TIMER
op_plus
l_int|0x3B
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
id|IRQ_TIMER3
comma
dot
id|end
op_assign
id|IRQ_TIMER3
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_timer3
r_struct
id|platform_device
id|s3c_device_timer3
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-timer&quot;
comma
dot
id|id
op_assign
l_int|3
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_timer3_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_timer3_resource
comma
)brace
suffix:semicolon
DECL|variable|s3c_device_timer3
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_timer3
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_S3C2440
multiline_comment|/* Camif Controller */
DECL|variable|s3c_camif_resource
r_static
r_struct
id|resource
id|s3c_camif_resource
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
id|S3C2440_PA_CAMIF
comma
dot
id|end
op_assign
id|S3C2440_PA_CAMIF
op_plus
id|S3C2440_SZ_CAMIF
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
id|IRQ_CAM
comma
dot
id|end
op_assign
id|IRQ_CAM
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_camif_dmamask
r_static
id|u64
id|s3c_device_camif_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|s3c_device_camif
r_struct
id|platform_device
id|s3c_device_camif
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2440-camif&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|s3c_camif_resource
)paren
comma
dot
id|resource
op_assign
id|s3c_camif_resource
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|s3c_device_camif_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffffUL
)brace
)brace
suffix:semicolon
DECL|variable|s3c_device_camif
id|EXPORT_SYMBOL
c_func
(paren
id|s3c_device_camif
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// CONFIG_CPU_S32440
eof
