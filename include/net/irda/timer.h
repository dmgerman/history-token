multiline_comment|/*********************************************************************&n; *                &n; * Filename:      timer.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Aug 16 00:59:29 1997&n; * Modified at:   Thu Oct  7 12:25:24 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef TIMER_H
DECL|macro|TIMER_H
mdefine_line|#define TIMER_H
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;asm/param.h&gt;  /* for HZ */
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
multiline_comment|/* &n; *  Timeout definitions, some defined in IrLAP p. 92&n; */
DECL|macro|POLL_TIMEOUT
mdefine_line|#define POLL_TIMEOUT        (450*HZ/1000)    /* Must never exceed 500 ms */
DECL|macro|FINAL_TIMEOUT
mdefine_line|#define FINAL_TIMEOUT       (500*HZ/1000)    /* Must never exceed 500 ms */
multiline_comment|/* &n; *  Normally twice of p-timer. Note 3, IrLAP p. 60 suggests at least twice &n; *  duration of the P-timer.&n; */
DECL|macro|WD_TIMEOUT
mdefine_line|#define WD_TIMEOUT          (POLL_TIMEOUT*2)
DECL|macro|MEDIABUSY_TIMEOUT
mdefine_line|#define MEDIABUSY_TIMEOUT   (500*HZ/1000)    /* 500 msec */
multiline_comment|/*&n; *  Slot timer must never exceed 85 ms, and must always be at least 25 ms, &n; *  suggested to  75-85 msec by IrDA lite. This doesn&squot;t work with a lot of&n; *  devices, and other stackes uses a lot more, so it&squot;s best we do it as well&n; */
DECL|macro|SLOT_TIMEOUT
mdefine_line|#define SLOT_TIMEOUT            (90*HZ/1000)
multiline_comment|/* &n; *  We set the query timeout to 100 ms and then expect the value to be &n; *  multiplied with the number of slots to product the actual timeout value&n; */
DECL|macro|QUERY_TIMEOUT
mdefine_line|#define QUERY_TIMEOUT           (HZ/10)       
DECL|macro|WATCHDOG_TIMEOUT
mdefine_line|#define WATCHDOG_TIMEOUT        (20*HZ)       /* 20 sec */
DECL|typedef|TIMER_CALLBACK
r_typedef
r_void
(paren
op_star
id|TIMER_CALLBACK
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|irda_start_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|ptimer
comma
r_int
id|timeout
comma
r_void
op_star
id|data
comma
id|TIMER_CALLBACK
id|callback
)paren
suffix:semicolon
r_inline
r_void
id|irlap_start_slot_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlap_start_query_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlap_start_final_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlap_start_wd_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlap_start_backoff_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|timeout
)paren
suffix:semicolon
r_void
id|irlap_start_mbusy_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
)paren
suffix:semicolon
r_void
id|irlap_stop_mbusy_timer
c_func
(paren
r_struct
id|irlap_cb
op_star
)paren
suffix:semicolon
r_struct
id|lsap_cb
suffix:semicolon
r_struct
id|lap_cb
suffix:semicolon
r_inline
r_void
id|irlmp_start_watchdog_timer
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlmp_start_discovery_timer
c_func
(paren
r_struct
id|irlmp_cb
op_star
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlmp_start_idle_timer
c_func
(paren
r_struct
id|lap_cb
op_star
comma
r_int
id|timeout
)paren
suffix:semicolon
r_inline
r_void
id|irlmp_stop_idle_timer
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
)paren
suffix:semicolon
macro_line|#endif
eof
