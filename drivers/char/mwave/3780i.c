multiline_comment|/*&n;*&n;* 3780i.c -- helper routines for the 3780i DSP&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;smapi.h&quot;
macro_line|#include &quot;mwavedd.h&quot;
macro_line|#include &quot;3780i.h&quot;
DECL|variable|dsp_lock
r_static
id|spinlock_t
id|dsp_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|flags
r_static
r_int
r_int
id|flags
suffix:semicolon
DECL|function|PaceMsaAccess
r_static
r_void
id|PaceMsaAccess
c_func
(paren
r_int
r_int
id|usDspBaseIO
)paren
(brace
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|dsp3780I_ReadMsaCfg
r_int
r_int
id|dsp3780I_ReadMsaCfg
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_int
r_int
id|ulMsaAddr
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_ReadMsaCfg entry usDspBaseIO %x ulMsaAddr %lx&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|ulMsaAddr
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulMsaAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulMsaAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|val
op_assign
id|InWordDsp
c_func
(paren
id|DSP_MsaDataDSISHigh
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_ReadMsaCfg exit val %x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|dsp3780I_WriteMsaCfg
r_void
id|dsp3780I_WriteMsaCfg
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_int
r_int
id|ulMsaAddr
comma
r_int
r_int
id|usValue
)paren
(brace
id|PRINTK_4
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_WriteMsaCfg entry usDspBaseIO %x ulMsaAddr %lx usValue %x&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|ulMsaAddr
comma
id|usValue
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulMsaAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulMsaAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaDataDSISHigh
comma
id|usValue
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|dsp3780I_WriteGenCfg
r_void
id|dsp3780I_WriteGenCfg
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_int
id|uIndex
comma
r_int
r_char
id|ucValue
)paren
(brace
id|DSP_ISA_SLAVE_CONTROL
id|rSlaveControl
suffix:semicolon
id|DSP_ISA_SLAVE_CONTROL
id|rSlaveControl_Save
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_WriteGenCfg entry usDspBaseIO %x uIndex %x ucValue %x&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|uIndex
comma
id|ucValue
)paren
suffix:semicolon
id|MKBYTE
c_func
(paren
id|rSlaveControl
)paren
op_assign
id|InByteDsp
c_func
(paren
id|DSP_IsaSlaveControl
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_WriteGenCfg rSlaveControl %x&bslash;n&quot;
comma
id|MKBYTE
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|rSlaveControl_Save
op_assign
id|rSlaveControl
suffix:semicolon
id|rSlaveControl.ConfigMode
op_assign
id|TRUE
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_WriteGenCfg entry rSlaveControl+ConfigMode %x&bslash;n&quot;
comma
id|MKBYTE
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKBYTE
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_ConfigAddress
comma
(paren
r_int
r_char
)paren
id|uIndex
)paren
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_ConfigData
comma
id|ucValue
)paren
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKBYTE
c_func
(paren
id|rSlaveControl_Save
)paren
)paren
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_WriteGenCfg exit&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|dsp3780I_ReadGenCfg
r_int
r_char
id|dsp3780I_ReadGenCfg
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_int
id|uIndex
)paren
(brace
id|DSP_ISA_SLAVE_CONTROL
id|rSlaveControl
suffix:semicolon
id|DSP_ISA_SLAVE_CONTROL
id|rSlaveControl_Save
suffix:semicolon
r_int
r_char
id|ucValue
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_ReadGenCfg entry usDspBaseIO %x uIndex %x&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|uIndex
)paren
suffix:semicolon
id|MKBYTE
c_func
(paren
id|rSlaveControl
)paren
op_assign
id|InByteDsp
c_func
(paren
id|DSP_IsaSlaveControl
)paren
suffix:semicolon
id|rSlaveControl_Save
op_assign
id|rSlaveControl
suffix:semicolon
id|rSlaveControl.ConfigMode
op_assign
id|TRUE
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKBYTE
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_ConfigAddress
comma
(paren
r_int
r_char
)paren
id|uIndex
)paren
suffix:semicolon
id|ucValue
op_assign
id|InByteDsp
c_func
(paren
id|DSP_ConfigData
)paren
suffix:semicolon
id|OutByteDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKBYTE
c_func
(paren
id|rSlaveControl_Save
)paren
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_ReadGenCfg exit ucValue %x&bslash;n&quot;
comma
id|ucValue
)paren
suffix:semicolon
r_return
id|ucValue
suffix:semicolon
)brace
DECL|function|dsp3780I_EnableDSP
r_int
id|dsp3780I_EnableDSP
c_func
(paren
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
comma
r_int
r_int
op_star
id|pIrqMap
comma
r_int
r_int
op_star
id|pDmaMap
)paren
(brace
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DSP_UART_CFG_1
id|rUartCfg1
suffix:semicolon
id|DSP_UART_CFG_2
id|rUartCfg2
suffix:semicolon
id|DSP_HBRIDGE_CFG_1
id|rHBridgeCfg1
suffix:semicolon
id|DSP_HBRIDGE_CFG_2
id|rHBridgeCfg2
suffix:semicolon
id|DSP_BUSMASTER_CFG_1
id|rBusmasterCfg1
suffix:semicolon
id|DSP_BUSMASTER_CFG_2
id|rBusmasterCfg2
suffix:semicolon
id|DSP_ISA_PROT_CFG
id|rIsaProtCfg
suffix:semicolon
id|DSP_POWER_MGMT_CFG
id|rPowerMgmtCfg
suffix:semicolon
id|DSP_HBUS_TIMER_CFG
id|rHBusTimerCfg
suffix:semicolon
id|DSP_LBUS_TIMEOUT_DISABLE
id|rLBusTimeoutDisable
suffix:semicolon
id|DSP_CHIP_RESET
id|rChipReset
suffix:semicolon
id|DSP_CLOCK_CONTROL_1
id|rClockControl1
suffix:semicolon
id|DSP_CLOCK_CONTROL_2
id|rClockControl2
suffix:semicolon
id|DSP_ISA_SLAVE_CONTROL
id|rSlaveControl
suffix:semicolon
id|DSP_HBRIDGE_CONTROL
id|rHBridgeControl
suffix:semicolon
r_int
r_int
id|ChipID
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tval
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_EnableDSP entry pSettings-&gt;bDSPEnabled %x&bslash;n&quot;
comma
id|pSettings-&gt;bDSPEnabled
)paren
suffix:semicolon
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
id|KERN_ERR
l_string|&quot;3780i::dsp3780I_EnableDSP: Error: DSP not enabled. Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_EnableDSP entry pSettings-&gt;bModemEnabled %x&bslash;n&quot;
comma
id|pSettings-&gt;bModemEnabled
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;bModemEnabled
)paren
(brace
id|rUartCfg1.Reserved
op_assign
id|rUartCfg2.Reserved
op_assign
l_int|0
suffix:semicolon
id|rUartCfg1.IrqActiveLow
op_assign
id|pSettings-&gt;bUartIrqActiveLow
suffix:semicolon
id|rUartCfg1.IrqPulse
op_assign
id|pSettings-&gt;bUartIrqPulse
suffix:semicolon
id|rUartCfg1.Irq
op_assign
(paren
r_int
r_char
)paren
id|pIrqMap
(braket
id|pSettings-&gt;usUartIrq
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|pSettings-&gt;usUartBaseIO
)paren
(brace
r_case
l_int|0x03F8
suffix:colon
id|rUartCfg1.BaseIO
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02F8
suffix:colon
id|rUartCfg1.BaseIO
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x03E8
suffix:colon
id|rUartCfg1.BaseIO
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02E8
suffix:colon
id|rUartCfg1.BaseIO
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rUartCfg2.Enable
op_assign
id|TRUE
suffix:semicolon
)brace
id|rHBridgeCfg1.Reserved
op_assign
id|rHBridgeCfg2.Reserved
op_assign
l_int|0
suffix:semicolon
id|rHBridgeCfg1.IrqActiveLow
op_assign
id|pSettings-&gt;bDspIrqActiveLow
suffix:semicolon
id|rHBridgeCfg1.IrqPulse
op_assign
id|pSettings-&gt;bDspIrqPulse
suffix:semicolon
id|rHBridgeCfg1.Irq
op_assign
(paren
r_int
r_char
)paren
id|pIrqMap
(braket
id|pSettings-&gt;usDspIrq
)braket
suffix:semicolon
id|rHBridgeCfg1.AccessMode
op_assign
l_int|1
suffix:semicolon
id|rHBridgeCfg2.Enable
op_assign
id|TRUE
suffix:semicolon
id|rBusmasterCfg2.Reserved
op_assign
l_int|0
suffix:semicolon
id|rBusmasterCfg1.Dma
op_assign
(paren
r_int
r_char
)paren
id|pDmaMap
(braket
id|pSettings-&gt;usDspDma
)braket
suffix:semicolon
id|rBusmasterCfg1.NumTransfers
op_assign
(paren
r_int
r_char
)paren
id|pSettings-&gt;usNumTransfers
suffix:semicolon
id|rBusmasterCfg1.ReRequest
op_assign
(paren
r_int
r_char
)paren
id|pSettings-&gt;usReRequest
suffix:semicolon
id|rBusmasterCfg1.MEMCS16
op_assign
id|pSettings-&gt;bEnableMEMCS16
suffix:semicolon
id|rBusmasterCfg2.IsaMemCmdWidth
op_assign
(paren
r_int
r_char
)paren
id|pSettings-&gt;usIsaMemCmdWidth
suffix:semicolon
id|rIsaProtCfg.Reserved
op_assign
l_int|0
suffix:semicolon
id|rIsaProtCfg.GateIOCHRDY
op_assign
id|pSettings-&gt;bGateIOCHRDY
suffix:semicolon
id|rPowerMgmtCfg.Reserved
op_assign
l_int|0
suffix:semicolon
id|rPowerMgmtCfg.Enable
op_assign
id|pSettings-&gt;bEnablePwrMgmt
suffix:semicolon
id|rHBusTimerCfg.LoadValue
op_assign
(paren
r_int
r_char
)paren
id|pSettings-&gt;usHBusTimerLoadValue
suffix:semicolon
id|rLBusTimeoutDisable.Reserved
op_assign
l_int|0
suffix:semicolon
id|rLBusTimeoutDisable.DisableTimeout
op_assign
id|pSettings-&gt;bDisableLBusTimeout
suffix:semicolon
id|MKWORD
c_func
(paren
id|rChipReset
)paren
op_assign
op_complement
id|pSettings-&gt;usChipletEnable
suffix:semicolon
id|rClockControl1.Reserved1
op_assign
id|rClockControl1.Reserved2
op_assign
l_int|0
suffix:semicolon
id|rClockControl1.N_Divisor
op_assign
id|pSettings-&gt;usN_Divisor
suffix:semicolon
id|rClockControl1.M_Multiplier
op_assign
id|pSettings-&gt;usM_Multiplier
suffix:semicolon
id|rClockControl2.Reserved
op_assign
l_int|0
suffix:semicolon
id|rClockControl2.PllBypass
op_assign
id|pSettings-&gt;bPllBypass
suffix:semicolon
multiline_comment|/* Issue a soft reset to the chip */
multiline_comment|/* Note: Since we may be coming in with 3780i clocks suspended, we must keep&n;&t;* soft-reset active for 10ms.&n;&t;*/
id|rSlaveControl.ClockControl
op_assign
l_int|0
suffix:semicolon
id|rSlaveControl.SoftReset
op_assign
id|TRUE
suffix:semicolon
id|rSlaveControl.ConfigMode
op_assign
id|FALSE
suffix:semicolon
id|rSlaveControl.Reserved
op_assign
l_int|0
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_EnableDSP usDspBaseIO %x index %x taddr %x&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|DSP_IsaSlaveControl
comma
id|usDspBaseIO
op_plus
id|DSP_IsaSlaveControl
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_EnableDSP rSlaveContrl %x&bslash;n&quot;
comma
id|MKWORD
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKWORD
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|tval
)paren
op_assign
id|InWordDsp
c_func
(paren
id|DSP_IsaSlaveControl
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_EnableDSP rSlaveControl 2 %x&bslash;n&quot;
comma
id|tval
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|11
suffix:semicolon
id|i
op_increment
)paren
id|udelay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|rSlaveControl.SoftReset
op_assign
id|FALSE
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKWORD
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|tval
)paren
op_assign
id|InWordDsp
c_func
(paren
id|DSP_IsaSlaveControl
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_EnableDSP rSlaveControl 3 %x&bslash;n&quot;
comma
id|tval
)paren
suffix:semicolon
multiline_comment|/* Program our general configuration registers */
id|WriteGenCfg
c_func
(paren
id|DSP_HBridgeCfg1Index
comma
id|MKBYTE
c_func
(paren
id|rHBridgeCfg1
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_HBridgeCfg2Index
comma
id|MKBYTE
c_func
(paren
id|rHBridgeCfg2
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_BusMasterCfg1Index
comma
id|MKBYTE
c_func
(paren
id|rBusmasterCfg1
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_BusMasterCfg2Index
comma
id|MKBYTE
c_func
(paren
id|rBusmasterCfg2
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_IsaProtCfgIndex
comma
id|MKBYTE
c_func
(paren
id|rIsaProtCfg
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_PowerMgCfgIndex
comma
id|MKBYTE
c_func
(paren
id|rPowerMgmtCfg
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_HBusTimerCfgIndex
comma
id|MKBYTE
c_func
(paren
id|rHBusTimerCfg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;bModemEnabled
)paren
(brace
id|WriteGenCfg
c_func
(paren
id|DSP_UartCfg1Index
comma
id|MKBYTE
c_func
(paren
id|rUartCfg1
)paren
)paren
suffix:semicolon
id|WriteGenCfg
c_func
(paren
id|DSP_UartCfg2Index
comma
id|MKBYTE
c_func
(paren
id|rUartCfg2
)paren
)paren
suffix:semicolon
)brace
id|rHBridgeControl.EnableDspInt
op_assign
id|FALSE
suffix:semicolon
id|rHBridgeControl.MemAutoInc
op_assign
id|TRUE
suffix:semicolon
id|rHBridgeControl.IoAutoInc
op_assign
id|FALSE
suffix:semicolon
id|rHBridgeControl.DiagnosticMode
op_assign
id|FALSE
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_EnableDSP DSP_HBridgeControl %x rHBridgeControl %x&bslash;n&quot;
comma
id|DSP_HBridgeControl
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_HBridgeControl
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_LBusTimeoutDisable
comma
id|MKWORD
c_func
(paren
id|rLBusTimeoutDisable
)paren
)paren
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_ClockControl_1
comma
id|MKWORD
c_func
(paren
id|rClockControl1
)paren
)paren
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_ClockControl_2
comma
id|MKWORD
c_func
(paren
id|rClockControl2
)paren
)paren
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_ChipReset
comma
id|MKWORD
c_func
(paren
id|rChipReset
)paren
)paren
suffix:semicolon
id|ChipID
op_assign
id|ReadMsaCfg
c_func
(paren
id|DSP_ChipID
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_EnableDSP exiting bRC=TRUE, ChipID %x&bslash;n&quot;
comma
id|ChipID
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_DisableDSP
r_int
id|dsp3780I_DisableDSP
c_func
(paren
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
)paren
(brace
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
id|DSP_ISA_SLAVE_CONTROL
id|rSlaveControl
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_DisableDSP entry&bslash;n&quot;
)paren
suffix:semicolon
id|rSlaveControl.ClockControl
op_assign
l_int|0
suffix:semicolon
id|rSlaveControl.SoftReset
op_assign
id|TRUE
suffix:semicolon
id|rSlaveControl.ConfigMode
op_assign
id|FALSE
suffix:semicolon
id|rSlaveControl.Reserved
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKWORD
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|rSlaveControl.ClockControl
op_assign
l_int|1
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_IsaSlaveControl
comma
id|MKWORD
c_func
(paren
id|rSlaveControl
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_DisableDSP exit&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_Reset
r_int
id|dsp3780I_Reset
c_func
(paren
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
)paren
(brace
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
id|DSP_BOOT_DOMAIN
id|rBootDomain
suffix:semicolon
id|DSP_HBRIDGE_CONTROL
id|rHBridgeControl
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Reset entry&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Mask DSP to PC interrupt */
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
op_assign
id|InWordDsp
c_func
(paren
id|DSP_HBridgeControl
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Reset rHBridgeControl %x&bslash;n&quot;
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|rHBridgeControl.EnableDspInt
op_assign
id|FALSE
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_HBridgeControl
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Reset the core via the boot domain register */
id|rBootDomain.ResetCore
op_assign
id|TRUE
suffix:semicolon
id|rBootDomain.Halt
op_assign
id|TRUE
suffix:semicolon
id|rBootDomain.NMI
op_assign
id|TRUE
suffix:semicolon
id|rBootDomain.Reserved
op_assign
l_int|0
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Reset rBootDomain %x&bslash;n&quot;
comma
id|MKWORD
c_func
(paren
id|rBootDomain
)paren
)paren
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_MspBootDomain
comma
id|MKWORD
c_func
(paren
id|rBootDomain
)paren
)paren
suffix:semicolon
multiline_comment|/* Reset all the chiplets and then reactivate them */
id|WriteMsaCfg
c_func
(paren
id|DSP_ChipReset
comma
l_int|0xFFFF
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_ChipReset
comma
(paren
r_int
r_int
)paren
(paren
op_complement
id|pSettings-&gt;usChipletEnable
)paren
)paren
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Reset exit bRC=0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_Run
r_int
id|dsp3780I_Run
c_func
(paren
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
)paren
(brace
r_int
r_int
id|usDspBaseIO
op_assign
id|pSettings-&gt;usDspBaseIO
suffix:semicolon
id|DSP_BOOT_DOMAIN
id|rBootDomain
suffix:semicolon
id|DSP_HBRIDGE_CONTROL
id|rHBridgeControl
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Run entry&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Transition the core to a running state */
id|rBootDomain.ResetCore
op_assign
id|TRUE
suffix:semicolon
id|rBootDomain.Halt
op_assign
id|FALSE
suffix:semicolon
id|rBootDomain.NMI
op_assign
id|TRUE
suffix:semicolon
id|rBootDomain.Reserved
op_assign
l_int|0
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_MspBootDomain
comma
id|MKWORD
c_func
(paren
id|rBootDomain
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|rBootDomain.ResetCore
op_assign
id|FALSE
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_MspBootDomain
comma
id|MKWORD
c_func
(paren
id|rBootDomain
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|rBootDomain.NMI
op_assign
id|FALSE
suffix:semicolon
id|WriteMsaCfg
c_func
(paren
id|DSP_MspBootDomain
comma
id|MKWORD
c_func
(paren
id|rBootDomain
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Enable DSP to PC interrupt */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
op_assign
id|InWordDsp
c_func
(paren
id|DSP_HBridgeControl
)paren
suffix:semicolon
id|rHBridgeControl.EnableDspInt
op_assign
id|TRUE
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Run rHBridgeControl %x&bslash;n&quot;
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_HBridgeControl
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780i_Run exit bRC=TRUE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_ReadDStore
r_int
id|dsp3780I_ReadDStore
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_void
id|__user
op_star
id|pvBuffer
comma
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
(brace
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
id|pvBuffer
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_ReadDStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|pusBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
multiline_comment|/* Set the initial MSA address. No adjustments need to be made to data store addresses */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulDSPAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulDSPAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Transfer the memory block */
r_while
c_loop
(paren
id|uCount
op_decrement
op_ne
l_int|0
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|InWordDsp
c_func
(paren
id|DSP_MsaDataDSISHigh
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_ReadDStore uCount %x val %x&bslash;n&quot;
comma
id|uCount
comma
id|val
)paren
suffix:semicolon
id|PaceMsaAccess
c_func
(paren
id|usDspBaseIO
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_ReadDStore exit bRC=TRUE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_ReadAndClearDStore
r_int
id|dsp3780I_ReadAndClearDStore
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_void
id|__user
op_star
id|pvBuffer
comma
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
(brace
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
id|pvBuffer
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_ReadAndDStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|pusBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
multiline_comment|/* Set the initial MSA address. No adjustments need to be made to data store addresses */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulDSPAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulDSPAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Transfer the memory block */
r_while
c_loop
(paren
id|uCount
op_decrement
op_ne
l_int|0
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|InWordDsp
c_func
(paren
id|DSP_ReadAndClear
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_ReadAndCleanDStore uCount %x val %x&bslash;n&quot;
comma
id|uCount
comma
id|val
)paren
suffix:semicolon
id|PaceMsaAccess
c_func
(paren
id|usDspBaseIO
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_ReadAndClearDStore exit bRC=TRUE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_WriteDStore
r_int
id|dsp3780I_WriteDStore
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_void
id|__user
op_star
id|pvBuffer
comma
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
(brace
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
id|pvBuffer
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780D_WriteDStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|pusBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
multiline_comment|/* Set the initial MSA address. No adjustments need to be made to data store addresses */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulDSPAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulDSPAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Transfer the memory block */
r_while
c_loop
(paren
id|uCount
op_decrement
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaDataDSISHigh
comma
id|val
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_WriteDStore uCount %x val %x&bslash;n&quot;
comma
id|uCount
comma
id|val
)paren
suffix:semicolon
id|PaceMsaAccess
c_func
(paren
id|usDspBaseIO
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780D_WriteDStore exit bRC=TRUE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_ReadIStore
r_int
id|dsp3780I_ReadIStore
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_void
id|__user
op_star
id|pvBuffer
comma
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
(brace
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
id|pvBuffer
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_ReadIStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|pusBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;* Set the initial MSA address. To convert from an instruction store&n;&t;* address to an MSA address&n;&t;* shift the address two bits to the left and set bit 22&n;&t;*/
id|ulDSPAddr
op_assign
(paren
id|ulDSPAddr
op_lshift
l_int|2
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulDSPAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulDSPAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Transfer the memory block */
r_while
c_loop
(paren
id|uCount
op_decrement
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|val_lo
comma
id|val_hi
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|val_lo
op_assign
id|InWordDsp
c_func
(paren
id|DSP_MsaDataISLow
)paren
suffix:semicolon
id|val_hi
op_assign
id|InWordDsp
c_func
(paren
id|DSP_MsaDataDSISHigh
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val_lo
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val_hi
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|PRINTK_4
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_ReadIStore uCount %x val_lo %x val_hi %x&bslash;n&quot;
comma
id|uCount
comma
id|val_lo
comma
id|val_hi
)paren
suffix:semicolon
id|PaceMsaAccess
c_func
(paren
id|usDspBaseIO
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_ReadIStore exit bRC=TRUE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_WriteIStore
r_int
id|dsp3780I_WriteIStore
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_void
id|__user
op_star
id|pvBuffer
comma
r_int
id|uCount
comma
r_int
r_int
id|ulDSPAddr
)paren
(brace
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
id|pvBuffer
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_WriteIStore entry usDspBaseIO %x, pusBuffer %p, uCount %x, ulDSPAddr %lx&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|pusBuffer
comma
id|uCount
comma
id|ulDSPAddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;* Set the initial MSA address. To convert from an instruction store&n;&t;* address to an MSA address&n;&t;* shift the address two bits to the left and set bit 22&n;&t;*/
id|ulDSPAddr
op_assign
(paren
id|ulDSPAddr
op_lshift
l_int|2
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrLow
comma
(paren
r_int
r_int
)paren
id|ulDSPAddr
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaAddrHigh
comma
(paren
r_int
r_int
)paren
(paren
id|ulDSPAddr
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Transfer the memory block */
r_while
c_loop
(paren
id|uCount
op_decrement
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|val_lo
comma
id|val_hi
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val_lo
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val_hi
comma
id|pusBuffer
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaDataISLow
comma
id|val_lo
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_MsaDataDSISHigh
comma
id|val_hi
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_WriteIStore uCount %x val_lo %x val_hi %x&bslash;n&quot;
comma
id|uCount
comma
id|val_lo
comma
id|val_hi
)paren
suffix:semicolon
id|PaceMsaAccess
c_func
(paren
id|usDspBaseIO
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780I::dsp3780I_WriteIStore exit bRC=TRUE&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsp3780I_GetIPCSource
r_int
id|dsp3780I_GetIPCSource
c_func
(paren
r_int
r_int
id|usDspBaseIO
comma
r_int
r_int
op_star
id|pusIPCSource
)paren
(brace
id|DSP_HBRIDGE_CONTROL
id|rHBridgeControl
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_GetIPCSource entry usDspBaseIO %x pusIPCSource %p&bslash;n&quot;
comma
id|usDspBaseIO
comma
id|pusIPCSource
)paren
suffix:semicolon
multiline_comment|/*&n;&t;* Disable DSP to PC interrupts, read the interrupt register,&n;&t;* clear the pending IPC bits, and reenable DSP to PC interrupts&n;&t;*/
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
op_assign
id|InWordDsp
c_func
(paren
id|DSP_HBridgeControl
)paren
suffix:semicolon
id|rHBridgeControl.EnableDspInt
op_assign
id|FALSE
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_HBridgeControl
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
op_star
id|pusIPCSource
op_assign
id|InWordDsp
c_func
(paren
id|DSP_Interrupt
)paren
suffix:semicolon
id|temp
op_assign
(paren
r_int
r_int
)paren
op_complement
(paren
op_star
id|pusIPCSource
)paren
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_GetIPCSource, usIPCSource %x ~ %x&bslash;n&quot;
comma
op_star
id|pusIPCSource
comma
id|temp
)paren
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_Interrupt
comma
(paren
r_int
r_int
)paren
op_complement
(paren
op_star
id|pusIPCSource
)paren
)paren
suffix:semicolon
id|rHBridgeControl.EnableDspInt
op_assign
id|TRUE
suffix:semicolon
id|OutWordDsp
c_func
(paren
id|DSP_HBridgeControl
comma
id|MKWORD
c_func
(paren
id|rHBridgeControl
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dsp_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_3780I
comma
l_string|&quot;3780i::dsp3780I_GetIPCSource exit usIPCSource %x&bslash;n&quot;
comma
op_star
id|pusIPCSource
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
