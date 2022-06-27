ffmpeg -re -i /run/media/mmcblk0p1/testVideo.mp4 -vcodec copy -f flv rtmp://127.0.0.1/live/mytest

ffmpeg常用命令
-f 强迫采用格式fmt
-i filename 输入文件
-s size 设置帧大小 默认是160x128
-r 设置帧频，默认25  （待验证，确认非标准桢率会导致音画不同步，所以只能设定为15或者29.97）
-qscale:v n(q:v n) n表示视频质量级别1-31（待验证值越小，质量越好）
-ab bitrate设置音频码率
-ar freq 设置音频采样率
-ac channels设置通道，默认为1
-vd device 设置视频捕获设备 eg:/dev/video0
-av device 设置音频设备 eg:/dev/dsp
-vcodec

ffmpeg -f video4linux2  -r 12 -s 640x480 -i /dev/video0 -vcodec libx264 -f flv rtmp://127.0.0.1:1935/live/live