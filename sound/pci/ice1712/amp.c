multiline_comment|/*&n; *   ALSA driver for ICEnsemble VT1724 (Envy24HT)&n; *&n; *   Lowlevel functions for Advanced Micro Peripherals Ltd AUDIO2000&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;ice1712.h&quot;
macro_line|#include &quot;amp.h&quot;
DECL|function|snd_vt1724_amp_init
r_static
r_int
id|__devinit
id|snd_vt1724_amp_init
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
multiline_comment|/* only use basic functionality for now */
id|ice-&gt;num_total_dacs
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* only PSDOUT0 is connected */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* entry point */
DECL|variable|__devinitdata
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_amp_cards
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|VT1724_SUBDEVICE_AUDIO2000
comma
l_string|&quot;AMP Ltd AUDIO2000&quot;
comma
id|snd_vt1724_amp_init
comma
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
eof
