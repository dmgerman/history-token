multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/hardware.h&n; *&n; *  Copyright (C) 1998-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains the hardware definitions of the EBSA-285.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#ifdef CONFIG_ARCH_FOOTBRIDGE
multiline_comment|/*   Virtual      Physical&t;Size&n; * 0xff800000&t;0x40000000&t;1MB&t;X-Bus&n; * 0xff000000&t;0x7c000000&t;1MB&t;PCI I/O space&n; * 0xfe000000&t;0x42000000&t;1MB&t;CSR&n; * 0xfd000000&t;0x78000000&t;1MB&t;Outbound write flush (not supported)&n; * 0xfc000000&t;0x79000000&t;1MB&t;PCI IACK/special space&n; * 0xfb000000&t;0x7a000000&t;16MB&t;PCI Config type 1&n; * 0xfa000000&t;0x7b000000&t;16MB&t;PCI Config type 0&n; * 0xf9000000&t;0x50000000&t;1MB&t;Cache flush&n; * 0xf0000000&t;0x80000000&t;16MB&t;ISA memory&n; */
DECL|macro|XBUS_SIZE
mdefine_line|#define XBUS_SIZE&t;&t;0x00100000
DECL|macro|XBUS_BASE
mdefine_line|#define XBUS_BASE&t;&t;0xff800000
DECL|macro|PCIO_SIZE
mdefine_line|#define PCIO_SIZE&t;&t;0x00100000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0xff000000
DECL|macro|ARMCSR_SIZE
mdefine_line|#define ARMCSR_SIZE&t;&t;0x00100000
DECL|macro|ARMCSR_BASE
mdefine_line|#define ARMCSR_BASE&t;&t;0xfe000000
DECL|macro|WFLUSH_SIZE
mdefine_line|#define WFLUSH_SIZE&t;&t;0x00100000
DECL|macro|WFLUSH_BASE
mdefine_line|#define WFLUSH_BASE&t;&t;0xfd000000
DECL|macro|PCIIACK_SIZE
mdefine_line|#define PCIIACK_SIZE&t;&t;0x00100000
DECL|macro|PCIIACK_BASE
mdefine_line|#define PCIIACK_BASE&t;&t;0xfc000000
DECL|macro|PCICFG1_SIZE
mdefine_line|#define PCICFG1_SIZE&t;&t;0x01000000
DECL|macro|PCICFG1_BASE
mdefine_line|#define PCICFG1_BASE&t;&t;0xfb000000
DECL|macro|PCICFG0_SIZE
mdefine_line|#define PCICFG0_SIZE&t;&t;0x01000000
DECL|macro|PCICFG0_BASE
mdefine_line|#define PCICFG0_BASE&t;&t;0xfa000000
DECL|macro|FLUSH_SIZE
mdefine_line|#define FLUSH_SIZE&t;&t;0x00100000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xf9000000
DECL|macro|PCIMEM_SIZE
mdefine_line|#define PCIMEM_SIZE&t;&t;0x01000000
DECL|macro|PCIMEM_BASE
mdefine_line|#define PCIMEM_BASE&t;&t;0xf0000000
macro_line|#elif defined(CONFIG_ARCH_CO285)
multiline_comment|/*&n; * This is the COEBSA285 cut-down mapping&n; */
DECL|macro|PCIMEM_SIZE
mdefine_line|#define PCIMEM_SIZE&t;&t;0x80000000
DECL|macro|PCIMEM_BASE
mdefine_line|#define PCIMEM_BASE&t;&t;0x80000000
DECL|macro|FLUSH_SIZE
mdefine_line|#define FLUSH_SIZE&t;&t;0x00100000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0x7e000000
DECL|macro|WFLUSH_SIZE
mdefine_line|#define WFLUSH_SIZE&t;&t;0x01000000
DECL|macro|WFLUSH_BASE
mdefine_line|#define WFLUSH_BASE&t;&t;0x7d000000
DECL|macro|ARMCSR_SIZE
mdefine_line|#define ARMCSR_SIZE&t;&t;0x00100000
DECL|macro|ARMCSR_BASE
mdefine_line|#define ARMCSR_BASE&t;&t;0x7cf00000
DECL|macro|XBUS_SIZE
mdefine_line|#define XBUS_SIZE&t;&t;0x00020000
DECL|macro|XBUS_BASE
mdefine_line|#define XBUS_BASE&t;&t;0x7cee0000
DECL|macro|PCIO_SIZE
mdefine_line|#define PCIO_SIZE&t;&t;0x00010000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0x7ced0000
macro_line|#else
macro_line|#error &quot;Undefined footbridge architecture&quot;
macro_line|#endif
DECL|macro|XBUS_LEDS
mdefine_line|#define XBUS_LEDS&t;&t;((volatile unsigned char *)(XBUS_BASE + 0x12000))
DECL|macro|XBUS_LED_AMBER
mdefine_line|#define XBUS_LED_AMBER&t;&t;(1 &lt;&lt; 0)
DECL|macro|XBUS_LED_GREEN
mdefine_line|#define XBUS_LED_GREEN&t;&t;(1 &lt;&lt; 1)
DECL|macro|XBUS_LED_RED
mdefine_line|#define XBUS_LED_RED&t;&t;(1 &lt;&lt; 2)
DECL|macro|XBUS_LED_TOGGLE
mdefine_line|#define XBUS_LED_TOGGLE&t;&t;(1 &lt;&lt; 8)
DECL|macro|XBUS_SWITCH
mdefine_line|#define XBUS_SWITCH&t;&t;((volatile unsigned char *)(XBUS_BASE + 0x12000))
DECL|macro|XBUS_SWITCH_SWITCH
mdefine_line|#define XBUS_SWITCH_SWITCH&t;((*XBUS_SWITCH) &amp; 15)
DECL|macro|XBUS_SWITCH_J17_13
mdefine_line|#define XBUS_SWITCH_J17_13&t;((*XBUS_SWITCH) &amp; (1 &lt;&lt; 4))
DECL|macro|XBUS_SWITCH_J17_11
mdefine_line|#define XBUS_SWITCH_J17_11&t;((*XBUS_SWITCH) &amp; (1 &lt;&lt; 5))
DECL|macro|XBUS_SWITCH_J17_9
mdefine_line|#define XBUS_SWITCH_J17_9&t;((*XBUS_SWITCH) &amp; (1 &lt;&lt; 6))
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x50000000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;(ARMCSR_BASE + 0x108)
multiline_comment|/* PIC irq control */
DECL|macro|PIC_LO
mdefine_line|#define PIC_LO&t;&t;&t;0x20
DECL|macro|PIC_MASK_LO
mdefine_line|#define PIC_MASK_LO&t;&t;0x21
DECL|macro|PIC_HI
mdefine_line|#define PIC_HI&t;&t;&t;0xA0
DECL|macro|PIC_MASK_HI
mdefine_line|#define PIC_MASK_HI&t;&t;0xA1
multiline_comment|/* GPIO pins */
DECL|macro|GPIO_CCLK
mdefine_line|#define GPIO_CCLK&t;&t;0x800
DECL|macro|GPIO_DSCLK
mdefine_line|#define GPIO_DSCLK&t;&t;0x400
DECL|macro|GPIO_E2CLK
mdefine_line|#define GPIO_E2CLK&t;&t;0x200
DECL|macro|GPIO_IOLOAD
mdefine_line|#define GPIO_IOLOAD&t;&t;0x100
DECL|macro|GPIO_RED_LED
mdefine_line|#define GPIO_RED_LED&t;&t;0x080
DECL|macro|GPIO_WDTIMER
mdefine_line|#define GPIO_WDTIMER&t;&t;0x040
DECL|macro|GPIO_DATA
mdefine_line|#define GPIO_DATA&t;&t;0x020
DECL|macro|GPIO_IOCLK
mdefine_line|#define GPIO_IOCLK&t;&t;0x010
DECL|macro|GPIO_DONE
mdefine_line|#define GPIO_DONE&t;&t;0x008
DECL|macro|GPIO_FAN
mdefine_line|#define GPIO_FAN&t;&t;0x004
DECL|macro|GPIO_GREEN_LED
mdefine_line|#define GPIO_GREEN_LED&t;&t;0x002
DECL|macro|GPIO_RESET
mdefine_line|#define GPIO_RESET&t;&t;0x001
multiline_comment|/* CPLD pins */
DECL|macro|CPLD_DS_ENABLE
mdefine_line|#define CPLD_DS_ENABLE&t;&t;8
DECL|macro|CPLD_7111_DISABLE
mdefine_line|#define CPLD_7111_DISABLE&t;4
DECL|macro|CPLD_UNMUTE
mdefine_line|#define CPLD_UNMUTE&t;&t;2
DECL|macro|CPLD_FLASH_WR_ENABLE
mdefine_line|#define CPLD_FLASH_WR_ENABLE&t;1
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|gpio_modify_op
c_func
(paren
r_int
id|mask
comma
r_int
id|set
)paren
suffix:semicolon
r_extern
r_void
id|gpio_modify_io
c_func
(paren
r_int
id|mask
comma
r_int
id|in
)paren
suffix:semicolon
r_extern
r_int
id|gpio_read
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpld_modify
c_func
(paren
r_int
id|mask
comma
r_int
id|set
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;1
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x6000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM &t;0x40000000
macro_line|#endif
eof
