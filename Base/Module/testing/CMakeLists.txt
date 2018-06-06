
set(REQUIRED_LIBRARIES gTest_static gMock_static libModule_gmock)
createUnitTests("${targetName}" "${REQUIRED_LIBRARIES}")
