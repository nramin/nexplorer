FROM debian:buster-slim

RUN apt-get update && apt-get install -y \
		make \
		vim-nox \
		gcc \
		libncurses5-dev \
		libncursesw5-dev

WORKDIR /build

COPY . .
