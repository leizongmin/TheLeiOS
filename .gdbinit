target remote localhost:1234
symbol-file target/kernel.elf
break main.cc:k_main
continue
