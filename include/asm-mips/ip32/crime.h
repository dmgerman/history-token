multiline_comment|/*&n; * Definitions for the SGI CRIME (CPU, Rendering, Interconnect and Memory&n; * Engine)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; */
macro_line|#ifndef __ASM_CRIME_H__
DECL|macro|__ASM_CRIME_H__
mdefine_line|#define __ASM_CRIME_H__
multiline_comment|/*&n; * Address map&n; */
DECL|macro|CRIME_BASE
mdefine_line|#define CRIME_BASE&t;0x14000000&t;/* physical */
DECL|macro|BIT
macro_line|#undef BIT
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;(1UL &lt;&lt; (x))
DECL|struct|sgi_crime
r_struct
id|sgi_crime
(brace
DECL|member|id
r_volatile
r_int
r_int
id|id
suffix:semicolon
DECL|macro|CRIME_ID_MASK
mdefine_line|#define CRIME_ID_MASK&t;&t;&t;0xff
DECL|macro|CRIME_ID_IDBITS
mdefine_line|#define CRIME_ID_IDBITS&t;&t;&t;0xf0
DECL|macro|CRIME_ID_IDVALUE
mdefine_line|#define CRIME_ID_IDVALUE&t;&t;0xa0
DECL|macro|CRIME_ID_REV
mdefine_line|#define CRIME_ID_REV&t;&t;&t;0x0f
DECL|macro|CRIME_REV_PETTY
mdefine_line|#define CRIME_REV_PETTY&t;&t;&t;0x00
DECL|macro|CRIME_REV_11
mdefine_line|#define CRIME_REV_11&t;&t;&t;0x11
DECL|macro|CRIME_REV_13
mdefine_line|#define CRIME_REV_13&t;&t;&t;0x13
DECL|macro|CRIME_REV_14
mdefine_line|#define CRIME_REV_14&t;&t;&t;0x14
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
DECL|macro|CRIME_CONTROL_MASK
mdefine_line|#define CRIME_CONTROL_MASK&t;&t;0x3fff
DECL|macro|CRIME_CONTROL_TRITON_SYSADC
mdefine_line|#define CRIME_CONTROL_TRITON_SYSADC&t;0x2000
DECL|macro|CRIME_CONTROL_CRIME_SYSADC
mdefine_line|#define CRIME_CONTROL_CRIME_SYSADC&t;0x1000
DECL|macro|CRIME_CONTROL_HARD_RESET
mdefine_line|#define CRIME_CONTROL_HARD_RESET&t;0x0800
DECL|macro|CRIME_CONTROL_SOFT_RESET
mdefine_line|#define CRIME_CONTROL_SOFT_RESET&t;0x0400
DECL|macro|CRIME_CONTROL_DOG_ENA
mdefine_line|#define CRIME_CONTROL_DOG_ENA&t;&t;0x0200
DECL|macro|CRIME_CONTROL_ENDIANESS
mdefine_line|#define CRIME_CONTROL_ENDIANESS&t;&t;0x0100
DECL|macro|CRIME_CONTROL_ENDIAN_BIG
mdefine_line|#define CRIME_CONTROL_ENDIAN_BIG&t;0x0100
DECL|macro|CRIME_CONTROL_ENDIAN_LITTLE
mdefine_line|#define CRIME_CONTROL_ENDIAN_LITTLE&t;0x0000
DECL|macro|CRIME_CONTROL_CQUEUE_HWM
mdefine_line|#define CRIME_CONTROL_CQUEUE_HWM&t;0x000f
DECL|macro|CRIME_CONTROL_CQUEUE_SHFT
mdefine_line|#define CRIME_CONTROL_CQUEUE_SHFT&t;0
DECL|macro|CRIME_CONTROL_WBUF_HWM
mdefine_line|#define CRIME_CONTROL_WBUF_HWM&t;&t;0x00f0
DECL|macro|CRIME_CONTROL_WBUF_SHFT
mdefine_line|#define CRIME_CONTROL_WBUF_SHFT&t;&t;8
DECL|member|istat
r_volatile
r_int
r_int
id|istat
suffix:semicolon
DECL|member|imask
r_volatile
r_int
r_int
id|imask
suffix:semicolon
DECL|member|soft_int
r_volatile
r_int
r_int
id|soft_int
suffix:semicolon
DECL|member|hard_int
r_volatile
r_int
r_int
id|hard_int
suffix:semicolon
DECL|macro|MACE_VID_IN1_INT
mdefine_line|#define MACE_VID_IN1_INT&t;&t;BIT(0)
DECL|macro|MACE_VID_IN2_INT
mdefine_line|#define MACE_VID_IN2_INT&t;&t;BIT(1)
DECL|macro|MACE_VID_OUT_INT
mdefine_line|#define MACE_VID_OUT_INT&t;&t;BIT(2)
DECL|macro|MACE_ETHERNET_INT
mdefine_line|#define MACE_ETHERNET_INT&t;&t;BIT(3)
DECL|macro|MACE_SUPERIO_INT
mdefine_line|#define MACE_SUPERIO_INT&t;&t;BIT(4)
DECL|macro|MACE_MISC_INT
mdefine_line|#define MACE_MISC_INT&t;&t;&t;BIT(5)
DECL|macro|MACE_AUDIO_INT
mdefine_line|#define MACE_AUDIO_INT&t;&t;&t;BIT(6)
DECL|macro|MACE_PCI_BRIDGE_INT
mdefine_line|#define MACE_PCI_BRIDGE_INT&t;&t;BIT(7)
DECL|macro|MACEPCI_SCSI0_INT
mdefine_line|#define MACEPCI_SCSI0_INT&t;&t;BIT(8)
DECL|macro|MACEPCI_SCSI1_INT
mdefine_line|#define MACEPCI_SCSI1_INT&t;&t;BIT(9)
DECL|macro|MACEPCI_SLOT0_INT
mdefine_line|#define MACEPCI_SLOT0_INT&t;&t;BIT(10)
DECL|macro|MACEPCI_SLOT1_INT
mdefine_line|#define MACEPCI_SLOT1_INT&t;&t;BIT(11)
DECL|macro|MACEPCI_SLOT2_INT
mdefine_line|#define MACEPCI_SLOT2_INT&t;&t;BIT(12)
DECL|macro|MACEPCI_SHARED0_INT
mdefine_line|#define MACEPCI_SHARED0_INT&t;&t;BIT(13)
DECL|macro|MACEPCI_SHARED1_INT
mdefine_line|#define MACEPCI_SHARED1_INT&t;&t;BIT(14)
DECL|macro|MACEPCI_SHARED2_INT
mdefine_line|#define MACEPCI_SHARED2_INT&t;&t;BIT(15)
DECL|macro|CRIME_GBE0_INT
mdefine_line|#define CRIME_GBE0_INT&t;&t;&t;BIT(16)
DECL|macro|CRIME_GBE1_INT
mdefine_line|#define CRIME_GBE1_INT&t;&t;&t;BIT(17)
DECL|macro|CRIME_GBE2_INT
mdefine_line|#define CRIME_GBE2_INT&t;&t;&t;BIT(18)
DECL|macro|CRIME_GBE3_INT
mdefine_line|#define CRIME_GBE3_INT&t;&t;&t;BIT(19)
DECL|macro|CRIME_CPUERR_INT
mdefine_line|#define CRIME_CPUERR_INT&t;&t;BIT(20)
DECL|macro|CRIME_MEMERR_INT
mdefine_line|#define CRIME_MEMERR_INT&t;&t;BIT(21)
DECL|macro|CRIME_RE_EMPTY_E_INT
mdefine_line|#define CRIME_RE_EMPTY_E_INT&t;&t;BIT(22)
DECL|macro|CRIME_RE_FULL_E_INT
mdefine_line|#define CRIME_RE_FULL_E_INT&t;&t;BIT(23)
DECL|macro|CRIME_RE_IDLE_E_INT
mdefine_line|#define CRIME_RE_IDLE_E_INT&t;&t;BIT(24)
DECL|macro|CRIME_RE_EMPTY_L_INT
mdefine_line|#define CRIME_RE_EMPTY_L_INT&t;&t;BIT(25)
DECL|macro|CRIME_RE_FULL_L_INT
mdefine_line|#define CRIME_RE_FULL_L_INT&t;&t;BIT(26)
DECL|macro|CRIME_RE_IDLE_L_INT
mdefine_line|#define CRIME_RE_IDLE_L_INT    &t;&t;BIT(27)
DECL|macro|CRIME_SOFT0_INT
mdefine_line|#define CRIME_SOFT0_INT&t;&t;&t;BIT(28)
DECL|macro|CRIME_SOFT1_INT
mdefine_line|#define CRIME_SOFT1_INT&t;&t;&t;BIT(29)
DECL|macro|CRIME_SOFT2_INT
mdefine_line|#define CRIME_SOFT2_INT&t;&t;&t;BIT(30)
DECL|macro|CRIME_SYSCORERR_INT
mdefine_line|#define CRIME_SYSCORERR_INT&t;&t;CRIME_SOFT2_INT
DECL|macro|CRIME_VICE_INT
mdefine_line|#define CRIME_VICE_INT&t;&t;&t;BIT(31)
multiline_comment|/* Masks for deciding who handles the interrupt */
DECL|macro|CRIME_MACE_INT_MASK
mdefine_line|#define CRIME_MACE_INT_MASK&t;&t;0x8f
DECL|macro|CRIME_MACEISA_INT_MASK
mdefine_line|#define CRIME_MACEISA_INT_MASK&t;&t;0x70
DECL|macro|CRIME_MACEPCI_INT_MASK
mdefine_line|#define CRIME_MACEPCI_INT_MASK&t;&t;0xff00
DECL|macro|CRIME_CRIME_INT_MASK
mdefine_line|#define CRIME_CRIME_INT_MASK&t;&t;0xffff0000
DECL|member|watchdog
r_volatile
r_int
r_int
id|watchdog
suffix:semicolon
DECL|macro|CRIME_DOG_POWER_ON_RESET
mdefine_line|#define CRIME_DOG_POWER_ON_RESET&t;0x00010000
DECL|macro|CRIME_DOG_WARM_RESET
mdefine_line|#define CRIME_DOG_WARM_RESET&t;&t;0x00080000
DECL|macro|CRIME_DOG_TIMEOUT
mdefine_line|#define CRIME_DOG_TIMEOUT&t;&t;(CRIME_DOG_POWER_ON_RESET|CRIME_DOG_WARM_RESET)
DECL|macro|CRIME_DOG_VALUE
mdefine_line|#define CRIME_DOG_VALUE&t;&t;&t;0x00007fff
DECL|member|timer
r_volatile
r_int
r_int
id|timer
suffix:semicolon
DECL|macro|CRIME_MASTER_FREQ
mdefine_line|#define CRIME_MASTER_FREQ&t;&t;66666500&t;/* Crime upcounter frequency */
DECL|macro|CRIME_NS_PER_TICK
mdefine_line|#define CRIME_NS_PER_TICK&t;&t;15&t;&t;/* for delay_calibrate */
DECL|member|cpu_error_addr
r_volatile
r_int
r_int
id|cpu_error_addr
suffix:semicolon
DECL|macro|CRIME_CPU_ERROR_ADDR_MASK
mdefine_line|#define CRIME_CPU_ERROR_ADDR_MASK&t;0x3ffffffff
DECL|member|cpu_error_stat
r_volatile
r_int
r_int
id|cpu_error_stat
suffix:semicolon
DECL|macro|CRIME_CPU_ERROR_MASK
mdefine_line|#define CRIME_CPU_ERROR_MASK&t;&t;0x7&t;&t;/* cpu error stat is 3 bits */
DECL|macro|CRIME_CPU_ERROR_CPU_ILL_ADDR
mdefine_line|#define CRIME_CPU_ERROR_CPU_ILL_ADDR&t;0x4
DECL|macro|CRIME_CPU_ERROR_VICE_WRT_PRTY
mdefine_line|#define CRIME_CPU_ERROR_VICE_WRT_PRTY&t;0x2
DECL|macro|CRIME_CPU_ERROR_CPU_WRT_PRTY
mdefine_line|#define CRIME_CPU_ERROR_CPU_WRT_PRTY&t;0x1
DECL|member|_pad0
r_int
r_int
id|_pad0
(braket
l_int|54
)braket
suffix:semicolon
DECL|member|mc_ctrl
r_volatile
r_int
r_int
id|mc_ctrl
suffix:semicolon
DECL|member|bank_ctrl
r_volatile
r_int
r_int
id|bank_ctrl
(braket
l_int|8
)braket
suffix:semicolon
DECL|macro|CRIME_MEM_BANK_CONTROL_MASK
mdefine_line|#define CRIME_MEM_BANK_CONTROL_MASK&t;&t;0x11f&t;/* 9 bits 7:5 reserved */
DECL|macro|CRIME_MEM_BANK_CONTROL_ADDR
mdefine_line|#define CRIME_MEM_BANK_CONTROL_ADDR&t;&t;0x01f
DECL|macro|CRIME_MEM_BANK_CONTROL_SDRAM_SIZE
mdefine_line|#define CRIME_MEM_BANK_CONTROL_SDRAM_SIZE&t;0x100
DECL|macro|CRIME_MAXBANKS
mdefine_line|#define CRIME_MAXBANKS&t;&t;&t;&t;8
DECL|member|mem_ref_counter
r_volatile
r_int
r_int
id|mem_ref_counter
suffix:semicolon
DECL|macro|CRIME_MEM_REF_COUNTER_MASK
mdefine_line|#define CRIME_MEM_REF_COUNTER_MASK&t;0x3ff&t;&t;/* 10bit */
DECL|member|mem_error_stat
r_volatile
r_int
r_int
id|mem_error_stat
suffix:semicolon
DECL|macro|CRIME_MEM_ERROR_STAT_MASK
mdefine_line|#define CRIME_MEM_ERROR_STAT_MASK       0x0ff7ffff&t;/* 28-bit register */
DECL|macro|CRIME_MEM_ERROR_MACE_ID
mdefine_line|#define CRIME_MEM_ERROR_MACE_ID&t;&t;0x0000007f
DECL|macro|CRIME_MEM_ERROR_MACE_ACCESS
mdefine_line|#define CRIME_MEM_ERROR_MACE_ACCESS&t;0x00000080
DECL|macro|CRIME_MEM_ERROR_RE_ID
mdefine_line|#define CRIME_MEM_ERROR_RE_ID&t;&t;0x00007f00
DECL|macro|CRIME_MEM_ERROR_RE_ACCESS
mdefine_line|#define CRIME_MEM_ERROR_RE_ACCESS&t;0x00008000
DECL|macro|CRIME_MEM_ERROR_GBE_ACCESS
mdefine_line|#define CRIME_MEM_ERROR_GBE_ACCESS&t;0x00010000
DECL|macro|CRIME_MEM_ERROR_VICE_ACCESS
mdefine_line|#define CRIME_MEM_ERROR_VICE_ACCESS&t;0x00020000
DECL|macro|CRIME_MEM_ERROR_CPU_ACCESS
mdefine_line|#define CRIME_MEM_ERROR_CPU_ACCESS&t;0x00040000
DECL|macro|CRIME_MEM_ERROR_RESERVED
mdefine_line|#define CRIME_MEM_ERROR_RESERVED&t;0x00080000
DECL|macro|CRIME_MEM_ERROR_SOFT_ERR
mdefine_line|#define CRIME_MEM_ERROR_SOFT_ERR&t;0x00100000
DECL|macro|CRIME_MEM_ERROR_HARD_ERR
mdefine_line|#define CRIME_MEM_ERROR_HARD_ERR&t;0x00200000
DECL|macro|CRIME_MEM_ERROR_MULTIPLE
mdefine_line|#define CRIME_MEM_ERROR_MULTIPLE&t;0x00400000
DECL|macro|CRIME_MEM_ERROR_ECC
mdefine_line|#define CRIME_MEM_ERROR_ECC&t;&t;0x01800000
DECL|macro|CRIME_MEM_ERROR_MEM_ECC_RD
mdefine_line|#define CRIME_MEM_ERROR_MEM_ECC_RD&t;0x00800000
DECL|macro|CRIME_MEM_ERROR_MEM_ECC_RMW
mdefine_line|#define CRIME_MEM_ERROR_MEM_ECC_RMW&t;0x01000000
DECL|macro|CRIME_MEM_ERROR_INV
mdefine_line|#define CRIME_MEM_ERROR_INV&t;&t;0x0e000000
DECL|macro|CRIME_MEM_ERROR_INV_MEM_ADDR_RD
mdefine_line|#define CRIME_MEM_ERROR_INV_MEM_ADDR_RD&t;0x02000000
DECL|macro|CRIME_MEM_ERROR_INV_MEM_ADDR_WR
mdefine_line|#define CRIME_MEM_ERROR_INV_MEM_ADDR_WR&t;0x04000000
DECL|macro|CRIME_MEM_ERROR_INV_MEM_ADDR_RMW
mdefine_line|#define CRIME_MEM_ERROR_INV_MEM_ADDR_RMW 0x08000000
DECL|member|mem_error_addr
r_volatile
r_int
r_int
id|mem_error_addr
suffix:semicolon
DECL|macro|CRIME_MEM_ERROR_ADDR_MASK
mdefine_line|#define CRIME_MEM_ERROR_ADDR_MASK&t;0x3fffffff
DECL|member|mem_ecc_syn
r_volatile
r_int
r_int
id|mem_ecc_syn
suffix:semicolon
DECL|macro|CRIME_MEM_ERROR_ECC_SYN_MASK
mdefine_line|#define CRIME_MEM_ERROR_ECC_SYN_MASK&t;0xffffffff
DECL|member|mem_ecc_chk
r_volatile
r_int
r_int
id|mem_ecc_chk
suffix:semicolon
DECL|macro|CRIME_MEM_ERROR_ECC_CHK_MASK
mdefine_line|#define CRIME_MEM_ERROR_ECC_CHK_MASK&t;0xffffffff
DECL|member|mem_ecc_repl
r_volatile
r_int
r_int
id|mem_ecc_repl
suffix:semicolon
DECL|macro|CRIME_MEM_ERROR_ECC_REPL_MASK
mdefine_line|#define CRIME_MEM_ERROR_ECC_REPL_MASK&t;0xffffffff
)brace
suffix:semicolon
r_extern
r_struct
id|sgi_crime
op_star
id|crime
suffix:semicolon
DECL|macro|CRIME_HI_MEM_BASE
mdefine_line|#define CRIME_HI_MEM_BASE&t;0x40000000&t;/* this is where whole 1G of RAM is mapped */
macro_line|#endif /* __ASM_CRIME_H__ */
eof
