multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|SNDRV_MAIN_OBJECT_FILE
mdefine_line|#define SNDRV_MAIN_OBJECT_FILE
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#ifndef MODULE
DECL|function|alsa_sound_last_init
r_static
r_int
id|__init
id|alsa_sound_last_init
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
comma
id|ok
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ALSA device list:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_CARDS
suffix:semicolon
id|idx
op_increment
)paren
r_if
c_cond
(paren
id|snd_cards
(braket
id|idx
)braket
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  #%i: %s&bslash;n&quot;
comma
id|idx
comma
id|snd_cards
(braket
id|idx
)braket
op_member_access_from_pointer
id|longname
)paren
suffix:semicolon
id|ok
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ok
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;  No soundcards found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_sound_last_init
)paren
macro_line|#endif /* MODULE */
eof