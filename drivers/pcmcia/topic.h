multiline_comment|/*&n; * topic.h 1.8 1999/08/28 04:01:47&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; * topic.h $Release$ 1999/08/28 04:01:47&n; */
macro_line|#ifndef _LINUX_TOPIC_H
DECL|macro|_LINUX_TOPIC_H
mdefine_line|#define _LINUX_TOPIC_H
multiline_comment|/* Register definitions for Toshiba ToPIC95/97/100 controllers */
DECL|macro|TOPIC_SOCKET_CONTROL
mdefine_line|#define TOPIC_SOCKET_CONTROL&t;&t;0x0090&t;/* 32 bit */
DECL|macro|TOPIC_SCR_IRQSEL
mdefine_line|#define  TOPIC_SCR_IRQSEL&t;&t;0x00000001
DECL|macro|TOPIC_SLOT_CONTROL
mdefine_line|#define TOPIC_SLOT_CONTROL&t;&t;0x00a0&t;/* 8 bit */
DECL|macro|TOPIC_SLOT_SLOTON
mdefine_line|#define  TOPIC_SLOT_SLOTON&t;&t;0x80
DECL|macro|TOPIC_SLOT_SLOTEN
mdefine_line|#define  TOPIC_SLOT_SLOTEN&t;&t;0x40
DECL|macro|TOPIC_SLOT_ID_LOCK
mdefine_line|#define  TOPIC_SLOT_ID_LOCK&t;&t;0x20
DECL|macro|TOPIC_SLOT_ID_WP
mdefine_line|#define  TOPIC_SLOT_ID_WP&t;&t;0x10
DECL|macro|TOPIC_SLOT_PORT_MASK
mdefine_line|#define  TOPIC_SLOT_PORT_MASK&t;&t;0x0c
DECL|macro|TOPIC_SLOT_PORT_SHIFT
mdefine_line|#define  TOPIC_SLOT_PORT_SHIFT&t;&t;2
DECL|macro|TOPIC_SLOT_OFS_MASK
mdefine_line|#define  TOPIC_SLOT_OFS_MASK&t;&t;0x03
DECL|macro|TOPIC_CARD_CONTROL
mdefine_line|#define TOPIC_CARD_CONTROL&t;&t;0x00a1&t;/* 8 bit */
DECL|macro|TOPIC_CCR_INTB
mdefine_line|#define  TOPIC_CCR_INTB&t;&t;&t;0x20
DECL|macro|TOPIC_CCR_INTA
mdefine_line|#define  TOPIC_CCR_INTA&t;&t;&t;0x10
DECL|macro|TOPIC_CCR_CLOCK
mdefine_line|#define  TOPIC_CCR_CLOCK&t;&t;0x0c
DECL|macro|TOPIC_CCR_PCICLK
mdefine_line|#define  TOPIC_CCR_PCICLK&t;&t;0x0c
DECL|macro|TOPIC_CCR_PCICLK_2
mdefine_line|#define  TOPIC_CCR_PCICLK_2&t;&t;0x08
DECL|macro|TOPIC_CCR_CCLK
mdefine_line|#define  TOPIC_CCR_CCLK&t;&t;&t;0x04
DECL|macro|TOPIC97_INT_CONTROL
mdefine_line|#define TOPIC97_INT_CONTROL&t;&t;0x00a1&t;/* 8 bit */
DECL|macro|TOPIC97_ICR_INTB
mdefine_line|#define  TOPIC97_ICR_INTB&t;&t;0x20
DECL|macro|TOPIC97_ICR_INTA
mdefine_line|#define  TOPIC97_ICR_INTA&t;&t;0x10
DECL|macro|TOPIC97_ICR_STSIRQNP
mdefine_line|#define  TOPIC97_ICR_STSIRQNP&t;&t;0x04
DECL|macro|TOPIC97_ICR_IRQNP
mdefine_line|#define  TOPIC97_ICR_IRQNP&t;&t;0x02
DECL|macro|TOPIC97_ICR_IRQSEL
mdefine_line|#define  TOPIC97_ICR_IRQSEL&t;&t;0x01
DECL|macro|TOPIC_CARD_DETECT
mdefine_line|#define TOPIC_CARD_DETECT&t;&t;0x00a3&t;/* 8 bit */
DECL|macro|TOPIC_CDR_MODE_PC32
mdefine_line|#define  TOPIC_CDR_MODE_PC32&t;&t;0x80
DECL|macro|TOPIC_CDR_VS1
mdefine_line|#define  TOPIC_CDR_VS1&t;&t;&t;0x04
DECL|macro|TOPIC_CDR_VS2
mdefine_line|#define  TOPIC_CDR_VS2&t;&t;&t;0x02
DECL|macro|TOPIC_CDR_SW_DETECT
mdefine_line|#define  TOPIC_CDR_SW_DETECT&t;&t;0x01
DECL|macro|TOPIC_REGISTER_CONTROL
mdefine_line|#define TOPIC_REGISTER_CONTROL&t;&t;0x00a4&t;/* 32 bit */
DECL|macro|TOPIC_RCR_RESUME_RESET
mdefine_line|#define  TOPIC_RCR_RESUME_RESET&t;&t;0x80000000
DECL|macro|TOPIC_RCR_REMOVE_RESET
mdefine_line|#define  TOPIC_RCR_REMOVE_RESET&t;&t;0x40000000
DECL|macro|TOPIC97_RCR_CLKRUN_ENA
mdefine_line|#define  TOPIC97_RCR_CLKRUN_ENA&t;&t;0x20000000
DECL|macro|TOPIC97_RCR_TESTMODE
mdefine_line|#define  TOPIC97_RCR_TESTMODE&t;&t;0x10000000
DECL|macro|TOPIC97_RCR_IOPLUP
mdefine_line|#define  TOPIC97_RCR_IOPLUP&t;&t;0x08000000
DECL|macro|TOPIC_RCR_BUFOFF_PWROFF
mdefine_line|#define  TOPIC_RCR_BUFOFF_PWROFF&t;0x02000000
DECL|macro|TOPIC_RCR_BUFOFF_SIGOFF
mdefine_line|#define  TOPIC_RCR_BUFOFF_SIGOFF&t;0x01000000
DECL|macro|TOPIC97_RCR_CB_DEV_MASK
mdefine_line|#define  TOPIC97_RCR_CB_DEV_MASK&t;0x0000f800
DECL|macro|TOPIC97_RCR_CB_DEV_SHIFT
mdefine_line|#define  TOPIC97_RCR_CB_DEV_SHIFT&t;11
DECL|macro|TOPIC97_RCR_RI_DISABLE
mdefine_line|#define  TOPIC97_RCR_RI_DISABLE&t;&t;0x00000004
DECL|macro|TOPIC97_RCR_CAUDIO_OFF
mdefine_line|#define  TOPIC97_RCR_CAUDIO_OFF&t;&t;0x00000002
DECL|macro|TOPIC_RCR_CAUDIO_INVERT
mdefine_line|#define  TOPIC_RCR_CAUDIO_INVERT&t;0x00000001
DECL|macro|TOPIC97_MISC1
mdefine_line|#define TOPIC97_MISC1&t;&t;&t;0x00ad  /* 8bit */
DECL|macro|TOPIC97_MISC1_CLOCKRUN_ENABLE
mdefine_line|#define  TOPIC97_MISC1_CLOCKRUN_ENABLE&t;0x80
DECL|macro|TOPIC97_MISC1_CLOCKRUN_MODE
mdefine_line|#define  TOPIC97_MISC1_CLOCKRUN_MODE&t;0x40
DECL|macro|TOPIC97_MISC1_DETECT_REQ_ENA
mdefine_line|#define  TOPIC97_MISC1_DETECT_REQ_ENA&t;0x10
DECL|macro|TOPIC97_MISC1_SCK_CLEAR_DIS
mdefine_line|#define  TOPIC97_MISC1_SCK_CLEAR_DIS&t;0x04
DECL|macro|TOPIC97_MISC1_R2_LOW_ENABLE
mdefine_line|#define  TOPIC97_MISC1_R2_LOW_ENABLE&t;0x10
DECL|macro|TOPIC97_MISC2
mdefine_line|#define TOPIC97_MISC2&t;&t;&t;0x00ae  /* 8 bit */
DECL|macro|TOPIC97_MISC2_SPWRCLK_MASK
mdefine_line|#define  TOPIC97_MISC2_SPWRCLK_MASK&t;0x70
DECL|macro|TOPIC97_MISC2_SPWRMOD
mdefine_line|#define  TOPIC97_MISC2_SPWRMOD&t;&t;0x08
DECL|macro|TOPIC97_MISC2_SPWR_ENABLE
mdefine_line|#define  TOPIC97_MISC2_SPWR_ENABLE&t;0x04
DECL|macro|TOPIC97_MISC2_ZV_MODE
mdefine_line|#define  TOPIC97_MISC2_ZV_MODE&t;&t;0x02
DECL|macro|TOPIC97_MISC2_ZV_ENABLE
mdefine_line|#define  TOPIC97_MISC2_ZV_ENABLE&t;0x01
DECL|macro|TOPIC97_ZOOM_VIDEO_CONTROL
mdefine_line|#define TOPIC97_ZOOM_VIDEO_CONTROL&t;0x009c  /* 8 bit */
DECL|macro|TOPIC97_ZV_CONTROL_ENABLE
mdefine_line|#define  TOPIC97_ZV_CONTROL_ENABLE&t;0x01
DECL|macro|TOPIC97_AUDIO_VIDEO_SWITCH
mdefine_line|#define TOPIC97_AUDIO_VIDEO_SWITCH&t;0x003c  /* 8 bit */
DECL|macro|TOPIC97_AVS_AUDIO_CONTROL
mdefine_line|#define  TOPIC97_AVS_AUDIO_CONTROL&t;0x02
DECL|macro|TOPIC97_AVS_VIDEO_CONTROL
mdefine_line|#define  TOPIC97_AVS_VIDEO_CONTROL&t;0x01
DECL|function|topic97_zoom_video
r_static
r_void
id|topic97_zoom_video
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
r_int
id|onoff
)paren
(brace
r_struct
id|yenta_socket
op_star
id|socket
op_assign
id|container_of
c_func
(paren
id|sock
comma
r_struct
id|yenta_socket
comma
id|socket
)paren
suffix:semicolon
id|u8
id|reg_zv
comma
id|reg
suffix:semicolon
id|reg_zv
op_assign
id|config_readb
c_func
(paren
id|socket
comma
id|TOPIC97_ZOOM_VIDEO_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|onoff
)paren
(brace
id|reg_zv
op_or_assign
id|TOPIC97_ZV_CONTROL_ENABLE
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TOPIC97_ZOOM_VIDEO_CONTROL
comma
id|reg_zv
)paren
suffix:semicolon
id|reg
op_assign
id|config_readb
c_func
(paren
id|socket
comma
id|TOPIC97_MISC2
)paren
suffix:semicolon
id|reg
op_or_assign
id|TOPIC97_MISC2_ZV_ENABLE
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TOPIC97_MISC2
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* not sure this is needed, doc is unclear */
macro_line|#if 0
id|reg
op_assign
id|config_readb
c_func
(paren
id|socket
comma
id|TOPIC97_AUDIO_VIDEO_SWITCH
)paren
suffix:semicolon
id|reg
op_or_assign
id|TOPIC97_AVS_AUDIO_CONTROL
op_or
id|TOPIC97_AVS_VIDEO_CONTROL
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TOPIC97_AUDIO_VIDEO_SWITCH
comma
id|reg
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|reg_zv
op_and_assign
op_complement
id|TOPIC97_ZV_CONTROL_ENABLE
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TOPIC97_ZOOM_VIDEO_CONTROL
comma
id|reg_zv
)paren
suffix:semicolon
)brace
)brace
DECL|function|topic97_override
r_static
r_int
id|topic97_override
c_func
(paren
r_struct
id|yenta_socket
op_star
id|socket
)paren
(brace
multiline_comment|/* ToPIC97/100 support ZV */
id|socket-&gt;socket.zoom_video
op_assign
id|topic97_zoom_video
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_TOPIC_H */
eof
