multiline_comment|/*&n; * Diva Server PRI specific part of initialisation&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.5  &n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &quot;sys.h&quot;
macro_line|#include &quot;idi.h&quot;
macro_line|#include &quot;divas.h&quot;
macro_line|#include &quot;pc.h&quot;
macro_line|#include &quot;pr_pc.h&quot;
macro_line|#include &quot;dsp_defs.h&quot;
macro_line|#include &quot;adapter.h&quot;
macro_line|#include &quot;uxio.h&quot;
DECL|macro|DIVAS_LOAD_CMD
mdefine_line|#define&t;DIVAS_LOAD_CMD&t;&t;0x02
DECL|macro|DIVAS_START_CMD
mdefine_line|#define&t;DIVAS_START_CMD&t;&t;0x03
DECL|macro|DIVAS_IRQ_RESET
mdefine_line|#define&t;DIVAS_IRQ_RESET&t;&t;0xC18
DECL|macro|DIVAS_IRQ_RESET_VAL
mdefine_line|#define DIVAS_IRQ_RESET_VAL&t;0xFE
DECL|macro|TEST_INT_DIVAS
mdefine_line|#define&t;TEST_INT_DIVAS&t;&t;0x11
DECL|macro|TEST_INT_DIVAS_BRI
mdefine_line|#define TEST_INT_DIVAS_BRI&t;0x12
DECL|macro|DIVAS_RESET
mdefine_line|#define DIVAS_RESET&t;0x81
DECL|macro|DIVAS_LED1
mdefine_line|#define DIVAS_LED1&t;0x04
DECL|macro|DIVAS_LED2
mdefine_line|#define DIVAS_LED2&t;0x08
DECL|macro|DIVAS_LED3
mdefine_line|#define DIVAS_LED3&t;0x20
DECL|macro|DIVAS_LED4
mdefine_line|#define DIVAS_LED4&t;0x40
DECL|macro|DIVAS_RESET_REG
mdefine_line|#define&t;DIVAS_RESET_REG&t;&t;0x20
DECL|macro|DIVAS_SIGNATURE
mdefine_line|#define&t;DIVAS_SIGNATURE&t;0x4447
multiline_comment|/* offset to start of MAINT area (used by xlog) */
DECL|macro|DIVAS_MAINT_OFFSET
mdefine_line|#define&t;DIVAS_MAINT_OFFSET&t;0xef00&t;/* value for PRI card */
DECL|macro|MP_PROTOCOL_ADDR
mdefine_line|#define MP_PROTOCOL_ADDR&t;&t;0xA0011000
DECL|macro|MP_DSP_CODE_BASE
mdefine_line|#define MP_DSP_CODE_BASE&t;&t;0xa03a0000  
r_typedef
r_struct
(brace
DECL|member|cmd
id|dword
id|cmd
suffix:semicolon
DECL|member|addr
id|dword
id|addr
suffix:semicolon
DECL|member|len
id|dword
id|len
suffix:semicolon
DECL|member|err
id|dword
id|err
suffix:semicolon
DECL|member|live
id|dword
id|live
suffix:semicolon
DECL|member|reserved
id|dword
id|reserved
(braket
(paren
l_int|0x1020
op_rshift
l_int|2
)paren
op_minus
l_int|6
)braket
suffix:semicolon
DECL|member|signature
id|dword
id|signature
suffix:semicolon
DECL|member|data
id|byte
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|diva_server_boot_t
)brace
id|diva_server_boot_t
suffix:semicolon
id|byte
id|mem_in
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
id|word
id|mem_inw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
r_void
id|mem_in_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|mem_look_ahead
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|PBUFFER
op_star
id|RBuffer
comma
id|ENTITY
op_star
id|e
)paren
suffix:semicolon
r_void
id|mem_out
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|byte
id|data
)paren
suffix:semicolon
r_void
id|mem_outw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|word
id|data
)paren
suffix:semicolon
r_void
id|mem_out_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|mem_inc
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
r_int
id|DivasPRIInitPCI
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_card_t
op_star
id|cfg
)paren
suffix:semicolon
r_static
r_int
id|pri_ISR
(paren
id|card_t
op_star
id|card
)paren
suffix:semicolon
DECL|function|diva_server_reset
r_static
r_int
id|diva_server_reset
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
id|byte
op_star
id|reg
suffix:semicolon
id|diva_server_boot_t
op_star
id|boot
op_assign
l_int|NULL
suffix:semicolon
id|dword
id|live
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|dword
id|dwWait
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: reset Diva Server PRI&quot;
)paren
)paren
suffix:semicolon
id|reg
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_REG_MEMORY
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|reg
(braket
id|DIVAS_RESET_REG
)braket
comma
id|DIVAS_RESET
op_or
id|DIVAS_LED1
op_or
id|DIVAS_LED2
op_or
id|DIVAS_LED3
op_or
id|DIVAS_LED4
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dwWait
op_assign
l_int|0x000fffff
suffix:semicolon
id|dwWait
suffix:semicolon
id|dwWait
op_decrement
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|reg
(braket
id|DIVAS_RESET_REG
)braket
comma
l_int|0x00
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dwWait
op_assign
l_int|0x000fffff
suffix:semicolon
id|dwWait
suffix:semicolon
id|dwWait
op_decrement
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|reg
)paren
suffix:semicolon
id|boot
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_RAM_MEMORY
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
id|boot-&gt;reserved
comma
l_int|0
)paren
suffix:semicolon
id|live
op_assign
id|UxCardMemInD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;live
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|live
op_ne
id|UxCardMemInD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;live
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|UxPause
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|5
)paren
(brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: card is reset but CPU not running&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: card reset after %d ms&quot;
comma
id|i
op_star
l_int|10
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diva_server_config
r_static
r_int
id|diva_server_config
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_config_t
op_star
id|config
)paren
(brace
id|byte
op_star
id|shared
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: configure Diva Server PRI&quot;
)paren
)paren
suffix:semicolon
id|shared
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|UxCardLog
c_func
(paren
l_int|0
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|8
)braket
comma
id|config-&gt;tei
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|9
)braket
comma
id|config-&gt;nt2
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|10
)braket
comma
id|config-&gt;sig_flags
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|11
)braket
comma
id|config-&gt;watchdog
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|12
)braket
comma
id|config-&gt;permanent
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|13
)braket
comma
id|config-&gt;x_interface
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|14
)braket
comma
id|config-&gt;stable_l2
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|15
)braket
comma
id|config-&gt;no_order_check
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|16
)braket
comma
id|config-&gt;handset_type
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|17
)braket
comma
l_int|0
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|18
)braket
comma
id|config-&gt;low_channel
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|19
)braket
comma
id|config-&gt;prot_version
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|20
)braket
comma
id|config-&gt;crc4
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|32
suffix:semicolon
id|j
op_increment
)paren
(brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|32
op_plus
(paren
id|i
op_star
l_int|96
)paren
op_plus
id|j
)braket
comma
id|config-&gt;terminal
(braket
id|i
)braket
dot
id|oad
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|32
suffix:semicolon
id|j
op_increment
)paren
(brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|64
op_plus
(paren
id|i
op_star
l_int|96
)paren
op_plus
id|j
)braket
comma
id|config-&gt;terminal
(braket
id|i
)braket
dot
id|osa
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|32
suffix:semicolon
id|j
op_increment
)paren
(brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|96
op_plus
(paren
id|i
op_star
l_int|96
)paren
op_plus
id|j
)braket
comma
id|config-&gt;terminal
(braket
id|i
)braket
dot
id|spid
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
)brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|shared
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|diva_server_reset_int
r_void
id|diva_server_reset_int
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
id|byte
op_star
id|cfg
suffix:semicolon
id|cfg
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_CFG_MEMORY
)paren
suffix:semicolon
id|UxCardMemOutW
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|cfg
(braket
id|DIVAS_IRQ_RESET
)braket
comma
id|DIVAS_IRQ_RESET_VAL
)paren
suffix:semicolon
id|UxCardMemOutW
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|cfg
(braket
id|DIVAS_IRQ_RESET
op_plus
l_int|2
)braket
comma
l_int|0
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|cfg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|diva_server_test_int
r_static
r_int
id|diva_server_test_int
c_func
(paren
id|card_t
op_star
id|card
)paren
(brace
r_int
id|i
suffix:semicolon
id|byte
op_star
id|shared
suffix:semicolon
id|byte
id|req_int
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: test interrupt for Diva Server PRI&quot;
)paren
)paren
suffix:semicolon
id|shared
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|0x3FE
)braket
)paren
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|0x3FE
)braket
comma
l_int|0
)paren
suffix:semicolon
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|shared
(braket
l_int|0x3FE
)braket
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|shared
)paren
suffix:semicolon
id|diva_server_reset_int
c_func
(paren
id|card
)paren
suffix:semicolon
id|shared
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_SHARED_MEMORY
)paren
suffix:semicolon
id|card-&gt;test_int_pend
op_assign
id|TEST_INT_DIVAS
suffix:semicolon
id|req_int
op_assign
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
op_amp
(paren
(paren
(paren
r_struct
id|pr_ram
op_star
)paren
id|shared
)paren
op_member_access_from_pointer
id|ReadyInt
)paren
)paren
suffix:semicolon
id|req_int
op_increment
suffix:semicolon
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
(paren
(paren
(paren
r_struct
id|pr_ram
op_star
)paren
id|shared
)paren
op_member_access_from_pointer
id|ReadyInt
)paren
comma
id|req_int
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|shared
)paren
suffix:semicolon
id|UxCardLog
c_func
(paren
l_int|0
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
l_int|50
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;test_int_pend
)paren
(brace
r_break
suffix:semicolon
)brace
id|UxPause
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;test_int_pend
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;active: timeout waiting for card to interrupt&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_hdr
r_static
r_void
id|print_hdr
c_func
(paren
r_int
r_char
op_star
id|code
comma
r_int
id|offset
)paren
(brace
r_int
r_char
id|hdr
(braket
l_int|80
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
OL
(paren
id|DIM
c_func
(paren
id|hdr
)paren
op_minus
l_int|1
)paren
)paren
op_logical_and
(paren
id|code
(braket
id|offset
op_plus
id|i
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_and
(paren
id|code
(braket
id|offset
op_plus
id|i
)braket
op_ne
l_char|&squot;&bslash;r&squot;
)paren
op_logical_and
(paren
id|code
(braket
id|offset
op_plus
id|i
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
)paren
(brace
id|hdr
(braket
id|i
)braket
op_assign
id|code
(braket
id|offset
op_plus
id|i
)braket
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|hdr
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: loading %s&quot;
comma
id|hdr
)paren
)paren
suffix:semicolon
)brace
DECL|function|diva_server_load
r_static
r_int
id|diva_server_load
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_load_t
op_star
id|load
)paren
(brace
id|diva_server_boot_t
op_star
id|boot
suffix:semicolon
r_int
id|i
comma
id|offset
comma
id|length
suffix:semicolon
id|dword
id|cmd
op_assign
l_int|0
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: loading Diva Server PRI&quot;
)paren
)paren
suffix:semicolon
id|boot
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_RAM_MEMORY
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|load-&gt;code_type
)paren
(brace
r_case
id|DIA_CPU_CODE
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: RISC code&quot;
)paren
)paren
suffix:semicolon
id|print_hdr
c_func
(paren
id|load-&gt;code
comma
l_int|0x80
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;addr
comma
id|MP_PROTOCOL_ADDR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_DSP_CODE
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: DSP code&quot;
)paren
)paren
suffix:semicolon
id|print_hdr
c_func
(paren
id|load-&gt;code
comma
l_int|0x0
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;addr
comma
(paren
id|MP_DSP_CODE_BASE
op_plus
(paren
(paren
(paren
r_sizeof
(paren
id|dword
)paren
op_plus
(paren
r_sizeof
(paren
id|t_dsp_download_desc
)paren
op_star
id|DSP_MAX_DOWNLOAD_COUNT
)paren
)paren
op_plus
op_complement
id|ALIGNMENT_MASK_MAESTRA
)paren
op_amp
id|ALIGNMENT_MASK_MAESTRA
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_TABLE_CODE
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: TABLE code&quot;
)paren
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;addr
comma
(paren
id|MP_DSP_CODE_BASE
op_plus
r_sizeof
(paren
id|dword
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_CONT_CODE
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: continuation code&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_DLOAD_CNT
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: COUNT code&quot;
)paren
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;addr
comma
id|MP_DSP_CODE_BASE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: unknown code type&quot;
)paren
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|UxCardLog
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|length
op_assign
(paren
id|load-&gt;length
op_minus
id|offset
op_ge
l_int|400
)paren
ques
c_cond
l_int|400
suffix:colon
id|load-&gt;length
op_minus
id|offset
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
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|UxCardMemOut
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;data
(braket
id|i
)braket
comma
id|load-&gt;code
(braket
id|offset
op_plus
id|i
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|load-&gt;code
(braket
id|offset
op_plus
id|i
)braket
op_ne
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;data
(braket
id|i
)braket
)paren
)paren
(brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: card code block verify failed&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;len
comma
(paren
id|length
op_plus
l_int|3
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;cmd
comma
id|DIVAS_LOAD_CMD
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
l_int|50000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cmd
op_assign
id|UxCardMemInD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmd
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/*UxPause(1);*/
)brace
r_if
c_cond
(paren
id|cmd
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: timeout waiting for card to ACK load (offset = %d)&quot;
comma
id|offset
)paren
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|offset
op_add_assign
id|length
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
id|load-&gt;length
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: DIVA Server card loaded&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diva_server_start
r_static
r_int
id|diva_server_start
c_func
(paren
id|card_t
op_star
id|card
comma
id|byte
op_star
id|channels
)paren
(brace
id|diva_server_boot_t
op_star
id|boot
suffix:semicolon
id|byte
op_star
id|ram
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dword
id|signature
op_assign
l_int|0
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: start Diva Server PRI&quot;
)paren
)paren
suffix:semicolon
id|card-&gt;is_live
op_assign
id|FALSE
suffix:semicolon
id|boot
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_RAM_MEMORY
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;addr
comma
id|MP_PROTOCOL_ADDR
)paren
suffix:semicolon
id|UxCardMemOutD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;cmd
comma
id|DIVAS_START_CMD
)paren
suffix:semicolon
id|UxCardLog
c_func
(paren
l_int|0
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
l_int|300
suffix:semicolon
id|i
op_increment
)paren
(brace
id|signature
op_assign
id|UxCardMemInD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|boot-&gt;signature
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|signature
op_rshift
l_int|16
)paren
op_eq
id|DIVAS_SIGNATURE
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: started card after %d ms&quot;
comma
id|i
op_star
l_int|10
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|UxPause
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|signature
op_rshift
l_int|16
)paren
op_ne
id|DIVAS_SIGNATURE
)paren
(brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: timeout waiting for card to run protocol code (sig = 0x%x)&quot;
comma
id|signature
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|card-&gt;is_live
op_assign
id|TRUE
suffix:semicolon
id|ram
op_assign
(paren
id|byte
op_star
)paren
id|boot
suffix:semicolon
id|ram
op_add_assign
id|DIVAS_SHARED_OFFSET
suffix:semicolon
op_star
id|channels
op_assign
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|ram
(braket
l_int|0x3F6
)braket
)paren
suffix:semicolon
id|card-&gt;serial_no
op_assign
id|UxCardMemInD
c_func
(paren
id|card-&gt;hw
comma
op_amp
id|ram
(braket
l_int|0x3F0
)braket
)paren
suffix:semicolon
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|boot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diva_server_test_int
c_func
(paren
id|card
)paren
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: interrupt test failed&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: DIVA Server card started&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|diva_server_mem_get
r_int
id|diva_server_mem_get
c_func
(paren
id|card_t
op_star
id|card
comma
id|mem_block_t
op_star
id|mem_block
)paren
(brace
id|byte
op_star
id|a
suffix:semicolon
id|byte
op_star
id|card_addr
suffix:semicolon
id|word
id|length
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|a
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_RAM_MEMORY
)paren
suffix:semicolon
id|card_addr
op_assign
id|a
suffix:semicolon
id|card_addr
op_add_assign
id|mem_block-&gt;addr
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
id|mem_block-&gt;data
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mem_block-&gt;data
(braket
id|i
)braket
op_assign
id|UxCardMemIn
c_func
(paren
id|card-&gt;hw
comma
id|card_addr
)paren
suffix:semicolon
id|card_addr
op_increment
suffix:semicolon
id|length
op_increment
suffix:semicolon
)brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|a
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise PRI specific entry points&n; */
DECL|function|DivasPriInit
r_int
id|DivasPriInit
c_func
(paren
id|card_t
op_star
id|card
comma
id|dia_card_t
op_star
id|cfg
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: initialise Diva Server PRI&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DivasPRIInitPCI
c_func
(paren
id|card
comma
id|cfg
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|card-&gt;card_reset
op_assign
id|diva_server_reset
suffix:semicolon
id|card-&gt;card_load
op_assign
id|diva_server_load
suffix:semicolon
id|card-&gt;card_config
op_assign
id|diva_server_config
suffix:semicolon
id|card-&gt;card_start
op_assign
id|diva_server_start
suffix:semicolon
id|card-&gt;reset_int
op_assign
id|diva_server_reset_int
suffix:semicolon
id|card-&gt;card_mem_get
op_assign
id|diva_server_mem_get
suffix:semicolon
id|card-&gt;xlog_offset
op_assign
id|DIVAS_MAINT_OFFSET
suffix:semicolon
id|card-&gt;out
op_assign
id|DivasOut
suffix:semicolon
id|card-&gt;test_int
op_assign
id|DivasTestInt
suffix:semicolon
id|card-&gt;dpc
op_assign
id|DivasDpc
suffix:semicolon
id|card-&gt;clear_int
op_assign
id|DivasClearInt
suffix:semicolon
id|card-&gt;card_isr
op_assign
id|pri_ISR
suffix:semicolon
id|card-&gt;a.ram_out
op_assign
id|mem_out
suffix:semicolon
id|card-&gt;a.ram_outw
op_assign
id|mem_outw
suffix:semicolon
id|card-&gt;a.ram_out_buffer
op_assign
id|mem_out_buffer
suffix:semicolon
id|card-&gt;a.ram_inc
op_assign
id|mem_inc
suffix:semicolon
id|card-&gt;a.ram_in
op_assign
id|mem_in
suffix:semicolon
id|card-&gt;a.ram_inw
op_assign
id|mem_inw
suffix:semicolon
id|card-&gt;a.ram_in_buffer
op_assign
id|mem_in_buffer
suffix:semicolon
id|card-&gt;a.ram_look_ahead
op_assign
id|mem_look_ahead
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pri_ISR
r_static
r_int
id|pri_ISR
(paren
id|card_t
op_star
id|card
)paren
(brace
r_int
id|served
op_assign
l_int|0
suffix:semicolon
id|byte
op_star
id|cfg
op_assign
id|UxCardMemAttach
c_func
(paren
id|card-&gt;hw
comma
id|DIVAS_CFG_MEMORY
)paren
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|isr
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|cfg
(braket
id|DIVAS_IRQ_RESET
)braket
suffix:semicolon
r_register
r_int
r_int
id|val
op_assign
op_star
id|isr
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x80000000
)paren
multiline_comment|/* our card had caused interrupt ??? */
(brace
id|served
op_assign
l_int|1
suffix:semicolon
id|card-&gt;int_pend
op_add_assign
l_int|1
suffix:semicolon
id|DivasDpcSchedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ISR DPC */
op_star
id|isr
op_assign
(paren
r_int
r_int
)paren
op_complement
l_int|0x03E00000
suffix:semicolon
multiline_comment|/* Clear interrupt line */
)brace
id|UxCardMemDetach
c_func
(paren
id|card-&gt;hw
comma
id|cfg
)paren
suffix:semicolon
r_return
(paren
id|served
op_ne
l_int|0
)paren
suffix:semicolon
)brace
eof
