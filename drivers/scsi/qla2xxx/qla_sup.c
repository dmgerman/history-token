multiline_comment|/******************************************************************************&n; *                  QLOGIC LINUX SOFTWARE&n; *&n; * QLogic ISP2x00 device driver for Linux 2.6.x&n; * Copyright (C) 2003-2004 QLogic Corporation&n; * (www.qlogic.com)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; ******************************************************************************/
macro_line|#include &quot;qla_os.h&quot;
macro_line|#include &quot;qla_def.h&quot;
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
r_uint8
id|qla2x00_read_flash_byte
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
id|qla2x00_write_flash_byte
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint32
comma
r_uint8
)paren
suffix:semicolon
r_static
r_uint8
id|qla2x00_poll_flash
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint8
id|poll_data
comma
r_uint8
id|mid
)paren
suffix:semicolon
r_static
r_uint8
id|qla2x00_program_flash_address
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint8
id|data
comma
r_uint8
id|mid
)paren
suffix:semicolon
r_static
r_uint8
id|qla2x00_erase_flash_sector
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint32
id|sec_mask
comma
r_uint8
id|mid
)paren
suffix:semicolon
r_uint8
id|qla2x00_get_flash_manufacturer
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
suffix:semicolon
r_uint16
id|qla2x00_get_flash_version
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_uint16
id|qla2x00_get_flash_image
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint8
op_star
id|image
)paren
suffix:semicolon
r_uint16
id|qla2x00_set_flash_image
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint8
op_star
id|image
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
op_star
id|reg
suffix:semicolon
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
op_star
id|reg
suffix:semicolon
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
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;u.isp2300.host_semaphore
comma
l_int|0
)paren
suffix:semicolon
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
multiline_comment|/* Erase Location */
id|nv_cmd
op_assign
(paren
id|addr
op_lshift
l_int|16
)paren
op_or
id|NV_ERASE_OP
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
l_int|11
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
multiline_comment|/* Wait for Erase to Finish */
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
id|NVRAM_DELAY
c_func
(paren
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
id|NVRAM_DELAY
c_func
(paren
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
r_return
(paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_nv_write() - Clean NVRAM operations.&n; * @ha: HA context&n; */
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
id|NVRAM_DELAY
c_func
(paren
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
)brace
multiline_comment|/**&n; * qla2x00_nv_write() - Prepare for NVRAM read/write operation.&n; * @ha: HA context&n; * @data: Serial interface selector&n; */
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
)paren
suffix:semicolon
id|NVRAM_DELAY
c_func
(paren
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
)paren
suffix:semicolon
id|NVRAM_DELAY
c_func
(paren
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
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|data
op_or
id|NVR_SELECT
)paren
suffix:semicolon
id|NVRAM_DELAY
c_func
(paren
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
)brace
multiline_comment|/*&n; * Flash support routines&n; */
multiline_comment|/**&n; * qla2x00_flash_enable() - Setup flash for reading and writing.&n; * @ha: HA context&n; */
r_void
DECL|function|qla2x00_flash_enable
id|qla2x00_flash_enable
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
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
id|data
op_or_assign
id|CSR_FLASH_ENABLE
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|data
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
multiline_comment|/**&n; * qla2x00_flash_disable() - Disable flash and allow RISC to run.&n; * @ha: HA context&n; */
r_void
DECL|function|qla2x00_flash_disable
id|qla2x00_flash_disable
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
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|data
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
id|data
op_and_assign
op_complement
(paren
id|CSR_FLASH_ENABLE
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|data
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
multiline_comment|/**&n; * qla2x00_read_flash_byte() - Reads a byte from flash&n; * @ha: HA context&n; * @addr: Address in flash to read&n; *&n; * A word is read from the chip, but, only the lower byte is valid.&n; *&n; * Returns the byte read from flash @addr.&n; */
r_uint8
DECL|function|qla2x00_read_flash_byte
id|qla2x00_read_flash_byte
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
r_uint16
id|bank_select
suffix:semicolon
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
multiline_comment|/* Setup bit 16 of flash address. */
id|bank_select
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
id|BIT_16
)paren
op_logical_and
(paren
(paren
id|bank_select
op_amp
id|CSR_FLASH_64K_BANK
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|bank_select
op_or_assign
id|CSR_FLASH_64K_BANK
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|bank_select
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|addr
op_amp
id|BIT_16
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|bank_select
op_amp
id|CSR_FLASH_64K_BANK
)paren
)paren
(brace
id|bank_select
op_and_assign
op_complement
(paren
id|CSR_FLASH_64K_BANK
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|bank_select
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
multiline_comment|/* The ISP2312 v2 chip cannot access the FLASH registers via MMIO. */
r_if
c_cond
(paren
id|IS_QLA2312
c_func
(paren
id|ha
)paren
op_logical_and
id|ha-&gt;product_id
(braket
l_int|3
)braket
op_eq
l_int|0x2
op_logical_and
id|ha-&gt;pio_address
)paren
(brace
r_uint16
id|data2
suffix:semicolon
id|reg
op_assign
(paren
id|device_reg_t
op_star
)paren
id|ha-&gt;pio_address
suffix:semicolon
id|outw
c_func
(paren
(paren
r_uint16
)paren
id|addr
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|reg-&gt;flash_address
)paren
)paren
suffix:semicolon
r_do
(brace
id|data
op_assign
id|inw
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|reg-&gt;flash_data
)paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|data2
op_assign
id|inw
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|reg-&gt;flash_data
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|data
op_ne
id|data2
)paren
suffix:semicolon
)brace
r_else
(brace
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;flash_address
comma
(paren
r_uint16
)paren
id|addr
)paren
suffix:semicolon
id|data
op_assign
id|qla2x00_debounce_register
c_func
(paren
op_amp
id|reg-&gt;flash_data
)paren
suffix:semicolon
)brace
r_return
(paren
(paren
r_uint8
)paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_write_flash_byte() - Write a byte to flash&n; * @ha: HA context&n; * @addr: Address in flash to write&n; * @data: Data to write&n; */
r_static
r_void
DECL|function|qla2x00_write_flash_byte
id|qla2x00_write_flash_byte
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint8
id|data
)paren
(brace
r_uint16
id|bank_select
suffix:semicolon
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
multiline_comment|/* Setup bit 16 of flash address. */
id|bank_select
op_assign
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
id|BIT_16
)paren
op_logical_and
(paren
(paren
id|bank_select
op_amp
id|CSR_FLASH_64K_BANK
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|bank_select
op_or_assign
id|CSR_FLASH_64K_BANK
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|bank_select
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|addr
op_amp
id|BIT_16
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|bank_select
op_amp
id|CSR_FLASH_64K_BANK
)paren
)paren
(brace
id|bank_select
op_and_assign
op_complement
(paren
id|CSR_FLASH_64K_BANK
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|bank_select
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
multiline_comment|/* The ISP2312 v2 chip cannot access the FLASH registers via MMIO. */
r_if
c_cond
(paren
id|IS_QLA2312
c_func
(paren
id|ha
)paren
op_logical_and
id|ha-&gt;product_id
(braket
l_int|3
)braket
op_eq
l_int|0x2
op_logical_and
id|ha-&gt;pio_address
)paren
(brace
id|reg
op_assign
(paren
id|device_reg_t
op_star
)paren
id|ha-&gt;pio_address
suffix:semicolon
id|outw
c_func
(paren
(paren
r_uint16
)paren
id|addr
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|reg-&gt;flash_address
)paren
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
r_uint16
)paren
id|data
comma
(paren
r_int
r_int
)paren
(paren
op_amp
id|reg-&gt;flash_data
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;flash_address
comma
(paren
r_uint16
)paren
id|addr
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;flash_data
comma
(paren
r_uint16
)paren
id|data
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
)brace
multiline_comment|/**&n; * qla2x00_poll_flash() - Polls flash for completion.&n; * @ha: HA context&n; * @addr: Address in flash to poll&n; * @poll_data: Data to be polled&n; * @mid: Flash manufacturer ID&n; *&n; * This function polls the device until bit 7 of what is read matches data&n; * bit 7 or until data bit 5 becomes a 1.  If that hapens, the flash ROM timed&n; * out (a fatal error).  The flash book recommeds reading bit 7 again after&n; * reading bit 5 as a 1.&n; *&n; * Returns 0 on success, else non-zero.&n; */
r_static
r_uint8
DECL|function|qla2x00_poll_flash
id|qla2x00_poll_flash
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint8
id|poll_data
comma
r_uint8
id|mid
)paren
(brace
r_uint8
id|status
suffix:semicolon
r_uint8
id|flash_data
suffix:semicolon
r_uint32
id|cnt
suffix:semicolon
r_int
id|failed_pass
suffix:semicolon
id|status
op_assign
l_int|1
suffix:semicolon
id|failed_pass
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Wait for 30 seconds for command to finish. */
id|poll_data
op_and_assign
id|BIT_7
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|3000000
suffix:semicolon
id|cnt
suffix:semicolon
id|cnt
op_decrement
)paren
(brace
id|flash_data
op_assign
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flash_data
op_amp
id|BIT_7
)paren
op_eq
id|poll_data
)paren
(brace
id|status
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mid
op_ne
l_int|0x40
op_logical_and
id|mid
op_ne
l_int|0xda
)paren
(brace
r_if
c_cond
(paren
id|flash_data
op_amp
id|BIT_5
)paren
id|failed_pass
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|failed_pass
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_program_flash_address() - Programs a flash address&n; * @ha: HA context&n; * @addr: Address in flash to program&n; * @data: Data to be written in flash&n; * @mid: Flash manufacturer ID&n; *&n; * Returns 0 on success, else non-zero.&n; */
r_static
r_uint8
DECL|function|qla2x00_program_flash_address
id|qla2x00_program_flash_address
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint8
id|data
comma
r_uint8
id|mid
)paren
(brace
multiline_comment|/* Write Program Command Sequence */
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0xaa
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x2aaa
comma
l_int|0x55
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0xa0
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
id|addr
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Wait for write to complete. */
r_return
(paren
id|qla2x00_poll_flash
c_func
(paren
id|ha
comma
id|addr
comma
id|data
comma
id|mid
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_erase_flash_sector() - Erase a flash sector.&n; * @ha: HA context&n; * @addr: Flash sector to erase&n; * @sec_mask: Sector address mask&n; * @mid: Flash manufacturer ID&n; *&n; * Returns 0 on success, else non-zero.&n; */
r_static
r_uint8
DECL|function|qla2x00_erase_flash_sector
id|qla2x00_erase_flash_sector
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint32
id|addr
comma
r_uint32
id|sec_mask
comma
r_uint8
id|mid
)paren
(brace
multiline_comment|/* Individual Sector Erase Command Sequence */
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0xaa
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x2aaa
comma
l_int|0x55
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0x80
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0xaa
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x2aaa
comma
l_int|0x55
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mid
op_eq
l_int|0xda
)paren
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
id|addr
op_amp
id|sec_mask
comma
l_int|0x10
)paren
suffix:semicolon
r_else
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
id|addr
op_amp
id|sec_mask
comma
l_int|0x30
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
multiline_comment|/* Wait for erase to complete. */
r_return
(paren
id|qla2x00_poll_flash
c_func
(paren
id|ha
comma
id|addr
comma
l_int|0x80
comma
id|mid
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_get_flash_manufacturer() - Read manufacturer ID from flash chip.&n; * @ha: HA context&n; *&n; * Returns the manufacturer&squot;s ID read from the flash chip.&n; */
r_uint8
DECL|function|qla2x00_get_flash_manufacturer
id|qla2x00_get_flash_manufacturer
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
r_uint8
id|manuf_id
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0xaa
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x2aaa
comma
l_int|0x55
)paren
suffix:semicolon
id|qla2x00_write_flash_byte
c_func
(paren
id|ha
comma
l_int|0x5555
comma
l_int|0x90
)paren
suffix:semicolon
id|manuf_id
op_assign
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
l_int|0x0001
)paren
suffix:semicolon
r_return
(paren
id|manuf_id
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_get_flash_version() - Read version information from flash.&n; * @ha: HA context&n; *&n; * Returns QLA_SUCCESS on successful retrieval of flash version.&n; */
r_uint16
DECL|function|qla2x00_get_flash_version
id|qla2x00_get_flash_version
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
r_uint16
id|ret
op_assign
id|QLA_SUCCESS
suffix:semicolon
r_uint32
id|loop_cnt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* this is for error exit only */
r_uint32
id|pcir_adr
suffix:semicolon
multiline_comment|/* The ISP2312 v2 chip cannot access the FLASH registers via MMIO. */
r_if
c_cond
(paren
id|IS_QLA2312
c_func
(paren
id|ha
)paren
op_logical_and
id|ha-&gt;product_id
(braket
l_int|3
)braket
op_eq
l_int|0x2
op_logical_and
op_logical_neg
id|ha-&gt;pio_address
)paren
id|ret
op_assign
id|QLA_FUNCTION_FAILED
suffix:semicolon
id|qla2x00_flash_enable
c_func
(paren
id|ha
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* Loop once to provide quick error exit */
multiline_comment|/* Match signature */
r_if
c_cond
(paren
op_logical_neg
(paren
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
l_int|0
)paren
op_eq
l_int|0x55
op_logical_and
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
l_int|1
)paren
op_eq
l_int|0xaa
)paren
)paren
(brace
multiline_comment|/* No signature */
id|DEBUG2
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;scsi(%ld): No matching FLASH &quot;
l_string|&quot;signature.&bslash;n&quot;
comma
id|ha-&gt;host_no
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|QLA_FUNCTION_FAILED
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pcir_adr
op_assign
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
l_int|0x18
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* validate signature of PCI data structure */
r_if
c_cond
(paren
(paren
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|pcir_adr
)paren
)paren
op_eq
l_char|&squot;P&squot;
op_logical_and
(paren
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|pcir_adr
op_plus
l_int|1
)paren
)paren
op_eq
l_char|&squot;C&squot;
op_logical_and
(paren
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|pcir_adr
op_plus
l_int|2
)paren
)paren
op_eq
l_char|&squot;I&squot;
op_logical_and
(paren
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|pcir_adr
op_plus
l_int|3
)paren
)paren
op_eq
l_char|&squot;R&squot;
)paren
(brace
multiline_comment|/* Read version */
id|ha-&gt;optrom_minor
op_assign
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|pcir_adr
op_plus
l_int|0x12
)paren
suffix:semicolon
id|ha-&gt;optrom_major
op_assign
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|pcir_adr
op_plus
l_int|0x13
)paren
suffix:semicolon
id|DEBUG3
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): got %d.%d.&bslash;n&quot;
comma
id|__func__
comma
id|ha-&gt;optrom_major
comma
id|ha-&gt;optrom_minor
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* error */
id|DEBUG2
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): PCI data struct not found. &quot;
l_string|&quot;pcir_adr=%x.&bslash;n&quot;
comma
id|__func__
comma
id|pcir_adr
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|QLA_FUNCTION_FAILED
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_decrement
id|loop_cnt
)paren
suffix:semicolon
id|qla2x00_flash_disable
c_func
(paren
id|ha
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_get_flash_image() - Read image from flash chip.&n; * @ha: HA context&n; * @image: Buffer to receive flash image&n; *&n; * Returns 0 on success, else non-zero.&n; */
r_uint16
DECL|function|qla2x00_get_flash_image
id|qla2x00_get_flash_image
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint8
op_star
id|image
)paren
(brace
r_uint32
id|addr
suffix:semicolon
r_uint32
id|midpoint
suffix:semicolon
r_uint8
op_star
id|data
suffix:semicolon
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|midpoint
op_assign
id|FLASH_IMAGE_SIZE
op_div
l_int|2
suffix:semicolon
id|qla2x00_flash_enable
c_func
(paren
id|ha
)paren
suffix:semicolon
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
l_int|0
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
r_for
c_loop
(paren
id|addr
op_assign
l_int|0
comma
id|data
op_assign
id|image
suffix:semicolon
id|addr
OL
id|FLASH_IMAGE_SIZE
suffix:semicolon
id|addr
op_increment
comma
id|data
op_increment
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
id|midpoint
)paren
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_SELECT
)paren
suffix:semicolon
op_star
id|data
op_assign
id|qla2x00_read_flash_byte
c_func
(paren
id|ha
comma
id|addr
)paren
suffix:semicolon
)brace
id|qla2x00_flash_disable
c_func
(paren
id|ha
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_set_flash_image() - Write image to flash chip.&n; * @ha: HA context&n; * @image: Source image to write to flash&n; *&n; * Returns 0 on success, else non-zero.&n; */
r_uint16
DECL|function|qla2x00_set_flash_image
id|qla2x00_set_flash_image
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint8
op_star
id|image
)paren
(brace
r_uint16
id|status
suffix:semicolon
r_uint32
id|addr
suffix:semicolon
r_uint32
id|midpoint
suffix:semicolon
r_uint32
id|sec_mask
suffix:semicolon
r_uint32
id|rest_addr
suffix:semicolon
r_uint8
id|mid
suffix:semicolon
r_uint8
id|sec_number
suffix:semicolon
r_uint8
id|data
suffix:semicolon
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
id|sec_number
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Reset ISP chip. */
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
comma
id|CSR_ISP_SOFT_RESET
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;ctrl_status
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|qla2x00_flash_enable
c_func
(paren
id|ha
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* Loop once to provide quick error exit */
multiline_comment|/* Structure of flash memory based on manufacturer */
id|mid
op_assign
id|qla2x00_get_flash_manufacturer
c_func
(paren
id|ha
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mid
op_eq
l_int|0x6d
)paren
(brace
singleline_comment|// Am29LV001 part
id|rest_addr
op_assign
l_int|0x1fff
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1e000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mid
op_eq
l_int|0x40
)paren
(brace
singleline_comment|// Mostel v29c51001 part
id|rest_addr
op_assign
l_int|0x1ff
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1fe00
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mid
op_eq
l_int|0xbf
)paren
(brace
singleline_comment|// SST39sf10 part
id|rest_addr
op_assign
l_int|0xfff
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1f000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mid
op_eq
l_int|0xda
)paren
(brace
singleline_comment|// Winbond W29EE011 part
id|rest_addr
op_assign
l_int|0x7f
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1ff80
suffix:semicolon
id|addr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|qla2x00_erase_flash_sector
c_func
(paren
id|ha
comma
id|addr
comma
id|sec_mask
comma
id|mid
)paren
)paren
(brace
id|status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// Am29F010 part
id|rest_addr
op_assign
l_int|0x3fff
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1c000
suffix:semicolon
)brace
id|midpoint
op_assign
id|FLASH_IMAGE_SIZE
op_div
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
l_int|0
suffix:semicolon
id|addr
OL
id|FLASH_IMAGE_SIZE
suffix:semicolon
id|addr
op_increment
)paren
(brace
id|data
op_assign
op_star
id|image
op_increment
suffix:semicolon
multiline_comment|/* Are we at the beginning of a sector? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr
op_amp
id|rest_addr
)paren
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
id|midpoint
)paren
id|WRT_REG_WORD
c_func
(paren
op_amp
id|reg-&gt;nvram
comma
id|NVR_SELECT
)paren
suffix:semicolon
multiline_comment|/* Then erase it */
r_if
c_cond
(paren
id|qla2x00_erase_flash_sector
c_func
(paren
id|ha
comma
id|addr
comma
id|sec_mask
comma
id|mid
)paren
)paren
(brace
id|status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sec_number
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mid
op_eq
l_int|0x6d
)paren
(brace
r_if
c_cond
(paren
id|sec_number
op_eq
l_int|1
op_logical_and
(paren
id|addr
op_eq
(paren
id|rest_addr
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|rest_addr
op_assign
l_int|0x0fff
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1f000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sec_number
op_eq
l_int|3
op_logical_and
(paren
id|addr
op_amp
l_int|0x7ffe
)paren
)paren
(brace
id|rest_addr
op_assign
l_int|0x3fff
suffix:semicolon
id|sec_mask
op_assign
l_int|0x1c000
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|qla2x00_program_flash_address
c_func
(paren
id|ha
comma
id|addr
comma
id|data
comma
id|mid
)paren
)paren
(brace
id|status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
id|qla2x00_flash_disable
c_func
(paren
id|ha
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
