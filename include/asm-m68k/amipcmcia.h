multiline_comment|/*&n;** asm-m68k/pcmcia.h -- Amiga Linux PCMCIA Definitions&n;**&n;** Copyright 1997 by Alain Malek&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created: 12/10/97 by Alain Malek&n;*/
macro_line|#ifndef __AMIGA_PCMCIA_H__
DECL|macro|__AMIGA_PCMCIA_H__
mdefine_line|#define __AMIGA_PCMCIA_H__
macro_line|#include &lt;asm/amigayle.h&gt;
multiline_comment|/* prototypes */
r_void
id|pcmcia_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pcmcia_copy_tuple
c_func
(paren
r_int
r_char
id|tuple_id
comma
r_void
op_star
id|tuple
comma
r_int
id|max_len
)paren
suffix:semicolon
r_void
id|pcmcia_program_voltage
c_func
(paren
r_int
id|voltage
)paren
suffix:semicolon
r_void
id|pcmcia_access_speed
c_func
(paren
r_int
id|speed
)paren
suffix:semicolon
r_void
id|pcmcia_write_enable
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pcmcia_write_disable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|pcmcia_read_status
r_static
r_inline
id|u_char
id|pcmcia_read_status
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|gayle.cardstatus
op_amp
l_int|0x7c
)paren
suffix:semicolon
)brace
DECL|function|pcmcia_get_intreq
r_static
r_inline
id|u_char
id|pcmcia_get_intreq
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|gayle.intreq
)paren
suffix:semicolon
)brace
DECL|function|pcmcia_ack_int
r_static
r_inline
r_void
id|pcmcia_ack_int
c_func
(paren
id|u_char
id|intreq
)paren
(brace
id|gayle.intreq
op_assign
l_int|0xf8
suffix:semicolon
)brace
DECL|function|pcmcia_enable_irq
r_static
r_inline
r_void
id|pcmcia_enable_irq
c_func
(paren
r_void
)paren
(brace
id|gayle.inten
op_or_assign
id|GAYLE_IRQ_IRQ
suffix:semicolon
)brace
DECL|function|pcmcia_disable_irq
r_static
r_inline
r_void
id|pcmcia_disable_irq
c_func
(paren
r_void
)paren
(brace
id|gayle.inten
op_and_assign
op_complement
id|GAYLE_IRQ_IRQ
suffix:semicolon
)brace
DECL|macro|PCMCIA_INSERTED
mdefine_line|#define PCMCIA_INSERTED&t;(gayle.cardstatus &amp; GAYLE_CS_CCDET)
multiline_comment|/* valid voltages for pcmcia_ProgramVoltage */
DECL|macro|PCMCIA_0V
mdefine_line|#define PCMCIA_0V&t;0
DECL|macro|PCMCIA_5V
mdefine_line|#define PCMCIA_5V&t;5
DECL|macro|PCMCIA_12V
mdefine_line|#define PCMCIA_12V&t;12
multiline_comment|/* valid speeds for pcmcia_AccessSpeed */
DECL|macro|PCMCIA_SPEED_100NS
mdefine_line|#define PCMCIA_SPEED_100NS&t;100
DECL|macro|PCMCIA_SPEED_150NS
mdefine_line|#define PCMCIA_SPEED_150NS&t;150
DECL|macro|PCMCIA_SPEED_250NS
mdefine_line|#define PCMCIA_SPEED_250NS&t;250
DECL|macro|PCMCIA_SPEED_720NS
mdefine_line|#define PCMCIA_SPEED_720NS&t;720
multiline_comment|/* PCMCIA Tuple codes */
DECL|macro|CISTPL_NULL
mdefine_line|#define CISTPL_NULL&t;&t;0x00
DECL|macro|CISTPL_DEVICE
mdefine_line|#define CISTPL_DEVICE&t;&t;0x01
DECL|macro|CISTPL_LONGLINK_CB
mdefine_line|#define CISTPL_LONGLINK_CB&t;0x02
DECL|macro|CISTPL_CONFIG_CB
mdefine_line|#define CISTPL_CONFIG_CB&t;0x04
DECL|macro|CISTPL_CFTABLE_ENTRY_CB
mdefine_line|#define CISTPL_CFTABLE_ENTRY_CB&t;0x05
DECL|macro|CISTPL_LONGLINK_MFC
mdefine_line|#define CISTPL_LONGLINK_MFC&t;0x06
DECL|macro|CISTPL_BAR
mdefine_line|#define CISTPL_BAR&t;&t;0x07
DECL|macro|CISTPL_CHECKSUM
mdefine_line|#define CISTPL_CHECKSUM&t;&t;0x10
DECL|macro|CISTPL_LONGLINK_A
mdefine_line|#define CISTPL_LONGLINK_A&t;0x11
DECL|macro|CISTPL_LONGLINK_C
mdefine_line|#define CISTPL_LONGLINK_C&t;0x12
DECL|macro|CISTPL_LINKTARGET
mdefine_line|#define CISTPL_LINKTARGET&t;0x13
DECL|macro|CISTPL_NO_LINK
mdefine_line|#define CISTPL_NO_LINK&t;&t;0x14
DECL|macro|CISTPL_VERS_1
mdefine_line|#define CISTPL_VERS_1&t;&t;0x15
DECL|macro|CISTPL_ALTSTR
mdefine_line|#define CISTPL_ALTSTR&t;&t;0x16
DECL|macro|CISTPL_DEVICE_A
mdefine_line|#define CISTPL_DEVICE_A&t;&t;0x17
DECL|macro|CISTPL_JEDEC_C
mdefine_line|#define CISTPL_JEDEC_C&t;&t;0x18
DECL|macro|CISTPL_JEDEC_A
mdefine_line|#define CISTPL_JEDEC_A&t;&t;0x19
DECL|macro|CISTPL_CONFIG
mdefine_line|#define CISTPL_CONFIG&t;&t;0x1a
DECL|macro|CISTPL_CFTABLE_ENTRY
mdefine_line|#define CISTPL_CFTABLE_ENTRY&t;0x1b
DECL|macro|CISTPL_DEVICE_OC
mdefine_line|#define CISTPL_DEVICE_OC&t;0x1c
DECL|macro|CISTPL_DEVICE_OA
mdefine_line|#define CISTPL_DEVICE_OA&t;0x1d
DECL|macro|CISTPL_DEVICE_GEO
mdefine_line|#define CISTPL_DEVICE_GEO&t;0x1e
DECL|macro|CISTPL_DEVICE_GEO_A
mdefine_line|#define CISTPL_DEVICE_GEO_A&t;0x1f
DECL|macro|CISTPL_MANFID
mdefine_line|#define CISTPL_MANFID&t;&t;0x20
DECL|macro|CISTPL_FUNCID
mdefine_line|#define CISTPL_FUNCID&t;&t;0x21
DECL|macro|CISTPL_FUNCE
mdefine_line|#define CISTPL_FUNCE&t;&t;0x22
DECL|macro|CISTPL_SWIL
mdefine_line|#define CISTPL_SWIL&t;&t;0x23
DECL|macro|CISTPL_END
mdefine_line|#define CISTPL_END&t;&t;0xff
multiline_comment|/* FUNCID */
DECL|macro|CISTPL_FUNCID_MULTI
mdefine_line|#define CISTPL_FUNCID_MULTI&t;0x00
DECL|macro|CISTPL_FUNCID_MEMORY
mdefine_line|#define CISTPL_FUNCID_MEMORY&t;0x01
DECL|macro|CISTPL_FUNCID_SERIAL
mdefine_line|#define CISTPL_FUNCID_SERIAL&t;0x02
DECL|macro|CISTPL_FUNCID_PARALLEL
mdefine_line|#define CISTPL_FUNCID_PARALLEL&t;0x03
DECL|macro|CISTPL_FUNCID_FIXED
mdefine_line|#define CISTPL_FUNCID_FIXED&t;0x04
DECL|macro|CISTPL_FUNCID_VIDEO
mdefine_line|#define CISTPL_FUNCID_VIDEO&t;0x05
DECL|macro|CISTPL_FUNCID_NETWORK
mdefine_line|#define CISTPL_FUNCID_NETWORK&t;0x06
DECL|macro|CISTPL_FUNCID_AIMS
mdefine_line|#define CISTPL_FUNCID_AIMS&t;0x07
DECL|macro|CISTPL_FUNCID_SCSI
mdefine_line|#define CISTPL_FUNCID_SCSI&t;0x08
macro_line|#endif
eof
