multiline_comment|/*&n;*&n;* tp3780i.h -- declarations for tp3780i.c&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#ifndef _LINUX_TP3780I_H
DECL|macro|_LINUX_TP3780I_H
mdefine_line|#define _LINUX_TP3780I_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;mwavepub.h&quot;
multiline_comment|/* DSP abilities constants for 3780i based Thinkpads */
DECL|macro|TP_ABILITIES_INTS_PER_SEC
mdefine_line|#define TP_ABILITIES_INTS_PER_SEC       39160800
DECL|macro|TP_ABILITIES_DATA_SIZE
mdefine_line|#define TP_ABILITIES_DATA_SIZE          32768
DECL|macro|TP_ABILITIES_INST_SIZE
mdefine_line|#define TP_ABILITIES_INST_SIZE          32768
DECL|macro|TP_ABILITIES_MWAVEOS_NAME
mdefine_line|#define TP_ABILITIES_MWAVEOS_NAME       &quot;mwaveos0700.dsp&quot;
DECL|macro|TP_ABILITIES_BIOSTASK_NAME
mdefine_line|#define TP_ABILITIES_BIOSTASK_NAME      &quot;mwbio701.dsp&quot;
multiline_comment|/* DSP configuration values for 3780i based Thinkpads */
DECL|macro|TP_CFG_NumTransfers
mdefine_line|#define TP_CFG_NumTransfers     3&t;/* 16 transfers */
DECL|macro|TP_CFG_RerequestTimer
mdefine_line|#define TP_CFG_RerequestTimer   1&t;/* 2 usec */
DECL|macro|TP_CFG_MEMCS16
mdefine_line|#define TP_CFG_MEMCS16          0&t;/* Disabled, 16-bit memory assumed */
DECL|macro|TP_CFG_IsaMemCmdWidth
mdefine_line|#define TP_CFG_IsaMemCmdWidth   3&t;/* 295 nsec (16-bit) */
DECL|macro|TP_CFG_GateIOCHRDY
mdefine_line|#define TP_CFG_GateIOCHRDY      0&t;/* No IOCHRDY gating */
DECL|macro|TP_CFG_EnablePwrMgmt
mdefine_line|#define TP_CFG_EnablePwrMgmt    1&t;/* Enable low poser suspend/resume */
DECL|macro|TP_CFG_HBusTimerValue
mdefine_line|#define TP_CFG_HBusTimerValue 255&t;/* HBus timer load value */
DECL|macro|TP_CFG_DisableLBusTimeout
mdefine_line|#define TP_CFG_DisableLBusTimeout 0&t;/* Enable LBus timeout */
DECL|macro|TP_CFG_N_Divisor
mdefine_line|#define TP_CFG_N_Divisor       32&t;/* Clock = 39.1608 Mhz */
DECL|macro|TP_CFG_M_Multiplier
mdefine_line|#define TP_CFG_M_Multiplier    37&t;/* &quot; */
DECL|macro|TP_CFG_PllBypass
mdefine_line|#define TP_CFG_PllBypass        0&t;/* dont bypass */
DECL|macro|TP_CFG_ChipletEnable
mdefine_line|#define TP_CFG_ChipletEnable 0xFFFF&t;/* Enable all chiplets */
r_typedef
r_struct
(brace
DECL|member|bDSPEnabled
r_int
id|bDSPEnabled
suffix:semicolon
DECL|member|bShareDspIrq
r_int
id|bShareDspIrq
suffix:semicolon
DECL|member|bShareUartIrq
r_int
id|bShareUartIrq
suffix:semicolon
DECL|member|rDspSettings
id|DSP_3780I_CONFIG_SETTINGS
id|rDspSettings
suffix:semicolon
DECL|typedef|THINKPAD_BD_DATA
)brace
id|THINKPAD_BD_DATA
suffix:semicolon
r_int
id|tp3780I_InitializeBoardData
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_CalcResources
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_ClaimResources
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_ReleaseResources
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_EnableDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_DisableDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_ResetDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_StartDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_QueryAbilities
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
comma
id|MW_ABILITIES
op_star
id|pAbilities
)paren
suffix:semicolon
r_int
id|tp3780I_Cleanup
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
suffix:semicolon
r_int
id|tp3780I_ReadWriteDspDStore
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
comma
r_int
r_int
id|uOpcode
comma
r_void
op_star
id|pvBuffer
comma
r_int
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
suffix:semicolon
r_int
id|tp3780I_ReadWriteDspIStore
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
comma
r_int
r_int
id|uOpcode
comma
r_void
op_star
id|pvBuffer
comma
r_int
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
suffix:semicolon
macro_line|#endif
eof
