multiline_comment|/*&n;*&n;* tp3780i.c -- board driver for 3780i on ThinkPads&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;smapi.h&quot;
macro_line|#include &quot;mwavedd.h&quot;
macro_line|#include &quot;tp3780i.h&quot;
macro_line|#include &quot;3780i.h&quot;
macro_line|#include &quot;mwavepub.h&quot;
r_extern
id|MWAVE_DEVICE_DATA
id|mwave_s_mdd
suffix:semicolon
DECL|variable|s_ausThinkpadIrqToField
r_static
r_int
r_int
id|s_ausThinkpadIrqToField
(braket
l_int|16
)braket
op_assign
(brace
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0x0001
comma
l_int|0x0002
comma
l_int|0x0003
comma
l_int|0xFFFF
comma
l_int|0x0004
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0x0005
comma
l_int|0x0006
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0x0007
)brace
suffix:semicolon
DECL|variable|s_ausThinkpadDmaToField
r_static
r_int
r_int
id|s_ausThinkpadDmaToField
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x0001
comma
l_int|0x0002
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0xFFFF
comma
l_int|0x0003
comma
l_int|0x0004
)brace
suffix:semicolon
DECL|variable|s_numIrqs
DECL|variable|s_numDmas
r_static
r_int
r_int
id|s_numIrqs
op_assign
l_int|16
comma
id|s_numDmas
op_assign
l_int|8
suffix:semicolon
DECL|function|EnableSRAM
r_static
r_void
id|EnableSRAM
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
id|DSP_GPIO_OUTPUT_DATA_15_8
id|rGpioOutputData
suffix:semicolon
id|DSP_GPIO_DRIVER_ENABLE_15_8
id|rGpioDriverEnable
suffix:semicolon
id|DSP_GPIO_MODE_15_8
id|rGpioMode
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::EnableSRAM, entry&bslash;n&quot;
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|rGpioMode
)paren
op_assign
id|ReadMsaCfg
c_func
(paren
id|DSP_GpioModeControl_15_8
)paren
suffix:semicolon
id|rGpioMode.GpioMode10
op_assign
l_int|0
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_GpioModeControl_15_8
comma
id|MKWORD
c_func
(paren
id|rGpioMode
)paren
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|rGpioDriverEnable
)paren
op_assign
l_int|0
suffix:semicolon
id|rGpioDriverEnable.Enable10
op_assign
id|TRUE
suffix:semicolon
id|rGpioDriverEnable.Mask10
op_assign
id|TRUE
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_GpioDriverEnable_15_8
comma
id|MKWORD
c_func
(paren
id|rGpioDriverEnable
)paren
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|rGpioOutputData
)paren
op_assign
l_int|0
suffix:semicolon
id|rGpioOutputData.Latch10
op_assign
l_int|0
suffix:semicolon
id|rGpioOutputData.Mask10
op_assign
id|TRUE
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_GpioOutputData_15_8
comma
id|MKWORD
c_func
(paren
id|rGpioOutputData
)paren
)paren
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::EnableSRAM exit&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|UartInterrupt
r_static
id|irqreturn_t
id|UartInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|PRINTK_3
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::UartInterrupt entry irq %x dev_id %p&bslash;n&quot;
comma
id|irq
comma
id|dev_id
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|DspInterrupt
r_static
id|irqreturn_t
id|DspInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|pMWAVE_DEVICE_DATA
id|pDrvData
op_assign
op_amp
id|mwave_s_mdd
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pDrvData-&gt;rBDData.rDspSettings
suffix:semicolon
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
r_int
r_int
id|usIPCSource
op_assign
l_int|0
comma
id|usIsolationMask
comma
id|usPCNum
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt entry irq %x dev_id %p&bslash;n&quot;
comma
id|irq
comma
id|dev_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dsp3780I_GetIPCSource
c_func
(paren
id|usDspBaseIO
comma
op_amp
id|usIPCSource
)paren
op_eq
l_int|0
)paren
(brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt, return from dsp3780i_GetIPCSource, usIPCSource %x&bslash;n&quot;
comma
id|usIPCSource
)paren
suffix:semicolon
id|usIsolationMask
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|usPCNum
op_assign
l_int|1
suffix:semicolon
id|usPCNum
op_le
l_int|16
suffix:semicolon
id|usPCNum
op_increment
)paren
(brace
r_if
c_cond
(paren
id|usIPCSource
op_amp
id|usIsolationMask
)paren
(brace
id|usIPCSource
op_and_assign
op_complement
id|usIsolationMask
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt usPCNum %x usIPCSource %x&bslash;n&quot;
comma
id|usPCNum
comma
id|usIPCSource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|usPCNum
op_minus
l_int|1
)braket
dot
id|usIntCount
op_eq
l_int|0
)paren
(brace
id|pDrvData-&gt;IPCs
(braket
id|usPCNum
op_minus
l_int|1
)braket
dot
id|usIntCount
op_assign
l_int|1
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt usIntCount %x&bslash;n&quot;
comma
id|pDrvData-&gt;IPCs
(braket
id|usPCNum
op_minus
l_int|1
)braket
dot
id|usIntCount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|usPCNum
op_minus
l_int|1
)braket
dot
id|bIsEnabled
op_eq
id|TRUE
)paren
(brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt, waking up usPCNum %x&bslash;n&quot;
comma
id|usPCNum
op_minus
l_int|1
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|pDrvData-&gt;IPCs
(braket
id|usPCNum
op_minus
l_int|1
)braket
dot
id|ipc_wait_queue
)paren
suffix:semicolon
)brace
r_else
(brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt, no one waiting for IPC %x&bslash;n&quot;
comma
id|usPCNum
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|usIPCSource
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* try next IPC */
id|usIsolationMask
op_assign
id|usIsolationMask
op_lshift
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt, return false from dsp3780i_GetIPCSource&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::DspInterrupt exit&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|tp3780I_InitializeBoardData
r_int
id|tp3780I_InitializeBoardData
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_InitializeBoardData entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
id|pBDData-&gt;bDSPEnabled
op_assign
id|FALSE
suffix:semicolon
id|pSettings-&gt;bInterruptClaimed
op_assign
id|FALSE
suffix:semicolon
id|retval
op_assign
id|smapi_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_InitializeBoardData: Error: SMAPI is not available on this machine&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mwave_3780i_irq
op_logical_or
id|mwave_3780i_io
op_logical_or
id|mwave_uart_irq
op_logical_or
id|mwave_uart_io
)paren
(brace
id|retval
op_assign
id|smapi_set_DSP_cfg
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_InitializeBoardData exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_Cleanup
r_int
id|tp3780I_Cleanup
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_Cleanup entry and exit pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_CalcResources
r_int
id|tp3780I_CalcResources
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
id|SMAPI_DSP_SETTINGS
id|rSmapiInfo
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_CalcResources entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smapi_query_DSP_cfg
c_func
(paren
op_amp
id|rSmapiInfo
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_CalcResources: Error: Could not query DSP config. Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
(paren
id|rSmapiInfo.usDspIRQ
op_eq
l_int|0
)paren
op_logical_or
(paren
id|rSmapiInfo.usDspBaseIO
op_eq
l_int|0
)paren
op_logical_or
(paren
id|rSmapiInfo.usUartIRQ
op_eq
l_int|0
)paren
op_logical_or
(paren
id|rSmapiInfo.usUartBaseIO
op_eq
l_int|0
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_CalcResources: Error: Illegal resource setting. Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|pSettings-&gt;bDSPEnabled
op_assign
(paren
id|rSmapiInfo.bDSPEnabled
op_logical_and
id|rSmapiInfo.bDSPPresent
)paren
suffix:semicolon
id|pSettings-&gt;bModemEnabled
op_assign
id|rSmapiInfo.bModemEnabled
suffix:semicolon
id|pSettings-&gt;usDspIrq
op_assign
id|rSmapiInfo.usDspIRQ
suffix:semicolon
id|pSettings-&gt;usDspDma
op_assign
id|rSmapiInfo.usDspDMA
suffix:semicolon
id|pSettings-&gt;usDspBaseIO
op_assign
id|rSmapiInfo.usDspBaseIO
suffix:semicolon
id|pSettings-&gt;usUartIrq
op_assign
id|rSmapiInfo.usUartIRQ
suffix:semicolon
id|pSettings-&gt;usUartBaseIO
op_assign
id|rSmapiInfo.usUartBaseIO
suffix:semicolon
id|pSettings-&gt;uDStoreSize
op_assign
id|TP_ABILITIES_DATA_SIZE
suffix:semicolon
id|pSettings-&gt;uIStoreSize
op_assign
id|TP_ABILITIES_INST_SIZE
suffix:semicolon
id|pSettings-&gt;uIps
op_assign
id|TP_ABILITIES_INTS_PER_SEC
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;bDSPEnabled
op_logical_and
id|pSettings-&gt;bModemEnabled
op_logical_and
id|pSettings-&gt;usDspIrq
op_eq
id|pSettings-&gt;usUartIrq
)paren
(brace
id|pBDData-&gt;bShareDspIrq
op_assign
id|pBDData-&gt;bShareUartIrq
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|pBDData-&gt;bShareDspIrq
op_assign
id|pBDData-&gt;bShareUartIrq
op_assign
l_int|0
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_CalcResources exit&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tp3780I_ClaimResources
r_int
id|tp3780I_ClaimResources
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_struct
id|resource
op_star
id|pres
suffix:semicolon
macro_line|#endif
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ClaimResources entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
id|pres
op_assign
id|request_region
c_func
(paren
id|pSettings-&gt;usDspBaseIO
comma
l_int|16
comma
l_string|&quot;mwave_3780i&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pres
op_eq
l_int|NULL
)paren
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
macro_line|#else
id|retval
op_assign
id|check_region
c_func
(paren
id|pSettings-&gt;usDspBaseIO
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
id|request_region
c_func
(paren
id|pSettings-&gt;usDspBaseIO
comma
l_int|16
comma
l_string|&quot;mwave_3780i&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|retval
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_ClaimResources: Error: Could not claim I/O region starting at %x&bslash;n&quot;
comma
id|pSettings-&gt;usDspBaseIO
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ClaimResources exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_ReleaseResources
r_int
id|tp3780I_ReleaseResources
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ReleaseResources entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|pSettings-&gt;usDspBaseIO
op_amp
(paren
op_complement
l_int|3
)paren
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;bInterruptClaimed
)paren
(brace
id|free_irq
c_func
(paren
id|pSettings-&gt;usDspIrq
comma
l_int|NULL
)paren
suffix:semicolon
id|pSettings-&gt;bInterruptClaimed
op_assign
id|FALSE
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ReleaseResources exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_EnableDSP
r_int
id|tp3780I_EnableDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|BOOLEAN
id|bDSPPoweredUp
op_assign
id|FALSE
comma
id|bDSPEnabled
op_assign
id|FALSE
comma
id|bInterruptAllocated
op_assign
id|FALSE
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_EnableDSP entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pBDData-&gt;bDSPEnabled
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: DSP already enabled!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pSettings-&gt;bDSPEnabled
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780::tp3780I_EnableDSP: Error: pSettings-&gt;bDSPEnabled not set&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pSettings-&gt;usDspIrq
op_ge
id|s_numIrqs
)paren
op_logical_or
(paren
id|pSettings-&gt;usDspDma
op_ge
id|s_numDmas
)paren
op_logical_or
(paren
id|s_ausThinkpadIrqToField
(braket
id|pSettings-&gt;usDspIrq
)braket
op_eq
l_int|0xFFFF
)paren
op_logical_or
(paren
id|s_ausThinkpadDmaToField
(braket
id|pSettings-&gt;usDspDma
)braket
op_eq
l_int|0xFFFF
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: invalid irq %x&bslash;n&quot;
comma
id|pSettings-&gt;usDspIrq
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|pSettings-&gt;usDspBaseIO
op_amp
l_int|0xF00F
)paren
op_ne
l_int|0
)paren
op_logical_or
(paren
id|pSettings-&gt;usDspBaseIO
op_amp
l_int|0x0FF0
)paren
op_eq
l_int|0
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: Invalid DSP base I/O address %x&bslash;n&quot;
comma
id|pSettings-&gt;usDspBaseIO
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pSettings-&gt;bModemEnabled
)paren
(brace
r_if
c_cond
(paren
id|pSettings-&gt;usUartIrq
op_ge
id|s_numIrqs
op_logical_or
id|s_ausThinkpadIrqToField
(braket
id|pSettings-&gt;usUartIrq
)braket
op_eq
l_int|0xFFFF
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: Invalid UART IRQ %x&bslash;n&quot;
comma
id|pSettings-&gt;usUartIrq
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|pSettings-&gt;usUartBaseIO
)paren
(brace
r_case
l_int|0x03F8
suffix:colon
r_case
l_int|0x02F8
suffix:colon
r_case
l_int|0x03E8
suffix:colon
r_case
l_int|0x02E8
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: Invalid UART base I/O address %x&bslash;n&quot;
comma
id|pSettings-&gt;usUartBaseIO
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
)brace
id|pSettings-&gt;bDspIrqActiveLow
op_assign
id|pSettings-&gt;bDspIrqPulse
op_assign
id|TRUE
suffix:semicolon
id|pSettings-&gt;bUartIrqActiveLow
op_assign
id|pSettings-&gt;bUartIrqPulse
op_assign
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
id|pBDData-&gt;bShareDspIrq
)paren
(brace
id|pSettings-&gt;bDspIrqActiveLow
op_assign
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pBDData-&gt;bShareUartIrq
)paren
(brace
id|pSettings-&gt;bUartIrqActiveLow
op_assign
id|FALSE
suffix:semicolon
)brace
id|pSettings-&gt;usNumTransfers
op_assign
id|TP_CFG_NumTransfers
suffix:semicolon
id|pSettings-&gt;usReRequest
op_assign
id|TP_CFG_RerequestTimer
suffix:semicolon
id|pSettings-&gt;bEnableMEMCS16
op_assign
id|TP_CFG_MEMCS16
suffix:semicolon
id|pSettings-&gt;usIsaMemCmdWidth
op_assign
id|TP_CFG_IsaMemCmdWidth
suffix:semicolon
id|pSettings-&gt;bGateIOCHRDY
op_assign
id|TP_CFG_GateIOCHRDY
suffix:semicolon
id|pSettings-&gt;bEnablePwrMgmt
op_assign
id|TP_CFG_EnablePwrMgmt
suffix:semicolon
id|pSettings-&gt;usHBusTimerLoadValue
op_assign
id|TP_CFG_HBusTimerValue
suffix:semicolon
id|pSettings-&gt;bDisableLBusTimeout
op_assign
id|TP_CFG_DisableLBusTimeout
suffix:semicolon
id|pSettings-&gt;usN_Divisor
op_assign
id|TP_CFG_N_Divisor
suffix:semicolon
id|pSettings-&gt;usM_Multiplier
op_assign
id|TP_CFG_M_Multiplier
suffix:semicolon
id|pSettings-&gt;bPllBypass
op_assign
id|TP_CFG_PllBypass
suffix:semicolon
id|pSettings-&gt;usChipletEnable
op_assign
id|TP_CFG_ChipletEnable
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pSettings-&gt;usUartIrq
comma
op_amp
id|UartInterrupt
comma
l_int|0
comma
l_string|&quot;mwave_uart&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: Could not get UART IRQ %x&bslash;n&quot;
comma
id|pSettings-&gt;usUartIrq
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* no conflict just release */
id|free_irq
c_func
(paren
id|pSettings-&gt;usUartIrq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pSettings-&gt;usDspIrq
comma
op_amp
id|DspInterrupt
comma
l_int|0
comma
l_string|&quot;mwave_3780i&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: Could not get 3780i IRQ %x&bslash;n&quot;
comma
id|pSettings-&gt;usDspIrq
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_else
(brace
id|PRINTK_3
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_EnableDSP, got interrupt %x bShareDspIrq %x&bslash;n&quot;
comma
id|pSettings-&gt;usDspIrq
comma
id|pBDData-&gt;bShareDspIrq
)paren
suffix:semicolon
id|bInterruptAllocated
op_assign
id|TRUE
suffix:semicolon
id|pSettings-&gt;bInterruptClaimed
op_assign
id|TRUE
suffix:semicolon
)brace
id|smapi_set_DSP_power_state
c_func
(paren
id|FALSE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smapi_set_DSP_power_state
c_func
(paren
id|TRUE
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: smapi_set_DSP_power_state(TRUE) failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_else
(brace
id|bDSPPoweredUp
op_assign
id|TRUE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dsp3780I_EnableDSP
c_func
(paren
id|pSettings
comma
id|s_ausThinkpadIrqToField
comma
id|s_ausThinkpadDmaToField
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;tp3780i::tp3780I_EnableDSP: Error: dsp7880I_EnableDSP() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|exit_cleanup
suffix:semicolon
)brace
r_else
(brace
id|bDSPEnabled
op_assign
id|TRUE
suffix:semicolon
)brace
id|EnableSRAM
c_func
(paren
id|pBDData
)paren
suffix:semicolon
id|pBDData-&gt;bDSPEnabled
op_assign
id|TRUE
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_EnableDSP exit&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|exit_cleanup
suffix:colon
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;tp3780i::tp3780I_EnableDSP: Cleaning up&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bDSPEnabled
)paren
id|dsp3780I_DisableDSP
c_func
(paren
id|pSettings
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bDSPPoweredUp
)paren
id|smapi_set_DSP_power_state
c_func
(paren
id|FALSE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bInterruptAllocated
)paren
(brace
id|free_irq
c_func
(paren
id|pSettings-&gt;usDspIrq
comma
l_int|NULL
)paren
suffix:semicolon
id|pSettings-&gt;bInterruptClaimed
op_assign
id|FALSE
suffix:semicolon
)brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|tp3780I_DisableDSP
r_int
id|tp3780I_DisableDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_DisableDSP entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pBDData-&gt;bDSPEnabled
)paren
(brace
id|dsp3780I_DisableDSP
c_func
(paren
op_amp
id|pBDData-&gt;rDspSettings
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;bInterruptClaimed
)paren
(brace
id|free_irq
c_func
(paren
id|pSettings-&gt;usDspIrq
comma
l_int|NULL
)paren
suffix:semicolon
id|pSettings-&gt;bInterruptClaimed
op_assign
id|FALSE
suffix:semicolon
)brace
id|smapi_set_DSP_power_state
c_func
(paren
id|FALSE
)paren
suffix:semicolon
id|pBDData-&gt;bDSPEnabled
op_assign
id|FALSE
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_DisableDSP exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_ResetDSP
r_int
id|tp3780I_ResetDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ResetDSP entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dsp3780I_Reset
c_func
(paren
id|pSettings
)paren
op_eq
l_int|0
)paren
(brace
id|EnableSRAM
c_func
(paren
id|pBDData
)paren
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ResetDSP exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_StartDSP
r_int
id|tp3780I_StartDSP
c_func
(paren
id|THINKPAD_BD_DATA
op_star
id|pBDData
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_StartDSP entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dsp3780I_Run
c_func
(paren
id|pSettings
)paren
op_eq
l_int|0
)paren
(brace
singleline_comment|// @BUG @TBD EnableSRAM(pBDData);
)brace
r_else
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_StartDSP exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_QueryAbilities
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
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_QueryAbilities entry pBDData %p&bslash;n&quot;
comma
id|pBDData
)paren
suffix:semicolon
multiline_comment|/* fill out standard constant fields */
id|pAbilities-&gt;instr_per_sec
op_assign
id|pBDData-&gt;rDspSettings.uIps
suffix:semicolon
id|pAbilities-&gt;data_size
op_assign
id|pBDData-&gt;rDspSettings.uDStoreSize
suffix:semicolon
id|pAbilities-&gt;inst_size
op_assign
id|pBDData-&gt;rDspSettings.uIStoreSize
suffix:semicolon
id|pAbilities-&gt;bus_dma_bw
op_assign
id|pBDData-&gt;rDspSettings.uDmaBandwidth
suffix:semicolon
multiline_comment|/* fill out dynamically determined fields */
id|pAbilities-&gt;component_list
(braket
l_int|0
)braket
op_assign
l_int|0x00010000
op_or
id|MW_ADC_MASK
suffix:semicolon
id|pAbilities-&gt;component_list
(braket
l_int|1
)braket
op_assign
l_int|0x00010000
op_or
id|MW_ACI_MASK
suffix:semicolon
id|pAbilities-&gt;component_list
(braket
l_int|2
)braket
op_assign
l_int|0x00010000
op_or
id|MW_AIC1_MASK
suffix:semicolon
id|pAbilities-&gt;component_list
(braket
l_int|3
)braket
op_assign
l_int|0x00010000
op_or
id|MW_AIC2_MASK
suffix:semicolon
id|pAbilities-&gt;component_list
(braket
l_int|4
)braket
op_assign
l_int|0x00010000
op_or
id|MW_CDDAC_MASK
suffix:semicolon
id|pAbilities-&gt;component_list
(braket
l_int|5
)braket
op_assign
l_int|0x00010000
op_or
id|MW_MIDI_MASK
suffix:semicolon
id|pAbilities-&gt;component_list
(braket
l_int|6
)braket
op_assign
l_int|0x00010000
op_or
id|MW_UART_MASK
suffix:semicolon
id|pAbilities-&gt;component_count
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* Fill out Mwave OS and BIOS task names */
id|memcpy
c_func
(paren
id|pAbilities-&gt;mwave_os_name
comma
id|TP_ABILITIES_MWAVEOS_NAME
comma
r_sizeof
(paren
id|TP_ABILITIES_MWAVEOS_NAME
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pAbilities-&gt;bios_task_name
comma
id|TP_ABILITIES_BIOSTASK_NAME
comma
r_sizeof
(paren
id|TP_ABILITIES_BIOSTASK_NAME
)paren
)paren
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_QueryAbilities exit retval=SUCCESSFUL&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_ReadWriteDspDStore
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
id|__user
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
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
id|BOOLEAN
id|bRC
op_assign
l_int|0
suffix:semicolon
id|PRINTK_6
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ReadWriteDspDStore entry pBDData %p, uOpcode %x, pvBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|pBDData
comma
id|uOpcode
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pBDData-&gt;bDSPEnabled
)paren
(brace
r_switch
c_cond
(paren
id|uOpcode
)paren
(brace
r_case
id|IOCTL_MW_READ_DATA
suffix:colon
id|bRC
op_assign
id|dsp3780I_ReadDStore
c_func
(paren
id|usDspBaseIO
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOCTL_MW_READCLEAR_DATA
suffix:colon
id|bRC
op_assign
id|dsp3780I_ReadAndClearDStore
c_func
(paren
id|usDspBaseIO
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOCTL_MW_WRITE_DATA
suffix:colon
id|bRC
op_assign
id|dsp3780I_WriteDStore
c_func
(paren
id|usDspBaseIO
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|retval
op_assign
(paren
id|bRC
)paren
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ReadWriteDspDStore exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tp3780I_ReadWriteDspIStore
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
id|__user
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
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|pBDData-&gt;rDspSettings
suffix:semicolon
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
id|BOOLEAN
id|bRC
op_assign
l_int|0
suffix:semicolon
id|PRINTK_6
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ReadWriteDspIStore entry pBDData %p, uOpcode %x, pvBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|pBDData
comma
id|uOpcode
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pBDData-&gt;bDSPEnabled
)paren
(brace
r_switch
c_cond
(paren
id|uOpcode
)paren
(brace
r_case
id|IOCTL_MW_READ_INST
suffix:colon
id|bRC
op_assign
id|dsp3780I_ReadIStore
c_func
(paren
id|usDspBaseIO
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOCTL_MW_WRITE_INST
suffix:colon
id|bRC
op_assign
id|dsp3780I_WriteIStore
c_func
(paren
id|usDspBaseIO
comma
id|pvBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|retval
op_assign
(paren
id|bRC
)paren
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_TP3780I
comma
l_string|&quot;tp3780i::tp3780I_ReadWriteDspIStore exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
