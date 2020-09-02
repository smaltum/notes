## 并发

### 信号的概念

- 信号是软件层次的中断
- 信号的响应依赖于中断

### signal()

- void (_signal(int signum,void ((func _) int)))(int)
- 信号会打断系统的调用

### 信号的不可靠性

### 可重入函数

### 信号的响应过程

### 常用函数

- kill
- raise
- alarm
- pause
- abort
- system
- sleep

### 信号集

### 信号屏蔽字/pending 集的处理

### 扩展

- sigsuspend
- sigaction
- setitimer

### 实时信号

### makefile 参考

[参考链接 1](https://www.cnblogs.com/tp-16b/p/8955462.html)  
[参考链接 2](https://www.cnblogs.com/wang_yb/p/3990952.html)
