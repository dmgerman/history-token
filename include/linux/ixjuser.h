multiline_comment|/******************************************************************************&n; *&n; *    ixjuser.h&n; *&n; *    Device Driver for the Internet PhoneJACK and&n; *    Internet LineJACK Telephony Cards.&n; *&n; *    (c) Copyright 1999 Quicknet Technologies, Inc.&n; *&n; *    This program is free software; you can redistribute it and/or&n; *    modify it under the terms of the GNU General Public License&n; *    as published by the Free Software Foundation; either version&n; *    2 of the License, or (at your option) any later version.&n; *&n; * Author:          Ed Okerson, &lt;eokerson@quicknet.net&gt;&n; *    &n; * Contributors:    Greg Herlein, &lt;gherlein@quicknet.net&gt;&n; *                  David W. Erhart, &lt;derhart@quicknet.net&gt;&n; *                  John Sellers, &lt;jsellers@quicknet.net&gt;&n; *                  Mike Preston, &lt;mpreston@quicknet.net&gt;&n; *&n; * More information about the hardware related to this driver can be found&n; * at our website:    http://www.quicknet.net&n; *&n; * Fixes:&n; *&n; * IN NO EVENT SHALL QUICKNET TECHNOLOGIES, INC. BE LIABLE TO ANY PARTY FOR&n; * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT&n; * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF QUICKNET&n; * TECHNOLOGIES, INC.HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * QUICKNET TECHNOLOGIES, INC. SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND QUICKNET TECHNOLOGIES, INC. HAS NO OBLIGATION &n; * TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.&n; *&n; *****************************************************************************/
DECL|variable|ixjuser_h_rcsid
r_static
r_char
id|ixjuser_h_rcsid
(braket
)braket
op_assign
l_string|&quot;$Id: ixjuser.h,v 3.11 2000/03/30 22:06:48 eokerson Exp $&quot;
suffix:semicolon
macro_line|#include &quot;telephony.h&quot;
multiline_comment|/******************************************************************************&n;*&n;* IOCTL&squot;s used for the Quicknet Cards&n;*&n;* If you use the IXJCTL_TESTRAM command, the card must be power cycled to&n;* reset the SRAM values before futher use.&n;*&n;******************************************************************************/
DECL|macro|IXJCTL_DSP_RESET
mdefine_line|#define IXJCTL_DSP_RESET &t;&t;_IO  (&squot;q&squot;, 0xC0)
DECL|macro|IXJCTL_RING
mdefine_line|#define IXJCTL_RING                     PHONE_RING
DECL|macro|IXJCTL_HOOKSTATE
mdefine_line|#define IXJCTL_HOOKSTATE                PHONE_HOOKSTATE
DECL|macro|IXJCTL_MAXRINGS
mdefine_line|#define IXJCTL_MAXRINGS&t;&t;&t;PHONE_MAXRINGS
DECL|macro|IXJCTL_RING_CADENCE
mdefine_line|#define IXJCTL_RING_CADENCE&t;&t;PHONE_RING_CADENCE
DECL|macro|IXJCTL_RING_START
mdefine_line|#define IXJCTL_RING_START&t;&t;PHONE_RING_START
DECL|macro|IXJCTL_RING_STOP
mdefine_line|#define IXJCTL_RING_STOP&t;&t;PHONE_RING_STOP
DECL|macro|IXJCTL_CARDTYPE
mdefine_line|#define IXJCTL_CARDTYPE&t;&t;&t;_IOR (&squot;q&squot;, 0xC1, int)
DECL|macro|IXJCTL_SERIAL
mdefine_line|#define IXJCTL_SERIAL&t;&t;&t;_IOR (&squot;q&squot;, 0xC2, int)
DECL|macro|IXJCTL_DSP_TYPE
mdefine_line|#define IXJCTL_DSP_TYPE                 _IOR (&squot;q&squot;, 0xC3, int)
DECL|macro|IXJCTL_DSP_VERSION
mdefine_line|#define IXJCTL_DSP_VERSION              _IOR (&squot;q&squot;, 0xC4, int)
DECL|macro|IXJCTL_VERSION
mdefine_line|#define IXJCTL_VERSION              &t;_IOR (&squot;q&squot;, 0xDA, char *)
DECL|macro|IXJCTL_DSP_IDLE
mdefine_line|#define IXJCTL_DSP_IDLE&t;&t;&t;_IO  (&squot;q&squot;, 0xC5)
DECL|macro|IXJCTL_TESTRAM
mdefine_line|#define IXJCTL_TESTRAM&t;&t;&t;_IO  (&squot;q&squot;, 0xC6)
multiline_comment|/******************************************************************************&n;*&n;* This group of IOCTLs deal with the record settings of the DSP&n;*&n;* The IXJCTL_REC_DEPTH command sets the internal buffer depth of the DSP.&n;* Setting a lower depth reduces latency, but increases the demand of the&n;* application to service the driver without frame loss.  The DSP has 480&n;* bytes of physical buffer memory for the record channel so the true&n;* maximum limit is determined by how many frames will fit in the buffer.&n;*&n;* 1 uncompressed (480 byte) 16-bit linear frame.&n;* 2 uncompressed (240 byte) 8-bit A-law/mu-law frames.&n;* 15 TrueSpeech 8.5 frames.&n;* 20 TrueSpeech 6.3,5.3,4.8 or 4.1 frames.&n;*&n;* The default in the driver is currently set to 2 frames.&n;*&n;* The IXJCTL_REC_VOLUME and IXJCTL_PLAY_VOLUME commands both use a Q8&n;* number as a parameter, 0x100 scales the signal by 1.0, 0x200 scales the&n;* signal by 2.0, 0x80 scales the signal by 0.5.  No protection is given&n;* against over-scaling, if the multiplication factor times the input&n;* signal exceeds 16 bits, overflow distortion will occur.  The default&n;* setting is 0x100 (1.0).&n;*&n;* The IXJCTL_REC_LEVEL returns the average signal level (not r.m.s.) on&n;* the most recently recorded frame as a 16 bit value.&n;******************************************************************************/
DECL|macro|IXJCTL_REC_CODEC
mdefine_line|#define IXJCTL_REC_CODEC                PHONE_REC_CODEC
DECL|macro|IXJCTL_REC_START
mdefine_line|#define IXJCTL_REC_START                PHONE_REC_START
DECL|macro|IXJCTL_REC_STOP
mdefine_line|#define IXJCTL_REC_STOP                 PHONE_REC_STOP
DECL|macro|IXJCTL_REC_DEPTH
mdefine_line|#define IXJCTL_REC_DEPTH&t;&t;PHONE_REC_DEPTH
DECL|macro|IXJCTL_FRAME
mdefine_line|#define IXJCTL_FRAME&t;&t;&t;PHONE_FRAME
DECL|macro|IXJCTL_REC_VOLUME
mdefine_line|#define IXJCTL_REC_VOLUME&t;&t;PHONE_REC_VOLUME
DECL|macro|IXJCTL_REC_LEVEL
mdefine_line|#define IXJCTL_REC_LEVEL&t;&t;PHONE_REC_LEVEL
r_typedef
r_enum
(brace
DECL|enumerator|f300_640
DECL|enumerator|f300_500
DECL|enumerator|f1100
DECL|enumerator|f350
DECL|enumerator|f400
DECL|enumerator|f480
DECL|enumerator|f440
DECL|enumerator|f620
DECL|enumerator|f20_50
id|f300_640
op_assign
l_int|4
comma
id|f300_500
comma
id|f1100
comma
id|f350
comma
id|f400
comma
id|f480
comma
id|f440
comma
id|f620
comma
id|f20_50
comma
DECL|enumerator|f133_200
DECL|enumerator|f300
DECL|enumerator|f300_420
DECL|enumerator|f330
DECL|enumerator|f300_425
DECL|enumerator|f330_440
DECL|enumerator|f340
DECL|enumerator|f350_400
id|f133_200
comma
id|f300
comma
id|f300_420
comma
id|f330
comma
id|f300_425
comma
id|f330_440
comma
id|f340
comma
id|f350_400
comma
DECL|enumerator|f350_440
DECL|enumerator|f350_450
DECL|enumerator|f360
DECL|enumerator|f380_420
DECL|enumerator|f392
DECL|enumerator|f400_425
DECL|enumerator|f400_440
DECL|enumerator|f400_450
id|f350_440
comma
id|f350_450
comma
id|f360
comma
id|f380_420
comma
id|f392
comma
id|f400_425
comma
id|f400_440
comma
id|f400_450
comma
DECL|enumerator|f420
DECL|enumerator|f425
DECL|enumerator|f425_450
DECL|enumerator|f425_475
DECL|enumerator|f435
DECL|enumerator|f440_450
DECL|enumerator|f440_480
DECL|enumerator|f445
DECL|enumerator|f450
id|f420
comma
id|f425
comma
id|f425_450
comma
id|f425_475
comma
id|f435
comma
id|f440_450
comma
id|f440_480
comma
id|f445
comma
id|f450
comma
DECL|enumerator|f452
DECL|enumerator|f475
DECL|enumerator|f480_620
DECL|enumerator|f494
DECL|enumerator|f500
DECL|enumerator|f520
DECL|enumerator|f523
DECL|enumerator|f525
DECL|enumerator|f540_660
DECL|enumerator|f587
id|f452
comma
id|f475
comma
id|f480_620
comma
id|f494
comma
id|f500
comma
id|f520
comma
id|f523
comma
id|f525
comma
id|f540_660
comma
id|f587
comma
DECL|enumerator|f590
DECL|enumerator|f600
DECL|enumerator|f660
DECL|enumerator|f700
DECL|enumerator|f740
DECL|enumerator|f750
DECL|enumerator|f750_1450
DECL|enumerator|f770
DECL|enumerator|f800
DECL|enumerator|f816
DECL|enumerator|f850
id|f590
comma
id|f600
comma
id|f660
comma
id|f700
comma
id|f740
comma
id|f750
comma
id|f750_1450
comma
id|f770
comma
id|f800
comma
id|f816
comma
id|f850
comma
DECL|enumerator|f857_1645
DECL|enumerator|f900
DECL|enumerator|f900_1300
DECL|enumerator|f935_1215
DECL|enumerator|f941_1477
DECL|enumerator|f942
DECL|enumerator|f950
DECL|enumerator|f950_1400
id|f857_1645
comma
id|f900
comma
id|f900_1300
comma
id|f935_1215
comma
id|f941_1477
comma
id|f942
comma
id|f950
comma
id|f950_1400
comma
DECL|enumerator|f975
DECL|enumerator|f1000
DECL|enumerator|f1020
DECL|enumerator|f1050
DECL|enumerator|f1100_1750
DECL|enumerator|f1140
DECL|enumerator|f1200
DECL|enumerator|f1209
DECL|enumerator|f1330
DECL|enumerator|f1336
id|f975
comma
id|f1000
comma
id|f1020
comma
id|f1050
comma
id|f1100_1750
comma
id|f1140
comma
id|f1200
comma
id|f1209
comma
id|f1330
comma
id|f1336
comma
DECL|enumerator|lf1366
DECL|enumerator|f1380
DECL|enumerator|f1400
DECL|enumerator|f1477
DECL|enumerator|f1600
DECL|enumerator|f1633_1638
DECL|enumerator|f1800
DECL|enumerator|f1860
id|lf1366
comma
id|f1380
comma
id|f1400
comma
id|f1477
comma
id|f1600
comma
id|f1633_1638
comma
id|f1800
comma
id|f1860
DECL|typedef|IXJ_FILTER_FREQ
)brace
id|IXJ_FILTER_FREQ
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|filter
r_int
r_int
id|filter
suffix:semicolon
DECL|member|freq
id|IXJ_FILTER_FREQ
id|freq
suffix:semicolon
DECL|member|enable
r_char
id|enable
suffix:semicolon
DECL|typedef|IXJ_FILTER
)brace
id|IXJ_FILTER
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|enable
r_char
id|enable
suffix:semicolon
DECL|member|en_filter
r_char
id|en_filter
suffix:semicolon
DECL|member|filter
r_int
r_int
id|filter
suffix:semicolon
DECL|member|on1
r_int
r_int
id|on1
suffix:semicolon
DECL|member|off1
r_int
r_int
id|off1
suffix:semicolon
DECL|member|on2
r_int
r_int
id|on2
suffix:semicolon
DECL|member|off2
r_int
r_int
id|off2
suffix:semicolon
DECL|member|on3
r_int
r_int
id|on3
suffix:semicolon
DECL|member|off3
r_int
r_int
id|off3
suffix:semicolon
DECL|typedef|IXJ_FILTER_CADENCE
)brace
id|IXJ_FILTER_CADENCE
suffix:semicolon
DECL|macro|IXJCTL_SET_FILTER
mdefine_line|#define IXJCTL_SET_FILTER&t;&t;_IOW (&squot;q&squot;, 0xC7, IXJ_FILTER *)
DECL|macro|IXJCTL_GET_FILTER_HIST
mdefine_line|#define IXJCTL_GET_FILTER_HIST&t;&t;_IOW (&squot;q&squot;, 0xC8, int)
DECL|macro|IXJCTL_FILTER_CADENCE
mdefine_line|#define IXJCTL_FILTER_CADENCE&t;&t;_IOW (&squot;q&squot;, 0xD6, IXJ_FILTER_CADENCE *)
DECL|macro|IXJCTL_PLAY_CID
mdefine_line|#define IXJCTL_PLAY_CID&t;&t;&t;_IO  (&squot;q&squot;, 0xD7)
multiline_comment|/******************************************************************************&n;*&n;* This IOCTL allows you to reassign values in the tone index table.  The&n;* tone table has 32 entries (0 - 31), but the driver only allows entries&n;* 13 - 27 to be modified, entry 0 is reserved for silence and 1 - 12 are&n;* the standard DTMF digits and 28 - 31 are the DTMF tones for A, B, C &amp; D.&n;* The positions used internally for Call Progress Tones are as follows:&n;*    Dial Tone   - 25&n;*    Ring Back   - 26&n;*    Busy Signal - 27&n;*&n;* The freq values are calculated as:&n;* freq = cos(2 * PI * frequency / 8000)&n;*&n;* The most commonly needed values are already calculated and listed in the&n;* enum IXJ_TONE_FREQ.  Each tone index can have two frequencies with&n;* different gains, if you are only using a single frequency set the unused&n;* one to 0.&n;*&n;* The gain values range from 0 to 15 indicating +6dB to -24dB in 2dB&n;* increments.&n;*&n;******************************************************************************/
r_typedef
r_enum
(brace
DECL|enumerator|hz20
id|hz20
op_assign
l_int|0x7ffa
comma
DECL|enumerator|hz50
id|hz50
op_assign
l_int|0x7fe5
comma
DECL|enumerator|hz133
id|hz133
op_assign
l_int|0x7f4c
comma
DECL|enumerator|hz200
id|hz200
op_assign
l_int|0x7e6b
comma
DECL|enumerator|hz261
id|hz261
op_assign
l_int|0x7d50
comma
multiline_comment|/* .63 C1  */
DECL|enumerator|hz277
id|hz277
op_assign
l_int|0x7cfa
comma
multiline_comment|/* .18 CS1 */
DECL|enumerator|hz293
id|hz293
op_assign
l_int|0x7c9f
comma
multiline_comment|/* .66 D1  */
DECL|enumerator|hz300
id|hz300
op_assign
l_int|0x7c75
comma
DECL|enumerator|hz311
id|hz311
op_assign
l_int|0x7c32
comma
multiline_comment|/* .13 DS1 */
DECL|enumerator|hz329
id|hz329
op_assign
l_int|0x7bbf
comma
multiline_comment|/* .63 E1  */
DECL|enumerator|hz330
id|hz330
op_assign
l_int|0x7bb8
comma
DECL|enumerator|hz340
id|hz340
op_assign
l_int|0x7b75
comma
DECL|enumerator|hz349
id|hz349
op_assign
l_int|0x7b37
comma
multiline_comment|/* .23 F1  */
DECL|enumerator|hz350
id|hz350
op_assign
l_int|0x7b30
comma
DECL|enumerator|hz360
id|hz360
op_assign
l_int|0x7ae9
comma
DECL|enumerator|hz369
id|hz369
op_assign
l_int|0x7aa8
comma
multiline_comment|/* .99 FS1 */
DECL|enumerator|hz380
id|hz380
op_assign
l_int|0x7a56
comma
DECL|enumerator|hz392
id|hz392
op_assign
l_int|0x79fa
comma
multiline_comment|/* .00 G1  */
DECL|enumerator|hz400
id|hz400
op_assign
l_int|0x79bb
comma
DECL|enumerator|hz415
id|hz415
op_assign
l_int|0x7941
comma
multiline_comment|/* .30 GS1 */
DECL|enumerator|hz420
id|hz420
op_assign
l_int|0x7918
comma
DECL|enumerator|hz425
id|hz425
op_assign
l_int|0x78ee
comma
DECL|enumerator|hz435
id|hz435
op_assign
l_int|0x7899
comma
DECL|enumerator|hz440
id|hz440
op_assign
l_int|0x786d
comma
multiline_comment|/* .00 A1  */
DECL|enumerator|hz445
id|hz445
op_assign
l_int|0x7842
comma
DECL|enumerator|hz450
id|hz450
op_assign
l_int|0x7815
comma
DECL|enumerator|hz452
id|hz452
op_assign
l_int|0x7803
comma
DECL|enumerator|hz466
id|hz466
op_assign
l_int|0x7784
comma
multiline_comment|/* .16 AS1 */
DECL|enumerator|hz475
id|hz475
op_assign
l_int|0x7731
comma
DECL|enumerator|hz480
id|hz480
op_assign
l_int|0x7701
comma
DECL|enumerator|hz493
id|hz493
op_assign
l_int|0x7685
comma
multiline_comment|/* .88 B1  */
DECL|enumerator|hz494
id|hz494
op_assign
l_int|0x767b
comma
DECL|enumerator|hz500
id|hz500
op_assign
l_int|0x7640
comma
DECL|enumerator|hz520
id|hz520
op_assign
l_int|0x7578
comma
DECL|enumerator|hz523
id|hz523
op_assign
l_int|0x7559
comma
multiline_comment|/* .25 C2  */
DECL|enumerator|hz525
id|hz525
op_assign
l_int|0x7544
comma
DECL|enumerator|hz540
id|hz540
op_assign
l_int|0x74a7
comma
DECL|enumerator|hz554
id|hz554
op_assign
l_int|0x7411
comma
multiline_comment|/* .37 CS2 */
DECL|enumerator|hz587
id|hz587
op_assign
l_int|0x72a1
comma
multiline_comment|/* .33 D2  */
DECL|enumerator|hz590
id|hz590
op_assign
l_int|0x727f
comma
DECL|enumerator|hz600
id|hz600
op_assign
l_int|0x720b
comma
DECL|enumerator|hz620
id|hz620
op_assign
l_int|0x711e
comma
DECL|enumerator|hz622
id|hz622
op_assign
l_int|0x7106
comma
multiline_comment|/* .25 DS2 */
DECL|enumerator|hz659
id|hz659
op_assign
l_int|0x6f3b
comma
multiline_comment|/* .26 E2  */
DECL|enumerator|hz660
id|hz660
op_assign
l_int|0x6f2e
comma
DECL|enumerator|hz698
id|hz698
op_assign
l_int|0x6d3d
comma
multiline_comment|/* .46 F2  */
DECL|enumerator|hz700
id|hz700
op_assign
l_int|0x6d22
comma
DECL|enumerator|hz739
id|hz739
op_assign
l_int|0x6b09
comma
multiline_comment|/* .99 FS2 */
DECL|enumerator|hz740
id|hz740
op_assign
l_int|0x6afa
comma
DECL|enumerator|hz750
id|hz750
op_assign
l_int|0x6a6c
comma
DECL|enumerator|hz770
id|hz770
op_assign
l_int|0x694b
comma
DECL|enumerator|hz783
id|hz783
op_assign
l_int|0x688b
comma
multiline_comment|/* .99 G2  */
DECL|enumerator|hz800
id|hz800
op_assign
l_int|0x678d
comma
DECL|enumerator|hz816
id|hz816
op_assign
l_int|0x6698
comma
DECL|enumerator|hz830
id|hz830
op_assign
l_int|0x65bf
comma
multiline_comment|/* .61 GS2 */
DECL|enumerator|hz850
id|hz850
op_assign
l_int|0x6484
comma
DECL|enumerator|hz857
id|hz857
op_assign
l_int|0x6414
comma
DECL|enumerator|hz880
id|hz880
op_assign
l_int|0x629f
comma
multiline_comment|/* .00 A2  */
DECL|enumerator|hz900
id|hz900
op_assign
l_int|0x6154
comma
DECL|enumerator|hz932
id|hz932
op_assign
l_int|0x5f35
comma
multiline_comment|/* .33 AS2 */
DECL|enumerator|hz935
id|hz935
op_assign
l_int|0x5f01
comma
DECL|enumerator|hz941
id|hz941
op_assign
l_int|0x5e9a
comma
DECL|enumerator|hz942
id|hz942
op_assign
l_int|0x5e88
comma
DECL|enumerator|hz950
id|hz950
op_assign
l_int|0x5dfd
comma
DECL|enumerator|hz975
id|hz975
op_assign
l_int|0x5c44
comma
DECL|enumerator|hz1000
id|hz1000
op_assign
l_int|0x5a81
comma
DECL|enumerator|hz1020
id|hz1020
op_assign
l_int|0x5912
comma
DECL|enumerator|hz1050
id|hz1050
op_assign
l_int|0x56e2
comma
DECL|enumerator|hz1100
id|hz1100
op_assign
l_int|0x5320
comma
DECL|enumerator|hz1140
id|hz1140
op_assign
l_int|0x5007
comma
DECL|enumerator|hz1200
id|hz1200
op_assign
l_int|0x4b3b
comma
DECL|enumerator|hz1209
id|hz1209
op_assign
l_int|0x4a80
comma
DECL|enumerator|hz1215
id|hz1215
op_assign
l_int|0x4a02
comma
DECL|enumerator|hz1250
id|hz1250
op_assign
l_int|0x471c
comma
DECL|enumerator|hz1300
id|hz1300
op_assign
l_int|0x42e0
comma
DECL|enumerator|hz1330
id|hz1330
op_assign
l_int|0x4049
comma
DECL|enumerator|hz1336
id|hz1336
op_assign
l_int|0x3fc4
comma
DECL|enumerator|hz1366
id|hz1366
op_assign
l_int|0x3d22
comma
DECL|enumerator|hz1380
id|hz1380
op_assign
l_int|0x3be4
comma
DECL|enumerator|hz1400
id|hz1400
op_assign
l_int|0x3a1b
comma
DECL|enumerator|hz1450
id|hz1450
op_assign
l_int|0x3596
comma
DECL|enumerator|hz1477
id|hz1477
op_assign
l_int|0x331c
comma
DECL|enumerator|hz1500
id|hz1500
op_assign
l_int|0x30fb
comma
DECL|enumerator|hz1600
id|hz1600
op_assign
l_int|0x278d
comma
DECL|enumerator|hz1633
id|hz1633
op_assign
l_int|0x2462
comma
DECL|enumerator|hz1638
id|hz1638
op_assign
l_int|0x23e7
comma
DECL|enumerator|hz1645
id|hz1645
op_assign
l_int|0x233a
comma
DECL|enumerator|hz1750
id|hz1750
op_assign
l_int|0x18f8
comma
DECL|enumerator|hz1800
id|hz1800
op_assign
l_int|0x1405
comma
DECL|enumerator|hz1860
id|hz1860
op_assign
l_int|0xe0b
comma
DECL|enumerator|hz2100
id|hz2100
op_assign
l_int|0xf5f6
comma
DECL|enumerator|hz2130
id|hz2130
op_assign
l_int|0xf2f5
comma
DECL|enumerator|hz2450
id|hz2450
op_assign
l_int|0xd3b3
comma
DECL|enumerator|hz2750
id|hz2750
op_assign
l_int|0xb8e4
DECL|typedef|IXJ_FREQ
)brace
id|IXJ_FREQ
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|C1
id|C1
op_assign
id|hz261
comma
DECL|enumerator|CS1
id|CS1
op_assign
id|hz277
comma
DECL|enumerator|D1
id|D1
op_assign
id|hz293
comma
DECL|enumerator|DS1
id|DS1
op_assign
id|hz311
comma
DECL|enumerator|E1
id|E1
op_assign
id|hz329
comma
DECL|enumerator|F1
id|F1
op_assign
id|hz349
comma
DECL|enumerator|FS1
id|FS1
op_assign
id|hz369
comma
DECL|enumerator|G1
id|G1
op_assign
id|hz392
comma
DECL|enumerator|GS1
id|GS1
op_assign
id|hz415
comma
DECL|enumerator|A1
id|A1
op_assign
id|hz440
comma
DECL|enumerator|AS1
id|AS1
op_assign
id|hz466
comma
DECL|enumerator|B1
id|B1
op_assign
id|hz493
comma
DECL|enumerator|C2
id|C2
op_assign
id|hz523
comma
DECL|enumerator|CS2
id|CS2
op_assign
id|hz554
comma
DECL|enumerator|D2
id|D2
op_assign
id|hz587
comma
DECL|enumerator|DS2
id|DS2
op_assign
id|hz622
comma
DECL|enumerator|E2
id|E2
op_assign
id|hz659
comma
DECL|enumerator|F2
id|F2
op_assign
id|hz698
comma
DECL|enumerator|FS2
id|FS2
op_assign
id|hz739
comma
DECL|enumerator|G2
id|G2
op_assign
id|hz783
comma
DECL|enumerator|GS2
id|GS2
op_assign
id|hz830
comma
DECL|enumerator|A2
id|A2
op_assign
id|hz880
comma
DECL|enumerator|AS2
id|AS2
op_assign
id|hz932
comma
DECL|typedef|IXJ_NOTE
)brace
id|IXJ_NOTE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|tone_index
r_int
id|tone_index
suffix:semicolon
DECL|member|freq0
r_int
id|freq0
suffix:semicolon
DECL|member|gain0
r_int
id|gain0
suffix:semicolon
DECL|member|freq1
r_int
id|freq1
suffix:semicolon
DECL|member|gain1
r_int
id|gain1
suffix:semicolon
DECL|typedef|IXJ_TONE
)brace
id|IXJ_TONE
suffix:semicolon
DECL|macro|IXJCTL_INIT_TONE
mdefine_line|#define IXJCTL_INIT_TONE&t;&t;_IOW (&squot;q&squot;, 0xC9, IXJ_TONE *)
multiline_comment|/******************************************************************************&n;*&n;* The IXJCTL_TONE_CADENCE ioctl defines tone sequences used for various&n;* Call Progress Tones (CPT).  This is accomplished by setting up an array of&n;* IXJ_CADENCE_ELEMENT structures that sequentially define the states of&n;* the tone sequence.  The tone_on_time and tone_off time are in&n;* 250 microsecond intervals.  A pointer to this array is passed to the&n;* driver as the ce element of an IXJ_CADENCE structure.  The elements_used&n;* must be set to the number of IXJ_CADENCE_ELEMENTS in the array.  The&n;* termination variable defines what to do at the end of a cadence, the&n;* options are to play the cadence once and stop, to repeat the last&n;* element of the cadence indefinatly, or to repeat the entire cadence&n;* indefinatly.  The ce variable is a pointer to the array of IXJ_TONE&n;* structures.  If the freq0 variable is non-zero, the tone table contents&n;* for the tone_index are updated to the frequencies and gains defined.  It&n;* should be noted that DTMF tones cannot be reassigned, so if DTMF tone&n;* table indexs are used in a cadence the frequency and gain variables will&n;* be ignored.&n;*&n;* If the array elements contain frequency parameters the driver will&n;* initialize the needed tone table elements and begin playing the tone,&n;* there is no preset limit on the number of elements in the cadence.  If&n;* there is more than one frequency used in the cadence, sequential elements&n;* of different frequencies MUST use different tone table indexes.  Only one&n;* cadence can be played at a time.  It is possible to build complex&n;* cadences with multiple frequencies using 2 tone table indexes by&n;* alternating between them.&n;*&n;******************************************************************************/
r_typedef
r_struct
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|tone_on_time
r_int
id|tone_on_time
suffix:semicolon
DECL|member|tone_off_time
r_int
id|tone_off_time
suffix:semicolon
DECL|member|freq0
r_int
id|freq0
suffix:semicolon
DECL|member|gain0
r_int
id|gain0
suffix:semicolon
DECL|member|freq1
r_int
id|freq1
suffix:semicolon
DECL|member|gain1
r_int
id|gain1
suffix:semicolon
DECL|typedef|IXJ_CADENCE_ELEMENT
)brace
id|IXJ_CADENCE_ELEMENT
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|PLAY_ONCE
id|PLAY_ONCE
comma
DECL|enumerator|REPEAT_LAST_ELEMENT
id|REPEAT_LAST_ELEMENT
comma
DECL|enumerator|REPEAT_ALL
id|REPEAT_ALL
DECL|typedef|IXJ_CADENCE_TERM
)brace
id|IXJ_CADENCE_TERM
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|elements_used
r_int
id|elements_used
suffix:semicolon
DECL|member|termination
id|IXJ_CADENCE_TERM
id|termination
suffix:semicolon
DECL|member|ce
id|IXJ_CADENCE_ELEMENT
op_star
id|ce
suffix:semicolon
DECL|typedef|IXJ_CADENCE
)brace
id|IXJ_CADENCE
suffix:semicolon
DECL|macro|IXJCTL_TONE_CADENCE
mdefine_line|#define IXJCTL_TONE_CADENCE&t;&t;_IOW (&squot;q&squot;, 0xCA, IXJ_CADENCE *)
multiline_comment|/******************************************************************************&n;*&n;* This group of IOCTLs deal with the playback settings of the DSP&n;*&n;******************************************************************************/
DECL|macro|IXJCTL_PLAY_CODEC
mdefine_line|#define IXJCTL_PLAY_CODEC               PHONE_PLAY_CODEC
DECL|macro|IXJCTL_PLAY_START
mdefine_line|#define IXJCTL_PLAY_START               PHONE_PLAY_START
DECL|macro|IXJCTL_PLAY_STOP
mdefine_line|#define IXJCTL_PLAY_STOP                PHONE_PLAY_STOP
DECL|macro|IXJCTL_PLAY_DEPTH
mdefine_line|#define IXJCTL_PLAY_DEPTH&t;&t;PHONE_PLAY_DEPTH
DECL|macro|IXJCTL_PLAY_VOLUME
mdefine_line|#define IXJCTL_PLAY_VOLUME&t;&t;PHONE_PLAY_VOLUME
DECL|macro|IXJCTL_PLAY_LEVEL
mdefine_line|#define IXJCTL_PLAY_LEVEL&t;&t;PHONE_PLAY_LEVEL
multiline_comment|/******************************************************************************&n;*&n;* This group of IOCTLs deal with the Acoustic Echo Cancellation settings&n;* of the DSP&n;*&n;* Issueing the IXJCTL_AEC_START command with a value of AEC_OFF has the&n;* same effect as IXJCTL_AEC_STOP.  This is to simplify slider bar&n;* controls.  IXJCTL_AEC_GET_LEVEL returns the current setting of the AEC.&n;******************************************************************************/
DECL|macro|IXJCTL_AEC_START
mdefine_line|#define IXJCTL_AEC_START&t;&t;_IOW (&squot;q&squot;, 0xCB, int)
DECL|macro|IXJCTL_AEC_STOP
mdefine_line|#define IXJCTL_AEC_STOP&t;&t;&t;_IO  (&squot;q&squot;, 0xCC)
DECL|macro|IXJCTL_AEC_GET_LEVEL
mdefine_line|#define IXJCTL_AEC_GET_LEVEL&t;&t;_IO  (&squot;q&squot;, 0xCD)
DECL|macro|AEC_OFF
mdefine_line|#define AEC_OFF   0
DECL|macro|AEC_LOW
mdefine_line|#define AEC_LOW   1
DECL|macro|AEC_MED
mdefine_line|#define AEC_MED   2
DECL|macro|AEC_HIGH
mdefine_line|#define AEC_HIGH  3
DECL|macro|AEC_AUTO
mdefine_line|#define AEC_AUTO  4
multiline_comment|/******************************************************************************&n;*&n;* Call Progress Tones, DTMF, etc.&n;* IXJCTL_DTMF_OOB determines if dtmf signaling is sent as Out-Of-Band&n;* only.  If you pass a 1, dtmf is suppressed from the audio stream.&n;* Tone on and off times are in 250 microsecond intervals so&n;* ioctl(ixj1, IXJCTL_SET_TONE_ON_TIME, 360);&n;* will set the tone on time of board ixj1 to 360 * 250us = 90ms&n;* the default values of tone on and off times is 840 or 210ms&n;******************************************************************************/
DECL|macro|IXJCTL_DTMF_READY
mdefine_line|#define IXJCTL_DTMF_READY&t;&t;PHONE_DTMF_READY
DECL|macro|IXJCTL_GET_DTMF
mdefine_line|#define IXJCTL_GET_DTMF                 PHONE_GET_DTMF
DECL|macro|IXJCTL_GET_DTMF_ASCII
mdefine_line|#define IXJCTL_GET_DTMF_ASCII           PHONE_GET_DTMF_ASCII
DECL|macro|IXJCTL_DTMF_OOB
mdefine_line|#define IXJCTL_DTMF_OOB&t;&t;&t;PHONE_DTMF_OOB
DECL|macro|IXJCTL_EXCEPTION
mdefine_line|#define IXJCTL_EXCEPTION&t;&t;PHONE_EXCEPTION
DECL|macro|IXJCTL_PLAY_TONE
mdefine_line|#define IXJCTL_PLAY_TONE&t;&t;PHONE_PLAY_TONE
DECL|macro|IXJCTL_SET_TONE_ON_TIME
mdefine_line|#define IXJCTL_SET_TONE_ON_TIME&t;&t;PHONE_SET_TONE_ON_TIME
DECL|macro|IXJCTL_SET_TONE_OFF_TIME
mdefine_line|#define IXJCTL_SET_TONE_OFF_TIME&t;PHONE_SET_TONE_OFF_TIME
DECL|macro|IXJCTL_GET_TONE_ON_TIME
mdefine_line|#define IXJCTL_GET_TONE_ON_TIME&t;&t;PHONE_GET_TONE_ON_TIME
DECL|macro|IXJCTL_GET_TONE_OFF_TIME
mdefine_line|#define IXJCTL_GET_TONE_OFF_TIME&t;PHONE_GET_TONE_OFF_TIME
DECL|macro|IXJCTL_GET_TONE_STATE
mdefine_line|#define IXJCTL_GET_TONE_STATE&t;&t;PHONE_GET_TONE_STATE
DECL|macro|IXJCTL_BUSY
mdefine_line|#define IXJCTL_BUSY&t;&t;&t;PHONE_BUSY
DECL|macro|IXJCTL_RINGBACK
mdefine_line|#define IXJCTL_RINGBACK&t;&t;&t;PHONE_RINGBACK
DECL|macro|IXJCTL_DIALTONE
mdefine_line|#define IXJCTL_DIALTONE&t;&t;&t;PHONE_DIALTONE
DECL|macro|IXJCTL_CPT_STOP
mdefine_line|#define IXJCTL_CPT_STOP&t;&t;&t;PHONE_CPT_STOP
multiline_comment|/******************************************************************************&n;* LineJack specific IOCTLs&n;*&n;* The lsb 4 bits of the LED argument represent the state of each of the 4&n;* LED&squot;s on the LineJack&n;******************************************************************************/
DECL|macro|IXJCTL_SET_LED
mdefine_line|#define IXJCTL_SET_LED&t;&t;&t;_IOW (&squot;q&squot;, 0xCE, int)
DECL|macro|IXJCTL_MIXER
mdefine_line|#define IXJCTL_MIXER&t;&t;&t;_IOW (&squot;q&squot;, 0xCF, int)
multiline_comment|/******************************************************************************&n;* &n;* The master volume controls use attenuation with 32 levels from 0 to -62dB&n;* with steps of 2dB each, the defines should be OR&squot;ed together then sent&n;* as the parameter to the mixer command to change the mixer settings.&n;* &n;******************************************************************************/
DECL|macro|MIXER_MASTER_L
mdefine_line|#define MIXER_MASTER_L&t;&t;0x0100
DECL|macro|MIXER_MASTER_R
mdefine_line|#define MIXER_MASTER_R&t;&t;0x0200
DECL|macro|ATT00DB
mdefine_line|#define ATT00DB&t;&t;&t;0x00
DECL|macro|ATT02DB
mdefine_line|#define ATT02DB&t;&t;&t;0x01
DECL|macro|ATT04DB
mdefine_line|#define ATT04DB&t;&t;&t;0x02
DECL|macro|ATT06DB
mdefine_line|#define ATT06DB&t;&t;&t;0x03
DECL|macro|ATT08DB
mdefine_line|#define ATT08DB&t;&t;&t;0x04
DECL|macro|ATT10DB
mdefine_line|#define ATT10DB&t;&t;&t;0x05
DECL|macro|ATT12DB
mdefine_line|#define ATT12DB&t;&t;&t;0x06
DECL|macro|ATT14DB
mdefine_line|#define ATT14DB&t;&t;&t;0x07
DECL|macro|ATT16DB
mdefine_line|#define ATT16DB&t;&t;&t;0x08
DECL|macro|ATT18DB
mdefine_line|#define ATT18DB&t;&t;&t;0x09
DECL|macro|ATT20DB
mdefine_line|#define ATT20DB&t;&t;&t;0x0A
DECL|macro|ATT22DB
mdefine_line|#define ATT22DB&t;&t;&t;0x0B
DECL|macro|ATT24DB
mdefine_line|#define ATT24DB&t;&t;&t;0x0C
DECL|macro|ATT26DB
mdefine_line|#define ATT26DB&t;&t;&t;0x0D
DECL|macro|ATT28DB
mdefine_line|#define ATT28DB&t;&t;&t;0x0E
DECL|macro|ATT30DB
mdefine_line|#define ATT30DB&t;&t;&t;0x0F
DECL|macro|ATT32DB
mdefine_line|#define ATT32DB&t;&t;&t;0x10
DECL|macro|ATT34DB
mdefine_line|#define ATT34DB&t;&t;&t;0x11
DECL|macro|ATT36DB
mdefine_line|#define ATT36DB&t;&t;&t;0x12
DECL|macro|ATT38DB
mdefine_line|#define ATT38DB&t;&t;&t;0x13
DECL|macro|ATT40DB
mdefine_line|#define ATT40DB&t;&t;&t;0x14
DECL|macro|ATT42DB
mdefine_line|#define ATT42DB&t;&t;&t;0x15
DECL|macro|ATT44DB
mdefine_line|#define ATT44DB&t;&t;&t;0x16
DECL|macro|ATT46DB
mdefine_line|#define ATT46DB&t;&t;&t;0x17
DECL|macro|ATT48DB
mdefine_line|#define ATT48DB&t;&t;&t;0x18
DECL|macro|ATT50DB
mdefine_line|#define ATT50DB&t;&t;&t;0x19
DECL|macro|ATT52DB
mdefine_line|#define ATT52DB&t;&t;&t;0x1A
DECL|macro|ATT54DB
mdefine_line|#define ATT54DB&t;&t;&t;0x1B
DECL|macro|ATT56DB
mdefine_line|#define ATT56DB&t;&t;&t;0x1C
DECL|macro|ATT58DB
mdefine_line|#define ATT58DB&t;&t;&t;0x1D
DECL|macro|ATT60DB
mdefine_line|#define ATT60DB&t;&t;&t;0x1E
DECL|macro|ATT62DB
mdefine_line|#define ATT62DB&t;&t;&t;0x1F
DECL|macro|MASTER_MUTE
mdefine_line|#define MASTER_MUTE&t;&t;0x80
multiline_comment|/******************************************************************************&n;* &n;* The input volume controls use gain with 32 levels from +12dB to -50dB&n;* with steps of 2dB each, the defines should be OR&squot;ed together then sent&n;* as the parameter to the mixer command to change the mixer settings.&n;* &n;******************************************************************************/
DECL|macro|MIXER_PORT_CD_L
mdefine_line|#define MIXER_PORT_CD_L&t;&t;0x0600
DECL|macro|MIXER_PORT_CD_R
mdefine_line|#define MIXER_PORT_CD_R&t;&t;0x0700
DECL|macro|MIXER_PORT_LINE_IN_L
mdefine_line|#define MIXER_PORT_LINE_IN_L&t;0x0800
DECL|macro|MIXER_PORT_LINE_IN_R
mdefine_line|#define MIXER_PORT_LINE_IN_R&t;0x0900
DECL|macro|MIXER_PORT_POTS_REC
mdefine_line|#define MIXER_PORT_POTS_REC&t;0x0C00
DECL|macro|MIXER_PORT_MIC
mdefine_line|#define MIXER_PORT_MIC&t;&t;0x0E00
DECL|macro|GAIN12DB
mdefine_line|#define GAIN12DB&t;&t;0x00
DECL|macro|GAIN10DB
mdefine_line|#define GAIN10DB&t;&t;0x01
DECL|macro|GAIN08DB
mdefine_line|#define GAIN08DB&t;&t;0x02
DECL|macro|GAIN06DB
mdefine_line|#define GAIN06DB&t;&t;0x03
DECL|macro|GAIN04DB
mdefine_line|#define GAIN04DB&t;&t;0x04
DECL|macro|GAIN02DB
mdefine_line|#define GAIN02DB&t;&t;0x05
DECL|macro|GAIN00DB
mdefine_line|#define GAIN00DB&t;&t;0x06
DECL|macro|GAIN_02DB
mdefine_line|#define GAIN_02DB&t;&t;0x07
DECL|macro|GAIN_04DB
mdefine_line|#define GAIN_04DB&t;&t;0x08
DECL|macro|GAIN_06DB
mdefine_line|#define GAIN_06DB&t;&t;0x09
DECL|macro|GAIN_08DB
mdefine_line|#define GAIN_08DB&t;&t;0x0A
DECL|macro|GAIN_10DB
mdefine_line|#define GAIN_10DB&t;&t;0x0B
DECL|macro|GAIN_12DB
mdefine_line|#define GAIN_12DB&t;&t;0x0C
DECL|macro|GAIN_14DB
mdefine_line|#define GAIN_14DB&t;&t;0x0D
DECL|macro|GAIN_16DB
mdefine_line|#define GAIN_16DB&t;&t;0x0E
DECL|macro|GAIN_18DB
mdefine_line|#define GAIN_18DB&t;&t;0x0F
DECL|macro|GAIN_20DB
mdefine_line|#define GAIN_20DB&t;&t;0x10
DECL|macro|GAIN_22DB
mdefine_line|#define GAIN_22DB&t;&t;0x11
DECL|macro|GAIN_24DB
mdefine_line|#define GAIN_24DB&t;&t;0x12
DECL|macro|GAIN_26DB
mdefine_line|#define GAIN_26DB&t;&t;0x13
DECL|macro|GAIN_28DB
mdefine_line|#define GAIN_28DB&t;&t;0x14
DECL|macro|GAIN_30DB
mdefine_line|#define GAIN_30DB&t;&t;0x15
DECL|macro|GAIN_32DB
mdefine_line|#define GAIN_32DB&t;&t;0x16
DECL|macro|GAIN_34DB
mdefine_line|#define GAIN_34DB&t;&t;0x17
DECL|macro|GAIN_36DB
mdefine_line|#define GAIN_36DB&t;&t;0x18
DECL|macro|GAIN_38DB
mdefine_line|#define GAIN_38DB&t;&t;0x19
DECL|macro|GAIN_40DB
mdefine_line|#define GAIN_40DB&t;&t;0x1A
DECL|macro|GAIN_42DB
mdefine_line|#define GAIN_42DB&t;&t;0x1B
DECL|macro|GAIN_44DB
mdefine_line|#define GAIN_44DB&t;&t;0x1C
DECL|macro|GAIN_46DB
mdefine_line|#define GAIN_46DB&t;&t;0x1D
DECL|macro|GAIN_48DB
mdefine_line|#define GAIN_48DB&t;&t;0x1E
DECL|macro|GAIN_50DB
mdefine_line|#define GAIN_50DB&t;&t;0x1F
DECL|macro|INPUT_MUTE
mdefine_line|#define INPUT_MUTE&t;&t;0x80
multiline_comment|/******************************************************************************&n;* &n;* The POTS volume control use attenuation with 8 levels from 0dB to -28dB&n;* with steps of 4dB each, the defines should be OR&squot;ed together then sent&n;* as the parameter to the mixer command to change the mixer settings.&n;* &n;******************************************************************************/
DECL|macro|MIXER_PORT_POTS_PLAY
mdefine_line|#define MIXER_PORT_POTS_PLAY&t;0x0F00
DECL|macro|POTS_ATT_00DB
mdefine_line|#define POTS_ATT_00DB&t;&t;0x00
DECL|macro|POTS_ATT_04DB
mdefine_line|#define POTS_ATT_04DB&t;&t;0x01
DECL|macro|POTS_ATT_08DB
mdefine_line|#define POTS_ATT_08DB&t;&t;0x02
DECL|macro|POTS_ATT_12DB
mdefine_line|#define POTS_ATT_12DB&t;&t;0x03
DECL|macro|POTS_ATT_16DB
mdefine_line|#define POTS_ATT_16DB&t;&t;0x04
DECL|macro|POTS_ATT_20DB
mdefine_line|#define POTS_ATT_20DB&t;&t;0x05
DECL|macro|POTS_ATT_24DB
mdefine_line|#define POTS_ATT_24DB&t;&t;0x06
DECL|macro|POTS_ATT_28DB
mdefine_line|#define POTS_ATT_28DB&t;&t;0x07
DECL|macro|POTS_MUTE
mdefine_line|#define POTS_MUTE&t;&t;0x80
multiline_comment|/******************************************************************************&n;* &n;* The DAA controls the interface to the PSTN port.  The driver loads the&n;* US coefficients by default, so if you live in a different country you&n;* need to load the set for your countries phone system.&n;* &n;******************************************************************************/
DECL|macro|IXJCTL_DAA_COEFF_SET
mdefine_line|#define IXJCTL_DAA_COEFF_SET&t;&t;_IOW (&squot;q&squot;, 0xD0, int)
DECL|macro|DAA_US
mdefine_line|#define DAA_US &t;&t;1&t;
singleline_comment|//PITA 8kHz
DECL|macro|DAA_UK
mdefine_line|#define DAA_UK &t;&t;2&t;
singleline_comment|//ISAR34 8kHz
DECL|macro|DAA_FRANCE
mdefine_line|#define DAA_FRANCE &t;3&t;
singleline_comment|//
DECL|macro|DAA_GERMANY
mdefine_line|#define DAA_GERMANY&t;4
DECL|macro|DAA_AUSTRALIA
mdefine_line|#define DAA_AUSTRALIA&t;5
DECL|macro|DAA_JAPAN
mdefine_line|#define DAA_JAPAN&t;6
multiline_comment|/******************************************************************************&n;* &n;* Use IXJCTL_PORT to set or query the port the card is set to.  If the&n;* argument is set to PORT_QUERY, the return value of the ioctl will&n;* indicate which port is currently in use, otherwise it will change the&n;* port.&n;* &n;******************************************************************************/
DECL|macro|IXJCTL_PORT
mdefine_line|#define IXJCTL_PORT&t;&t;&t;_IOW (&squot;q&squot;, 0xD1, int)
DECL|macro|PORT_QUERY
mdefine_line|#define PORT_QUERY&t;0
DECL|macro|PORT_POTS
mdefine_line|#define PORT_POTS&t;1
DECL|macro|PORT_PSTN
mdefine_line|#define PORT_PSTN&t;2
DECL|macro|PORT_SPEAKER
mdefine_line|#define PORT_SPEAKER&t;3
DECL|macro|PORT_HANDSET
mdefine_line|#define PORT_HANDSET&t;4
DECL|macro|IXJCTL_PSTN_SET_STATE
mdefine_line|#define IXJCTL_PSTN_SET_STATE&t;&t;PHONE_PSTN_SET_STATE
DECL|macro|IXJCTL_PSTN_GET_STATE
mdefine_line|#define IXJCTL_PSTN_GET_STATE&t;&t;PHONE_PSTN_GET_STATE
DECL|macro|PSTN_ON_HOOK
mdefine_line|#define PSTN_ON_HOOK&t;0
DECL|macro|PSTN_RINGING
mdefine_line|#define PSTN_RINGING&t;1
DECL|macro|PSTN_OFF_HOOK
mdefine_line|#define PSTN_OFF_HOOK&t;2
DECL|macro|PSTN_PULSE_DIAL
mdefine_line|#define PSTN_PULSE_DIAL&t;3
multiline_comment|/******************************************************************************&n;* &n;* The DAA Analog GAIN sets 2 parameters at one time, the receive gain (AGRR), &n;* and the transmit gain (AGX).  OR together the components and pass them&n;* as the parameter to IXJCTL_DAA_AGAIN.  The default setting is both at 0dB.&n;* &n;******************************************************************************/
DECL|macro|IXJCTL_DAA_AGAIN
mdefine_line|#define IXJCTL_DAA_AGAIN&t;&t;_IOW (&squot;q&squot;, 0xD2, int)
DECL|macro|AGRR00DB
mdefine_line|#define AGRR00DB&t;0x00&t;
singleline_comment|// Analog gain in receive direction 0dB
DECL|macro|AGRR3_5DB
mdefine_line|#define AGRR3_5DB&t;0x10&t;
singleline_comment|// Analog gain in receive direction 3.5dB
DECL|macro|AGRR06DB
mdefine_line|#define AGRR06DB&t;0x30&t;
singleline_comment|// Analog gain in receive direction 6dB
DECL|macro|AGX00DB
mdefine_line|#define AGX00DB&t;&t;0x00&t;
singleline_comment|// Analog gain in transmit direction 0dB
DECL|macro|AGX_6DB
mdefine_line|#define AGX_6DB&t;&t;0x04&t;
singleline_comment|// Analog gain in transmit direction -6dB
DECL|macro|AGX3_5DB
mdefine_line|#define AGX3_5DB&t;0x08&t;
singleline_comment|// Analog gain in transmit direction 3.5dB
DECL|macro|AGX_2_5B
mdefine_line|#define AGX_2_5B&t;0x0C&t;
singleline_comment|// Analog gain in transmit direction -2.5dB
DECL|macro|IXJCTL_PSTN_LINETEST
mdefine_line|#define IXJCTL_PSTN_LINETEST&t;&t;_IO  (&squot;q&squot;, 0xD3)
DECL|macro|IXJCTL_CID
mdefine_line|#define IXJCTL_CID&t;&t;&t;_IOR (&squot;q&squot;, 0xD4, PHONE_CID *)
DECL|macro|IXJCTL_VMWI
mdefine_line|#define IXJCTL_VMWI&t;&t;&t;_IOR (&squot;q&squot;, 0xD8, int)
DECL|macro|IXJCTL_CIDCW
mdefine_line|#define IXJCTL_CIDCW&t;&t;&t;_IOW (&squot;q&squot;, 0xD9, PHONE_CID *)
multiline_comment|/******************************************************************************&n;* &n;* The wink duration is tunable with this ioctl.  The default wink duration  &n;* is 320ms.  You do not need to use this ioctl if you do not require a&n;* different wink duration.&n;* &n;******************************************************************************/
DECL|macro|IXJCTL_WINK_DURATION
mdefine_line|#define IXJCTL_WINK_DURATION&t;&t;PHONE_WINK_DURATION
multiline_comment|/******************************************************************************&n;* &n;* This ioctl will connect the POTS port to the PSTN port on the LineJACK&n;* In order for this to work properly the port selection should be set to&n;* the PSTN port with IXJCTL_PORT prior to calling this ioctl.  This will&n;* enable conference calls between PSTN callers and network callers.&n;* Passing a 1 to this ioctl enables the POTS&lt;-&gt;PSTN connection while&n;* passing a 0 turns it back off.&n;* &n;******************************************************************************/
DECL|macro|IXJCTL_POTS_PSTN
mdefine_line|#define IXJCTL_POTS_PSTN&t;&t;_IOW (&squot;q&squot;, 0xD5, int)
multiline_comment|/******************************************************************************&n;*&n;* IOCTLs added by request.&n;*&n;* IXJCTL_HZ sets the value your Linux kernel uses for HZ as defined in&n;*           /usr/include/asm/param.h, this determines the fundamental&n;*           frequency of the clock ticks on your Linux system.  The kernel&n;*           must be rebuilt if you change this value, also all modules you&n;*           use (except this one) must be recompiled.  The default value&n;*           is 100, and you only need to use this IOCTL if you use some&n;*           other value.&n;*&n;*&n;* IXJCTL_RATE sets the number of times per second that the driver polls&n;*             the DSP.  This value cannot be larger than HZ.  By&n;*             increasing both of these values, you may be able to reduce&n;*             latency because the max hang time that can exist between the&n;*             driver and the DSP will be reduced.&n;*&n;******************************************************************************/
DECL|macro|IXJCTL_HZ
mdefine_line|#define IXJCTL_HZ                       _IOW (&squot;q&squot;, 0xE0, int)
DECL|macro|IXJCTL_RATE
mdefine_line|#define IXJCTL_RATE                     _IOW (&squot;q&squot;, 0xE1, int)
DECL|macro|IXJCTL_FRAMES_READ
mdefine_line|#define IXJCTL_FRAMES_READ&t;&t;_IOR (&squot;q&squot;, 0xE2, unsigned long)
DECL|macro|IXJCTL_FRAMES_WRITTEN
mdefine_line|#define IXJCTL_FRAMES_WRITTEN&t;&t;_IOR (&squot;q&squot;, 0xE3, unsigned long)
DECL|macro|IXJCTL_READ_WAIT
mdefine_line|#define IXJCTL_READ_WAIT&t;&t;_IOR (&squot;q&squot;, 0xE4, unsigned long)
DECL|macro|IXJCTL_WRITE_WAIT
mdefine_line|#define IXJCTL_WRITE_WAIT&t;&t;_IOR (&squot;q&squot;, 0xE5, unsigned long)
DECL|macro|IXJCTL_DRYBUFFER_READ
mdefine_line|#define IXJCTL_DRYBUFFER_READ&t;&t;_IOR (&squot;q&squot;, 0xE6, unsigned long)
DECL|macro|IXJCTL_DRYBUFFER_CLEAR
mdefine_line|#define IXJCTL_DRYBUFFER_CLEAR&t;&t;_IO  (&squot;q&squot;, 0xE7)
multiline_comment|/******************************************************************************&n;*&n;* The intercom IOCTL&squot;s short the output from one card to the input of the&n;* other and vice versa (actually done in the DSP read function).  It is only&n;* necessary to execute the IOCTL on one card, but it is necessary to have&n;* both devices open to be able to detect hook switch changes.  The record&n;* codec and rate of each card must match the playback codec and rate of&n;* the other card for this to work properly.&n;*&n;******************************************************************************/
DECL|macro|IXJCTL_INTERCOM_START
mdefine_line|#define IXJCTL_INTERCOM_START &t;&t;_IOW (&squot;q&squot;, 0xFD, int)
DECL|macro|IXJCTL_INTERCOM_STOP
mdefine_line|#define IXJCTL_INTERCOM_STOP  &t;&t;_IOW (&squot;q&squot;, 0xFE, int)
eof
