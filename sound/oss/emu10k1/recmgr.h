multiline_comment|/*     &n; **********************************************************************&n; *     recmgr.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _RECORDMGR_H
DECL|macro|_RECORDMGR_H
mdefine_line|#define _RECORDMGR_H
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;cardwi.h&quot;
multiline_comment|/* Recording resources */
DECL|macro|WAVERECORD_AC97
mdefine_line|#define WAVERECORD_AC97&t;&t;0x01
DECL|macro|WAVERECORD_MIC
mdefine_line|#define WAVERECORD_MIC&t;&t;0x02
DECL|macro|WAVERECORD_FX
mdefine_line|#define WAVERECORD_FX&t;&t;0x03
r_void
id|emu10k1_start_record
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|wavein_buffer
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_stop_record
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|wavein_buffer
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_set_record_src
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|wiinst
op_star
id|wiinst
)paren
suffix:semicolon
macro_line|#endif /* _RECORDMGR_H */
eof
