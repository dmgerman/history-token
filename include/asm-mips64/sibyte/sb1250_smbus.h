multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  SMBUS Constants                          File: sb1250_smbus.h&n;    *  &n;    *  This module contains constants and macros useful for &n;    *  manipulating the SB1250&squot;s SMbus devices.&n;    *  &n;    *  SB1250 specification level:  01/02/2002&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_SMBUS_H
DECL|macro|_SB1250_SMBUS_H
mdefine_line|#define _SB1250_SMBUS_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*&n; * SMBus Clock Frequency Register (Table 14-2)&n; */
DECL|macro|S_SMB_FREQ_DIV
mdefine_line|#define S_SMB_FREQ_DIV              0
DECL|macro|M_SMB_FREQ_DIV
mdefine_line|#define M_SMB_FREQ_DIV              _SB_MAKEMASK(13,S_SMB_FREQ_DIV)
DECL|macro|V_SMB_FREQ_DIV
mdefine_line|#define V_SMB_FREQ_DIV(x)           _SB_MAKEVALUE(x,S_SMB_FREQ_DIV)
DECL|macro|K_SMB_FREQ_400KHZ
mdefine_line|#define K_SMB_FREQ_400KHZ&t;    0x1F
DECL|macro|K_SMB_FREQ_100KHZ
mdefine_line|#define K_SMB_FREQ_100KHZ&t;    0x7D
DECL|macro|S_SMB_CMD
mdefine_line|#define S_SMB_CMD                   0
DECL|macro|M_SMB_CMD
mdefine_line|#define M_SMB_CMD                   _SB_MAKEMASK(8,S_SMB_CMD)
DECL|macro|V_SMB_CMD
mdefine_line|#define V_SMB_CMD(x)                _SB_MAKEVALUE(x,S_SMB_CMD)
multiline_comment|/*&n; * SMBus control register (Table 14-4)&n; */
DECL|macro|M_SMB_ERR_INTR
mdefine_line|#define M_SMB_ERR_INTR              _SB_MAKEMASK1(0)
DECL|macro|M_SMB_FINISH_INTR
mdefine_line|#define M_SMB_FINISH_INTR           _SB_MAKEMASK1(1)
DECL|macro|M_SMB_DATA_OUT
mdefine_line|#define M_SMB_DATA_OUT              _SB_MAKEMASK1(4)
DECL|macro|M_SMB_DATA_DIR
mdefine_line|#define M_SMB_DATA_DIR              _SB_MAKEMASK1(5)
DECL|macro|M_SMB_DATA_DIR_OUTPUT
mdefine_line|#define M_SMB_DATA_DIR_OUTPUT       M_SMB_DATA_DIR
DECL|macro|M_SMB_CLK_OUT
mdefine_line|#define M_SMB_CLK_OUT               _SB_MAKEMASK1(6)
DECL|macro|M_SMB_DIRECT_ENABLE
mdefine_line|#define M_SMB_DIRECT_ENABLE         _SB_MAKEMASK1(7)
multiline_comment|/*&n; * SMBus status registers (Table 14-5)&n; */
DECL|macro|M_SMB_BUSY
mdefine_line|#define M_SMB_BUSY                  _SB_MAKEMASK1(0)
DECL|macro|M_SMB_ERROR
mdefine_line|#define M_SMB_ERROR                 _SB_MAKEMASK1(1)
DECL|macro|M_SMB_ERROR_TYPE
mdefine_line|#define M_SMB_ERROR_TYPE            _SB_MAKEMASK1(2)
DECL|macro|M_SMB_REF
mdefine_line|#define M_SMB_REF                   _SB_MAKEMASK1(6)
DECL|macro|M_SMB_DATA_IN
mdefine_line|#define M_SMB_DATA_IN               _SB_MAKEMASK1(7)
multiline_comment|/*&n; * SMBus Start/Command registers (Table 14-9)&n; */
DECL|macro|S_SMB_ADDR
mdefine_line|#define S_SMB_ADDR                  0
DECL|macro|M_SMB_ADDR
mdefine_line|#define M_SMB_ADDR                  _SB_MAKEMASK(7,S_SMB_ADDR)
DECL|macro|V_SMB_ADDR
mdefine_line|#define V_SMB_ADDR(x)               _SB_MAKEVALUE(x,S_SMB_ADDR)
DECL|macro|G_SMB_ADDR
mdefine_line|#define G_SMB_ADDR(x)               _SB_GETVALUE(x,S_SMB_ADDR,M_SMB_ADDR)
DECL|macro|M_SMB_QDATA
mdefine_line|#define M_SMB_QDATA                 _SB_MAKEMASK1(7)
DECL|macro|S_SMB_TT
mdefine_line|#define S_SMB_TT                    8
DECL|macro|M_SMB_TT
mdefine_line|#define M_SMB_TT                    _SB_MAKEMASK(3,S_SMB_TT)
DECL|macro|V_SMB_TT
mdefine_line|#define V_SMB_TT(x)                 _SB_MAKEVALUE(x,S_SMB_TT)
DECL|macro|G_SMB_TT
mdefine_line|#define G_SMB_TT(x)                 _SB_GETVALUE(x,S_SMB_TT,M_SMB_TT)
DECL|macro|K_SMB_TT_WR1BYTE
mdefine_line|#define K_SMB_TT_WR1BYTE            0
DECL|macro|K_SMB_TT_WR2BYTE
mdefine_line|#define K_SMB_TT_WR2BYTE            1
DECL|macro|K_SMB_TT_WR3BYTE
mdefine_line|#define K_SMB_TT_WR3BYTE            2
DECL|macro|K_SMB_TT_CMD_RD1BYTE
mdefine_line|#define K_SMB_TT_CMD_RD1BYTE        3
DECL|macro|K_SMB_TT_CMD_RD2BYTE
mdefine_line|#define K_SMB_TT_CMD_RD2BYTE        4
DECL|macro|K_SMB_TT_RD1BYTE
mdefine_line|#define K_SMB_TT_RD1BYTE            5
DECL|macro|K_SMB_TT_QUICKCMD
mdefine_line|#define K_SMB_TT_QUICKCMD           6
DECL|macro|K_SMB_TT_EEPROMREAD
mdefine_line|#define K_SMB_TT_EEPROMREAD         7
DECL|macro|V_SMB_TT_WR1BYTE
mdefine_line|#define V_SMB_TT_WR1BYTE&t;    V_SMB_TT(K_SMB_TT_WR1BYTE)
DECL|macro|V_SMB_TT_WR2BYTE
mdefine_line|#define V_SMB_TT_WR2BYTE&t;    V_SMB_TT(K_SMB_TT_WR2BYTE)
DECL|macro|V_SMB_TT_WR3BYTE
mdefine_line|#define V_SMB_TT_WR3BYTE&t;    V_SMB_TT(K_SMB_TT_WR3BYTE)
DECL|macro|V_SMB_TT_CMD_RD1BYTE
mdefine_line|#define V_SMB_TT_CMD_RD1BYTE&t;    V_SMB_TT(K_SMB_TT_CMD_RD1BYTE)
DECL|macro|V_SMB_TT_CMD_RD2BYTE
mdefine_line|#define V_SMB_TT_CMD_RD2BYTE&t;    V_SMB_TT(K_SMB_TT_CMD_RD2BYTE)
DECL|macro|V_SMB_TT_RD1BYTE
mdefine_line|#define V_SMB_TT_RD1BYTE&t;    V_SMB_TT(K_SMB_TT_RD1BYTE)
DECL|macro|V_SMB_TT_QUICKCMD
mdefine_line|#define V_SMB_TT_QUICKCMD&t;    V_SMB_TT(K_SMB_TT_QUICKCMD)
DECL|macro|V_SMB_TT_EEPROMREAD
mdefine_line|#define V_SMB_TT_EEPROMREAD&t;    V_SMB_TT(K_SMB_TT_EEPROMREAD)
DECL|macro|M_SMB_PEC
mdefine_line|#define M_SMB_PEC                   _SB_MAKEMASK1(15)
multiline_comment|/*&n; * SMBus Data Register (Table 14-6) and SMBus Extra Register (Table 14-7)&n; */
DECL|macro|S_SMB_LB
mdefine_line|#define S_SMB_LB                    0
DECL|macro|M_SMB_LB
mdefine_line|#define M_SMB_LB                    _SB_MAKEMASK(8,S_SMB_LB)
DECL|macro|V_SMB_LB
mdefine_line|#define V_SMB_LB(x)                 _SB_MAKEVALUE(x,S_SMB_LB)
DECL|macro|S_SMB_MB
mdefine_line|#define S_SMB_MB                    8
DECL|macro|M_SMB_MB
mdefine_line|#define M_SMB_MB                    _SB_MAKEMASK(8,S_SMB_MB)
DECL|macro|V_SMB_MB
mdefine_line|#define V_SMB_MB(x)                 _SB_MAKEVALUE(x,S_SMB_MB)
multiline_comment|/*&n; * SMBus Packet Error Check register (Table 14-8)&n; */
DECL|macro|S_SPEC_PEC
mdefine_line|#define S_SPEC_PEC                  0
DECL|macro|M_SPEC_PEC
mdefine_line|#define M_SPEC_PEC                  _SB_MAKEMASK(8,S_SPEC_PEC)
DECL|macro|V_SPEC_MB
mdefine_line|#define V_SPEC_MB(x)                _SB_MAKEVALUE(x,S_SPEC_PEC)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_SMB_CMDH
mdefine_line|#define S_SMB_CMDH                  8
DECL|macro|M_SMB_CMDH
mdefine_line|#define M_SMB_CMDH                  _SB_MAKEMASK(8,S_SMBH_CMD)
DECL|macro|V_SMB_CMDH
mdefine_line|#define V_SMB_CMDH(x)               _SB_MAKEVALUE(x,S_SMBH_CMD)
DECL|macro|M_SMB_EXTEND
mdefine_line|#define M_SMB_EXTEND&t;&t;    _SB_MAKEMASK1(14)
DECL|macro|M_SMB_DIR
mdefine_line|#define M_SMB_DIR&t;&t;    _SB_MAKEMASK1(13)
DECL|macro|S_SMB_DFMT
mdefine_line|#define S_SMB_DFMT                  8
DECL|macro|M_SMB_DFMT
mdefine_line|#define M_SMB_DFMT                  _SB_MAKEMASK(3,S_SMB_DFMT)
DECL|macro|V_SMB_DFMT
mdefine_line|#define V_SMB_DFMT(x)               _SB_MAKEVALUE(x,S_SMB_DFMT)
DECL|macro|G_SMB_DFMT
mdefine_line|#define G_SMB_DFMT(x)               _SB_GETVALUE(x,S_SMB_DFMT,M_SMB_DFMT)
DECL|macro|K_SMB_DFMT_1BYTE
mdefine_line|#define K_SMB_DFMT_1BYTE            0
DECL|macro|K_SMB_DFMT_2BYTE
mdefine_line|#define K_SMB_DFMT_2BYTE            1
DECL|macro|K_SMB_DFMT_3BYTE
mdefine_line|#define K_SMB_DFMT_3BYTE            2
DECL|macro|K_SMB_DFMT_4BYTE
mdefine_line|#define K_SMB_DFMT_4BYTE            3
DECL|macro|K_SMB_DFMT_NODATA
mdefine_line|#define K_SMB_DFMT_NODATA           4
DECL|macro|K_SMB_DFMT_CMD4BYTE
mdefine_line|#define K_SMB_DFMT_CMD4BYTE         5
DECL|macro|K_SMB_DFMT_CMD5BYTE
mdefine_line|#define K_SMB_DFMT_CMD5BYTE         6
DECL|macro|K_SMB_DFMT_RESERVED
mdefine_line|#define K_SMB_DFMT_RESERVED         7
DECL|macro|V_SMB_DFMT_1BYTE
mdefine_line|#define V_SMB_DFMT_1BYTE&t;    V_SMB_DFMT(K_SMB_DFMT_1BYTE)
DECL|macro|V_SMB_DFMT_2BYTE
mdefine_line|#define V_SMB_DFMT_2BYTE&t;    V_SMB_DFMT(K_SMB_DFMT_2BYTE)
DECL|macro|V_SMB_DFMT_3BYTE
mdefine_line|#define V_SMB_DFMT_3BYTE&t;    V_SMB_DFMT(K_SMB_DFMT_3BYTE)
DECL|macro|V_SMB_DFMT_4BYTE
mdefine_line|#define V_SMB_DFMT_4BYTE&t;    V_SMB_DFMT(K_SMB_DFMT_4BYTE)
DECL|macro|V_SMB_DFMT_NODATA
mdefine_line|#define V_SMB_DFMT_NODATA&t;    V_SMB_DFMT(K_SMB_DFMT_NODATA)
DECL|macro|V_SMB_DFMT_CMD4BYTE
mdefine_line|#define V_SMB_DFMT_CMD4BYTE&t;    V_SMB_DFMT(K_SMB_DFMT_CMD4BYTE)
DECL|macro|V_SMB_DFMT_CMD5BYTE
mdefine_line|#define V_SMB_DFMT_CMD5BYTE&t;    V_SMB_DFMT(K_SMB_DFMT_CMD5BYTE)
DECL|macro|V_SMB_DFMT_RESERVED
mdefine_line|#define V_SMB_DFMT_RESERVED&t;    V_SMB_DFMT(K_SMB_DFMT_RESERVED)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
macro_line|#endif
eof
