multiline_comment|/* (C) 2001 Nemosoft Unv.    webcam@smcc.demon.nl&n;   &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef PWC_IOCTL_H
DECL|macro|PWC_IOCTL_H
mdefine_line|#define PWC_IOCTL_H
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
multiline_comment|/* Set AGC (Automatic Gain Control); int &lt; 0 = auto, 0..65535 = fixed */
DECL|macro|VIDIOCPWCSAGC
mdefine_line|#define VIDIOCPWCSAGC&t;&t;_IOW(&squot;v&squot;, 200, int)
multiline_comment|/* Get AGC; int &lt; 0 = auto; &gt;= 0 = fixed, range 0..65535 */
DECL|macro|VIDIOCPWCGAGC
mdefine_line|#define VIDIOCPWCGAGC&t;&t;_IOR(&squot;v&squot;, 200, int)
multiline_comment|/* Set shutter speed; int &lt; 0 = auto; &gt;= 0 = fixed, range 0..65535 */
DECL|macro|VIDIOCPWCSSHUTTER
mdefine_line|#define VIDIOCPWCSSHUTTER&t;_IOW(&squot;v&squot;, 201, int)
macro_line|#endif
eof
