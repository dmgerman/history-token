macro_line|#ifndef __SOUND_EWS_H
DECL|macro|__SOUND_EWS_H
mdefine_line|#define __SOUND_EWS_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   Lowlevel functions for Terratec EWS88MT/D, EWX24/96, DMX 6Fire&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                    2002 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|EWS_DEVICE_DESC
mdefine_line|#define EWS_DEVICE_DESC &bslash;&n;&t;&t;&quot;{TerraTec,EWX 24/96},&quot;&bslash;&n;&t;&t;&quot;{TerraTec,EWS 88MT},&quot;&bslash;&n;&t;&t;&quot;{TerraTec,EWS 88D},&quot;&bslash;&n;&t;&t;&quot;{TerraTec,DMX 6Fire},&quot;
DECL|macro|ICE1712_SUBDEVICE_EWX2496
mdefine_line|#define ICE1712_SUBDEVICE_EWX2496&t;0x3b153011
DECL|macro|ICE1712_SUBDEVICE_EWS88MT
mdefine_line|#define ICE1712_SUBDEVICE_EWS88MT&t;0x3b151511
DECL|macro|ICE1712_SUBDEVICE_EWS88MT_NEW
mdefine_line|#define ICE1712_SUBDEVICE_EWS88MT_NEW&t;0x3b152511
DECL|macro|ICE1712_SUBDEVICE_EWS88D
mdefine_line|#define ICE1712_SUBDEVICE_EWS88D&t;0x3b152b11
DECL|macro|ICE1712_SUBDEVICE_DMX6FIRE
mdefine_line|#define ICE1712_SUBDEVICE_DMX6FIRE&t;0x3b153811
multiline_comment|/* entry point */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_ice1712_ews_cards
(braket
)braket
suffix:semicolon
multiline_comment|/* TerraTec EWX 24/96 configuration definitions */
DECL|macro|ICE1712_EWX2496_AK4524_CS
mdefine_line|#define ICE1712_EWX2496_AK4524_CS&t;0x01&t;/* AK4524 chip select; low = active */
DECL|macro|ICE1712_EWX2496_AIN_SEL
mdefine_line|#define ICE1712_EWX2496_AIN_SEL&t;&t;0x02&t;/* input sensitivity switch; high = louder */
DECL|macro|ICE1712_EWX2496_AOUT_SEL
mdefine_line|#define ICE1712_EWX2496_AOUT_SEL&t;0x04&t;/* output sensitivity switch; high = louder */
DECL|macro|ICE1712_EWX2496_RW
mdefine_line|#define ICE1712_EWX2496_RW&t;&t;0x08&t;/* read/write switch for i2c; high = write  */
DECL|macro|ICE1712_EWX2496_SERIAL_DATA
mdefine_line|#define ICE1712_EWX2496_SERIAL_DATA&t;0x10&t;/* i2c &amp; ak4524 data */
DECL|macro|ICE1712_EWX2496_SERIAL_CLOCK
mdefine_line|#define ICE1712_EWX2496_SERIAL_CLOCK&t;0x20&t;/* i2c &amp; ak4524 clock */
DECL|macro|ICE1712_EWX2496_TX2
mdefine_line|#define ICE1712_EWX2496_TX2&t;&t;0x40&t;/* MIDI2 (not used) */
DECL|macro|ICE1712_EWX2496_RX2
mdefine_line|#define ICE1712_EWX2496_RX2&t;&t;0x80&t;/* MIDI2 (not used) */
multiline_comment|/* TerraTec EWS 88MT/D configuration definitions */
multiline_comment|/* RW, SDA snd SCLK are identical with EWX24/96 */
DECL|macro|ICE1712_EWS88_CS8414_RATE
mdefine_line|#define ICE1712_EWS88_CS8414_RATE&t;0x07&t;/* CS8414 sample rate: gpio 0-2 */
DECL|macro|ICE1712_EWS88_RW
mdefine_line|#define ICE1712_EWS88_RW&t;&t;0x08&t;/* read/write switch for i2c; high = write  */
DECL|macro|ICE1712_EWS88_SERIAL_DATA
mdefine_line|#define ICE1712_EWS88_SERIAL_DATA&t;0x10&t;/* i2c &amp; ak4524 data */
DECL|macro|ICE1712_EWS88_SERIAL_CLOCK
mdefine_line|#define ICE1712_EWS88_SERIAL_CLOCK&t;0x20&t;/* i2c &amp; ak4524 clock */
DECL|macro|ICE1712_EWS88_TX2
mdefine_line|#define ICE1712_EWS88_TX2&t;&t;0x40&t;/* MIDI2 (only on 88D) */
DECL|macro|ICE1712_EWS88_RX2
mdefine_line|#define ICE1712_EWS88_RX2&t;&t;0x80&t;/* MIDI2 (only on 88D) */
multiline_comment|/* i2c address */
DECL|macro|ICE1712_EWS88MT_CS8404_ADDR
mdefine_line|#define ICE1712_EWS88MT_CS8404_ADDR&t;(0x40&gt;&gt;1)
DECL|macro|ICE1712_EWS88MT_INPUT_ADDR
mdefine_line|#define ICE1712_EWS88MT_INPUT_ADDR&t;(0x46&gt;&gt;1)
DECL|macro|ICE1712_EWS88MT_OUTPUT_ADDR
mdefine_line|#define ICE1712_EWS88MT_OUTPUT_ADDR&t;(0x48&gt;&gt;1)
DECL|macro|ICE1712_EWS88MT_OUTPUT_SENSE
mdefine_line|#define ICE1712_EWS88MT_OUTPUT_SENSE&t;0x40&t;/* mask */
DECL|macro|ICE1712_EWS88D_PCF_ADDR
mdefine_line|#define ICE1712_EWS88D_PCF_ADDR&t;&t;(0x40&gt;&gt;1)
multiline_comment|/* TerraTec DMX 6Fire configuration definitions */
DECL|macro|ICE1712_6FIRE_AK4524_CS_MASK
mdefine_line|#define ICE1712_6FIRE_AK4524_CS_MASK&t;0x07&t;/* AK4524 chip select #1-#3 */
DECL|macro|ICE1712_6FIRE_RW
mdefine_line|#define ICE1712_6FIRE_RW&t;&t;0x08&t;/* read/write switch for i2c; high = write  */
DECL|macro|ICE1712_6FIRE_SERIAL_DATA
mdefine_line|#define ICE1712_6FIRE_SERIAL_DATA&t;0x10&t;/* i2c &amp; ak4524 data */
DECL|macro|ICE1712_6FIRE_SERIAL_CLOCK
mdefine_line|#define ICE1712_6FIRE_SERIAL_CLOCK&t;0x20&t;/* i2c &amp; ak4524 clock */
DECL|macro|ICE1712_6FIRE_TX2
mdefine_line|#define ICE1712_6FIRE_TX2&t;&t;0x40&t;/* MIDI2 */
DECL|macro|ICE1712_6FIRE_RX2
mdefine_line|#define ICE1712_6FIRE_RX2&t;&t;0x80&t;/* MIDI2 */
DECL|macro|ICE1712_6FIRE_PCF9554_ADDR
mdefine_line|#define ICE1712_6FIRE_PCF9554_ADDR&t;(0x40&gt;&gt;1)
DECL|macro|ICE1712_6FIRE_CS8427_ADDR
mdefine_line|#define ICE1712_6FIRE_CS8427_ADDR&t;(0x22)
macro_line|#endif /* __SOUND_EWS_H */
eof
