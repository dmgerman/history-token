macro_line|#ifndef __MODE_CTRL00_H
DECL|macro|__MODE_CTRL00_H
mdefine_line|#define __MODE_CTRL00_H
multiline_comment|/*&n; * Register definitions for the reset and mode control&n; */
multiline_comment|/*&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
DECL|macro|BOOT_CR
mdefine_line|#define BOOT_CR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  ))
DECL|macro|BOOT_CR_BF_MSK
mdefine_line|#define BOOT_CR_BF_MSK (0x1)
DECL|macro|BOOT_CR_BF_OFST
mdefine_line|#define BOOT_CR_BF_OFST (0)
DECL|macro|BOOT_CR_HM_MSK
mdefine_line|#define BOOT_CR_HM_MSK (0x2)
DECL|macro|BOOT_CR_HM_OFST
mdefine_line|#define BOOT_CR_HM_OFST (1)
DECL|macro|BOOT_CR_RE_MSK
mdefine_line|#define BOOT_CR_RE_MSK (0x4)
DECL|macro|BOOT_CR_RE_OFST
mdefine_line|#define BOOT_CR_RE_OFST (2)
DECL|macro|RESET_SR
mdefine_line|#define RESET_SR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x4 ))
DECL|macro|RESET_SR_WR_MSK
mdefine_line|#define RESET_SR_WR_MSK (0x1)
DECL|macro|RESET_SR_WR_OFST
mdefine_line|#define RESET_SR_WR_OFST (0)
DECL|macro|RESET_SR_CR_MSK
mdefine_line|#define RESET_SR_CR_MSK (0x2)
DECL|macro|RESET_SR_CR_OFST
mdefine_line|#define RESET_SR_CR_OFST (1)
DECL|macro|RESET_SR_JT_MSK
mdefine_line|#define RESET_SR_JT_MSK (0x4)
DECL|macro|RESET_SR_JT_OFST
mdefine_line|#define RESET_SR_JT_OFST (2)
DECL|macro|RESET_SR_ER_MSK
mdefine_line|#define RESET_SR_ER_MSK (0x8)
DECL|macro|RESET_SR_ER_OFST
mdefine_line|#define RESET_SR_ER_OFST (3)
DECL|macro|ID_CODE
mdefine_line|#define ID_CODE(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x08 ))
DECL|macro|SRAM0_SR
mdefine_line|#define SRAM0_SR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x20 ))
DECL|macro|SRAM0_SR_SIZE_MSK
mdefine_line|#define SRAM0_SR_SIZE_MSK (0xFFFFF000)
DECL|macro|SRAM0_SR_SIZE_OFST
mdefine_line|#define SRAM0_SR_SIZE_OFST (12)
DECL|macro|SRAM1_SR
mdefine_line|#define SRAM1_SR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x24 ))
DECL|macro|SRAM1_SR_SIZE_MSK
mdefine_line|#define SRAM1_SR_SIZE_MSK (0xFFFFF000)
DECL|macro|SRAM1_SR_SIZE_OFST
mdefine_line|#define SRAM1_SR_SIZE_OFST (12)
DECL|macro|DPSRAM0_SR
mdefine_line|#define DPSRAM0_SR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x30 ))
DECL|macro|DPSRAM0_SR_MODE_MSK
mdefine_line|#define DPSRAM0_SR_MODE_MSK (0xF)
DECL|macro|DPSRAM0_SR_MODE_OFST
mdefine_line|#define DPSRAM0_SR_MODE_OFST (0)
DECL|macro|DPSRAM0_SR_GLBL_MSK
mdefine_line|#define DPSRAM0_SR_GLBL_MSK (0x30)
DECL|macro|DPSRAM0_SR_SIZE_MSK
mdefine_line|#define DPSRAM0_SR_SIZE_MSK (0xFFFFF000)
DECL|macro|DPSRAM0_SR_SIZE_OFST
mdefine_line|#define DPSRAM0_SR_SIZE_OFST (12)
DECL|macro|DPSRAM0_LCR
mdefine_line|#define DPSRAM0_LCR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x34 ))
DECL|macro|DPSRAM0_LCR_LCKADDR_MSK
mdefine_line|#define DPSRAM0_LCR_LCKADDR_MSK (0x1FFE0)
DECL|macro|DPSRAM0_LCR_LCKADDR_OFST
mdefine_line|#define DPSRAM0_LCR_LCKADDR_OFST (4)
DECL|macro|DPSRAM1_SR
mdefine_line|#define DPSRAM1_SR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x38 ))
DECL|macro|DPSRAM1_SR_MODE_MSK
mdefine_line|#define DPSRAM1_SR_MODE_MSK (0xF)
DECL|macro|DPSRAM1_SR_MODE_OFST
mdefine_line|#define DPSRAM1_SR_MODE_OFST (0)
DECL|macro|DPSRAM1_SR_GLBL_MSK
mdefine_line|#define DPSRAM1_SR_GLBL_MSK (0x30)
DECL|macro|DPSRAM1_SR_GLBL_OFST
mdefine_line|#define DPSRAM1_SR_GLBL_OFST (4)
DECL|macro|DPSRAM1_SR_SIZE_MSK
mdefine_line|#define DPSRAM1_SR_SIZE_MSK (0xFFFFF000)
DECL|macro|DPSRAM1_SR_SIZE_OFST
mdefine_line|#define DPSRAM1_SR_SIZE_OFST (12)
DECL|macro|DPSRAM1_LCR
mdefine_line|#define DPSRAM1_LCR(BASE_ADDR) (MODE_CTRL00_TYPE (BASE_ADDR  + 0x3C ))
DECL|macro|DPSRAM1_LCR_LCKADDR_MSK
mdefine_line|#define DPSRAM1_LCR_LCKADDR_MSK (0x1FFE0)
DECL|macro|DPSRAM1_LCR_LCKADDR_OFST
mdefine_line|#define DPSRAM1_LCR_LCKADDR_OFST (4)
macro_line|#endif /* __MODE_CTRL00_H */
eof
