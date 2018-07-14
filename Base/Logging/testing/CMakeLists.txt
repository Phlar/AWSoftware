set(REQUIRED_LIBRARIES gTest_static gMock_static libLogging)
createUnitTests("${targetName}" "${REQUIRED_LIBRARIES}")
