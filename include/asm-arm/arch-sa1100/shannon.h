macro_line|#ifndef _INCLUDE_SHANNON_H
DECL|macro|_INCLUDE_SHANNON_H
mdefine_line|#define _INCLUDE_SHANNON_H
multiline_comment|/* taken from comp.os.inferno Tue, 12 Sep 2000 09:21:50 GMT,&n; * written by &lt;forsyth@vitanuova.com&gt; */
DECL|macro|SHANNON_GPIO_SPI_FLASH
mdefine_line|#define SHANNON_GPIO_SPI_FLASH&t;&t;GPIO_GPIO (0)&t;/* Output - Driven low, enables SPI to flash */
DECL|macro|SHANNON_GPIO_SPI_DSP
mdefine_line|#define SHANNON_GPIO_SPI_DSP&t;&t;GPIO_GPIO (1)&t;/* Output - Driven low, enables SPI to DSP */
multiline_comment|/* lcd lower = GPIO 2-9 */
DECL|macro|SHANNON_GPIO_SPI_OUTPUT
mdefine_line|#define SHANNON_GPIO_SPI_OUTPUT&t;&t;GPIO_GPIO (10)&t;/* Output - SPI output to DSP */
DECL|macro|SHANNON_GPIO_SPI_INPUT
mdefine_line|#define SHANNON_GPIO_SPI_INPUT&t;&t;GPIO_GPIO (11)&t;/* Input  - SPI input from DSP */
DECL|macro|SHANNON_GPIO_SPI_CLOCK
mdefine_line|#define SHANNON_GPIO_SPI_CLOCK&t;&t;GPIO_GPIO (12)&t;/* Output - Clock for SPI */
DECL|macro|SHANNON_GPIO_SPI_FRAME
mdefine_line|#define SHANNON_GPIO_SPI_FRAME&t;&t;GPIO_GPIO (13)&t;/* Output - Frame marker - not used */
DECL|macro|SHANNON_GPIO_SPI_RTS
mdefine_line|#define SHANNON_GPIO_SPI_RTS&t;&t;GPIO_GPIO (14)&t;/* Input  - SPI Ready to Send */
DECL|macro|SHANNON_IRQ_GPIO_SPI_RTS
mdefine_line|#define SHANNON_IRQ_GPIO_SPI_RTS&t;IRQ_GPIO14
DECL|macro|SHANNON_GPIO_SPI_CTS
mdefine_line|#define SHANNON_GPIO_SPI_CTS&t;&t;GPIO_GPIO (15)&t;/* Output - SPI Clear to Send */
DECL|macro|SHANNON_GPIO_IRQ_CODEC
mdefine_line|#define SHANNON_GPIO_IRQ_CODEC&t;&t;GPIO_GPIO (16)&t;/* in, irq from ucb1200 */
DECL|macro|SHANNON_IRQ_GPIO_IRQ_CODEC
mdefine_line|#define SHANNON_IRQ_GPIO_IRQ_CODEC&t;IRQ_GPIO16
DECL|macro|SHANNON_GPIO_DSP_RESET
mdefine_line|#define SHANNON_GPIO_DSP_RESET&t;&t;GPIO_GPIO (17)&t;/* Output - Drive low to reset the DSP */
DECL|macro|SHANNON_GPIO_CODEC_RESET
mdefine_line|#define SHANNON_GPIO_CODEC_RESET&t;GPIO_GPIO (18)&t;/* Output - Drive low to reset the UCB1x00 */
DECL|macro|SHANNON_GPIO_U3_RTS
mdefine_line|#define SHANNON_GPIO_U3_RTS&t;&t;GPIO_GPIO (19)&t;/* ?? */
DECL|macro|SHANNON_GPIO_U3_CTS
mdefine_line|#define SHANNON_GPIO_U3_CTS&t;&t;GPIO_GPIO (20)&t;/* ?? */
DECL|macro|SHANNON_GPIO_SENSE_12V
mdefine_line|#define SHANNON_GPIO_SENSE_12V&t;&t;GPIO_GPIO (21)&t;/* Input, 12v flash unprotect detected */
DECL|macro|SHANNON_GPIO_DISP_EN
mdefine_line|#define SHANNON_GPIO_DISP_EN&t;&t;GPIO_GPIO (22)&t;/* out */
multiline_comment|/* XXX GPIO 23 unaccounted for */
DECL|macro|SHANNON_GPIO_EJECT_0
mdefine_line|#define SHANNON_GPIO_EJECT_0&t;&t;GPIO_GPIO (24)&t;/* in */
DECL|macro|SHANNON_IRQ_GPIO_EJECT_0
mdefine_line|#define SHANNON_IRQ_GPIO_EJECT_0&t;IRQ_GPIO24
DECL|macro|SHANNON_GPIO_EJECT_1
mdefine_line|#define SHANNON_GPIO_EJECT_1&t;&t;GPIO_GPIO (25)&t;/* in */
DECL|macro|SHANNON_IRQ_GPIO_EJECT_1
mdefine_line|#define SHANNON_IRQ_GPIO_EJECT_1&t;IRQ_GPIO25
DECL|macro|SHANNON_GPIO_RDY_0
mdefine_line|#define SHANNON_GPIO_RDY_0&t;&t;GPIO_GPIO (26)&t;/* in */
DECL|macro|SHANNON_IRQ_GPIO_RDY_0
mdefine_line|#define SHANNON_IRQ_GPIO_RDY_0&t;&t;IRQ_GPIO26
DECL|macro|SHANNON_GPIO_RDY_1
mdefine_line|#define SHANNON_GPIO_RDY_1&t;&t;GPIO_GPIO (27)&t;/* in */
DECL|macro|SHANNON_IRQ_GPIO_RDY_1
mdefine_line|#define SHANNON_IRQ_GPIO_RDY_1&t;&t;IRQ_GPIO27
multiline_comment|/* MCP UCB codec GPIO pins... */
DECL|macro|SHANNON_UCB_GPIO_BACKLIGHT
mdefine_line|#define SHANNON_UCB_GPIO_BACKLIGHT&t;9
DECL|macro|SHANNON_UCB_GPIO_BRIGHT_MASK
mdefine_line|#define SHANNON_UCB_GPIO_BRIGHT_MASK  &t;7
DECL|macro|SHANNON_UCB_GPIO_BRIGHT
mdefine_line|#define SHANNON_UCB_GPIO_BRIGHT&t;&t;6
DECL|macro|SHANNON_UCB_GPIO_CONTRAST_MASK
mdefine_line|#define SHANNON_UCB_GPIO_CONTRAST_MASK&t;0x3f
DECL|macro|SHANNON_UCB_GPIO_CONTRAST
mdefine_line|#define SHANNON_UCB_GPIO_CONTRAST&t;0
macro_line|#endif
eof
