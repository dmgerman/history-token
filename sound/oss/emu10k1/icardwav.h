multiline_comment|/*     &n; **********************************************************************&n; *     icardwav.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _ICARDWAV_H
DECL|macro|_ICARDWAV_H
mdefine_line|#define _ICARDWAV_H
DECL|struct|wave_format
r_struct
id|wave_format
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|samplingrate
r_int
id|samplingrate
suffix:semicolon
DECL|member|bitsperchannel
id|u8
id|bitsperchannel
suffix:semicolon
DECL|member|channels
id|u8
id|channels
suffix:semicolon
multiline_comment|/* 1 = Mono, 2 = Stereo, 3, ... = Multichannel */
DECL|member|bytesperchannel
id|u8
id|bytesperchannel
suffix:semicolon
DECL|member|bytespervoicesample
id|u8
id|bytespervoicesample
suffix:semicolon
DECL|member|bytespersample
id|u8
id|bytespersample
suffix:semicolon
DECL|member|bytespersec
r_int
id|bytespersec
suffix:semicolon
DECL|member|passthrough
id|u8
id|passthrough
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* emu10k1_wave states */
DECL|macro|WAVE_STATE_OPEN
mdefine_line|#define WAVE_STATE_OPEN&t;&t;0x01&t;
DECL|macro|WAVE_STATE_STARTED
mdefine_line|#define WAVE_STATE_STARTED&t;0x02
DECL|macro|WAVE_STATE_CLOSED
mdefine_line|#define WAVE_STATE_CLOSED&t;0x04
macro_line|#endif /* _ICARDWAV_H */
eof
