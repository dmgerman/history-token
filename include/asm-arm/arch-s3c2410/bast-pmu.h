multiline_comment|/* linux/include/asm-arm/arch-s3c2410/bast-pmu.h&n; *&n; * (c) 2003,2004 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&t;Vincent Sanders &lt;vince@simtec.co.uk&gt;&n; *&n; * Machine BAST - Power Management chip&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *&t;08-Oct-2003&t;BJD&t;Initial creation&n;*/
macro_line|#ifndef __ASM_ARCH_BASTPMU_H
DECL|macro|__ASM_ARCH_BASTPMU_H
mdefine_line|#define __ASM_ARCH_BASTPMU_H &quot;08_OCT_2004&quot;
DECL|macro|BASTPMU_REG_IDENT
mdefine_line|#define BASTPMU_REG_IDENT&t;(0x00)
DECL|macro|BASTPMU_REG_VERSION
mdefine_line|#define BASTPMU_REG_VERSION&t;(0x01)
DECL|macro|BASTPMU_REG_DDCCTRL
mdefine_line|#define BASTPMU_REG_DDCCTRL&t;(0x02)
DECL|macro|BASTPMU_REG_POWER
mdefine_line|#define BASTPMU_REG_POWER&t;(0x03)
DECL|macro|BASTPMU_REG_RESET
mdefine_line|#define BASTPMU_REG_RESET&t;(0x04)
DECL|macro|BASTPMU_REG_GWO
mdefine_line|#define BASTPMU_REG_GWO&t;&t;(0x05)
DECL|macro|BASTPMU_REG_WOL
mdefine_line|#define BASTPMU_REG_WOL&t;&t;(0x06)
DECL|macro|BASTPMU_REG_WOR
mdefine_line|#define BASTPMU_REG_WOR&t;&t;(0x07)
DECL|macro|BASTPMU_REG_UID
mdefine_line|#define BASTPMU_REG_UID&t;&t;(0x09)
DECL|macro|BASTPMU_EEPROM
mdefine_line|#define BASTPMU_EEPROM&t;&t;(0xC0)
DECL|macro|BASTPMU_EEP_UID
mdefine_line|#define BASTPMU_EEP_UID&t;&t;(BASTPMU_EEPROM + 0)
DECL|macro|BASTPMU_EEP_WOL
mdefine_line|#define BASTPMU_EEP_WOL&t;&t;(BASTPMU_EEPROM + 8)
DECL|macro|BASTPMU_EEP_WOR
mdefine_line|#define BASTPMU_EEP_WOR&t;&t;(BASTPMU_EEPROM + 9)
DECL|macro|BASTPMU_IDENT_0
mdefine_line|#define BASTPMU_IDENT_0&t;&t;0x53
DECL|macro|BASTPMU_IDENT_1
mdefine_line|#define BASTPMU_IDENT_1&t;&t;0x42
DECL|macro|BASTPMU_IDENT_2
mdefine_line|#define BASTPMU_IDENT_2&t;&t;0x50
DECL|macro|BASTPMU_IDENT_3
mdefine_line|#define BASTPMU_IDENT_3&t;&t;0x4d
DECL|macro|BASTPMU_RESET_GUARD
mdefine_line|#define BASTPMU_RESET_GUARD&t;(0x55)
macro_line|#endif /* __ASM_ARCH_BASTPMU_H */
eof
