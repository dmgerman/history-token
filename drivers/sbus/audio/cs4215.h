multiline_comment|/* $Id: cs4215.h,v 1.8 2000/10/27 07:01:38 uzi Exp $&n; * drivers/sbus/audio/cs4215.h&n; *&n; * Copyright (C) 1997 Rudolf Koenig (rfkoenig@immd4.informatik.uni-erlangen.de)&n; * Used with dbri.h&n; */
macro_line|#ifndef _CS4215_H_
DECL|macro|_CS4215_H_
mdefine_line|#define _CS4215_H_
DECL|struct|cs4215
r_struct
id|cs4215
(brace
DECL|member|data
id|__u8
id|data
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Data mode: Time slots 5-8 */
DECL|member|ctrl
id|__u8
id|ctrl
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Ctrl mode: Time slots 1-4 */
DECL|member|onboard
id|__u8
id|onboard
suffix:semicolon
DECL|member|offset
id|__u8
id|offset
suffix:semicolon
multiline_comment|/* Bit offset from frame sync to time slot 1 */
DECL|member|status
r_volatile
id|__u32
id|status
suffix:semicolon
DECL|member|version
r_volatile
id|__u32
id|version
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Control mode first &n; */
multiline_comment|/* Time Slot 1, Status register */
DECL|macro|CS4215_CLB
mdefine_line|#define CS4215_CLB&t;(1&lt;&lt;2)&t;/* Control Latch Bit */
DECL|macro|CS4215_OLB
mdefine_line|#define CS4215_OLB&t;(1&lt;&lt;3)&t;/* 1: line: 2.0V, speaker 4V */
multiline_comment|/* 0: line: 2.8V, speaker 8V */
DECL|macro|CS4215_MLB
mdefine_line|#define CS4215_MLB&t;(1&lt;&lt;4)&t;/* 1: Microphone: 20dB gain disabled */
DECL|macro|CS4215_RSRVD_1
mdefine_line|#define CS4215_RSRVD_1  (1&lt;&lt;5)
multiline_comment|/* Time Slot 2, Data Format Register */
DECL|macro|CS4215_DFR_LINEAR16
mdefine_line|#define CS4215_DFR_LINEAR16&t;0
DECL|macro|CS4215_DFR_ULAW
mdefine_line|#define CS4215_DFR_ULAW&t;&t;1
DECL|macro|CS4215_DFR_ALAW
mdefine_line|#define CS4215_DFR_ALAW&t;&t;2
DECL|macro|CS4215_DFR_LINEAR8
mdefine_line|#define CS4215_DFR_LINEAR8&t;3
DECL|macro|CS4215_DFR_STEREO
mdefine_line|#define CS4215_DFR_STEREO&t;(1&lt;&lt;2)
r_static
r_struct
(brace
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
DECL|member|xtal
r_int
r_char
id|xtal
suffix:semicolon
DECL|member|csval
r_int
r_char
id|csval
suffix:semicolon
DECL|variable|CS4215_FREQ
)brace
id|CS4215_FREQ
(braket
)braket
op_assign
(brace
(brace
l_int|8000
comma
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
(paren
l_int|0
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|16000
comma
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
(paren
l_int|1
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|27429
comma
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
(paren
l_int|2
op_lshift
l_int|3
)paren
)brace
comma
multiline_comment|/* Actually 24428.57 */
(brace
l_int|32000
comma
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
(paren
l_int|3
op_lshift
l_int|3
)paren
)brace
comma
multiline_comment|/* {&t; NA,&t;(1&lt;&lt;4),&t;(4&lt;&lt;3)&t;}, */
multiline_comment|/* {&t; NA,&t;(1&lt;&lt;4),&t;(5&lt;&lt;3)&t;}, */
(brace
l_int|48000
comma
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
(paren
l_int|6
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|9600
comma
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
(paren
l_int|7
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|5513
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|0
op_lshift
l_int|3
)paren
)brace
comma
multiline_comment|/* Actually 5512.5 */
(brace
l_int|11025
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|1
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|18900
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|2
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|22050
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|3
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|37800
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|4
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|44100
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|5
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|33075
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|6
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|6615
comma
(paren
l_int|2
op_lshift
l_int|4
)paren
comma
(paren
l_int|7
op_lshift
l_int|3
)paren
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|CS4215_HPF
mdefine_line|#define CS4215_HPF&t;(1&lt;&lt;7)&t;/* High Pass Filter, 1: Enabled */
DECL|macro|CS4215_12_MASK
mdefine_line|#define CS4215_12_MASK&t;0xfcbf&t;/* Mask off reserved bits in slot 1 &amp; 2 */
multiline_comment|/* Time Slot 3, Serial Port Control register */
DECL|macro|CS4215_XEN
mdefine_line|#define CS4215_XEN&t;(1&lt;&lt;0)&t;/* 0: Enable serial output */
DECL|macro|CS4215_XCLK
mdefine_line|#define CS4215_XCLK&t;(1&lt;&lt;1)&t;/* 1: Master mode: Generate SCLK */
DECL|macro|CS4215_BSEL_64
mdefine_line|#define CS4215_BSEL_64&t;(0&lt;&lt;2)&t;/* Bitrate: 64 bits per frame */
DECL|macro|CS4215_BSEL_128
mdefine_line|#define CS4215_BSEL_128&t;(1&lt;&lt;2)
DECL|macro|CS4215_BSEL_256
mdefine_line|#define CS4215_BSEL_256&t;(2&lt;&lt;2)
DECL|macro|CS4215_MCK_MAST
mdefine_line|#define CS4215_MCK_MAST (0&lt;&lt;4)&t;/* Master clock */
DECL|macro|CS4215_MCK_XTL1
mdefine_line|#define CS4215_MCK_XTL1 (1&lt;&lt;4)&t;/* 24.576 MHz clock source */
DECL|macro|CS4215_MCK_XTL2
mdefine_line|#define CS4215_MCK_XTL2 (2&lt;&lt;4)&t;/* 16.9344 MHz clock source */
DECL|macro|CS4215_MCK_CLK1
mdefine_line|#define CS4215_MCK_CLK1 (3&lt;&lt;4)&t;/* Clockin, 256 x Fs */
DECL|macro|CS4215_MCK_CLK2
mdefine_line|#define CS4215_MCK_CLK2 (4&lt;&lt;4)&t;/* Clockin, see DFR */
multiline_comment|/* Time Slot 4, Test Register */
DECL|macro|CS4215_DAD
mdefine_line|#define CS4215_DAD&t;(1&lt;&lt;0)&t;/* 0:Digital-Dig loop, 1:Dig-Analog-Dig loop */
DECL|macro|CS4215_ENL
mdefine_line|#define CS4215_ENL&t;(1&lt;&lt;1)&t;/* Enable Loopback Testing */
multiline_comment|/* Time Slot 5, Parallel Port Register */
multiline_comment|/* Read only here and the same as the in data mode */
multiline_comment|/* Time Slot 6, Reserved  */
multiline_comment|/* Time Slot 7, Version Register  */
DECL|macro|CS4215_VERSION_MASK
mdefine_line|#define CS4215_VERSION_MASK 0xf&t;/* Known versions 0/C, 1/D, 2/E */
multiline_comment|/* Time Slot 8, Reserved  */
multiline_comment|/*&n; * Data mode&n; */
multiline_comment|/* Time Slot 1-2: Left Channel Data, 2-3: Right Channel Data  */
multiline_comment|/* Time Slot 5, Output Setting  */
DECL|macro|CS4215_LO
mdefine_line|#define CS4215_LO(v)&t;v&t;/* Left Output Attenuation 0x3f: -94.5 dB */
DECL|macro|CS4215_LE
mdefine_line|#define CS4215_LE&t;(1&lt;&lt;6)&t;/* Line Out Enable */
DECL|macro|CS4215_HE
mdefine_line|#define CS4215_HE&t;(1&lt;&lt;7)&t;/* Headphone Enable */
multiline_comment|/* Time Slot 6, Output Setting  */
DECL|macro|CS4215_RO
mdefine_line|#define CS4215_RO(v)&t;v&t;/* Right Output Attenuation 0x3f: -94.5 dB */
DECL|macro|CS4215_SE
mdefine_line|#define CS4215_SE&t;(1&lt;&lt;6)&t;/* Speaker Enable */
DECL|macro|CS4215_ADI
mdefine_line|#define CS4215_ADI&t;(1&lt;&lt;7)&t;/* A/D Data Invalid: Busy in calibration */
multiline_comment|/* Time Slot 7, Input Setting */
DECL|macro|CS4215_LG
mdefine_line|#define CS4215_LG(v)&t;v&t;/* Left Gain Setting 0xf: 22.5 dB */
DECL|macro|CS4215_IS
mdefine_line|#define CS4215_IS&t;(1&lt;&lt;4)&t;/* Input Select: 1=Microphone, 0=Line */
DECL|macro|CS4215_OVR
mdefine_line|#define CS4215_OVR&t;(1&lt;&lt;5)&t;/* 1: Overrange condition occurred */
DECL|macro|CS4215_PIO0
mdefine_line|#define CS4215_PIO0&t;(1&lt;&lt;6)&t;/* Parallel I/O 0 */
DECL|macro|CS4215_PIO1
mdefine_line|#define CS4215_PIO1&t;(1&lt;&lt;7)
multiline_comment|/* Time Slot 8, Input Setting */
DECL|macro|CS4215_RG
mdefine_line|#define CS4215_RG(v)&t;v&t;/* Right Gain Setting 0xf: 22.5 dB */
DECL|macro|CS4215_MA
mdefine_line|#define CS4215_MA(v)&t;(v&lt;&lt;4)&t;/* Monitor Path Attenuation 0xf: mute */
macro_line|#endif /* _CS4215_H_ */
eof
