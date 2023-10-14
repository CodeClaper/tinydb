#!/bin/bash
PROCESS=tinydb
LOG="./memlog.txt"
#删除上次的监控文件
if [ -f "$LOG" ];then
rm "$LOG"
fi
#过滤出需要的进程ID
PID=$(ps | grep $PROCESS | grep -v 'grep' | awk '{print $1;}')
while [ "$PID" != "" ]
do
cat /proc/$PID/status | grep RSS >> "$LOG"#过滤出VmRSS行
sleep 5
PID=$(ps | grep $PROCESS | grep -v 'grep' | awk '{print $1;}')
done
