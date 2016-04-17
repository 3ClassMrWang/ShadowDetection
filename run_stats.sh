#!/bin/bash

#echo '第一部分'
#指标测量脚本，多进程，每次运行4-5个进程
#python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/16 16 &
#python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/17 17 &
#python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/18 18 &
#python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/19 19 &
#python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/20 20 &

#循环查询函数 -> 2
#while true
#do
#function check1(){
#    jobs -l
#    count=`jobs -l | wc -l`
#    sleep 300
#    echo '当前进程数=' $count
#    if [ '0' == $count ];then
        echo '第二部分'
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/21 21 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/22 22 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/23 23 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/24 24 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/25 25 &
#        echo 'break'
#       break
#    fi
#}
#check1
#done

#循环查询函数 -> 3
while true
do
function check2(){
    jobs -l
    count=`jobs -l | wc -l`
    sleep 300
    echo '当前进程数=' $count
    if [ '0' == $count ];then
        echo '第三部分'
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/26 26 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/27 27 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/28 28 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/29 29 &
        echo 'break'
        break
    fi
}
check2
done

#循环查询函数 -> 4
while true
do
function check3(){
    jobs -l
    count=`jobs -l | wc -l`
    sleep 300
    echo '当前进程数=' $count
    if [ `0` == $count ];then
        echo '第四部分'
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/30 30 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/31 31 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/32 32 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/33 33 &
        echo 'break'
        break
    fi
}
check3
done

#循环查询函数 -> 5
while true
do
function check4(){
    jobs -l
    count=`jobs -l | wc -l`
    sleep 300
    echo '当前进程数=' $count
    if [ '0' == $count ];then
        echo '第五部分'
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/34 34 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/35 35 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/36 36 &
        python3 processFolder.py /media/wcj/U/dataset2014/dataset /media/wcj/U/dataset2014/results/37 37 &
        echo 'break'
        break
    fi
}
check4
done

#循环查询函数 -> 5
while true
do
function check5(){
    jobs -l
    count=`jobs -l | wc -l`
    sleep 300
    echo '当前进程数=' $count
    if [ '0' == $count ];then
        echo 'break'
        break
    fi
}
check5
done

echo '程序结束'
