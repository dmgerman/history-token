multiline_comment|/******************************************************************************&n; *                  QLOGIC LINUX SOFTWARE&n; *&n; * QLogic ISP2x00 device driver for Linux 2.6.x&n; * Copyright (C) 2003-2004 QLogic Corporation&n; * (www.qlogic.com)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; ******************************************************************************/
macro_line|#include &quot;qla_def.h&quot;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_uint16
id|qla2x00_nvram_request
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint32
)paren
suffix:semicolon
r_static
r_void
id|qla2x00_nv_deselect
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|qla2x00_nv_write
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
)paren
suffix:semicolon
multiline_comment|/*&n; * NVRAM support routines&n; */
multiline_comment|/**&n; * qla2x00_lock_nvram_access() - &n; * @ha: HA context&n; */
r_void
DECL|function|qla2x00_lock_nvram_access
id|qla2x00_lock_nvram_access
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
r_uint16
id|data
suffix:semicolon
id|device_reg_t
id|__iomem
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_QLA2100
c_func
(paren
id|ha
)paren
op_logical_and
op_logical_neg
id|IS_QLA2200
c_func
(paren
id|ha
)paren
op_logical_and
op_logical_neg
id|IS_QLA2300
c_func
(paren
id|ha
)paren
)paren
(brace
id|data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
r_while
c_loop
(paren
id|data
op_amp
id|NVR_BUSY
)paren
(brace
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
)brace
multiline_comment|/* Lock resource */
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
comma
l_int|0x1
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|data
op_amp
id|BIT_0
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Lock failed */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
comma
l_int|0x1
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * qla2x00_unlock_nvram_access() - &n; * @ha: HA context&n; */
r_void
DECL|function|qla2x00_unlock_nvram_access
id|qla2x00_unlock_nvram_access
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|device_reg_t
id|__iomem
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_QLA2100
c_func
(paren
id|ha
)paren
op_logical_and
op_logical_neg
id|IS_QLA2200
c_func
(paren
id|ha
)paren
op_logical_and
op_logical_neg
id|IS_QLA2300
c_func
(paren
id|ha
)paren
)paren
(brace
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
comma
l_int|0
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * qla2x00_release_nvram_protection() - &n; * @ha: HA context&n; */
r_void
DECL|function|qla2x00_release_nvram_protection
id|qla2x00_release_nvram_protection
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|device_reg_t
op_star
id|reg
suffix:semicolon
r_uint32
id|word
suffix:semicolon
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
multiline_comment|/* Release NVRAM write protection. */
r_if
c_cond
(paren
id|IS_QLA2322
c_func
(paren
id|ha
)paren
op_logical_or
id|IS_QLA6322
c_func
(paren
id|ha
)paren
)paren
(brace
multiline_comment|/* Write enable. */
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|word
op_assign
l_int|0
suffix:semicolon
id|word
OL
l_int|8
suffix:semicolon
id|word
op_increment
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
multiline_comment|/* Enable protection register. */
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_PR_ENABLE
op_or
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_PR_ENABLE
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_PR_ENABLE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|word
op_assign
l_int|0
suffix:semicolon
id|word
OL
l_int|8
suffix:semicolon
id|word
op_increment
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
op_or
id|NVR_PR_ENABLE
)paren
suffix:semicolon
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
multiline_comment|/* Clear protection register (ffff is cleared). */
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_PR_ENABLE
op_or
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_PR_ENABLE
op_or
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_PR_ENABLE
op_or
id|NVR_DATA_OUT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|word
op_assign
l_int|0
suffix:semicolon
id|word
OL
l_int|8
suffix:semicolon
id|word
op_increment
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
op_or
id|NVR_PR_ENABLE
)paren
suffix:semicolon
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
multiline_comment|/* Wait for NVRAM to become ready. */
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_SELECT
)paren
suffix:semicolon
r_do
(brace
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
id|word
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|word
op_amp
id|NVR_DATA_IN
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * qla2x00_get_nvram_word() - Calculates word position in NVRAM and calls the&n; *&t;request routine to get the word from NVRAM.&n; * @ha: HA context&n; * @addr: Address in NVRAM to read&n; *&n; * Returns the word read from nvram @addr.&n; */
r_uint16
DECL|function|qla2x00_get_nvram_word
id|qla2x00_get_nvram_word
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
)paren
(brace
r_uint16
id|data
suffix:semicolon
r_uint32
id|nv_cmd
suffix:semicolon
id|nv_cmd
op_assign
id|addr
op_lshift
l_int|16
suffix:semicolon
id|nv_cmd
op_or_assign
id|NV_READ_OP
suffix:semicolon
id|data
op_assign
id|qla2x00_nvram_request
c_func
(paren
id|ha
comma
id|nv_cmd
)paren
suffix:semicolon
r_return
(paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_write_nvram_word() - Write NVRAM data.&n; * @ha: HA context&n; * @addr: Address in NVRAM to write&n; * @data: word to program&n; */
r_void
DECL|function|qla2x00_write_nvram_word
id|qla2x00_write_nvram_word
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint16
id|data
)paren
(brace
r_int
id|count
suffix:semicolon
r_uint16
id|word
suffix:semicolon
r_uint32
id|nv_cmd
suffix:semicolon
id|device_reg_t
id|__iomem
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|word
op_assign
l_int|0
suffix:semicolon
id|word
OL
l_int|8
suffix:semicolon
id|word
op_increment
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
multiline_comment|/* Write data */
id|nv_cmd
op_assign
(paren
id|addr
op_lshift
l_int|16
)paren
op_or
id|NV_WRITE_OP
suffix:semicolon
id|nv_cmd
op_or_assign
id|data
suffix:semicolon
id|nv_cmd
op_lshift_assign
l_int|5
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|27
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nv_cmd
op_amp
id|BIT_31
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
r_else
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
id|nv_cmd
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
multiline_comment|/* Wait for NVRAM to become ready */
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_SELECT
)paren
suffix:semicolon
r_do
(brace
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
id|word
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|word
op_amp
id|NVR_DATA_IN
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
multiline_comment|/* Disable writes */
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|10
suffix:semicolon
id|count
op_increment
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
id|qla2x00_nv_deselect
c_func
(paren
id|ha
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_nvram_request() - Sends read command to NVRAM and gets data from&n; *&t;NVRAM.&n; * @ha: HA context&n; * @nv_cmd: NVRAM command&n; *&n; * Bit definitions for NVRAM command:&n; *&n; *&t;Bit 26     = start bit&n; *&t;Bit 25, 24 = opcode&n; *&t;Bit 23-16  = address&n; *&t;Bit 15-0   = write data&n; *&n; * Returns the word read from nvram @addr.&n; */
r_static
r_uint16
DECL|function|qla2x00_nvram_request
id|qla2x00_nvram_request
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|nv_cmd
)paren
(brace
r_uint8
id|cnt
suffix:semicolon
id|device_reg_t
id|__iomem
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
r_uint16
id|data
op_assign
l_int|0
suffix:semicolon
r_uint16
id|reg_data
suffix:semicolon
multiline_comment|/* Send command to NVRAM. */
id|nv_cmd
op_lshift_assign
l_int|5
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
l_int|11
suffix:semicolon
id|cnt
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nv_cmd
op_amp
id|BIT_31
)paren
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
id|NVR_DATA_OUT
)paren
suffix:semicolon
r_else
id|qla2x00_nv_write
c_func
(paren
id|ha
comma
l_int|0
)paren
suffix:semicolon
id|nv_cmd
op_lshift_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Read data from NVRAM. */
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
l_int|16
suffix:semicolon
id|cnt
op_increment
)paren
(brace
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_SELECT
op_or
id|NVR_CLOCK
)paren
suffix:semicolon
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
id|data
op_lshift_assign
l_int|1
suffix:semicolon
id|reg_data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg_data
op_amp
id|NVR_DATA_IN
)paren
id|data
op_or_assign
id|BIT_0
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_SELECT
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Deselect chip. */
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_DESELECT
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_nv_write() - Clean NVRAM operations.&n; * @ha: HA context&n; */
r_static
r_void
DECL|function|qla2x00_nv_deselect
id|qla2x00_nv_deselect
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|device_reg_t
id|__iomem
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_DESELECT
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_nv_write() - Prepare for NVRAM read/write operation.&n; * @ha: HA context&n; * @data: Serial interface selector&n; */
r_static
r_void
DECL|function|qla2x00_nv_write
id|qla2x00_nv_write
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint16
id|data
)paren
(brace
id|device_reg_t
id|__iomem
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|data
op_or
id|NVR_SELECT
op_or
id|NVR_WRT_ENABLE
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|data
op_or
id|NVR_SELECT
op_or
id|NVR_CLOCK
op_or
id|NVR_WRT_ENABLE
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|data
op_or
id|NVR_SELECT
op_or
id|NVR_WRT_ENABLE
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|NVRAM_DELAY
c_func
(paren
)paren
suffix:semicolon
)brace
eof
