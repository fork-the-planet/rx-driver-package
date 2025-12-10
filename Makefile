RELEASE_TAG_COMMIT_NUMBER_LATEST = c6eac928c7b04867a6261cda5eceb02f935c4e56
RELEASE_TAG_COMMIT_VERSION_LATEST = 1.48
VERSIONS_FILE_NAME = versions.xml

MODULE_NAME_LIST_LATEST = 	r_emwin_rx \

all:
	for i in $(MODULE_NAME_LIST_LATEST); do \
		cd ./source/$$i/; \
		make; \
		cd ../../; \
	done

latest:
	for i in $(MODULE_NAME_LIST_LATEST); do \
		cd ./source/$$i/; \
		make; \
		cd ../../; \
	done

clean:
	rm -rf ./FITModules
	mkdir ./FITModules

fix_xml:
	sed -i '/  <!-- Latest Package -->/q' ./$(VERSIONS_FILE_NAME)
	for i in $(MODULE_NAME_LIST_LATEST); do \
		cd ./source/$$i/; \
		sh ../../tools/version_xml_generator.sh ./Makefile release_tag_commit_number=$(RELEASE_TAG_COMMIT_NUMBER_LATEST) release_tag_commit_version=$(RELEASE_TAG_COMMIT_VERSION_LATEST) >> ../../$(VERSIONS_FILE_NAME);\
		cd ../..; \
	done
	echo "</modules>" >> ./$(VERSIONS_FILE_NAME)
	sed -i 's/\r//g' ./$(VERSIONS_FILE_NAME)

update_xml:
	sed -i '/  <!-- Latest Package -->/d' ./$(VERSIONS_FILE_NAME)
	sed -i '/<\/modules>/d' ./$(VERSIONS_FILE_NAME)
	echo "  <!-- Latest Package -->" >> ./$(VERSIONS_FILE_NAME)
	for i in $(MODULE_NAME_LIST_LATEST); do \
		cd ./source/$$i/; \
		sh ../../tools/version_xml_generator.sh ./Makefile release_tag_commit_number=$(RELEASE_TAG_COMMIT_NUMBER_LATEST) release_tag_commit_version=$(RELEASE_TAG_COMMIT_VERSION_LATEST) >> ../../$(VERSIONS_FILE_NAME);\
		cd ../..; \
	done
	echo "</modules>" >> ./$(VERSIONS_FILE_NAME)
	sed -i 's/\r//g' ./$(VERSIONS_FILE_NAME)

%:
	rm -rf ./repo
	mkdir ./repo
	git clone https://github.com/renesas/rx-driver-package.git -b $@ ./repo
	mv ./repo/FITModules/* ./FITModules
	rm -rf ./repo
