target remote localhost:1234
symbol-file target/kernel.elf
break main.c:k_main
continue
