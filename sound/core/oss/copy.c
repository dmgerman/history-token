multiline_comment|/*&n; *  Linear conversion Plug-In&n; *  Copyright (c) 2000 by Abramo Bagnara &lt;abramo@alsa-project.org&gt;&n; *&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Library General Public License as&n; *   published by the Free Software Foundation; either version 2 of&n; *   the License, or (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU Library General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Library General Public&n; *   License along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &quot;pcm_plugin.h&quot;
DECL|function|copy_transfer
r_static
id|snd_pcm_sframes_t
id|copy_transfer
c_func
(paren
id|snd_pcm_plugin_t
op_star
id|plugin
comma
r_const
id|snd_pcm_plugin_channel_t
op_star
id|src_channels
comma
id|snd_pcm_plugin_channel_t
op_star
id|dst_channels
comma
id|snd_pcm_uframes_t
id|frames
)paren
(brace
r_int
r_int
id|channel
suffix:semicolon
r_int
r_int
id|nchannels
suffix:semicolon
id|snd_assert
c_func
(paren
id|plugin
op_ne
l_int|NULL
op_logical_and
id|src_channels
op_ne
l_int|NULL
op_logical_and
id|dst_channels
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frames
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|nchannels
op_assign
id|plugin-&gt;src_format.channels
suffix:semicolon
r_for
c_loop
(paren
id|channel
op_assign
l_int|0
suffix:semicolon
id|channel
OL
id|nchannels
suffix:semicolon
id|channel
op_increment
)paren
(brace
id|snd_assert
c_func
(paren
id|src_channels-&gt;area.first
op_mod
l_int|8
op_eq
l_int|0
op_logical_and
id|src_channels-&gt;area.step
op_mod
l_int|8
op_eq
l_int|0
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dst_channels-&gt;area.first
op_mod
l_int|8
op_eq
l_int|0
op_logical_and
id|dst_channels-&gt;area.step
op_mod
l_int|8
op_eq
l_int|0
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|src_channels-&gt;enabled
)paren
(brace
r_if
c_cond
(paren
id|dst_channels-&gt;wanted
)paren
id|snd_pcm_area_silence
c_func
(paren
op_amp
id|dst_channels-&gt;area
comma
l_int|0
comma
id|frames
comma
id|plugin-&gt;dst_format.format
)paren
suffix:semicolon
id|dst_channels-&gt;enabled
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dst_channels-&gt;enabled
op_assign
l_int|1
suffix:semicolon
id|snd_pcm_area_copy
c_func
(paren
op_amp
id|src_channels-&gt;area
comma
l_int|0
comma
op_amp
id|dst_channels-&gt;area
comma
l_int|0
comma
id|frames
comma
id|plugin-&gt;src_format.format
)paren
suffix:semicolon
id|src_channels
op_increment
suffix:semicolon
id|dst_channels
op_increment
suffix:semicolon
)brace
r_return
id|frames
suffix:semicolon
)brace
DECL|function|snd_pcm_plugin_build_copy
r_int
id|snd_pcm_plugin_build_copy
c_func
(paren
id|snd_pcm_plug_t
op_star
id|plug
comma
id|snd_pcm_plugin_format_t
op_star
id|src_format
comma
id|snd_pcm_plugin_format_t
op_star
id|dst_format
comma
id|snd_pcm_plugin_t
op_star
op_star
id|r_plugin
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_pcm_plugin_t
op_star
id|plugin
suffix:semicolon
r_int
id|width
suffix:semicolon
id|snd_assert
c_func
(paren
id|r_plugin
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
op_star
id|r_plugin
op_assign
l_int|NULL
suffix:semicolon
id|snd_assert
c_func
(paren
id|src_format-&gt;format
op_eq
id|dst_format-&gt;format
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|src_format-&gt;rate
op_eq
id|dst_format-&gt;rate
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|src_format-&gt;channels
op_eq
id|dst_format-&gt;channels
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|width
op_assign
id|snd_pcm_format_physical_width
c_func
(paren
id|src_format-&gt;format
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|width
OG
l_int|0
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|err
op_assign
id|snd_pcm_plugin_build
c_func
(paren
id|plug
comma
l_string|&quot;copy&quot;
comma
id|src_format
comma
id|dst_format
comma
l_int|0
comma
op_amp
id|plugin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|plugin-&gt;transfer
op_assign
id|copy_transfer
suffix:semicolon
op_star
id|r_plugin
op_assign
id|plugin
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
