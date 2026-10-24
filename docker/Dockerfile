##
## Container to build&test
## obtain key from from github.com => Settings => Credentials => Personal Access Token
##
## ```bash
## docker build -t containername .
## export GHCR_KEY=xxxxx
## echo $GHCR_KEY | docker login ghcr.io -u USERNAME --password-stdin
## docker tag containername  ghcr.io/sername(lowercase)/containername
## docker push ghcr.io/username(lowercase)/avxbuild-arm64
## ```
##
##  Then enable repo or make container public:
##     github.com => Packages
##
FROM ubuntu:latest
RUN apt-get update && apt-get upgrade -y
RUN apt-get update --fix-missing
RUN apt-get install -y build-essential git sudo file cmake \
      libboost-program-options-dev libboost-timer-dev libgtest-dev \
      python3-jinja2
