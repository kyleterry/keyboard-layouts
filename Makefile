MKDIR_P            := mkdir -p
DOCKER             := docker
BUILDER_IMAGE_NAME := kyleterry/qmk-keyboard-builder:latest
NAMESPACE          := kt-qmk
FORCE_PERMS        := true
BUILD_ERRORS       = exit 1

define GET_KEYBOARDS
  MAPS := $$(patsubst keyboards/%/keymap.c,%,$$(wildcard keyboards/*/keymap.c))
  MAPS += $$(patsubst keyboards/%/keymap.c,%,$$(wildcard keyboards/*/*/keymap.c))
  MAPS += $$(patsubst keyboards/%/keymap.c,%,$$(wildcard keyboards/*/*/*/keymap.c))

  UNMAPS := $$(foreach MAP, $$(MAPS), $$(lastword $$(subst /, , $$(MAP))))

  PREPARED := $$(foreach UNMAP, $$(UNMAPS), $$(subst /$$(UNMAP), , $$(MAPS)))
  KEYBOARDS := $$(sort $$(filter-out $$(MAPS), $$(PREPARED)))
endef

define GET_LAYOUTS
  LAYOUTS := $$(patsubst keyboards/$$(KEYBOARD)/%/keymap.c,%,$$(wildcard keyboards/$$(KEYBOARD)/*/keymap.c))
  LAYOUTS += $$(patsubst keyboards/$$(KEYBOARD)/%/keymap.c,%,$$(wildcard keyboards/$$(KEYBOARD)/*/*/keymap.c))
  LAYOUTS += $$(patsubst keyboards/$$(KEYBOARD)/%/keymap.c,%,$$(wildcard keyboards/$$(KEYBOARD)/*/*/*/keymap.c))
endef

.PHONY: build-builder release-builder
build-builder: ; $(DOCKER) build -t $(BUILDER_IMAGE_NAME) .
release-builder: ; $(DOCKER) push $(BUILDER_IMAGE_NAME)

.PHONY: list-keyboards
list-keyboards:
	$(eval $(call GET_KEYBOARDS))
	@echo $(KEYBOARDS)

.PHONY: clean
clean:
	rm -rf *.hex
