
set(REQUIRED_LIBRARIES gTest_static gMock_static boost_regex_static)
createUnitTests("${targetName}" "${REQUIRED_LIBRARIES}")
