multiline_comment|/* $Id: display7seg.h,v 1.2 2000/08/02 06:22:35 davem Exp $&n; *&n; * display7seg - Driver interface for the 7-segment display&n; * present on Sun Microsystems CP1400 and CP1500&n; *&n; * Copyright (c) 2000 Eric Brower &lt;ebrower@usa.net&gt;&n; *&n; */
macro_line|#ifndef __display7seg_h__
DECL|macro|__display7seg_h__
mdefine_line|#define __display7seg_h__
DECL|macro|D7S_IOC
mdefine_line|#define D7S_IOC&t;&squot;p&squot;
DECL|macro|D7SIOCRD
mdefine_line|#define D7SIOCRD _IOR(D7S_IOC, 0x45, int)&t;/* Read device state&t;*/
DECL|macro|D7SIOCWR
mdefine_line|#define D7SIOCWR _IOW(D7S_IOC, 0x46, int)&t;/* Write device state&t;*/
DECL|macro|D7SIOCTM
mdefine_line|#define D7SIOCTM _IO (D7S_IOC, 0x47)&t;&t;/* Translate mode (FLIP)*/
multiline_comment|/*&n; * ioctl flag definitions&n; *&n; * POINT&t;- Toggle decimal point&t;(0=absent 1=present)&n; * ALARM&t;- Toggle alarm LED &t;&t;(0=green  1=red)&n; * FLIP&t;&t;- Toggle inverted mode &t;(0=normal 1=flipped) &n; * bits 0-4&t;- Character displayed&t;(see definitions below)&n; *&n; * Display segments are defined as follows, &n; * subject to D7S_FLIP register state:&n; *&n; *    a&n; *   ---&n; * f|   |b&n; *   -g-&n; * e|   |c&n; *   ---&n; *    d&n; */
DECL|macro|D7S_POINT
mdefine_line|#define D7S_POINT&t;(1 &lt;&lt; 7)&t;/* Decimal point*/
DECL|macro|D7S_ALARM
mdefine_line|#define D7S_ALARM&t;(1 &lt;&lt; 6)&t;/* Alarm LED &t;*/
DECL|macro|D7S_FLIP
mdefine_line|#define D7S_FLIP&t;(1 &lt;&lt; 5)&t;/* Flip display */
DECL|macro|D7S_0
mdefine_line|#define D7S_0&t;&t;0x00&t;&t;/* Numerals 0-9 */
DECL|macro|D7S_1
mdefine_line|#define D7S_1&t;&t;0x01
DECL|macro|D7S_2
mdefine_line|#define D7S_2&t;&t;0x02
DECL|macro|D7S_3
mdefine_line|#define D7S_3&t;&t;0x03
DECL|macro|D7S_4
mdefine_line|#define D7S_4&t;&t;0x04
DECL|macro|D7S_5
mdefine_line|#define D7S_5&t;&t;0x05
DECL|macro|D7S_6
mdefine_line|#define D7S_6&t;&t;0x06
DECL|macro|D7S_7
mdefine_line|#define D7S_7&t;&t;0x07
DECL|macro|D7S_8
mdefine_line|#define D7S_8&t;&t;0x08
DECL|macro|D7S_9
mdefine_line|#define D7S_9&t;&t;0x09
DECL|macro|D7S_A
mdefine_line|#define D7S_A&t;&t;0x0A&t;&t;/* Letters A-F, H, L, P */
DECL|macro|D7S_B
mdefine_line|#define D7S_B&t;&t;0x0B
DECL|macro|D7S_C
mdefine_line|#define D7S_C&t;&t;0x0C
DECL|macro|D7S_D
mdefine_line|#define D7S_D&t;&t;0x0D
DECL|macro|D7S_E
mdefine_line|#define D7S_E&t;&t;0x0E
DECL|macro|D7S_F
mdefine_line|#define D7S_F&t;&t;0x0F
DECL|macro|D7S_H
mdefine_line|#define D7S_H&t;&t;0x10
DECL|macro|D7S_E2
mdefine_line|#define D7S_E2&t;&t;0x11
DECL|macro|D7S_L
mdefine_line|#define D7S_L&t;&t;0x12
DECL|macro|D7S_P
mdefine_line|#define D7S_P&t;&t;0x13
DECL|macro|D7S_SEGA
mdefine_line|#define D7S_SEGA&t;0x14&t;&t;/* Individual segments */
DECL|macro|D7S_SEGB
mdefine_line|#define D7S_SEGB&t;0x15
DECL|macro|D7S_SEGC
mdefine_line|#define D7S_SEGC&t;0x16
DECL|macro|D7S_SEGD
mdefine_line|#define D7S_SEGD&t;0x17
DECL|macro|D7S_SEGE
mdefine_line|#define D7S_SEGE&t;0x18
DECL|macro|D7S_SEGF
mdefine_line|#define D7S_SEGF&t;0x19
DECL|macro|D7S_SEGG
mdefine_line|#define D7S_SEGG&t;0x1A
DECL|macro|D7S_SEGABFG
mdefine_line|#define D7S_SEGABFG 0x1B&t;&t;/* Segment groupings */
DECL|macro|D7S_SEGCDEG
mdefine_line|#define D7S_SEGCDEG&t;0x1C
DECL|macro|D7S_SEGBCEF
mdefine_line|#define D7S_SEGBCEF 0x1D
DECL|macro|D7S_SEGADG
mdefine_line|#define D7S_SEGADG&t;0x1E
DECL|macro|D7S_BLANK
mdefine_line|#define D7S_BLANK&t;0x1F&t;&t;/* Clear all segments */
DECL|macro|D7S_MIN_VAL
mdefine_line|#define D7S_MIN_VAL&t;0x0
DECL|macro|D7S_MAX_VAL
mdefine_line|#define D7S_MAX_VAL&t;0x1F
macro_line|#endif /* ifndef __display7seg_h__ */
eof
