multiline_comment|/*&n; * cpcihp_zt5550.h&n; *&n; * Intel/Ziatech ZT5550 CompactPCI Host Controller driver definitions&n; *&n; * Copyright 2002 SOMA Networks, Inc.&n; * Copyright 2001 Intel San Luis Obispo&n; * Copyright 2000,2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY &n; * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL &n; * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, &n; * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, &n; * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR &n; * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF &n; * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING &n; * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS &n; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;scottm@somanetworks.com&gt;&n; */
macro_line|#ifndef _CPCIHP_ZT5550_H
DECL|macro|_CPCIHP_ZT5550_H
mdefine_line|#define _CPCIHP_ZT5550_H
multiline_comment|/* Direct registers */
DECL|macro|CSR_HCINDEX
mdefine_line|#define CSR_HCINDEX&t;&t;0x00
DECL|macro|CSR_HCDATA
mdefine_line|#define CSR_HCDATA&t;&t;0x04
DECL|macro|CSR_INTSTAT
mdefine_line|#define CSR_INTSTAT&t;&t;0x08
DECL|macro|CSR_INTMASK
mdefine_line|#define CSR_INTMASK&t;&t;0x09
DECL|macro|CSR_CNT0CMD
mdefine_line|#define CSR_CNT0CMD&t;&t;0x0C
DECL|macro|CSR_CNT1CMD
mdefine_line|#define CSR_CNT1CMD&t;&t;0x0E
DECL|macro|CSR_CNT0
mdefine_line|#define CSR_CNT0&t;&t;0x10
DECL|macro|CSR_CNT1
mdefine_line|#define CSR_CNT1&t;&t;0x14
multiline_comment|/* Masks for interrupt bits in CSR_INTMASK direct register */
DECL|macro|CNT0_INT_MASK
mdefine_line|#define CNT0_INT_MASK&t;&t;0x01
DECL|macro|CNT1_INT_MASK
mdefine_line|#define CNT1_INT_MASK&t;&t;0x02
DECL|macro|ENUM_INT_MASK
mdefine_line|#define ENUM_INT_MASK&t;&t;0x04
DECL|macro|ALL_DIRECT_INTS_MASK
mdefine_line|#define ALL_DIRECT_INTS_MASK&t;0x07
multiline_comment|/* Indexed registers (through CSR_INDEX, CSR_DATA) */
DECL|macro|HC_INT_MASK_REG
mdefine_line|#define HC_INT_MASK_REG&t;&t;0x04
DECL|macro|HC_STATUS_REG
mdefine_line|#define HC_STATUS_REG&t;&t;0x08
DECL|macro|HC_CMD_REG
mdefine_line|#define HC_CMD_REG&t;&t;0x0C
DECL|macro|ARB_CONFIG_GNT_REG
mdefine_line|#define ARB_CONFIG_GNT_REG&t;0x10
DECL|macro|ARB_CONFIG_CFG_REG
mdefine_line|#define ARB_CONFIG_CFG_REG&t;0x12
DECL|macro|ARB_CONFIG_REG
mdefine_line|#define ARB_CONFIG_REG&t; &t;0x10
DECL|macro|ISOL_CONFIG_REG
mdefine_line|#define ISOL_CONFIG_REG&t;&t;0x18
DECL|macro|FAULT_STATUS_REG
mdefine_line|#define FAULT_STATUS_REG&t;0x20
DECL|macro|FAULT_CONFIG_REG
mdefine_line|#define FAULT_CONFIG_REG&t;0x24
DECL|macro|WD_CONFIG_REG
mdefine_line|#define WD_CONFIG_REG&t;&t;0x2C
DECL|macro|HC_DIAG_REG
mdefine_line|#define HC_DIAG_REG&t;&t;0x30
DECL|macro|SERIAL_COMM_REG
mdefine_line|#define SERIAL_COMM_REG&t;&t;0x34
DECL|macro|SERIAL_OUT_REG
mdefine_line|#define SERIAL_OUT_REG&t;&t;0x38
DECL|macro|SERIAL_IN_REG
mdefine_line|#define SERIAL_IN_REG&t;&t;0x3C
multiline_comment|/* Masks for interrupt bits in HC_INT_MASK_REG indexed register */
DECL|macro|SERIAL_INT_MASK
mdefine_line|#define SERIAL_INT_MASK&t;&t;0x01
DECL|macro|FAULT_INT_MASK
mdefine_line|#define FAULT_INT_MASK&t;&t;0x02
DECL|macro|HCF_INT_MASK
mdefine_line|#define HCF_INT_MASK&t;&t;0x04
DECL|macro|ALL_INDEXED_INTS_MASK
mdefine_line|#define ALL_INDEXED_INTS_MASK&t;0x07
multiline_comment|/* Digital I/O port storing ENUM# */
DECL|macro|ENUM_PORT
mdefine_line|#define ENUM_PORT&t;0xE1
multiline_comment|/* Mask to get to the ENUM# bit on the bus */
DECL|macro|ENUM_MASK
mdefine_line|#define ENUM_MASK&t;0x40
macro_line|#endif&t;&t;&t;&t;/* _CPCIHP_ZT5550_H */
eof
