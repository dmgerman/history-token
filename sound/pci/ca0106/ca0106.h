multiline_comment|/*&n; *  Copyright (c) 2004 James Courtier-Dutton &lt;James@superbug.demon.co.uk&gt;&n; *  Driver CA0106 chips. e.g. Sound Blaster Audigy LS and Live 24bit&n; *  Version: 0.0.20&n; *&n; *  FEATURES currently supported:&n; *    See ca0106_main.c for features.&n; * &n; *  Changelog:&n; *    Support interrupts per period.&n; *    Removed noise from Center/LFE channel when in Analog mode.&n; *    Rename and remove mixer controls.&n; *  0.0.6&n; *    Use separate card based DMA buffer for periods table list.&n; *  0.0.7&n; *    Change remove and rename ctrls into lists.&n; *  0.0.8&n; *    Try to fix capture sources.&n; *  0.0.9&n; *    Fix AC3 output.&n; *    Enable S32_LE format support.&n; *  0.0.10&n; *    Enable playback 48000 and 96000 rates. (Rates other that these do not work, even with &quot;plug:front&quot;.)&n; *  0.0.11&n; *    Add Model name recognition.&n; *  0.0.12&n; *    Correct interrupt timing. interrupt at end of period, instead of in the middle of a playback period.&n; *    Remove redundent &quot;voice&quot; handling.&n; *  0.0.13&n; *    Single trigger call for multi channels.&n; *  0.0.14&n; *    Set limits based on what the sound card hardware can do.&n; *    playback periods_min=2, periods_max=8&n; *    capture hw constraints require period_size = n * 64 bytes.&n; *    playback hw constraints require period_size = n * 64 bytes.&n; *  0.0.15&n; *    Separated ca0106.c into separate functional .c files.&n; *  0.0.16&n; *    Implement 192000 sample rate.&n; *  0.0.17&n; *    Add support for SB0410 and SB0413.&n; *  0.0.18&n; *    Modified Copyright message.&n; *  0.0.19&n; *    Added I2C and SPI registers. Filled in interrupt enable.&n; *  0.0.20&n; *    Added GPIO info for SB Live 24bit.&n; *&n; *&n; *  This code was initally based on code from ALSA&squot;s emu10k1x.c which is:&n; *  Copyright (c) by Francisco Moraes &lt;fmoraes@nc.rr.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/************************************************************************************************/
multiline_comment|/* PCI function 0 registers, address = &lt;val&gt; + PCIBASE0&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************************************/
DECL|macro|PTR
mdefine_line|#define PTR&t;&t;&t;0x00&t;&t;/* Indexed register set pointer register&t;*/
multiline_comment|/* NOTE: The CHANNELNUM and ADDRESS words can&t;*/
multiline_comment|/* be modified independently of each other.&t;*/
multiline_comment|/* CNL[1:0], ADDR[27:16]                        */
DECL|macro|DATA
mdefine_line|#define DATA&t;&t;&t;0x04&t;&t;/* Indexed register set data register&t;&t;*/
multiline_comment|/* DATA[31:0]&t;&t;&t;&t;&t;*/
DECL|macro|IPR
mdefine_line|#define IPR&t;&t;&t;0x08&t;&t;/* Global interrupt pending register&t;&t;*/
multiline_comment|/* Clear pending interrupts by writing a 1 to&t;*/
multiline_comment|/* the relevant bits and zero to the other bits&t;*/
DECL|macro|IPR_MIDI_RX_B
mdefine_line|#define IPR_MIDI_RX_B&t;&t;0x00020000&t;/* MIDI UART-B Receive buffer non-empty&t;&t;*/
DECL|macro|IPR_MIDI_TX_B
mdefine_line|#define IPR_MIDI_TX_B&t;&t;0x00010000&t;/* MIDI UART-B Transmit buffer empty&t;&t;*/
DECL|macro|IPR_SPDIF_IN_USER
mdefine_line|#define IPR_SPDIF_IN_USER&t;0x00004000      /* SPDIF input user data has 16 more bits&t;*/
DECL|macro|IPR_SPDIF_OUT_USER
mdefine_line|#define IPR_SPDIF_OUT_USER&t;0x00002000      /* SPDIF output user data needs 16 more bits&t;*/
DECL|macro|IPR_SPDIF_OUT_FRAME
mdefine_line|#define IPR_SPDIF_OUT_FRAME&t;0x00001000      /* SPDIF frame about to start&t;&t;&t;*/
DECL|macro|IPR_SPI
mdefine_line|#define IPR_SPI&t;&t;&t;0x00000800      /* SPI transaction completed&t;&t;&t;*/
DECL|macro|IPR_I2C_EEPROM
mdefine_line|#define IPR_I2C_EEPROM&t;&t;0x00000400      /* I2C EEPROM transaction completed&t;&t;*/
DECL|macro|IPR_I2C_DAC
mdefine_line|#define IPR_I2C_DAC&t;&t;0x00000200      /* I2C DAC transaction completed&t;&t;*/
DECL|macro|IPR_AI
mdefine_line|#define IPR_AI&t;&t;&t;0x00000100      /* Audio pending register changed. See PTR reg 0x76&t;*/
DECL|macro|IPR_GPI
mdefine_line|#define IPR_GPI&t;&t;&t;0x00000080      /* General Purpose input changed&t;&t;*/
DECL|macro|IPR_SRC_LOCKED
mdefine_line|#define IPR_SRC_LOCKED          0x00000040      /* SRC lock status changed&t;&t;&t;*/
DECL|macro|IPR_SPDIF_STATUS
mdefine_line|#define IPR_SPDIF_STATUS        0x00000020      /* SPDIF status changed&t;&t;&t;&t;*/
DECL|macro|IPR_TIMER2
mdefine_line|#define IPR_TIMER2              0x00000010      /* 192000Hz Timer&t;&t;&t;&t;*/
DECL|macro|IPR_TIMER1
mdefine_line|#define IPR_TIMER1              0x00000008      /* 44100Hz Timer&t;&t;&t;&t;*/
DECL|macro|IPR_MIDI_RX_A
mdefine_line|#define IPR_MIDI_RX_A&t;&t;0x00000004&t;/* MIDI UART-A Receive buffer non-empty&t;&t;*/
DECL|macro|IPR_MIDI_TX_A
mdefine_line|#define IPR_MIDI_TX_A&t;&t;0x00000002&t;/* MIDI UART-A Transmit buffer empty&t;&t;*/
DECL|macro|IPR_PCI
mdefine_line|#define IPR_PCI&t;&t;&t;0x00000001&t;/* PCI Bus error&t;&t;&t;&t;*/
DECL|macro|INTE
mdefine_line|#define INTE&t;&t;&t;0x0c&t;&t;/* Interrupt enable register&t;&t;&t;*/
DECL|macro|INTE_MIDI_RX_B
mdefine_line|#define INTE_MIDI_RX_B&t;&t;0x00020000&t;/* MIDI UART-B Receive buffer non-empty&t;&t;*/
DECL|macro|INTE_MIDI_TX_B
mdefine_line|#define INTE_MIDI_TX_B&t;&t;0x00010000&t;/* MIDI UART-B Transmit buffer empty&t;&t;*/
DECL|macro|INTE_SPDIF_IN_USER
mdefine_line|#define INTE_SPDIF_IN_USER&t;0x00004000      /* SPDIF input user data has 16 more bits&t;*/
DECL|macro|INTE_SPDIF_OUT_USER
mdefine_line|#define INTE_SPDIF_OUT_USER&t;0x00002000      /* SPDIF output user data needs 16 more bits&t;*/
DECL|macro|INTE_SPDIF_OUT_FRAME
mdefine_line|#define INTE_SPDIF_OUT_FRAME&t;0x00001000      /* SPDIF frame about to start&t;&t;&t;*/
DECL|macro|INTE_SPI
mdefine_line|#define INTE_SPI&t;&t;0x00000800      /* SPI transaction completed&t;&t;&t;*/
DECL|macro|INTE_I2C_EEPROM
mdefine_line|#define INTE_I2C_EEPROM&t;&t;0x00000400      /* I2C EEPROM transaction completed&t;&t;*/
DECL|macro|INTE_I2C_DAC
mdefine_line|#define INTE_I2C_DAC&t;&t;0x00000200      /* I2C DAC transaction completed&t;&t;*/
DECL|macro|INTE_AI
mdefine_line|#define INTE_AI&t;&t;&t;0x00000100      /* Audio pending register changed. See PTR reg 0x75 */
DECL|macro|INTE_GPI
mdefine_line|#define INTE_GPI&t;&t;0x00000080      /* General Purpose input changed&t;&t;*/
DECL|macro|INTE_SRC_LOCKED
mdefine_line|#define INTE_SRC_LOCKED         0x00000040      /* SRC lock status changed&t;&t;&t;*/
DECL|macro|INTE_SPDIF_STATUS
mdefine_line|#define INTE_SPDIF_STATUS       0x00000020      /* SPDIF status changed&t;&t;&t;&t;*/
DECL|macro|INTE_TIMER2
mdefine_line|#define INTE_TIMER2             0x00000010      /* 192000Hz Timer&t;&t;&t;&t;*/
DECL|macro|INTE_TIMER1
mdefine_line|#define INTE_TIMER1             0x00000008      /* 44100Hz Timer&t;&t;&t;&t;*/
DECL|macro|INTE_MIDI_RX_A
mdefine_line|#define INTE_MIDI_RX_A&t;&t;0x00000004&t;/* MIDI UART-A Receive buffer non-empty&t;&t;*/
DECL|macro|INTE_MIDI_TX_A
mdefine_line|#define INTE_MIDI_TX_A&t;&t;0x00000002&t;/* MIDI UART-A Transmit buffer empty&t;&t;*/
DECL|macro|INTE_PCI
mdefine_line|#define INTE_PCI&t;&t;0x00000001&t;/* PCI Bus error&t;&t;&t;&t;*/
DECL|macro|UNKNOWN10
mdefine_line|#define UNKNOWN10&t;&t;0x10&t;&t;/* Unknown ??. Defaults to 0 */
DECL|macro|HCFG
mdefine_line|#define HCFG&t;&t;&t;0x14&t;&t;/* Hardware config register&t;&t;&t;*/
multiline_comment|/* 0x1000 causes AC3 to fails. It adds a dither bit. */
DECL|macro|HCFG_STAC
mdefine_line|#define HCFG_STAC&t;&t;0x10000000&t;/* Special mode for STAC9460 Codec. */
DECL|macro|HCFG_CAPTURE_I2S_BYPASS
mdefine_line|#define HCFG_CAPTURE_I2S_BYPASS&t;0x08000000&t;/* 1 = bypass I2S input async SRC. */
DECL|macro|HCFG_CAPTURE_SPDIF_BYPASS
mdefine_line|#define HCFG_CAPTURE_SPDIF_BYPASS 0x04000000&t;/* 1 = bypass SPDIF input async SRC. */
DECL|macro|HCFG_PLAYBACK_I2S_BYPASS
mdefine_line|#define HCFG_PLAYBACK_I2S_BYPASS 0x02000000&t;/* 0 = I2S IN mixer output, 1 = I2S IN1. */
DECL|macro|HCFG_FORCE_LOCK
mdefine_line|#define HCFG_FORCE_LOCK&t;&t;0x01000000&t;/* For test only. Force input SRC tracker to lock. */
DECL|macro|HCFG_PLAYBACK_ATTENUATION
mdefine_line|#define HCFG_PLAYBACK_ATTENUATION 0x00006000&t;/* Playback attenuation mask. 0 = 0dB, 1 = 6dB, 2 = 12dB, 3 = Mute. */
DECL|macro|HCFG_PLAYBACK_DITHER
mdefine_line|#define HCFG_PLAYBACK_DITHER&t;0x00001000&t;/* 1 = Add dither bit to all playback channels. */
DECL|macro|HCFG_PLAYBACK_S32_LE
mdefine_line|#define HCFG_PLAYBACK_S32_LE&t;0x00000800&t;/* 1 = S32_LE, 0 = S16_LE                       */
DECL|macro|HCFG_CAPTURE_S32_LE
mdefine_line|#define HCFG_CAPTURE_S32_LE&t;0x00000400&t;/* 1 = S32_LE, 0 = S16_LE (S32_LE current not working)&t;*/
DECL|macro|HCFG_8_CHANNEL_PLAY
mdefine_line|#define HCFG_8_CHANNEL_PLAY&t;0x00000200&t;/* 1 = 8 channels, 0 = 2 channels per substream.*/
DECL|macro|HCFG_8_CHANNEL_CAPTURE
mdefine_line|#define HCFG_8_CHANNEL_CAPTURE&t;0x00000100&t;/* 1 = 8 channels, 0 = 2 channels per substream.*/
DECL|macro|HCFG_MONO
mdefine_line|#define HCFG_MONO&t;&t;0x00000080&t;/* 1 = I2S Input mono                           */
DECL|macro|HCFG_I2S_OUTPUT
mdefine_line|#define HCFG_I2S_OUTPUT&t;&t;0x00000010&t;/* 1 = I2S Output disabled                      */
DECL|macro|HCFG_AC97
mdefine_line|#define HCFG_AC97&t;&t;0x00000008&t;/* 0 = AC97 1.0, 1 = AC97 2.0                   */
DECL|macro|HCFG_LOCK_PLAYBACK_CACHE
mdefine_line|#define HCFG_LOCK_PLAYBACK_CACHE 0x00000004&t;/* 1 = Cancel bustmaster accesses to soundcache */
multiline_comment|/* NOTE: This should generally never be used.  &t;*/
DECL|macro|HCFG_LOCK_CAPTURE_CACHE
mdefine_line|#define HCFG_LOCK_CAPTURE_CACHE&t;0x00000002&t;/* 1 = Cancel bustmaster accesses to soundcache */
multiline_comment|/* NOTE: This should generally never be used.  &t;*/
DECL|macro|HCFG_AUDIOENABLE
mdefine_line|#define HCFG_AUDIOENABLE&t;0x00000001&t;/* 0 = CODECs transmit zero-valued samples&t;*/
multiline_comment|/* Should be set to 1 when the EMU10K1 is&t;*/
multiline_comment|/* completely initialized.&t;&t;&t;*/
DECL|macro|GPIO
mdefine_line|#define GPIO&t;&t;&t;0x18&t;&t;/* Defaults: 005f03a3-Analog, 005f02a2-SPDIF.   */
multiline_comment|/* Here pins 0,1,2,3,4,,6 are output. 5,7 are input */
multiline_comment|/* For the Audigy LS, pin 0 (or bit 8) controls the SPDIF/Analog jack. */
multiline_comment|/* SB Live 24bit:&n;&t;&t;&t;&t;&t;&t; * bit 8 0 = SPDIF in and out / 1 = Analog (Mic or Line)-in.&n;&t;&t;&t;&t;&t;&t; * bit 9 0 = Mute / 1 = Analog out.&n;&t;&t;&t;&t;&t;&t; * bit 10 0 = Line-in / 1 = Mic-in.&n;&t;&t;&t;&t;&t;&t; * bit 11 0 = ? / 1 = ?&n;&t;&t;&t;&t;&t;&t; * bit 12 0 = ? / 1 = ?&n;&t;&t;&t;&t;&t;&t; * bit 13 0 = ? / 1 = ?&n;&t;&t;&t;&t;&t;&t; * bit 14 0 = Mute / 1 = Analog out&n;&t;&t;&t;&t;&t;&t; * bit 15 0 = ? / 1 = ?&n;&t;&t;&t;&t;&t;&t; * Both bit 9 and bit 14 have to be set for analog sound to work on the SB Live 24bit.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 8 general purpose programmable In/Out pins.&n;&t;&t;&t;&t;&t;&t; * GPI [8:0] Read only. Default 0.&n;&t;&t;&t;&t;&t;&t; * GPO [15:8] Default 0x9. (Default to SPDIF jack enabled for SPDIF)&n;&t;&t;&t;&t;&t;&t; * GPO Enable [23:16] Default 0x0f. Setting a bit to 1, causes the pin to be an output pin.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|AC97DATA
mdefine_line|#define AC97DATA&t;&t;0x1c&t;&t;/* AC97 register set data register (16 bit)&t;*/
DECL|macro|AC97ADDRESS
mdefine_line|#define AC97ADDRESS&t;&t;0x1e&t;&t;/* AC97 register set address register (8 bit)&t;*/
multiline_comment|/********************************************************************************************************/
multiline_comment|/* CA0106 pointer-offset register set, accessed through the PTR and DATA registers                     */
multiline_comment|/********************************************************************************************************/
multiline_comment|/* Initally all registers from 0x00 to 0x3f have zero contents. */
DECL|macro|PLAYBACK_LIST_ADDR
mdefine_line|#define PLAYBACK_LIST_ADDR&t;0x00&t;&t;/* Base DMA address of a list of pointers to each period/size */
multiline_comment|/* One list entry: 4 bytes for DMA address, &n;&t;&t;&t;&t;&t;&t; * 4 bytes for period_size &lt;&lt; 16.&n;&t;&t;&t;&t;&t;&t; * One list entry is 8 bytes long.&n;&t;&t;&t;&t;&t;&t; * One list entry for each period in the buffer.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* ADDR[31:0], Default: 0x0 */
DECL|macro|PLAYBACK_LIST_SIZE
mdefine_line|#define PLAYBACK_LIST_SIZE&t;0x01&t;&t;/* Size of list in bytes &lt;&lt; 16. E.g. 8 periods -&gt; 0x00380000  */
multiline_comment|/* SIZE[21:16], Default: 0x8 */
DECL|macro|PLAYBACK_LIST_PTR
mdefine_line|#define PLAYBACK_LIST_PTR&t;0x02&t;&t;/* Pointer to the current period being played */
multiline_comment|/* PTR[5:0], Default: 0x0 */
DECL|macro|PLAYBACK_UNKNOWN3
mdefine_line|#define PLAYBACK_UNKNOWN3&t;0x03&t;&t;/* Not used ?? */
DECL|macro|PLAYBACK_DMA_ADDR
mdefine_line|#define PLAYBACK_DMA_ADDR&t;0x04&t;&t;/* Playback DMA addresss */
multiline_comment|/* DMA[31:0], Default: 0x0 */
DECL|macro|PLAYBACK_PERIOD_SIZE
mdefine_line|#define PLAYBACK_PERIOD_SIZE&t;0x05&t;&t;/* Playback period size. win2000 uses 0x04000000 */
multiline_comment|/* SIZE[31:16], Default: 0x0 */
DECL|macro|PLAYBACK_POINTER
mdefine_line|#define PLAYBACK_POINTER&t;0x06&t;&t;/* Playback period pointer. Used with PLAYBACK_LIST_PTR to determine buffer position currently in DAC */
multiline_comment|/* POINTER[15:0], Default: 0x0 */
DECL|macro|PLAYBACK_PERIOD_END_ADDR
mdefine_line|#define PLAYBACK_PERIOD_END_ADDR 0x07&t;&t;/* Playback fifo end address */
multiline_comment|/* END_ADDR[15:0], FLAG[16] 0 = don&squot;t stop, 1 = stop */
DECL|macro|PLAYBACK_FIFO_OFFSET_ADDRESS
mdefine_line|#define PLAYBACK_FIFO_OFFSET_ADDRESS&t;0x08&t;/* Current fifo offset address [21:16] */
multiline_comment|/* Cache size valid [5:0] */
DECL|macro|PLAYBACK_UNKNOWN9
mdefine_line|#define PLAYBACK_UNKNOWN9&t;0x09&t;&t;/* 0x9 to 0xf Unused */
DECL|macro|CAPTURE_DMA_ADDR
mdefine_line|#define CAPTURE_DMA_ADDR&t;0x10&t;&t;/* Capture DMA address */
multiline_comment|/* DMA[31:0], Default: 0x0 */
DECL|macro|CAPTURE_BUFFER_SIZE
mdefine_line|#define CAPTURE_BUFFER_SIZE&t;0x11&t;&t;/* Capture buffer size */
multiline_comment|/* SIZE[31:16], Default: 0x0 */
DECL|macro|CAPTURE_POINTER
mdefine_line|#define CAPTURE_POINTER&t;&t;0x12&t;&t;/* Capture buffer pointer. Sample currently in ADC */
multiline_comment|/* POINTER[15:0], Default: 0x0 */
DECL|macro|CAPTURE_FIFO_OFFSET_ADDRESS
mdefine_line|#define CAPTURE_FIFO_OFFSET_ADDRESS&t;0x13&t;/* Current fifo offset address [21:16] */
multiline_comment|/* Cache size valid [5:0] */
DECL|macro|PLAYBACK_LAST_SAMPLE
mdefine_line|#define PLAYBACK_LAST_SAMPLE    0x20&t;&t;/* The sample currently being played */
multiline_comment|/* 0x21 - 0x3f unused */
DECL|macro|BASIC_INTERRUPT
mdefine_line|#define BASIC_INTERRUPT         0x40&t;&t;/* Used by both playback and capture interrupt handler */
multiline_comment|/* Playback (0x1&lt;&lt;channel_id) */
multiline_comment|/* Capture  (0x100&lt;&lt;channel_id) */
multiline_comment|/* Playback sample rate 96000 = 0x20000 */
multiline_comment|/* Start Playback [3:0] (one bit per channel)&n;&t;&t;&t;&t;&t;&t; * Start Capture [11:8] (one bit per channel)&n;&t;&t;&t;&t;&t;&t; * Playback rate [23:16] (2 bits per channel) (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * Playback mixer in enable [27:24] (one bit per channel)&n;&t;&t;&t;&t;&t;&t; * Playback mixer out enable [31:28] (one bit per channel)&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* The Digital out jack is shared with the Center/LFE Analogue output. &n; * The jack has 4 poles. I will call 1 - Tip, 2 - Next to 1, 3 - Next to 2, 4 - Next to 3&n; * For Analogue: 1 -&gt; Center Speaker, 2 -&gt; Sub Woofer, 3 -&gt; Ground, 4 -&gt; Ground&n; * For Digital: 1 -&gt; Front SPDIF, 2 -&gt; Rear SPDIF, 3 -&gt; Center/Subwoofer SPDIF, 4 -&gt; Ground.&n; * Standard 4 pole Video A/V cable with RCA outputs: 1 -&gt; White, 2 -&gt; Yellow, 3 -&gt; Sheild on all three, 4 -&gt; Red.&n; * So, from this you can see that you cannot use a Standard 4 pole Video A/V cable with the SB Audigy LS card.&n; */
multiline_comment|/* The Front SPDIF PCM gets mixed with samples from the AC97 codec, so can only work for Stereo PCM and not AC3/DTS&n; * The Rear SPDIF can be used for Stereo PCM and also AC3/DTS&n; * The Center/LFE SPDIF cannot be used for AC3/DTS, but can be used for Stereo PCM.&n; * Summary: For ALSA we use the Rear channel for SPDIF Digital AC3/DTS output&n; */
multiline_comment|/* A standard 2 pole mono mini-jack to RCA plug can be used for SPDIF Stereo PCM output from the Front channel.&n; * A standard 3 pole stereo mini-jack to 2 RCA plugs can be used for SPDIF AC3/DTS and Stereo PCM output utilising the Rear channel and just one of the RCA plugs. &n; */
DECL|macro|SPCS0
mdefine_line|#define SPCS0&t;&t;&t;0x41&t;&t;/* SPDIF output Channel Status 0 register. For Rear. default=0x02108004, non-audio=0x02108006&t;*/
DECL|macro|SPCS1
mdefine_line|#define SPCS1&t;&t;&t;0x42&t;&t;/* SPDIF output Channel Status 1 register. For Front */
DECL|macro|SPCS2
mdefine_line|#define SPCS2&t;&t;&t;0x43&t;&t;/* SPDIF output Channel Status 2 register. For Center/LFE */
DECL|macro|SPCS3
mdefine_line|#define SPCS3&t;&t;&t;0x44&t;&t;/* SPDIF output Channel Status 3 register. Unknown */
multiline_comment|/* When Channel set to 0: */
DECL|macro|SPCS_CLKACCYMASK
mdefine_line|#define SPCS_CLKACCYMASK&t;0x30000000&t;/* Clock accuracy&t;&t;&t;&t;*/
DECL|macro|SPCS_CLKACCY_1000PPM
mdefine_line|#define SPCS_CLKACCY_1000PPM&t;0x00000000&t;/* 1000 parts per million&t;&t;&t;*/
DECL|macro|SPCS_CLKACCY_50PPM
mdefine_line|#define SPCS_CLKACCY_50PPM&t;0x10000000&t;/* 50 parts per million&t;&t;&t;&t;*/
DECL|macro|SPCS_CLKACCY_VARIABLE
mdefine_line|#define SPCS_CLKACCY_VARIABLE&t;0x20000000&t;/* Variable accuracy&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATEMASK
mdefine_line|#define SPCS_SAMPLERATEMASK&t;0x0f000000&t;/* Sample rate&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATE_44
mdefine_line|#define SPCS_SAMPLERATE_44&t;0x00000000&t;/* 44.1kHz sample rate&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATE_48
mdefine_line|#define SPCS_SAMPLERATE_48&t;0x02000000&t;/* 48kHz sample rate&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATE_32
mdefine_line|#define SPCS_SAMPLERATE_32&t;0x03000000&t;/* 32kHz sample rate&t;&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUMMASK
mdefine_line|#define SPCS_CHANNELNUMMASK&t;0x00f00000&t;/* Channel number&t;&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUM_UNSPEC
mdefine_line|#define SPCS_CHANNELNUM_UNSPEC&t;0x00000000&t;/* Unspecified channel number&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUM_LEFT
mdefine_line|#define SPCS_CHANNELNUM_LEFT&t;0x00100000&t;/* Left channel&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUM_RIGHT
mdefine_line|#define SPCS_CHANNELNUM_RIGHT&t;0x00200000&t;/* Right channel&t;&t;&t;&t;*/
DECL|macro|SPCS_SOURCENUMMASK
mdefine_line|#define SPCS_SOURCENUMMASK&t;0x000f0000&t;/* Source number&t;&t;&t;&t;*/
DECL|macro|SPCS_SOURCENUM_UNSPEC
mdefine_line|#define SPCS_SOURCENUM_UNSPEC&t;0x00000000&t;/* Unspecified source number&t;&t;&t;*/
DECL|macro|SPCS_GENERATIONSTATUS
mdefine_line|#define SPCS_GENERATIONSTATUS&t;0x00008000&t;/* Originality flag (see IEC-958 spec)&t;&t;*/
DECL|macro|SPCS_CATEGORYCODEMASK
mdefine_line|#define SPCS_CATEGORYCODEMASK&t;0x00007f00&t;/* Category code (see IEC-958 spec)&t;&t;*/
DECL|macro|SPCS_MODEMASK
mdefine_line|#define SPCS_MODEMASK&t;&t;0x000000c0&t;/* Mode (see IEC-958 spec)&t;&t;&t;*/
DECL|macro|SPCS_EMPHASISMASK
mdefine_line|#define SPCS_EMPHASISMASK&t;0x00000038&t;/* Emphasis&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_EMPHASIS_NONE
mdefine_line|#define SPCS_EMPHASIS_NONE&t;0x00000000&t;/* No emphasis&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_EMPHASIS_50_15
mdefine_line|#define SPCS_EMPHASIS_50_15&t;0x00000008&t;/* 50/15 usec 2 channel&t;&t;&t;&t;*/
DECL|macro|SPCS_COPYRIGHT
mdefine_line|#define SPCS_COPYRIGHT&t;&t;0x00000004&t;/* Copyright asserted flag -- do not modify&t;*/
DECL|macro|SPCS_NOTAUDIODATA
mdefine_line|#define SPCS_NOTAUDIODATA&t;0x00000002&t;/* 0 = Digital audio, 1 = not audio&t;&t;*/
DECL|macro|SPCS_PROFESSIONAL
mdefine_line|#define SPCS_PROFESSIONAL&t;0x00000001&t;/* 0 = Consumer (IEC-958), 1 = pro (AES3-1992)&t;*/
multiline_comment|/* When Channel set to 1: */
DECL|macro|SPCS_WORD_LENGTH_MASK
mdefine_line|#define SPCS_WORD_LENGTH_MASK&t;0x0000000f&t;/* Word Length Mask&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_16
mdefine_line|#define SPCS_WORD_LENGTH_16&t;0x00000008&t;/* Word Length 16 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_17
mdefine_line|#define SPCS_WORD_LENGTH_17&t;0x00000006&t;/* Word Length 17 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_18
mdefine_line|#define SPCS_WORD_LENGTH_18&t;0x00000004&t;/* Word Length 18 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_19
mdefine_line|#define SPCS_WORD_LENGTH_19&t;0x00000002&t;/* Word Length 19 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_20A
mdefine_line|#define SPCS_WORD_LENGTH_20A&t;0x0000000a&t;/* Word Length 20 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_20
mdefine_line|#define SPCS_WORD_LENGTH_20&t;0x00000009&t;/* Word Length 20 bit (both 0xa and 0x9 are 20 bit) */
DECL|macro|SPCS_WORD_LENGTH_21
mdefine_line|#define SPCS_WORD_LENGTH_21&t;0x00000007&t;/* Word Length 21 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_21
mdefine_line|#define SPCS_WORD_LENGTH_21&t;0x00000007&t;/* Word Length 21 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_22
mdefine_line|#define SPCS_WORD_LENGTH_22&t;0x00000005&t;/* Word Length 22 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_23
mdefine_line|#define SPCS_WORD_LENGTH_23&t;0x00000003&t;/* Word Length 23 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_WORD_LENGTH_24
mdefine_line|#define SPCS_WORD_LENGTH_24&t;0x0000000b&t;/* Word Length 24 bit&t;&t;&t;&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_MASK
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_MASK&t;0x000000f0 /* Original Sample rate&t;&t;&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_NONE
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_NONE&t;0x00000000 /* Original Sample rate not indicated&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_16000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_16000&t;0x00000010 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_RES1
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_RES1&t;0x00000020 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_32000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_32000&t;0x00000030 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_12000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_12000&t;0x00000040 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_11025
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_11025&t;0x00000050 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_8000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_8000&t;0x00000060 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_RES2
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_RES2&t;0x00000070 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_192000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_192000 0x00000080 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_24000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_24000&t;0x00000090 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_96000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_96000&t;0x000000a0 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_48000
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_48000&t;0x000000b0 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_176400
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_176400 0x000000c0 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_22050
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_22050&t;0x000000d0 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_88200
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_88200&t;0x000000e0 /* Original Sample rate&t;*/
DECL|macro|SPCS_ORIGINAL_SAMPLE_RATE_44100
mdefine_line|#define SPCS_ORIGINAL_SAMPLE_RATE_44100&t;0x000000f0 /* Original Sample rate&t;*/
DECL|macro|SPDIF_SELECT1
mdefine_line|#define SPDIF_SELECT1&t;&t;0x45&t;&t;/* Enables SPDIF or Analogue outputs 0-SPDIF, 0xf00-Analogue */
multiline_comment|/* 0x100 - Front, 0x800 - Rear, 0x200 - Center/LFE.&n;&t;&t;&t;&t;&t;&t; * But as the jack is shared, use 0xf00.&n;&t;&t;&t;&t;&t;&t; * The Windows2000 driver uses 0x0000000f for both digital and analog.&n;&t;&t;&t;&t;&t;&t; * 0xf00 introduces interesting noises onto the Center/LFE.&n;&t;&t;&t;&t;&t;&t; * If you turn the volume up, you hear computer noise,&n;&t;&t;&t;&t;&t;&t; * e.g. mouse moving, changing between app windows etc.&n;&t;&t;&t;&t;&t;&t; * So, I am going to set this to 0x0000000f all the time now,&n;&t;&t;&t;&t;&t;&t; * same as the windows driver does.&n;&t;&t;&t;&t;&t;&t; * Use register SPDIF_SELECT2(0x72) to switch between SPDIF and Analog.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* When Channel = 0:&n;&t;&t;&t;&t;&t;&t; * Wide SPDIF format [3:0] (one bit for each channel) (0=20bit, 1=24bit)&n;&t;&t;&t;&t;&t;&t; * Tristate SPDIF Output [11:8] (one bit for each channel) (0=Not tristate, 1=Tristate)&n;&t;&t;&t;&t;&t;&t; * SPDIF Bypass enable [19:16] (one bit for each channel) (0=Not bypass, 1=Bypass)&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* When Channel = 1:&n;&t;&t;&t;&t;&t;&t; * SPDIF 0 User data [7:0]&n;&t;&t;&t;&t;&t;&t; * SPDIF 1 User data [15:8]&n;&t;&t;&t;&t;&t;&t; * SPDIF 0 User data [23:16]&n;&t;&t;&t;&t;&t;&t; * SPDIF 0 User data [31:24]&n;&t;&t;&t;&t;&t;&t; * User data can be sent by using the SPDIF output frame pending and SPDIF output user bit interrupts.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|WATERMARK
mdefine_line|#define WATERMARK&t;&t;0x46&t;&t;/* Test bit to indicate cache usage level */
DECL|macro|SPDIF_INPUT_STATUS
mdefine_line|#define SPDIF_INPUT_STATUS&t;0x49&t;&t;/* SPDIF Input status register. Bits the same as SPCS.&n;&t;&t;&t;&t;&t;&t; * When Channel = 0: Bits the same as SPCS channel 0.&n;&t;&t;&t;&t;&t;&t; * When Channel = 1: Bits the same as SPCS channel 1.&n;&t;&t;&t;&t;&t;&t; * When Channel = 2:&n;&t;&t;&t;&t;&t;&t; * SPDIF Input User data [16:0]&n;&t;&t;&t;&t;&t;&t; * SPDIF Input Frame count [21:16]&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|CAPTURE_CACHE_DATA
mdefine_line|#define CAPTURE_CACHE_DATA&t;0x50&t;&t;/* 0x50-0x5f Recorded samples. */
DECL|macro|CAPTURE_SOURCE
mdefine_line|#define CAPTURE_SOURCE          0x60            /* Capture Source 0 = MIC */
DECL|macro|CAPTURE_SOURCE_CHANNEL0
mdefine_line|#define CAPTURE_SOURCE_CHANNEL0 0xf0000000&t;/* Mask for selecting the Capture sources */
DECL|macro|CAPTURE_SOURCE_CHANNEL1
mdefine_line|#define CAPTURE_SOURCE_CHANNEL1 0x0f000000&t;/* 0 - SPDIF mixer output. */
DECL|macro|CAPTURE_SOURCE_CHANNEL2
mdefine_line|#define CAPTURE_SOURCE_CHANNEL2 0x00f00000      /* 1 - What you hear or . 2 - ?? */
DECL|macro|CAPTURE_SOURCE_CHANNEL3
mdefine_line|#define CAPTURE_SOURCE_CHANNEL3 0x000f0000&t;/* 3 - Mic in, Line in, TAD in, Aux in. */
DECL|macro|CAPTURE_SOURCE_RECORD_MAP
mdefine_line|#define CAPTURE_SOURCE_RECORD_MAP 0x0000ffff&t;/* Default 0x00e4 */
multiline_comment|/* Record Map [7:0] (2 bits per channel) 0=mapped to channel 0, 1=mapped to channel 1, 2=mapped to channel2, 3=mapped to channel3 &n;&t;&t;&t;&t;&t;&t; * Record source select for channel 0 [18:16]&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 1 [22:20]&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 2 [26:24]&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 3 [30:28]&n;&t;&t;&t;&t;&t;&t; * 0 - SPDIF mixer output.&n;&t;&t;&t;&t;&t;&t; * 1 - i2s mixer output.&n;&t;&t;&t;&t;&t;&t; * 2 - SPDIF input.&n;&t;&t;&t;&t;&t;&t; * 3 - i2s input.&n;&t;&t;&t;&t;&t;&t; * 4 - AC97 capture.&n;&t;&t;&t;&t;&t;&t; * 5 - SRC output.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|CAPTURE_VOLUME1
mdefine_line|#define CAPTURE_VOLUME1         0x61            /* Capture  volume per channel 0-3 */
DECL|macro|CAPTURE_VOLUME2
mdefine_line|#define CAPTURE_VOLUME2         0x62            /* Capture  volume per channel 4-7 */
DECL|macro|PLAYBACK_ROUTING1
mdefine_line|#define PLAYBACK_ROUTING1       0x63            /* Playback routing of channels 0-7. Effects AC3 output. Default 0x32765410 */
DECL|macro|ROUTING1_REAR
mdefine_line|#define ROUTING1_REAR           0x77000000      /* Channel_id 0 sends to 10, Channel_id 1 sends to 32 */
DECL|macro|ROUTING1_NULL
mdefine_line|#define ROUTING1_NULL           0x00770000      /* Channel_id 2 sends to 54, Channel_id 3 sends to 76 */
DECL|macro|ROUTING1_CENTER_LFE
mdefine_line|#define ROUTING1_CENTER_LFE     0x00007700      /* 0x32765410 means, send Channel_id 0 to FRONT, Channel_id 1 to REAR */
DECL|macro|ROUTING1_FRONT
mdefine_line|#define ROUTING1_FRONT          0x00000077&t;/* Channel_id 2 to CENTER_LFE, Channel_id 3 to NULL. */
multiline_comment|/* Channel_id&squot;s handle stereo channels. Channel X is a single mono channel */
multiline_comment|/* Host is input from the PCI bus. */
multiline_comment|/* Host channel 0 [2:0] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 1 [6:4] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 2 [10:8] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 3 [14:12] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 4 [18:16] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 5 [22:20] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 6 [26:24] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * Host channel 7 [30:28] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PLAYBACK_ROUTING2
mdefine_line|#define PLAYBACK_ROUTING2       0x64            /* Playback Routing . Feeding Capture channels back into Playback. Effects AC3 output. Default 0x76767676 */
multiline_comment|/* SRC is input from the capture inputs. */
multiline_comment|/* SRC channel 0 [2:0] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 1 [6:4] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 2 [10:8] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 3 [14:12] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 4 [18:16] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 5 [22:20] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 6 [26:24] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; * SRC channel 7 [30:28] -&gt; SPDIF Mixer/Router channel 0-7.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PLAYBACK_MUTE
mdefine_line|#define PLAYBACK_MUTE           0x65            /* Unknown. While playing 0x0, while silent 0x00fc0000 */
multiline_comment|/* SPDIF Mixer input control:&n;&t;&t;&t;&t;&t;&t; * Invert SRC to SPDIF Mixer [7-0] (One bit per channel)&n;&t;&t;&t;&t;&t;&t; * Invert Host to SPDIF Mixer [15:8] (One bit per channel)&n;&t;&t;&t;&t;&t;&t; * SRC to SPDIF Mixer disable [23:16] (One bit per channel)&n;&t;&t;&t;&t;&t;&t; * Host to SPDIF Mixer disable [31:24] (One bit per channel)&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PLAYBACK_VOLUME1
mdefine_line|#define PLAYBACK_VOLUME1        0x66            /* Playback SPDIF volume per channel. Set to the same PLAYBACK_VOLUME(0x6a) */
multiline_comment|/* PLAYBACK_VOLUME1 must be set to 30303030 for SPDIF AC3 Playback */
multiline_comment|/* SPDIF mixer input volume. 0=12dB, 0x30=0dB, 0xFE=-51.5dB, 0xff=Mute */
multiline_comment|/* One register for each of the 4 stereo streams. */
multiline_comment|/* SRC Right volume [7:0]&n;&t;&t;&t;&t;&t;&t; * SRC Left  volume [15:8]&n;&t;&t;&t;&t;&t;&t; * Host Right volume [23:16]&n;&t;&t;&t;&t;&t;&t; * Host Left  volume [31:24]&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|CAPTURE_ROUTING1
mdefine_line|#define CAPTURE_ROUTING1        0x67            /* Capture Routing. Default 0x32765410 */
multiline_comment|/* Similar to register 0x63, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outputs to the Analog outputs instead of SPDIF. */
DECL|macro|CAPTURE_ROUTING2
mdefine_line|#define CAPTURE_ROUTING2        0x68            /* Unknown Routing. Default 0x76767676 */
multiline_comment|/* Similar to register 0x64, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outputs to the Analog outputs instead of SPDIF. */
DECL|macro|CAPTURE_MUTE
mdefine_line|#define CAPTURE_MUTE            0x69            /* Unknown. While capturing 0x0, while silent 0x00fc0000 */
multiline_comment|/* Similar to register 0x65, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outputs to the Analog outputs instead of SPDIF. */
DECL|macro|PLAYBACK_VOLUME2
mdefine_line|#define PLAYBACK_VOLUME2        0x6a            /* Playback Analog volume per channel. Does not effect AC3 output */
multiline_comment|/* Similar to register 0x66, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outputs to the Analog outputs instead of SPDIF. */
DECL|macro|UNKNOWN6b
mdefine_line|#define UNKNOWN6b               0x6b            /* Unknown. Readonly. Default 00400000 00400000 00400000 00400000 */
DECL|macro|UART_A_DATA
mdefine_line|#define UART_A_DATA&t;&t;0x6c            /* Uart, used in setting sample rates, bits per sample etc. */
DECL|macro|UART_A_CMD
mdefine_line|#define UART_A_CMD&t;&t;0x6d            /* Uart, used in setting sample rates, bits per sample etc. */
DECL|macro|UART_B_DATA
mdefine_line|#define UART_B_DATA&t;&t;0x6e            /* Uart, Unknown. */
DECL|macro|UART_B_CMD
mdefine_line|#define UART_B_CMD&t;&t;0x6f            /* Uart, Unknown. */
DECL|macro|SAMPLE_RATE_TRACKER_STATUS
mdefine_line|#define SAMPLE_RATE_TRACKER_STATUS 0x70         /* Readonly. Default 00108000 00108000 00500000 00500000 */
multiline_comment|/* Estimated sample rate [19:0] Relative to 48kHz. 0x8000 =  1.0&n;&t;&t;&t;&t;&t;&t; * Rate Locked [20]&n;&t;&t;&t;&t;&t;&t; * SPDIF Locked [21] For SPDIF channel only.&n;&t;&t;&t;&t;&t;&t; * Valid Audio [22] For SPDIF channel only.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|CAPTURE_CONTROL
mdefine_line|#define CAPTURE_CONTROL         0x71            /* Some sort of routing. default = 40c81000 30303030 30300000 00700000 */
multiline_comment|/* Channel_id 0: 0x40c81000 must be changed to 0x40c80000 for SPDIF AC3 input or output. */
multiline_comment|/* Channel_id 1: 0xffffffff(mute) 0x30303030(max) controls CAPTURE feedback into PLAYBACK. */
multiline_comment|/* Sample rate output control register Channel=0&n;&t;&t;&t;&t;&t;&t; * Sample output rate [1:0] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * Sample input rate [3:2] (0=48kHz, 1=Not available, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * SRC input source select [4] 0=Audio from digital mixer, 1=Audio from analog source.&n;&t;&t;&t;&t;&t;&t; * Record rate [9:8] (0=48kHz, 1=Not available, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * Record mixer output enable [12:10] &n;&t;&t;&t;&t;&t;&t; * I2S input rate master mode [15:14] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * I2S output rate [17:16] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * I2S output source select [18] (0=Audio from host, 1=Audio from SRC)&n;&t;&t;&t;&t;&t;&t; * Record mixer I2S enable [20:19] (enable/disable i2sin1 and i2sin0)&n;&t;&t;&t;&t;&t;&t; * I2S output master clock select [21] (0=256*I2S output rate, 1=512*I2S output rate.)&n;&t;&t;&t;&t;&t;&t; * I2S input master clock select [22] (0=256*I2S input rate, 1=512*I2S input rate.)&n;&t;&t;&t;&t;&t;&t; * I2S input mode [23] (0=Slave, 1=Master)&n;&t;&t;&t;&t;&t;&t; * SPDIF output rate [25:24] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)&n;&t;&t;&t;&t;&t;&t; * SPDIF output source select [26] (0=host, 1=SRC)&n;&t;&t;&t;&t;&t;&t; * Not used [27]&n;&t;&t;&t;&t;&t;&t; * Record Source 0 input [29:28] (0=SPDIF in, 1=I2S in, 2=AC97 Mic, 3=AC97 PCM)&n;&t;&t;&t;&t;&t;&t; * Record Source 1 input [31:30] (0=SPDIF in, 1=I2S in, 2=AC97 Mic, 3=AC97 PCM)&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Sample rate output control register Channel=1&n;&t;&t;&t;&t;&t;&t; * I2S Input 0 volume Right [7:0]&n;&t;&t;&t;&t;&t;&t; * I2S Input 0 volume Left [15:8]&n;&t;&t;&t;&t;&t;&t; * I2S Input 1 volume Right [23:16]&n;&t;&t;&t;&t;&t;&t; * I2S Input 1 volume Left [31:24]&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Sample rate output control register Channel=2&n;&t;&t;&t;&t;&t;&t; * SPDIF Input volume Right [23:16]&n;&t;&t;&t;&t;&t;&t; * SPDIF Input volume Left [31:24]&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Sample rate output control register Channel=3&n;&t;&t;&t;&t;&t;&t; * No used&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|SPDIF_SELECT2
mdefine_line|#define SPDIF_SELECT2           0x72            /* Some sort of routing. Channel_id 0 only. default = 0x0f0f003f. Analog 0x000b0000, Digital 0x0b000000 */
DECL|macro|ROUTING2_FRONT_MASK
mdefine_line|#define ROUTING2_FRONT_MASK     0x00010000      /* Enable for Front speakers. */
DECL|macro|ROUTING2_CENTER_LFE_MASK
mdefine_line|#define ROUTING2_CENTER_LFE_MASK 0x00020000     /* Enable for Center/LFE speakers. */
DECL|macro|ROUTING2_REAR_MASK
mdefine_line|#define ROUTING2_REAR_MASK      0x00080000      /* Enable for Rear speakers. */
multiline_comment|/* Audio output control&n;&t;&t;&t;&t;&t;&t; * AC97 output enable [5:0]&n;&t;&t;&t;&t;&t;&t; * I2S output enable [19:16]&n;&t;&t;&t;&t;&t;&t; * SPDIF output enable [27:24]&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|UNKNOWN73
mdefine_line|#define UNKNOWN73               0x73            /* Unknown. Readonly. Default 0x0 */
DECL|macro|CHIP_VERSION
mdefine_line|#define CHIP_VERSION            0x74            /* P17 Chip version. Channel_id 0 only. Default 00000071 */
DECL|macro|EXTENDED_INT_MASK
mdefine_line|#define EXTENDED_INT_MASK       0x75            /* Used by both playback and capture interrupt handler */
multiline_comment|/* Sets which Interrupts are enabled. */
multiline_comment|/* 0x00000001 = Half period. Playback.&n;&t;&t;&t;&t;&t;&t; * 0x00000010 = Full period. Playback.&n;&t;&t;&t;&t;&t;&t; * 0x00000100 = Half buffer. Playback.&n;&t;&t;&t;&t;&t;&t; * 0x00001000 = Full buffer. Playback.&n;&t;&t;&t;&t;&t;&t; * 0x00010000 = Half buffer. Capture.&n;&t;&t;&t;&t;&t;&t; * 0x00100000 = Full buffer. Capture.&n;&t;&t;&t;&t;&t;&t; * Capture can only do 2 periods.&n;&t;&t;&t;&t;&t;&t; * 0x01000000 = End audio. Playback.&n;&t;&t;&t;&t;&t;&t; * 0x40000000 = Half buffer Playback,Caputre xrun.&n;&t;&t;&t;&t;&t;&t; * 0x80000000 = Full buffer Playback,Caputre xrun.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|EXTENDED_INT
mdefine_line|#define EXTENDED_INT            0x76            /* Used by both playback and capture interrupt handler */
multiline_comment|/* Shows which interrupts are active at the moment. */
multiline_comment|/* Same bit layout as EXTENDED_INT_MASK */
DECL|macro|COUNTER77
mdefine_line|#define COUNTER77               0x77&t;&t;/* Counter range 0 to 0x3fffff, 192000 counts per second. */
DECL|macro|COUNTER78
mdefine_line|#define COUNTER78               0x78&t;&t;/* Counter range 0 to 0x3fffff, 44100 counts per second. */
DECL|macro|EXTENDED_INT_TIMER
mdefine_line|#define EXTENDED_INT_TIMER      0x79            /* Channel_id 0 only. Used by both playback and capture interrupt handler */
multiline_comment|/* Causes interrupts based on timer intervals. */
DECL|macro|SPI
mdefine_line|#define SPI&t;&t;&t;0x7a&t;&t;/* SPI: Serial Interface Register */
DECL|macro|I2C_A
mdefine_line|#define I2C_A&t;&t;&t;0x7b&t;&t;/* I2C Address. 32 bit */
DECL|macro|I2C_0
mdefine_line|#define I2C_0&t;&t;&t;0x7c&t;&t;/* I2C Data Port 0. 32 bit */
DECL|macro|I2C_1
mdefine_line|#define I2C_1&t;&t;&t;0x7d&t;&t;/* I2C Data Port 1. 32 bit */
DECL|macro|SET_CHANNEL
mdefine_line|#define SET_CHANNEL 0  /* Testing channel outputs 0=Front, 1=Center/LFE, 2=Unknown, 3=Rear */
DECL|macro|PCM_FRONT_CHANNEL
mdefine_line|#define PCM_FRONT_CHANNEL 0
DECL|macro|PCM_REAR_CHANNEL
mdefine_line|#define PCM_REAR_CHANNEL 1
DECL|macro|PCM_CENTER_LFE_CHANNEL
mdefine_line|#define PCM_CENTER_LFE_CHANNEL 2
DECL|macro|PCM_UNKNOWN_CHANNEL
mdefine_line|#define PCM_UNKNOWN_CHANNEL 3
DECL|macro|CONTROL_FRONT_CHANNEL
mdefine_line|#define CONTROL_FRONT_CHANNEL 0
DECL|macro|CONTROL_REAR_CHANNEL
mdefine_line|#define CONTROL_REAR_CHANNEL 3
DECL|macro|CONTROL_CENTER_LFE_CHANNEL
mdefine_line|#define CONTROL_CENTER_LFE_CHANNEL 1
DECL|macro|CONTROL_UNKNOWN_CHANNEL
mdefine_line|#define CONTROL_UNKNOWN_CHANNEL 2
DECL|typedef|ca0106_channel_t
r_typedef
r_struct
id|snd_ca0106_channel
id|ca0106_channel_t
suffix:semicolon
DECL|typedef|ca0106_t
r_typedef
r_struct
id|snd_ca0106
id|ca0106_t
suffix:semicolon
DECL|typedef|ca0106_pcm_t
r_typedef
r_struct
id|snd_ca0106_pcm
id|ca0106_pcm_t
suffix:semicolon
DECL|struct|snd_ca0106_channel
r_struct
id|snd_ca0106_channel
(brace
DECL|member|emu
id|ca0106_t
op_star
id|emu
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|use
r_int
id|use
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
id|ca0106_t
op_star
id|emu
comma
id|ca0106_channel_t
op_star
id|channel
)paren
suffix:semicolon
DECL|member|epcm
id|ca0106_pcm_t
op_star
id|epcm
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_ca0106_pcm
r_struct
id|snd_ca0106_pcm
(brace
DECL|member|emu
id|ca0106_t
op_star
id|emu
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|channel_id
r_int
id|channel_id
suffix:semicolon
DECL|member|running
r_int
r_int
id|running
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// definition of the chip-specific record
DECL|struct|snd_ca0106
r_struct
id|snd_ca0106
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
multiline_comment|/* chip revision */
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|model
r_int
r_int
id|model
suffix:semicolon
multiline_comment|/* subsystem id */
DECL|member|emu_lock
id|spinlock_t
id|emu_lock
suffix:semicolon
DECL|member|ac97
id|ac97_t
op_star
id|ac97
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|playback_channels
id|ca0106_channel_t
id|playback_channels
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|capture_channels
id|ca0106_channel_t
id|capture_channels
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|spdif_bits
id|u32
id|spdif_bits
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* s/pdif out setup */
DECL|member|spdif_enable
r_int
id|spdif_enable
suffix:semicolon
DECL|member|capture_source
r_int
id|capture_source
suffix:semicolon
DECL|member|buffer
r_struct
id|snd_dma_buffer
id|buffer
suffix:semicolon
)brace
suffix:semicolon
r_int
id|__devinit
id|snd_ca0106_mixer
c_func
(paren
id|ca0106_t
op_star
id|emu
)paren
suffix:semicolon
r_int
id|__devinit
id|snd_ca0106_proc_init
c_func
(paren
id|ca0106_t
op_star
id|emu
)paren
suffix:semicolon
r_int
r_int
id|snd_ca0106_ptr_read
c_func
(paren
id|ca0106_t
op_star
id|emu
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|chn
)paren
suffix:semicolon
r_void
id|snd_ca0106_ptr_write
c_func
(paren
id|ca0106_t
op_star
id|emu
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|chn
comma
r_int
r_int
id|data
)paren
suffix:semicolon
eof
