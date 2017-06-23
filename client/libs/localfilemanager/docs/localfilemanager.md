<!--
Created by Qibin Chen on 20/06/2017.
-->

Documentation - LocalFileManager
================

*   [Overview](#overview)
*   [Functions](#functions)

<h2 id="overview">Overview</h2>

*   Local file handling apis.
*   This library includes getting photo files and opening an image(in various format) safely.

<h2 id="functions">Functions</h2>

```c++
QList<QString> GetDirs(QString dir);
//  Return a list of directories

QList<QString> GetFiles(QString dir);
//  Return a list of files under a directory with suffix 'jpg', 'png' and 'gif'

QPixmap *OpenImage(QString filename);
//  Try to open an image by all means.

QMovie *OpenMovie(QString filename);
//  Open a gif or mp4 file.
```

---

