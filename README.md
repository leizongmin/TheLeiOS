# The LeiOS

学习 C 语言和操作系统，顺便做点有趣的事情。

## 开发环境配置

如果以 macOS 作为开发环境， 构建工具使用 Docker 执行，需要当前系统安装以下工具：

- Docker，用于执行编译构建工具；
- Qemu，用于运行构建好的系统镜像；
- 执行 `make init` 初始化构建环境；
- 执行 `brew install x86_64-elf-gcc` 安装 GCC 编译器；
- 执行 `brew install xorriso` 安装 `xorriso`（`grub-mkrescue` 依赖）；
- 执行 `./install-grub.sh` 构建 `grub-mkrescue`；

如果以 Linux 作为开发环境，以 Debian/Ubuntu 系统为例，需要执行命令安装必要的工具：

```bash
apt install -y gcc nasm grub2 xorriso
apt install -y qemu-system-x86
```

## 开发过程

- 执行命令 `make kernel` 构建；
- 执行命令 `make run-kernel` 在 QEMU 模拟器中启动；
- 执行命令 `make run-kernel DEBUG=1` 在 QEMU 模拟器中启动并开启 GDB 调试；
- 执行命令 `make gdb` 连接 GDB 调试；

## 截图

<img src="screenshot.png" width="640px">

## 学习资源

- [intermezzOS - An operating system for learning](https://intermezzos.github.io/book/first-edition/preface.html)
- [Booting into C](https://www.ics.uci.edu/~aburtsev/238P/hw/hw4-boot-into-c/hw4-boot-into-c.html)
