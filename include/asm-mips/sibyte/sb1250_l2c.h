multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  L2 Cache constants and macros&t;&t;File: sb1250_l2c.h&n;    *  &n;    *  This module contains constants useful for manipulating the&n;    *  level 2 cache.&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_L2C_H
DECL|macro|_SB1250_L2C_H
mdefine_line|#define _SB1250_L2C_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*&n; * Level 2 Cache Tag register (Table 5-3)&n; */
DECL|macro|S_L2C_TAG_MBZ
mdefine_line|#define S_L2C_TAG_MBZ               0
DECL|macro|M_L2C_TAG_MBZ
mdefine_line|#define M_L2C_TAG_MBZ               _SB_MAKEMASK(5,S_L2C_TAG_MBZ)
DECL|macro|S_L2C_TAG_INDEX
mdefine_line|#define S_L2C_TAG_INDEX             5
DECL|macro|M_L2C_TAG_INDEX
mdefine_line|#define M_L2C_TAG_INDEX             _SB_MAKEMASK(12,S_L2C_TAG_INDEX)
DECL|macro|V_L2C_TAG_INDEX
mdefine_line|#define V_L2C_TAG_INDEX(x)          _SB_MAKEVALUE(x,S_L2C_TAG_INDEX)
DECL|macro|G_L2C_TAG_INDEX
mdefine_line|#define G_L2C_TAG_INDEX(x)          _SB_GETVALUE(x,S_L2C_TAG_INDEX,M_L2C_TAG_INDEX)
DECL|macro|S_L2C_TAG_TAG
mdefine_line|#define S_L2C_TAG_TAG               17
DECL|macro|M_L2C_TAG_TAG
mdefine_line|#define M_L2C_TAG_TAG               _SB_MAKEMASK(23,S_L2C_TAG_TAG)
DECL|macro|V_L2C_TAG_TAG
mdefine_line|#define V_L2C_TAG_TAG(x)            _SB_MAKEVALUE(x,S_L2C_TAG_TAG)
DECL|macro|G_L2C_TAG_TAG
mdefine_line|#define G_L2C_TAG_TAG(x)            _SB_GETVALUE(x,S_L2C_TAG_TAG,M_L2C_TAG_TAG)
DECL|macro|S_L2C_TAG_ECC
mdefine_line|#define S_L2C_TAG_ECC               40
DECL|macro|M_L2C_TAG_ECC
mdefine_line|#define M_L2C_TAG_ECC               _SB_MAKEMASK(6,S_L2C_TAG_ECC)
DECL|macro|V_L2C_TAG_ECC
mdefine_line|#define V_L2C_TAG_ECC(x)            _SB_MAKEVALUE(x,S_L2C_TAG_ECC)
DECL|macro|G_L2C_TAG_ECC
mdefine_line|#define G_L2C_TAG_ECC(x)            _SB_GETVALUE(x,S_L2C_TAG_ECC,M_L2C_TAG_ECC)
DECL|macro|S_L2C_TAG_WAY
mdefine_line|#define S_L2C_TAG_WAY               46
DECL|macro|M_L2C_TAG_WAY
mdefine_line|#define M_L2C_TAG_WAY               _SB_MAKEMASK(2,S_L2C_TAG_WAY)
DECL|macro|V_L2C_TAG_WAY
mdefine_line|#define V_L2C_TAG_WAY(x)            _SB_MAKEVALUE(x,S_L2C_TAG_WAY)
DECL|macro|G_L2C_TAG_WAY
mdefine_line|#define G_L2C_TAG_WAY(x)            _SB_GETVALUE(x,S_L2C_TAG_WAY,M_L2C_TAG_WAY)
DECL|macro|M_L2C_TAG_DIRTY
mdefine_line|#define M_L2C_TAG_DIRTY             _SB_MAKEMASK1(48)
DECL|macro|M_L2C_TAG_VALID
mdefine_line|#define M_L2C_TAG_VALID             _SB_MAKEMASK1(49)
multiline_comment|/*&n; * Format of level 2 cache management address (table 5-2)&n; */
DECL|macro|S_L2C_MGMT_INDEX
mdefine_line|#define S_L2C_MGMT_INDEX            5
DECL|macro|M_L2C_MGMT_INDEX
mdefine_line|#define M_L2C_MGMT_INDEX            _SB_MAKEMASK(12,S_L2C_MGMT_INDEX)
DECL|macro|V_L2C_MGMT_INDEX
mdefine_line|#define V_L2C_MGMT_INDEX(x)         _SB_MAKEVALUE(x,S_L2C_MGMT_INDEX)
DECL|macro|G_L2C_MGMT_INDEX
mdefine_line|#define G_L2C_MGMT_INDEX(x)         _SB_GETVALUE(x,S_L2C_MGMT_INDEX,M_L2C_MGMT_INDEX)
DECL|macro|S_L2C_MGMT_QUADRANT
mdefine_line|#define S_L2C_MGMT_QUADRANT         15
DECL|macro|M_L2C_MGMT_QUADRANT
mdefine_line|#define M_L2C_MGMT_QUADRANT         _SB_MAKEMASK(2,S_L2C_MGMT_QUADRANT)
DECL|macro|V_L2C_MGMT_QUADRANT
mdefine_line|#define V_L2C_MGMT_QUADRANT(x)      _SB_MAKEVALUE(x,S_L2C_MGMT_QUADRANT)
DECL|macro|G_L2C_MGMT_QUADRANT
mdefine_line|#define G_L2C_MGMT_QUADRANT(x)      _SB_GETVALUE(x,S_L2C_MGMT_QUADRANT,M_L2C_MGMT_QUADRANT)
DECL|macro|S_L2C_MGMT_HALF
mdefine_line|#define S_L2C_MGMT_HALF&t;&t;    16
DECL|macro|M_L2C_MGMT_HALF
mdefine_line|#define M_L2C_MGMT_HALF&t;            _SB_MAKEMASK(1,S_L2C_MGMT_HALF)
DECL|macro|S_L2C_MGMT_WAY
mdefine_line|#define S_L2C_MGMT_WAY              17
DECL|macro|M_L2C_MGMT_WAY
mdefine_line|#define M_L2C_MGMT_WAY              _SB_MAKEMASK(2,S_L2C_MGMT_WAY)
DECL|macro|V_L2C_MGMT_WAY
mdefine_line|#define V_L2C_MGMT_WAY(x)           _SB_MAKEVALUE(x,S_L2C_MGMT_WAY)
DECL|macro|G_L2C_MGMT_WAY
mdefine_line|#define G_L2C_MGMT_WAY(x)           _SB_GETVALUE(x,S_L2C_MGMT_WAY,M_L2C_MGMT_WAY)
DECL|macro|S_L2C_MGMT_TAG
mdefine_line|#define S_L2C_MGMT_TAG              21
DECL|macro|M_L2C_MGMT_TAG
mdefine_line|#define M_L2C_MGMT_TAG              _SB_MAKEMASK(6,S_L2C_MGMT_TAG)
DECL|macro|V_L2C_MGMT_TAG
mdefine_line|#define V_L2C_MGMT_TAG(x)           _SB_MAKEVALUE(x,S_L2C_MGMT_TAG)
DECL|macro|G_L2C_MGMT_TAG
mdefine_line|#define G_L2C_MGMT_TAG(x)           _SB_GETVALUE(x,S_L2C_MGMT_TAG,M_L2C_MGMT_TAG)
DECL|macro|M_L2C_MGMT_DIRTY
mdefine_line|#define M_L2C_MGMT_DIRTY            _SB_MAKEMASK1(19)
DECL|macro|M_L2C_MGMT_VALID
mdefine_line|#define M_L2C_MGMT_VALID            _SB_MAKEMASK1(20)
DECL|macro|A_L2C_MGMT_TAG_BASE
mdefine_line|#define A_L2C_MGMT_TAG_BASE         0x00D0000000
DECL|macro|L2C_ENTRIES_PER_WAY
mdefine_line|#define L2C_ENTRIES_PER_WAY       4096
DECL|macro|L2C_NUM_WAYS
mdefine_line|#define L2C_NUM_WAYS              4
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
multiline_comment|/*&n; * L2 Read Misc. register (A_L2_READ_MISC)&n; */
DECL|macro|S_L2C_MISC_NO_WAY
mdefine_line|#define S_L2C_MISC_NO_WAY&t;&t;10
DECL|macro|M_L2C_MISC_NO_WAY
mdefine_line|#define M_L2C_MISC_NO_WAY&t;&t;_SB_MAKEMASK(4,S_L2C_MISC_NO_WAY)
DECL|macro|V_L2C_MISC_NO_WAY
mdefine_line|#define V_L2C_MISC_NO_WAY(x)&t;&t;_SB_MAKEVALUE(x,S_L2C_MISC_NO_WAY)
DECL|macro|G_L2C_MISC_NO_WAY
mdefine_line|#define G_L2C_MISC_NO_WAY(x)&t;&t;_SB_GETVALUE(x,S_L2C_MISC_NO_WAY,M_L2C_MISC_NO_WAY)
DECL|macro|M_L2C_MISC_ECC_CLEANUP_DIS
mdefine_line|#define M_L2C_MISC_ECC_CLEANUP_DIS&t;_SB_MAKEMASK1(9)
DECL|macro|M_L2C_MISC_MC_PRIO_LOW
mdefine_line|#define M_L2C_MISC_MC_PRIO_LOW&t;&t;_SB_MAKEMASK1(8)
DECL|macro|M_L2C_MISC_SOFT_DISABLE_T
mdefine_line|#define M_L2C_MISC_SOFT_DISABLE_T&t;_SB_MAKEMASK1(7)
DECL|macro|M_L2C_MISC_SOFT_DISABLE_B
mdefine_line|#define M_L2C_MISC_SOFT_DISABLE_B&t;_SB_MAKEMASK1(6)
DECL|macro|M_L2C_MISC_SOFT_DISABLE_R
mdefine_line|#define M_L2C_MISC_SOFT_DISABLE_R&t;_SB_MAKEMASK1(5)
DECL|macro|M_L2C_MISC_SOFT_DISABLE_L
mdefine_line|#define M_L2C_MISC_SOFT_DISABLE_L&t;_SB_MAKEMASK1(4)
DECL|macro|M_L2C_MISC_SCACHE_DISABLE_T
mdefine_line|#define M_L2C_MISC_SCACHE_DISABLE_T&t;_SB_MAKEMASK1(3)
DECL|macro|M_L2C_MISC_SCACHE_DISABLE_B
mdefine_line|#define M_L2C_MISC_SCACHE_DISABLE_B&t;_SB_MAKEMASK1(2)
DECL|macro|M_L2C_MISC_SCACHE_DISABLE_R
mdefine_line|#define M_L2C_MISC_SCACHE_DISABLE_R&t;_SB_MAKEMASK1(1)
DECL|macro|M_L2C_MISC_SCACHE_DISABLE_L
mdefine_line|#define M_L2C_MISC_SCACHE_DISABLE_L&t;_SB_MAKEMASK1(0)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
macro_line|#endif
eof
