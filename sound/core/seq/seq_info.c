multiline_comment|/*&n; *   ALSA sequencer /proc interface&n; *   Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;seq_info.h&quot;
macro_line|#include &quot;seq_clientmgr.h&quot;
macro_line|#include &quot;seq_timer.h&quot;
DECL|variable|queues_entry
r_static
id|snd_info_entry_t
op_star
id|queues_entry
suffix:semicolon
DECL|variable|clients_entry
r_static
id|snd_info_entry_t
op_star
id|clients_entry
suffix:semicolon
DECL|variable|timer_entry
r_static
id|snd_info_entry_t
op_star
id|timer_entry
suffix:semicolon
r_static
id|snd_info_entry_t
op_star
id|__init
DECL|function|create_info_entry
id|create_info_entry
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|size
comma
r_void
(paren
op_star
id|read
)paren
(paren
id|snd_info_entry_t
op_star
comma
id|snd_info_buffer_t
op_star
)paren
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|snd_info_create_module_entry
c_func
(paren
id|THIS_MODULE
comma
id|name
comma
id|snd_seq_root
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
l_int|NULL
suffix:semicolon
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
id|size
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|read
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
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/* create all our /proc entries */
DECL|function|snd_seq_info_init
r_int
id|__init
id|snd_seq_info_init
c_func
(paren
r_void
)paren
(brace
id|queues_entry
op_assign
id|create_info_entry
c_func
(paren
l_string|&quot;queues&quot;
comma
l_int|512
op_plus
(paren
l_int|256
op_star
id|SNDRV_SEQ_MAX_QUEUES
)paren
comma
id|snd_seq_info_queues_read
)paren
suffix:semicolon
id|clients_entry
op_assign
id|create_info_entry
c_func
(paren
l_string|&quot;clients&quot;
comma
l_int|512
op_plus
(paren
l_int|256
op_star
id|SNDRV_SEQ_MAX_CLIENTS
)paren
comma
id|snd_seq_info_clients_read
)paren
suffix:semicolon
id|timer_entry
op_assign
id|create_info_entry
c_func
(paren
l_string|&quot;timer&quot;
comma
l_int|1024
comma
id|snd_seq_info_timer_read
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_info_done
r_int
id|__exit
id|snd_seq_info_done
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|queues_entry
)paren
id|snd_info_unregister
c_func
(paren
id|queues_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clients_entry
)paren
id|snd_info_unregister
c_func
(paren
id|clients_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_entry
)paren
id|snd_info_unregister
c_func
(paren
id|timer_entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
