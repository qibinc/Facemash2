<!--
Created by Qibin Chen on 20/06/2017.
-->

Documentation - PhotoStream
================

*   [Overview](#overview)
*   [Classes](#classes)
    *   [WechatStream](#wechatstream)
*   [Libraries](#libraries)
    *   [UiUtility](#uiutility)
    *   [LocalFileManager](#localfilemanager)

---

<h2 id="overview">Overview</h2>

*	 Photo stream model.
*	 Photos and gifs can be passed through various methods, such as wechat.
*	 A PhotoStream is derived from QThread. When enabled(QThread::start), it won't affect the main app. Photos are continuously put into the folder which StreamDisplay(the viewcontroller) will check every few milliseconds.

---

<h2 id="classes">Classes</h2>

<h3 id="wechatstream"> wechatstream </h3>

##### protected:

```c++
void WechatStream::run() override
{
	pycode = fopen("main.py", "r");
	Py_Initialize();
	PyRun_SimpleFile(pycode, "main.py");
}
```

#####  python code:

```python
import itchat, os
from itchat.content import *

@itchat.msg_register([PICTURE], isGroupChat=True)
@itchat.msg_register([PICTURE])
def download_files(msg):
    path = 'wechat_photo_stream_temp/' + msg['FromUserName'] + '/'
    if not(os.path.exists(path)):
        os.makedirs(path)
    filename = path + msg['FileName']
    msg['Text'](filename)
    # itchat.send('@%s@%s' % ({'Picture': 'img', 'Video': 'vid'}.get(msg['Type'], 'fil'), filename), toUserName='filehelper')

itchat.auto_login()
itchat.run()
```

---
