multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  Memory Controller constants              File: sb1250_mc.h       &n;    *  &n;    *  This module contains constants and macros useful for&n;    *  programming the memory controller.&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_MC_H
DECL|macro|_SB1250_MC_H
mdefine_line|#define _SB1250_MC_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*&n; * Memory Channel Config Register (table 6-14)&n; */
DECL|macro|S_MC_RESERVED0
mdefine_line|#define S_MC_RESERVED0              0
DECL|macro|M_MC_RESERVED0
mdefine_line|#define M_MC_RESERVED0              _SB_MAKEMASK(8,S_MC_RESERVED0)
DECL|macro|S_MC_CHANNEL_SEL
mdefine_line|#define S_MC_CHANNEL_SEL            8
DECL|macro|M_MC_CHANNEL_SEL
mdefine_line|#define M_MC_CHANNEL_SEL            _SB_MAKEMASK(8,S_MC_CHANNEL_SEL)
DECL|macro|V_MC_CHANNEL_SEL
mdefine_line|#define V_MC_CHANNEL_SEL(x)         _SB_MAKEVALUE(x,S_MC_CHANNEL_SEL)
DECL|macro|G_MC_CHANNEL_SEL
mdefine_line|#define G_MC_CHANNEL_SEL(x)         _SB_GETVALUE(x,S_MC_CHANNEL_SEL,M_MC_CHANNEL_SEL)
DECL|macro|S_MC_BANK0_MAP
mdefine_line|#define S_MC_BANK0_MAP              16
DECL|macro|M_MC_BANK0_MAP
mdefine_line|#define M_MC_BANK0_MAP              _SB_MAKEMASK(4,S_MC_BANK0_MAP)
DECL|macro|V_MC_BANK0_MAP
mdefine_line|#define V_MC_BANK0_MAP(x)           _SB_MAKEVALUE(x,S_MC_BANK0_MAP)
DECL|macro|G_MC_BANK0_MAP
mdefine_line|#define G_MC_BANK0_MAP(x)           _SB_GETVALUE(x,S_MC_BANK0_MAP,M_MC_BANK0_MAP)
DECL|macro|K_MC_BANK0_MAP_DEFAULT
mdefine_line|#define K_MC_BANK0_MAP_DEFAULT      0x00
DECL|macro|V_MC_BANK0_MAP_DEFAULT
mdefine_line|#define V_MC_BANK0_MAP_DEFAULT      V_MC_BANK0_MAP(K_MC_BANK0_MAP_DEFAULT)
DECL|macro|S_MC_BANK1_MAP
mdefine_line|#define S_MC_BANK1_MAP              20
DECL|macro|M_MC_BANK1_MAP
mdefine_line|#define M_MC_BANK1_MAP              _SB_MAKEMASK(4,S_MC_BANK1_MAP)
DECL|macro|V_MC_BANK1_MAP
mdefine_line|#define V_MC_BANK1_MAP(x)           _SB_MAKEVALUE(x,S_MC_BANK1_MAP)
DECL|macro|G_MC_BANK1_MAP
mdefine_line|#define G_MC_BANK1_MAP(x)           _SB_GETVALUE(x,S_MC_BANK1_MAP,M_MC_BANK1_MAP)
DECL|macro|K_MC_BANK1_MAP_DEFAULT
mdefine_line|#define K_MC_BANK1_MAP_DEFAULT      0x08
DECL|macro|V_MC_BANK1_MAP_DEFAULT
mdefine_line|#define V_MC_BANK1_MAP_DEFAULT      V_MC_BANK1_MAP(K_MC_BANK1_MAP_DEFAULT)
DECL|macro|S_MC_BANK2_MAP
mdefine_line|#define S_MC_BANK2_MAP              24
DECL|macro|M_MC_BANK2_MAP
mdefine_line|#define M_MC_BANK2_MAP              _SB_MAKEMASK(4,S_MC_BANK2_MAP)
DECL|macro|V_MC_BANK2_MAP
mdefine_line|#define V_MC_BANK2_MAP(x)           _SB_MAKEVALUE(x,S_MC_BANK2_MAP)
DECL|macro|G_MC_BANK2_MAP
mdefine_line|#define G_MC_BANK2_MAP(x)           _SB_GETVALUE(x,S_MC_BANK2_MAP,M_MC_BANK2_MAP)
DECL|macro|K_MC_BANK2_MAP_DEFAULT
mdefine_line|#define K_MC_BANK2_MAP_DEFAULT      0x09
DECL|macro|V_MC_BANK2_MAP_DEFAULT
mdefine_line|#define V_MC_BANK2_MAP_DEFAULT      V_MC_BANK2_MAP(K_MC_BANK2_MAP_DEFAULT)
DECL|macro|S_MC_BANK3_MAP
mdefine_line|#define S_MC_BANK3_MAP              28
DECL|macro|M_MC_BANK3_MAP
mdefine_line|#define M_MC_BANK3_MAP              _SB_MAKEMASK(4,S_MC_BANK3_MAP)
DECL|macro|V_MC_BANK3_MAP
mdefine_line|#define V_MC_BANK3_MAP(x)           _SB_MAKEVALUE(x,S_MC_BANK3_MAP)
DECL|macro|G_MC_BANK3_MAP
mdefine_line|#define G_MC_BANK3_MAP(x)           _SB_GETVALUE(x,S_MC_BANK3_MAP,M_MC_BANK3_MAP)
DECL|macro|K_MC_BANK3_MAP_DEFAULT
mdefine_line|#define K_MC_BANK3_MAP_DEFAULT      0x0C
DECL|macro|V_MC_BANK3_MAP_DEFAULT
mdefine_line|#define V_MC_BANK3_MAP_DEFAULT      V_MC_BANK3_MAP(K_MC_BANK3_MAP_DEFAULT)
DECL|macro|M_MC_RESERVED1
mdefine_line|#define M_MC_RESERVED1              _SB_MAKEMASK(8,32)
DECL|macro|S_MC_QUEUE_SIZE
mdefine_line|#define S_MC_QUEUE_SIZE&t;&t;    40
DECL|macro|M_MC_QUEUE_SIZE
mdefine_line|#define M_MC_QUEUE_SIZE             _SB_MAKEMASK(4,S_MC_QUEUE_SIZE)
DECL|macro|V_MC_QUEUE_SIZE
mdefine_line|#define V_MC_QUEUE_SIZE(x)          _SB_MAKEVALUE(x,S_MC_QUEUE_SIZE)
DECL|macro|G_MC_QUEUE_SIZE
mdefine_line|#define G_MC_QUEUE_SIZE(x)          _SB_GETVALUE(x,S_MC_QUEUE_SIZE,M_MC_QUEUE_SIZE)
DECL|macro|V_MC_QUEUE_SIZE_DEFAULT
mdefine_line|#define V_MC_QUEUE_SIZE_DEFAULT     V_MC_QUEUE_SIZE(0x0A)
DECL|macro|S_MC_AGE_LIMIT
mdefine_line|#define S_MC_AGE_LIMIT              44
DECL|macro|M_MC_AGE_LIMIT
mdefine_line|#define M_MC_AGE_LIMIT              _SB_MAKEMASK(4,S_MC_AGE_LIMIT)
DECL|macro|V_MC_AGE_LIMIT
mdefine_line|#define V_MC_AGE_LIMIT(x)           _SB_MAKEVALUE(x,S_MC_AGE_LIMIT)
DECL|macro|G_MC_AGE_LIMIT
mdefine_line|#define G_MC_AGE_LIMIT(x)           _SB_GETVALUE(x,S_MC_AGE_LIMIT,M_MC_AGE_LIMIT)
DECL|macro|V_MC_AGE_LIMIT_DEFAULT
mdefine_line|#define V_MC_AGE_LIMIT_DEFAULT      V_MC_AGE_LIMIT(8)
DECL|macro|S_MC_WR_LIMIT
mdefine_line|#define S_MC_WR_LIMIT               48
DECL|macro|M_MC_WR_LIMIT
mdefine_line|#define M_MC_WR_LIMIT               _SB_MAKEMASK(4,S_MC_WR_LIMIT)
DECL|macro|V_MC_WR_LIMIT
mdefine_line|#define V_MC_WR_LIMIT(x)            _SB_MAKEVALUE(x,S_MC_WR_LIMIT)
DECL|macro|G_MC_WR_LIMIT
mdefine_line|#define G_MC_WR_LIMIT(x)            _SB_GETVALUE(x,S_MC_WR_LIMIT,M_MC_WR_LIMIT)
DECL|macro|V_MC_WR_LIMIT_DEFAULT
mdefine_line|#define V_MC_WR_LIMIT_DEFAULT       V_MC_WR_LIMIT(5)
DECL|macro|M_MC_IOB1HIGHPRIORITY
mdefine_line|#define M_MC_IOB1HIGHPRIORITY&t;    _SB_MAKEMASK1(52)
DECL|macro|M_MC_RESERVED2
mdefine_line|#define M_MC_RESERVED2              _SB_MAKEMASK(3,53)
DECL|macro|S_MC_CS_MODE
mdefine_line|#define S_MC_CS_MODE                56
DECL|macro|M_MC_CS_MODE
mdefine_line|#define M_MC_CS_MODE                _SB_MAKEMASK(4,S_MC_CS_MODE)
DECL|macro|V_MC_CS_MODE
mdefine_line|#define V_MC_CS_MODE(x)             _SB_MAKEVALUE(x,S_MC_CS_MODE)
DECL|macro|G_MC_CS_MODE
mdefine_line|#define G_MC_CS_MODE(x)             _SB_GETVALUE(x,S_MC_CS_MODE,M_MC_CS_MODE)
DECL|macro|K_MC_CS_MODE_MSB_CS
mdefine_line|#define K_MC_CS_MODE_MSB_CS         0
DECL|macro|K_MC_CS_MODE_INTLV_CS
mdefine_line|#define K_MC_CS_MODE_INTLV_CS       15
DECL|macro|K_MC_CS_MODE_MIXED_CS_10
mdefine_line|#define K_MC_CS_MODE_MIXED_CS_10    12
DECL|macro|K_MC_CS_MODE_MIXED_CS_30
mdefine_line|#define K_MC_CS_MODE_MIXED_CS_30    6
DECL|macro|K_MC_CS_MODE_MIXED_CS_32
mdefine_line|#define K_MC_CS_MODE_MIXED_CS_32    3
DECL|macro|V_MC_CS_MODE_MSB_CS
mdefine_line|#define V_MC_CS_MODE_MSB_CS         V_MC_CS_MODE(K_MC_CS_MODE_MSB_CS)
DECL|macro|V_MC_CS_MODE_INTLV_CS
mdefine_line|#define V_MC_CS_MODE_INTLV_CS       V_MC_CS_MODE(K_MC_CS_MODE_INTLV_CS)
DECL|macro|V_MC_CS_MODE_MIXED_CS_10
mdefine_line|#define V_MC_CS_MODE_MIXED_CS_10    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_10)
DECL|macro|V_MC_CS_MODE_MIXED_CS_30
mdefine_line|#define V_MC_CS_MODE_MIXED_CS_30    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_30)
DECL|macro|V_MC_CS_MODE_MIXED_CS_32
mdefine_line|#define V_MC_CS_MODE_MIXED_CS_32    V_MC_CS_MODE(K_MC_CS_MODE_MIXED_CS_32)
DECL|macro|M_MC_ECC_DISABLE
mdefine_line|#define M_MC_ECC_DISABLE            _SB_MAKEMASK1(60)
DECL|macro|M_MC_BERR_DISABLE
mdefine_line|#define M_MC_BERR_DISABLE           _SB_MAKEMASK1(61)
DECL|macro|M_MC_FORCE_SEQ
mdefine_line|#define M_MC_FORCE_SEQ              _SB_MAKEMASK1(62)
DECL|macro|M_MC_DEBUG
mdefine_line|#define M_MC_DEBUG                  _SB_MAKEMASK1(63)
DECL|macro|V_MC_CONFIG_DEFAULT
mdefine_line|#define V_MC_CONFIG_DEFAULT     V_MC_WR_LIMIT_DEFAULT | V_MC_AGE_LIMIT_DEFAULT | &bslash;&n;&t;&t;&t;&t;V_MC_BANK0_MAP_DEFAULT | V_MC_BANK1_MAP_DEFAULT | &bslash;&n;&t;&t;&t;&t;V_MC_BANK2_MAP_DEFAULT | V_MC_BANK3_MAP_DEFAULT | V_MC_CHANNEL_SEL(0) | &bslash;&n;                                M_MC_IOB1HIGHPRIORITY | V_MC_QUEUE_SIZE_DEFAULT
multiline_comment|/*&n; * Memory clock config register (Table 6-15)&n; *&n; * Note: this field has been updated to be consistent with the errata to 0.2&n; */
DECL|macro|S_MC_CLK_RATIO
mdefine_line|#define S_MC_CLK_RATIO              0
DECL|macro|M_MC_CLK_RATIO
mdefine_line|#define M_MC_CLK_RATIO              _SB_MAKEMASK(4,S_MC_CLK_RATIO)
DECL|macro|V_MC_CLK_RATIO
mdefine_line|#define V_MC_CLK_RATIO(x)           _SB_MAKEVALUE(x,S_MC_CLK_RATIO)
DECL|macro|G_MC_CLK_RATIO
mdefine_line|#define G_MC_CLK_RATIO(x)           _SB_GETVALUE(x,S_MC_CLK_RATIO,M_MC_CLK_RATIO)
DECL|macro|K_MC_CLK_RATIO_2X
mdefine_line|#define K_MC_CLK_RATIO_2X           4
DECL|macro|K_MC_CLK_RATIO_25X
mdefine_line|#define K_MC_CLK_RATIO_25X          5
DECL|macro|K_MC_CLK_RATIO_3X
mdefine_line|#define K_MC_CLK_RATIO_3X           6
DECL|macro|K_MC_CLK_RATIO_35X
mdefine_line|#define K_MC_CLK_RATIO_35X          7
DECL|macro|K_MC_CLK_RATIO_4X
mdefine_line|#define K_MC_CLK_RATIO_4X           8
DECL|macro|K_MC_CLK_RATIO_45X
mdefine_line|#define K_MC_CLK_RATIO_45X&t;    9
DECL|macro|V_MC_CLK_RATIO_2X
mdefine_line|#define V_MC_CLK_RATIO_2X&t;    V_MC_CLK_RATIO(K_MC_CLK_RATIO_2X)
DECL|macro|V_MC_CLK_RATIO_25X
mdefine_line|#define V_MC_CLK_RATIO_25X          V_MC_CLK_RATIO(K_MC_CLK_RATIO_25X)
DECL|macro|V_MC_CLK_RATIO_3X
mdefine_line|#define V_MC_CLK_RATIO_3X           V_MC_CLK_RATIO(K_MC_CLK_RATIO_3X)
DECL|macro|V_MC_CLK_RATIO_35X
mdefine_line|#define V_MC_CLK_RATIO_35X          V_MC_CLK_RATIO(K_MC_CLK_RATIO_35X)
DECL|macro|V_MC_CLK_RATIO_4X
mdefine_line|#define V_MC_CLK_RATIO_4X           V_MC_CLK_RATIO(K_MC_CLK_RATIO_4X)
DECL|macro|V_MC_CLK_RATIO_45X
mdefine_line|#define V_MC_CLK_RATIO_45X          V_MC_CLK_RATIO(K_MC_CLK_RATIO_45X)
DECL|macro|V_MC_CLK_RATIO_DEFAULT
mdefine_line|#define V_MC_CLK_RATIO_DEFAULT      V_MC_CLK_RATIO_25X
DECL|macro|S_MC_REF_RATE
mdefine_line|#define S_MC_REF_RATE                8
DECL|macro|M_MC_REF_RATE
mdefine_line|#define M_MC_REF_RATE                _SB_MAKEMASK(8,S_MC_REF_RATE)
DECL|macro|V_MC_REF_RATE
mdefine_line|#define V_MC_REF_RATE(x)             _SB_MAKEVALUE(x,S_MC_REF_RATE)
DECL|macro|G_MC_REF_RATE
mdefine_line|#define G_MC_REF_RATE(x)             _SB_GETVALUE(x,S_MC_REF_RATE,M_MC_REF_RATE)
DECL|macro|K_MC_REF_RATE_100MHz
mdefine_line|#define K_MC_REF_RATE_100MHz         0x62
DECL|macro|K_MC_REF_RATE_133MHz
mdefine_line|#define K_MC_REF_RATE_133MHz         0x81
DECL|macro|K_MC_REF_RATE_200MHz
mdefine_line|#define K_MC_REF_RATE_200MHz         0xC4 
DECL|macro|V_MC_REF_RATE_100MHz
mdefine_line|#define V_MC_REF_RATE_100MHz         V_MC_REF_RATE(K_MC_REF_RATE_100MHz)
DECL|macro|V_MC_REF_RATE_133MHz
mdefine_line|#define V_MC_REF_RATE_133MHz         V_MC_REF_RATE(K_MC_REF_RATE_133MHz)
DECL|macro|V_MC_REF_RATE_200MHz
mdefine_line|#define V_MC_REF_RATE_200MHz         V_MC_REF_RATE(K_MC_REF_RATE_200MHz)
DECL|macro|V_MC_REF_RATE_DEFAULT
mdefine_line|#define V_MC_REF_RATE_DEFAULT        V_MC_REF_RATE_100MHz
DECL|macro|S_MC_CLOCK_DRIVE
mdefine_line|#define S_MC_CLOCK_DRIVE             16
DECL|macro|M_MC_CLOCK_DRIVE
mdefine_line|#define M_MC_CLOCK_DRIVE             _SB_MAKEMASK(4,S_MC_CLOCK_DRIVE)
DECL|macro|V_MC_CLOCK_DRIVE
mdefine_line|#define V_MC_CLOCK_DRIVE(x)          _SB_MAKEVALUE(x,S_MC_CLOCK_DRIVE)
DECL|macro|G_MC_CLOCK_DRIVE
mdefine_line|#define G_MC_CLOCK_DRIVE(x)          _SB_GETVALUE(x,S_MC_CLOCK_DRIVE,M_MC_CLOCK_DRIVE)
DECL|macro|V_MC_CLOCK_DRIVE_DEFAULT
mdefine_line|#define V_MC_CLOCK_DRIVE_DEFAULT     V_MC_CLOCK_DRIVE(0xF)
DECL|macro|S_MC_DATA_DRIVE
mdefine_line|#define S_MC_DATA_DRIVE              20
DECL|macro|M_MC_DATA_DRIVE
mdefine_line|#define M_MC_DATA_DRIVE              _SB_MAKEMASK(4,S_MC_DATA_DRIVE)
DECL|macro|V_MC_DATA_DRIVE
mdefine_line|#define V_MC_DATA_DRIVE(x)           _SB_MAKEVALUE(x,S_MC_DATA_DRIVE)
DECL|macro|G_MC_DATA_DRIVE
mdefine_line|#define G_MC_DATA_DRIVE(x)           _SB_GETVALUE(x,S_MC_DATA_DRIVE,M_MC_DATA_DRIVE)
DECL|macro|V_MC_DATA_DRIVE_DEFAULT
mdefine_line|#define V_MC_DATA_DRIVE_DEFAULT      V_MC_DATA_DRIVE(0x0)
DECL|macro|S_MC_ADDR_DRIVE
mdefine_line|#define S_MC_ADDR_DRIVE              24
DECL|macro|M_MC_ADDR_DRIVE
mdefine_line|#define M_MC_ADDR_DRIVE              _SB_MAKEMASK(4,S_MC_ADDR_DRIVE)
DECL|macro|V_MC_ADDR_DRIVE
mdefine_line|#define V_MC_ADDR_DRIVE(x)           _SB_MAKEVALUE(x,S_MC_ADDR_DRIVE)
DECL|macro|G_MC_ADDR_DRIVE
mdefine_line|#define G_MC_ADDR_DRIVE(x)           _SB_GETVALUE(x,S_MC_ADDR_DRIVE,M_MC_ADDR_DRIVE)
DECL|macro|V_MC_ADDR_DRIVE_DEFAULT
mdefine_line|#define V_MC_ADDR_DRIVE_DEFAULT      V_MC_ADDR_DRIVE(0x0)
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MC_REF_DISABLE
mdefine_line|#define M_MC_REF_DISABLE             _SB_MAKEMASK1(30)
macro_line|#endif /* 112x PASS1 */
DECL|macro|M_MC_DLL_BYPASS
mdefine_line|#define M_MC_DLL_BYPASS              _SB_MAKEMASK1(31)
DECL|macro|S_MC_DQI_SKEW
mdefine_line|#define S_MC_DQI_SKEW               32
DECL|macro|M_MC_DQI_SKEW
mdefine_line|#define M_MC_DQI_SKEW               _SB_MAKEMASK(8,S_MC_DQI_SKEW)
DECL|macro|V_MC_DQI_SKEW
mdefine_line|#define V_MC_DQI_SKEW(x)            _SB_MAKEVALUE(x,S_MC_DQI_SKEW)
DECL|macro|G_MC_DQI_SKEW
mdefine_line|#define G_MC_DQI_SKEW(x)            _SB_GETVALUE(x,S_MC_DQI_SKEW,M_MC_DQI_SKEW)
DECL|macro|V_MC_DQI_SKEW_DEFAULT
mdefine_line|#define V_MC_DQI_SKEW_DEFAULT       V_MC_DQI_SKEW(0)
DECL|macro|S_MC_DQO_SKEW
mdefine_line|#define S_MC_DQO_SKEW               40
DECL|macro|M_MC_DQO_SKEW
mdefine_line|#define M_MC_DQO_SKEW               _SB_MAKEMASK(8,S_MC_DQO_SKEW)
DECL|macro|V_MC_DQO_SKEW
mdefine_line|#define V_MC_DQO_SKEW(x)            _SB_MAKEVALUE(x,S_MC_DQO_SKEW)
DECL|macro|G_MC_DQO_SKEW
mdefine_line|#define G_MC_DQO_SKEW(x)            _SB_GETVALUE(x,S_MC_DQO_SKEW,M_MC_DQO_SKEW)
DECL|macro|V_MC_DQO_SKEW_DEFAULT
mdefine_line|#define V_MC_DQO_SKEW_DEFAULT       V_MC_DQO_SKEW(0)
DECL|macro|S_MC_ADDR_SKEW
mdefine_line|#define S_MC_ADDR_SKEW               48
DECL|macro|M_MC_ADDR_SKEW
mdefine_line|#define M_MC_ADDR_SKEW               _SB_MAKEMASK(8,S_MC_ADDR_SKEW)
DECL|macro|V_MC_ADDR_SKEW
mdefine_line|#define V_MC_ADDR_SKEW(x)            _SB_MAKEVALUE(x,S_MC_ADDR_SKEW)
DECL|macro|G_MC_ADDR_SKEW
mdefine_line|#define G_MC_ADDR_SKEW(x)            _SB_GETVALUE(x,S_MC_ADDR_SKEW,M_MC_ADDR_SKEW)
DECL|macro|V_MC_ADDR_SKEW_DEFAULT
mdefine_line|#define V_MC_ADDR_SKEW_DEFAULT       V_MC_ADDR_SKEW(0x0F)
DECL|macro|S_MC_DLL_DEFAULT
mdefine_line|#define S_MC_DLL_DEFAULT             56
DECL|macro|M_MC_DLL_DEFAULT
mdefine_line|#define M_MC_DLL_DEFAULT             _SB_MAKEMASK(8,S_MC_DLL_DEFAULT)
DECL|macro|V_MC_DLL_DEFAULT
mdefine_line|#define V_MC_DLL_DEFAULT(x)          _SB_MAKEVALUE(x,S_MC_DLL_DEFAULT)
DECL|macro|G_MC_DLL_DEFAULT
mdefine_line|#define G_MC_DLL_DEFAULT(x)          _SB_GETVALUE(x,S_MC_DLL_DEFAULT,M_MC_DLL_DEFAULT)
DECL|macro|V_MC_DLL_DEFAULT_DEFAULT
mdefine_line|#define V_MC_DLL_DEFAULT_DEFAULT     V_MC_DLL_DEFAULT(0x10)
DECL|macro|V_MC_CLKCONFIG_DEFAULT
mdefine_line|#define V_MC_CLKCONFIG_DEFAULT       V_MC_DLL_DEFAULT_DEFAULT |  &bslash;&n;                                     V_MC_ADDR_SKEW_DEFAULT | &bslash;&n;                                     V_MC_DQO_SKEW_DEFAULT | &bslash;&n;                                     V_MC_DQI_SKEW_DEFAULT | &bslash;&n;                                     V_MC_ADDR_DRIVE_DEFAULT | &bslash;&n;                                     V_MC_DATA_DRIVE_DEFAULT | &bslash;&n;                                     V_MC_CLOCK_DRIVE_DEFAULT | &bslash;&n;                                     V_MC_REF_RATE_DEFAULT 
multiline_comment|/*&n; * DRAM Command Register (Table 6-13)&n; */
DECL|macro|S_MC_COMMAND
mdefine_line|#define S_MC_COMMAND                0
DECL|macro|M_MC_COMMAND
mdefine_line|#define M_MC_COMMAND                _SB_MAKEMASK(4,S_MC_COMMAND)
DECL|macro|V_MC_COMMAND
mdefine_line|#define V_MC_COMMAND(x)             _SB_MAKEVALUE(x,S_MC_COMMAND)
DECL|macro|G_MC_COMMAND
mdefine_line|#define G_MC_COMMAND(x)             _SB_GETVALUE(x,S_MC_COMMAND,M_MC_COMMAND)
DECL|macro|K_MC_COMMAND_EMRS
mdefine_line|#define K_MC_COMMAND_EMRS           0
DECL|macro|K_MC_COMMAND_MRS
mdefine_line|#define K_MC_COMMAND_MRS            1
DECL|macro|K_MC_COMMAND_PRE
mdefine_line|#define K_MC_COMMAND_PRE            2
DECL|macro|K_MC_COMMAND_AR
mdefine_line|#define K_MC_COMMAND_AR             3
DECL|macro|K_MC_COMMAND_SETRFSH
mdefine_line|#define K_MC_COMMAND_SETRFSH        4
DECL|macro|K_MC_COMMAND_CLRRFSH
mdefine_line|#define K_MC_COMMAND_CLRRFSH        5
DECL|macro|K_MC_COMMAND_SETPWRDN
mdefine_line|#define K_MC_COMMAND_SETPWRDN       6
DECL|macro|K_MC_COMMAND_CLRPWRDN
mdefine_line|#define K_MC_COMMAND_CLRPWRDN       7
DECL|macro|V_MC_COMMAND_EMRS
mdefine_line|#define V_MC_COMMAND_EMRS           V_MC_COMMAND(K_MC_COMMAND_EMRS)
DECL|macro|V_MC_COMMAND_MRS
mdefine_line|#define V_MC_COMMAND_MRS            V_MC_COMMAND(K_MC_COMMAND_MRS)
DECL|macro|V_MC_COMMAND_PRE
mdefine_line|#define V_MC_COMMAND_PRE            V_MC_COMMAND(K_MC_COMMAND_PRE)
DECL|macro|V_MC_COMMAND_AR
mdefine_line|#define V_MC_COMMAND_AR             V_MC_COMMAND(K_MC_COMMAND_AR)
DECL|macro|V_MC_COMMAND_SETRFSH
mdefine_line|#define V_MC_COMMAND_SETRFSH        V_MC_COMMAND(K_MC_COMMAND_SETRFSH)
DECL|macro|V_MC_COMMAND_CLRRFSH
mdefine_line|#define V_MC_COMMAND_CLRRFSH        V_MC_COMMAND(K_MC_COMMAND_CLRRFSH)
DECL|macro|V_MC_COMMAND_SETPWRDN
mdefine_line|#define V_MC_COMMAND_SETPWRDN       V_MC_COMMAND(K_MC_COMMAND_SETPWRDN)
DECL|macro|V_MC_COMMAND_CLRPWRDN
mdefine_line|#define V_MC_COMMAND_CLRPWRDN       V_MC_COMMAND(K_MC_COMMAND_CLRPWRDN)
DECL|macro|M_MC_CS0
mdefine_line|#define M_MC_CS0                    _SB_MAKEMASK1(4)
DECL|macro|M_MC_CS1
mdefine_line|#define M_MC_CS1                    _SB_MAKEMASK1(5)
DECL|macro|M_MC_CS2
mdefine_line|#define M_MC_CS2                    _SB_MAKEMASK1(6)
DECL|macro|M_MC_CS3
mdefine_line|#define M_MC_CS3                    _SB_MAKEMASK1(7)
multiline_comment|/*&n; * DRAM Mode Register (Table 6-14)&n; */
DECL|macro|S_MC_EMODE
mdefine_line|#define S_MC_EMODE                  0
DECL|macro|M_MC_EMODE
mdefine_line|#define M_MC_EMODE                  _SB_MAKEMASK(15,S_MC_EMODE)
DECL|macro|V_MC_EMODE
mdefine_line|#define V_MC_EMODE(x)               _SB_MAKEVALUE(x,S_MC_EMODE)
DECL|macro|G_MC_EMODE
mdefine_line|#define G_MC_EMODE(x)               _SB_GETVALUE(x,S_MC_EMODE,M_MC_EMODE)
DECL|macro|V_MC_EMODE_DEFAULT
mdefine_line|#define V_MC_EMODE_DEFAULT          V_MC_EMODE(0)
DECL|macro|S_MC_MODE
mdefine_line|#define S_MC_MODE                   16
DECL|macro|M_MC_MODE
mdefine_line|#define M_MC_MODE                   _SB_MAKEMASK(15,S_MC_MODE)
DECL|macro|V_MC_MODE
mdefine_line|#define V_MC_MODE(x)                _SB_MAKEVALUE(x,S_MC_MODE)
DECL|macro|G_MC_MODE
mdefine_line|#define G_MC_MODE(x)                _SB_GETVALUE(x,S_MC_MODE,M_MC_MODE)
DECL|macro|V_MC_MODE_DEFAULT
mdefine_line|#define V_MC_MODE_DEFAULT           V_MC_MODE(0x22)
DECL|macro|S_MC_DRAM_TYPE
mdefine_line|#define S_MC_DRAM_TYPE              32
DECL|macro|M_MC_DRAM_TYPE
mdefine_line|#define M_MC_DRAM_TYPE              _SB_MAKEMASK(3,S_MC_DRAM_TYPE)
DECL|macro|V_MC_DRAM_TYPE
mdefine_line|#define V_MC_DRAM_TYPE(x)           _SB_MAKEVALUE(x,S_MC_DRAM_TYPE)
DECL|macro|G_MC_DRAM_TYPE
mdefine_line|#define G_MC_DRAM_TYPE(x)           _SB_GETVALUE(x,S_MC_DRAM_TYPE,M_MC_DRAM_TYPE)
DECL|macro|K_MC_DRAM_TYPE_JEDEC
mdefine_line|#define K_MC_DRAM_TYPE_JEDEC        0
DECL|macro|K_MC_DRAM_TYPE_FCRAM
mdefine_line|#define K_MC_DRAM_TYPE_FCRAM        1
DECL|macro|K_MC_DRAM_TYPE_SGRAM
mdefine_line|#define K_MC_DRAM_TYPE_SGRAM&t;    2
DECL|macro|V_MC_DRAM_TYPE_JEDEC
mdefine_line|#define V_MC_DRAM_TYPE_JEDEC        V_MC_DRAM_TYPE(K_MC_DRAM_TYPE_JEDEC)
DECL|macro|V_MC_DRAM_TYPE_FCRAM
mdefine_line|#define V_MC_DRAM_TYPE_FCRAM        V_MC_DRAM_TYPE(K_MC_DRAM_TYPE_FCRAM)
DECL|macro|V_MC_DRAM_TYPE_SGRAM
mdefine_line|#define V_MC_DRAM_TYPE_SGRAM        V_MC_DRAM_TYPE(K_MC_DRAM_TYPE_SGRAM)
DECL|macro|M_MC_EXTERNALDECODE
mdefine_line|#define M_MC_EXTERNALDECODE&t;    _SB_MAKEMASK1(35)
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MC_PRE_ON_A8
mdefine_line|#define M_MC_PRE_ON_A8              _SB_MAKEMASK1(36)
DECL|macro|M_MC_RAM_WITH_A13
mdefine_line|#define M_MC_RAM_WITH_A13           _SB_MAKEMASK1(38)
macro_line|#endif /* 112x PASS1 */
multiline_comment|/*&n; * SDRAM Timing Register  (Table 6-15)&n; */
DECL|macro|M_MC_w2rIDLE_TWOCYCLES
mdefine_line|#define M_MC_w2rIDLE_TWOCYCLES&t;  _SB_MAKEMASK1(60)
DECL|macro|M_MC_r2wIDLE_TWOCYCLES
mdefine_line|#define M_MC_r2wIDLE_TWOCYCLES&t;  _SB_MAKEMASK1(61)
DECL|macro|M_MC_r2rIDLE_TWOCYCLES
mdefine_line|#define M_MC_r2rIDLE_TWOCYCLES&t;  _SB_MAKEMASK1(62)
DECL|macro|S_MC_tFIFO
mdefine_line|#define S_MC_tFIFO                56
DECL|macro|M_MC_tFIFO
mdefine_line|#define M_MC_tFIFO                _SB_MAKEMASK(4,S_MC_tFIFO)
DECL|macro|V_MC_tFIFO
mdefine_line|#define V_MC_tFIFO(x)             _SB_MAKEVALUE(x,S_MC_tFIFO)
DECL|macro|G_MC_tFIFO
mdefine_line|#define G_MC_tFIFO(x)             _SB_GETVALUE(x,S_MC_tFIFO,M_MC_tFIFO)
DECL|macro|K_MC_tFIFO_DEFAULT
mdefine_line|#define K_MC_tFIFO_DEFAULT        1
DECL|macro|V_MC_tFIFO_DEFAULT
mdefine_line|#define V_MC_tFIFO_DEFAULT        V_MC_tFIFO(K_MC_tFIFO_DEFAULT)
DECL|macro|S_MC_tRFC
mdefine_line|#define S_MC_tRFC                 52
DECL|macro|M_MC_tRFC
mdefine_line|#define M_MC_tRFC                 _SB_MAKEMASK(4,S_MC_tRFC)
DECL|macro|V_MC_tRFC
mdefine_line|#define V_MC_tRFC(x)              _SB_MAKEVALUE(x,S_MC_tRFC)
DECL|macro|G_MC_tRFC
mdefine_line|#define G_MC_tRFC(x)              _SB_GETVALUE(x,S_MC_tRFC,M_MC_tRFC)
DECL|macro|K_MC_tRFC_DEFAULT
mdefine_line|#define K_MC_tRFC_DEFAULT         12
DECL|macro|V_MC_tRFC_DEFAULT
mdefine_line|#define V_MC_tRFC_DEFAULT         V_MC_tRFC(K_MC_tRFC_DEFAULT)
DECL|macro|S_MC_tCwCr
mdefine_line|#define S_MC_tCwCr                40
DECL|macro|M_MC_tCwCr
mdefine_line|#define M_MC_tCwCr                _SB_MAKEMASK(4,S_MC_tCwCr)
DECL|macro|V_MC_tCwCr
mdefine_line|#define V_MC_tCwCr(x)             _SB_MAKEVALUE(x,S_MC_tCwCr)
DECL|macro|G_MC_tCwCr
mdefine_line|#define G_MC_tCwCr(x)             _SB_GETVALUE(x,S_MC_tCwCr,M_MC_tCwCr)
DECL|macro|K_MC_tCwCr_DEFAULT
mdefine_line|#define K_MC_tCwCr_DEFAULT        4
DECL|macro|V_MC_tCwCr_DEFAULT
mdefine_line|#define V_MC_tCwCr_DEFAULT        V_MC_tCwCr(K_MC_tCwCr_DEFAULT)
DECL|macro|S_MC_tRCr
mdefine_line|#define S_MC_tRCr                 28
DECL|macro|M_MC_tRCr
mdefine_line|#define M_MC_tRCr                 _SB_MAKEMASK(4,S_MC_tRCr)
DECL|macro|V_MC_tRCr
mdefine_line|#define V_MC_tRCr(x)              _SB_MAKEVALUE(x,S_MC_tRCr)
DECL|macro|G_MC_tRCr
mdefine_line|#define G_MC_tRCr(x)              _SB_GETVALUE(x,S_MC_tRCr,M_MC_tRCr)
DECL|macro|K_MC_tRCr_DEFAULT
mdefine_line|#define K_MC_tRCr_DEFAULT         9
DECL|macro|V_MC_tRCr_DEFAULT
mdefine_line|#define V_MC_tRCr_DEFAULT         V_MC_tRCr(K_MC_tRCr_DEFAULT)
DECL|macro|S_MC_tRCw
mdefine_line|#define S_MC_tRCw                 24
DECL|macro|M_MC_tRCw
mdefine_line|#define M_MC_tRCw                 _SB_MAKEMASK(4,S_MC_tRCw)
DECL|macro|V_MC_tRCw
mdefine_line|#define V_MC_tRCw(x)              _SB_MAKEVALUE(x,S_MC_tRCw)
DECL|macro|G_MC_tRCw
mdefine_line|#define G_MC_tRCw(x)              _SB_GETVALUE(x,S_MC_tRCw,M_MC_tRCw)
DECL|macro|K_MC_tRCw_DEFAULT
mdefine_line|#define K_MC_tRCw_DEFAULT         10
DECL|macro|V_MC_tRCw_DEFAULT
mdefine_line|#define V_MC_tRCw_DEFAULT         V_MC_tRCw(K_MC_tRCw_DEFAULT)
DECL|macro|S_MC_tRRD
mdefine_line|#define S_MC_tRRD                 20
DECL|macro|M_MC_tRRD
mdefine_line|#define M_MC_tRRD                 _SB_MAKEMASK(4,S_MC_tRRD)
DECL|macro|V_MC_tRRD
mdefine_line|#define V_MC_tRRD(x)              _SB_MAKEVALUE(x,S_MC_tRRD)
DECL|macro|G_MC_tRRD
mdefine_line|#define G_MC_tRRD(x)              _SB_GETVALUE(x,S_MC_tRRD,M_MC_tRRD)
DECL|macro|K_MC_tRRD_DEFAULT
mdefine_line|#define K_MC_tRRD_DEFAULT         2
DECL|macro|V_MC_tRRD_DEFAULT
mdefine_line|#define V_MC_tRRD_DEFAULT         V_MC_tRRD(K_MC_tRRD_DEFAULT)
DECL|macro|S_MC_tRP
mdefine_line|#define S_MC_tRP                  16
DECL|macro|M_MC_tRP
mdefine_line|#define M_MC_tRP                  _SB_MAKEMASK(4,S_MC_tRP)
DECL|macro|V_MC_tRP
mdefine_line|#define V_MC_tRP(x)               _SB_MAKEVALUE(x,S_MC_tRP)
DECL|macro|G_MC_tRP
mdefine_line|#define G_MC_tRP(x)               _SB_GETVALUE(x,S_MC_tRP,M_MC_tRP)
DECL|macro|K_MC_tRP_DEFAULT
mdefine_line|#define K_MC_tRP_DEFAULT          4
DECL|macro|V_MC_tRP_DEFAULT
mdefine_line|#define V_MC_tRP_DEFAULT          V_MC_tRP(K_MC_tRP_DEFAULT)
DECL|macro|S_MC_tCwD
mdefine_line|#define S_MC_tCwD                 8
DECL|macro|M_MC_tCwD
mdefine_line|#define M_MC_tCwD                 _SB_MAKEMASK(4,S_MC_tCwD)
DECL|macro|V_MC_tCwD
mdefine_line|#define V_MC_tCwD(x)              _SB_MAKEVALUE(x,S_MC_tCwD)
DECL|macro|G_MC_tCwD
mdefine_line|#define G_MC_tCwD(x)              _SB_GETVALUE(x,S_MC_tCwD,M_MC_tCwD)
DECL|macro|K_MC_tCwD_DEFAULT
mdefine_line|#define K_MC_tCwD_DEFAULT         1
DECL|macro|V_MC_tCwD_DEFAULT
mdefine_line|#define V_MC_tCwD_DEFAULT         V_MC_tCwD(K_MC_tCwD_DEFAULT)
DECL|macro|M_tCrDh
mdefine_line|#define M_tCrDh                   _SB_MAKEMASK1(7)
DECL|macro|M_MC_tCrDh
mdefine_line|#define M_MC_tCrDh&t;&t;  M_tCrDh
DECL|macro|S_MC_tCrD
mdefine_line|#define S_MC_tCrD                 4
DECL|macro|M_MC_tCrD
mdefine_line|#define M_MC_tCrD                 _SB_MAKEMASK(3,S_MC_tCrD)
DECL|macro|V_MC_tCrD
mdefine_line|#define V_MC_tCrD(x)              _SB_MAKEVALUE(x,S_MC_tCrD)
DECL|macro|G_MC_tCrD
mdefine_line|#define G_MC_tCrD(x)              _SB_GETVALUE(x,S_MC_tCrD,M_MC_tCrD)
DECL|macro|K_MC_tCrD_DEFAULT
mdefine_line|#define K_MC_tCrD_DEFAULT         2
DECL|macro|V_MC_tCrD_DEFAULT
mdefine_line|#define V_MC_tCrD_DEFAULT         V_MC_tCrD(K_MC_tCrD_DEFAULT)
DECL|macro|S_MC_tRCD
mdefine_line|#define S_MC_tRCD                 0
DECL|macro|M_MC_tRCD
mdefine_line|#define M_MC_tRCD                 _SB_MAKEMASK(4,S_MC_tRCD)
DECL|macro|V_MC_tRCD
mdefine_line|#define V_MC_tRCD(x)              _SB_MAKEVALUE(x,S_MC_tRCD)
DECL|macro|G_MC_tRCD
mdefine_line|#define G_MC_tRCD(x)              _SB_GETVALUE(x,S_MC_tRCD,M_MC_tRCD)
DECL|macro|K_MC_tRCD_DEFAULT
mdefine_line|#define K_MC_tRCD_DEFAULT         3
DECL|macro|V_MC_tRCD_DEFAULT
mdefine_line|#define V_MC_tRCD_DEFAULT         V_MC_tRCD(K_MC_tRCD_DEFAULT)
DECL|macro|V_MC_TIMING_DEFAULT
mdefine_line|#define V_MC_TIMING_DEFAULT     V_MC_tFIFO(K_MC_tFIFO_DEFAULT) | &bslash;&n;                                V_MC_tRFC(K_MC_tRFC_DEFAULT) | &bslash;&n;                                V_MC_tCwCr(K_MC_tCwCr_DEFAULT) | &bslash;&n;                                V_MC_tRCr(K_MC_tRCr_DEFAULT) | &bslash;&n;                                V_MC_tRCw(K_MC_tRCw_DEFAULT) | &bslash;&n;                                V_MC_tRRD(K_MC_tRRD_DEFAULT) | &bslash;&n;                                V_MC_tRP(K_MC_tRP_DEFAULT) | &bslash;&n;                                V_MC_tCwD(K_MC_tCwD_DEFAULT) | &bslash;&n;                                V_MC_tCrD(K_MC_tCrD_DEFAULT) | &bslash;&n;                                V_MC_tRCD(K_MC_tRCD_DEFAULT) | &bslash;&n;                                M_MC_r2rIDLE_TWOCYCLES
multiline_comment|/*&n; * Errata says these are not the default&n; *                               M_MC_w2rIDLE_TWOCYCLES | &bslash;&n; *                               M_MC_r2wIDLE_TWOCYCLES | &bslash;&n; */
multiline_comment|/*&n; * Chip Select Start Address Register (Table 6-17)&n; */
DECL|macro|S_MC_CS0_START
mdefine_line|#define S_MC_CS0_START              0
DECL|macro|M_MC_CS0_START
mdefine_line|#define M_MC_CS0_START              _SB_MAKEMASK(16,S_MC_CS0_START)
DECL|macro|V_MC_CS0_START
mdefine_line|#define V_MC_CS0_START(x)           _SB_MAKEVALUE(x,S_MC_CS0_START)
DECL|macro|G_MC_CS0_START
mdefine_line|#define G_MC_CS0_START(x)           _SB_GETVALUE(x,S_MC_CS0_START,M_MC_CS0_START)
DECL|macro|S_MC_CS1_START
mdefine_line|#define S_MC_CS1_START              16
DECL|macro|M_MC_CS1_START
mdefine_line|#define M_MC_CS1_START              _SB_MAKEMASK(16,S_MC_CS1_START)
DECL|macro|V_MC_CS1_START
mdefine_line|#define V_MC_CS1_START(x)           _SB_MAKEVALUE(x,S_MC_CS1_START)
DECL|macro|G_MC_CS1_START
mdefine_line|#define G_MC_CS1_START(x)           _SB_GETVALUE(x,S_MC_CS1_START,M_MC_CS1_START)
DECL|macro|S_MC_CS2_START
mdefine_line|#define S_MC_CS2_START              32
DECL|macro|M_MC_CS2_START
mdefine_line|#define M_MC_CS2_START              _SB_MAKEMASK(16,S_MC_CS2_START)
DECL|macro|V_MC_CS2_START
mdefine_line|#define V_MC_CS2_START(x)           _SB_MAKEVALUE(x,S_MC_CS2_START)
DECL|macro|G_MC_CS2_START
mdefine_line|#define G_MC_CS2_START(x)           _SB_GETVALUE(x,S_MC_CS2_START,M_MC_CS2_START)
DECL|macro|S_MC_CS3_START
mdefine_line|#define S_MC_CS3_START              48
DECL|macro|M_MC_CS3_START
mdefine_line|#define M_MC_CS3_START              _SB_MAKEMASK(16,S_MC_CS3_START)
DECL|macro|V_MC_CS3_START
mdefine_line|#define V_MC_CS3_START(x)           _SB_MAKEVALUE(x,S_MC_CS3_START)
DECL|macro|G_MC_CS3_START
mdefine_line|#define G_MC_CS3_START(x)           _SB_GETVALUE(x,S_MC_CS3_START,M_MC_CS3_START)
multiline_comment|/*&n; * Chip Select End Address Register (Table 6-18)&n; */
DECL|macro|S_MC_CS0_END
mdefine_line|#define S_MC_CS0_END                0
DECL|macro|M_MC_CS0_END
mdefine_line|#define M_MC_CS0_END                _SB_MAKEMASK(16,S_MC_CS0_END)
DECL|macro|V_MC_CS0_END
mdefine_line|#define V_MC_CS0_END(x)             _SB_MAKEVALUE(x,S_MC_CS0_END)
DECL|macro|G_MC_CS0_END
mdefine_line|#define G_MC_CS0_END(x)             _SB_GETVALUE(x,S_MC_CS0_END,M_MC_CS0_END)
DECL|macro|S_MC_CS1_END
mdefine_line|#define S_MC_CS1_END                16
DECL|macro|M_MC_CS1_END
mdefine_line|#define M_MC_CS1_END                _SB_MAKEMASK(16,S_MC_CS1_END)
DECL|macro|V_MC_CS1_END
mdefine_line|#define V_MC_CS1_END(x)             _SB_MAKEVALUE(x,S_MC_CS1_END)
DECL|macro|G_MC_CS1_END
mdefine_line|#define G_MC_CS1_END(x)             _SB_GETVALUE(x,S_MC_CS1_END,M_MC_CS1_END)
DECL|macro|S_MC_CS2_END
mdefine_line|#define S_MC_CS2_END                32
DECL|macro|M_MC_CS2_END
mdefine_line|#define M_MC_CS2_END                _SB_MAKEMASK(16,S_MC_CS2_END)
DECL|macro|V_MC_CS2_END
mdefine_line|#define V_MC_CS2_END(x)             _SB_MAKEVALUE(x,S_MC_CS2_END)
DECL|macro|G_MC_CS2_END
mdefine_line|#define G_MC_CS2_END(x)             _SB_GETVALUE(x,S_MC_CS2_END,M_MC_CS2_END)
DECL|macro|S_MC_CS3_END
mdefine_line|#define S_MC_CS3_END                48
DECL|macro|M_MC_CS3_END
mdefine_line|#define M_MC_CS3_END                _SB_MAKEMASK(16,S_MC_CS3_END)
DECL|macro|V_MC_CS3_END
mdefine_line|#define V_MC_CS3_END(x)             _SB_MAKEVALUE(x,S_MC_CS3_END)
DECL|macro|G_MC_CS3_END
mdefine_line|#define G_MC_CS3_END(x)             _SB_GETVALUE(x,S_MC_CS3_END,M_MC_CS3_END)
multiline_comment|/*&n; * Chip Select Interleave Register (Table 6-19)&n; */
DECL|macro|S_MC_INTLV_RESERVED
mdefine_line|#define S_MC_INTLV_RESERVED         0
DECL|macro|M_MC_INTLV_RESERVED
mdefine_line|#define M_MC_INTLV_RESERVED         _SB_MAKEMASK(5,S_MC_INTLV_RESERVED)
DECL|macro|S_MC_INTERLEAVE
mdefine_line|#define S_MC_INTERLEAVE             7
DECL|macro|M_MC_INTERLEAVE
mdefine_line|#define M_MC_INTERLEAVE             _SB_MAKEMASK(18,S_MC_INTERLEAVE)
DECL|macro|V_MC_INTERLEAVE
mdefine_line|#define V_MC_INTERLEAVE(x)          _SB_MAKEVALUE(x,S_MC_INTERLEAVE)
DECL|macro|S_MC_INTLV_MBZ
mdefine_line|#define S_MC_INTLV_MBZ              25
DECL|macro|M_MC_INTLV_MBZ
mdefine_line|#define M_MC_INTLV_MBZ              _SB_MAKEMASK(39,S_MC_INTLV_MBZ)
multiline_comment|/*&n; * Row Address Bits Register (Table 6-20)&n; */
DECL|macro|S_MC_RAS_RESERVED
mdefine_line|#define S_MC_RAS_RESERVED           0
DECL|macro|M_MC_RAS_RESERVED
mdefine_line|#define M_MC_RAS_RESERVED           _SB_MAKEMASK(5,S_MC_RAS_RESERVED)
DECL|macro|S_MC_RAS_SELECT
mdefine_line|#define S_MC_RAS_SELECT             12
DECL|macro|M_MC_RAS_SELECT
mdefine_line|#define M_MC_RAS_SELECT             _SB_MAKEMASK(25,S_MC_RAS_SELECT)
DECL|macro|V_MC_RAS_SELECT
mdefine_line|#define V_MC_RAS_SELECT(x)          _SB_MAKEVALUE(x,S_MC_RAS_SELECT)
DECL|macro|S_MC_RAS_MBZ
mdefine_line|#define S_MC_RAS_MBZ                37
DECL|macro|M_MC_RAS_MBZ
mdefine_line|#define M_MC_RAS_MBZ                _SB_MAKEMASK(27,S_MC_RAS_MBZ)
multiline_comment|/*&n; * Column Address Bits Register (Table 6-21)&n; */
DECL|macro|S_MC_CAS_RESERVED
mdefine_line|#define S_MC_CAS_RESERVED           0
DECL|macro|M_MC_CAS_RESERVED
mdefine_line|#define M_MC_CAS_RESERVED           _SB_MAKEMASK(5,S_MC_CAS_RESERVED)
DECL|macro|S_MC_CAS_SELECT
mdefine_line|#define S_MC_CAS_SELECT             5
DECL|macro|M_MC_CAS_SELECT
mdefine_line|#define M_MC_CAS_SELECT             _SB_MAKEMASK(18,S_MC_CAS_SELECT)
DECL|macro|V_MC_CAS_SELECT
mdefine_line|#define V_MC_CAS_SELECT(x)          _SB_MAKEVALUE(x,S_MC_CAS_SELECT)
DECL|macro|S_MC_CAS_MBZ
mdefine_line|#define S_MC_CAS_MBZ                23
DECL|macro|M_MC_CAS_MBZ
mdefine_line|#define M_MC_CAS_MBZ                _SB_MAKEMASK(41,S_MC_CAS_MBZ)
multiline_comment|/*&n; * Bank Address Address Bits Register (Table 6-22)&n; */
DECL|macro|S_MC_BA_RESERVED
mdefine_line|#define S_MC_BA_RESERVED            0
DECL|macro|M_MC_BA_RESERVED
mdefine_line|#define M_MC_BA_RESERVED            _SB_MAKEMASK(5,S_MC_BA_RESERVED)
DECL|macro|S_MC_BA_SELECT
mdefine_line|#define S_MC_BA_SELECT              5
DECL|macro|M_MC_BA_SELECT
mdefine_line|#define M_MC_BA_SELECT              _SB_MAKEMASK(20,S_MC_BA_SELECT)
DECL|macro|V_MC_BA_SELECT
mdefine_line|#define V_MC_BA_SELECT(x)           _SB_MAKEVALUE(x,S_MC_BA_SELECT)
DECL|macro|S_MC_BA_MBZ
mdefine_line|#define S_MC_BA_MBZ                 25
DECL|macro|M_MC_BA_MBZ
mdefine_line|#define M_MC_BA_MBZ                 _SB_MAKEMASK(39,S_MC_BA_MBZ)
multiline_comment|/*&n; * Chip Select Attribute Register (Table 6-23)&n; */
DECL|macro|K_MC_CS_ATTR_CLOSED
mdefine_line|#define K_MC_CS_ATTR_CLOSED         0
DECL|macro|K_MC_CS_ATTR_CASCHECK
mdefine_line|#define K_MC_CS_ATTR_CASCHECK       1
DECL|macro|K_MC_CS_ATTR_HINT
mdefine_line|#define K_MC_CS_ATTR_HINT           2
DECL|macro|K_MC_CS_ATTR_OPEN
mdefine_line|#define K_MC_CS_ATTR_OPEN           3
DECL|macro|S_MC_CS0_PAGE
mdefine_line|#define S_MC_CS0_PAGE               0
DECL|macro|M_MC_CS0_PAGE
mdefine_line|#define M_MC_CS0_PAGE               _SB_MAKEMASK(2,S_MC_CS0_PAGE)
DECL|macro|V_MC_CS0_PAGE
mdefine_line|#define V_MC_CS0_PAGE(x)            _SB_MAKEVALUE(x,S_MC_CS0_PAGE)
DECL|macro|G_MC_CS0_PAGE
mdefine_line|#define G_MC_CS0_PAGE(x)            _SB_GETVALUE(x,S_MC_CS0_PAGE,M_MC_CS0_PAGE)
DECL|macro|S_MC_CS1_PAGE
mdefine_line|#define S_MC_CS1_PAGE               16
DECL|macro|M_MC_CS1_PAGE
mdefine_line|#define M_MC_CS1_PAGE               _SB_MAKEMASK(2,S_MC_CS1_PAGE)
DECL|macro|V_MC_CS1_PAGE
mdefine_line|#define V_MC_CS1_PAGE(x)            _SB_MAKEVALUE(x,S_MC_CS1_PAGE)
DECL|macro|G_MC_CS1_PAGE
mdefine_line|#define G_MC_CS1_PAGE(x)            _SB_GETVALUE(x,S_MC_CS1_PAGE,M_MC_CS1_PAGE)
DECL|macro|S_MC_CS2_PAGE
mdefine_line|#define S_MC_CS2_PAGE               32
DECL|macro|M_MC_CS2_PAGE
mdefine_line|#define M_MC_CS2_PAGE               _SB_MAKEMASK(2,S_MC_CS2_PAGE)
DECL|macro|V_MC_CS2_PAGE
mdefine_line|#define V_MC_CS2_PAGE(x)            _SB_MAKEVALUE(x,S_MC_CS2_PAGE)
DECL|macro|G_MC_CS2_PAGE
mdefine_line|#define G_MC_CS2_PAGE(x)            _SB_GETVALUE(x,S_MC_CS2_PAGE,M_MC_CS2_PAGE)
DECL|macro|S_MC_CS3_PAGE
mdefine_line|#define S_MC_CS3_PAGE               48
DECL|macro|M_MC_CS3_PAGE
mdefine_line|#define M_MC_CS3_PAGE               _SB_MAKEMASK(2,S_MC_CS3_PAGE)
DECL|macro|V_MC_CS3_PAGE
mdefine_line|#define V_MC_CS3_PAGE(x)            _SB_MAKEVALUE(x,S_MC_CS3_PAGE)
DECL|macro|G_MC_CS3_PAGE
mdefine_line|#define G_MC_CS3_PAGE(x)            _SB_GETVALUE(x,S_MC_CS3_PAGE,M_MC_CS3_PAGE)
multiline_comment|/*&n; * ECC Test ECC Register (Table 6-25)&n; */
DECL|macro|S_MC_ECC_INVERT
mdefine_line|#define S_MC_ECC_INVERT             0
DECL|macro|M_MC_ECC_INVERT
mdefine_line|#define M_MC_ECC_INVERT             _SB_MAKEMASK(8,S_MC_ECC_INVERT)
macro_line|#endif
eof
