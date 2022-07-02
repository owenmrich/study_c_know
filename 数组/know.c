连续存放的,查找最快 数组名+下标
一维数组求个数
int size = sizeof(arr) / sizeof(*arr);

int num = sizeof(arr) / sizeof(arr [0][0]);//求数组元素总个数

int col = sizeof(arr [0]) / sizeof(arr [0][0]);//求二维数组的列数

int line = num / col;//求二维数组的行数
