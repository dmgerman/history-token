multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_XDI_DSRV_4_BRI_INC__
DECL|macro|__DIVA_XDI_DSRV_4_BRI_INC__
mdefine_line|#define __DIVA_XDI_DSRV_4_BRI_INC__
multiline_comment|/*&n; * Some special registers in the PLX 9054&n; */
DECL|macro|PLX9054_P2LDBELL
mdefine_line|#define PLX9054_P2LDBELL    0x60
DECL|macro|PLX9054_L2PDBELL
mdefine_line|#define PLX9054_L2PDBELL    0x64
DECL|macro|PLX9054_INTCSR
mdefine_line|#define PLX9054_INTCSR      0x69
DECL|macro|PLX9054_INT_ENABLE
mdefine_line|#define PLX9054_INT_ENABLE  0x09
DECL|macro|PLX9054_SOFT_RESET
mdefine_line|#define PLX9054_SOFT_RESET 0x4000
DECL|macro|PLX9054_RELOAD_EEPROM
mdefine_line|#define PLX9054_RELOAD_EEPROM 0x2000
DECL|macro|DIVA_4BRI_REVISION
mdefine_line|#define DIVA_4BRI_REVISION(__x__) (((__x__)-&gt;cardType == CARDTYPE_DIVASRV_Q_8M_V2_PCI) || ((__x__)-&gt;cardType == CARDTYPE_DIVASRV_VOICE_Q_8M_V2_PCI) || ((__x__)-&gt;cardType == CARDTYPE_DIVASRV_B_2M_V2_PCI) || ((__x__)-&gt;cardType == CARDTYPE_DIVASRV_B_2F_PCI) || ((__x__)-&gt;cardType == CARDTYPE_DIVASRV_VOICE_B_2M_V2_PCI))
r_void
id|diva_os_set_qBri_functions
(paren
id|PISDN_ADAPTER
id|IoAdapter
)paren
suffix:semicolon
r_void
id|diva_os_set_qBri2_functions
(paren
id|PISDN_ADAPTER
id|IoAdapter
)paren
suffix:semicolon
macro_line|#endif
eof
