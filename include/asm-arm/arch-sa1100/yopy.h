macro_line|#ifndef __ASM_ARCH_YOPY_H__
DECL|macro|__ASM_ARCH_YOPY_H__
mdefine_line|#define __ASM_ARCH_YOPY_H__
multiline_comment|/******************************************************************************&n; * Memory mappings&n; ******************************************************************************/
multiline_comment|/* Flash memories */
DECL|macro|YOPY_FLASH0_BASE_P
mdefine_line|#define YOPY_FLASH0_BASE_P&t;(0x00000000)&t;/* CS0 */
DECL|macro|YOPY_FLASH0_BASE_V
mdefine_line|#define YOPY_FLASH0_BASE_V&t;(0xe8000000)
DECL|macro|YOPY_FLASH0_BASE
mdefine_line|#define YOPY_FLASH0_BASE&t;YOPY_FLASH0_BASE_V
DECL|macro|YOPY_FLASH0_SIZE
mdefine_line|#define YOPY_FLASH0_SIZE&t;(0x04000000)&t;/* map 64MB */
DECL|macro|YOPY_FLASH1_BASE_P
mdefine_line|#define YOPY_FLASH1_BASE_P&t;(0x08000000)&t;/* CS1 */
DECL|macro|YOPY_FLASH1_BASE_V
mdefine_line|#define YOPY_FLASH1_BASE_V&t;(YOPY_FLASH0_BASE_V + YOPY_FLASH0_SIZE)
DECL|macro|YOPY_FLASH1_BASE
mdefine_line|#define YOPY_FLASH1_BASE&t;YOPY_FLASH1_BASE_V
DECL|macro|YOPY_FLASH1_SIZE
mdefine_line|#define YOPY_FLASH1_SIZE&t;(0x04000000)&t;/* map 64MB */
multiline_comment|/* LCD Controller */
DECL|macro|YOPY_LCD_IO_BASE_P
mdefine_line|#define YOPY_LCD_IO_BASE_P&t;(0x48000000)&t;/* CS5 */
DECL|macro|YOPY_LCD_IO_BASE_V
mdefine_line|#define YOPY_LCD_IO_BASE_V&t;(0xf0000000)
DECL|macro|YOPY_LCD_IO_BASE
mdefine_line|#define YOPY_LCD_IO_BASE&t;YOPY_LCD_IO_BASE_V
DECL|macro|YOPY_LCD_IO_RANGE
mdefine_line|#define YOPY_LCD_IO_RANGE&t;(0x00208000)
multiline_comment|/* Extended GPIO */
DECL|macro|YOPY_EGPIO_BASE_P
mdefine_line|#define YOPY_EGPIO_BASE_P&t;(0x10000000)&t;/* CS2 */
DECL|macro|YOPY_EGPIO_BASE_V
mdefine_line|#define YOPY_EGPIO_BASE_V&t;(0xf1000000)
DECL|macro|YOPY_EGPIO_BASE
mdefine_line|#define YOPY_EGPIO_BASE&t;&t;YOPY_EGPIO_BASE_V
DECL|macro|YOPY_EGPIO_RANGE
mdefine_line|#define YOPY_EGPIO_RANGE&t;4
DECL|macro|YOPY_EGPIO
mdefine_line|#define YOPY_EGPIO&t;&t;(*((volatile Word *)YOPY_EGPIO_BASE))
multiline_comment|/******************************************************************************&n; * GPIO assignements&n; ******************************************************************************/
DECL|macro|GPIO_UCB1200_IRQ
mdefine_line|#define GPIO_UCB1200_IRQ&t;GPIO_GPIO0
DECL|macro|GPIO_UCB1200_RESET
mdefine_line|#define GPIO_UCB1200_RESET&t;GPIO_GPIO22
DECL|macro|GPIO_CF_IREQ
mdefine_line|#define GPIO_CF_IREQ&t;&t;GPIO_GPIO2
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD&t;&t;GPIO_GPIO3
DECL|macro|GPIO_CF_BVD1
mdefine_line|#define GPIO_CF_BVD1&t;&t;GPIO_GPIO4
DECL|macro|GPIO_CF_BVD2
mdefine_line|#define GPIO_CF_BVD2&t;&t;GPIO_GPIO5
DECL|macro|GPIO_CF_CSEL
mdefine_line|#define GPIO_CF_CSEL&t;&t;GPIO_GPIO6
DECL|macro|GPIO_CF_READY
mdefine_line|#define GPIO_CF_READY&t;&t;GPIO_CF_IREQ
DECL|macro|GPIO_CF_STSCHG
mdefine_line|#define GPIO_CF_STSCHG&t;&t;GPIO_CF_BVD1
DECL|macro|GPIO_CF_SPKR
mdefine_line|#define GPIO_CF_SPKR&t;&t;GPIO_CF_BVD2
DECL|macro|GPIO_MASK
mdefine_line|#define GPIO_MASK(io)&t;&t;(1 &lt;&lt; (io))
DECL|macro|GPIO_YOPY_PLL_ML
mdefine_line|#define GPIO_YOPY_PLL_ML&t;PPC_LDD7
DECL|macro|GPIO_YOPY_PLL_MC
mdefine_line|#define GPIO_YOPY_PLL_MC&t;PPC_L_LCLK
DECL|macro|GPIO_YOPY_PLL_MD
mdefine_line|#define GPIO_YOPY_PLL_MD&t;PPC_L_FCLK
DECL|macro|GPIO_YOPY_L3_MODE
mdefine_line|#define GPIO_YOPY_L3_MODE&t;PPC_LDD4
DECL|macro|GPIO_YOPY_L3_CLOCK
mdefine_line|#define GPIO_YOPY_L3_CLOCK&t;PPC_LDD5
DECL|macro|GPIO_YOPY_L3_DATA
mdefine_line|#define GPIO_YOPY_L3_DATA&t;PPC_LDD6
DECL|macro|GPIO_CF_RESET
mdefine_line|#define GPIO_CF_RESET&t;&t;0
DECL|macro|GPIO_CLKDIV_CLR1
mdefine_line|#define GPIO_CLKDIV_CLR1&t;1
DECL|macro|GPIO_CLKDIV_CLR2
mdefine_line|#define GPIO_CLKDIV_CLR2&t;2
DECL|macro|GPIO_SPEAKER_MUTE
mdefine_line|#define GPIO_SPEAKER_MUTE&t;5
DECL|macro|GPIO_CF_POWER
mdefine_line|#define GPIO_CF_POWER&t;&t;8
DECL|macro|GPIO_AUDIO_OPAMP_POWER
mdefine_line|#define GPIO_AUDIO_OPAMP_POWER&t;11
DECL|macro|GPIO_AUDIO_CODEC_POWER
mdefine_line|#define GPIO_AUDIO_CODEC_POWER&t;12
DECL|macro|GPIO_AUDIO_POWER
mdefine_line|#define GPIO_AUDIO_POWER&t;13
DECL|macro|GPIO_IRDA_POWER
mdefine_line|#define GPIO_IRDA_POWER&t;&t;PPC_L_PCLK
DECL|macro|GPIO_IRDA_FIR
mdefine_line|#define GPIO_IRDA_FIR&t;&t;PPC_LDD0
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
id|yopy_gpio_test
c_func
(paren
r_int
r_int
id|gpio
)paren
suffix:semicolon
r_extern
r_void
id|yopy_gpio_set
c_func
(paren
r_int
r_int
id|gpio
comma
r_int
id|level
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/******************************************************************************&n; * IRQ assignements&n; ******************************************************************************/
multiline_comment|/* for our old drivers */
DECL|macro|IRQ_SP0_UDC
mdefine_line|#define IRQ_SP0_UDC&t;13
DECL|macro|IRQ_SP1_SDLC
mdefine_line|#define IRQ_SP1_SDLC&t;14
DECL|macro|IRQ_SP1_UART
mdefine_line|#define IRQ_SP1_UART&t;15
DECL|macro|IRQ_SP2_ICP
mdefine_line|#define IRQ_SP2_ICP&t;16
DECL|macro|IRQ_SP2_UART
mdefine_line|#define IRQ_SP2_UART&t;16
DECL|macro|IRQ_SP3_UART
mdefine_line|#define IRQ_SP3_UART&t;17
DECL|macro|IRQ_SP4_MCP
mdefine_line|#define IRQ_SP4_MCP&t;18
DECL|macro|IRQ_SP4_SSP
mdefine_line|#define IRQ_SP4_SSP&t;19
DECL|macro|IRQ_RTC_HZ
mdefine_line|#define IRQ_RTC_HZ&t;30
DECL|macro|IRQ_RTC_ALARM
mdefine_line|#define IRQ_RTC_ALARM&t;31
multiline_comment|/* GPIO interrupts */
DECL|macro|IRQ_GPIO_UCB1200_IRQ
mdefine_line|#define IRQ_GPIO_UCB1200_IRQ&t;IRQ_GPIO0
DECL|macro|IRQ_CF_IREQ
mdefine_line|#define IRQ_CF_IREQ&t;&t;IRQ_GPIO2
DECL|macro|IRQ_CF_CD
mdefine_line|#define IRQ_CF_CD&t;&t;IRQ_GPIO3
DECL|macro|IRQ_CF_BVD1
mdefine_line|#define IRQ_CF_BVD1&t;&t;IRQ_GPIO4
DECL|macro|IRQ_CF_BVD2
mdefine_line|#define IRQ_CF_BVD2&t;&t;IRQ_GPIO5
DECL|macro|IRQ_UART_CTS
mdefine_line|#define IRQ_UART_CTS&t;&t;IRQ_GPIO7
DECL|macro|IRQ_UART_DCD
mdefine_line|#define IRQ_UART_DCD&t;&t;IRQ_GPIO8
DECL|macro|IRQ_UART_DSR
mdefine_line|#define IRQ_UART_DSR&t;&t;IRQ_GPIO9
DECL|macro|IRQ_FLASH_STATUS
mdefine_line|#define IRQ_FLASH_STATUS&t;IRQ_GPIO23
DECL|macro|IRQ_BUTTON_POWER
mdefine_line|#define IRQ_BUTTON_POWER&t;IRQ_GPIO1
DECL|macro|IRQ_BUTTON_UP
mdefine_line|#define IRQ_BUTTON_UP&t;&t;IRQ_GPIO14
DECL|macro|IRQ_BUTTON_DOWN
mdefine_line|#define IRQ_BUTTON_DOWN&t;&t;IRQ_GPIO15
DECL|macro|IRQ_BUTTON_LEFT
mdefine_line|#define IRQ_BUTTON_LEFT&t;&t;IRQ_GPIO16
DECL|macro|IRQ_BUTTON_RIGHT
mdefine_line|#define IRQ_BUTTON_RIGHT&t;IRQ_GPIO17
DECL|macro|IRQ_BUTTON_SHOT0
mdefine_line|#define IRQ_BUTTON_SHOT0&t;IRQ_GPIO18
DECL|macro|IRQ_BUTTON_SHOT1
mdefine_line|#define IRQ_BUTTON_SHOT1&t;IRQ_GPIO20
DECL|macro|IRQ_BUTTON_PIMS
mdefine_line|#define IRQ_BUTTON_PIMS&t;&t;IRQ_UCB1200_IO1
DECL|macro|IRQ_BUTTON_MP3
mdefine_line|#define IRQ_BUTTON_MP3&t;&t;IRQ_UCB1200_IO2
DECL|macro|IRQ_BUTTON_RECORD
mdefine_line|#define IRQ_BUTTON_RECORD&t;IRQ_UCB1200_IO3
DECL|macro|IRQ_BUTTON_PREV
mdefine_line|#define IRQ_BUTTON_PREV&t;&t;IRQ_UCB1200_IO4
DECL|macro|IRQ_BUTTON_SELECT
mdefine_line|#define IRQ_BUTTON_SELECT&t;IRQ_UCB1200_IO5
DECL|macro|IRQ_BUTTON_NEXT
mdefine_line|#define IRQ_BUTTON_NEXT&t;&t;IRQ_UCB1200_IO6
DECL|macro|IRQ_BUTTON_CANCEL
mdefine_line|#define IRQ_BUTTON_CANCEL&t;IRQ_UCB1200_IO7
DECL|macro|IRQ_BUTTON_REMOTE
mdefine_line|#define IRQ_BUTTON_REMOTE&t;IRQ_UCB1200_IO8
macro_line|#endif
eof
