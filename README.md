#BlockSci

## Installation on Ubuntu 2023
```
  sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
  sudo apt-get update
  sudo apt install cmake libtool autoconf libboost-filesystem-dev libboost-iostreams-dev \
  libboost-serialization-dev libboost-thread-dev libboost-test-dev  libssl-dev libjsoncpp-dev \
  libcurl4-openssl-dev libjsoncpp-dev libjsonrpccpp-dev libsnappy-dev zlib1g-dev libbz2-dev \
  liblz4-dev libzstd-dev libjemalloc-dev libsparsehash-dev python3-dev python3-pip
  
  git clone https://github.com/citp/BlockSci.git
  cd BlockSci
  mkdir release
  cd release
  CC=gcc-1 CXX=g++-11 cmake -DCMAKE_BUILD_TYPE=Release ..
  make
  sudo make install
  
  cd ..
  CC=gcc-1 CXX=g++-11 sudo -H pip3 install -e blockscipy
```
