multiline_comment|/* $Id: msi.h,v 1.3 1996/08/29 09:48:25 davem Exp $&n; * msi.h:  Defines specific to the MBus - Sbus - Interface.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Eddie C. Dost   (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC_MSI_H
DECL|macro|_SPARC_MSI_H
mdefine_line|#define _SPARC_MSI_H
multiline_comment|/*&n; * Locations of MSI Registers.&n; */
DECL|macro|MSI_MBUS_ARBEN
mdefine_line|#define MSI_MBUS_ARBEN&t;0xe0001008&t;/* MBus Arbiter Enable register */
multiline_comment|/*&n; * Useful bits in the MSI Registers.&n; */
DECL|macro|MSI_ASYNC_MODE
mdefine_line|#define MSI_ASYNC_MODE  0x80000000&t;/* Operate the MSI asynchronously */
DECL|function|msi_set_sync
r_extern
id|__inline__
r_void
id|msi_set_sync
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;lda [%0] %1, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;andn %%g3, %2, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;sta %%g3, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|MSI_MBUS_ARBEN
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
comma
l_string|&quot;r&quot;
(paren
id|MSI_ASYNC_MODE
)paren
suffix:colon
l_string|&quot;g3&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_MSI_H) */
eof
