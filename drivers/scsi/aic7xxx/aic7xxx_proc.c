multiline_comment|/*&n; * Copyright (c) 2000-2001 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * String handling code courtesy of Gerard Roudier&squot;s &lt;groudier@club-internet.fr&gt;&n; * sym driver.&n; *&n; * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7xxx_proc.c#29 $&n; */
macro_line|#include &quot;aic7xxx_osm.h&quot;
macro_line|#include &quot;aic7xxx_inline.h&quot;
macro_line|#include &quot;aic7xxx_93cx6.h&quot;
r_static
r_void
id|copy_mem_info
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_char
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
r_static
r_int
id|copy_info
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_static
r_void
id|ahc_dump_target_state
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|info_str
op_star
id|info
comma
id|u_int
id|our_id
comma
r_char
id|channel
comma
id|u_int
id|target_id
comma
id|u_int
id|target_offset
)paren
suffix:semicolon
r_static
r_void
id|ahc_dump_device_state
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_struct
id|ahc_linux_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ahc_proc_write_seeprom
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_static
r_void
DECL|function|copy_mem_info
id|copy_mem_info
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;pos
op_plus
id|len
OG
id|info-&gt;offset
op_plus
id|info-&gt;length
)paren
id|len
op_assign
id|info-&gt;offset
op_plus
id|info-&gt;length
op_minus
id|info-&gt;pos
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;pos
op_plus
id|len
OL
id|info-&gt;offset
)paren
(brace
id|info-&gt;pos
op_add_assign
id|len
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;pos
OL
id|info-&gt;offset
)paren
(brace
id|off_t
id|partial
suffix:semicolon
id|partial
op_assign
id|info-&gt;offset
op_minus
id|info-&gt;pos
suffix:semicolon
id|data
op_add_assign
id|partial
suffix:semicolon
id|info-&gt;pos
op_add_assign
id|partial
suffix:semicolon
id|len
op_sub_assign
id|partial
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
id|memcpy
c_func
(paren
id|info-&gt;buffer
comma
id|data
comma
id|len
)paren
suffix:semicolon
id|info-&gt;pos
op_add_assign
id|len
suffix:semicolon
id|info-&gt;buffer
op_add_assign
id|len
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|copy_info
id|copy_info
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|len
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|copy_mem_info
c_func
(paren
id|info
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
r_void
DECL|function|ahc_format_transinfo
id|ahc_format_transinfo
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_struct
id|ahc_transinfo
op_star
id|tinfo
)paren
(brace
id|u_int
id|speed
suffix:semicolon
id|u_int
id|freq
suffix:semicolon
id|u_int
id|mb
suffix:semicolon
id|speed
op_assign
l_int|3300
suffix:semicolon
id|freq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tinfo-&gt;offset
op_ne
l_int|0
)paren
(brace
id|freq
op_assign
id|aic_calc_syncsrate
c_func
(paren
id|tinfo-&gt;period
)paren
suffix:semicolon
id|speed
op_assign
id|freq
suffix:semicolon
)brace
id|speed
op_mul_assign
(paren
l_int|0x01
op_lshift
id|tinfo-&gt;width
)paren
suffix:semicolon
id|mb
op_assign
id|speed
op_div
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|mb
OG
l_int|0
)paren
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;%d.%03dMB/s transfers&quot;
comma
id|mb
comma
id|speed
op_mod
l_int|1000
)paren
suffix:semicolon
r_else
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;%dKB/s transfers&quot;
comma
id|speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq
op_ne
l_int|0
)paren
(brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot; (%d.%03dMHz%s, offset %d&quot;
comma
id|freq
op_div
l_int|1000
comma
id|freq
op_mod
l_int|1000
comma
(paren
id|tinfo-&gt;ppr_options
op_amp
id|MSG_EXT_PPR_DT_REQ
)paren
op_ne
l_int|0
ques
c_cond
l_string|&quot; DT&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tinfo-&gt;offset
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tinfo-&gt;width
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|freq
op_ne
l_int|0
)paren
(brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;, &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot; (&quot;
)paren
suffix:semicolon
)brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;%dbit)&quot;
comma
l_int|8
op_star
(paren
l_int|0x01
op_lshift
id|tinfo-&gt;width
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|freq
op_ne
l_int|0
)paren
(brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;)&quot;
)paren
suffix:semicolon
)brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ahc_dump_target_state
id|ahc_dump_target_state
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|info_str
op_star
id|info
comma
id|u_int
id|our_id
comma
r_char
id|channel
comma
id|u_int
id|target_id
comma
id|u_int
id|target_offset
)paren
(brace
r_struct
id|ahc_linux_target
op_star
id|targ
suffix:semicolon
r_struct
id|ahc_initiator_tinfo
op_star
id|tinfo
suffix:semicolon
r_struct
id|ahc_tmode_tstate
op_star
id|tstate
suffix:semicolon
r_int
id|lun
suffix:semicolon
id|tinfo
op_assign
id|ahc_fetch_transinfo
c_func
(paren
id|ahc
comma
id|channel
comma
id|our_id
comma
id|target_id
comma
op_amp
id|tstate
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
id|AHC_TWIN
)paren
op_ne
l_int|0
)paren
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;Channel %c &quot;
comma
id|channel
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;Target %d Negotiation Settings&bslash;n&quot;
comma
id|target_id
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;tUser: &quot;
)paren
suffix:semicolon
id|ahc_format_transinfo
c_func
(paren
id|info
comma
op_amp
id|tinfo-&gt;user
)paren
suffix:semicolon
id|targ
op_assign
id|ahc-&gt;platform_data-&gt;targets
(braket
id|target_offset
)braket
suffix:semicolon
r_if
c_cond
(paren
id|targ
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;tGoal: &quot;
)paren
suffix:semicolon
id|ahc_format_transinfo
c_func
(paren
id|info
comma
op_amp
id|tinfo-&gt;goal
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;tCurr: &quot;
)paren
suffix:semicolon
id|ahc_format_transinfo
c_func
(paren
id|info
comma
op_amp
id|tinfo-&gt;curr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|lun
op_assign
l_int|0
suffix:semicolon
id|lun
OL
id|AHC_NUM_LUNS
suffix:semicolon
id|lun
op_increment
)paren
(brace
r_struct
id|ahc_linux_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|targ-&gt;devices
(braket
id|lun
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|ahc_dump_device_state
c_func
(paren
id|info
comma
id|dev
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|ahc_dump_device_state
id|ahc_dump_device_state
c_func
(paren
r_struct
id|info_str
op_star
id|info
comma
r_struct
id|ahc_linux_device
op_star
id|dev
)paren
(brace
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;tChannel %c Target %d Lun %d Settings&bslash;n&quot;
comma
id|dev-&gt;target-&gt;channel
op_plus
l_char|&squot;A&squot;
comma
id|dev-&gt;target-&gt;target
comma
id|dev-&gt;lun
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;t&bslash;tCommands Queued %ld&bslash;n&quot;
comma
id|dev-&gt;commands_issued
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;t&bslash;tCommands Active %d&bslash;n&quot;
comma
id|dev-&gt;active
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;t&bslash;tCommand Openings %d&bslash;n&quot;
comma
id|dev-&gt;openings
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;t&bslash;tMax Tagged Openings %d&bslash;n&quot;
comma
id|dev-&gt;maxtags
)paren
suffix:semicolon
id|copy_info
c_func
(paren
id|info
comma
l_string|&quot;&bslash;t&bslash;tDevice Queue Frozen Count %d&bslash;n&quot;
comma
id|dev-&gt;qfrozen
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ahc_proc_write_seeprom
id|ahc_proc_write_seeprom
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_struct
id|seeprom_descriptor
id|sd
suffix:semicolon
r_int
id|have_seeprom
suffix:semicolon
id|u_long
id|s
suffix:semicolon
r_int
id|paused
suffix:semicolon
r_int
id|written
suffix:semicolon
multiline_comment|/* Default to failure. */
id|written
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|ahc_lock
c_func
(paren
id|ahc
comma
op_amp
id|s
)paren
suffix:semicolon
id|paused
op_assign
id|ahc_is_paused
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|paused
)paren
id|ahc_pause
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ne
r_sizeof
(paren
r_struct
id|seeprom_config
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;ahc_proc_write_seeprom: incorrect buffer size&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|have_seeprom
op_assign
id|ahc_verify_cksum
c_func
(paren
(paren
r_struct
id|seeprom_config
op_star
)paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|have_seeprom
op_eq
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;ahc_proc_write_seeprom: cksum verification failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|sd.sd_ahc
op_assign
id|ahc
suffix:semicolon
macro_line|#if AHC_PCI_CONFIG &gt; 0
r_if
c_cond
(paren
(paren
id|ahc-&gt;chip
op_amp
id|AHC_PCI
)paren
op_ne
l_int|0
)paren
(brace
id|sd.sd_control_offset
op_assign
id|SEECTL
suffix:semicolon
id|sd.sd_status_offset
op_assign
id|SEECTL
suffix:semicolon
id|sd.sd_dataout_offset
op_assign
id|SEECTL
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;flags
op_amp
id|AHC_LARGE_SEEPROM
)paren
id|sd.sd_chip
op_assign
id|C56_66
suffix:semicolon
r_else
id|sd.sd_chip
op_assign
id|C46
suffix:semicolon
id|sd.sd_MS
op_assign
id|SEEMS
suffix:semicolon
id|sd.sd_RDY
op_assign
id|SEERDY
suffix:semicolon
id|sd.sd_CS
op_assign
id|SEECS
suffix:semicolon
id|sd.sd_CK
op_assign
id|SEECK
suffix:semicolon
id|sd.sd_DO
op_assign
id|SEEDO
suffix:semicolon
id|sd.sd_DI
op_assign
id|SEEDI
suffix:semicolon
id|have_seeprom
op_assign
id|ahc_acquire_seeprom
c_func
(paren
id|ahc
comma
op_amp
id|sd
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
(paren
id|ahc-&gt;chip
op_amp
id|AHC_VL
)paren
op_ne
l_int|0
)paren
(brace
id|sd.sd_control_offset
op_assign
id|SEECTL_2840
suffix:semicolon
id|sd.sd_status_offset
op_assign
id|STATUS_2840
suffix:semicolon
id|sd.sd_dataout_offset
op_assign
id|STATUS_2840
suffix:semicolon
id|sd.sd_chip
op_assign
id|C46
suffix:semicolon
id|sd.sd_MS
op_assign
l_int|0
suffix:semicolon
id|sd.sd_RDY
op_assign
id|EEPROM_TF
suffix:semicolon
id|sd.sd_CS
op_assign
id|CS_2840
suffix:semicolon
id|sd.sd_CK
op_assign
id|CK_2840
suffix:semicolon
id|sd.sd_DO
op_assign
id|DO_2840
suffix:semicolon
id|sd.sd_DI
op_assign
id|DI_2840
suffix:semicolon
id|have_seeprom
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;ahc_proc_write_seeprom: unsupported adapter type&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|have_seeprom
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;ahc_proc_write_seeprom: No Serial EEPROM&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_else
(brace
id|u_int
id|start_addr
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;seep_config
op_eq
l_int|NULL
)paren
(brace
id|ahc-&gt;seep_config
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|ahc-&gt;seep_config
)paren
comma
id|M_DEVBUF
comma
id|M_NOWAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;seep_config
op_eq
l_int|NULL
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aic7xxx: Unable to allocate serial &quot;
l_string|&quot;eeprom buffer.  Write failing&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
id|printf
c_func
(paren
l_string|&quot;aic7xxx: Writing Serial EEPROM&bslash;n&quot;
)paren
suffix:semicolon
id|start_addr
op_assign
l_int|32
op_star
(paren
id|ahc-&gt;channel
op_minus
l_char|&squot;A&squot;
)paren
suffix:semicolon
id|ahc_write_seeprom
c_func
(paren
op_amp
id|sd
comma
(paren
id|u_int16_t
op_star
)paren
id|buffer
comma
id|start_addr
comma
r_sizeof
(paren
r_struct
id|seeprom_config
)paren
op_div
l_int|2
)paren
suffix:semicolon
id|ahc_read_seeprom
c_func
(paren
op_amp
id|sd
comma
(paren
r_uint16
op_star
)paren
id|ahc-&gt;seep_config
comma
id|start_addr
comma
r_sizeof
(paren
r_struct
id|seeprom_config
)paren
op_div
l_int|2
)paren
suffix:semicolon
macro_line|#if AHC_PCI_CONFIG &gt; 0
r_if
c_cond
(paren
(paren
id|ahc-&gt;chip
op_amp
id|AHC_VL
)paren
op_eq
l_int|0
)paren
id|ahc_release_seeprom
c_func
(paren
op_amp
id|sd
)paren
suffix:semicolon
macro_line|#endif
id|written
op_assign
id|length
suffix:semicolon
)brace
id|done
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|paused
)paren
id|ahc_unpause
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|ahc_unlock
c_func
(paren
id|ahc
comma
op_amp
id|s
)paren
suffix:semicolon
r_return
(paren
id|written
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return information to handle /proc support for the driver.&n; */
r_int
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
DECL|function|ahc_linux_proc_info
id|ahc_linux_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
macro_line|#else
id|ahc_linux_proc_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|inout
)paren
macro_line|#endif
(brace
r_struct
id|ahc_softc
op_star
id|ahc
suffix:semicolon
r_struct
id|info_str
id|info
suffix:semicolon
r_char
id|ahc_info
(braket
l_int|256
)braket
suffix:semicolon
id|u_long
id|s
suffix:semicolon
id|u_int
id|max_targ
suffix:semicolon
id|u_int
id|i
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|ahc_list_lock
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
id|TAILQ_FOREACH
c_func
(paren
id|ahc
comma
op_amp
id|ahc_tailq
comma
id|links
)paren
(brace
r_if
c_cond
(paren
id|ahc-&gt;platform_data-&gt;host-&gt;host_no
op_eq
id|hostno
)paren
r_break
suffix:semicolon
)brace
macro_line|#else
id|ahc
op_assign
id|ahc_find_softc
c_func
(paren
op_star
(paren
r_struct
id|ahc_softc
op_star
op_star
)paren
id|shost-&gt;hostdata
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ahc
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* Has data been written to the file? */
r_if
c_cond
(paren
id|inout
op_eq
id|TRUE
)paren
(brace
id|retval
op_assign
id|ahc_proc_write_seeprom
c_func
(paren
id|ahc
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
)paren
op_star
id|start
op_assign
id|buffer
suffix:semicolon
id|info.buffer
op_assign
id|buffer
suffix:semicolon
id|info.length
op_assign
id|length
suffix:semicolon
id|info.offset
op_assign
id|offset
suffix:semicolon
id|info.pos
op_assign
l_int|0
suffix:semicolon
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;Adaptec AIC7xxx driver version: %s&bslash;n&quot;
comma
id|AIC7XXX_DRIVER_VERSION
)paren
suffix:semicolon
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|ahc-&gt;description
)paren
suffix:semicolon
id|ahc_controller_info
c_func
(paren
id|ahc
comma
id|ahc_info
)paren
suffix:semicolon
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|ahc_info
)paren
suffix:semicolon
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;Allocated SCBs: %d, SG List Length: %d&bslash;n&bslash;n&quot;
comma
id|ahc-&gt;scb_data-&gt;numscbs
comma
id|AHC_NSEG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;seep_config
op_eq
l_int|NULL
)paren
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;No Serial EEPROM&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;Serial EEPROM:&bslash;n&quot;
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
r_sizeof
(paren
op_star
id|ahc-&gt;seep_config
)paren
op_div
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|i
op_ne
l_int|0
)paren
)paren
(brace
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;0x%.4x &quot;
comma
(paren
(paren
r_uint16
op_star
)paren
id|ahc-&gt;seep_config
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|copy_info
c_func
(paren
op_amp
id|info
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|max_targ
op_assign
l_int|15
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
(paren
id|AHC_WIDE
op_or
id|AHC_TWIN
)paren
)paren
op_eq
l_int|0
)paren
id|max_targ
op_assign
l_int|7
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|max_targ
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u_int
id|our_id
suffix:semicolon
id|u_int
id|target_id
suffix:semicolon
r_char
id|channel
suffix:semicolon
id|channel
op_assign
l_char|&squot;A&squot;
suffix:semicolon
id|our_id
op_assign
id|ahc-&gt;our_id
suffix:semicolon
id|target_id
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|7
op_logical_and
(paren
id|ahc-&gt;features
op_amp
id|AHC_TWIN
)paren
op_ne
l_int|0
)paren
(brace
id|channel
op_assign
l_char|&squot;B&squot;
suffix:semicolon
id|our_id
op_assign
id|ahc-&gt;our_id_b
suffix:semicolon
id|target_id
op_assign
id|i
op_mod
l_int|8
suffix:semicolon
)brace
id|ahc_dump_target_state
c_func
(paren
id|ahc
comma
op_amp
id|info
comma
id|our_id
comma
id|channel
comma
id|target_id
comma
id|i
)paren
suffix:semicolon
)brace
id|retval
op_assign
id|info.pos
OG
id|info.offset
ques
c_cond
id|info.pos
op_minus
id|info.offset
suffix:colon
l_int|0
suffix:semicolon
id|done
suffix:colon
id|ahc_list_unlock
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
r_return
(paren
id|retval
)paren
suffix:semicolon
)brace
eof
