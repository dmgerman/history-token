multiline_comment|/*&n; * arch/ppc/platforms/sandpoint.h&n; * &n; * Definitions for Motorola SPS Sandpoint Test Platform&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2000, 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * Sandpoint uses the CHRP map (Map B).&n; */
macro_line|#ifndef __PPC_PLATFORMS_SANDPOINT_H
DECL|macro|__PPC_PLATFORMS_SANDPOINT_H
mdefine_line|#define __PPC_PLATFORMS_SANDPOINT_H
macro_line|#ifdef CONFIG_SANDPOINT_X3
DECL|macro|SANDPOINT_SIO_SLOT
mdefine_line|#define SANDPOINT_SIO_SLOT      0&t;/* Cascaded from EPIC IRQ 0 */
macro_line|#if 0
multiline_comment|/* The Sandpoint X3 allows the IDE interrupt to be directly connected&n; * from the Windbond (PCI INTC or INTD) to the serial EPIC.  Someday&n; * we should try this, but it was easier to use the existing 83c553&n; * initialization than change it to route the different interrupts :-).&n; *&t;-- Dan&n; */
mdefine_line|#define SANDPOINT_IDE_INT0&t;23&t;/* EPIC 7 */
mdefine_line|#define SANDPOINT_IDE_INT1&t;24&t;/* EPIC 8 */
macro_line|#else
DECL|macro|SANDPOINT_IDE_INT0
mdefine_line|#define SANDPOINT_IDE_INT0&t;14&t;/* 8259 Test */
DECL|macro|SANDPOINT_IDE_INT1
mdefine_line|#define SANDPOINT_IDE_INT1&t;15&t;/* 8259 Test */
macro_line|#endif
macro_line|#else
multiline_comment|/*&n;  * Define the PCI slot that the 8259 is sharing interrupts with.&n;  * Valid values are 1 (PCI slot 2) and 2 (PCI slot 3).&n;  */
DECL|macro|SANDPOINT_SIO_SLOT
mdefine_line|#define SANDPOINT_SIO_SLOT      1
multiline_comment|/* ...and for the IDE from the 8259....&n;*/
DECL|macro|SANDPOINT_IDE_INT0
mdefine_line|#define SANDPOINT_IDE_INT0&t;14
DECL|macro|SANDPOINT_IDE_INT1
mdefine_line|#define SANDPOINT_IDE_INT1&t;15
macro_line|#endif
DECL|macro|SANDPOINT_SIO_IRQ
mdefine_line|#define&t;SANDPOINT_SIO_IRQ&t;(SANDPOINT_SIO_SLOT + NUM_8259_INTERRUPTS)
multiline_comment|/*&n; * The sandpoint boards have processor modules that either have an 8240 or&n; * an MPC107 host bridge on them.  These bridges have an IDSEL line that allows&n; * them to respond to PCI transactions as if they were a normal PCI devices.&n; * However, the processor on the processor side of the bridge can not reach&n; * out onto the PCI bus and then select the bridge or bad things will happen&n; * (documented in the 8240 and 107 manuals).&n; * Because of this, we always skip the bridge PCI device when accessing the&n; * PCI bus.  The PCI slot that the bridge occupies is defined by the macro&n; * below.&n; */
DECL|macro|SANDPOINT_HOST_BRIDGE_IDSEL
mdefine_line|#define SANDPOINT_HOST_BRIDGE_IDSEL     12
r_void
id|sandpoint_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __PPC_PLATFORMS_SANDPOINT_H */
eof
