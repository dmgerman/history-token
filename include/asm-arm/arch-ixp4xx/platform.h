multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/platform.h&n; *&n; * Constants and functions that are useful to IXP4xx platform-specific code&n; * and device drivers.&n; *&n; * Copyright (C) 2004 MontaVista Software, Inc.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
macro_line|#error &quot;Do not include this directly, instead #include &lt;asm/hardware.h&gt;&quot;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * Expansion bus memory regions&n; */
DECL|macro|IXP4XX_EXP_BUS_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_BASE_PHYS&t;(0x50000000)
DECL|macro|IXP4XX_EXP_BUS_CSX_REGION_SIZE
mdefine_line|#define&t;IXP4XX_EXP_BUS_CSX_REGION_SIZE&t;(0x01000000)
DECL|macro|IXP4XX_EXP_BUS_CS0_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS0_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x00000000)
DECL|macro|IXP4XX_EXP_BUS_CS1_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS1_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x01000000)
DECL|macro|IXP4XX_EXP_BUS_CS2_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS2_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x02000000)
DECL|macro|IXP4XX_EXP_BUS_CS3_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS3_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x03000000)
DECL|macro|IXP4XX_EXP_BUS_CS4_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS4_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x04000000)
DECL|macro|IXP4XX_EXP_BUS_CS5_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS5_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x05000000)
DECL|macro|IXP4XX_EXP_BUS_CS6_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS6_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x06000000)
DECL|macro|IXP4XX_EXP_BUS_CS7_BASE_PHYS
mdefine_line|#define IXP4XX_EXP_BUS_CS7_BASE_PHYS&t;(IXP4XX_EXP_BUS_BASE_PHYS + 0x07000000)
DECL|macro|IXP4XX_FLASH_WRITABLE
mdefine_line|#define IXP4XX_FLASH_WRITABLE&t;(0x2)
DECL|macro|IXP4XX_FLASH_DEFAULT
mdefine_line|#define IXP4XX_FLASH_DEFAULT&t;(0xbcd23c40)
DECL|macro|IXP4XX_FLASH_WRITE
mdefine_line|#define IXP4XX_FLASH_WRITE&t;(0xbcd23c42)
multiline_comment|/*&n; * Clock Speed Definitions.&n; */
DECL|macro|IXP4XX_PERIPHERAL_BUS_CLOCK
mdefine_line|#define IXP4XX_PERIPHERAL_BUS_CLOCK &t;(66) /* 66Mhzi APB BUS   */ 
DECL|macro|IXP4XX_UART_XTAL
mdefine_line|#define IXP4XX_UART_XTAL        &t;14745600
multiline_comment|/*&n; * The IXP4xx chips do not have an I2C unit, so GPIO lines are just&n; * used to &n; * Used as platform_data to provide GPIO pin information to the ixp42x&n; * I2C driver.&n; */
DECL|struct|ixp4xx_i2c_pins
r_struct
id|ixp4xx_i2c_pins
(brace
DECL|member|sda_pin
r_int
r_int
id|sda_pin
suffix:semicolon
DECL|member|scl_pin
r_int
r_int
id|scl_pin
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|sys_timer
suffix:semicolon
multiline_comment|/*&n; * Functions used by platform-level setup code&n; */
r_extern
r_void
id|ixp4xx_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ixp4xx_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ixp4xx_sys_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|ixp4xx_timer
suffix:semicolon
r_extern
r_void
id|ixp4xx_pci_preinit
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|pci_sys_data
suffix:semicolon
r_extern
r_int
id|ixp4xx_setup
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
suffix:semicolon
r_extern
r_struct
id|pci_bus
op_star
id|ixp4xx_scan_bus
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
suffix:semicolon
multiline_comment|/*&n; * GPIO-functions&n; */
multiline_comment|/*&n; * The following converted to the real HW bits the gpio_line_config&n; */
multiline_comment|/* GPIO pin types */
DECL|macro|IXP4XX_GPIO_OUT
mdefine_line|#define IXP4XX_GPIO_OUT &t;&t;0x1
DECL|macro|IXP4XX_GPIO_IN
mdefine_line|#define IXP4XX_GPIO_IN  &t;&t;0x2
DECL|macro|IXP4XX_GPIO_INTSTYLE_MASK
mdefine_line|#define IXP4XX_GPIO_INTSTYLE_MASK&t;0x7C  /* Bits [6:2] define interrupt style */
multiline_comment|/* &n; * GPIO interrupt types.&n; */
DECL|macro|IXP4XX_GPIO_ACTIVE_HIGH
mdefine_line|#define IXP4XX_GPIO_ACTIVE_HIGH&t;&t;0x4 /* Default */
DECL|macro|IXP4XX_GPIO_ACTIVE_LOW
mdefine_line|#define IXP4XX_GPIO_ACTIVE_LOW&t;&t;0x8
DECL|macro|IXP4XX_GPIO_RISING_EDGE
mdefine_line|#define IXP4XX_GPIO_RISING_EDGE&t;&t;0x10
DECL|macro|IXP4XX_GPIO_FALLING_EDGE
mdefine_line|#define IXP4XX_GPIO_FALLING_EDGE &t;0x20
DECL|macro|IXP4XX_GPIO_TRANSITIONAL
mdefine_line|#define IXP4XX_GPIO_TRANSITIONAL &t;0x40
multiline_comment|/* GPIO signal types */
DECL|macro|IXP4XX_GPIO_LOW
mdefine_line|#define IXP4XX_GPIO_LOW&t;&t;&t;0
DECL|macro|IXP4XX_GPIO_HIGH
mdefine_line|#define IXP4XX_GPIO_HIGH&t;&t;1
multiline_comment|/* GPIO Clocks */
DECL|macro|IXP4XX_GPIO_CLK_0
mdefine_line|#define IXP4XX_GPIO_CLK_0&t;&t;14
DECL|macro|IXP4XX_GPIO_CLK_1
mdefine_line|#define IXP4XX_GPIO_CLK_1&t;&t;15
r_extern
r_void
id|gpio_line_config
c_func
(paren
id|u8
id|line
comma
id|u32
id|style
)paren
suffix:semicolon
DECL|function|gpio_line_get
r_static
r_inline
r_void
id|gpio_line_get
c_func
(paren
id|u8
id|line
comma
r_int
op_star
id|value
)paren
(brace
op_star
id|value
op_assign
(paren
op_star
id|IXP4XX_GPIO_GPINR
op_rshift
id|line
)paren
op_amp
l_int|0x1
suffix:semicolon
)brace
DECL|function|gpio_line_set
r_static
r_inline
r_void
id|gpio_line_set
c_func
(paren
id|u8
id|line
comma
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
op_eq
id|IXP4XX_GPIO_HIGH
)paren
op_star
id|IXP4XX_GPIO_GPOUTR
op_or_assign
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|value
op_eq
id|IXP4XX_GPIO_LOW
)paren
op_star
id|IXP4XX_GPIO_GPOUTR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
)brace
DECL|function|gpio_line_isr_clear
r_static
r_inline
r_void
id|gpio_line_isr_clear
c_func
(paren
id|u8
id|line
)paren
(brace
op_star
id|IXP4XX_GPIO_GPISR
op_assign
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
)brace
macro_line|#endif 
singleline_comment|// __ASSEMBLY__
eof
