multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for timer API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/timer.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ioctl32.h&quot;
DECL|macro|AP
mdefine_line|#define AP(x) snd_ioctl32_##x
DECL|variable|hwdep_mappers
r_struct
id|ioctl32_mapper
id|hwdep_mappers
(braket
)braket
op_assign
(brace
(brace
id|SNDRV_HWDEP_IOCTL_PVERSION
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_HWDEP_IOCTL_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_HWDEP_INFO
comma
l_int|NULL
)brace
comma
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
eof
