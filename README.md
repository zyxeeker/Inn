## 介绍

<div align="center">
<h1>Inn</h1>
<p>纯用C++开发的多人聊天服务器</p>

![GitHub top language](https://img.shields.io/github/languages/top/zyxeeker/Inn?logo=c&style=for-the-badge)
![](https://img.shields.io/badge/Ubuntu-18.04-orange?logo=ubuntu&style=for-the-badge)
![](https://img.shields.io/badge/MySQL-5.7.33-orange?logo=mysql&style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/zyxeeker/Inn?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/zyxeeker/Inn?style=for-the-badge)

</div>



目前已实现用户对用户的通信![](/img/image-20210414192839334.png)

## 进度

- [x] 连接数据库
- [x] 实现 epoll ET 模式
- [x] 未加密的简单聊天
- [x] 登陆与注册
- [x] 线程池

### ToDo:

- [ ] 加入 epoll LT 模式
- [ ] 解析配置文件（加入 yaml）
- [ ] 完善日志模块
- [ ] 加密通信
- [ ] 加入通信验证
- [ ] 实现多人聊天

## 调用

默认端口为 9006

### 登录方式

```
LOGIN username passwd
```

### 注册方式

```
REG username passwd
```

###  聊天方式

```
CHAT destination_username chat_content
```

