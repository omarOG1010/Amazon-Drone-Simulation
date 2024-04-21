# for M1/M2 mac users, use this FROM instruction instead
# FROM --platform=linux/amd64 ubuntu:20.04

FROM ubuntu:20.04

ENV TZ=America/Chicago
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  pkg-config \
  build-essential \
  libssl-dev \
  zlib1g-dev
  
RUN mkdir /app

COPY . /app

WORKDIR /app

RUN make -j

CMD ["./build/bin/transit_service","8081","apps/transit_service/web/"]