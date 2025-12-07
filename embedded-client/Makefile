IMAGE_NAME := dyshell
WORKSPACE_PATH := /workspace
EMBEDDED_PROJECT_PATH := $(WORKSPACE_PATH)/embedded-client
THIRDPARTY_PATH := $(WORKSPACE_PATH)/thirdparty
DOCKER_ARGS := --rm --net=host -v $(shell pwd)/..:$(WORKSPACE_PATH) -e WORKSPACE_PATH=$(WORKSPACE_PATH)

.PHONY: all build-client

all: build-client

build-docker:
	docker build -t $(IMAGE_NAME) .

build-client:
	docker run $(DOCKER_ARGS) -t --entrypoint=/bin/bash $(IMAGE_NAME) -c "cd $(EMBEDDED_PROJECT_PATH) && ./build.sh $(EMBEDDED_PROJECT_PATH) $(THIRDPARTY_PATH)"

console:
	docker run $(DOCKER_ARGS) -it --entrypoint=/bin/bash $(IMAGE_NAME)
