multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/serial.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; * serial definitions&n; *&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
DECL|macro|OMAP1510_UART1_BASE
mdefine_line|#define OMAP1510_UART1_BASE&t;(unsigned char *)0xfffb0000
DECL|macro|OMAP1510_UART2_BASE
mdefine_line|#define OMAP1510_UART2_BASE&t;(unsigned char *)0xfffb0800
DECL|macro|OMAP1510_UART3_BASE
mdefine_line|#define OMAP1510_UART3_BASE&t;(unsigned char *)0xfffb9800
DECL|macro|OMAP730_UART1_BASE
mdefine_line|#define OMAP730_UART1_BASE&t;(unsigned char *)0xfffb0000
DECL|macro|OMAP730_UART2_BASE
mdefine_line|#define OMAP730_UART2_BASE&t;(unsigned char *)0xfffb0800
macro_line|#if defined(CONFIG_ARCH_OMAP1510) || defined(CONFIG_ARCH_OMAP1610)
DECL|macro|OMAP_SERIAL_REG_SHIFT
mdefine_line|#define OMAP_SERIAL_REG_SHIFT 2
macro_line|#else
DECL|macro|OMAP_SERIAL_REG_SHIFT
mdefine_line|#define OMAP_SERIAL_REG_SHIFT 0
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* UART3 Registers Maping through MPU bus */
DECL|macro|OMAP_MPU_UART3_BASE
mdefine_line|#define OMAP_MPU_UART3_BASE&t;0xFFFB9800&t;/* UART3 through MPU bus */
DECL|macro|UART3_RHR
mdefine_line|#define UART3_RHR&t;&t;(OMAP_MPU_UART3_BASE + 0)
DECL|macro|UART3_THR
mdefine_line|#define UART3_THR&t;&t;(OMAP_MPU_UART3_BASE + 0)
DECL|macro|UART3_DLL
mdefine_line|#define UART3_DLL&t;&t;(OMAP_MPU_UART3_BASE + 0)
DECL|macro|UART3_IER
mdefine_line|#define UART3_IER&t;&t;(OMAP_MPU_UART3_BASE + 4)
DECL|macro|UART3_DLH
mdefine_line|#define UART3_DLH&t;&t;(OMAP_MPU_UART3_BASE + 4)
DECL|macro|UART3_IIR
mdefine_line|#define UART3_IIR&t;&t;(OMAP_MPU_UART3_BASE + 8)
DECL|macro|UART3_FCR
mdefine_line|#define UART3_FCR&t;&t;(OMAP_MPU_UART3_BASE + 8)
DECL|macro|UART3_EFR
mdefine_line|#define UART3_EFR&t;&t;(OMAP_MPU_UART3_BASE + 8)
DECL|macro|UART3_LCR
mdefine_line|#define UART3_LCR&t;&t;(OMAP_MPU_UART3_BASE + 0x0C)
DECL|macro|UART3_MCR
mdefine_line|#define UART3_MCR&t;&t;(OMAP_MPU_UART3_BASE + 0x10)
DECL|macro|UART3_XON1_ADDR1
mdefine_line|#define UART3_XON1_ADDR1&t;(OMAP_MPU_UART3_BASE + 0x10)
DECL|macro|UART3_XON2_ADDR2
mdefine_line|#define UART3_XON2_ADDR2&t;(OMAP_MPU_UART3_BASE + 0x14)
DECL|macro|UART3_LSR
mdefine_line|#define UART3_LSR&t;&t;(OMAP_MPU_UART3_BASE + 0x14)
DECL|macro|UART3_TCR
mdefine_line|#define UART3_TCR&t;&t;(OMAP_MPU_UART3_BASE + 0x18)
DECL|macro|UART3_MSR
mdefine_line|#define UART3_MSR&t;&t;(OMAP_MPU_UART3_BASE + 0x18)
DECL|macro|UART3_XOFF1
mdefine_line|#define UART3_XOFF1&t;&t;(OMAP_MPU_UART3_BASE + 0x18)
DECL|macro|UART3_XOFF2
mdefine_line|#define UART3_XOFF2&t;&t;(OMAP_MPU_UART3_BASE + 0x1C)
DECL|macro|UART3_SPR
mdefine_line|#define UART3_SPR&t;&t;(OMAP_MPU_UART3_BASE + 0x1C)
DECL|macro|UART3_TLR
mdefine_line|#define UART3_TLR&t;&t;(OMAP_MPU_UART3_BASE + 0x1C)
DECL|macro|UART3_MDR1
mdefine_line|#define UART3_MDR1&t;&t;(OMAP_MPU_UART3_BASE + 0x20)
DECL|macro|UART3_MDR2
mdefine_line|#define UART3_MDR2&t;&t;(OMAP_MPU_UART3_BASE + 0x24)
DECL|macro|UART3_SFLSR
mdefine_line|#define UART3_SFLSR&t;&t;(OMAP_MPU_UART3_BASE + 0x28)
DECL|macro|UART3_TXFLL
mdefine_line|#define UART3_TXFLL&t;&t;(OMAP_MPU_UART3_BASE + 0x28)
DECL|macro|UART3_RESUME
mdefine_line|#define UART3_RESUME&t;&t;(OMAP_MPU_UART3_BASE + 0x2C)
DECL|macro|UART3_TXFLH
mdefine_line|#define UART3_TXFLH&t;&t;(OMAP_MPU_UART3_BASE + 0x2C)
DECL|macro|UART3_SFREGL
mdefine_line|#define UART3_SFREGL&t;&t;(OMAP_MPU_UART3_BASE + 0x30)
DECL|macro|UART3_RXFLL
mdefine_line|#define UART3_RXFLL&t;&t;(OMAP_MPU_UART3_BASE + 0x30)
DECL|macro|UART3_SFREGH
mdefine_line|#define UART3_SFREGH&t;&t;(OMAP_MPU_UART3_BASE + 0x34)
DECL|macro|UART3_RXFLH
mdefine_line|#define UART3_RXFLH&t;&t;(OMAP_MPU_UART3_BASE + 0x34)
DECL|macro|UART3_BLR
mdefine_line|#define UART3_BLR&t;&t;(OMAP_MPU_UART3_BASE + 0x38)
DECL|macro|UART3_ACREG
mdefine_line|#define UART3_ACREG&t;&t;(OMAP_MPU_UART3_BASE + 0x3C)
DECL|macro|UART3_DIV16
mdefine_line|#define UART3_DIV16&t;&t;(OMAP_MPU_UART3_BASE + 0x3C)
DECL|macro|UART3_SCR
mdefine_line|#define UART3_SCR&t;&t;(OMAP_MPU_UART3_BASE + 0x40)
DECL|macro|UART3_SSR
mdefine_line|#define UART3_SSR&t;&t;(OMAP_MPU_UART3_BASE + 0x44)
DECL|macro|UART3_EBLR
mdefine_line|#define UART3_EBLR&t;&t;(OMAP_MPU_UART3_BASE + 0x48)
DECL|macro|UART3_OSC_12M_SEL
mdefine_line|#define UART3_OSC_12M_SEL&t;(OMAP_MPU_UART3_BASE + 0x4C)
DECL|macro|UART3_MVR
mdefine_line|#define UART3_MVR&t;&t;(OMAP_MPU_UART3_BASE + 0x50)
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (12000000/16)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1610
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (48000000/16)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP730
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (48000000/16)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;&t;2
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS&t;(ASYNC_SKIP_TEST)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&bslash;&n;&t;{&t;&bslash;&n;&t;&t;.uart =&t;&t;&t;PORT_OMAP,&t;&t;&bslash;&n;&t;&t;.baud_base =&t;&t;BASE_BAUD,&t;&t;&bslash;&n;&t;&t;.iomem_base =&t;&t;OMAP730_UART1_BASE,&t;&bslash;&n;&t;&t;.iomem_reg_shift =&t;0,&t;&t;&t;&bslash;&n;&t;&t;.io_type =&t;&t;SERIAL_IO_MEM,&t;&t;&bslash;&n;&t;&t;.irq =&t;&t;&t;INT_UART1,&t;&t;&bslash;&n;&t;&t;.flags =&t;&t;&t;STD_COM_FLAGS,&t;&t;&bslash;&n;&t;}, {&t;&bslash;&n;&t;&t;.uart =&t;&t;&t;PORT_OMAP,&t;&t;&bslash;&n;&t;&t;.baud_base =&t;&t;BASE_BAUD,&t;&t;&bslash;&n;&t;&t;.iomem_base =&t;&t;OMAP730_UART2_BASE,&t;&bslash;&n;&t;&t;.iomem_reg_shift =&t;0,&t;&t;&t;&bslash;&n;&t;&t;.io_type =&t;&t;SERIAL_IO_MEM,&t;&t;&bslash;&n;&t;&t;.irq =&t;&t;&t;INT_UART2,&t;&t;&bslash;&n;&t;&t;.flags =&t;&t;&t;STD_COM_FLAGS,&t;&t;&bslash;&n;&t;}
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;3
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS&t;(ASYNC_SKIP_TEST)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&bslash;&n;&t;{&t;&bslash;&n;&t;&t;.uart =&t;&t;&t;PORT_OMAP,&t;&t;&bslash;&n;&t;&t;.baud_base =&t;&t;BASE_BAUD,&t;&t;&bslash;&n;&t;&t;.iomem_base =&t;&t;OMAP1510_UART1_BASE,&t;&bslash;&n;&t;&t;.iomem_reg_shift =&t;2,&t;&t;&t;&bslash;&n;&t;&t;.io_type =&t;&t;SERIAL_IO_MEM,&t;&t;&bslash;&n;&t;&t;.irq =&t;&t;&t;INT_UART1,&t;&t;&bslash;&n;&t;&t;.flags =&t;&t;STD_COM_FLAGS,&t;&t;&bslash;&n;&t;}, {&t;&bslash;&n;&t;&t;.uart =&t;&t;&t;PORT_OMAP,&t;&t;&bslash;&n;&t;&t;.baud_base =&t;&t;BASE_BAUD,&t;&t;&bslash;&n;&t;&t;.iomem_base =&t;&t;OMAP1510_UART2_BASE,&t;&bslash;&n;&t;&t;.iomem_reg_shift =&t;2,&t;&t;&t;&bslash;&n;&t;&t;.io_type =&t;&t;SERIAL_IO_MEM,&t;&t;&bslash;&n;&t;&t;.irq =&t;&t;&t;INT_UART2,&t;&t;&bslash;&n;&t;&t;.flags =&t;&t;STD_COM_FLAGS,&t;&t;&bslash;&n;&t;}, {&t;&bslash;&n;&t;&t;.uart =&t;&t;&t;PORT_OMAP,&t;&t;&bslash;&n;&t;&t;.baud_base =&t;&t;BASE_BAUD,&t;&t;&bslash;&n;&t;&t;.iomem_base =&t;&t;OMAP1510_UART3_BASE,&t;&bslash;&n;&t;&t;.iomem_reg_shift =&t;2,&t;&t;&t;&bslash;&n;&t;&t;.io_type =&t;&t;SERIAL_IO_MEM,&t;&t;&bslash;&n;&t;&t;.irq =&t;&t;&t;INT_UART3,&t;&t;&bslash;&n;&t;&t;.flags =&t;&t;STD_COM_FLAGS,&t;&t;&bslash;&n;&t;}
macro_line|#endif&t;&t;&t;&t;/* CONFIG_ARCH_OMAP730 */
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
multiline_comment|/* OMAP FCR trigger  redefinitions */
DECL|macro|UART_FCR_R_TRIGGER_8
mdefine_line|#define UART_FCR_R_TRIGGER_8&t;0x00&t;/* Mask for receive trigger set at 8 */
DECL|macro|UART_FCR_R_TRIGGER_16
mdefine_line|#define UART_FCR_R_TRIGGER_16&t;0x40&t;/* Mask for receive trigger set at 16 */
DECL|macro|UART_FCR_R_TRIGGER_56
mdefine_line|#define UART_FCR_R_TRIGGER_56&t;0x80&t;/* Mask for receive trigger set at 56 */
DECL|macro|UART_FCR_R_TRIGGER_60
mdefine_line|#define UART_FCR_R_TRIGGER_60&t;0xC0&t;/* Mask for receive trigger set at 60 */
multiline_comment|/* There is an error in the description of the transmit trigger levels of&n;   OMAP5910 TRM from January 2003. The transmit trigger level 56 is not&n;   56 but 32, the transmit trigger level 60 is not 60 but 56!&n;   Additionally, the descritption of these trigger levels is&n;   a little bit unclear. The trigger level define the number of EMPTY&n;   entries in the FIFO. Thus, if TRIGGER_8 is used, an interrupt is requested&n;   if 8 FIFO entries are empty (and 56 entries are still filled [the FIFO&n;   size is 64]). Or: If TRIGGER_56 is selected, everytime there are less than&n;   8 characters in the FIFO, an interrrupt is spawned. In other words: The&n;   trigger number is equal the number of characters which can be&n;   written without FIFO overrun */
DECL|macro|UART_FCR_T_TRIGGER_8
mdefine_line|#define UART_FCR_T_TRIGGER_8&t;0x00&t;/* Mask for transmit trigger set at 8 */
DECL|macro|UART_FCR_T_TRIGGER_16
mdefine_line|#define UART_FCR_T_TRIGGER_16&t;0x10&t;/* Mask for transmit trigger set at 16 */
DECL|macro|UART_FCR_T_TRIGGER_32
mdefine_line|#define UART_FCR_T_TRIGGER_32&t;0x20&t;/* Mask for transmit trigger set at 32 */
DECL|macro|UART_FCR_T_TRIGGER_56
mdefine_line|#define UART_FCR_T_TRIGGER_56&t;0x30&t;/* Mask for transmit trigger set at 56 */
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif&t;/* __ASM_ARCH_SERIAL_H */
eof
