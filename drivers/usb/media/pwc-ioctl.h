macro_line|#ifndef PWC_IOCTL_H
DECL|macro|PWC_IOCTL_H
mdefine_line|#define PWC_IOCTL_H
multiline_comment|/* (C) 2001-2002 Nemosoft Unv.    webcam@smcc.demon.nl&n;   &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
multiline_comment|/*         This is pwc-ioctl.h belonging to PWC 8.7                        */
multiline_comment|/* &n;   Changes&n;   2001/08/03  Alvarado   Added ioctl constants to access methods for &n;                          changing white balance and red/blue gains&n; */
multiline_comment|/* These are private ioctl() commands, specific for the Philips webcams.&n;   They contain functions not found in other webcams, and settings not&n;   specified in the Video4Linux API. &n;   &n;   The #define names are built up like follows:&n;   VIDIOC&t;&t;VIDeo IOCtl prefix&n;         PWC&t;&t;Philps WebCam&n;            G           optional: Get&n;            S           optional: Set&n;             ... &t;the function&n; */
multiline_comment|/* The frame rate is encoded in the video_window.flags parameter using&n;   the upper 16 bits, since some flags are defined nowadays. The following&n;   defines provide a mask and shift to filter out this value.&n;   &n;   In &squot;Snapshot&squot; mode the camera freezes its automatic exposure and colour &n;   balance controls.&n; */
DECL|macro|PWC_FPS_SHIFT
mdefine_line|#define PWC_FPS_SHIFT&t;&t;16
DECL|macro|PWC_FPS_MASK
mdefine_line|#define PWC_FPS_MASK&t;&t;0x00FF0000
DECL|macro|PWC_FPS_FRMASK
mdefine_line|#define PWC_FPS_FRMASK&t;&t;0x003F0000
DECL|macro|PWC_FPS_SNAPSHOT
mdefine_line|#define PWC_FPS_SNAPSHOT&t;0x00400000
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
multiline_comment|/* This is a probe function; since so many devices are supported, it&n;    becomes difficult to include all the names in programs that want to&n;    check for the enhanced Philips stuff. So in stead, try this PROBE;&n;    it returns a structure with the original name, and the corresponding &n;    Philips type.&n;    To use, fill the structure with zeroes, call PROBE and if that succeeds,&n;    compare the name with that returned from VIDIOCGCAP; they should be the&n;    same. If so, you can be assured it is a Philips (OEM) cam and the type&n;    is valid.&n; */
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
macro_line|#endif
eof
