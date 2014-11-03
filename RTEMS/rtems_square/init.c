/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */
/*  updated for triple test, 2003/11/06, Erik Adli */

#define CONFIGURE_INIT
#include "system.h"
#include <inttypes.h>
#include <stdio.h>

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */
rtems_id   Task_id[ 2 ];         /* array of task ids */
rtems_name Task_name[ 2 ];       /* array of task names */

rtems_task Init (rtems_task_argument argument)
{
  rtems_status_code status;
  uint32_t ticks_per_second;

  puts( "\n\n\n*** RTEMS SQUARE ***" );

  ticks_per_second = rtems_clock_get_ticks_per_second();
  printf("\nTicks per second in your system: %" PRIu32 "\n", ticks_per_second);

  Task_name[ 1 ] = rtems_build_name( 'T', 'A', '1', ' ' );

  // prototype: rtems_task_create( name, initial_priority, stack_size, initial_modes, attribute_set, *id );
  status = rtems_task_create(
			     Task_name[ 1 ], 1, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
			     RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ 1 ]
			     );

  // prototype: rtems_task_start( id, entry_point, argument );
  status = rtems_task_start( Task_id[ 1 ], Task_Rate_Monotonic_Period, 1 );

  // delete init task after starting the working task
  status = rtems_task_delete( RTEMS_SELF );
}
