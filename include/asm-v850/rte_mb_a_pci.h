multiline_comment|/*&n; * include/asm-v850/mb_a_pci.h -- PCI support for Midas lab RTE-MOTHER-A board&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_MB_A_PCI_H__
DECL|macro|__V850_MB_A_PCI_H__
mdefine_line|#define __V850_MB_A_PCI_H__
DECL|macro|MB_A_PCI_MEM_ADDR
mdefine_line|#define MB_A_PCI_MEM_ADDR&t;GCS5_ADDR
DECL|macro|MB_A_PCI_MEM_SIZE
mdefine_line|#define MB_A_PCI_MEM_SIZE&t;(GCS5_SIZE / 2)
DECL|macro|MB_A_PCI_IO_ADDR
mdefine_line|#define MB_A_PCI_IO_ADDR&t;(GCS5_ADDR + MB_A_PCI_MEM_SIZE)
DECL|macro|MB_A_PCI_IO_SIZE
mdefine_line|#define MB_A_PCI_IO_SIZE&t;(GCS5_SIZE / 2)
DECL|macro|MB_A_PCI_REG_BASE_ADDR
mdefine_line|#define MB_A_PCI_REG_BASE_ADDR&t;GCS6_ADDR
DECL|macro|MB_A_PCI_PCICR_ADDR
mdefine_line|#define MB_A_PCI_PCICR_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x4)
DECL|macro|MB_A_PCI_PCICR
mdefine_line|#define MB_A_PCI_PCICR&t;&t;(*(volatile u16 *)MB_A_PCI_PCICR_ADDR)
DECL|macro|MB_A_PCI_PCISR_ADDR
mdefine_line|#define MB_A_PCI_PCISR_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x6)
DECL|macro|MB_A_PCI_PCISR
mdefine_line|#define MB_A_PCI_PCISR&t;&t;(*(volatile u16 *)MB_A_PCI_PCISR_ADDR)
DECL|macro|MB_A_PCI_PCILTR_ADDR
mdefine_line|#define MB_A_PCI_PCILTR_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0xD)
DECL|macro|MB_A_PCI_PCILTR
mdefine_line|#define MB_A_PCI_PCILTR&t;&t;(*(volatile u8 *)MB_A_PCI_PCILTR_ADDR)
DECL|macro|MB_A_PCI_PCIBAR0_ADDR
mdefine_line|#define MB_A_PCI_PCIBAR0_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x10)
DECL|macro|MB_A_PCI_PCIBAR0
mdefine_line|#define MB_A_PCI_PCIBAR0&t;(*(volatile u32 *)MB_A_PCI_PCIBAR0_ADDR)
DECL|macro|MB_A_PCI_PCIBAR1_ADDR
mdefine_line|#define MB_A_PCI_PCIBAR1_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x14)
DECL|macro|MB_A_PCI_PCIBAR1
mdefine_line|#define MB_A_PCI_PCIBAR1&t;(*(volatile u32 *)MB_A_PCI_PCIBAR1_ADDR)
DECL|macro|MB_A_PCI_PCIBAR2_ADDR
mdefine_line|#define MB_A_PCI_PCIBAR2_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x18)
DECL|macro|MB_A_PCI_PCIBAR2
mdefine_line|#define MB_A_PCI_PCIBAR2&t;(*(volatile u32 *)MB_A_PCI_PCIBAR2_ADDR)
DECL|macro|MB_A_PCI_VENDOR_ID_ADDR
mdefine_line|#define MB_A_PCI_VENDOR_ID_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x2C)
DECL|macro|MB_A_PCI_VENDOR_ID
mdefine_line|#define MB_A_PCI_VENDOR_ID&t;(*(volatile u16 *)MB_A_PCI_VENDOR_ID_ADDR)
DECL|macro|MB_A_PCI_DEVICE_ID_ADDR
mdefine_line|#define MB_A_PCI_DEVICE_ID_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x2E)
DECL|macro|MB_A_PCI_DEVICE_ID
mdefine_line|#define MB_A_PCI_DEVICE_ID&t;(*(volatile u16 *)MB_A_PCI_DEVICE_ID_ADDR)
DECL|macro|MB_A_PCI_DMRR_ADDR
mdefine_line|#define MB_A_PCI_DMRR_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0x9C)
DECL|macro|MB_A_PCI_DMRR
mdefine_line|#define MB_A_PCI_DMRR&t;&t;(*(volatile u32 *)MB_A_PCI_DMRR_ADDR)
DECL|macro|MB_A_PCI_DMLBAM_ADDR
mdefine_line|#define MB_A_PCI_DMLBAM_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0xA0)
DECL|macro|MB_A_PCI_DMLBAM
mdefine_line|#define MB_A_PCI_DMLBAM&t;&t;(*(volatile u32 *)MB_A_PCI_DMLBAM_ADDR)
DECL|macro|MB_A_PCI_DMLBAI_ADDR
mdefine_line|#define MB_A_PCI_DMLBAI_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0xA4)
DECL|macro|MB_A_PCI_DMLBAI
mdefine_line|#define MB_A_PCI_DMLBAI&t;&t;(*(volatile u32 *)MB_A_PCI_DMLBAI_ADDR)
DECL|macro|MB_A_PCI_PCIPBAM_ADDR
mdefine_line|#define MB_A_PCI_PCIPBAM_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0xA8)
DECL|macro|MB_A_PCI_PCIPBAM
mdefine_line|#define MB_A_PCI_PCIPBAM&t;(*(volatile u32 *)MB_A_PCI_PCIPBAM_ADDR)
multiline_comment|/* `PCI Configuration Address Register for Direct Master to PCI IO/CFG&squot;  */
DECL|macro|MB_A_PCI_DMCFGA_ADDR
mdefine_line|#define MB_A_PCI_DMCFGA_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0xAC)
DECL|macro|MB_A_PCI_DMCFGA
mdefine_line|#define MB_A_PCI_DMCFGA&t;&t;(*(volatile u32 *)MB_A_PCI_DMCFGA_ADDR)
multiline_comment|/* `PCI Permanent Configuration ID Register&squot;  */
DECL|macro|MB_A_PCI_PCIHIDR_ADDR
mdefine_line|#define MB_A_PCI_PCIHIDR_ADDR&t;(MB_A_PCI_REG_BASE_ADDR + 0xF0)
DECL|macro|MB_A_PCI_PCIHIDR
mdefine_line|#define MB_A_PCI_PCIHIDR&t;(*(volatile u32 *)MB_A_PCI_PCIHIDR_ADDR)
macro_line|#endif /* __V850_MB_A_PCI_H__ */
eof
