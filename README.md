*******************************************************************************

Fornux C++ Superset 5.0

Client side Fornux C++ Superset source-to-source compiler streaming functionality

Copyright (c) 2019
Fornux Inc.

*******************************************************************************


1) Shareware (Windows)


Example #1 (Cygwin):

- Changing the directory: "cd fcxxss/"

- Setting the root dir: "export FCXXSS_DIR=$(pwd)"

- Setting the path: "export PATH=$(pwd)/bin:$PATH"

- Changing the directory: "cd devel/"

- Setting the compiler: "export FCXXSS_CC=cl.sh"

- Running: "fcxxss-cl.sh memoryleak.cpp -O2"

- Executing: "./a.exe"


Example #2 (CMD):

- Changing the directory: "cd fcxxss\"

- Setting the root dir: "set FCXXSS_DIR=%CD%"

- Setting the path: "set PATH=%CD%\bin;%PATH%"

- Changing the directory: "cd devel\"

- Setting the compiler: "set FCXXSS_CC=cl.sh"

- Running: "bash -c 'fcxxss-cl.sh memoryleak.cpp -O2'"

- Executing: ".\a.exe"


2) Software as a Service (Linux & Windows):

- Creating an account at: https://fcxxss.fornux.com/db/signup.php

- Confirming the email

- Logging in to: https://fcxxss.fornux.com/db/login.php

- Running "ssh-keygen" on your host

- Copying the contents of "~/.ssh/id_rsa.pub" into "Settings -> SSH Public Key" and clicking "Save"

- Installing the development headers "libboost1.62-dev" (Ubuntu Linux)


Example #1:

- Changing the directory: "cd fcxxss/"

- Setting the root dir: "export FCXXSS_DIR=$(pwd)"

- Setting the path: "export PATH=$(pwd)/bin:$PATH"

- Changing the directory: "cd devel/"

- Running: "export FCXXSS_CC=\<compiler\>"

- Running: "export FCXXSS_USERNAME=\<email\>"

- Running: "fcxxss.sh memoryleak.cpp -O2"

- Executing: "./a.out"


Example #2:

- Changing the directory: "cd fcxxss/"

- Setting the root dir: "export FCXXSS_DIR=$(pwd)"

- Setting the path: "export PATH=$(pwd)/bin:$PATH"

- Changing the working directory

- Cmake one-liner: "FCXXSS_LD=\<compiler\> FCXXSS_CC=\<compiler\> FCXXSS_USERNAME=\<email\> cmake -DCMAKE_C_COMPILER=fcxxss.sh -DCMAKE_CXX_COMPILER=fcxxss.sh .."


Voila! 

Also it was tested with GNU GCC 5 & 6, Clang 5 & 6.


Sincerely,  
Phil Bouchard  
CEO of Fornux Inc.  
phil@fornux.com  
