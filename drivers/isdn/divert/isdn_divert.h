multiline_comment|/* $Id: isdn_divert.h,v 1.5.6.1 2001/09/23 22:24:36 kai Exp $&n; *&n; * Header for the diversion supplementary ioctl interface.&n; *&n; * Copyright 1998       by Werner Cornelius (werner@ikt.de)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/******************************************/
multiline_comment|/* IOCTL codes for interface to user prog */
multiline_comment|/******************************************/
DECL|macro|DIVERT_IIOC_VERSION
mdefine_line|#define DIVERT_IIOC_VERSION 0x01 /* actual version */
DECL|macro|IIOCGETVER
mdefine_line|#define IIOCGETVER   _IO(&squot;I&squot;, 1)  /* get version of interface */
DECL|macro|IIOCGETDRV
mdefine_line|#define IIOCGETDRV   _IO(&squot;I&squot;, 2)  /* get driver number */
DECL|macro|IIOCGETNAM
mdefine_line|#define IIOCGETNAM   _IO(&squot;I&squot;, 3)  /* get driver name */
DECL|macro|IIOCGETRULE
mdefine_line|#define IIOCGETRULE  _IO(&squot;I&squot;, 4)  /* read one rule */
DECL|macro|IIOCMODRULE
mdefine_line|#define IIOCMODRULE  _IO(&squot;I&squot;, 5)  /* modify/replace a rule */  
DECL|macro|IIOCINSRULE
mdefine_line|#define IIOCINSRULE  _IO(&squot;I&squot;, 6)  /* insert/append one rule */
DECL|macro|IIOCDELRULE
mdefine_line|#define IIOCDELRULE  _IO(&squot;I&squot;, 7)  /* delete a rule */
DECL|macro|IIOCDODFACT
mdefine_line|#define IIOCDODFACT  _IO(&squot;I&squot;, 8)  /* hangup/reject/alert/immediately deflect a call */
DECL|macro|IIOCDOCFACT
mdefine_line|#define IIOCDOCFACT  _IO(&squot;I&squot;, 9)  /* activate control forwarding in PBX */
DECL|macro|IIOCDOCFDIS
mdefine_line|#define IIOCDOCFDIS  _IO(&squot;I&squot;,10)  /* deactivate control forwarding in PBX */
DECL|macro|IIOCDOCFINT
mdefine_line|#define IIOCDOCFINT  _IO(&squot;I&squot;,11)  /* interrogate control forwarding in PBX */
multiline_comment|/*************************************/
multiline_comment|/* states reported through interface */
multiline_comment|/*************************************/
DECL|macro|DEFLECT_IGNORE
mdefine_line|#define DEFLECT_IGNORE    0  /* ignore incoming call */
DECL|macro|DEFLECT_REPORT
mdefine_line|#define DEFLECT_REPORT    1  /* only report */
DECL|macro|DEFLECT_PROCEED
mdefine_line|#define DEFLECT_PROCEED   2  /* deflect when externally triggered */
DECL|macro|DEFLECT_ALERT
mdefine_line|#define DEFLECT_ALERT     3  /* alert and deflect after delay */ 
DECL|macro|DEFLECT_REJECT
mdefine_line|#define DEFLECT_REJECT    4  /* reject immediately */
DECL|macro|DIVERT_ACTIVATE
mdefine_line|#define DIVERT_ACTIVATE   5  /* diversion activate */
DECL|macro|DIVERT_DEACTIVATE
mdefine_line|#define DIVERT_DEACTIVATE 6  /* diversion deactivate */
DECL|macro|DIVERT_REPORT
mdefine_line|#define DIVERT_REPORT     7  /* interrogation result */ 
DECL|macro|DEFLECT_AUTODEL
mdefine_line|#define DEFLECT_AUTODEL 255  /* only for internal use */ 
DECL|macro|DEFLECT_ALL_IDS
mdefine_line|#define DEFLECT_ALL_IDS   0xFFFFFFFF /* all drivers selected */
r_typedef
r_struct
DECL|member|drvid
(brace
id|ulong
id|drvid
suffix:semicolon
multiline_comment|/* driver ids, bit mapped */
DECL|member|my_msn
r_char
id|my_msn
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* desired msn, subaddr allowed */
DECL|member|caller
r_char
id|caller
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* caller id, partial string with * + subaddr allowed */
DECL|member|to_nr
r_char
id|to_nr
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* deflected to number incl. subaddress */
DECL|member|si1
DECL|member|si2
id|u_char
id|si1
comma
id|si2
suffix:semicolon
multiline_comment|/* service indicators, si1=bitmask, si1+2 0 = all */
DECL|member|screen
id|u_char
id|screen
suffix:semicolon
multiline_comment|/* screening: 0 = no info, 1 = info, 2 = nfo with nr */
DECL|member|callopt
id|u_char
id|callopt
suffix:semicolon
multiline_comment|/* option for call handling: &n;                       0 = all calls&n;                       1 = only non waiting calls&n;                       2 = only waiting calls */
DECL|member|action
id|u_char
id|action
suffix:semicolon
multiline_comment|/* desired action: &n;                       0 = don&squot;t report call -&gt; ignore&n;                       1 = report call, do not allow/proceed for deflection&n;                       2 = report call, send proceed, wait max waittime secs&n;                       3 = report call, alert and deflect after waittime &n;                       4 = report call, reject immediately  &n;                       actions 1-2 only take place if interface is opened &n;&t;&t;    */
DECL|member|waittime
id|u_char
id|waittime
suffix:semicolon
multiline_comment|/* maximum wait time for proceeding */
DECL|typedef|divert_rule
)brace
id|divert_rule
suffix:semicolon
r_typedef
r_union
DECL|member|drv_version
(brace
r_int
id|drv_version
suffix:semicolon
multiline_comment|/* return of driver version */
r_struct
DECL|member|drvid
(brace
r_int
id|drvid
suffix:semicolon
multiline_comment|/* id of driver */
DECL|member|drvnam
r_char
id|drvnam
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* name of driver */
DECL|member|getid
)brace
id|getid
suffix:semicolon
r_struct
DECL|member|ruleidx
(brace
r_int
id|ruleidx
suffix:semicolon
multiline_comment|/* index of rule */
DECL|member|rule
id|divert_rule
id|rule
suffix:semicolon
multiline_comment|/* rule parms */
DECL|member|getsetrule
)brace
id|getsetrule
suffix:semicolon
r_struct
DECL|member|subcmd
(brace
id|u_char
id|subcmd
suffix:semicolon
multiline_comment|/* 0 = hangup/reject,&n;                        1 = alert,&n;                        2 = deflect */
DECL|member|callid
id|ulong
id|callid
suffix:semicolon
multiline_comment|/* id of call delivered by ascii output */
DECL|member|to_nr
r_char
id|to_nr
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* destination when deflect,&n;                        else uus1 string (maxlen 31),&n;                        data from rule used if empty */
DECL|member|fwd_ctrl
)brace
id|fwd_ctrl
suffix:semicolon
r_struct
DECL|member|drvid
(brace
r_int
id|drvid
suffix:semicolon
multiline_comment|/* id of driver */
DECL|member|cfproc
id|u_char
id|cfproc
suffix:semicolon
multiline_comment|/* cfu = 0, cfb = 1, cfnr = 2 */
DECL|member|procid
id|ulong
id|procid
suffix:semicolon
multiline_comment|/* process id returned when no error */
DECL|member|service
id|u_char
id|service
suffix:semicolon
multiline_comment|/* basically coded service, 0 = all */
DECL|member|msn
r_char
id|msn
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* desired msn, empty = all */
DECL|member|fwd_nr
r_char
id|fwd_nr
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* forwarded to number + subaddress */
DECL|member|cf_ctrl
)brace
id|cf_ctrl
suffix:semicolon
DECL|typedef|divert_ioctl
)brace
id|divert_ioctl
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#include &lt;linux/isdn_divertif.h&gt;
DECL|macro|AUTODEL_TIME
mdefine_line|#define AUTODEL_TIME 30 /* timeout in s to delete internal entries */
multiline_comment|/**************************************************/
multiline_comment|/* structure keeping ascii info for device output */
multiline_comment|/**************************************************/
DECL|struct|divert_info
r_struct
id|divert_info
DECL|member|next
(brace
r_struct
id|divert_info
op_star
id|next
suffix:semicolon
DECL|member|usage_cnt
id|ulong
id|usage_cnt
suffix:semicolon
multiline_comment|/* number of files still to work */
DECL|member|info_start
r_char
id|info_start
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* info string start */
)brace
suffix:semicolon
multiline_comment|/**************/
multiline_comment|/* Prototypes */
multiline_comment|/**************/
r_extern
id|ulong
id|if_used
suffix:semicolon
multiline_comment|/* number of interface users */
r_extern
r_int
id|divert_dev_deinit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|divert_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|put_info_buffer
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ll_callback
c_func
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
id|isdn_divert_if
id|divert_if
suffix:semicolon
r_extern
id|divert_rule
op_star
id|getruleptr
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|insertrule
c_func
(paren
r_int
comma
id|divert_rule
op_star
)paren
suffix:semicolon
r_extern
r_int
id|deleterule
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|deleteprocs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|deflect_extern_action
c_func
(paren
id|u_char
comma
id|ulong
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cf_command
c_func
(paren
r_int
comma
r_int
comma
id|u_char
comma
r_char
op_star
comma
id|u_char
comma
r_char
op_star
comma
id|ulong
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
eof
