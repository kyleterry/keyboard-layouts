MKDIR_P            := mkdir -p
DOCKER             := docker
BUILDER_IMAGE_NAME := kyleterry/qmk:latest-alpine
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

define MATCH_KEYBOARD
  $$(eval $$(call GET_KEYBOARDS))
  LAYOUT := $$(lastword $$(subst /, ,$1))
  KEYBOARD := $$(subst /$$(LAYOUT),,$1)
  KEYBOARD_BIN := $$(subst /,_,$$(KEYBOARD))
  ifneq ($$(filter $$(KEYBOARD),$$(KEYBOARDS)),)
    $$(eval $$(call GET_LAYOUTS))
    $$(eval $$(call echo $$(LAYOUTS)))
    ifeq ($$(filter $$(LAYOUT),$$(LAYOUTS)),)
      $$(info make: *** No rule to make target '$1'. Stop.)
      $$(info | No layout exists with that name. Please use `make keyboard/layout`)
      $$(BUILD_ERRORS)
    endif
  else
    $$(info make: *** No rule to make target '$1'. Stop.)
    $$(info | No keyboard exists with that name. Please use `make keyboard/layout`)
    $$(BUILD_ERRORS)
  endif
endef

.PHONY: %
%: 
	$(eval $(call MATCH_KEYBOARD,$@))
	$(DOCKER) run -it --rm \
		-v $(PWD)/keyboards/$(KEYBOARD)/$(LAYOUT):/build/keyboards/$(KEYBOARD)/keymaps/$(NAMESPACE)-$(LAYOUT) \
		-v $(PWD):/build/out \
		$(BUILDER_IMAGE_NAME) \
		bash -c \
		"make $(KEYBOARD):$(NAMESPACE)-$(LAYOUT) && cp .build/$(KEYBOARD_BIN)*_$(NAMESPACE)-$(LAYOUT).hex out/$(KEYBOARD_BIN)-$(LAYOUT).hex"
ifeq ($(FORCE_PERMS),true)
	sudo chown $(USER):$(USER) $(KEYBOARD_BIN)-$(LAYOUT).hex
endif
