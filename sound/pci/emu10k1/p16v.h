multiline_comment|/*&n; *  Copyright (c) by James Courtier-Dutton &lt;James@superbug.demon.co.uk&gt;&n; *  Driver p16v chips&n; *  Version: 0.21&n; *&n; *  FEATURES currently supported:&n; *    Output fixed at S32_LE, 2 channel to hw:0,0&n; *    Rates: 44.1, 48, 96, 192.&n; *&n; *  Changelog:&n; *  0.8&n; *    Use separate card based buffer for periods table.&n; *  0.9&n; *    Use 2 channel output streams instead of 8 channel.&n; *       (8 channel output streams might be good for ASIO type output)&n; *    Corrected speaker output, so Front -&gt; Front etc.&n; *  0.10&n; *    Fixed missed interrupts.&n; *  0.11&n; *    Add Sound card model number and names.&n; *    Add Analog volume controls.&n; *  0.12&n; *    Corrected playback interrupts. Now interrupt per period, instead of half period.&n; *  0.13&n; *    Use single trigger for multichannel.&n; *  0.14&n; *    Mic capture now works at fixed: S32_LE, 96000Hz, Stereo.&n; *  0.15&n; *    Force buffer_size / period_size == INTEGER.&n; *  0.16&n; *    Update p16v.c to work with changed alsa api.&n; *  0.17&n; *    Update p16v.c to work with changed alsa api. Removed boot_devs.&n; *  0.18&n; *    Merging with snd-emu10k1 driver.&n; *  0.19&n; *    One stereo channel at 24bit now works.&n; *  0.20&n; *    Added better register defines.&n; *  0.21&n; *    Split from p16v.c&n; *&n; *&n; *  BUGS:&n; *    Some stability problems when unloading the snd-p16v kernel module.&n; *    --&n; *&n; *  TODO:&n; *    SPDIF out.&n; *    Find out how to change capture sample rates. E.g. To record SPDIF at 48000Hz.&n; *    Currently capture fixed at 48000Hz.&n; *&n; *    --&n; *  GENERAL INFO:&n; *    Model: SB0240&n; *    P16V Chip: CA0151-DBS&n; *    Audigy 2 Chip: CA0102-IAT&n; *    AC97 Codec: STAC 9721&n; *    ADC: Philips 1361T (Stereo 24bit)&n; *    DAC: CS4382-K (8-channel, 24bit, 192Khz)&n; *&n; *  This code was initally based on code from ALSA&squot;s emu10k1x.c which is:&n; *  Copyright (c) by Francisco Moraes &lt;fmoraes@nc.rr.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/********************************************************************************************************/
multiline_comment|/* Audigy2 P16V pointer-offset register set, accessed through the PTR2 and DATA2 registers                     */
multiline_comment|/********************************************************************************************************/
multiline_comment|/* The sample rate of the SPDIF outputs is set by modifying a register in the EMU10K2 PTR register A_SPDIF_SAMPLERATE.&n; * The sample rate is also controlled by the same registers that control the rate of the EMU10K2 sample rate converters.&n; */
multiline_comment|/* Initally all registers from 0x00 to 0x3f have zero contents. */
DECL|macro|PLAYBACK_LIST_ADDR
mdefine_line|#define PLAYBACK_LIST_ADDR&t;0x00&t;&t;/* Base DMA address of a list of pointers to each period/size */
multiline_comment|/* One list entry: 4 bytes for DMA address, &n;&t;&t;&t;&t;&t;&t; * 4 bytes for period_size &lt;&lt; 16.&n;&t;&t;&t;&t;&t;&t; * One list entry is 8 bytes long.&n;&t;&t;&t;&t;&t;&t; * One list entry for each period in the buffer.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PLAYBACK_LIST_SIZE
mdefine_line|#define PLAYBACK_LIST_SIZE&t;0x01&t;&t;/* Size of list in bytes &lt;&lt; 16. E.g. 8 periods -&gt; 0x00380000  */
DECL|macro|PLAYBACK_LIST_PTR
mdefine_line|#define PLAYBACK_LIST_PTR&t;0x02&t;&t;/* Pointer to the current period being played */
DECL|macro|PLAYBACK_UNKNOWN3
mdefine_line|#define PLAYBACK_UNKNOWN3&t;0x03&t;&t;/* Not used */
DECL|macro|PLAYBACK_DMA_ADDR
mdefine_line|#define PLAYBACK_DMA_ADDR&t;0x04&t;&t;/* Playback DMA addresss */
DECL|macro|PLAYBACK_PERIOD_SIZE
mdefine_line|#define PLAYBACK_PERIOD_SIZE&t;0x05&t;&t;/* Playback period size. win2000 uses 0x04000000 */
DECL|macro|PLAYBACK_POINTER
mdefine_line|#define PLAYBACK_POINTER&t;0x06&t;&t;/* Playback period pointer. Used with PLAYBACK_LIST_PTR to determine buffer position currently in DAC */
DECL|macro|PLAYBACK_FIFO_END_ADDRESS
mdefine_line|#define PLAYBACK_FIFO_END_ADDRESS&t;0x07&t;&t;/* Playback FIFO end address */
DECL|macro|PLAYBACK_FIFO_POINTER
mdefine_line|#define PLAYBACK_FIFO_POINTER&t;0x08&t;&t;/* Playback FIFO pointer and number of valid sound samples in cache */
DECL|macro|PLAYBACK_UNKNOWN9
mdefine_line|#define PLAYBACK_UNKNOWN9&t;0x09&t;&t;/* Not used */
DECL|macro|CAPTURE_DMA_ADDR
mdefine_line|#define CAPTURE_DMA_ADDR&t;0x10&t;&t;/* Capture DMA address */
DECL|macro|CAPTURE_BUFFER_SIZE
mdefine_line|#define CAPTURE_BUFFER_SIZE&t;0x11&t;&t;/* Capture buffer size */
DECL|macro|CAPTURE_POINTER
mdefine_line|#define CAPTURE_POINTER&t;&t;0x12&t;&t;/* Capture buffer pointer. Sample currently in ADC */
DECL|macro|CAPTURE_FIFO_POINTER
mdefine_line|#define CAPTURE_FIFO_POINTER&t;0x13&t;&t;/* Capture FIFO pointer and number of valid sound samples in cache */
DECL|macro|CAPTURE_P16V_VOLUME1
mdefine_line|#define CAPTURE_P16V_VOLUME1&t;0x14&t;&t;/* Low: Capture volume 0xXXXX3030 */
DECL|macro|CAPTURE_P16V_VOLUME2
mdefine_line|#define CAPTURE_P16V_VOLUME2&t;0x15&t;&t;/* High:Has no effect on capture volume */
DECL|macro|CAPTURE_P16V_SOURCE
mdefine_line|#define CAPTURE_P16V_SOURCE     0x16            /* P16V source select. Set to 0x0700E4E5 for AC97 CAPTURE */
multiline_comment|/* [0:1] Capture input 0 channel select. 0 = Capture output 0.&n;&t;&t;&t;&t;&t;&t; *                                       1 = Capture output 1.&n;&t;&t;&t;&t;&t;&t; *                                       2 = Capture output 2.&n;&t;&t;&t;&t;&t;&t; *                                       3 = Capture output 3.&n;&t;&t;&t;&t;&t;&t; * [3:2] Capture input 1 channel select. 0 = Capture output 0.&n;&t;&t;&t;&t;&t;&t; *                                       1 = Capture output 1.&n;&t;&t;&t;&t;&t;&t; *                                       2 = Capture output 2.&n;&t;&t;&t;&t;&t;&t; *                                       3 = Capture output 3.&n;&t;&t;&t;&t;&t;&t; * [5:4] Capture input 2 channel select. 0 = Capture output 0.&n;&t;&t;&t;&t;&t;&t; *                                       1 = Capture output 1.&n;&t;&t;&t;&t;&t;&t; *                                       2 = Capture output 2.&n;&t;&t;&t;&t;&t;&t; *                                       3 = Capture output 3.&n;&t;&t;&t;&t;&t;&t; * [7:6] Capture input 3 channel select. 0 = Capture output 0.&n;&t;&t;&t;&t;&t;&t; *                                       1 = Capture output 1.&n;&t;&t;&t;&t;&t;&t; *                                       2 = Capture output 2.&n;&t;&t;&t;&t;&t;&t; *                                       3 = Capture output 3.&n;&t;&t;&t;&t;&t;&t; * [9:8] Playback input 0 channel select. 0 = Play output 0.&n;&t;&t;&t;&t;&t;&t; *                                        1 = Play output 1.&n;&t;&t;&t;&t;&t;&t; *                                        2 = Play output 2.&n;&t;&t;&t;&t;&t;&t; *                                        3 = Play output 3.&n;&t;&t;&t;&t;&t;&t; * [11:10] Playback input 1 channel select. 0 = Play output 0.&n;&t;&t;&t;&t;&t;&t; *                                          1 = Play output 1.&n;&t;&t;&t;&t;&t;&t; *                                          2 = Play output 2.&n;&t;&t;&t;&t;&t;&t; *                                          3 = Play output 3.&n;&t;&t;&t;&t;&t;&t; * [13:12] Playback input 2 channel select. 0 = Play output 0.&n;&t;&t;&t;&t;&t;&t; *                                          1 = Play output 1.&n;&t;&t;&t;&t;&t;&t; *                                          2 = Play output 2.&n;&t;&t;&t;&t;&t;&t; *                                          3 = Play output 3.&n;&t;&t;&t;&t;&t;&t; * [15:14] Playback input 3 channel select. 0 = Play output 0.&n;&t;&t;&t;&t;&t;&t; *                                          1 = Play output 1.&n;&t;&t;&t;&t;&t;&t; *                                          2 = Play output 2.&n;&t;&t;&t;&t;&t;&t; *                                          3 = Play output 3.&n;&t;&t;&t;&t;&t;&t; * [19:16] Playback mixer output enable. 1 bit per channel.&n;&t;&t;&t;&t;&t;&t; * [23:20] Capture mixer output enable. 1 bit per channel.&n;&t;&t;&t;&t;&t;&t; * [26:24] FX engine channel capture 0 = 0x60-0x67.&n;&t;&t;&t;&t;&t;&t; *                                   1 = 0x68-0x6f.&n;&t;&t;&t;&t;&t;&t; *                                   2 = 0x70-0x77.&n;&t;&t;&t;&t;&t;&t; *                                   3 = 0x78-0x7f.&n;&t;&t;&t;&t;&t;&t; *                                   4 = 0x80-0x87.&n;&t;&t;&t;&t;&t;&t; *                                   5 = 0x88-0x8f.&n;&t;&t;&t;&t;&t;&t; *                                   6 = 0x90-0x97.&n;&t;&t;&t;&t;&t;&t; *                                   7 = 0x98-0x9f.&n;&t;&t;&t;&t;&t;&t; * [31:27] Not used.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 0x1 = capture on.&n;&t;&t;&t;&t;&t;&t; * 0x100 = capture off.&n;&t;&t;&t;&t;&t;&t; * 0x200 = capture off.&n;&t;&t;&t;&t;&t;&t; * 0x1000 = capture off.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|CAPTURE_RATE_STATUS
mdefine_line|#define CAPTURE_RATE_STATUS&t;&t;0x17&t;&t;/* Capture sample rate. Read only */
multiline_comment|/* [15:0] Not used.&n;&t;&t;&t;&t;&t;&t; * [18:16] Channel 0 Detected sample rate. 0 - 44.1khz&n;&t;&t;&t;&t;&t;&t; *                               1 - 48 khz&n;&t;&t;&t;&t;&t;&t; *                               2 - 96 khz&n;&t;&t;&t;&t;&t;&t; *                               3 - 192 khz&n;&t;&t;&t;&t;&t;&t; *                               7 - undefined rate.&n;&t;&t;&t;&t;&t;&t; * [19] Channel 0. 1 - Valid, 0 - Not Valid.&n;&t;&t;&t;&t;&t;&t; * [22:20] Channel 1 Detected sample rate. &n;&t;&t;&t;&t;&t;&t; * [23] Channel 1. 1 - Valid, 0 - Not Valid.&n;&t;&t;&t;&t;&t;&t; * [26:24] Channel 2 Detected sample rate. &n;&t;&t;&t;&t;&t;&t; * [27] Channel 2. 1 - Valid, 0 - Not Valid.&n;&t;&t;&t;&t;&t;&t; * [30:28] Channel 3 Detected sample rate. &n;&t;&t;&t;&t;&t;&t; * [31] Channel 3. 1 - Valid, 0 - Not Valid.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 0x18 - 0x1f unused */
DECL|macro|PLAYBACK_LAST_SAMPLE
mdefine_line|#define PLAYBACK_LAST_SAMPLE    0x20&t;&t;/* The sample currently being played. Read only */
multiline_comment|/* 0x21 - 0x3f unused */
DECL|macro|BASIC_INTERRUPT
mdefine_line|#define BASIC_INTERRUPT         0x40&t;&t;/* Used by both playback and capture interrupt handler */
multiline_comment|/* Playback (0x1&lt;&lt;channel_id) Don&squot;t touch high 16bits. */
multiline_comment|/* Capture  (0x100&lt;&lt;channel_id). not tested */
multiline_comment|/* Start Playback [3:0] (one bit per channel)&n;&t;&t;&t;&t;&t;&t; * Start Capture [11:8] (one bit per channel)&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 0 [18:16]&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 1 [22:20]&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 2 [26:24]&n;&t;&t;&t;&t;&t;&t; * Record source select for channel 3 [30:28]&n;&t;&t;&t;&t;&t;&t; * 0 - SPDIF channel.&n;&t;&t;&t;&t;&t;&t; * 1 - I2S channel.&n;&t;&t;&t;&t;&t;&t; * 2 - SRC48 channel.&n;&t;&t;&t;&t;&t;&t; * 3 - SRCMulti_SPDIF channel.&n;&t;&t;&t;&t;&t;&t; * 4 - SRCMulti_I2S channel.&n;&t;&t;&t;&t;&t;&t; * 5 - SPDIF channel.&n;&t;&t;&t;&t;&t;&t; * 6 - fxengine capture.&n;&t;&t;&t;&t;&t;&t; * 7 - AC97 capture.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Default 41110000.&n;&t;&t;&t;&t;&t;&t; * Writing 0xffffffff hangs the PC.&n;&t;&t;&t;&t;&t;&t; * Writing 0xffff0000 -&gt; 77770000 so it must be some sort of route.&n;&t;&t;&t;&t;&t;&t; * bit 0x1 starts DMA playback on channel_id 0&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 0x41,42 take values from 0 - 0xffffffff, but have no effect on playback */
multiline_comment|/* 0x43,0x48 do not remember settings */
multiline_comment|/* 0x41-45 unused */
DECL|macro|WATERMARK
mdefine_line|#define WATERMARK            0x46&t;&t;/* Test bit to indicate cache level usage */
multiline_comment|/* Values it can have while playing on channel 0. &n;&t;&t;&t;&t;&t;&t; * 0000f000, 0000f004, 0000f008, 0000f00c.&n;&t;&t;&t;&t;&t;&t; * Readonly.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 0x47-0x4f unused */
multiline_comment|/* 0x50-0x5f Capture cache data */
DECL|macro|SRCSel
mdefine_line|#define SRCSel&t;&t;&t;0x60            /* SRCSel. Default 0x4. Bypass P16V 0x14 */
multiline_comment|/* [0] 0 = 10K2 audio, 1 = SRC48 mixer output.&n;&t;&t;&t;&t;&t;&t; * [2] 0 = 10K2 audio, 1 = SRCMulti SPDIF mixer output.&n;&t;&t;&t;&t;&t;&t; * [4] 0 = 10K2 audio, 1 = SRCMulti I2S mixer output.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* SRC48 converts samples rates 44.1, 48, 96, 192 to 48 khz. */
multiline_comment|/* SRCMulti converts 48khz samples rates to 44.1, 48, 96, 192 to 48. */
multiline_comment|/* SRC48 and SRCMULTI sample rate select and output select. */
multiline_comment|/* 0xffffffff -&gt; 0xC0000015&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXXX4 = Enable Front Left/Right&n;&t;&t;&t;&t;&t;&t; * Enable PCMs&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 0x61 -&gt; 0x6c are Volume controls */
DECL|macro|PLAYBACK_VOLUME_MIXER1
mdefine_line|#define PLAYBACK_VOLUME_MIXER1  0x61&t;&t;/* SRC48 Low to mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER2
mdefine_line|#define PLAYBACK_VOLUME_MIXER2  0x62&t;&t;/* SRC48 High to mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER3
mdefine_line|#define PLAYBACK_VOLUME_MIXER3  0x63&t;&t;/* SRCMULTI SPDIF Low to mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER4
mdefine_line|#define PLAYBACK_VOLUME_MIXER4  0x64&t;&t;/* SRCMULTI SPDIF High to mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER5
mdefine_line|#define PLAYBACK_VOLUME_MIXER5  0x65&t;&t;/* SRCMULTI I2S Low to mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER6
mdefine_line|#define PLAYBACK_VOLUME_MIXER6  0x66&t;&t;/* SRCMULTI I2S High to mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER7
mdefine_line|#define PLAYBACK_VOLUME_MIXER7  0x67&t;&t;/* P16V Low to SRCMULTI SPDIF mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER8
mdefine_line|#define PLAYBACK_VOLUME_MIXER8  0x68&t;&t;/* P16V High to SRCMULTI SPDIF mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER9
mdefine_line|#define PLAYBACK_VOLUME_MIXER9  0x69&t;&t;/* P16V Low to SRCMULTI I2S mixer input volume control. */
multiline_comment|/* 0xXXXX3030 = PCM0 Volume (Front).&n;&t;&t;&t;&t;&t;&t; * 0x3030XXXX = PCM1 Volume (Center)&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PLAYBACK_VOLUME_MIXER10
mdefine_line|#define PLAYBACK_VOLUME_MIXER10  0x6a&t;&t;/* P16V High to SRCMULTI I2S mixer input volume control. */
multiline_comment|/* 0x3030XXXX = PCM3 Volume (Rear). */
DECL|macro|PLAYBACK_VOLUME_MIXER11
mdefine_line|#define PLAYBACK_VOLUME_MIXER11  0x6b&t;&t;/* E10K2 Low to SRC48 mixer input volume control. */
DECL|macro|PLAYBACK_VOLUME_MIXER12
mdefine_line|#define PLAYBACK_VOLUME_MIXER12 0x6c&t;&t;/* E10K2 High to SRC48 mixer input volume control. */
DECL|macro|SRC48_ENABLE
mdefine_line|#define SRC48_ENABLE            0x6d            /* SRC48 input audio enable */
multiline_comment|/* SRC48 converts samples rates 44.1, 48, 96, 192 to 48 khz. */
multiline_comment|/* [23:16] The corresponding P16V channel to SRC48 enabled if == 1.&n;&t;&t;&t;&t;&t;&t; * [31:24] The corresponding E10K2 channel to SRC48 enabled.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|SRCMULTI_ENABLE
mdefine_line|#define SRCMULTI_ENABLE         0x6e            /* SRCMulti input audio enable. Default 0xffffffff */
multiline_comment|/* SRCMulti converts 48khz samples rates to 44.1, 48, 96, 192 to 48. */
multiline_comment|/* [7:0] The corresponding P16V channel to SRCMulti_I2S enabled if == 1.&n;&t;&t;&t;&t;&t;&t; * [15:8] The corresponding E10K2 channel to SRCMulti I2S enabled.&n;&t;&t;&t;&t;&t;&t; * [23:16] The corresponding P16V channel to SRCMulti SPDIF enabled.&n;&t;&t;&t;&t;&t;&t; * [31:24] The corresponding E10K2 channel to SRCMulti SPDIF enabled.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Bypass P16V 0xff00ff00 &n;&t;&t;&t;&t;&t;&t; * Bitmap. 0 = Off, 1 = On.&n;&t;&t;&t;&t;&t;&t; * P16V playback outputs:&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXXX1 = PCM0 Left. (Front)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXXX2 = PCM0 Right.&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXXX4 = PCM1 Left. (Center/LFE)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXXX8 = PCM1 Right.&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX1X = PCM2 Left. (Unknown)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX2X = PCM2 Right.&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX4X = PCM3 Left. (Rear)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX8X = PCM3 Right.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|AUDIO_OUT_ENABLE
mdefine_line|#define AUDIO_OUT_ENABLE        0x6f            /* Default: 000100FF */
multiline_comment|/* [3:0] Does something, but not documented. Probably capture enable.&n;&t;&t;&t;&t;&t;&t; * [7:4] Playback channels enable. not documented.&n;&t;&t;&t;&t;&t;&t; * [16] AC97 output enable if == 1&n;&t;&t;&t;&t;&t;&t; * [30] 0 = SRCMulti_I2S input from fxengine 0x68-0x6f.&n;&t;&t;&t;&t;&t;&t; *      1 = SRCMulti_I2S input from SRC48 output.&n;&t;&t;&t;&t;&t;&t; * [31] 0 = SRCMulti_SPDIF input from fxengine 0x60-0x67.&n;&t;&t;&t;&t;&t;&t; *      1 = SRCMulti_SPDIF input from SRC48 output.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* 0xffffffff -&gt; C00100FF */
multiline_comment|/* 0 -&gt; Not playback sound, irq still running */
multiline_comment|/* 0xXXXXXX10 = PCM0 Left/Right On. (Front)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX20 = PCM1 Left/Right On. (Center/LFE)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX40 = PCM2 Left/Right On. (Unknown)&n;&t;&t;&t;&t;&t;&t; * 0xXXXXXX80 = PCM3 Left/Right On. (Rear)&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PLAYBACK_SPDIF_SELECT
mdefine_line|#define PLAYBACK_SPDIF_SELECT     0x70          /* Default: 12030F00 */
multiline_comment|/* 0xffffffff -&gt; 3FF30FFF */
multiline_comment|/* 0x00000001 pauses stream/irq fail. */
multiline_comment|/* All other bits do not effect playback */
DECL|macro|PLAYBACK_SPDIF_SRC_SELECT
mdefine_line|#define PLAYBACK_SPDIF_SRC_SELECT 0x71          /* Default: 0000E4E4 */
multiline_comment|/* 0xffffffff -&gt; F33FFFFF */
multiline_comment|/* All bits do not effect playback */
DECL|macro|PLAYBACK_SPDIF_USER_DATA0
mdefine_line|#define PLAYBACK_SPDIF_USER_DATA0 0x72&t;&t;/* SPDIF out user data 0 */
DECL|macro|PLAYBACK_SPDIF_USER_DATA1
mdefine_line|#define PLAYBACK_SPDIF_USER_DATA1 0x73&t;&t;/* SPDIF out user data 1 */
multiline_comment|/* 0x74-0x75 unknown */
DECL|macro|CAPTURE_SPDIF_CONTROL
mdefine_line|#define CAPTURE_SPDIF_CONTROL&t;0x76&t;&t;/* SPDIF in control setting */
DECL|macro|CAPTURE_SPDIF_STATUS
mdefine_line|#define CAPTURE_SPDIF_STATUS&t;0x77&t;&t;/* SPDIF in status */
DECL|macro|CAPURE_SPDIF_USER_DATA0
mdefine_line|#define CAPURE_SPDIF_USER_DATA0 0x78&t;&t;/* SPDIF in user data 0 */
DECL|macro|CAPURE_SPDIF_USER_DATA1
mdefine_line|#define CAPURE_SPDIF_USER_DATA1 0x79&t;&t;/* SPDIF in user data 1 */
DECL|macro|CAPURE_SPDIF_USER_DATA2
mdefine_line|#define CAPURE_SPDIF_USER_DATA2 0x7a&t;&t;/* SPDIF in user data 2 */
eof
