*******************************************************************************

Fornux C++ Superset 4.1

Client side Fornux C++ Superset source-to-source compiler streaming functionality

Copyright (c) 2019
Fornux Inc.

*******************************************************************************


To try it out it's only a matter of:

- Creating an account at: https://fcxxss.fornux.com/db/signup.php

- Confirming the email

- Logging in to: https://fcxxss.fornux.com/db/login.php

- Running "ssh-keygen" on your host

- Copying the contents of "~/.ssh/id_rsa.pub" into "Settings -> SSH Public Key" and clicking "Save"

- Installing the development headers "libboost1.62-dev" (Ubuntu Linux)


Example #1:

- Changing the directory on the host to: "fcxxss/devel"

- Running: "export FCXXSS_CC=\<compiler\>"

- Running: "export FCXXSS_USERNAME=\<email\>"

- Running: "../bin/fcxxss.sh memoryleak.cpp -O2"

- Executing: "./a.out"


Example #2:

- Add "fcxxss.sh" directory to $PATH

- Cmake one-liner: "FCXXSS_LD=\<compiler\> FCXXSS_CC=\<compiler\> FCXXSS_USERNAME=\<email\> cmake -DCMAKE_C_COMPILER=fcxxss.sh -DCMAKE_CXX_COMPILER=fcxxss.sh .."


Voila! 

Also it was tested with GNU GCC 5 & 6, Clang 5 & 6.


Sincerely,  
Phil Bouchard  
C.T.O. of Fornux Inc.  
phil@fornux.com  
