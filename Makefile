MKDIR_P            := mkdir -p
DOCKER             := docker
BUILDER_IMAGE_NAME := kyleterry/qmk:latest-alpine
NAMESPACE          := kt-qmk
OUT                := out
FORCE_PERMS        := true
BUILD_ERRORS       = exit 1

define GET_KEYBOARDS
  KEYBOARDS := $$(sort $$(patsubst keyboards/%/,%,$$(dir $$(wildcard keyboards/*/))))
endef

define GET_LAYOUTS
  LAYOUTS := $$(sort $$(patsubst keyboards/$(KEYBOARD)/%/,%,$$(dir $$(wildcard keyboards/$(KEYBOARD)/*/))))
endef

define GET_VARIANTS
  VARIANTS := $$(sort $$(patsubst keyboards/%/,%,$$(dir $$(wildcard keyboards/*/*/))))
endef

$(eval $(call GET_KEYBOARDS))
$(eval $(call GET_VARIANTS))

.PHONY: all
all: $(foreach variant, $(VARIANTS), keyboards/$(variant))

.PHONY: list-keyboards
list-keyboards:
	@echo $(KEYBOARDS)

.PHONY: list-variants
list-variants:
	@echo $(VARIANTS)

.PHONY: clean
clean:
	rm -rf $(OUT)

$(OUT):
	$(MKDIR_P) $(OUT)

define MATCH_KEYBOARD
  KEYBOARD := $$(firstword $$(subst /, ,$1))
  ifneq ($$(filter $$(KEYBOARD),$$(KEYBOARDS)),)
    LAYOUT := $$(lastword $$(subst /, ,$1))
    $$(eval $$(call GET_LAYOUTS))
    $$(eval $$(call echo $$(LAYOUTS)))
    ifeq ($$(filter $$(LAYOUT),$$(LAYOUTS)),)
      $$(info make: *** No rule to make target '$1'. Stop.)
      $$(info | No layout exists with that name. Please use `make keyboards/keyboard/layout`)
      $$(BUILD_ERRORS)
    endif
  else
    $$(info make: *** No rule to make target '$1'. Stop.)
    $$(info | No keyboard exists with that name. Please use `make keyboards/keyboard/layout`)
    $$(BUILD_ERRORS)
  endif
endef

.PHONY: keyboards keyboards/%
keyboards/%: $(OUT)
	$(eval $(call MATCH_KEYBOARD,$*))
	$(DOCKER) run -it --rm \
		-v $(PWD)/keyboards/$(KEYBOARD)/$(LAYOUT):/build/keyboards/$(KEYBOARD)/keymaps/$(NAMESPACE)-$(LAYOUT) \
		-v $(PWD)/$(OUT):/build/out \
		$(BUILDER_IMAGE_NAME) \
		bash -c \
		"make $(KEYBOARD):$(NAMESPACE)-$(LAYOUT) && cp .build/$(KEYBOARD)*_$(NAMESPACE)-$(LAYOUT).hex out/$(KEYBOARD)-$(LAYOUT).hex"
ifeq ($(FORCE_PERMS),true)
	sudo chown $(USER):$(USER) $(OUT)/$(KEYBOARD)-$(LAYOUT).hex
endif

.PHONY: build-builder release-builder
build-builder: ; $(DOCKER) build -t $(BUILDER_IMAGE_NAME) .
release-builder: ; $(DOCKER) push $(BUILDER_IMAGE_NAME)
