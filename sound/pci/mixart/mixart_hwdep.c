multiline_comment|/*&n; * Driver for Digigram miXart soundcards&n; *&n; * hwdep device manager&n; *&n; * Copyright (c) 2003 by Digigram &lt;alsa@digigram.com&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;mixart.h&quot;
macro_line|#include &quot;mixart_mixer.h&quot;
macro_line|#include &quot;mixart_core.h&quot;
macro_line|#include &quot;mixart_hwdep.h&quot;
multiline_comment|/* miXart hwdep interface id string */
DECL|macro|SND_MIXART_HWDEP_ID
mdefine_line|#define SND_MIXART_HWDEP_ID       &quot;miXart Loader&quot;
DECL|function|mixart_hwdep_open
r_static
r_int
id|mixart_hwdep_open
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_hwdep_release
r_static
r_int
id|mixart_hwdep_release
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * wait for a value on a peudo register, exit with a timeout&n; *&n; * @param mgr pointer to miXart manager structure&n; * @param offset unsigned pseudo_register base + offset of value&n; * @param value value&n; * @param timeout timeout in centisenconds&n; */
DECL|function|mixart_wait_nice_for_register_value
r_static
r_int
id|mixart_wait_nice_for_register_value
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
comma
id|u32
id|offset
comma
r_int
id|is_egal
comma
id|u32
id|value
comma
r_int
r_int
id|timeout
)paren
(brace
r_int
r_int
id|end_time
op_assign
id|jiffies
op_plus
(paren
id|timeout
op_star
id|HZ
op_div
l_int|100
)paren
suffix:semicolon
id|u32
id|read
suffix:semicolon
r_do
(brace
multiline_comment|/* we may take too long time in this loop.&n;&t;&t; * so give controls back to kernel if needed.&n;&t;&t; */
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
id|read
op_assign
id|readl_be
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_egal
)paren
(brace
r_if
c_cond
(paren
id|read
op_eq
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* wait for different value */
r_if
c_cond
(paren
id|read
op_ne
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|time_after_eq
c_func
(paren
id|end_time
comma
id|jiffies
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n;  structures needed to upload elf code packets &n; */
DECL|typedef|snd_mixart_elf32_ehdr_t
r_typedef
r_struct
id|snd_mixart_elf32_ehdr
id|snd_mixart_elf32_ehdr_t
suffix:semicolon
DECL|struct|snd_mixart_elf32_ehdr
r_struct
id|snd_mixart_elf32_ehdr
(brace
DECL|member|e_ident
id|u8
id|e_ident
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|e_type
id|u16
id|e_type
suffix:semicolon
DECL|member|e_machine
id|u16
id|e_machine
suffix:semicolon
DECL|member|e_version
id|u32
id|e_version
suffix:semicolon
DECL|member|e_entry
id|u32
id|e_entry
suffix:semicolon
DECL|member|e_phoff
id|u32
id|e_phoff
suffix:semicolon
DECL|member|e_shoff
id|u32
id|e_shoff
suffix:semicolon
DECL|member|e_flags
id|u32
id|e_flags
suffix:semicolon
DECL|member|e_ehsize
id|u16
id|e_ehsize
suffix:semicolon
DECL|member|e_phentsize
id|u16
id|e_phentsize
suffix:semicolon
DECL|member|e_phnum
id|u16
id|e_phnum
suffix:semicolon
DECL|member|e_shentsize
id|u16
id|e_shentsize
suffix:semicolon
DECL|member|e_shnum
id|u16
id|e_shnum
suffix:semicolon
DECL|member|e_shstrndx
id|u16
id|e_shstrndx
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|snd_mixart_elf32_phdr_t
r_typedef
r_struct
id|snd_mixart_elf32_phdr
id|snd_mixart_elf32_phdr_t
suffix:semicolon
DECL|struct|snd_mixart_elf32_phdr
r_struct
id|snd_mixart_elf32_phdr
(brace
DECL|member|p_type
id|u32
id|p_type
suffix:semicolon
DECL|member|p_offset
id|u32
id|p_offset
suffix:semicolon
DECL|member|p_vaddr
id|u32
id|p_vaddr
suffix:semicolon
DECL|member|p_paddr
id|u32
id|p_paddr
suffix:semicolon
DECL|member|p_filesz
id|u32
id|p_filesz
suffix:semicolon
DECL|member|p_memsz
id|u32
id|p_memsz
suffix:semicolon
DECL|member|p_flags
id|u32
id|p_flags
suffix:semicolon
DECL|member|p_align
id|u32
id|p_align
suffix:semicolon
)brace
suffix:semicolon
DECL|function|mixart_load_elf
r_static
r_int
id|mixart_load_elf
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
comma
id|snd_hwdep_dsp_image_t
op_star
id|dsp
)paren
(brace
r_char
id|elf32_magic_number
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x7f
comma
l_char|&squot;E&squot;
comma
l_char|&squot;L&squot;
comma
l_char|&squot;F&squot;
)brace
suffix:semicolon
id|snd_mixart_elf32_ehdr_t
id|elf_header
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|elf_header
comma
id|dsp-&gt;image
comma
r_sizeof
(paren
id|snd_mixart_elf32_ehdr_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|elf32_magic_number
(braket
id|i
)braket
op_ne
id|elf_header.e_ident
(braket
id|i
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|elf_header.e_phoff
op_ne
l_int|0
)paren
(brace
id|snd_mixart_elf32_phdr_t
id|elf_programheader
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
id|be16_to_cpu
c_func
(paren
id|elf_header.e_phnum
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|pos
op_assign
id|be32_to_cpu
c_func
(paren
id|elf_header.e_phoff
)paren
op_plus
(paren
id|u32
)paren
(paren
id|i
op_star
id|be16_to_cpu
c_func
(paren
id|elf_header.e_phentsize
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|elf_programheader
comma
id|dsp-&gt;image
op_plus
id|pos
comma
r_sizeof
(paren
id|elf_programheader
)paren
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
id|elf_programheader.p_type
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|elf_programheader.p_filesz
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user_toio
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|be32_to_cpu
c_func
(paren
id|elf_programheader.p_vaddr
)paren
)paren
comma
id|dsp-&gt;image
op_plus
id|be32_to_cpu
c_func
(paren
id|elf_programheader.p_offset
)paren
comma
id|be32_to_cpu
c_func
(paren
id|elf_programheader.p_filesz
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_hwdep_dsp_status
r_static
r_int
id|mixart_hwdep_dsp_status
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_status_t
op_star
id|info
)paren
(brace
id|mixart_mgr_t
op_star
id|mgr
op_assign
id|hw-&gt;private_data
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;id
comma
l_string|&quot;miXart&quot;
)paren
suffix:semicolon
id|info-&gt;num_dsps
op_assign
id|MIXART_HARDW_FILES_MAX_INDEX
suffix:semicolon
r_if
c_cond
(paren
id|mgr-&gt;hwdep-&gt;dsp_loaded
op_amp
(paren
l_int|1
op_lshift
id|MIXART_MOTHERBOARD_ELF_INDEX
)paren
)paren
id|info-&gt;chip_ready
op_assign
l_int|1
suffix:semicolon
id|info-&gt;version
op_assign
id|MIXART_DRIVER_VERSION
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * get basic information and init miXart&n; */
multiline_comment|/* audio IDs for request to the board */
DECL|macro|MIXART_FIRST_ANA_AUDIO_ID
mdefine_line|#define MIXART_FIRST_ANA_AUDIO_ID       0
DECL|macro|MIXART_FIRST_DIG_AUDIO_ID
mdefine_line|#define MIXART_FIRST_DIG_AUDIO_ID       8
DECL|function|mixart_enum_connectors
r_static
r_int
id|mixart_enum_connectors
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
(brace
id|u32
id|k
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
id|mixart_enum_connector_resp_t
id|connector
suffix:semicolon
id|mixart_audio_info_req_t
id|audio_info_req
suffix:semicolon
id|mixart_audio_info_resp_t
id|audio_info
suffix:semicolon
id|audio_info_req.line_max_level
op_assign
id|MIXART_FLOAT_P_22_0_TO_HEX
suffix:semicolon
id|audio_info_req.micro_max_level
op_assign
id|MIXART_FLOAT_M_20_0_TO_HEX
suffix:semicolon
id|audio_info_req.cd_max_level
op_assign
id|MIXART_FLOAT____0_0_TO_HEX
suffix:semicolon
id|request.message_id
op_assign
id|MSG_SYSTEM_ENUM_PLAY_CONNECTOR
suffix:semicolon
id|request.uid
op_assign
(paren
id|mixart_uid_t
)paren
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* board num = 0 */
id|request.data
op_assign
l_int|NULL
suffix:semicolon
id|request.size
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|connector
)paren
comma
op_amp
id|connector
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
(paren
id|connector.error_code
)paren
op_logical_or
(paren
id|connector.uid_count
OG
id|MIXART_MAX_PHYS_CONNECTORS
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error MSG_SYSTEM_ENUM_PLAY_CONNECTOR&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|connector.uid_count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|mixart_pipe_t
op_star
id|pipe
suffix:semicolon
r_if
c_cond
(paren
id|k
OL
id|MIXART_FIRST_DIG_AUDIO_ID
)paren
(brace
id|pipe
op_assign
op_amp
id|mgr-&gt;chip
(braket
id|k
op_div
l_int|2
)braket
op_member_access_from_pointer
id|pipe_out_ana
suffix:semicolon
)brace
r_else
(brace
id|pipe
op_assign
op_amp
id|mgr-&gt;chip
(braket
(paren
id|k
op_minus
id|MIXART_FIRST_DIG_AUDIO_ID
)paren
op_div
l_int|2
)braket
op_member_access_from_pointer
id|pipe_out_dig
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
op_amp
l_int|1
)paren
(brace
id|pipe-&gt;uid_right_connector
op_assign
id|connector.uid
(braket
id|k
)braket
suffix:semicolon
multiline_comment|/* odd */
)brace
r_else
(brace
id|pipe-&gt;uid_left_connector
op_assign
id|connector.uid
(braket
id|k
)braket
suffix:semicolon
multiline_comment|/* even */
)brace
multiline_comment|/* snd_printk(KERN_DEBUG &quot;playback connector[%d].object_id = %x&bslash;n&quot;, k, connector.uid[k].object_id); */
multiline_comment|/* TODO: really need send_msg MSG_CONNECTOR_GET_AUDIO_INFO for each connector ? perhaps for analog level caps ? */
id|request.message_id
op_assign
id|MSG_CONNECTOR_GET_AUDIO_INFO
suffix:semicolon
id|request.uid
op_assign
id|connector.uid
(braket
id|k
)braket
suffix:semicolon
id|request.data
op_assign
op_amp
id|audio_info_req
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|audio_info_req
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|audio_info
)paren
comma
op_amp
id|audio_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error MSG_CONNECTOR_GET_AUDIO_INFO&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*snd_printk(KERN_DEBUG &quot;play  analog_info.analog_level_present = %x&bslash;n&quot;, audio_info.info.analog_info.analog_level_present);*/
)brace
id|request.message_id
op_assign
id|MSG_SYSTEM_ENUM_RECORD_CONNECTOR
suffix:semicolon
id|request.uid
op_assign
(paren
id|mixart_uid_t
)paren
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* board num = 0 */
id|request.data
op_assign
l_int|NULL
suffix:semicolon
id|request.size
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|connector
)paren
comma
op_amp
id|connector
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
(paren
id|connector.error_code
)paren
op_logical_or
(paren
id|connector.uid_count
OG
id|MIXART_MAX_PHYS_CONNECTORS
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error MSG_SYSTEM_ENUM_RECORD_CONNECTOR&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|connector.uid_count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|mixart_pipe_t
op_star
id|pipe
suffix:semicolon
r_if
c_cond
(paren
id|k
OL
id|MIXART_FIRST_DIG_AUDIO_ID
)paren
(brace
id|pipe
op_assign
op_amp
id|mgr-&gt;chip
(braket
id|k
op_div
l_int|2
)braket
op_member_access_from_pointer
id|pipe_in_ana
suffix:semicolon
)brace
r_else
(brace
id|pipe
op_assign
op_amp
id|mgr-&gt;chip
(braket
(paren
id|k
op_minus
id|MIXART_FIRST_DIG_AUDIO_ID
)paren
op_div
l_int|2
)braket
op_member_access_from_pointer
id|pipe_in_dig
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
op_amp
l_int|1
)paren
(brace
id|pipe-&gt;uid_right_connector
op_assign
id|connector.uid
(braket
id|k
)braket
suffix:semicolon
multiline_comment|/* odd */
)brace
r_else
(brace
id|pipe-&gt;uid_left_connector
op_assign
id|connector.uid
(braket
id|k
)braket
suffix:semicolon
multiline_comment|/* even */
)brace
multiline_comment|/* snd_printk(KERN_DEBUG &quot;capture connector[%d].object_id = %x&bslash;n&quot;, k, connector.uid[k].object_id); */
multiline_comment|/* TODO: really need send_msg MSG_CONNECTOR_GET_AUDIO_INFO for each connector ? perhaps for analog level caps ? */
id|request.message_id
op_assign
id|MSG_CONNECTOR_GET_AUDIO_INFO
suffix:semicolon
id|request.uid
op_assign
id|connector.uid
(braket
id|k
)braket
suffix:semicolon
id|request.data
op_assign
op_amp
id|audio_info_req
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|audio_info_req
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|audio_info
)paren
comma
op_amp
id|audio_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error MSG_CONNECTOR_GET_AUDIO_INFO&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*snd_printk(KERN_DEBUG &quot;rec  analog_info.analog_level_present = %x&bslash;n&quot;, audio_info.info.analog_info.analog_level_present);*/
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_enum_physio
r_static
r_int
id|mixart_enum_physio
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
(brace
id|u32
id|k
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
id|mixart_uid_t
id|get_console_mgr
suffix:semicolon
id|mixart_return_uid_t
id|console_mgr
suffix:semicolon
id|mixart_uid_enumeration_t
id|phys_io
suffix:semicolon
multiline_comment|/* get the uid for the console manager */
id|get_console_mgr.object_id
op_assign
l_int|0
suffix:semicolon
id|get_console_mgr.desc
op_assign
id|MSG_CONSOLE_MANAGER
op_or
l_int|0
suffix:semicolon
multiline_comment|/* cardindex = 0 */
id|request.message_id
op_assign
id|MSG_CONSOLE_GET_CLOCK_UID
suffix:semicolon
id|request.uid
op_assign
id|get_console_mgr
suffix:semicolon
id|request.data
op_assign
op_amp
id|get_console_mgr
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|get_console_mgr
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|console_mgr
)paren
comma
op_amp
id|console_mgr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
(paren
id|console_mgr.error_code
op_ne
l_int|0
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;error MSG_CONSOLE_GET_CLOCK_UID : err=%x&bslash;n&quot;
comma
id|console_mgr.error_code
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* used later for clock issues ! */
id|mgr-&gt;uid_console_manager
op_assign
id|console_mgr.uid
suffix:semicolon
id|request.message_id
op_assign
id|MSG_SYSTEM_ENUM_PHYSICAL_IO
suffix:semicolon
id|request.uid
op_assign
(paren
id|mixart_uid_t
)paren
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|request.data
op_assign
op_amp
id|console_mgr.uid
suffix:semicolon
id|request.size
op_assign
r_sizeof
(paren
id|console_mgr.uid
)paren
suffix:semicolon
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|phys_io
)paren
comma
op_amp
id|phys_io
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
(paren
id|phys_io.error_code
op_ne
l_int|0
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error MSG_SYSTEM_ENUM_PHYSICAL_IO err(%x) error_code(%x)&bslash;n&quot;
comma
id|err
comma
id|phys_io.error_code
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|snd_assert
c_func
(paren
id|phys_io.nb_uid
op_ge
(paren
id|MIXART_MAX_CARDS
op_star
l_int|2
)paren
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* min 2 phys io per card (analog in + analog out) */
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|mgr-&gt;num_cards
suffix:semicolon
id|k
op_increment
)paren
(brace
id|mgr-&gt;chip
(braket
id|k
)braket
op_member_access_from_pointer
id|uid_in_analog_physio
op_assign
id|phys_io.uid
(braket
id|k
)braket
suffix:semicolon
id|mgr-&gt;chip
(braket
id|k
)braket
op_member_access_from_pointer
id|uid_out_analog_physio
op_assign
id|phys_io.uid
(braket
id|phys_io.nb_uid
op_div
l_int|2
op_plus
id|k
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixart_first_init
r_static
r_int
id|mixart_first_init
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
(brace
id|u32
id|k
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mixart_msg_t
id|request
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|mixart_enum_connectors
c_func
(paren
id|mgr
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|mixart_enum_physio
c_func
(paren
id|mgr
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* send a synchro command to card (necessary to do this before first MSG_STREAM_START_STREAM_GRP_PACKET) */
multiline_comment|/* though why not here */
id|request.message_id
op_assign
id|MSG_SYSTEM_SEND_SYNCHRO_CMD
suffix:semicolon
id|request.uid
op_assign
(paren
id|mixart_uid_t
)paren
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|request.data
op_assign
l_int|NULL
suffix:semicolon
id|request.size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this command has no data. response is a 32 bit status */
id|err
op_assign
id|snd_mixart_send_msg
c_func
(paren
id|mgr
comma
op_amp
id|request
comma
r_sizeof
(paren
id|k
)paren
comma
op_amp
id|k
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_or
(paren
id|k
op_ne
l_int|0
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error MSG_SYSTEM_SEND_SYNCHRO_CMD&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
op_eq
l_int|0
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* firmware base addresses (when hard coded) */
DECL|macro|MIXART_MOTHERBOARD_XLX_BASE_ADDRESS
mdefine_line|#define MIXART_MOTHERBOARD_XLX_BASE_ADDRESS   0x00600000
DECL|function|mixart_hwdep_dsp_load
r_static
r_int
id|mixart_hwdep_dsp_load
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_image_t
op_star
id|dsp
)paren
(brace
id|mixart_mgr_t
op_star
id|mgr
op_assign
id|hw-&gt;private_data
suffix:semicolon
r_int
id|err
comma
id|card_index
suffix:semicolon
id|u32
id|status_xilinx
comma
id|status_elf
comma
id|status_daught
suffix:semicolon
id|u32
id|val
suffix:semicolon
multiline_comment|/* read motherboard xilinx status */
id|status_xilinx
op_assign
id|readl_be
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_MXLX_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* read elf status */
id|status_elf
op_assign
id|readl_be
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_ELF_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* read daughterboard xilinx status */
id|status_daught
op_assign
id|readl_be
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* motherboard xilinx status 5 will say that the board is performing a reset */
r_if
c_cond
(paren
id|status_xilinx
op_eq
l_int|5
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;miXart is resetting !&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* try again later */
)brace
r_switch
c_cond
(paren
id|dsp-&gt;index
)paren
(brace
r_case
id|MIXART_MOTHERBOARD_XLX_INDEX
suffix:colon
multiline_comment|/* xilinx already loaded ? */
r_if
c_cond
(paren
id|status_xilinx
op_eq
l_int|4
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;xilinx is already loaded !&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* the status should be 0 == &quot;idle&quot; */
r_if
c_cond
(paren
id|status_xilinx
op_ne
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xilinx load error ! status = %d&bslash;n&quot;
comma
id|status_xilinx
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* modprob -r may help ? */
)brace
multiline_comment|/* check xilinx validity */
id|snd_assert
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
(paren
id|dsp-&gt;image
)paren
)paren
(braket
l_int|0
)braket
op_eq
l_int|0xFFFFFFFF
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dsp-&gt;length
op_mod
l_int|4
op_eq
l_int|0
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* set xilinx status to copying */
id|writel_be
c_func
(paren
l_int|1
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_MXLX_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* setup xilinx base address */
id|writel_be
c_func
(paren
id|MIXART_MOTHERBOARD_XLX_BASE_ADDRESS
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* setup code size for xilinx file */
id|writel_be
c_func
(paren
id|dsp-&gt;length
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_MXLX_SIZE_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* copy xilinx code */
r_if
c_cond
(paren
id|copy_from_user_toio
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_MOTHERBOARD_XLX_BASE_ADDRESS
)paren
comma
id|dsp-&gt;image
comma
id|dsp-&gt;length
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* set xilinx status to copy finished */
id|writel_be
c_func
(paren
l_int|2
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_MXLX_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* return, because no further processing needed */
r_return
l_int|0
suffix:semicolon
r_case
id|MIXART_MOTHERBOARD_ELF_INDEX
suffix:colon
r_if
c_cond
(paren
id|status_elf
op_eq
l_int|4
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;elf file already loaded !&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* the status should be 0 == &quot;idle&quot; */
r_if
c_cond
(paren
id|status_elf
op_ne
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;elf load error ! status = %d&bslash;n&quot;
comma
id|status_elf
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* modprob -r may help ? */
)brace
multiline_comment|/* wait for xilinx status == 4 */
id|err
op_assign
id|mixart_wait_nice_for_register_value
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_MXLX_STATUS_OFFSET
comma
l_int|1
comma
l_int|4
comma
l_int|500
)paren
suffix:semicolon
multiline_comment|/* 5sec */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xilinx was not loaded or could not be started&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* init some data on the card */
id|writel_be
c_func
(paren
l_int|0
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_BOARDNUMBER
)paren
)paren
suffix:semicolon
multiline_comment|/* set miXart boardnumber to 0 */
id|writel_be
c_func
(paren
l_int|0
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_FLOWTABLE_PTR
)paren
)paren
suffix:semicolon
multiline_comment|/* reset pointer to flow table on miXart */
multiline_comment|/* set elf status to copying */
id|writel_be
c_func
(paren
l_int|1
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_ELF_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* process the copying of the elf packets */
id|err
op_assign
id|mixart_load_elf
c_func
(paren
id|mgr
comma
id|dsp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* set elf status to copy finished */
id|writel_be
c_func
(paren
l_int|2
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_ELF_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* wait for elf status == 4 */
id|err
op_assign
id|mixart_wait_nice_for_register_value
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_ELF_STATUS_OFFSET
comma
l_int|1
comma
l_int|4
comma
l_int|300
)paren
suffix:semicolon
multiline_comment|/* 3sec */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;elf could not be started&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* miXart waits at this point on the pointer to the flow table */
id|writel_be
c_func
(paren
(paren
id|u32
)paren
id|mgr-&gt;flowinfo.addr
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_FLOWTABLE_PTR
)paren
)paren
suffix:semicolon
multiline_comment|/* give pointer of flow table to miXart */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* return, another xilinx file has to be loaded before */
r_case
id|MIXART_AESEBUBOARD_XLX_INDEX
suffix:colon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* elf and xilinx should be loaded */
r_if
c_cond
(paren
(paren
id|status_elf
op_ne
l_int|4
)paren
op_logical_or
(paren
id|status_xilinx
op_ne
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xilinx or elf not successfully loaded&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* modprob -r may help ? */
)brace
multiline_comment|/* wait for daughter detection != 0 */
id|err
op_assign
id|mixart_wait_nice_for_register_value
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET
comma
l_int|0
comma
l_int|0
comma
l_int|30
)paren
suffix:semicolon
multiline_comment|/* 300msec */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error starting elf file&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* the board type can now be retrieved */
id|mgr-&gt;board_type
op_assign
(paren
id|DAUGHTER_TYPE_MASK
op_amp
id|readl_be
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DBRD_TYPE_OFFSET
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mgr-&gt;board_type
op_eq
id|MIXART_DAUGHTER_TYPE_NONE
)paren
r_break
suffix:semicolon
multiline_comment|/* no daughter board; the file does not have to be loaded, continue after the switch */
multiline_comment|/* only if aesebu daughter board presence (elf code must run)  */
r_if
c_cond
(paren
id|mgr-&gt;board_type
op_ne
id|MIXART_DAUGHTER_TYPE_AES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* daughter should be idle */
r_if
c_cond
(paren
id|status_daught
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;daughter load error ! status = %d&bslash;n&quot;
comma
id|status_daught
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* modprob -r may help ? */
)brace
multiline_comment|/* check daughterboard xilinx validity */
id|snd_assert
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
(paren
id|dsp-&gt;image
)paren
)paren
(braket
l_int|0
)braket
op_eq
l_int|0xFFFFFFFF
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dsp-&gt;length
op_mod
l_int|4
op_eq
l_int|0
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* inform mixart about the size of the file */
id|writel_be
c_func
(paren
id|dsp-&gt;length
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_SIZE_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* set daughterboard status to 1 */
id|writel_be
c_func
(paren
l_int|1
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* wait for status == 2 */
id|err
op_assign
id|mixart_wait_nice_for_register_value
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_STATUS_OFFSET
comma
l_int|1
comma
l_int|2
comma
l_int|30
)paren
suffix:semicolon
multiline_comment|/* 300msec */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;daughter board load error&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* get the address where to write the file */
id|val
op_assign
id|readl_be
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET
)paren
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|val
op_ne
l_int|0
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* copy daughterboard xilinx code */
r_if
c_cond
(paren
id|copy_from_user_toio
c_func
(paren
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|val
)paren
comma
id|dsp-&gt;image
comma
id|dsp-&gt;length
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* set daughterboard status to 4 */
id|writel_be
c_func
(paren
l_int|4
comma
id|MIXART_MEM
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_STATUS_OFFSET
)paren
)paren
suffix:semicolon
multiline_comment|/* continue with init */
r_break
suffix:semicolon
)brace
multiline_comment|/* end of switch file index*/
multiline_comment|/* wait for daughter status == 3 */
id|err
op_assign
id|mixart_wait_nice_for_register_value
c_func
(paren
id|mgr
comma
id|MIXART_PSEUDOREG_DXLX_STATUS_OFFSET
comma
l_int|1
comma
l_int|3
comma
l_int|300
)paren
suffix:semicolon
multiline_comment|/* 3sec */
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;daughter board could not be initialised&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* init mailbox (communication with embedded) */
id|snd_mixart_init_mailbox
c_func
(paren
id|mgr
)paren
suffix:semicolon
multiline_comment|/* first communication with embedded */
id|err
op_assign
id|mixart_first_init
c_func
(paren
id|mgr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;miXart could not be set up&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* create devices and mixer in accordance with HW options*/
r_for
c_loop
(paren
id|card_index
op_assign
l_int|0
suffix:semicolon
id|card_index
OL
id|mgr-&gt;num_cards
suffix:semicolon
id|card_index
op_increment
)paren
(brace
id|mixart_t
op_star
id|chip
op_assign
id|mgr-&gt;chip
(braket
id|card_index
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_mixart_create_pcm
c_func
(paren
id|chip
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|card_index
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_mixart_create_mixer
c_func
(paren
id|chip-&gt;mgr
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|chip-&gt;card
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;miXart firmware downloaded and successfully set up&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_mixart_hwdep_new
r_int
id|snd_mixart_hwdep_new
c_func
(paren
id|mixart_mgr_t
op_star
id|mgr
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_hwdep_t
op_star
id|hw
suffix:semicolon
multiline_comment|/* only create hwdep interface for first cardX (see &quot;index&quot; module parameter)*/
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_hwdep_new
c_func
(paren
id|mgr-&gt;chip
(braket
l_int|0
)braket
op_member_access_from_pointer
id|card
comma
id|SND_MIXART_HWDEP_ID
comma
l_int|0
comma
op_amp
id|hw
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|hw-&gt;iface
op_assign
id|SNDRV_HWDEP_IFACE_MIXART
suffix:semicolon
id|hw-&gt;private_data
op_assign
id|mgr
suffix:semicolon
id|hw-&gt;ops.open
op_assign
id|mixart_hwdep_open
suffix:semicolon
id|hw-&gt;ops.release
op_assign
id|mixart_hwdep_release
suffix:semicolon
id|hw-&gt;ops.dsp_status
op_assign
id|mixart_hwdep_dsp_status
suffix:semicolon
id|hw-&gt;ops.dsp_load
op_assign
id|mixart_hwdep_dsp_load
suffix:semicolon
id|hw-&gt;exclusive
op_assign
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|hw-&gt;name
comma
id|SND_MIXART_HWDEP_ID
)paren
suffix:semicolon
id|mgr-&gt;hwdep
op_assign
id|hw
suffix:semicolon
id|mgr-&gt;hwdep-&gt;dsp_loaded
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
