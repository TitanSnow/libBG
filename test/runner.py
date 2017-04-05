import os
if os.name=="nt":
    from nt_runner import *
else:
    from unix_runner import *
