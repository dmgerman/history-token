multiline_comment|/*&n; *  drivers/s390/char/sclp.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt;&n; *&t;&t; Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#ifndef __SCLP_H__
DECL|macro|__SCLP_H__
mdefine_line|#define __SCLP_H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
multiline_comment|/* maximum number of pages concerning our own memory management */
DECL|macro|MAX_KMEM_PAGES
mdefine_line|#define MAX_KMEM_PAGES (sizeof(unsigned long) &lt;&lt; 3)
DECL|macro|MAX_CONSOLE_PAGES
mdefine_line|#define MAX_CONSOLE_PAGES&t;4
DECL|macro|EvTyp_OpCmd
mdefine_line|#define EvTyp_OpCmd&t;&t;0x01
DECL|macro|EvTyp_Msg
mdefine_line|#define EvTyp_Msg&t;&t;0x02
DECL|macro|EvTyp_StateChange
mdefine_line|#define EvTyp_StateChange&t;0x08
DECL|macro|EvTyp_PMsgCmd
mdefine_line|#define EvTyp_PMsgCmd&t;&t;0x09
DECL|macro|EvTyp_CntlProgOpCmd
mdefine_line|#define EvTyp_CntlProgOpCmd&t;0x20
DECL|macro|EvTyp_CntlProgIdent
mdefine_line|#define EvTyp_CntlProgIdent&t;0x0B
DECL|macro|EvTyp_SigQuiesce
mdefine_line|#define EvTyp_SigQuiesce&t;0x1D
DECL|macro|EvTyp_VT220Msg
mdefine_line|#define EvTyp_VT220Msg&t;&t;0x1A
DECL|macro|EvTyp_OpCmd_Mask
mdefine_line|#define EvTyp_OpCmd_Mask&t;0x80000000
DECL|macro|EvTyp_Msg_Mask
mdefine_line|#define EvTyp_Msg_Mask&t;&t;0x40000000
DECL|macro|EvTyp_StateChange_Mask
mdefine_line|#define EvTyp_StateChange_Mask&t;0x01000000
DECL|macro|EvTyp_PMsgCmd_Mask
mdefine_line|#define EvTyp_PMsgCmd_Mask&t;0x00800000
DECL|macro|EvTyp_CtlProgOpCmd_Mask
mdefine_line|#define EvTyp_CtlProgOpCmd_Mask&t;0x00000001
DECL|macro|EvTyp_CtlProgIdent_Mask
mdefine_line|#define EvTyp_CtlProgIdent_Mask&t;0x00200000
DECL|macro|EvTyp_SigQuiesce_Mask
mdefine_line|#define EvTyp_SigQuiesce_Mask&t;0x00000008
DECL|macro|EvTyp_VT220Msg_Mask
mdefine_line|#define EvTyp_VT220Msg_Mask&t;0x00000040
DECL|macro|GnrlMsgFlgs_DOM
mdefine_line|#define GnrlMsgFlgs_DOM&t;&t;0x8000
DECL|macro|GnrlMsgFlgs_SndAlrm
mdefine_line|#define GnrlMsgFlgs_SndAlrm&t;0x4000
DECL|macro|GnrlMsgFlgs_HoldMsg
mdefine_line|#define GnrlMsgFlgs_HoldMsg&t;0x2000
DECL|macro|LnTpFlgs_CntlText
mdefine_line|#define LnTpFlgs_CntlText&t;0x8000
DECL|macro|LnTpFlgs_LabelText
mdefine_line|#define LnTpFlgs_LabelText&t;0x4000
DECL|macro|LnTpFlgs_DataText
mdefine_line|#define LnTpFlgs_DataText&t;0x2000
DECL|macro|LnTpFlgs_EndText
mdefine_line|#define LnTpFlgs_EndText&t;0x1000
DECL|macro|LnTpFlgs_PromptText
mdefine_line|#define LnTpFlgs_PromptText&t;0x0800
DECL|typedef|sclp_cmdw_t
r_typedef
r_int
r_int
id|sclp_cmdw_t
suffix:semicolon
DECL|macro|SCLP_CMDW_READDATA
mdefine_line|#define SCLP_CMDW_READDATA&t;0x00770005
DECL|macro|SCLP_CMDW_WRITEDATA
mdefine_line|#define SCLP_CMDW_WRITEDATA&t;0x00760005
DECL|macro|SCLP_CMDW_WRITEMASK
mdefine_line|#define SCLP_CMDW_WRITEMASK&t;0x00780005
DECL|macro|GDS_ID_MDSMU
mdefine_line|#define GDS_ID_MDSMU&t;&t;0x1310
DECL|macro|GDS_ID_MDSRouteInfo
mdefine_line|#define GDS_ID_MDSRouteInfo&t;0x1311
DECL|macro|GDS_ID_AgUnWrkCorr
mdefine_line|#define GDS_ID_AgUnWrkCorr&t;0x1549
DECL|macro|GDS_ID_SNACondReport
mdefine_line|#define GDS_ID_SNACondReport&t;0x1532
DECL|macro|GDS_ID_CPMSU
mdefine_line|#define GDS_ID_CPMSU&t;&t;0x1212
DECL|macro|GDS_ID_RoutTargInstr
mdefine_line|#define GDS_ID_RoutTargInstr&t;0x154D
DECL|macro|GDS_ID_OpReq
mdefine_line|#define GDS_ID_OpReq&t;&t;0x8070
DECL|macro|GDS_ID_TextCmd
mdefine_line|#define GDS_ID_TextCmd&t;&t;0x1320
DECL|macro|GDS_KEY_SelfDefTextMsg
mdefine_line|#define GDS_KEY_SelfDefTextMsg&t;0x31
DECL|typedef|sccb_mask_t
r_typedef
id|u32
id|sccb_mask_t
suffix:semicolon
multiline_comment|/* ATTENTION: assumes 32bit mask !!! */
DECL|struct|sccb_header
r_struct
id|sccb_header
(brace
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|function_code
id|u8
id|function_code
suffix:semicolon
DECL|member|control_mask
id|u8
id|control_mask
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|response_code
id|u16
id|response_code
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|gds_subvector
r_struct
id|gds_subvector
(brace
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|key
id|u8
id|key
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|gds_vector
r_struct
id|gds_vector
(brace
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|gds_id
id|u16
id|gds_id
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|evbuf_header
r_struct
id|evbuf_header
(brace
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|_reserved
id|u16
id|_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sclp_req
r_struct
id|sclp_req
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list_head for request queueing. */
DECL|member|command
id|sclp_cmdw_t
id|command
suffix:semicolon
multiline_comment|/* sclp command to execute */
DECL|member|sccb
r_void
op_star
id|sccb
suffix:semicolon
multiline_comment|/* pointer to the sccb to execute */
DECL|member|status
r_char
id|status
suffix:semicolon
multiline_comment|/* status of this request */
DECL|member|start_count
r_int
id|start_count
suffix:semicolon
multiline_comment|/* number of SVCs done for this req */
multiline_comment|/* Callback that is called after reaching final status. */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|sclp_req
op_star
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|callback_data
r_void
op_star
id|callback_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCLP_REQ_FILLED
mdefine_line|#define SCLP_REQ_FILLED&t;  0x00&t;/* request is ready to be processed */
DECL|macro|SCLP_REQ_QUEUED
mdefine_line|#define SCLP_REQ_QUEUED&t;  0x01&t;/* request is queued to be processed */
DECL|macro|SCLP_REQ_RUNNING
mdefine_line|#define SCLP_REQ_RUNNING  0x02&t;/* request is currently running */
DECL|macro|SCLP_REQ_DONE
mdefine_line|#define SCLP_REQ_DONE&t;  0x03&t;/* request is completed successfully */
DECL|macro|SCLP_REQ_FAILED
mdefine_line|#define SCLP_REQ_FAILED&t;  0x05&t;/* request is finally failed */
multiline_comment|/* function pointers that a high level driver has to use for registration */
multiline_comment|/* of some routines it wants to be called from the low level driver */
DECL|struct|sclp_register
r_struct
id|sclp_register
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* event masks this user is registered for */
DECL|member|receive_mask
id|sccb_mask_t
id|receive_mask
suffix:semicolon
DECL|member|send_mask
id|sccb_mask_t
id|send_mask
suffix:semicolon
multiline_comment|/* actually present events */
DECL|member|sclp_receive_mask
id|sccb_mask_t
id|sclp_receive_mask
suffix:semicolon
DECL|member|sclp_send_mask
id|sccb_mask_t
id|sclp_send_mask
suffix:semicolon
multiline_comment|/* called if event type availability changes */
DECL|member|state_change_fn
r_void
(paren
op_star
id|state_change_fn
)paren
(paren
r_struct
id|sclp_register
op_star
)paren
suffix:semicolon
multiline_comment|/* called for events in cp_receive_mask/sclp_receive_mask */
DECL|member|receiver_fn
r_void
(paren
op_star
id|receiver_fn
)paren
(paren
r_struct
id|evbuf_header
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* externals from sclp.c */
r_int
id|sclp_add_request
c_func
(paren
r_struct
id|sclp_req
op_star
id|req
)paren
suffix:semicolon
r_void
id|sclp_sync_wait
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|sclp_register
c_func
(paren
r_struct
id|sclp_register
op_star
id|reg
)paren
suffix:semicolon
r_void
id|sclp_unregister
c_func
(paren
r_struct
id|sclp_register
op_star
id|reg
)paren
suffix:semicolon
r_int
id|sclp_remove_processed
c_func
(paren
r_struct
id|sccb_header
op_star
id|sccb
)paren
suffix:semicolon
r_int
id|sclp_deactivate
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|sclp_reactivate
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* useful inlines */
multiline_comment|/* VM uses EBCDIC 037, LPAR+native(SE+HMC) use EBCDIC 500 */
multiline_comment|/* translate single character from ASCII to EBCDIC */
r_static
r_inline
r_int
r_char
DECL|function|sclp_ascebc
id|sclp_ascebc
c_func
(paren
r_int
r_char
id|ch
)paren
(brace
r_return
(paren
id|MACHINE_IS_VM
)paren
ques
c_cond
id|_ascebc
(braket
id|ch
)braket
suffix:colon
id|_ascebc_500
(braket
id|ch
)braket
suffix:semicolon
)brace
multiline_comment|/* translate string from EBCDIC to ASCII */
r_static
r_inline
r_void
DECL|function|sclp_ebcasc_str
id|sclp_ebcasc_str
c_func
(paren
r_int
r_char
op_star
id|str
comma
r_int
id|nr
)paren
(brace
(paren
id|MACHINE_IS_VM
)paren
ques
c_cond
id|EBCASC
c_func
(paren
id|str
comma
id|nr
)paren
suffix:colon
id|EBCASC_500
c_func
(paren
id|str
comma
id|nr
)paren
suffix:semicolon
)brace
multiline_comment|/* translate string from ASCII to EBCDIC */
r_static
r_inline
r_void
DECL|function|sclp_ascebc_str
id|sclp_ascebc_str
c_func
(paren
r_int
r_char
op_star
id|str
comma
r_int
id|nr
)paren
(brace
(paren
id|MACHINE_IS_VM
)paren
ques
c_cond
id|ASCEBC
c_func
(paren
id|str
comma
id|nr
)paren
suffix:colon
id|ASCEBC_500
c_func
(paren
id|str
comma
id|nr
)paren
suffix:semicolon
)brace
macro_line|#endif&t; /* __SCLP_H__ */
eof
