multiline_comment|/*&n; * linux/include/asm-arm/hardware/locomo.h&n; *&n; * This file contains the definitions for the LoCoMo G/A Chip&n; *&n; * (C) Copyright 2004 John Lenz&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Based on sa1111.h&n; */
macro_line|#ifndef _ASM_ARCH_LOCOMO
DECL|macro|_ASM_ARCH_LOCOMO
mdefine_line|#define _ASM_ARCH_LOCOMO
DECL|macro|locomo_writel
mdefine_line|#define locomo_writel(val,addr)&t;({ *(volatile u16 *)(addr) = (val); })
DECL|macro|locomo_readl
mdefine_line|#define locomo_readl(addr)&t;(*(volatile u16 *)(addr))
multiline_comment|/* LOCOMO version */
DECL|macro|LOCOMO_VER
mdefine_line|#define LOCOMO_VER&t;0x00
multiline_comment|/* Pin status */
DECL|macro|LOCOMO_ST
mdefine_line|#define LOCOMO_ST&t;0x04
multiline_comment|/* Pin status */
DECL|macro|LOCOMO_C32K
mdefine_line|#define LOCOMO_C32K&t;0x08
multiline_comment|/* Interrupt controller */
DECL|macro|LOCOMO_ICR
mdefine_line|#define LOCOMO_ICR&t;0x0C
multiline_comment|/* MCS decoder for boot selecting */
DECL|macro|LOCOMO_MCSX0
mdefine_line|#define LOCOMO_MCSX0&t;0x10
DECL|macro|LOCOMO_MCSX1
mdefine_line|#define LOCOMO_MCSX1&t;0x14
DECL|macro|LOCOMO_MCSX2
mdefine_line|#define LOCOMO_MCSX2&t;0x18
DECL|macro|LOCOMO_MCSX3
mdefine_line|#define LOCOMO_MCSX3&t;0x1c
multiline_comment|/* Touch panel controller */
DECL|macro|LOCOMO_ASD
mdefine_line|#define LOCOMO_ASD&t;0x20&t;&t;/* AD start delay */
DECL|macro|LOCOMO_HSD
mdefine_line|#define LOCOMO_HSD&t;0x28&t;&t;/* HSYS delay */
DECL|macro|LOCOMO_HSC
mdefine_line|#define LOCOMO_HSC&t;0x2c&t;&t;/* HSYS period */
DECL|macro|LOCOMO_TADC
mdefine_line|#define LOCOMO_TADC&t;0x30&t;&t;/* tablet ADC clock */
multiline_comment|/* Long time timer */
DECL|macro|LOCOMO_LTC
mdefine_line|#define LOCOMO_LTC&t;0xd8&t;&t;/* LTC interrupt setting */
DECL|macro|LOCOMO_LTINT
mdefine_line|#define LOCOMO_LTINT&t;0xdc&t;&t;/* LTC interrupt */
multiline_comment|/* DAC control signal for LCD (COMADJ ) */
DECL|macro|LOCOMO_DAC
mdefine_line|#define LOCOMO_DAC&t;&t;0xe0
multiline_comment|/* DAC control */
DECL|macro|LOCOMO_DAC_SCLOEB
mdefine_line|#define&t;LOCOMO_DAC_SCLOEB&t;0x08&t;/* SCL pin output data       */
DECL|macro|LOCOMO_DAC_TEST
mdefine_line|#define&t;LOCOMO_DAC_TEST&t;&t;0x04&t;/* Test bit                  */
DECL|macro|LOCOMO_DAC_SDA
mdefine_line|#define&t;LOCOMO_DAC_SDA&t;&t;0x02&t;/* SDA pin level (read-only) */
DECL|macro|LOCOMO_DAC_SDAOEB
mdefine_line|#define&t;LOCOMO_DAC_SDAOEB&t;0x01&t;/* SDA pin output data       */
multiline_comment|/* SPI interface */
DECL|macro|LOCOMO_SPIMD
mdefine_line|#define LOCOMO_SPIMD&t;0x60&t;&t;/* SPI mode setting */
DECL|macro|LOCOMO_SPICT
mdefine_line|#define LOCOMO_SPICT&t;0x64&t;&t;/* SPI mode control */
DECL|macro|LOCOMO_SPIST
mdefine_line|#define LOCOMO_SPIST&t;0x68&t;&t;/* SPI status */
DECL|macro|LOCOMO_SPIIS
mdefine_line|#define LOCOMO_SPIIS&t;0x70&t;&t;/* SPI interrupt status */
DECL|macro|LOCOMO_SPIWE
mdefine_line|#define LOCOMO_SPIWE&t;0x74&t;&t;/* SPI interrupt status write enable */
DECL|macro|LOCOMO_SPIIE
mdefine_line|#define LOCOMO_SPIIE&t;0x78&t;&t;/* SPI interrupt enable */
DECL|macro|LOCOMO_SPIIR
mdefine_line|#define LOCOMO_SPIIR&t;0x7c&t;&t;/* SPI interrupt request */
DECL|macro|LOCOMO_SPITD
mdefine_line|#define LOCOMO_SPITD&t;0x80&t;&t;/* SPI transfer data write */
DECL|macro|LOCOMO_SPIRD
mdefine_line|#define LOCOMO_SPIRD&t;0x84&t;&t;/* SPI receive data read */
DECL|macro|LOCOMO_SPITS
mdefine_line|#define LOCOMO_SPITS&t;0x88&t;&t;/* SPI transfer data shift */
DECL|macro|LOCOMO_SPIRS
mdefine_line|#define LOCOMO_SPIRS&t;0x8C&t;&t;/* SPI receive data shift */
DECL|macro|LOCOMO_SPI_TEND
mdefine_line|#define&t;LOCOMO_SPI_TEND&t;(1 &lt;&lt; 3)&t;/* Transfer end bit */
DECL|macro|LOCOMO_SPI_OVRN
mdefine_line|#define&t;LOCOMO_SPI_OVRN&t;(1 &lt;&lt; 2)&t;/* Over Run bit */
DECL|macro|LOCOMO_SPI_RFW
mdefine_line|#define&t;LOCOMO_SPI_RFW&t;(1 &lt;&lt; 1)&t;/* write buffer bit */
DECL|macro|LOCOMO_SPI_RFR
mdefine_line|#define&t;LOCOMO_SPI_RFR&t;(1)&t;&t;/* read buffer bit */
multiline_comment|/* GPIO */
DECL|macro|LOCOMO_GPD
mdefine_line|#define LOCOMO_GPD&t;&t;0x90&t;/* GPIO direction */
DECL|macro|LOCOMO_GPE
mdefine_line|#define LOCOMO_GPE&t;&t;0x94&t;/* GPIO input enable */
DECL|macro|LOCOMO_GPL
mdefine_line|#define LOCOMO_GPL&t;&t;0x98&t;/* GPIO level */
DECL|macro|LOCOMO_GPO
mdefine_line|#define LOCOMO_GPO&t;&t;0x9c&t;/* GPIO out data setteing */
DECL|macro|LOCOMO_GRIE
mdefine_line|#define LOCOMO_GRIE&t;&t;0xa0&t;/* GPIO rise detection */
DECL|macro|LOCOMO_GFIE
mdefine_line|#define LOCOMO_GFIE&t;&t;0xa4&t;/* GPIO fall detection */
DECL|macro|LOCOMO_GIS
mdefine_line|#define LOCOMO_GIS&t;&t;0xa8&t;/* GPIO edge detection status */
DECL|macro|LOCOMO_GWE
mdefine_line|#define LOCOMO_GWE&t;&t;0xac&t;/* GPIO status write enable */
DECL|macro|LOCOMO_GIE
mdefine_line|#define LOCOMO_GIE&t;&t;0xb0&t;/* GPIO interrupt enable */
DECL|macro|LOCOMO_GIR
mdefine_line|#define LOCOMO_GIR&t;&t;0xb4&t;/* GPIO interrupt request */
DECL|macro|LOCOMO_GPIO
mdefine_line|#define&t;LOCOMO_GPIO(Nb)&t;&t;(0x01 &lt;&lt; (Nb))
DECL|macro|LOCOMO_GPIO_RTS
mdefine_line|#define LOCOMO_GPIO_RTS&t;&t;LOCOMO_GPIO(0)
DECL|macro|LOCOMO_GPIO_CTS
mdefine_line|#define LOCOMO_GPIO_CTS&t;&t;LOCOMO_GPIO(1)
DECL|macro|LOCOMO_GPIO_DSR
mdefine_line|#define LOCOMO_GPIO_DSR&t;&t;LOCOMO_GPIO(2)
DECL|macro|LOCOMO_GPIO_DTR
mdefine_line|#define LOCOMO_GPIO_DTR&t;&t;LOCOMO_GPIO(3)
DECL|macro|LOCOMO_GPIO_LCD_VSHA_ON
mdefine_line|#define LOCOMO_GPIO_LCD_VSHA_ON&t;LOCOMO_GPIO(4)
DECL|macro|LOCOMO_GPIO_LCD_VSHD_ON
mdefine_line|#define LOCOMO_GPIO_LCD_VSHD_ON&t;LOCOMO_GPIO(5)
DECL|macro|LOCOMO_GPIO_LCD_VEE_ON
mdefine_line|#define LOCOMO_GPIO_LCD_VEE_ON&t;LOCOMO_GPIO(6)
DECL|macro|LOCOMO_GPIO_LCD_MOD
mdefine_line|#define LOCOMO_GPIO_LCD_MOD&t;LOCOMO_GPIO(7)
DECL|macro|LOCOMO_GPIO_DAC_ON
mdefine_line|#define LOCOMO_GPIO_DAC_ON&t;LOCOMO_GPIO(8)
DECL|macro|LOCOMO_GPIO_FL_VR
mdefine_line|#define LOCOMO_GPIO_FL_VR&t;LOCOMO_GPIO(9)
DECL|macro|LOCOMO_GPIO_DAC_SDATA
mdefine_line|#define LOCOMO_GPIO_DAC_SDATA&t;LOCOMO_GPIO(10)
DECL|macro|LOCOMO_GPIO_DAC_SCK
mdefine_line|#define LOCOMO_GPIO_DAC_SCK&t;LOCOMO_GPIO(11)
DECL|macro|LOCOMO_GPIO_DAC_SLOAD
mdefine_line|#define LOCOMO_GPIO_DAC_SLOAD&t;LOCOMO_GPIO(12)
multiline_comment|/* Start the definitions of the devices.  Each device has an initial&n; * base address and a series of offsets from that base address. */
multiline_comment|/* Keyboard controller */
DECL|macro|LOCOMO_KEYBOARD
mdefine_line|#define LOCOMO_KEYBOARD&t;&t;0x40
DECL|macro|LOCOMO_KIB
mdefine_line|#define LOCOMO_KIB&t;&t;0x00&t;/* KIB level */
DECL|macro|LOCOMO_KSC
mdefine_line|#define LOCOMO_KSC&t;&t;0x04&t;/* KSTRB control */
DECL|macro|LOCOMO_KCMD
mdefine_line|#define LOCOMO_KCMD&t;&t;0x08&t;/* KSTRB command */
DECL|macro|LOCOMO_KIC
mdefine_line|#define LOCOMO_KIC&t;&t;0x0c&t;/* Key interrupt */
multiline_comment|/* Front light adjustment controller */
DECL|macro|LOCOMO_FRONTLIGHT
mdefine_line|#define LOCOMO_FRONTLIGHT&t;0xc8
DECL|macro|LOCOMO_ALS
mdefine_line|#define LOCOMO_ALS&t;&t;0x00&t;/* Adjust light cycle */
DECL|macro|LOCOMO_ALD
mdefine_line|#define LOCOMO_ALD&t;&t;0x04&t;/* Adjust light duty */
multiline_comment|/* Backlight controller: TFT signal */
DECL|macro|LOCOMO_BACKLIGHT
mdefine_line|#define LOCOMO_BACKLIGHT&t;0x38
DECL|macro|LOCOMO_TC
mdefine_line|#define LOCOMO_TC&t;&t;0x00&t;&t;/* TFT control signal */
DECL|macro|LOCOMO_CPSD
mdefine_line|#define LOCOMO_CPSD&t;&t;0x04&t;&t;/* CPS delay */
multiline_comment|/* Audio controller */
DECL|macro|LOCOMO_AUDIO
mdefine_line|#define LOCOMO_AUDIO&t;&t;0x54
DECL|macro|LOCOMO_ACC
mdefine_line|#define LOCOMO_ACC&t;&t;0x00&t;/* Audio clock */
DECL|macro|LOCOMO_PAIF
mdefine_line|#define LOCOMO_PAIF&t;&t;0x7C&t;/* PCM audio interface */
multiline_comment|/* Audio clock */
DECL|macro|LOCOMO_ACC_XON
mdefine_line|#define&t;LOCOMO_ACC_XON&t;&t;0x80
DECL|macro|LOCOMO_ACC_XEN
mdefine_line|#define&t;LOCOMO_ACC_XEN&t;&t;0x40
DECL|macro|LOCOMO_ACC_XSEL0
mdefine_line|#define&t;LOCOMO_ACC_XSEL0&t;0x00
DECL|macro|LOCOMO_ACC_XSEL1
mdefine_line|#define&t;LOCOMO_ACC_XSEL1&t;0x20
DECL|macro|LOCOMO_ACC_MCLKEN
mdefine_line|#define&t;LOCOMO_ACC_MCLKEN&t;0x10
DECL|macro|LOCOMO_ACC_64FSEN
mdefine_line|#define&t;LOCOMO_ACC_64FSEN&t;0x08
DECL|macro|LOCOMO_ACC_CLKSEL000
mdefine_line|#define&t;LOCOMO_ACC_CLKSEL000&t;0x00&t;/* mclk  2 */
DECL|macro|LOCOMO_ACC_CLKSEL001
mdefine_line|#define&t;LOCOMO_ACC_CLKSEL001&t;0x01&t;/* mclk  3 */
DECL|macro|LOCOMO_ACC_CLKSEL010
mdefine_line|#define&t;LOCOMO_ACC_CLKSEL010&t;0x02&t;/* mclk  4 */
DECL|macro|LOCOMO_ACC_CLKSEL011
mdefine_line|#define&t;LOCOMO_ACC_CLKSEL011&t;0x03&t;/* mclk  6 */
DECL|macro|LOCOMO_ACC_CLKSEL100
mdefine_line|#define&t;LOCOMO_ACC_CLKSEL100&t;0x04&t;/* mclk  8 */
DECL|macro|LOCOMO_ACC_CLKSEL101
mdefine_line|#define&t;LOCOMO_ACC_CLKSEL101&t;0x05&t;/* mclk 12 */
multiline_comment|/* PCM audio interface */
DECL|macro|LOCOMO_PAIF_SCINV
mdefine_line|#define&t;LOCOMO_PAIF_SCINV&t;0x20
DECL|macro|LOCOMO_PAIF_SCEN
mdefine_line|#define&t;LOCOMO_PAIF_SCEN&t;0x10
DECL|macro|LOCOMO_PAIF_LRCRST
mdefine_line|#define&t;LOCOMO_PAIF_LRCRST&t;0x08
DECL|macro|LOCOMO_PAIF_LRCEVE
mdefine_line|#define&t;LOCOMO_PAIF_LRCEVE&t;0x04
DECL|macro|LOCOMO_PAIF_LRCINV
mdefine_line|#define&t;LOCOMO_PAIF_LRCINV&t;0x02
DECL|macro|LOCOMO_PAIF_LRCEN
mdefine_line|#define&t;LOCOMO_PAIF_LRCEN&t;0x01
multiline_comment|/* LED controller */
DECL|macro|LOCOMO_LED
mdefine_line|#define LOCOMO_LED&t;&t;0xe8
DECL|macro|LOCOMO_LPT0
mdefine_line|#define LOCOMO_LPT0&t;&t;0x00
DECL|macro|LOCOMO_LPT1
mdefine_line|#define LOCOMO_LPT1&t;&t;0x04
multiline_comment|/* LED control */
DECL|macro|LOCOMO_LPT_TOFH
mdefine_line|#define LOCOMO_LPT_TOFH&t;&t;0x80
DECL|macro|LOCOMO_LPT_TOFL
mdefine_line|#define LOCOMO_LPT_TOFL&t;&t;0x08
DECL|macro|LOCOMO_LPT_TOH
mdefine_line|#define LOCOMO_LPT_TOH(TOH)&t;((TOH &amp; 0x7) &lt;&lt; 4)
DECL|macro|LOCOMO_LPT_TOL
mdefine_line|#define LOCOMO_LPT_TOL(TOL)&t;((TOL &amp; 0x7))
r_extern
r_struct
id|bus_type
id|locomo_bus_type
suffix:semicolon
DECL|macro|LOCOMO_DEVID_KEYBOARD
mdefine_line|#define LOCOMO_DEVID_KEYBOARD&t;0
DECL|macro|LOCOMO_DEVID_FRONTLIGHT
mdefine_line|#define LOCOMO_DEVID_FRONTLIGHT&t;1
DECL|macro|LOCOMO_DEVID_BACKLIGHT
mdefine_line|#define LOCOMO_DEVID_BACKLIGHT&t;2
DECL|macro|LOCOMO_DEVID_AUDIO
mdefine_line|#define LOCOMO_DEVID_AUDIO&t;3
DECL|macro|LOCOMO_DEVID_LED
mdefine_line|#define LOCOMO_DEVID_LED&t;4
DECL|macro|LOCOMO_DEVID_UART
mdefine_line|#define LOCOMO_DEVID_UART&t;5
DECL|struct|locomo_dev
r_struct
id|locomo_dev
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|devid
r_int
r_int
id|devid
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|mapbase
r_void
op_star
id|mapbase
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|dma_mask
id|u64
id|dma_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LOCOMO_DEV
mdefine_line|#define LOCOMO_DEV(_d)&t;container_of((_d), struct locomo_dev, dev)
DECL|macro|locomo_get_drvdata
mdefine_line|#define locomo_get_drvdata(d)&t;dev_get_drvdata(&amp;(d)-&gt;dev)
DECL|macro|locomo_set_drvdata
mdefine_line|#define locomo_set_drvdata(d,p)&t;dev_set_drvdata(&amp;(d)-&gt;dev, p)
DECL|struct|locomo_driver
r_struct
id|locomo_driver
(brace
DECL|member|drv
r_struct
id|device_driver
id|drv
suffix:semicolon
DECL|member|devid
r_int
r_int
id|devid
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|locomo_dev
op_star
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|locomo_dev
op_star
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|locomo_dev
op_star
comma
id|u32
)paren
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|locomo_dev
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LOCOMO_DRV
mdefine_line|#define LOCOMO_DRV(_d)&t;container_of((_d), struct locomo_driver, drv)
DECL|macro|LOCOMO_DRIVER_NAME
mdefine_line|#define LOCOMO_DRIVER_NAME(_ldev) ((_ldev)-&gt;dev.driver-&gt;name)
r_void
id|locomo_lcd_power
c_func
(paren
r_struct
id|locomo_dev
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|locomo_driver_register
c_func
(paren
r_struct
id|locomo_driver
op_star
)paren
suffix:semicolon
r_void
id|locomo_driver_unregister
c_func
(paren
r_struct
id|locomo_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* GPIO control functions */
r_void
id|locomo_gpio_set_dir
c_func
(paren
r_struct
id|locomo_dev
op_star
id|ldev
comma
r_int
r_int
id|bits
comma
r_int
r_int
id|dir
)paren
suffix:semicolon
r_int
r_int
id|locomo_gpio_read_level
c_func
(paren
r_struct
id|locomo_dev
op_star
id|ldev
comma
r_int
r_int
id|bits
)paren
suffix:semicolon
r_int
r_int
id|locomo_gpio_read_output
c_func
(paren
r_struct
id|locomo_dev
op_star
id|ldev
comma
r_int
r_int
id|bits
)paren
suffix:semicolon
r_void
id|locomo_gpio_write
c_func
(paren
r_struct
id|locomo_dev
op_star
id|ldev
comma
r_int
r_int
id|bits
comma
r_int
r_int
id|set
)paren
suffix:semicolon
multiline_comment|/* M62332 control function */
r_void
id|locomo_m62332_senddata
c_func
(paren
r_struct
id|locomo_dev
op_star
id|ldev
comma
r_int
r_int
id|dac_data
comma
r_int
id|channel
)paren
suffix:semicolon
macro_line|#endif
eof
