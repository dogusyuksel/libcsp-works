IMAGE_NAME := dyshell
WORKSPACE_PATH := /workspace
BINDING_PROJECT_PATH := $(WORKSPACE_PATH)/rust-server/bindings-creator
SERVER_PROJECT_PATH := $(WORKSPACE_PATH)/rust-server/csp-server
DOCKER_ARGS := --rm --net=host -v $(shell pwd)/..:$(WORKSPACE_PATH) -e WORKSPACE_PATH=$(WORKSPACE_PATH)

.PHONY: all create-bindings build-server

all: create-bindings

build-docker:
	docker build -t $(IMAGE_NAME) .

create-bindings: build-docker
	docker run $(DOCKER_ARGS) -t --entrypoint=/bin/bash $(IMAGE_NAME) -c "cd $(BINDING_PROJECT_PATH) && cargo clean && cargo build"

build-server: build-docker
	docker run $(DOCKER_ARGS) -t --entrypoint=/bin/bash $(IMAGE_NAME) -c "cd $(SERVER_PROJECT_PATH) && cargo clean && cargo build"

console: build-docker
	docker run $(DOCKER_ARGS) -it --entrypoint=/bin/bash $(IMAGE_NAME)
