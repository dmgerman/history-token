multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.2&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|AC97_SINGLE_VALUE
mdefine_line|#define AC97_SINGLE_VALUE(reg,shift,mask,invert) ((reg) | ((shift) &lt;&lt; 8) | ((mask) &lt;&lt; 16) | ((invert) &lt;&lt; 24))
DECL|macro|AC97_SINGLE
mdefine_line|#define AC97_SINGLE(xname, reg, shift, mask, invert) &bslash;&n;{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_ac97_info_single, &bslash;&n;  .get = snd_ac97_get_single, .put = snd_ac97_put_single, &bslash;&n;  .private_value =  AC97_SINGLE_VALUE(reg, shift, mask, invert) }
multiline_comment|/* ac97_codec.c */
r_extern
r_const
r_char
op_star
id|snd_ac97_stereo_enhancements
(braket
)braket
suffix:semicolon
r_extern
r_const
id|snd_kcontrol_new_t
id|snd_ac97_controls_3d
(braket
)braket
suffix:semicolon
r_extern
r_const
id|snd_kcontrol_new_t
id|snd_ac97_controls_spdif
(braket
)braket
suffix:semicolon
id|snd_kcontrol_t
op_star
id|snd_ac97_cnew
c_func
(paren
r_const
id|snd_kcontrol_new_t
op_star
id|_template
comma
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
r_void
id|snd_ac97_get_name
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|id
comma
r_char
op_star
id|name
comma
r_int
id|modem
)paren
suffix:semicolon
r_int
id|snd_ac97_info_single
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
suffix:semicolon
r_int
id|snd_ac97_get_single
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
r_int
id|snd_ac97_put_single
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
r_int
id|snd_ac97_try_bit
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
id|reg
comma
r_int
id|bit
)paren
suffix:semicolon
r_int
id|snd_ac97_remove_ctl
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|suffix
)paren
suffix:semicolon
r_int
id|snd_ac97_rename_ctl
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_const
r_char
op_star
id|src
comma
r_const
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|suffix
)paren
suffix:semicolon
r_int
id|snd_ac97_swap_ctl
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_const
r_char
op_star
id|s1
comma
r_const
r_char
op_star
id|s2
comma
r_const
r_char
op_star
id|suffix
)paren
suffix:semicolon
r_void
id|snd_ac97_rename_vol_ctl
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_const
r_char
op_star
id|src
comma
r_const
r_char
op_star
id|dst
)paren
suffix:semicolon
multiline_comment|/* ac97_proc.c */
r_void
id|snd_ac97_bus_proc_init
c_func
(paren
id|ac97_bus_t
op_star
id|ac97
)paren
suffix:semicolon
r_void
id|snd_ac97_bus_proc_done
c_func
(paren
id|ac97_bus_t
op_star
id|ac97
)paren
suffix:semicolon
r_void
id|snd_ac97_proc_init
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
r_void
id|snd_ac97_proc_done
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
eof
