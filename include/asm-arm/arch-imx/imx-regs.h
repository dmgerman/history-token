macro_line|#ifndef _IMX_REGS_H
DECL|macro|_IMX_REGS_H
mdefine_line|#define _IMX_REGS_H
multiline_comment|/* ------------------------------------------------------------------------&n; *  Motorola IMX system registers&n; * ------------------------------------------------------------------------&n; *&n; */
multiline_comment|/*&n; *  Register BASEs, based on OFFSETs&n; *&n; */
DECL|macro|IMX_AIPI1_BASE
mdefine_line|#define IMX_AIPI1_BASE             (0x00000 + IMX_IO_BASE)
DECL|macro|IMX_WDT_BASE
mdefine_line|#define IMX_WDT_BASE               (0x01000 + IMX_IO_BASE)
DECL|macro|IMX_TIM1_BASE
mdefine_line|#define IMX_TIM1_BASE              (0x02000 + IMX_IO_BASE)
DECL|macro|IMX_TIM2_BASE
mdefine_line|#define IMX_TIM2_BASE              (0x03000 + IMX_IO_BASE)
DECL|macro|IMX_RTC_BASE
mdefine_line|#define IMX_RTC_BASE               (0x04000 + IMX_IO_BASE)
DECL|macro|IMX_LCDC_BASE
mdefine_line|#define IMX_LCDC_BASE              (0x05000 + IMX_IO_BASE)
DECL|macro|IMX_UART1_BASE
mdefine_line|#define IMX_UART1_BASE             (0x06000 + IMX_IO_BASE)
DECL|macro|IMX_UART2_BASE
mdefine_line|#define IMX_UART2_BASE             (0x07000 + IMX_IO_BASE)
DECL|macro|IMX_PWM_BASE
mdefine_line|#define IMX_PWM_BASE               (0x08000 + IMX_IO_BASE)
DECL|macro|IMX_DMAC_BASE
mdefine_line|#define IMX_DMAC_BASE              (0x09000 + IMX_IO_BASE)
DECL|macro|IMX_AIPI2_BASE
mdefine_line|#define IMX_AIPI2_BASE             (0x10000 + IMX_IO_BASE)
DECL|macro|IMX_SIM_BASE
mdefine_line|#define IMX_SIM_BASE               (0x11000 + IMX_IO_BASE)
DECL|macro|IMX_USBD_BASE
mdefine_line|#define IMX_USBD_BASE              (0x12000 + IMX_IO_BASE)
DECL|macro|IMX_SPI1_BASE
mdefine_line|#define IMX_SPI1_BASE              (0x13000 + IMX_IO_BASE)
DECL|macro|IMX_MMC_BASE
mdefine_line|#define IMX_MMC_BASE               (0x14000 + IMX_IO_BASE)
DECL|macro|IMX_ASP_BASE
mdefine_line|#define IMX_ASP_BASE               (0x15000 + IMX_IO_BASE)
DECL|macro|IMX_BTA_BASE
mdefine_line|#define IMX_BTA_BASE               (0x16000 + IMX_IO_BASE)
DECL|macro|IMX_I2C_BASE
mdefine_line|#define IMX_I2C_BASE               (0x17000 + IMX_IO_BASE)
DECL|macro|IMX_SSI_BASE
mdefine_line|#define IMX_SSI_BASE               (0x18000 + IMX_IO_BASE)
DECL|macro|IMX_SPI2_BASE
mdefine_line|#define IMX_SPI2_BASE              (0x19000 + IMX_IO_BASE)
DECL|macro|IMX_MSHC_BASE
mdefine_line|#define IMX_MSHC_BASE              (0x1A000 + IMX_IO_BASE)
DECL|macro|IMX_PLL_BASE
mdefine_line|#define IMX_PLL_BASE               (0x1B000 + IMX_IO_BASE)
DECL|macro|IMX_GPIO_BASE
mdefine_line|#define IMX_GPIO_BASE              (0x1C000 + IMX_IO_BASE)
DECL|macro|IMX_EIM_BASE
mdefine_line|#define IMX_EIM_BASE               (0x20000 + IMX_IO_BASE)
DECL|macro|IMX_SDRAMC_BASE
mdefine_line|#define IMX_SDRAMC_BASE            (0x21000 + IMX_IO_BASE)
DECL|macro|IMX_MMA_BASE
mdefine_line|#define IMX_MMA_BASE               (0x22000 + IMX_IO_BASE)
DECL|macro|IMX_AITC_BASE
mdefine_line|#define IMX_AITC_BASE              (0x23000 + IMX_IO_BASE)
DECL|macro|IMX_CSI_BASE
mdefine_line|#define IMX_CSI_BASE               (0x24000 + IMX_IO_BASE)
multiline_comment|/* PLL registers */
DECL|macro|CSCR
mdefine_line|#define CSCR   __REG(IMX_PLL_BASE)        /* Clock Source Control Register */
DECL|macro|CSCR_SYSTEM_SEL
mdefine_line|#define CSCR_SYSTEM_SEL (1&lt;&lt;16)
DECL|macro|MPCTL0
mdefine_line|#define MPCTL0 __REG(IMX_PLL_BASE + 0x4)  /* MCU PLL Control Register 0 */
DECL|macro|MPCTL1
mdefine_line|#define MPCTL1 __REG(IMX_PLL_BASE + 0x8)  /* MCU PLL and System Clock Register 1 */
DECL|macro|SPCTL0
mdefine_line|#define SPCTL0 __REG(IMX_PLL_BASE + 0xc)  /* System PLL Control Register 0 */
DECL|macro|SPCTL1
mdefine_line|#define SPCTL1 __REG(IMX_PLL_BASE + 0x10) /* System PLL Control Register 1 */
DECL|macro|PCDR
mdefine_line|#define PCDR   __REG(IMX_PLL_BASE + 0x20) /* Peripheral Clock Divider Register */
DECL|macro|CSCR_MPLL_RESTART
mdefine_line|#define CSCR_MPLL_RESTART (1&lt;&lt;21)
multiline_comment|/*&n; *  GPIO Module and I/O Multiplexer&n; *  x = 0..3 for reg_A, reg_B, reg_C, reg_D&n; */
DECL|macro|DDIR
mdefine_line|#define DDIR(x)    __REG2(IMX_GPIO_BASE + 0x00, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|OCR1
mdefine_line|#define OCR1(x)    __REG2(IMX_GPIO_BASE + 0x04, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|OCR2
mdefine_line|#define OCR2(x)    __REG2(IMX_GPIO_BASE + 0x08, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ICONFA1
mdefine_line|#define ICONFA1(x) __REG2(IMX_GPIO_BASE + 0x0c, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ICONFA2
mdefine_line|#define ICONFA2(x) __REG2(IMX_GPIO_BASE + 0x10, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ICONFB1
mdefine_line|#define ICONFB1(x) __REG2(IMX_GPIO_BASE + 0x14, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ICONFB2
mdefine_line|#define ICONFB2(x) __REG2(IMX_GPIO_BASE + 0x18, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|DR
mdefine_line|#define DR(x)      __REG2(IMX_GPIO_BASE + 0x1c, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|GIUS
mdefine_line|#define GIUS(x)    __REG2(IMX_GPIO_BASE + 0x20, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|SSR
mdefine_line|#define SSR(x)     __REG2(IMX_GPIO_BASE + 0x24, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ICR1
mdefine_line|#define ICR1(x)    __REG2(IMX_GPIO_BASE + 0x28, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ICR2
mdefine_line|#define ICR2(x)    __REG2(IMX_GPIO_BASE + 0x2c, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|IMR
mdefine_line|#define IMR(x)     __REG2(IMX_GPIO_BASE + 0x30, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|ISR
mdefine_line|#define ISR(x)     __REG2(IMX_GPIO_BASE + 0x34, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|GPR
mdefine_line|#define GPR(x)     __REG2(IMX_GPIO_BASE + 0x38, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|SWR
mdefine_line|#define SWR(x)     __REG2(IMX_GPIO_BASE + 0x3c, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|PUEN
mdefine_line|#define PUEN(x)    __REG2(IMX_GPIO_BASE + 0x40, ((x) &amp; 3) &lt;&lt; 8)
DECL|macro|GPIO_PIN_MASK
mdefine_line|#define GPIO_PIN_MASK 0x1f
DECL|macro|GPIO_PORT_MASK
mdefine_line|#define GPIO_PORT_MASK (0x3 &lt;&lt; 5)
DECL|macro|GPIO_PORTA
mdefine_line|#define GPIO_PORTA (0&lt;&lt;5)
DECL|macro|GPIO_PORTB
mdefine_line|#define GPIO_PORTB (1&lt;&lt;5)
DECL|macro|GPIO_PORTC
mdefine_line|#define GPIO_PORTC (2&lt;&lt;5)
DECL|macro|GPIO_PORTD
mdefine_line|#define GPIO_PORTD (3&lt;&lt;5)
DECL|macro|GPIO_OUT
mdefine_line|#define GPIO_OUT   (1&lt;&lt;7)
DECL|macro|GPIO_IN
mdefine_line|#define GPIO_IN    (0&lt;&lt;7)
DECL|macro|GPIO_PUEN
mdefine_line|#define GPIO_PUEN  (1&lt;&lt;8)
DECL|macro|GPIO_PF
mdefine_line|#define GPIO_PF    (0&lt;&lt;9)
DECL|macro|GPIO_AF
mdefine_line|#define GPIO_AF    (1&lt;&lt;9)
DECL|macro|GPIO_OCR_MASK
mdefine_line|#define GPIO_OCR_MASK (3&lt;&lt;10)
DECL|macro|GPIO_AIN
mdefine_line|#define GPIO_AIN   (0&lt;&lt;10)
DECL|macro|GPIO_BIN
mdefine_line|#define GPIO_BIN   (1&lt;&lt;10)
DECL|macro|GPIO_CIN
mdefine_line|#define GPIO_CIN   (2&lt;&lt;10)
DECL|macro|GPIO_GPIO
mdefine_line|#define GPIO_GPIO  (3&lt;&lt;10)
DECL|macro|GPIO_AOUT
mdefine_line|#define GPIO_AOUT  (1&lt;&lt;12)
DECL|macro|GPIO_BOUT
mdefine_line|#define GPIO_BOUT  (1&lt;&lt;13)
multiline_comment|/* assignements for GPIO alternate/primary functions */
multiline_comment|/* FIXME: This list is not completed. The correct directions are&n; * missing on some (many) pins&n; */
DECL|macro|PA0_PF_A24
mdefine_line|#define PA0_PF_A24           ( GPIO_PORTA | GPIO_PF | 0 )
DECL|macro|PA0_AIN_SPI2_CLK
mdefine_line|#define PA0_AIN_SPI2_CLK     ( GPIO_PORTA | GPIO_OUT | GPIO_AIN | 0 )
DECL|macro|PA0_AF_ETMTRACESYNC
mdefine_line|#define PA0_AF_ETMTRACESYNC  ( GPIO_PORTA | GPIO_AF | 0 )
DECL|macro|PA1_AOUT_SPI2_RXD
mdefine_line|#define PA1_AOUT_SPI2_RXD    ( GPIO_PORTA | GPIO_IN | GPIO_AOUT | 1 )
DECL|macro|PA1_PF_TIN
mdefine_line|#define PA1_PF_TIN           ( GPIO_PORTA | GPIO_PF | 1 )
DECL|macro|PA2_PF_PWM0
mdefine_line|#define PA2_PF_PWM0          ( GPIO_PORTA | GPIO_OUT | GPIO_PF | 2 )
DECL|macro|PA3_PF_CSI_MCLK
mdefine_line|#define PA3_PF_CSI_MCLK      ( GPIO_PORTA | GPIO_PF | 3 )
DECL|macro|PA4_PF_CSI_D0
mdefine_line|#define PA4_PF_CSI_D0        ( GPIO_PORTA | GPIO_PF | 4 )
DECL|macro|PA5_PF_CSI_D1
mdefine_line|#define PA5_PF_CSI_D1        ( GPIO_PORTA | GPIO_PF | 5 )
DECL|macro|PA6_PF_CSI_D2
mdefine_line|#define PA6_PF_CSI_D2        ( GPIO_PORTA | GPIO_PF | 6 )
DECL|macro|PA7_PF_CSI_D3
mdefine_line|#define PA7_PF_CSI_D3        ( GPIO_PORTA | GPIO_PF | 7 )
DECL|macro|PA8_PF_CSI_D4
mdefine_line|#define PA8_PF_CSI_D4        ( GPIO_PORTA | GPIO_PF | 8 )
DECL|macro|PA9_PF_CSI_D5
mdefine_line|#define PA9_PF_CSI_D5        ( GPIO_PORTA | GPIO_PF | 9 )
DECL|macro|PA10_PF_CSI_D6
mdefine_line|#define PA10_PF_CSI_D6       ( GPIO_PORTA | GPIO_PF | 10 )
DECL|macro|PA11_PF_CSI_D7
mdefine_line|#define PA11_PF_CSI_D7       ( GPIO_PORTA | GPIO_PF | 11 )
DECL|macro|PA12_PF_CSI_VSYNC
mdefine_line|#define PA12_PF_CSI_VSYNC    ( GPIO_PORTA | GPIO_PF | 12 )
DECL|macro|PA13_PF_CSI_HSYNC
mdefine_line|#define PA13_PF_CSI_HSYNC    ( GPIO_PORTA | GPIO_PF | 13 )
DECL|macro|PA14_PF_CSI_PIXCLK
mdefine_line|#define PA14_PF_CSI_PIXCLK   ( GPIO_PORTA | GPIO_PF | 14 )
DECL|macro|PA15_PF_I2C_SDA
mdefine_line|#define PA15_PF_I2C_SDA      ( GPIO_PORTA | GPIO_OUT | GPIO_PF | 15 )
DECL|macro|PA16_PF_I2C_SCL
mdefine_line|#define PA16_PF_I2C_SCL      ( GPIO_PORTA | GPIO_OUT | GPIO_PF | 16 )
DECL|macro|PA17_AF_ETMTRACEPKT4
mdefine_line|#define PA17_AF_ETMTRACEPKT4 ( GPIO_PORTA | GPIO_AF | 17 )
DECL|macro|PA17_AIN_SPI2_SS
mdefine_line|#define PA17_AIN_SPI2_SS     ( GPIO_PORTA | GPIO_AIN | 17 )
DECL|macro|PA18_AF_ETMTRACEPKT5
mdefine_line|#define PA18_AF_ETMTRACEPKT5 ( GPIO_PORTA | GPIO_AF | 18 )
DECL|macro|PA19_AF_ETMTRACEPKT6
mdefine_line|#define PA19_AF_ETMTRACEPKT6 ( GPIO_PORTA | GPIO_AF | 19 )
DECL|macro|PA20_AF_ETMTRACEPKT7
mdefine_line|#define PA20_AF_ETMTRACEPKT7 ( GPIO_PORTA | GPIO_AF | 20 )
DECL|macro|PA21_PF_A0
mdefine_line|#define PA21_PF_A0           ( GPIO_PORTA | GPIO_PF | 21 )
DECL|macro|PA22_PF_CS4
mdefine_line|#define PA22_PF_CS4          ( GPIO_PORTA | GPIO_PF | 22 )
DECL|macro|PA23_PF_CS5
mdefine_line|#define PA23_PF_CS5          ( GPIO_PORTA | GPIO_PF | 23 )
DECL|macro|PA24_PF_A16
mdefine_line|#define PA24_PF_A16          ( GPIO_PORTA | GPIO_PF | 24 )
DECL|macro|PA24_AF_ETMTRACEPKT0
mdefine_line|#define PA24_AF_ETMTRACEPKT0 ( GPIO_PORTA | GPIO_AF | 24 )
DECL|macro|PA25_PF_A17
mdefine_line|#define PA25_PF_A17          ( GPIO_PORTA | GPIO_PF | 25 )
DECL|macro|PA25_AF_ETMTRACEPKT1
mdefine_line|#define PA25_AF_ETMTRACEPKT1 ( GPIO_PORTA | GPIO_AF | 25 )
DECL|macro|PA26_PF_A18
mdefine_line|#define PA26_PF_A18          ( GPIO_PORTA | GPIO_PF | 26 )
DECL|macro|PA26_AF_ETMTRACEPKT2
mdefine_line|#define PA26_AF_ETMTRACEPKT2 ( GPIO_PORTA | GPIO_AF | 26 )
DECL|macro|PA27_PF_A19
mdefine_line|#define PA27_PF_A19          ( GPIO_PORTA | GPIO_PF | 27 )
DECL|macro|PA27_AF_ETMTRACEPKT3
mdefine_line|#define PA27_AF_ETMTRACEPKT3 ( GPIO_PORTA | GPIO_AF | 27 )
DECL|macro|PA28_PF_A20
mdefine_line|#define PA28_PF_A20          ( GPIO_PORTA | GPIO_PF | 28 )
DECL|macro|PA28_AF_ETMPIPESTAT0
mdefine_line|#define PA28_AF_ETMPIPESTAT0 ( GPIO_PORTA | GPIO_AF | 28 )
DECL|macro|PA29_PF_A21
mdefine_line|#define PA29_PF_A21          ( GPIO_PORTA | GPIO_PF | 29 )
DECL|macro|PA29_AF_ETMPIPESTAT1
mdefine_line|#define PA29_AF_ETMPIPESTAT1 ( GPIO_PORTA | GPIO_AF | 29 )
DECL|macro|PA30_PF_A22
mdefine_line|#define PA30_PF_A22          ( GPIO_PORTA | GPIO_PF | 30 )
DECL|macro|PA30_AF_ETMPIPESTAT2
mdefine_line|#define PA30_AF_ETMPIPESTAT2 ( GPIO_PORTA | GPIO_AF | 30 )
DECL|macro|PA31_PF_A23
mdefine_line|#define PA31_PF_A23          ( GPIO_PORTA | GPIO_PF | 31 )
DECL|macro|PA31_AF_ETMTRACECLK
mdefine_line|#define PA31_AF_ETMTRACECLK  ( GPIO_PORTA | GPIO_AF | 31 )
DECL|macro|PB8_PF_SD_DAT0
mdefine_line|#define PB8_PF_SD_DAT0       ( GPIO_PORTB | GPIO_PF | GPIO_PUEN | 8 )
DECL|macro|PB8_AF_MS_PIO
mdefine_line|#define PB8_AF_MS_PIO        ( GPIO_PORTB | GPIO_AF | 8 )
DECL|macro|PB9_PF_SD_DAT1
mdefine_line|#define PB9_PF_SD_DAT1       ( GPIO_PORTB | GPIO_PF | GPIO_PUEN  | 9 )
DECL|macro|PB9_AF_MS_PI1
mdefine_line|#define PB9_AF_MS_PI1        ( GPIO_PORTB | GPIO_AF | 9 )
DECL|macro|PB10_PF_SD_DAT2
mdefine_line|#define PB10_PF_SD_DAT2      ( GPIO_PORTB | GPIO_PF | GPIO_PUEN  | 10 )
DECL|macro|PB10_AF_MS_SCLKI
mdefine_line|#define PB10_AF_MS_SCLKI     ( GPIO_PORTB | GPIO_AF | 10 )
DECL|macro|PB11_PF_SD_DAT3
mdefine_line|#define PB11_PF_SD_DAT3      ( GPIO_PORTB | GPIO_PF | 11 )
DECL|macro|PB11_AF_MS_SDIO
mdefine_line|#define PB11_AF_MS_SDIO      ( GPIO_PORTB | GPIO_AF | 11 )
DECL|macro|PB12_PF_SD_CLK
mdefine_line|#define PB12_PF_SD_CLK       ( GPIO_PORTB | GPIO_PF | 12 )
DECL|macro|PB12_AF_MS_SCLK0
mdefine_line|#define PB12_AF_MS_SCLK0     ( GPIO_PORTB | GPIO_AF | 12 )
DECL|macro|PB13_PF_SD_CMD
mdefine_line|#define PB13_PF_SD_CMD       ( GPIO_PORTB | GPIO_PF | GPIO_PUEN | 13 )
DECL|macro|PB13_AF_MS_BS
mdefine_line|#define PB13_AF_MS_BS        ( GPIO_PORTB | GPIO_AF | 13 )
DECL|macro|PB14_AF_SSI_RXFS
mdefine_line|#define PB14_AF_SSI_RXFS     ( GPIO_PORTB | GPIO_AF | 14 )
DECL|macro|PB15_AF_SSI_RXCLK
mdefine_line|#define PB15_AF_SSI_RXCLK    ( GPIO_PORTB | GPIO_AF | 15 )
DECL|macro|PB16_AF_SSI_RXDAT
mdefine_line|#define PB16_AF_SSI_RXDAT    ( GPIO_PORTB | GPIO_IN | GPIO_AF | 16 )
DECL|macro|PB17_AF_SSI_TXDAT
mdefine_line|#define PB17_AF_SSI_TXDAT    ( GPIO_PORTB | GPIO_OUT | GPIO_AF | 17 )
DECL|macro|PB18_AF_SSI_TXFS
mdefine_line|#define PB18_AF_SSI_TXFS     ( GPIO_PORTB | GPIO_AF | 18 )
DECL|macro|PB19_AF_SSI_TXCLK
mdefine_line|#define PB19_AF_SSI_TXCLK    ( GPIO_PORTB | GPIO_AF | 19 )
DECL|macro|PB20_PF_USBD_AFE
mdefine_line|#define PB20_PF_USBD_AFE     ( GPIO_PORTB | GPIO_PF | 20 )
DECL|macro|PB21_PF_USBD_OE
mdefine_line|#define PB21_PF_USBD_OE      ( GPIO_PORTB | GPIO_PF | 21 )
DECL|macro|PB22_PFUSBD_RCV
mdefine_line|#define PB22_PFUSBD_RCV      ( GPIO_PORTB | GPIO_PF | 22 )
DECL|macro|PB23_PF_USBD_SUSPND
mdefine_line|#define PB23_PF_USBD_SUSPND  ( GPIO_PORTB | GPIO_PF | 23 )
DECL|macro|PB24_PF_USBD_VP
mdefine_line|#define PB24_PF_USBD_VP      ( GPIO_PORTB | GPIO_PF | 24 )
DECL|macro|PB25_PF_USBD_VM
mdefine_line|#define PB25_PF_USBD_VM      ( GPIO_PORTB | GPIO_PF | 25 )
DECL|macro|PB26_PF_USBD_VPO
mdefine_line|#define PB26_PF_USBD_VPO     ( GPIO_PORTB | GPIO_PF | 26 )
DECL|macro|PB27_PF_USBD_VMO
mdefine_line|#define PB27_PF_USBD_VMO     ( GPIO_PORTB | GPIO_PF | 27 )
DECL|macro|PB28_PF_UART2_CTS
mdefine_line|#define PB28_PF_UART2_CTS    ( GPIO_PORTB | GPIO_OUT | GPIO_PF | 28 )
DECL|macro|PB29_PF_UART2_RTS
mdefine_line|#define PB29_PF_UART2_RTS    ( GPIO_PORTB | GPIO_IN | GPIO_PF | 29 )
DECL|macro|PB30_PF_UART2_TXD
mdefine_line|#define PB30_PF_UART2_TXD    ( GPIO_PORTB | GPIO_OUT | GPIO_PF | 30 )
DECL|macro|PB31_PF_UART2_RXD
mdefine_line|#define PB31_PF_UART2_RXD    ( GPIO_PORTB | GPIO_IN | GPIO_PF | 31 )
DECL|macro|PC3_PF_SSI_RXFS
mdefine_line|#define PC3_PF_SSI_RXFS      ( GPIO_PORTC | GPIO_PF | 3 )
DECL|macro|PC4_PF_SSI_RXCLK
mdefine_line|#define PC4_PF_SSI_RXCLK     ( GPIO_PORTC | GPIO_PF | 4 )
DECL|macro|PC5_PF_SSI_RXDAT
mdefine_line|#define PC5_PF_SSI_RXDAT     ( GPIO_PORTC | GPIO_IN | GPIO_PF | 5 )
DECL|macro|PC6_PF_SSI_TXDAT
mdefine_line|#define PC6_PF_SSI_TXDAT     ( GPIO_PORTC | GPIO_OUT | GPIO_PF | 6 )
DECL|macro|PC7_PF_SSI_TXFS
mdefine_line|#define PC7_PF_SSI_TXFS      ( GPIO_PORTC | GPIO_PF | 7 )
DECL|macro|PC8_PF_SSI_TXCLK
mdefine_line|#define PC8_PF_SSI_TXCLK     ( GPIO_PORTC | GPIO_PF | 8 )
DECL|macro|PC9_PF_UART1_CTS
mdefine_line|#define PC9_PF_UART1_CTS     ( GPIO_PORTC | GPIO_OUT | GPIO_PF | 9 )
DECL|macro|PC10_PF_UART1_RTS
mdefine_line|#define PC10_PF_UART1_RTS    ( GPIO_PORTC | GPIO_IN | GPIO_PF | 10 )
DECL|macro|PC11_PF_UART1_TXD
mdefine_line|#define PC11_PF_UART1_TXD    ( GPIO_PORTC | GPIO_OUT | GPIO_PF | 11 )
DECL|macro|PC12_PF_UART1_RXD
mdefine_line|#define PC12_PF_UART1_RXD    ( GPIO_PORTC | GPIO_IN | GPIO_PF | 12 )
DECL|macro|PC13_PF_SPI1_SPI_RDY
mdefine_line|#define PC13_PF_SPI1_SPI_RDY ( GPIO_PORTC | GPIO_PF | 13 )
DECL|macro|PC14_PF_SPI1_SCLK
mdefine_line|#define PC14_PF_SPI1_SCLK    ( GPIO_PORTC | GPIO_PF | 14 )
DECL|macro|PC15_PF_SPI1_SS
mdefine_line|#define PC15_PF_SPI1_SS      ( GPIO_PORTC | GPIO_PF | 15 )
DECL|macro|PC16_PF_SPI1_MISO
mdefine_line|#define PC16_PF_SPI1_MISO    ( GPIO_PORTC | GPIO_PF | 16 )
DECL|macro|PC17_PF_SPI1_MOSI
mdefine_line|#define PC17_PF_SPI1_MOSI    ( GPIO_PORTC | GPIO_PF | 17 )
DECL|macro|PD6_PF_LSCLK
mdefine_line|#define PD6_PF_LSCLK         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 6 )
DECL|macro|PD7_PF_REV
mdefine_line|#define PD7_PF_REV           ( GPIO_PORTD | GPIO_PF | 7 )
DECL|macro|PD7_AF_UART2_DTR
mdefine_line|#define PD7_AF_UART2_DTR     ( GPIO_PORTD | GPIO_IN | GPIO_AF | 7 )
DECL|macro|PD7_AIN_SPI2_SCLK
mdefine_line|#define PD7_AIN_SPI2_SCLK    ( GPIO_PORTD | GPIO_AIN | 7 )
DECL|macro|PD8_PF_CLS
mdefine_line|#define PD8_PF_CLS           ( GPIO_PORTD | GPIO_PF | 8 )
DECL|macro|PD8_AF_UART2_DCD
mdefine_line|#define PD8_AF_UART2_DCD     ( GPIO_PORTD | GPIO_OUT | GPIO_AF | 8 )
DECL|macro|PD8_AIN_SPI2_SS
mdefine_line|#define PD8_AIN_SPI2_SS      ( GPIO_PORTD | GPIO_AIN | 8 )
DECL|macro|PD9_PF_PS
mdefine_line|#define PD9_PF_PS            ( GPIO_PORTD | GPIO_PF | 9 )
DECL|macro|PD9_AF_UART2_RI
mdefine_line|#define PD9_AF_UART2_RI      ( GPIO_PORTD | GPIO_OUT | GPIO_AF | 9 )
DECL|macro|PD9_AOUT_SPI2_RXD
mdefine_line|#define PD9_AOUT_SPI2_RXD    ( GPIO_PORTD | GPIO_IN | GPIO_AOUT | 9 )
DECL|macro|PD10_PF_SPL_SPR
mdefine_line|#define PD10_PF_SPL_SPR      ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 10 )
DECL|macro|PD10_AF_UART2_DSR
mdefine_line|#define PD10_AF_UART2_DSR    ( GPIO_PORTD | GPIO_OUT | GPIO_AF | 10 )
DECL|macro|PD10_AIN_SPI2_TXD
mdefine_line|#define PD10_AIN_SPI2_TXD    ( GPIO_PORTD | GPIO_OUT | GPIO_AIN | 10 )
DECL|macro|PD11_PF_CONTRAST
mdefine_line|#define PD11_PF_CONTRAST     ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 11 )
DECL|macro|PD12_PF_ACD_OE
mdefine_line|#define PD12_PF_ACD_OE       ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 12 )
DECL|macro|PD13_PF_LP_HSYNC
mdefine_line|#define PD13_PF_LP_HSYNC     ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 13 )
DECL|macro|PD14_PF_FLM_VSYNC
mdefine_line|#define PD14_PF_FLM_VSYNC    ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 14 )
DECL|macro|PD15_PF_LD0
mdefine_line|#define PD15_PF_LD0          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 15 )
DECL|macro|PD16_PF_LD1
mdefine_line|#define PD16_PF_LD1          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 16 )
DECL|macro|PD17_PF_LD2
mdefine_line|#define PD17_PF_LD2          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 17 )
DECL|macro|PD18_PF_LD3
mdefine_line|#define PD18_PF_LD3          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 18 )
DECL|macro|PD19_PF_LD4
mdefine_line|#define PD19_PF_LD4          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 19 )
DECL|macro|PD20_PF_LD5
mdefine_line|#define PD20_PF_LD5          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 20 )
DECL|macro|PD21_PF_LD6
mdefine_line|#define PD21_PF_LD6          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 21 )
DECL|macro|PD22_PF_LD7
mdefine_line|#define PD22_PF_LD7          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 22 )
DECL|macro|PD23_PF_LD8
mdefine_line|#define PD23_PF_LD8          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 23 )
DECL|macro|PD24_PF_LD9
mdefine_line|#define PD24_PF_LD9          ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 24 )
DECL|macro|PD25_PF_LD10
mdefine_line|#define PD25_PF_LD10         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 25 )
DECL|macro|PD26_PF_LD11
mdefine_line|#define PD26_PF_LD11         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 26 )
DECL|macro|PD27_PF_LD12
mdefine_line|#define PD27_PF_LD12         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 27 )
DECL|macro|PD28_PF_LD13
mdefine_line|#define PD28_PF_LD13         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 28 )
DECL|macro|PD29_PF_LD14
mdefine_line|#define PD29_PF_LD14         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 29 )
DECL|macro|PD30_PF_LD15
mdefine_line|#define PD30_PF_LD15         ( GPIO_PORTD | GPIO_OUT | GPIO_PF | 30 )
DECL|macro|PD31_PF_TMR2OUT
mdefine_line|#define PD31_PF_TMR2OUT      ( GPIO_PORTD | GPIO_PF | 31 )
DECL|macro|PD31_BIN_SPI2_TXD
mdefine_line|#define PD31_BIN_SPI2_TXD    ( GPIO_PORTD | GPIO_BIN | 31 )
multiline_comment|/*&n; *  DMA Controller&n; */
DECL|macro|DCR
mdefine_line|#define DCR     __REG(IMX_DMAC_BASE +0x00)&t;/* DMA Control Register */
DECL|macro|DISR
mdefine_line|#define DISR    __REG(IMX_DMAC_BASE +0x04)&t;/* DMA Interrupt status Register */
DECL|macro|DIMR
mdefine_line|#define DIMR    __REG(IMX_DMAC_BASE +0x08)&t;/* DMA Interrupt mask Register */
DECL|macro|DBTOSR
mdefine_line|#define DBTOSR  __REG(IMX_DMAC_BASE +0x0c)&t;/* DMA Burst timeout status Register */
DECL|macro|DRTOSR
mdefine_line|#define DRTOSR  __REG(IMX_DMAC_BASE +0x10)&t;/* DMA Request timeout Register */
DECL|macro|DSESR
mdefine_line|#define DSESR   __REG(IMX_DMAC_BASE +0x14)&t;/* DMA Transfer Error Status Register */
DECL|macro|DBOSR
mdefine_line|#define DBOSR   __REG(IMX_DMAC_BASE +0x18)&t;/* DMA Buffer overflow status Register */
DECL|macro|DBTOCR
mdefine_line|#define DBTOCR  __REG(IMX_DMAC_BASE +0x1c)&t;/* DMA Burst timeout control Register */
DECL|macro|WSRA
mdefine_line|#define WSRA    __REG(IMX_DMAC_BASE +0x40)&t;/* W-Size Register A */
DECL|macro|XSRA
mdefine_line|#define XSRA    __REG(IMX_DMAC_BASE +0x44)&t;/* X-Size Register A */
DECL|macro|YSRA
mdefine_line|#define YSRA    __REG(IMX_DMAC_BASE +0x48)&t;/* Y-Size Register A */
DECL|macro|WSRB
mdefine_line|#define WSRB    __REG(IMX_DMAC_BASE +0x4c)&t;/* W-Size Register B */
DECL|macro|XSRB
mdefine_line|#define XSRB    __REG(IMX_DMAC_BASE +0x50)&t;/* X-Size Register B */
DECL|macro|YSRB
mdefine_line|#define YSRB    __REG(IMX_DMAC_BASE +0x54)&t;/* Y-Size Register B */
DECL|macro|SAR
mdefine_line|#define SAR(x)  __REG2( IMX_DMAC_BASE + 0x80, (x) &lt;&lt; 6)&t;/* Source Address Registers */
DECL|macro|DAR
mdefine_line|#define DAR(x)  __REG2( IMX_DMAC_BASE + 0x84, (x) &lt;&lt; 6)&t;/* Destination Address Registers */
DECL|macro|CNTR
mdefine_line|#define CNTR(x) __REG2( IMX_DMAC_BASE + 0x88, (x) &lt;&lt; 6)&t;/* Count Registers */
DECL|macro|CCR
mdefine_line|#define CCR(x)  __REG2( IMX_DMAC_BASE + 0x8c, (x) &lt;&lt; 6)&t;/*&#xfffd;Control Registers */
DECL|macro|RSSR
mdefine_line|#define RSSR(x) __REG2( IMX_DMAC_BASE + 0x90, (x) &lt;&lt; 6)&t;/* Request source select Registers */
DECL|macro|BLR
mdefine_line|#define BLR(x)  __REG2( IMX_DMAC_BASE + 0x94, (x) &lt;&lt; 6)&t;/* Burst length Registers */
DECL|macro|RTOR
mdefine_line|#define RTOR(x) __REG2( IMX_DMAC_BASE + 0x98, (x) &lt;&lt; 6)&t;/* Request timeout Registers */
DECL|macro|BUCR
mdefine_line|#define BUCR(x) __REG2( IMX_DMAC_BASE + 0x98, (x) &lt;&lt; 6)&t;/* Bus Utilization Registers */
DECL|macro|DCR_DRST
mdefine_line|#define DCR_DRST           (1&lt;&lt;1)
DECL|macro|DCR_DEN
mdefine_line|#define DCR_DEN            (1&lt;&lt;0)
DECL|macro|DBTOCR_EN
mdefine_line|#define DBTOCR_EN          (1&lt;&lt;15)
DECL|macro|DBTOCR_CNT
mdefine_line|#define DBTOCR_CNT(x)      ((x) &amp; 0x7fff )
DECL|macro|CNTR_CNT
mdefine_line|#define CNTR_CNT(x)        ((x) &amp; 0xffffff )
DECL|macro|CCR_DMOD_LINEAR
mdefine_line|#define CCR_DMOD_LINEAR    ( 0x0 &lt;&lt; 12 )
DECL|macro|CCR_DMOD_2D
mdefine_line|#define CCR_DMOD_2D        ( 0x1 &lt;&lt; 12 )
DECL|macro|CCR_DMOD_FIFO
mdefine_line|#define CCR_DMOD_FIFO      ( 0x2 &lt;&lt; 12 )
DECL|macro|CCR_DMOD_EOBFIFO
mdefine_line|#define CCR_DMOD_EOBFIFO   ( 0x3 &lt;&lt; 12 )
DECL|macro|CCR_SMOD_LINEAR
mdefine_line|#define CCR_SMOD_LINEAR    ( 0x0 &lt;&lt; 10 )
DECL|macro|CCR_SMOD_2D
mdefine_line|#define CCR_SMOD_2D        ( 0x1 &lt;&lt; 10 )
DECL|macro|CCR_SMOD_FIFO
mdefine_line|#define CCR_SMOD_FIFO      ( 0x2 &lt;&lt; 10 )
DECL|macro|CCR_SMOD_EOBFIFO
mdefine_line|#define CCR_SMOD_EOBFIFO   ( 0x3 &lt;&lt; 10 )
DECL|macro|CCR_MDIR_DEC
mdefine_line|#define CCR_MDIR_DEC       (1&lt;&lt;9)
DECL|macro|CCR_MSEL_B
mdefine_line|#define CCR_MSEL_B         (1&lt;&lt;8)
DECL|macro|CCR_DSIZ_32
mdefine_line|#define CCR_DSIZ_32        ( 0x0 &lt;&lt; 6 )
DECL|macro|CCR_DSIZ_8
mdefine_line|#define CCR_DSIZ_8         ( 0x1 &lt;&lt; 6 )
DECL|macro|CCR_DSIZ_16
mdefine_line|#define CCR_DSIZ_16        ( 0x2 &lt;&lt; 6 )
DECL|macro|CCR_SSIZ_32
mdefine_line|#define CCR_SSIZ_32        ( 0x0 &lt;&lt; 4 )
DECL|macro|CCR_SSIZ_8
mdefine_line|#define CCR_SSIZ_8         ( 0x1 &lt;&lt; 4 )
DECL|macro|CCR_SSIZ_16
mdefine_line|#define CCR_SSIZ_16        ( 0x2 &lt;&lt; 4 )
DECL|macro|CCR_REN
mdefine_line|#define CCR_REN            (1&lt;&lt;3)
DECL|macro|CCR_RPT
mdefine_line|#define CCR_RPT            (1&lt;&lt;2)
DECL|macro|CCR_FRC
mdefine_line|#define CCR_FRC            (1&lt;&lt;1)
DECL|macro|CCR_CEN
mdefine_line|#define CCR_CEN            (1&lt;&lt;0)
DECL|macro|RTOR_EN
mdefine_line|#define RTOR_EN            (1&lt;&lt;15)
DECL|macro|RTOR_CLK
mdefine_line|#define RTOR_CLK           (1&lt;&lt;14)
DECL|macro|RTOR_PSC
mdefine_line|#define RTOR_PSC           (1&lt;&lt;13)
multiline_comment|/*&n; *  Interrupt controller&n; */
DECL|macro|IMX_INTCNTL
mdefine_line|#define IMX_INTCNTL        __REG(IMX_AITC_BASE+0x00)
DECL|macro|INTCNTL_FIAD
mdefine_line|#define INTCNTL_FIAD       (1&lt;&lt;19)
DECL|macro|INTCNTL_NIAD
mdefine_line|#define INTCNTL_NIAD       (1&lt;&lt;20)
DECL|macro|IMX_NIMASK
mdefine_line|#define IMX_NIMASK         __REG(IMX_AITC_BASE+0x04)
DECL|macro|IMX_INTENNUM
mdefine_line|#define IMX_INTENNUM       __REG(IMX_AITC_BASE+0x08)
DECL|macro|IMX_INTDISNUM
mdefine_line|#define IMX_INTDISNUM      __REG(IMX_AITC_BASE+0x0c)
DECL|macro|IMX_INTENABLEH
mdefine_line|#define IMX_INTENABLEH     __REG(IMX_AITC_BASE+0x10)
DECL|macro|IMX_INTENABLEL
mdefine_line|#define IMX_INTENABLEL     __REG(IMX_AITC_BASE+0x14)
multiline_comment|/*&n; *  General purpose timers&n; */
DECL|macro|IMX_TCTL
mdefine_line|#define IMX_TCTL(x)        __REG( 0x00 + (x))
DECL|macro|TCTL_SWR
mdefine_line|#define TCTL_SWR           (1&lt;&lt;15)
DECL|macro|TCTL_FRR
mdefine_line|#define TCTL_FRR           (1&lt;&lt;8)
DECL|macro|TCTL_CAP_RIS
mdefine_line|#define TCTL_CAP_RIS       (1&lt;&lt;6)
DECL|macro|TCTL_CAP_FAL
mdefine_line|#define TCTL_CAP_FAL       (2&lt;&lt;6)
DECL|macro|TCTL_CAP_RIS_FAL
mdefine_line|#define TCTL_CAP_RIS_FAL   (3&lt;&lt;6)
DECL|macro|TCTL_OM
mdefine_line|#define TCTL_OM            (1&lt;&lt;5)
DECL|macro|TCTL_IRQEN
mdefine_line|#define TCTL_IRQEN         (1&lt;&lt;4)
DECL|macro|TCTL_CLK_PCLK1
mdefine_line|#define TCTL_CLK_PCLK1     (1&lt;&lt;1)
DECL|macro|TCTL_CLK_PCLK1_16
mdefine_line|#define TCTL_CLK_PCLK1_16  (2&lt;&lt;1)
DECL|macro|TCTL_CLK_TIN
mdefine_line|#define TCTL_CLK_TIN       (3&lt;&lt;1)
DECL|macro|TCTL_CLK_32
mdefine_line|#define TCTL_CLK_32        (4&lt;&lt;1)
DECL|macro|TCTL_TEN
mdefine_line|#define TCTL_TEN           (1&lt;&lt;0)
DECL|macro|IMX_TPRER
mdefine_line|#define IMX_TPRER(x)       __REG( 0x04 + (x))
DECL|macro|IMX_TCMP
mdefine_line|#define IMX_TCMP(x)        __REG( 0x08 + (x))
DECL|macro|IMX_TCR
mdefine_line|#define IMX_TCR(x)         __REG( 0x0C + (x))
DECL|macro|IMX_TCN
mdefine_line|#define IMX_TCN(x)         __REG( 0x10 + (x))
DECL|macro|IMX_TSTAT
mdefine_line|#define IMX_TSTAT(x)       __REG( 0x14 + (x))
DECL|macro|TSTAT_CAPT
mdefine_line|#define TSTAT_CAPT         (1&lt;&lt;1)
DECL|macro|TSTAT_COMP
mdefine_line|#define TSTAT_COMP         (1&lt;&lt;0)
multiline_comment|/*&n; * LCD Controller&n; */
DECL|macro|LCDC_SSA
mdefine_line|#define LCDC_SSA&t;__REG(IMX_LCDC_BASE+0x00)
DECL|macro|LCDC_SIZE
mdefine_line|#define LCDC_SIZE&t;__REG(IMX_LCDC_BASE+0x04)
DECL|macro|SIZE_XMAX
mdefine_line|#define SIZE_XMAX(x)&t;((((x) &gt;&gt; 4) &amp; 0x3f) &lt;&lt; 20)
DECL|macro|SIZE_YMAX
mdefine_line|#define SIZE_YMAX(y)    ( (y) &amp; 0x1ff )
DECL|macro|LCDC_VPW
mdefine_line|#define LCDC_VPW&t;__REG(IMX_LCDC_BASE+0x08)
DECL|macro|VPW_VPW
mdefine_line|#define VPW_VPW(x)&t;( (x) &amp; 0x3ff )
DECL|macro|LCDC_CPOS
mdefine_line|#define LCDC_CPOS&t;__REG(IMX_LCDC_BASE+0x0C)
DECL|macro|CPOS_CC1
mdefine_line|#define CPOS_CC1        (1&lt;&lt;31)
DECL|macro|CPOS_CC0
mdefine_line|#define CPOS_CC0        (1&lt;&lt;30)
DECL|macro|CPOS_OP
mdefine_line|#define CPOS_OP         (1&lt;&lt;28)
DECL|macro|CPOS_CXP
mdefine_line|#define CPOS_CXP(x)     (((x) &amp; 3ff) &lt;&lt; 16)
DECL|macro|CPOS_CYP
mdefine_line|#define CPOS_CYP(y)     ((y) &amp; 0x1ff)
DECL|macro|LCDC_LCWHB
mdefine_line|#define LCDC_LCWHB&t;__REG(IMX_LCDC_BASE+0x10)
DECL|macro|LCWHB_BK_EN
mdefine_line|#define LCWHB_BK_EN     (1&lt;&lt;31)
DECL|macro|LCWHB_CW
mdefine_line|#define LCWHB_CW(w)     (((w) &amp; 0x1f) &lt;&lt; 24)
DECL|macro|LCWHB_CH
mdefine_line|#define LCWHB_CH(h)     (((h) &amp; 0x1f) &lt;&lt; 16)
DECL|macro|LCWHB_BD
mdefine_line|#define LCWHB_BD(x)     ((x) &amp; 0xff)
DECL|macro|LCDC_LCHCC
mdefine_line|#define LCDC_LCHCC&t;__REG(IMX_LCDC_BASE+0x14)
DECL|macro|LCHCC_CUR_COL_R
mdefine_line|#define LCHCC_CUR_COL_R(r) (((r) &amp; 0x1f) &lt;&lt; 11)
DECL|macro|LCHCC_CUR_COL_G
mdefine_line|#define LCHCC_CUR_COL_G(g) (((g) &amp; 0x3f) &lt;&lt; 5)
DECL|macro|LCHCC_CUR_COL_B
mdefine_line|#define LCHCC_CUR_COL_B(b) ((b) &amp; 0x1f)
DECL|macro|LCDC_PCR
mdefine_line|#define LCDC_PCR&t;__REG(IMX_LCDC_BASE+0x18)
DECL|macro|PCR_TFT
mdefine_line|#define PCR_TFT         (1&lt;&lt;31)
DECL|macro|PCR_COLOR
mdefine_line|#define PCR_COLOR       (1&lt;&lt;30)
DECL|macro|PCR_PBSIZ_1
mdefine_line|#define PCR_PBSIZ_1     (0&lt;&lt;28)
DECL|macro|PCR_PBSIZ_2
mdefine_line|#define PCR_PBSIZ_2     (1&lt;&lt;28)
DECL|macro|PCR_PBSIZ_4
mdefine_line|#define PCR_PBSIZ_4     (2&lt;&lt;28)
DECL|macro|PCR_PBSIZ_8
mdefine_line|#define PCR_PBSIZ_8     (3&lt;&lt;28)
DECL|macro|PCR_BPIX_1
mdefine_line|#define PCR_BPIX_1      (0&lt;&lt;25)
DECL|macro|PCR_BPIX_2
mdefine_line|#define PCR_BPIX_2      (1&lt;&lt;25)
DECL|macro|PCR_BPIX_4
mdefine_line|#define PCR_BPIX_4      (2&lt;&lt;25)
DECL|macro|PCR_BPIX_8
mdefine_line|#define PCR_BPIX_8      (3&lt;&lt;25)
DECL|macro|PCR_BPIX_12
mdefine_line|#define PCR_BPIX_12     (4&lt;&lt;25)
DECL|macro|PCR_BPIX_16
mdefine_line|#define PCR_BPIX_16     (4&lt;&lt;25)
DECL|macro|PCR_PIXPOL
mdefine_line|#define PCR_PIXPOL      (1&lt;&lt;24)
DECL|macro|PCR_FLMPOL
mdefine_line|#define PCR_FLMPOL      (1&lt;&lt;23)
DECL|macro|PCR_LPPOL
mdefine_line|#define PCR_LPPOL       (1&lt;&lt;22)
DECL|macro|PCR_CLKPOL
mdefine_line|#define PCR_CLKPOL      (1&lt;&lt;21)
DECL|macro|PCR_OEPOL
mdefine_line|#define PCR_OEPOL       (1&lt;&lt;20)
DECL|macro|PCR_SCLKIDLE
mdefine_line|#define PCR_SCLKIDLE    (1&lt;&lt;19)
DECL|macro|PCR_END_SEL
mdefine_line|#define PCR_END_SEL     (1&lt;&lt;18)
DECL|macro|PCR_END_BYTE_SWAP
mdefine_line|#define PCR_END_BYTE_SWAP (1&lt;&lt;17)
DECL|macro|PCR_REV_VS
mdefine_line|#define PCR_REV_VS      (1&lt;&lt;16)
DECL|macro|PCR_ACD_SEL
mdefine_line|#define PCR_ACD_SEL     (1&lt;&lt;15)
DECL|macro|PCR_ACD
mdefine_line|#define PCR_ACD(x)      (((x) &amp; 0x7f) &lt;&lt; 8)
DECL|macro|PCR_SCLK_SEL
mdefine_line|#define PCR_SCLK_SEL    (1&lt;&lt;7)
DECL|macro|PCR_SHARP
mdefine_line|#define PCR_SHARP       (1&lt;&lt;6)
DECL|macro|PCR_PCD
mdefine_line|#define PCR_PCD(x)      ((x) &amp; 0x3f)
DECL|macro|LCDC_HCR
mdefine_line|#define LCDC_HCR&t;__REG(IMX_LCDC_BASE+0x1C)
DECL|macro|HCR_H_WIDTH
mdefine_line|#define HCR_H_WIDTH(x)  (((x) &amp; 0x3f) &lt;&lt; 26)
DECL|macro|HCR_H_WAIT_1
mdefine_line|#define HCR_H_WAIT_1(x) (((x) &amp; 0xff) &lt;&lt; 8)
DECL|macro|HCR_H_WAIT_2
mdefine_line|#define HCR_H_WAIT_2(x) ((x) &amp; 0xff)
DECL|macro|LCDC_VCR
mdefine_line|#define LCDC_VCR&t;__REG(IMX_LCDC_BASE+0x20)
DECL|macro|VCR_V_WIDTH
mdefine_line|#define VCR_V_WIDTH(x)  (((x) &amp; 0x3f) &lt;&lt; 26)
DECL|macro|VCR_V_WAIT_1
mdefine_line|#define VCR_V_WAIT_1(x) (((x) &amp; 0xff) &lt;&lt; 8)
DECL|macro|VCR_V_WAIT_2
mdefine_line|#define VCR_V_WAIT_2(x) ((x) &amp; 0xff)
DECL|macro|LCDC_POS
mdefine_line|#define LCDC_POS&t;__REG(IMX_LCDC_BASE+0x24)
DECL|macro|POS_POS
mdefine_line|#define POS_POS(x)      ((x) &amp; 1f)
DECL|macro|LCDC_LSCR1
mdefine_line|#define LCDC_LSCR1&t;__REG(IMX_LCDC_BASE+0x28)
DECL|macro|LSCR1_PS_RISE_DELAY
mdefine_line|#define LSCR1_PS_RISE_DELAY(x)    (((x) &amp; 0x7f) &lt;&lt; 26)
DECL|macro|LSCR1_CLS_RISE_DELAY
mdefine_line|#define LSCR1_CLS_RISE_DELAY(x)   (((x) &amp; 0x3f) &lt;&lt; 16)
DECL|macro|LSCR1_REV_TOGGLE_DELAY
mdefine_line|#define LSCR1_REV_TOGGLE_DELAY(x) (((x) &amp; 0xf) &lt;&lt; 8)
DECL|macro|LSCR1_GRAY2
mdefine_line|#define LSCR1_GRAY2(x)            (((x) &amp; 0xf) &lt;&lt; 4)
DECL|macro|LSCR1_GRAY1
mdefine_line|#define LSCR1_GRAY1(x)            (((x) &amp; 0xf))
DECL|macro|LCDC_PWMR
mdefine_line|#define LCDC_PWMR&t;__REG(IMX_LCDC_BASE+0x2C)
DECL|macro|PWMR_CLS
mdefine_line|#define PWMR_CLS(x)     (((x) &amp; 0x1ff) &lt;&lt; 16)
DECL|macro|PWMR_LDMSK
mdefine_line|#define PWMR_LDMSK      (1&lt;&lt;15)
DECL|macro|PWMR_SCR1
mdefine_line|#define PWMR_SCR1       (1&lt;&lt;10)
DECL|macro|PWMR_SCR0
mdefine_line|#define PWMR_SCR0       (1&lt;&lt;9)
DECL|macro|PWMR_CC_EN
mdefine_line|#define PWMR_CC_EN      (1&lt;&lt;8)
DECL|macro|PWMR_PW
mdefine_line|#define PWMR_PW(x)      ((x) &amp; 0xff)
DECL|macro|LCDC_DMACR
mdefine_line|#define LCDC_DMACR&t;__REG(IMX_LCDC_BASE+0x30)
DECL|macro|DMACR_BURST
mdefine_line|#define DMACR_BURST     (1&lt;&lt;31)
DECL|macro|DMACR_HM
mdefine_line|#define DMACR_HM(x)     (((x) &amp; 0xf) &lt;&lt; 16)
DECL|macro|DMACR_TM
mdefine_line|#define DMACR_TM(x)     ((x) &amp;0xf)
DECL|macro|LCDC_RMCR
mdefine_line|#define LCDC_RMCR&t;__REG(IMX_LCDC_BASE+0x34)
DECL|macro|RMCR_LCDC_EN
mdefine_line|#define RMCR_LCDC_EN&t;&t;(1&lt;&lt;1)
DECL|macro|RMCR_SELF_REF
mdefine_line|#define RMCR_SELF_REF&t;&t;(1&lt;&lt;0)
DECL|macro|LCDC_LCDICR
mdefine_line|#define LCDC_LCDICR&t;__REG(IMX_LCDC_BASE+0x38)
DECL|macro|LCDICR_INT_SYN
mdefine_line|#define LCDICR_INT_SYN  (1&lt;&lt;2)
DECL|macro|LCDICR_INT_CON
mdefine_line|#define LCDICR_INT_CON  (1)
DECL|macro|LCDC_LCDISR
mdefine_line|#define LCDC_LCDISR&t;__REG(IMX_LCDC_BASE+0x40)
DECL|macro|LCDISR_UDR_ERR
mdefine_line|#define LCDISR_UDR_ERR (1&lt;&lt;3)
DECL|macro|LCDISR_ERR_RES
mdefine_line|#define LCDISR_ERR_RES (1&lt;&lt;2)
DECL|macro|LCDISR_EOF
mdefine_line|#define LCDISR_EOF     (1&lt;&lt;1)
DECL|macro|LCDISR_BOF
mdefine_line|#define LCDISR_BOF     (1&lt;&lt;0)
multiline_comment|/*&n; *  UART Module. Takes the UART base address as argument&n; */
DECL|macro|URXD0
mdefine_line|#define URXD0(x) __REG( 0x0 + (x)) /* Receiver Register */
DECL|macro|URTX0
mdefine_line|#define URTX0(x) __REG( 0x40 + (x)) /* Transmitter Register */
DECL|macro|UCR1
mdefine_line|#define UCR1(x)  __REG( 0x80 + (x)) /* Control Register 1 */
DECL|macro|UCR2
mdefine_line|#define UCR2(x)  __REG( 0x84 + (x)) /* Control Register 2 */
DECL|macro|UCR3
mdefine_line|#define UCR3(x)  __REG( 0x88 + (x)) /* Control Register 3 */
DECL|macro|UCR4
mdefine_line|#define UCR4(x)  __REG( 0x8c + (x)) /* Control Register 4 */
DECL|macro|UFCR
mdefine_line|#define UFCR(x)  __REG( 0x90 + (x)) /* FIFO Control Register */
DECL|macro|USR1
mdefine_line|#define USR1(x)  __REG( 0x94 + (x)) /* Status Register 1 */
DECL|macro|USR2
mdefine_line|#define USR2(x)  __REG( 0x98 + (x)) /* Status Register 2 */
DECL|macro|UESC
mdefine_line|#define UESC(x)  __REG( 0x9c + (x)) /* Escape Character Register */
DECL|macro|UTIM
mdefine_line|#define UTIM(x)  __REG( 0xa0 + (x)) /* Escape Timer Register */
DECL|macro|UBIR
mdefine_line|#define UBIR(x)  __REG( 0xa4 + (x)) /* BRM Incremental Register */
DECL|macro|UBMR
mdefine_line|#define UBMR(x)  __REG( 0xa8 + (x)) /* BRM Modulator Register */
DECL|macro|UBRC
mdefine_line|#define UBRC(x)  __REG( 0xac + (x)) /* Baud Rate Count Register */
DECL|macro|BIPR1
mdefine_line|#define BIPR1(x) __REG( 0xb0 + (x)) /* Incremental Preset Register 1 */
DECL|macro|BIPR2
mdefine_line|#define BIPR2(x) __REG( 0xb4 + (x)) /* Incremental Preset Register 2 */
DECL|macro|BIPR3
mdefine_line|#define BIPR3(x) __REG( 0xb8 + (x)) /* Incremental Preset Register 3 */
DECL|macro|BIPR4
mdefine_line|#define BIPR4(x) __REG( 0xbc + (x)) /* Incremental Preset Register 4 */
DECL|macro|BMPR1
mdefine_line|#define BMPR1(x) __REG( 0xc0 + (x)) /* BRM Modulator Register 1 */
DECL|macro|BMPR2
mdefine_line|#define BMPR2(x) __REG( 0xc4 + (x)) /* BRM Modulator Register 2 */
DECL|macro|BMPR3
mdefine_line|#define BMPR3(x) __REG( 0xc8 + (x)) /* BRM Modulator Register 3 */
DECL|macro|BMPR4
mdefine_line|#define BMPR4(x) __REG( 0xcc + (x)) /* BRM Modulator Register 4 */
DECL|macro|UTS
mdefine_line|#define UTS(x)   __REG( 0xd0 + (x)) /* UART Test Register */
multiline_comment|/* UART Control Register Bit Fields.*/
DECL|macro|URXD_CHARRDY
mdefine_line|#define  URXD_CHARRDY    (1&lt;&lt;15)
DECL|macro|URXD_ERR
mdefine_line|#define  URXD_ERR        (1&lt;&lt;14)
DECL|macro|URXD_OVRRUN
mdefine_line|#define  URXD_OVRRUN     (1&lt;&lt;13)
DECL|macro|URXD_FRMERR
mdefine_line|#define  URXD_FRMERR     (1&lt;&lt;12)
DECL|macro|URXD_BRK
mdefine_line|#define  URXD_BRK        (1&lt;&lt;11)
DECL|macro|URXD_PRERR
mdefine_line|#define  URXD_PRERR      (1&lt;&lt;10)
DECL|macro|UCR1_ADEN
mdefine_line|#define  UCR1_ADEN       (1&lt;&lt;15) /* Auto dectect interrupt */
DECL|macro|UCR1_ADBR
mdefine_line|#define  UCR1_ADBR       (1&lt;&lt;14) /* Auto detect baud rate */
DECL|macro|UCR1_TRDYEN
mdefine_line|#define  UCR1_TRDYEN     (1&lt;&lt;13) /* Transmitter ready interrupt enable */
DECL|macro|UCR1_IDEN
mdefine_line|#define  UCR1_IDEN       (1&lt;&lt;12) /* Idle condition interrupt */
DECL|macro|UCR1_RRDYEN
mdefine_line|#define  UCR1_RRDYEN     (1&lt;&lt;9)&t; /* Recv ready interrupt enable */
DECL|macro|UCR1_RDMAEN
mdefine_line|#define  UCR1_RDMAEN     (1&lt;&lt;8)&t; /* Recv ready DMA enable */
DECL|macro|UCR1_IREN
mdefine_line|#define  UCR1_IREN       (1&lt;&lt;7)&t; /* Infrared interface enable */
DECL|macro|UCR1_TXMPTYEN
mdefine_line|#define  UCR1_TXMPTYEN   (1&lt;&lt;6)&t; /* Transimitter empty interrupt enable */
DECL|macro|UCR1_RTSDEN
mdefine_line|#define  UCR1_RTSDEN     (1&lt;&lt;5)&t; /* RTS delta interrupt enable */
DECL|macro|UCR1_SNDBRK
mdefine_line|#define  UCR1_SNDBRK     (1&lt;&lt;4)&t; /* Send break */
DECL|macro|UCR1_TDMAEN
mdefine_line|#define  UCR1_TDMAEN     (1&lt;&lt;3)&t; /* Transmitter ready DMA enable */
DECL|macro|UCR1_UARTCLKEN
mdefine_line|#define  UCR1_UARTCLKEN  (1&lt;&lt;2)&t; /* UART clock enabled */
DECL|macro|UCR1_DOZE
mdefine_line|#define  UCR1_DOZE       (1&lt;&lt;1)&t; /* Doze */
DECL|macro|UCR1_UARTEN
mdefine_line|#define  UCR1_UARTEN     (1&lt;&lt;0)&t; /* UART enabled */
DECL|macro|UCR2_ESCI
mdefine_line|#define  UCR2_ESCI     &t; (1&lt;&lt;15) /* Escape seq interrupt enable */
DECL|macro|UCR2_IRTS
mdefine_line|#define  UCR2_IRTS  &t; (1&lt;&lt;14) /* Ignore RTS pin */
DECL|macro|UCR2_CTSC
mdefine_line|#define  UCR2_CTSC  &t; (1&lt;&lt;13) /* CTS pin control */
DECL|macro|UCR2_CTS
mdefine_line|#define  UCR2_CTS        (1&lt;&lt;12) /* Clear to send */
DECL|macro|UCR2_ESCEN
mdefine_line|#define  UCR2_ESCEN      (1&lt;&lt;11) /* Escape enable */
DECL|macro|UCR2_PREN
mdefine_line|#define  UCR2_PREN       (1&lt;&lt;8)  /* Parity enable */
DECL|macro|UCR2_PROE
mdefine_line|#define  UCR2_PROE       (1&lt;&lt;7)  /* Parity odd/even */
DECL|macro|UCR2_STPB
mdefine_line|#define  UCR2_STPB       (1&lt;&lt;6)&t; /* Stop */
DECL|macro|UCR2_WS
mdefine_line|#define  UCR2_WS         (1&lt;&lt;5)&t; /* Word size */
DECL|macro|UCR2_RTSEN
mdefine_line|#define  UCR2_RTSEN      (1&lt;&lt;4)&t; /* Request to send interrupt enable */
DECL|macro|UCR2_TXEN
mdefine_line|#define  UCR2_TXEN       (1&lt;&lt;2)&t; /* Transmitter enabled */
DECL|macro|UCR2_RXEN
mdefine_line|#define  UCR2_RXEN       (1&lt;&lt;1)&t; /* Receiver enabled */
DECL|macro|UCR2_SRST
mdefine_line|#define  UCR2_SRST &t; (1&lt;&lt;0)&t; /* SW reset */
DECL|macro|UCR3_DTREN
mdefine_line|#define  UCR3_DTREN &t; (1&lt;&lt;13) /* DTR interrupt enable */
DECL|macro|UCR3_PARERREN
mdefine_line|#define  UCR3_PARERREN   (1&lt;&lt;12) /* Parity enable */
DECL|macro|UCR3_FRAERREN
mdefine_line|#define  UCR3_FRAERREN   (1&lt;&lt;11) /* Frame error interrupt enable */
DECL|macro|UCR3_DSR
mdefine_line|#define  UCR3_DSR        (1&lt;&lt;10) /* Data set ready */
DECL|macro|UCR3_DCD
mdefine_line|#define  UCR3_DCD        (1&lt;&lt;9)  /* Data carrier detect */
DECL|macro|UCR3_RI
mdefine_line|#define  UCR3_RI         (1&lt;&lt;8)  /* Ring indicator */
DECL|macro|UCR3_TIMEOUTEN
mdefine_line|#define  UCR3_TIMEOUTEN  (1&lt;&lt;7)  /* Timeout interrupt enable */
DECL|macro|UCR3_RXDSEN
mdefine_line|#define  UCR3_RXDSEN&t; (1&lt;&lt;6)  /* Receive status interrupt enable */
DECL|macro|UCR3_AIRINTEN
mdefine_line|#define  UCR3_AIRINTEN   (1&lt;&lt;5)  /* Async IR wake interrupt enable */
DECL|macro|UCR3_AWAKEN
mdefine_line|#define  UCR3_AWAKEN&t; (1&lt;&lt;4)  /* Async wake interrupt enable */
DECL|macro|UCR3_REF25
mdefine_line|#define  UCR3_REF25 &t; (1&lt;&lt;3)  /* Ref freq 25 MHz */
DECL|macro|UCR3_REF30
mdefine_line|#define  UCR3_REF30 &t; (1&lt;&lt;2)  /* Ref Freq 30 MHz */
DECL|macro|UCR3_INVT
mdefine_line|#define  UCR3_INVT  &t; (1&lt;&lt;1)  /* Inverted Infrared transmission */
DECL|macro|UCR3_BPEN
mdefine_line|#define  UCR3_BPEN  &t; (1&lt;&lt;0)  /* Preset registers enable */
DECL|macro|UCR4_CTSTL_32
mdefine_line|#define  UCR4_CTSTL_32   (32&lt;&lt;10) /* CTS trigger level (32 chars) */
DECL|macro|UCR4_INVR
mdefine_line|#define  UCR4_INVR  &t; (1&lt;&lt;9)  /* Inverted infrared reception */
DECL|macro|UCR4_ENIRI
mdefine_line|#define  UCR4_ENIRI &t; (1&lt;&lt;8)  /* Serial infrared interrupt enable */
DECL|macro|UCR4_WKEN
mdefine_line|#define  UCR4_WKEN  &t; (1&lt;&lt;7)  /* Wake interrupt enable */
DECL|macro|UCR4_REF16
mdefine_line|#define  UCR4_REF16 &t; (1&lt;&lt;6)  /* Ref freq 16 MHz */
DECL|macro|UCR4_IRSC
mdefine_line|#define  UCR4_IRSC  &t; (1&lt;&lt;5)  /* IR special case */
DECL|macro|UCR4_TCEN
mdefine_line|#define  UCR4_TCEN  &t; (1&lt;&lt;3)  /* Transmit complete interrupt enable */
DECL|macro|UCR4_BKEN
mdefine_line|#define  UCR4_BKEN  &t; (1&lt;&lt;2)  /* Break condition interrupt enable */
DECL|macro|UCR4_OREN
mdefine_line|#define  UCR4_OREN  &t; (1&lt;&lt;1)  /* Receiver overrun interrupt enable */
DECL|macro|UCR4_DREN
mdefine_line|#define  UCR4_DREN  &t; (1&lt;&lt;0)  /* Recv data ready interrupt enable */
DECL|macro|UFCR_RXTL_SHF
mdefine_line|#define  UFCR_RXTL_SHF   0       /* Receiver trigger level shift */
DECL|macro|UFCR_RFDIV
mdefine_line|#define  UFCR_RFDIV      (7&lt;&lt;7)  /* Reference freq divider mask */
DECL|macro|UFCR_TXTL_SHF
mdefine_line|#define  UFCR_TXTL_SHF   10      /* Transmitter trigger level shift */
DECL|macro|USR1_PARITYERR
mdefine_line|#define  USR1_PARITYERR  (1&lt;&lt;15) /* Parity error interrupt flag */
DECL|macro|USR1_RTSS
mdefine_line|#define  USR1_RTSS  &t; (1&lt;&lt;14) /* RTS pin status */
DECL|macro|USR1_TRDY
mdefine_line|#define  USR1_TRDY  &t; (1&lt;&lt;13) /* Transmitter ready interrupt/dma flag */
DECL|macro|USR1_RTSD
mdefine_line|#define  USR1_RTSD  &t; (1&lt;&lt;12) /* RTS delta */
DECL|macro|USR1_ESCF
mdefine_line|#define  USR1_ESCF  &t; (1&lt;&lt;11) /* Escape seq interrupt flag */
DECL|macro|USR1_FRAMERR
mdefine_line|#define  USR1_FRAMERR    (1&lt;&lt;10) /* Frame error interrupt flag */
DECL|macro|USR1_RRDY
mdefine_line|#define  USR1_RRDY       (1&lt;&lt;9)&t; /* Receiver ready interrupt/dma flag */
DECL|macro|USR1_TIMEOUT
mdefine_line|#define  USR1_TIMEOUT    (1&lt;&lt;7)&t; /* Receive timeout interrupt status */
DECL|macro|USR1_RXDS
mdefine_line|#define  USR1_RXDS  &t; (1&lt;&lt;6)&t; /* Receiver idle interrupt flag */
DECL|macro|USR1_AIRINT
mdefine_line|#define  USR1_AIRINT&t; (1&lt;&lt;5)&t; /* Async IR wake interrupt flag */
DECL|macro|USR1_AWAKE
mdefine_line|#define  USR1_AWAKE &t; (1&lt;&lt;4)&t; /* Aysnc wake interrupt flag */
DECL|macro|USR2_ADET
mdefine_line|#define  USR2_ADET  &t; (1&lt;&lt;15) /* Auto baud rate detect complete */
DECL|macro|USR2_TXFE
mdefine_line|#define  USR2_TXFE  &t; (1&lt;&lt;14) /* Transmit buffer FIFO empty */
DECL|macro|USR2_DTRF
mdefine_line|#define  USR2_DTRF  &t; (1&lt;&lt;13) /* DTR edge interrupt flag */
DECL|macro|USR2_IDLE
mdefine_line|#define  USR2_IDLE  &t; (1&lt;&lt;12) /* Idle condition */
DECL|macro|USR2_IRINT
mdefine_line|#define  USR2_IRINT &t; (1&lt;&lt;8)&t; /* Serial infrared interrupt flag */
DECL|macro|USR2_WAKE
mdefine_line|#define  USR2_WAKE  &t; (1&lt;&lt;7)&t; /* Wake */
DECL|macro|USR2_RTSF
mdefine_line|#define  USR2_RTSF  &t; (1&lt;&lt;4)&t; /* RTS edge interrupt flag */
DECL|macro|USR2_TXDC
mdefine_line|#define  USR2_TXDC  &t; (1&lt;&lt;3)&t; /* Transmitter complete */
DECL|macro|USR2_BRCD
mdefine_line|#define  USR2_BRCD  &t; (1&lt;&lt;2)&t; /* Break condition */
DECL|macro|USR2_ORE
mdefine_line|#define  USR2_ORE        (1&lt;&lt;1)&t; /* Overrun error */
DECL|macro|USR2_RDR
mdefine_line|#define  USR2_RDR        (1&lt;&lt;0)&t; /* Recv data ready */
DECL|macro|UTS_FRCPERR
mdefine_line|#define  UTS_FRCPERR&t; (1&lt;&lt;13) /* Force parity error */
DECL|macro|UTS_LOOP
mdefine_line|#define  UTS_LOOP        (1&lt;&lt;12) /* Loop tx and rx */
DECL|macro|UTS_TXEMPTY
mdefine_line|#define  UTS_TXEMPTY&t; (1&lt;&lt;6)&t; /* TxFIFO empty */
DECL|macro|UTS_RXEMPTY
mdefine_line|#define  UTS_RXEMPTY&t; (1&lt;&lt;5)&t; /* RxFIFO empty */
DECL|macro|UTS_TXFULL
mdefine_line|#define  UTS_TXFULL &t; (1&lt;&lt;4)&t; /* TxFIFO full */
DECL|macro|UTS_RXFULL
mdefine_line|#define  UTS_RXFULL &t; (1&lt;&lt;3)&t; /* RxFIFO full */
DECL|macro|UTS_SOFTRST
mdefine_line|#define  UTS_SOFTRST&t; (1&lt;&lt;0)&t; /* Software reset */
macro_line|#endif&t;&t;&t;&t;
singleline_comment|// _IMX_REGS_H
eof
