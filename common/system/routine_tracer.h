#ifndef __ROUTINE_TRACER_H
#define __ROUTINE_TRACER_H

#include "fixed_types.h"
#include "subsecond_time.h"

#include <deque>

class Thread;

class RoutineTracerThread
{
   public:
      RoutineTracerThread(Thread *thread);
      virtual ~RoutineTracerThread();

      void routineEnter(IntPtr eip);
      void routineExit(IntPtr eip);

   protected:
      Thread *m_thread;
      std::deque<IntPtr> m_stack;

   private:
      virtual void functionEnter(IntPtr eip) {}
      virtual void functionExit(IntPtr eip) {}
      virtual void functionChildEnter(IntPtr eip, IntPtr eip_child) {}
      virtual void functionChildExit(IntPtr eip, IntPtr eip_child) {}
};

class RoutineTracer
{
   public:
      class Routine
      {
         public:
            const IntPtr m_eip;
            const char *m_name;
            const char *m_location;

            Routine(IntPtr eip, const char *name, int column, int line, const char *filename);
      };

      static RoutineTracer* create();

      RoutineTracer();
      virtual ~RoutineTracer();

      virtual void addRoutine(IntPtr eip, const char *name, int column, int line, const char *filename) = 0;
      virtual RoutineTracerThread* getThreadHandler(Thread *thread) = 0;
};

#endif // __ROUTINE_TRACER_H