multiline_comment|/*&n; * Definitions for the SGI O2 Mace chip.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; */
macro_line|#ifndef __ASM_MACE_H__
DECL|macro|__ASM_MACE_H__
mdefine_line|#define __ASM_MACE_H__
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Address map&n; */
DECL|macro|MACE_BASE
mdefine_line|#define MACE_BASE&t;&t;KSEG1ADDR(0x1f000000)
DECL|macro|MACE_PCI
mdefine_line|#define MACE_PCI&t;&t;(0x00080000)
DECL|macro|MACE_VIN1
mdefine_line|#define MACE_VIN1&t;&t;(0x00100000)
DECL|macro|MACE_VIN2
mdefine_line|#define MACE_VIN2&t;&t;(0x00180000)
DECL|macro|MACE_VOUT
mdefine_line|#define MACE_VOUT&t;&t;(0x00200000)
DECL|macro|MACE_ENET
mdefine_line|#define MACE_ENET&t;&t;(0x00280000)
DECL|macro|MACE_PERIF
mdefine_line|#define MACE_PERIF&t;&t;(0x00300000)
DECL|macro|MACE_ISA_EXT
mdefine_line|#define MACE_ISA_EXT&t;&t;(0x00380000)
DECL|macro|MACE_AUDIO_BASE
mdefine_line|#define MACE_AUDIO_BASE&t;&t;(MACE_PERIF&t;&t;)
DECL|macro|MACE_ISA_BASE
mdefine_line|#define MACE_ISA_BASE&t;&t;(MACE_PERIF + 0x00010000)
DECL|macro|MACE_KBDMS_BASE
mdefine_line|#define MACE_KBDMS_BASE&t;&t;(MACE_PERIF + 0x00020000)
DECL|macro|MACE_I2C_BASE
mdefine_line|#define MACE_I2C_BASE&t;&t;(MACE_PERIF + 0x00030000)
DECL|macro|MACE_UST_BASE
mdefine_line|#define MACE_UST_BASE&t;&t;(MACE_PERIF + 0x00040000)
DECL|macro|BIT
macro_line|#undef BIT
DECL|macro|BIT
mdefine_line|#define BIT(__bit_offset) (1UL &lt;&lt; (__bit_offset))
multiline_comment|/*&n; * Mace MACEPCI interface, 32 bit regs&n; */
DECL|macro|MACEPCI_ERROR_ADDR
mdefine_line|#define MACEPCI_ERROR_ADDR&t;&t;(MACE_PCI&t;      )
DECL|macro|MACEPCI_ERROR_FLAGS
mdefine_line|#define MACEPCI_ERROR_FLAGS&t;&t;(MACE_PCI + 0x00000004)
DECL|macro|MACEPCI_CONTROL
mdefine_line|#define MACEPCI_CONTROL&t;&t;&t;(MACE_PCI + 0x00000008)
DECL|macro|MACEPCI_REV
mdefine_line|#define MACEPCI_REV&t;&t;&t;(MACE_PCI + 0x0000000c)
DECL|macro|MACEPCI_WFLUSH
mdefine_line|#define MACEPCI_WFLUSH&t;&t;&t;(MACE_PCI + 0x0000000c) /* ??? --IV !!! It&squot;s for flushing read buffers on PCI MEMORY accesses!!! */
DECL|macro|MACEPCI_CONFIG_ADDR
mdefine_line|#define MACEPCI_CONFIG_ADDR&t;&t;(MACE_PCI + 0x00000cf8)
DECL|macro|MACEPCI_CONFIG_DATA
mdefine_line|#define MACEPCI_CONFIG_DATA&t;&t;(MACE_PCI + 0x00000cfc)
DECL|macro|MACEPCI_LOW_MEMORY
mdefine_line|#define MACEPCI_LOW_MEMORY&t;&t;0x1a000000
DECL|macro|MACEPCI_LOW_IO
mdefine_line|#define MACEPCI_LOW_IO&t;&t;&t;0x18000000
DECL|macro|MACEPCI_SWAPPED_VIEW
mdefine_line|#define MACEPCI_SWAPPED_VIEW&t;&t;0
DECL|macro|MACEPCI_NATIVE_VIEW
mdefine_line|#define MACEPCI_NATIVE_VIEW&t;&t;0x40000000
DECL|macro|MACEPCI_IO
mdefine_line|#define MACEPCI_IO&t;&t;&t;0x80000000
multiline_comment|/*#define MACEPCI_HI_MEMORY&t;&t;0x0000000280000000UL * This mipght be just 0x0000000200000000UL 2G more :) (or maybe it is different between 1.1 &amp; 1.5 */
DECL|macro|MACEPCI_HI_MEMORY
mdefine_line|#define MACEPCI_HI_MEMORY&t;&t;0x0000000200000000UL /* This mipght be just 0x0000000200000000UL 2G more :) (or maybe it is different between 1.1 &amp; 1.5 */
DECL|macro|MACEPCI_HI_IO
mdefine_line|#define MACEPCI_HI_IO&t;&t;&t;0x0000000100000000UL
multiline_comment|/*&n; * Bits in the MACEPCI_CONTROL register&n; */
DECL|macro|MACEPCI_CONTROL_INT
mdefine_line|#define MACEPCI_CONTROL_INT(x)&t;&t;BIT(x)
DECL|macro|MACEPCI_CONTROL_INT_MASK
mdefine_line|#define MACEPCI_CONTROL_INT_MASK&t;0xff
DECL|macro|MACEPCI_CONTROL_SERR_ENA
mdefine_line|#define MACEPCI_CONTROL_SERR_ENA&t;BIT(8)
DECL|macro|MACEPCI_CONTROL_ARB_N6
mdefine_line|#define MACEPCI_CONTROL_ARB_N6&t;&t;BIT(9)
DECL|macro|MACEPCI_CONTROL_PARITY_ERR
mdefine_line|#define MACEPCI_CONTROL_PARITY_ERR&t;BIT(10)
DECL|macro|MACEPCI_CONTROL_MRMRA_ENA
mdefine_line|#define MACEPCI_CONTROL_MRMRA_ENA&t;BIT(11)
DECL|macro|MACEPCI_CONTROL_ARB_N3
mdefine_line|#define MACEPCI_CONTROL_ARB_N3&t;&t;BIT(12)
DECL|macro|MACEPCI_CONTROL_ARB_N4
mdefine_line|#define MACEPCI_CONTROL_ARB_N4&t;&t;BIT(13)
DECL|macro|MACEPCI_CONTROL_ARB_N5
mdefine_line|#define MACEPCI_CONTROL_ARB_N5&t;&t;BIT(14)
DECL|macro|MACEPCI_CONTROL_PARK_LIU
mdefine_line|#define MACEPCI_CONTROL_PARK_LIU&t;BIT(15)
DECL|macro|MACEPCI_CONTROL_INV_INT
mdefine_line|#define MACEPCI_CONTROL_INV_INT(x)&t;BIT(16+x)
DECL|macro|MACEPCI_CONTROL_INV_INT_MASK
mdefine_line|#define MACEPCI_CONTROL_INV_INT_MASK&t;0x00ff0000
DECL|macro|MACEPCI_CONTROL_OVERRUN_INT
mdefine_line|#define MACEPCI_CONTROL_OVERRUN_INT&t;BIT(24)
DECL|macro|MACEPCI_CONTROL_PARITY_INT
mdefine_line|#define MACEPCI_CONTROL_PARITY_INT&t;BIT(25)
DECL|macro|MACEPCI_CONTROL_SERR_INT
mdefine_line|#define MACEPCI_CONTROL_SERR_INT&t;BIT(26)
DECL|macro|MACEPCI_CONTROL_IT_INT
mdefine_line|#define MACEPCI_CONTROL_IT_INT&t;&t;BIT(27)
DECL|macro|MACEPCI_CONTROL_RE_INT
mdefine_line|#define MACEPCI_CONTROL_RE_INT&t;&t;BIT(28)
DECL|macro|MACEPCI_CONTROL_DPED_INT
mdefine_line|#define MACEPCI_CONTROL_DPED_INT&t;BIT(29)
DECL|macro|MACEPCI_CONTROL_TAR_INT
mdefine_line|#define MACEPCI_CONTROL_TAR_INT&t;&t;BIT(30)
DECL|macro|MACEPCI_CONTROL_MAR_INT
mdefine_line|#define MACEPCI_CONTROL_MAR_INT&t;&t;BIT(31)
multiline_comment|/*&n; * Bits in the MACE_PCI error register&n; */
DECL|macro|MACEPCI_ERROR_MASTER_ABORT
mdefine_line|#define MACEPCI_ERROR_MASTER_ABORT&t;&t;BIT(31)
DECL|macro|MACEPCI_ERROR_TARGET_ABORT
mdefine_line|#define MACEPCI_ERROR_TARGET_ABORT&t;&t;BIT(30)
DECL|macro|MACEPCI_ERROR_DATA_PARITY_ERR
mdefine_line|#define MACEPCI_ERROR_DATA_PARITY_ERR&t;&t;BIT(29)
DECL|macro|MACEPCI_ERROR_RETRY_ERR
mdefine_line|#define MACEPCI_ERROR_RETRY_ERR&t;&t;BIT(28)
DECL|macro|MACEPCI_ERROR_ILLEGAL_CMD
mdefine_line|#define MACEPCI_ERROR_ILLEGAL_CMD&t;&t;BIT(27)
DECL|macro|MACEPCI_ERROR_SYSTEM_ERR
mdefine_line|#define MACEPCI_ERROR_SYSTEM_ERR&t;&t;BIT(26)
DECL|macro|MACEPCI_ERROR_INTERRUPT_TEST
mdefine_line|#define MACEPCI_ERROR_INTERRUPT_TEST&t;&t;BIT(25)
DECL|macro|MACEPCI_ERROR_PARITY_ERR
mdefine_line|#define MACEPCI_ERROR_PARITY_ERR&t;&t;BIT(24)
DECL|macro|MACEPCI_ERROR_OVERRUN
mdefine_line|#define MACEPCI_ERROR_OVERRUN&t;&t;&t;BIT(23)
DECL|macro|MACEPCI_ERROR_RSVD
mdefine_line|#define MACEPCI_ERROR_RSVD&t;&t;&t;BIT(22)
DECL|macro|MACEPCI_ERROR_MEMORY_ADDR
mdefine_line|#define MACEPCI_ERROR_MEMORY_ADDR&t;&t;BIT(21)
DECL|macro|MACEPCI_ERROR_CONFIG_ADDR
mdefine_line|#define MACEPCI_ERROR_CONFIG_ADDR&t;&t;BIT(20)
DECL|macro|MACEPCI_ERROR_MASTER_ABORT_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_MASTER_ABORT_ADDR_VALID&t;BIT(19)
DECL|macro|MACEPCI_ERROR_TARGET_ABORT_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_TARGET_ABORT_ADDR_VALID&t;BIT(18)
DECL|macro|MACEPCI_ERROR_DATA_PARITY_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_DATA_PARITY_ADDR_VALID&t;BIT(17)
DECL|macro|MACEPCI_ERROR_RETRY_ADDR_VALID
mdefine_line|#define MACEPCI_ERROR_RETRY_ADDR_VALID&t;&t;BIT(16)
DECL|macro|MACEPCI_ERROR_SIG_TABORT
mdefine_line|#define MACEPCI_ERROR_SIG_TABORT&t;&t;BIT(4)
DECL|macro|MACEPCI_ERROR_DEVSEL_MASK
mdefine_line|#define MACEPCI_ERROR_DEVSEL_MASK&t;&t;0xc0
DECL|macro|MACEPCI_ERROR_DEVSEL_FAST
mdefine_line|#define MACEPCI_ERROR_DEVSEL_FAST&t;&t;0
DECL|macro|MACEPCI_ERROR_DEVSEL_MED
mdefine_line|#define MACEPCI_ERROR_DEVSEL_MED&t;&t;0x40
DECL|macro|MACEPCI_ERROR_DEVSEL_SLOW
mdefine_line|#define MACEPCI_ERROR_DEVSEL_SLOW&t;&t;0x80
DECL|macro|MACEPCI_ERROR_FBB
mdefine_line|#define MACEPCI_ERROR_FBB&t;&t;&t;BIT(1)
DECL|macro|MACEPCI_ERROR_66MHZ
mdefine_line|#define MACEPCI_ERROR_66MHZ&t;&t;&t;BIT(0)
multiline_comment|/*&n; * Mace timer registers - 64 bit regs (63:32 are UST, 31:0 are MSC)&n; */
DECL|macro|MSC_PART
mdefine_line|#define MSC_PART(__reg) ((__reg) &amp; 0x00000000ffffffff)
DECL|macro|UST_PART
mdefine_line|#define UST_PART(__reg) (((__reg) &amp; 0xffffffff00000000) &gt;&gt; 32)
DECL|macro|MACE_UST_UST
mdefine_line|#define MACE_UST_UST&t;&t;(MACE_UST_BASE&t;&t;   ) /* Universial system time */
DECL|macro|MACE_UST_COMPARE1
mdefine_line|#define MACE_UST_COMPARE1&t;(MACE_UST_BASE + 0x00000008) /* Interrupt compare reg 1 */
DECL|macro|MACE_UST_COMPARE2
mdefine_line|#define MACE_UST_COMPARE2&t;(MACE_UST_BASE + 0x00000010) /* Interrupt compare reg 2 */
DECL|macro|MACE_UST_COMPARE3
mdefine_line|#define MACE_UST_COMPARE3&t;(MACE_UST_BASE + 0x00000018) /* Interrupt compare reg 3 */
DECL|macro|MACE_UST_PERIOD_NS
mdefine_line|#define MACE_UST_PERIOD_NS&t;960&t;/* UST Period in ns  */
DECL|macro|MACE_UST_AIN_MSC
mdefine_line|#define MACE_UST_AIN_MSC&t;(MACE_UST_BASE + 0x00000020) /* Audio in MSC/UST pair */
DECL|macro|MACE_UST_AOUT1_MSC
mdefine_line|#define MACE_UST_AOUT1_MSC&t;(MACE_UST_BASE + 0x00000028) /* Audio out 1 MSC/UST pair */
DECL|macro|MACE_UST_AOUT2_MSC
mdefine_line|#define MACE_UST_AOUT2_MSC&t;(MACE_UST_BASE + 0x00000030) /* Audio out 2 MSC/UST pair */
DECL|macro|MACE_VIN1_MSC_UST
mdefine_line|#define MACE_VIN1_MSC_UST&t;(MACE_UST_BASE + 0x00000038) /* Video In 1 MSC/UST pair */
DECL|macro|MACE_VIN2_MSC_UST
mdefine_line|#define MACE_VIN2_MSC_UST&t;(MACE_UST_BASE + 0x00000040) /* Video In 2 MSC/UST pair */
DECL|macro|MACE_VOUT_MSC_UST
mdefine_line|#define MACE_VOUT_MSC_UST&t;(MACE_UST_BASE + 0x00000048) /* Video out MSC/UST pair */
multiline_comment|/*&n; * Mace &quot;ISA&quot; peripherals&n; */
DECL|macro|MACEISA_EPP_BASE
mdefine_line|#define MACEISA_EPP_BASE   &t;(MACE_ISA_EXT&t;&t;  )
DECL|macro|MACEISA_ECP_BASE
mdefine_line|#define MACEISA_ECP_BASE   &t;(MACE_ISA_EXT + 0x00008000)
DECL|macro|MACEISA_SER1_BASE
mdefine_line|#define MACEISA_SER1_BASE&t;(MACE_ISA_EXT + 0x00010000)
DECL|macro|MACEISA_SER1_REGS
mdefine_line|#define MACEISA_SER1_REGS       (MACE_ISA_BASE + 0x00020000)
DECL|macro|MACEISA_SER2_BASE
mdefine_line|#define MACEISA_SER2_BASE&t;(MACE_ISA_EXT + 0x00018000)
DECL|macro|MACEISA_SER2_REGS
mdefine_line|#define MACEISA_SER2_REGS       (MACE_ISA_BASE + 0x00030000)
DECL|macro|MACEISA_RTC_BASE
mdefine_line|#define MACEISA_RTC_BASE&t;(MACE_ISA_EXT + 0x00020000)
DECL|macro|MACEISA_GAME_BASE
mdefine_line|#define MACEISA_GAME_BASE&t;(MACE_ISA_EXT + 0x00030000)
multiline_comment|/*&n; * Ringbase address and reset register - 64 bits&n; */
DECL|macro|MACEISA_RINGBASE
mdefine_line|#define MACEISA_RINGBASE&t;MACE_ISA_BASE
multiline_comment|/* Ring buffers occupy 8 4K buffers */
DECL|macro|MACEISA_RINGBUFFERS_SIZE
mdefine_line|#define MACEISA_RINGBUFFERS_SIZE 8*4*1024
multiline_comment|/*&n; * Flash-ROM/LED/DP-RAM/NIC Controller Register - 64 bits (?)&n; */
DECL|macro|MACEISA_FLASH_NIC_REG
mdefine_line|#define MACEISA_FLASH_NIC_REG&t;(MACE_ISA_BASE + 0x00000008)
multiline_comment|/*&n; * Bit definitions for that&n; */
DECL|macro|MACEISA_FLASH_WE
mdefine_line|#define MACEISA_FLASH_WE       BIT(0) /* 1=&gt; Enable FLASH writes */
DECL|macro|MACEISA_PWD_CLEAR
mdefine_line|#define MACEISA_PWD_CLEAR      BIT(1) /* 1=&gt; PWD CLEAR jumper detected */
DECL|macro|MACEISA_NIC_DEASSERT
mdefine_line|#define MACEISA_NIC_DEASSERT   BIT(2)
DECL|macro|MACEISA_NIC_DATA
mdefine_line|#define MACEISA_NIC_DATA       BIT(3)
DECL|macro|MACEISA_LED_RED
mdefine_line|#define MACEISA_LED_RED        BIT(4) /* 0=&gt; Illuminate RED LED */
DECL|macro|MACEISA_LED_GREEN
mdefine_line|#define MACEISA_LED_GREEN      BIT(5) /* 0=&gt; Illuminate GREEN LED */
DECL|macro|MACEISA_DP_RAM_ENABLE
mdefine_line|#define MACEISA_DP_RAM_ENABLE  BIT(6)
multiline_comment|/*&n; * ISA interrupt and status registers - 32 bit&n; */
DECL|macro|MACEISA_INT_STAT
mdefine_line|#define MACEISA_INT_STAT&t;(MACE_ISA_BASE + 0x00000014)
DECL|macro|MACEISA_INT_MASK
mdefine_line|#define MACEISA_INT_MASK&t;(MACE_ISA_BASE + 0x0000001c)
multiline_comment|/*&n; * Bits in the status/mask registers&n; */
DECL|macro|MACEISA_AUDIO_SW_INT
mdefine_line|#define MACEISA_AUDIO_SW_INT&t;&t;BIT (0)
DECL|macro|MACEISA_AUDIO_SC_INT
mdefine_line|#define MACEISA_AUDIO_SC_INT&t;&t;BIT (1)
DECL|macro|MACEISA_AUDIO1_DMAT_INT
mdefine_line|#define MACEISA_AUDIO1_DMAT_INT&t;&t;BIT (2)
DECL|macro|MACEISA_AUDIO1_OF_INT
mdefine_line|#define MACEISA_AUDIO1_OF_INT&t;&t;BIT (3)
DECL|macro|MACEISA_AUDIO2_DMAT_INT
mdefine_line|#define MACEISA_AUDIO2_DMAT_INT&t;&t;BIT (4)
DECL|macro|MACEISA_AUDIO2_MERR_INT
mdefine_line|#define MACEISA_AUDIO2_MERR_INT&t;&t;BIT (5)
DECL|macro|MACEISA_AUDIO3_DMAT_INT
mdefine_line|#define MACEISA_AUDIO3_DMAT_INT&t;&t;BIT (6)
DECL|macro|MACEISA_AUDIO3_MERR_INT
mdefine_line|#define MACEISA_AUDIO3_MERR_INT&t;&t;BIT (7)
DECL|macro|MACEISA_RTC_INT
mdefine_line|#define MACEISA_RTC_INT&t;&t;&t;BIT (8)
DECL|macro|MACEISA_KEYB_INT
mdefine_line|#define MACEISA_KEYB_INT&t;&t;BIT (9)
DECL|macro|MACEISA_KEYB_POLL_INT
mdefine_line|#define MACEISA_KEYB_POLL_INT&t;&t;BIT (10)
DECL|macro|MACEISA_MOUSE_INT
mdefine_line|#define MACEISA_MOUSE_INT&t;&t;BIT (11)
DECL|macro|MACEISA_MOUSE_POLL_INT
mdefine_line|#define MACEISA_MOUSE_POLL_INT&t;&t;BIT (12)
DECL|macro|MACEISA_TIMER0_INT
mdefine_line|#define MACEISA_TIMER0_INT&t;&t;BIT (13)
DECL|macro|MACEISA_TIMER1_INT
mdefine_line|#define MACEISA_TIMER1_INT&t;&t;BIT (14)
DECL|macro|MACEISA_TIMER2_INT
mdefine_line|#define MACEISA_TIMER2_INT&t;&t;BIT (15)
DECL|macro|MACEISA_PARALLEL_INT
mdefine_line|#define MACEISA_PARALLEL_INT&t;&t;BIT (16)
DECL|macro|MACEISA_PAR_CTXA_INT
mdefine_line|#define MACEISA_PAR_CTXA_INT&t;&t;BIT (17)
DECL|macro|MACEISA_PAR_CTXB_INT
mdefine_line|#define MACEISA_PAR_CTXB_INT&t;&t;BIT (18)
DECL|macro|MACEISA_PAR_MERR_INT
mdefine_line|#define MACEISA_PAR_MERR_INT&t;&t;BIT (19)
DECL|macro|MACEISA_SERIAL1_INT
mdefine_line|#define MACEISA_SERIAL1_INT&t;&t;BIT (20)
DECL|macro|MACEISA_SERIAL1_TDMAT_INT
mdefine_line|#define MACEISA_SERIAL1_TDMAT_INT&t;BIT (21)
DECL|macro|MACEISA_SERIAL1_TDMAPR_INT
mdefine_line|#define MACEISA_SERIAL1_TDMAPR_INT&t;BIT (22)
DECL|macro|MACEISA_SERIAL1_TDMAME_INT
mdefine_line|#define MACEISA_SERIAL1_TDMAME_INT&t;BIT (23)
DECL|macro|MACEISA_SERIAL1_RDMAT_INT
mdefine_line|#define MACEISA_SERIAL1_RDMAT_INT&t;BIT (24)
DECL|macro|MACEISA_SERIAL1_RDMAOR_INT
mdefine_line|#define MACEISA_SERIAL1_RDMAOR_INT&t;BIT (25)
DECL|macro|MACEISA_SERIAL2_INT
mdefine_line|#define MACEISA_SERIAL2_INT&t;&t;BIT (26)
DECL|macro|MACEISA_SERIAL2_TDMAT_INT
mdefine_line|#define MACEISA_SERIAL2_TDMAT_INT&t;BIT (27)
DECL|macro|MACEISA_SERIAL2_TDMAPR_INT
mdefine_line|#define MACEISA_SERIAL2_TDMAPR_INT&t;BIT (28)
DECL|macro|MACEISA_SERIAL2_TDMAME_INT
mdefine_line|#define MACEISA_SERIAL2_TDMAME_INT&t;BIT (29)
DECL|macro|MACEISA_SERIAL2_RDMAT_INT
mdefine_line|#define MACEISA_SERIAL2_RDMAT_INT&t;BIT (30)
DECL|macro|MACEISA_SERIAL2_RDMAOR_INT
mdefine_line|#define MACEISA_SERIAL2_RDMAOR_INT&t;BIT (31)
DECL|macro|MACEI2C_CONFIG
mdefine_line|#define MACEI2C_CONFIG&t;MACE_I2C_BASE
DECL|macro|MACEI2C_CONTROL
mdefine_line|#define MACEI2C_CONTROL&t;(MACE_I2C_BASE|0x10)
DECL|macro|MACEI2C_DATA
mdefine_line|#define MACEI2C_DATA&t;(MACE_I2C_BASE|0x18)
multiline_comment|/* Bits for I2C_CONFIG */
DECL|macro|MACEI2C_RESET
mdefine_line|#define MACEI2C_RESET           BIT(0)
DECL|macro|MACEI2C_FAST
mdefine_line|#define MACEI2C_FAST            BIT(1)
DECL|macro|MACEI2C_DATA_OVERRIDE
mdefine_line|#define MACEI2C_DATA_OVERRIDE   BIT(2)
DECL|macro|MACEI2C_CLOCK_OVERRIDE
mdefine_line|#define MACEI2C_CLOCK_OVERRIDE  BIT(3)
DECL|macro|MACEI2C_DATA_STATUS
mdefine_line|#define MACEI2C_DATA_STATUS     BIT(4)
DECL|macro|MACEI2C_CLOCK_STATUS
mdefine_line|#define MACEI2C_CLOCK_STATUS    BIT(5)
multiline_comment|/* Bits for I2C_CONTROL */
DECL|macro|MACEI2C_NOT_IDLE
mdefine_line|#define MACEI2C_NOT_IDLE        BIT(0)&t;/* write: 0=force idle&n;&t;&t;&t;&t;         * read: 0=idle 1=not idle */
DECL|macro|MACEI2C_DIR
mdefine_line|#define MACEI2C_DIR&t;&t;BIT(1)&t;/* 0=write 1=read */
DECL|macro|MACEI2C_MORE_BYTES
mdefine_line|#define MACEI2C_MORE_BYTES&t;BIT(2)&t;/* 0=last byte 1=more bytes */
DECL|macro|MACEI2C_TRANS_BUSY
mdefine_line|#define MACEI2C_TRANS_BUSY&t;BIT(4)&t;/* 0=trans done 1=trans busy */
DECL|macro|MACEI2C_NACK
mdefine_line|#define MACEI2C_NACK&t;        BIT(5)&t;/* 0=ack received 1=ack not */
DECL|macro|MACEI2C_BUS_ERROR
mdefine_line|#define MACEI2C_BUS_ERROR&t;BIT(7)&t;/* 0=no bus err 1=bus err */
DECL|macro|MACEISA_AUDIO_INT
mdefine_line|#define MACEISA_AUDIO_INT (MACEISA_AUDIO_SW_INT |               &bslash;&n;                           MACEISA_AUDIO_SC_INT |               &bslash;&n;                           MACEISA_AUDIO1_DMAT_INT |            &bslash;&n;                           MACEISA_AUDIO1_OF_INT |              &bslash;&n;                           MACEISA_AUDIO2_DMAT_INT |            &bslash;&n;                           MACEISA_AUDIO2_MERR_INT |            &bslash;&n;                           MACEISA_AUDIO3_DMAT_INT |            &bslash;&n;                           MACEISA_AUDIO3_MERR_INT)
DECL|macro|MACEISA_MISC_INT
mdefine_line|#define MACEISA_MISC_INT (MACEISA_RTC_INT |                     &bslash;&n;                          MACEISA_KEYB_INT |                    &bslash;&n;                          MACEISA_KEYB_POLL_INT |               &bslash;&n;                          MACEISA_MOUSE_INT |                   &bslash;&n;                          MACEISA_MOUSE_POLL_INT |              &bslash;&n;                          MACEISA_TIMER0_INT |                  &bslash;&n;                          MACEISA_TIMER1_INT |                  &bslash;&n;                          MACEISA_TIMER2_INT)
DECL|macro|MACEISA_SUPERIO_INT
mdefine_line|#define MACEISA_SUPERIO_INT (MACEISA_PARALLEL_INT |             &bslash;&n;                             MACEISA_PAR_CTXA_INT |             &bslash;&n;                             MACEISA_PAR_CTXB_INT |             &bslash;&n;                             MACEISA_PAR_MERR_INT |             &bslash;&n;                             MACEISA_SERIAL1_INT |              &bslash;&n;                             MACEISA_SERIAL1_TDMAT_INT |        &bslash;&n;                             MACEISA_SERIAL1_TDMAPR_INT |       &bslash;&n;                             MACEISA_SERIAL1_TDMAME_INT |       &bslash;&n;                             MACEISA_SERIAL1_RDMAT_INT |        &bslash;&n;                             MACEISA_SERIAL1_RDMAOR_INT |       &bslash;&n;                             MACEISA_SERIAL2_INT |              &bslash;&n;                             MACEISA_SERIAL2_TDMAT_INT |        &bslash;&n;                             MACEISA_SERIAL2_TDMAPR_INT |       &bslash;&n;                             MACEISA_SERIAL2_TDMAME_INT |       &bslash;&n;                             MACEISA_SERIAL2_RDMAT_INT |        &bslash;&n;                             MACEISA_SERIAL2_RDMAOR_INT)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * XXX Some of these are probably not needed (or even legal?)&n; */
DECL|function|mace_read_8
r_static
r_inline
id|u8
id|mace_read_8
(paren
r_int
r_int
id|__offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|mace_read_16
r_static
r_inline
id|u16
id|mace_read_16
(paren
r_int
r_int
id|__offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|mace_read_32
r_static
r_inline
id|u32
id|mace_read_32
(paren
r_int
r_int
id|__offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|mace_read_64
r_static
r_inline
id|u64
id|mace_read_64
(paren
r_int
r_int
id|__offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|u64
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|mace_write_8
r_static
r_inline
r_void
id|mace_write_8
(paren
r_int
r_int
id|__offset
comma
id|u8
id|__val
)paren
(brace
op_star
(paren
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
op_assign
id|__val
suffix:semicolon
)brace
DECL|function|mace_write_16
r_static
r_inline
r_void
id|mace_write_16
(paren
r_int
r_int
id|__offset
comma
id|u16
id|__val
)paren
(brace
op_star
(paren
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
op_assign
id|__val
suffix:semicolon
)brace
DECL|function|mace_write_32
r_static
r_inline
r_void
id|mace_write_32
(paren
r_int
r_int
id|__offset
comma
id|u32
id|__val
)paren
(brace
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
op_assign
id|__val
suffix:semicolon
)brace
DECL|function|mace_write_64
r_static
r_inline
r_void
id|mace_write_64
(paren
r_int
r_int
id|__offset
comma
id|u64
id|__val
)paren
(brace
op_star
(paren
(paren
r_volatile
id|u64
op_star
)paren
(paren
id|MACE_BASE
op_plus
id|__offset
)paren
)paren
op_assign
id|__val
suffix:semicolon
)brace
multiline_comment|/* Call it whenever device needs to read data from main memory coherently */
DECL|function|mace_inv_read_buffers
r_static
r_inline
r_void
id|mace_inv_read_buffers
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&t;mace_write_32(MACEPCI_WFLUSH,0xffffffff);*/
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_MACE_H__ */
eof
