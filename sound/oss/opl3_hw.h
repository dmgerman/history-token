multiline_comment|/*&n; *&t;opl3_hw.h&t;- Definitions of the OPL-3 registers&n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; *&n; *&n; *&t;The OPL-3 mode is switched on by writing 0x01, to the offset 5&n; *&t;of the right side.&n; *&n; *&t;Another special register at the right side is at offset 4. It contains&n; *&t;a bit mask defining which voices are used as 4 OP voices.&n; *&n; *&t;The percussive mode is implemented in the left side only.&n; *&n; *&t;With the above exceptions the both sides can be operated independently.&n; *&t;&n; *&t;A 4 OP voice can be created by setting the corresponding&n; *&t;bit at offset 4 of the right side.&n; *&n; *&t;For example setting the rightmost bit (0x01) changes the&n; *&t;first voice on the right side to the 4 OP mode. The fourth&n; *&t;voice is made inaccessible.&n; *&n; *&t;If a voice is set to the 2 OP mode, it works like 2 OP modes&n; *&t;of the original YM3812 (AdLib). In addition the voice can &n; *&t;be connected the left, right or both stereo channels. It can&n; *&t;even be left unconnected. This works with 4 OP voices also.&n; *&n; *&t;The stereo connection bits are located in the FEEDBACK_CONNECTION&n; *&t;register of the voice (0xC0-0xC8). In 4 OP voices these bits are&n; *&t;in the second half of the voice.&n; */
multiline_comment|/*&n; *&t;Register numbers for the global registers&n; */
DECL|macro|TEST_REGISTER
mdefine_line|#define TEST_REGISTER&t;&t;&t;&t;0x01
DECL|macro|ENABLE_WAVE_SELECT
mdefine_line|#define   ENABLE_WAVE_SELECT&t;&t;0x20
DECL|macro|TIMER1_REGISTER
mdefine_line|#define TIMER1_REGISTER&t;&t;&t;&t;0x02
DECL|macro|TIMER2_REGISTER
mdefine_line|#define TIMER2_REGISTER&t;&t;&t;&t;0x03
DECL|macro|TIMER_CONTROL_REGISTER
mdefine_line|#define TIMER_CONTROL_REGISTER&t;&t;&t;0x04&t;/* Left side */
DECL|macro|IRQ_RESET
mdefine_line|#define   IRQ_RESET&t;&t;&t;0x80
DECL|macro|TIMER1_MASK
mdefine_line|#define   TIMER1_MASK&t;&t;&t;0x40
DECL|macro|TIMER2_MASK
mdefine_line|#define   TIMER2_MASK&t;&t;&t;0x20
DECL|macro|TIMER1_START
mdefine_line|#define   TIMER1_START&t;&t;&t;0x01
DECL|macro|TIMER2_START
mdefine_line|#define   TIMER2_START&t;&t;&t;0x02
DECL|macro|CONNECTION_SELECT_REGISTER
mdefine_line|#define CONNECTION_SELECT_REGISTER&t;&t;0x04&t;/* Right side */
DECL|macro|RIGHT_4OP_0
mdefine_line|#define   RIGHT_4OP_0&t;&t;&t;0x01
DECL|macro|RIGHT_4OP_1
mdefine_line|#define   RIGHT_4OP_1&t;&t;&t;0x02
DECL|macro|RIGHT_4OP_2
mdefine_line|#define   RIGHT_4OP_2&t;&t;&t;0x04
DECL|macro|LEFT_4OP_0
mdefine_line|#define   LEFT_4OP_0&t;&t;&t;0x08
DECL|macro|LEFT_4OP_1
mdefine_line|#define   LEFT_4OP_1&t;&t;&t;0x10
DECL|macro|LEFT_4OP_2
mdefine_line|#define   LEFT_4OP_2&t;&t;&t;0x20
DECL|macro|OPL3_MODE_REGISTER
mdefine_line|#define OPL3_MODE_REGISTER&t;&t;&t;0x05&t;/* Right side */
DECL|macro|OPL3_ENABLE
mdefine_line|#define   OPL3_ENABLE&t;&t;&t;0x01
DECL|macro|OPL4_ENABLE
mdefine_line|#define   OPL4_ENABLE&t;&t;&t;0x02
DECL|macro|KBD_SPLIT_REGISTER
mdefine_line|#define KBD_SPLIT_REGISTER&t;&t;&t;0x08&t;/* Left side */
DECL|macro|COMPOSITE_SINE_WAVE_MODE
mdefine_line|#define   COMPOSITE_SINE_WAVE_MODE&t;0x80&t;&t;/* Don&squot;t use with OPL-3? */
DECL|macro|KEYBOARD_SPLIT
mdefine_line|#define   KEYBOARD_SPLIT&t;&t;0x40
DECL|macro|PERCOSSION_REGISTER
mdefine_line|#define PERCOSSION_REGISTER&t;&t;&t;0xbd&t;/* Left side only */
DECL|macro|TREMOLO_DEPTH
mdefine_line|#define   TREMOLO_DEPTH&t;&t;&t;0x80
DECL|macro|VIBRATO_DEPTH
mdefine_line|#define   VIBRATO_DEPTH&t;&t;&t;0x40
DECL|macro|PERCOSSION_ENABLE
mdefine_line|#define&t;  PERCOSSION_ENABLE&t;&t;0x20
DECL|macro|BASSDRUM_ON
mdefine_line|#define   BASSDRUM_ON&t;&t;&t;0x10
DECL|macro|SNAREDRUM_ON
mdefine_line|#define   SNAREDRUM_ON&t;&t;&t;0x08
DECL|macro|TOMTOM_ON
mdefine_line|#define   TOMTOM_ON&t;&t;&t;0x04
DECL|macro|CYMBAL_ON
mdefine_line|#define   CYMBAL_ON&t;&t;&t;0x02
DECL|macro|HIHAT_ON
mdefine_line|#define   HIHAT_ON&t;&t;&t;0x01
multiline_comment|/*&n; *&t;Offsets to the register banks for operators. To get the&n; *&t;register number just add the operator offset to the bank offset&n; *&n; *&t;AM/VIB/EG/KSR/Multiple (0x20 to 0x35)&n; */
DECL|macro|AM_VIB
mdefine_line|#define AM_VIB&t;&t;&t;&t;&t;0x20
DECL|macro|TREMOLO_ON
mdefine_line|#define   TREMOLO_ON&t;&t;&t;0x80
DECL|macro|VIBRATO_ON
mdefine_line|#define   VIBRATO_ON&t;&t;&t;0x40
DECL|macro|SUSTAIN_ON
mdefine_line|#define   SUSTAIN_ON&t;&t;&t;0x20
DECL|macro|KSR
mdefine_line|#define   KSR&t;&t;&t;&t;0x10 &t;/* Key scaling rate */
DECL|macro|MULTIPLE_MASK
mdefine_line|#define   MULTIPLE_MASK&t;&t;0x0f&t;/* Frequency multiplier */
multiline_comment|/*&n;  *&t;KSL/Total level (0x40 to 0x55)&n;  */
DECL|macro|KSL_LEVEL
mdefine_line|#define KSL_LEVEL&t;&t;&t;&t;0x40
DECL|macro|KSL_MASK
mdefine_line|#define   KSL_MASK&t;&t;&t;0xc0&t;/* Envelope scaling bits */
DECL|macro|TOTAL_LEVEL_MASK
mdefine_line|#define   TOTAL_LEVEL_MASK&t;&t;0x3f&t;/* Strength (volume) of OP */
multiline_comment|/*&n; *&t;Attack / Decay rate (0x60 to 0x75)&n; */
DECL|macro|ATTACK_DECAY
mdefine_line|#define ATTACK_DECAY&t;&t;&t;&t;0x60
DECL|macro|ATTACK_MASK
mdefine_line|#define   ATTACK_MASK&t;&t;&t;0xf0
DECL|macro|DECAY_MASK
mdefine_line|#define   DECAY_MASK&t;&t;&t;0x0f
multiline_comment|/*&n; * Sustain level / Release rate (0x80 to 0x95)&n; */
DECL|macro|SUSTAIN_RELEASE
mdefine_line|#define SUSTAIN_RELEASE&t;&t;&t;&t;0x80
DECL|macro|SUSTAIN_MASK
mdefine_line|#define   SUSTAIN_MASK&t;&t;&t;0xf0
DECL|macro|RELEASE_MASK
mdefine_line|#define   RELEASE_MASK&t;&t;&t;0x0f
multiline_comment|/*&n; * Wave select (0xE0 to 0xF5)&n; */
DECL|macro|WAVE_SELECT
mdefine_line|#define WAVE_SELECT&t;&t;&t;0xe0
multiline_comment|/*&n; *&t;Offsets to the register banks for voices. Just add to the&n; *&t;voice number to get the register number.&n; *&n; *&t;F-Number low bits (0xA0 to 0xA8).&n; */
DECL|macro|FNUM_LOW
mdefine_line|#define FNUM_LOW&t;&t;&t;&t;0xa0
multiline_comment|/*&n; *&t;F-number high bits / Key on / Block (octave) (0xB0 to 0xB8)&n; */
DECL|macro|KEYON_BLOCK
mdefine_line|#define KEYON_BLOCK&t;&t;&t;&t;&t;0xb0
DECL|macro|KEYON_BIT
mdefine_line|#define&t;  KEYON_BIT&t;&t;&t;&t;0x20
DECL|macro|BLOCKNUM_MASK
mdefine_line|#define&t;  BLOCKNUM_MASK&t;&t;&t;&t;0x1c
DECL|macro|FNUM_HIGH_MASK
mdefine_line|#define   FNUM_HIGH_MASK&t;&t;&t;0x03
multiline_comment|/*&n; *&t;Feedback / Connection (0xc0 to 0xc8)&n; *&n; *&t;These registers have two new bits when the OPL-3 mode&n; *&t;is selected. These bits controls connecting the voice&n; *&t;to the stereo channels. For 4 OP voices this bit is&n; *&t;defined in the second half of the voice (add 3 to the&n; *&t;register offset).&n; *&n; *&t;For 4 OP voices the connection bit is used in the&n; *&t;both halves (gives 4 ways to connect the operators).&n; */
DECL|macro|FEEDBACK_CONNECTION
mdefine_line|#define FEEDBACK_CONNECTION&t;&t;&t;&t;0xc0
DECL|macro|FEEDBACK_MASK
mdefine_line|#define   FEEDBACK_MASK&t;&t;&t;&t;0x0e&t;/* Valid just for 1st OP of a voice */
DECL|macro|CONNECTION_BIT
mdefine_line|#define   CONNECTION_BIT&t;&t;&t;0x01
multiline_comment|/*&n; *&t;In the 4 OP mode there is four possible configurations how the&n; *&t;operators can be connected together (in 2 OP modes there is just&n; *&t;AM or FM). The 4 OP connection mode is defined by the rightmost&n; *&t;bit of the FEEDBACK_CONNECTION (0xC0-0xC8) on the both halves.&n; *&n; *&t;First half&t;Second half&t;Mode&n; *&n; *&t;&t;&t;&t;&t; +---+&n; *&t;&t;&t;&t;&t; v   |&n; *&t;0&t;&t;0&t;&t;&gt;+-1-+--2--3--4--&gt;&n; *&n; *&n; *&t;&t;&t;&t;&t;&n; *&t;&t;&t;&t;&t; +---+&n; *&t;&t;&t;&t;&t; |   |&n; *&t;0&t;&t;1&t;&t;&gt;+-1-+--2-+&n; *&t;&t;&t;&t;&t;&t;  |-&gt;&n; *&t;&t;&t;&t;&t;&gt;--3----4-+&n; *&t;&t;&t;&t;&t;&n; *&t;&t;&t;&t;&t; +---+&n; *&t;&t;&t;&t;&t; |   |&n; *&t;1&t;&t;0&t;&t;&gt;+-1-+-----+&n; *&t;&t;&t;&t;&t;&t;   |-&gt;&n; *&t;&t;&t;&t;&t;&gt;--2--3--4-+&n; *&n; *&t;&t;&t;&t;&t; +---+&n; *&t;&t;&t;&t;&t; |   |&n; *&t;1&t;&t;1&t;&t;&gt;+-1-+--+&n; *&t;&t;&t;&t;&t;&t;|&n; *&t;&t;&t;&t;&t;&gt;--2--3-+-&gt;&n; *&t;&t;&t;&t;&t;&t;|&n; *&t;&t;&t;&t;&t;&gt;--4----+&n; */
DECL|macro|STEREO_BITS
mdefine_line|#define   STEREO_BITS&t;&t;&t;&t;0x30&t;/* OPL-3 only */
DECL|macro|VOICE_TO_LEFT
mdefine_line|#define     VOICE_TO_LEFT&t;&t;0x10
DECL|macro|VOICE_TO_RIGHT
mdefine_line|#define     VOICE_TO_RIGHT&t;&t;0x20
multiline_comment|/*&n; * &t;Definition table for the physical voices&n; */
DECL|struct|physical_voice_info
r_struct
id|physical_voice_info
(brace
DECL|member|voice_num
r_int
r_char
id|voice_num
suffix:semicolon
DECL|member|voice_mode
r_int
r_char
id|voice_mode
suffix:semicolon
multiline_comment|/* 0=unavailable, 2=2 OP, 4=4 OP */
DECL|member|ioaddr
r_int
r_int
id|ioaddr
suffix:semicolon
multiline_comment|/* I/O port (left or right side) */
DECL|member|op
r_int
r_char
id|op
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Operator offsets */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;There is 18 possible 2 OP voices&n; *&t;(9 in the left and 9 in the right).&n; *&t;The first OP is the modulator and 2nd is the carrier.&n; *&n; *&t;The first three voices in the both sides may be connected&n; *&t;with another voice to a 4 OP voice. For example voice 0&n; *&t;can be connected with voice 3. The operators of voice 3 are&n; *&t;used as operators 3 and 4 of the new 4 OP voice.&n; *&t;In this case the 2 OP voice number 0 is the &squot;first half&squot; and&n; *&t;voice 3 is the second.&n; */
DECL|macro|USE_LEFT
mdefine_line|#define USE_LEFT&t;0
DECL|macro|USE_RIGHT
mdefine_line|#define USE_RIGHT&t;1
DECL|variable|pv_map
r_static
r_struct
id|physical_voice_info
id|pv_map
(braket
l_int|18
)braket
op_assign
(brace
multiline_comment|/*       No Mode Side&t;&t;OP1&t;OP2&t;OP3   OP4&t;*/
multiline_comment|/*&t;---------------------------------------------------&t;*/
(brace
l_int|0
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x00
comma
l_int|0x03
comma
l_int|0x08
comma
l_int|0x0b
)brace
)brace
comma
(brace
l_int|1
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x01
comma
l_int|0x04
comma
l_int|0x09
comma
l_int|0x0c
)brace
)brace
comma
(brace
l_int|2
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x02
comma
l_int|0x05
comma
l_int|0x0a
comma
l_int|0x0d
)brace
)brace
comma
(brace
l_int|3
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x08
comma
l_int|0x0b
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|4
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x09
comma
l_int|0x0c
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|5
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x0a
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|6
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x10
comma
l_int|0x13
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
multiline_comment|/* Used by percussive voices */
(brace
l_int|7
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x11
comma
l_int|0x14
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
multiline_comment|/* if the percussive mode */
(brace
l_int|8
comma
l_int|2
comma
id|USE_LEFT
comma
(brace
l_int|0x12
comma
l_int|0x15
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
multiline_comment|/* is selected */
(brace
l_int|0
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x00
comma
l_int|0x03
comma
l_int|0x08
comma
l_int|0x0b
)brace
)brace
comma
(brace
l_int|1
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x01
comma
l_int|0x04
comma
l_int|0x09
comma
l_int|0x0c
)brace
)brace
comma
(brace
l_int|2
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x02
comma
l_int|0x05
comma
l_int|0x0a
comma
l_int|0x0d
)brace
)brace
comma
(brace
l_int|3
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x08
comma
l_int|0x0b
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|4
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x09
comma
l_int|0x0c
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|5
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x0a
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|6
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x10
comma
l_int|0x13
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|7
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x11
comma
l_int|0x14
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
(brace
l_int|8
comma
l_int|2
comma
id|USE_RIGHT
comma
(brace
l_int|0x12
comma
l_int|0x15
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;DMA buffer calls&n; */
eof
