FROM gcc:13.2-bookworm

RUN addgroup --gid 501 app && \
    adduser --uid 501 --gid 20 --gecos "" --disabled-password app

RUN apt update && apt install -y cmake ninja-build zip

USER app

ENV VCPKG_FORCE_SYSTEM_BINARIES=1
RUN cd && \
    git clone https://github.com/Microsoft/vcpkg.git && \
    ./vcpkg/bootstrap-vcpkg.sh
