multiline_comment|/*&n;** asm-m68k/amigahw.h -- This header defines some macros and pointers for&n;**                    the various Amiga custom hardware registers.&n;**                    The naming conventions used here conform to those&n;**                    used in the Amiga Hardware Reference Manual, 3rd Edition&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created: 9/24/92 by Greg Harp&n;*/
macro_line|#ifndef _M68K_AMIGAHW_H
DECL|macro|_M68K_AMIGAHW_H
mdefine_line|#define _M68K_AMIGAHW_H
macro_line|#include &lt;linux/ioport.h&gt;
multiline_comment|/*&n;     *  Different Amiga models&n;     */
r_extern
r_int
r_int
id|amiga_model
suffix:semicolon
DECL|macro|AMI_UNKNOWN
mdefine_line|#define AMI_UNKNOWN&t;(0)
DECL|macro|AMI_500
mdefine_line|#define AMI_500&t;&t;(1)
DECL|macro|AMI_500PLUS
mdefine_line|#define AMI_500PLUS&t;(2)
DECL|macro|AMI_600
mdefine_line|#define AMI_600&t;&t;(3)
DECL|macro|AMI_1000
mdefine_line|#define AMI_1000&t;(4)
DECL|macro|AMI_1200
mdefine_line|#define AMI_1200&t;(5)
DECL|macro|AMI_2000
mdefine_line|#define AMI_2000&t;(6)
DECL|macro|AMI_2500
mdefine_line|#define AMI_2500&t;(7)
DECL|macro|AMI_3000
mdefine_line|#define AMI_3000&t;(8)
DECL|macro|AMI_3000T
mdefine_line|#define AMI_3000T&t;(9)
DECL|macro|AMI_3000PLUS
mdefine_line|#define AMI_3000PLUS&t;(10)
DECL|macro|AMI_4000
mdefine_line|#define AMI_4000&t;(11)
DECL|macro|AMI_4000T
mdefine_line|#define AMI_4000T&t;(12)
DECL|macro|AMI_CDTV
mdefine_line|#define AMI_CDTV&t;(13)
DECL|macro|AMI_CD32
mdefine_line|#define AMI_CD32&t;(14)
DECL|macro|AMI_DRACO
mdefine_line|#define AMI_DRACO&t;(15)
multiline_comment|/*&n;     *  Chipsets&n;     */
r_extern
r_int
r_int
id|amiga_chipset
suffix:semicolon
DECL|macro|CS_STONEAGE
mdefine_line|#define CS_STONEAGE&t;(0)
DECL|macro|CS_OCS
mdefine_line|#define CS_OCS&t;&t;(1)
DECL|macro|CS_ECS
mdefine_line|#define CS_ECS&t;&t;(2)
DECL|macro|CS_AGA
mdefine_line|#define CS_AGA&t;&t;(3)
multiline_comment|/*&n;     *  Miscellaneous&n;     */
r_extern
r_int
r_int
id|amiga_eclock
suffix:semicolon
multiline_comment|/* 700 kHz E Peripheral Clock */
r_extern
r_int
r_int
id|amiga_masterclock
suffix:semicolon
multiline_comment|/* 28 MHz Master Clock */
r_extern
r_int
r_int
id|amiga_colorclock
suffix:semicolon
multiline_comment|/* 3.5 MHz Color Clock */
r_extern
r_int
r_int
id|amiga_chip_size
suffix:semicolon
multiline_comment|/* Chip RAM Size (bytes) */
r_extern
r_int
r_char
id|amiga_vblank
suffix:semicolon
multiline_comment|/* VBLANK Frequency */
r_extern
r_int
r_char
id|amiga_psfreq
suffix:semicolon
multiline_comment|/* Power Supply Frequency */
DECL|macro|AMIGAHW_DECLARE
mdefine_line|#define AMIGAHW_DECLARE(name)&t;unsigned name : 1
DECL|macro|AMIGAHW_SET
mdefine_line|#define AMIGAHW_SET(name)&t;(amiga_hw_present.name = 1)
DECL|macro|AMIGAHW_PRESENT
mdefine_line|#define AMIGAHW_PRESENT(name)&t;(amiga_hw_present.name)
DECL|struct|amiga_hw_present
r_struct
id|amiga_hw_present
(brace
multiline_comment|/* video hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_VIDEO
)paren
suffix:semicolon
multiline_comment|/* Amiga Video */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_BLITTER
)paren
suffix:semicolon
multiline_comment|/* Amiga Blitter */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMBER_FF
)paren
suffix:semicolon
multiline_comment|/* Amber Flicker Fixer */
multiline_comment|/* sound hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_AUDIO
)paren
suffix:semicolon
multiline_comment|/* Amiga Audio */
multiline_comment|/* disk storage interfaces */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_FLOPPY
)paren
suffix:semicolon
multiline_comment|/* Amiga Floppy */
id|AMIGAHW_DECLARE
c_func
(paren
id|A3000_SCSI
)paren
suffix:semicolon
multiline_comment|/* SCSI (wd33c93, A3000 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A4000_SCSI
)paren
suffix:semicolon
multiline_comment|/* SCSI (ncr53c710, A4000T alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A1200_IDE
)paren
suffix:semicolon
multiline_comment|/* IDE (A1200 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A4000_IDE
)paren
suffix:semicolon
multiline_comment|/* IDE (A4000 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|CD_ROM
)paren
suffix:semicolon
multiline_comment|/* CD ROM drive */
multiline_comment|/* other I/O hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_KEYBOARD
)paren
suffix:semicolon
multiline_comment|/* Amiga Keyboard */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_MOUSE
)paren
suffix:semicolon
multiline_comment|/* Amiga Mouse */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_SERIAL
)paren
suffix:semicolon
multiline_comment|/* Amiga Serial */
id|AMIGAHW_DECLARE
c_func
(paren
id|AMI_PARALLEL
)paren
suffix:semicolon
multiline_comment|/* Amiga Parallel */
multiline_comment|/* real time clocks */
id|AMIGAHW_DECLARE
c_func
(paren
id|A2000_CLK
)paren
suffix:semicolon
multiline_comment|/* Hardware Clock (A2000 alike) */
id|AMIGAHW_DECLARE
c_func
(paren
id|A3000_CLK
)paren
suffix:semicolon
multiline_comment|/* Hardware Clock (A3000 alike) */
multiline_comment|/* supporting hardware */
id|AMIGAHW_DECLARE
c_func
(paren
id|CHIP_RAM
)paren
suffix:semicolon
multiline_comment|/* Chip RAM */
id|AMIGAHW_DECLARE
c_func
(paren
id|PAULA
)paren
suffix:semicolon
multiline_comment|/* Paula (8364) */
id|AMIGAHW_DECLARE
c_func
(paren
id|DENISE
)paren
suffix:semicolon
multiline_comment|/* Denise (8362) */
id|AMIGAHW_DECLARE
c_func
(paren
id|DENISE_HR
)paren
suffix:semicolon
multiline_comment|/* Denise (8373) */
id|AMIGAHW_DECLARE
c_func
(paren
id|LISA
)paren
suffix:semicolon
multiline_comment|/* Lisa (8375) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_PAL
)paren
suffix:semicolon
multiline_comment|/* Normal/Fat PAL Agnus (8367/8371) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_NTSC
)paren
suffix:semicolon
multiline_comment|/* Normal/Fat NTSC Agnus (8361/8370) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_HR_PAL
)paren
suffix:semicolon
multiline_comment|/* Fat Hires PAL Agnus (8372) */
id|AMIGAHW_DECLARE
c_func
(paren
id|AGNUS_HR_NTSC
)paren
suffix:semicolon
multiline_comment|/* Fat Hires NTSC Agnus (8372) */
id|AMIGAHW_DECLARE
c_func
(paren
id|ALICE_PAL
)paren
suffix:semicolon
multiline_comment|/* PAL Alice (8374) */
id|AMIGAHW_DECLARE
c_func
(paren
id|ALICE_NTSC
)paren
suffix:semicolon
multiline_comment|/* NTSC Alice (8374) */
id|AMIGAHW_DECLARE
c_func
(paren
id|MAGIC_REKICK
)paren
suffix:semicolon
multiline_comment|/* A3000 Magic Hard Rekick */
id|AMIGAHW_DECLARE
c_func
(paren
id|PCMCIA
)paren
suffix:semicolon
multiline_comment|/* PCMCIA Slot */
id|AMIGAHW_DECLARE
c_func
(paren
id|GG2_ISA
)paren
suffix:semicolon
multiline_comment|/* GG2 Zorro2ISA Bridge */
id|AMIGAHW_DECLARE
c_func
(paren
id|ZORRO
)paren
suffix:semicolon
multiline_comment|/* Zorro AutoConfig */
id|AMIGAHW_DECLARE
c_func
(paren
id|ZORRO3
)paren
suffix:semicolon
multiline_comment|/* Zorro III */
)brace
suffix:semicolon
r_extern
r_struct
id|amiga_hw_present
id|amiga_hw_present
suffix:semicolon
DECL|struct|CUSTOM
r_struct
id|CUSTOM
(brace
DECL|member|bltddat
r_int
r_int
id|bltddat
suffix:semicolon
DECL|member|dmaconr
r_int
r_int
id|dmaconr
suffix:semicolon
DECL|member|vposr
r_int
r_int
id|vposr
suffix:semicolon
DECL|member|vhposr
r_int
r_int
id|vhposr
suffix:semicolon
DECL|member|dskdatr
r_int
r_int
id|dskdatr
suffix:semicolon
DECL|member|joy0dat
r_int
r_int
id|joy0dat
suffix:semicolon
DECL|member|joy1dat
r_int
r_int
id|joy1dat
suffix:semicolon
DECL|member|clxdat
r_int
r_int
id|clxdat
suffix:semicolon
DECL|member|adkconr
r_int
r_int
id|adkconr
suffix:semicolon
DECL|member|pot0dat
r_int
r_int
id|pot0dat
suffix:semicolon
DECL|member|pot1dat
r_int
r_int
id|pot1dat
suffix:semicolon
DECL|member|potgor
r_int
r_int
id|potgor
suffix:semicolon
DECL|member|serdatr
r_int
r_int
id|serdatr
suffix:semicolon
DECL|member|dskbytr
r_int
r_int
id|dskbytr
suffix:semicolon
DECL|member|intenar
r_int
r_int
id|intenar
suffix:semicolon
DECL|member|intreqr
r_int
r_int
id|intreqr
suffix:semicolon
DECL|member|dskptr
r_int
r_char
op_star
id|dskptr
suffix:semicolon
DECL|member|dsklen
r_int
r_int
id|dsklen
suffix:semicolon
DECL|member|dskdat
r_int
r_int
id|dskdat
suffix:semicolon
DECL|member|refptr
r_int
r_int
id|refptr
suffix:semicolon
DECL|member|vposw
r_int
r_int
id|vposw
suffix:semicolon
DECL|member|vhposw
r_int
r_int
id|vhposw
suffix:semicolon
DECL|member|copcon
r_int
r_int
id|copcon
suffix:semicolon
DECL|member|serdat
r_int
r_int
id|serdat
suffix:semicolon
DECL|member|serper
r_int
r_int
id|serper
suffix:semicolon
DECL|member|potgo
r_int
r_int
id|potgo
suffix:semicolon
DECL|member|joytest
r_int
r_int
id|joytest
suffix:semicolon
DECL|member|strequ
r_int
r_int
id|strequ
suffix:semicolon
DECL|member|strvbl
r_int
r_int
id|strvbl
suffix:semicolon
DECL|member|strhor
r_int
r_int
id|strhor
suffix:semicolon
DECL|member|strlong
r_int
r_int
id|strlong
suffix:semicolon
DECL|member|bltcon0
r_int
r_int
id|bltcon0
suffix:semicolon
DECL|member|bltcon1
r_int
r_int
id|bltcon1
suffix:semicolon
DECL|member|bltafwm
r_int
r_int
id|bltafwm
suffix:semicolon
DECL|member|bltalwm
r_int
r_int
id|bltalwm
suffix:semicolon
DECL|member|bltcpt
r_int
r_char
op_star
id|bltcpt
suffix:semicolon
DECL|member|bltbpt
r_int
r_char
op_star
id|bltbpt
suffix:semicolon
DECL|member|bltapt
r_int
r_char
op_star
id|bltapt
suffix:semicolon
DECL|member|bltdpt
r_int
r_char
op_star
id|bltdpt
suffix:semicolon
DECL|member|bltsize
r_int
r_int
id|bltsize
suffix:semicolon
DECL|member|pad2d
r_int
r_char
id|pad2d
suffix:semicolon
DECL|member|bltcon0l
r_int
r_char
id|bltcon0l
suffix:semicolon
DECL|member|bltsizv
r_int
r_int
id|bltsizv
suffix:semicolon
DECL|member|bltsizh
r_int
r_int
id|bltsizh
suffix:semicolon
DECL|member|bltcmod
r_int
r_int
id|bltcmod
suffix:semicolon
DECL|member|bltbmod
r_int
r_int
id|bltbmod
suffix:semicolon
DECL|member|bltamod
r_int
r_int
id|bltamod
suffix:semicolon
DECL|member|bltdmod
r_int
r_int
id|bltdmod
suffix:semicolon
DECL|member|spare2
r_int
r_int
id|spare2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bltcdat
r_int
r_int
id|bltcdat
suffix:semicolon
DECL|member|bltbdat
r_int
r_int
id|bltbdat
suffix:semicolon
DECL|member|bltadat
r_int
r_int
id|bltadat
suffix:semicolon
DECL|member|spare3
r_int
r_int
id|spare3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|deniseid
r_int
r_int
id|deniseid
suffix:semicolon
DECL|member|dsksync
r_int
r_int
id|dsksync
suffix:semicolon
DECL|member|cop1lc
r_int
r_int
op_star
id|cop1lc
suffix:semicolon
DECL|member|cop2lc
r_int
r_int
op_star
id|cop2lc
suffix:semicolon
DECL|member|copjmp1
r_int
r_int
id|copjmp1
suffix:semicolon
DECL|member|copjmp2
r_int
r_int
id|copjmp2
suffix:semicolon
DECL|member|copins
r_int
r_int
id|copins
suffix:semicolon
DECL|member|diwstrt
r_int
r_int
id|diwstrt
suffix:semicolon
DECL|member|diwstop
r_int
r_int
id|diwstop
suffix:semicolon
DECL|member|ddfstrt
r_int
r_int
id|ddfstrt
suffix:semicolon
DECL|member|ddfstop
r_int
r_int
id|ddfstop
suffix:semicolon
DECL|member|dmacon
r_int
r_int
id|dmacon
suffix:semicolon
DECL|member|clxcon
r_int
r_int
id|clxcon
suffix:semicolon
DECL|member|intena
r_int
r_int
id|intena
suffix:semicolon
DECL|member|intreq
r_int
r_int
id|intreq
suffix:semicolon
DECL|member|adkcon
r_int
r_int
id|adkcon
suffix:semicolon
r_struct
(brace
DECL|member|audlc
r_int
r_int
op_star
id|audlc
suffix:semicolon
DECL|member|audlen
r_int
r_int
id|audlen
suffix:semicolon
DECL|member|audper
r_int
r_int
id|audper
suffix:semicolon
DECL|member|audvol
r_int
r_int
id|audvol
suffix:semicolon
DECL|member|auddat
r_int
r_int
id|auddat
suffix:semicolon
DECL|member|audspare
r_int
r_int
id|audspare
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|aud
)brace
id|aud
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bplpt
r_int
r_char
op_star
id|bplpt
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bplcon0
r_int
r_int
id|bplcon0
suffix:semicolon
DECL|member|bplcon1
r_int
r_int
id|bplcon1
suffix:semicolon
DECL|member|bplcon2
r_int
r_int
id|bplcon2
suffix:semicolon
DECL|member|bplcon3
r_int
r_int
id|bplcon3
suffix:semicolon
DECL|member|bpl1mod
r_int
r_int
id|bpl1mod
suffix:semicolon
DECL|member|bpl2mod
r_int
r_int
id|bpl2mod
suffix:semicolon
DECL|member|bplcon4
r_int
r_int
id|bplcon4
suffix:semicolon
DECL|member|clxcon2
r_int
r_int
id|clxcon2
suffix:semicolon
DECL|member|bpldat
r_int
r_int
id|bpldat
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sprpt
r_int
r_char
op_star
id|sprpt
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
DECL|member|pos
r_int
r_int
id|pos
suffix:semicolon
DECL|member|ctl
r_int
r_int
id|ctl
suffix:semicolon
DECL|member|dataa
r_int
r_int
id|dataa
suffix:semicolon
DECL|member|datab
r_int
r_int
id|datab
suffix:semicolon
DECL|member|spr
)brace
id|spr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|color
r_int
r_int
id|color
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|htotal
r_int
r_int
id|htotal
suffix:semicolon
DECL|member|hsstop
r_int
r_int
id|hsstop
suffix:semicolon
DECL|member|hbstrt
r_int
r_int
id|hbstrt
suffix:semicolon
DECL|member|hbstop
r_int
r_int
id|hbstop
suffix:semicolon
DECL|member|vtotal
r_int
r_int
id|vtotal
suffix:semicolon
DECL|member|vsstop
r_int
r_int
id|vsstop
suffix:semicolon
DECL|member|vbstrt
r_int
r_int
id|vbstrt
suffix:semicolon
DECL|member|vbstop
r_int
r_int
id|vbstop
suffix:semicolon
DECL|member|sprhstrt
r_int
r_int
id|sprhstrt
suffix:semicolon
DECL|member|sprhstop
r_int
r_int
id|sprhstop
suffix:semicolon
DECL|member|bplhstrt
r_int
r_int
id|bplhstrt
suffix:semicolon
DECL|member|bplhstop
r_int
r_int
id|bplhstop
suffix:semicolon
DECL|member|hhposw
r_int
r_int
id|hhposw
suffix:semicolon
DECL|member|hhposr
r_int
r_int
id|hhposr
suffix:semicolon
DECL|member|beamcon0
r_int
r_int
id|beamcon0
suffix:semicolon
DECL|member|hsstrt
r_int
r_int
id|hsstrt
suffix:semicolon
DECL|member|vsstrt
r_int
r_int
id|vsstrt
suffix:semicolon
DECL|member|hcenter
r_int
r_int
id|hcenter
suffix:semicolon
DECL|member|diwhigh
r_int
r_int
id|diwhigh
suffix:semicolon
DECL|member|spare4
r_int
r_int
id|spare4
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|fmode
r_int
r_int
id|fmode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * DMA register bits&n; */
DECL|macro|DMAF_SETCLR
mdefine_line|#define DMAF_SETCLR&t;&t;(0x8000)
DECL|macro|DMAF_AUD0
mdefine_line|#define DMAF_AUD0&t;&t;(0x0001)
DECL|macro|DMAF_AUD1
mdefine_line|#define DMAF_AUD1&t;&t;(0x0002)
DECL|macro|DMAF_AUD2
mdefine_line|#define DMAF_AUD2&t;&t;(0x0004)
DECL|macro|DMAF_AUD3
mdefine_line|#define DMAF_AUD3&t;&t;(0x0008)
DECL|macro|DMAF_DISK
mdefine_line|#define DMAF_DISK&t;&t;(0x0010)
DECL|macro|DMAF_SPRITE
mdefine_line|#define DMAF_SPRITE&t;&t;(0x0020)
DECL|macro|DMAF_BLITTER
mdefine_line|#define DMAF_BLITTER&t;&t;(0x0040)
DECL|macro|DMAF_COPPER
mdefine_line|#define DMAF_COPPER&t;&t;(0x0080)
DECL|macro|DMAF_RASTER
mdefine_line|#define DMAF_RASTER&t;&t;(0x0100)
DECL|macro|DMAF_MASTER
mdefine_line|#define DMAF_MASTER&t;&t;(0x0200)
DECL|macro|DMAF_BLITHOG
mdefine_line|#define DMAF_BLITHOG&t;&t;(0x0400)
DECL|macro|DMAF_BLTNZERO
mdefine_line|#define DMAF_BLTNZERO&t;&t;(0x2000)
DECL|macro|DMAF_BLTDONE
mdefine_line|#define DMAF_BLTDONE&t;&t;(0x4000)
DECL|macro|DMAF_ALL
mdefine_line|#define DMAF_ALL&t;&t;(0x01FF)
DECL|struct|CIA
r_struct
id|CIA
(brace
DECL|member|pra
DECL|member|pad0
r_int
r_char
id|pra
suffix:semicolon
r_char
id|pad0
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|prb
DECL|member|pad1
r_int
r_char
id|prb
suffix:semicolon
r_char
id|pad1
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|ddra
DECL|member|pad2
r_int
r_char
id|ddra
suffix:semicolon
r_char
id|pad2
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|ddrb
DECL|member|pad3
r_int
r_char
id|ddrb
suffix:semicolon
r_char
id|pad3
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|talo
DECL|member|pad4
r_int
r_char
id|talo
suffix:semicolon
r_char
id|pad4
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|tahi
DECL|member|pad5
r_int
r_char
id|tahi
suffix:semicolon
r_char
id|pad5
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|tblo
DECL|member|pad6
r_int
r_char
id|tblo
suffix:semicolon
r_char
id|pad6
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|tbhi
DECL|member|pad7
r_int
r_char
id|tbhi
suffix:semicolon
r_char
id|pad7
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|todlo
DECL|member|pad8
r_int
r_char
id|todlo
suffix:semicolon
r_char
id|pad8
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|todmid
DECL|member|pad9
r_int
r_char
id|todmid
suffix:semicolon
r_char
id|pad9
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|todhi
DECL|member|pada
r_int
r_char
id|todhi
suffix:semicolon
r_char
id|pada
(braket
l_int|0x1ff
)braket
suffix:semicolon
DECL|member|sdr
DECL|member|padb
r_int
r_char
id|sdr
suffix:semicolon
r_char
id|padb
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|icr
DECL|member|padc
r_int
r_char
id|icr
suffix:semicolon
r_char
id|padc
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|cra
DECL|member|padd
r_int
r_char
id|cra
suffix:semicolon
r_char
id|padd
(braket
l_int|0xff
)braket
suffix:semicolon
DECL|member|crb
DECL|member|pade
r_int
r_char
id|crb
suffix:semicolon
r_char
id|pade
(braket
l_int|0xff
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|zTwoBase
mdefine_line|#define zTwoBase (0x80000000)
DECL|macro|ZTWO_PADDR
mdefine_line|#define ZTWO_PADDR(x) (((unsigned long)(x))-zTwoBase)
DECL|macro|ZTWO_VADDR
mdefine_line|#define ZTWO_VADDR(x) (((unsigned long)(x))+zTwoBase)
DECL|macro|CUSTOM_PHYSADDR
mdefine_line|#define CUSTOM_PHYSADDR     (0xdff000)
DECL|macro|custom
mdefine_line|#define custom ((*(volatile struct CUSTOM *)(zTwoBase+CUSTOM_PHYSADDR)))
DECL|macro|CIAA_PHYSADDR
mdefine_line|#define CIAA_PHYSADDR&t;  (0xbfe001)
DECL|macro|CIAB_PHYSADDR
mdefine_line|#define CIAB_PHYSADDR&t;  (0xbfd000)
DECL|macro|ciaa
mdefine_line|#define ciaa   ((*(volatile struct CIA *)(zTwoBase + CIAA_PHYSADDR)))
DECL|macro|ciab
mdefine_line|#define ciab   ((*(volatile struct CIA *)(zTwoBase + CIAB_PHYSADDR)))
DECL|macro|CHIP_PHYSADDR
mdefine_line|#define CHIP_PHYSADDR&t;    (0x000000)
r_void
id|amiga_chip_init
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|amiga_chip_alloc
c_func
(paren
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
op_star
id|amiga_chip_alloc_res
c_func
(paren
r_int
r_int
id|size
comma
r_struct
id|resource
op_star
id|res
)paren
suffix:semicolon
r_void
id|amiga_chip_free
c_func
(paren
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_int
r_int
id|amiga_chip_avail
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*MILAN*/
r_extern
r_volatile
r_int
r_int
id|amiga_audio_min_period
suffix:semicolon
DECL|function|amifb_video_off
r_static
r_inline
r_void
id|amifb_video_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|amiga_chipset
op_eq
id|CS_ECS
op_logical_or
id|amiga_chipset
op_eq
id|CS_AGA
)paren
(brace
multiline_comment|/* program Denise/Lisa for a higher maximum play rate */
id|custom.htotal
op_assign
l_int|113
suffix:semicolon
multiline_comment|/* 31 kHz */
id|custom.vtotal
op_assign
l_int|223
suffix:semicolon
multiline_comment|/* 70 Hz */
id|custom.beamcon0
op_assign
l_int|0x4390
suffix:semicolon
multiline_comment|/* HARDDIS, VAR{BEAM,VSY,HSY,CSY}EN */
multiline_comment|/* suspend the monitor */
id|custom.hsstrt
op_assign
id|custom.hsstop
op_assign
l_int|116
suffix:semicolon
id|custom.vsstrt
op_assign
id|custom.vsstop
op_assign
l_int|226
suffix:semicolon
id|amiga_audio_min_period
op_assign
l_int|57
suffix:semicolon
)brace
)brace
DECL|struct|tod3000
r_struct
id|tod3000
(brace
DECL|member|second2
r_int
r_int
suffix:colon
l_int|28
comma
id|second2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|second1
r_int
r_int
suffix:colon
l_int|28
comma
id|second1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|minute2
r_int
r_int
suffix:colon
l_int|28
comma
id|minute2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|minute1
r_int
r_int
suffix:colon
l_int|28
comma
id|minute1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|hour2
r_int
r_int
suffix:colon
l_int|28
comma
id|hour2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|hour1
r_int
r_int
suffix:colon
l_int|28
comma
id|hour1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|weekday
r_int
r_int
suffix:colon
l_int|28
comma
id|weekday
suffix:colon
l_int|4
suffix:semicolon
DECL|member|day2
r_int
r_int
suffix:colon
l_int|28
comma
id|day2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|day1
r_int
r_int
suffix:colon
l_int|28
comma
id|day1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|month2
r_int
r_int
suffix:colon
l_int|28
comma
id|month2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|month1
r_int
r_int
suffix:colon
l_int|28
comma
id|month1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|year2
r_int
r_int
suffix:colon
l_int|28
comma
id|year2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|year1
r_int
r_int
suffix:colon
l_int|28
comma
id|year1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|cntrl1
r_int
r_int
suffix:colon
l_int|28
comma
id|cntrl1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* control-byte 1 */
DECL|member|cntrl2
r_int
r_int
suffix:colon
l_int|28
comma
id|cntrl2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* control-byte 2 */
DECL|member|cntrl3
r_int
r_int
suffix:colon
l_int|28
comma
id|cntrl3
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* control-byte 3 */
)brace
suffix:semicolon
DECL|macro|TOD3000_CNTRL1_HOLD
mdefine_line|#define TOD3000_CNTRL1_HOLD&t;0
DECL|macro|TOD3000_CNTRL1_FREE
mdefine_line|#define TOD3000_CNTRL1_FREE&t;9
DECL|macro|tod_3000
mdefine_line|#define tod_3000 ((*(volatile struct tod3000 *)(zTwoBase+0xDC0000)))
DECL|struct|tod2000
r_struct
id|tod2000
(brace
DECL|member|second2
r_int
r_int
suffix:colon
l_int|28
comma
id|second2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|second1
r_int
r_int
suffix:colon
l_int|28
comma
id|second1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|minute2
r_int
r_int
suffix:colon
l_int|28
comma
id|minute2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|minute1
r_int
r_int
suffix:colon
l_int|28
comma
id|minute1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|hour2
r_int
r_int
suffix:colon
l_int|28
comma
id|hour2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|hour1
r_int
r_int
suffix:colon
l_int|28
comma
id|hour1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|day2
r_int
r_int
suffix:colon
l_int|28
comma
id|day2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|day1
r_int
r_int
suffix:colon
l_int|28
comma
id|day1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|month2
r_int
r_int
suffix:colon
l_int|28
comma
id|month2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|month1
r_int
r_int
suffix:colon
l_int|28
comma
id|month1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|year2
r_int
r_int
suffix:colon
l_int|28
comma
id|year2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* lower digit */
DECL|member|year1
r_int
r_int
suffix:colon
l_int|28
comma
id|year1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* upper digit */
DECL|member|weekday
r_int
r_int
suffix:colon
l_int|28
comma
id|weekday
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cntrl1
r_int
r_int
suffix:colon
l_int|28
comma
id|cntrl1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* control-byte 1 */
DECL|member|cntrl2
r_int
r_int
suffix:colon
l_int|28
comma
id|cntrl2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* control-byte 2 */
DECL|member|cntrl3
r_int
r_int
suffix:colon
l_int|28
comma
id|cntrl3
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* control-byte 3 */
)brace
suffix:semicolon
DECL|macro|TOD2000_CNTRL1_HOLD
mdefine_line|#define TOD2000_CNTRL1_HOLD&t;(1&lt;&lt;0)
DECL|macro|TOD2000_CNTRL1_BUSY
mdefine_line|#define TOD2000_CNTRL1_BUSY&t;(1&lt;&lt;1)
DECL|macro|TOD2000_CNTRL3_24HMODE
mdefine_line|#define TOD2000_CNTRL3_24HMODE&t;(1&lt;&lt;2)
DECL|macro|TOD2000_HOUR1_PM
mdefine_line|#define TOD2000_HOUR1_PM&t;(1&lt;&lt;2)
DECL|macro|tod_2000
mdefine_line|#define tod_2000 ((*(volatile struct tod2000 *)(zTwoBase+0xDC0000)))
macro_line|#endif /* _M68K_AMIGAHW_H */
eof
