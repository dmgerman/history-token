multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/board-innovator.h&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_INNOVATOR_H
DECL|macro|__ASM_ARCH_OMAP_INNOVATOR_H
mdefine_line|#define __ASM_ARCH_OMAP_INNOVATOR_H
macro_line|#if defined (CONFIG_ARCH_OMAP1510)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; *  OMAP-1510 FPGA&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP1510P1_FPGA_BASE
mdefine_line|#define OMAP1510P1_FPGA_BASE&t;&t;&t;0xE8000000&t;/* Virtual */
DECL|macro|OMAP1510P1_FPGA_SIZE
mdefine_line|#define OMAP1510P1_FPGA_SIZE&t;&t;&t;SZ_4K
DECL|macro|OMAP1510P1_FPGA_START
mdefine_line|#define OMAP1510P1_FPGA_START&t;&t;&t;0x08000000&t;/* Physical */
multiline_comment|/* Revision */
DECL|macro|OMAP1510P1_FPGA_REV_LOW
mdefine_line|#define OMAP1510P1_FPGA_REV_LOW&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x0)
DECL|macro|OMAP1510P1_FPGA_REV_HIGH
mdefine_line|#define OMAP1510P1_FPGA_REV_HIGH&t;&t;(OMAP1510P1_FPGA_BASE + 0x1)
DECL|macro|OMAP1510P1_FPGA_LCD_PANEL_CONTROL
mdefine_line|#define OMAP1510P1_FPGA_LCD_PANEL_CONTROL&t;(OMAP1510P1_FPGA_BASE + 0x2)
DECL|macro|OMAP1510P1_FPGA_LED_DIGIT
mdefine_line|#define OMAP1510P1_FPGA_LED_DIGIT&t;&t;(OMAP1510P1_FPGA_BASE + 0x3)
DECL|macro|INNOVATOR_FPGA_HID_SPI
mdefine_line|#define INNOVATOR_FPGA_HID_SPI&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x4)
DECL|macro|OMAP1510P1_FPGA_POWER
mdefine_line|#define OMAP1510P1_FPGA_POWER&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x5)
multiline_comment|/* Interrupt status */
DECL|macro|OMAP1510P1_FPGA_ISR_LO
mdefine_line|#define OMAP1510P1_FPGA_ISR_LO&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x6)
DECL|macro|OMAP1510P1_FPGA_ISR_HI
mdefine_line|#define OMAP1510P1_FPGA_ISR_HI&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x7)
multiline_comment|/* Interrupt mask */
DECL|macro|OMAP1510P1_FPGA_IMR_LO
mdefine_line|#define OMAP1510P1_FPGA_IMR_LO&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x8)
DECL|macro|OMAP1510P1_FPGA_IMR_HI
mdefine_line|#define OMAP1510P1_FPGA_IMR_HI&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x9)
multiline_comment|/* Reset registers */
DECL|macro|OMAP1510P1_FPGA_HOST_RESET
mdefine_line|#define OMAP1510P1_FPGA_HOST_RESET&t;&t;(OMAP1510P1_FPGA_BASE + 0xa)
DECL|macro|OMAP1510P1_FPGA_RST
mdefine_line|#define OMAP1510P1_FPGA_RST&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0xb)
DECL|macro|OMAP1510P1_FPGA_AUDIO
mdefine_line|#define OMAP1510P1_FPGA_AUDIO&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0xc)
DECL|macro|OMAP1510P1_FPGA_DIP
mdefine_line|#define OMAP1510P1_FPGA_DIP&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0xe)
DECL|macro|OMAP1510P1_FPGA_FPGA_IO
mdefine_line|#define OMAP1510P1_FPGA_FPGA_IO&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0xf)
DECL|macro|OMAP1510P1_FPGA_UART1
mdefine_line|#define OMAP1510P1_FPGA_UART1&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x14)
DECL|macro|OMAP1510P1_FPGA_UART2
mdefine_line|#define OMAP1510P1_FPGA_UART2&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x15)
DECL|macro|OMAP1510P1_FPGA_OMAP1510_STATUS
mdefine_line|#define OMAP1510P1_FPGA_OMAP1510_STATUS&t;&t;(OMAP1510P1_FPGA_BASE + 0x16)
DECL|macro|OMAP1510P1_FPGA_BOARD_REV
mdefine_line|#define OMAP1510P1_FPGA_BOARD_REV&t;&t;(OMAP1510P1_FPGA_BASE + 0x18)
DECL|macro|OMAP1510P1_PPT_DATA
mdefine_line|#define OMAP1510P1_PPT_DATA&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x100)
DECL|macro|OMAP1510P1_PPT_STATUS
mdefine_line|#define OMAP1510P1_PPT_STATUS&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x101)
DECL|macro|OMAP1510P1_PPT_CONTROL
mdefine_line|#define OMAP1510P1_PPT_CONTROL&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x102)
DECL|macro|OMAP1510P1_FPGA_TOUCHSCREEN
mdefine_line|#define OMAP1510P1_FPGA_TOUCHSCREEN&t;&t;(OMAP1510P1_FPGA_BASE + 0x204)
DECL|macro|INNOVATOR_FPGA_INFO
mdefine_line|#define INNOVATOR_FPGA_INFO&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x205)
DECL|macro|INNOVATOR_FPGA_LCD_BRIGHT_LO
mdefine_line|#define INNOVATOR_FPGA_LCD_BRIGHT_LO&t;&t;(OMAP1510P1_FPGA_BASE + 0x206)
DECL|macro|INNOVATOR_FPGA_LCD_BRIGHT_HI
mdefine_line|#define INNOVATOR_FPGA_LCD_BRIGHT_HI&t;&t;(OMAP1510P1_FPGA_BASE + 0x207)
DECL|macro|INNOVATOR_FPGA_LED_GRN_LO
mdefine_line|#define INNOVATOR_FPGA_LED_GRN_LO&t;&t;(OMAP1510P1_FPGA_BASE + 0x208)
DECL|macro|INNOVATOR_FPGA_LED_GRN_HI
mdefine_line|#define INNOVATOR_FPGA_LED_GRN_HI&t;&t;(OMAP1510P1_FPGA_BASE + 0x209)
DECL|macro|INNOVATOR_FPGA_LED_RED_LO
mdefine_line|#define INNOVATOR_FPGA_LED_RED_LO&t;&t;(OMAP1510P1_FPGA_BASE + 0x20a)
DECL|macro|INNOVATOR_FPGA_LED_RED_HI
mdefine_line|#define INNOVATOR_FPGA_LED_RED_HI&t;&t;(OMAP1510P1_FPGA_BASE + 0x20b)
DECL|macro|INNOVATOR_FPGA_CAM_USB_CONTROL
mdefine_line|#define INNOVATOR_FPGA_CAM_USB_CONTROL&t;&t;(OMAP1510P1_FPGA_BASE + 0x20c)
DECL|macro|INNOVATOR_FPGA_EXP_CONTROL
mdefine_line|#define INNOVATOR_FPGA_EXP_CONTROL&t;&t;(OMAP1510P1_FPGA_BASE + 0x20d)
DECL|macro|INNOVATOR_FPGA_ISR2
mdefine_line|#define INNOVATOR_FPGA_ISR2&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x20e)
DECL|macro|INNOVATOR_FPGA_IMR2
mdefine_line|#define INNOVATOR_FPGA_IMR2&t;&t;&t;(OMAP1510P1_FPGA_BASE + 0x210)
DECL|macro|OMAP1510P1_FPGA_ETHR_START
mdefine_line|#define OMAP1510P1_FPGA_ETHR_START&t;&t;(OMAP1510P1_FPGA_START + 0x300)
DECL|macro|OMAP1510P1_FPGA_ETHR_BASE
mdefine_line|#define OMAP1510P1_FPGA_ETHR_BASE&t;&t;(OMAP1510P1_FPGA_BASE + 0x300)
multiline_comment|/*&n; * Power up Giga UART driver, turn on HID clock.&n; * Turn off BT power, since we&squot;re not using it and it&n; * draws power.&n; */
DECL|macro|OMAP1510P1_FPGA_RESET_VALUE
mdefine_line|#define OMAP1510P1_FPGA_RESET_VALUE&t;&t;0x42
DECL|macro|OMAP1510P1_FPGA_PCR_IF_PD0
mdefine_line|#define OMAP1510P1_FPGA_PCR_IF_PD0&t;&t;(1 &lt;&lt; 7)
DECL|macro|OMAP1510P1_FPGA_PCR_COM2_EN
mdefine_line|#define OMAP1510P1_FPGA_PCR_COM2_EN&t;&t;(1 &lt;&lt; 6)
DECL|macro|OMAP1510P1_FPGA_PCR_COM1_EN
mdefine_line|#define OMAP1510P1_FPGA_PCR_COM1_EN&t;&t;(1 &lt;&lt; 5)
DECL|macro|OMAP1510P1_FPGA_PCR_EXP_PD0
mdefine_line|#define OMAP1510P1_FPGA_PCR_EXP_PD0&t;&t;(1 &lt;&lt; 4)
DECL|macro|OMAP1510P1_FPGA_PCR_EXP_PD1
mdefine_line|#define OMAP1510P1_FPGA_PCR_EXP_PD1&t;&t;(1 &lt;&lt; 3)
DECL|macro|OMAP1510P1_FPGA_PCR_48MHZ_CLK
mdefine_line|#define OMAP1510P1_FPGA_PCR_48MHZ_CLK&t;&t;(1 &lt;&lt; 2)
DECL|macro|OMAP1510P1_FPGA_PCR_4MHZ_CLK
mdefine_line|#define OMAP1510P1_FPGA_PCR_4MHZ_CLK&t;&t;(1 &lt;&lt; 1)
DECL|macro|OMAP1510P1_FPGA_PCR_RSRVD_BIT0
mdefine_line|#define OMAP1510P1_FPGA_PCR_RSRVD_BIT0&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * Innovator/OMAP1510 FPGA HID register bit definitions&n; */
DECL|macro|FPGA_HID_SCLK
mdefine_line|#define FPGA_HID_SCLK&t;(1&lt;&lt;0)&t;/* output */
DECL|macro|FPGA_HID_MOSI
mdefine_line|#define FPGA_HID_MOSI&t;(1&lt;&lt;1)&t;/* output */
DECL|macro|FPGA_HID_nSS
mdefine_line|#define FPGA_HID_nSS&t;(1&lt;&lt;2)&t;/* output 0/1 chip idle/select */
DECL|macro|FPGA_HID_nHSUS
mdefine_line|#define FPGA_HID_nHSUS&t;(1&lt;&lt;3)&t;/* output 0/1 host active/suspended */
DECL|macro|FPGA_HID_MISO
mdefine_line|#define FPGA_HID_MISO&t;(1&lt;&lt;4)&t;/* input */
DECL|macro|FPGA_HID_ATN
mdefine_line|#define FPGA_HID_ATN&t;(1&lt;&lt;5)&t;/* input  0/1 chip idle/ATN */
DECL|macro|FPGA_HID_rsrvd
mdefine_line|#define FPGA_HID_rsrvd&t;(1&lt;&lt;6)
DECL|macro|FPGA_HID_RESETn
mdefine_line|#define FPGA_HID_RESETn (1&lt;&lt;7)&t;/* output - 0/1 USAR reset/run */
macro_line|#ifndef OMAP_SDRAM_DEVICE
DECL|macro|OMAP_SDRAM_DEVICE
mdefine_line|#define OMAP_SDRAM_DEVICE&t;&t;&t;D256M_1X16_4B
macro_line|#endif
DECL|macro|OMAP1510P1_IMIF_PRI_VALUE
mdefine_line|#define OMAP1510P1_IMIF_PRI_VALUE&t;&t;0x00
DECL|macro|OMAP1510P1_EMIFS_PRI_VALUE
mdefine_line|#define OMAP1510P1_EMIFS_PRI_VALUE&t;&t;0x00
DECL|macro|OMAP1510P1_EMIFF_PRI_VALUE
mdefine_line|#define OMAP1510P1_EMIFF_PRI_VALUE&t;&t;0x00
multiline_comment|/*&n; * These definitions define an area of FLASH set aside&n; * for the use of MTD/JFFS2. This is the area of flash&n; * that a JFFS2 filesystem will reside which is mounted&n; * at boot with the &quot;root=/dev/mtdblock/0 rw&quot;&n; * command line option. The flash address used here must&n; * fall within the legal range defined by rrload for storing&n; * the filesystem component. This address will be sufficiently&n; * deep into the overall flash range to avoid the other&n; * components also stored in flash such as the bootloader,&n; * the bootloader params, and the kernel.&n; * The SW2 settings for the map below are:&n; * 1 off, 2 off, 3 on, 4 off.&n; */
multiline_comment|/* Intel flash_0, partitioned as expected by rrload */
DECL|macro|OMAP_FLASH_0_BASE
mdefine_line|#define OMAP_FLASH_0_BASE&t;0xD8000000
DECL|macro|OMAP_FLASH_0_START
mdefine_line|#define OMAP_FLASH_0_START&t;0x00000000
DECL|macro|OMAP_FLASH_0_SIZE
mdefine_line|#define OMAP_FLASH_0_SIZE&t;SZ_16M
multiline_comment|/* Intel flash_1, used for cramfs or other flash file systems */
DECL|macro|OMAP_FLASH_1_BASE
mdefine_line|#define OMAP_FLASH_1_BASE&t;0xD9000000
DECL|macro|OMAP_FLASH_1_START
mdefine_line|#define OMAP_FLASH_1_START&t;0x01000000
DECL|macro|OMAP_FLASH_1_SIZE
mdefine_line|#define OMAP_FLASH_1_SIZE&t;SZ_16M
multiline_comment|/* The FPGA IRQ is cascaded through GPIO_13 */
DECL|macro|INT_FPGA
mdefine_line|#define INT_FPGA&t;&t;(IH_GPIO_BASE + 13)
multiline_comment|/* IRQ Numbers for interrupts muxed through the FPGA */
DECL|macro|IH_FPGA_BASE
mdefine_line|#define IH_FPGA_BASE&t;&t;IH_BOARD_BASE
DECL|macro|INT_FPGA_ATN
mdefine_line|#define INT_FPGA_ATN&t;&t;(IH_FPGA_BASE + 0)
DECL|macro|INT_FPGA_ACK
mdefine_line|#define INT_FPGA_ACK&t;&t;(IH_FPGA_BASE + 1)
DECL|macro|INT_FPGA2
mdefine_line|#define INT_FPGA2&t;&t;(IH_FPGA_BASE + 2)
DECL|macro|INT_FPGA3
mdefine_line|#define INT_FPGA3&t;&t;(IH_FPGA_BASE + 3)
DECL|macro|INT_FPGA4
mdefine_line|#define INT_FPGA4&t;&t;(IH_FPGA_BASE + 4)
DECL|macro|INT_FPGA5
mdefine_line|#define INT_FPGA5&t;&t;(IH_FPGA_BASE + 5)
DECL|macro|INT_FPGA6
mdefine_line|#define INT_FPGA6&t;&t;(IH_FPGA_BASE + 6)
DECL|macro|INT_FPGA7
mdefine_line|#define INT_FPGA7&t;&t;(IH_FPGA_BASE + 7)
DECL|macro|INT_FPGA8
mdefine_line|#define INT_FPGA8&t;&t;(IH_FPGA_BASE + 8)
DECL|macro|INT_FPGA9
mdefine_line|#define INT_FPGA9&t;&t;(IH_FPGA_BASE + 9)
DECL|macro|INT_FPGA10
mdefine_line|#define INT_FPGA10&t;&t;(IH_FPGA_BASE + 10)
DECL|macro|INT_FPGA11
mdefine_line|#define INT_FPGA11&t;&t;(IH_FPGA_BASE + 11)
DECL|macro|INT_FPGA12
mdefine_line|#define INT_FPGA12&t;&t;(IH_FPGA_BASE + 12)
DECL|macro|INT_ETHER
mdefine_line|#define INT_ETHER&t;&t;(IH_FPGA_BASE + 13)
DECL|macro|INT_FPGAUART1
mdefine_line|#define INT_FPGAUART1&t;&t;(IH_FPGA_BASE + 14)
DECL|macro|INT_FPGAUART2
mdefine_line|#define INT_FPGAUART2&t;&t;(IH_FPGA_BASE + 15)
DECL|macro|INT_FPGA_TS
mdefine_line|#define INT_FPGA_TS&t;&t;(IH_FPGA_BASE + 16)
DECL|macro|INT_FPGA17
mdefine_line|#define INT_FPGA17&t;&t;(IH_FPGA_BASE + 17)
DECL|macro|INT_FPGA_CAM
mdefine_line|#define INT_FPGA_CAM&t;&t;(IH_FPGA_BASE + 18)
DECL|macro|INT_FPGA_RTC_A
mdefine_line|#define INT_FPGA_RTC_A&t;&t;(IH_FPGA_BASE + 19)
DECL|macro|INT_FPGA_RTC_B
mdefine_line|#define INT_FPGA_RTC_B&t;&t;(IH_FPGA_BASE + 20)
DECL|macro|INT_FPGA_CD
mdefine_line|#define INT_FPGA_CD&t;&t;(IH_FPGA_BASE + 21)
DECL|macro|INT_FPGA22
mdefine_line|#define INT_FPGA22&t;&t;(IH_FPGA_BASE + 22)
DECL|macro|INT_FPGA23
mdefine_line|#define INT_FPGA23&t;&t;(IH_FPGA_BASE + 23)
DECL|macro|NR_FPGA_IRQS
mdefine_line|#define NR_FPGA_IRQS&t;&t; 24
macro_line|#ifndef __ASSEMBLY__
r_void
id|fpga_write
c_func
(paren
r_int
r_char
id|val
comma
r_int
id|reg
)paren
suffix:semicolon
r_int
r_char
id|fpga_read
c_func
(paren
r_int
id|reg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* CONFIG_ARCH_OMAP1510 */
macro_line|#if defined (CONFIG_ARCH_OMAP1610)
multiline_comment|/* At OMAP1610 Innovator the Ethernet is directly connected to CS1 */
DECL|macro|OMAP1610_ETHR_BASE
mdefine_line|#define OMAP1610_ETHR_BASE&t;&t;0xE8000000
DECL|macro|OMAP1610_ETHR_SIZE
mdefine_line|#define OMAP1610_ETHR_SIZE&t;&t;SZ_4K
DECL|macro|OMAP1610_ETHR_START
mdefine_line|#define OMAP1610_ETHR_START&t;&t;0x04000000
multiline_comment|/* Intel STRATA NOR flash at CS3 */
DECL|macro|OMAP1610_NOR_FLASH_BASE
mdefine_line|#define OMAP1610_NOR_FLASH_BASE&t;&t;0xD8000000
DECL|macro|OMAP1610_NOR_FLASH_SIZE
mdefine_line|#define OMAP1610_NOR_FLASH_SIZE&t;&t;SZ_32M
DECL|macro|OMAP1610_NOR_FLASH_START
mdefine_line|#define OMAP1610_NOR_FLASH_START&t;0x0C000000
macro_line|#endif /* CONFIG_ARCH_OMAP1610 */
macro_line|#endif /* __ASM_ARCH_OMAP_INNOVATOR_H */
eof
