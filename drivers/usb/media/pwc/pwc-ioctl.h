macro_line|#ifndef PWC_IOCTL_H
DECL|macro|PWC_IOCTL_H
mdefine_line|#define PWC_IOCTL_H
multiline_comment|/* (C) 2001-2004 Nemosoft Unv.&n;   (C) 2004      Luc Saillard (luc@saillard.org)&n;&n;   NOTE: this version of pwc is an unofficial (modified) release of pwc &amp; pcwx&n;   driver and thus may have bugs that are not present in the original version.&n;   Please send bug reports and support requests to &lt;luc@saillard.org&gt;.&n;   The decompression routines have been implemented by reverse-engineering the&n;   Nemosoft binary pwcx module. Caveat emptor.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
multiline_comment|/* This is pwc-ioctl.h belonging to PWC 8.12.1&n;   It contains structures and defines to communicate from user space&n;   directly to the driver.&n; */
multiline_comment|/*&n;   Changes&n;   2001/08/03  Alvarado   Added ioctl constants to access methods for&n;                          changing white balance and red/blue gains&n;   2002/12/15  G. H. Fernandez-Toribio   VIDIOCGREALSIZE&n;   2003/12/13  Nemosft Unv. Some modifications to make interfacing to&n;               PWCX easier&n; */
multiline_comment|/* These are private ioctl() commands, specific for the Philips webcams.&n;   They contain functions not found in other webcams, and settings not&n;   specified in the Video4Linux API.&n;&n;   The #define names are built up like follows:&n;   VIDIOC&t;&t;VIDeo IOCtl prefix&n;         PWC&t;&t;Philps WebCam&n;            G           optional: Get&n;            S           optional: Set&n;             ... &t;the function&n; */
multiline_comment|/* Enumeration of image sizes */
DECL|macro|PSZ_SQCIF
mdefine_line|#define PSZ_SQCIF&t;0x00
DECL|macro|PSZ_QSIF
mdefine_line|#define PSZ_QSIF&t;0x01
DECL|macro|PSZ_QCIF
mdefine_line|#define PSZ_QCIF&t;0x02
DECL|macro|PSZ_SIF
mdefine_line|#define PSZ_SIF&t;&t;0x03
DECL|macro|PSZ_CIF
mdefine_line|#define PSZ_CIF&t;&t;0x04
DECL|macro|PSZ_VGA
mdefine_line|#define PSZ_VGA&t;&t;0x05
DECL|macro|PSZ_MAX
mdefine_line|#define PSZ_MAX&t;&t;6
multiline_comment|/* The frame rate is encoded in the video_window.flags parameter using&n;   the upper 16 bits, since some flags are defined nowadays. The following&n;   defines provide a mask and shift to filter out this value.&n;&n;   In &squot;Snapshot&squot; mode the camera freezes its automatic exposure and colour&n;   balance controls.&n; */
DECL|macro|PWC_FPS_SHIFT
mdefine_line|#define PWC_FPS_SHIFT&t;&t;16
DECL|macro|PWC_FPS_MASK
mdefine_line|#define PWC_FPS_MASK&t;&t;0x00FF0000
DECL|macro|PWC_FPS_FRMASK
mdefine_line|#define PWC_FPS_FRMASK&t;&t;0x003F0000
DECL|macro|PWC_FPS_SNAPSHOT
mdefine_line|#define PWC_FPS_SNAPSHOT&t;0x00400000
multiline_comment|/* structure for transfering x &amp; y coordinates */
DECL|struct|pwc_coord
r_struct
id|pwc_coord
(brace
DECL|member|x
DECL|member|y
r_int
id|x
comma
id|y
suffix:semicolon
multiline_comment|/* guess what */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size, or offset */
)brace
suffix:semicolon
multiline_comment|/* Used with VIDIOCPWCPROBE */
DECL|struct|pwc_probe
r_struct
id|pwc_probe
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pwc_serial
r_struct
id|pwc_serial
(brace
DECL|member|serial
r_char
id|serial
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* String with serial number. Contains terminating 0 */
)brace
suffix:semicolon
multiline_comment|/* pwc_whitebalance.mode values */
DECL|macro|PWC_WB_INDOOR
mdefine_line|#define PWC_WB_INDOOR&t;&t;0
DECL|macro|PWC_WB_OUTDOOR
mdefine_line|#define PWC_WB_OUTDOOR&t;&t;1
DECL|macro|PWC_WB_FL
mdefine_line|#define PWC_WB_FL&t;&t;2
DECL|macro|PWC_WB_MANUAL
mdefine_line|#define PWC_WB_MANUAL&t;&t;3
DECL|macro|PWC_WB_AUTO
mdefine_line|#define PWC_WB_AUTO&t;&t;4
multiline_comment|/* Used with VIDIOCPWC[SG]AWB (Auto White Balance). &n;   Set mode to one of the PWC_WB_* values above.&n;   *red and *blue are the respective gains of these colour components inside &n;   the camera; range 0..65535&n;   When &squot;mode&squot; == PWC_WB_MANUAL, &squot;manual_red&squot; and &squot;manual_blue&squot; are set or read; &n;   otherwise undefined.&n;   &squot;read_red&squot; and &squot;read_blue&squot; are read-only.&n;*/
DECL|struct|pwc_whitebalance
r_struct
id|pwc_whitebalance
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|manual_red
DECL|member|manual_blue
r_int
id|manual_red
comma
id|manual_blue
suffix:semicolon
multiline_comment|/* R/W */
DECL|member|read_red
DECL|member|read_blue
r_int
id|read_red
comma
id|read_blue
suffix:semicolon
multiline_comment|/* R/O */
)brace
suffix:semicolon
multiline_comment|/* &n;   &squot;control_speed&squot; and &squot;control_delay&squot; are used in automatic whitebalance mode,&n;   and tell the camera how fast it should react to changes in lighting, and &n;   with how much delay. Valid values are 0..65535.&n;*/
DECL|struct|pwc_wb_speed
r_struct
id|pwc_wb_speed
(brace
DECL|member|control_speed
r_int
id|control_speed
suffix:semicolon
DECL|member|control_delay
r_int
id|control_delay
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Used with VIDIOCPWC[SG]LED */
DECL|struct|pwc_leds
r_struct
id|pwc_leds
(brace
DECL|member|led_on
r_int
id|led_on
suffix:semicolon
multiline_comment|/* Led on-time; range = 0..25000 */
DECL|member|led_off
r_int
id|led_off
suffix:semicolon
multiline_comment|/* Led off-time; range = 0..25000  */
)brace
suffix:semicolon
multiline_comment|/* Image size (used with GREALSIZE) */
DECL|struct|pwc_imagesize
r_struct
id|pwc_imagesize
(brace
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Defines and structures for Motorized Pan &amp; Tilt */
DECL|macro|PWC_MPT_PAN
mdefine_line|#define PWC_MPT_PAN&t;&t;0x01
DECL|macro|PWC_MPT_TILT
mdefine_line|#define PWC_MPT_TILT&t;&t;0x02
DECL|macro|PWC_MPT_TIMEOUT
mdefine_line|#define PWC_MPT_TIMEOUT&t;&t;0x04 /* for status */
multiline_comment|/* Set angles; when absolute != 0, the angle is absolute and the &n;   driver calculates the relative offset for you. This can only&n;   be used with VIDIOCPWCSANGLE; VIDIOCPWCGANGLE always returns&n;   absolute angles.&n; */
DECL|struct|pwc_mpt_angles
r_struct
id|pwc_mpt_angles
(brace
DECL|member|absolute
r_int
id|absolute
suffix:semicolon
multiline_comment|/* write-only */
DECL|member|pan
r_int
id|pan
suffix:semicolon
multiline_comment|/* degrees * 100 */
DECL|member|tilt
r_int
id|tilt
suffix:semicolon
multiline_comment|/* degress * 100 */
)brace
suffix:semicolon
multiline_comment|/* Range of angles of the camera, both horizontally and vertically.&n; */
DECL|struct|pwc_mpt_range
r_struct
id|pwc_mpt_range
(brace
DECL|member|pan_min
DECL|member|pan_max
r_int
id|pan_min
comma
id|pan_max
suffix:semicolon
multiline_comment|/* degrees * 100 */
DECL|member|tilt_min
DECL|member|tilt_max
r_int
id|tilt_min
comma
id|tilt_max
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pwc_mpt_status
r_struct
id|pwc_mpt_status
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|time_pan
r_int
id|time_pan
suffix:semicolon
DECL|member|time_tilt
r_int
id|time_tilt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is used for out-of-kernel decompression. With it, you can get&n;   all the necessary information to initialize and use the decompressor&n;   routines in standalone applications.&n; */
DECL|struct|pwc_video_command
r_struct
id|pwc_video_command
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* camera type (645, 675, 730, etc.) */
DECL|member|release
r_int
id|release
suffix:semicolon
multiline_comment|/* release number */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* one of PSZ_* */
DECL|member|alternate
r_int
id|alternate
suffix:semicolon
DECL|member|command_len
r_int
id|command_len
suffix:semicolon
multiline_comment|/* length of USB video command */
DECL|member|command_buf
r_int
r_char
id|command_buf
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* Actual USB video command */
DECL|member|bandlength
r_int
id|bandlength
suffix:semicolon
multiline_comment|/* &gt;0 = compressed */
DECL|member|frame_size
r_int
id|frame_size
suffix:semicolon
multiline_comment|/* Size of one (un)compressed frame */
)brace
suffix:semicolon
multiline_comment|/* Flags for PWCX subroutines. Not all modules honour all flags. */
DECL|macro|PWCX_FLAG_PLANAR
mdefine_line|#define PWCX_FLAG_PLANAR&t;0x0001
DECL|macro|PWCX_FLAG_BAYER
mdefine_line|#define PWCX_FLAG_BAYER&t;&t;0x0008
multiline_comment|/* IOCTL definitions */
multiline_comment|/* Restore user settings */
DECL|macro|VIDIOCPWCRUSER
mdefine_line|#define VIDIOCPWCRUSER&t;&t;_IO(&squot;v&squot;, 192)
multiline_comment|/* Save user settings */
DECL|macro|VIDIOCPWCSUSER
mdefine_line|#define VIDIOCPWCSUSER&t;&t;_IO(&squot;v&squot;, 193)
multiline_comment|/* Restore factory settings */
DECL|macro|VIDIOCPWCFACTORY
mdefine_line|#define VIDIOCPWCFACTORY&t;_IO(&squot;v&squot;, 194)
multiline_comment|/* You can manipulate the compression factor. A compression preference of 0&n;    means use uncompressed modes when available; 1 is low compression, 2 is&n;    medium and 3 is high compression preferred. Of course, the higher the&n;    compression, the lower the bandwidth used but more chance of artefacts&n;    in the image. The driver automatically chooses a higher compression when&n;    the preferred mode is not available.&n;  */
multiline_comment|/* Set preferred compression quality (0 = uncompressed, 3 = highest compression) */
DECL|macro|VIDIOCPWCSCQUAL
mdefine_line|#define VIDIOCPWCSCQUAL&t;&t;_IOW(&squot;v&squot;, 195, int)
multiline_comment|/* Get preferred compression quality */
DECL|macro|VIDIOCPWCGCQUAL
mdefine_line|#define VIDIOCPWCGCQUAL&t;&t;_IOR(&squot;v&squot;, 195, int)
multiline_comment|/* Retrieve serial number of camera */
DECL|macro|VIDIOCPWCGSERIAL
mdefine_line|#define VIDIOCPWCGSERIAL&t;_IOR(&squot;v&squot;, 198, struct pwc_serial)
multiline_comment|/* This is a probe function; since so many devices are supported, it&n;    becomes difficult to include all the names in programs that want to&n;    check for the enhanced Philips stuff. So in stead, try this PROBE;&n;    it returns a structure with the original name, and the corresponding&n;    Philips type.&n;    To use, fill the structure with zeroes, call PROBE and if that succeeds,&n;    compare the name with that returned from VIDIOCGCAP; they should be the&n;    same. If so, you can be assured it is a Philips (OEM) cam and the type&n;    is valid.&n; */
DECL|macro|VIDIOCPWCPROBE
mdefine_line|#define VIDIOCPWCPROBE&t;&t;_IOR(&squot;v&squot;, 199, struct pwc_probe)
multiline_comment|/* Set AGC (Automatic Gain Control); int &lt; 0 = auto, 0..65535 = fixed */
DECL|macro|VIDIOCPWCSAGC
mdefine_line|#define VIDIOCPWCSAGC&t;&t;_IOW(&squot;v&squot;, 200, int)
multiline_comment|/* Get AGC; int &lt; 0 = auto; &gt;= 0 = fixed, range 0..65535 */
DECL|macro|VIDIOCPWCGAGC
mdefine_line|#define VIDIOCPWCGAGC&t;&t;_IOR(&squot;v&squot;, 200, int)
multiline_comment|/* Set shutter speed; int &lt; 0 = auto; &gt;= 0 = fixed, range 0..65535 */
DECL|macro|VIDIOCPWCSSHUTTER
mdefine_line|#define VIDIOCPWCSSHUTTER&t;_IOW(&squot;v&squot;, 201, int)
multiline_comment|/* Color compensation (Auto White Balance) */
DECL|macro|VIDIOCPWCSAWB
mdefine_line|#define VIDIOCPWCSAWB           _IOW(&squot;v&squot;, 202, struct pwc_whitebalance)
DECL|macro|VIDIOCPWCGAWB
mdefine_line|#define VIDIOCPWCGAWB           _IOR(&squot;v&squot;, 202, struct pwc_whitebalance)
multiline_comment|/* Auto WB speed */
DECL|macro|VIDIOCPWCSAWBSPEED
mdefine_line|#define VIDIOCPWCSAWBSPEED&t;_IOW(&squot;v&squot;, 203, struct pwc_wb_speed)
DECL|macro|VIDIOCPWCGAWBSPEED
mdefine_line|#define VIDIOCPWCGAWBSPEED&t;_IOR(&squot;v&squot;, 203, struct pwc_wb_speed)
multiline_comment|/* LEDs on/off/blink; int range 0..65535 */
DECL|macro|VIDIOCPWCSLED
mdefine_line|#define VIDIOCPWCSLED           _IOW(&squot;v&squot;, 205, struct pwc_leds)
DECL|macro|VIDIOCPWCGLED
mdefine_line|#define VIDIOCPWCGLED           _IOR(&squot;v&squot;, 205, struct pwc_leds)
multiline_comment|/* Contour (sharpness); int &lt; 0 = auto, 0..65536 = fixed */
DECL|macro|VIDIOCPWCSCONTOUR
mdefine_line|#define VIDIOCPWCSCONTOUR&t;_IOW(&squot;v&squot;, 206, int)
DECL|macro|VIDIOCPWCGCONTOUR
mdefine_line|#define VIDIOCPWCGCONTOUR&t;_IOR(&squot;v&squot;, 206, int)
multiline_comment|/* Backlight compensation; 0 = off, otherwise on */
DECL|macro|VIDIOCPWCSBACKLIGHT
mdefine_line|#define VIDIOCPWCSBACKLIGHT&t;_IOW(&squot;v&squot;, 207, int)
DECL|macro|VIDIOCPWCGBACKLIGHT
mdefine_line|#define VIDIOCPWCGBACKLIGHT&t;_IOR(&squot;v&squot;, 207, int)
multiline_comment|/* Flickerless mode; = 0 off, otherwise on */
DECL|macro|VIDIOCPWCSFLICKER
mdefine_line|#define VIDIOCPWCSFLICKER&t;_IOW(&squot;v&squot;, 208, int)
DECL|macro|VIDIOCPWCGFLICKER
mdefine_line|#define VIDIOCPWCGFLICKER&t;_IOR(&squot;v&squot;, 208, int)  
multiline_comment|/* Dynamic noise reduction; 0 off, 3 = high noise reduction */
DECL|macro|VIDIOCPWCSDYNNOISE
mdefine_line|#define VIDIOCPWCSDYNNOISE&t;_IOW(&squot;v&squot;, 209, int)
DECL|macro|VIDIOCPWCGDYNNOISE
mdefine_line|#define VIDIOCPWCGDYNNOISE&t;_IOR(&squot;v&squot;, 209, int)
multiline_comment|/* Real image size as used by the camera; tells you whether or not there&squot;s a gray border around the image */
DECL|macro|VIDIOCPWCGREALSIZE
mdefine_line|#define VIDIOCPWCGREALSIZE&t;_IOR(&squot;v&squot;, 210, struct pwc_imagesize)
multiline_comment|/* Motorized pan &amp; tilt functions */
DECL|macro|VIDIOCPWCMPTRESET
mdefine_line|#define VIDIOCPWCMPTRESET&t;_IOW(&squot;v&squot;, 211, int)
DECL|macro|VIDIOCPWCMPTGRANGE
mdefine_line|#define VIDIOCPWCMPTGRANGE&t;_IOR(&squot;v&squot;, 211, struct pwc_mpt_range)
DECL|macro|VIDIOCPWCMPTSANGLE
mdefine_line|#define VIDIOCPWCMPTSANGLE&t;_IOW(&squot;v&squot;, 212, struct pwc_mpt_angles)
DECL|macro|VIDIOCPWCMPTGANGLE
mdefine_line|#define VIDIOCPWCMPTGANGLE&t;_IOR(&squot;v&squot;, 212, struct pwc_mpt_angles)
DECL|macro|VIDIOCPWCMPTSTATUS
mdefine_line|#define VIDIOCPWCMPTSTATUS&t;_IOR(&squot;v&squot;, 213, struct pwc_mpt_status)
multiline_comment|/* Get the USB set-video command; needed for initializing libpwcx */
DECL|macro|VIDIOCPWCGVIDCMD
mdefine_line|#define VIDIOCPWCGVIDCMD&t;_IOR(&squot;v&squot;, 215, struct pwc_video_command)
DECL|struct|pwc_table_init_buffer
r_struct
id|pwc_table_init_buffer
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDIOCPWCGVIDTABLE
mdefine_line|#define VIDIOCPWCGVIDTABLE&t;_IOR(&squot;v&squot;, 216, struct pwc_table_init_buffer)
macro_line|#endif
eof
