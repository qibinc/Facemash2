# coding=utf-8
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

itchat.auto_login(True)
itchat.run()
