multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for sequencer API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/timer.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;sound/asequencer.h&gt;
macro_line|#include &quot;ioctl32.h&quot;
DECL|variable|seq_mappers
r_struct
id|ioctl32_mapper
id|seq_mappers
(braket
)braket
op_assign
(brace
(brace
id|SNDRV_SEQ_IOCTL_PVERSION
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_CLIENT_ID
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SYSTEM_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_CLIENT_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_DELETE_PORT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_PORT_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_PORT_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_CREATE_QUEUE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_DELETE_QUEUE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_QUEUE_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_QUEUE_INFO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_QUEUE_OWNER
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_QUEUE_OWNER
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_CLIENT_POOL
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_SET_CLIENT_POOL
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_REMOVE_EVENTS
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_QUERY_SUBS
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT
comma
l_int|NULL
)brace
comma
(brace
id|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT
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
