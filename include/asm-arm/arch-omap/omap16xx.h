multiline_comment|/* linux/include/asm-arm/arch-omap/omap16xx.h&n; *&n; * Hardware definitions for TI OMAP1610/5912/1710 processors.&n; *&n; * Cleanup for Linux-2.6 by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP16XX_H
DECL|macro|__ASM_ARCH_OMAP16XX_H
mdefine_line|#define __ASM_ARCH_OMAP16XX_H
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Base addresses&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */
DECL|macro|OMAP16XX_SRAM_BASE
mdefine_line|#define OMAP16XX_SRAM_BASE&t;0xD0000000
DECL|macro|OMAP1610_SRAM_SIZE
mdefine_line|#define OMAP1610_SRAM_SIZE&t;(SZ_16K)
DECL|macro|OMAP5912_SRAM_SIZE
mdefine_line|#define OMAP5912_SRAM_SIZE&t;0x3E800
DECL|macro|OMAP16XX_SRAM_START
mdefine_line|#define OMAP16XX_SRAM_START&t;0x20000000
DECL|macro|OMAP16XX_DSP_BASE
mdefine_line|#define OMAP16XX_DSP_BASE&t;0xE0000000
DECL|macro|OMAP16XX_DSP_SIZE
mdefine_line|#define OMAP16XX_DSP_SIZE&t;0x28000
DECL|macro|OMAP16XX_DSP_START
mdefine_line|#define OMAP16XX_DSP_START&t;0xE0000000
DECL|macro|OMAP16XX_DSPREG_BASE
mdefine_line|#define OMAP16XX_DSPREG_BASE&t;0xE1000000
DECL|macro|OMAP16XX_DSPREG_SIZE
mdefine_line|#define OMAP16XX_DSPREG_SIZE&t;SZ_128K
DECL|macro|OMAP16XX_DSPREG_START
mdefine_line|#define OMAP16XX_DSPREG_START&t;0xE1000000
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Memory used by power management&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP1610_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP1610_SRAM_IDLE_SUSPEND&t;(OMAP16XX_SRAM_BASE + OMAP1610_SRAM_SIZE - 0x200)
DECL|macro|OMAP5912_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP5912_SRAM_IDLE_SUSPEND&t;(OMAP16XX_SRAM_BASE + OMAP5912_SRAM_SIZE - 0x200)
DECL|macro|OMAP1610_SRAM_API_SUSPEND
mdefine_line|#define OMAP1610_SRAM_API_SUSPEND&t;(OMAP1610_SRAM_IDLE_SUSPEND + 0x100)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Interrupts&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP_IH2_0_BASE
mdefine_line|#define OMAP_IH2_0_BASE&t;&t;(0xfffe0000)
DECL|macro|OMAP_IH2_1_BASE
mdefine_line|#define OMAP_IH2_1_BASE&t;&t;(0xfffe0100)
DECL|macro|OMAP_IH2_2_BASE
mdefine_line|#define OMAP_IH2_2_BASE&t;&t;(0xfffe0200)
DECL|macro|OMAP_IH2_3_BASE
mdefine_line|#define OMAP_IH2_3_BASE&t;&t;(0xfffe0300)
DECL|macro|OMAP_IH2_0_ITR
mdefine_line|#define OMAP_IH2_0_ITR&t;&t;(OMAP_IH2_0_BASE + 0x00)
DECL|macro|OMAP_IH2_0_MIR
mdefine_line|#define OMAP_IH2_0_MIR&t;&t;(OMAP_IH2_0_BASE + 0x04)
DECL|macro|OMAP_IH2_0_SIR_IRQ
mdefine_line|#define OMAP_IH2_0_SIR_IRQ&t;(OMAP_IH2_0_BASE + 0x10)
DECL|macro|OMAP_IH2_0_SIR_FIQ
mdefine_line|#define OMAP_IH2_0_SIR_FIQ&t;(OMAP_IH2_0_BASE + 0x14)
DECL|macro|OMAP_IH2_0_CONTROL
mdefine_line|#define OMAP_IH2_0_CONTROL&t;(OMAP_IH2_0_BASE + 0x18)
DECL|macro|OMAP_IH2_0_ILR0
mdefine_line|#define OMAP_IH2_0_ILR0&t;&t;(OMAP_IH2_0_BASE + 0x1c)
DECL|macro|OMAP_IH2_0_ISR
mdefine_line|#define OMAP_IH2_0_ISR&t;&t;(OMAP_IH2_0_BASE + 0x9c)
DECL|macro|OMAP_IH2_1_ITR
mdefine_line|#define OMAP_IH2_1_ITR&t;&t;(OMAP_IH2_1_BASE + 0x00)
DECL|macro|OMAP_IH2_1_MIR
mdefine_line|#define OMAP_IH2_1_MIR&t;&t;(OMAP_IH2_1_BASE + 0x04)
DECL|macro|OMAP_IH2_1_SIR_IRQ
mdefine_line|#define OMAP_IH2_1_SIR_IRQ&t;(OMAP_IH2_1_BASE + 0x10)
DECL|macro|OMAP_IH2_1_SIR_FIQ
mdefine_line|#define OMAP_IH2_1_SIR_FIQ&t;(OMAP_IH2_1_BASE + 0x14)
DECL|macro|OMAP_IH2_1_CONTROL
mdefine_line|#define OMAP_IH2_1_CONTROL&t;(OMAP_IH2_1_BASE + 0x18)
DECL|macro|OMAP_IH2_1_ILR1
mdefine_line|#define OMAP_IH2_1_ILR1&t;&t;(OMAP_IH2_1_BASE + 0x1c)
DECL|macro|OMAP_IH2_1_ISR
mdefine_line|#define OMAP_IH2_1_ISR&t;&t;(OMAP_IH2_1_BASE + 0x9c)
DECL|macro|OMAP_IH2_2_ITR
mdefine_line|#define OMAP_IH2_2_ITR&t;&t;(OMAP_IH2_2_BASE + 0x00)
DECL|macro|OMAP_IH2_2_MIR
mdefine_line|#define OMAP_IH2_2_MIR&t;&t;(OMAP_IH2_2_BASE + 0x04)
DECL|macro|OMAP_IH2_2_SIR_IRQ
mdefine_line|#define OMAP_IH2_2_SIR_IRQ&t;(OMAP_IH2_2_BASE + 0x10)
DECL|macro|OMAP_IH2_2_SIR_FIQ
mdefine_line|#define OMAP_IH2_2_SIR_FIQ&t;(OMAP_IH2_2_BASE + 0x14)
DECL|macro|OMAP_IH2_2_CONTROL
mdefine_line|#define OMAP_IH2_2_CONTROL&t;(OMAP_IH2_2_BASE + 0x18)
DECL|macro|OMAP_IH2_2_ILR2
mdefine_line|#define OMAP_IH2_2_ILR2&t;&t;(OMAP_IH2_2_BASE + 0x1c)
DECL|macro|OMAP_IH2_2_ISR
mdefine_line|#define OMAP_IH2_2_ISR&t;&t;(OMAP_IH2_2_BASE + 0x9c)
DECL|macro|OMAP_IH2_3_ITR
mdefine_line|#define OMAP_IH2_3_ITR&t;&t;(OMAP_IH2_3_BASE + 0x00)
DECL|macro|OMAP_IH2_3_MIR
mdefine_line|#define OMAP_IH2_3_MIR&t;&t;(OMAP_IH2_3_BASE + 0x04)
DECL|macro|OMAP_IH2_3_SIR_IRQ
mdefine_line|#define OMAP_IH2_3_SIR_IRQ&t;(OMAP_IH2_3_BASE + 0x10)
DECL|macro|OMAP_IH2_3_SIR_FIQ
mdefine_line|#define OMAP_IH2_3_SIR_FIQ&t;(OMAP_IH2_3_BASE + 0x14)
DECL|macro|OMAP_IH2_3_CONTROL
mdefine_line|#define OMAP_IH2_3_CONTROL&t;(OMAP_IH2_3_BASE + 0x18)
DECL|macro|OMAP_IH2_3_ILR3
mdefine_line|#define OMAP_IH2_3_ILR3&t;&t;(OMAP_IH2_3_BASE + 0x1c)
DECL|macro|OMAP_IH2_3_ISR
mdefine_line|#define OMAP_IH2_3_ISR&t;&t;(OMAP_IH2_3_BASE + 0x9c)
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Clocks&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP16XX_ARM_IDLECT3
mdefine_line|#define OMAP16XX_ARM_IDLECT3&t;(CLKGEN_REG_BASE + 0x24)
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Pin configuration registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP16XX_CONF_VOLTAGE_VDDSHV6
mdefine_line|#define OMAP16XX_CONF_VOLTAGE_VDDSHV6&t;(1 &lt;&lt; 8)
DECL|macro|OMAP16XX_CONF_VOLTAGE_VDDSHV7
mdefine_line|#define OMAP16XX_CONF_VOLTAGE_VDDSHV7&t;(1 &lt;&lt; 9)
DECL|macro|OMAP16XX_CONF_VOLTAGE_VDDSHV8
mdefine_line|#define OMAP16XX_CONF_VOLTAGE_VDDSHV8&t;(1 &lt;&lt; 10)
DECL|macro|OMAP16XX_CONF_VOLTAGE_VDDSHV9
mdefine_line|#define OMAP16XX_CONF_VOLTAGE_VDDSHV9&t;(1 &lt;&lt; 11)
DECL|macro|OMAP16XX_SUBLVDS_CONF_VALID
mdefine_line|#define OMAP16XX_SUBLVDS_CONF_VALID&t;(1 &lt;&lt; 13)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * TIPB bus interface&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|TIPB_SWITCH_BASE
mdefine_line|#define TIPB_SWITCH_BASE&t;&t; (0xfffbc800)
DECL|macro|OMAP16XX_MMCSD2_SSW_MPU_CONF
mdefine_line|#define OMAP16XX_MMCSD2_SSW_MPU_CONF&t;(TIPB_SWITCH_BASE + 0x160)
multiline_comment|/* UART3 Registers Maping through MPU bus */
DECL|macro|UART3_RHR
mdefine_line|#define UART3_RHR               (OMAP_UART3_BASE + 0)
DECL|macro|UART3_THR
mdefine_line|#define UART3_THR               (OMAP_UART3_BASE + 0)
DECL|macro|UART3_DLL
mdefine_line|#define UART3_DLL               (OMAP_UART3_BASE + 0)
DECL|macro|UART3_IER
mdefine_line|#define UART3_IER               (OMAP_UART3_BASE + 4)
DECL|macro|UART3_DLH
mdefine_line|#define UART3_DLH               (OMAP_UART3_BASE + 4)
DECL|macro|UART3_IIR
mdefine_line|#define UART3_IIR               (OMAP_UART3_BASE + 8)
DECL|macro|UART3_FCR
mdefine_line|#define UART3_FCR               (OMAP_UART3_BASE + 8)
DECL|macro|UART3_EFR
mdefine_line|#define UART3_EFR               (OMAP_UART3_BASE + 8)
DECL|macro|UART3_LCR
mdefine_line|#define UART3_LCR               (OMAP_UART3_BASE + 0x0C)
DECL|macro|UART3_MCR
mdefine_line|#define UART3_MCR               (OMAP_UART3_BASE + 0x10)
DECL|macro|UART3_XON1_ADDR1
mdefine_line|#define UART3_XON1_ADDR1        (OMAP_UART3_BASE + 0x10)
DECL|macro|UART3_XON2_ADDR2
mdefine_line|#define UART3_XON2_ADDR2        (OMAP_UART3_BASE + 0x14)
DECL|macro|UART3_LSR
mdefine_line|#define UART3_LSR               (OMAP_UART3_BASE + 0x14)
DECL|macro|UART3_TCR
mdefine_line|#define UART3_TCR               (OMAP_UART3_BASE + 0x18)
DECL|macro|UART3_MSR
mdefine_line|#define UART3_MSR               (OMAP_UART3_BASE + 0x18)
DECL|macro|UART3_XOFF1
mdefine_line|#define UART3_XOFF1             (OMAP_UART3_BASE + 0x18)
DECL|macro|UART3_XOFF2
mdefine_line|#define UART3_XOFF2             (OMAP_UART3_BASE + 0x1C)
DECL|macro|UART3_SPR
mdefine_line|#define UART3_SPR               (OMAP_UART3_BASE + 0x1C)
DECL|macro|UART3_TLR
mdefine_line|#define UART3_TLR               (OMAP_UART3_BASE + 0x1C)
DECL|macro|UART3_MDR1
mdefine_line|#define UART3_MDR1              (OMAP_UART3_BASE + 0x20)
DECL|macro|UART3_MDR2
mdefine_line|#define UART3_MDR2              (OMAP_UART3_BASE + 0x24)
DECL|macro|UART3_SFLSR
mdefine_line|#define UART3_SFLSR             (OMAP_UART3_BASE + 0x28)
DECL|macro|UART3_TXFLL
mdefine_line|#define UART3_TXFLL             (OMAP_UART3_BASE + 0x28)
DECL|macro|UART3_RESUME
mdefine_line|#define UART3_RESUME            (OMAP_UART3_BASE + 0x2C)
DECL|macro|UART3_TXFLH
mdefine_line|#define UART3_TXFLH             (OMAP_UART3_BASE + 0x2C)
DECL|macro|UART3_SFREGL
mdefine_line|#define UART3_SFREGL            (OMAP_UART3_BASE + 0x30)
DECL|macro|UART3_RXFLL
mdefine_line|#define UART3_RXFLL             (OMAP_UART3_BASE + 0x30)
DECL|macro|UART3_SFREGH
mdefine_line|#define UART3_SFREGH            (OMAP_UART3_BASE + 0x34)
DECL|macro|UART3_RXFLH
mdefine_line|#define UART3_RXFLH             (OMAP_UART3_BASE + 0x34)
DECL|macro|UART3_BLR
mdefine_line|#define UART3_BLR               (OMAP_UART3_BASE + 0x38)
DECL|macro|UART3_ACREG
mdefine_line|#define UART3_ACREG             (OMAP_UART3_BASE + 0x3C)
DECL|macro|UART3_DIV16
mdefine_line|#define UART3_DIV16             (OMAP_UART3_BASE + 0x3C)
DECL|macro|UART3_SCR
mdefine_line|#define UART3_SCR               (OMAP_UART3_BASE + 0x40)
DECL|macro|UART3_SSR
mdefine_line|#define UART3_SSR               (OMAP_UART3_BASE + 0x44)
DECL|macro|UART3_EBLR
mdefine_line|#define UART3_EBLR              (OMAP_UART3_BASE + 0x48)
DECL|macro|UART3_OSC_12M_SEL
mdefine_line|#define UART3_OSC_12M_SEL       (OMAP_UART3_BASE + 0x4C)
DECL|macro|UART3_MVR
mdefine_line|#define UART3_MVR               (OMAP_UART3_BASE + 0x50)
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Pulse-Width Light&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP16XX_PWL_BASE
mdefine_line|#define OMAP16XX_PWL_BASE&t;(0xfffb5800)
DECL|macro|OMAP16XX_PWL_ENABLE
mdefine_line|#define OMAP16XX_PWL_ENABLE&t;(OMAP16XX_PWL_BASE + 0x00)
DECL|macro|OMAP16XX_PWL_CLK_ENABLE
mdefine_line|#define OMAP16XX_PWL_CLK_ENABLE&t;(OMAP16XX_PWL_BASE + 0x04)
macro_line|#endif /*  __ASM_ARCH_OMAP16XX_H */
eof
