macro_line|#ifndef __EMU8000_LOCAL_H
DECL|macro|__EMU8000_LOCAL_H
mdefine_line|#define __EMU8000_LOCAL_H
multiline_comment|/*&n; *  Local defininitons for the emu8000 (AWE32/64)&n; *&n; *  Copyright (C) 1999 Steve Ratcliffe&n; *  Copyright (C) 1999-2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu8000.h&gt;
macro_line|#include &lt;sound/emu8000_reg.h&gt;
DECL|macro|NELEM
mdefine_line|#define NELEM(arr) (sizeof(arr)/sizeof((arr)[0]))
multiline_comment|/* emu8000_patch.c */
r_int
id|snd_emu8000_sample_new
c_func
(paren
id|snd_emux_t
op_star
id|rec
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_emu8000_sample_free
c_func
(paren
id|snd_emux_t
op_star
id|rec
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
)paren
suffix:semicolon
r_void
id|snd_emu8000_sample_reset
c_func
(paren
id|snd_emux_t
op_star
id|rec
)paren
suffix:semicolon
multiline_comment|/* emu8000_callback.c */
r_void
id|snd_emu8000_ops_setup
c_func
(paren
id|emu8000_t
op_star
id|emu
)paren
suffix:semicolon
multiline_comment|/* emu8000_pcm.c */
r_int
id|snd_emu8000_pcm_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|emu8000_t
op_star
id|emu
comma
r_int
id|index
)paren
suffix:semicolon
macro_line|#endif&t;/* __EMU8000_LOCAL_H */
eof
