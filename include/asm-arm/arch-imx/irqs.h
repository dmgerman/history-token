multiline_comment|/*&n; *  linux/include/asm-arm/arch-imxads/irqs.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ARM_IRQS_H__
DECL|macro|__ARM_IRQS_H__
mdefine_line|#define __ARM_IRQS_H__
multiline_comment|/* Use the imx definitions */
macro_line|#include &lt;asm/arch/hardware.h&gt;
multiline_comment|/*&n; *  IMX Interrupt numbers&n; *&n; */
DECL|macro|INT_SOFTINT
mdefine_line|#define INT_SOFTINT                 0
DECL|macro|CSI_INT
mdefine_line|#define CSI_INT                     6
DECL|macro|DSPA_MAC_INT
mdefine_line|#define DSPA_MAC_INT                7
DECL|macro|DSPA_INT
mdefine_line|#define DSPA_INT                    8
DECL|macro|COMP_INT
mdefine_line|#define COMP_INT                    9
DECL|macro|MSHC_XINT
mdefine_line|#define MSHC_XINT                   10
DECL|macro|GPIO_INT_PORTA
mdefine_line|#define GPIO_INT_PORTA              11
DECL|macro|GPIO_INT_PORTB
mdefine_line|#define GPIO_INT_PORTB              12
DECL|macro|GPIO_INT_PORTC
mdefine_line|#define GPIO_INT_PORTC              13
DECL|macro|LCDC_INT
mdefine_line|#define LCDC_INT                    14
DECL|macro|SIM_INT
mdefine_line|#define SIM_INT                     15
DECL|macro|SIM_DATA_INT
mdefine_line|#define SIM_DATA_INT                16
DECL|macro|RTC_INT
mdefine_line|#define RTC_INT                     17
DECL|macro|RTC_SAMINT
mdefine_line|#define RTC_SAMINT                  18
DECL|macro|UART2_MINT_PFERR
mdefine_line|#define UART2_MINT_PFERR            19
DECL|macro|UART2_MINT_RTS
mdefine_line|#define UART2_MINT_RTS              20
DECL|macro|UART2_MINT_DTR
mdefine_line|#define UART2_MINT_DTR              21
DECL|macro|UART2_MINT_UARTC
mdefine_line|#define UART2_MINT_UARTC            22
DECL|macro|UART2_MINT_TX
mdefine_line|#define UART2_MINT_TX               23
DECL|macro|UART2_MINT_RX
mdefine_line|#define UART2_MINT_RX               24
DECL|macro|UART1_MINT_PFERR
mdefine_line|#define UART1_MINT_PFERR            25
DECL|macro|UART1_MINT_RTS
mdefine_line|#define UART1_MINT_RTS              26
DECL|macro|UART1_MINT_DTR
mdefine_line|#define UART1_MINT_DTR              27
DECL|macro|UART1_MINT_UARTC
mdefine_line|#define UART1_MINT_UARTC            28
DECL|macro|UART1_MINT_TX
mdefine_line|#define UART1_MINT_TX               29
DECL|macro|UART1_MINT_RX
mdefine_line|#define UART1_MINT_RX               30
DECL|macro|VOICE_DAC_INT
mdefine_line|#define VOICE_DAC_INT               31
DECL|macro|VOICE_ADC_INT
mdefine_line|#define VOICE_ADC_INT               32
DECL|macro|PEN_DATA_INT
mdefine_line|#define PEN_DATA_INT                33
DECL|macro|PWM_INT
mdefine_line|#define PWM_INT                     34
DECL|macro|SDHC_INT
mdefine_line|#define SDHC_INT                    35
DECL|macro|I2C_INT
mdefine_line|#define I2C_INT                     39
DECL|macro|CSPI_INT
mdefine_line|#define CSPI_INT                    41
DECL|macro|SSI_TX_INT
mdefine_line|#define SSI_TX_INT                  42
DECL|macro|SSI_TX_ERR_INT
mdefine_line|#define SSI_TX_ERR_INT              43
DECL|macro|SSI_RX_INT
mdefine_line|#define SSI_RX_INT                  44
DECL|macro|SSI_RX_ERR_INT
mdefine_line|#define SSI_RX_ERR_INT              45
DECL|macro|TOUCH_INT
mdefine_line|#define TOUCH_INT                   46
DECL|macro|USBD_INT0
mdefine_line|#define USBD_INT0                   47
DECL|macro|USBD_INT1
mdefine_line|#define USBD_INT1                   48
DECL|macro|USBD_INT2
mdefine_line|#define USBD_INT2                   49
DECL|macro|USBD_INT3
mdefine_line|#define USBD_INT3                   50
DECL|macro|USBD_INT4
mdefine_line|#define USBD_INT4                   51
DECL|macro|USBD_INT5
mdefine_line|#define USBD_INT5                   52
DECL|macro|USBD_INT6
mdefine_line|#define USBD_INT6                   53
DECL|macro|BTSYS_INT
mdefine_line|#define BTSYS_INT                   55
DECL|macro|BTTIM_INT
mdefine_line|#define BTTIM_INT                   56
DECL|macro|BTWUI_INT
mdefine_line|#define BTWUI_INT                   57
DECL|macro|TIM2_INT
mdefine_line|#define TIM2_INT                    58
DECL|macro|TIM1_INT
mdefine_line|#define TIM1_INT                    59
DECL|macro|DMA_ERR
mdefine_line|#define DMA_ERR                     60
DECL|macro|DMA_INT
mdefine_line|#define DMA_INT                     61
DECL|macro|GPIO_INT_PORTD
mdefine_line|#define GPIO_INT_PORTD              62
DECL|macro|IMX_IRQS
mdefine_line|#define IMX_IRQS                         (64)
multiline_comment|/* note: the IMX has four gpio ports (A-D), but only&n; *       the following pins are connected to the outside&n; *       world:&n; *&n; * PORT A: bits 0-31&n; * PORT B: bits 8-31&n; * PORT C: bits 3-17&n; * PORT D: bits 6-31&n; *&n; * We map these interrupts straight on. As a result we have&n; * several holes in the interrupt mapping. We do this for two&n; * reasons:&n; *   - mapping the interrupts without holes would get&n; *     far more complicated&n; *   - Motorola could well decide to bring some processor&n; *     with more pins connected&n; */
DECL|macro|IRQ_GPIOA
mdefine_line|#define IRQ_GPIOA(x)  (IMX_IRQS + x)
DECL|macro|IRQ_GPIOB
mdefine_line|#define IRQ_GPIOB(x)  (IRQ_GPIOA(32) + x)
DECL|macro|IRQ_GPIOC
mdefine_line|#define IRQ_GPIOC(x)  (IRQ_GPIOB(32) + x)
DECL|macro|IRQ_GPIOD
mdefine_line|#define IRQ_GPIOD(x)  (IRQ_GPIOC(32) + x)
multiline_comment|/* decode irq number to use with IMR(x), ISR(x) and friends */
DECL|macro|IRQ_TO_REG
mdefine_line|#define IRQ_TO_REG(irq) ((irq - IMX_IRQS) &gt;&gt; 5)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (IRQ_GPIOD(32) + 1)
DECL|macro|IRQ_GPIO
mdefine_line|#define IRQ_GPIO(x)
macro_line|#endif
eof
