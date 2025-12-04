IMAGE_NAME := dyshell
WORKSPACE := /workspace/embedded-client
THIRDPARTY := /workspace/thirdparty
DOCKER_ARGS := --rm --net=host -v $(shell pwd)/..:/workspace -e WORKSPACE=$(WORKSPACE) -e THIRDPARTY=$(THIRDPARTY)

.PHONY: all create-bindings build-server


build-docker:
	docker build -t $(IMAGE_NAME) .

all: build-docker
	docker run $(DOCKER_ARGS) -t --entrypoint=/bin/bash $(IMAGE_NAME) -c "cd $(WORKSPACE) && ./build.sh"

clean: build-docker
	docker run $(DOCKER_ARGS) -t --entrypoint=/bin/bash $(IMAGE_NAME) -c "rm -rf $(THIRDPARTY)/libcspbuild $(WORKSPACE)/build"

console: build-docker
	docker run $(DOCKER_ARGS) -it --entrypoint=/bin/bash $(IMAGE_NAME)
