multiline_comment|/*&n; *  linux/include/asm-cris/ide.h&n; *&n; *  Copyright (C) 2000  Axis Communications AB&n; *&n; *  Authors:    Bjorn Wesen&n; *&n; */
multiline_comment|/*&n; *  This file contains the ETRAX 100LX specific IDE code.&n; */
macro_line|#ifndef __ASMCRIS_IDE_H
DECL|macro|__ASMCRIS_IDE_H
mdefine_line|#define __ASMCRIS_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/svinto.h&gt;
multiline_comment|/* ETRAX 100 can support 4 IDE busses on the same pins (serialized) */
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;__sti()
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
multiline_comment|/* all IDE busses share the same IRQ, number 4.&n;&t; * this has the side-effect that ide-probe.c will cluster our 4 interfaces&n;&t; * together in a hwgroup, and will serialize accesses. this is good, because&n;&t; * we can&squot;t access more than one interface at the same time on ETRAX100.&n;&t; */
r_return
l_int|4
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
id|ide_ioreg_t
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
multiline_comment|/* we have no real I/O base address per interface, since all go through the&n;&t; * same register. but in a bitfield in that register, we have the i/f number.&n;&t; * so we can use the io_base to remember that bitfield.&n;&t; */
r_static
r_const
r_int
r_int
id|io_bases
(braket
id|MAX_HWIFS
)braket
op_assign
(brace
id|IO_FIELD
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|sel
comma
l_int|0
)paren
comma
id|IO_FIELD
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|sel
comma
l_int|1
)paren
comma
id|IO_FIELD
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|sel
comma
l_int|2
)paren
comma
id|IO_FIELD
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|sel
comma
l_int|3
)paren
)brace
suffix:semicolon
r_return
id|io_bases
(braket
id|index
)braket
suffix:semicolon
)brace
multiline_comment|/* this is called once for each interface, to setup the port addresses. data_port is the result&n; * of the ide_default_io_base call above. ctrl_port will be 0, but that is don&squot;t care for us.&n; */
DECL|function|ide_init_hwif_ports
r_static
id|__inline__
r_void
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* fill in ports for ATA addresses 0 to 7 */
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|data_port
op_or
id|IO_FIELD
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|addr
comma
id|i
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|cs0
comma
id|active
)paren
suffix:semicolon
)brace
multiline_comment|/* the IDE control register is at ATA address 6, with CS1 active instead of CS0 */
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|data_port
op_or
id|IO_FIELD
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|addr
comma
l_int|6
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_ATA_CTRL_DATA
comma
id|cs1
comma
id|active
)paren
suffix:semicolon
multiline_comment|/* whats this for ? */
id|hw-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|ide_init_default_hwifs
r_static
id|__inline__
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_HWIFS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hw
comma
id|ide_default_io_base
c_func
(paren
id|index
)paren
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|ide_default_irq
c_func
(paren
id|ide_default_io_base
c_func
(paren
id|index
)paren
)paren
suffix:semicolon
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|bit0
r_int
id|bit0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nIEN
r_int
id|nIEN
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device INTRQ to host */
DECL|member|SRST
r_int
id|SRST
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* host soft reset bit */
DECL|member|bit3
r_int
id|bit3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ATA-2 thingy */
DECL|member|reserved456
r_int
id|reserved456
suffix:colon
l_int|3
suffix:semicolon
DECL|member|HOB
r_int
id|HOB
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 48-bit address ordering */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|control_t
)brace
id|control_t
suffix:semicolon
multiline_comment|/* some configuration options we don&squot;t need */
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC 0
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS&t;0
multiline_comment|/* request and free a normal interrupt */
DECL|macro|ide_request_irq
mdefine_line|#define ide_request_irq(irq,hand,flg,dev,id)&t;request_irq((irq),(hand),(flg),(dev),(id))
DECL|macro|ide_free_irq
mdefine_line|#define ide_free_irq(irq,dev_id)&t;&t;free_irq((irq), (dev_id))
multiline_comment|/* ide-probe.c calls ide_request_region and stuff on the io_ports defined,&n; * but since they are not actually memory-mapped in the ETRAX driver, we don&squot;t&n; * do anything.&n; */
DECL|macro|ide_check_region
mdefine_line|#define ide_check_region(from,extent)&t;&t;(0)
DECL|macro|ide_request_region
mdefine_line|#define ide_request_region(from,extent,name)&t;do {} while(0)
DECL|macro|ide_release_region
mdefine_line|#define ide_release_region(from,extent)&t;&t;do {} while(0)
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_fix_driveid
mdefine_line|#define ide_fix_driveid(id)&t;&t;do {} while (0)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
multiline_comment|/* the drive addressing is done through a controller register on the Etrax CPU */
r_void
id|OUT_BYTE
c_func
(paren
r_int
r_char
id|data
comma
id|ide_ioreg_t
id|reg
)paren
suffix:semicolon
r_int
r_char
id|IN_BYTE
c_func
(paren
id|ide_ioreg_t
id|reg
)paren
suffix:semicolon
multiline_comment|/* this tells ide.h not to define the standard macros */
DECL|macro|HAVE_ARCH_IN_OUT
mdefine_line|#define HAVE_ARCH_IN_OUT&t;1
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMCRIS_IDE_H */
eof
