FROM debian:experimental as build

ADD . /shorturl
WORKDIR /shorturl
RUN apt-get -qq update && apt-get install -t experimental -q -y gcc g++ cmake libboost-all-dev
RUN ./build.sh
