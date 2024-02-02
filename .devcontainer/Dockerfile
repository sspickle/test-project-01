#
# You don't need to use this if you're using cloud9. But if you want to work offline
# this might be useful to get a working environment for free.
#

FROM gcc:9.5

RUN apt-get update

RUN apt-get install -y valgrind

RUN apt-get install -y python3 python3-dev python3-pip python3-setuptools python3-pytest

RUN pip3 install cython

RUN apt-get install -y emacs-nox

RUN apt-get install -y clang-format

RUN pip3 install flask

RUN apt-get install -y cmake zip

RUN mkdir /gtest

RUN cd /gtest/ && wget https://github.com/google/googletest/archive/main.zip && unzip main.zip && cmake -DCMAKE_CXX_STANDARD=14 ./googletest-main/ && make && make install

COPY . /work

WORKDIR /work

CMD ["/bin/bash"]

