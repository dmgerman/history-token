multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Title&t;&t;:&t;RIO Host Card Hardware Definitions&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Author&t;&t;:&t;N.P.Vassallo&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Creation&t;:&t;26th April 1999&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Version&t;&t;:&t;1.0.0&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Copyright&t;:&t;(c) Specialix International Ltd. 1999&t;*&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Description&t;:&t;Prototypes, structures and definitions&t;*/
multiline_comment|/*&t;&t;&t;&t;describing the RIO board hardware&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* History...&n;&n;1.0.0&t;26/04/99 NPV&t;Creation.&n;&n;*/
macro_line|#ifndef&t;_rioboard_h&t;&t;&t;&t;/* If RIOBOARD.H not already defined */
DECL|macro|_rioboard_h
mdefine_line|#define&t;_rioboard_h    1
multiline_comment|/*****************************************************************************&n;***********************                                ***********************&n;***********************   Hardware Control Registers   ***********************&n;***********************                                ***********************&n;*****************************************************************************/
multiline_comment|/* Hardware Registers... */
DECL|macro|RIO_REG_BASE
mdefine_line|#define&t;RIO_REG_BASE&t;0x7C00&t;&t;&t;/* Base of control registers */
DECL|macro|RIO_CONFIG
mdefine_line|#define&t;RIO_CONFIG&t;RIO_REG_BASE + 0x0000&t;/* WRITE: Configuration Register */
DECL|macro|RIO_INTSET
mdefine_line|#define&t;RIO_INTSET&t;RIO_REG_BASE + 0x0080&t;/* WRITE: Interrupt Set */
DECL|macro|RIO_RESET
mdefine_line|#define&t;RIO_RESET&t;RIO_REG_BASE + 0x0100&t;/* WRITE: Host Reset */
DECL|macro|RIO_INTRESET
mdefine_line|#define&t;RIO_INTRESET&t;RIO_REG_BASE + 0x0180&t;/* WRITE: Interrupt Reset */
DECL|macro|RIO_VPD_ROM
mdefine_line|#define&t;RIO_VPD_ROM&t;RIO_REG_BASE + 0x0000&t;/* READ: Vital Product Data ROM */
DECL|macro|RIO_INTSTAT
mdefine_line|#define&t;RIO_INTSTAT&t;RIO_REG_BASE + 0x0080&t;/* READ: Interrupt Status (Jet boards only) */
DECL|macro|RIO_RESETSTAT
mdefine_line|#define&t;RIO_RESETSTAT&t;RIO_REG_BASE + 0x0100&t;/* READ: Reset Status (Jet boards only) */
multiline_comment|/* RIO_VPD_ROM definitions... */
DECL|macro|VPD_SLX_ID1
mdefine_line|#define&t;VPD_SLX_ID1&t;0x00&t;&t;&t;/* READ: Specialix Identifier #1 */
DECL|macro|VPD_SLX_ID2
mdefine_line|#define&t;VPD_SLX_ID2&t;0x01&t;&t;&t;/* READ: Specialix Identifier #2 */
DECL|macro|VPD_HW_REV
mdefine_line|#define&t;VPD_HW_REV&t;0x02&t;&t;&t;/* READ: Hardware Revision */
DECL|macro|VPD_HW_ASSEM
mdefine_line|#define&t;VPD_HW_ASSEM&t;0x03&t;&t;&t;/* READ: Hardware Assembly Level */
DECL|macro|VPD_UNIQUEID4
mdefine_line|#define&t;VPD_UNIQUEID4&t;0x04&t;&t;&t;/* READ: Unique Identifier #4 */
DECL|macro|VPD_UNIQUEID3
mdefine_line|#define&t;VPD_UNIQUEID3&t;0x05&t;&t;&t;/* READ: Unique Identifier #3 */
DECL|macro|VPD_UNIQUEID2
mdefine_line|#define&t;VPD_UNIQUEID2&t;0x06&t;&t;&t;/* READ: Unique Identifier #2 */
DECL|macro|VPD_UNIQUEID1
mdefine_line|#define&t;VPD_UNIQUEID1&t;0x07&t;&t;&t;/* READ: Unique Identifier #1 */
DECL|macro|VPD_MANU_YEAR
mdefine_line|#define&t;VPD_MANU_YEAR&t;0x08&t;&t;&t;/* READ: Year Of Manufacture (0 = 1970) */
DECL|macro|VPD_MANU_WEEK
mdefine_line|#define&t;VPD_MANU_WEEK&t;0x09&t;&t;&t;/* READ: Week Of Manufacture (0 = week 1 Jan) */
DECL|macro|VPD_HWFEATURE1
mdefine_line|#define&t;VPD_HWFEATURE1&t;0x0A&t;&t;&t;/* READ: Hardware Feature Byte 1 */
DECL|macro|VPD_HWFEATURE2
mdefine_line|#define&t;VPD_HWFEATURE2&t;0x0B&t;&t;&t;/* READ: Hardware Feature Byte 2 */
DECL|macro|VPD_HWFEATURE3
mdefine_line|#define&t;VPD_HWFEATURE3&t;0x0C&t;&t;&t;/* READ: Hardware Feature Byte 3 */
DECL|macro|VPD_HWFEATURE4
mdefine_line|#define&t;VPD_HWFEATURE4&t;0x0D&t;&t;&t;/* READ: Hardware Feature Byte 4 */
DECL|macro|VPD_HWFEATURE5
mdefine_line|#define&t;VPD_HWFEATURE5&t;0x0E&t;&t;&t;/* READ: Hardware Feature Byte 5 */
DECL|macro|VPD_OEMID
mdefine_line|#define&t;VPD_OEMID&t;0x0F&t;&t;&t;/* READ: OEM Identifier */
DECL|macro|VPD_IDENT
mdefine_line|#define&t;VPD_IDENT&t;0x10&t;&t;&t;/* READ: Identifier string (16 bytes) */
DECL|macro|VPD_IDENT_LEN
mdefine_line|#define&t;VPD_IDENT_LEN&t;0x10
multiline_comment|/* VPD ROM Definitions... */
DECL|macro|SLX_ID1
mdefine_line|#define&t;SLX_ID1&t;&t;0x4D
DECL|macro|SLX_ID2
mdefine_line|#define&t;SLX_ID2&t;&t;0x98
DECL|macro|PRODUCT_ID
mdefine_line|#define&t;PRODUCT_ID(a)&t;((a&gt;&gt;4)&amp;0xF)&t;&t;/* Use to obtain Product ID from VPD_UNIQUEID1 */
DECL|macro|ID_SX_ISA
mdefine_line|#define&t;ID_SX_ISA&t;0x2
DECL|macro|ID_RIO_EISA
mdefine_line|#define&t;ID_RIO_EISA&t;0x3
DECL|macro|ID_SX_PCI
mdefine_line|#define&t;ID_SX_PCI&t;0x5
DECL|macro|ID_SX_EISA
mdefine_line|#define&t;ID_SX_EISA&t;0x7
DECL|macro|ID_RIO_RTA16
mdefine_line|#define&t;ID_RIO_RTA16&t;0x9
DECL|macro|ID_RIO_ISA
mdefine_line|#define&t;ID_RIO_ISA&t;0xA
DECL|macro|ID_RIO_MCA
mdefine_line|#define&t;ID_RIO_MCA&t;0xB
DECL|macro|ID_RIO_SBUS
mdefine_line|#define&t;ID_RIO_SBUS&t;0xC
DECL|macro|ID_RIO_PCI
mdefine_line|#define&t;ID_RIO_PCI&t;0xD
DECL|macro|ID_RIO_RTA8
mdefine_line|#define&t;ID_RIO_RTA8&t;0xE
multiline_comment|/* Transputer bootstrap definitions... */
DECL|macro|BOOTLOADADDR
mdefine_line|#define&t;BOOTLOADADDR&t;&t;(0x8000 - 6)
DECL|macro|BOOTINDICATE
mdefine_line|#define&t;BOOTINDICATE&t;&t;(0x8000 - 2)
multiline_comment|/* Firmware load position... */
DECL|macro|FIRMWARELOADADDR
mdefine_line|#define&t;FIRMWARELOADADDR&t;0x7C00&t;&t;/* Firmware is loaded _before_ this address */
multiline_comment|/*****************************************************************************&n;*****************************                    *****************************&n;*****************************   RIO (Rev1) ISA   *****************************&n;*****************************                    *****************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_ISA_IDENT
mdefine_line|#define&t;RIO_ISA_IDENT&t;&quot;JBJGPGGHINSMJPJR&quot;
DECL|macro|RIO_ISA_CFG_BOOTRAM
mdefine_line|#define&t;RIO_ISA_CFG_BOOTRAM&t;0x01&t;&t;/* Boot from RAM, else Link */
DECL|macro|RIO_ISA_CFG_BUSENABLE
mdefine_line|#define&t;RIO_ISA_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_ISA_CFG_IRQMASK
mdefine_line|#define&t;RIO_ISA_CFG_IRQMASK&t;0x30&t;&t;/* Interrupt mask */
DECL|macro|RIO_ISA_CFG_IRQ12
mdefine_line|#define&t;  RIO_ISA_CFG_IRQ12&t;0x10&t;&t;/* Interrupt Level 12 */
DECL|macro|RIO_ISA_CFG_IRQ11
mdefine_line|#define&t;  RIO_ISA_CFG_IRQ11&t;0x20&t;&t;/* Interrupt Level 11 */
DECL|macro|RIO_ISA_CFG_IRQ9
mdefine_line|#define&t;  RIO_ISA_CFG_IRQ9&t;0x30&t;&t;/* Interrupt Level 9 */
DECL|macro|RIO_ISA_CFG_LINK20
mdefine_line|#define&t;RIO_ISA_CFG_LINK20&t;0x40&t;&t;/* 20Mbps link, else 10Mbps */
DECL|macro|RIO_ISA_CFG_WAITSTATE0
mdefine_line|#define&t;RIO_ISA_CFG_WAITSTATE0&t;0x80&t;&t;/* 0 waitstates, else 1 */
multiline_comment|/*****************************************************************************&n;*****************************                    *****************************&n;*****************************   RIO (Rev2) ISA   *****************************&n;*****************************                    *****************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_ISA2_IDENT
mdefine_line|#define&t;RIO_ISA2_IDENT&t;&quot;JBJGPGGHINSMJPJR&quot;
DECL|macro|RIO_ISA2_CFG_BOOTRAM
mdefine_line|#define&t;RIO_ISA2_CFG_BOOTRAM&t;0x01&t;&t;/* Boot from RAM, else Link */
DECL|macro|RIO_ISA2_CFG_BUSENABLE
mdefine_line|#define&t;RIO_ISA2_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_ISA2_CFG_INTENABLE
mdefine_line|#define&t;RIO_ISA2_CFG_INTENABLE&t;0x04&t;&t;/* Interrupt enable, else disable */
DECL|macro|RIO_ISA2_CFG_16BIT
mdefine_line|#define&t;RIO_ISA2_CFG_16BIT&t;0x08&t;&t;/* 16bit mode, else 8bit */
DECL|macro|RIO_ISA2_CFG_IRQMASK
mdefine_line|#define&t;RIO_ISA2_CFG_IRQMASK&t;0x30&t;&t;/* Interrupt mask */
DECL|macro|RIO_ISA2_CFG_IRQ15
mdefine_line|#define&t;  RIO_ISA2_CFG_IRQ15&t;0x00&t;&t;/* Interrupt Level 15 */
DECL|macro|RIO_ISA2_CFG_IRQ12
mdefine_line|#define&t;  RIO_ISA2_CFG_IRQ12&t;0x10&t;&t;/* Interrupt Level 12 */
DECL|macro|RIO_ISA2_CFG_IRQ11
mdefine_line|#define&t;  RIO_ISA2_CFG_IRQ11&t;0x20&t;&t;/* Interrupt Level 11 */
DECL|macro|RIO_ISA2_CFG_IRQ9
mdefine_line|#define&t;  RIO_ISA2_CFG_IRQ9&t;0x30&t;&t;/* Interrupt Level 9 */
DECL|macro|RIO_ISA2_CFG_LINK20
mdefine_line|#define&t;RIO_ISA2_CFG_LINK20&t;0x40&t;&t;/* 20Mbps link, else 10Mbps */
DECL|macro|RIO_ISA2_CFG_WAITSTATE0
mdefine_line|#define&t;RIO_ISA2_CFG_WAITSTATE0&t;0x80&t;&t;/* 0 waitstates, else 1 */
multiline_comment|/*****************************************************************************&n;*****************************                   ******************************&n;*****************************   RIO (Jet) ISA   ******************************&n;*****************************                   ******************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_ISA3_IDENT
mdefine_line|#define&t;RIO_ISA3_IDENT&t;&quot;JET HOST BY KEV#&quot;
DECL|macro|RIO_ISA3_CFG_BUSENABLE
mdefine_line|#define&t;RIO_ISA3_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_ISA3_CFG_INTENABLE
mdefine_line|#define&t;RIO_ISA3_CFG_INTENABLE&t;0x04&t;&t;/* Interrupt enable, else disable */
DECL|macro|RIO_ISA32_CFG_IRQMASK
mdefine_line|#define&t;RIO_ISA32_CFG_IRQMASK&t;0xF30&t;&t;/* Interrupt mask */
DECL|macro|RIO_ISA3_CFG_IRQ15
mdefine_line|#define&t;  RIO_ISA3_CFG_IRQ15&t;0xF0&t;&t;/* Interrupt Level 15 */
DECL|macro|RIO_ISA3_CFG_IRQ12
mdefine_line|#define&t;  RIO_ISA3_CFG_IRQ12&t;0xC0&t;&t;/* Interrupt Level 12 */
DECL|macro|RIO_ISA3_CFG_IRQ11
mdefine_line|#define&t;  RIO_ISA3_CFG_IRQ11&t;0xB0&t;&t;/* Interrupt Level 11 */
DECL|macro|RIO_ISA3_CFG_IRQ10
mdefine_line|#define&t;  RIO_ISA3_CFG_IRQ10&t;0xA0&t;&t;/* Interrupt Level 10 */
DECL|macro|RIO_ISA3_CFG_IRQ9
mdefine_line|#define&t;  RIO_ISA3_CFG_IRQ9&t;0x90&t;&t;/* Interrupt Level 9 */
multiline_comment|/*****************************************************************************&n;*********************************             ********************************&n;*********************************   RIO MCA   ********************************&n;*********************************             ********************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_MCA_IDENT
mdefine_line|#define&t;RIO_MCA_IDENT&t;&quot;JBJGPGGHINSMJPJR&quot;
DECL|macro|RIO_MCA_CFG_BOOTRAM
mdefine_line|#define&t;RIO_MCA_CFG_BOOTRAM&t;0x01&t;&t;/* Boot from RAM, else Link */
DECL|macro|RIO_MCA_CFG_BUSENABLE
mdefine_line|#define&t;RIO_MCA_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_MCA_CFG_LINK20
mdefine_line|#define&t;RIO_MCA_CFG_LINK20&t;0x40&t;&t;/* 20Mbps link, else 10Mbps */
multiline_comment|/*****************************************************************************&n;********************************              ********************************&n;********************************   RIO EISA   ********************************&n;********************************              ********************************&n;*****************************************************************************/
multiline_comment|/* EISA Configuration Space Definitions... */
DECL|macro|EISA_PRODUCT_ID1
mdefine_line|#define&t;EISA_PRODUCT_ID1&t;0xC80
DECL|macro|EISA_PRODUCT_ID2
mdefine_line|#define&t;EISA_PRODUCT_ID2&t;0xC81
DECL|macro|EISA_PRODUCT_NUMBER
mdefine_line|#define&t;EISA_PRODUCT_NUMBER&t;0xC82
DECL|macro|EISA_REVISION_NUMBER
mdefine_line|#define&t;EISA_REVISION_NUMBER&t;0xC83
DECL|macro|EISA_CARD_ENABLE
mdefine_line|#define&t;EISA_CARD_ENABLE&t;0xC84
DECL|macro|EISA_VPD_UNIQUEID4
mdefine_line|#define&t;EISA_VPD_UNIQUEID4&t;0xC88&t;&t;/* READ: Unique Identifier #4 */
DECL|macro|EISA_VPD_UNIQUEID3
mdefine_line|#define&t;EISA_VPD_UNIQUEID3&t;0xC8A&t;&t;/* READ: Unique Identifier #3 */
DECL|macro|EISA_VPD_UNIQUEID2
mdefine_line|#define&t;EISA_VPD_UNIQUEID2&t;0xC90&t;&t;/* READ: Unique Identifier #2 */
DECL|macro|EISA_VPD_UNIQUEID1
mdefine_line|#define&t;EISA_VPD_UNIQUEID1&t;0xC92&t;&t;/* READ: Unique Identifier #1 */
DECL|macro|EISA_VPD_MANU_YEAR
mdefine_line|#define&t;EISA_VPD_MANU_YEAR&t;0xC98&t;&t;/* READ: Year Of Manufacture (0 = 1970) */
DECL|macro|EISA_VPD_MANU_WEEK
mdefine_line|#define&t;EISA_VPD_MANU_WEEK&t;0xC9A&t;&t;/* READ: Week Of Manufacture (0 = week 1 Jan) */
DECL|macro|EISA_MEM_ADDR_23_16
mdefine_line|#define&t;EISA_MEM_ADDR_23_16&t;0xC00
DECL|macro|EISA_MEM_ADDR_31_24
mdefine_line|#define&t;EISA_MEM_ADDR_31_24&t;0xC01
DECL|macro|EISA_RIO_CONFIG
mdefine_line|#define&t;EISA_RIO_CONFIG&t;&t;0xC02&t;&t;/* WRITE: Configuration Register */
DECL|macro|EISA_RIO_INTSET
mdefine_line|#define&t;EISA_RIO_INTSET&t;&t;0xC03&t;&t;/* WRITE: Interrupt Set */
DECL|macro|EISA_RIO_INTRESET
mdefine_line|#define&t;EISA_RIO_INTRESET&t;0xC03&t;&t;/* READ:  Interrupt Reset */
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_EISA_CFG_BOOTRAM
mdefine_line|#define&t;RIO_EISA_CFG_BOOTRAM&t;0x01&t;&t;/* Boot from RAM, else Link */
DECL|macro|RIO_EISA_CFG_LINK20
mdefine_line|#define&t;RIO_EISA_CFG_LINK20&t;0x02&t;&t;/* 20Mbps link, else 10Mbps */
DECL|macro|RIO_EISA_CFG_BUSENABLE
mdefine_line|#define&t;RIO_EISA_CFG_BUSENABLE&t;0x04&t;&t;/* Enable processor bus */
DECL|macro|RIO_EISA_CFG_PROCRUN
mdefine_line|#define&t;RIO_EISA_CFG_PROCRUN&t;0x08&t;&t;/* Processor running, else reset */
DECL|macro|RIO_EISA_CFG_IRQMASK
mdefine_line|#define&t;RIO_EISA_CFG_IRQMASK&t;0xF0&t;&t;/* Interrupt mask */
DECL|macro|RIO_EISA_CFG_IRQ15
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ15&t;0xF0&t;&t;/* Interrupt Level 15 */
DECL|macro|RIO_EISA_CFG_IRQ14
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ14&t;0xE0&t;&t;/* Interrupt Level 14 */
DECL|macro|RIO_EISA_CFG_IRQ12
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ12&t;0xC0&t;&t;/* Interrupt Level 12 */
DECL|macro|RIO_EISA_CFG_IRQ11
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ11&t;0xB0&t;&t;/* Interrupt Level 11 */
DECL|macro|RIO_EISA_CFG_IRQ10
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ10&t;0xA0&t;&t;/* Interrupt Level 10 */
DECL|macro|RIO_EISA_CFG_IRQ9
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ9&t;0x90&t;&t;/* Interrupt Level 9 */
DECL|macro|RIO_EISA_CFG_IRQ7
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ7&t;0x70&t;&t;/* Interrupt Level 7 */
DECL|macro|RIO_EISA_CFG_IRQ6
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ6&t;0x60&t;&t;/* Interrupt Level 6 */
DECL|macro|RIO_EISA_CFG_IRQ5
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ5&t;0x50&t;&t;/* Interrupt Level 5 */
DECL|macro|RIO_EISA_CFG_IRQ4
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ4&t;0x40&t;&t;/* Interrupt Level 4 */
DECL|macro|RIO_EISA_CFG_IRQ3
mdefine_line|#define&t;  RIO_EISA_CFG_IRQ3&t;0x30&t;&t;/* Interrupt Level 3 */
multiline_comment|/*****************************************************************************&n;********************************              ********************************&n;********************************   RIO SBus   ********************************&n;********************************              ********************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_SBUS_IDENT
mdefine_line|#define&t;RIO_SBUS_IDENT&t;&quot;JBPGK#&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
DECL|macro|RIO_SBUS_CFG_BOOTRAM
mdefine_line|#define&t;RIO_SBUS_CFG_BOOTRAM&t;0x01&t;&t;/* Boot from RAM, else Link */
DECL|macro|RIO_SBUS_CFG_BUSENABLE
mdefine_line|#define&t;RIO_SBUS_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_SBUS_CFG_INTENABLE
mdefine_line|#define&t;RIO_SBUS_CFG_INTENABLE&t;0x04&t;&t;/* Interrupt enable, else disable */
DECL|macro|RIO_SBUS_CFG_IRQMASK
mdefine_line|#define&t;RIO_SBUS_CFG_IRQMASK&t;0x38&t;&t;/* Interrupt mask */
DECL|macro|RIO_SBUS_CFG_IRQNONE
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQNONE&t;0x00&t;&t;/* No Interrupt */
DECL|macro|RIO_SBUS_CFG_IRQ7
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ7&t;0x38&t;&t;/* Interrupt Level 7 */
DECL|macro|RIO_SBUS_CFG_IRQ6
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ6&t;0x30&t;&t;/* Interrupt Level 6 */
DECL|macro|RIO_SBUS_CFG_IRQ5
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ5&t;0x28&t;&t;/* Interrupt Level 5 */
DECL|macro|RIO_SBUS_CFG_IRQ4
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ4&t;0x20&t;&t;/* Interrupt Level 4 */
DECL|macro|RIO_SBUS_CFG_IRQ3
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ3&t;0x18&t;&t;/* Interrupt Level 3 */
DECL|macro|RIO_SBUS_CFG_IRQ2
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ2&t;0x10&t;&t;/* Interrupt Level 2 */
DECL|macro|RIO_SBUS_CFG_IRQ1
mdefine_line|#define&t;  RIO_SBUS_CFG_IRQ1&t;0x08&t;&t;/* Interrupt Level 1 */
DECL|macro|RIO_SBUS_CFG_LINK20
mdefine_line|#define&t;RIO_SBUS_CFG_LINK20&t;0x40&t;&t;/* 20Mbps link, else 10Mbps */
DECL|macro|RIO_SBUS_CFG_PROC25
mdefine_line|#define&t;RIO_SBUS_CFG_PROC25&t;0x80&t;&t;/* 25Mhz processor clock, else 20Mhz */
multiline_comment|/*****************************************************************************&n;*********************************             ********************************&n;*********************************   RIO PCI   ********************************&n;*********************************             ********************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_PCI_IDENT
mdefine_line|#define&t;RIO_PCI_IDENT&t;&quot;ECDDPGJGJHJRGSK#&quot;
DECL|macro|RIO_PCI_CFG_BOOTRAM
mdefine_line|#define&t;RIO_PCI_CFG_BOOTRAM&t;0x01&t;&t;/* Boot from RAM, else Link */
DECL|macro|RIO_PCI_CFG_BUSENABLE
mdefine_line|#define&t;RIO_PCI_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_PCI_CFG_INTENABLE
mdefine_line|#define&t;RIO_PCI_CFG_INTENABLE&t;0x04&t;&t;/* Interrupt enable, else disable */
DECL|macro|RIO_PCI_CFG_LINK20
mdefine_line|#define&t;RIO_PCI_CFG_LINK20&t;0x40&t;&t;/* 20Mbps link, else 10Mbps */
DECL|macro|RIO_PCI_CFG_PROC25
mdefine_line|#define&t;RIO_PCI_CFG_PROC25&t;0x80&t;&t;/* 25Mhz processor clock, else 20Mhz */
multiline_comment|/* PCI Definitions... */
DECL|macro|SPX_VENDOR_ID
mdefine_line|#define&t;SPX_VENDOR_ID&t;&t;0x11CB&t;&t;/* Assigned by the PCI SIG */
DECL|macro|SPX_DEVICE_ID
mdefine_line|#define&t;SPX_DEVICE_ID&t;&t;0x8000&t;&t;/* RIO bridge boards */
DECL|macro|SPX_PLXDEVICE_ID
mdefine_line|#define&t;SPX_PLXDEVICE_ID&t;0x2000&t;&t;/* PLX bridge boards */
DECL|macro|SPX_SUB_VENDOR_ID
mdefine_line|#define&t;SPX_SUB_VENDOR_ID&t;SPX_VENDOR_ID&t;/* Same as vendor id */
DECL|macro|RIO_SUB_SYS_ID
mdefine_line|#define&t;RIO_SUB_SYS_ID&t;&t;0x0800&t;&t;/* RIO PCI board */
multiline_comment|/*****************************************************************************&n;*****************************                   ******************************&n;*****************************   RIO (Jet) PCI   ******************************&n;*****************************                   ******************************&n;*****************************************************************************/
multiline_comment|/* Control Register Definitions... */
DECL|macro|RIO_PCI2_IDENT
mdefine_line|#define&t;RIO_PCI2_IDENT&t;&quot;JET HOST BY KEV#&quot;
DECL|macro|RIO_PCI2_CFG_BUSENABLE
mdefine_line|#define&t;RIO_PCI2_CFG_BUSENABLE&t;0x02&t;&t;/* Enable processor bus */
DECL|macro|RIO_PCI2_CFG_INTENABLE
mdefine_line|#define&t;RIO_PCI2_CFG_INTENABLE&t;0x04&t;&t;/* Interrupt enable, else disable */
multiline_comment|/* PCI Definitions... */
DECL|macro|RIO2_SUB_SYS_ID
mdefine_line|#define&t;RIO2_SUB_SYS_ID&t;&t;0x0100&t;&t;/* RIO (Jet) PCI board */
macro_line|#endif&t;&t;&t;&t;&t;&t;/*_rioboard_h */
multiline_comment|/* End of RIOBOARD.H */
eof
