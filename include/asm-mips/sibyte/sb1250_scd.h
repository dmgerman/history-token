multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  SCD Constants and Macros&t;&t;&t;File: sb1250_scd.h&n;    *  &n;    *  This module contains constants and macros useful for&n;    *  manipulating the System Control and Debug module on the 1250.&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_SCD_H
DECL|macro|_SB1250_SCD_H
mdefine_line|#define _SB1250_SCD_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*  *********************************************************************&n;    *  System control/debug registers&n;    ********************************************************************* */
multiline_comment|/*&n; * System Revision Register (Table 4-1)&n; */
DECL|macro|M_SYS_RESERVED
mdefine_line|#define M_SYS_RESERVED&t;&t;    _SB_MAKEMASK(8,0)
DECL|macro|S_SYS_REVISION
mdefine_line|#define S_SYS_REVISION              _SB_MAKE64(8)
DECL|macro|M_SYS_REVISION
mdefine_line|#define M_SYS_REVISION              _SB_MAKEMASK(8,S_SYS_REVISION)
DECL|macro|V_SYS_REVISION
mdefine_line|#define V_SYS_REVISION(x)           _SB_MAKEVALUE(x,S_SYS_REVISION)
DECL|macro|G_SYS_REVISION
mdefine_line|#define G_SYS_REVISION(x)           _SB_GETVALUE(x,S_SYS_REVISION,M_SYS_REVISION)
macro_line|#if SIBYTE_HDR_FEATURE_CHIP(1250)
DECL|macro|K_SYS_REVISION_BCM1250_PASS1
mdefine_line|#define K_SYS_REVISION_BCM1250_PASS1&t;1
DECL|macro|K_SYS_REVISION_BCM1250_PASS2
mdefine_line|#define K_SYS_REVISION_BCM1250_PASS2&t;3
DECL|macro|K_SYS_REVISION_BCM1250_A10
mdefine_line|#define K_SYS_REVISION_BCM1250_A10&t;11
DECL|macro|K_SYS_REVISION_BCM1250_PASS2_2
mdefine_line|#define K_SYS_REVISION_BCM1250_PASS2_2&t;16
DECL|macro|K_SYS_REVISION_BCM1250_B2
mdefine_line|#define K_SYS_REVISION_BCM1250_B2&t;17
DECL|macro|K_SYS_REVISION_BCM1250_PASS3
mdefine_line|#define K_SYS_REVISION_BCM1250_PASS3&t;32
DECL|macro|K_SYS_REVISION_BCM1250_C1
mdefine_line|#define K_SYS_REVISION_BCM1250_C1&t;33
multiline_comment|/* XXX: discourage people from using these constants.  */
DECL|macro|K_SYS_REVISION_PASS1
mdefine_line|#define K_SYS_REVISION_PASS1&t;    K_SYS_REVISION_BCM1250_PASS1
DECL|macro|K_SYS_REVISION_PASS2
mdefine_line|#define K_SYS_REVISION_PASS2&t;    K_SYS_REVISION_BCM1250_PASS2
DECL|macro|K_SYS_REVISION_PASS2_2
mdefine_line|#define K_SYS_REVISION_PASS2_2&t;    K_SYS_REVISION_BCM1250_PASS2_2
DECL|macro|K_SYS_REVISION_PASS3
mdefine_line|#define K_SYS_REVISION_PASS3&t;    K_SYS_REVISION_BCM1250_PASS3
macro_line|#endif /* 1250 */
macro_line|#if SIBYTE_HDR_FEATURE_CHIP(112x)
DECL|macro|K_SYS_REVISION_BCM112x_A1
mdefine_line|#define K_SYS_REVISION_BCM112x_A1&t;32
DECL|macro|K_SYS_REVISION_BCM112x_A2
mdefine_line|#define K_SYS_REVISION_BCM112x_A2&t;33
macro_line|#endif /* 112x */
multiline_comment|/* XXX: discourage people from using these constants.  */
DECL|macro|S_SYS_PART
mdefine_line|#define S_SYS_PART                  _SB_MAKE64(16)
DECL|macro|M_SYS_PART
mdefine_line|#define M_SYS_PART                  _SB_MAKEMASK(16,S_SYS_PART)
DECL|macro|V_SYS_PART
mdefine_line|#define V_SYS_PART(x)               _SB_MAKEVALUE(x,S_SYS_PART)
DECL|macro|G_SYS_PART
mdefine_line|#define G_SYS_PART(x)               _SB_GETVALUE(x,S_SYS_PART,M_SYS_PART)
multiline_comment|/* XXX: discourage people from using these constants.  */
DECL|macro|K_SYS_PART_SB1250
mdefine_line|#define K_SYS_PART_SB1250           0x1250
DECL|macro|K_SYS_PART_BCM1120
mdefine_line|#define K_SYS_PART_BCM1120          0x1121
DECL|macro|K_SYS_PART_BCM1125
mdefine_line|#define K_SYS_PART_BCM1125          0x1123
DECL|macro|K_SYS_PART_BCM1125H
mdefine_line|#define K_SYS_PART_BCM1125H         0x1124
multiline_comment|/* The &quot;peripheral set&quot; (SOC type) is the low 4 bits of the &quot;part&quot; field.  */
DECL|macro|S_SYS_SOC_TYPE
mdefine_line|#define S_SYS_SOC_TYPE              _SB_MAKE64(16)
DECL|macro|M_SYS_SOC_TYPE
mdefine_line|#define M_SYS_SOC_TYPE              _SB_MAKEMASK(4,S_SYS_SOC_TYPE)
DECL|macro|V_SYS_SOC_TYPE
mdefine_line|#define V_SYS_SOC_TYPE(x)           _SB_MAKEVALUE(x,S_SYS_SOC_TYPE)
DECL|macro|G_SYS_SOC_TYPE
mdefine_line|#define G_SYS_SOC_TYPE(x)           _SB_GETVALUE(x,S_SYS_SOC_TYPE,M_SYS_SOC_TYPE)
DECL|macro|K_SYS_SOC_TYPE_BCM1250
mdefine_line|#define K_SYS_SOC_TYPE_BCM1250      0x0
DECL|macro|K_SYS_SOC_TYPE_BCM1120
mdefine_line|#define K_SYS_SOC_TYPE_BCM1120      0x1
DECL|macro|K_SYS_SOC_TYPE_BCM1250_ALT
mdefine_line|#define K_SYS_SOC_TYPE_BCM1250_ALT  0x2&t;&t;/* 1250pass2 w/ 1/4 L2.  */
DECL|macro|K_SYS_SOC_TYPE_BCM1125
mdefine_line|#define K_SYS_SOC_TYPE_BCM1125      0x3
DECL|macro|K_SYS_SOC_TYPE_BCM1125H
mdefine_line|#define K_SYS_SOC_TYPE_BCM1125H     0x4
DECL|macro|K_SYS_SOC_TYPE_BCM1250_ALT2
mdefine_line|#define K_SYS_SOC_TYPE_BCM1250_ALT2 0x5&t;&t;/* 1250pass2 w/ 1/2 L2.  */
multiline_comment|/*&n; * Calculate correct SOC type given a copy of system revision register.&n; *&n; * (For the assembler version, sysrev and dest may be the same register.&n; * Also, it clobbers AT.)&n; */
macro_line|#ifdef __ASSEMBLER__
DECL|macro|SYS_SOC_TYPE
mdefine_line|#define SYS_SOC_TYPE(dest, sysrev)&t;&t;&t;&t;&t;&bslash;&n;&t;.set push ;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set reorder ;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dsrl&t;dest, sysrev, S_SYS_SOC_TYPE ;&t;&t;&t;&t;&bslash;&n;&t;andi&t;dest, dest, (M_SYS_SOC_TYPE &gt;&gt; S_SYS_SOC_TYPE);&t;&t;&bslash;&n;&t;beq&t;dest, K_SYS_SOC_TYPE_BCM1250_ALT, 991f ;&t;&t;&bslash;&n;&t;beq&t;dest, K_SYS_SOC_TYPE_BCM1250_ALT2, 991f&t; ;&t;&t;&bslash;&n;&t;b&t;992f ;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;991:&t;li&t;dest, K_SYS_SOC_TYPE_BCM1250 ;&t;&t;&t;&t;&bslash;&n;992:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.set pop
macro_line|#else
DECL|macro|SYS_SOC_TYPE
mdefine_line|#define SYS_SOC_TYPE(sysrev)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((G_SYS_SOC_TYPE(sysrev) == K_SYS_SOC_TYPE_BCM1250_ALT&t;&t;&bslash;&n;&t;  || G_SYS_SOC_TYPE(sysrev) == K_SYS_SOC_TYPE_BCM1250_ALT2)&t;&bslash;&n;&t; ? K_SYS_SOC_TYPE_BCM1250 : G_SYS_SOC_TYPE(sysrev))
macro_line|#endif
DECL|macro|S_SYS_WID
mdefine_line|#define S_SYS_WID                   _SB_MAKE64(32)
DECL|macro|M_SYS_WID
mdefine_line|#define M_SYS_WID                   _SB_MAKEMASK(32,S_SYS_WID)
DECL|macro|V_SYS_WID
mdefine_line|#define V_SYS_WID(x)                _SB_MAKEVALUE(x,S_SYS_WID)
DECL|macro|G_SYS_WID
mdefine_line|#define G_SYS_WID(x)                _SB_GETVALUE(x,S_SYS_WID,M_SYS_WID)
multiline_comment|/* System Manufacturing Register&n;* Register: SCD_SYSTEM_MANUF&n;*/
multiline_comment|/* Wafer ID: bits 31:0 */
DECL|macro|S_SYS_WAFERID1_200
mdefine_line|#define S_SYS_WAFERID1_200        _SB_MAKE64(0)
DECL|macro|M_SYS_WAFERID1_200
mdefine_line|#define M_SYS_WAFERID1_200        _SB_MAKEMASK(32,S_SYS_WAFERID1_200)
DECL|macro|V_SYS_WAFERID1_200
mdefine_line|#define V_SYS_WAFERID1_200(x)     _SB_MAKEVALUE(x,S_SYS_WAFERID1_200)
DECL|macro|G_SYS_WAFERID1_200
mdefine_line|#define G_SYS_WAFERID1_200(x)     _SB_GETVALUE(x,S_SYS_WAFERID1_200,M_SYS_WAFERID1_200)
DECL|macro|S_SYS_BIN
mdefine_line|#define S_SYS_BIN                 _SB_MAKE64(32)
DECL|macro|M_SYS_BIN
mdefine_line|#define M_SYS_BIN                 _SB_MAKEMASK(4,S_SYS_BIN)
DECL|macro|V_SYS_BIN
mdefine_line|#define V_SYS_BIN                 _SB_MAKEVALUE(x,S_SYS_BIN)
DECL|macro|G_SYS_BIN
mdefine_line|#define G_SYS_BIN                 _SB_GETVALUE(x,S_SYS_BIN,M_SYS_BIN)
multiline_comment|/* Wafer ID: bits 39:36 */
DECL|macro|S_SYS_WAFERID2_200
mdefine_line|#define S_SYS_WAFERID2_200        _SB_MAKE64(36)
DECL|macro|M_SYS_WAFERID2_200
mdefine_line|#define M_SYS_WAFERID2_200        _SB_MAKEMASK(4,S_SYS_WAFERID2_200)
DECL|macro|V_SYS_WAFERID2_200
mdefine_line|#define V_SYS_WAFERID2_200(x)     _SB_MAKEVALUE(x,S_SYS_WAFERID2_200)
DECL|macro|G_SYS_WAFERID2_200
mdefine_line|#define G_SYS_WAFERID2_200(x)     _SB_GETVALUE(x,S_SYS_WAFERID2_200,M_SYS_WAFERID2_200)
multiline_comment|/* Wafer ID: bits 39:0 */
DECL|macro|S_SYS_WAFERID_300
mdefine_line|#define S_SYS_WAFERID_300         _SB_MAKE64(0)
DECL|macro|M_SYS_WAFERID_300
mdefine_line|#define M_SYS_WAFERID_300         _SB_MAKEMASK(40,S_SYS_WAFERID_300)
DECL|macro|V_SYS_WAFERID_300
mdefine_line|#define V_SYS_WAFERID_300(x)      _SB_MAKEVALUE(x,S_SYS_WAFERID_300)
DECL|macro|G_SYS_WAFERID_300
mdefine_line|#define G_SYS_WAFERID_300(x)      _SB_GETVALUE(x,S_SYS_WAFERID_300,M_SYS_WAFERID_300)
DECL|macro|S_SYS_XPOS
mdefine_line|#define S_SYS_XPOS                _SB_MAKE64(40)
DECL|macro|M_SYS_XPOS
mdefine_line|#define M_SYS_XPOS                _SB_MAKEMASK(6,S_SYS_XPOS)
DECL|macro|V_SYS_XPOS
mdefine_line|#define V_SYS_XPOS(x)             _SB_MAKEVALUE(x,S_SYS_XPOS)
DECL|macro|G_SYS_XPOS
mdefine_line|#define G_SYS_XPOS(x)             _SB_GETVALUE(x,S_SYS_XPOS,M_SYS_XPOS)
DECL|macro|S_SYS_YPOS
mdefine_line|#define S_SYS_YPOS                _SB_MAKE64(46)
DECL|macro|M_SYS_YPOS
mdefine_line|#define M_SYS_YPOS                _SB_MAKEMASK(6,S_SYS_YPOS)
DECL|macro|V_SYS_YPOS
mdefine_line|#define V_SYS_YPOS(x)             _SB_MAKEVALUE(x,S_SYS_YPOS)
DECL|macro|G_SYS_YPOS
mdefine_line|#define G_SYS_YPOS(x)             _SB_GETVALUE(x,S_SYS_YPOS,M_SYS_YPOS)
multiline_comment|/*&n; * System Config Register (Table 4-2)&n; * Register: SCD_SYSTEM_CFG&n; */
DECL|macro|M_SYS_LDT_PLL_BYP
mdefine_line|#define M_SYS_LDT_PLL_BYP           _SB_MAKEMASK1(3)
DECL|macro|M_SYS_PCI_SYNC_TEST_MODE
mdefine_line|#define M_SYS_PCI_SYNC_TEST_MODE    _SB_MAKEMASK1(4)
DECL|macro|M_SYS_IOB0_DIV
mdefine_line|#define M_SYS_IOB0_DIV              _SB_MAKEMASK1(5)
DECL|macro|M_SYS_IOB1_DIV
mdefine_line|#define M_SYS_IOB1_DIV              _SB_MAKEMASK1(6)
DECL|macro|S_SYS_PLL_DIV
mdefine_line|#define S_SYS_PLL_DIV               _SB_MAKE64(7)
DECL|macro|M_SYS_PLL_DIV
mdefine_line|#define M_SYS_PLL_DIV               _SB_MAKEMASK(5,S_SYS_PLL_DIV)
DECL|macro|V_SYS_PLL_DIV
mdefine_line|#define V_SYS_PLL_DIV(x)            _SB_MAKEVALUE(x,S_SYS_PLL_DIV)
DECL|macro|G_SYS_PLL_DIV
mdefine_line|#define G_SYS_PLL_DIV(x)            _SB_GETVALUE(x,S_SYS_PLL_DIV,M_SYS_PLL_DIV)
DECL|macro|M_SYS_SER0_ENABLE
mdefine_line|#define M_SYS_SER0_ENABLE           _SB_MAKEMASK1(12)
DECL|macro|M_SYS_SER0_RSTB_EN
mdefine_line|#define M_SYS_SER0_RSTB_EN          _SB_MAKEMASK1(13)
DECL|macro|M_SYS_SER1_ENABLE
mdefine_line|#define M_SYS_SER1_ENABLE           _SB_MAKEMASK1(14)
DECL|macro|M_SYS_SER1_RSTB_EN
mdefine_line|#define M_SYS_SER1_RSTB_EN          _SB_MAKEMASK1(15)
DECL|macro|M_SYS_PCMCIA_ENABLE
mdefine_line|#define M_SYS_PCMCIA_ENABLE         _SB_MAKEMASK1(16)
DECL|macro|S_SYS_BOOT_MODE
mdefine_line|#define S_SYS_BOOT_MODE             _SB_MAKE64(17)
DECL|macro|M_SYS_BOOT_MODE
mdefine_line|#define M_SYS_BOOT_MODE             _SB_MAKEMASK(2,S_SYS_BOOT_MODE)
DECL|macro|V_SYS_BOOT_MODE
mdefine_line|#define V_SYS_BOOT_MODE(x)          _SB_MAKEVALUE(x,S_SYS_BOOT_MODE)
DECL|macro|G_SYS_BOOT_MODE
mdefine_line|#define G_SYS_BOOT_MODE(x)          _SB_GETVALUE(x,S_SYS_BOOT_MODE,M_SYS_BOOT_MODE)
DECL|macro|K_SYS_BOOT_MODE_ROM32
mdefine_line|#define K_SYS_BOOT_MODE_ROM32       0
DECL|macro|K_SYS_BOOT_MODE_ROM8
mdefine_line|#define K_SYS_BOOT_MODE_ROM8        1
DECL|macro|K_SYS_BOOT_MODE_SMBUS_SMALL
mdefine_line|#define K_SYS_BOOT_MODE_SMBUS_SMALL 2
DECL|macro|K_SYS_BOOT_MODE_SMBUS_BIG
mdefine_line|#define K_SYS_BOOT_MODE_SMBUS_BIG   3
DECL|macro|M_SYS_PCI_HOST
mdefine_line|#define M_SYS_PCI_HOST              _SB_MAKEMASK1(19)
DECL|macro|M_SYS_PCI_ARBITER
mdefine_line|#define M_SYS_PCI_ARBITER           _SB_MAKEMASK1(20)
DECL|macro|M_SYS_SOUTH_ON_LDT
mdefine_line|#define M_SYS_SOUTH_ON_LDT          _SB_MAKEMASK1(21)
DECL|macro|M_SYS_BIG_ENDIAN
mdefine_line|#define M_SYS_BIG_ENDIAN            _SB_MAKEMASK1(22)
DECL|macro|M_SYS_GENCLK_EN
mdefine_line|#define M_SYS_GENCLK_EN             _SB_MAKEMASK1(23)
DECL|macro|M_SYS_LDT_TEST_EN
mdefine_line|#define M_SYS_LDT_TEST_EN           _SB_MAKEMASK1(24)
DECL|macro|M_SYS_GEN_PARITY_EN
mdefine_line|#define M_SYS_GEN_PARITY_EN         _SB_MAKEMASK1(25)
DECL|macro|S_SYS_CONFIG
mdefine_line|#define S_SYS_CONFIG                26
DECL|macro|M_SYS_CONFIG
mdefine_line|#define M_SYS_CONFIG                _SB_MAKEMASK(6,S_SYS_CONFIG)
DECL|macro|V_SYS_CONFIG
mdefine_line|#define V_SYS_CONFIG(x)             _SB_MAKEVALUE(x,S_SYS_CONFIG)
DECL|macro|G_SYS_CONFIG
mdefine_line|#define G_SYS_CONFIG(x)             _SB_GETVALUE(x,S_SYS_CONFIG,M_SYS_CONFIG)
multiline_comment|/* The following bits are writeable by JTAG only. */
DECL|macro|M_SYS_CLKSTOP
mdefine_line|#define M_SYS_CLKSTOP               _SB_MAKEMASK1(32)
DECL|macro|M_SYS_CLKSTEP
mdefine_line|#define M_SYS_CLKSTEP               _SB_MAKEMASK1(33)
DECL|macro|S_SYS_CLKCOUNT
mdefine_line|#define S_SYS_CLKCOUNT              34
DECL|macro|M_SYS_CLKCOUNT
mdefine_line|#define M_SYS_CLKCOUNT              _SB_MAKEMASK(8,S_SYS_CLKCOUNT)
DECL|macro|V_SYS_CLKCOUNT
mdefine_line|#define V_SYS_CLKCOUNT(x)           _SB_MAKEVALUE(x,S_SYS_CLKCOUNT)
DECL|macro|G_SYS_CLKCOUNT
mdefine_line|#define G_SYS_CLKCOUNT(x)           _SB_GETVALUE(x,S_SYS_CLKCOUNT,M_SYS_CLKCOUNT)
DECL|macro|M_SYS_PLL_BYPASS
mdefine_line|#define M_SYS_PLL_BYPASS            _SB_MAKEMASK1(42)
DECL|macro|S_SYS_PLL_IREF
mdefine_line|#define S_SYS_PLL_IREF&t;&t;    43
DECL|macro|M_SYS_PLL_IREF
mdefine_line|#define M_SYS_PLL_IREF&t;&t;    _SB_MAKEMASK(2,S_SYS_PLL_IREF)
DECL|macro|S_SYS_PLL_VCO
mdefine_line|#define S_SYS_PLL_VCO&t;&t;    45
DECL|macro|M_SYS_PLL_VCO
mdefine_line|#define M_SYS_PLL_VCO&t;&t;    _SB_MAKEMASK(2,S_SYS_PLL_VCO)
DECL|macro|S_SYS_PLL_VREG
mdefine_line|#define S_SYS_PLL_VREG&t;&t;    47
DECL|macro|M_SYS_PLL_VREG
mdefine_line|#define M_SYS_PLL_VREG&t;&t;    _SB_MAKEMASK(2,S_SYS_PLL_VREG)
DECL|macro|M_SYS_MEM_RESET
mdefine_line|#define M_SYS_MEM_RESET             _SB_MAKEMASK1(49)
DECL|macro|M_SYS_L2C_RESET
mdefine_line|#define M_SYS_L2C_RESET             _SB_MAKEMASK1(50)
DECL|macro|M_SYS_IO_RESET_0
mdefine_line|#define M_SYS_IO_RESET_0            _SB_MAKEMASK1(51)
DECL|macro|M_SYS_IO_RESET_1
mdefine_line|#define M_SYS_IO_RESET_1            _SB_MAKEMASK1(52)
DECL|macro|M_SYS_SCD_RESET
mdefine_line|#define M_SYS_SCD_RESET             _SB_MAKEMASK1(53)
multiline_comment|/* End of bits writable by JTAG only. */
DECL|macro|M_SYS_CPU_RESET_0
mdefine_line|#define M_SYS_CPU_RESET_0           _SB_MAKEMASK1(54)
DECL|macro|M_SYS_CPU_RESET_1
mdefine_line|#define M_SYS_CPU_RESET_1           _SB_MAKEMASK1(55)
DECL|macro|M_SYS_UNICPU0
mdefine_line|#define M_SYS_UNICPU0               _SB_MAKEMASK1(56)
DECL|macro|M_SYS_UNICPU1
mdefine_line|#define M_SYS_UNICPU1               _SB_MAKEMASK1(57)
DECL|macro|M_SYS_SB_SOFTRES
mdefine_line|#define M_SYS_SB_SOFTRES            _SB_MAKEMASK1(58)
DECL|macro|M_SYS_EXT_RESET
mdefine_line|#define M_SYS_EXT_RESET             _SB_MAKEMASK1(59)
DECL|macro|M_SYS_SYSTEM_RESET
mdefine_line|#define M_SYS_SYSTEM_RESET          _SB_MAKEMASK1(60)
DECL|macro|M_SYS_MISR_MODE
mdefine_line|#define M_SYS_MISR_MODE             _SB_MAKEMASK1(61)
DECL|macro|M_SYS_MISR_RESET
mdefine_line|#define M_SYS_MISR_RESET            _SB_MAKEMASK1(62)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_SYS_SW_FLAG
mdefine_line|#define M_SYS_SW_FLAG&t;&t;    _SB_MAKEMASK1(63)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*&n; * Mailbox Registers (Table 4-3)&n; * Registers: SCD_MBOX_CPU_x&n; */
DECL|macro|S_MBOX_INT_3
mdefine_line|#define S_MBOX_INT_3                0
DECL|macro|M_MBOX_INT_3
mdefine_line|#define M_MBOX_INT_3                _SB_MAKEMASK(16,S_MBOX_INT_3)
DECL|macro|S_MBOX_INT_2
mdefine_line|#define S_MBOX_INT_2                16
DECL|macro|M_MBOX_INT_2
mdefine_line|#define M_MBOX_INT_2                _SB_MAKEMASK(16,S_MBOX_INT_2)
DECL|macro|S_MBOX_INT_1
mdefine_line|#define S_MBOX_INT_1                32
DECL|macro|M_MBOX_INT_1
mdefine_line|#define M_MBOX_INT_1                _SB_MAKEMASK(16,S_MBOX_INT_1)
DECL|macro|S_MBOX_INT_0
mdefine_line|#define S_MBOX_INT_0                48
DECL|macro|M_MBOX_INT_0
mdefine_line|#define M_MBOX_INT_0                _SB_MAKEMASK(16,S_MBOX_INT_0)
multiline_comment|/*&n; * Watchdog Registers (Table 4-8) (Table 4-9) (Table 4-10)&n; * Registers: SCD_WDOG_INIT_CNT_x&n; */
DECL|macro|V_SCD_WDOG_FREQ
mdefine_line|#define V_SCD_WDOG_FREQ             1000000
DECL|macro|S_SCD_WDOG_INIT
mdefine_line|#define S_SCD_WDOG_INIT             0
DECL|macro|M_SCD_WDOG_INIT
mdefine_line|#define M_SCD_WDOG_INIT             _SB_MAKEMASK(23,S_SCD_WDOG_INIT)
DECL|macro|S_SCD_WDOG_CNT
mdefine_line|#define S_SCD_WDOG_CNT              0
DECL|macro|M_SCD_WDOG_CNT
mdefine_line|#define M_SCD_WDOG_CNT              _SB_MAKEMASK(23,S_SCD_WDOG_CNT)
DECL|macro|S_SCD_WDOG_ENABLE
mdefine_line|#define S_SCD_WDOG_ENABLE           0
DECL|macro|M_SCD_WDOG_ENABLE
mdefine_line|#define M_SCD_WDOG_ENABLE           _SB_MAKEMASK1(S_SCD_WDOG_ENABLE)
DECL|macro|S_SCD_WDOG_RESET_TYPE
mdefine_line|#define S_SCD_WDOG_RESET_TYPE       2
DECL|macro|M_SCD_WDOG_RESET_TYPE
mdefine_line|#define M_SCD_WDOG_RESET_TYPE       _SB_MAKEMASK(3,S_SCD_WDOG_RESET_TYPE)
DECL|macro|V_SCD_WDOG_RESET_TYPE
mdefine_line|#define V_SCD_WDOG_RESET_TYPE(x)    _SB_MAKEVALUE(x,S_SCD_WDOG_RESET_TYPE)
DECL|macro|G_SCD_WDOG_RESET_TYPE
mdefine_line|#define G_SCD_WDOG_RESET_TYPE(x)    _SB_GETVALUE(x,S_SCD_WDOG_RESET_TYPE,M_SCD_WDOG_RESET_TYPE)
DECL|macro|K_SCD_WDOG_RESET_FULL
mdefine_line|#define K_SCD_WDOG_RESET_FULL       0&t;/* actually, (x &amp; 1) == 0  */
DECL|macro|K_SCD_WDOG_RESET_SOFT
mdefine_line|#define K_SCD_WDOG_RESET_SOFT       1
DECL|macro|K_SCD_WDOG_RESET_CPU0
mdefine_line|#define K_SCD_WDOG_RESET_CPU0       3
DECL|macro|K_SCD_WDOG_RESET_CPU1
mdefine_line|#define K_SCD_WDOG_RESET_CPU1       5
DECL|macro|K_SCD_WDOG_RESET_BOTH_CPUS
mdefine_line|#define K_SCD_WDOG_RESET_BOTH_CPUS  7
multiline_comment|/* This feature is present in 1250 C0 and later, but *not* in 112x A revs.  */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3)
DECL|macro|S_SCD_WDOG_HAS_RESET
mdefine_line|#define S_SCD_WDOG_HAS_RESET        8
DECL|macro|M_SCD_WDOG_HAS_RESET
mdefine_line|#define M_SCD_WDOG_HAS_RESET        _SB_MAKEMASK1(S_SCD_WDOG_HAS_RESET)
macro_line|#endif
multiline_comment|/*&n; * Timer Registers (Table 4-11) (Table 4-12) (Table 4-13)&n; */
DECL|macro|V_SCD_TIMER_FREQ
mdefine_line|#define V_SCD_TIMER_FREQ            1000000
DECL|macro|S_SCD_TIMER_INIT
mdefine_line|#define S_SCD_TIMER_INIT            0
DECL|macro|M_SCD_TIMER_INIT
mdefine_line|#define M_SCD_TIMER_INIT            _SB_MAKEMASK(20,S_SCD_TIMER_INIT)
DECL|macro|V_SCD_TIMER_INIT
mdefine_line|#define V_SCD_TIMER_INIT(x)         _SB_MAKEVALUE(x,S_SCD_TIMER_INIT)
DECL|macro|G_SCD_TIMER_INIT
mdefine_line|#define G_SCD_TIMER_INIT(x)         _SB_GETVALUE(x,S_SCD_TIMER_INIT,M_SCD_TIMER_INIT)
DECL|macro|S_SCD_TIMER_CNT
mdefine_line|#define S_SCD_TIMER_CNT             0
DECL|macro|M_SCD_TIMER_CNT
mdefine_line|#define M_SCD_TIMER_CNT             _SB_MAKEMASK(20,S_SCD_TIMER_CNT)
DECL|macro|V_SCD_TIMER_CNT
mdefine_line|#define V_SCD_TIMER_CNT(x)         _SB_MAKEVALUE(x,S_SCD_TIMER_CNT)
DECL|macro|G_SCD_TIMER_CNT
mdefine_line|#define G_SCD_TIMER_CNT(x)         _SB_GETVALUE(x,S_SCD_TIMER_CNT,M_SCD_TIMER_CNT)
DECL|macro|M_SCD_TIMER_ENABLE
mdefine_line|#define M_SCD_TIMER_ENABLE          _SB_MAKEMASK1(0)
DECL|macro|M_SCD_TIMER_MODE
mdefine_line|#define M_SCD_TIMER_MODE            _SB_MAKEMASK1(1)
DECL|macro|M_SCD_TIMER_MODE_CONTINUOUS
mdefine_line|#define M_SCD_TIMER_MODE_CONTINUOUS M_SCD_TIMER_MODE
multiline_comment|/*&n; * System Performance Counters&n; */
DECL|macro|S_SPC_CFG_SRC0
mdefine_line|#define S_SPC_CFG_SRC0            0
DECL|macro|M_SPC_CFG_SRC0
mdefine_line|#define M_SPC_CFG_SRC0            _SB_MAKEMASK(8,S_SPC_CFG_SRC0)
DECL|macro|V_SPC_CFG_SRC0
mdefine_line|#define V_SPC_CFG_SRC0(x)         _SB_MAKEVALUE(x,S_SPC_CFG_SRC0)
DECL|macro|G_SPC_CFG_SRC0
mdefine_line|#define G_SPC_CFG_SRC0(x)         _SB_GETVALUE(x,S_SPC_CFG_SRC0,M_SPC_CFG_SRC0)
DECL|macro|S_SPC_CFG_SRC1
mdefine_line|#define S_SPC_CFG_SRC1            8
DECL|macro|M_SPC_CFG_SRC1
mdefine_line|#define M_SPC_CFG_SRC1            _SB_MAKEMASK(8,S_SPC_CFG_SRC1)
DECL|macro|V_SPC_CFG_SRC1
mdefine_line|#define V_SPC_CFG_SRC1(x)         _SB_MAKEVALUE(x,S_SPC_CFG_SRC1)
DECL|macro|G_SPC_CFG_SRC1
mdefine_line|#define G_SPC_CFG_SRC1(x)         _SB_GETVALUE(x,S_SPC_CFG_SRC1,M_SPC_CFG_SRC1)
DECL|macro|S_SPC_CFG_SRC2
mdefine_line|#define S_SPC_CFG_SRC2            16
DECL|macro|M_SPC_CFG_SRC2
mdefine_line|#define M_SPC_CFG_SRC2            _SB_MAKEMASK(8,S_SPC_CFG_SRC2)
DECL|macro|V_SPC_CFG_SRC2
mdefine_line|#define V_SPC_CFG_SRC2(x)         _SB_MAKEVALUE(x,S_SPC_CFG_SRC2)
DECL|macro|G_SPC_CFG_SRC2
mdefine_line|#define G_SPC_CFG_SRC2(x)         _SB_GETVALUE(x,S_SPC_CFG_SRC2,M_SPC_CFG_SRC2)
DECL|macro|S_SPC_CFG_SRC3
mdefine_line|#define S_SPC_CFG_SRC3            24
DECL|macro|M_SPC_CFG_SRC3
mdefine_line|#define M_SPC_CFG_SRC3            _SB_MAKEMASK(8,S_SPC_CFG_SRC3)
DECL|macro|V_SPC_CFG_SRC3
mdefine_line|#define V_SPC_CFG_SRC3(x)         _SB_MAKEVALUE(x,S_SPC_CFG_SRC3)
DECL|macro|G_SPC_CFG_SRC3
mdefine_line|#define G_SPC_CFG_SRC3(x)         _SB_GETVALUE(x,S_SPC_CFG_SRC3,M_SPC_CFG_SRC3)
DECL|macro|M_SPC_CFG_CLEAR
mdefine_line|#define M_SPC_CFG_CLEAR&t;&t;_SB_MAKEMASK1(32)
DECL|macro|M_SPC_CFG_ENABLE
mdefine_line|#define M_SPC_CFG_ENABLE&t;_SB_MAKEMASK1(33)
multiline_comment|/*&n; * Bus Watcher&n; */
DECL|macro|S_SCD_BERR_TID
mdefine_line|#define S_SCD_BERR_TID            8
DECL|macro|M_SCD_BERR_TID
mdefine_line|#define M_SCD_BERR_TID            _SB_MAKEMASK(10,S_SCD_BERR_TID)
DECL|macro|V_SCD_BERR_TID
mdefine_line|#define V_SCD_BERR_TID(x)         _SB_MAKEVALUE(x,S_SCD_BERR_TID)
DECL|macro|G_SCD_BERR_TID
mdefine_line|#define G_SCD_BERR_TID(x)         _SB_GETVALUE(x,S_SCD_BERR_TID,M_SCD_BERR_TID)
DECL|macro|S_SCD_BERR_RID
mdefine_line|#define S_SCD_BERR_RID            18
DECL|macro|M_SCD_BERR_RID
mdefine_line|#define M_SCD_BERR_RID            _SB_MAKEMASK(4,S_SCD_BERR_RID)
DECL|macro|V_SCD_BERR_RID
mdefine_line|#define V_SCD_BERR_RID(x)         _SB_MAKEVALUE(x,S_SCD_BERR_RID)
DECL|macro|G_SCD_BERR_RID
mdefine_line|#define G_SCD_BERR_RID(x)         _SB_GETVALUE(x,S_SCD_BERR_RID,M_SCD_BERR_RID)
DECL|macro|S_SCD_BERR_DCODE
mdefine_line|#define S_SCD_BERR_DCODE          22
DECL|macro|M_SCD_BERR_DCODE
mdefine_line|#define M_SCD_BERR_DCODE          _SB_MAKEMASK(3,S_SCD_BERR_DCODE)
DECL|macro|V_SCD_BERR_DCODE
mdefine_line|#define V_SCD_BERR_DCODE(x)       _SB_MAKEVALUE(x,S_SCD_BERR_DCODE)
DECL|macro|G_SCD_BERR_DCODE
mdefine_line|#define G_SCD_BERR_DCODE(x)       _SB_GETVALUE(x,S_SCD_BERR_DCODE,M_SCD_BERR_DCODE)
DECL|macro|M_SCD_BERR_MULTERRS
mdefine_line|#define M_SCD_BERR_MULTERRS       _SB_MAKEMASK1(30)
DECL|macro|S_SCD_L2ECC_CORR_D
mdefine_line|#define S_SCD_L2ECC_CORR_D        0
DECL|macro|M_SCD_L2ECC_CORR_D
mdefine_line|#define M_SCD_L2ECC_CORR_D        _SB_MAKEMASK(8,S_SCD_L2ECC_CORR_D)
DECL|macro|V_SCD_L2ECC_CORR_D
mdefine_line|#define V_SCD_L2ECC_CORR_D(x)     _SB_MAKEVALUE(x,S_SCD_L2ECC_CORR_D)
DECL|macro|G_SCD_L2ECC_CORR_D
mdefine_line|#define G_SCD_L2ECC_CORR_D(x)     _SB_GETVALUE(x,S_SCD_L2ECC_CORR_D,M_SCD_L2ECC_CORR_D)
DECL|macro|S_SCD_L2ECC_BAD_D
mdefine_line|#define S_SCD_L2ECC_BAD_D         8
DECL|macro|M_SCD_L2ECC_BAD_D
mdefine_line|#define M_SCD_L2ECC_BAD_D         _SB_MAKEMASK(8,S_SCD_L2ECC_BAD_D)
DECL|macro|V_SCD_L2ECC_BAD_D
mdefine_line|#define V_SCD_L2ECC_BAD_D(x)      _SB_MAKEVALUE(x,S_SCD_L2ECC_BAD_D)
DECL|macro|G_SCD_L2ECC_BAD_D
mdefine_line|#define G_SCD_L2ECC_BAD_D(x)      _SB_GETVALUE(x,S_SCD_L2ECC_BAD_D,M_SCD_L2ECC_BAD_D)
DECL|macro|S_SCD_L2ECC_CORR_T
mdefine_line|#define S_SCD_L2ECC_CORR_T        16
DECL|macro|M_SCD_L2ECC_CORR_T
mdefine_line|#define M_SCD_L2ECC_CORR_T        _SB_MAKEMASK(8,S_SCD_L2ECC_CORR_T)
DECL|macro|V_SCD_L2ECC_CORR_T
mdefine_line|#define V_SCD_L2ECC_CORR_T(x)     _SB_MAKEVALUE(x,S_SCD_L2ECC_CORR_T)
DECL|macro|G_SCD_L2ECC_CORR_T
mdefine_line|#define G_SCD_L2ECC_CORR_T(x)     _SB_GETVALUE(x,S_SCD_L2ECC_CORR_T,M_SCD_L2ECC_CORR_T)
DECL|macro|S_SCD_L2ECC_BAD_T
mdefine_line|#define S_SCD_L2ECC_BAD_T         24
DECL|macro|M_SCD_L2ECC_BAD_T
mdefine_line|#define M_SCD_L2ECC_BAD_T         _SB_MAKEMASK(8,S_SCD_L2ECC_BAD_T)
DECL|macro|V_SCD_L2ECC_BAD_T
mdefine_line|#define V_SCD_L2ECC_BAD_T(x)      _SB_MAKEVALUE(x,S_SCD_L2ECC_BAD_T)
DECL|macro|G_SCD_L2ECC_BAD_T
mdefine_line|#define G_SCD_L2ECC_BAD_T(x)      _SB_GETVALUE(x,S_SCD_L2ECC_BAD_T,M_SCD_L2ECC_BAD_T)
DECL|macro|S_SCD_MEM_ECC_CORR
mdefine_line|#define S_SCD_MEM_ECC_CORR        0
DECL|macro|M_SCD_MEM_ECC_CORR
mdefine_line|#define M_SCD_MEM_ECC_CORR        _SB_MAKEMASK(8,S_SCD_MEM_ECC_CORR)
DECL|macro|V_SCD_MEM_ECC_CORR
mdefine_line|#define V_SCD_MEM_ECC_CORR(x)     _SB_MAKEVALUE(x,S_SCD_MEM_ECC_CORR)
DECL|macro|G_SCD_MEM_ECC_CORR
mdefine_line|#define G_SCD_MEM_ECC_CORR(x)     _SB_GETVALUE(x,S_SCD_MEM_ECC_CORR,M_SCD_MEM_ECC_CORR)
DECL|macro|S_SCD_MEM_ECC_BAD
mdefine_line|#define S_SCD_MEM_ECC_BAD         8
DECL|macro|M_SCD_MEM_ECC_BAD
mdefine_line|#define M_SCD_MEM_ECC_BAD         _SB_MAKEMASK(8,S_SCD_MEM_ECC_BAD)
DECL|macro|V_SCD_MEM_ECC_BAD
mdefine_line|#define V_SCD_MEM_ECC_BAD(x)      _SB_MAKEVALUE(x,S_SCD_MEM_ECC_BAD)
DECL|macro|G_SCD_MEM_ECC_BAD
mdefine_line|#define G_SCD_MEM_ECC_BAD(x)      _SB_GETVALUE(x,S_SCD_MEM_ECC_BAD,M_SCD_MEM_ECC_BAD)
DECL|macro|S_SCD_MEM_BUSERR
mdefine_line|#define S_SCD_MEM_BUSERR          16
DECL|macro|M_SCD_MEM_BUSERR
mdefine_line|#define M_SCD_MEM_BUSERR          _SB_MAKEMASK(8,S_SCD_MEM_BUSERR)
DECL|macro|V_SCD_MEM_BUSERR
mdefine_line|#define V_SCD_MEM_BUSERR(x)       _SB_MAKEVALUE(x,S_SCD_MEM_BUSERR)
DECL|macro|G_SCD_MEM_BUSERR
mdefine_line|#define G_SCD_MEM_BUSERR(x)       _SB_GETVALUE(x,S_SCD_MEM_BUSERR,M_SCD_MEM_BUSERR)
multiline_comment|/*&n; * Address Trap Registers&n; */
DECL|macro|M_ATRAP_INDEX
mdefine_line|#define M_ATRAP_INDEX&t;&t;  _SB_MAKEMASK(4,0)
DECL|macro|M_ATRAP_ADDRESS
mdefine_line|#define M_ATRAP_ADDRESS&t;&t;  _SB_MAKEMASK(40,0)
DECL|macro|S_ATRAP_CFG_CNT
mdefine_line|#define S_ATRAP_CFG_CNT            0
DECL|macro|M_ATRAP_CFG_CNT
mdefine_line|#define M_ATRAP_CFG_CNT            _SB_MAKEMASK(3,S_ATRAP_CFG_CNT)
DECL|macro|V_ATRAP_CFG_CNT
mdefine_line|#define V_ATRAP_CFG_CNT(x)         _SB_MAKEVALUE(x,S_ATRAP_CFG_CNT)
DECL|macro|G_ATRAP_CFG_CNT
mdefine_line|#define G_ATRAP_CFG_CNT(x)         _SB_GETVALUE(x,S_ATRAP_CFG_CNT,M_ATRAP_CFG_CNT)
DECL|macro|M_ATRAP_CFG_WRITE
mdefine_line|#define M_ATRAP_CFG_WRITE&t;   _SB_MAKEMASK1(3)
DECL|macro|M_ATRAP_CFG_ALL
mdefine_line|#define M_ATRAP_CFG_ALL&t;  &t;   _SB_MAKEMASK1(4)
DECL|macro|M_ATRAP_CFG_INV
mdefine_line|#define M_ATRAP_CFG_INV&t;   &t;   _SB_MAKEMASK1(5)
DECL|macro|M_ATRAP_CFG_USESRC
mdefine_line|#define M_ATRAP_CFG_USESRC&t;   _SB_MAKEMASK1(6)
DECL|macro|M_ATRAP_CFG_SRCINV
mdefine_line|#define M_ATRAP_CFG_SRCINV&t;   _SB_MAKEMASK1(7)
DECL|macro|S_ATRAP_CFG_AGENTID
mdefine_line|#define S_ATRAP_CFG_AGENTID     8
DECL|macro|M_ATRAP_CFG_AGENTID
mdefine_line|#define M_ATRAP_CFG_AGENTID     _SB_MAKEMASK(4,S_ATRAP_CFG_AGENTID)
DECL|macro|V_ATRAP_CFG_AGENTID
mdefine_line|#define V_ATRAP_CFG_AGENTID(x)  _SB_MAKEVALUE(x,S_ATRAP_CFG_AGENTID)
DECL|macro|G_ATRAP_CFG_AGENTID
mdefine_line|#define G_ATRAP_CFG_AGENTID(x)  _SB_GETVALUE(x,S_ATRAP_CFG_AGENTID,M_ATRAP_CFG_AGENTID)
DECL|macro|K_BUS_AGENT_CPU0
mdefine_line|#define K_BUS_AGENT_CPU0&t;0
DECL|macro|K_BUS_AGENT_CPU1
mdefine_line|#define K_BUS_AGENT_CPU1&t;1
DECL|macro|K_BUS_AGENT_IOB0
mdefine_line|#define K_BUS_AGENT_IOB0&t;2
DECL|macro|K_BUS_AGENT_IOB1
mdefine_line|#define K_BUS_AGENT_IOB1&t;3
DECL|macro|K_BUS_AGENT_SCD
mdefine_line|#define K_BUS_AGENT_SCD&t;4
DECL|macro|K_BUS_AGENT_RESERVED
mdefine_line|#define K_BUS_AGENT_RESERVED&t;5
DECL|macro|K_BUS_AGENT_L2C
mdefine_line|#define K_BUS_AGENT_L2C&t;6
DECL|macro|K_BUS_AGENT_MC
mdefine_line|#define K_BUS_AGENT_MC&t;7
DECL|macro|S_ATRAP_CFG_CATTR
mdefine_line|#define S_ATRAP_CFG_CATTR     12
DECL|macro|M_ATRAP_CFG_CATTR
mdefine_line|#define M_ATRAP_CFG_CATTR     _SB_MAKEMASK(3,S_ATRAP_CFG_CATTR)
DECL|macro|V_ATRAP_CFG_CATTR
mdefine_line|#define V_ATRAP_CFG_CATTR(x)  _SB_MAKEVALUE(x,S_ATRAP_CFG_CATTR)
DECL|macro|G_ATRAP_CFG_CATTR
mdefine_line|#define G_ATRAP_CFG_CATTR(x)  _SB_GETVALUE(x,S_ATRAP_CFG_CATTR,M_ATRAP_CFG_CATTR)
DECL|macro|K_ATRAP_CFG_CATTR_IGNORE
mdefine_line|#define K_ATRAP_CFG_CATTR_IGNORE&t;0
DECL|macro|K_ATRAP_CFG_CATTR_UNC
mdefine_line|#define K_ATRAP_CFG_CATTR_UNC    &t;1
DECL|macro|K_ATRAP_CFG_CATTR_CACHEABLE
mdefine_line|#define K_ATRAP_CFG_CATTR_CACHEABLE&t;2
DECL|macro|K_ATRAP_CFG_CATTR_NONCOH
mdefine_line|#define K_ATRAP_CFG_CATTR_NONCOH  &t;3
DECL|macro|K_ATRAP_CFG_CATTR_COHERENT
mdefine_line|#define K_ATRAP_CFG_CATTR_COHERENT&t;4
DECL|macro|K_ATRAP_CFG_CATTR_NOTUNC
mdefine_line|#define K_ATRAP_CFG_CATTR_NOTUNC&t;5
DECL|macro|K_ATRAP_CFG_CATTR_NOTNONCOH
mdefine_line|#define K_ATRAP_CFG_CATTR_NOTNONCOH&t;6
DECL|macro|K_ATRAP_CFG_CATTR_NOTCOHERENT
mdefine_line|#define K_ATRAP_CFG_CATTR_NOTCOHERENT   7
multiline_comment|/*&n; * Trace Buffer Config register&n; */
DECL|macro|M_SCD_TRACE_CFG_RESET
mdefine_line|#define M_SCD_TRACE_CFG_RESET           _SB_MAKEMASK1(0)
DECL|macro|M_SCD_TRACE_CFG_START_READ
mdefine_line|#define M_SCD_TRACE_CFG_START_READ      _SB_MAKEMASK1(1)
DECL|macro|M_SCD_TRACE_CFG_START
mdefine_line|#define M_SCD_TRACE_CFG_START           _SB_MAKEMASK1(2)
DECL|macro|M_SCD_TRACE_CFG_STOP
mdefine_line|#define M_SCD_TRACE_CFG_STOP            _SB_MAKEMASK1(3)
DECL|macro|M_SCD_TRACE_CFG_FREEZE
mdefine_line|#define M_SCD_TRACE_CFG_FREEZE          _SB_MAKEMASK1(4)
DECL|macro|M_SCD_TRACE_CFG_FREEZE_FULL
mdefine_line|#define M_SCD_TRACE_CFG_FREEZE_FULL     _SB_MAKEMASK1(5)
DECL|macro|M_SCD_TRACE_CFG_DEBUG_FULL
mdefine_line|#define M_SCD_TRACE_CFG_DEBUG_FULL      _SB_MAKEMASK1(6)
DECL|macro|M_SCD_TRACE_CFG_FULL
mdefine_line|#define M_SCD_TRACE_CFG_FULL            _SB_MAKEMASK1(7)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_SCD_TRACE_CFG_FORCECNT
mdefine_line|#define M_SCD_TRACE_CFG_FORCECNT        _SB_MAKEMASK1(8)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_SCD_TRACE_CFG_CUR_ADDR
mdefine_line|#define S_SCD_TRACE_CFG_CUR_ADDR        10
DECL|macro|M_SCD_TRACE_CFG_CUR_ADDR
mdefine_line|#define M_SCD_TRACE_CFG_CUR_ADDR        _SB_MAKEMASK(8,S_SCD_TRACE_CFG_CUR_ADDR)
DECL|macro|V_SCD_TRACE_CFG_CUR_ADDR
mdefine_line|#define V_SCD_TRACE_CFG_CUR_ADDR(x)     _SB_MAKEVALUE(x,S_SCD_TRACE_CFG_CUR_ADDR)
DECL|macro|G_SCD_TRACE_CFG_CUR_ADDR
mdefine_line|#define G_SCD_TRACE_CFG_CUR_ADDR(x)     _SB_GETVALUE(x,S_SCD_TRACE_CFG_CUR_ADDR,M_SCD_TRACE_CFG_CUR_ADDR)
multiline_comment|/*&n; * Trace Event registers&n; */
DECL|macro|S_SCD_TREVT_ADDR_MATCH
mdefine_line|#define S_SCD_TREVT_ADDR_MATCH          0
DECL|macro|M_SCD_TREVT_ADDR_MATCH
mdefine_line|#define M_SCD_TREVT_ADDR_MATCH          _SB_MAKEMASK(4,S_SCD_TREVT_ADDR_MATCH)
DECL|macro|V_SCD_TREVT_ADDR_MATCH
mdefine_line|#define V_SCD_TREVT_ADDR_MATCH(x)       _SB_MAKEVALUE(x,S_SCD_TREVT_ADDR_MATCH)
DECL|macro|G_SCD_TREVT_ADDR_MATCH
mdefine_line|#define G_SCD_TREVT_ADDR_MATCH(x)       _SB_GETVALUE(x,S_SCD_TREVT_ADDR_MATCH,M_SCD_TREVT_ADDR_MATCH)
DECL|macro|M_SCD_TREVT_REQID_MATCH
mdefine_line|#define M_SCD_TREVT_REQID_MATCH         _SB_MAKEMASK1(4)
DECL|macro|M_SCD_TREVT_DATAID_MATCH
mdefine_line|#define M_SCD_TREVT_DATAID_MATCH        _SB_MAKEMASK1(5)
DECL|macro|M_SCD_TREVT_RESPID_MATCH
mdefine_line|#define M_SCD_TREVT_RESPID_MATCH        _SB_MAKEMASK1(6)
DECL|macro|M_SCD_TREVT_INTERRUPT
mdefine_line|#define M_SCD_TREVT_INTERRUPT           _SB_MAKEMASK1(7)
DECL|macro|M_SCD_TREVT_DEBUG_PIN
mdefine_line|#define M_SCD_TREVT_DEBUG_PIN           _SB_MAKEMASK1(9)
DECL|macro|M_SCD_TREVT_WRITE
mdefine_line|#define M_SCD_TREVT_WRITE               _SB_MAKEMASK1(10)
DECL|macro|M_SCD_TREVT_READ
mdefine_line|#define M_SCD_TREVT_READ                _SB_MAKEMASK1(11)
DECL|macro|S_SCD_TREVT_REQID
mdefine_line|#define S_SCD_TREVT_REQID               12
DECL|macro|M_SCD_TREVT_REQID
mdefine_line|#define M_SCD_TREVT_REQID               _SB_MAKEMASK(4,S_SCD_TREVT_REQID)
DECL|macro|V_SCD_TREVT_REQID
mdefine_line|#define V_SCD_TREVT_REQID(x)            _SB_MAKEVALUE(x,S_SCD_TREVT_REQID)
DECL|macro|G_SCD_TREVT_REQID
mdefine_line|#define G_SCD_TREVT_REQID(x)            _SB_GETVALUE(x,S_SCD_TREVT_REQID,M_SCD_TREVT_REQID)
DECL|macro|S_SCD_TREVT_RESPID
mdefine_line|#define S_SCD_TREVT_RESPID              16
DECL|macro|M_SCD_TREVT_RESPID
mdefine_line|#define M_SCD_TREVT_RESPID              _SB_MAKEMASK(4,S_SCD_TREVT_RESPID)
DECL|macro|V_SCD_TREVT_RESPID
mdefine_line|#define V_SCD_TREVT_RESPID(x)           _SB_MAKEVALUE(x,S_SCD_TREVT_RESPID)
DECL|macro|G_SCD_TREVT_RESPID
mdefine_line|#define G_SCD_TREVT_RESPID(x)           _SB_GETVALUE(x,S_SCD_TREVT_RESPID,M_SCD_TREVT_RESPID)
DECL|macro|S_SCD_TREVT_DATAID
mdefine_line|#define S_SCD_TREVT_DATAID              20
DECL|macro|M_SCD_TREVT_DATAID
mdefine_line|#define M_SCD_TREVT_DATAID              _SB_MAKEMASK(4,S_SCD_TREVT_DATAID)
DECL|macro|V_SCD_TREVT_DATAID
mdefine_line|#define V_SCD_TREVT_DATAID(x)           _SB_MAKEVALUE(x,S_SCD_TREVT_DATAID)
DECL|macro|G_SCD_TREVT_DATAID
mdefine_line|#define G_SCD_TREVT_DATAID(x)           _SB_GETVALUE(x,S_SCD_TREVT_DATAID,M_SCD_TREVT_DATID)
DECL|macro|S_SCD_TREVT_COUNT
mdefine_line|#define S_SCD_TREVT_COUNT               24
DECL|macro|M_SCD_TREVT_COUNT
mdefine_line|#define M_SCD_TREVT_COUNT               _SB_MAKEMASK(8,S_SCD_TREVT_COUNT)
DECL|macro|V_SCD_TREVT_COUNT
mdefine_line|#define V_SCD_TREVT_COUNT(x)            _SB_MAKEVALUE(x,S_SCD_TREVT_COUNT)
DECL|macro|G_SCD_TREVT_COUNT
mdefine_line|#define G_SCD_TREVT_COUNT(x)            _SB_GETVALUE(x,S_SCD_TREVT_COUNT,M_SCD_TREVT_COUNT)
multiline_comment|/*&n; * Trace Sequence registers&n; */
DECL|macro|S_SCD_TRSEQ_EVENT4
mdefine_line|#define S_SCD_TRSEQ_EVENT4              0
DECL|macro|M_SCD_TRSEQ_EVENT4
mdefine_line|#define M_SCD_TRSEQ_EVENT4              _SB_MAKEMASK(4,S_SCD_TRSEQ_EVENT4)
DECL|macro|V_SCD_TRSEQ_EVENT4
mdefine_line|#define V_SCD_TRSEQ_EVENT4(x)           _SB_MAKEVALUE(x,S_SCD_TRSEQ_EVENT4)
DECL|macro|G_SCD_TRSEQ_EVENT4
mdefine_line|#define G_SCD_TRSEQ_EVENT4(x)           _SB_GETVALUE(x,S_SCD_TRSEQ_EVENT4,M_SCD_TRSEQ_EVENT4)
DECL|macro|S_SCD_TRSEQ_EVENT3
mdefine_line|#define S_SCD_TRSEQ_EVENT3              4
DECL|macro|M_SCD_TRSEQ_EVENT3
mdefine_line|#define M_SCD_TRSEQ_EVENT3              _SB_MAKEMASK(4,S_SCD_TRSEQ_EVENT3)
DECL|macro|V_SCD_TRSEQ_EVENT3
mdefine_line|#define V_SCD_TRSEQ_EVENT3(x)           _SB_MAKEVALUE(x,S_SCD_TRSEQ_EVENT3)
DECL|macro|G_SCD_TRSEQ_EVENT3
mdefine_line|#define G_SCD_TRSEQ_EVENT3(x)           _SB_GETVALUE(x,S_SCD_TRSEQ_EVENT3,M_SCD_TRSEQ_EVENT3)
DECL|macro|S_SCD_TRSEQ_EVENT2
mdefine_line|#define S_SCD_TRSEQ_EVENT2              8
DECL|macro|M_SCD_TRSEQ_EVENT2
mdefine_line|#define M_SCD_TRSEQ_EVENT2              _SB_MAKEMASK(4,S_SCD_TRSEQ_EVENT2)
DECL|macro|V_SCD_TRSEQ_EVENT2
mdefine_line|#define V_SCD_TRSEQ_EVENT2(x)           _SB_MAKEVALUE(x,S_SCD_TRSEQ_EVENT2)
DECL|macro|G_SCD_TRSEQ_EVENT2
mdefine_line|#define G_SCD_TRSEQ_EVENT2(x)           _SB_GETVALUE(x,S_SCD_TRSEQ_EVENT2,M_SCD_TRSEQ_EVENT2)
DECL|macro|S_SCD_TRSEQ_EVENT1
mdefine_line|#define S_SCD_TRSEQ_EVENT1              12
DECL|macro|M_SCD_TRSEQ_EVENT1
mdefine_line|#define M_SCD_TRSEQ_EVENT1              _SB_MAKEMASK(4,S_SCD_TRSEQ_EVENT1)
DECL|macro|V_SCD_TRSEQ_EVENT1
mdefine_line|#define V_SCD_TRSEQ_EVENT1(x)           _SB_MAKEVALUE(x,S_SCD_TRSEQ_EVENT1)
DECL|macro|G_SCD_TRSEQ_EVENT1
mdefine_line|#define G_SCD_TRSEQ_EVENT1(x)           _SB_GETVALUE(x,S_SCD_TRSEQ_EVENT1,M_SCD_TRSEQ_EVENT1)
DECL|macro|K_SCD_TRSEQ_E0
mdefine_line|#define K_SCD_TRSEQ_E0                  0
DECL|macro|K_SCD_TRSEQ_E1
mdefine_line|#define K_SCD_TRSEQ_E1                  1
DECL|macro|K_SCD_TRSEQ_E2
mdefine_line|#define K_SCD_TRSEQ_E2                  2
DECL|macro|K_SCD_TRSEQ_E3
mdefine_line|#define K_SCD_TRSEQ_E3                  3
DECL|macro|K_SCD_TRSEQ_E0_E1
mdefine_line|#define K_SCD_TRSEQ_E0_E1               4
DECL|macro|K_SCD_TRSEQ_E1_E2
mdefine_line|#define K_SCD_TRSEQ_E1_E2               5
DECL|macro|K_SCD_TRSEQ_E2_E3
mdefine_line|#define K_SCD_TRSEQ_E2_E3               6
DECL|macro|K_SCD_TRSEQ_E0_E1_E2
mdefine_line|#define K_SCD_TRSEQ_E0_E1_E2            7
DECL|macro|K_SCD_TRSEQ_E0_E1_E2_E3
mdefine_line|#define K_SCD_TRSEQ_E0_E1_E2_E3         8
DECL|macro|K_SCD_TRSEQ_E0E1
mdefine_line|#define K_SCD_TRSEQ_E0E1                9
DECL|macro|K_SCD_TRSEQ_E0E1E2
mdefine_line|#define K_SCD_TRSEQ_E0E1E2              10
DECL|macro|K_SCD_TRSEQ_E0E1E2E3
mdefine_line|#define K_SCD_TRSEQ_E0E1E2E3            11
DECL|macro|K_SCD_TRSEQ_E0E1_E2
mdefine_line|#define K_SCD_TRSEQ_E0E1_E2             12
DECL|macro|K_SCD_TRSEQ_E0E1_E2E3
mdefine_line|#define K_SCD_TRSEQ_E0E1_E2E3           13
DECL|macro|K_SCD_TRSEQ_E0E1_E2_E3
mdefine_line|#define K_SCD_TRSEQ_E0E1_E2_E3          14
DECL|macro|K_SCD_TRSEQ_IGNORED
mdefine_line|#define K_SCD_TRSEQ_IGNORED             15
DECL|macro|K_SCD_TRSEQ_TRIGGER_ALL
mdefine_line|#define K_SCD_TRSEQ_TRIGGER_ALL         (V_SCD_TRSEQ_EVENT1(K_SCD_TRSEQ_IGNORED) | &bslash;&n;                                         V_SCD_TRSEQ_EVENT2(K_SCD_TRSEQ_IGNORED) | &bslash;&n;                                         V_SCD_TRSEQ_EVENT3(K_SCD_TRSEQ_IGNORED) | &bslash;&n;                                         V_SCD_TRSEQ_EVENT4(K_SCD_TRSEQ_IGNORED))
DECL|macro|S_SCD_TRSEQ_FUNCTION
mdefine_line|#define S_SCD_TRSEQ_FUNCTION            16
DECL|macro|M_SCD_TRSEQ_FUNCTION
mdefine_line|#define M_SCD_TRSEQ_FUNCTION            _SB_MAKEMASK(4,S_SCD_TRSEQ_FUNCTION)
DECL|macro|V_SCD_TRSEQ_FUNCTION
mdefine_line|#define V_SCD_TRSEQ_FUNCTION(x)         _SB_MAKEVALUE(x,S_SCD_TRSEQ_FUNCTION)
DECL|macro|G_SCD_TRSEQ_FUNCTION
mdefine_line|#define G_SCD_TRSEQ_FUNCTION(x)         _SB_GETVALUE(x,S_SCD_TRSEQ_FUNCTION,M_SCD_TRSEQ_FUNCTION)
DECL|macro|K_SCD_TRSEQ_FUNC_NOP
mdefine_line|#define K_SCD_TRSEQ_FUNC_NOP            0
DECL|macro|K_SCD_TRSEQ_FUNC_START
mdefine_line|#define K_SCD_TRSEQ_FUNC_START          1
DECL|macro|K_SCD_TRSEQ_FUNC_STOP
mdefine_line|#define K_SCD_TRSEQ_FUNC_STOP           2
DECL|macro|K_SCD_TRSEQ_FUNC_FREEZE
mdefine_line|#define K_SCD_TRSEQ_FUNC_FREEZE         3
DECL|macro|V_SCD_TRSEQ_FUNC_NOP
mdefine_line|#define V_SCD_TRSEQ_FUNC_NOP            V_SCD_TRSEQ_FUNCTION(K_SCD_TRSEQ_FUNC_NOP)
DECL|macro|V_SCD_TRSEQ_FUNC_START
mdefine_line|#define V_SCD_TRSEQ_FUNC_START          V_SCD_TRSEQ_FUNCTION(K_SCD_TRSEQ_FUNC_START)
DECL|macro|V_SCD_TRSEQ_FUNC_STOP
mdefine_line|#define V_SCD_TRSEQ_FUNC_STOP           V_SCD_TRSEQ_FUNCTION(K_SCD_TRSEQ_FUNC_STOP)
DECL|macro|V_SCD_TRSEQ_FUNC_FREEZE
mdefine_line|#define V_SCD_TRSEQ_FUNC_FREEZE         V_SCD_TRSEQ_FUNCTION(K_SCD_TRSEQ_FUNC_FREEZE)
DECL|macro|M_SCD_TRSEQ_ASAMPLE
mdefine_line|#define M_SCD_TRSEQ_ASAMPLE             _SB_MAKEMASK1(18)
DECL|macro|M_SCD_TRSEQ_DSAMPLE
mdefine_line|#define M_SCD_TRSEQ_DSAMPLE             _SB_MAKEMASK1(19)
DECL|macro|M_SCD_TRSEQ_DEBUGPIN
mdefine_line|#define M_SCD_TRSEQ_DEBUGPIN            _SB_MAKEMASK1(20)
DECL|macro|M_SCD_TRSEQ_DEBUGCPU
mdefine_line|#define M_SCD_TRSEQ_DEBUGCPU            _SB_MAKEMASK1(21)
DECL|macro|M_SCD_TRSEQ_CLEARUSE
mdefine_line|#define M_SCD_TRSEQ_CLEARUSE            _SB_MAKEMASK1(22)
macro_line|#endif
eof
