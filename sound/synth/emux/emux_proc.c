multiline_comment|/*&n; *  Copyright (C) 2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *  Proc interface for Emu8k/Emu10k1 WaveTable synth&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emux_synth.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#include &quot;emux_voice.h&quot;
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_void
DECL|function|snd_emux_proc_info_read
id|snd_emux_proc_info_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buf
)paren
(brace
id|snd_emux_t
op_star
id|emu
suffix:semicolon
r_int
id|i
suffix:semicolon
id|emu
op_assign
id|entry-&gt;private_data
suffix:semicolon
id|down
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;name
)paren
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Device: %s&bslash;n&quot;
comma
id|emu-&gt;name
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Ports: %d&bslash;n&quot;
comma
id|emu-&gt;num_ports
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Addresses:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|emu-&gt;num_ports
suffix:semicolon
id|i
op_increment
)paren
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot; %d:%d&quot;
comma
id|emu-&gt;client
comma
id|emu-&gt;ports
(braket
id|i
)braket
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Use Counter: %d&bslash;n&quot;
comma
id|emu-&gt;used
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Max Voices: %d&bslash;n&quot;
comma
id|emu-&gt;max_voices
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Allocated Voices: %d&bslash;n&quot;
comma
id|emu-&gt;num_voices
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;memhdr
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Memory Size: %d&bslash;n&quot;
comma
id|emu-&gt;memhdr-&gt;size
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Memory Available: %d&bslash;n&quot;
comma
id|snd_util_mem_avail
c_func
(paren
id|emu-&gt;memhdr
)paren
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Allocated Blocks: %d&bslash;n&quot;
comma
id|emu-&gt;memhdr-&gt;nblocks
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Memory Size: 0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|emu-&gt;sflist
)paren
(brace
id|down
c_func
(paren
op_amp
id|emu-&gt;sflist-&gt;presets_mutex
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;SoundFonts: %d&bslash;n&quot;
comma
id|emu-&gt;sflist-&gt;fonts_size
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Instruments: %d&bslash;n&quot;
comma
id|emu-&gt;sflist-&gt;zone_counter
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Samples: %d&bslash;n&quot;
comma
id|emu-&gt;sflist-&gt;sample_counter
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Locked Instruments: %d&bslash;n&quot;
comma
id|emu-&gt;sflist-&gt;zone_locked
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;Locked Samples: %d&bslash;n&quot;
comma
id|emu-&gt;sflist-&gt;sample_locked
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|emu-&gt;sflist-&gt;presets_mutex
)paren
suffix:semicolon
)brace
macro_line|#if 0  /* debug */
r_if
c_cond
(paren
id|emu-&gt;voices
(braket
l_int|0
)braket
dot
id|state
op_ne
id|SNDRV_EMUX_ST_OFF
op_logical_and
id|emu-&gt;voices
(braket
l_int|0
)braket
dot
id|ch
op_ge
l_int|0
)paren
(brace
id|snd_emux_voice_t
op_star
id|vp
op_assign
op_amp
id|emu-&gt;voices
(braket
l_int|0
)braket
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;voice 0: on&bslash;n&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;mod delay=%x, atkhld=%x, dcysus=%x, rel=%x&bslash;n&quot;
comma
id|vp-&gt;reg.parm.moddelay
comma
id|vp-&gt;reg.parm.modatkhld
comma
id|vp-&gt;reg.parm.moddcysus
comma
id|vp-&gt;reg.parm.modrelease
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;vol delay=%x, atkhld=%x, dcysus=%x, rel=%x&bslash;n&quot;
comma
id|vp-&gt;reg.parm.voldelay
comma
id|vp-&gt;reg.parm.volatkhld
comma
id|vp-&gt;reg.parm.voldcysus
comma
id|vp-&gt;reg.parm.volrelease
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;lfo1 delay=%x, lfo2 delay=%x, pefe=%x&bslash;n&quot;
comma
id|vp-&gt;reg.parm.lfo1delay
comma
id|vp-&gt;reg.parm.lfo2delay
comma
id|vp-&gt;reg.parm.pefe
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;fmmod=%x, tremfrq=%x, fm2frq2=%x&bslash;n&quot;
comma
id|vp-&gt;reg.parm.fmmod
comma
id|vp-&gt;reg.parm.tremfrq
comma
id|vp-&gt;reg.parm.fm2frq2
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;cutoff=%x, filterQ=%x, chorus=%x, reverb=%x&bslash;n&quot;
comma
id|vp-&gt;reg.parm.cutoff
comma
id|vp-&gt;reg.parm.filterQ
comma
id|vp-&gt;reg.parm.chorus
comma
id|vp-&gt;reg.parm.reverb
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;avol=%x, acutoff=%x, apitch=%x&bslash;n&quot;
comma
id|vp-&gt;avol
comma
id|vp-&gt;acutoff
comma
id|vp-&gt;apitch
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;apan=%x, aaux=%x, ptarget=%x, vtarget=%x, ftarget=%x&bslash;n&quot;
comma
id|vp-&gt;apan
comma
id|vp-&gt;aaux
comma
id|vp-&gt;ptarget
comma
id|vp-&gt;vtarget
comma
id|vp-&gt;ftarget
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;start=%x, end=%x, loopstart=%x, loopend=%x&bslash;n&quot;
comma
id|vp-&gt;reg.start
comma
id|vp-&gt;reg.end
comma
id|vp-&gt;reg.loopstart
comma
id|vp-&gt;reg.loopend
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;sample_mode=%x, rate=%x&bslash;n&quot;
comma
id|vp-&gt;reg.sample_mode
comma
id|vp-&gt;reg.rate_offset
)paren
suffix:semicolon
)brace
macro_line|#endif
id|up
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
)brace
DECL|function|snd_emux_proc_init
r_void
id|snd_emux_proc_init
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|device
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;wavetableD%d&quot;
comma
id|device
)paren
suffix:semicolon
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|card
comma
id|name
comma
id|card-&gt;proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
l_int|1024
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_emux_proc_info_read
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
r_else
id|emu-&gt;proc
op_assign
id|entry
suffix:semicolon
)brace
DECL|function|snd_emux_proc_free
r_void
id|snd_emux_proc_free
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;proc
)paren
(brace
id|snd_info_unregister
c_func
(paren
id|emu-&gt;proc
)paren
suffix:semicolon
id|emu-&gt;proc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
