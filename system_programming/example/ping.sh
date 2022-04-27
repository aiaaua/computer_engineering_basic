#!/bin/bash
ping -c 1 192.168.0.1 1> /dev/null
if [ $? == 0 ]
then
	echo "게이트웨이 핑 성공!"
else
	echo "게이트웨이 핑 실패!"
fi
