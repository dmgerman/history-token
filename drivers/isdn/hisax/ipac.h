multiline_comment|/* $Id: ipac.h,v 1.5.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * IPAC specific defines&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/* All Registers original Siemens Spec  */
DECL|macro|IPAC_CONF
mdefine_line|#define IPAC_CONF&t;0xC0
DECL|macro|IPAC_MASK
mdefine_line|#define IPAC_MASK&t;0xC1
DECL|macro|IPAC_ISTA
mdefine_line|#define IPAC_ISTA&t;0xC1
DECL|macro|IPAC_ID
mdefine_line|#define IPAC_ID&t;&t;0xC2
DECL|macro|IPAC_ACFG
mdefine_line|#define IPAC_ACFG&t;0xC3
DECL|macro|IPAC_AOE
mdefine_line|#define IPAC_AOE&t;0xC4
DECL|macro|IPAC_ARX
mdefine_line|#define IPAC_ARX&t;0xC5
DECL|macro|IPAC_ATX
mdefine_line|#define IPAC_ATX&t;0xC5
DECL|macro|IPAC_PITA1
mdefine_line|#define IPAC_PITA1&t;0xC6
DECL|macro|IPAC_PITA2
mdefine_line|#define IPAC_PITA2&t;0xC7
DECL|macro|IPAC_POTA1
mdefine_line|#define IPAC_POTA1&t;0xC8
DECL|macro|IPAC_POTA2
mdefine_line|#define IPAC_POTA2&t;0xC9
DECL|macro|IPAC_PCFG
mdefine_line|#define IPAC_PCFG&t;0xCA
DECL|macro|IPAC_SCFG
mdefine_line|#define IPAC_SCFG&t;0xCB
DECL|macro|IPAC_TIMR2
mdefine_line|#define IPAC_TIMR2&t;0xCC
r_void
id|ipac_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_void
id|ipac_irq
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/* Macro to build the needed D- and B-Channel access routines given&n; * access functions for the IPAC */
DECL|macro|BUILD_IPAC_OPS
mdefine_line|#define BUILD_IPAC_OPS(ipac)                                                  &bslash;&n;                                                                              &bslash;&n;static u8                                                                     &bslash;&n;ipac ## _dc_read(struct IsdnCardState *cs, u8 offset)                         &bslash;&n;{                                                                             &bslash;&n;&t;return ipac ## _read(cs, offset+0x80);                                &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static void                                                                   &bslash;&n;ipac ## _dc_write(struct IsdnCardState *cs, u8 offset, u8 value)              &bslash;&n;{                                                                             &bslash;&n;&t;ipac ## _write(cs, offset+0x80, value);                               &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static void                                                                   &bslash;&n;ipac ## _dc_read_fifo(struct IsdnCardState *cs, u8 * data, int size)          &bslash;&n;{                                                                             &bslash;&n;&t;ipac ## _readfifo(cs, 0x80, data, size);                              &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static void                                                                   &bslash;&n;ipac ## _dc_write_fifo(struct IsdnCardState *cs, u8 * data, int size)         &bslash;&n;{                                                                             &bslash;&n;&t;ipac ## _writefifo(cs, 0x80, data, size);                             &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static struct dc_hw_ops ipac ## _dc_ops = {                                   &bslash;&n;&t;.read_reg   = ipac ## _dc_read,                                       &bslash;&n;&t;.write_reg  = ipac ## _dc_write,                                      &bslash;&n;&t;.read_fifo  = ipac ## _dc_read_fifo,                                  &bslash;&n;&t;.write_fifo = ipac ## _dc_write_fifo,                                 &bslash;&n;};                                                                            &bslash;&n;                                                                              &bslash;&n;static u8                                                                     &bslash;&n;ipac ## _bc_read(struct IsdnCardState *cs, int hscx, u8 offset)               &bslash;&n;{                                                                             &bslash;&n;&t;return ipac ## _read(cs, offset + (hscx ? 0x40 : 0));                 &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static void                                                                   &bslash;&n;ipac ## _bc_write(struct IsdnCardState *cs, int hscx, u8 offset, u8 value)    &bslash;&n;{                                                                             &bslash;&n;&t;ipac ## _write(cs, offset + (hscx ? 0x40 : 0), value);                &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static void                                                                   &bslash;&n;ipac ## _bc_read_fifo(struct IsdnCardState *cs, int hscx, u8 *data, int size) &bslash;&n;{                                                                             &bslash;&n;&t;ipac ## _readfifo(cs, hscx ? 0x40 : 0, data, size);                   &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static void                                                                   &bslash;&n;ipac ## _bc_write_fifo(struct IsdnCardState *cs, int hscx, u8 *data, int size)&bslash;&n;{                                                                             &bslash;&n;&t;ipac ## _writefifo(cs, hscx ? 0x40 : 0, data, size);                  &bslash;&n;}                                                                             &bslash;&n;                                                                              &bslash;&n;static struct bc_hw_ops ipac ## _bc_ops = {                                   &bslash;&n;&t;.read_reg   = ipac ## _bc_read,                                       &bslash;&n;&t;.write_reg  = ipac ## _bc_write,                                      &bslash;&n;&t;.read_fifo  = ipac ## _bc_read_fifo,                                  &bslash;&n;&t;.write_fifo = ipac ## _bc_write_fifo,                                 &bslash;&n;}
eof
