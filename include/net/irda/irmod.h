multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irmod.h&n; * Version:       0.3&n; * Description:   IrDA module and utilities functions&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Dec 15 13:58:52 1997&n; * Modified at:   Fri Jan 28 13:15:24 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *&n; *     Copyright (c) 1998-2000 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2001 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charg.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRMOD_H
DECL|macro|IRMOD_H
mdefine_line|#define IRMOD_H
macro_line|#include &lt;net/irda/irda.h&gt;&t;&t;/* Notify stuff */
multiline_comment|/* Nothing much here anymore - Maybe this header should be merged in&n; * another header like net/irda/irda.h... - Jean II */
multiline_comment|/* Locking wrapper - Note the inverted logic on irda_lock().&n; * Those function basically return false if the lock is already in the&n; * position you want to set it. - Jean II */
DECL|macro|irda_lock
mdefine_line|#define irda_lock(lock)&t;&t;(! test_and_set_bit(0, (void *) (lock)))
DECL|macro|irda_unlock
mdefine_line|#define irda_unlock(lock)&t;(test_and_clear_bit(0, (void *) (lock)))
multiline_comment|/* Zero the notify structure */
r_void
id|irda_notify_init
c_func
(paren
id|notify_t
op_star
id|notify
)paren
suffix:semicolon
macro_line|#endif /* IRMOD_H */
eof
