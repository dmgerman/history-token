multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/gtwx5715.h&n; *&n; * Gemtek GTWX5715 Gateway (Linksys WRV54G)&n; *&n; * Copyright 2004 (c) George T. Joseph&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
macro_line|#error &quot;Do not include this directly, instead #include &lt;asm/hardware.h&gt;&quot;
macro_line|#endif
macro_line|#include &quot;irqs.h&quot;
DECL|macro|GTWX5715_GPIO0
mdefine_line|#define GTWX5715_GPIO0&t;0
DECL|macro|GTWX5715_GPIO1
mdefine_line|#define GTWX5715_GPIO1&t;1
DECL|macro|GTWX5715_GPIO2
mdefine_line|#define GTWX5715_GPIO2&t;2
DECL|macro|GTWX5715_GPIO3
mdefine_line|#define GTWX5715_GPIO3&t;3
DECL|macro|GTWX5715_GPIO4
mdefine_line|#define GTWX5715_GPIO4&t;4
DECL|macro|GTWX5715_GPIO5
mdefine_line|#define GTWX5715_GPIO5&t;5
DECL|macro|GTWX5715_GPIO6
mdefine_line|#define GTWX5715_GPIO6&t;6
DECL|macro|GTWX5715_GPIO7
mdefine_line|#define GTWX5715_GPIO7&t;7
DECL|macro|GTWX5715_GPIO8
mdefine_line|#define GTWX5715_GPIO8&t;8
DECL|macro|GTWX5715_GPIO9
mdefine_line|#define GTWX5715_GPIO9&t;9
DECL|macro|GTWX5715_GPIO10
mdefine_line|#define GTWX5715_GPIO10&t;10
DECL|macro|GTWX5715_GPIO11
mdefine_line|#define GTWX5715_GPIO11&t;11
DECL|macro|GTWX5715_GPIO12
mdefine_line|#define GTWX5715_GPIO12&t;12
DECL|macro|GTWX5715_GPIO13
mdefine_line|#define GTWX5715_GPIO13&t;13
DECL|macro|GTWX5715_GPIO14
mdefine_line|#define GTWX5715_GPIO14&t;14
DECL|macro|GTWX5715_GPIO0_IRQ
mdefine_line|#define GTWX5715_GPIO0_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO0
DECL|macro|GTWX5715_GPIO1_IRQ
mdefine_line|#define GTWX5715_GPIO1_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO1
DECL|macro|GTWX5715_GPIO2_IRQ
mdefine_line|#define GTWX5715_GPIO2_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO2
DECL|macro|GTWX5715_GPIO3_IRQ
mdefine_line|#define GTWX5715_GPIO3_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO3
DECL|macro|GTWX5715_GPIO4_IRQ
mdefine_line|#define GTWX5715_GPIO4_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO4
DECL|macro|GTWX5715_GPIO5_IRQ
mdefine_line|#define GTWX5715_GPIO5_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO5
DECL|macro|GTWX5715_GPIO6_IRQ
mdefine_line|#define GTWX5715_GPIO6_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO6
DECL|macro|GTWX5715_GPIO7_IRQ
mdefine_line|#define GTWX5715_GPIO7_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO7
DECL|macro|GTWX5715_GPIO8_IRQ
mdefine_line|#define GTWX5715_GPIO8_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO8
DECL|macro|GTWX5715_GPIO9_IRQ
mdefine_line|#define GTWX5715_GPIO9_IRQ&t;&t;&t;IRQ_IXP4XX_GPIO9
DECL|macro|GTWX5715_GPIO10_IRQ
mdefine_line|#define GTWX5715_GPIO10_IRQ&t;&t;IRQ_IXP4XX_GPIO10
DECL|macro|GTWX5715_GPIO11_IRQ
mdefine_line|#define GTWX5715_GPIO11_IRQ&t;&t;IRQ_IXP4XX_GPIO11
DECL|macro|GTWX5715_GPIO12_IRQ
mdefine_line|#define GTWX5715_GPIO12_IRQ&t;&t;IRQ_IXP4XX_GPIO12
DECL|macro|GTWX5715_GPIO13_IRQ
mdefine_line|#define GTWX5715_GPIO13_IRQ&t;&t;IRQ_IXP4XX_SW_INT1
DECL|macro|GTWX5715_GPIO14_IRQ
mdefine_line|#define GTWX5715_GPIO14_IRQ&t;&t;IRQ_IXP4XX_SW_INT2
DECL|macro|GTWX5715_FLASH_BASE
mdefine_line|#define&t;GTWX5715_FLASH_BASE&t;IXP4XX_EXP_BUS_CS0_BASE_PHYS
DECL|macro|GTWX5715_FLASH_SIZE
mdefine_line|#define&t;GTWX5715_FLASH_SIZE&t;(0x00800000)
multiline_comment|/* PCI controller GPIO to IRQ pin mappings&n;&n;&t;&t;&t;INTA&t;INTB&n;SLOT 0&t;10&t;&t;11&n;SLOT 1&t;11&t;&t;10&n;&n;*/
DECL|macro|GTWX5715_PCI_SLOT0_DEVID
mdefine_line|#define&t;GTWX5715_PCI_SLOT0_DEVID&t;0
DECL|macro|GTWX5715_PCI_SLOT0_INTA_GPIO
mdefine_line|#define&t;GTWX5715_PCI_SLOT0_INTA_GPIO&t;GTWX5715_GPIO10
DECL|macro|GTWX5715_PCI_SLOT0_INTB_GPIO
mdefine_line|#define&t;GTWX5715_PCI_SLOT0_INTB_GPIO&t;GTWX5715_GPIO11
DECL|macro|GTWX5715_PCI_SLOT0_INTA_IRQ
mdefine_line|#define&t;GTWX5715_PCI_SLOT0_INTA_IRQ&t;GTWX5715_GPIO10_IRQ
DECL|macro|GTWX5715_PCI_SLOT0_INTB_IRQ
mdefine_line|#define&t;GTWX5715_PCI_SLOT0_INTB_IRQ&t;GTWX5715_GPIO11_IRQ
DECL|macro|GTWX5715_PCI_SLOT1_DEVID
mdefine_line|#define&t;GTWX5715_PCI_SLOT1_DEVID&t;1
DECL|macro|GTWX5715_PCI_SLOT1_INTA_GPIO
mdefine_line|#define&t;GTWX5715_PCI_SLOT1_INTA_GPIO&t;GTWX5715_GPIO11
DECL|macro|GTWX5715_PCI_SLOT1_INTB_GPIO
mdefine_line|#define&t;GTWX5715_PCI_SLOT1_INTB_GPIO&t;GTWX5715_GPIO10
DECL|macro|GTWX5715_PCI_SLOT1_INTA_IRQ
mdefine_line|#define&t;GTWX5715_PCI_SLOT1_INTA_IRQ&t;GTWX5715_GPIO11_IRQ
DECL|macro|GTWX5715_PCI_SLOT1_INTB_IRQ
mdefine_line|#define&t;GTWX5715_PCI_SLOT1_INTB_IRQ&t;GTWX5715_GPIO10_IRQ
DECL|macro|GTWX5715_PCI_SLOT_COUNT
mdefine_line|#define GTWX5715_PCI_SLOT_COUNT&t;&t;&t;2
DECL|macro|GTWX5715_PCI_INT_PIN_COUNT
mdefine_line|#define GTWX5715_PCI_INT_PIN_COUNT&t;&t;2
multiline_comment|/*&n; * GPIO 5,6,7 and12 are hard wired to the Kendin KS8995M Switch&n; * and operate as an SPI type interface.  The details of the interface&n; * are available on Kendin/Micrel&squot;s web site.&n; */
DECL|macro|GTWX5715_KSSPI_SELECT
mdefine_line|#define GTWX5715_KSSPI_SELECT&t;GTWX5715_GPIO5
DECL|macro|GTWX5715_KSSPI_TXD
mdefine_line|#define GTWX5715_KSSPI_TXD&t;&t;GTWX5715_GPIO6
DECL|macro|GTWX5715_KSSPI_CLOCK
mdefine_line|#define GTWX5715_KSSPI_CLOCK&t;GTWX5715_GPIO7
DECL|macro|GTWX5715_KSSPI_RXD
mdefine_line|#define GTWX5715_KSSPI_RXD&t;&t;GTWX5715_GPIO12
multiline_comment|/*&n; * The &quot;reset&quot; button is wired to GPIO 3.&n; * The GPIO is brought &quot;low&quot; when the button is pushed.&n; */
DECL|macro|GTWX5715_BUTTON_GPIO
mdefine_line|#define GTWX5715_BUTTON_GPIO&t;GTWX5715_GPIO3
DECL|macro|GTWX5715_BUTTON_IRQ
mdefine_line|#define GTWX5715_BUTTON_IRQ&t;GTWX5715_GPIO3_IRQ
multiline_comment|/*&n; *  Board Label      Front Label&n; *  LED1             Power&n; *  LED2             Wireless-G&n; *  LED3             not populated but could be&n; *  LED4             Internet&n; *  LED5 - LED8      Controlled by KS8995M Switch&n; *  LED9             DMZ&n; */
DECL|macro|GTWX5715_LED1_GPIO
mdefine_line|#define GTWX5715_LED1_GPIO&t;&t;GTWX5715_GPIO2
DECL|macro|GTWX5715_LED2_GPIO
mdefine_line|#define GTWX5715_LED2_GPIO&t;&t;GTWX5715_GPIO9
DECL|macro|GTWX5715_LED3_GPIO
mdefine_line|#define GTWX5715_LED3_GPIO&t;&t;GTWX5715_GPIO8
DECL|macro|GTWX5715_LED4_GPIO
mdefine_line|#define GTWX5715_LED4_GPIO&t;&t;GTWX5715_GPIO1
DECL|macro|GTWX5715_LED9_GPIO
mdefine_line|#define GTWX5715_LED9_GPIO&t;&t;GTWX5715_GPIO4
eof
