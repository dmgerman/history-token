macro_line|#ifndef _ARCH_ARM_MFTB2_h_
DECL|macro|_ARCH_ARM_MFTB2_h_
mdefine_line|#define _ARCH_ARM_MFTB2_h_
singleline_comment|// Defines for arch/arm/mm/mm-sa1100.h
DECL|macro|TRIZEPS_PHYS_VIRT_MAP_SIZE
mdefine_line|#define TRIZEPS_PHYS_VIRT_MAP_SIZE   0x00800000l
singleline_comment|// physical address (only for mm-sa1100.h)
DECL|macro|TRIZEPS_PHYS_IO_BASE
mdefine_line|#define TRIZEPS_PHYS_IO_BASE         0x30000000l
DECL|macro|TRIZEPS_PHYS_MEM_BASE
mdefine_line|#define TRIZEPS_PHYS_MEM_BASE        0x38000000l
singleline_comment|// virtual
DECL|macro|TRIZEPS_IO_BASE
mdefine_line|#define TRIZEPS_IO_BASE&t;&t;     0xF0000000l
DECL|macro|TRIZEPS_MEM_BASE
mdefine_line|#define TRIZEPS_MEM_BASE             0xF2000000l
singleline_comment|// Offsets for phys and virtual
DECL|macro|TRIZEPS_OFFSET_REG0
mdefine_line|#define TRIZEPS_OFFSET_REG0          0x00300000l
DECL|macro|TRIZEPS_OFFSET_REG1
mdefine_line|#define TRIZEPS_OFFSET_REG1          0x00380000l
DECL|macro|TRIZEPS_OFFSET_IDE_CS0
mdefine_line|#define TRIZEPS_OFFSET_IDE_CS0       0x00000000l
DECL|macro|TRIZEPS_OFFSET_IDE_CS1
mdefine_line|#define TRIZEPS_OFFSET_IDE_CS1       0x00080000l
DECL|macro|TRIZEPS_OFFSET_UART5
mdefine_line|#define TRIZEPS_OFFSET_UART5         0x00100000l
DECL|macro|TRIZEPS_OFFSET_UART6
mdefine_line|#define TRIZEPS_OFFSET_UART6         0x00180000l
DECL|macro|TRIZEPS_PHYS_REG0
mdefine_line|#define TRIZEPS_PHYS_REG0            (TRIZEPS_PHYS_IO_BASE + TRIZEPS_OFFSET_REG0)
DECL|macro|TRIZEPS_PHYS_REG1
mdefine_line|#define TRIZEPS_PHYS_REG1            (TRIZEPS_PHYS_IO_BASE + TRIZEPS_OFFSET_REG1)
DECL|macro|TRIZEPS_PHYS_IDE_CS0
mdefine_line|#define TRIZEPS_PHYS_IDE_CS0         (TRIZEPS_PHYS_IO_BASE + TRIZEPS_OFFSET_IDE_CS0)
DECL|macro|TRIZEPS_PHYS_IDE_CS1
mdefine_line|#define TRIZEPS_PHYS_IDE_CS1         (TRIZEPS_PHYS_IO_BASE + TRIZEPS_OFFSET_IDE_CS1)
DECL|macro|TRIZEPS_PHYS_UART5
mdefine_line|#define TRIZEPS_PHYS_UART5           (TRIZEPS_PHYS_IO_BASE + TRIZEPS_OFFSET_UART5)
DECL|macro|TRIZEPS_PHYS_UART6
mdefine_line|#define TRIZEPS_PHYS_UART6           (TRIZEPS_PHYS_IO_BASE + TRIZEPS_OFFSET_UART6)
singleline_comment|// Use follow defines in devices
singleline_comment|// virtual address
DECL|macro|TRIZEPS_REG0
mdefine_line|#define TRIZEPS_REG0    (TRIZEPS_IO_BASE + TRIZEPS_OFFSET_REG0)
DECL|macro|TRIZEPS_REG1
mdefine_line|#define TRIZEPS_REG1    (TRIZEPS_IO_BASE + TRIZEPS_OFFSET_REG1)
DECL|macro|TRIZEPS_IDE_CS0
mdefine_line|#define TRIZEPS_IDE_CS0 (TRIZEPS_IO_BASE + TRIZEPS_OFFSET_IDE_CS0)
DECL|macro|TRIZEPS_IDE_CS1
mdefine_line|#define TRIZEPS_IDE_CS1 (TRIZEPS_IO_BASE + TRIZEPS_OFFSET_IDE_CS1)
DECL|macro|TRIZEPS_UART5
mdefine_line|#define TRIZEPS_UART5   (TRIZEPS_IO_BASE + TRIZEPS_OFFSET_UART5)
DECL|macro|TRIZEPS_UART6
mdefine_line|#define TRIZEPS_UART6   (TRIZEPS_IO_BASE + TRIZEPS_OFFSET_UART6)
DECL|macro|TRIZEPS_BAUD_BASE
mdefine_line|#define TRIZEPS_BAUD_BASE 1500000
singleline_comment|//#if 0 //temporarily disabled
macro_line|#ifndef __ASSEMBLY__
DECL|struct|tri_uart_cts_data_t
r_struct
id|tri_uart_cts_data_t
(brace
DECL|member|cts_gpio
r_int
id|cts_gpio
suffix:semicolon
DECL|member|cts_prev_state
r_int
id|cts_prev_state
suffix:semicolon
DECL|member|info
r_struct
id|uart_info
op_star
id|info
suffix:semicolon
DECL|member|port
r_struct
id|uart_port
op_star
id|port
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Defines for MFTB2 serial_sa1100.c hardware handshaking lines */
DECL|macro|SERIAL_FULL
mdefine_line|#define SERIAL_FULL
DECL|macro|NOT_CONNECTED
mdefine_line|#define NOT_CONNECTED&t;0
macro_line|#ifdef SERIAL_FULL
DECL|macro|TRIZEPS_GPIO_UART1_RTS
mdefine_line|#define TRIZEPS_GPIO_UART1_RTS&t;GPIO_GPIO14
DECL|macro|TRIZEPS_GPIO_UART1_DTR
mdefine_line|#define TRIZEPS_GPIO_UART1_DTR&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO9
DECL|macro|TRIZEPS_GPIO_UART1_CTS
mdefine_line|#define TRIZEPS_GPIO_UART1_CTS&t;GPIO_GPIO15
DECL|macro|TRIZEPS_GPIO_UART1_DCD
mdefine_line|#define TRIZEPS_GPIO_UART1_DCD&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO2
DECL|macro|TRIZEPS_GPIO_UART1_DSR
mdefine_line|#define TRIZEPS_GPIO_UART1_DSR&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO3
DECL|macro|TRIZEPS_GPIO_UART3_RTS
mdefine_line|#define TRIZEPS_GPIO_UART3_RTS&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO7
DECL|macro|TRIZEPS_GPIO_UART3_DTR
mdefine_line|#define TRIZEPS_GPIO_UART3_DTR&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO8
DECL|macro|TRIZEPS_GPIO_UART3_CTS
mdefine_line|#define TRIZEPS_GPIO_UART3_CTS&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO4
DECL|macro|TRIZEPS_GPIO_UART3_DCD
mdefine_line|#define TRIZEPS_GPIO_UART3_DCD&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO5
DECL|macro|TRIZEPS_GPIO_UART3_DSR
mdefine_line|#define TRIZEPS_GPIO_UART3_DSR&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO6
DECL|macro|TRIZEPS_GPIO_UART2_RTS
mdefine_line|#define TRIZEPS_GPIO_UART2_RTS&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO7
DECL|macro|TRIZEPS_GPIO_UART2_DTR
mdefine_line|#define TRIZEPS_GPIO_UART2_DTR&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO8
DECL|macro|TRIZEPS_GPIO_UART2_CTS
mdefine_line|#define TRIZEPS_GPIO_UART2_CTS&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO4
DECL|macro|TRIZEPS_GPIO_UART2_DCD
mdefine_line|#define TRIZEPS_GPIO_UART2_DCD&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO5
DECL|macro|TRIZEPS_GPIO_UART2_DSR
mdefine_line|#define TRIZEPS_GPIO_UART2_DSR&t;NOT_CONNECTED 
singleline_comment|//GPIO_GPIO6
DECL|macro|TRIZEPS_IRQ_UART1_CTS
mdefine_line|#define TRIZEPS_IRQ_UART1_CTS&t;IRQ_GPIO15
DECL|macro|TRIZEPS_IRQ_UART1_DCD
mdefine_line|#define TRIZEPS_IRQ_UART1_DCD&t;NO_IRQ 
singleline_comment|//IRQ_GPIO2
DECL|macro|TRIZEPS_IRQ_UART1_DSR
mdefine_line|#define TRIZEPS_IRQ_UART1_DSR&t;NO_IRQ 
singleline_comment|//IRQ_GPIO3
DECL|macro|TRIZEPS_IRQ_UART3_CTS
mdefine_line|#define TRIZEPS_IRQ_UART3_CTS&t;NO_IRQ 
singleline_comment|//IRQ_GPIO4
DECL|macro|TRIZEPS_IRQ_UART3_DCD
mdefine_line|#define TRIZEPS_IRQ_UART3_DCD&t;NO_IRQ 
singleline_comment|//IRQ_GPIO5
DECL|macro|TRIZEPS_IRQ_UART3_DSR
mdefine_line|#define TRIZEPS_IRQ_UART3_DSR&t;NO_IRQ 
singleline_comment|//IRQ_GPIO6
DECL|macro|TRIZEPS_IRQ_UART2_CTS
mdefine_line|#define TRIZEPS_IRQ_UART2_CTS&t;NO_IRQ 
singleline_comment|//IRQ_GPIO4
DECL|macro|TRIZEPS_IRQ_UART2_DCD
mdefine_line|#define TRIZEPS_IRQ_UART2_DCD&t;NO_IRQ 
singleline_comment|//IRQ_GPIO5
DECL|macro|TRIZEPS_IRQ_UART2_DSR
mdefine_line|#define TRIZEPS_IRQ_UART2_DSR&t;NO_IRQ 
singleline_comment|//IRQ_GPIO6
macro_line|#endif /* SERIAL_FULL */
singleline_comment|//#endif //0
multiline_comment|/*&n; * This section contains the defines for the MFTB2 implementation&n; * of drivers/ide/hd.c. HD_IOBASE_0 and HD_IOBASE_1 have to be&n; * adjusted if hardware changes.&n; */
DECL|macro|TRIZEPS_IRQ_IDE
mdefine_line|#define TRIZEPS_IRQ_IDE 10&t;&t;/* MFTB2 specific */
multiline_comment|/*---   ROOT   ---*/
DECL|macro|TRIZEPS_GPIO_ROOT_NFS
mdefine_line|#define TRIZEPS_GPIO_ROOT_NFS       0
DECL|macro|TRIZEPS_GPIO_ROOT_HD
mdefine_line|#define TRIZEPS_GPIO_ROOT_HD        21
multiline_comment|/*---  PCMCIA  ---*/
DECL|macro|TRIZEPS_GPIO_PCMCIA_IRQ0
mdefine_line|#define TRIZEPS_GPIO_PCMCIA_IRQ0 1
DECL|macro|TRIZEPS_GPIO_PCMCIA_CD0
mdefine_line|#define TRIZEPS_GPIO_PCMCIA_CD0  24
DECL|macro|TRIZEPS_IRQ_PCMCIA_IRQ0
mdefine_line|#define TRIZEPS_IRQ_PCMCIA_IRQ0  TRIZEPS_GPIO_PCMCIA_IRQ0
DECL|macro|TRIZEPS_IRQ_PCMCIA_CD0
mdefine_line|#define TRIZEPS_IRQ_PCMCIA_CD0   TRIZEPS_GPIO_PCMCIA_CD0 + 32 - 11
singleline_comment|// REGISTER 0 -&gt; 0x0XXXX (16bit access)
singleline_comment|// read only
DECL|macro|TRIZEPS_A_STAT
mdefine_line|#define TRIZEPS_A_STAT             0x8000l
DECL|macro|TRIZEPS_F_STAT
mdefine_line|#define TRIZEPS_F_STAT             0x4000l
DECL|macro|TRIZEPS_BATT_FAULT_EN
mdefine_line|#define TRIZEPS_BATT_FAULT_EN      0x2000l
DECL|macro|TRIZEPS_nDQ
mdefine_line|#define TRIZEPS_nDQ                0x1000l
DECL|macro|TRIZEPS_MFT_OFF
mdefine_line|#define TRIZEPS_MFT_OFF            0x0800l
DECL|macro|TRIZEPS_D_APWOFF
mdefine_line|#define TRIZEPS_D_APWOFF           0x0400l
DECL|macro|TRIZEPS_F_CTRL
mdefine_line|#define TRIZEPS_F_CTRL             0x0200l
DECL|macro|TRIZEPS_F_STOP
mdefine_line|#define TRIZEPS_F_STOP             0x0100l
singleline_comment|// read / write
DECL|macro|TRIZEPS_KP_IR_EN
mdefine_line|#define TRIZEPS_KP_IR_EN           0x0080l
DECL|macro|TRIZEPS_FIR
mdefine_line|#define TRIZEPS_FIR                0x0040l
DECL|macro|TRIZEPS_BAR_ON
mdefine_line|#define TRIZEPS_BAR_ON             0x0020l
DECL|macro|TRIZEPS_VCI_ON
mdefine_line|#define TRIZEPS_VCI_ON             0x0010l
DECL|macro|TRIZEPS_LED4
mdefine_line|#define TRIZEPS_LED4               0x0008l
DECL|macro|TRIZEPS_LED3
mdefine_line|#define TRIZEPS_LED3               0x0004l
DECL|macro|TRIZEPS_LED2
mdefine_line|#define TRIZEPS_LED2               0x0002l
DECL|macro|TRIZEPS_LED1
mdefine_line|#define TRIZEPS_LED1               0x0001l
singleline_comment|// REGISTER 1 -&gt; 0x1XXXX (16bit access)
singleline_comment|// read only
DECL|macro|TRIZEPS_nVCI2
mdefine_line|#define TRIZEPS_nVCI2              0x8000l
DECL|macro|TRIZEPS_nAB_LOW
mdefine_line|#define TRIZEPS_nAB_LOW            0x4000l
DECL|macro|TRIZEPS_nMB_DEAD
mdefine_line|#define TRIZEPS_nMB_DEAD           0x2000l
DECL|macro|TRIZEPS_nMB_LOW
mdefine_line|#define TRIZEPS_nMB_LOW            0x1000l
DECL|macro|TRIZEPS_nPCM_VS2
mdefine_line|#define TRIZEPS_nPCM_VS2           0x0800l
DECL|macro|TRIZEPS_nPCM_VS1
mdefine_line|#define TRIZEPS_nPCM_VS1           0x0400l
DECL|macro|TRIZEPS_PCM_BVD2
mdefine_line|#define TRIZEPS_PCM_BVD2           0x0200l
DECL|macro|TRIZEPS_PCM_BVD1
mdefine_line|#define TRIZEPS_PCM_BVD1           0x0100l
singleline_comment|// read / write
DECL|macro|TRIZEPS_nROOT_NFS
mdefine_line|#define TRIZEPS_nROOT_NFS          0x0080l
DECL|macro|TRIZEPS_nROOT_HD
mdefine_line|#define TRIZEPS_nROOT_HD           0x0040l
DECL|macro|TRIZEPS_nPCM_ENA_REG
mdefine_line|#define TRIZEPS_nPCM_ENA_REG       0x0020l
DECL|macro|TRIZEPS_nPCM_RESET_DISABLE
mdefine_line|#define TRIZEPS_nPCM_RESET_DISABLE 0x0010l
DECL|macro|TRIZEPS_PCM_EN0_REG
mdefine_line|#define TRIZEPS_PCM_EN0_REG        0x0008l
DECL|macro|TRIZEPS_PCM_EN1_REG
mdefine_line|#define TRIZEPS_PCM_EN1_REG        0x0004l
DECL|macro|TRIZEPS_PCM_V3_EN_REG
mdefine_line|#define TRIZEPS_PCM_V3_EN_REG      0x0002l
DECL|macro|TRIZEPS_PCM_V5_EN_REG
mdefine_line|#define TRIZEPS_PCM_V5_EN_REG      0x0001l
multiline_comment|/* Access to Board Control Register */
DECL|macro|TRIZEPS_BCR0
mdefine_line|#define TRIZEPS_BCR0 (*(volatile unsigned short *)(TRIZEPS_REG0))
DECL|macro|TRIZEPS_BCR1
mdefine_line|#define TRIZEPS_BCR1 (*(volatile unsigned short *)(TRIZEPS_REG1))
DECL|macro|TRIZEPS_BCR_set
mdefine_line|#define TRIZEPS_BCR_set( reg, x ) do { &bslash;&n;&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;(reg) |= (x); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while (0)
DECL|macro|TRIZEPS_BCR_clear
mdefine_line|#define TRIZEPS_BCR_clear( reg, x ) do { &bslash;&n;&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;(reg) &amp;= ~(x); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while (0)
DECL|macro|TRIZEPS_OFFSET_KP_REG
mdefine_line|#define TRIZEPS_OFFSET_KP_REG      0x00200000l
DECL|macro|TRIZEPS_OFFSET_VCI2
mdefine_line|#define TRIZEPS_OFFSET_VCI2        0x00280000l
DECL|macro|TRIZEPS_OFFSET_VCI4
mdefine_line|#define TRIZEPS_OFFSET_VCI4        0x00400000l
DECL|macro|TRIZEPS_OFFSET_VCI2_1_DPR
mdefine_line|#define TRIZEPS_OFFSET_VCI2_1_DPR  (TRIZEPS_OFFSET_VCI2 + 0x00010000l)
DECL|macro|TRIZEPS_OFFSET_VCI2_2_DPR
mdefine_line|#define TRIZEPS_OFFSET_VCI2_2_DPR  (TRIZEPS_OFFSET_VCI2 + 0x00018000l)
DECL|macro|TRIZEPS_OFFSET_VCI2_1_SEMA
mdefine_line|#define TRIZEPS_OFFSET_VCI2_1_SEMA (TRIZEPS_OFFSET_VCI2 + 0x00020000l)
DECL|macro|TRIZEPS_OFFSET_VCI2_2_SEMA
mdefine_line|#define TRIZEPS_OFFSET_VCI2_2_SEMA (TRIZEPS_OFFSET_VCI2 + 0x00028000l)
DECL|macro|TRIZEPS_OFFSET_VCI4_1_DPR
mdefine_line|#define TRIZEPS_OFFSET_VCI4_1_DPR  (TRIZEPS_OFFSET_VCI4 + 0x00000000l)
DECL|macro|TRIZEPS_OFFSET_VCI4_2_DPR
mdefine_line|#define TRIZEPS_OFFSET_VCI4_2_DPR  (TRIZEPS_OFFSET_VCI4 + 0x00008000l)
DECL|macro|TRIZEPS_OFFSET_VCI4_1_SEMA
mdefine_line|#define TRIZEPS_OFFSET_VCI4_1_SEMA (TRIZEPS_OFFSET_VCI4 + 0x00000380l)
DECL|macro|TRIZEPS_OFFSET_VCI4_2_SEMA
mdefine_line|#define TRIZEPS_OFFSET_VCI4_2_SEMA (TRIZEPS_OFFSET_VCI4 + 0x00000388l)
DECL|macro|TRIZEPS_OFFSET_VCI4_1_CNTR
mdefine_line|#define TRIZEPS_OFFSET_VCI4_1_CNTR (TRIZEPS_OFFSET_VCI4 + 0x00000390l)
DECL|macro|TRIZEPS_OFFSET_VCI4_2_CNTR
mdefine_line|#define TRIZEPS_OFFSET_VCI4_2_CNTR (TRIZEPS_OFFSET_VCI4 + 0x00000392l)
DECL|macro|TRIZEPS_PHYS_KP_REG
mdefine_line|#define TRIZEPS_PHYS_KP_REG        (PHYS_TRIZEPS_IO_BASE + TRIZEPS_OFFSET_KP_REG)
singleline_comment|// VCI address
DECL|macro|TRIZEPS_PHYS_VCI2_1_DPR
mdefine_line|#define TRIZEPS_PHYS_VCI2_1_DPR    (TRIZEPS_PHYS_MEM_BASE + TRIZEPS_OFFSET_VCI2_1_DPR)
DECL|macro|TRIZEPS_PHYS_VCI2_2_DPR
mdefine_line|#define TRIZEPS_PHYS_VCI2_2_DPR    (TRIZEPS_PHYS_MEM_BASE + TRIZEPS_OFFSET_VCI2_2_DPR)
DECL|macro|TRIZEPS_PHYS_VCI2_1_SEMA
mdefine_line|#define TRIZEPS_PHYS_VCI2_1_SEMA   (TRIZEPS_PHYS_MEM_BASE + TRIZEPS_OFFSET_VCI2_1_SEMA)
DECL|macro|TRIZEPS_PHYS_VCI2_2_SEMA
mdefine_line|#define TRIZEPS_PHYS_VCI2_2_SEMA   (TRIZEPS_PHYS_MEM_BASE + TRIZEPS_OFFSET_VCI2_2_SEMA)
singleline_comment|// VCI4 address
DECL|macro|TRIZEPS_PHYS_VCI4_1_DPR
mdefine_line|#define TRIZEPS_PHYS_VCI4_1_DPR    (TRIZEPS_PHYS_MEM_BASE + TRIZEPS_OFFSET_VCI4_1_DPR)
DECL|macro|TRIZEPS_PHYS_VCI4_2_DPR
mdefine_line|#define TRIZEPS_PHYS_VCI4_2_DPR    (TRIZEPS_PHYS_MEM_BASE + TRIZEPS_OFFSET_VCI4_2_DPR)
DECL|macro|TRIZEPS_PHYS_VCI4_1_SEMA
mdefine_line|#define TRIZEPS_PHYS_VCI4_1_SEMA   (TRIZEPS_PHYS_IO_BASE  + TRIZEPS_OFFSET_VCI4_1_SEMA)
DECL|macro|TRIZEPS_PHYS_VCI4_2_SEMA
mdefine_line|#define TRIZEPS_PHYS_VCI4_2_SEMA   (TRIZEPS_PHYS_IO_BASE  + TRIZEPS_OFFSET_VCI4_2_SEMA)
DECL|macro|TRIZEPS_PHYS_VCI4_1_CNTR
mdefine_line|#define TRIZEPS_PHYS_VCI4_1_CNTR   (TRIZEPS_PHYS_IO_BASE  + TRIZEPS_OFFSET_VCI4_1_CNTR)
DECL|macro|TRIZEPS_PHYS_VCI4_2_CNTR
mdefine_line|#define TRIZEPS_PHYS_VCI4_2_CNTR   (TRIZEPS_PHYS_IO_BASE  + TRIZEPS_OFFSET_VCI4_2_CNTR)
DECL|macro|TRIZEPS_KP_REG
mdefine_line|#define TRIZEPS_KP_REG               (TRIZEPS_IO_BASE  + TRIZEPS_OFFSET_KP_REG)
singleline_comment|// VCI address
DECL|macro|TRIZEPS_VCI2_1_DPR
mdefine_line|#define TRIZEPS_VCI2_1_DPR           (TRIZEPS_MEM_BASE + TRIZEPS_OFFSET_VCI2_1_DPR)
DECL|macro|TRIZEPS_VCI2_2_DPR
mdefine_line|#define TRIZEPS_VCI2_2_DPR           (TRIZEPS_MEM_BASE + TRIZEPS_OFFSET_VCI2_2_DPR)
DECL|macro|TRIZEPS_VCI2_1_SEMA
mdefine_line|#define TRIZEPS_VCI2_1_SEMA          (TRIZEPS_MEM_BASE + TRIZEPS_OFFSET_VCI2_1_SEMA)
DECL|macro|TRIZEPS_VCI2_2_SEMA
mdefine_line|#define TRIZEPS_VCI2_2_SEMA          (TRIZEPS_MEM_BASE + TRIZEPS_OFFSET_VCI2_2_SEMA)
singleline_comment|// VCI4 address
DECL|macro|TRIZEPS_VCI4_1_DPR
mdefine_line|#define TRIZEPS_VCI4_1_DPR           (TRIZEPS_MEM_BASE + TRIZEPS_OFFSET_VCI4_1_DPR)
DECL|macro|TRIZEPS_VCI4_2_DPR
mdefine_line|#define TRIZEPS_VCI4_2_DPR           (TRIZEPS_MEM_BASE + TRIZEPS_OFFSET_VCI4_2_DPR)
DECL|macro|TRIZEPS_VCI4_1_SEMA
mdefine_line|#define TRIZEPS_VCI4_1_SEMA          (TRIZEPS_IO_BASE  + TRIZEPS_OFFSET_VCI4_1_SEMA)
DECL|macro|TRIZEPS_VCI4_2_SEMA
mdefine_line|#define TRIZEPS_VCI4_2_SEMA          (TRIZEPS_IO_BASE  + TRIZEPS_OFFSET_VCI4_2_SEMA)
DECL|macro|TRIZEPS_VCI4_1_CNTR
mdefine_line|#define TRIZEPS_VCI4_1_CNTR          (TRIZEPS_IO_BASE  + TRIZEPS_OFFSET_VCI4_1_CNTR)
DECL|macro|TRIZEPS_VCI4_2_CNTR
mdefine_line|#define TRIZEPS_VCI4_2_CNTR          (TRIZEPS_IO_BASE  + TRIZEPS_OFFSET_VCI4_2_CNTR)
macro_line|#endif
eof
