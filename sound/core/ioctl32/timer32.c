multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for timer API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/timer.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ioctl32.h&quot;
DECL|struct|sndrv_timer_info32
r_struct
id|sndrv_timer_info32
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|card
id|s32
id|card
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|name
r_int
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|ticks
id|u32
id|ticks
suffix:semicolon
DECL|member|resolution
id|u32
id|resolution
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CVT_sndrv_timer_info
mdefine_line|#define CVT_sndrv_timer_info()&bslash;&n;{&bslash;&n;&t;COPY(flags);&bslash;&n;&t;COPY(card);&bslash;&n;&t;memcpy(dst-&gt;id, src-&gt;id, sizeof(src-&gt;id));&bslash;&n;&t;memcpy(dst-&gt;name, src-&gt;name, sizeof(src-&gt;name));&bslash;&n;&t;COPY(ticks);&bslash;&n;&t;COPY(resolution);&bslash;&n;}
DECL|struct|timeval32
r_struct
id|timeval32
(brace
DECL|member|tv_sec
id|s32
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|s32
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_timer_status32
r_struct
id|sndrv_timer_status32
(brace
DECL|member|tstamp
r_struct
id|timeval32
id|tstamp
suffix:semicolon
DECL|member|resolution
id|u32
id|resolution
suffix:semicolon
DECL|member|lost
id|u32
id|lost
suffix:semicolon
DECL|member|overrun
id|u32
id|overrun
suffix:semicolon
DECL|member|queue
id|u32
id|queue
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CVT_sndrv_timer_status
mdefine_line|#define CVT_sndrv_timer_status()&bslash;&n;{&bslash;&n;&t;COPY(tstamp.tv_sec);&bslash;&n;&t;COPY(tstamp.tv_usec);&bslash;&n;&t;COPY(resolution);&bslash;&n;&t;COPY(lost);&bslash;&n;&t;COPY(overrun);&bslash;&n;&t;COPY(queue);&bslash;&n;}
DECL|variable|timer_info
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|timer_info
)paren
suffix:semicolon
DECL|variable|timer_status
id|DEFINE_ALSA_IOCTL
c_func
(paren
id|timer_status
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|macro|AP
mdefine_line|#define AP(x) snd_ioctl32_##x
DECL|variable|timer_mappers
r_struct
id|ioctl32_mapper
id|timer_mappers
(braket
)braket
op_assign
(brace
(brace
id|SNDRV_TIMER_IOCTL_PVERSION
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_NEXT_DEVICE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_SELECT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_INFO
comma
id|AP
c_func
(paren
id|timer_info
)paren
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_PARAMS
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_STATUS
comma
id|AP
c_func
(paren
id|timer_status
)paren
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_START
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_STOP
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_TIMER_IOCTL_CONTINUE
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
