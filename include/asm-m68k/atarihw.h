multiline_comment|/*&n;** linux/atarihw.h -- This header defines some macros and pointers for&n;**                    the various Atari custom hardware registers.&n;**&n;** Copyright 1994 by Bj&#xfffd;rn Brauel&n;**&n;** 5/1/94 Roman Hodek:&n;**   Added definitions for TT specific chips.&n;**&n;** 1996-09-13 lars brinkhoff &lt;f93labr@dd.chalmers.se&gt;:&n;**   Finally added definitions for the matrix/codec and the DSP56001 host&n;**   interface.&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef _LINUX_ATARIHW_H_
DECL|macro|_LINUX_ATARIHW_H_
mdefine_line|#define _LINUX_ATARIHW_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/raw_io.h&gt;
r_extern
id|u_long
id|atari_mch_cookie
suffix:semicolon
r_extern
id|u_long
id|atari_mch_type
suffix:semicolon
r_extern
id|u_long
id|atari_switches
suffix:semicolon
r_extern
r_int
id|atari_rtc_year_offset
suffix:semicolon
r_extern
r_int
id|atari_dont_touch_floppy_select
suffix:semicolon
multiline_comment|/* convenience macros for testing machine type */
DECL|macro|MACH_IS_ST
mdefine_line|#define MACH_IS_ST&t;((atari_mch_cookie &gt;&gt; 16) == ATARI_MCH_ST)
DECL|macro|MACH_IS_STE
mdefine_line|#define MACH_IS_STE&t;((atari_mch_cookie &gt;&gt; 16) == ATARI_MCH_STE &amp;&amp; &bslash;&n;&t;&t;&t; (atari_mch_cookie &amp; 0xffff) == 0)
DECL|macro|MACH_IS_MSTE
mdefine_line|#define MACH_IS_MSTE&t;((atari_mch_cookie &gt;&gt; 16) == ATARI_MCH_STE &amp;&amp; &bslash;&n;&t;&t;&t; (atari_mch_cookie &amp; 0xffff) == 0x10)
DECL|macro|MACH_IS_TT
mdefine_line|#define MACH_IS_TT&t;((atari_mch_cookie &gt;&gt; 16) == ATARI_MCH_TT)
DECL|macro|MACH_IS_FALCON
mdefine_line|#define MACH_IS_FALCON&t;((atari_mch_cookie &gt;&gt; 16) == ATARI_MCH_FALCON)
DECL|macro|MACH_IS_MEDUSA
mdefine_line|#define MACH_IS_MEDUSA&t;(atari_mch_type == ATARI_MACH_MEDUSA)
DECL|macro|MACH_IS_HADES
mdefine_line|#define MACH_IS_HADES&t;(atari_mch_type == ATARI_MACH_HADES)
DECL|macro|MACH_IS_AB40
mdefine_line|#define MACH_IS_AB40&t;(atari_mch_type == ATARI_MACH_AB40)
multiline_comment|/* values for atari_switches */
DECL|macro|ATARI_SWITCH_IKBD
mdefine_line|#define ATARI_SWITCH_IKBD&t;0x01
DECL|macro|ATARI_SWITCH_MIDI
mdefine_line|#define ATARI_SWITCH_MIDI&t;0x02
DECL|macro|ATARI_SWITCH_SND6
mdefine_line|#define ATARI_SWITCH_SND6&t;0x04
DECL|macro|ATARI_SWITCH_SND7
mdefine_line|#define ATARI_SWITCH_SND7&t;0x08
DECL|macro|ATARI_SWITCH_OVSC_SHIFT
mdefine_line|#define ATARI_SWITCH_OVSC_SHIFT&t;16
DECL|macro|ATARI_SWITCH_OVSC_IKBD
mdefine_line|#define ATARI_SWITCH_OVSC_IKBD&t;(ATARI_SWITCH_IKBD &lt;&lt; ATARI_SWITCH_OVSC_SHIFT)
DECL|macro|ATARI_SWITCH_OVSC_MIDI
mdefine_line|#define ATARI_SWITCH_OVSC_MIDI&t;(ATARI_SWITCH_MIDI &lt;&lt; ATARI_SWITCH_OVSC_SHIFT)
DECL|macro|ATARI_SWITCH_OVSC_SND6
mdefine_line|#define ATARI_SWITCH_OVSC_SND6&t;(ATARI_SWITCH_SND6 &lt;&lt; ATARI_SWITCH_OVSC_SHIFT)
DECL|macro|ATARI_SWITCH_OVSC_SND7
mdefine_line|#define ATARI_SWITCH_OVSC_SND7&t;(ATARI_SWITCH_SND7 &lt;&lt; ATARI_SWITCH_OVSC_SHIFT)
DECL|macro|ATARI_SWITCH_OVSC_MASK
mdefine_line|#define ATARI_SWITCH_OVSC_MASK&t;0xffff0000
multiline_comment|/*&n; * Define several Hardware-Chips for indication so that for the ATARI we do&n; * no longer decide whether it is a Falcon or other machine . It&squot;s just&n; * important what hardware the machine uses&n; */
multiline_comment|/* ++roman 08/08/95: rewritten from ORing constants to a C bitfield */
DECL|macro|ATARIHW_DECLARE
mdefine_line|#define ATARIHW_DECLARE(name)&t;unsigned name : 1
DECL|macro|ATARIHW_SET
mdefine_line|#define ATARIHW_SET(name)&t;(atari_hw_present.name = 1)
DECL|macro|ATARIHW_PRESENT
mdefine_line|#define ATARIHW_PRESENT(name)&t;(atari_hw_present.name)
DECL|struct|atari_hw_present
r_struct
id|atari_hw_present
(brace
multiline_comment|/* video hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|STND_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* ST-Shifter - no base low ! */
id|ATARIHW_DECLARE
c_func
(paren
id|EXTD_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* STe-Shifter - 24 bit address */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* TT-Shifter */
id|ATARIHW_DECLARE
c_func
(paren
id|VIDEL_SHIFTER
)paren
suffix:semicolon
multiline_comment|/* Falcon-Shifter */
multiline_comment|/* sound hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|YM_2149
)paren
suffix:semicolon
multiline_comment|/* Yamaha YM 2149 */
id|ATARIHW_DECLARE
c_func
(paren
id|PCM_8BIT
)paren
suffix:semicolon
multiline_comment|/* PCM-Sound in STe-ATARI */
id|ATARIHW_DECLARE
c_func
(paren
id|CODEC
)paren
suffix:semicolon
multiline_comment|/* CODEC Sound (Falcon) */
multiline_comment|/* disk storage interfaces */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_SCSI
)paren
suffix:semicolon
multiline_comment|/* Directly mapped NCR5380 */
id|ATARIHW_DECLARE
c_func
(paren
id|ST_SCSI
)paren
suffix:semicolon
multiline_comment|/* NCR5380 via ST-DMA (Falcon) */
id|ATARIHW_DECLARE
c_func
(paren
id|ACSI
)paren
suffix:semicolon
multiline_comment|/* Standard ACSI like in STs */
id|ATARIHW_DECLARE
c_func
(paren
id|IDE
)paren
suffix:semicolon
multiline_comment|/* IDE Interface */
id|ATARIHW_DECLARE
c_func
(paren
id|FDCSPEED
)paren
suffix:semicolon
multiline_comment|/* 8/16 MHz switch for FDC */
multiline_comment|/* other I/O hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|ST_MFP
)paren
suffix:semicolon
multiline_comment|/* The ST-MFP (there should be no Atari&n;&t;&t;&t;&t;&t;   without it... but who knows?) */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_MFP
)paren
suffix:semicolon
multiline_comment|/* 2nd MFP */
id|ATARIHW_DECLARE
c_func
(paren
id|SCC
)paren
suffix:semicolon
multiline_comment|/* Serial Communications Contr. */
id|ATARIHW_DECLARE
c_func
(paren
id|ST_ESCC
)paren
suffix:semicolon
multiline_comment|/* SCC Z83230 in an ST */
id|ATARIHW_DECLARE
c_func
(paren
id|ANALOG_JOY
)paren
suffix:semicolon
multiline_comment|/* Paddle Interface for STe&n;&t;&t;&t;&t;&t;   and Falcon */
id|ATARIHW_DECLARE
c_func
(paren
id|MICROWIRE
)paren
suffix:semicolon
multiline_comment|/* Microwire Interface */
multiline_comment|/* DMA */
id|ATARIHW_DECLARE
c_func
(paren
id|STND_DMA
)paren
suffix:semicolon
multiline_comment|/* 24 Bit limited ST-DMA */
id|ATARIHW_DECLARE
c_func
(paren
id|EXTD_DMA
)paren
suffix:semicolon
multiline_comment|/* 32 Bit ST-DMA */
id|ATARIHW_DECLARE
c_func
(paren
id|SCSI_DMA
)paren
suffix:semicolon
multiline_comment|/* DMA for the NCR5380 */
id|ATARIHW_DECLARE
c_func
(paren
id|SCC_DMA
)paren
suffix:semicolon
multiline_comment|/* DMA for the SCC */
multiline_comment|/* real time clocks */
id|ATARIHW_DECLARE
c_func
(paren
id|TT_CLK
)paren
suffix:semicolon
multiline_comment|/* TT compatible clock chip */
id|ATARIHW_DECLARE
c_func
(paren
id|MSTE_CLK
)paren
suffix:semicolon
multiline_comment|/* Mega ST(E) clock chip */
multiline_comment|/* supporting hardware */
id|ATARIHW_DECLARE
c_func
(paren
id|SCU
)paren
suffix:semicolon
multiline_comment|/* System Control Unit */
id|ATARIHW_DECLARE
c_func
(paren
id|BLITTER
)paren
suffix:semicolon
multiline_comment|/* Blitter */
id|ATARIHW_DECLARE
c_func
(paren
id|VME
)paren
suffix:semicolon
multiline_comment|/* VME Bus */
id|ATARIHW_DECLARE
c_func
(paren
id|DSP56K
)paren
suffix:semicolon
multiline_comment|/* DSP56k processor in Falcon */
)brace
suffix:semicolon
r_extern
r_struct
id|atari_hw_present
id|atari_hw_present
suffix:semicolon
multiline_comment|/* Reading the MFP port register gives a machine independent delay, since the&n; * MFP always has a 8 MHz clock. This avoids problems with the varying length&n; * of nops on various machines. Somebody claimed that the tstb takes 600 ns.&n; */
DECL|macro|MFPDELAY
mdefine_line|#define&t;MFPDELAY() &bslash;&n;&t;__asm__ __volatile__ ( &quot;tstb %0&quot; : : &quot;m&quot; (mfp.par_dt_reg) : &quot;cc&quot; );
multiline_comment|/* Do cache push/invalidate for DMA read/write. This function obeys the&n; * snooping on some machines (Medusa) and processors: The Medusa itself can&n; * snoop, but only the &squot;040 can source data from its cache to DMA writes i.e.,&n; * reads from memory). Both &squot;040 and &squot;060 invalidate cache entries on snooped&n; * DMA reads (i.e., writes to memory).&n; */
DECL|macro|atari_readb
mdefine_line|#define atari_readb   raw_inb
DECL|macro|atari_writeb
mdefine_line|#define atari_writeb  raw_outb
DECL|macro|atari_inb_p
mdefine_line|#define atari_inb_p   raw_inb
DECL|macro|atari_outb_p
mdefine_line|#define atari_outb_p  raw_outb
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|function|dma_cache_maintenance
r_static
r_inline
r_void
id|dma_cache_maintenance
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|len
comma
r_int
id|writeflag
)paren
(brace
r_if
c_cond
(paren
id|writeflag
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MEDUSA
op_logical_or
id|CPU_IS_060
)paren
id|cache_push
c_func
(paren
id|paddr
comma
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MEDUSA
)paren
id|cache_clear
c_func
(paren
id|paddr
comma
id|len
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n;** Shifter  &n; */
DECL|macro|ST_LOW
mdefine_line|#define ST_LOW  0
DECL|macro|ST_MID
mdefine_line|#define ST_MID  1
DECL|macro|ST_HIGH
mdefine_line|#define ST_HIGH 2
DECL|macro|TT_LOW
mdefine_line|#define TT_LOW  7
DECL|macro|TT_MID
mdefine_line|#define TT_MID  4
DECL|macro|TT_HIGH
mdefine_line|#define TT_HIGH 6
DECL|macro|SHF_BAS
mdefine_line|#define SHF_BAS (0xffff8200)    
DECL|struct|SHIFTER
r_struct
id|SHIFTER
(brace
DECL|member|pad1
id|u_char
id|pad1
suffix:semicolon
DECL|member|bas_hi
id|u_char
id|bas_hi
suffix:semicolon
DECL|member|pad2
id|u_char
id|pad2
suffix:semicolon
DECL|member|bas_md
id|u_char
id|bas_md
suffix:semicolon
DECL|member|pad3
id|u_char
id|pad3
suffix:semicolon
DECL|member|vcounthi
id|u_char
r_volatile
id|vcounthi
suffix:semicolon
DECL|member|pad4
id|u_char
id|pad4
suffix:semicolon
DECL|member|vcountmid
id|u_char
r_volatile
id|vcountmid
suffix:semicolon
DECL|member|pad5
id|u_char
id|pad5
suffix:semicolon
DECL|member|vcountlow
id|u_char
r_volatile
id|vcountlow
suffix:semicolon
DECL|member|syncmode
id|u_char
r_volatile
id|syncmode
suffix:semicolon
DECL|member|pad6
id|u_char
id|pad6
suffix:semicolon
DECL|member|pad7
id|u_char
id|pad7
suffix:semicolon
DECL|member|bas_lo
id|u_char
id|bas_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|shifter
macro_line|# define shifter ((*(volatile struct SHIFTER *)SHF_BAS))
DECL|macro|SHF_FBAS
mdefine_line|#define SHF_FBAS (0xffff820e)
DECL|struct|SHIFTER_F030
r_struct
id|SHIFTER_F030
(brace
DECL|member|off_next
id|u_short
id|off_next
suffix:semicolon
DECL|member|scn_width
id|u_short
id|scn_width
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|shifter_f030
macro_line|# define shifter_f030 ((*(volatile struct SHIFTER_F030 *)SHF_FBAS))
DECL|macro|SHF_TBAS
mdefine_line|#define&t;SHF_TBAS (0xffff8200)
DECL|struct|SHIFTER_TT
r_struct
id|SHIFTER_TT
(brace
DECL|member|char_dummy0
id|u_char
id|char_dummy0
suffix:semicolon
DECL|member|bas_hi
id|u_char
id|bas_hi
suffix:semicolon
multiline_comment|/* video mem base addr, high and mid byte */
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|bas_md
id|u_char
id|bas_md
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|vcount_hi
id|u_char
id|vcount_hi
suffix:semicolon
multiline_comment|/* pointer to currently displayed byte */
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|vcount_md
id|u_char
id|vcount_md
suffix:semicolon
DECL|member|char_dummy4
id|u_char
id|char_dummy4
suffix:semicolon
DECL|member|vcount_lo
id|u_char
id|vcount_lo
suffix:semicolon
DECL|member|st_sync
id|u_short
id|st_sync
suffix:semicolon
multiline_comment|/* ST compatible sync mode register, unused */
DECL|member|char_dummy5
id|u_char
id|char_dummy5
suffix:semicolon
DECL|member|bas_lo
id|u_char
id|bas_lo
suffix:semicolon
multiline_comment|/* video mem addr, low byte */
DECL|member|char_dummy6
id|u_char
id|char_dummy6
(braket
l_int|2
op_plus
l_int|3
op_star
l_int|16
)braket
suffix:semicolon
multiline_comment|/* $ffff8240: */
DECL|member|color_reg
id|u_short
id|color_reg
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16 color registers */
DECL|member|st_shiftmode
id|u_char
id|st_shiftmode
suffix:semicolon
multiline_comment|/* ST compatible shift mode register, unused */
DECL|member|char_dummy7
id|u_char
id|char_dummy7
suffix:semicolon
DECL|member|tt_shiftmode
id|u_short
id|tt_shiftmode
suffix:semicolon
multiline_comment|/* TT shift mode register */
)brace
suffix:semicolon
DECL|macro|shifter_tt
mdefine_line|#define&t;shifter_tt&t;((*(volatile struct SHIFTER_TT *)SHF_TBAS))
multiline_comment|/* values for shifter_tt-&gt;tt_shiftmode */
DECL|macro|TT_SHIFTER_STLOW
mdefine_line|#define&t;TT_SHIFTER_STLOW&t;&t;0x0000
DECL|macro|TT_SHIFTER_STMID
mdefine_line|#define&t;TT_SHIFTER_STMID&t;&t;0x0100
DECL|macro|TT_SHIFTER_STHIGH
mdefine_line|#define&t;TT_SHIFTER_STHIGH&t;&t;0x0200
DECL|macro|TT_SHIFTER_TTLOW
mdefine_line|#define&t;TT_SHIFTER_TTLOW&t;&t;0x0700
DECL|macro|TT_SHIFTER_TTMID
mdefine_line|#define&t;TT_SHIFTER_TTMID&t;&t;0x0400
DECL|macro|TT_SHIFTER_TTHIGH
mdefine_line|#define&t;TT_SHIFTER_TTHIGH&t;&t;0x0600
DECL|macro|TT_SHIFTER_MODEMASK
mdefine_line|#define&t;TT_SHIFTER_MODEMASK&t;0x0700
DECL|macro|TT_SHIFTER_NUMMODE
mdefine_line|#define TT_SHIFTER_NUMMODE&t;0x0008
DECL|macro|TT_SHIFTER_PALETTE_MASK
mdefine_line|#define&t;TT_SHIFTER_PALETTE_MASK&t;0x000f
DECL|macro|TT_SHIFTER_GRAYMODE
mdefine_line|#define&t;TT_SHIFTER_GRAYMODE&t;&t;0x1000
multiline_comment|/* 256 TT palette registers */
DECL|macro|TT_PALETTE_BASE
mdefine_line|#define&t;TT_PALETTE_BASE&t;(0xffff8400)
DECL|macro|tt_palette
mdefine_line|#define&t;tt_palette&t;((volatile u_short *)TT_PALETTE_BASE)
DECL|macro|TT_PALETTE_RED_MASK
mdefine_line|#define&t;TT_PALETTE_RED_MASK&t;&t;0x0f00
DECL|macro|TT_PALETTE_GREEN_MASK
mdefine_line|#define&t;TT_PALETTE_GREEN_MASK&t;0x00f0
DECL|macro|TT_PALETTE_BLUE_MASK
mdefine_line|#define&t;TT_PALETTE_BLUE_MASK&t;0x000f
multiline_comment|/*&n;** Falcon030 VIDEL Video Controller&n;** for description see File &squot;linux&bslash;tools&bslash;atari&bslash;hardware.txt&n; */
DECL|macro|f030_col
mdefine_line|#define f030_col ((u_long *)&t;&t;0xffff9800)
DECL|macro|f030_xreg
mdefine_line|#define f030_xreg ((u_short*)&t;&t;0xffff8282)
DECL|macro|f030_yreg
mdefine_line|#define f030_yreg ((u_short*)&t;&t;0xffff82a2)
DECL|macro|f030_creg
mdefine_line|#define f030_creg ((u_short*)&t;&t;0xffff82c0)
DECL|macro|f030_sreg
mdefine_line|#define f030_sreg ((u_short*)&t;&t;0xffff8260)
DECL|macro|f030_mreg
mdefine_line|#define f030_mreg ((u_short*)&t;&t;0xffff820a)
DECL|macro|f030_linewidth
mdefine_line|#define f030_linewidth ((u_short*)      0xffff820e)
DECL|macro|f030_hscroll
mdefine_line|#define f030_hscroll ((u_char*)&t;&t;0xffff8265)
DECL|macro|VIDEL_BAS
mdefine_line|#define VIDEL_BAS (0xffff8260)
DECL|struct|VIDEL
r_struct
id|VIDEL
(brace
DECL|member|st_shift
id|u_short
id|st_shift
suffix:semicolon
DECL|member|pad1
id|u_short
id|pad1
suffix:semicolon
DECL|member|xoffset_s
id|u_char
id|xoffset_s
suffix:semicolon
DECL|member|xoffset
id|u_char
id|xoffset
suffix:semicolon
DECL|member|f_shift
id|u_short
id|f_shift
suffix:semicolon
DECL|member|pad2
id|u_char
id|pad2
(braket
l_int|0x1a
)braket
suffix:semicolon
DECL|member|hht
id|u_short
id|hht
suffix:semicolon
DECL|member|hbb
id|u_short
id|hbb
suffix:semicolon
DECL|member|hbe
id|u_short
id|hbe
suffix:semicolon
DECL|member|hdb
id|u_short
id|hdb
suffix:semicolon
DECL|member|hde
id|u_short
id|hde
suffix:semicolon
DECL|member|hss
id|u_short
id|hss
suffix:semicolon
DECL|member|pad3
id|u_char
id|pad3
(braket
l_int|0x14
)braket
suffix:semicolon
DECL|member|vft
id|u_short
id|vft
suffix:semicolon
DECL|member|vbb
id|u_short
id|vbb
suffix:semicolon
DECL|member|vbe
id|u_short
id|vbe
suffix:semicolon
DECL|member|vdb
id|u_short
id|vdb
suffix:semicolon
DECL|member|vde
id|u_short
id|vde
suffix:semicolon
DECL|member|vss
id|u_short
id|vss
suffix:semicolon
DECL|member|pad4
id|u_char
id|pad4
(braket
l_int|0x12
)braket
suffix:semicolon
DECL|member|control
id|u_short
id|control
suffix:semicolon
DECL|member|mode
id|u_short
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|videl
mdefine_line|#define&t;videl&t;((*(volatile struct VIDEL *)VIDEL_BAS))
multiline_comment|/*&n;** DMA/WD1772 Disk Controller&n; */
DECL|macro|FWD_BAS
mdefine_line|#define FWD_BAS (0xffff8604)  
DECL|struct|DMA_WD
r_struct
id|DMA_WD
(brace
DECL|member|fdc_acces_seccount
id|u_short
id|fdc_acces_seccount
suffix:semicolon
DECL|member|dma_mode_status
id|u_short
id|dma_mode_status
suffix:semicolon
DECL|member|dma_vhi
id|u_char
id|dma_vhi
suffix:semicolon
multiline_comment|/* Some extended ST-DMAs can handle 32 bit addresses */
DECL|member|dma_hi
id|u_char
id|dma_hi
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|dma_md
id|u_char
id|dma_md
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|dma_lo
id|u_char
id|dma_lo
suffix:semicolon
DECL|member|fdc_speed
id|u_short
id|fdc_speed
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|dma_wd
macro_line|# define dma_wd ((*(volatile struct DMA_WD *)FWD_BAS))
multiline_comment|/* alias */
DECL|macro|st_dma
mdefine_line|#define&t;st_dma dma_wd
multiline_comment|/* The two highest bytes of an extended DMA as a short; this is a must&n; * for the Medusa.&n; */
DECL|macro|st_dma_ext_dmahi
mdefine_line|#define st_dma_ext_dmahi (*((volatile unsigned short *)0xffff8608))
multiline_comment|/*&n;** YM2149 Sound Chip&n;** access in bytes&n; */
DECL|macro|YM_BAS
mdefine_line|#define YM_BAS (0xffff8800)
DECL|struct|SOUND_YM
r_struct
id|SOUND_YM
(brace
DECL|member|rd_data_reg_sel
id|u_char
id|rd_data_reg_sel
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|wd_data
id|u_char
id|wd_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sound_ym
mdefine_line|#define sound_ym ((*(volatile struct SOUND_YM *)YM_BAS))
multiline_comment|/* TT SCSI DMA */
DECL|macro|TT_SCSI_DMA_BAS
mdefine_line|#define&t;TT_SCSI_DMA_BAS&t;(0xffff8700)
DECL|struct|TT_DMA
r_struct
id|TT_DMA
(brace
DECL|member|char_dummy0
id|u_char
id|char_dummy0
suffix:semicolon
DECL|member|dma_addr_hi
id|u_char
id|dma_addr_hi
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|dma_addr_hmd
id|u_char
id|dma_addr_hmd
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|dma_addr_lmd
id|u_char
id|dma_addr_lmd
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|dma_addr_lo
id|u_char
id|dma_addr_lo
suffix:semicolon
DECL|member|char_dummy4
id|u_char
id|char_dummy4
suffix:semicolon
DECL|member|dma_cnt_hi
id|u_char
id|dma_cnt_hi
suffix:semicolon
DECL|member|char_dummy5
id|u_char
id|char_dummy5
suffix:semicolon
DECL|member|dma_cnt_hmd
id|u_char
id|dma_cnt_hmd
suffix:semicolon
DECL|member|char_dummy6
id|u_char
id|char_dummy6
suffix:semicolon
DECL|member|dma_cnt_lmd
id|u_char
id|dma_cnt_lmd
suffix:semicolon
DECL|member|char_dummy7
id|u_char
id|char_dummy7
suffix:semicolon
DECL|member|dma_cnt_lo
id|u_char
id|dma_cnt_lo
suffix:semicolon
DECL|member|dma_restdata
id|u_long
id|dma_restdata
suffix:semicolon
DECL|member|dma_ctrl
id|u_short
id|dma_ctrl
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tt_scsi_dma
mdefine_line|#define&t;tt_scsi_dma&t;((*(volatile struct TT_DMA *)TT_SCSI_DMA_BAS))
multiline_comment|/* TT SCSI Controller 5380 */
DECL|macro|TT_5380_BAS
mdefine_line|#define&t;TT_5380_BAS&t;(0xffff8781)
DECL|struct|TT_5380
r_struct
id|TT_5380
(brace
DECL|member|scsi_data
id|u_char
id|scsi_data
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|scsi_icr
id|u_char
id|scsi_icr
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|scsi_mode
id|u_char
id|scsi_mode
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|scsi_tcr
id|u_char
id|scsi_tcr
suffix:semicolon
DECL|member|char_dummy4
id|u_char
id|char_dummy4
suffix:semicolon
DECL|member|scsi_idstat
id|u_char
id|scsi_idstat
suffix:semicolon
DECL|member|char_dummy5
id|u_char
id|char_dummy5
suffix:semicolon
DECL|member|scsi_dmastat
id|u_char
id|scsi_dmastat
suffix:semicolon
DECL|member|char_dummy6
id|u_char
id|char_dummy6
suffix:semicolon
DECL|member|scsi_targrcv
id|u_char
id|scsi_targrcv
suffix:semicolon
DECL|member|char_dummy7
id|u_char
id|char_dummy7
suffix:semicolon
DECL|member|scsi_inircv
id|u_char
id|scsi_inircv
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tt_scsi
mdefine_line|#define&t;tt_scsi&t;&t;&t;((*(volatile struct TT_5380 *)TT_5380_BAS))
DECL|macro|tt_scsi_regp
mdefine_line|#define&t;tt_scsi_regp&t;((volatile char *)TT_5380_BAS)
multiline_comment|/* &n;** Falcon DMA Sound Subsystem&n; */
DECL|macro|MATRIX_BASE
mdefine_line|#define MATRIX_BASE (0xffff8930)
DECL|struct|MATRIX
r_struct
id|MATRIX
(brace
DECL|member|source
id|u_short
id|source
suffix:semicolon
DECL|member|destination
id|u_short
id|destination
suffix:semicolon
DECL|member|external_frequency_divider
id|u_char
id|external_frequency_divider
suffix:semicolon
DECL|member|internal_frequency_divider
id|u_char
id|internal_frequency_divider
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|matrix
mdefine_line|#define matrix (*(volatile struct MATRIX *)MATRIX_BASE)
DECL|macro|CODEC_BASE
mdefine_line|#define CODEC_BASE (0xffff8936)
DECL|struct|CODEC
r_struct
id|CODEC
(brace
DECL|member|tracks
id|u_char
id|tracks
suffix:semicolon
DECL|member|input_source
id|u_char
id|input_source
suffix:semicolon
DECL|macro|CODEC_SOURCE_ADC
mdefine_line|#define CODEC_SOURCE_ADC        1
DECL|macro|CODEC_SOURCE_MATRIX
mdefine_line|#define CODEC_SOURCE_MATRIX     2
DECL|member|adc_source
id|u_char
id|adc_source
suffix:semicolon
DECL|macro|ADC_SOURCE_RIGHT_PSG
mdefine_line|#define ADC_SOURCE_RIGHT_PSG    1
DECL|macro|ADC_SOURCE_LEFT_PSG
mdefine_line|#define ADC_SOURCE_LEFT_PSG     2
DECL|member|gain
id|u_char
id|gain
suffix:semicolon
DECL|macro|CODEC_GAIN_RIGHT
mdefine_line|#define CODEC_GAIN_RIGHT        0x0f
DECL|macro|CODEC_GAIN_LEFT
mdefine_line|#define CODEC_GAIN_LEFT         0xf0
DECL|member|attenuation
id|u_char
id|attenuation
suffix:semicolon
DECL|macro|CODEC_ATTENUATION_RIGHT
mdefine_line|#define CODEC_ATTENUATION_RIGHT 0x0f
DECL|macro|CODEC_ATTENUATION_LEFT
mdefine_line|#define CODEC_ATTENUATION_LEFT  0xf0
DECL|member|unused1
id|u_char
id|unused1
suffix:semicolon
DECL|member|status
id|u_char
id|status
suffix:semicolon
DECL|macro|CODEC_OVERFLOW_RIGHT
mdefine_line|#define CODEC_OVERFLOW_RIGHT    1
DECL|macro|CODEC_OVERFLOW_LEFT
mdefine_line|#define CODEC_OVERFLOW_LEFT     2
DECL|member|unused2
DECL|member|unused3
DECL|member|unused4
DECL|member|unused5
id|u_char
id|unused2
comma
id|unused3
comma
id|unused4
comma
id|unused5
suffix:semicolon
DECL|member|gpio_directions
id|u_char
id|gpio_directions
suffix:semicolon
DECL|macro|GPIO_IN
mdefine_line|#define GPIO_IN                 0
DECL|macro|GPIO_OUT
mdefine_line|#define GPIO_OUT                1
DECL|member|unused6
id|u_char
id|unused6
suffix:semicolon
DECL|member|gpio_data
id|u_char
id|gpio_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|codec
mdefine_line|#define codec (*(volatile struct CODEC *)CODEC_BASE)
multiline_comment|/*&n;** Falcon Blitter&n;*/
DECL|macro|BLT_BAS
mdefine_line|#define BLT_BAS (0xffff8a00)
DECL|struct|BLITTER
r_struct
id|BLITTER
(brace
DECL|member|halftone
id|u_short
id|halftone
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|src_x_inc
id|u_short
id|src_x_inc
suffix:semicolon
DECL|member|src_y_inc
id|u_short
id|src_y_inc
suffix:semicolon
DECL|member|src_address
id|u_long
id|src_address
suffix:semicolon
DECL|member|endmask1
id|u_short
id|endmask1
suffix:semicolon
DECL|member|endmask2
id|u_short
id|endmask2
suffix:semicolon
DECL|member|endmask3
id|u_short
id|endmask3
suffix:semicolon
DECL|member|dst_x_inc
id|u_short
id|dst_x_inc
suffix:semicolon
DECL|member|dst_y_inc
id|u_short
id|dst_y_inc
suffix:semicolon
DECL|member|dst_address
id|u_long
id|dst_address
suffix:semicolon
DECL|member|wd_per_line
id|u_short
id|wd_per_line
suffix:semicolon
DECL|member|ln_per_bb
id|u_short
id|ln_per_bb
suffix:semicolon
DECL|member|hlf_op_reg
id|u_short
id|hlf_op_reg
suffix:semicolon
DECL|member|log_op_reg
id|u_short
id|log_op_reg
suffix:semicolon
DECL|member|lin_nm_reg
id|u_short
id|lin_nm_reg
suffix:semicolon
DECL|member|skew_reg
id|u_short
id|skew_reg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|blitter
macro_line|# define blitter ((*(volatile struct BLITTER *)BLT_BAS))
multiline_comment|/*&n;** SCC Z8530&n; */
DECL|macro|SCC_BAS
mdefine_line|#define SCC_BAS (0xffff8c81)
DECL|struct|SCC
r_struct
id|SCC
(brace
DECL|member|cha_a_ctrl
id|u_char
id|cha_a_ctrl
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|cha_a_data
id|u_char
id|cha_a_data
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|cha_b_ctrl
id|u_char
id|cha_b_ctrl
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|cha_b_data
id|u_char
id|cha_b_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|scc
macro_line|# define scc ((*(volatile struct SCC*)SCC_BAS))
multiline_comment|/* The ESCC (Z85230) in an Atari ST. The channels are reversed! */
DECL|macro|st_escc
macro_line|# define st_escc ((*(volatile struct SCC*)0xfffffa31))
DECL|macro|st_escc_dsr
macro_line|# define st_escc_dsr ((*(volatile char *)0xfffffa39))
multiline_comment|/* TT SCC DMA Controller (same chip as SCSI DMA) */
DECL|macro|TT_SCC_DMA_BAS
mdefine_line|#define&t;TT_SCC_DMA_BAS&t;(0xffff8c00)
DECL|macro|tt_scc_dma
mdefine_line|#define&t;tt_scc_dma&t;((*(volatile struct TT_DMA *)TT_SCC_DMA_BAS))
multiline_comment|/*&n;** VIDEL Palette Register &n; */
DECL|macro|FPL_BAS
mdefine_line|#define FPL_BAS (0xffff9800)
DECL|struct|VIDEL_PALETTE
r_struct
id|VIDEL_PALETTE
(brace
DECL|member|reg
id|u_long
id|reg
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|videl_palette
macro_line|# define videl_palette ((*(volatile struct VIDEL_PALETTE*)FPL_BAS))
multiline_comment|/*&n;** Falcon DSP Host Interface&n; */
DECL|macro|DSP56K_HOST_INTERFACE_BASE
mdefine_line|#define DSP56K_HOST_INTERFACE_BASE (0xffffa200)
DECL|struct|DSP56K_HOST_INTERFACE
r_struct
id|DSP56K_HOST_INTERFACE
(brace
DECL|member|icr
id|u_char
id|icr
suffix:semicolon
DECL|macro|DSP56K_ICR_RREQ
mdefine_line|#define DSP56K_ICR_RREQ&t;0x01
DECL|macro|DSP56K_ICR_TREQ
mdefine_line|#define DSP56K_ICR_TREQ&t;0x02
DECL|macro|DSP56K_ICR_HF0
mdefine_line|#define DSP56K_ICR_HF0&t;0x08
DECL|macro|DSP56K_ICR_HF1
mdefine_line|#define DSP56K_ICR_HF1&t;0x10
DECL|macro|DSP56K_ICR_HM0
mdefine_line|#define DSP56K_ICR_HM0&t;0x20
DECL|macro|DSP56K_ICR_HM1
mdefine_line|#define DSP56K_ICR_HM1&t;0x40
DECL|macro|DSP56K_ICR_INIT
mdefine_line|#define DSP56K_ICR_INIT&t;0x80
DECL|member|cvr
id|u_char
id|cvr
suffix:semicolon
DECL|macro|DSP56K_CVR_HV_MASK
mdefine_line|#define DSP56K_CVR_HV_MASK 0x1f
DECL|macro|DSP56K_CVR_HC
mdefine_line|#define DSP56K_CVR_HC&t;0x80
DECL|member|isr
id|u_char
id|isr
suffix:semicolon
DECL|macro|DSP56K_ISR_RXDF
mdefine_line|#define DSP56K_ISR_RXDF&t;0x01
DECL|macro|DSP56K_ISR_TXDE
mdefine_line|#define DSP56K_ISR_TXDE&t;0x02
DECL|macro|DSP56K_ISR_TRDY
mdefine_line|#define DSP56K_ISR_TRDY&t;0x04
DECL|macro|DSP56K_ISR_HF2
mdefine_line|#define DSP56K_ISR_HF2&t;0x08
DECL|macro|DSP56K_ISR_HF3
mdefine_line|#define DSP56K_ISR_HF3&t;0x10
DECL|macro|DSP56K_ISR_DMA
mdefine_line|#define DSP56K_ISR_DMA&t;0x40
DECL|macro|DSP56K_ISR_HREQ
mdefine_line|#define DSP56K_ISR_HREQ&t;0x80
DECL|member|ivr
id|u_char
id|ivr
suffix:semicolon
r_union
(brace
DECL|member|b
id|u_char
id|b
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|w
id|u_short
id|w
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|l
id|u_long
id|l
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|dsp56k_host_interface
mdefine_line|#define dsp56k_host_interface ((*(volatile struct DSP56K_HOST_INTERFACE *)DSP56K_HOST_INTERFACE_BASE))
multiline_comment|/*&n;** MFP 68901&n; */
DECL|macro|MFP_BAS
mdefine_line|#define MFP_BAS (0xfffffa01)
DECL|struct|MFP
r_struct
id|MFP
(brace
DECL|member|par_dt_reg
id|u_char
id|par_dt_reg
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|active_edge
id|u_char
id|active_edge
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|data_dir
id|u_char
id|data_dir
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|int_en_a
id|u_char
id|int_en_a
suffix:semicolon
DECL|member|char_dummy4
id|u_char
id|char_dummy4
suffix:semicolon
DECL|member|int_en_b
id|u_char
id|int_en_b
suffix:semicolon
DECL|member|char_dummy5
id|u_char
id|char_dummy5
suffix:semicolon
DECL|member|int_pn_a
id|u_char
id|int_pn_a
suffix:semicolon
DECL|member|char_dummy6
id|u_char
id|char_dummy6
suffix:semicolon
DECL|member|int_pn_b
id|u_char
id|int_pn_b
suffix:semicolon
DECL|member|char_dummy7
id|u_char
id|char_dummy7
suffix:semicolon
DECL|member|int_sv_a
id|u_char
id|int_sv_a
suffix:semicolon
DECL|member|char_dummy8
id|u_char
id|char_dummy8
suffix:semicolon
DECL|member|int_sv_b
id|u_char
id|int_sv_b
suffix:semicolon
DECL|member|char_dummy9
id|u_char
id|char_dummy9
suffix:semicolon
DECL|member|int_mk_a
id|u_char
id|int_mk_a
suffix:semicolon
DECL|member|char_dummy10
id|u_char
id|char_dummy10
suffix:semicolon
DECL|member|int_mk_b
id|u_char
id|int_mk_b
suffix:semicolon
DECL|member|char_dummy11
id|u_char
id|char_dummy11
suffix:semicolon
DECL|member|vec_adr
id|u_char
id|vec_adr
suffix:semicolon
DECL|member|char_dummy12
id|u_char
id|char_dummy12
suffix:semicolon
DECL|member|tim_ct_a
id|u_char
id|tim_ct_a
suffix:semicolon
DECL|member|char_dummy13
id|u_char
id|char_dummy13
suffix:semicolon
DECL|member|tim_ct_b
id|u_char
id|tim_ct_b
suffix:semicolon
DECL|member|char_dummy14
id|u_char
id|char_dummy14
suffix:semicolon
DECL|member|tim_ct_cd
id|u_char
id|tim_ct_cd
suffix:semicolon
DECL|member|char_dummy15
id|u_char
id|char_dummy15
suffix:semicolon
DECL|member|tim_dt_a
id|u_char
id|tim_dt_a
suffix:semicolon
DECL|member|char_dummy16
id|u_char
id|char_dummy16
suffix:semicolon
DECL|member|tim_dt_b
id|u_char
id|tim_dt_b
suffix:semicolon
DECL|member|char_dummy17
id|u_char
id|char_dummy17
suffix:semicolon
DECL|member|tim_dt_c
id|u_char
id|tim_dt_c
suffix:semicolon
DECL|member|char_dummy18
id|u_char
id|char_dummy18
suffix:semicolon
DECL|member|tim_dt_d
id|u_char
id|tim_dt_d
suffix:semicolon
DECL|member|char_dummy19
id|u_char
id|char_dummy19
suffix:semicolon
DECL|member|sync_char
id|u_char
id|sync_char
suffix:semicolon
DECL|member|char_dummy20
id|u_char
id|char_dummy20
suffix:semicolon
DECL|member|usart_ctr
id|u_char
id|usart_ctr
suffix:semicolon
DECL|member|char_dummy21
id|u_char
id|char_dummy21
suffix:semicolon
DECL|member|rcv_stat
id|u_char
id|rcv_stat
suffix:semicolon
DECL|member|char_dummy22
id|u_char
id|char_dummy22
suffix:semicolon
DECL|member|trn_stat
id|u_char
id|trn_stat
suffix:semicolon
DECL|member|char_dummy23
id|u_char
id|char_dummy23
suffix:semicolon
DECL|member|usart_dta
id|u_char
id|usart_dta
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|mfp
macro_line|# define mfp ((*(volatile struct MFP*)MFP_BAS))
multiline_comment|/* TT&squot;s second MFP */
DECL|macro|TT_MFP_BAS
mdefine_line|#define&t;TT_MFP_BAS&t;(0xfffffa81)
DECL|macro|tt_mfp
macro_line|# define tt_mfp ((*(volatile struct MFP*)TT_MFP_BAS))
multiline_comment|/* TT System Control Unit */
DECL|macro|TT_SCU_BAS
mdefine_line|#define&t;TT_SCU_BAS&t;(0xffff8e01)
DECL|struct|TT_SCU
r_struct
id|TT_SCU
(brace
DECL|member|sys_mask
id|u_char
id|sys_mask
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|sys_stat
id|u_char
id|sys_stat
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|softint
id|u_char
id|softint
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|vmeint
id|u_char
id|vmeint
suffix:semicolon
DECL|member|char_dummy4
id|u_char
id|char_dummy4
suffix:semicolon
DECL|member|gp_reg1
id|u_char
id|gp_reg1
suffix:semicolon
DECL|member|char_dummy5
id|u_char
id|char_dummy5
suffix:semicolon
DECL|member|gp_reg2
id|u_char
id|gp_reg2
suffix:semicolon
DECL|member|char_dummy6
id|u_char
id|char_dummy6
suffix:semicolon
DECL|member|vme_mask
id|u_char
id|vme_mask
suffix:semicolon
DECL|member|char_dummy7
id|u_char
id|char_dummy7
suffix:semicolon
DECL|member|vme_stat
id|u_char
id|vme_stat
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tt_scu
mdefine_line|#define&t;tt_scu&t;((*(volatile struct TT_SCU *)TT_SCU_BAS))
multiline_comment|/* TT real time clock */
DECL|macro|TT_RTC_BAS
mdefine_line|#define&t;TT_RTC_BAS&t;(0xffff8961)
DECL|struct|TT_RTC
r_struct
id|TT_RTC
(brace
DECL|member|regsel
id|u_char
id|regsel
suffix:semicolon
DECL|member|dummy
id|u_char
id|dummy
suffix:semicolon
DECL|member|data
id|u_char
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tt_rtc
mdefine_line|#define&t;tt_rtc&t;((*(volatile struct TT_RTC *)TT_RTC_BAS))
multiline_comment|/*&n;** ACIA 6850&n; */
multiline_comment|/* constants for the ACIA registers */
multiline_comment|/* baudrate selection and reset (Baudrate = clock/factor) */
DECL|macro|ACIA_DIV1
mdefine_line|#define ACIA_DIV1  0
DECL|macro|ACIA_DIV16
mdefine_line|#define ACIA_DIV16 1
DECL|macro|ACIA_DIV64
mdefine_line|#define ACIA_DIV64 2
DECL|macro|ACIA_RESET
mdefine_line|#define ACIA_RESET 3
multiline_comment|/* character format */
DECL|macro|ACIA_D7E2S
mdefine_line|#define ACIA_D7E2S (0&lt;&lt;2)&t;/* 7 data, even parity, 2 stop */
DECL|macro|ACIA_D7O2S
mdefine_line|#define ACIA_D7O2S (1&lt;&lt;2)&t;/* 7 data, odd parity, 2 stop */
DECL|macro|ACIA_D7E1S
mdefine_line|#define ACIA_D7E1S (2&lt;&lt;2)&t;/* 7 data, even parity, 1 stop */
DECL|macro|ACIA_D7O1S
mdefine_line|#define ACIA_D7O1S (3&lt;&lt;2)&t;/* 7 data, odd parity, 1 stop */
DECL|macro|ACIA_D8N2S
mdefine_line|#define ACIA_D8N2S (4&lt;&lt;2)&t;/* 8 data, no parity, 2 stop */
DECL|macro|ACIA_D8N1S
mdefine_line|#define ACIA_D8N1S (5&lt;&lt;2)&t;/* 8 data, no parity, 1 stop */
DECL|macro|ACIA_D8E1S
mdefine_line|#define ACIA_D8E1S (6&lt;&lt;2)&t;/* 8 data, even parity, 1 stop */
DECL|macro|ACIA_D8O1S
mdefine_line|#define ACIA_D8O1S (7&lt;&lt;2)&t;/* 8 data, odd parity, 1 stop */
multiline_comment|/* transmit control */
DECL|macro|ACIA_RLTID
mdefine_line|#define ACIA_RLTID (0&lt;&lt;5)&t;/* RTS low, TxINT disabled */
DECL|macro|ACIA_RLTIE
mdefine_line|#define ACIA_RLTIE (1&lt;&lt;5)&t;/* RTS low, TxINT enabled */
DECL|macro|ACIA_RHTID
mdefine_line|#define ACIA_RHTID (2&lt;&lt;5)&t;/* RTS high, TxINT disabled */
DECL|macro|ACIA_RLTIDSB
mdefine_line|#define ACIA_RLTIDSB (3&lt;&lt;5)&t;/* RTS low, TxINT disabled, send break */
multiline_comment|/* receive control */
DECL|macro|ACIA_RID
mdefine_line|#define ACIA_RID (0&lt;&lt;7)&t;&t;/* RxINT disabled */
DECL|macro|ACIA_RIE
mdefine_line|#define ACIA_RIE (1&lt;&lt;7)&t;&t;/* RxINT enabled */
multiline_comment|/* status fields of the ACIA */
DECL|macro|ACIA_RDRF
mdefine_line|#define ACIA_RDRF 1&t;&t;/* Receive Data Register Full */
DECL|macro|ACIA_TDRE
mdefine_line|#define ACIA_TDRE (1&lt;&lt;1)&t;/* Transmit Data Register Empty */
DECL|macro|ACIA_DCD
mdefine_line|#define ACIA_DCD  (1&lt;&lt;2)&t;/* Data Carrier Detect */
DECL|macro|ACIA_CTS
mdefine_line|#define ACIA_CTS  (1&lt;&lt;3)&t;/* Clear To Send */
DECL|macro|ACIA_FE
mdefine_line|#define ACIA_FE   (1&lt;&lt;4)&t;/* Framing Error */
DECL|macro|ACIA_OVRN
mdefine_line|#define ACIA_OVRN (1&lt;&lt;5)&t;/* Receiver Overrun */
DECL|macro|ACIA_PE
mdefine_line|#define ACIA_PE   (1&lt;&lt;6)&t;/* Parity Error */
DECL|macro|ACIA_IRQ
mdefine_line|#define ACIA_IRQ  (1&lt;&lt;7)&t;/* Interrupt Request */
DECL|macro|ACIA_BAS
mdefine_line|#define ACIA_BAS (0xfffffc00)
DECL|struct|ACIA
r_struct
id|ACIA
(brace
DECL|member|key_ctrl
id|u_char
id|key_ctrl
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|key_data
id|u_char
id|key_data
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|mid_ctrl
id|u_char
id|mid_ctrl
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|mid_data
id|u_char
id|mid_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|acia
macro_line|# define acia ((*(volatile struct ACIA*)ACIA_BAS))
DECL|macro|TT_DMASND_BAS
mdefine_line|#define&t;TT_DMASND_BAS (0xffff8900)
DECL|struct|TT_DMASND
r_struct
id|TT_DMASND
(brace
DECL|member|int_ctrl
id|u_char
id|int_ctrl
suffix:semicolon
multiline_comment|/* Falcon: Interrupt control */
DECL|member|ctrl
id|u_char
id|ctrl
suffix:semicolon
DECL|member|pad2
id|u_char
id|pad2
suffix:semicolon
DECL|member|bas_hi
id|u_char
id|bas_hi
suffix:semicolon
DECL|member|pad3
id|u_char
id|pad3
suffix:semicolon
DECL|member|bas_mid
id|u_char
id|bas_mid
suffix:semicolon
DECL|member|pad4
id|u_char
id|pad4
suffix:semicolon
DECL|member|bas_low
id|u_char
id|bas_low
suffix:semicolon
DECL|member|pad5
id|u_char
id|pad5
suffix:semicolon
DECL|member|addr_hi
id|u_char
id|addr_hi
suffix:semicolon
DECL|member|pad6
id|u_char
id|pad6
suffix:semicolon
DECL|member|addr_mid
id|u_char
id|addr_mid
suffix:semicolon
DECL|member|pad7
id|u_char
id|pad7
suffix:semicolon
DECL|member|addr_low
id|u_char
id|addr_low
suffix:semicolon
DECL|member|pad8
id|u_char
id|pad8
suffix:semicolon
DECL|member|end_hi
id|u_char
id|end_hi
suffix:semicolon
DECL|member|pad9
id|u_char
id|pad9
suffix:semicolon
DECL|member|end_mid
id|u_char
id|end_mid
suffix:semicolon
DECL|member|pad10
id|u_char
id|pad10
suffix:semicolon
DECL|member|end_low
id|u_char
id|end_low
suffix:semicolon
DECL|member|pad11
id|u_char
id|pad11
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|track_select
id|u_char
id|track_select
suffix:semicolon
multiline_comment|/* Falcon */
DECL|member|mode
id|u_char
id|mode
suffix:semicolon
DECL|member|pad12
id|u_char
id|pad12
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Falcon only: */
DECL|member|cbar_src
id|u_short
id|cbar_src
suffix:semicolon
DECL|member|cbar_dst
id|u_short
id|cbar_dst
suffix:semicolon
DECL|member|ext_div
id|u_char
id|ext_div
suffix:semicolon
DECL|member|int_div
id|u_char
id|int_div
suffix:semicolon
DECL|member|rec_track_select
id|u_char
id|rec_track_select
suffix:semicolon
DECL|member|dac_src
id|u_char
id|dac_src
suffix:semicolon
DECL|member|adc_src
id|u_char
id|adc_src
suffix:semicolon
DECL|member|input_gain
id|u_char
id|input_gain
suffix:semicolon
DECL|member|output_atten
id|u_short
id|output_atten
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tt_dmasnd
macro_line|# define tt_dmasnd ((*(volatile struct TT_DMASND *)TT_DMASND_BAS))
DECL|macro|DMASND_MFP_INT_REPLAY
mdefine_line|#define DMASND_MFP_INT_REPLAY     0x01
DECL|macro|DMASND_MFP_INT_RECORD
mdefine_line|#define DMASND_MFP_INT_RECORD     0x02
DECL|macro|DMASND_TIMERA_INT_REPLAY
mdefine_line|#define DMASND_TIMERA_INT_REPLAY  0x04
DECL|macro|DMASND_TIMERA_INT_RECORD
mdefine_line|#define DMASND_TIMERA_INT_RECORD  0x08
DECL|macro|DMASND_CTRL_OFF
mdefine_line|#define&t;DMASND_CTRL_OFF&t;&t;  0x00
DECL|macro|DMASND_CTRL_ON
mdefine_line|#define&t;DMASND_CTRL_ON&t;&t;  0x01
DECL|macro|DMASND_CTRL_REPEAT
mdefine_line|#define&t;DMASND_CTRL_REPEAT&t;  0x02
DECL|macro|DMASND_CTRL_RECORD_ON
mdefine_line|#define DMASND_CTRL_RECORD_ON     0x10
DECL|macro|DMASND_CTRL_RECORD_OFF
mdefine_line|#define DMASND_CTRL_RECORD_OFF    0x00
DECL|macro|DMASND_CTRL_RECORD_REPEAT
mdefine_line|#define DMASND_CTRL_RECORD_REPEAT 0x20
DECL|macro|DMASND_CTRL_SELECT_REPLAY
mdefine_line|#define DMASND_CTRL_SELECT_REPLAY 0x00
DECL|macro|DMASND_CTRL_SELECT_RECORD
mdefine_line|#define DMASND_CTRL_SELECT_RECORD 0x80
DECL|macro|DMASND_MODE_MONO
mdefine_line|#define&t;DMASND_MODE_MONO&t;  0x80
DECL|macro|DMASND_MODE_STEREO
mdefine_line|#define&t;DMASND_MODE_STEREO&t;  0x00
DECL|macro|DMASND_MODE_8BIT
mdefine_line|#define DMASND_MODE_8BIT&t;  0x00
DECL|macro|DMASND_MODE_16BIT
mdefine_line|#define DMASND_MODE_16BIT&t;  0x40&t;/* Falcon only */
DECL|macro|DMASND_MODE_6KHZ
mdefine_line|#define&t;DMASND_MODE_6KHZ&t;  0x00&t;/* Falcon: mute */
DECL|macro|DMASND_MODE_12KHZ
mdefine_line|#define&t;DMASND_MODE_12KHZ&t;  0x01
DECL|macro|DMASND_MODE_25KHZ
mdefine_line|#define&t;DMASND_MODE_25KHZ&t;  0x02
DECL|macro|DMASND_MODE_50KHZ
mdefine_line|#define&t;DMASND_MODE_50KHZ&t;  0x03
DECL|macro|DMASNDSetBase
mdefine_line|#define DMASNDSetBase(bufstart)&t;&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tt_dmasnd.bas_hi  = (unsigned char)(((bufstart) &amp; 0xff0000) &gt;&gt; 16); &bslash;&n;&t;tt_dmasnd.bas_mid = (unsigned char)(((bufstart) &amp; 0x00ff00) &gt;&gt; 8); &bslash;&n;&t;tt_dmasnd.bas_low = (unsigned char) ((bufstart) &amp; 0x0000ff); &bslash;&n;    } while( 0 )
DECL|macro|DMASNDGetAdr
mdefine_line|#define DMASNDGetAdr() ((tt_dmasnd.addr_hi &lt;&lt; 16) +&t;&bslash;&n;&t;&t;&t;(tt_dmasnd.addr_mid &lt;&lt; 8) +&t;&bslash;&n;&t;&t;&t;(tt_dmasnd.addr_low))
DECL|macro|DMASNDSetEnd
mdefine_line|#define DMASNDSetEnd(bufend)&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tt_dmasnd.end_hi  = (unsigned char)(((bufend) &amp; 0xff0000) &gt;&gt; 16); &bslash;&n;&t;tt_dmasnd.end_mid = (unsigned char)(((bufend) &amp; 0x00ff00) &gt;&gt; 8); &bslash;&n;&t;tt_dmasnd.end_low = (unsigned char) ((bufend) &amp; 0x0000ff); &bslash;&n;    } while( 0 )
DECL|macro|TT_MICROWIRE_BAS
mdefine_line|#define&t;TT_MICROWIRE_BAS&t;(0xffff8922)
DECL|struct|TT_MICROWIRE
r_struct
id|TT_MICROWIRE
(brace
DECL|member|data
id|u_short
id|data
suffix:semicolon
DECL|member|mask
id|u_short
id|mask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tt_microwire
macro_line|# define tt_microwire ((*(volatile struct TT_MICROWIRE *)TT_MICROWIRE_BAS))
DECL|macro|MW_LM1992_ADDR
mdefine_line|#define&t;MW_LM1992_ADDR&t;&t;0x0400
DECL|macro|MW_LM1992_VOLUME
mdefine_line|#define&t;MW_LM1992_VOLUME(dB)&t;&bslash;&n;    (0x0c0 | ((dB) &lt; -80 ? 0 : (dB) &gt; 0 ? 40 : (((dB) + 80) / 2)))
DECL|macro|MW_LM1992_BALLEFT
mdefine_line|#define&t;MW_LM1992_BALLEFT(dB)&t;&bslash;&n;    (0x140 | ((dB) &lt; -40 ? 0 : (dB) &gt; 0 ? 20 : (((dB) + 40) / 2)))
DECL|macro|MW_LM1992_BALRIGHT
mdefine_line|#define&t;MW_LM1992_BALRIGHT(dB)&t;&bslash;&n;    (0x100 | ((dB) &lt; -40 ? 0 : (dB) &gt; 0 ? 20 : (((dB) + 40) / 2)))
DECL|macro|MW_LM1992_TREBLE
mdefine_line|#define&t;MW_LM1992_TREBLE(dB)&t;&bslash;&n;    (0x080 | ((dB) &lt; -12 ? 0 : (dB) &gt; 12 ? 12 : (((dB) / 2) + 6)))
DECL|macro|MW_LM1992_BASS
mdefine_line|#define&t;MW_LM1992_BASS(dB)&t;&bslash;&n;    (0x040 | ((dB) &lt; -12 ? 0 : (dB) &gt; 12 ? 12 : (((dB) / 2) + 6)))
DECL|macro|MW_LM1992_PSG_LOW
mdefine_line|#define&t;MW_LM1992_PSG_LOW&t;0x000
DECL|macro|MW_LM1992_PSG_HIGH
mdefine_line|#define&t;MW_LM1992_PSG_HIGH&t;0x001
DECL|macro|MW_LM1992_PSG_OFF
mdefine_line|#define&t;MW_LM1992_PSG_OFF&t;0x002
DECL|macro|MSTE_RTC_BAS
mdefine_line|#define MSTE_RTC_BAS&t;(0xfffffc21)
DECL|struct|MSTE_RTC
r_struct
id|MSTE_RTC
(brace
DECL|member|sec_ones
id|u_char
id|sec_ones
suffix:semicolon
DECL|member|dummy1
id|u_char
id|dummy1
suffix:semicolon
DECL|member|sec_tens
id|u_char
id|sec_tens
suffix:semicolon
DECL|member|dummy2
id|u_char
id|dummy2
suffix:semicolon
DECL|member|min_ones
id|u_char
id|min_ones
suffix:semicolon
DECL|member|dummy3
id|u_char
id|dummy3
suffix:semicolon
DECL|member|min_tens
id|u_char
id|min_tens
suffix:semicolon
DECL|member|dummy4
id|u_char
id|dummy4
suffix:semicolon
DECL|member|hr_ones
id|u_char
id|hr_ones
suffix:semicolon
DECL|member|dummy5
id|u_char
id|dummy5
suffix:semicolon
DECL|member|hr_tens
id|u_char
id|hr_tens
suffix:semicolon
DECL|member|dummy6
id|u_char
id|dummy6
suffix:semicolon
DECL|member|weekday
id|u_char
id|weekday
suffix:semicolon
DECL|member|dummy7
id|u_char
id|dummy7
suffix:semicolon
DECL|member|day_ones
id|u_char
id|day_ones
suffix:semicolon
DECL|member|dummy8
id|u_char
id|dummy8
suffix:semicolon
DECL|member|day_tens
id|u_char
id|day_tens
suffix:semicolon
DECL|member|dummy9
id|u_char
id|dummy9
suffix:semicolon
DECL|member|mon_ones
id|u_char
id|mon_ones
suffix:semicolon
DECL|member|dummy10
id|u_char
id|dummy10
suffix:semicolon
DECL|member|mon_tens
id|u_char
id|mon_tens
suffix:semicolon
DECL|member|dummy11
id|u_char
id|dummy11
suffix:semicolon
DECL|member|year_ones
id|u_char
id|year_ones
suffix:semicolon
DECL|member|dummy12
id|u_char
id|dummy12
suffix:semicolon
DECL|member|year_tens
id|u_char
id|year_tens
suffix:semicolon
DECL|member|dummy13
id|u_char
id|dummy13
suffix:semicolon
DECL|member|mode
id|u_char
id|mode
suffix:semicolon
DECL|member|dummy14
id|u_char
id|dummy14
suffix:semicolon
DECL|member|test
id|u_char
id|test
suffix:semicolon
DECL|member|dummy15
id|u_char
id|dummy15
suffix:semicolon
DECL|member|reset
id|u_char
id|reset
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|mste_rtc
mdefine_line|#define mste_rtc ((*(volatile struct MSTE_RTC *)MSTE_RTC_BAS))
macro_line|#endif /* linux/atarihw.h */
eof
