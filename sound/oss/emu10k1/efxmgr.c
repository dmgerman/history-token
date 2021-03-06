multiline_comment|/*&n; **********************************************************************&n; *     efxmgr.c&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;efxmgr.h&quot;
DECL|function|emu10k1_find_control_gpr
r_int
id|emu10k1_find_control_gpr
c_func
(paren
r_struct
id|patch_manager
op_star
id|mgr
comma
r_const
r_char
op_star
id|patch_name
comma
r_const
r_char
op_star
id|gpr_name
)paren
(brace
r_struct
id|dsp_patch
op_star
id|patch
suffix:semicolon
r_struct
id|dsp_rpatch
op_star
id|rpatch
suffix:semicolon
r_char
id|s
(braket
id|PATCH_NAME_SIZE
op_plus
l_int|4
)braket
suffix:semicolon
r_int
r_int
op_star
id|gpr_used
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_find_control_gpr(): %s %s&bslash;n&quot;
comma
id|patch_name
comma
id|gpr_name
)paren
suffix:semicolon
id|rpatch
op_assign
op_amp
id|mgr-&gt;rpatch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rpatch-&gt;name
comma
id|patch_name
)paren
)paren
(brace
id|gpr_used
op_assign
id|rpatch-&gt;gpr_used
suffix:semicolon
r_goto
id|match
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|mgr-&gt;current_pages
op_star
id|PATCHES_PER_PAGE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|patch
op_assign
id|PATCH
c_func
(paren
id|mgr
comma
id|i
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%s&quot;
comma
id|patch-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
id|patch_name
)paren
)paren
(brace
id|gpr_used
op_assign
id|patch-&gt;gpr_used
suffix:semicolon
r_goto
id|match
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
id|match
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_GPRS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mgr-&gt;gpr
(braket
id|i
)braket
dot
id|type
op_eq
id|GPR_TYPE_CONTROL
op_logical_and
id|test_bit
c_func
(paren
id|i
comma
id|gpr_used
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|mgr-&gt;gpr
(braket
id|i
)braket
dot
id|name
comma
id|gpr_name
)paren
)paren
r_return
id|i
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|emu10k1_set_control_gpr
r_void
id|emu10k1_set_control_gpr
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_int
id|addr
comma
id|s32
id|val
comma
r_int
id|flag
)paren
(brace
r_struct
id|patch_manager
op_star
id|mgr
op_assign
op_amp
id|card-&gt;mgr
suffix:semicolon
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_set_control_gpr(): %d %x&bslash;n&quot;
comma
id|addr
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
l_int|0
op_logical_or
id|addr
op_ge
id|NUM_GPRS
)paren
r_return
suffix:semicolon
singleline_comment|//fixme: once patch manager is up, remember to fix this for the audigy
r_if
c_cond
(paren
id|card-&gt;is_audigy
)paren
(brace
id|sblive_writeptr
c_func
(paren
id|card
comma
id|A_GPR_BASE
op_plus
id|addr
comma
l_int|0
comma
id|val
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|flag
)paren
id|val
op_add_assign
id|sblive_readptr
c_func
(paren
id|card
comma
id|GPR_BASE
op_plus
id|addr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
id|mgr-&gt;gpr
(braket
id|addr
)braket
dot
id|max
)paren
id|val
op_assign
id|mgr-&gt;gpr
(braket
id|addr
)braket
dot
id|max
suffix:semicolon
r_else
r_if
c_cond
(paren
id|val
OL
id|mgr-&gt;gpr
(braket
id|addr
)braket
dot
id|min
)paren
id|val
op_assign
id|mgr-&gt;gpr
(braket
id|addr
)braket
dot
id|min
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|GPR_BASE
op_plus
id|addr
comma
l_int|0
comma
id|val
)paren
suffix:semicolon
)brace
)brace
singleline_comment|//TODO: make this configurable:
DECL|macro|VOLCTRL_CHANNEL
mdefine_line|#define VOLCTRL_CHANNEL SOUND_MIXER_VOLUME
DECL|macro|VOLCTRL_STEP_SIZE
mdefine_line|#define VOLCTRL_STEP_SIZE        5
singleline_comment|//An internal function for setting OSS mixer controls.
DECL|function|emu10k1_set_oss_vol
r_static
r_void
id|emu10k1_set_oss_vol
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_int
id|oss_mixer
comma
r_int
r_int
id|left
comma
r_int
r_int
id|right
)paren
(brace
r_extern
r_char
id|volume_params
(braket
id|SOUND_MIXER_NRDEVICES
)braket
suffix:semicolon
id|card-&gt;ac97-&gt;mixer_state
(braket
id|oss_mixer
)braket
op_assign
(paren
id|right
op_lshift
l_int|8
)paren
op_or
id|left
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;is_aps
)paren
id|card-&gt;ac97
op_member_access_from_pointer
id|write_mixer
c_func
(paren
id|card-&gt;ac97
comma
id|oss_mixer
comma
id|left
comma
id|right
)paren
suffix:semicolon
id|emu10k1_set_volume_gpr
c_func
(paren
id|card
comma
id|card-&gt;mgr.ctrl_gpr
(braket
id|oss_mixer
)braket
(braket
l_int|0
)braket
comma
id|left
comma
id|volume_params
(braket
id|oss_mixer
)braket
)paren
suffix:semicolon
id|emu10k1_set_volume_gpr
c_func
(paren
id|card
comma
id|card-&gt;mgr.ctrl_gpr
(braket
id|oss_mixer
)braket
(braket
l_int|1
)braket
comma
id|right
comma
id|volume_params
(braket
id|oss_mixer
)braket
)paren
suffix:semicolon
)brace
singleline_comment|//FIXME: mute should unmute when pressed a second time
DECL|function|emu10k1_mute_irqhandler
r_void
id|emu10k1_mute_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
r_int
id|oss_channel
op_assign
id|VOLCTRL_CHANNEL
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
r_static
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|left
op_assign
id|val
op_amp
l_int|0xff
suffix:semicolon
id|right
op_assign
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|val
op_assign
id|card-&gt;ac97-&gt;mixer_state
(braket
id|oss_channel
)braket
suffix:semicolon
id|left
op_assign
l_int|0
suffix:semicolon
id|right
op_assign
l_int|0
suffix:semicolon
)brace
id|emu10k1_set_oss_vol
c_func
(paren
id|card
comma
id|oss_channel
comma
id|left
comma
id|right
)paren
suffix:semicolon
)brace
DECL|function|emu10k1_volincr_irqhandler
r_void
id|emu10k1_volincr_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
r_int
id|oss_channel
op_assign
id|VOLCTRL_CHANNEL
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
id|left
op_assign
id|card-&gt;ac97-&gt;mixer_state
(braket
id|oss_channel
)braket
op_amp
l_int|0xff
suffix:semicolon
id|right
op_assign
(paren
id|card-&gt;ac97-&gt;mixer_state
(braket
id|oss_channel
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|left
op_add_assign
id|VOLCTRL_STEP_SIZE
)paren
OG
l_int|100
)paren
id|left
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
(paren
id|right
op_add_assign
id|VOLCTRL_STEP_SIZE
)paren
OG
l_int|100
)paren
id|right
op_assign
l_int|100
suffix:semicolon
id|emu10k1_set_oss_vol
c_func
(paren
id|card
comma
id|oss_channel
comma
id|left
comma
id|right
)paren
suffix:semicolon
)brace
DECL|function|emu10k1_voldecr_irqhandler
r_void
id|emu10k1_voldecr_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
r_int
id|oss_channel
op_assign
id|VOLCTRL_CHANNEL
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
id|left
op_assign
id|card-&gt;ac97-&gt;mixer_state
(braket
id|oss_channel
)braket
op_amp
l_int|0xff
suffix:semicolon
id|right
op_assign
(paren
id|card-&gt;ac97-&gt;mixer_state
(braket
id|oss_channel
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|left
op_sub_assign
id|VOLCTRL_STEP_SIZE
)paren
OL
l_int|0
)paren
id|left
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|right
op_sub_assign
id|VOLCTRL_STEP_SIZE
)paren
OL
l_int|0
)paren
id|right
op_assign
l_int|0
suffix:semicolon
id|emu10k1_set_oss_vol
c_func
(paren
id|card
comma
id|oss_channel
comma
id|left
comma
id|right
)paren
suffix:semicolon
)brace
DECL|function|emu10k1_set_volume_gpr
r_void
id|emu10k1_set_volume_gpr
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_int
id|addr
comma
id|s32
id|vol
comma
r_int
id|scale
)paren
(brace
r_struct
id|patch_manager
op_star
id|mgr
op_assign
op_amp
id|card-&gt;mgr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_static
r_const
id|s32
id|log2lin
(braket
l_int|4
)braket
op_assign
initialization_block
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
l_int|0
)paren
r_return
suffix:semicolon
id|vol
op_assign
(paren
l_int|100
op_minus
id|vol
)paren
op_star
id|scale
op_div
l_int|100
suffix:semicolon
singleline_comment|// Thanks to the comp.dsp newsgroup for this neat trick:
id|vol
op_assign
(paren
id|vol
op_ge
id|scale
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|log2lin
(braket
id|vol
op_amp
l_int|3
)braket
op_rshift
(paren
id|vol
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mgr-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|emu10k1_set_control_gpr
c_func
(paren
id|card
comma
id|addr
comma
id|vol
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mgr-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|emu10k1_dsp_irqhandler
r_void
id|emu10k1_dsp_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;pt.state
op_ne
id|PT_STATE_INACTIVE
)paren
(brace
id|u32
id|bc
suffix:semicolon
id|bc
op_assign
id|sblive_readptr
c_func
(paren
id|card
comma
id|GPR_BASE
op_plus
id|card-&gt;pt.intr_gpr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bc
op_ne
l_int|0
)paren
(brace
id|DPD
c_func
(paren
l_int|3
comma
l_string|&quot;pt interrupt, bc = %d&bslash;n&quot;
comma
id|bc
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;pt.lock
comma
id|flags
)paren
suffix:semicolon
id|card-&gt;pt.blocks_played
op_assign
id|bc
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;pt.blocks_played
op_ge
id|card-&gt;pt.blocks_copied
)paren
(brace
id|DPF
c_func
(paren
l_int|1
comma
l_string|&quot;buffer underrun in passthrough playback&bslash;n&quot;
)paren
suffix:semicolon
id|emu10k1_pt_stop
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|card-&gt;pt.wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;pt.lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
eof
