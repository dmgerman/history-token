multiline_comment|/* $Id: isdnif.h,v 1.37.6.5 2001/06/11 22:08:38 kai Exp $&n;&n; * Linux ISDN subsystem&n; *&n; * Definition of the interface between the subsystem and its low-level drivers.&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    Thinking Objects Software GmbH Wuerzburg&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
macro_line|#ifndef __ISDNIF_H__
DECL|macro|__ISDNIF_H__
mdefine_line|#define __ISDNIF_H__
multiline_comment|/*&n; * Values for general protocol-selection&n; */
DECL|macro|ISDN_PTYPE_UNKNOWN
mdefine_line|#define ISDN_PTYPE_UNKNOWN   0   /* Protocol undefined   */
DECL|macro|ISDN_PTYPE_1TR6
mdefine_line|#define ISDN_PTYPE_1TR6      1   /* german 1TR6-protocol */
DECL|macro|ISDN_PTYPE_EURO
mdefine_line|#define ISDN_PTYPE_EURO      2   /* EDSS1-protocol       */
DECL|macro|ISDN_PTYPE_LEASED
mdefine_line|#define ISDN_PTYPE_LEASED    3   /* for leased lines     */
DECL|macro|ISDN_PTYPE_NI1
mdefine_line|#define ISDN_PTYPE_NI1       4   /* US NI-1 protocol     */
DECL|macro|ISDN_PTYPE_MAX
mdefine_line|#define ISDN_PTYPE_MAX       7   /* Max. 8 Protocols     */
multiline_comment|/*&n; * Values for Layer-2-protocol-selection&n; */
DECL|macro|ISDN_PROTO_L2_X75I
mdefine_line|#define ISDN_PROTO_L2_X75I   0   /* X75/LAPB with I-Frames            */
DECL|macro|ISDN_PROTO_L2_X75UI
mdefine_line|#define ISDN_PROTO_L2_X75UI  1   /* X75/LAPB with UI-Frames           */
DECL|macro|ISDN_PROTO_L2_X75BUI
mdefine_line|#define ISDN_PROTO_L2_X75BUI 2   /* X75/LAPB with UI-Frames           */
DECL|macro|ISDN_PROTO_L2_HDLC
mdefine_line|#define ISDN_PROTO_L2_HDLC   3   /* HDLC                              */
DECL|macro|ISDN_PROTO_L2_TRANS
mdefine_line|#define ISDN_PROTO_L2_TRANS  4   /* Transparent (Voice)               */
DECL|macro|ISDN_PROTO_L2_X25DTE
mdefine_line|#define ISDN_PROTO_L2_X25DTE 5   /* X25/LAPB DTE mode                 */
DECL|macro|ISDN_PROTO_L2_X25DCE
mdefine_line|#define ISDN_PROTO_L2_X25DCE 6   /* X25/LAPB DCE mode                 */
DECL|macro|ISDN_PROTO_L2_V11096
mdefine_line|#define ISDN_PROTO_L2_V11096 7   /* V.110 bitrate adaption 9600 Baud  */
DECL|macro|ISDN_PROTO_L2_V11019
mdefine_line|#define ISDN_PROTO_L2_V11019 8   /* V.110 bitrate adaption 19200 Baud */
DECL|macro|ISDN_PROTO_L2_V11038
mdefine_line|#define ISDN_PROTO_L2_V11038 9   /* V.110 bitrate adaption 38400 Baud */
DECL|macro|ISDN_PROTO_L2_MODEM
mdefine_line|#define ISDN_PROTO_L2_MODEM  10  /* Analog Modem on Board */
DECL|macro|ISDN_PROTO_L2_FAX
mdefine_line|#define ISDN_PROTO_L2_FAX    11  /* Fax Group 2/3         */
DECL|macro|ISDN_PROTO_L2_HDLC_56K
mdefine_line|#define ISDN_PROTO_L2_HDLC_56K 12   /* HDLC 56k                          */
DECL|macro|ISDN_PROTO_L2_MAX
mdefine_line|#define ISDN_PROTO_L2_MAX    15  /* Max. 16 Protocols                 */
multiline_comment|/*&n; * Values for Layer-3-protocol-selection&n; */
DECL|macro|ISDN_PROTO_L3_TRANS
mdefine_line|#define ISDN_PROTO_L3_TRANS&t;0&t;/* Transparent */
DECL|macro|ISDN_PROTO_L3_TRANSDSP
mdefine_line|#define ISDN_PROTO_L3_TRANSDSP&t;1&t;/* Transparent with DSP */
DECL|macro|ISDN_PROTO_L3_FCLASS2
mdefine_line|#define ISDN_PROTO_L3_FCLASS2&t;2&t;/* Fax Group 2/3 CLASS 2 */
DECL|macro|ISDN_PROTO_L3_FCLASS1
mdefine_line|#define ISDN_PROTO_L3_FCLASS1&t;3&t;/* Fax Group 2/3 CLASS 1 */
DECL|macro|ISDN_PROTO_L3_MAX
mdefine_line|#define ISDN_PROTO_L3_MAX&t;7&t;/* Max. 8 Protocols */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/***************************************************************************/
multiline_comment|/* Extensions made by Werner Cornelius (werner@ikt.de)                     */
multiline_comment|/*                                                                         */
multiline_comment|/* The proceed command holds a incoming call in a state to leave processes */
multiline_comment|/* enough time to check whether ist should be accepted.                    */
multiline_comment|/* The PROT_IO Command extends the interface to make protocol dependant    */
multiline_comment|/* features available (call diversion, call waiting...).                   */
multiline_comment|/*                                                                         */
multiline_comment|/* The PROT_IO Command is executed with the desired driver id and the arg  */
multiline_comment|/* parameter coded as follows:                                             */
multiline_comment|/* The lower 8 bits of arg contain the desired protocol from ISDN_PTYPE    */
multiline_comment|/* definitions. The upper 24 bits represent the protocol specific cmd/stat.*/
multiline_comment|/* Any additional data is protocol and command specific.                   */
multiline_comment|/* This mechanism also applies to the statcallb callback STAT_PROT.        */
multiline_comment|/*                                                                         */
multiline_comment|/* This suggested extension permits an easy expansion of protocol specific */
multiline_comment|/* handling. Extensions may be added at any time without changing the HL   */
multiline_comment|/* driver code and not getting conflicts without certifications.           */
multiline_comment|/* The well known CAPI 2.0 interface handles such extensions in a similar  */
multiline_comment|/* way. Perhaps a protocol specific module may be added and separately     */
multiline_comment|/* loaded and linked to the basic isdn module for handling.                */
multiline_comment|/***************************************************************************/
multiline_comment|/*****************/
multiline_comment|/* DSS1 commands */
multiline_comment|/*****************/
DECL|macro|DSS1_CMD_INVOKE
mdefine_line|#define DSS1_CMD_INVOKE       ((0x00 &lt;&lt; 8) | ISDN_PTYPE_EURO)   /* invoke a supplementary service */
DECL|macro|DSS1_CMD_INVOKE_ABORT
mdefine_line|#define DSS1_CMD_INVOKE_ABORT ((0x01 &lt;&lt; 8) | ISDN_PTYPE_EURO)   /* abort a invoke cmd */
multiline_comment|/*******************************/
multiline_comment|/* DSS1 Status callback values */
multiline_comment|/*******************************/
DECL|macro|DSS1_STAT_INVOKE_RES
mdefine_line|#define DSS1_STAT_INVOKE_RES  ((0x80 &lt;&lt; 8) | ISDN_PTYPE_EURO)   /* Result for invocation */
DECL|macro|DSS1_STAT_INVOKE_ERR
mdefine_line|#define DSS1_STAT_INVOKE_ERR  ((0x81 &lt;&lt; 8) | ISDN_PTYPE_EURO)   /* Error Return for invocation */
DECL|macro|DSS1_STAT_INVOKE_BRD
mdefine_line|#define DSS1_STAT_INVOKE_BRD  ((0x82 &lt;&lt; 8) | ISDN_PTYPE_EURO)   /* Deliver invoke broadcast info */
multiline_comment|/*********************************************************************/
multiline_comment|/* structures for DSS1 commands and callback                         */
multiline_comment|/*                                                                   */
multiline_comment|/* An action is invoked by sending a DSS1_CMD_INVOKE. The ll_id, proc*/
multiline_comment|/* timeout, datalen and data fields must be set before calling.      */
multiline_comment|/*                                                                   */
multiline_comment|/* The return value is a positive hl_id value also delivered in the  */
multiline_comment|/* hl_id field. A value of zero signals no more left hl_id capacitys.*/
multiline_comment|/* A negative return value signals errors in LL. So if the return    */
multiline_comment|/* value is &lt;= 0 no action in LL will be taken -&gt; request ignored    */
multiline_comment|/*                                                                   */
multiline_comment|/* The timeout field must be filled with a positive value specifying */
multiline_comment|/* the amount of time the INVOKED process waits for a reaction from  */
multiline_comment|/* the network.                                                      */
multiline_comment|/* If a response (either error or result) is received during this    */
multiline_comment|/* intervall, a reporting callback is initiated and the process will */
multiline_comment|/* be deleted, the hl identifier will be freed.                      */
multiline_comment|/* If no response is received during the specified intervall, a error*/
multiline_comment|/* callback is initiated with timeout set to -1 and a datalen set    */
multiline_comment|/* to 0.                                                             */
multiline_comment|/* If timeout is set to a value &lt;= 0 during INVOCATION the process is*/
multiline_comment|/* immediately deleted after sending the data. No callback occurs !  */
multiline_comment|/*                                                                   */
multiline_comment|/* A currently waiting process may be aborted with INVOKE_ABORT. No  */
multiline_comment|/* callback will occur when a process has been aborted.              */
multiline_comment|/*                                                                   */
multiline_comment|/* Broadcast invoke frames from the network are reported via the     */
multiline_comment|/* STAT_INVOKE_BRD callback. The ll_id is set to 0, the other fields */
multiline_comment|/* are supplied by the network and not by the HL.                    */
multiline_comment|/*********************************************************************/
multiline_comment|/*****************/
multiline_comment|/* NI1 commands */
multiline_comment|/*****************/
DECL|macro|NI1_CMD_INVOKE
mdefine_line|#define NI1_CMD_INVOKE       ((0x00 &lt;&lt; 8) | ISDN_PTYPE_NI1)   /* invoke a supplementary service */
DECL|macro|NI1_CMD_INVOKE_ABORT
mdefine_line|#define NI1_CMD_INVOKE_ABORT ((0x01 &lt;&lt; 8) | ISDN_PTYPE_NI1)   /* abort a invoke cmd */
multiline_comment|/*******************************/
multiline_comment|/* NI1 Status callback values */
multiline_comment|/*******************************/
DECL|macro|NI1_STAT_INVOKE_RES
mdefine_line|#define NI1_STAT_INVOKE_RES  ((0x80 &lt;&lt; 8) | ISDN_PTYPE_NI1)   /* Result for invocation */
DECL|macro|NI1_STAT_INVOKE_ERR
mdefine_line|#define NI1_STAT_INVOKE_ERR  ((0x81 &lt;&lt; 8) | ISDN_PTYPE_NI1)   /* Error Return for invocation */
DECL|macro|NI1_STAT_INVOKE_BRD
mdefine_line|#define NI1_STAT_INVOKE_BRD  ((0x82 &lt;&lt; 8) | ISDN_PTYPE_NI1)   /* Deliver invoke broadcast info */
r_typedef
r_struct
DECL|member|ll_id
(brace
id|ulong
id|ll_id
suffix:semicolon
multiline_comment|/* ID supplied by LL when executing    */
multiline_comment|/* a command and returned by HL for    */
multiline_comment|/* INVOKE_RES and INVOKE_ERR           */
DECL|member|hl_id
r_int
id|hl_id
suffix:semicolon
multiline_comment|/* ID supplied by HL when called       */
multiline_comment|/* for executing a cmd and delivered   */
multiline_comment|/* for results and errors              */
multiline_comment|/* must be supplied by LL when aborting*/
DECL|member|proc
r_int
id|proc
suffix:semicolon
multiline_comment|/* invoke procedure used by CMD_INVOKE */
multiline_comment|/* returned by callback and broadcast  */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout for INVOKE CMD in ms        */
multiline_comment|/* -1  in stat callback when timed out */
multiline_comment|/* error value when error callback     */
DECL|member|datalen
r_int
id|datalen
suffix:semicolon
multiline_comment|/* length of cmd or stat data          */
DECL|member|data
id|u_char
op_star
id|data
suffix:semicolon
multiline_comment|/* pointer to data delivered or send   */
DECL|typedef|isdn_cmd_stat
)brace
id|isdn_cmd_stat
suffix:semicolon
multiline_comment|/*&n; * Commands from linklevel to lowlevel&n; *&n; */
DECL|macro|ISDN_CMD_IOCTL
mdefine_line|#define ISDN_CMD_IOCTL    0       /* Perform ioctl                         */
DECL|macro|ISDN_CMD_DIAL
mdefine_line|#define ISDN_CMD_DIAL     1       /* Dial out                              */
DECL|macro|ISDN_CMD_ACCEPTD
mdefine_line|#define ISDN_CMD_ACCEPTD  2       /* Accept an incoming call on D-Chan.    */
DECL|macro|ISDN_CMD_ACCEPTB
mdefine_line|#define ISDN_CMD_ACCEPTB  3       /* Request B-Channel connect.            */
DECL|macro|ISDN_CMD_HANGUP
mdefine_line|#define ISDN_CMD_HANGUP   4       /* Hangup                                */
DECL|macro|ISDN_CMD_CLREAZ
mdefine_line|#define ISDN_CMD_CLREAZ   5       /* Clear EAZ(s) of channel               */
DECL|macro|ISDN_CMD_SETEAZ
mdefine_line|#define ISDN_CMD_SETEAZ   6       /* Set EAZ(s) of channel                 */
DECL|macro|ISDN_CMD_GETEAZ
mdefine_line|#define ISDN_CMD_GETEAZ   7       /* Get EAZ(s) of channel                 */
DECL|macro|ISDN_CMD_SETSIL
mdefine_line|#define ISDN_CMD_SETSIL   8       /* Set Service-Indicator-List of channel */
DECL|macro|ISDN_CMD_GETSIL
mdefine_line|#define ISDN_CMD_GETSIL   9       /* Get Service-Indicator-List of channel */
DECL|macro|ISDN_CMD_SETL2
mdefine_line|#define ISDN_CMD_SETL2   10       /* Set B-Chan. Layer2-Parameter          */
DECL|macro|ISDN_CMD_GETL2
mdefine_line|#define ISDN_CMD_GETL2   11       /* Get B-Chan. Layer2-Parameter          */
DECL|macro|ISDN_CMD_SETL3
mdefine_line|#define ISDN_CMD_SETL3   12       /* Set B-Chan. Layer3-Parameter          */
DECL|macro|ISDN_CMD_GETL3
mdefine_line|#define ISDN_CMD_GETL3   13       /* Get B-Chan. Layer3-Parameter          */
DECL|macro|ISDN_CMD_LOCK
mdefine_line|#define ISDN_CMD_LOCK    14       /* Signal usage by upper levels          */
DECL|macro|ISDN_CMD_UNLOCK
mdefine_line|#define ISDN_CMD_UNLOCK  15       /* Release usage-lock                    */
DECL|macro|ISDN_CMD_SUSPEND
mdefine_line|#define ISDN_CMD_SUSPEND 16       /* Suspend connection                    */
DECL|macro|ISDN_CMD_RESUME
mdefine_line|#define ISDN_CMD_RESUME  17       /* Resume connection                     */
DECL|macro|ISDN_CMD_PROCEED
mdefine_line|#define ISDN_CMD_PROCEED 18       /* Proceed with call establishment       */
DECL|macro|ISDN_CMD_ALERT
mdefine_line|#define ISDN_CMD_ALERT   19       /* Alert after Proceeding                */
DECL|macro|ISDN_CMD_REDIR
mdefine_line|#define ISDN_CMD_REDIR   20       /* Redir a incoming call                 */
DECL|macro|ISDN_CMD_PROT_IO
mdefine_line|#define ISDN_CMD_PROT_IO 21       /* Protocol specific commands            */
DECL|macro|CAPI_PUT_MESSAGE
mdefine_line|#define CAPI_PUT_MESSAGE 22       /* CAPI message send down or up          */
DECL|macro|ISDN_CMD_FAXCMD
mdefine_line|#define ISDN_CMD_FAXCMD  23       /* FAX commands to HL-driver             */
DECL|macro|ISDN_CMD_AUDIO
mdefine_line|#define ISDN_CMD_AUDIO   24       /* DSP, DTMF, ... settings               */
multiline_comment|/*&n; * Status-Values delivered from lowlevel to linklevel via&n; * statcallb().&n; *&n; */
DECL|macro|ISDN_STAT_STAVAIL
mdefine_line|#define ISDN_STAT_STAVAIL 256    /* Raw status-data available             */
DECL|macro|ISDN_STAT_ICALL
mdefine_line|#define ISDN_STAT_ICALL   257    /* Incoming call detected                */
DECL|macro|ISDN_STAT_RUN
mdefine_line|#define ISDN_STAT_RUN     258    /* Signal protocol-code is running       */
DECL|macro|ISDN_STAT_STOP
mdefine_line|#define ISDN_STAT_STOP    259    /* Signal halt of protocol-code          */
DECL|macro|ISDN_STAT_DCONN
mdefine_line|#define ISDN_STAT_DCONN   260    /* Signal D-Channel connect              */
DECL|macro|ISDN_STAT_BCONN
mdefine_line|#define ISDN_STAT_BCONN   261    /* Signal B-Channel connect              */
DECL|macro|ISDN_STAT_DHUP
mdefine_line|#define ISDN_STAT_DHUP    262    /* Signal D-Channel disconnect           */
DECL|macro|ISDN_STAT_BHUP
mdefine_line|#define ISDN_STAT_BHUP    263    /* Signal B-Channel disconnect           */
DECL|macro|ISDN_STAT_CINF
mdefine_line|#define ISDN_STAT_CINF    264    /* Charge-Info                           */
DECL|macro|ISDN_STAT_LOAD
mdefine_line|#define ISDN_STAT_LOAD    265    /* Signal new lowlevel-driver is loaded  */
DECL|macro|ISDN_STAT_UNLOAD
mdefine_line|#define ISDN_STAT_UNLOAD  266    /* Signal unload of lowlevel-driver      */
DECL|macro|ISDN_STAT_BSENT
mdefine_line|#define ISDN_STAT_BSENT   267    /* Signal packet sent                    */
DECL|macro|ISDN_STAT_NODCH
mdefine_line|#define ISDN_STAT_NODCH   268    /* Signal no D-Channel                   */
DECL|macro|ISDN_STAT_ADDCH
mdefine_line|#define ISDN_STAT_ADDCH   269    /* Add more Channels                     */
DECL|macro|ISDN_STAT_CAUSE
mdefine_line|#define ISDN_STAT_CAUSE   270    /* Cause-Message                         */
DECL|macro|ISDN_STAT_ICALLW
mdefine_line|#define ISDN_STAT_ICALLW  271    /* Incoming call without B-chan waiting  */
DECL|macro|ISDN_STAT_REDIR
mdefine_line|#define ISDN_STAT_REDIR   272    /* Redir result                          */
DECL|macro|ISDN_STAT_PROT
mdefine_line|#define ISDN_STAT_PROT    273    /* protocol IO specific callback         */
DECL|macro|ISDN_STAT_DISPLAY
mdefine_line|#define ISDN_STAT_DISPLAY 274    /* deliver a received display message    */
DECL|macro|ISDN_STAT_L1ERR
mdefine_line|#define ISDN_STAT_L1ERR   275    /* Signal Layer-1 Error                  */
DECL|macro|ISDN_STAT_FAXIND
mdefine_line|#define ISDN_STAT_FAXIND  276    /* FAX indications from HL-driver        */
DECL|macro|ISDN_STAT_AUDIO
mdefine_line|#define ISDN_STAT_AUDIO   277    /* DTMF, DSP indications                 */
DECL|macro|ISDN_STAT_DISCH
mdefine_line|#define ISDN_STAT_DISCH   278    /* Disable/Enable channel usage          */
multiline_comment|/*&n; * Audio commands&n; */
DECL|macro|ISDN_AUDIO_SETDD
mdefine_line|#define ISDN_AUDIO_SETDD&t;0&t;/* Set DTMF detection           */
DECL|macro|ISDN_AUDIO_DTMF
mdefine_line|#define ISDN_AUDIO_DTMF&t;&t;1&t;/* Rx/Tx DTMF                   */
multiline_comment|/*&n; * Values for errcode field&n; */
DECL|macro|ISDN_STAT_L1ERR_SEND
mdefine_line|#define ISDN_STAT_L1ERR_SEND 1
DECL|macro|ISDN_STAT_L1ERR_RECV
mdefine_line|#define ISDN_STAT_L1ERR_RECV 2
multiline_comment|/*&n; * Values for feature-field of interface-struct.&n; */
multiline_comment|/* Layer 2 */
DECL|macro|ISDN_FEATURE_L2_X75I
mdefine_line|#define ISDN_FEATURE_L2_X75I    (0x0001 &lt;&lt; ISDN_PROTO_L2_X75I)
DECL|macro|ISDN_FEATURE_L2_X75UI
mdefine_line|#define ISDN_FEATURE_L2_X75UI   (0x0001 &lt;&lt; ISDN_PROTO_L2_X75UI)
DECL|macro|ISDN_FEATURE_L2_X75BUI
mdefine_line|#define ISDN_FEATURE_L2_X75BUI  (0x0001 &lt;&lt; ISDN_PROTO_L2_X75BUI)
DECL|macro|ISDN_FEATURE_L2_HDLC
mdefine_line|#define ISDN_FEATURE_L2_HDLC    (0x0001 &lt;&lt; ISDN_PROTO_L2_HDLC)
DECL|macro|ISDN_FEATURE_L2_TRANS
mdefine_line|#define ISDN_FEATURE_L2_TRANS   (0x0001 &lt;&lt; ISDN_PROTO_L2_TRANS)
DECL|macro|ISDN_FEATURE_L2_X25DTE
mdefine_line|#define ISDN_FEATURE_L2_X25DTE  (0x0001 &lt;&lt; ISDN_PROTO_L2_X25DTE)
DECL|macro|ISDN_FEATURE_L2_X25DCE
mdefine_line|#define ISDN_FEATURE_L2_X25DCE  (0x0001 &lt;&lt; ISDN_PROTO_L2_X25DCE)
DECL|macro|ISDN_FEATURE_L2_V11096
mdefine_line|#define ISDN_FEATURE_L2_V11096  (0x0001 &lt;&lt; ISDN_PROTO_L2_V11096)
DECL|macro|ISDN_FEATURE_L2_V11019
mdefine_line|#define ISDN_FEATURE_L2_V11019  (0x0001 &lt;&lt; ISDN_PROTO_L2_V11019)
DECL|macro|ISDN_FEATURE_L2_V11038
mdefine_line|#define ISDN_FEATURE_L2_V11038  (0x0001 &lt;&lt; ISDN_PROTO_L2_V11038)
DECL|macro|ISDN_FEATURE_L2_MODEM
mdefine_line|#define ISDN_FEATURE_L2_MODEM   (0x0001 &lt;&lt; ISDN_PROTO_L2_MODEM)
DECL|macro|ISDN_FEATURE_L2_FAX
mdefine_line|#define ISDN_FEATURE_L2_FAX&t;(0x0001 &lt;&lt; ISDN_PROTO_L2_FAX)
DECL|macro|ISDN_FEATURE_L2_HDLC_56K
mdefine_line|#define ISDN_FEATURE_L2_HDLC_56K (0x0001 &lt;&lt; ISDN_PROTO_L2_HDLC_56K)
DECL|macro|ISDN_FEATURE_L2_MASK
mdefine_line|#define ISDN_FEATURE_L2_MASK    (0x0FFFF) /* Max. 16 protocols */
DECL|macro|ISDN_FEATURE_L2_SHIFT
mdefine_line|#define ISDN_FEATURE_L2_SHIFT   (0)
multiline_comment|/* Layer 3 */
DECL|macro|ISDN_FEATURE_L3_TRANS
mdefine_line|#define ISDN_FEATURE_L3_TRANS   (0x10000 &lt;&lt; ISDN_PROTO_L3_TRANS)
DECL|macro|ISDN_FEATURE_L3_TRANSDSP
mdefine_line|#define ISDN_FEATURE_L3_TRANSDSP (0x10000 &lt;&lt; ISDN_PROTO_L3_TRANSDSP)
DECL|macro|ISDN_FEATURE_L3_FCLASS2
mdefine_line|#define ISDN_FEATURE_L3_FCLASS2&t;(0x10000 &lt;&lt; ISDN_PROTO_L3_FCLASS2)
DECL|macro|ISDN_FEATURE_L3_FCLASS1
mdefine_line|#define ISDN_FEATURE_L3_FCLASS1&t;(0x10000 &lt;&lt; ISDN_PROTO_L3_FCLASS1)
DECL|macro|ISDN_FEATURE_L3_MASK
mdefine_line|#define ISDN_FEATURE_L3_MASK    (0x0FF0000) /* Max. 8 Protocols */
DECL|macro|ISDN_FEATURE_L3_SHIFT
mdefine_line|#define ISDN_FEATURE_L3_SHIFT   (16)
multiline_comment|/* Signaling */
DECL|macro|ISDN_FEATURE_P_UNKNOWN
mdefine_line|#define ISDN_FEATURE_P_UNKNOWN  (0x1000000 &lt;&lt; ISDN_PTYPE_UNKNOWN)
DECL|macro|ISDN_FEATURE_P_1TR6
mdefine_line|#define ISDN_FEATURE_P_1TR6     (0x1000000 &lt;&lt; ISDN_PTYPE_1TR6)
DECL|macro|ISDN_FEATURE_P_EURO
mdefine_line|#define ISDN_FEATURE_P_EURO     (0x1000000 &lt;&lt; ISDN_PTYPE_EURO)
DECL|macro|ISDN_FEATURE_P_NI1
mdefine_line|#define ISDN_FEATURE_P_NI1      (0x1000000 &lt;&lt; ISDN_PTYPE_NI1)
DECL|macro|ISDN_FEATURE_P_MASK
mdefine_line|#define ISDN_FEATURE_P_MASK     (0x0FF000000) /* Max. 8 Protocols */
DECL|macro|ISDN_FEATURE_P_SHIFT
mdefine_line|#define ISDN_FEATURE_P_SHIFT    (24)
DECL|struct|setup_parm
r_typedef
r_struct
id|setup_parm
(brace
DECL|member|phone
r_int
r_char
id|phone
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Remote Phone-Number */
DECL|member|eazmsn
r_int
r_char
id|eazmsn
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Local EAZ or MSN    */
DECL|member|si1
r_int
r_char
id|si1
suffix:semicolon
multiline_comment|/* Service Indicator 1 */
DECL|member|si2
r_int
r_char
id|si2
suffix:semicolon
multiline_comment|/* Service Indicator 2 */
DECL|member|plan
r_int
r_char
id|plan
suffix:semicolon
multiline_comment|/* Numbering plan      */
DECL|member|screen
r_int
r_char
id|screen
suffix:semicolon
multiline_comment|/* Screening info      */
DECL|typedef|setup_parm
)brace
id|setup_parm
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
multiline_comment|/* T.30 Fax G3 */
DECL|macro|FAXIDLEN
mdefine_line|#define FAXIDLEN 21
DECL|struct|T30_s
r_typedef
r_struct
id|T30_s
(brace
multiline_comment|/* session parameters */
DECL|member|resolution
id|__u8
id|resolution
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rate
id|__u8
id|rate
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|width
id|__u8
id|width
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|length
id|__u8
id|length
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|compression
id|__u8
id|compression
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ecm
id|__u8
id|ecm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|binary
id|__u8
id|binary
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|scantime
id|__u8
id|scantime
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|id
id|__u8
id|id
(braket
id|FAXIDLEN
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* additional parameters */
DECL|member|phase
id|__u8
id|phase
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|direction
id|__u8
id|direction
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|code
id|__u8
id|code
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|badlin
id|__u8
id|badlin
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|badmul
id|__u8
id|badmul
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bor
id|__u8
id|bor
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|fet
id|__u8
id|fet
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|pollid
id|__u8
id|pollid
(braket
id|FAXIDLEN
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|cq
id|__u8
id|cq
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|cr
id|__u8
id|cr
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ctcrty
id|__u8
id|ctcrty
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|minsp
id|__u8
id|minsp
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|phcto
id|__u8
id|phcto
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rel
id|__u8
id|rel
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|nbc
id|__u8
id|nbc
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* remote station parameters */
DECL|member|r_resolution
id|__u8
id|r_resolution
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_rate
id|__u8
id|r_rate
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_width
id|__u8
id|r_width
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_length
id|__u8
id|r_length
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_compression
id|__u8
id|r_compression
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_ecm
id|__u8
id|r_ecm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_binary
id|__u8
id|r_binary
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_scantime
id|__u8
id|r_scantime
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_id
id|__u8
id|r_id
(braket
id|FAXIDLEN
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|r_code
id|__u8
id|r_code
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|T30_s
)brace
id|T30_s
suffix:semicolon
DECL|macro|ISDN_TTY_FAX_CONN_IN
mdefine_line|#define ISDN_TTY_FAX_CONN_IN&t;0
DECL|macro|ISDN_TTY_FAX_CONN_OUT
mdefine_line|#define ISDN_TTY_FAX_CONN_OUT&t;1
DECL|macro|ISDN_TTY_FAX_FCON
mdefine_line|#define ISDN_TTY_FAX_FCON&t;0
DECL|macro|ISDN_TTY_FAX_DIS
mdefine_line|#define ISDN_TTY_FAX_DIS &t;1
DECL|macro|ISDN_TTY_FAX_FTT
mdefine_line|#define ISDN_TTY_FAX_FTT &t;2
DECL|macro|ISDN_TTY_FAX_MCF
mdefine_line|#define ISDN_TTY_FAX_MCF &t;3
DECL|macro|ISDN_TTY_FAX_DCS
mdefine_line|#define ISDN_TTY_FAX_DCS &t;4
DECL|macro|ISDN_TTY_FAX_TRAIN_OK
mdefine_line|#define ISDN_TTY_FAX_TRAIN_OK&t;5
DECL|macro|ISDN_TTY_FAX_EOP
mdefine_line|#define ISDN_TTY_FAX_EOP &t;6
DECL|macro|ISDN_TTY_FAX_EOM
mdefine_line|#define ISDN_TTY_FAX_EOM &t;7
DECL|macro|ISDN_TTY_FAX_MPS
mdefine_line|#define ISDN_TTY_FAX_MPS &t;8
DECL|macro|ISDN_TTY_FAX_DTC
mdefine_line|#define ISDN_TTY_FAX_DTC &t;9
DECL|macro|ISDN_TTY_FAX_RID
mdefine_line|#define ISDN_TTY_FAX_RID &t;10
DECL|macro|ISDN_TTY_FAX_HNG
mdefine_line|#define ISDN_TTY_FAX_HNG &t;11
DECL|macro|ISDN_TTY_FAX_DT
mdefine_line|#define ISDN_TTY_FAX_DT  &t;12
DECL|macro|ISDN_TTY_FAX_FCON_I
mdefine_line|#define ISDN_TTY_FAX_FCON_I&t;13
DECL|macro|ISDN_TTY_FAX_DR
mdefine_line|#define ISDN_TTY_FAX_DR  &t;14
DECL|macro|ISDN_TTY_FAX_ET
mdefine_line|#define ISDN_TTY_FAX_ET  &t;15
DECL|macro|ISDN_TTY_FAX_CFR
mdefine_line|#define ISDN_TTY_FAX_CFR &t;16
DECL|macro|ISDN_TTY_FAX_PTS
mdefine_line|#define ISDN_TTY_FAX_PTS &t;17
DECL|macro|ISDN_TTY_FAX_SENT
mdefine_line|#define ISDN_TTY_FAX_SENT&t;18
DECL|macro|ISDN_FAX_PHASE_IDLE
mdefine_line|#define ISDN_FAX_PHASE_IDLE&t;0
DECL|macro|ISDN_FAX_PHASE_A
mdefine_line|#define ISDN_FAX_PHASE_A&t;1
DECL|macro|ISDN_FAX_PHASE_B
mdefine_line|#define ISDN_FAX_PHASE_B   &t;2
DECL|macro|ISDN_FAX_PHASE_C
mdefine_line|#define ISDN_FAX_PHASE_C   &t;3
DECL|macro|ISDN_FAX_PHASE_D
mdefine_line|#define ISDN_FAX_PHASE_D   &t;4
DECL|macro|ISDN_FAX_PHASE_E
mdefine_line|#define ISDN_FAX_PHASE_E   &t;5
macro_line|#endif /* TTY_FAX */
DECL|macro|ISDN_FAX_CLASS1_FAE
mdefine_line|#define ISDN_FAX_CLASS1_FAE&t;0
DECL|macro|ISDN_FAX_CLASS1_FTS
mdefine_line|#define ISDN_FAX_CLASS1_FTS&t;1
DECL|macro|ISDN_FAX_CLASS1_FRS
mdefine_line|#define ISDN_FAX_CLASS1_FRS&t;2
DECL|macro|ISDN_FAX_CLASS1_FTM
mdefine_line|#define ISDN_FAX_CLASS1_FTM&t;3
DECL|macro|ISDN_FAX_CLASS1_FRM
mdefine_line|#define ISDN_FAX_CLASS1_FRM&t;4
DECL|macro|ISDN_FAX_CLASS1_FTH
mdefine_line|#define ISDN_FAX_CLASS1_FTH&t;5
DECL|macro|ISDN_FAX_CLASS1_FRH
mdefine_line|#define ISDN_FAX_CLASS1_FRH&t;6
DECL|macro|ISDN_FAX_CLASS1_CTRL
mdefine_line|#define ISDN_FAX_CLASS1_CTRL&t;7
DECL|macro|ISDN_FAX_CLASS1_OK
mdefine_line|#define ISDN_FAX_CLASS1_OK&t;0
DECL|macro|ISDN_FAX_CLASS1_CONNECT
mdefine_line|#define ISDN_FAX_CLASS1_CONNECT&t;1
DECL|macro|ISDN_FAX_CLASS1_NOCARR
mdefine_line|#define ISDN_FAX_CLASS1_NOCARR&t;2
DECL|macro|ISDN_FAX_CLASS1_ERROR
mdefine_line|#define ISDN_FAX_CLASS1_ERROR&t;3
DECL|macro|ISDN_FAX_CLASS1_FCERROR
mdefine_line|#define ISDN_FAX_CLASS1_FCERROR&t;4
DECL|macro|ISDN_FAX_CLASS1_QUERY
mdefine_line|#define ISDN_FAX_CLASS1_QUERY&t;5
r_typedef
r_struct
(brace
DECL|member|cmd
id|__u8
id|cmd
suffix:semicolon
DECL|member|subcmd
id|__u8
id|subcmd
suffix:semicolon
DECL|member|para
id|__u8
id|para
(braket
l_int|50
)braket
suffix:semicolon
DECL|typedef|aux_s
)brace
id|aux_s
suffix:semicolon
DECL|macro|AT_COMMAND
mdefine_line|#define AT_COMMAND&t;0
DECL|macro|AT_EQ_VALUE
mdefine_line|#define AT_EQ_VALUE&t;1
DECL|macro|AT_QUERY
mdefine_line|#define AT_QUERY&t;2
DECL|macro|AT_EQ_QUERY
mdefine_line|#define AT_EQ_QUERY&t;3
multiline_comment|/* CAPI structs */
multiline_comment|/* this is compatible to the old union size */
DECL|macro|MAX_CAPI_PARA_LEN
mdefine_line|#define MAX_CAPI_PARA_LEN 50
r_typedef
r_struct
(brace
multiline_comment|/* Header */
DECL|member|Length
id|__u16
id|Length
suffix:semicolon
DECL|member|ApplId
id|__u16
id|ApplId
suffix:semicolon
DECL|member|Command
id|__u8
id|Command
suffix:semicolon
DECL|member|Subcommand
id|__u8
id|Subcommand
suffix:semicolon
DECL|member|Messagenumber
id|__u16
id|Messagenumber
suffix:semicolon
multiline_comment|/* Parameter */
r_union
(brace
DECL|member|Controller
id|__u32
id|Controller
suffix:semicolon
DECL|member|PLCI
id|__u32
id|PLCI
suffix:semicolon
DECL|member|NCCI
id|__u32
id|NCCI
suffix:semicolon
DECL|member|adr
)brace
id|adr
suffix:semicolon
DECL|member|para
id|__u8
id|para
(braket
id|MAX_CAPI_PARA_LEN
)braket
suffix:semicolon
DECL|typedef|capi_msg
)brace
id|capi_msg
suffix:semicolon
multiline_comment|/*&n; * Structure for exchanging above infos&n; *&n; */
r_typedef
r_struct
(brace
DECL|member|driver
r_int
id|driver
suffix:semicolon
multiline_comment|/* Lowlevel-Driver-ID            */
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* Command or Status (see above) */
DECL|member|arg
id|ulong
id|arg
suffix:semicolon
multiline_comment|/* Additional Data               */
r_union
(brace
DECL|member|errcode
id|ulong
id|errcode
suffix:semicolon
multiline_comment|/* Type of error with STAT_L1ERR&t;*/
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Amount of bytes sent with STAT_BSENT&t;*/
DECL|member|num
id|u_char
id|num
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* Additional Data&t;&t;&t;*/
DECL|member|setup
id|setup_parm
id|setup
suffix:semicolon
multiline_comment|/* For SETUP msg&t;&t;&t;*/
DECL|member|cmsg
id|capi_msg
id|cmsg
suffix:semicolon
multiline_comment|/* For CAPI like messages&t;&t;*/
DECL|member|display
r_char
id|display
(braket
l_int|85
)braket
suffix:semicolon
multiline_comment|/* display message data&t;&t;*/
DECL|member|isdn_io
id|isdn_cmd_stat
id|isdn_io
suffix:semicolon
multiline_comment|/* ISDN IO-parameter/result&t;*/
DECL|member|aux
id|aux_s
id|aux
suffix:semicolon
multiline_comment|/* for modem commands/indications&t;*/
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
DECL|member|fax
id|T30_s
op_star
id|fax
suffix:semicolon
multiline_comment|/* Pointer to ttys fax struct&t;&t;*/
macro_line|#endif
DECL|member|userdata
id|ulong
id|userdata
suffix:semicolon
multiline_comment|/* User Data */
DECL|member|parm
)brace
id|parm
suffix:semicolon
DECL|typedef|isdn_ctrl
)brace
id|isdn_ctrl
suffix:semicolon
DECL|macro|dss1_io
mdefine_line|#define dss1_io    isdn_io
DECL|macro|ni1_io
mdefine_line|#define ni1_io     isdn_io
multiline_comment|/*&n; * The interface-struct itself (initialized at load-time of lowlevel-driver)&n; *&n; * See Documentation/isdn/INTERFACE for a description, how the communication&n; * between the ISDN subsystem and its drivers is done.&n; *&n; */
r_typedef
r_struct
(brace
multiline_comment|/* Number of channels supported by this driver&n;   */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* &n;   * Maximum Size of transmit/receive-buffer this driver supports.&n;   */
DECL|member|maxbufsize
r_int
id|maxbufsize
suffix:semicolon
multiline_comment|/* Feature-Flags for this driver.&n;   * See defines ISDN_FEATURE_... for Values&n;   */
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
multiline_comment|/*&n;   * Needed for calculating&n;   * dev-&gt;hard_header_len = linklayer header + hl_hdrlen;&n;   * Drivers, not supporting sk_buff&squot;s should set this to 0.&n;   */
DECL|member|hl_hdrlen
r_int
r_int
id|hl_hdrlen
suffix:semicolon
multiline_comment|/*&n;   * Receive-Callback using sk_buff&squot;s&n;   * Parameters:&n;   *             int                    Driver-ID&n;   *             int                    local channel-number (0 ...)&n;   *             struct sk_buff *skb    received Data&n;   */
DECL|member|rcvcallb_skb
r_void
(paren
op_star
id|rcvcallb_skb
)paren
(paren
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Status-Callback&n;   * Parameters:&n;   *             isdn_ctrl*&n;   *                   driver  = Driver ID.&n;   *                   command = One of above ISDN_STAT_... constants.&n;   *                   arg     = depending on status-type.&n;   *                   num     = depending on status-type.&n;   */
DECL|member|statcallb
r_int
(paren
op_star
id|statcallb
)paren
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
multiline_comment|/* Send command&n;   * Parameters:&n;   *             isdn_ctrl*&n;   *                   driver  = Driver ID.&n;   *                   command = One of above ISDN_CMD_... constants.&n;   *                   arg     = depending on command.&n;   *                   num     = depending on command.&n;   */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;   * Send data using sk_buff&squot;s&n;   * Parameters:&n;   *             int                    driverId&n;   *             int                    local channel-number (0...)&n;   *             int                    Flag: Need ACK for this packet.&n;   *             struct sk_buff *skb    Data to send&n;   */
DECL|member|writebuf_skb
r_int
(paren
op_star
id|writebuf_skb
)paren
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
multiline_comment|/* Send raw D-Channel-Commands&n;   * Parameters:&n;   *             u_char pointer data&n;   *             int    length of data&n;   *             int    Flag: 0 = Call form Kernel-Space (use memcpy,&n;   *                              no schedule allowed) &n;   *                          1 = Data is in User-Space (use memcpy_fromfs,&n;   *                              may schedule)&n;   *             int    driverId&n;   *             int    local channel-number (0 ...)&n;   */
DECL|member|writecmd
r_int
(paren
op_star
id|writecmd
)paren
(paren
r_const
id|u_char
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Read raw Status replies&n;   *             u_char pointer data (volatile)&n;   *             int    length of buffer&n;   *             int    Flag: 0 = Call form Kernel-Space (use memcpy,&n;   *                              no schedule allowed) &n;   *                          1 = Data is in User-Space (use memcpy_fromfs,&n;   *                              may schedule)&n;   *             int    driverId&n;   *             int    local channel-number (0 ...)&n;   */
DECL|member|readstat
r_int
(paren
op_star
id|readstat
)paren
(paren
id|u_char
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
l_int|20
)braket
suffix:semicolon
DECL|typedef|isdn_if
)brace
id|isdn_if
suffix:semicolon
multiline_comment|/*&n; * Function which must be called by lowlevel-driver at loadtime with&n; * the following fields of above struct set:&n; *&n; * channels     Number of channels that will be supported.&n; * hl_hdrlen    Space to preserve in sk_buff&squot;s when sending. Drivers, not&n; *              supporting sk_buff&squot;s should set this to 0.&n; * command      Address of Command-Handler.&n; * features     Bitwise coded Features of this driver. (use ISDN_FEATURE_...)&n; * writebuf_skb Address of Skbuff-Send-Handler.&n; * writecmd        &quot;    &quot;  D-Channel  &quot; which accepts raw D-Ch-Commands.&n; * readstat        &quot;    &quot;  D-Channel  &quot; which delivers raw Status-Data.&n; *&n; * The linklevel-driver fills the following fields:&n; *&n; * channels      Driver-ID assigned to this driver. (Must be used on all&n; *               subsequent callbacks.&n; * rcvcallb_skb  Address of handler for received Skbuff&squot;s.&n; * statcallb        &quot;    &quot;     &quot;    for status-changes.&n; *&n; */
r_extern
r_int
id|register_isdn
c_func
(paren
id|isdn_if
op_star
)paren
suffix:semicolon
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ISDNIF_H__ */
eof
