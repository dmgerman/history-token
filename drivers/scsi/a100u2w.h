multiline_comment|/*&n; * Initio A100 device driver for Linux.&n; *&n; * Copyright (c) 1994-1998 Initio Corporation&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * --------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification, immediately at the beginning of the file.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU General Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
multiline_comment|/*&n; * Revision History:&n; * 06/18/98 HL, Initial production Version 1.02&n; * 12/19/98 bv, Use spinlocks for 2.1.95 and up&n; * 06/25/02 Doug Ledford &lt;dledford@redhat.com&gt;&n; *&t; - This and the i60uscsi.h file are almost identical,&n; *&t;   merged them into a single header used by both .c files.&n; */
DECL|macro|inia100_REVID
mdefine_line|#define inia100_REVID &quot;Initio INI-A100U2W SCSI device driver; Revision: 1.02d&quot;
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
DECL|macro|U32
mdefine_line|#define U32     u32
macro_line|#if 1
DECL|macro|ORC_MAXQUEUE
mdefine_line|#define ORC_MAXQUEUE&t;&t;245
DECL|macro|ORC_MAXTAGS
mdefine_line|#define ORC_MAXTAGS&t;&t;64
macro_line|#else
DECL|macro|ORC_MAXQUEUE
mdefine_line|#define ORC_MAXQUEUE&t;&t;25
DECL|macro|ORC_MAXTAGS
mdefine_line|#define ORC_MAXTAGS&t;&t;8
macro_line|#endif
DECL|macro|TOTAL_SG_ENTRY
mdefine_line|#define TOTAL_SG_ENTRY&t;&t;32
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;&t;16
DECL|macro|IMAX_CDB
mdefine_line|#define IMAX_CDB&t;&t;&t;15
DECL|macro|SENSE_SIZE
mdefine_line|#define SENSE_SIZE&t;&t;14
multiline_comment|/************************************************************************/
multiline_comment|/*              Scatter-Gather Element Structure                        */
multiline_comment|/************************************************************************/
DECL|struct|ORC_SG_Struc
r_typedef
r_struct
id|ORC_SG_Struc
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
DECL|typedef|ORC_SG
)brace
id|ORC_SG
suffix:semicolon
multiline_comment|/* SCSI related definition                                              */
DECL|macro|DISC_NOT_ALLOW
mdefine_line|#define DISC_NOT_ALLOW          0x80&t;/* Disconnect is not allowed    */
DECL|macro|DISC_ALLOW
mdefine_line|#define DISC_ALLOW              0xC0&t;/* Disconnect is allowed        */
DECL|macro|ORC_OFFSET_SCB
mdefine_line|#define ORC_OFFSET_SCB&t;&t;&t;16
DECL|macro|ORC_MAX_SCBS
mdefine_line|#define ORC_MAX_SCBS&t;&t;    250
DECL|macro|MAX_CHANNELS
mdefine_line|#define MAX_CHANNELS       2
DECL|macro|MAX_ESCB_ELE
mdefine_line|#define MAX_ESCB_ELE&t;&t;&t;&t;64
DECL|macro|TCF_DRV_255_63
mdefine_line|#define TCF_DRV_255_63     0x0400
multiline_comment|/********************************************************/
multiline_comment|/*      Orchid Host Command Set                         */
multiline_comment|/********************************************************/
DECL|macro|ORC_CMD_NOP
mdefine_line|#define ORC_CMD_NOP&t;&t;0x00&t;/* Host command - NOP             */
DECL|macro|ORC_CMD_VERSION
mdefine_line|#define ORC_CMD_VERSION&t;&t;0x01&t;/* Host command - Get F/W version */
DECL|macro|ORC_CMD_ECHO
mdefine_line|#define ORC_CMD_ECHO&t;&t;0x02&t;/* Host command - ECHO            */
DECL|macro|ORC_CMD_SET_NVM
mdefine_line|#define ORC_CMD_SET_NVM&t;&t;0x03&t;/* Host command - Set NVRAM       */
DECL|macro|ORC_CMD_GET_NVM
mdefine_line|#define ORC_CMD_GET_NVM&t;&t;0x04&t;/* Host command - Get NVRAM       */
DECL|macro|ORC_CMD_GET_BUS_STATUS
mdefine_line|#define ORC_CMD_GET_BUS_STATUS&t;0x05&t;/* Host command - Get SCSI bus status */
DECL|macro|ORC_CMD_ABORT_SCB
mdefine_line|#define ORC_CMD_ABORT_SCB&t;0x06&t;/* Host command - Abort SCB       */
DECL|macro|ORC_CMD_ISSUE_SCB
mdefine_line|#define ORC_CMD_ISSUE_SCB&t;0x07&t;/* Host command - Issue SCB       */
multiline_comment|/********************************************************/
multiline_comment|/*              Orchid Register Set                     */
multiline_comment|/********************************************************/
DECL|macro|ORC_GINTS
mdefine_line|#define ORC_GINTS&t;0xA0&t;/* Global Interrupt Status        */
DECL|macro|QINT
mdefine_line|#define QINT&t;&t;0x04&t;/* Reply Queue Interrupt  */
DECL|macro|ORC_GIMSK
mdefine_line|#define ORC_GIMSK&t;0xA1&t;/* Global Interrupt MASK  */
DECL|macro|MQINT
mdefine_line|#define MQINT&t;&t;0x04&t;/* Mask Reply Queue Interrupt     */
DECL|macro|ORC_GCFG
mdefine_line|#define&t;ORC_GCFG&t;0xA2&t;/* Global Configure               */
DECL|macro|EEPRG
mdefine_line|#define EEPRG&t;&t;0x01&t;/* Enable EEPROM programming */
DECL|macro|ORC_GSTAT
mdefine_line|#define&t;ORC_GSTAT&t;0xA3&t;/* Global status          */
DECL|macro|WIDEBUS
mdefine_line|#define WIDEBUS&t;&t;0x10&t;/* Wide SCSI Devices connected    */
DECL|macro|ORC_HDATA
mdefine_line|#define ORC_HDATA&t;0xA4&t;/* Host Data                      */
DECL|macro|ORC_HCTRL
mdefine_line|#define ORC_HCTRL&t;0xA5&t;/* Host Control                   */
DECL|macro|SCSIRST
mdefine_line|#define SCSIRST&t;&t;0x80&t;/* SCSI bus reset         */
DECL|macro|HDO
mdefine_line|#define HDO&t;&t;&t;0x40&t;/* Host data out          */
DECL|macro|HOSTSTOP
mdefine_line|#define HOSTSTOP&t;&t;0x02&t;/* Host stop RISC engine  */
DECL|macro|DEVRST
mdefine_line|#define DEVRST&t;&t;0x01&t;/* Device reset                   */
DECL|macro|ORC_HSTUS
mdefine_line|#define ORC_HSTUS&t;0xA6&t;/* Host Status                    */
DECL|macro|HDI
mdefine_line|#define HDI&t;&t;&t;0x02&t;/* Host data in                   */
DECL|macro|RREADY
mdefine_line|#define RREADY&t;&t;0x01&t;/* RISC engine is ready to receive */
DECL|macro|ORC_NVRAM
mdefine_line|#define&t;ORC_NVRAM&t;0xA7&t;/* Nvram port address             */
DECL|macro|SE2CS
mdefine_line|#define SE2CS&t;&t;0x008
DECL|macro|SE2CLK
mdefine_line|#define SE2CLK&t;&t;0x004
DECL|macro|SE2DO
mdefine_line|#define SE2DO&t;&t;0x002
DECL|macro|SE2DI
mdefine_line|#define SE2DI&t;&t;0x001
DECL|macro|ORC_PQUEUE
mdefine_line|#define ORC_PQUEUE&t;0xA8&t;/* Posting queue FIFO             */
DECL|macro|ORC_PQCNT
mdefine_line|#define ORC_PQCNT&t;0xA9&t;/* Posting queue FIFO Cnt */
DECL|macro|ORC_RQUEUE
mdefine_line|#define ORC_RQUEUE&t;0xAA&t;/* Reply queue FIFO               */
DECL|macro|ORC_RQUEUECNT
mdefine_line|#define ORC_RQUEUECNT&t;0xAB&t;/* Reply queue FIFO Cnt           */
DECL|macro|ORC_FWBASEADR
mdefine_line|#define&t;ORC_FWBASEADR&t;0xAC&t;/* Firmware base address  */
DECL|macro|ORC_EBIOSADR0
mdefine_line|#define&t;ORC_EBIOSADR0 0xB0&t;/* External Bios address */
DECL|macro|ORC_EBIOSADR1
mdefine_line|#define&t;ORC_EBIOSADR1 0xB1&t;/* External Bios address */
DECL|macro|ORC_EBIOSADR2
mdefine_line|#define&t;ORC_EBIOSADR2 0xB2&t;/* External Bios address */
DECL|macro|ORC_EBIOSDATA
mdefine_line|#define&t;ORC_EBIOSDATA 0xB3&t;/* External Bios address */
DECL|macro|ORC_SCBSIZE
mdefine_line|#define&t;ORC_SCBSIZE&t;0xB7&t;/* SCB size register              */
DECL|macro|ORC_SCBBASE0
mdefine_line|#define&t;ORC_SCBBASE0&t;0xB8&t;/* SCB base address 0             */
DECL|macro|ORC_SCBBASE1
mdefine_line|#define&t;ORC_SCBBASE1&t;0xBC&t;/* SCB base address 1             */
DECL|macro|ORC_RISCCTL
mdefine_line|#define&t;ORC_RISCCTL&t;0xE0&t;/* RISC Control                   */
DECL|macro|PRGMRST
mdefine_line|#define PRGMRST&t;&t;0x002
DECL|macro|DOWNLOAD
mdefine_line|#define DOWNLOAD&t;&t;0x001
DECL|macro|ORC_PRGMCTR0
mdefine_line|#define&t;ORC_PRGMCTR0&t;0xE2&t;/* RISC program counter           */
DECL|macro|ORC_PRGMCTR1
mdefine_line|#define&t;ORC_PRGMCTR1&t;0xE3&t;/* RISC program counter           */
DECL|macro|ORC_RISCRAM
mdefine_line|#define&t;ORC_RISCRAM&t;0xEC&t;/* RISC RAM data port 4 bytes     */
DECL|struct|orc_extended_scb
r_typedef
r_struct
id|orc_extended_scb
(brace
multiline_comment|/* Extended SCB                 */
DECL|member|ESCB_SGList
id|ORC_SG
id|ESCB_SGList
(braket
id|TOTAL_SG_ENTRY
)braket
suffix:semicolon
multiline_comment|/*0 Start of SG list              */
DECL|member|SCB_Srb
r_struct
id|scsi_cmnd
op_star
id|SCB_Srb
suffix:semicolon
multiline_comment|/*50 SRB Pointer */
DECL|typedef|ESCB
)brace
id|ESCB
suffix:semicolon
multiline_comment|/***********************************************************************&n;&t;&t;SCSI Control Block&n;************************************************************************/
DECL|struct|orc_scb
r_typedef
r_struct
id|orc_scb
(brace
multiline_comment|/* Scsi_Ctrl_Blk                */
DECL|member|SCB_Opcode
id|UBYTE
id|SCB_Opcode
suffix:semicolon
multiline_comment|/*00 SCB command code&amp;residual  */
DECL|member|SCB_Flags
id|UBYTE
id|SCB_Flags
suffix:semicolon
multiline_comment|/*01 SCB Flags                  */
DECL|member|SCB_Target
id|UBYTE
id|SCB_Target
suffix:semicolon
multiline_comment|/*02 Target Id                  */
DECL|member|SCB_Lun
id|UBYTE
id|SCB_Lun
suffix:semicolon
multiline_comment|/*03 Lun                        */
DECL|member|SCB_Reserved0
id|U32
id|SCB_Reserved0
suffix:semicolon
multiline_comment|/*04 Reserved for ORCHID must 0 */
DECL|member|SCB_XferLen
id|U32
id|SCB_XferLen
suffix:semicolon
multiline_comment|/*08 Data Transfer Length       */
DECL|member|SCB_Reserved1
id|U32
id|SCB_Reserved1
suffix:semicolon
multiline_comment|/*0C Reserved for ORCHID must 0 */
DECL|member|SCB_SGLen
id|U32
id|SCB_SGLen
suffix:semicolon
multiline_comment|/*10 SG list # * 8              */
DECL|member|SCB_SGPAddr
id|U32
id|SCB_SGPAddr
suffix:semicolon
multiline_comment|/*14 SG List Buf physical Addr  */
DECL|member|SCB_SGPAddrHigh
id|U32
id|SCB_SGPAddrHigh
suffix:semicolon
multiline_comment|/*18 SG Buffer high physical Addr */
DECL|member|SCB_HaStat
id|UBYTE
id|SCB_HaStat
suffix:semicolon
multiline_comment|/*1C Host Status                */
DECL|member|SCB_TaStat
id|UBYTE
id|SCB_TaStat
suffix:semicolon
multiline_comment|/*1D Target Status              */
DECL|member|SCB_Status
id|UBYTE
id|SCB_Status
suffix:semicolon
multiline_comment|/*1E SCB status                 */
DECL|member|SCB_Link
id|UBYTE
id|SCB_Link
suffix:semicolon
multiline_comment|/*1F Link pointer, default 0xFF */
DECL|member|SCB_SenseLen
id|UBYTE
id|SCB_SenseLen
suffix:semicolon
multiline_comment|/*20 Sense Allocation Length    */
DECL|member|SCB_CDBLen
id|UBYTE
id|SCB_CDBLen
suffix:semicolon
multiline_comment|/*21 CDB Length                 */
DECL|member|SCB_Ident
id|UBYTE
id|SCB_Ident
suffix:semicolon
multiline_comment|/*22 Identify                   */
DECL|member|SCB_TagMsg
id|UBYTE
id|SCB_TagMsg
suffix:semicolon
multiline_comment|/*23 Tag Message                */
DECL|member|SCB_CDB
id|UBYTE
id|SCB_CDB
(braket
id|IMAX_CDB
)braket
suffix:semicolon
multiline_comment|/*24 SCSI CDBs                  */
DECL|member|SCB_ScbIdx
id|UBYTE
id|SCB_ScbIdx
suffix:semicolon
multiline_comment|/*3C Index for this ORCSCB      */
DECL|member|SCB_SensePAddr
id|U32
id|SCB_SensePAddr
suffix:semicolon
multiline_comment|/*34 Sense Buffer physical Addr */
DECL|member|SCB_EScb
id|ESCB
op_star
id|SCB_EScb
suffix:semicolon
multiline_comment|/*38 Extended SCB Pointer       */
macro_line|#ifndef ALPHA
DECL|member|SCB_Reserved2
id|UBYTE
id|SCB_Reserved2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/*3E Reserved for Driver use    */
macro_line|#endif
DECL|typedef|ORC_SCB
)brace
id|ORC_SCB
suffix:semicolon
multiline_comment|/* Opcodes of ORCSCB_Opcode */
DECL|macro|ORC_EXECSCSI
mdefine_line|#define ORC_EXECSCSI&t;0x00&t;/* SCSI initiator command with residual */
DECL|macro|ORC_BUSDEVRST
mdefine_line|#define ORC_BUSDEVRST&t;0x01&t;/* SCSI Bus Device Reset  */
multiline_comment|/* Status of ORCSCB_Status */
DECL|macro|ORCSCB_COMPLETE
mdefine_line|#define ORCSCB_COMPLETE&t;0x00&t;/* SCB request completed  */
DECL|macro|ORCSCB_POST
mdefine_line|#define ORCSCB_POST&t;0x01&t;/* SCB is posted by the HOST      */
multiline_comment|/* Bit Definition for ORCSCB_Flags */
DECL|macro|SCF_DISINT
mdefine_line|#define SCF_DISINT&t;0x01&t;/* Disable HOST interrupt */
DECL|macro|SCF_DIR
mdefine_line|#define SCF_DIR&t;&t;0x18&t;/* Direction bits         */
DECL|macro|SCF_NO_DCHK
mdefine_line|#define SCF_NO_DCHK&t;0x00&t;/* Direction determined by SCSI   */
DECL|macro|SCF_DIN
mdefine_line|#define SCF_DIN&t;&t;0x08&t;/* From Target to Initiator       */
DECL|macro|SCF_DOUT
mdefine_line|#define SCF_DOUT&t;0x10&t;/* From Initiator to Target       */
DECL|macro|SCF_NO_XF
mdefine_line|#define SCF_NO_XF&t;0x18&t;/* No data transfer               */
DECL|macro|SCF_POLL
mdefine_line|#define SCF_POLL   0x40
multiline_comment|/* Error Codes for ORCSCB_HaStat */
DECL|macro|HOST_SEL_TOUT
mdefine_line|#define HOST_SEL_TOUT&t;0x11
DECL|macro|HOST_DO_DU
mdefine_line|#define HOST_DO_DU&t;0x12
DECL|macro|HOST_BUS_FREE
mdefine_line|#define HOST_BUS_FREE&t;0x13
DECL|macro|HOST_BAD_PHAS
mdefine_line|#define HOST_BAD_PHAS&t;0x14
DECL|macro|HOST_INV_CMD
mdefine_line|#define HOST_INV_CMD&t;0x16
DECL|macro|HOST_SCSI_RST
mdefine_line|#define HOST_SCSI_RST&t;0x1B
DECL|macro|HOST_DEV_RST
mdefine_line|#define HOST_DEV_RST&t;0x1C
multiline_comment|/* Error Codes for ORCSCB_TaStat */
DECL|macro|TARGET_CHK_COND
mdefine_line|#define TARGET_CHK_COND&t;0x02
DECL|macro|TARGET_BUSY
mdefine_line|#define TARGET_BUSY&t;0x08
DECL|macro|TARGET_TAG_FULL
mdefine_line|#define TARGET_TAG_FULL&t;0x28
multiline_comment|/***********************************************************************&n;&t;&t;Target Device Control Structure&n;**********************************************************************/
DECL|struct|ORC_Tar_Ctrl_Struc
r_typedef
r_struct
id|ORC_Tar_Ctrl_Struc
(brace
DECL|member|TCS_DrvDASD
id|UBYTE
id|TCS_DrvDASD
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|TCS_DrvSCSI
id|UBYTE
id|TCS_DrvSCSI
suffix:semicolon
multiline_comment|/* 7 */
DECL|member|TCS_DrvHead
id|UBYTE
id|TCS_DrvHead
suffix:semicolon
multiline_comment|/* 8 */
DECL|member|TCS_DrvFlags
id|UWORD
id|TCS_DrvFlags
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|TCS_DrvSector
id|UBYTE
id|TCS_DrvSector
suffix:semicolon
multiline_comment|/* 7 */
DECL|typedef|ORC_TCS
)brace
id|ORC_TCS
suffix:semicolon
multiline_comment|/* Bit Definition for TCF_DrvFlags */
DECL|macro|TCS_DF_NODASD_SUPT
mdefine_line|#define&t;TCS_DF_NODASD_SUPT&t;0x20&t;/* Suppress OS/2 DASD Mgr support */
DECL|macro|TCS_DF_NOSCSI_SUPT
mdefine_line|#define&t;TCS_DF_NOSCSI_SUPT&t;0x40&t;/* Suppress OS/2 SCSI Mgr support */
multiline_comment|/***********************************************************************&n;              Host Adapter Control Structure&n;************************************************************************/
DECL|struct|ORC_Ha_Ctrl_Struc
r_typedef
r_struct
id|ORC_Ha_Ctrl_Struc
(brace
DECL|member|HCS_Base
id|USHORT
id|HCS_Base
suffix:semicolon
multiline_comment|/* 00 */
DECL|member|HCS_Index
id|UBYTE
id|HCS_Index
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
multiline_comment|/* 06    H/A SCSI ID */
DECL|member|HCS_BIOS
id|UBYTE
id|HCS_BIOS
suffix:semicolon
multiline_comment|/* 07    BIOS configuration */
DECL|member|HCS_Flags
id|UBYTE
id|HCS_Flags
suffix:semicolon
multiline_comment|/* 0B */
DECL|member|HCS_HAConfig1
id|UBYTE
id|HCS_HAConfig1
suffix:semicolon
multiline_comment|/* 1B    SCSI0MAXTags */
DECL|member|HCS_MaxTar
id|UBYTE
id|HCS_MaxTar
suffix:semicolon
multiline_comment|/* 1B    SCSI0MAXTags */
DECL|member|HCS_Units
id|USHORT
id|HCS_Units
suffix:semicolon
multiline_comment|/* Number of units this adapter  */
DECL|member|HCS_AFlags
id|USHORT
id|HCS_AFlags
suffix:semicolon
multiline_comment|/* Adapter info. defined flags   */
DECL|member|HCS_Timeout
id|ULONG
id|HCS_Timeout
suffix:semicolon
multiline_comment|/* Adapter timeout value   */
DECL|member|HCS_virScbArray
id|ORC_SCB
op_star
id|HCS_virScbArray
suffix:semicolon
multiline_comment|/* 28 Virtual Pointer to SCB array */
DECL|member|HCS_physScbArray
id|dma_addr_t
id|HCS_physScbArray
suffix:semicolon
multiline_comment|/* Scb Physical address */
DECL|member|HCS_virEscbArray
id|ESCB
op_star
id|HCS_virEscbArray
suffix:semicolon
multiline_comment|/* Virtual pointer to ESCB Scatter list */
DECL|member|HCS_physEscbArray
id|dma_addr_t
id|HCS_physEscbArray
suffix:semicolon
multiline_comment|/* scatter list Physical address */
DECL|member|TargetFlag
id|UBYTE
id|TargetFlag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 30  target configuration, TCF_EN_TAG */
DECL|member|MaximumTags
id|UBYTE
id|MaximumTags
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 40  ORC_MAX_SCBS */
DECL|member|ActiveTags
id|UBYTE
id|ActiveTags
(braket
l_int|16
)braket
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 50 */
DECL|member|HCS_Tcs
id|ORC_TCS
id|HCS_Tcs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|BitAllocFlag
id|U32
id|BitAllocFlag
(braket
id|MAX_CHANNELS
)braket
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Max STB is 256, So 256/32 */
DECL|member|BitAllocFlagLock
id|spinlock_t
id|BitAllocFlagLock
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|typedef|ORC_HCS
)brace
id|ORC_HCS
suffix:semicolon
multiline_comment|/* Bit Definition for HCS_Flags */
DECL|macro|HCF_SCSI_RESET
mdefine_line|#define HCF_SCSI_RESET&t;0x01&t;/* SCSI BUS RESET         */
DECL|macro|HCF_PARITY
mdefine_line|#define HCF_PARITY    &t;0x02&t;/* parity card                    */
DECL|macro|HCF_LVDS
mdefine_line|#define HCF_LVDS     &t;0x10&t;/* parity card                    */
multiline_comment|/* Bit Definition for TargetFlag */
DECL|macro|TCF_EN_255
mdefine_line|#define TCF_EN_255&t;    0x08
DECL|macro|TCF_EN_TAG
mdefine_line|#define TCF_EN_TAG&t;    0x10
DECL|macro|TCF_BUSY
mdefine_line|#define TCF_BUSY&t;      0x20
DECL|macro|TCF_DISCONNECT
mdefine_line|#define TCF_DISCONNECT&t;0x40
DECL|macro|TCF_SPIN_UP
mdefine_line|#define TCF_SPIN_UP&t;  0x80
multiline_comment|/* Bit Definition for HCS_AFlags */
DECL|macro|HCS_AF_IGNORE
mdefine_line|#define&t;HCS_AF_IGNORE&t;&t;0x01&t;/* Adapter ignore         */
DECL|macro|HCS_AF_DISABLE_RESET
mdefine_line|#define&t;HCS_AF_DISABLE_RESET&t;0x10&t;/* Adapter disable reset  */
DECL|macro|HCS_AF_DISABLE_ADPT
mdefine_line|#define&t;HCS_AF_DISABLE_ADPT&t;0x80&t;/* Adapter disable                */
DECL|struct|_NVRAM
r_typedef
r_struct
id|_NVRAM
(brace
multiline_comment|/*----------header ---------------*/
DECL|member|SubVendorID0
id|UCHAR
id|SubVendorID0
suffix:semicolon
multiline_comment|/* 00 - Sub Vendor ID           */
DECL|member|SubVendorID1
id|UCHAR
id|SubVendorID1
suffix:semicolon
multiline_comment|/* 00 - Sub Vendor ID           */
DECL|member|SubSysID0
id|UCHAR
id|SubSysID0
suffix:semicolon
multiline_comment|/* 02 - Sub System ID           */
DECL|member|SubSysID1
id|UCHAR
id|SubSysID1
suffix:semicolon
multiline_comment|/* 02 - Sub System ID           */
DECL|member|SubClass
id|UCHAR
id|SubClass
suffix:semicolon
multiline_comment|/* 04 - Sub Class               */
DECL|member|VendorID0
id|UCHAR
id|VendorID0
suffix:semicolon
multiline_comment|/* 05 - Vendor ID               */
DECL|member|VendorID1
id|UCHAR
id|VendorID1
suffix:semicolon
multiline_comment|/* 05 - Vendor ID               */
DECL|member|DeviceID0
id|UCHAR
id|DeviceID0
suffix:semicolon
multiline_comment|/* 07 - Device ID               */
DECL|member|DeviceID1
id|UCHAR
id|DeviceID1
suffix:semicolon
multiline_comment|/* 07 - Device ID               */
DECL|member|Reserved0
id|UCHAR
id|Reserved0
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 09 - Reserved                */
DECL|member|Revision
id|UCHAR
id|Revision
suffix:semicolon
multiline_comment|/* 0B - Revision of data structure */
multiline_comment|/* ----Host Adapter Structure ---- */
DECL|member|NumOfCh
id|UCHAR
id|NumOfCh
suffix:semicolon
multiline_comment|/* 0C - Number of SCSI channel  */
DECL|member|BIOSConfig1
id|UCHAR
id|BIOSConfig1
suffix:semicolon
multiline_comment|/* 0D - BIOS configuration 1    */
DECL|member|BIOSConfig2
id|UCHAR
id|BIOSConfig2
suffix:semicolon
multiline_comment|/* 0E - BIOS boot channel&amp;target ID */
DECL|member|BIOSConfig3
id|UCHAR
id|BIOSConfig3
suffix:semicolon
multiline_comment|/* 0F - BIOS configuration 3    */
multiline_comment|/* ----SCSI channel Structure ---- */
multiline_comment|/* from &quot;CTRL-I SCSI Host Adapter SetUp menu &quot;  */
DECL|member|SCSI0Id
id|UCHAR
id|SCSI0Id
suffix:semicolon
multiline_comment|/* 10 - Channel 0 SCSI ID       */
DECL|member|SCSI0Config
id|UCHAR
id|SCSI0Config
suffix:semicolon
multiline_comment|/* 11 - Channel 0 SCSI configuration */
DECL|member|SCSI0MaxTags
id|UCHAR
id|SCSI0MaxTags
suffix:semicolon
multiline_comment|/* 12 - Channel 0 Maximum tags  */
DECL|member|SCSI0ResetTime
id|UCHAR
id|SCSI0ResetTime
suffix:semicolon
multiline_comment|/* 13 - Channel 0 Reset recovering time */
DECL|member|ReservedforChannel0
id|UCHAR
id|ReservedforChannel0
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 14 - Reserved                */
multiline_comment|/* ----SCSI target Structure ----  */
multiline_comment|/* from &quot;CTRL-I SCSI device SetUp menu &quot;                        */
DECL|member|Target00Config
id|UCHAR
id|Target00Config
suffix:semicolon
multiline_comment|/* 16 - Channel 0 Target 0 config */
DECL|member|Target01Config
id|UCHAR
id|Target01Config
suffix:semicolon
multiline_comment|/* 17 - Channel 0 Target 1 config */
DECL|member|Target02Config
id|UCHAR
id|Target02Config
suffix:semicolon
multiline_comment|/* 18 - Channel 0 Target 2 config */
DECL|member|Target03Config
id|UCHAR
id|Target03Config
suffix:semicolon
multiline_comment|/* 19 - Channel 0 Target 3 config */
DECL|member|Target04Config
id|UCHAR
id|Target04Config
suffix:semicolon
multiline_comment|/* 1A - Channel 0 Target 4 config */
DECL|member|Target05Config
id|UCHAR
id|Target05Config
suffix:semicolon
multiline_comment|/* 1B - Channel 0 Target 5 config */
DECL|member|Target06Config
id|UCHAR
id|Target06Config
suffix:semicolon
multiline_comment|/* 1C - Channel 0 Target 6 config */
DECL|member|Target07Config
id|UCHAR
id|Target07Config
suffix:semicolon
multiline_comment|/* 1D - Channel 0 Target 7 config */
DECL|member|Target08Config
id|UCHAR
id|Target08Config
suffix:semicolon
multiline_comment|/* 1E - Channel 0 Target 8 config */
DECL|member|Target09Config
id|UCHAR
id|Target09Config
suffix:semicolon
multiline_comment|/* 1F - Channel 0 Target 9 config */
DECL|member|Target0AConfig
id|UCHAR
id|Target0AConfig
suffix:semicolon
multiline_comment|/* 20 - Channel 0 Target A config */
DECL|member|Target0BConfig
id|UCHAR
id|Target0BConfig
suffix:semicolon
multiline_comment|/* 21 - Channel 0 Target B config */
DECL|member|Target0CConfig
id|UCHAR
id|Target0CConfig
suffix:semicolon
multiline_comment|/* 22 - Channel 0 Target C config */
DECL|member|Target0DConfig
id|UCHAR
id|Target0DConfig
suffix:semicolon
multiline_comment|/* 23 - Channel 0 Target D config */
DECL|member|Target0EConfig
id|UCHAR
id|Target0EConfig
suffix:semicolon
multiline_comment|/* 24 - Channel 0 Target E config */
DECL|member|Target0FConfig
id|UCHAR
id|Target0FConfig
suffix:semicolon
multiline_comment|/* 25 - Channel 0 Target F config */
DECL|member|SCSI1Id
id|UCHAR
id|SCSI1Id
suffix:semicolon
multiline_comment|/* 26 - Channel 1 SCSI ID       */
DECL|member|SCSI1Config
id|UCHAR
id|SCSI1Config
suffix:semicolon
multiline_comment|/* 27 - Channel 1 SCSI configuration */
DECL|member|SCSI1MaxTags
id|UCHAR
id|SCSI1MaxTags
suffix:semicolon
multiline_comment|/* 28 - Channel 1 Maximum tags  */
DECL|member|SCSI1ResetTime
id|UCHAR
id|SCSI1ResetTime
suffix:semicolon
multiline_comment|/* 29 - Channel 1 Reset recovering time */
DECL|member|ReservedforChannel1
id|UCHAR
id|ReservedforChannel1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 2A - Reserved                */
multiline_comment|/* ----SCSI target Structure ----  */
multiline_comment|/* from &quot;CTRL-I SCSI device SetUp menu &quot;                                          */
DECL|member|Target10Config
id|UCHAR
id|Target10Config
suffix:semicolon
multiline_comment|/* 2C - Channel 1 Target 0 config */
DECL|member|Target11Config
id|UCHAR
id|Target11Config
suffix:semicolon
multiline_comment|/* 2D - Channel 1 Target 1 config */
DECL|member|Target12Config
id|UCHAR
id|Target12Config
suffix:semicolon
multiline_comment|/* 2E - Channel 1 Target 2 config */
DECL|member|Target13Config
id|UCHAR
id|Target13Config
suffix:semicolon
multiline_comment|/* 2F - Channel 1 Target 3 config */
DECL|member|Target14Config
id|UCHAR
id|Target14Config
suffix:semicolon
multiline_comment|/* 30 - Channel 1 Target 4 config */
DECL|member|Target15Config
id|UCHAR
id|Target15Config
suffix:semicolon
multiline_comment|/* 31 - Channel 1 Target 5 config */
DECL|member|Target16Config
id|UCHAR
id|Target16Config
suffix:semicolon
multiline_comment|/* 32 - Channel 1 Target 6 config */
DECL|member|Target17Config
id|UCHAR
id|Target17Config
suffix:semicolon
multiline_comment|/* 33 - Channel 1 Target 7 config */
DECL|member|Target18Config
id|UCHAR
id|Target18Config
suffix:semicolon
multiline_comment|/* 34 - Channel 1 Target 8 config */
DECL|member|Target19Config
id|UCHAR
id|Target19Config
suffix:semicolon
multiline_comment|/* 35 - Channel 1 Target 9 config */
DECL|member|Target1AConfig
id|UCHAR
id|Target1AConfig
suffix:semicolon
multiline_comment|/* 36 - Channel 1 Target A config */
DECL|member|Target1BConfig
id|UCHAR
id|Target1BConfig
suffix:semicolon
multiline_comment|/* 37 - Channel 1 Target B config */
DECL|member|Target1CConfig
id|UCHAR
id|Target1CConfig
suffix:semicolon
multiline_comment|/* 38 - Channel 1 Target C config */
DECL|member|Target1DConfig
id|UCHAR
id|Target1DConfig
suffix:semicolon
multiline_comment|/* 39 - Channel 1 Target D config */
DECL|member|Target1EConfig
id|UCHAR
id|Target1EConfig
suffix:semicolon
multiline_comment|/* 3A - Channel 1 Target E config */
DECL|member|Target1FConfig
id|UCHAR
id|Target1FConfig
suffix:semicolon
multiline_comment|/* 3B - Channel 1 Target F config */
DECL|member|reserved
id|UCHAR
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 3C - Reserved                */
multiline_comment|/* ---------- CheckSum ----------       */
DECL|member|CheckSum
id|UCHAR
id|CheckSum
suffix:semicolon
multiline_comment|/* 3F - Checksum of NVRam       */
DECL|typedef|NVRAM
DECL|typedef|PNVRAM
)brace
id|NVRAM
comma
op_star
id|PNVRAM
suffix:semicolon
multiline_comment|/* Bios Configuration for nvram-&gt;BIOSConfig1                            */
DECL|macro|NBC_BIOSENABLE
mdefine_line|#define NBC_BIOSENABLE  0x01    /* BIOS enable                    */
DECL|macro|NBC_CDROM
mdefine_line|#define NBC_CDROM       0x02    /* Support bootable CDROM */
DECL|macro|NBC_REMOVABLE
mdefine_line|#define NBC_REMOVABLE   0x04    /* Support removable drive        */
multiline_comment|/* Bios Configuration for nvram-&gt;BIOSConfig2                            */
DECL|macro|NBB_TARGET_MASK
mdefine_line|#define NBB_TARGET_MASK 0x0F    /* Boot SCSI target ID number     */
DECL|macro|NBB_CHANL_MASK
mdefine_line|#define NBB_CHANL_MASK  0xF0    /* Boot SCSI channel number       */
multiline_comment|/* Bit definition for nvram-&gt;SCSIConfig                                 */
DECL|macro|NCC_BUSRESET
mdefine_line|#define NCC_BUSRESET    0x01    /* Reset SCSI bus at power up     */
DECL|macro|NCC_PARITYCHK
mdefine_line|#define NCC_PARITYCHK   0x02    /* SCSI parity enable             */
DECL|macro|NCC_LVDS
mdefine_line|#define NCC_LVDS        0x10    /* Enable LVDS                    */
DECL|macro|NCC_ACTTERM1
mdefine_line|#define NCC_ACTTERM1    0x20    /* Enable active terminator 1     */
DECL|macro|NCC_ACTTERM2
mdefine_line|#define NCC_ACTTERM2    0x40    /* Enable active terminator 2     */
DECL|macro|NCC_AUTOTERM
mdefine_line|#define NCC_AUTOTERM    0x80    /* Enable auto termination        */
multiline_comment|/* Bit definition for nvram-&gt;TargetxConfig                              */
DECL|macro|NTC_PERIOD
mdefine_line|#define NTC_PERIOD      0x07    /* Maximum Sync. Speed            */
DECL|macro|NTC_1GIGA
mdefine_line|#define NTC_1GIGA       0x08    /* 255 head / 63 sectors (64/32) */
DECL|macro|NTC_NO_SYNC
mdefine_line|#define NTC_NO_SYNC     0x10    /* NO SYNC. NEGO          */
DECL|macro|NTC_NO_WIDESYNC
mdefine_line|#define NTC_NO_WIDESYNC 0x20    /* NO WIDE SYNC. NEGO             */
DECL|macro|NTC_DISC_ENABLE
mdefine_line|#define NTC_DISC_ENABLE 0x40    /* Enable SCSI disconnect */
DECL|macro|NTC_SPINUP
mdefine_line|#define NTC_SPINUP      0x80    /* Start disk drive               */
multiline_comment|/* Default NVRam values                                                 */
DECL|macro|NBC_DEFAULT
mdefine_line|#define NBC_DEFAULT     (NBC_ENABLE)
DECL|macro|NCC_DEFAULT
mdefine_line|#define NCC_DEFAULT     (NCC_BUSRESET | NCC_AUTOTERM | NCC_PARITYCHK)
DECL|macro|NCC_MAX_TAGS
mdefine_line|#define NCC_MAX_TAGS    0x20    /* Maximum tags per target        */
DECL|macro|NCC_RESET_TIME
mdefine_line|#define NCC_RESET_TIME  0x0A    /* SCSI RESET recovering time     */
DECL|macro|NTC_DEFAULT
mdefine_line|#define NTC_DEFAULT     (NTC_1GIGA | NTC_NO_WIDESYNC | NTC_DISC_ENABLE)
DECL|macro|ORC_RD
mdefine_line|#define ORC_RD(x,y)             (UCHAR)(inb(  (int)((ULONG)((ULONG)x+(UCHAR)y)) ))
DECL|macro|ORC_RDWORD
mdefine_line|#define ORC_RDWORD(x,y)         (short)(inl((int)((ULONG)((ULONG)x+(UCHAR)y)) ))
DECL|macro|ORC_RDLONG
mdefine_line|#define ORC_RDLONG(x,y)         (long)(inl((int)((ULONG)((ULONG)x+(UCHAR)y)) ))
DECL|macro|ORC_WR
mdefine_line|#define ORC_WR(     adr,data)   outb( (UCHAR)(data), (int)(adr))
DECL|macro|ORC_WRSHORT
mdefine_line|#define ORC_WRSHORT(adr,data)   outw( (UWORD)(data), (int)(adr))
DECL|macro|ORC_WRLONG
mdefine_line|#define ORC_WRLONG( adr,data)   outl( (ULONG)(data), (int)(adr))
eof
