# A class used to generate variables with dots in their name
# Taken from tinyurl.com/y4chuth3
class Make:
    def __getattr__(self, name):
        self.__dict__[name] = Make()
        return self.__dict__[name]
    
class ReactorBase:
    lf_module_cache = None
    def lf_module(self):
        if self.lf_module_cache is None:
            import sys
            module_name = sys.modules[self.__class__.__module__].__name__
            main_module = __import__(module_name)
            self.lf_module_cache = main_module.lf
        return self.lf_module_cache
    def check_deadline(self, invoke_deadline_handler=True):
        """Check if the deadline of the currently executing reaction has passed.
        
        Args:
            invoke_deadline_handler (bool): If True, invoke the deadline handler if the deadline has passed.
            
        Returns:
            bool: True if the deadline has passed, False otherwise.
        """        
        # Call the C function through the binding.
        # This idiom is used to invoke C functions bound to the main module and defined
        # pythontarget.c.
        return self.lf_module().check_deadline(self, invoke_deadline_handler)

    def update_deadline(self, updated_deadline=0):
        """
        Update the deadline of the currently executing reaction.
        
        Args:
            updated_deadline (interval_t): The updated deadline.
        """        
        # Call the C function through the binding.
        # This idiom is used to invoke C functions bound to the main module and defined
        # pythontarget.c.
        return self.lf_module().update_deadline(self, updated_deadline)

    def register_user_trace_event(self, description: str):
        """Register a user trace event for tracing. Enable tracing in the target (e.g. tracing: True).
        
        Args:
            description: Human-readable description of the event.
            
        Returns:
            int: An opaque handle to pass to tracepoint_user_event and tracepoint_user_value.
                 Returns 0 if tracing is disabled or registration failed.
        """
        return self.lf_module().register_user_trace_event(self, description)

    def tracepoint_user_event(self, handle):
        """Record a user-defined trace event at the current logical time.
        
        Args:
            handle: The handle returned by register_user_trace_event(description).
        """
        self.lf_module().tracepoint_user_event(self, handle)

    def tracepoint_user_value(self, handle, value):
        """Record a user-defined trace event with a value at the current logical time.
        
        Args:
            handle: The handle returned by register_user_trace_event(description).
            value: Integer value to record (e.g. a count or timestamp).
        """
        self.lf_module().tracepoint_user_value(self, handle, value)

    def lf_async(self, action, function, *args):
        """Invoke a Python callable without blocking the rest of the program.

        ``function(*args)`` runs while this reaction is suspended, and this method
        returns whatever ``function`` returns. Outputs set before the call are
        produced at the current tag. The rest of the reaction runs at the tag where
        ``lf_async_resume(action)`` is called.

        The calling reaction must list ``action`` as an effect, and a reaction
        declared earlier in this reactor must be triggered by ``action`` and call
        ``lf_async_resume``. A physical action is scheduled when ``function``
        returns. A logical action is scheduled before ``function`` runs, after the
        action's minimum delay.

        Other reactions of this reactor can run, and can modify state, while this
        call is suspended. The reactor's reactions are mutually exclusive. If the
        program is already stopping, ``function`` runs directly and this returns
        at the current tag.
        """
        return self.lf_module().lf_async(self, action, function, args)

    def lf_async_resume(self, action):
        """Resume every due ``lf_async`` call waiting on ``action``.

        Call this from the reaction triggered by ``action``. If that call's
        function has not returned, this waits for it, so the suspended reaction
        continues at this tag. If nothing is waiting, this does nothing.
        """
        return self.lf_module().lf_async_resume(action)

    def lf_await(self, port):
        """Suspend this reaction until ``lf_await_resume(port)`` is called.

        Outputs set before the call are produced at the current tag. The rest of
        the reaction runs at the tag of the resuming call, and ``port.value`` and
        ``port.is_present`` then reflect the port at that tag. If the program
        stops first, this returns at the stop tag.
        """
        return self.lf_module().lf_await(self, port)

    def lf_await_resume(self, port):
        """Resume every ``lf_await`` on ``port`` in this reactor, oldest first.

        If nothing is waiting on ``port``, this does nothing.
        """
        return self.lf_module().lf_await_resume(self, port)

    def lf_add_worker_thread(self):
        """Add a worker thread to the pool. Returns 0 on success, or -1."""
        return self.lf_module().lf_add_worker_thread(self)

    def lf_added_worker_thread_count(self):
        """Return the number of worker threads added at runtime."""
        return self.lf_module().lf_added_worker_thread_count(self)

    def lf_thread_id(self):
        """Return the id of the worker thread executing the caller."""
        return self.lf_module().lf_thread_id()
