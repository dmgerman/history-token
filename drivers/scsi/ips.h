multiline_comment|/*****************************************************************************/
multiline_comment|/* ips.h -- driver for the IBM ServeRAID controller                          */
multiline_comment|/*                                                                           */
multiline_comment|/* Written By: Keith Mitchell, IBM Corporation                               */
multiline_comment|/*                                                                           */
multiline_comment|/* Copyright (C) 1999 IBM Corporation                                        */
multiline_comment|/*                                                                           */
multiline_comment|/* This program is free software; you can redistribute it and/or modify      */
multiline_comment|/* it under the terms of the GNU General Public License as published by      */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or         */
multiline_comment|/* (at your option) any later version.                                       */
multiline_comment|/*                                                                           */
multiline_comment|/* This program is distributed in the hope that it will be useful,           */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
multiline_comment|/* GNU General Public License for more details.                              */
multiline_comment|/*                                                                           */
multiline_comment|/* NO WARRANTY                                                               */
multiline_comment|/* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR        */
multiline_comment|/* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT      */
multiline_comment|/* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,      */
multiline_comment|/* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is    */
multiline_comment|/* solely responsible for determining the appropriateness of using and       */
multiline_comment|/* distributing the Program and assumes all risks associated with its        */
multiline_comment|/* exercise of rights under this Agreement, including but not limited to     */
multiline_comment|/* the risks and costs of program errors, damage to or loss of data,         */
multiline_comment|/* programs or equipment, and unavailability or interruption of operations.  */
multiline_comment|/*                                                                           */
multiline_comment|/* DISCLAIMER OF LIABILITY                                                   */
multiline_comment|/* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY   */
multiline_comment|/* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        */
multiline_comment|/* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND   */
multiline_comment|/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     */
multiline_comment|/* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE    */
multiline_comment|/* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED  */
multiline_comment|/* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES             */
multiline_comment|/*                                                                           */
multiline_comment|/* You should have received a copy of the GNU General Public License         */
multiline_comment|/* along with this program; if not, write to the Free Software               */
multiline_comment|/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
multiline_comment|/*                                                                           */
multiline_comment|/* Bugs/Comments/Suggestions should be mailed to:                            */
multiline_comment|/*      ipslinux@us.ibm.com                                                  */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef _IPS_H_
DECL|macro|_IPS_H_
mdefine_line|#define _IPS_H_
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Prototypes */
r_extern
r_int
id|ips_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_eh_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ips_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|ips_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|do_ipsintr
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;    * Some handy macros&n;    */
macro_line|#ifndef LinuxVersionCode
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(x,y,z)  (((x)&lt;&lt;16)+((y)&lt;&lt;8)+(z))
macro_line|#endif
DECL|macro|IPS_HA
mdefine_line|#define IPS_HA(x)                   ((ips_ha_t *) x-&gt;hostdata)
DECL|macro|IPS_COMMAND_ID
mdefine_line|#define IPS_COMMAND_ID(ha, scb)     (int) (scb - ha-&gt;scbs)
DECL|macro|IPS_IS_TROMBONE
mdefine_line|#define IPS_IS_TROMBONE(ha)         (((ha-&gt;device_id == IPS_DEVICEID_COPPERHEAD) &amp;&amp; &bslash;&n;                                         (ha-&gt;revision_id &gt;= IPS_REVID_TROMBONE32) &amp;&amp; &bslash;&n;                                         (ha-&gt;revision_id &lt;= IPS_REVID_TROMBONE64)) ? 1 : 0)
DECL|macro|IPS_IS_CLARINET
mdefine_line|#define IPS_IS_CLARINET(ha)         (((ha-&gt;device_id == IPS_DEVICEID_COPPERHEAD) &amp;&amp; &bslash;&n;                                         (ha-&gt;revision_id &gt;= IPS_REVID_CLARINETP1) &amp;&amp; &bslash;&n;                                         (ha-&gt;revision_id &lt;= IPS_REVID_CLARINETP3)) ? 1 : 0)
DECL|macro|IPS_IS_MORPHEUS
mdefine_line|#define IPS_IS_MORPHEUS(ha)         (ha-&gt;device_id == IPS_DEVICEID_MORPHEUS)
DECL|macro|IPS_USE_I2O_DELIVER
mdefine_line|#define IPS_USE_I2O_DELIVER(ha)     ((IPS_IS_MORPHEUS(ha) || &bslash;&n;                                         (IPS_IS_TROMBONE(ha) &amp;&amp; &bslash;&n;                                          (ips_force_i2o))) ? 1 : 0)
DECL|macro|IPS_USE_I2O_STATUS
mdefine_line|#define IPS_USE_I2O_STATUS(ha)      (IPS_IS_MORPHEUS(ha))
DECL|macro|IPS_USE_MEMIO
mdefine_line|#define IPS_USE_MEMIO(ha)           ((IPS_IS_MORPHEUS(ha) || &bslash;&n;                                         ((IPS_IS_TROMBONE(ha) || IPS_IS_CLARINET(ha)) &amp;&amp; &bslash;&n;                                          (ips_force_memio))) ? 1 : 0)
macro_line|#ifndef VIRT_TO_BUS
DECL|macro|VIRT_TO_BUS
mdefine_line|#define VIRT_TO_BUS(x)           (unsigned int)virt_to_bus((void *) x)
macro_line|#endif
macro_line|#ifndef UDELAY
DECL|macro|UDELAY
mdefine_line|#define UDELAY udelay
macro_line|#endif
macro_line|#ifndef MDELAY
DECL|macro|MDELAY
mdefine_line|#define MDELAY mdelay
macro_line|#endif
macro_line|#ifndef verify_area_20
DECL|macro|verify_area_20
mdefine_line|#define verify_area_20(t,a,sz)   (0) /* success */
macro_line|#endif
macro_line|#ifndef DECLARE_MUTEX_LOCKED
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(sem) struct semaphore sem = MUTEX_LOCKED;
macro_line|#endif
multiline_comment|/*&n;    * Lock macros&n;    */
DECL|macro|IPS_SCB_LOCK
mdefine_line|#define IPS_SCB_LOCK(cpu_flags)      spin_lock_irqsave(&amp;ha-&gt;scb_lock, cpu_flags)
DECL|macro|IPS_SCB_UNLOCK
mdefine_line|#define IPS_SCB_UNLOCK(cpu_flags)    spin_unlock_irqrestore(&amp;ha-&gt;scb_lock, cpu_flags)
DECL|macro|IPS_QUEUE_LOCK
mdefine_line|#define IPS_QUEUE_LOCK(queue)        spin_lock_irqsave(&amp;(queue)-&gt;lock, (queue)-&gt;cpu_flags)
DECL|macro|IPS_QUEUE_UNLOCK
mdefine_line|#define IPS_QUEUE_UNLOCK(queue)      spin_unlock_irqrestore(&amp;(queue)-&gt;lock, (queue)-&gt;cpu_flags)
DECL|macro|IPS_HA_LOCK
mdefine_line|#define IPS_HA_LOCK(cpu_flags)       spin_lock_irqsave(&amp;ha-&gt;ips_lock, cpu_flags)
DECL|macro|IPS_HA_UNLOCK
mdefine_line|#define IPS_HA_UNLOCK(cpu_flags)     spin_unlock_irqrestore(&amp;ha-&gt;ips_lock, cpu_flags)
multiline_comment|/*&n;    * Adapter address map equates&n;    */
DECL|macro|IPS_REG_HISR
mdefine_line|#define IPS_REG_HISR                 0x08    /* Host Interrupt Status Reg   */
DECL|macro|IPS_REG_CCSAR
mdefine_line|#define IPS_REG_CCSAR                0x10    /* Cmd Channel System Addr Reg */
DECL|macro|IPS_REG_CCCR
mdefine_line|#define IPS_REG_CCCR                 0x14    /* Cmd Channel Control Reg     */
DECL|macro|IPS_REG_SQHR
mdefine_line|#define IPS_REG_SQHR                 0x20    /* Status Q Head Reg           */
DECL|macro|IPS_REG_SQTR
mdefine_line|#define IPS_REG_SQTR                 0x24    /* Status Q Tail Reg           */
DECL|macro|IPS_REG_SQER
mdefine_line|#define IPS_REG_SQER                 0x28    /* Status Q End Reg            */
DECL|macro|IPS_REG_SQSR
mdefine_line|#define IPS_REG_SQSR                 0x2C    /* Status Q Start Reg          */
DECL|macro|IPS_REG_SCPR
mdefine_line|#define IPS_REG_SCPR                 0x05    /* Subsystem control port reg  */
DECL|macro|IPS_REG_ISPR
mdefine_line|#define IPS_REG_ISPR                 0x06    /* interrupt status port reg   */
DECL|macro|IPS_REG_CBSP
mdefine_line|#define IPS_REG_CBSP                 0x07    /* CBSP register               */
DECL|macro|IPS_REG_FLAP
mdefine_line|#define IPS_REG_FLAP                 0x18    /* Flash address port          */
DECL|macro|IPS_REG_FLDP
mdefine_line|#define IPS_REG_FLDP                 0x1C    /* Flash data port             */
DECL|macro|IPS_REG_NDAE
mdefine_line|#define IPS_REG_NDAE                 0x38    /* Anaconda 64 NDAE Register   */
DECL|macro|IPS_REG_I2O_INMSGQ
mdefine_line|#define IPS_REG_I2O_INMSGQ           0x40    /* I2O Inbound Message Queue   */
DECL|macro|IPS_REG_I2O_OUTMSGQ
mdefine_line|#define IPS_REG_I2O_OUTMSGQ          0x44    /* I2O Outbound Message Queue  */
DECL|macro|IPS_REG_I2O_HIR
mdefine_line|#define IPS_REG_I2O_HIR              0x30    /* I2O Interrupt Status        */
DECL|macro|IPS_REG_I960_IDR
mdefine_line|#define IPS_REG_I960_IDR             0x20    /* i960 Inbound Doorbell       */
DECL|macro|IPS_REG_I960_MSG0
mdefine_line|#define IPS_REG_I960_MSG0            0x18    /* i960 Outbound Reg 0         */
DECL|macro|IPS_REG_I960_MSG1
mdefine_line|#define IPS_REG_I960_MSG1            0x1C    /* i960 Outbound Reg 1         */
DECL|macro|IPS_REG_I960_OIMR
mdefine_line|#define IPS_REG_I960_OIMR            0x34    /* i960 Oubound Int Mask Reg   */
multiline_comment|/*&n;    * Adapter register bit equates&n;    */
DECL|macro|IPS_BIT_GHI
mdefine_line|#define IPS_BIT_GHI                  0x04    /* HISR General Host Interrupt */
DECL|macro|IPS_BIT_SQO
mdefine_line|#define IPS_BIT_SQO                  0x02    /* HISR Status Q Overflow      */
DECL|macro|IPS_BIT_SCE
mdefine_line|#define IPS_BIT_SCE                  0x01    /* HISR Status Channel Enqueue */
DECL|macro|IPS_BIT_SEM
mdefine_line|#define IPS_BIT_SEM                  0x08    /* CCCR Semaphore Bit          */
DECL|macro|IPS_BIT_ILE
mdefine_line|#define IPS_BIT_ILE                  0x10    /* CCCR ILE Bit                */
DECL|macro|IPS_BIT_START_CMD
mdefine_line|#define IPS_BIT_START_CMD            0x101A  /* CCCR Start Command Channel  */
DECL|macro|IPS_BIT_START_STOP
mdefine_line|#define IPS_BIT_START_STOP           0x0002  /* CCCR Start/Stop Bit         */
DECL|macro|IPS_BIT_RST
mdefine_line|#define IPS_BIT_RST                  0x80    /* SCPR Reset Bit              */
DECL|macro|IPS_BIT_EBM
mdefine_line|#define IPS_BIT_EBM                  0x02    /* SCPR Enable Bus Master      */
DECL|macro|IPS_BIT_EI
mdefine_line|#define IPS_BIT_EI                   0x80    /* HISR Enable Interrupts      */
DECL|macro|IPS_BIT_OP
mdefine_line|#define IPS_BIT_OP                   0x01    /* OP bit in CBSP              */
DECL|macro|IPS_BIT_I2O_OPQI
mdefine_line|#define IPS_BIT_I2O_OPQI             0x08    /* General Host Interrupt      */
DECL|macro|IPS_BIT_I960_MSG0I
mdefine_line|#define IPS_BIT_I960_MSG0I           0x01    /* Message Register 0 Interrupt*/
DECL|macro|IPS_BIT_I960_MSG1I
mdefine_line|#define IPS_BIT_I960_MSG1I           0x02    /* Message Register 1 Interrupt*/
multiline_comment|/*&n;    * Adapter Command ID Equates&n;    */
DECL|macro|IPS_CMD_GET_LD_INFO
mdefine_line|#define IPS_CMD_GET_LD_INFO          0x19
DECL|macro|IPS_CMD_GET_SUBSYS
mdefine_line|#define IPS_CMD_GET_SUBSYS           0x40
DECL|macro|IPS_CMD_READ_CONF
mdefine_line|#define IPS_CMD_READ_CONF            0x38
DECL|macro|IPS_CMD_RW_NVRAM_PAGE
mdefine_line|#define IPS_CMD_RW_NVRAM_PAGE        0xBC
DECL|macro|IPS_CMD_READ
mdefine_line|#define IPS_CMD_READ                 0x02
DECL|macro|IPS_CMD_WRITE
mdefine_line|#define IPS_CMD_WRITE                0x03
DECL|macro|IPS_CMD_FFDC
mdefine_line|#define IPS_CMD_FFDC                 0xD7
DECL|macro|IPS_CMD_ENQUIRY
mdefine_line|#define IPS_CMD_ENQUIRY              0x05
DECL|macro|IPS_CMD_FLUSH
mdefine_line|#define IPS_CMD_FLUSH                0x0A
DECL|macro|IPS_CMD_READ_SG
mdefine_line|#define IPS_CMD_READ_SG              0x82
DECL|macro|IPS_CMD_WRITE_SG
mdefine_line|#define IPS_CMD_WRITE_SG             0x83
DECL|macro|IPS_CMD_DCDB
mdefine_line|#define IPS_CMD_DCDB                 0x04
DECL|macro|IPS_CMD_DCDB_SG
mdefine_line|#define IPS_CMD_DCDB_SG              0x84
DECL|macro|IPS_CMD_CONFIG_SYNC
mdefine_line|#define IPS_CMD_CONFIG_SYNC          0x58
DECL|macro|IPS_CMD_ERROR_TABLE
mdefine_line|#define IPS_CMD_ERROR_TABLE          0x17
DECL|macro|IPS_CMD_RW_BIOSFW
mdefine_line|#define IPS_CMD_RW_BIOSFW            0x22
multiline_comment|/*&n;    * Adapter Equates&n;    */
DECL|macro|IPS_CSL
mdefine_line|#define IPS_CSL                      0xFF
DECL|macro|IPS_POCL
mdefine_line|#define IPS_POCL                     0x30
DECL|macro|IPS_NORM_STATE
mdefine_line|#define IPS_NORM_STATE               0x00
DECL|macro|IPS_MAX_ADAPTERS
mdefine_line|#define IPS_MAX_ADAPTERS             16
DECL|macro|IPS_MAX_IOCTL
mdefine_line|#define IPS_MAX_IOCTL                1
DECL|macro|IPS_MAX_IOCTL_QUEUE
mdefine_line|#define IPS_MAX_IOCTL_QUEUE          8
DECL|macro|IPS_MAX_QUEUE
mdefine_line|#define IPS_MAX_QUEUE                128
DECL|macro|IPS_BLKSIZE
mdefine_line|#define IPS_BLKSIZE                  512
DECL|macro|IPS_MAX_SG
mdefine_line|#define IPS_MAX_SG                   17
DECL|macro|IPS_MAX_LD
mdefine_line|#define IPS_MAX_LD                   8
DECL|macro|IPS_MAX_CHANNELS
mdefine_line|#define IPS_MAX_CHANNELS             4
DECL|macro|IPS_MAX_TARGETS
mdefine_line|#define IPS_MAX_TARGETS              15
DECL|macro|IPS_MAX_CHUNKS
mdefine_line|#define IPS_MAX_CHUNKS               16
DECL|macro|IPS_MAX_CMDS
mdefine_line|#define IPS_MAX_CMDS                 128
DECL|macro|IPS_MAX_XFER
mdefine_line|#define IPS_MAX_XFER                 0x10000
DECL|macro|IPS_NVRAM_P5_SIG
mdefine_line|#define IPS_NVRAM_P5_SIG             0xFFDDBB99
DECL|macro|IPS_MAX_POST_BYTES
mdefine_line|#define IPS_MAX_POST_BYTES           0x02
DECL|macro|IPS_MAX_CONFIG_BYTES
mdefine_line|#define IPS_MAX_CONFIG_BYTES         0x02
DECL|macro|IPS_GOOD_POST_STATUS
mdefine_line|#define IPS_GOOD_POST_STATUS         0x80
DECL|macro|IPS_SEM_TIMEOUT
mdefine_line|#define IPS_SEM_TIMEOUT              2000
DECL|macro|IPS_IOCTL_COMMAND
mdefine_line|#define IPS_IOCTL_COMMAND            0x0D
DECL|macro|IPS_IOCTL_NEW_COMMAND
mdefine_line|#define IPS_IOCTL_NEW_COMMAND        0x81
DECL|macro|IPS_INTR_ON
mdefine_line|#define IPS_INTR_ON                  0
DECL|macro|IPS_INTR_IORL
mdefine_line|#define IPS_INTR_IORL                1
DECL|macro|IPS_INTR_HAL
mdefine_line|#define IPS_INTR_HAL                 2
DECL|macro|IPS_ADAPTER_ID
mdefine_line|#define IPS_ADAPTER_ID               0xF
DECL|macro|IPS_VENDORID
mdefine_line|#define IPS_VENDORID                 0x1014
DECL|macro|IPS_DEVICEID_COPPERHEAD
mdefine_line|#define IPS_DEVICEID_COPPERHEAD      0x002E
DECL|macro|IPS_DEVICEID_MORPHEUS
mdefine_line|#define IPS_DEVICEID_MORPHEUS        0x01BD
DECL|macro|IPS_SUBDEVICEID_4M
mdefine_line|#define IPS_SUBDEVICEID_4M           0x01BE
DECL|macro|IPS_SUBDEVICEID_4L
mdefine_line|#define IPS_SUBDEVICEID_4L           0x01BF
DECL|macro|IPS_SUBDEVICEID_4MX
mdefine_line|#define IPS_SUBDEVICEID_4MX          0x0208
DECL|macro|IPS_SUBDEVICEID_4LX
mdefine_line|#define IPS_SUBDEVICEID_4LX          0x020E
DECL|macro|IPS_IOCTL_SIZE
mdefine_line|#define IPS_IOCTL_SIZE               8192
DECL|macro|IPS_STATUS_SIZE
mdefine_line|#define IPS_STATUS_SIZE              4
DECL|macro|IPS_STATUS_Q_SIZE
mdefine_line|#define IPS_STATUS_Q_SIZE            (IPS_MAX_CMDS+1) * IPS_STATUS_SIZE
DECL|macro|IPS_IMAGE_SIZE
mdefine_line|#define IPS_IMAGE_SIZE               500 * 1024
DECL|macro|IPS_MEMMAP_SIZE
mdefine_line|#define IPS_MEMMAP_SIZE              128
DECL|macro|IPS_ONE_MSEC
mdefine_line|#define IPS_ONE_MSEC                 1
DECL|macro|IPS_ONE_SEC
mdefine_line|#define IPS_ONE_SEC                  1000
multiline_comment|/*&n;    * Geometry Settings&n;    */
DECL|macro|IPS_COMP_HEADS
mdefine_line|#define IPS_COMP_HEADS               128
DECL|macro|IPS_COMP_SECTORS
mdefine_line|#define IPS_COMP_SECTORS             32
DECL|macro|IPS_NORM_HEADS
mdefine_line|#define IPS_NORM_HEADS               254
DECL|macro|IPS_NORM_SECTORS
mdefine_line|#define IPS_NORM_SECTORS             63
multiline_comment|/*&n;    * Adapter Basic Status Codes&n;    */
DECL|macro|IPS_BASIC_STATUS_MASK
mdefine_line|#define IPS_BASIC_STATUS_MASK        0xFF
DECL|macro|IPS_GSC_STATUS_MASK
mdefine_line|#define IPS_GSC_STATUS_MASK          0x0F
DECL|macro|IPS_CMD_SUCCESS
mdefine_line|#define IPS_CMD_SUCCESS              0x00
DECL|macro|IPS_CMD_RECOVERED_ERROR
mdefine_line|#define IPS_CMD_RECOVERED_ERROR      0x01
DECL|macro|IPS_INVAL_OPCO
mdefine_line|#define IPS_INVAL_OPCO               0x03
DECL|macro|IPS_INVAL_CMD_BLK
mdefine_line|#define IPS_INVAL_CMD_BLK            0x04
DECL|macro|IPS_INVAL_PARM_BLK
mdefine_line|#define IPS_INVAL_PARM_BLK           0x05
DECL|macro|IPS_BUSY
mdefine_line|#define IPS_BUSY                     0x08
DECL|macro|IPS_CMD_CMPLT_WERROR
mdefine_line|#define IPS_CMD_CMPLT_WERROR         0x0C
DECL|macro|IPS_LD_ERROR
mdefine_line|#define IPS_LD_ERROR                 0x0D
DECL|macro|IPS_CMD_TIMEOUT
mdefine_line|#define IPS_CMD_TIMEOUT              0x0E
DECL|macro|IPS_PHYS_DRV_ERROR
mdefine_line|#define IPS_PHYS_DRV_ERROR           0x0F
multiline_comment|/*&n;    * Adapter Extended Status Equates&n;    */
DECL|macro|IPS_ERR_SEL_TO
mdefine_line|#define IPS_ERR_SEL_TO               0xF0
DECL|macro|IPS_ERR_OU_RUN
mdefine_line|#define IPS_ERR_OU_RUN               0xF2
DECL|macro|IPS_ERR_HOST_RESET
mdefine_line|#define IPS_ERR_HOST_RESET           0xF7
DECL|macro|IPS_ERR_DEV_RESET
mdefine_line|#define IPS_ERR_DEV_RESET            0xF8
DECL|macro|IPS_ERR_RECOVERY
mdefine_line|#define IPS_ERR_RECOVERY             0xFC
DECL|macro|IPS_ERR_CKCOND
mdefine_line|#define IPS_ERR_CKCOND               0xFF
multiline_comment|/*&n;    * Operating System Defines&n;    */
DECL|macro|IPS_OS_WINDOWS_NT
mdefine_line|#define IPS_OS_WINDOWS_NT            0x01
DECL|macro|IPS_OS_NETWARE
mdefine_line|#define IPS_OS_NETWARE               0x02
DECL|macro|IPS_OS_OPENSERVER
mdefine_line|#define IPS_OS_OPENSERVER            0x03
DECL|macro|IPS_OS_UNIXWARE
mdefine_line|#define IPS_OS_UNIXWARE              0x04
DECL|macro|IPS_OS_SOLARIS
mdefine_line|#define IPS_OS_SOLARIS               0x05
DECL|macro|IPS_OS_OS2
mdefine_line|#define IPS_OS_OS2                   0x06
DECL|macro|IPS_OS_LINUX
mdefine_line|#define IPS_OS_LINUX                 0x07
DECL|macro|IPS_OS_FREEBSD
mdefine_line|#define IPS_OS_FREEBSD               0x08
multiline_comment|/*&n;    * Adapter Revision ID&squot;s&n;    */
DECL|macro|IPS_REVID_SERVERAID
mdefine_line|#define IPS_REVID_SERVERAID          0x02
DECL|macro|IPS_REVID_NAVAJO
mdefine_line|#define IPS_REVID_NAVAJO             0x03
DECL|macro|IPS_REVID_SERVERAID2
mdefine_line|#define IPS_REVID_SERVERAID2         0x04
DECL|macro|IPS_REVID_CLARINETP1
mdefine_line|#define IPS_REVID_CLARINETP1         0x05
DECL|macro|IPS_REVID_CLARINETP2
mdefine_line|#define IPS_REVID_CLARINETP2         0x07
DECL|macro|IPS_REVID_CLARINETP3
mdefine_line|#define IPS_REVID_CLARINETP3         0x0D
DECL|macro|IPS_REVID_TROMBONE32
mdefine_line|#define IPS_REVID_TROMBONE32         0x0F
DECL|macro|IPS_REVID_TROMBONE64
mdefine_line|#define IPS_REVID_TROMBONE64         0x10
multiline_comment|/*&n;    * NVRAM Page 5 Adapter Defines&n;    */
DECL|macro|IPS_ADTYPE_SERVERAID
mdefine_line|#define IPS_ADTYPE_SERVERAID         0x01
DECL|macro|IPS_ADTYPE_SERVERAID2
mdefine_line|#define IPS_ADTYPE_SERVERAID2        0x02
DECL|macro|IPS_ADTYPE_NAVAJO
mdefine_line|#define IPS_ADTYPE_NAVAJO            0x03
DECL|macro|IPS_ADTYPE_KIOWA
mdefine_line|#define IPS_ADTYPE_KIOWA             0x04
DECL|macro|IPS_ADTYPE_SERVERAID3
mdefine_line|#define IPS_ADTYPE_SERVERAID3        0x05
DECL|macro|IPS_ADTYPE_SERVERAID3L
mdefine_line|#define IPS_ADTYPE_SERVERAID3L       0x06
DECL|macro|IPS_ADTYPE_SERVERAID4H
mdefine_line|#define IPS_ADTYPE_SERVERAID4H       0x07
DECL|macro|IPS_ADTYPE_SERVERAID4M
mdefine_line|#define IPS_ADTYPE_SERVERAID4M       0x08
DECL|macro|IPS_ADTYPE_SERVERAID4L
mdefine_line|#define IPS_ADTYPE_SERVERAID4L       0x09
DECL|macro|IPS_ADTYPE_SERVERAID4MX
mdefine_line|#define IPS_ADTYPE_SERVERAID4MX      0x0A
DECL|macro|IPS_ADTYPE_SERVERAID4LX
mdefine_line|#define IPS_ADTYPE_SERVERAID4LX      0x0B
multiline_comment|/*&n;    * Adapter Command/Status Packet Definitions&n;    */
DECL|macro|IPS_SUCCESS
mdefine_line|#define IPS_SUCCESS                  0x01 /* Successfully completed       */
DECL|macro|IPS_SUCCESS_IMM
mdefine_line|#define IPS_SUCCESS_IMM              0x02 /* Success - Immediately        */
DECL|macro|IPS_FAILURE
mdefine_line|#define IPS_FAILURE                  0x04 /* Completed with Error         */
multiline_comment|/*&n;    * Logical Drive Equates&n;    */
DECL|macro|IPS_LD_OFFLINE
mdefine_line|#define IPS_LD_OFFLINE               0x02
DECL|macro|IPS_LD_OKAY
mdefine_line|#define IPS_LD_OKAY                  0x03
DECL|macro|IPS_LD_FREE
mdefine_line|#define IPS_LD_FREE                  0x00
DECL|macro|IPS_LD_SYS
mdefine_line|#define IPS_LD_SYS                   0x06
DECL|macro|IPS_LD_CRS
mdefine_line|#define IPS_LD_CRS                   0x24
multiline_comment|/*&n;    * DCDB Table Equates&n;    */
DECL|macro|IPS_NO_DISCONNECT
mdefine_line|#define IPS_NO_DISCONNECT            0x00
DECL|macro|IPS_DISCONNECT_ALLOWED
mdefine_line|#define IPS_DISCONNECT_ALLOWED       0x80
DECL|macro|IPS_NO_AUTO_REQSEN
mdefine_line|#define IPS_NO_AUTO_REQSEN           0x40
DECL|macro|IPS_DATA_NONE
mdefine_line|#define IPS_DATA_NONE                0x00
DECL|macro|IPS_DATA_UNK
mdefine_line|#define IPS_DATA_UNK                 0x00
DECL|macro|IPS_DATA_IN
mdefine_line|#define IPS_DATA_IN                  0x01
DECL|macro|IPS_DATA_OUT
mdefine_line|#define IPS_DATA_OUT                 0x02
DECL|macro|IPS_TRANSFER64K
mdefine_line|#define IPS_TRANSFER64K              0x08
DECL|macro|IPS_NOTIMEOUT
mdefine_line|#define IPS_NOTIMEOUT                0x00
DECL|macro|IPS_TIMEOUT10
mdefine_line|#define IPS_TIMEOUT10                0x10
DECL|macro|IPS_TIMEOUT60
mdefine_line|#define IPS_TIMEOUT60                0x20
DECL|macro|IPS_TIMEOUT20M
mdefine_line|#define IPS_TIMEOUT20M               0x30
multiline_comment|/*&n;    * Host adapter Flags (bit numbers)&n;    */
DECL|macro|IPS_IN_INTR
mdefine_line|#define IPS_IN_INTR                  0
DECL|macro|IPS_IN_ABORT
mdefine_line|#define IPS_IN_ABORT                 1
DECL|macro|IPS_IN_RESET
mdefine_line|#define IPS_IN_RESET                 2
multiline_comment|/*&n;    * SCB Flags&n;    */
DECL|macro|IPS_SCB_ACTIVE
mdefine_line|#define IPS_SCB_ACTIVE               0x00001
DECL|macro|IPS_SCB_WAITING
mdefine_line|#define IPS_SCB_WAITING              0x00002
multiline_comment|/*&n;    * Passthru stuff&n;    */
DECL|macro|IPS_COPPUSRCMD
mdefine_line|#define IPS_COPPUSRCMD              ((&squot;C&squot;&lt;&lt;8) | 65)
DECL|macro|IPS_COPPIOCCMD
mdefine_line|#define IPS_COPPIOCCMD              ((&squot;C&squot;&lt;&lt;8) | 66)
DECL|macro|IPS_NUMCTRLS
mdefine_line|#define IPS_NUMCTRLS                ((&squot;C&squot;&lt;&lt;8) | 68)
DECL|macro|IPS_CTRLINFO
mdefine_line|#define IPS_CTRLINFO                ((&squot;C&squot;&lt;&lt;8) | 69)
DECL|macro|IPS_FLASHBIOS
mdefine_line|#define IPS_FLASHBIOS               ((&squot;C&squot;&lt;&lt;8) | 70)
multiline_comment|/* time oriented stuff */
DECL|macro|IPS_IS_LEAP_YEAR
mdefine_line|#define IPS_IS_LEAP_YEAR(y)           (((y % 4 == 0) &amp;&amp; ((y % 100 != 0) || (y % 400 == 0))) ? 1 : 0)
DECL|macro|IPS_NUM_LEAP_YEARS_THROUGH
mdefine_line|#define IPS_NUM_LEAP_YEARS_THROUGH(y) ((y) / 4 - (y) / 100 + (y) / 400)
DECL|macro|IPS_SECS_MIN
mdefine_line|#define IPS_SECS_MIN                 60
DECL|macro|IPS_SECS_HOUR
mdefine_line|#define IPS_SECS_HOUR                3600
DECL|macro|IPS_SECS_8HOURS
mdefine_line|#define IPS_SECS_8HOURS              28800
DECL|macro|IPS_SECS_DAY
mdefine_line|#define IPS_SECS_DAY                 86400
DECL|macro|IPS_DAYS_NORMAL_YEAR
mdefine_line|#define IPS_DAYS_NORMAL_YEAR         365
DECL|macro|IPS_DAYS_LEAP_YEAR
mdefine_line|#define IPS_DAYS_LEAP_YEAR           366
DECL|macro|IPS_EPOCH_YEAR
mdefine_line|#define IPS_EPOCH_YEAR               1970
multiline_comment|/*&n;    * Scsi_Host Template&n;    */
macro_line|#if LINUX_VERSION_CODE &lt; LinuxVersionCode(2,3,27)
DECL|macro|IPS
mdefine_line|#define IPS {                            &bslash;&n;    next : NULL,                          &bslash;&n;    module : NULL,                        &bslash;&n;    proc_info : NULL,                     &bslash;&n;    proc_dir : NULL,                      &bslash;&n;    name : NULL,                          &bslash;&n;    detect : ips_detect,                  &bslash;&n;    release : ips_release,                &bslash;&n;    info : ips_info,                      &bslash;&n;    command : NULL,                       &bslash;&n;    queuecommand : ips_queue,             &bslash;&n;    eh_strategy_handler : NULL,           &bslash;&n;    eh_abort_handler : ips_eh_abort,      &bslash;&n;    eh_device_reset_handler : NULL,       &bslash;&n;    eh_bus_reset_handler : NULL,          &bslash;&n;    eh_host_reset_handler : ips_eh_reset, &bslash;&n;    abort : NULL,                         &bslash;&n;    reset : NULL,                         &bslash;&n;    slave_attach : NULL,                  &bslash;&n;    bios_param : ips_biosparam,           &bslash;&n;    can_queue : 0,                        &bslash;&n;    this_id: -1,                          &bslash;&n;    sg_tablesize : IPS_MAX_SG,            &bslash;&n;    cmd_per_lun: 16,                      &bslash;&n;    present : 0,                          &bslash;&n;    unchecked_isa_dma : 0,                &bslash;&n;    use_clustering : ENABLE_CLUSTERING,   &bslash;&n;    use_new_eh_code : 1                   &bslash;&n;}
macro_line|#else
DECL|macro|IPS
mdefine_line|#define IPS {                            &bslash;&n;    next : NULL,                          &bslash;&n;    module : NULL,                        &bslash;&n;    proc_info : NULL,                     &bslash;&n;    name : NULL,                          &bslash;&n;    detect : ips_detect,                  &bslash;&n;    release : ips_release,                &bslash;&n;    info : ips_info,                      &bslash;&n;    command : NULL,                       &bslash;&n;    queuecommand : ips_queue,             &bslash;&n;    eh_strategy_handler : NULL,           &bslash;&n;    eh_abort_handler : ips_eh_abort,      &bslash;&n;    eh_device_reset_handler : NULL,       &bslash;&n;    eh_bus_reset_handler : NULL,          &bslash;&n;    eh_host_reset_handler : ips_eh_reset, &bslash;&n;    abort : NULL,                         &bslash;&n;    reset : NULL,                         &bslash;&n;    slave_attach : NULL,                  &bslash;&n;    bios_param : ips_biosparam,           &bslash;&n;    can_queue : 0,                        &bslash;&n;    this_id: -1,                          &bslash;&n;    sg_tablesize : IPS_MAX_SG,            &bslash;&n;    cmd_per_lun: 16,                      &bslash;&n;    present : 0,                          &bslash;&n;    unchecked_isa_dma : 0,                &bslash;&n;    use_clustering : ENABLE_CLUSTERING,   &bslash;&n;    use_new_eh_code : 1                   &bslash;&n;}
macro_line|#endif
multiline_comment|/*&n; * IBM PCI Raid Command Formats&n; */
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|log_drv
id|u8
id|log_drv
suffix:semicolon
DECL|member|sg_count
id|u8
id|sg_count
suffix:semicolon
DECL|member|lba
id|u32
id|lba
suffix:semicolon
DECL|member|sg_addr
id|u32
id|sg_addr
suffix:semicolon
DECL|member|sector_count
id|u16
id|sector_count
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_IO_CMD
DECL|typedef|PIPS_IO_CMD
)brace
id|IPS_IO_CMD
comma
op_star
id|PIPS_IO_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_LD_CMD
DECL|typedef|PIPS_LD_CMD
)brace
id|IPS_LD_CMD
comma
op_star
id|PIPS_LD_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|typedef|IPS_IOCTL_CMD
DECL|typedef|PIPS_IOCTL_CMD
)brace
id|IPS_IOCTL_CMD
comma
op_star
id|PIPS_IOCTL_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|dcdb_address
id|u32
id|dcdb_address
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_DCDB_CMD
DECL|typedef|PIPS_DCDB_CMD
)brace
id|IPS_DCDB_CMD
comma
op_star
id|PIPS_DCDB_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|channel
id|u8
id|channel
suffix:semicolon
DECL|member|source_target
id|u8
id|source_target
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_CS_CMD
DECL|typedef|PIPS_CS_CMD
)brace
id|IPS_CS_CMD
comma
op_star
id|PIPS_CS_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|log_drv
id|u8
id|log_drv
suffix:semicolon
DECL|member|control
id|u8
id|control
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_US_CMD
DECL|typedef|PIPS_US_CMD
)brace
id|IPS_US_CMD
comma
op_star
id|PIPS_US_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_FC_CMD
DECL|typedef|PIPS_FC_CMD
)brace
id|IPS_FC_CMD
comma
op_star
id|PIPS_FC_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|desc
id|u8
id|desc
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_STATUS_CMD
DECL|typedef|PIPS_STATUS_CMD
)brace
id|IPS_STATUS_CMD
comma
op_star
id|PIPS_STATUS_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|page
id|u8
id|page
suffix:semicolon
DECL|member|write
id|u8
id|write
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|IPS_NVRAM_CMD
DECL|typedef|PIPS_NVRAM_CMD
)brace
id|IPS_NVRAM_CMD
comma
op_star
id|PIPS_NVRAM_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reset_count
id|u8
id|reset_count
suffix:semicolon
DECL|member|reset_type
id|u8
id|reset_type
suffix:semicolon
DECL|member|second
id|u8
id|second
suffix:semicolon
DECL|member|minute
id|u8
id|minute
suffix:semicolon
DECL|member|hour
id|u8
id|hour
suffix:semicolon
DECL|member|day
id|u8
id|day
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|month
id|u8
id|month
suffix:semicolon
DECL|member|yearH
id|u8
id|yearH
suffix:semicolon
DECL|member|yearL
id|u8
id|yearL
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|typedef|IPS_FFDC_CMD
DECL|typedef|PIPS_FFDC_CMD
)brace
id|IPS_FFDC_CMD
comma
op_star
id|PIPS_FFDC_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|direction
id|u8
id|direction
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|total_packets
id|u8
id|total_packets
suffix:semicolon
DECL|member|packet_num
id|u8
id|packet_num
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|typedef|IPS_FLASHFW_CMD
DECL|typedef|PIPS_FLASHFW_CMD
)brace
id|IPS_FLASHFW_CMD
comma
op_star
id|PIPS_FLASHFW_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|direction
id|u8
id|direction
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|typedef|IPS_FLASHBIOS_CMD
DECL|typedef|PIPS_FLASHBIOS_CMD
)brace
id|IPS_FLASHBIOS_CMD
comma
op_star
id|PIPS_FLASHBIOS_CMD
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|basic_io
id|IPS_IO_CMD
id|basic_io
suffix:semicolon
DECL|member|logical_info
id|IPS_LD_CMD
id|logical_info
suffix:semicolon
DECL|member|ioctl_info
id|IPS_IOCTL_CMD
id|ioctl_info
suffix:semicolon
DECL|member|dcdb
id|IPS_DCDB_CMD
id|dcdb
suffix:semicolon
DECL|member|config_sync
id|IPS_CS_CMD
id|config_sync
suffix:semicolon
DECL|member|unlock_stripe
id|IPS_US_CMD
id|unlock_stripe
suffix:semicolon
DECL|member|flush_cache
id|IPS_FC_CMD
id|flush_cache
suffix:semicolon
DECL|member|status
id|IPS_STATUS_CMD
id|status
suffix:semicolon
DECL|member|nvram
id|IPS_NVRAM_CMD
id|nvram
suffix:semicolon
DECL|member|ffdc
id|IPS_FFDC_CMD
id|ffdc
suffix:semicolon
DECL|member|flashfw
id|IPS_FLASHFW_CMD
id|flashfw
suffix:semicolon
DECL|member|flashbios
id|IPS_FLASHBIOS_CMD
id|flashbios
suffix:semicolon
DECL|typedef|IPS_HOST_COMMAND
DECL|typedef|PIPS_HOST_COMMAND
)brace
id|IPS_HOST_COMMAND
comma
op_star
id|PIPS_HOST_COMMAND
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|logical_id
id|u8
id|logical_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|raid_level
id|u8
id|raid_level
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|sector_count
id|u32
id|sector_count
suffix:semicolon
DECL|typedef|IPS_DRIVE_INFO
DECL|typedef|PIPS_DRIVE_INFO
)brace
id|IPS_DRIVE_INFO
comma
op_star
id|PIPS_DRIVE_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|no_of_log_drive
id|u8
id|no_of_log_drive
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|drive_info
id|IPS_DRIVE_INFO
id|drive_info
(braket
id|IPS_MAX_LD
)braket
suffix:semicolon
DECL|typedef|IPS_LD_INFO
DECL|typedef|PIPS_LD_INFO
)brace
id|IPS_LD_INFO
comma
op_star
id|PIPS_LD_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|device_address
id|u8
id|device_address
suffix:semicolon
DECL|member|cmd_attribute
id|u8
id|cmd_attribute
suffix:semicolon
DECL|member|transfer_length
id|u16
id|transfer_length
suffix:semicolon
DECL|member|buffer_pointer
id|u32
id|buffer_pointer
suffix:semicolon
DECL|member|cdb_length
id|u8
id|cdb_length
suffix:semicolon
DECL|member|sense_length
id|u8
id|sense_length
suffix:semicolon
DECL|member|sg_count
id|u8
id|sg_count
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|scsi_cdb
id|u8
id|scsi_cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|sense_info
id|u8
id|sense_info
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|scsi_status
id|u8
id|scsi_status
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|IPS_DCDB_TABLE
DECL|typedef|PIPS_DCDB_TABLE
)brace
id|IPS_DCDB_TABLE
comma
op_star
id|PIPS_DCDB_TABLE
suffix:semicolon
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|reserved
r_volatile
id|u8
id|reserved
suffix:semicolon
DECL|member|command_id
r_volatile
id|u8
id|command_id
suffix:semicolon
DECL|member|basic_status
r_volatile
id|u8
id|basic_status
suffix:semicolon
DECL|member|extended_status
r_volatile
id|u8
id|extended_status
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|value
r_volatile
id|u32
id|value
suffix:semicolon
DECL|typedef|IPS_STATUS
DECL|typedef|PIPS_STATUS
)brace
id|IPS_STATUS
comma
op_star
id|PIPS_STATUS
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|status
id|IPS_STATUS
id|status
(braket
id|IPS_MAX_CMDS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|p_status_start
r_volatile
id|PIPS_STATUS
id|p_status_start
suffix:semicolon
DECL|member|p_status_end
r_volatile
id|PIPS_STATUS
id|p_status_end
suffix:semicolon
DECL|member|p_status_tail
r_volatile
id|PIPS_STATUS
id|p_status_tail
suffix:semicolon
DECL|member|hw_status_start
r_volatile
id|u32
id|hw_status_start
suffix:semicolon
DECL|member|hw_status_tail
r_volatile
id|u32
id|hw_status_tail
suffix:semicolon
DECL|member|logical_drive_info
id|IPS_LD_INFO
id|logical_drive_info
suffix:semicolon
DECL|typedef|IPS_ADAPTER
DECL|typedef|PIPS_ADAPTER
)brace
id|IPS_ADAPTER
comma
op_star
id|PIPS_ADAPTER
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucLogDriveCount
id|u8
id|ucLogDriveCount
suffix:semicolon
DECL|member|ucMiscFlag
id|u8
id|ucMiscFlag
suffix:semicolon
DECL|member|ucSLTFlag
id|u8
id|ucSLTFlag
suffix:semicolon
DECL|member|ucBSTFlag
id|u8
id|ucBSTFlag
suffix:semicolon
DECL|member|ucPwrChgCnt
id|u8
id|ucPwrChgCnt
suffix:semicolon
DECL|member|ucWrongAdrCnt
id|u8
id|ucWrongAdrCnt
suffix:semicolon
DECL|member|ucUnidentCnt
id|u8
id|ucUnidentCnt
suffix:semicolon
DECL|member|ucNVramDevChgCnt
id|u8
id|ucNVramDevChgCnt
suffix:semicolon
DECL|member|CodeBlkVersion
id|u8
id|CodeBlkVersion
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|BootBlkVersion
id|u8
id|BootBlkVersion
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ulDriveSize
id|u32
id|ulDriveSize
(braket
id|IPS_MAX_LD
)braket
suffix:semicolon
DECL|member|ucConcurrentCmdCount
id|u8
id|ucConcurrentCmdCount
suffix:semicolon
DECL|member|ucMaxPhysicalDevices
id|u8
id|ucMaxPhysicalDevices
suffix:semicolon
DECL|member|usFlashRepgmCount
id|u16
id|usFlashRepgmCount
suffix:semicolon
DECL|member|ucDefunctDiskCount
id|u8
id|ucDefunctDiskCount
suffix:semicolon
DECL|member|ucRebuildFlag
id|u8
id|ucRebuildFlag
suffix:semicolon
DECL|member|ucOfflineLogDrvCount
id|u8
id|ucOfflineLogDrvCount
suffix:semicolon
DECL|member|ucCriticalDrvCount
id|u8
id|ucCriticalDrvCount
suffix:semicolon
DECL|member|usConfigUpdateCount
id|u16
id|usConfigUpdateCount
suffix:semicolon
DECL|member|ucBlkFlag
id|u8
id|ucBlkFlag
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|usAddrDeadDisk
id|u16
id|usAddrDeadDisk
(braket
id|IPS_MAX_CHANNELS
op_star
id|IPS_MAX_TARGETS
)braket
suffix:semicolon
DECL|typedef|IPS_ENQ
DECL|typedef|PIPS_ENQ
)brace
id|IPS_ENQ
comma
op_star
id|PIPS_ENQ
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucInitiator
id|u8
id|ucInitiator
suffix:semicolon
DECL|member|ucParameters
id|u8
id|ucParameters
suffix:semicolon
DECL|member|ucMiscFlag
id|u8
id|ucMiscFlag
suffix:semicolon
DECL|member|ucState
id|u8
id|ucState
suffix:semicolon
DECL|member|ulBlockCount
id|u32
id|ulBlockCount
suffix:semicolon
DECL|member|ucDeviceId
id|u8
id|ucDeviceId
(braket
l_int|28
)braket
suffix:semicolon
DECL|typedef|IPS_DEVSTATE
DECL|typedef|PIPS_DEVSTATE
)brace
id|IPS_DEVSTATE
comma
op_star
id|PIPS_DEVSTATE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucChn
id|u8
id|ucChn
suffix:semicolon
DECL|member|ucTgt
id|u8
id|ucTgt
suffix:semicolon
DECL|member|ucReserved
id|u16
id|ucReserved
suffix:semicolon
DECL|member|ulStartSect
id|u32
id|ulStartSect
suffix:semicolon
DECL|member|ulNoOfSects
id|u32
id|ulNoOfSects
suffix:semicolon
DECL|typedef|IPS_CHUNK
DECL|typedef|PIPS_CHUNK
)brace
id|IPS_CHUNK
comma
op_star
id|PIPS_CHUNK
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucUserField
id|u16
id|ucUserField
suffix:semicolon
DECL|member|ucState
id|u8
id|ucState
suffix:semicolon
DECL|member|ucRaidCacheParam
id|u8
id|ucRaidCacheParam
suffix:semicolon
DECL|member|ucNoOfChunkUnits
id|u8
id|ucNoOfChunkUnits
suffix:semicolon
DECL|member|ucStripeSize
id|u8
id|ucStripeSize
suffix:semicolon
DECL|member|ucParams
id|u8
id|ucParams
suffix:semicolon
DECL|member|ucReserved
id|u8
id|ucReserved
suffix:semicolon
DECL|member|ulLogDrvSize
id|u32
id|ulLogDrvSize
suffix:semicolon
DECL|member|chunk
id|IPS_CHUNK
id|chunk
(braket
id|IPS_MAX_CHUNKS
)braket
suffix:semicolon
DECL|typedef|IPS_LD
DECL|typedef|PIPS_LD
)brace
id|IPS_LD
comma
op_star
id|PIPS_LD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|board_disc
id|u8
id|board_disc
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|processor
id|u8
id|processor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ucNoChanType
id|u8
id|ucNoChanType
suffix:semicolon
DECL|member|ucNoHostIntType
id|u8
id|ucNoHostIntType
suffix:semicolon
DECL|member|ucCompression
id|u8
id|ucCompression
suffix:semicolon
DECL|member|ucNvramType
id|u8
id|ucNvramType
suffix:semicolon
DECL|member|ulNvramSize
id|u32
id|ulNvramSize
suffix:semicolon
DECL|typedef|IPS_HARDWARE
DECL|typedef|PIPS_HARDWARE
)brace
id|IPS_HARDWARE
comma
op_star
id|PIPS_HARDWARE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucLogDriveCount
id|u8
id|ucLogDriveCount
suffix:semicolon
DECL|member|ucDateD
id|u8
id|ucDateD
suffix:semicolon
DECL|member|ucDateM
id|u8
id|ucDateM
suffix:semicolon
DECL|member|ucDateY
id|u8
id|ucDateY
suffix:semicolon
DECL|member|init_id
id|u8
id|init_id
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|host_id
id|u8
id|host_id
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|time_sign
id|u8
id|time_sign
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
DECL|member|usCfgDrvUpdateCnt
id|u32
id|usCfgDrvUpdateCnt
suffix:colon
l_int|16
suffix:semicolon
DECL|member|ConcurDrvStartCnt
id|u32
id|ConcurDrvStartCnt
suffix:colon
l_int|4
suffix:semicolon
DECL|member|StartupDelay
id|u32
id|StartupDelay
suffix:colon
l_int|4
suffix:semicolon
DECL|member|auto_rearrange
id|u32
id|auto_rearrange
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cd_boot
id|u32
id|cd_boot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cluster
id|u32
id|cluster
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|5
suffix:semicolon
DECL|member|UserOpt
)brace
id|UserOpt
suffix:semicolon
DECL|member|user_field
id|u16
id|user_field
suffix:semicolon
DECL|member|ucRebuildRate
id|u8
id|ucRebuildRate
suffix:semicolon
DECL|member|ucReserve
id|u8
id|ucReserve
suffix:semicolon
DECL|member|hardware_disc
id|IPS_HARDWARE
id|hardware_disc
suffix:semicolon
DECL|member|logical_drive
id|IPS_LD
id|logical_drive
(braket
id|IPS_MAX_LD
)braket
suffix:semicolon
DECL|member|dev
id|IPS_DEVSTATE
id|dev
(braket
id|IPS_MAX_CHANNELS
)braket
(braket
id|IPS_MAX_TARGETS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|512
)braket
suffix:semicolon
DECL|typedef|IPS_CONF
DECL|typedef|PIPS_CONF
)brace
id|IPS_CONF
comma
op_star
id|PIPS_CONF
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|signature
id|u32
id|signature
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|adapter_slot
id|u8
id|adapter_slot
suffix:semicolon
DECL|member|adapter_type
id|u16
id|adapter_type
suffix:semicolon
DECL|member|bios_high
id|u8
id|bios_high
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bios_low
id|u8
id|bios_low
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u8
id|reserved3
suffix:semicolon
DECL|member|operating_system
id|u8
id|operating_system
suffix:semicolon
DECL|member|driver_high
id|u8
id|driver_high
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|driver_low
id|u8
id|driver_low
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved4
id|u8
id|reserved4
(braket
l_int|100
)braket
suffix:semicolon
DECL|typedef|IPS_NVRAM_P5
DECL|typedef|PIPS_NVRAM_P5
)brace
id|IPS_NVRAM_P5
comma
op_star
id|PIPS_NVRAM_P5
suffix:semicolon
DECL|struct|_IPS_SUBSYS
r_typedef
r_struct
id|_IPS_SUBSYS
(brace
DECL|member|param
id|u32
id|param
(braket
l_int|128
)braket
suffix:semicolon
DECL|typedef|IPS_SUBSYS
DECL|typedef|PIPS_SUBSYS
)brace
id|IPS_SUBSYS
comma
op_star
id|PIPS_SUBSYS
suffix:semicolon
multiline_comment|/*&n; * Inquiry Data Format&n; */
r_typedef
r_struct
(brace
DECL|member|DeviceType
id|u8
id|DeviceType
suffix:colon
l_int|5
suffix:semicolon
DECL|member|DeviceTypeQualifier
id|u8
id|DeviceTypeQualifier
suffix:colon
l_int|3
suffix:semicolon
DECL|member|DeviceTypeModifier
id|u8
id|DeviceTypeModifier
suffix:colon
l_int|7
suffix:semicolon
DECL|member|RemoveableMedia
id|u8
id|RemoveableMedia
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Versions
id|u8
id|Versions
suffix:semicolon
DECL|member|ResponseDataFormat
id|u8
id|ResponseDataFormat
suffix:semicolon
DECL|member|AdditionalLength
id|u8
id|AdditionalLength
suffix:semicolon
DECL|member|Reserved
id|u16
id|Reserved
suffix:semicolon
DECL|member|SoftReset
id|u8
id|SoftReset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|CommandQueue
id|u8
id|CommandQueue
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Reserved2
id|u8
id|Reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LinkedCommands
id|u8
id|LinkedCommands
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Synchronous
id|u8
id|Synchronous
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide16Bit
id|u8
id|Wide16Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide32Bit
id|u8
id|Wide32Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RelativeAddressing
id|u8
id|RelativeAddressing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|VendorId
id|u8
id|VendorId
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ProductId
id|u8
id|ProductId
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ProductRevisionLevel
id|u8
id|ProductRevisionLevel
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|VendorSpecific
id|u8
id|VendorSpecific
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|Reserved3
id|u8
id|Reserved3
(braket
l_int|40
)braket
suffix:semicolon
DECL|typedef|IPS_INQ_DATA
DECL|typedef|PIPS_INQ_DATA
)brace
id|IPS_INQ_DATA
comma
op_star
id|PIPS_INQ_DATA
suffix:semicolon
multiline_comment|/*&n; * Read Capacity Data Format&n; */
r_typedef
r_struct
(brace
DECL|member|lba
id|u32
id|lba
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|typedef|IPS_CAPACITY
)brace
id|IPS_CAPACITY
suffix:semicolon
multiline_comment|/*&n; * Sense Data Format&n; */
r_typedef
r_struct
(brace
DECL|member|pg_pc
id|u8
id|pg_pc
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code                    */
DECL|member|pg_res1
id|u8
id|pg_res1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved                     */
DECL|member|pg_len
id|u8
id|pg_len
suffix:semicolon
multiline_comment|/* Page Length                  */
DECL|member|pg_trk_z
id|u16
id|pg_trk_z
suffix:semicolon
multiline_comment|/* Tracks per zone              */
DECL|member|pg_asec_z
id|u16
id|pg_asec_z
suffix:semicolon
multiline_comment|/* Alternate sectors per zone   */
DECL|member|pg_atrk_z
id|u16
id|pg_atrk_z
suffix:semicolon
multiline_comment|/* Alternate tracks per zone    */
DECL|member|pg_atrk_v
id|u16
id|pg_atrk_v
suffix:semicolon
multiline_comment|/* Alternate tracks per volume  */
DECL|member|pg_sec_t
id|u16
id|pg_sec_t
suffix:semicolon
multiline_comment|/* Sectors per track            */
DECL|member|pg_bytes_s
id|u16
id|pg_bytes_s
suffix:semicolon
multiline_comment|/* Bytes per physical sectors   */
DECL|member|pg_intl
id|u16
id|pg_intl
suffix:semicolon
multiline_comment|/* Interleave                   */
DECL|member|pg_trkskew
id|u16
id|pg_trkskew
suffix:semicolon
multiline_comment|/* Track skew factor            */
DECL|member|pg_cylskew
id|u16
id|pg_cylskew
suffix:semicolon
multiline_comment|/* Cylinder Skew Factor         */
DECL|member|pg_res2
id|u32
id|pg_res2
suffix:colon
l_int|27
suffix:semicolon
multiline_comment|/* Reserved                     */
DECL|member|pg_ins
id|u32
id|pg_ins
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Inhibit Slave                */
DECL|member|pg_surf
id|u32
id|pg_surf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Allocate Surface Sectors     */
DECL|member|pg_rmb
id|u32
id|pg_rmb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Removeable                   */
DECL|member|pg_hsec
id|u32
id|pg_hsec
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hard sector formatting       */
DECL|member|pg_ssec
id|u32
id|pg_ssec
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Soft sector formatting       */
DECL|typedef|IPS_DADF
)brace
id|IPS_DADF
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pg_pc
id|u8
id|pg_pc
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code                     */
DECL|member|pg_res1
id|u8
id|pg_res1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved                      */
DECL|member|pg_len
id|u8
id|pg_len
suffix:semicolon
multiline_comment|/* Page Length                   */
DECL|member|pg_cylu
id|u16
id|pg_cylu
suffix:semicolon
multiline_comment|/* Number of cylinders (upper)   */
DECL|member|pg_cyll
id|u8
id|pg_cyll
suffix:semicolon
multiline_comment|/* Number of cylinders (lower)   */
DECL|member|pg_head
id|u8
id|pg_head
suffix:semicolon
multiline_comment|/* Number of heads               */
DECL|member|pg_wrpcompu
id|u16
id|pg_wrpcompu
suffix:semicolon
multiline_comment|/* Write precomp (upper)         */
DECL|member|pg_wrpcompl
id|u32
id|pg_wrpcompl
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Write precomp (lower)         */
DECL|member|pg_redwrcur
id|u32
id|pg_redwrcur
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Reduced write current         */
DECL|member|pg_drstep
id|u32
id|pg_drstep
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* Drive step rate               */
DECL|member|pg_landu
id|u32
id|pg_landu
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* Landing zone cylinder (upper) */
DECL|member|pg_landl
id|u32
id|pg_landl
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Landing zone cylinder (lower) */
DECL|member|pg_res2
id|u32
id|pg_res2
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Reserved                      */
DECL|typedef|IPS_RDDG
)brace
id|IPS_RDDG
suffix:semicolon
DECL|struct|ips_blk_desc
r_struct
id|ips_blk_desc
(brace
DECL|member|bd_dencode
id|u8
id|bd_dencode
suffix:semicolon
DECL|member|bd_nblks1
id|u8
id|bd_nblks1
suffix:semicolon
DECL|member|bd_nblks2
id|u8
id|bd_nblks2
suffix:semicolon
DECL|member|bd_nblks3
id|u8
id|bd_nblks3
suffix:semicolon
DECL|member|bd_res
id|u8
id|bd_res
suffix:semicolon
DECL|member|bd_blen1
id|u8
id|bd_blen1
suffix:semicolon
DECL|member|bd_blen2
id|u8
id|bd_blen2
suffix:semicolon
DECL|member|bd_blen3
id|u8
id|bd_blen3
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|plh_len
id|u8
id|plh_len
suffix:semicolon
multiline_comment|/* Data length             */
DECL|member|plh_type
id|u8
id|plh_type
suffix:semicolon
multiline_comment|/* Medium type             */
DECL|member|plh_res
id|u8
id|plh_res
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Reserved                */
DECL|member|plh_wp
id|u8
id|plh_wp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write protect           */
DECL|member|plh_bdl
id|u8
id|plh_bdl
suffix:semicolon
multiline_comment|/* Block descriptor length */
DECL|typedef|ips_sense_plh_t
)brace
id|ips_sense_plh_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|plh
id|ips_sense_plh_t
id|plh
suffix:semicolon
DECL|member|blk_desc
r_struct
id|ips_blk_desc
id|blk_desc
suffix:semicolon
r_union
(brace
DECL|member|pg3
id|IPS_DADF
id|pg3
suffix:semicolon
DECL|member|pg4
id|IPS_RDDG
id|pg4
suffix:semicolon
DECL|member|pdata
)brace
id|pdata
suffix:semicolon
DECL|typedef|ips_mdata_t
)brace
id|ips_mdata_t
suffix:semicolon
multiline_comment|/*&n; * Scatter Gather list format&n; */
DECL|struct|ips_sglist
r_typedef
r_struct
id|ips_sglist
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|typedef|IPS_SG_LIST
DECL|typedef|PIPS_SG_LIST
)brace
id|IPS_SG_LIST
comma
op_star
id|PIPS_SG_LIST
suffix:semicolon
DECL|struct|_IPS_INFOSTR
r_typedef
r_struct
id|_IPS_INFOSTR
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|pos
r_int
id|pos
suffix:semicolon
DECL|member|localpos
r_int
id|localpos
suffix:semicolon
DECL|typedef|IPS_INFOSTR
)brace
id|IPS_INFOSTR
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|option_name
r_char
op_star
id|option_name
suffix:semicolon
DECL|member|option_flag
r_int
op_star
id|option_flag
suffix:semicolon
DECL|member|option_value
r_int
id|option_value
suffix:semicolon
DECL|typedef|IPS_OPTION
)brace
id|IPS_OPTION
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|userbuffer
r_void
op_star
id|userbuffer
suffix:semicolon
DECL|member|usersize
id|u32
id|usersize
suffix:semicolon
DECL|member|kernbuffer
r_void
op_star
id|kernbuffer
suffix:semicolon
DECL|member|kernsize
id|u32
id|kernsize
suffix:semicolon
DECL|member|ha
r_void
op_star
id|ha
suffix:semicolon
DECL|member|SC
r_void
op_star
id|SC
suffix:semicolon
DECL|member|pt
r_void
op_star
id|pt
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
op_star
id|sem
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|retcode
id|u32
id|retcode
suffix:semicolon
DECL|typedef|IPS_FLASH_DATA
)brace
id|IPS_FLASH_DATA
suffix:semicolon
multiline_comment|/*&n; * Status Info&n; */
DECL|struct|ips_stat
r_typedef
r_struct
id|ips_stat
(brace
DECL|member|residue_len
id|u32
id|residue_len
suffix:semicolon
DECL|member|scb_addr
id|u32
id|scb_addr
suffix:semicolon
DECL|typedef|ips_stat_t
)brace
id|ips_stat_t
suffix:semicolon
multiline_comment|/*&n; * SCB Queue Format&n; */
DECL|struct|ips_scb_queue
r_typedef
r_struct
id|ips_scb_queue
(brace
DECL|member|head
r_struct
id|ips_scb
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|ips_scb
op_star
id|tail
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|cpu_flags
id|u32
id|cpu_flags
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|ips_scb_queue_t
)brace
id|ips_scb_queue_t
suffix:semicolon
multiline_comment|/*&n; * Wait queue_format&n; */
DECL|struct|ips_wait_queue
r_typedef
r_struct
id|ips_wait_queue
(brace
DECL|member|head
id|Scsi_Cmnd
op_star
id|head
suffix:semicolon
DECL|member|tail
id|Scsi_Cmnd
op_star
id|tail
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|cpu_flags
id|u32
id|cpu_flags
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|ips_wait_queue_t
)brace
id|ips_wait_queue_t
suffix:semicolon
DECL|struct|ips_copp_wait_item
r_typedef
r_struct
id|ips_copp_wait_item
(brace
DECL|member|scsi_cmd
id|Scsi_Cmnd
op_star
id|scsi_cmd
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
op_star
id|sem
suffix:semicolon
DECL|member|next
r_struct
id|ips_copp_wait_item
op_star
id|next
suffix:semicolon
DECL|typedef|ips_copp_wait_item_t
)brace
id|ips_copp_wait_item_t
suffix:semicolon
DECL|struct|ips_copp_queue
r_typedef
r_struct
id|ips_copp_queue
(brace
DECL|member|head
r_struct
id|ips_copp_wait_item
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|ips_copp_wait_item
op_star
id|tail
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|cpu_flags
id|u32
id|cpu_flags
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|ips_copp_queue_t
)brace
id|ips_copp_queue_t
suffix:semicolon
multiline_comment|/* forward decl for host structure */
r_struct
id|ips_ha
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|issue
r_int
(paren
op_star
id|issue
)paren
(paren
r_struct
id|ips_ha
op_star
comma
r_struct
id|ips_scb
op_star
)paren
suffix:semicolon
DECL|member|isinit
r_int
(paren
op_star
id|isinit
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|isintr
r_int
(paren
op_star
id|isintr
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|erasebios
r_int
(paren
op_star
id|erasebios
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|programbios
r_int
(paren
op_star
id|programbios
)paren
(paren
r_struct
id|ips_ha
op_star
comma
r_char
op_star
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
DECL|member|verifybios
r_int
(paren
op_star
id|verifybios
)paren
(paren
r_struct
id|ips_ha
op_star
comma
r_char
op_star
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
DECL|member|statupd
id|u32
(paren
op_star
id|statupd
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|statinit
r_void
(paren
op_star
id|statinit
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|intr
r_void
(paren
op_star
id|intr
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|member|enableint
r_void
(paren
op_star
id|enableint
)paren
(paren
r_struct
id|ips_ha
op_star
)paren
suffix:semicolon
DECL|typedef|ips_hw_func_t
)brace
id|ips_hw_func_t
suffix:semicolon
DECL|struct|ips_ha
r_typedef
r_struct
id|ips_ha
(brace
DECL|member|ha_id
id|u8
id|ha_id
(braket
id|IPS_MAX_CHANNELS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|dcdb_active
id|u32
id|dcdb_active
(braket
id|IPS_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|io_addr
id|u32
id|io_addr
suffix:semicolon
multiline_comment|/* Base I/O address           */
DECL|member|irq
id|u8
id|irq
suffix:semicolon
multiline_comment|/* IRQ for adapter            */
DECL|member|ntargets
id|u8
id|ntargets
suffix:semicolon
multiline_comment|/* Number of targets          */
DECL|member|nbus
id|u8
id|nbus
suffix:semicolon
multiline_comment|/* Number of buses            */
DECL|member|nlun
id|u8
id|nlun
suffix:semicolon
multiline_comment|/* Number of Luns             */
DECL|member|ad_type
id|u16
id|ad_type
suffix:semicolon
multiline_comment|/* Adapter type               */
DECL|member|host_num
id|u16
id|host_num
suffix:semicolon
multiline_comment|/* Adapter number             */
DECL|member|max_xfer
id|u32
id|max_xfer
suffix:semicolon
multiline_comment|/* Maximum Xfer size          */
DECL|member|max_cmds
id|u32
id|max_cmds
suffix:semicolon
multiline_comment|/* Max concurrent commands    */
DECL|member|num_ioctl
id|u32
id|num_ioctl
suffix:semicolon
multiline_comment|/* Number of Ioctls           */
DECL|member|sp
id|ips_stat_t
id|sp
suffix:semicolon
multiline_comment|/* Status packer pointer      */
DECL|member|scbs
r_struct
id|ips_scb
op_star
id|scbs
suffix:semicolon
multiline_comment|/* Array of all CCBS          */
DECL|member|scb_freelist
r_struct
id|ips_scb
op_star
id|scb_freelist
suffix:semicolon
multiline_comment|/* SCB free list              */
DECL|member|scb_waitlist
id|ips_wait_queue_t
id|scb_waitlist
suffix:semicolon
multiline_comment|/* Pending SCB list           */
DECL|member|copp_waitlist
id|ips_copp_queue_t
id|copp_waitlist
suffix:semicolon
multiline_comment|/* Pending PT list            */
DECL|member|scb_activelist
id|ips_scb_queue_t
id|scb_activelist
suffix:semicolon
multiline_comment|/* Active SCB list            */
DECL|member|dummy
id|IPS_IO_CMD
op_star
id|dummy
suffix:semicolon
multiline_comment|/* dummy command              */
DECL|member|adapt
id|IPS_ADAPTER
op_star
id|adapt
suffix:semicolon
multiline_comment|/* Adapter status area        */
DECL|member|enq
id|IPS_ENQ
op_star
id|enq
suffix:semicolon
multiline_comment|/* Adapter Enquiry data       */
DECL|member|conf
id|IPS_CONF
op_star
id|conf
suffix:semicolon
multiline_comment|/* Adapter config data        */
DECL|member|nvram
id|IPS_NVRAM_P5
op_star
id|nvram
suffix:semicolon
multiline_comment|/* NVRAM page 5 data          */
DECL|member|subsys
id|IPS_SUBSYS
op_star
id|subsys
suffix:semicolon
multiline_comment|/* Subsystem parameters       */
DECL|member|ioctl_data
r_char
op_star
id|ioctl_data
suffix:semicolon
multiline_comment|/* IOCTL data area            */
DECL|member|ioctl_datasize
id|u32
id|ioctl_datasize
suffix:semicolon
multiline_comment|/* IOCTL data size            */
DECL|member|cmd_in_progress
id|u32
id|cmd_in_progress
suffix:semicolon
multiline_comment|/* Current command in progress*/
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* HA flags                   */
DECL|member|waitflag
id|u8
id|waitflag
suffix:semicolon
multiline_comment|/* are we waiting for cmd     */
DECL|member|active
id|u8
id|active
suffix:semicolon
DECL|member|reset_count
id|u16
id|reset_count
suffix:semicolon
multiline_comment|/* number of resets           */
DECL|member|last_ffdc
id|u32
id|last_ffdc
suffix:semicolon
multiline_comment|/* last time we sent ffdc info*/
DECL|member|revision_id
id|u8
id|revision_id
suffix:semicolon
multiline_comment|/* Revision level             */
DECL|member|device_id
id|u16
id|device_id
suffix:semicolon
multiline_comment|/* PCI device ID              */
DECL|member|slot_num
id|u8
id|slot_num
suffix:semicolon
multiline_comment|/* PCI Slot Number            */
DECL|member|subdevice_id
id|u16
id|subdevice_id
suffix:semicolon
multiline_comment|/* Subsystem device ID        */
DECL|member|ioctl_order
id|u8
id|ioctl_order
suffix:semicolon
multiline_comment|/* Number of pages in ioctl   */
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
multiline_comment|/* Empty                      */
DECL|member|bios_version
id|u8
id|bios_version
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* BIOS Revision              */
DECL|member|mem_addr
id|u32
id|mem_addr
suffix:semicolon
multiline_comment|/* Memory mapped address      */
DECL|member|io_len
id|u32
id|io_len
suffix:semicolon
multiline_comment|/* Size of IO Address         */
DECL|member|mem_len
id|u32
id|mem_len
suffix:semicolon
multiline_comment|/* Size of memory address     */
DECL|member|mem_ptr
r_char
op_star
id|mem_ptr
suffix:semicolon
multiline_comment|/* Memory mapped Ptr          */
DECL|member|ioremap_ptr
r_char
op_star
id|ioremap_ptr
suffix:semicolon
multiline_comment|/* ioremapped memory pointer  */
DECL|member|func
id|ips_hw_func_t
id|func
suffix:semicolon
multiline_comment|/* hw function pointers       */
DECL|member|pcidev
r_struct
id|pci_dev
op_star
id|pcidev
suffix:semicolon
multiline_comment|/* PCI device handle          */
DECL|member|scb_lock
id|spinlock_t
id|scb_lock
suffix:semicolon
DECL|member|copp_lock
id|spinlock_t
id|copp_lock
suffix:semicolon
DECL|member|ips_lock
id|spinlock_t
id|ips_lock
suffix:semicolon
DECL|member|save_ioctl_data
r_char
op_star
id|save_ioctl_data
suffix:semicolon
multiline_comment|/* Save Area for ioctl_data   */
DECL|member|save_ioctl_order
id|u8
id|save_ioctl_order
suffix:semicolon
multiline_comment|/* Save Area for ioctl_order  */
DECL|member|save_ioctl_datasize
id|u32
id|save_ioctl_datasize
suffix:semicolon
multiline_comment|/* Save Area for ioctl_datasize */
DECL|typedef|ips_ha_t
)brace
id|ips_ha_t
suffix:semicolon
DECL|typedef|ips_scb_callback
r_typedef
r_void
(paren
op_star
id|ips_scb_callback
)paren
(paren
id|ips_ha_t
op_star
comma
r_struct
id|ips_scb
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * SCB Format&n; */
DECL|struct|ips_scb
r_typedef
r_struct
id|ips_scb
(brace
DECL|member|cmd
id|IPS_HOST_COMMAND
id|cmd
suffix:semicolon
DECL|member|dcdb
id|IPS_DCDB_TABLE
id|dcdb
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|lun
id|u8
id|lun
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|scb_busaddr
id|u32
id|scb_busaddr
suffix:semicolon
DECL|member|data_busaddr
id|u32
id|data_busaddr
suffix:semicolon
DECL|member|timeout
id|u32
id|timeout
suffix:semicolon
DECL|member|basic_status
id|u8
id|basic_status
suffix:semicolon
DECL|member|extended_status
id|u8
id|extended_status
suffix:semicolon
DECL|member|breakup
id|u8
id|breakup
suffix:semicolon
DECL|member|sg_break
id|u8
id|sg_break
suffix:semicolon
DECL|member|data_len
id|u32
id|data_len
suffix:semicolon
DECL|member|sg_len
id|u32
id|sg_len
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|op_code
id|u32
id|op_code
suffix:semicolon
DECL|member|sg_list
id|IPS_SG_LIST
op_star
id|sg_list
suffix:semicolon
DECL|member|scsi_cmd
id|Scsi_Cmnd
op_star
id|scsi_cmd
suffix:semicolon
DECL|member|q_next
r_struct
id|ips_scb
op_star
id|q_next
suffix:semicolon
DECL|member|callback
id|ips_scb_callback
id|callback
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
op_star
id|sem
suffix:semicolon
DECL|typedef|ips_scb_t
)brace
id|ips_scb_t
suffix:semicolon
DECL|struct|ips_scb_pt
r_typedef
r_struct
id|ips_scb_pt
(brace
DECL|member|cmd
id|IPS_HOST_COMMAND
id|cmd
suffix:semicolon
DECL|member|dcdb
id|IPS_DCDB_TABLE
id|dcdb
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|lun
id|u8
id|lun
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|scb_busaddr
id|u32
id|scb_busaddr
suffix:semicolon
DECL|member|data_busaddr
id|u32
id|data_busaddr
suffix:semicolon
DECL|member|timeout
id|u32
id|timeout
suffix:semicolon
DECL|member|basic_status
id|u8
id|basic_status
suffix:semicolon
DECL|member|extended_status
id|u8
id|extended_status
suffix:semicolon
DECL|member|breakup
id|u16
id|breakup
suffix:semicolon
DECL|member|data_len
id|u32
id|data_len
suffix:semicolon
DECL|member|sg_len
id|u32
id|sg_len
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|op_code
id|u32
id|op_code
suffix:semicolon
DECL|member|sg_list
id|IPS_SG_LIST
op_star
id|sg_list
suffix:semicolon
DECL|member|scsi_cmd
id|Scsi_Cmnd
op_star
id|scsi_cmd
suffix:semicolon
DECL|member|q_next
r_struct
id|ips_scb
op_star
id|q_next
suffix:semicolon
DECL|member|callback
id|ips_scb_callback
id|callback
suffix:semicolon
DECL|typedef|ips_scb_pt_t
)brace
id|ips_scb_pt_t
suffix:semicolon
multiline_comment|/*&n; * Passthru Command Format&n; */
r_typedef
r_struct
(brace
DECL|member|CoppID
id|u8
id|CoppID
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|CoppCmd
id|u32
id|CoppCmd
suffix:semicolon
DECL|member|PtBuffer
id|u32
id|PtBuffer
suffix:semicolon
DECL|member|CmdBuffer
id|u8
op_star
id|CmdBuffer
suffix:semicolon
DECL|member|CmdBSize
id|u32
id|CmdBSize
suffix:semicolon
DECL|member|CoppCP
id|ips_scb_pt_t
id|CoppCP
suffix:semicolon
DECL|member|TimeOut
id|u32
id|TimeOut
suffix:semicolon
DECL|member|BasicStatus
id|u8
id|BasicStatus
suffix:semicolon
DECL|member|ExtendedStatus
id|u8
id|ExtendedStatus
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|typedef|ips_passthru_t
)brace
id|ips_passthru_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 2&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -2&n; * c-argdecl-indent: 2&n; * c-label-offset: -2&n; * c-continued-statement-offset: 2&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
