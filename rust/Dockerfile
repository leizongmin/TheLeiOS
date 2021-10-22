FROM rust:1.56

RUN apt-get update -y && apt install grub2 xorriso -y
RUN rustup default nightly
RUN rustup target add thumbv7em-none-eabihf
RUN rustup component add llvm-tools-preview
RUN rustup component add rust-src
