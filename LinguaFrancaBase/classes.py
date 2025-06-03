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
