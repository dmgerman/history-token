multiline_comment|/*&n; *  Interface for hwdep device&n; *&n; *  Copyright (C) 2004 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/hwdep.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;emux_voice.h&quot;
multiline_comment|/*&n; * open the hwdep device&n; */
r_static
r_int
DECL|function|snd_emux_hwdep_open
id|snd_emux_hwdep_open
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * close the device&n; */
r_static
r_int
DECL|function|snd_emux_hwdep_release
id|snd_emux_hwdep_release
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|TMP_CLIENT_ID
mdefine_line|#define TMP_CLIENT_ID&t;0x1001
multiline_comment|/*&n; * load patch&n; */
r_static
r_int
DECL|function|snd_emux_hwdep_load_patch
id|snd_emux_hwdep_load_patch
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_int
id|err
suffix:semicolon
id|soundfont_patch_info_t
id|patch
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|patch
comma
id|arg
comma
r_sizeof
(paren
id|patch
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|patch.type
op_ge
id|SNDRV_SFNT_LOAD_INFO
op_logical_and
id|patch.type
op_le
id|SNDRV_SFNT_PROBE_DATA
)paren
(brace
id|err
op_assign
id|snd_soundfont_load
c_func
(paren
id|emu-&gt;sflist
comma
id|arg
comma
id|patch.len
op_plus
r_sizeof
(paren
id|patch
)paren
comma
id|TMP_CLIENT_ID
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
)brace
r_else
(brace
r_if
c_cond
(paren
id|emu-&gt;ops.load_fx
)paren
r_return
id|emu-&gt;ops
dot
id|load_fx
c_func
(paren
id|emu
comma
id|patch.type
comma
id|patch.optarg
comma
id|arg
comma
id|patch.len
op_plus
r_sizeof
(paren
id|patch
)paren
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * set misc mode&n; */
r_static
r_int
DECL|function|snd_emux_hwdep_misc_mode
id|snd_emux_hwdep_misc_mode
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|sndrv_emux_misc_mode
id|info
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|arg
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|info.mode
OL
l_int|0
op_logical_or
id|info.mode
op_ge
id|EMUX_MD_END
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info.port
OL
l_int|0
)paren
(brace
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
id|emu-&gt;portptrs
(braket
id|i
)braket
op_member_access_from_pointer
id|ctrls
(braket
id|info.mode
)braket
op_assign
id|info.value
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|info.port
OL
id|emu-&gt;num_ports
)paren
id|emu-&gt;portptrs
(braket
id|info.port
)braket
op_member_access_from_pointer
id|ctrls
(braket
id|info.mode
)braket
op_assign
id|info.value
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ioctl&n; */
r_static
r_int
DECL|function|snd_emux_hwdep_ioctl
id|snd_emux_hwdep_ioctl
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|snd_emux_t
op_star
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_t
comma
id|hw-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_EMUX_IOCTL_VERSION
suffix:colon
r_return
id|put_user
c_func
(paren
id|SNDRV_EMUX_VERSION
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDRV_EMUX_IOCTL_LOAD_PATCH
suffix:colon
r_return
id|snd_emux_hwdep_load_patch
c_func
(paren
id|emu
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDRV_EMUX_IOCTL_RESET_SAMPLES
suffix:colon
id|snd_soundfont_remove_samples
c_func
(paren
id|emu-&gt;sflist
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_EMUX_IOCTL_REMOVE_LAST_SAMPLES
suffix:colon
id|snd_soundfont_remove_unlocked
c_func
(paren
id|emu-&gt;sflist
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_EMUX_IOCTL_MEM_AVAIL
suffix:colon
r_if
c_cond
(paren
id|emu-&gt;memhdr
)paren
(brace
r_int
id|size
op_assign
id|snd_util_mem_avail
c_func
(paren
id|emu-&gt;memhdr
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|size
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDRV_EMUX_IOCTL_MISC_MODE
suffix:colon
r_return
id|snd_emux_hwdep_misc_mode
c_func
(paren
id|emu
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * register hwdep device&n; */
r_int
DECL|function|snd_emux_init_hwdep
id|snd_emux_init_hwdep
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
(brace
id|snd_hwdep_t
op_star
id|hw
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_hwdep_new
c_func
(paren
id|emu-&gt;card
comma
id|SNDRV_EMUX_HWDEP_NAME
comma
id|emu-&gt;hwdep_idx
comma
op_amp
id|hw
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|emu-&gt;hwdep
op_assign
id|hw
suffix:semicolon
id|strcpy
c_func
(paren
id|hw-&gt;name
comma
id|SNDRV_EMUX_HWDEP_NAME
)paren
suffix:semicolon
id|hw-&gt;iface
op_assign
id|SNDRV_HWDEP_IFACE_EMUX_WAVETABLE
suffix:semicolon
id|hw-&gt;ops.open
op_assign
id|snd_emux_hwdep_open
suffix:semicolon
id|hw-&gt;ops.release
op_assign
id|snd_emux_hwdep_release
suffix:semicolon
id|hw-&gt;ops.ioctl
op_assign
id|snd_emux_hwdep_ioctl
suffix:semicolon
id|hw-&gt;exclusive
op_assign
l_int|1
suffix:semicolon
id|hw-&gt;private_data
op_assign
id|emu
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|emu-&gt;card
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * unregister&n; */
r_void
DECL|function|snd_emux_delete_hwdep
id|snd_emux_delete_hwdep
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
id|emu-&gt;hwdep
)paren
(brace
id|snd_device_free
c_func
(paren
id|emu-&gt;card
comma
id|emu-&gt;hwdep
)paren
suffix:semicolon
id|emu-&gt;hwdep
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
