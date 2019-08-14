FROM frolvlad/alpine-gxx AS build

RUN apk add --no-cache make

RUN mkdir -p /source-code/src
WORKDIR /source-code

COPY ./src ./src 
COPY ./makefile .

RUN make 

FROM alpine:latest AS execute

RUN mkdir /machine-loader

WORKDIR /machine-loader

COPY --from=build /source-code/release/load .
COPY ./docker_entrypoint.sh .

ENTRYPOINT /bin/sh ./docker_entrypoint.sh
