multiline_comment|/* $Id: isdn_tty.h,v 1.22.6.2 2001/09/23 22:24:32 kai Exp $&n; *&n; * header for Linux ISDN subsystem, tty related functions (linklevel).&n; *&n; * Copyright 1994-1999  by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DLE
mdefine_line|#define DLE 0x10
DECL|macro|ETX
mdefine_line|#define ETX 0x03
DECL|macro|DC4
mdefine_line|#define DC4 0x14
multiline_comment|/*&n; * Definition of some special Registers of AT-Emulator&n; */
DECL|macro|REG_RINGATA
mdefine_line|#define REG_RINGATA   0
DECL|macro|REG_RINGCNT
mdefine_line|#define REG_RINGCNT   1  /* ring counter register */
DECL|macro|REG_ESC
mdefine_line|#define REG_ESC       2
DECL|macro|REG_CR
mdefine_line|#define REG_CR        3
DECL|macro|REG_LF
mdefine_line|#define REG_LF        4
DECL|macro|REG_BS
mdefine_line|#define REG_BS        5
DECL|macro|REG_WAITC
mdefine_line|#define REG_WAITC     7
DECL|macro|REG_RESP
mdefine_line|#define REG_RESP     12  /* show response messages register */
DECL|macro|BIT_RESP
mdefine_line|#define BIT_RESP      1  /* show response messages bit      */
DECL|macro|REG_RESPNUM
mdefine_line|#define REG_RESPNUM  12  /* show numeric responses register */
DECL|macro|BIT_RESPNUM
mdefine_line|#define BIT_RESPNUM   2  /* show numeric responses bit      */
DECL|macro|REG_ECHO
mdefine_line|#define REG_ECHO     12
DECL|macro|BIT_ECHO
mdefine_line|#define BIT_ECHO      4
DECL|macro|REG_DCD
mdefine_line|#define REG_DCD      12
DECL|macro|BIT_DCD
mdefine_line|#define BIT_DCD       8
DECL|macro|REG_CTS
mdefine_line|#define REG_CTS      12
DECL|macro|BIT_CTS
mdefine_line|#define BIT_CTS      16
DECL|macro|REG_DTRR
mdefine_line|#define REG_DTRR     12
DECL|macro|BIT_DTRR
mdefine_line|#define BIT_DTRR     32
DECL|macro|REG_DSR
mdefine_line|#define REG_DSR      12
DECL|macro|BIT_DSR
mdefine_line|#define BIT_DSR      64
DECL|macro|REG_CPPP
mdefine_line|#define REG_CPPP     12
DECL|macro|BIT_CPPP
mdefine_line|#define BIT_CPPP    128
DECL|macro|REG_DXMT
mdefine_line|#define REG_DXMT     13
DECL|macro|BIT_DXMT
mdefine_line|#define BIT_DXMT      1
DECL|macro|REG_T70
mdefine_line|#define REG_T70      13
DECL|macro|BIT_T70
mdefine_line|#define BIT_T70       2
DECL|macro|BIT_T70_EXT
mdefine_line|#define BIT_T70_EXT  32
DECL|macro|REG_DTRHUP
mdefine_line|#define REG_DTRHUP   13
DECL|macro|BIT_DTRHUP
mdefine_line|#define BIT_DTRHUP    4
DECL|macro|REG_RESPXT
mdefine_line|#define REG_RESPXT   13
DECL|macro|BIT_RESPXT
mdefine_line|#define BIT_RESPXT    8
DECL|macro|REG_CIDONCE
mdefine_line|#define REG_CIDONCE  13
DECL|macro|BIT_CIDONCE
mdefine_line|#define BIT_CIDONCE  16
DECL|macro|REG_RUNG
mdefine_line|#define REG_RUNG     13  /* show RUNG message register      */
DECL|macro|BIT_RUNG
mdefine_line|#define BIT_RUNG     64  /* show RUNG message bit           */
DECL|macro|REG_DISPLAY
mdefine_line|#define REG_DISPLAY  13
DECL|macro|BIT_DISPLAY
mdefine_line|#define BIT_DISPLAY 128
DECL|macro|REG_L2PROT
mdefine_line|#define REG_L2PROT   14
DECL|macro|REG_L3PROT
mdefine_line|#define REG_L3PROT   15
DECL|macro|REG_PSIZE
mdefine_line|#define REG_PSIZE    16
DECL|macro|REG_WSIZE
mdefine_line|#define REG_WSIZE    17
DECL|macro|REG_SI1
mdefine_line|#define REG_SI1      18
DECL|macro|REG_SI2
mdefine_line|#define REG_SI2      19
DECL|macro|REG_SI1I
mdefine_line|#define REG_SI1I     20
DECL|macro|REG_PLAN
mdefine_line|#define REG_PLAN     21
DECL|macro|REG_SCREEN
mdefine_line|#define REG_SCREEN   22
DECL|macro|REG_CPN
mdefine_line|#define REG_CPN      23
DECL|macro|BIT_CPN
mdefine_line|#define BIT_CPN       1
DECL|macro|REG_CPNFCON
mdefine_line|#define REG_CPNFCON  23
DECL|macro|BIT_CPNFCON
mdefine_line|#define BIT_CPNFCON   2
DECL|macro|REG_CDN
mdefine_line|#define REG_CDN      23
DECL|macro|BIT_CDN
mdefine_line|#define BIT_CDN       4
multiline_comment|/* defines for result codes */
DECL|macro|RESULT_OK
mdefine_line|#define RESULT_OK&t;&t;0
DECL|macro|RESULT_CONNECT
mdefine_line|#define RESULT_CONNECT&t;&t;1
DECL|macro|RESULT_RING
mdefine_line|#define RESULT_RING&t;&t;2
DECL|macro|RESULT_NO_CARRIER
mdefine_line|#define RESULT_NO_CARRIER&t;3
DECL|macro|RESULT_ERROR
mdefine_line|#define RESULT_ERROR&t;&t;4
DECL|macro|RESULT_CONNECT64000
mdefine_line|#define RESULT_CONNECT64000&t;5
DECL|macro|RESULT_NO_DIALTONE
mdefine_line|#define RESULT_NO_DIALTONE&t;6
DECL|macro|RESULT_BUSY
mdefine_line|#define RESULT_BUSY&t;&t;7
DECL|macro|RESULT_NO_ANSWER
mdefine_line|#define RESULT_NO_ANSWER&t;8
DECL|macro|RESULT_RINGING
mdefine_line|#define RESULT_RINGING&t;&t;9
DECL|macro|RESULT_NO_MSN_EAZ
mdefine_line|#define RESULT_NO_MSN_EAZ&t;10
DECL|macro|RESULT_VCON
mdefine_line|#define RESULT_VCON&t;&t;11
DECL|macro|RESULT_RUNG
mdefine_line|#define RESULT_RUNG&t;&t;12
DECL|macro|TTY_IS_FCLASS1
mdefine_line|#define TTY_IS_FCLASS1(info) &bslash;&n;&t;((info-&gt;emu.mdmreg[REG_L2PROT] == ISDN_PROTO_L2_FAX) &amp;&amp; &bslash;&n;&t; (info-&gt;emu.mdmreg[REG_L3PROT] == ISDN_PROTO_L3_FCLASS1))
DECL|macro|TTY_IS_FCLASS2
mdefine_line|#define TTY_IS_FCLASS2(info) &bslash;&n;&t;((info-&gt;emu.mdmreg[REG_L2PROT] == ISDN_PROTO_L2_FAX) &amp;&amp; &bslash;&n;&t; (info-&gt;emu.mdmreg[REG_L3PROT] == ISDN_PROTO_L3_FCLASS2))
r_extern
r_void
id|isdn_tty_modem_escape
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_modem_ring
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_carrier_timeout
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_modem_xmit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_modem_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_readmodem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_find_icall
c_func
(paren
r_int
comma
r_int
comma
id|setup_parm
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_cleanup_xmit
c_func
(paren
id|modem_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_stat_callback
c_func
(paren
r_int
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_rcv_skb
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_capi_facility
c_func
(paren
id|capi_msg
op_star
id|cm
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_at_cout
c_func
(paren
r_char
op_star
comma
id|modem_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_modem_hup
c_func
(paren
id|modem_info
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
r_extern
r_int
id|isdn_tty_cmd_PLUSF_FAX
c_func
(paren
r_char
op_star
op_star
comma
id|modem_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_fax_command
c_func
(paren
id|modem_info
op_star
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_fax_bitorder
c_func
(paren
id|modem_info
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
