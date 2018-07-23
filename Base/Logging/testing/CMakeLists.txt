set(REQUIRED_LIBRARIES gTest_static gMock_static libLogging_gmock libLogging)
createUnitTests("${targetName}" "${REQUIRED_LIBRARIES}")
