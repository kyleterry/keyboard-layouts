DOCKER := docker
BUILDER_IMAGE_NAME := kyleterry/qmk:latest-alpine

.PHONY: build-builder release-builder
build-builder: ; $(DOCKER) build -f Dockerfile.builder -t $(BUILDER_IMAGE_NAME) .
release-builder: ; $(DOCKER) push $(BUILDER_IMAGE_NAME)

keyboards/%/%:
	@mkdir -p out
	$(DOCKER) run -it --rm -v $(PWD)/$@:/build/$@ -v $(PWD)/out:/build/.build kyleterry/qmk:latest-alpine make $(keyboard):$(layout)
