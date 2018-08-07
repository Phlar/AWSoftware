set(REQUIRED_LIBRARIES gTest_static libSceneGraphBase_gmock libSceneGraphBase)
createUnitTests("${targetName}" "${REQUIRED_LIBRARIES}")
