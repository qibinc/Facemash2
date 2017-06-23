# Facemash2

*   [Features](#features)
*   [Installation](#installation)
*   [Documentation](#documentation)
*   [Demo](#demo)

<h2 id="features">Features</h2>

* 实现照片展现、存储
* 实现简单的用户系统
* 制定打分评价系统
* 记录用户操作日志
* 微信登录照片表情弹幕

<h2 id="installation">Installation</h2>

*   CMake, Qt, Python/itchat REQUIRED

*   How to compile

      ```
      cd path/to/Facemash2
      mkdir build
      cd build
      cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt/5.x -DPYTHON_INCLUDE_DIR=/path/to/python/2.7/include/ -DPYTHON_LIBRARIES=/path/to/python/2.7/lib/libpython2.7.dylib
      make
      ```

*   You will find the executables under the folder bin

<h2 id="documentation">Documentation</h2>

### Apps

* <a href="server/documents/serverDoc.md" title="Server Documentation">Server</a>

* <a href="client/docs/client.md" title="Client Documentation">Client</a>

### Libraries

* <a href="client/libs/photostream/docs/photostream.md" title="PhotoStream Documentation">PhotoStream</a>

* <a href="client/libs/clientnetwork/docs/clientnetwork.md" title="ClientNetwork Documentation">ClientNetwork</a>

* <a href="client/libs/uiutility/docs/uiutility.md" title="UiUtility Documentation">UiUtility</a>

* <a href="client/libs/localfilemanager/docs/localfilemanager.md" title="LocalFileManager Documentation">LocalFileManager</a>

<h2 id="demo">Demo</h2>

![Demo](demo.gif)
