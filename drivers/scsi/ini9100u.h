multiline_comment|/**************************************************************************&n; * Initio 9100 device driver for Linux.&n; *&n; * Copyright (c) 1994-1998 Initio Corporation&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * --------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification, immediately at the beginning of the file.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU General Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; *************************************************************************&n; *&n; * Module: ini9100u.h&n; * Description: INI-9100U/UW LINUX device driver header&n; * Revision History:&n; * 06/18/96 Harry Chen, Initial Version 1.00A (Beta)&n; * 06/23/98 hc&t;- v1.01k&n; *&t;&t;- Get it work for kernel version &gt;= 2.1.75&n; * 12/09/98 bv&t;- v1.03a&n; *&t;&t;- Removed unused code&n; * 12/13/98 bv&t;- v1.03b&n; *&t;&t;- Add spinlocks to HCS structure.&n; * 21/01/99 bv&t;- v1.03e&n; *&t;&t;- Added PCI_ID structure&n; **************************************************************************/
macro_line|#ifndef&t;CVT_LINUX_VERSION
DECL|macro|CVT_LINUX_VERSION
mdefine_line|#define&t;CVT_LINUX_VERSION(V,P,S)&t;(((V) * 65536) + ((P) * 256) + (S))
macro_line|#endif
macro_line|#ifndef&t;LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#include &quot;sd.h&quot;
r_extern
r_int
id|i91u_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i91u_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i91u_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i91u_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|i91u_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i91u_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i91u_biosparam
c_func
(paren
id|Scsi_Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*for linux v2.0 */
DECL|macro|i91u_REVID
mdefine_line|#define i91u_REVID &quot;Initio INI-9X00U/UW SCSI device driver; Revision: 1.03g&quot;
DECL|macro|INI9100U
mdefine_line|#define INI9100U&t;{ &bslash;&n;&t;next:&t;&t;NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;module:&t;&t;NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name:&t;&quot;INI9100U&quot;, &bslash;&n;&t;proc_info:&t;NULL,&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;i91u_REVID, &bslash;&n;&t;detect:&t;&t;i91u_detect, &bslash;&n;&t;release:&t;i91u_release, &bslash;&n;&t;info:&t;&t;NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;command:&t;i91u_command, &bslash;&n;&t;queuecommand:&t;i91u_queue, &bslash;&n; &t;eh_strategy_handler: NULL, &bslash;&n; &t;eh_abort_handler: NULL, &bslash;&n; &t;eh_device_reset_handler: NULL, &bslash;&n; &t;eh_bus_reset_handler: NULL, &bslash;&n; &t;eh_host_reset_handler: NULL, &bslash;&n;&t;abort:&t;&t;i91u_abort, &bslash;&n;&t;reset:&t;&t;i91u_reset, &bslash;&n;&t;slave_attach:&t;NULL, &bslash;&n;&t;bios_param:&t;i91u_biosparam, &bslash;&n;&t;can_queue:&t;1, &bslash;&n;&t;this_id:&t;1, &bslash;&n;&t;sg_tablesize:&t;SG_ALL, &bslash;&n;&t;cmd_per_lun: &t;1, &bslash;&n;&t;present:&t;0, &bslash;&n;&t;unchecked_isa_dma: 0, &bslash;&n;&t;use_clustering:&t;ENABLE_CLUSTERING, &bslash;&n; use_new_eh_code: 0 &bslash;&n;}
DECL|macro|VIRT_TO_BUS
mdefine_line|#define VIRT_TO_BUS(i)  (unsigned int) virt_to_bus((void *)(i))
DECL|macro|ULONG
mdefine_line|#define ULONG   unsigned long
DECL|macro|USHORT
mdefine_line|#define USHORT  unsigned short
DECL|macro|UCHAR
mdefine_line|#define UCHAR   unsigned char
DECL|macro|BYTE
mdefine_line|#define BYTE    unsigned char
DECL|macro|WORD
mdefine_line|#define WORD    unsigned short
DECL|macro|DWORD
mdefine_line|#define DWORD   unsigned long
DECL|macro|UBYTE
mdefine_line|#define UBYTE   unsigned char
DECL|macro|UWORD
mdefine_line|#define UWORD   unsigned short
DECL|macro|UDWORD
mdefine_line|#define UDWORD  unsigned long
macro_line|#ifdef ALPHA
DECL|macro|U32
mdefine_line|#define U32   unsigned int
macro_line|#else
DECL|macro|U32
mdefine_line|#define U32   unsigned long
macro_line|#endif
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL     0&t;&t;/* zero          */
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE     (1)&t;&t;/* boolean true  */
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE    (0)&t;&t;/* boolean false */
macro_line|#endif
macro_line|#ifndef FAILURE
DECL|macro|FAILURE
mdefine_line|#define FAILURE  (-1)
macro_line|#endif
DECL|macro|i91u_MAXQUEUE
mdefine_line|#define i91u_MAXQUEUE&t;&t;2
DECL|macro|TOTAL_SG_ENTRY
mdefine_line|#define TOTAL_SG_ENTRY&t;&t;32
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;&t;16
DECL|macro|SENSE_SIZE
mdefine_line|#define SENSE_SIZE&t;&t;14
DECL|macro|INI_VENDOR_ID
mdefine_line|#define INI_VENDOR_ID   0x1101&t;/* Initio&squot;s PCI vendor ID       */
DECL|macro|DMX_VENDOR_ID
mdefine_line|#define DMX_VENDOR_ID&t;0x134a&t;/* Domex&squot;s PCI vendor ID&t;*/
DECL|macro|I950_DEVICE_ID
mdefine_line|#define I950_DEVICE_ID&t;0x9500&t;/* Initio&squot;s inic-950 product ID   */
DECL|macro|I940_DEVICE_ID
mdefine_line|#define I940_DEVICE_ID&t;0x9400&t;/* Initio&squot;s inic-940 product ID   */
DECL|macro|I935_DEVICE_ID
mdefine_line|#define I935_DEVICE_ID&t;0x9401&t;/* Initio&squot;s inic-935 product ID   */
DECL|macro|I920_DEVICE_ID
mdefine_line|#define I920_DEVICE_ID&t;0x0002&t;/* Initio&squot;s other product ID      */
multiline_comment|/************************************************************************/
multiline_comment|/*              Vendor ID/Device ID Pair Structure&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|struct|PCI_ID_Struc
r_typedef
r_struct
id|PCI_ID_Struc
(brace
DECL|member|vendor_id
r_int
r_int
id|vendor_id
suffix:semicolon
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
DECL|typedef|PCI_ID
)brace
id|PCI_ID
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/*              Scatter-Gather Element Structure                        */
multiline_comment|/************************************************************************/
DECL|struct|SG_Struc
r_typedef
r_struct
id|SG_Struc
(brace
DECL|member|SG_Ptr
id|U32
id|SG_Ptr
suffix:semicolon
multiline_comment|/* Data Pointer */
DECL|member|SG_Len
id|U32
id|SG_Len
suffix:semicolon
multiline_comment|/* Data Length */
DECL|typedef|SG
)brace
id|SG
suffix:semicolon
multiline_comment|/***********************************************************************&n;&t;&t;SCSI Control Block&n;************************************************************************/
DECL|struct|Scsi_Ctrl_Blk
r_typedef
r_struct
id|Scsi_Ctrl_Blk
(brace
DECL|member|SCB_InitioReserved
id|U32
id|SCB_InitioReserved
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|SCB_Opcode
id|UBYTE
id|SCB_Opcode
suffix:semicolon
multiline_comment|/*24 SCB command code */
DECL|member|SCB_Flags
id|UBYTE
id|SCB_Flags
suffix:semicolon
multiline_comment|/*25 SCB Flags */
DECL|member|SCB_Target
id|UBYTE
id|SCB_Target
suffix:semicolon
multiline_comment|/*26 Target Id */
DECL|member|SCB_Lun
id|UBYTE
id|SCB_Lun
suffix:semicolon
multiline_comment|/*27 Lun */
DECL|member|SCB_BufPtr
id|U32
id|SCB_BufPtr
suffix:semicolon
multiline_comment|/*28 Data Buffer Pointer */
DECL|member|SCB_BufLen
id|U32
id|SCB_BufLen
suffix:semicolon
multiline_comment|/*2C Data Allocation Length */
DECL|member|SCB_SGLen
id|UBYTE
id|SCB_SGLen
suffix:semicolon
multiline_comment|/*30 SG list # */
DECL|member|SCB_SenseLen
id|UBYTE
id|SCB_SenseLen
suffix:semicolon
multiline_comment|/*31 Sense Allocation Length */
DECL|member|SCB_HaStat
id|UBYTE
id|SCB_HaStat
suffix:semicolon
multiline_comment|/*32 */
DECL|member|SCB_TaStat
id|UBYTE
id|SCB_TaStat
suffix:semicolon
multiline_comment|/*33 */
DECL|member|SCB_CDBLen
id|UBYTE
id|SCB_CDBLen
suffix:semicolon
multiline_comment|/*34 CDB Length */
DECL|member|SCB_Ident
id|UBYTE
id|SCB_Ident
suffix:semicolon
multiline_comment|/*35 Identify */
DECL|member|SCB_TagMsg
id|UBYTE
id|SCB_TagMsg
suffix:semicolon
multiline_comment|/*36 Tag Message */
DECL|member|SCB_TagId
id|UBYTE
id|SCB_TagId
suffix:semicolon
multiline_comment|/*37 Queue Tag */
DECL|member|SCB_CDB
id|UBYTE
id|SCB_CDB
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/*38 */
DECL|member|SCB_SGPAddr
id|U32
id|SCB_SGPAddr
suffix:semicolon
multiline_comment|/*44 SG List/Sense Buf phy. Addr. */
DECL|member|SCB_SensePtr
id|U32
id|SCB_SensePtr
suffix:semicolon
multiline_comment|/*48 Sense data pointer */
DECL|member|SCB_Post
r_void
(paren
op_star
id|SCB_Post
)paren
(paren
id|BYTE
op_star
comma
id|BYTE
op_star
)paren
suffix:semicolon
multiline_comment|/*4C POST routine */
DECL|member|SCB_Srb
id|Scsi_Cmnd
op_star
id|SCB_Srb
suffix:semicolon
multiline_comment|/*50 SRB Pointer */
DECL|member|SCB_SGList
id|SG
id|SCB_SGList
(braket
id|TOTAL_SG_ENTRY
)braket
suffix:semicolon
multiline_comment|/*54 Start of SG list */
DECL|typedef|SCB
)brace
id|SCB
suffix:semicolon
multiline_comment|/* Opcodes of SCB_Opcode */
DECL|macro|ExecSCSI
mdefine_line|#define ExecSCSI        0x1
DECL|macro|BusDevRst
mdefine_line|#define BusDevRst       0x2
DECL|macro|AbortCmd
mdefine_line|#define AbortCmd        0x3
multiline_comment|/* Bit Definition for SCB_Flags */
DECL|macro|SCF_DONE
mdefine_line|#define SCF_DONE        0x01
DECL|macro|SCF_POST
mdefine_line|#define SCF_POST        0x02
DECL|macro|SCF_SENSE
mdefine_line|#define SCF_SENSE       0x04
DECL|macro|SCF_DIR
mdefine_line|#define SCF_DIR         0x18
DECL|macro|SCF_NO_DCHK
mdefine_line|#define SCF_NO_DCHK     0x00
DECL|macro|SCF_DIN
mdefine_line|#define SCF_DIN         0x08
DECL|macro|SCF_DOUT
mdefine_line|#define SCF_DOUT        0x10
DECL|macro|SCF_NO_XF
mdefine_line|#define SCF_NO_XF       0x18
DECL|macro|SCF_POLL
mdefine_line|#define SCF_POLL        0x40
DECL|macro|SCF_SG
mdefine_line|#define SCF_SG          0x80
multiline_comment|/* Error Codes for SCB_HaStat */
DECL|macro|HOST_SEL_TOUT
mdefine_line|#define HOST_SEL_TOUT   0x11
DECL|macro|HOST_DO_DU
mdefine_line|#define HOST_DO_DU      0x12
DECL|macro|HOST_BUS_FREE
mdefine_line|#define HOST_BUS_FREE   0x13
DECL|macro|HOST_BAD_PHAS
mdefine_line|#define HOST_BAD_PHAS   0x14
DECL|macro|HOST_INV_CMD
mdefine_line|#define HOST_INV_CMD    0x16
DECL|macro|HOST_SCSI_RST
mdefine_line|#define HOST_SCSI_RST   0x1B
DECL|macro|HOST_DEV_RST
mdefine_line|#define HOST_DEV_RST    0x1C
multiline_comment|/* Error Codes for SCB_TaStat */
DECL|macro|TARGET_CHKCOND
mdefine_line|#define TARGET_CHKCOND  0x02
DECL|macro|TARGET_BUSY
mdefine_line|#define TARGET_BUSY     0x08
multiline_comment|/* Queue tag msg: Simple_quque_tag, Head_of_queue_tag, Ordered_queue_tag */
DECL|macro|MSG_STAG
mdefine_line|#define MSG_STAG        0x20
DECL|macro|MSG_HTAG
mdefine_line|#define MSG_HTAG        0x21
DECL|macro|MSG_OTAG
mdefine_line|#define MSG_OTAG        0x22
multiline_comment|/***********************************************************************&n;&t;&t;Target Device Control Structure&n;**********************************************************************/
DECL|struct|Tar_Ctrl_Struc
r_typedef
r_struct
id|Tar_Ctrl_Struc
(brace
DECL|member|TCS_InitioReserved
id|ULONG
id|TCS_InitioReserved
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|TCS_DrvFlags
id|UWORD
id|TCS_DrvFlags
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|TCS_DrvHead
id|UBYTE
id|TCS_DrvHead
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|TCS_DrvSector
id|UBYTE
id|TCS_DrvSector
suffix:semicolon
multiline_comment|/* 7 */
DECL|typedef|TCS
)brace
id|TCS
suffix:semicolon
multiline_comment|/***********************************************************************&n;&t;&t;Target Device Control Structure&n;**********************************************************************/
multiline_comment|/* Bit Definition for TCF_DrvFlags */
DECL|macro|TCF_DRV_255_63
mdefine_line|#define TCF_DRV_255_63          0x0400
multiline_comment|/***********************************************************************&n;&t;      Host Adapter Control Structure&n;************************************************************************/
DECL|struct|Ha_Ctrl_Struc
r_typedef
r_struct
id|Ha_Ctrl_Struc
(brace
DECL|member|HCS_Base
id|UWORD
id|HCS_Base
suffix:semicolon
multiline_comment|/* 00 */
DECL|member|HCS_BIOS
id|UWORD
id|HCS_BIOS
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|HCS_Intr
id|UBYTE
id|HCS_Intr
suffix:semicolon
multiline_comment|/* 04 */
DECL|member|HCS_SCSI_ID
id|UBYTE
id|HCS_SCSI_ID
suffix:semicolon
multiline_comment|/* 05 */
DECL|member|HCS_MaxTar
id|UBYTE
id|HCS_MaxTar
suffix:semicolon
multiline_comment|/* 06 */
DECL|member|HCS_NumScbs
id|UBYTE
id|HCS_NumScbs
suffix:semicolon
multiline_comment|/* 07 */
DECL|member|HCS_Flags
id|UBYTE
id|HCS_Flags
suffix:semicolon
multiline_comment|/* 08 */
DECL|member|HCS_Index
id|UBYTE
id|HCS_Index
suffix:semicolon
multiline_comment|/* 09 */
DECL|member|HCS_Reserved
id|UBYTE
id|HCS_Reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0a */
DECL|member|HCS_InitioReserved
id|ULONG
id|HCS_InitioReserved
(braket
l_int|27
)braket
suffix:semicolon
multiline_comment|/* 0C */
DECL|member|HCS_Tcs
id|TCS
id|HCS_Tcs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 78 -&gt; 16 Targets */
DECL|member|pSRB_head
id|Scsi_Cmnd
op_star
id|pSRB_head
suffix:semicolon
multiline_comment|/* SRB save queue header     */
DECL|member|pSRB_tail
id|Scsi_Cmnd
op_star
id|pSRB_tail
suffix:semicolon
multiline_comment|/* SRB save queue tail       */
DECL|member|HCS_AvailLock
id|spinlock_t
id|HCS_AvailLock
suffix:semicolon
DECL|member|HCS_SemaphLock
id|spinlock_t
id|HCS_SemaphLock
suffix:semicolon
DECL|member|pSRB_lock
id|spinlock_t
id|pSRB_lock
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|typedef|HCS
)brace
id|HCS
suffix:semicolon
multiline_comment|/* Bit Definition for HCB_Flags */
DECL|macro|HCF_EXPECT_RESET
mdefine_line|#define HCF_EXPECT_RESET        0x10
multiline_comment|/* SCSI related definition                                              */
DECL|macro|DISC_NOT_ALLOW
mdefine_line|#define DISC_NOT_ALLOW          0x80&t;/* Disconnect is not allowed    */
DECL|macro|DISC_ALLOW
mdefine_line|#define DISC_ALLOW              0xC0&t;/* Disconnect is allowed        */
eof
