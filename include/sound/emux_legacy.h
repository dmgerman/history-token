macro_line|#ifndef __SOUND_EMUX_LEGACY_H
DECL|macro|__SOUND_EMUX_LEGACY_H
mdefine_line|#define __SOUND_EMUX_LEGACY_H
multiline_comment|/*&n; *  Copyright (c) 1999-2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *  Definitions of OSS compatible headers for Emu8000 device informations&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;seq_oss_legacy.h&quot;
multiline_comment|/*&n; * awe hardware controls&n; */
DECL|macro|_EMUX_OSS_DEBUG_MODE
mdefine_line|#define _EMUX_OSS_DEBUG_MODE&t;&t;0x00
DECL|macro|_EMUX_OSS_REVERB_MODE
mdefine_line|#define _EMUX_OSS_REVERB_MODE&t;&t;0x01
DECL|macro|_EMUX_OSS_CHORUS_MODE
mdefine_line|#define _EMUX_OSS_CHORUS_MODE&t;&t;0x02
DECL|macro|_EMUX_OSS_REMOVE_LAST_SAMPLES
mdefine_line|#define _EMUX_OSS_REMOVE_LAST_SAMPLES&t;0x03
DECL|macro|_EMUX_OSS_INITIALIZE_CHIP
mdefine_line|#define _EMUX_OSS_INITIALIZE_CHIP&t;0x04
DECL|macro|_EMUX_OSS_SEND_EFFECT
mdefine_line|#define _EMUX_OSS_SEND_EFFECT&t;&t;0x05
DECL|macro|_EMUX_OSS_TERMINATE_CHANNEL
mdefine_line|#define _EMUX_OSS_TERMINATE_CHANNEL&t;0x06
DECL|macro|_EMUX_OSS_TERMINATE_ALL
mdefine_line|#define _EMUX_OSS_TERMINATE_ALL&t;&t;0x07
DECL|macro|_EMUX_OSS_INITIAL_VOLUME
mdefine_line|#define _EMUX_OSS_INITIAL_VOLUME&t;0x08
DECL|macro|_EMUX_OSS_INITIAL_ATTEN
mdefine_line|#define _EMUX_OSS_INITIAL_ATTEN&t;_EMUX_OSS_INITIAL_VOLUME
DECL|macro|_EMUX_OSS_RESET_CHANNEL
mdefine_line|#define _EMUX_OSS_RESET_CHANNEL&t;&t;0x09
DECL|macro|_EMUX_OSS_CHANNEL_MODE
mdefine_line|#define _EMUX_OSS_CHANNEL_MODE&t;&t;0x0a
DECL|macro|_EMUX_OSS_DRUM_CHANNELS
mdefine_line|#define _EMUX_OSS_DRUM_CHANNELS&t;&t;0x0b
DECL|macro|_EMUX_OSS_MISC_MODE
mdefine_line|#define _EMUX_OSS_MISC_MODE&t;&t;0x0c
DECL|macro|_EMUX_OSS_RELEASE_ALL
mdefine_line|#define _EMUX_OSS_RELEASE_ALL&t;&t;0x0d
DECL|macro|_EMUX_OSS_NOTEOFF_ALL
mdefine_line|#define _EMUX_OSS_NOTEOFF_ALL&t;&t;0x0e
DECL|macro|_EMUX_OSS_CHN_PRESSURE
mdefine_line|#define _EMUX_OSS_CHN_PRESSURE&t;&t;0x0f
DECL|macro|_EMUX_OSS_EQUALIZER
mdefine_line|#define _EMUX_OSS_EQUALIZER&t;&t;0x11
DECL|macro|_EMUX_OSS_MODE_FLAG
mdefine_line|#define _EMUX_OSS_MODE_FLAG&t;&t;0x80
DECL|macro|_EMUX_OSS_COOKED_FLAG
mdefine_line|#define _EMUX_OSS_COOKED_FLAG&t;&t;0x40&t;/* not supported */
DECL|macro|_EMUX_OSS_MODE_VALUE_MASK
mdefine_line|#define _EMUX_OSS_MODE_VALUE_MASK&t;0x3F
multiline_comment|/*&n; * mode type definitions&n; */
r_enum
(brace
DECL|enumerator|EMUX_MD_EXCLUSIVE_OFF
multiline_comment|/* 0*/
id|EMUX_MD_EXCLUSIVE_OFF
comma
multiline_comment|/* obsolete */
DECL|enumerator|EMUX_MD_EXCLUSIVE_ON
multiline_comment|/* 1*/
id|EMUX_MD_EXCLUSIVE_ON
comma
multiline_comment|/* obsolete */
DECL|enumerator|EMUX_MD_VERSION
multiline_comment|/* 2*/
id|EMUX_MD_VERSION
comma
multiline_comment|/* read only */
DECL|enumerator|EMUX_MD_EXCLUSIVE_SOUND
multiline_comment|/* 3*/
id|EMUX_MD_EXCLUSIVE_SOUND
comma
multiline_comment|/* 0/1: exclusive note on (default=1) */
DECL|enumerator|EMUX_MD_REALTIME_PAN
multiline_comment|/* 4*/
id|EMUX_MD_REALTIME_PAN
comma
multiline_comment|/* 0/1: do realtime pan change (default=1) */
DECL|enumerator|EMUX_MD_GUS_BANK
multiline_comment|/* 5*/
id|EMUX_MD_GUS_BANK
comma
multiline_comment|/* bank number for GUS patches (default=0) */
DECL|enumerator|EMUX_MD_KEEP_EFFECT
multiline_comment|/* 6*/
id|EMUX_MD_KEEP_EFFECT
comma
multiline_comment|/* 0/1: keep effect values, (default=0) */
DECL|enumerator|EMUX_MD_ZERO_ATTEN
multiline_comment|/* 7*/
id|EMUX_MD_ZERO_ATTEN
comma
multiline_comment|/* attenuation of max volume (default=32) */
DECL|enumerator|EMUX_MD_CHN_PRIOR
multiline_comment|/* 8*/
id|EMUX_MD_CHN_PRIOR
comma
multiline_comment|/* 0/1: set MIDI channel priority mode (default=1) */
DECL|enumerator|EMUX_MD_MOD_SENSE
multiline_comment|/* 9*/
id|EMUX_MD_MOD_SENSE
comma
multiline_comment|/* integer: modwheel sensitivity (def=18) */
DECL|enumerator|EMUX_MD_DEF_PRESET
multiline_comment|/*10*/
id|EMUX_MD_DEF_PRESET
comma
multiline_comment|/* integer: default preset number (def=0) */
DECL|enumerator|EMUX_MD_DEF_BANK
multiline_comment|/*11*/
id|EMUX_MD_DEF_BANK
comma
multiline_comment|/* integer: default bank number (def=0) */
DECL|enumerator|EMUX_MD_DEF_DRUM
multiline_comment|/*12*/
id|EMUX_MD_DEF_DRUM
comma
multiline_comment|/* integer: default drumset number (def=0) */
DECL|enumerator|EMUX_MD_TOGGLE_DRUM_BANK
multiline_comment|/*13*/
id|EMUX_MD_TOGGLE_DRUM_BANK
comma
multiline_comment|/* 0/1: toggle drum flag with bank# (def=0) */
DECL|enumerator|EMUX_MD_NEW_VOLUME_CALC
multiline_comment|/*14*/
id|EMUX_MD_NEW_VOLUME_CALC
comma
multiline_comment|/* 0/1: volume calculation mode (def=1) */
DECL|enumerator|EMUX_MD_CHORUS_MODE
multiline_comment|/*15*/
id|EMUX_MD_CHORUS_MODE
comma
multiline_comment|/* integer: chorus mode (def=2) */
DECL|enumerator|EMUX_MD_REVERB_MODE
multiline_comment|/*16*/
id|EMUX_MD_REVERB_MODE
comma
multiline_comment|/* integer: chorus mode (def=4) */
DECL|enumerator|EMUX_MD_BASS_LEVEL
multiline_comment|/*17*/
id|EMUX_MD_BASS_LEVEL
comma
multiline_comment|/* integer: bass level (def=5) */
DECL|enumerator|EMUX_MD_TREBLE_LEVEL
multiline_comment|/*18*/
id|EMUX_MD_TREBLE_LEVEL
comma
multiline_comment|/* integer: treble level (def=9) */
DECL|enumerator|EMUX_MD_DEBUG_MODE
multiline_comment|/*19*/
id|EMUX_MD_DEBUG_MODE
comma
multiline_comment|/* integer: debug level (def=0) */
DECL|enumerator|EMUX_MD_PAN_EXCHANGE
multiline_comment|/*20*/
id|EMUX_MD_PAN_EXCHANGE
comma
multiline_comment|/* 0/1: exchange panning direction (def=0) */
DECL|enumerator|EMUX_MD_END
id|EMUX_MD_END
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * effect parameters&n; */
r_enum
(brace
multiline_comment|/* modulation envelope parameters */
DECL|enumerator|EMUX_FX_ENV1_DELAY
multiline_comment|/* 0*/
id|EMUX_FX_ENV1_DELAY
comma
multiline_comment|/* WORD: ENVVAL */
DECL|enumerator|EMUX_FX_ENV1_ATTACK
multiline_comment|/* 1*/
id|EMUX_FX_ENV1_ATTACK
comma
multiline_comment|/* BYTE: up ATKHLD */
DECL|enumerator|EMUX_FX_ENV1_HOLD
multiline_comment|/* 2*/
id|EMUX_FX_ENV1_HOLD
comma
multiline_comment|/* BYTE: lw ATKHLD */
DECL|enumerator|EMUX_FX_ENV1_DECAY
multiline_comment|/* 3*/
id|EMUX_FX_ENV1_DECAY
comma
multiline_comment|/* BYTE: lw DCYSUS */
DECL|enumerator|EMUX_FX_ENV1_RELEASE
multiline_comment|/* 4*/
id|EMUX_FX_ENV1_RELEASE
comma
multiline_comment|/* BYTE: lw DCYSUS */
DECL|enumerator|EMUX_FX_ENV1_SUSTAIN
multiline_comment|/* 5*/
id|EMUX_FX_ENV1_SUSTAIN
comma
multiline_comment|/* BYTE: up DCYSUS */
DECL|enumerator|EMUX_FX_ENV1_PITCH
multiline_comment|/* 6*/
id|EMUX_FX_ENV1_PITCH
comma
multiline_comment|/* BYTE: up PEFE */
DECL|enumerator|EMUX_FX_ENV1_CUTOFF
multiline_comment|/* 7*/
id|EMUX_FX_ENV1_CUTOFF
comma
multiline_comment|/* BYTE: lw PEFE */
multiline_comment|/* volume envelope parameters */
DECL|enumerator|EMUX_FX_ENV2_DELAY
multiline_comment|/* 8*/
id|EMUX_FX_ENV2_DELAY
comma
multiline_comment|/* WORD: ENVVOL */
DECL|enumerator|EMUX_FX_ENV2_ATTACK
multiline_comment|/* 9*/
id|EMUX_FX_ENV2_ATTACK
comma
multiline_comment|/* BYTE: up ATKHLDV */
DECL|enumerator|EMUX_FX_ENV2_HOLD
multiline_comment|/*10*/
id|EMUX_FX_ENV2_HOLD
comma
multiline_comment|/* BYTE: lw ATKHLDV */
DECL|enumerator|EMUX_FX_ENV2_DECAY
multiline_comment|/*11*/
id|EMUX_FX_ENV2_DECAY
comma
multiline_comment|/* BYTE: lw DCYSUSV */
DECL|enumerator|EMUX_FX_ENV2_RELEASE
multiline_comment|/*12*/
id|EMUX_FX_ENV2_RELEASE
comma
multiline_comment|/* BYTE: lw DCYSUSV */
DECL|enumerator|EMUX_FX_ENV2_SUSTAIN
multiline_comment|/*13*/
id|EMUX_FX_ENV2_SUSTAIN
comma
multiline_comment|/* BYTE: up DCYSUSV */
multiline_comment|/* LFO1 (tremolo &amp; vibrato) parameters */
DECL|enumerator|EMUX_FX_LFO1_DELAY
multiline_comment|/*14*/
id|EMUX_FX_LFO1_DELAY
comma
multiline_comment|/* WORD: LFO1VAL */
DECL|enumerator|EMUX_FX_LFO1_FREQ
multiline_comment|/*15*/
id|EMUX_FX_LFO1_FREQ
comma
multiline_comment|/* BYTE: lo TREMFRQ */
DECL|enumerator|EMUX_FX_LFO1_VOLUME
multiline_comment|/*16*/
id|EMUX_FX_LFO1_VOLUME
comma
multiline_comment|/* BYTE: up TREMFRQ */
DECL|enumerator|EMUX_FX_LFO1_PITCH
multiline_comment|/*17*/
id|EMUX_FX_LFO1_PITCH
comma
multiline_comment|/* BYTE: up FMMOD */
DECL|enumerator|EMUX_FX_LFO1_CUTOFF
multiline_comment|/*18*/
id|EMUX_FX_LFO1_CUTOFF
comma
multiline_comment|/* BYTE: lo FMMOD */
multiline_comment|/* LFO2 (vibrato) parameters */
DECL|enumerator|EMUX_FX_LFO2_DELAY
multiline_comment|/*19*/
id|EMUX_FX_LFO2_DELAY
comma
multiline_comment|/* WORD: LFO2VAL */
DECL|enumerator|EMUX_FX_LFO2_FREQ
multiline_comment|/*20*/
id|EMUX_FX_LFO2_FREQ
comma
multiline_comment|/* BYTE: lo FM2FRQ2 */
DECL|enumerator|EMUX_FX_LFO2_PITCH
multiline_comment|/*21*/
id|EMUX_FX_LFO2_PITCH
comma
multiline_comment|/* BYTE: up FM2FRQ2 */
multiline_comment|/* Other overall effect parameters */
DECL|enumerator|EMUX_FX_INIT_PITCH
multiline_comment|/*22*/
id|EMUX_FX_INIT_PITCH
comma
multiline_comment|/* SHORT: pitch offset */
DECL|enumerator|EMUX_FX_CHORUS
multiline_comment|/*23*/
id|EMUX_FX_CHORUS
comma
multiline_comment|/* BYTE: chorus effects send (0-255) */
DECL|enumerator|EMUX_FX_REVERB
multiline_comment|/*24*/
id|EMUX_FX_REVERB
comma
multiline_comment|/* BYTE: reverb effects send (0-255) */
DECL|enumerator|EMUX_FX_CUTOFF
multiline_comment|/*25*/
id|EMUX_FX_CUTOFF
comma
multiline_comment|/* BYTE: up IFATN */
DECL|enumerator|EMUX_FX_FILTERQ
multiline_comment|/*26*/
id|EMUX_FX_FILTERQ
comma
multiline_comment|/* BYTE: up CCCA */
multiline_comment|/* Sample / loop offset changes */
DECL|enumerator|EMUX_FX_SAMPLE_START
multiline_comment|/*27*/
id|EMUX_FX_SAMPLE_START
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|EMUX_FX_LOOP_START
multiline_comment|/*28*/
id|EMUX_FX_LOOP_START
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|EMUX_FX_LOOP_END
multiline_comment|/*29*/
id|EMUX_FX_LOOP_END
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|EMUX_FX_COARSE_SAMPLE_START
multiline_comment|/*30*/
id|EMUX_FX_COARSE_SAMPLE_START
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|EMUX_FX_COARSE_LOOP_START
multiline_comment|/*31*/
id|EMUX_FX_COARSE_LOOP_START
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|EMUX_FX_COARSE_LOOP_END
multiline_comment|/*32*/
id|EMUX_FX_COARSE_LOOP_END
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|EMUX_FX_ATTEN
multiline_comment|/*33*/
id|EMUX_FX_ATTEN
comma
multiline_comment|/* BYTE: lo IFATN */
DECL|enumerator|EMUX_FX_END
id|EMUX_FX_END
comma
)brace
suffix:semicolon
multiline_comment|/* number of effects */
DECL|macro|EMUX_NUM_EFFECTS
mdefine_line|#define EMUX_NUM_EFFECTS  EMUX_FX_END
multiline_comment|/* effect flag values */
DECL|macro|EMUX_FX_FLAG_OFF
mdefine_line|#define EMUX_FX_FLAG_OFF&t;0
DECL|macro|EMUX_FX_FLAG_SET
mdefine_line|#define EMUX_FX_FLAG_SET&t;1
DECL|macro|EMUX_FX_FLAG_ADD
mdefine_line|#define EMUX_FX_FLAG_ADD&t;2
macro_line|#endif /* __SOUND_EMUX_LEGACY_H */
eof
