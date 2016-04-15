# Project ShadowDetection

> PROJECT DESCRIPTION

项目针对固定摄像头的运动物体检测场景，首先进行进行背景减除，再利用阴影检测算法检测并去除阴影

> PROJECT CONTENTS

### bgs

背景减除，获取前景和背景模型。

示例：./run_bgs.sh 或 ./run_bgs_camera.sh

### sdd

根据bgs产生的前景掩膜及背景模型，对其进行分析，检测和去除阴影，目前有5种算法。

示例：./run_sdd.sh

### demo

整合bgs和sdd编写的示例程序

### stats

bgs和sdd算法性能采用ChangeDetection.net数据集进行测量，stats根据其示例指标测量程序编写

示例：python3 processFolder.py datasetPath resultsRootPath

> CAUTION

bgs采用的是BGSLibrary，共有37种算法
	