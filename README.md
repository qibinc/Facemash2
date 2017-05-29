# Facemash2

*   [Features](#features)
*   [Installation](#installation)
*   [Documentation](#documentation)

<h2 id="features">Features</h2>

* 实现照片展现、存储
* 实现简单的用户系统
* 制定打分评价系统
* 展现照片排名
* 记录用户操作日志

<h2 id="installation">Installation</h2>

*   CMake, Qt REQUIRED

* How to compile a cmake project

    ```
    cd path/to/facemash2
    mkdir build
    cd build
    cmake .. -DCMAKE_PREFIX_PATH=path/to/qt/5.x
    make
    ```

* You will find the executables under the folder bin

<<<<<<< HEAD
cqb@Cqbs-MacBook-Air:~/developer/Facemash2/build$ make
Scanning dependencies of target Client_automoc
[  7%] Automatic moc and uic for target Client
Generating moc source Client_automoc.dir/moc_widget_J5JSJ2JUM22MGN.cpp
Generating moc compilation Client_automoc.cpp
Generating ui header ui_widget.h
[  7%] Built target Client_automoc
Scanning dependencies of target Client
[ 15%] Building CXX object client/CMakeFiles/Client.dir/source/main.cpp.o
[ 23%] Building CXX object client/CMakeFiles/Client.dir/source/widget.cpp.o
[ 30%] Building CXX object client/CMakeFiles/Client.dir/Client_automoc.cpp.o
[ 38%] Linking CXX executable ../../bin/Client
[ 38%] Built target Client
Scanning dependencies of target Server_automoc
[ 46%] Automatic moc and uic for target server
Generating moc compilation Server_automoc.cpp
[ 46%] Built target Server_automoc
Scanning dependencies of target utilitieslib_automoc
[ 53%] Automatic moc and uic for target utilitieslib
Generating moc compilation utilitieslib_automoc.cpp
[ 53%] Built target utilitieslib_automoc
Scanning dependencies of target utilitieslib
[ 61%] Building CXX object server/utilities/CMakeFiles/utilitieslib.dir/source/TestUtility.cpp.o
[ 69%] Building CXX object server/utilities/CMakeFiles/utilitieslib.dir/utilitieslib_automoc.cpp.o
[ 76%] Linking CXX static library libutilitieslib.a
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib: file: libutilitieslib.a(utilitieslib_automoc.cpp.o) has no symbols
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib: file: libutilitieslib.a(utilitieslib_automoc.cpp.o) has no symbols
[ 76%] Built target utilitieslib
Scanning dependencies of target server
[ 84%] Building CXX object server/CMakeFiles/server.dir/source/main.cpp.o
[ 92%] Building CXX object server/CMakeFiles/server.dir/Server_automoc.cpp.o
[100%] Linking CXX executable ../../bin/server
[100%] Built target server
```
=======
<h2 id="documentation">Documentation</h2>
>>>>>>> origin/client

*   <a href="/client/docs/Documentation-Client.md" title="Client Documentation">Client</a>
