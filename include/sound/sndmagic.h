macro_line|#ifndef __SOUND_SNDMAGIC_H
DECL|macro|__SOUND_SNDMAGIC_H
mdefine_line|#define __SOUND_SNDMAGIC_H
multiline_comment|/*&n; *  Magic allocation, deallocation, check&n; *  Copyright (c) 2000 by Abramo Bagnara &lt;abramo@alsa-project.org&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
r_void
op_star
id|_snd_magic_kcalloc
c_func
(paren
r_int
r_int
id|magic
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
op_star
id|_snd_magic_kmalloc
c_func
(paren
r_int
r_int
id|magic
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/**&n; * snd_magic_kmalloc - allocate a record with a magic-prefix&n; * @type: the type to allocate a record (like xxx_t)&n; * @extra: the extra size to allocate in bytes&n; * @flags: the allocation condition (GFP_XXX)&n; *&n; * Allocates a record of the given type with the extra space and&n; * returns its pointer.  The allocated record has a secret magic-key&n; * to be checked via snd_magic_cast() for safe casts.&n; *&n; * The allocated pointer must be released via snd_magic_kfree().&n; *&n; * The &quot;struct xxx&quot; style cannot be used as the type argument&n; * because the magic-key constant is generated from the type-name&n; * string.&n; */
DECL|macro|snd_magic_kmalloc
mdefine_line|#define snd_magic_kmalloc(type, extra, flags) &bslash;&n;&t;(type *) _snd_magic_kmalloc(type##_magic, sizeof(type) + extra, flags)
multiline_comment|/**&n; * snd_magic_kcalloc - allocate a record with a magic-prefix and initialize&n; * @type: the type to allocate a record (like xxx_t)&n; * @extra: the extra size to allocate in bytes&n; * @flags: the allocation condition (GFP_XXX)&n; *&n; * Works like snd_magic_kmalloc() but this clears the area with zero&n; * automatically.&n; */
DECL|macro|snd_magic_kcalloc
mdefine_line|#define snd_magic_kcalloc(type, extra, flags) &bslash;&n;&t;(type *) _snd_magic_kcalloc(type##_magic, sizeof(type) + extra, flags)
multiline_comment|/**&n; * snd_magic_kfree - release the allocated area&n; * @ptr: the pointer allocated via snd_magic_kmalloc() or snd_magic_kcalloc()&n; *&n; * Releases the memory area allocated via snd_magic_kmalloc() or&n; * snd_magic_kcalloc() function.&n; */
r_void
id|snd_magic_kfree
c_func
(paren
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|function|_snd_magic_value
r_static
r_inline
r_int
r_int
id|_snd_magic_value
c_func
(paren
r_void
op_star
id|obj
)paren
(brace
r_return
id|obj
op_eq
l_int|NULL
ques
c_cond
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:colon
op_star
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|obj
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|_snd_magic_bad
r_static
r_inline
r_int
id|_snd_magic_bad
c_func
(paren
r_void
op_star
id|obj
comma
r_int
r_int
id|magic
)paren
(brace
r_return
id|_snd_magic_value
c_func
(paren
id|obj
)paren
op_ne
id|magic
suffix:semicolon
)brace
DECL|macro|snd_magic_cast1
mdefine_line|#define snd_magic_cast1(t, expr, cmd) snd_magic_cast(t, expr, cmd)
multiline_comment|/**&n; * snd_magic_cast - check and cast the magic-allocated pointer&n; * @type: the type of record to cast&n; * @ptr: the magic-allocated pointer&n; * @action...: the action to do if failed&n; *&n; * This macro provides a safe cast for the given type, which was&n; * allocated via snd_magic_kmalloc() or snd_magic_kcallc().&n; * If the pointer is invalid, i.e. the cast-type doesn&squot;t match,&n; * the action arguments are called with a debug message.&n; */
DECL|macro|snd_magic_cast
mdefine_line|#define snd_magic_cast(type, ptr, action...) &bslash;&n;&t;(type *) ({&bslash;&n;&t;void *__ptr = ptr;&bslash;&n;&t;unsigned long __magic = _snd_magic_value(__ptr);&bslash;&n;&t;if (__magic != type##_magic) {&bslash;&n;&t;&t;snd_printk(&quot;bad MAGIC (0x%lx)&bslash;n&quot;, __magic);&bslash;&n;&t;&t;action;&bslash;&n;&t;}&bslash;&n;&t;__ptr;&bslash;&n;})
DECL|macro|snd_device_t_magic
mdefine_line|#define snd_device_t_magic&t;&t;&t;0xa15a00ff
DECL|macro|snd_pcm_t_magic
mdefine_line|#define snd_pcm_t_magic&t;&t;&t;&t;0xa15a0101
DECL|macro|snd_pcm_file_t_magic
mdefine_line|#define snd_pcm_file_t_magic&t;&t;&t;0xa15a0102
DECL|macro|snd_pcm_substream_t_magic
mdefine_line|#define snd_pcm_substream_t_magic&t;&t;0xa15a0103
DECL|macro|snd_pcm_proc_private_t_magic
mdefine_line|#define snd_pcm_proc_private_t_magic&t;&t;0xa15a0104
DECL|macro|snd_pcm_oss_file_t_magic
mdefine_line|#define snd_pcm_oss_file_t_magic&t;&t;0xa15a0105
DECL|macro|snd_mixer_oss_t_magic
mdefine_line|#define snd_mixer_oss_t_magic&t;&t;&t;0xa15a0106
singleline_comment|// #define snd_pcm_sgbuf_t_magic&t;&t;&t;0xa15a0107
DECL|macro|snd_info_private_data_t_magic
mdefine_line|#define snd_info_private_data_t_magic&t;&t;0xa15a0201
DECL|macro|snd_info_entry_t_magic
mdefine_line|#define snd_info_entry_t_magic&t;&t;&t;0xa15a0202
DECL|macro|snd_ctl_file_t_magic
mdefine_line|#define snd_ctl_file_t_magic&t;&t;&t;0xa15a0301
DECL|macro|snd_kcontrol_t_magic
mdefine_line|#define snd_kcontrol_t_magic&t;&t;&t;0xa15a0302
DECL|macro|snd_rawmidi_t_magic
mdefine_line|#define snd_rawmidi_t_magic&t;&t;&t;0xa15a0401
DECL|macro|snd_rawmidi_file_t_magic
mdefine_line|#define snd_rawmidi_file_t_magic&t;&t;0xa15a0402
DECL|macro|snd_virmidi_t_magic
mdefine_line|#define snd_virmidi_t_magic&t;&t;&t;0xa15a0403
DECL|macro|snd_virmidi_dev_t_magic
mdefine_line|#define snd_virmidi_dev_t_magic&t;&t;&t;0xa15a0404
DECL|macro|snd_timer_t_magic
mdefine_line|#define snd_timer_t_magic&t;&t;&t;0xa15a0501
DECL|macro|snd_timer_user_t_magic
mdefine_line|#define snd_timer_user_t_magic&t;&t;&t;0xa15a0502
DECL|macro|snd_hwdep_t_magic
mdefine_line|#define snd_hwdep_t_magic&t;&t;&t;0xa15a0601
DECL|macro|snd_seq_device_t_magic
mdefine_line|#define snd_seq_device_t_magic&t;&t;&t;0xa15a0701
DECL|macro|es18xx_t_magic
mdefine_line|#define es18xx_t_magic&t;&t;&t;&t;0xa15a1101
DECL|macro|trident_t_magic
mdefine_line|#define trident_t_magic&t;&t;&t;&t;0xa15a1201
DECL|macro|es1938_t_magic
mdefine_line|#define es1938_t_magic&t;&t;&t;&t;0xa15a1301
DECL|macro|cs46xx_t_magic
mdefine_line|#define cs46xx_t_magic&t;&t;&t;&t;0xa15a1401
DECL|macro|cs46xx_pcm_t_magic
mdefine_line|#define cs46xx_pcm_t_magic&t;&t;&t;0xa15a1402
DECL|macro|ensoniq_t_magic
mdefine_line|#define ensoniq_t_magic&t;&t;&t;&t;0xa15a1501
DECL|macro|sonicvibes_t_magic
mdefine_line|#define sonicvibes_t_magic&t;&t;&t;0xa15a1601
DECL|macro|mpu401_t_magic
mdefine_line|#define mpu401_t_magic&t;&t;&t;&t;0xa15a1701
DECL|macro|fm801_t_magic
mdefine_line|#define fm801_t_magic&t;&t;&t;&t;0xa15a1801
DECL|macro|ac97_t_magic
mdefine_line|#define ac97_t_magic&t;&t;&t;&t;0xa15a1901
DECL|macro|ak4531_t_magic
mdefine_line|#define ak4531_t_magic&t;&t;&t;&t;0xa15a1a01
DECL|macro|snd_uart16550_t_magic
mdefine_line|#define snd_uart16550_t_magic&t;&t;&t;0xa15a1b01
DECL|macro|emu10k1_t_magic
mdefine_line|#define emu10k1_t_magic&t;&t;&t;&t;0xa15a1c01
DECL|macro|emu10k1_pcm_t_magic
mdefine_line|#define emu10k1_pcm_t_magic&t;&t;&t;0xa15a1c02
DECL|macro|emu10k1_midi_t_magic
mdefine_line|#define emu10k1_midi_t_magic&t;&t;&t;0xa15a1c03
DECL|macro|snd_gus_card_t_magic
mdefine_line|#define snd_gus_card_t_magic&t;&t;&t;0xa15a1d01
DECL|macro|gus_pcm_private_t_magic
mdefine_line|#define gus_pcm_private_t_magic&t;&t;&t;0xa15a1d02
DECL|macro|gus_proc_private_t_magic
mdefine_line|#define gus_proc_private_t_magic&t;&t;0xa15a1d03
DECL|macro|tea6330t_t_magic
mdefine_line|#define tea6330t_t_magic&t;&t;&t;0xa15a1e01
DECL|macro|ad1848_t_magic
mdefine_line|#define ad1848_t_magic&t;&t;&t;&t;0xa15a1f01
DECL|macro|cs4231_t_magic
mdefine_line|#define cs4231_t_magic&t;&t;&t;&t;0xa15a2001
DECL|macro|es1688_t_magic
mdefine_line|#define es1688_t_magic&t;&t;&t;&t;0xa15a2101
DECL|macro|opti93x_t_magic
mdefine_line|#define opti93x_t_magic&t;&t;&t;&t;0xa15a2201
DECL|macro|emu8000_t_magic
mdefine_line|#define emu8000_t_magic&t;&t;&t;&t;0xa15a2301
DECL|macro|emu8000_proc_private_t_magic
mdefine_line|#define emu8000_proc_private_t_magic&t;&t;0xa15a2302
DECL|macro|snd_emux_t_magic
mdefine_line|#define snd_emux_t_magic&t;&t;&t;0xa15a2303
DECL|macro|snd_emux_port_t_magic
mdefine_line|#define snd_emux_port_t_magic&t;&t;&t;0xa15a2304
DECL|macro|sb_t_magic
mdefine_line|#define sb_t_magic&t;&t;&t;&t;0xa15a2401
DECL|macro|snd_sb_csp_t_magic
mdefine_line|#define snd_sb_csp_t_magic&t;&t;&t;0xa15a2402
DECL|macro|snd_card_dummy_t_magic
mdefine_line|#define snd_card_dummy_t_magic&t;&t;&t;0xa15a2501
DECL|macro|snd_card_dummy_pcm_t_magic
mdefine_line|#define snd_card_dummy_pcm_t_magic&t;&t;0xa15a2502
DECL|macro|opl3_t_magic
mdefine_line|#define opl3_t_magic&t;&t;&t;&t;0xa15a2601
DECL|macro|opl4_t_magic
mdefine_line|#define opl4_t_magic&t;&t;&t;&t;0xa15a2602
DECL|macro|snd_seq_dummy_port_t_magic
mdefine_line|#define snd_seq_dummy_port_t_magic&t;&t;0xa15a2701
DECL|macro|ice1712_t_magic
mdefine_line|#define ice1712_t_magic&t;&t;&t;&t;0xa15a2801
DECL|macro|ad1816a_t_magic
mdefine_line|#define ad1816a_t_magic&t;&t;&t;&t;0xa15a2901
DECL|macro|intel8x0_t_magic
mdefine_line|#define intel8x0_t_magic&t;&t;&t;0xa15a2a01
DECL|macro|es1968_t_magic
mdefine_line|#define es1968_t_magic&t;&t;&t;&t;0xa15a2b01
DECL|macro|esschan_t_magic
mdefine_line|#define esschan_t_magic&t;&t;&t;&t;0xa15a2b02
DECL|macro|via82xx_t_magic
mdefine_line|#define via82xx_t_magic&t;&t;&t;&t;0xa15a2c01
DECL|macro|pdplus_t_magic
mdefine_line|#define pdplus_t_magic&t;&t;&t;&t;0xa15a2d01
DECL|macro|cmipci_t_magic
mdefine_line|#define cmipci_t_magic&t;&t;&t;&t;0xa15a2e01
DECL|macro|ymfpci_t_magic
mdefine_line|#define ymfpci_t_magic&t;&t;&t;&t;0xa15a2f01
DECL|macro|ymfpci_pcm_t_magic
mdefine_line|#define ymfpci_pcm_t_magic&t;&t;&t;0xa15a2f02
DECL|macro|cs4281_t_magic
mdefine_line|#define cs4281_t_magic&t;&t;&t;&t;0xa15a3001
DECL|macro|snd_i2c_bus_t_magic
mdefine_line|#define snd_i2c_bus_t_magic&t;&t;&t;0xa15a3101
DECL|macro|snd_i2c_device_t_magic
mdefine_line|#define snd_i2c_device_t_magic&t;&t;&t;0xa15a3102
DECL|macro|cs8427_t_magic
mdefine_line|#define cs8427_t_magic&t;&t;&t;&t;0xa15a3111
DECL|macro|m3_t_magic
mdefine_line|#define m3_t_magic&t;&t;&t;&t;0xa15a3201
DECL|macro|m3_dma_t_magic
mdefine_line|#define m3_dma_t_magic&t;&t;&t;&t;0xa15a3202
DECL|macro|nm256_t_magic
mdefine_line|#define nm256_t_magic&t;&t;&t;&t;0xa15a3301
DECL|macro|nm256_dma_t_magic
mdefine_line|#define nm256_dma_t_magic&t;&t;&t;0xa15a3302
DECL|macro|sam9407_t_magic
mdefine_line|#define sam9407_t_magic&t;&t;&t;&t;0xa15a3401
DECL|macro|pmac_t_magic
mdefine_line|#define pmac_t_magic&t;&t;&t;&t;0xa15a3501
DECL|macro|ali_t_magic
mdefine_line|#define ali_t_magic&t;&t;&t;&t;0xa15a3601
DECL|macro|mtpav_t_magic
mdefine_line|#define mtpav_t_magic&t;&t;&t;&t;0xa15a3701
DECL|macro|mtpav_port_t_magic
mdefine_line|#define mtpav_port_t_magic&t;&t;&t;0xa15a3702
DECL|macro|korg1212_t_magic
mdefine_line|#define korg1212_t_magic&t;&t;&t;0xa15a3800
DECL|macro|opl3sa2_t_magic
mdefine_line|#define opl3sa2_t_magic&t;&t;&t;&t;0xa15a3900
DECL|macro|serialmidi_t_magic
mdefine_line|#define serialmidi_t_magic&t;&t;&t;0xa15a3a00
DECL|macro|sa11xx_uda1341_t_magic
mdefine_line|#define sa11xx_uda1341_t_magic&t;&t;&t;0xa15a3b00
DECL|macro|uda1341_t_magic
mdefine_line|#define uda1341_t_magic                         0xa15a3c00
DECL|macro|l3_client_t_magic
mdefine_line|#define l3_client_t_magic                       0xa15a3d00
DECL|macro|snd_usb_audio_t_magic
mdefine_line|#define snd_usb_audio_t_magic&t;&t;&t;0xa15a3e01
DECL|macro|usb_mixer_elem_info_t_magic
mdefine_line|#define usb_mixer_elem_info_t_magic&t;&t;0xa15a3e02
DECL|macro|snd_usb_stream_t_magic
mdefine_line|#define snd_usb_stream_t_magic&t;&t;&t;0xa15a3e03
DECL|macro|snd_usb_midi_t_magic
mdefine_line|#define snd_usb_midi_t_magic&t;&t;&t;0xa15a3f01
DECL|macro|snd_usb_midi_out_endpoint_t_magic
mdefine_line|#define snd_usb_midi_out_endpoint_t_magic&t;0xa15a3f02
DECL|macro|snd_usb_midi_in_endpoint_t_magic
mdefine_line|#define snd_usb_midi_in_endpoint_t_magic&t;0xa15a3f03
DECL|macro|ak4117_t_magic
mdefine_line|#define ak4117_t_magic&t;&t;&t;&t;0xa15a4000
DECL|macro|psic_t_magic
mdefine_line|#define psic_t_magic&t;&t;&t;&t;0xa15a4100
DECL|macro|vx_core_t_magic
mdefine_line|#define vx_core_t_magic&t;&t;&t;&t;0xa15a4110
DECL|macro|vx_pipe_t_magic
mdefine_line|#define vx_pipe_t_magic&t;&t;&t;&t;0xa15a4112
DECL|macro|azf3328_t_magic
mdefine_line|#define azf3328_t_magic&t;&t;&t;&t;0xa15a4200
macro_line|#else
DECL|macro|snd_magic_kcalloc
mdefine_line|#define snd_magic_kcalloc(type, extra, flags) (type *) snd_kcalloc(sizeof(type) + extra, flags)
DECL|macro|snd_magic_kmalloc
mdefine_line|#define snd_magic_kmalloc(type, extra, flags) (type *) kmalloc(sizeof(type) + extra, flags)
DECL|macro|snd_magic_cast
mdefine_line|#define snd_magic_cast(type, ptr, retval) (type *) ptr
DECL|macro|snd_magic_cast1
mdefine_line|#define snd_magic_cast1(type, ptr, retval) snd_magic_cast(type, ptr, retval)
DECL|macro|snd_magic_kfree
mdefine_line|#define snd_magic_kfree kfree
macro_line|#endif
macro_line|#endif /* __SOUND_SNDMAGIC_H */
eof
