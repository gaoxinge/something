FROM ubuntu:16.04

##########
# config #
##########
COPY sources.list /etc/apt/sources.list
RUN apt-get update

########
# tool #
########
RUN apt-get install -y net-tools
RUN apt-get install -y git
RUN apt-get install -y vim

# ssh
RUN apt-get install -y openssh-server
RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -ri 's/UsePAM yes/#UsePAM yes/g' /etc/ssh/sshd_config

# with docker
# RUN apt-get update
# RUN apt-get install -y sudo
# RUN apt-get install -y docker.io

############
# language #
############
RUN apt-get install -y build-essential

RUN wget -qO- https://dl.google.com/go/go1.13.6.linux-amd64.tar.gz | tar xz -C /usr/local
ENV PATH $PATH:/usr/local/go/bin

# python
# RUN apt-get install -y software-properties-common
# RUN add-apt-repository ppa:deadsnakes/ppa
# RUN apt-get update
# RUN apt-get install -y python3.7
# RUN apt-get update
# RUN apt-get install -y python-dev
# RUN apt-get install -y python-setuptools
# RUN easy_install -U pip
RUN apt-get update
RUN apt-get install -y python3-dev
RUN apt-get install -y python3-setuptools
RUN easy_install3 -U pip

#######
# cmd #
#######
CMD ["/usr/sbin/sshd", "-D"]