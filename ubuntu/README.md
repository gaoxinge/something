## ssh 

- [Linux开启ssh服务](https://www.cnblogs.com/fengbeihong/p/3307575.html)
- [rastasheep/ubuntu-sshd](https://hub.docker.com/r/rastasheep/ubuntu-sshd/~/dockerfile/)
- [password define for ssh connection into docker container](https://stackoverflow.com/questions/40330205/password-define-for-ssh-connection-into-docker-container)
- [Ubuntu 安装 SSH，并开启 root 远程登录](http://zhang-jc.github.io/2016/05/25/Ubuntu-%E5%AE%89%E8%A3%85-SSH%EF%BC%8C%E5%B9%B6%E5%BC%80%E5%90%AF-root-%E8%BF%9C%E7%A8%8B%E7%99%BB%E5%BD%95/)
- [linux 远程连接ssh提示IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY解决](https://blog.csdn.net/watsy/article/details/12611919)

## docker

- [Is there any way to use hostname command in the container?](https://github.com/moby/moby/issues/8902)
- [Is it ok to run docker from inside docker?](https://stackoverflow.com/questions/27879713/is-it-ok-to-run-docker-from-inside-docker)
- [Bind to docker socket on Windows](https://stackoverflow.com/questions/36765138/bind-to-docker-socket-on-windows)
- [Docker Inside a Docker on Windows](https://stackoverflow.com/questions/47225616/docker-inside-a-docker-on-windows)
- [How do I install Docker on Ubuntu 16.04 LTS?](https://askubuntu.com/questions/938700/how-do-i-install-docker-on-ubuntu-16-04-lts)
- [systemd and systemctl within Ubuntu Docker images](https://stackoverflow.com/questions/39169403/systemd-and-systemctl-within-ubuntu-docker-images)
- [systemctl failed to connect to bus - docker ubuntu:16.04 container](https://askubuntu.com/questions/813588/systemctl-failed-to-connect-to-bus-docker-ubuntu16-04-container)
- [Systemctl status is not working in my Docker container](https://forums.docker.com/t/systemctl-status-is-not-working-in-my-docker-container/9075)

## python

- [Installing Python 3 on Linux](https://docs.python-guide.org/starting/install3/linux/)
- [Proper way to install pip on Ubuntu](https://stackoverflow.com/questions/37954008/proper-way-to-install-pip-on-ubuntu)
- [How to get setuptools and easy_install?](https://stackoverflow.com/questions/8650459/how-to-get-setuptools-and-easy-install)
- [pip refuses to upgrade](https://stackoverflow.com/questions/41674368/pip-refuses-to-upgrade)
- [How to install pip with Python 3?](https://stackoverflow.com/questions/6587507/how-to-install-pip-with-python-3)

## usage

### with docker

```
$ docker build -t qwer .
$ docker run -d -p 22:22 -v //var/run/docker.sock:/var/run/docker.sock --cap-add SYS_ADMIN qwer
```

### without docker

```
$ docker build -t qwer .
$ docker run -d -p 22:22 qwer
```

```
$ ssh root@127.0.0.1         # password root
$ copy-ssh-id root@127.0.0.1 # password root
```