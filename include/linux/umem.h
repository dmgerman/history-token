multiline_comment|/*&n; * This file contains defines for the&n; *   Micro Memory MM5415&n; * family PCI Memory Module with Battery Backup.&n; *&n; * Copyright Micro Memory INC 2001.  All rights reserved.&n; * Release under the terms of the GNU GENERAL PUBLIC LICENSE version 2.&n; * See the file COPYING.&n; */
macro_line|#ifndef _DRIVERS_BLOCK_MM_H
DECL|macro|_DRIVERS_BLOCK_MM_H
mdefine_line|#define _DRIVERS_BLOCK_MM_H
DECL|macro|IRQ_TIMEOUT
mdefine_line|#define IRQ_TIMEOUT (1 * HZ)
multiline_comment|/* CSR register definition */
DECL|macro|MEMCTRLSTATUS_MAGIC
mdefine_line|#define MEMCTRLSTATUS_MAGIC&t;0x00
DECL|macro|MM_MAGIC_VALUE
mdefine_line|#define  MM_MAGIC_VALUE&t;&t;(unsigned char)0x59
DECL|macro|MEMCTRLSTATUS_BATTERY
mdefine_line|#define MEMCTRLSTATUS_BATTERY&t;0x04
DECL|macro|BATTERY_1_DISABLED
mdefine_line|#define  BATTERY_1_DISABLED&t;0x01
DECL|macro|BATTERY_1_FAILURE
mdefine_line|#define  BATTERY_1_FAILURE&t;0x02
DECL|macro|BATTERY_2_DISABLED
mdefine_line|#define  BATTERY_2_DISABLED&t;0x04
DECL|macro|BATTERY_2_FAILURE
mdefine_line|#define  BATTERY_2_FAILURE&t;0x08
DECL|macro|MEMCTRLSTATUS_MEMORY
mdefine_line|#define MEMCTRLSTATUS_MEMORY&t;0x07
DECL|macro|MEM_128_MB
mdefine_line|#define  MEM_128_MB&t;&t;0xfe
DECL|macro|MEM_256_MB
mdefine_line|#define  MEM_256_MB&t;&t;0xfc
DECL|macro|MEM_512_MB
mdefine_line|#define  MEM_512_MB&t;&t;0xf8
DECL|macro|MEM_1_GB
mdefine_line|#define  MEM_1_GB&t;&t;0xf0
DECL|macro|MEM_2_GB
mdefine_line|#define  MEM_2_GB&t;&t;0xe0
DECL|macro|MEMCTRLCMD_LEDCTRL
mdefine_line|#define MEMCTRLCMD_LEDCTRL&t;0x08
DECL|macro|LED_REMOVE
mdefine_line|#define  LED_REMOVE&t;&t;2
DECL|macro|LED_FAULT
mdefine_line|#define  LED_FAULT&t;&t;4
DECL|macro|LED_POWER
mdefine_line|#define  LED_POWER&t;&t;6
DECL|macro|LED_FLIP
mdefine_line|#define&t; LED_FLIP&t;&t;255
DECL|macro|LED_OFF
mdefine_line|#define  LED_OFF&t;&t;0x00
DECL|macro|LED_ON
mdefine_line|#define  LED_ON&t;&t;&t;0x01
DECL|macro|LED_FLASH_3_5
mdefine_line|#define  LED_FLASH_3_5&t;&t;0x02
DECL|macro|LED_FLASH_7_0
mdefine_line|#define  LED_FLASH_7_0&t;&t;0x03
DECL|macro|LED_POWER_ON
mdefine_line|#define  LED_POWER_ON&t;&t;0x00
DECL|macro|LED_POWER_OFF
mdefine_line|#define  LED_POWER_OFF&t;&t;0x01
DECL|macro|USER_BIT1
mdefine_line|#define  USER_BIT1&t;&t;0x01
DECL|macro|USER_BIT2
mdefine_line|#define  USER_BIT2&t;&t;0x02
DECL|macro|MEMORY_INITIALIZED
mdefine_line|#define MEMORY_INITIALIZED&t;USER_BIT1
DECL|macro|MEMCTRLCMD_ERRCTRL
mdefine_line|#define MEMCTRLCMD_ERRCTRL&t;0x0C
DECL|macro|EDC_NONE_DEFAULT
mdefine_line|#define  EDC_NONE_DEFAULT&t;0x00
DECL|macro|EDC_NONE
mdefine_line|#define  EDC_NONE&t;&t;0x01
DECL|macro|EDC_STORE_READ
mdefine_line|#define  EDC_STORE_READ&t;&t;0x02
DECL|macro|EDC_STORE_CORRECT
mdefine_line|#define  EDC_STORE_CORRECT&t;0x03
DECL|macro|MEMCTRLCMD_ERRCNT
mdefine_line|#define MEMCTRLCMD_ERRCNT&t;0x0D
DECL|macro|MEMCTRLCMD_ERRSTATUS
mdefine_line|#define MEMCTRLCMD_ERRSTATUS&t;0x0E
DECL|macro|ERROR_DATA_LOG
mdefine_line|#define ERROR_DATA_LOG&t;&t;0x20
DECL|macro|ERROR_ADDR_LOG
mdefine_line|#define ERROR_ADDR_LOG&t;&t;0x28
DECL|macro|ERROR_COUNT
mdefine_line|#define ERROR_COUNT&t;&t;0x3D
DECL|macro|ERROR_SYNDROME
mdefine_line|#define ERROR_SYNDROME&t;&t;0x3E
DECL|macro|ERROR_CHECK
mdefine_line|#define ERROR_CHECK&t;&t;0x3F
DECL|macro|DMA_PCI_ADDR
mdefine_line|#define DMA_PCI_ADDR&t;&t;0x40
DECL|macro|DMA_LOCAL_ADDR
mdefine_line|#define DMA_LOCAL_ADDR&t;&t;0x48
DECL|macro|DMA_TRANSFER_SIZE
mdefine_line|#define DMA_TRANSFER_SIZE&t;0x50
DECL|macro|DMA_DESCRIPTOR_ADDR
mdefine_line|#define DMA_DESCRIPTOR_ADDR&t;0x58
DECL|macro|DMA_SEMAPHORE_ADDR
mdefine_line|#define DMA_SEMAPHORE_ADDR&t;0x60
DECL|macro|DMA_STATUS_CTRL
mdefine_line|#define DMA_STATUS_CTRL&t;&t;0x68
DECL|macro|DMASCR_GO
mdefine_line|#define  DMASCR_GO&t;&t;0x00001
DECL|macro|DMASCR_TRANSFER_READ
mdefine_line|#define  DMASCR_TRANSFER_READ&t;0x00002
DECL|macro|DMASCR_CHAIN_EN
mdefine_line|#define  DMASCR_CHAIN_EN&t;0x00004
DECL|macro|DMASCR_SEM_EN
mdefine_line|#define  DMASCR_SEM_EN&t;&t;0x00010
DECL|macro|DMASCR_DMA_COMP_EN
mdefine_line|#define  DMASCR_DMA_COMP_EN&t;0x00020
DECL|macro|DMASCR_CHAIN_COMP_EN
mdefine_line|#define  DMASCR_CHAIN_COMP_EN&t;0x00040
DECL|macro|DMASCR_ERR_INT_EN
mdefine_line|#define  DMASCR_ERR_INT_EN&t;0x00080
DECL|macro|DMASCR_PARITY_INT_EN
mdefine_line|#define  DMASCR_PARITY_INT_EN&t;0x00100
DECL|macro|DMASCR_ANY_ERR
mdefine_line|#define  DMASCR_ANY_ERR&t;&t;0x00800
DECL|macro|DMASCR_MBE_ERR
mdefine_line|#define  DMASCR_MBE_ERR&t;&t;0x01000
DECL|macro|DMASCR_PARITY_ERR_REP
mdefine_line|#define  DMASCR_PARITY_ERR_REP&t;0x02000
DECL|macro|DMASCR_PARITY_ERR_DET
mdefine_line|#define  DMASCR_PARITY_ERR_DET&t;0x04000
DECL|macro|DMASCR_SYSTEM_ERR_SIG
mdefine_line|#define  DMASCR_SYSTEM_ERR_SIG&t;0x08000
DECL|macro|DMASCR_TARGET_ABT
mdefine_line|#define  DMASCR_TARGET_ABT&t;0x10000
DECL|macro|DMASCR_MASTER_ABT
mdefine_line|#define  DMASCR_MASTER_ABT&t;0x20000
DECL|macro|DMASCR_DMA_COMPLETE
mdefine_line|#define  DMASCR_DMA_COMPLETE&t;0x40000
DECL|macro|DMASCR_CHAIN_COMPLETE
mdefine_line|#define  DMASCR_CHAIN_COMPLETE&t;0x80000
multiline_comment|/* &n;3.SOME PCs HAVE HOST BRIDGES WHICH APPARENTLY DO NOT CORRECTLY HANDLE &n;READ-LINE (0xE) OR READ-MULTIPLE (0xC) PCI COMMAND CODES DURING DMA &n;TRANSFERS. IN OTHER SYSTEMS THESE COMMAND CODES WILL CAUSE THE HOST BRIDGE &n;TO ALLOW LONGER BURSTS DURING DMA READ OPERATIONS. THE UPPER FOUR BITS &n;(31..28) OF THE DMA CSR HAVE BEEN MADE PROGRAMMABLE, SO THAT EITHER A 0x6, &n;AN 0xE OR A 0xC CAN BE WRITTEN TO THEM TO SET THE COMMAND CODE USED DURING &n;DMA READ OPERATIONS.&n;*/
DECL|macro|DMASCR_READ
mdefine_line|#define        DMASCR_READ   0x60000000
DECL|macro|DMASCR_READLINE
mdefine_line|#define        DMASCR_READLINE   0xE0000000
DECL|macro|DMASCR_READMULTI
mdefine_line|#define        DMASCR_READMULTI   0xC0000000
DECL|macro|DMASCR_ERROR_MASK
mdefine_line|#define DMASCR_ERROR_MASK&t;(DMASCR_MASTER_ABT | DMASCR_TARGET_ABT | DMASCR_SYSTEM_ERR_SIG | DMASCR_PARITY_ERR_DET | DMASCR_MBE_ERR | DMASCR_ANY_ERR)
DECL|macro|DMASCR_HARD_ERROR
mdefine_line|#define DMASCR_HARD_ERROR&t;(DMASCR_MASTER_ABT | DMASCR_TARGET_ABT | DMASCR_SYSTEM_ERR_SIG | DMASCR_PARITY_ERR_DET | DMASCR_MBE_ERR)
DECL|macro|WINDOWMAP_WINNUM
mdefine_line|#define WINDOWMAP_WINNUM&t;0x7B
DECL|macro|DMA_READ_FROM_HOST
mdefine_line|#define DMA_READ_FROM_HOST 0
DECL|macro|DMA_WRITE_TO_HOST
mdefine_line|#define DMA_WRITE_TO_HOST 1
DECL|struct|mm_dma_desc
r_struct
id|mm_dma_desc
(brace
DECL|member|pci_addr
id|u64
id|pci_addr
suffix:semicolon
DECL|member|local_addr
id|u64
id|local_addr
suffix:semicolon
DECL|member|transfer_size
id|u32
id|transfer_size
suffix:semicolon
DECL|member|zero1
id|u32
id|zero1
suffix:semicolon
DECL|member|next_desc_addr
id|u64
id|next_desc_addr
suffix:semicolon
DECL|member|sem_addr
id|u64
id|sem_addr
suffix:semicolon
DECL|member|control_bits
id|u32
id|control_bits
suffix:semicolon
DECL|member|zero2
id|u32
id|zero2
suffix:semicolon
DECL|member|data_dma_handle
id|dma_addr_t
id|data_dma_handle
suffix:semicolon
multiline_comment|/* Copy of the bits */
DECL|member|sem_control_bits
id|u64
id|sem_control_bits
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|macro|PCI_VENDOR_ID_MICRO_MEMORY
mdefine_line|#define PCI_VENDOR_ID_MICRO_MEMORY&t;&t;0x1332
DECL|macro|PCI_DEVICE_ID_MICRO_MEMORY_5415CN
mdefine_line|#define PCI_DEVICE_ID_MICRO_MEMORY_5415CN&t;0x5415
macro_line|#endif
eof
