macro_line|#ifndef __SOUND_AK4531_CODEC_H
DECL|macro|__SOUND_AK4531_CODEC_H
mdefine_line|#define __SOUND_AK4531_CODEC_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.1&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;info.h&quot;
macro_line|#include &quot;control.h&quot;
multiline_comment|/*&n; *  ASAHI KASEI - AK4531 codec&n; *  - not really AC&squot;97 codec, but it uses very similar interface as AC&squot;97&n; */
multiline_comment|/*&n; *  AK4531 codec registers&n; */
DECL|macro|AK4531_LMASTER
mdefine_line|#define AK4531_LMASTER  0x00&t;/* master volume left */
DECL|macro|AK4531_RMASTER
mdefine_line|#define AK4531_RMASTER  0x01&t;/* master volume right */
DECL|macro|AK4531_LVOICE
mdefine_line|#define AK4531_LVOICE   0x02&t;/* channel volume left */
DECL|macro|AK4531_RVOICE
mdefine_line|#define AK4531_RVOICE   0x03&t;/* channel volume right */
DECL|macro|AK4531_LFM
mdefine_line|#define AK4531_LFM      0x04&t;/* FM volume left */
DECL|macro|AK4531_RFM
mdefine_line|#define AK4531_RFM      0x05&t;/* FM volume right */
DECL|macro|AK4531_LCD
mdefine_line|#define AK4531_LCD      0x06&t;/* CD volume left */
DECL|macro|AK4531_RCD
mdefine_line|#define AK4531_RCD      0x07&t;/* CD volume right */
DECL|macro|AK4531_LLINE
mdefine_line|#define AK4531_LLINE    0x08&t;/* LINE volume left */
DECL|macro|AK4531_RLINE
mdefine_line|#define AK4531_RLINE    0x09&t;/* LINE volume right */
DECL|macro|AK4531_LAUXA
mdefine_line|#define AK4531_LAUXA    0x0a&t;/* AUXA volume left */
DECL|macro|AK4531_RAUXA
mdefine_line|#define AK4531_RAUXA    0x0b&t;/* AUXA volume right */
DECL|macro|AK4531_MONO1
mdefine_line|#define AK4531_MONO1    0x0c&t;/* MONO1 volume left */
DECL|macro|AK4531_MONO2
mdefine_line|#define AK4531_MONO2    0x0d&t;/* MONO1 volume right */
DECL|macro|AK4531_MIC
mdefine_line|#define AK4531_MIC      0x0e&t;/* MIC volume */
DECL|macro|AK4531_MONO_OUT
mdefine_line|#define AK4531_MONO_OUT 0x0f&t;/* Mono-out volume */
DECL|macro|AK4531_OUT_SW1
mdefine_line|#define AK4531_OUT_SW1  0x10&t;/* Output mixer switch 1 */
DECL|macro|AK4531_OUT_SW2
mdefine_line|#define AK4531_OUT_SW2  0x11&t;/* Output mixer switch 2 */
DECL|macro|AK4531_LIN_SW1
mdefine_line|#define AK4531_LIN_SW1  0x12&t;/* Input left mixer switch 1 */
DECL|macro|AK4531_RIN_SW1
mdefine_line|#define AK4531_RIN_SW1  0x13&t;/* Input right mixer switch 1 */
DECL|macro|AK4531_LIN_SW2
mdefine_line|#define AK4531_LIN_SW2  0x14&t;/* Input left mixer switch 2 */
DECL|macro|AK4531_RIN_SW2
mdefine_line|#define AK4531_RIN_SW2  0x15&t;/* Input right mixer switch 2 */
DECL|macro|AK4531_RESET
mdefine_line|#define AK4531_RESET    0x16&t;/* Reset &amp; power down */
DECL|macro|AK4531_CLOCK
mdefine_line|#define AK4531_CLOCK    0x17&t;/* Clock select */
DECL|macro|AK4531_AD_IN
mdefine_line|#define AK4531_AD_IN    0x18&t;/* AD input select */
DECL|macro|AK4531_MIC_GAIN
mdefine_line|#define AK4531_MIC_GAIN 0x19&t;/* MIC amplified gain */
DECL|typedef|ak4531_t
r_typedef
r_struct
id|_snd_ak4531
id|ak4531_t
suffix:semicolon
DECL|struct|_snd_ak4531
r_struct
id|_snd_ak4531
(brace
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
id|ak4531_t
op_star
id|ak4531
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|ak4531_t
op_star
id|ak4531
)paren
suffix:semicolon
multiline_comment|/* --- */
DECL|member|regs
r_int
r_char
id|regs
(braket
l_int|0x20
)braket
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_ak4531_mixer
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|ak4531_t
op_star
id|_ak4531
comma
id|ak4531_t
op_star
op_star
id|rak4531
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_AK4531_CODEC_H */
eof
