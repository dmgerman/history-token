multiline_comment|/* $Id$&n; *&n; * vac.h: Various VIC controller defines.  The VIC is a VME controller&n; *        used in Baget/MIPS series.&n; *&n; * Copyright (C) 1998 Gleb Raiko &amp; Vladimir Roganov&n; */
macro_line|#ifndef _MIPS_VAC_H
DECL|macro|_MIPS_VAC_H
mdefine_line|#define _MIPS_VAC_H
DECL|macro|VAC_SLSEL1_MASK
mdefine_line|#define VAC_SLSEL1_MASK      0x000
DECL|macro|VAC_SLSEL1_BASE
mdefine_line|#define VAC_SLSEL1_BASE      0x100
DECL|macro|VAC_SLSEL0_MASK
mdefine_line|#define VAC_SLSEL0_MASK      0x200
DECL|macro|VAC_SLSEL0_BASE
mdefine_line|#define VAC_SLSEL0_BASE      0x300
DECL|macro|VAC_ICFSEL_BASE
mdefine_line|#define VAC_ICFSEL_BASE      0x400
DECL|macro|VAC_ICFSEL_GLOBAL_VAL
mdefine_line|#define VAC_ICFSEL_GLOBAL_VAL(x) (((x)&gt;&gt;8)&amp;0xff)
DECL|macro|VAC_ICFSEL_MODULE_VAL
mdefine_line|#define VAC_ICFSEL_MODULE_VAL(x) ((x)&amp;0xff)
DECL|macro|VAC_DRAM_MASK
mdefine_line|#define VAC_DRAM_MASK        0x500
DECL|macro|VAC_BNDR2
mdefine_line|#define VAC_BNDR2            0x600
DECL|macro|VAC_BNDR3
mdefine_line|#define VAC_BNDR3            0x700
DECL|macro|VAC_A24_BASE
mdefine_line|#define VAC_A24_BASE         0x800
DECL|macro|VAC_A24_MASK
mdefine_line|#define    VAC_A24_MASK          (0x3f&lt;&lt;9)
DECL|macro|VAC_A24_D32_ENABLE
mdefine_line|#define    VAC_A24_D32_ENABLE    (1&lt;&lt;8)
DECL|macro|VAC_A24_A24_CACHINH
mdefine_line|#define    VAC_A24_A24_CACHINH   (1&lt;&lt;7)
DECL|macro|VAC_A24_A16D32_ENABLE
mdefine_line|#define    VAC_A24_A16D32_ENABLE (1&lt;&lt;6)  
DECL|macro|VAC_A24_A16D32
mdefine_line|#define    VAC_A24_A16D32        (1&lt;&lt;5)  
DECL|macro|VAC_A24_DATAPATH
mdefine_line|#define    VAC_A24_DATAPATH      (1&lt;&lt;4)
DECL|macro|VAC_A24_IO_CACHINH
mdefine_line|#define    VAC_A24_IO_CACHINH    (1&lt;&lt;3)
DECL|macro|VAC_REG1
mdefine_line|#define VAC_REG1             0x900
DECL|macro|VAC_REG2
mdefine_line|#define VAC_REG2             0xA00
DECL|macro|VAC_REG3
mdefine_line|#define VAC_REG3             0xB00
DECL|macro|VAC_REG_WORD
mdefine_line|#define    VAC_REG_WORD      (1&lt;&lt;15)
DECL|macro|VAC_REG_ASIZ1
mdefine_line|#define    VAC_REG_ASIZ1     (1&lt;&lt;14)
DECL|macro|VAC_REG_ASIZ0
mdefine_line|#define    VAC_REG_ASIZ0     (1&lt;&lt;13)
DECL|macro|VAC_REG_ASIZ_VAL
mdefine_line|#define    VAC_REG_ASIZ_VAL(x) (((x)&gt;&gt;13)&amp;3)
DECL|macro|VAC_REG_CACHINH
mdefine_line|#define    VAC_REG_CACHINH   (1&lt;&lt;12)
DECL|macro|VAC_REG_INACTIVE
mdefine_line|#define    VAC_REG_INACTIVE  (0&lt;&lt;10)
DECL|macro|VAC_REG_SHARED
mdefine_line|#define    VAC_REG_SHARED    (1&lt;&lt;10)
DECL|macro|VAC_REG_VSB
mdefine_line|#define    VAC_REG_VSB       (2&lt;&lt;10)
DECL|macro|VAC_REG_MWB
mdefine_line|#define    VAC_REG_MWB       (3&lt;&lt;10)
DECL|macro|VAC_REG_MASK
mdefine_line|#define    VAC_REG_MASK      (3&lt;&lt;10)
DECL|macro|VAC_REG_MODE
mdefine_line|#define    VAC_REG_MODE(x)   (((x)&gt;&gt;10)&amp;3)
DECL|macro|VAC_IOSEL4_CTRL
mdefine_line|#define VAC_IOSEL4_CTRL      0xC00
DECL|macro|VAC_IOSEL5_CTRL
mdefine_line|#define VAC_IOSEL5_CTRL      0xD00
DECL|macro|VAC_SHRCS_CTRL
mdefine_line|#define VAC_SHRCS_CTRL       0xE00
DECL|macro|VAC_EPROMCS_CTRL
mdefine_line|#define VAC_EPROMCS_CTRL     0xF00
DECL|macro|VAC_IOSEL0_CTRL
mdefine_line|#define VAC_IOSEL0_CTRL      0x1000
DECL|macro|VAC_IOSEL1_CTRL
mdefine_line|#define VAC_IOSEL1_CTRL      0x1100
DECL|macro|VAC_IOSEL2_CTRL
mdefine_line|#define VAC_IOSEL2_CTRL      0x1200
DECL|macro|VAC_IOSEL3_CTRL
mdefine_line|#define VAC_IOSEL3_CTRL      0x1300
DECL|macro|VAC_CTRL_IOWR
mdefine_line|#define    VAC_CTRL_IOWR               (1&lt;&lt;0)
DECL|macro|VAC_CTRL_IORD
mdefine_line|#define    VAC_CTRL_IORD               (1&lt;&lt;1)
DECL|macro|VAC_CTRL_DELAY_IOSELI
mdefine_line|#define    VAC_CTRL_DELAY_IOSELI(x)    (((x)&amp;3)&lt;&lt;2)
DECL|macro|VAC_CTRL_DELAY_IOSELI_VAL
mdefine_line|#define    VAC_CTRL_DELAY_IOSELI_VAL(x) (((x)&gt;&gt;2)&amp;3)
DECL|macro|VAC_CTRL_DELAY_IOWR
mdefine_line|#define    VAC_CTRL_DELAY_IOWR(x)      (((x)&amp;3)&lt;&lt;4)
DECL|macro|VAC_CTRL_DELAY_IOWR_VAL
mdefine_line|#define    VAC_CTRL_DELAY_IOWR_VAL(x)  (((x)&gt;&gt;4)&amp;3)
DECL|macro|VAC_CTRL_DELAY_IORD
mdefine_line|#define    VAC_CTRL_DELAY_IORD(x)      (((x)&amp;3)&lt;&lt;6)
DECL|macro|VAC_CTRL_DELAY_IORD_VAL
mdefine_line|#define    VAC_CTRL_DELAY_IORD_VAL(x)  (((x)&gt;&gt;6)&amp;3)
DECL|macro|VAC_CTRL_RECOVERY_IOSELI
mdefine_line|#define    VAC_CTRL_RECOVERY_IOSELI(x) ((((x)-1)&amp;7)&lt;&lt;8)
DECL|macro|VAC_CTRL_RECOVERY_IOSELI_VAL
mdefine_line|#define    VAC_CTRL_RECOVERY_IOSELI_VAL(x) ((((x)&gt;&gt;8)&amp;7)+1)
DECL|macro|VAC_CTRL_DSACK0
mdefine_line|#define    VAC_CTRL_DSACK0             (1&lt;&lt;11)
DECL|macro|VAC_CTRL_DSACK1
mdefine_line|#define    VAC_CTRL_DSACK1             (1&lt;&lt;12)
DECL|macro|VAC_CTRL_DELAY_DSACKI
mdefine_line|#define    VAC_CTRL_DELAY_DSACKI(x)    ((((x)-1)&amp;7)&lt;&lt;13)
DECL|macro|VAC_CTRL_DELAY_DSACKI_VAL
mdefine_line|#define    VAC_CTRL_DELAY_DSACKI_VAL(x) ((((x)&gt;&gt;13)&amp;7)+1)
DECL|macro|VAC_DECODE_CTRL
mdefine_line|#define VAC_DECODE_CTRL      0x1400
DECL|macro|VAC_DECODE_FPUCS
mdefine_line|#define    VAC_DECODE_FPUCS   (1&lt;&lt;0)
DECL|macro|VAC_DECODE_CPUCLK
mdefine_line|#define    VAC_DECODE_CPUCLK(x)  (((x)&amp;3)&lt;&lt;1)
DECL|macro|VAC_DECODE_CPUCLK_VAL
mdefine_line|#define    VAC_DECODE_CPUCLK_VAL(x) (((x)&gt;&gt;1)&amp;3)
DECL|macro|VAC_DECODE_RDR_SLSEL0
mdefine_line|#define    VAC_DECODE_RDR_SLSEL0 (1&lt;&lt;3)
DECL|macro|VAC_DECODE_RDR_SLSEL1
mdefine_line|#define    VAC_DECODE_RDR_SLSEL1 (1&lt;&lt;4)
DECL|macro|VAC_DECODE_DSACK
mdefine_line|#define    VAC_DECODE_DSACK   (1&lt;&lt;5)
DECL|macro|VAC_DECODE_QFY_BNDR
mdefine_line|#define    VAC_DECODE_QFY_BNDR    (1&lt;&lt;6)
DECL|macro|VAC_DECODE_QFY_ICFSEL
mdefine_line|#define    VAC_DECODE_QFY_ICFSEL  (1&lt;&lt;7)
DECL|macro|VAC_DECODE_QFY_SLSEL1
mdefine_line|#define    VAC_DECODE_QFY_SLSEL1  (1&lt;&lt;8)
DECL|macro|VAC_DECODE_QFY_SLSEL0
mdefine_line|#define    VAC_DECODE_QFY_SLSEL0  (1&lt;&lt;9)
DECL|macro|VAC_DECODE_CMP_SLSEL1_LO
mdefine_line|#define    VAC_DECODE_CMP_SLSEL1_LO  (1&lt;&lt;10)
DECL|macro|VAC_DECODE_CMP_SLSEL1_HI
mdefine_line|#define    VAC_DECODE_CMP_SLSEL1_HI  (1&lt;&lt;11)
DECL|macro|VAC_DECODE_CMP_SLSEL1_VAL
mdefine_line|#define    VAC_DECODE_CMP_SLSEL1_VAL(x) (((x)&gt;&gt;10)&amp;3)
DECL|macro|VAC_DECODE_DRAMCS
mdefine_line|#define    VAC_DECODE_DRAMCS  (3&lt;&lt;12)
DECL|macro|VAC_DECODE_SHRCS
mdefine_line|#define    VAC_DECODE_SHRCS   (2&lt;&lt;12)
DECL|macro|VAC_DECODE_VSBSEL
mdefine_line|#define    VAC_DECODE_VSBSEL  (1&lt;&lt;12)
DECL|macro|VAC_DECODE_EPROMCS
mdefine_line|#define    VAC_DECODE_EPROMCS (0&lt;&lt;12)
DECL|macro|VAC_DECODE_MODE_VAL
mdefine_line|#define    VAC_DECODE_MODE_VAL(x) (((x)&gt;&gt;12)&amp;3)
DECL|macro|VAC_DECODE_QFY_DRAMCS
mdefine_line|#define    VAC_DECODE_QFY_DRAMCS  (1&lt;&lt;14)
DECL|macro|VAC_DECODE_DSACKI
mdefine_line|#define    VAC_DECODE_DSACKI  (1&lt;&lt;15)
DECL|macro|VAC_INT_STATUS
mdefine_line|#define VAC_INT_STATUS       0x1500
DECL|macro|VAC_INT_CTRL
mdefine_line|#define VAC_INT_CTRL         0x1600
DECL|macro|VAC_INT_CTRL_TIMER_PIO11
mdefine_line|#define    VAC_INT_CTRL_TIMER_PIO11    (3&lt;&lt;0)
DECL|macro|VAC_INT_CTRL_TIMER_PIO10
mdefine_line|#define    VAC_INT_CTRL_TIMER_PIO10    (2&lt;&lt;0)
DECL|macro|VAC_INT_CTRL_TIMER_PIO7
mdefine_line|#define    VAC_INT_CTRL_TIMER_PIO7     (1&lt;&lt;0)
DECL|macro|VAC_INT_CTRL_TIMER_DISABLE
mdefine_line|#define    VAC_INT_CTRL_TIMER_DISABLE  (0&lt;&lt;0)
DECL|macro|VAC_INT_CTRL_TIMER_MASK
mdefine_line|#define    VAC_INT_CTRL_TIMER_MASK     (3&lt;&lt;0)
DECL|macro|VAC_INT_CTRL_UART_B_PIO11
mdefine_line|#define    VAC_INT_CTRL_UART_B_PIO11   (3&lt;&lt;2)
DECL|macro|VAC_INT_CTRL_UART_B_PIO10
mdefine_line|#define    VAC_INT_CTRL_UART_B_PIO10   (2&lt;&lt;2)
DECL|macro|VAC_INT_CTRL_UART_B_PIO7
mdefine_line|#define    VAC_INT_CTRL_UART_B_PIO7    (1&lt;&lt;2)
DECL|macro|VAC_INT_CTRL_UART_B_DISABLE
mdefine_line|#define    VAC_INT_CTRL_UART_B_DISABLE (0&lt;&lt;2)
DECL|macro|VAC_INT_CTRL_UART_A_PIO11
mdefine_line|#define    VAC_INT_CTRL_UART_A_PIO11   (3&lt;&lt;4)
DECL|macro|VAC_INT_CTRL_UART_A_PIO10
mdefine_line|#define    VAC_INT_CTRL_UART_A_PIO10   (2&lt;&lt;4)
DECL|macro|VAC_INT_CTRL_UART_A_PIO7
mdefine_line|#define    VAC_INT_CTRL_UART_A_PIO7    (1&lt;&lt;4)
DECL|macro|VAC_INT_CTRL_UART_A_DISABLE
mdefine_line|#define    VAC_INT_CTRL_UART_A_DISABLE (0&lt;&lt;4)
DECL|macro|VAC_INT_CTRL_MBOX_PIO11
mdefine_line|#define    VAC_INT_CTRL_MBOX_PIO11     (3&lt;&lt;6)
DECL|macro|VAC_INT_CTRL_MBOX_PIO10
mdefine_line|#define    VAC_INT_CTRL_MBOX_PIO10     (2&lt;&lt;6)
DECL|macro|VAC_INT_CTRL_MBOX_PIO7
mdefine_line|#define    VAC_INT_CTRL_MBOX_PIO7      (1&lt;&lt;6)
DECL|macro|VAC_INT_CTRL_MBOX_DISABLE
mdefine_line|#define    VAC_INT_CTRL_MBOX_DISABLE   (0&lt;&lt;6)
DECL|macro|VAC_INT_CTRL_PIO4_PIO11
mdefine_line|#define    VAC_INT_CTRL_PIO4_PIO11     (3&lt;&lt;8)
DECL|macro|VAC_INT_CTRL_PIO4_PIO10
mdefine_line|#define    VAC_INT_CTRL_PIO4_PIO10     (2&lt;&lt;8)
DECL|macro|VAC_INT_CTRL_PIO4_PIO7
mdefine_line|#define    VAC_INT_CTRL_PIO4_PIO7      (1&lt;&lt;8)
DECL|macro|VAC_INT_CTRL_PIO4_DISABLE
mdefine_line|#define    VAC_INT_CTRL_PIO4_DISABLE   (0&lt;&lt;8)
DECL|macro|VAC_INT_CTRL_PIO7_PIO11
mdefine_line|#define    VAC_INT_CTRL_PIO7_PIO11     (3&lt;&lt;10)
DECL|macro|VAC_INT_CTRL_PIO7_PIO10
mdefine_line|#define    VAC_INT_CTRL_PIO7_PIO10     (2&lt;&lt;10)
DECL|macro|VAC_INT_CTRL_PIO7_PIO7
mdefine_line|#define    VAC_INT_CTRL_PIO7_PIO7      (1&lt;&lt;10)
DECL|macro|VAC_INT_CTRL_PIO7_DISABLE
mdefine_line|#define    VAC_INT_CTRL_PIO7_DISABLE   (0&lt;&lt;10)
DECL|macro|VAC_INT_CTRL_PIO8_PIO11
mdefine_line|#define    VAC_INT_CTRL_PIO8_PIO11     (3&lt;&lt;12)
DECL|macro|VAC_INT_CTRL_PIO8_PIO10
mdefine_line|#define    VAC_INT_CTRL_PIO8_PIO10     (2&lt;&lt;12)
DECL|macro|VAC_INT_CTRL_PIO8_PIO7
mdefine_line|#define    VAC_INT_CTRL_PIO8_PIO7      (1&lt;&lt;12)
DECL|macro|VAC_INT_CTRL_PIO8_DISABLE
mdefine_line|#define    VAC_INT_CTRL_PIO8_DISABLE   (0&lt;&lt;12)
DECL|macro|VAC_INT_CTRL_PIO9_PIO11
mdefine_line|#define    VAC_INT_CTRL_PIO9_PIO11     (3&lt;&lt;14)
DECL|macro|VAC_INT_CTRL_PIO9_PIO10
mdefine_line|#define    VAC_INT_CTRL_PIO9_PIO10     (2&lt;&lt;14)
DECL|macro|VAC_INT_CTRL_PIO9_PIO7
mdefine_line|#define    VAC_INT_CTRL_PIO9_PIO7      (1&lt;&lt;14)
DECL|macro|VAC_INT_CTRL_PIO9_DISABLE
mdefine_line|#define    VAC_INT_CTRL_PIO9_DISABLE   (0&lt;&lt;14)
DECL|macro|VAC_DEV_LOC
mdefine_line|#define VAC_DEV_LOC          0x1700
DECL|macro|VAC_DEV_LOC_IOSEL
mdefine_line|#define    VAC_DEV_LOC_IOSEL(x)   (1&lt;&lt;(x))
DECL|macro|VAC_PIO_DATA_OUT
mdefine_line|#define VAC_PIO_DATA_OUT     0x1800
DECL|macro|VAC_PIO_PIN
mdefine_line|#define VAC_PIO_PIN          0x1900
DECL|macro|VAC_PIO_DIRECTION
mdefine_line|#define VAC_PIO_DIRECTION    0x1A00
DECL|macro|VAC_PIO_DIR_OUT
mdefine_line|#define    VAC_PIO_DIR_OUT(x)     (1&lt;&lt;(x))
DECL|macro|VAC_PIO_DIR_IN
mdefine_line|#define    VAC_PIO_DIR_IN(x)      (0&lt;&lt;(x))
DECL|macro|VAC_PIO_DIR_FCIACK
mdefine_line|#define    VAC_PIO_DIR_FCIACK     (1&lt;&lt;14)
DECL|macro|VAC_PIO_FUNC
mdefine_line|#define VAC_PIO_FUNC         0x1B00
DECL|macro|VAC_PIO_FUNC_UART_A_TX
mdefine_line|#define    VAC_PIO_FUNC_UART_A_TX (1&lt;&lt;0)
DECL|macro|VAC_PIO_FUNC_UART_A_RX
mdefine_line|#define    VAC_PIO_FUNC_UART_A_RX (1&lt;&lt;1)
DECL|macro|VAC_PIO_FUNC_UART_B_TX
mdefine_line|#define    VAC_PIO_FUNC_UART_B_TX (1&lt;&lt;2)
DECL|macro|VAC_PIO_FUNC_UART_B_RX
mdefine_line|#define    VAC_PIO_FUNC_UART_B_RX (1&lt;&lt;3)
DECL|macro|VAC_PIO_FUNC_IORD
mdefine_line|#define    VAC_PIO_FUNC_IORD      (1&lt;&lt;4)
DECL|macro|VAC_PIO_FUNC_IOWR
mdefine_line|#define    VAC_PIO_FUNC_IOWR      (1&lt;&lt;5)
DECL|macro|VAC_PIO_FUNC_IOSEL3
mdefine_line|#define    VAC_PIO_FUNC_IOSEL3    (1&lt;&lt;6)
DECL|macro|VAC_PIO_FUNC_IRQ7
mdefine_line|#define    VAC_PIO_FUNC_IRQ7      (1&lt;&lt;7)
DECL|macro|VAC_PIO_FUNC_IOSEL4
mdefine_line|#define    VAC_PIO_FUNC_IOSEL4    (1&lt;&lt;8)
DECL|macro|VAC_PIO_FUNC_IOSEL5
mdefine_line|#define    VAC_PIO_FUNC_IOSEL5    (1&lt;&lt;9)
DECL|macro|VAC_PIO_FUNC_IRQ10
mdefine_line|#define    VAC_PIO_FUNC_IRQ10     (1&lt;&lt;10)
DECL|macro|VAC_PIO_FUNC_IRQ11
mdefine_line|#define    VAC_PIO_FUNC_IRQ11     (1&lt;&lt;11)
DECL|macro|VAC_PIO_FUNC_OUT
mdefine_line|#define    VAC_PIO_FUNC_OUT       (1&lt;&lt;12)
DECL|macro|VAC_PIO_FUNC_IOSEL2
mdefine_line|#define    VAC_PIO_FUNC_IOSEL2    (1&lt;&lt;13)
DECL|macro|VAC_PIO_FUNC_DELAY
mdefine_line|#define    VAC_PIO_FUNC_DELAY     (1&lt;&lt;14)
DECL|macro|VAC_PIO_FUNC_FCIACK
mdefine_line|#define    VAC_PIO_FUNC_FCIACK    (1&lt;&lt;15)
DECL|macro|VAC_CPU_CLK_DIV
mdefine_line|#define VAC_CPU_CLK_DIV      0x1C00
DECL|macro|VAC_UART_A_MODE
mdefine_line|#define VAC_UART_A_MODE      0x1D00
DECL|macro|VAC_UART_MODE_PARITY_ENABLE
mdefine_line|#define    VAC_UART_MODE_PARITY_ENABLE  (1&lt;&lt;15) /* Inversed in manual ? */
DECL|macro|VAC_UART_MODE_PARITY_ODD
mdefine_line|#define    VAC_UART_MODE_PARITY_ODD     (1&lt;&lt;14) /* Inversed in manual ? */
DECL|macro|VAC_UART_MODE_8BIT_CHAR
mdefine_line|#define    VAC_UART_MODE_8BIT_CHAR      (1&lt;&lt;13)
DECL|macro|VAC_UART_MODE_BAUD
mdefine_line|#define    VAC_UART_MODE_BAUD(x)        (((x)&amp;7)&lt;&lt;10)
DECL|macro|VAC_UART_MODE_CHAR_RX_ENABLE
mdefine_line|#define    VAC_UART_MODE_CHAR_RX_ENABLE (1&lt;&lt;9)
DECL|macro|VAC_UART_MODE_CHAR_TX_ENABLE
mdefine_line|#define    VAC_UART_MODE_CHAR_TX_ENABLE (1&lt;&lt;8)
DECL|macro|VAC_UART_MODE_TX_ENABLE
mdefine_line|#define    VAC_UART_MODE_TX_ENABLE      (1&lt;&lt;7)
DECL|macro|VAC_UART_MODE_RX_ENABLE
mdefine_line|#define    VAC_UART_MODE_RX_ENABLE      (1&lt;&lt;6)
DECL|macro|VAC_UART_MODE_SEND_BREAK
mdefine_line|#define    VAC_UART_MODE_SEND_BREAK     (1&lt;&lt;5)
DECL|macro|VAC_UART_MODE_LOOPBACK
mdefine_line|#define    VAC_UART_MODE_LOOPBACK       (1&lt;&lt;4)
DECL|macro|VAC_UART_MODE_INITIAL
mdefine_line|#define    VAC_UART_MODE_INITIAL        (VAC_UART_MODE_8BIT_CHAR | &bslash;&n;                                         VAC_UART_MODE_TX_ENABLE | &bslash;&n;                                         VAC_UART_MODE_RX_ENABLE | &bslash;&n;                                         VAC_UART_MODE_CHAR_TX_ENABLE | &bslash;&n;                                         VAC_UART_MODE_CHAR_RX_ENABLE | &bslash;&n;                                         VAC_UART_MODE_BAUD(5)) /* 9600/4 */
DECL|macro|VAC_UART_A_TX
mdefine_line|#define VAC_UART_A_TX        0x1E00
DECL|macro|VAC_UART_B_MODE
mdefine_line|#define VAC_UART_B_MODE      0x1F00
DECL|macro|VAC_UART_A_RX
mdefine_line|#define VAC_UART_A_RX        0x2000
DECL|macro|VAC_UART_RX_ERR_BREAK
mdefine_line|#define    VAC_UART_RX_ERR_BREAK        (1&lt;&lt;10)
DECL|macro|VAC_UART_RX_ERR_FRAME
mdefine_line|#define    VAC_UART_RX_ERR_FRAME        (1&lt;&lt;9)
DECL|macro|VAC_UART_RX_ERR_PARITY
mdefine_line|#define    VAC_UART_RX_ERR_PARITY       (1&lt;&lt;8)
DECL|macro|VAC_UART_RX_DATA_MASK
mdefine_line|#define    VAC_UART_RX_DATA_MASK        (0xff)
DECL|macro|VAC_UART_B_RX
mdefine_line|#define VAC_UART_B_RX        0x2100
DECL|macro|VAC_UART_B_TX
mdefine_line|#define VAC_UART_B_TX        0x2200
DECL|macro|VAC_UART_A_INT_MASK
mdefine_line|#define VAC_UART_A_INT_MASK  0x2300
DECL|macro|VAC_UART_INT_RX_READY
mdefine_line|#define    VAC_UART_INT_RX_READY        (1&lt;&lt;15)
DECL|macro|VAC_UART_INT_RX_FULL
mdefine_line|#define    VAC_UART_INT_RX_FULL         (1&lt;&lt;14)
DECL|macro|VAC_UART_INT_RX_BREAK_CHANGE
mdefine_line|#define    VAC_UART_INT_RX_BREAK_CHANGE (1&lt;&lt;13)
DECL|macro|VAC_UART_INT_RX_ERRS
mdefine_line|#define    VAC_UART_INT_RX_ERRS         (1&lt;&lt;12)
DECL|macro|VAC_UART_INT_TX_READY
mdefine_line|#define    VAC_UART_INT_TX_READY        (1&lt;&lt;11)
DECL|macro|VAC_UART_INT_TX_EMPTY
mdefine_line|#define    VAC_UART_INT_TX_EMPTY        (1&lt;&lt;10)
DECL|macro|VAC_UART_B_INT_MASK
mdefine_line|#define VAC_UART_B_INT_MASK  0x2400
DECL|macro|VAC_UART_A_INT_STATUS
mdefine_line|#define VAC_UART_A_INT_STATUS  0x2500
DECL|macro|VAC_UART_STATUS_RX_READY
mdefine_line|#define    VAC_UART_STATUS_RX_READY        (1&lt;&lt;15)
DECL|macro|VAC_UART_STATUS_RX_FULL
mdefine_line|#define    VAC_UART_STATUS_RX_FULL         (1&lt;&lt;14)
DECL|macro|VAC_UART_STATUS_RX_BREAK_CHANGE
mdefine_line|#define    VAC_UART_STATUS_RX_BREAK_CHANGE (1&lt;&lt;13)
DECL|macro|VAC_UART_STATUS_RX_ERR_PARITY
mdefine_line|#define    VAC_UART_STATUS_RX_ERR_PARITY   (1&lt;&lt;12)
DECL|macro|VAC_UART_STATUS_RX_ERR_FRAME
mdefine_line|#define    VAC_UART_STATUS_RX_ERR_FRAME    (1&lt;&lt;11)
DECL|macro|VAC_UART_STATUS_RX_ERR_OVERRUN
mdefine_line|#define    VAC_UART_STATUS_RX_ERR_OVERRUN  (1&lt;&lt;10)
DECL|macro|VAC_UART_STATUS_TX_READY
mdefine_line|#define    VAC_UART_STATUS_TX_READY        (1&lt;&lt;9)
DECL|macro|VAC_UART_STATUS_TX_EMPTY
mdefine_line|#define    VAC_UART_STATUS_TX_EMPTY        (1&lt;&lt;8)
DECL|macro|VAC_UART_STATUS_INTS
mdefine_line|#define    VAC_UART_STATUS_INTS            (0xff&lt;&lt;8)
DECL|macro|VAC_UART_B_INT_STATUS
mdefine_line|#define VAC_UART_B_INT_STATUS  0x2600
DECL|macro|VAC_TIMER_DATA
mdefine_line|#define VAC_TIMER_DATA       0x2700
DECL|macro|VAC_TIMER_CTRL
mdefine_line|#define VAC_TIMER_CTRL       0x2800
DECL|macro|VAC_TIMER_ONCE
mdefine_line|#define    VAC_TIMER_ONCE      (1&lt;&lt;15)
DECL|macro|VAC_TIMER_ENABLE
mdefine_line|#define    VAC_TIMER_ENABLE    (1&lt;&lt;14)
DECL|macro|VAC_TIMER_PRESCALE
mdefine_line|#define    VAC_TIMER_PRESCALE(x) (((x)&amp;0x3F)&lt;&lt;8)
DECL|macro|VAC_ID
mdefine_line|#define VAC_ID               0x2900
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
DECL|macro|vac_inb
mdefine_line|#define vac_inb(p)    (*(volatile unsigned char *)(VAC_BASE + (p)))
DECL|macro|vac_outb
mdefine_line|#define vac_outb(v,p) (*((volatile unsigned char *)(VAC_BASE + (p))) = v)
DECL|macro|vac_inw
mdefine_line|#define vac_inw(p)    (*(volatile unsigned short*)(VAC_BASE + (p)))
DECL|macro|vac_outw
mdefine_line|#define vac_outw(v,p) (*((volatile unsigned short*)(VAC_BASE + (p))) = v)
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
macro_line|#endif /* !(_MIPS_VAC_H) */
eof
