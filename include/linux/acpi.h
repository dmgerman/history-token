multiline_comment|/*&n; *  acpi.h - ACPI driver interface&n; *&n; *  Copyright (C) 1999 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_ACPI_H
DECL|macro|_LINUX_ACPI_H
mdefine_line|#define _LINUX_ACPI_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#endif /* __KERNEL__ */
DECL|typedef|acpi_sstate_t
r_typedef
r_int
id|acpi_sstate_t
suffix:semicolon
multiline_comment|/*&n; * Device states&n; */
r_enum
(brace
DECL|enumerator|ACPI_D0
id|ACPI_D0
comma
multiline_comment|/* fully-on */
DECL|enumerator|ACPI_D1
id|ACPI_D1
comma
multiline_comment|/* partial-on */
DECL|enumerator|ACPI_D2
id|ACPI_D2
comma
multiline_comment|/* partial-on */
DECL|enumerator|ACPI_D3
id|ACPI_D3
comma
multiline_comment|/* fully-off */
)brace
suffix:semicolon
DECL|typedef|acpi_dstate_t
r_typedef
r_int
id|acpi_dstate_t
suffix:semicolon
multiline_comment|/* RSDP location */
DECL|macro|ACPI_BIOS_ROM_BASE
mdefine_line|#define ACPI_BIOS_ROM_BASE (0x0e0000)
DECL|macro|ACPI_BIOS_ROM_END
mdefine_line|#define ACPI_BIOS_ROM_END  (0x100000)
multiline_comment|/* Table signatures */
DECL|macro|ACPI_RSDP1_SIG
mdefine_line|#define ACPI_RSDP1_SIG 0x20445352 /* &squot;RSD &squot; */
DECL|macro|ACPI_RSDP2_SIG
mdefine_line|#define ACPI_RSDP2_SIG 0x20525450 /* &squot;PTR &squot; */
DECL|macro|ACPI_RSDT_SIG
mdefine_line|#define ACPI_RSDT_SIG  0x54445352 /* &squot;RSDT&squot; */
DECL|macro|ACPI_FADT_SIG
mdefine_line|#define ACPI_FADT_SIG  0x50434146 /* &squot;FACP&squot; */
DECL|macro|ACPI_DSDT_SIG
mdefine_line|#define ACPI_DSDT_SIG  0x54445344 /* &squot;DSDT&squot; */
DECL|macro|ACPI_FACS_SIG
mdefine_line|#define ACPI_FACS_SIG  0x53434146 /* &squot;FACS&squot; */
DECL|macro|ACPI_SIG_LEN
mdefine_line|#define ACPI_SIG_LEN&t;&t;4
DECL|macro|ACPI_FADT_SIGNATURE
mdefine_line|#define ACPI_FADT_SIGNATURE&t;&quot;FACP&quot;
multiline_comment|/* PM1_STS/EN flags */
DECL|macro|ACPI_TMR
mdefine_line|#define ACPI_TMR    0x0001
DECL|macro|ACPI_BM
mdefine_line|#define ACPI_BM&t;    0x0010
DECL|macro|ACPI_GBL
mdefine_line|#define ACPI_GBL    0x0020
DECL|macro|ACPI_PWRBTN
mdefine_line|#define ACPI_PWRBTN 0x0100
DECL|macro|ACPI_SLPBTN
mdefine_line|#define ACPI_SLPBTN 0x0200
DECL|macro|ACPI_RTC
mdefine_line|#define ACPI_RTC    0x0400
DECL|macro|ACPI_WAK
mdefine_line|#define ACPI_WAK    0x8000
multiline_comment|/* PM1_CNT flags */
DECL|macro|ACPI_SCI_EN
mdefine_line|#define ACPI_SCI_EN   0x0001
DECL|macro|ACPI_BM_RLD
mdefine_line|#define ACPI_BM_RLD   0x0002
DECL|macro|ACPI_GBL_RLS
mdefine_line|#define ACPI_GBL_RLS  0x0004
DECL|macro|ACPI_SLP_TYP0
mdefine_line|#define ACPI_SLP_TYP0 0x0400
DECL|macro|ACPI_SLP_TYP1
mdefine_line|#define ACPI_SLP_TYP1 0x0800
DECL|macro|ACPI_SLP_TYP2
mdefine_line|#define ACPI_SLP_TYP2 0x1000
DECL|macro|ACPI_SLP_EN
mdefine_line|#define ACPI_SLP_EN   0x2000
DECL|macro|ACPI_SLP_TYP_MASK
mdefine_line|#define ACPI_SLP_TYP_MASK  0x1c00
DECL|macro|ACPI_SLP_TYP_SHIFT
mdefine_line|#define ACPI_SLP_TYP_SHIFT 10
multiline_comment|/* PM_TMR masks */
DECL|macro|ACPI_TMR_VAL_EXT
mdefine_line|#define ACPI_TMR_VAL_EXT 0x00000100
DECL|macro|ACPI_TMR_MASK
mdefine_line|#define ACPI_TMR_MASK&t; 0x00ffffff
DECL|macro|ACPI_TMR_HZ
mdefine_line|#define ACPI_TMR_HZ&t; 3579545 /* 3.58 MHz */
DECL|macro|ACPI_TMR_KHZ
mdefine_line|#define ACPI_TMR_KHZ&t; (ACPI_TMR_HZ / 1000)
DECL|macro|ACPI_MICROSEC_TO_TMR_TICKS
mdefine_line|#define ACPI_MICROSEC_TO_TMR_TICKS(val) &bslash;&n;  (((val) * (ACPI_TMR_KHZ)) / 1000)
multiline_comment|/* PM2_CNT flags */
DECL|macro|ACPI_ARB_DIS
mdefine_line|#define ACPI_ARB_DIS 0x01
multiline_comment|/* FADT flags */
DECL|macro|ACPI_WBINVD
mdefine_line|#define ACPI_WBINVD&t;  0x00000001
DECL|macro|ACPI_WBINVD_FLUSH
mdefine_line|#define ACPI_WBINVD_FLUSH 0x00000002
DECL|macro|ACPI_PROC_C1
mdefine_line|#define ACPI_PROC_C1&t;  0x00000004
DECL|macro|ACPI_P_LVL2_UP
mdefine_line|#define ACPI_P_LVL2_UP&t;  0x00000008
DECL|macro|ACPI_PWR_BUTTON
mdefine_line|#define ACPI_PWR_BUTTON&t;  0x00000010
DECL|macro|ACPI_SLP_BUTTON
mdefine_line|#define ACPI_SLP_BUTTON&t;  0x00000020
DECL|macro|ACPI_FIX_RTC
mdefine_line|#define ACPI_FIX_RTC&t;  0x00000040
DECL|macro|ACPI_RTC_64
mdefine_line|#define ACPI_RTC_64&t;  0x00000080
DECL|macro|ACPI_TMR_VAL_EXT
mdefine_line|#define ACPI_TMR_VAL_EXT  0x00000100
DECL|macro|ACPI_DCK_CAP
mdefine_line|#define ACPI_DCK_CAP&t;  0x00000200
multiline_comment|/* FADT BOOT_ARCH flags */
DECL|macro|FADT_BOOT_ARCH_LEGACY_DEVICES
mdefine_line|#define FADT_BOOT_ARCH_LEGACY_DEVICES&t;0x0001
DECL|macro|FADT_BOOT_ARCH_KBD_CONTROLLER
mdefine_line|#define FADT_BOOT_ARCH_KBD_CONTROLLER&t;0x0002
multiline_comment|/* FACS flags */
DECL|macro|ACPI_S4BIOS
mdefine_line|#define ACPI_S4BIOS&t;  0x00000001
multiline_comment|/* processor block offsets */
DECL|macro|ACPI_P_CNT
mdefine_line|#define ACPI_P_CNT&t;  0x00000000
DECL|macro|ACPI_P_LVL2
mdefine_line|#define ACPI_P_LVL2&t;  0x00000004
DECL|macro|ACPI_P_LVL3
mdefine_line|#define ACPI_P_LVL3&t;  0x00000005
multiline_comment|/* C-state latencies (microseconds) */
DECL|macro|ACPI_MAX_P_LVL2_LAT
mdefine_line|#define ACPI_MAX_P_LVL2_LAT 100
DECL|macro|ACPI_MAX_P_LVL3_LAT
mdefine_line|#define ACPI_MAX_P_LVL3_LAT 1000
DECL|macro|ACPI_INFINITE_LAT
mdefine_line|#define ACPI_INFINITE_LAT   (~0UL)
multiline_comment|/*&n; * Sysctl declarations&n; */
r_enum
(brace
DECL|enumerator|CTL_ACPI
id|CTL_ACPI
op_assign
l_int|10
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|ACPI_FADT
id|ACPI_FADT
op_assign
l_int|1
comma
DECL|enumerator|ACPI_DSDT
id|ACPI_DSDT
comma
DECL|enumerator|ACPI_PM1_ENABLE
id|ACPI_PM1_ENABLE
comma
DECL|enumerator|ACPI_GPE_ENABLE
id|ACPI_GPE_ENABLE
comma
DECL|enumerator|ACPI_GPE_LEVEL
id|ACPI_GPE_LEVEL
comma
DECL|enumerator|ACPI_EVENT
id|ACPI_EVENT
comma
DECL|enumerator|ACPI_P_BLK
id|ACPI_P_BLK
comma
DECL|enumerator|ACPI_ENTER_LVL2_LAT
id|ACPI_ENTER_LVL2_LAT
comma
DECL|enumerator|ACPI_ENTER_LVL3_LAT
id|ACPI_ENTER_LVL3_LAT
comma
DECL|enumerator|ACPI_P_LVL2_LAT
id|ACPI_P_LVL2_LAT
comma
DECL|enumerator|ACPI_P_LVL3_LAT
id|ACPI_P_LVL3_LAT
comma
DECL|enumerator|ACPI_C1_TIME
id|ACPI_C1_TIME
comma
DECL|enumerator|ACPI_C2_TIME
id|ACPI_C2_TIME
comma
DECL|enumerator|ACPI_C3_TIME
id|ACPI_C3_TIME
comma
DECL|enumerator|ACPI_C1_COUNT
id|ACPI_C1_COUNT
comma
DECL|enumerator|ACPI_C2_COUNT
id|ACPI_C2_COUNT
comma
DECL|enumerator|ACPI_C3_COUNT
id|ACPI_C3_COUNT
comma
DECL|enumerator|ACPI_S0_SLP_TYP
id|ACPI_S0_SLP_TYP
comma
DECL|enumerator|ACPI_S1_SLP_TYP
id|ACPI_S1_SLP_TYP
comma
DECL|enumerator|ACPI_S5_SLP_TYP
id|ACPI_S5_SLP_TYP
comma
DECL|enumerator|ACPI_SLEEP
id|ACPI_SLEEP
comma
DECL|enumerator|ACPI_FACS
id|ACPI_FACS
comma
DECL|enumerator|ACPI_XSDT
id|ACPI_XSDT
comma
DECL|enumerator|ACPI_PMTIMER
id|ACPI_PMTIMER
comma
DECL|enumerator|ACPI_BATT
id|ACPI_BATT
comma
)brace
suffix:semicolon
DECL|macro|ACPI_SLP_TYP_DISABLED
mdefine_line|#define ACPI_SLP_TYP_DISABLED&t;(~0UL)
macro_line|#endif /* _LINUX_ACPI_H */
eof
