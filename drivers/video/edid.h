multiline_comment|/* &n; * drivers/video/edid.h - EDID/DDC Header&n; *&n; * Based on:&n; *   1. XFree86 4.3.0, edid.h&n; *      Copyright 1998 by Egbert Eich &lt;Egbert.Eich@Physik.TU-Darmstadt.DE&gt;&n; * &n; *   2. John Fremlin &lt;vii@users.sourceforge.net&gt; and &n; *      Ani Joshi &lt;ajoshi@unixbox.com&gt;&n; *&n; * DDC is a Trademark of VESA (Video Electronics Standard Association).&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n;*/
macro_line|#ifndef __EDID_H__
DECL|macro|__EDID_H__
mdefine_line|#define __EDID_H__
DECL|macro|EDID_LENGTH
mdefine_line|#define EDID_LENGTH&t;&t;&t;&t;0x80
DECL|macro|EDID_HEADER
mdefine_line|#define EDID_HEADER&t;&t;&t;&t;0x00
DECL|macro|EDID_HEADER_END
mdefine_line|#define EDID_HEADER_END&t;&t;&t;&t;0x07
DECL|macro|ID_MANUFACTURER_NAME
mdefine_line|#define ID_MANUFACTURER_NAME&t;&t;&t;0x08
DECL|macro|ID_MANUFACTURER_NAME_END
mdefine_line|#define ID_MANUFACTURER_NAME_END&t;&t;0x09
DECL|macro|ID_MODEL
mdefine_line|#define ID_MODEL&t;&t;&t;&t;0x0a
DECL|macro|ID_SERIAL_NUMBER
mdefine_line|#define ID_SERIAL_NUMBER&t;&t;&t;0x0c
DECL|macro|MANUFACTURE_WEEK
mdefine_line|#define MANUFACTURE_WEEK&t;&t;&t;0x10
DECL|macro|MANUFACTURE_YEAR
mdefine_line|#define MANUFACTURE_YEAR&t;&t;&t;0x11
DECL|macro|EDID_STRUCT_VERSION
mdefine_line|#define EDID_STRUCT_VERSION&t;&t;&t;0x12
DECL|macro|EDID_STRUCT_REVISION
mdefine_line|#define EDID_STRUCT_REVISION&t;&t;&t;0x13
DECL|macro|EDID_STRUCT_DISPLAY
mdefine_line|#define EDID_STRUCT_DISPLAY                     0x14
DECL|macro|DPMS_FLAGS
mdefine_line|#define DPMS_FLAGS&t;&t;&t;&t;0x18
DECL|macro|ESTABLISHED_TIMING_1
mdefine_line|#define ESTABLISHED_TIMING_1&t;&t;&t;0x23
DECL|macro|ESTABLISHED_TIMING_2
mdefine_line|#define ESTABLISHED_TIMING_2&t;&t;&t;0x24
DECL|macro|MANUFACTURERS_TIMINGS
mdefine_line|#define MANUFACTURERS_TIMINGS&t;&t;&t;0x25
multiline_comment|/* standard timings supported */
DECL|macro|STD_TIMING
mdefine_line|#define STD_TIMING                              8
DECL|macro|STD_TIMING_DESCRIPTION_SIZE
mdefine_line|#define STD_TIMING_DESCRIPTION_SIZE             2
DECL|macro|STD_TIMING_DESCRIPTIONS_START
mdefine_line|#define STD_TIMING_DESCRIPTIONS_START           0x26
DECL|macro|DETAILED_TIMING_DESCRIPTIONS_START
mdefine_line|#define DETAILED_TIMING_DESCRIPTIONS_START&t;0x36
DECL|macro|DETAILED_TIMING_DESCRIPTION_SIZE
mdefine_line|#define DETAILED_TIMING_DESCRIPTION_SIZE&t;18
DECL|macro|NO_DETAILED_TIMING_DESCRIPTIONS
mdefine_line|#define NO_DETAILED_TIMING_DESCRIPTIONS&t;&t;4
DECL|macro|DETAILED_TIMING_DESCRIPTION_1
mdefine_line|#define DETAILED_TIMING_DESCRIPTION_1&t;&t;0x36
DECL|macro|DETAILED_TIMING_DESCRIPTION_2
mdefine_line|#define DETAILED_TIMING_DESCRIPTION_2&t;&t;0x48
DECL|macro|DETAILED_TIMING_DESCRIPTION_3
mdefine_line|#define DETAILED_TIMING_DESCRIPTION_3&t;&t;0x5a
DECL|macro|DETAILED_TIMING_DESCRIPTION_4
mdefine_line|#define DETAILED_TIMING_DESCRIPTION_4&t;&t;0x6c
DECL|macro|DESCRIPTOR_DATA
mdefine_line|#define DESCRIPTOR_DATA&t;&t;&t;&t;5
DECL|macro|UPPER_NIBBLE
mdefine_line|#define UPPER_NIBBLE( x ) &bslash;&n;        (((128|64|32|16) &amp; (x)) &gt;&gt; 4)
DECL|macro|LOWER_NIBBLE
mdefine_line|#define LOWER_NIBBLE( x ) &bslash;&n;        ((1|2|4|8) &amp; (x))
DECL|macro|COMBINE_HI_8LO
mdefine_line|#define COMBINE_HI_8LO( hi, lo ) &bslash;&n;        ( (((unsigned)hi) &lt;&lt; 8) | (unsigned)lo )
DECL|macro|COMBINE_HI_4LO
mdefine_line|#define COMBINE_HI_4LO( hi, lo ) &bslash;&n;        ( (((unsigned)hi) &lt;&lt; 4) | (unsigned)lo )
DECL|macro|PIXEL_CLOCK_LO
mdefine_line|#define PIXEL_CLOCK_LO     (unsigned)block[ 0 ]
DECL|macro|PIXEL_CLOCK_HI
mdefine_line|#define PIXEL_CLOCK_HI     (unsigned)block[ 1 ]
DECL|macro|PIXEL_CLOCK
mdefine_line|#define PIXEL_CLOCK&t;   (COMBINE_HI_8LO( PIXEL_CLOCK_HI,PIXEL_CLOCK_LO )*10000)
DECL|macro|H_ACTIVE_LO
mdefine_line|#define H_ACTIVE_LO        (unsigned)block[ 2 ]
DECL|macro|H_BLANKING_LO
mdefine_line|#define H_BLANKING_LO      (unsigned)block[ 3 ]
DECL|macro|H_ACTIVE_HI
mdefine_line|#define H_ACTIVE_HI        UPPER_NIBBLE( (unsigned)block[ 4 ] )
DECL|macro|H_ACTIVE
mdefine_line|#define H_ACTIVE           COMBINE_HI_8LO( H_ACTIVE_HI, H_ACTIVE_LO )
DECL|macro|H_BLANKING_HI
mdefine_line|#define H_BLANKING_HI      LOWER_NIBBLE( (unsigned)block[ 4 ] )
DECL|macro|H_BLANKING
mdefine_line|#define H_BLANKING         COMBINE_HI_8LO( H_BLANKING_HI, H_BLANKING_LO )
DECL|macro|V_ACTIVE_LO
mdefine_line|#define V_ACTIVE_LO        (unsigned)block[ 5 ]
DECL|macro|V_BLANKING_LO
mdefine_line|#define V_BLANKING_LO      (unsigned)block[ 6 ]
DECL|macro|V_ACTIVE_HI
mdefine_line|#define V_ACTIVE_HI        UPPER_NIBBLE( (unsigned)block[ 7 ] )
DECL|macro|V_ACTIVE
mdefine_line|#define V_ACTIVE           COMBINE_HI_8LO( V_ACTIVE_HI, V_ACTIVE_LO )
DECL|macro|V_BLANKING_HI
mdefine_line|#define V_BLANKING_HI      LOWER_NIBBLE( (unsigned)block[ 7 ] )
DECL|macro|V_BLANKING
mdefine_line|#define V_BLANKING         COMBINE_HI_8LO( V_BLANKING_HI, V_BLANKING_LO )
DECL|macro|H_SYNC_OFFSET_LO
mdefine_line|#define H_SYNC_OFFSET_LO   (unsigned)block[ 8 ]
DECL|macro|H_SYNC_WIDTH_LO
mdefine_line|#define H_SYNC_WIDTH_LO    (unsigned)block[ 9 ]
DECL|macro|V_SYNC_OFFSET_LO
mdefine_line|#define V_SYNC_OFFSET_LO   UPPER_NIBBLE( (unsigned)block[ 10 ] )
DECL|macro|V_SYNC_WIDTH_LO
mdefine_line|#define V_SYNC_WIDTH_LO    LOWER_NIBBLE( (unsigned)block[ 10 ] )
DECL|macro|V_SYNC_WIDTH_HI
mdefine_line|#define V_SYNC_WIDTH_HI    ((unsigned)block[ 11 ] &amp; (1|2))
DECL|macro|V_SYNC_OFFSET_HI
mdefine_line|#define V_SYNC_OFFSET_HI   (((unsigned)block[ 11 ] &amp; (4|8)) &gt;&gt; 2)
DECL|macro|H_SYNC_WIDTH_HI
mdefine_line|#define H_SYNC_WIDTH_HI    (((unsigned)block[ 11 ] &amp; (16|32)) &gt;&gt; 4)
DECL|macro|H_SYNC_OFFSET_HI
mdefine_line|#define H_SYNC_OFFSET_HI   (((unsigned)block[ 11 ] &amp; (64|128)) &gt;&gt; 6)
DECL|macro|V_SYNC_WIDTH
mdefine_line|#define V_SYNC_WIDTH       COMBINE_HI_4LO( V_SYNC_WIDTH_HI, V_SYNC_WIDTH_LO )
DECL|macro|V_SYNC_OFFSET
mdefine_line|#define V_SYNC_OFFSET      COMBINE_HI_4LO( V_SYNC_OFFSET_HI, V_SYNC_OFFSET_LO )
DECL|macro|H_SYNC_WIDTH
mdefine_line|#define H_SYNC_WIDTH       COMBINE_HI_4LO( H_SYNC_WIDTH_HI, H_SYNC_WIDTH_LO )
DECL|macro|H_SYNC_OFFSET
mdefine_line|#define H_SYNC_OFFSET      COMBINE_HI_4LO( H_SYNC_OFFSET_HI, H_SYNC_OFFSET_LO )
DECL|macro|H_SIZE_LO
mdefine_line|#define H_SIZE_LO          (unsigned)block[ 12 ]
DECL|macro|V_SIZE_LO
mdefine_line|#define V_SIZE_LO          (unsigned)block[ 13 ]
DECL|macro|H_SIZE_HI
mdefine_line|#define H_SIZE_HI          UPPER_NIBBLE( (unsigned)block[ 14 ] )
DECL|macro|V_SIZE_HI
mdefine_line|#define V_SIZE_HI          LOWER_NIBBLE( (unsigned)block[ 14 ] )
DECL|macro|H_SIZE
mdefine_line|#define H_SIZE             COMBINE_HI_8LO( H_SIZE_HI, H_SIZE_LO )
DECL|macro|V_SIZE
mdefine_line|#define V_SIZE             COMBINE_HI_8LO( V_SIZE_HI, V_SIZE_LO )
DECL|macro|H_BORDER
mdefine_line|#define H_BORDER           (unsigned)block[ 15 ]
DECL|macro|V_BORDER
mdefine_line|#define V_BORDER           (unsigned)block[ 16 ]
DECL|macro|FLAGS
mdefine_line|#define FLAGS              (unsigned)block[ 17 ]
DECL|macro|INTERLACED
mdefine_line|#define INTERLACED         (FLAGS&amp;128)
DECL|macro|SYNC_TYPE
mdefine_line|#define SYNC_TYPE          (FLAGS&amp;3&lt;&lt;3)&t;/* bits 4,3 */
DECL|macro|SYNC_SEPARATE
mdefine_line|#define SYNC_SEPARATE      (3&lt;&lt;3)
DECL|macro|HSYNC_POSITIVE
mdefine_line|#define HSYNC_POSITIVE     (FLAGS &amp; 4)
DECL|macro|VSYNC_POSITIVE
mdefine_line|#define VSYNC_POSITIVE     (FLAGS &amp; 2)
DECL|macro|V_MIN_RATE
mdefine_line|#define V_MIN_RATE              block[ 5 ]
DECL|macro|V_MAX_RATE
mdefine_line|#define V_MAX_RATE              block[ 6 ]
DECL|macro|H_MIN_RATE
mdefine_line|#define H_MIN_RATE              block[ 7 ]
DECL|macro|H_MAX_RATE
mdefine_line|#define H_MAX_RATE              block[ 8 ]
DECL|macro|MAX_PIXEL_CLOCK
mdefine_line|#define MAX_PIXEL_CLOCK         (((int)block[ 9 ]) * 10)
DECL|macro|GTF_SUPPORT
mdefine_line|#define GTF_SUPPORT&t;&t;block[10]
DECL|macro|DPMS_ACTIVE_OFF
mdefine_line|#define DPMS_ACTIVE_OFF&t;&t;(1 &lt;&lt; 5)
DECL|macro|DPMS_SUSPEND
mdefine_line|#define DPMS_SUSPEND&t;&t;(1 &lt;&lt; 6)
DECL|macro|DPMS_STANDBY
mdefine_line|#define DPMS_STANDBY&t;&t;(1 &lt;&lt; 7)
macro_line|#endif /* __EDID_H__ */
eof
