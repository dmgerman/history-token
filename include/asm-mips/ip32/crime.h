multiline_comment|/*&n; * Definitions for the SGI O2 Crime chip.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; */
macro_line|#ifndef __ASM_CRIME_H__
DECL|macro|__ASM_CRIME_H__
mdefine_line|#define __ASM_CRIME_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Address map&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|CRIME_BASE
mdefine_line|#define CRIME_BASE&t;KSEG1ADDR(0x14000000)
macro_line|#else
DECL|macro|CRIME_BASE
mdefine_line|#define CRIME_BASE&t;0xffffffffb4000000
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|function|crime_read_64
r_static
r_inline
id|u64
id|crime_read_64
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
id|CRIME_BASE
op_plus
id|__offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|crime_write_64
r_static
r_inline
r_void
id|crime_write_64
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
id|CRIME_BASE
op_plus
id|__offset
)paren
)paren
op_assign
id|__val
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|BIT
macro_line|#undef BIT
DECL|macro|BIT
mdefine_line|#define BIT(x) (1UL &lt;&lt; (x))
multiline_comment|/* All CRIME registers are 64 bits */
DECL|macro|CRIME_ID
mdefine_line|#define CRIME_ID&t;&t;0
DECL|macro|CRIME_ID_MASK
mdefine_line|#define CRIME_ID_MASK&t;&t;0xff
DECL|macro|CRIME_ID_IDBITS
mdefine_line|#define CRIME_ID_IDBITS&t;&t;0xf0
DECL|macro|CRIME_ID_IDVALUE
mdefine_line|#define CRIME_ID_IDVALUE&t;0xa0
DECL|macro|CRIME_ID_REV
mdefine_line|#define CRIME_ID_REV&t;&t;0x0f
DECL|macro|CRIME_REV_PETTY
mdefine_line|#define CRIME_REV_PETTY&t;&t;0x00
DECL|macro|CRIME_REV_11
mdefine_line|#define CRIME_REV_11&t;&t;0x11
DECL|macro|CRIME_REV_13
mdefine_line|#define CRIME_REV_13&t;&t;0x13
DECL|macro|CRIME_REV_14
mdefine_line|#define CRIME_REV_14&t;&t;0x14
DECL|macro|CRIME_CONTROL
mdefine_line|#define CRIME_CONTROL&t;&t;(0x00000008)
DECL|macro|CRIME_CONTROL_MASK
mdefine_line|#define CRIME_CONTROL_MASK&t;0x3fff&t;&t;/* 14-bit registers */
multiline_comment|/* CRIME_CONTROL register bits */
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
DECL|macro|CRIME_INT_STAT
mdefine_line|#define CRIME_INT_STAT&t;&t;&t;(0x00000010)
DECL|macro|CRIME_INT_MASK
mdefine_line|#define CRIME_INT_MASK&t;&t;&t;(0x00000018)
DECL|macro|CRIME_SOFT_INT
mdefine_line|#define CRIME_SOFT_INT&t;&t;&t;(0x00000020)
DECL|macro|CRIME_HARD_INT
mdefine_line|#define CRIME_HARD_INT&t;&t;&t;(0x00000028)
multiline_comment|/* Bits in CRIME_INT_XXX and CRIME_HARD_INT */
DECL|macro|MACE_VID_IN1_INT
mdefine_line|#define MACE_VID_IN1_INT&t;&t;BIT (0)
DECL|macro|MACE_VID_IN2_INT
mdefine_line|#define MACE_VID_IN2_INT&t;&t;BIT (1)
DECL|macro|MACE_VID_OUT_INT
mdefine_line|#define MACE_VID_OUT_INT&t;&t;BIT (2)
DECL|macro|MACE_ETHERNET_INT
mdefine_line|#define MACE_ETHERNET_INT&t;&t;BIT (3)
DECL|macro|MACE_SUPERIO_INT
mdefine_line|#define MACE_SUPERIO_INT&t;&t;BIT (4)
DECL|macro|MACE_MISC_INT
mdefine_line|#define MACE_MISC_INT&t;&t;&t;BIT (5)
DECL|macro|MACE_AUDIO_INT
mdefine_line|#define MACE_AUDIO_INT&t;&t;&t;BIT (6)
DECL|macro|MACE_PCI_BRIDGE_INT
mdefine_line|#define MACE_PCI_BRIDGE_INT&t;&t;BIT (7)
DECL|macro|MACEPCI_SCSI0_INT
mdefine_line|#define MACEPCI_SCSI0_INT&t;&t;BIT (8)
DECL|macro|MACEPCI_SCSI1_INT
mdefine_line|#define MACEPCI_SCSI1_INT&t;&t;BIT (9)
DECL|macro|MACEPCI_SLOT0_INT
mdefine_line|#define MACEPCI_SLOT0_INT&t;&t;BIT (10)
DECL|macro|MACEPCI_SLOT1_INT
mdefine_line|#define MACEPCI_SLOT1_INT&t;&t;BIT (11)
DECL|macro|MACEPCI_SLOT2_INT
mdefine_line|#define MACEPCI_SLOT2_INT&t;&t;BIT (12)
DECL|macro|MACEPCI_SHARED0_INT
mdefine_line|#define MACEPCI_SHARED0_INT&t;&t;BIT (13)
DECL|macro|MACEPCI_SHARED1_INT
mdefine_line|#define MACEPCI_SHARED1_INT&t;&t;BIT (14)
DECL|macro|MACEPCI_SHARED2_INT
mdefine_line|#define MACEPCI_SHARED2_INT&t;&t;BIT (15)
DECL|macro|CRIME_GBE0_INT
mdefine_line|#define CRIME_GBE0_INT&t;&t;&t;BIT (16)
DECL|macro|CRIME_GBE1_INT
mdefine_line|#define CRIME_GBE1_INT&t;&t;&t;BIT (17)
DECL|macro|CRIME_GBE2_INT
mdefine_line|#define CRIME_GBE2_INT&t;&t;&t;BIT (18)
DECL|macro|CRIME_GBE3_INT
mdefine_line|#define CRIME_GBE3_INT&t;&t;&t;BIT (19)
DECL|macro|CRIME_CPUERR_INT
mdefine_line|#define CRIME_CPUERR_INT&t;&t;BIT (20)
DECL|macro|CRIME_MEMERR_INT
mdefine_line|#define CRIME_MEMERR_INT&t;&t;BIT (21)
DECL|macro|CRIME_RE_EMPTY_E_INT
mdefine_line|#define CRIME_RE_EMPTY_E_INT&t;&t;BIT (22)
DECL|macro|CRIME_RE_FULL_E_INT
mdefine_line|#define CRIME_RE_FULL_E_INT&t;&t;BIT (23)
DECL|macro|CRIME_RE_IDLE_E_INT
mdefine_line|#define CRIME_RE_IDLE_E_INT&t;&t;BIT (24)
DECL|macro|CRIME_RE_EMPTY_L_INT
mdefine_line|#define CRIME_RE_EMPTY_L_INT&t;&t;BIT (25)
DECL|macro|CRIME_RE_FULL_L_INT
mdefine_line|#define CRIME_RE_FULL_L_INT&t;&t;BIT (26)
DECL|macro|CRIME_RE_IDLE_L_INT
mdefine_line|#define CRIME_RE_IDLE_L_INT    &t;&t;BIT (27)
DECL|macro|CRIME_SOFT0_INT
mdefine_line|#define CRIME_SOFT0_INT&t;&t;&t;BIT (28)
DECL|macro|CRIME_SOFT1_INT
mdefine_line|#define CRIME_SOFT1_INT&t;&t;&t;BIT (29)
DECL|macro|CRIME_SOFT2_INT
mdefine_line|#define CRIME_SOFT2_INT&t;&t;&t;BIT (30)
DECL|macro|CRIME_SYSCORERR_INT
mdefine_line|#define CRIME_SYSCORERR_INT&t;&t;CRIME_SOFT2_INT
DECL|macro|CRIME_VICE_INT
mdefine_line|#define CRIME_VICE_INT&t;&t;&t;BIT (31)
multiline_comment|/* Masks for deciding who handles the interrupt */
DECL|macro|CRIME_MACE_INT_MASK
mdefine_line|#define CRIME_MACE_INT_MASK&t;&t;0x8f
DECL|macro|CRIME_MACEISA_INT_MASK
mdefine_line|#define CRIME_MACEISA_INT_MASK&t;&t;0x70
DECL|macro|CRIME_MACEPCI_INT_MASK
mdefine_line|#define CRIME_MACEPCI_INT_MASK&t;&t;0xff00
DECL|macro|CRIME_CRIME_INT_MASK
mdefine_line|#define CRIME_CRIME_INT_MASK&t;&t;0xffff0000
multiline_comment|/*&n; * XXX Todo&n; */
DECL|macro|CRIME_DOG
mdefine_line|#define CRIME_DOG&t;&t;&t;(0x00000030)
multiline_comment|/* We are word-play compatible but not misspelling compatible */
DECL|macro|MC_GRUFF
mdefine_line|#define MC_GRUFF&t;&t;&t;CRIME_DOG
DECL|macro|CRIME_DOG_MASK
mdefine_line|#define CRIME_DOG_MASK&t;&t;&t;(0x001fffff)
multiline_comment|/* CRIME_DOG register bits */
DECL|macro|CRIME_DOG_POWER_ON_RESET
mdefine_line|#define CRIME_DOG_POWER_ON_RESET&t;(0x00010000)
DECL|macro|CRIME_DOG_WARM_RESET
mdefine_line|#define CRIME_DOG_WARM_RESET&t;&t;(0x00080000)
DECL|macro|CRIME_DOG_TIMEOUT
mdefine_line|#define CRIME_DOG_TIMEOUT&t;&t;(CRIME_DOG_POWER_ON_RESET|CRIME_DOG_WARM_RESET)
DECL|macro|CRIME_DOG_VALUE
mdefine_line|#define CRIME_DOG_VALUE&t;&t;&t;(0x00007fff)&t;/* ??? */
DECL|macro|CRIME_TIME
mdefine_line|#define CRIME_TIME&t;&t;&t;(0x00000038)
DECL|macro|CRIME_TIME_MASK
mdefine_line|#define CRIME_TIME_MASK&t;&t;&t;(0x0000ffffffffffff)
macro_line|#ifdef MASTER_FREQ
DECL|macro|MASTER_FREQ
macro_line|#undef MASTER_FREQ
macro_line|#endif
DECL|macro|CRIME_MASTER_FREQ
mdefine_line|#define CRIME_MASTER_FREQ&t;&t;66666500&t;/* Crime upcounter frequency */
DECL|macro|CRIME_NS_PER_TICK
mdefine_line|#define CRIME_NS_PER_TICK&t;&t;15&t;/* for delay_calibrate */
DECL|macro|CRIME_CPU_ERROR_ADDR
mdefine_line|#define CRIME_CPU_ERROR_ADDR&t;&t;(0x00000040)
DECL|macro|CRIME_CPU_ERROR_ADDR_MASK
mdefine_line|#define CRIME_CPU_ERROR_ADDR_MASK&t;(0x3ffffffff)
DECL|macro|CRIME_CPU_ERROR_STAT
mdefine_line|#define CRIME_CPU_ERROR_STAT&t;&t;(0x00000048)
multiline_comment|/* REV_PETTY only! */
DECL|macro|CRIME_CPU_ERROR_ENA
mdefine_line|#define CRIME_CPU_ERROR_ENA&t;&t;(0x00000050)
multiline_comment|/*&n; * bit definitions for CRIME/VICE error status and enable registers&n; */
DECL|macro|CRIME_CPU_ERROR_MASK
mdefine_line|#define CRIME_CPU_ERROR_MASK           0x7UL   /* cpu error stat is 3 bits */
DECL|macro|CRIME_CPU_ERROR_CPU_ILL_ADDR
mdefine_line|#define CRIME_CPU_ERROR_CPU_ILL_ADDR   0x4
DECL|macro|CRIME_CPU_ERROR_VICE_WRT_PRTY
mdefine_line|#define CRIME_CPU_ERROR_VICE_WRT_PRTY  0x2
DECL|macro|CRIME_CPU_ERROR_CPU_WRT_PRTY
mdefine_line|#define CRIME_CPU_ERROR_CPU_WRT_PRTY   0x1
multiline_comment|/*&n; * these are the definitions for the error status/enable  register in&n; * petty crime.  Note that the enable register does not exist in crime&n; * rev 1 and above.&n; */
DECL|macro|CRIME_CPU_ERROR_MASK_REV0
mdefine_line|#define CRIME_CPU_ERROR_MASK_REV0&t;&t;0x3ff&t;/* cpu error stat is 9 bits */
DECL|macro|CRIME_CPU_ERROR_CPU_INV_ADDR_RD
mdefine_line|#define CRIME_CPU_ERROR_CPU_INV_ADDR_RD&t;&t;0x200
DECL|macro|CRIME_CPU_ERROR_VICE_II
mdefine_line|#define CRIME_CPU_ERROR_VICE_II&t;&t;&t;0x100
DECL|macro|CRIME_CPU_ERROR_VICE_SYSAD
mdefine_line|#define CRIME_CPU_ERROR_VICE_SYSAD&t;&t;0x80
DECL|macro|CRIME_CPU_ERROR_VICE_SYSCMD
mdefine_line|#define CRIME_CPU_ERROR_VICE_SYSCMD&t;&t;0x40
DECL|macro|CRIME_CPU_ERROR_VICE_INV_ADDR
mdefine_line|#define CRIME_CPU_ERROR_VICE_INV_ADDR&t;&t;0x20
DECL|macro|CRIME_CPU_ERROR_CPU_II
mdefine_line|#define CRIME_CPU_ERROR_CPU_II&t;&t;&t;0x10
DECL|macro|CRIME_CPU_ERROR_CPU_SYSAD
mdefine_line|#define CRIME_CPU_ERROR_CPU_SYSAD&t;&t;0x8
DECL|macro|CRIME_CPU_ERROR_CPU_SYSCMD
mdefine_line|#define CRIME_CPU_ERROR_CPU_SYSCMD&t;&t;0x4
DECL|macro|CRIME_CPU_ERROR_CPU_INV_ADDR_WR
mdefine_line|#define CRIME_CPU_ERROR_CPU_INV_ADDR_WR&t;&t;0x2
DECL|macro|CRIME_CPU_ERROR_CPU_INV_REG_ADDR
mdefine_line|#define CRIME_CPU_ERROR_CPU_INV_REG_ADDR&t;0x1
DECL|macro|CRIME_VICE_ERROR_ADDR
mdefine_line|#define CRIME_VICE_ERROR_ADDR&t;&t;(0x00000058)
DECL|macro|CRIME_VICE_ERROR_ADDR_MASK
mdefine_line|#define CRIME_VICE_ERROR_ADDR_MASK&t;(0x3fffffff)
DECL|macro|CRIME_MEM_CONTROL
mdefine_line|#define CRIME_MEM_CONTROL&t;&t;(0x00000200)
DECL|macro|CRIME_MEM_CONTROL_MASK
mdefine_line|#define CRIME_MEM_CONTROL_MASK&t;&t;0x3&t;/* 25 cent register */
DECL|macro|CRIME_MEM_CONTROL_ECC_ENA
mdefine_line|#define CRIME_MEM_CONTROL_ECC_ENA&t;0x1
DECL|macro|CRIME_MEM_CONTROL_USE_ECC_REPL
mdefine_line|#define CRIME_MEM_CONTROL_USE_ECC_REPL&t;0x2
multiline_comment|/*&n; * macros for CRIME memory bank control registers.&n; */
DECL|macro|CRIME_MEM_BANK_CONTROL
mdefine_line|#define CRIME_MEM_BANK_CONTROL(__bank)&t;&t;(0x00000208 + ((__bank) &lt;&lt; 3))
DECL|macro|CRIME_MEM_BANK_CONTROL_MASK
mdefine_line|#define CRIME_MEM_BANK_CONTROL_MASK&t;&t;0x11f /* 9 bits 7:5 reserved */
DECL|macro|CRIME_MEM_BANK_CONTROL_ADDR
mdefine_line|#define CRIME_MEM_BANK_CONTROL_ADDR&t;&t;0x01f
DECL|macro|CRIME_MEM_BANK_CONTROL_SDRAM_SIZE
mdefine_line|#define CRIME_MEM_BANK_CONTROL_SDRAM_SIZE&t;0x100
DECL|macro|CRIME_MEM_REFRESH_COUNTER
mdefine_line|#define CRIME_MEM_REFRESH_COUNTER&t;(0x00000248)
DECL|macro|CRIME_MEM_REFRESH_COUNTER_MASK
mdefine_line|#define CRIME_MEM_REFRESH_COUNTER_MASK&t;0x7ff&t;/* 11-bit register */
DECL|macro|CRIME_MAXBANKS
mdefine_line|#define CRIME_MAXBANKS                 8
multiline_comment|/*&n; * CRIME Memory error status register bit definitions&n; */
DECL|macro|CRIME_MEM_ERROR_STAT
mdefine_line|#define CRIME_MEM_ERROR_STAT&t;&t;(0x00000250)
DECL|macro|CRIME_MEM_ERROR_STAT_MASK
mdefine_line|#define CRIME_MEM_ERROR_STAT_MASK       0x0ff7ffff    /* 28-bit register */
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
mdefine_line|#define CRIME_MEM_ERROR_INV_MEM_ADDR_RMW&t;0x08000000
DECL|macro|CRIME_MEM_ERROR_ADDR
mdefine_line|#define CRIME_MEM_ERROR_ADDR&t;&t;(0x00000258)
DECL|macro|CRIME_MEM_ERROR_ADDR_MASK
mdefine_line|#define CRIME_MEM_ERROR_ADDR_MASK&t;0x3fffffff
DECL|macro|CRIME_MEM_ERROR_ECC_SYN
mdefine_line|#define CRIME_MEM_ERROR_ECC_SYN&t;&t;(0x00000260)
DECL|macro|CRIME_MEM_ERROR_ECC_SYN_MASK
mdefine_line|#define CRIME_MEM_ERROR_ECC_SYN_MASK&t;0xffffffff
DECL|macro|CRIME_MEM_ERROR_ECC_CHK
mdefine_line|#define CRIME_MEM_ERROR_ECC_CHK&t;&t;(0x00000268)
DECL|macro|CRIME_MEM_ERROR_ECC_CHK_MASK
mdefine_line|#define CRIME_MEM_ERROR_ECC_CHK_MASK    0xffffffff
DECL|macro|CRIME_MEM_ERROR_ECC_REPL
mdefine_line|#define CRIME_MEM_ERROR_ECC_REPL&t;(0x00000270)
DECL|macro|CRIME_MEM_ERROR_ECC_REPL_MASK
mdefine_line|#define CRIME_MEM_ERROR_ECC_REPL_MASK&t;0xffffffff
macro_line|#endif /* __ASM_CRIME_H__ */
eof
