macro_line|#ifndef __SOUND_MINORS_H
DECL|macro|__SOUND_MINORS_H
mdefine_line|#define __SOUND_MINORS_H
multiline_comment|/*&n; *  MINOR numbers&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|SNDRV_MINOR_DEVICES
mdefine_line|#define SNDRV_MINOR_DEVICES&t;&t;32
DECL|macro|SNDRV_MINOR_CARD
mdefine_line|#define SNDRV_MINOR_CARD(minor)&t;&t;((minor) &gt;&gt; 5)
DECL|macro|SNDRV_MINOR_DEVICE
mdefine_line|#define SNDRV_MINOR_DEVICE(minor)&t;((minor) &amp; 0x001f)
DECL|macro|SNDRV_MINOR
mdefine_line|#define SNDRV_MINOR(card, dev)&t;&t;(((card) &lt;&lt; 5) | (dev))
DECL|macro|SNDRV_MINOR_CONTROL
mdefine_line|#define SNDRV_MINOR_CONTROL&t;&t;0&t;/* 0 - 0 */
DECL|macro|SNDRV_MINOR_SEQUENCER
mdefine_line|#define SNDRV_MINOR_SEQUENCER&t;&t;1
DECL|macro|SNDRV_MINOR_TIMER
mdefine_line|#define SNDRV_MINOR_TIMER&t;&t;(1+32)
DECL|macro|SNDRV_MINOR_HWDEP
mdefine_line|#define SNDRV_MINOR_HWDEP&t;&t;4&t;/* 4 - 7 */
DECL|macro|SNDRV_MINOR_HWDEPS
mdefine_line|#define SNDRV_MINOR_HWDEPS&t;&t;4
DECL|macro|SNDRV_MINOR_RAWMIDI
mdefine_line|#define SNDRV_MINOR_RAWMIDI&t;&t;8&t;/* 8 - 15 */
DECL|macro|SNDRV_MINOR_RAWMIDIS
mdefine_line|#define SNDRV_MINOR_RAWMIDIS&t;&t;8
DECL|macro|SNDRV_MINOR_PCM_PLAYBACK
mdefine_line|#define SNDRV_MINOR_PCM_PLAYBACK&t;16&t;/* 16 - 23 */
DECL|macro|SNDRV_MINOR_PCM_CAPTURE
mdefine_line|#define SNDRV_MINOR_PCM_CAPTURE&t;&t;24&t;/* 24 - 31 */
DECL|macro|SNDRV_MINOR_PCMS
mdefine_line|#define SNDRV_MINOR_PCMS&t;&t;8
DECL|macro|SNDRV_DEVICE_TYPE_CONTROL
mdefine_line|#define SNDRV_DEVICE_TYPE_CONTROL&t;SNDRV_MINOR_CONTROL
DECL|macro|SNDRV_DEVICE_TYPE_HWDEP
mdefine_line|#define SNDRV_DEVICE_TYPE_HWDEP&t;&t;SNDRV_MINOR_HWDEP
DECL|macro|SNDRV_DEVICE_TYPE_MIXER
mdefine_line|#define SNDRV_DEVICE_TYPE_MIXER&t;&t;SNDRV_MINOR_MIXER
DECL|macro|SNDRV_DEVICE_TYPE_RAWMIDI
mdefine_line|#define SNDRV_DEVICE_TYPE_RAWMIDI&t;SNDRV_MINOR_RAWMIDI
DECL|macro|SNDRV_DEVICE_TYPE_PCM_PLAYBACK
mdefine_line|#define SNDRV_DEVICE_TYPE_PCM_PLAYBACK&t;SNDRV_MINOR_PCM_PLAYBACK
DECL|macro|SNDRV_DEVICE_TYPE_PCM_PLOOP
mdefine_line|#define SNDRV_DEVICE_TYPE_PCM_PLOOP&t;SNDRV_MINOR_PCM_PLOOP
DECL|macro|SNDRV_DEVICE_TYPE_PCM_CAPTURE
mdefine_line|#define SNDRV_DEVICE_TYPE_PCM_CAPTURE&t;SNDRV_MINOR_PCM_CAPTURE
DECL|macro|SNDRV_DEVICE_TYPE_PCM_CLOOP
mdefine_line|#define SNDRV_DEVICE_TYPE_PCM_CLOOP&t;SNDRV_MINOR_PCM_CLOOP
DECL|macro|SNDRV_DEVICE_TYPE_SEQUENCER
mdefine_line|#define SNDRV_DEVICE_TYPE_SEQUENCER&t;SNDRV_MINOR_SEQUENCER
DECL|macro|SNDRV_DEVICE_TYPE_TIMER
mdefine_line|#define SNDRV_DEVICE_TYPE_TIMER&t;&t;SNDRV_MINOR_TIMER
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|macro|SNDRV_MINOR_OSS_DEVICES
mdefine_line|#define SNDRV_MINOR_OSS_DEVICES&t;&t;16
DECL|macro|SNDRV_MINOR_OSS_CARD
mdefine_line|#define SNDRV_MINOR_OSS_CARD(minor)&t;((minor) &gt;&gt; 4)
DECL|macro|SNDRV_MINOR_OSS_DEVICE
mdefine_line|#define SNDRV_MINOR_OSS_DEVICE(minor)&t;((minor) &amp; 0x000f)
DECL|macro|SNDRV_MINOR_OSS
mdefine_line|#define SNDRV_MINOR_OSS(card, dev)&t;(((card) &lt;&lt; 4) | (dev))
DECL|macro|SNDRV_MINOR_OSS_MIXER
mdefine_line|#define SNDRV_MINOR_OSS_MIXER&t;&t;0&t;/* /dev/mixer - OSS 3.XX compatible */
DECL|macro|SNDRV_MINOR_OSS_SEQUENCER
mdefine_line|#define SNDRV_MINOR_OSS_SEQUENCER&t;1&t;/* /dev/sequencer - OSS 3.XX compatible */
DECL|macro|SNDRV_MINOR_OSS_MIDI
mdefine_line|#define&t;SNDRV_MINOR_OSS_MIDI&t;&t;2&t;/* /dev/midi - native midi interface - OSS 3.XX compatible - UART */
DECL|macro|SNDRV_MINOR_OSS_PCM
mdefine_line|#define SNDRV_MINOR_OSS_PCM&t;&t;3&t;/* alias */
DECL|macro|SNDRV_MINOR_OSS_PCM_8
mdefine_line|#define SNDRV_MINOR_OSS_PCM_8&t;&t;3&t;/* /dev/dsp - 8bit PCM - OSS 3.XX compatible */
DECL|macro|SNDRV_MINOR_OSS_AUDIO
mdefine_line|#define SNDRV_MINOR_OSS_AUDIO&t;&t;4&t;/* /dev/audio - SunSparc compatible */
DECL|macro|SNDRV_MINOR_OSS_PCM_16
mdefine_line|#define SNDRV_MINOR_OSS_PCM_16&t;&t;5&t;/* /dev/dsp16 - 16bit PCM - OSS 3.XX compatible */
DECL|macro|SNDRV_MINOR_OSS_SNDSTAT
mdefine_line|#define SNDRV_MINOR_OSS_SNDSTAT&t;&t;6&t;/* /dev/sndstat - for compatibility with OSS */
DECL|macro|SNDRV_MINOR_OSS_RESERVED7
mdefine_line|#define SNDRV_MINOR_OSS_RESERVED7&t;7&t;/* reserved for future use */
DECL|macro|SNDRV_MINOR_OSS_MUSIC
mdefine_line|#define SNDRV_MINOR_OSS_MUSIC&t;&t;8&t;/* /dev/music - OSS 3.XX compatible */
DECL|macro|SNDRV_MINOR_OSS_DMMIDI
mdefine_line|#define SNDRV_MINOR_OSS_DMMIDI&t;&t;9&t;/* /dev/dmmidi0 - this device can have another minor # with OSS */
DECL|macro|SNDRV_MINOR_OSS_DMFM
mdefine_line|#define SNDRV_MINOR_OSS_DMFM&t;&t;10&t;/* /dev/dmfm0 - this device can have another minor # with OSS */
DECL|macro|SNDRV_MINOR_OSS_MIXER1
mdefine_line|#define SNDRV_MINOR_OSS_MIXER1&t;&t;11&t;/* alternate mixer */
DECL|macro|SNDRV_MINOR_OSS_PCM1
mdefine_line|#define SNDRV_MINOR_OSS_PCM1&t;&t;12&t;/* alternate PCM (GF-A-1) */
DECL|macro|SNDRV_MINOR_OSS_MIDI1
mdefine_line|#define SNDRV_MINOR_OSS_MIDI1&t;&t;13&t;/* alternate midi - SYNTH */
DECL|macro|SNDRV_MINOR_OSS_DMMIDI1
mdefine_line|#define SNDRV_MINOR_OSS_DMMIDI1&t;&t;14&t;/* alternate dmmidi - SYNTH */
DECL|macro|SNDRV_MINOR_OSS_RESERVED15
mdefine_line|#define SNDRV_MINOR_OSS_RESERVED15&t;15&t;/* reserved for future use */
DECL|macro|SNDRV_OSS_DEVICE_TYPE_MIXER
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_MIXER&t;0
DECL|macro|SNDRV_OSS_DEVICE_TYPE_SEQUENCER
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_SEQUENCER&t;1
DECL|macro|SNDRV_OSS_DEVICE_TYPE_PCM
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_PCM&t;2
DECL|macro|SNDRV_OSS_DEVICE_TYPE_MIDI
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_MIDI&t;3
DECL|macro|SNDRV_OSS_DEVICE_TYPE_DMFM
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_DMFM&t;4
DECL|macro|SNDRV_OSS_DEVICE_TYPE_SNDSTAT
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_SNDSTAT&t;5
DECL|macro|SNDRV_OSS_DEVICE_TYPE_MUSIC
mdefine_line|#define SNDRV_OSS_DEVICE_TYPE_MUSIC&t;6
macro_line|#endif
macro_line|#endif /* __SOUND_MINORS_H */
eof
