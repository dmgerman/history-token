multiline_comment|/*&n; *  linux/drivers/message/fusion/mptscsih.h&n; *      High performance SCSI / Fibre Channel SCSI Host device driver.&n; *      For use with PCI chip/adapter(s):&n; *          LSIFC9xx/LSI409xx Fibre Channel&n; *      running LSI Logic Fusion MPT (Message Passing Technology) firmware.&n; *&n; *  Credits:&n; *      This driver would not exist if not for Alan Cox&squot;s development&n; *      of the linux i2o driver.&n; *&n; *      A huge debt of gratitude is owed to David S. Miller (DaveM)&n; *      for fixing much of the stupid and broken stuff in the early&n; *      driver while porting to sparc64 platform.  THANK YOU!&n; *&n; *      (see also mptbase.c)&n; *&n; *  Copyright (c) 1999-2004 LSI Logic Corporation&n; *  Originally By: Steven J. Ralston&n; *  (mailto:netscape.net)&n; *  (mailto:mpt_linux_developer@lsil.com)&n; *&n; *  $Id: mptscsih.h,v 1.21 2002/12/03 21:26:35 pdelaney Exp $&n; */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    NO WARRANTY&n;    THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;    solely responsible for determining the appropriateness of using and&n;    distributing the Program and assumes all risks associated with its&n;    exercise of rights under this Agreement, including but not limited to&n;    the risks and costs of program errors, damage to or loss of data,&n;    programs or equipment, and unavailability or interruption of operations.&n;&n;    DISCLAIMER OF LIABILITY&n;    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef SCSIHOST_H_INCLUDED
DECL|macro|SCSIHOST_H_INCLUDED
mdefine_line|#define SCSIHOST_H_INCLUDED
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&t;SCSI Public stuff...&n; */
DECL|macro|MPT_SCSI_CMD_PER_DEV_HIGH
mdefine_line|#define MPT_SCSI_CMD_PER_DEV_HIGH&t;31
DECL|macro|MPT_SCSI_CMD_PER_DEV_LOW
mdefine_line|#define MPT_SCSI_CMD_PER_DEV_LOW&t;7
DECL|macro|MPT_SCSI_CMD_PER_LUN
mdefine_line|#define MPT_SCSI_CMD_PER_LUN&t;&t;7
DECL|macro|MPT_SCSI_MAX_SECTORS
mdefine_line|#define MPT_SCSI_MAX_SECTORS    8192
multiline_comment|/* To disable domain validation, uncomment the&n; * following line. No effect for FC devices.&n; * For SCSI devices, driver will negotiate to&n; * NVRAM settings (if available) or to maximum adapter&n; * capabilities.&n; */
DECL|macro|MPTSCSIH_ENABLE_DOMAIN_VALIDATION
mdefine_line|#define MPTSCSIH_ENABLE_DOMAIN_VALIDATION
multiline_comment|/* SCSI driver setup structure. Settings can be overridden&n; * by command line options.&n; */
DECL|macro|MPTSCSIH_DOMAIN_VALIDATION
mdefine_line|#define MPTSCSIH_DOMAIN_VALIDATION      1
DECL|macro|MPTSCSIH_MAX_WIDTH
mdefine_line|#define MPTSCSIH_MAX_WIDTH              1
DECL|macro|MPTSCSIH_MIN_SYNC
mdefine_line|#define MPTSCSIH_MIN_SYNC               0x08
DECL|macro|MPTSCSIH_SAF_TE
mdefine_line|#define MPTSCSIH_SAF_TE                 0
DECL|struct|mptscsih_driver_setup
r_struct
id|mptscsih_driver_setup
(brace
DECL|member|dv
id|u8
id|dv
suffix:semicolon
DECL|member|max_width
id|u8
id|max_width
suffix:semicolon
DECL|member|min_sync_factor
id|u8
id|min_sync_factor
suffix:semicolon
DECL|member|saf_te
id|u8
id|saf_te
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
