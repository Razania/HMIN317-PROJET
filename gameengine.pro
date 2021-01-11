QT       += core gui widgets
QT += 3dcore 3drender 3dinput 3dextras
TARGET = gameengine
TEMPLATE = app

LIBS += -lOpenGL32

SOURCES += \
    GameObjects/directionallightobject.cpp \
    GameObjects/pointlightobject.cpp \
    GameObjects/skyboxgameobject.cpp \
    GameObjects/spotlightobject.cpp \
    Main/main.cpp \
    Main/mainwidget.cpp \
    GameObjects/camera.cpp \
    GameObjects/gameobject.cpp \
    GameObjects/transform.cpp \
    GameObjects/chunkgameobject.cpp \
    Misc/lightningengine.cpp \
    WorldGeneration/chunk.cpp \
    WorldGeneration/worldgrid.cpp \
    WorldGeneration/block.cpp \
    Misc/geometryengine.cpp \
    Misc/textureloader.cpp \
    noise/src/latlon.cpp \
    noise/src/model/cylinder.cpp \
    noise/src/model/line.cpp \
    noise/src/model/plane.cpp \
    noise/src/model/sphere.cpp \
    noise/src/module/abs.cpp \
    noise/src/module/add.cpp \
    noise/src/module/billow.cpp \
    noise/src/module/blend.cpp \
    noise/src/module/cache.cpp \
    noise/src/module/checkerboard.cpp \
    noise/src/module/clamp.cpp \
    noise/src/module/const.cpp \
    noise/src/module/curve.cpp \
    noise/src/module/cylinders.cpp \
    noise/src/module/displace.cpp \
    noise/src/module/exponent.cpp \
    noise/src/module/invert.cpp \
    noise/src/module/max.cpp \
    noise/src/module/min.cpp \
    noise/src/module/modulebase.cpp \
    noise/src/module/multiply.cpp \
    noise/src/module/perlin.cpp \
    noise/src/module/power.cpp \
    noise/src/module/ridgedmulti.cpp \
    noise/src/module/rotatepoint.cpp \
    noise/src/module/scalebias.cpp \
    noise/src/module/scalepoint.cpp \
    noise/src/module/select.cpp \
    noise/src/module/spheres.cpp \
    noise/src/module/terrace.cpp \
    noise/src/module/translatepoint.cpp \
    noise/src/module/turbulence.cpp \
    noise/src/module/voronoi.cpp \
    noise/src/noisegen.cpp \
    noise/src/win32/dllmain.cpp


HEADERS += \
    GameObjects/directionallightobject.h \
    GameObjects/pointlightobject.h \
    GameObjects/skyboxgameobject.h \
    GameObjects/spotlightobject.h \
    Main/mainwidget.h \
    GameObjects/camera.h \
    GameObjects/gameobject.h \
    GameObjects/transform.h \
    GameObjects/chunkgameobject.h \
    Misc/Generic.h \
    Misc/enum.h \
    Misc/lightningengine.h \
    PerlinNoise/PerlinNoise.hpp \
    WorldGeneration/chunk.h \
    WorldGeneration/worldgrid.h \
    WorldGeneration/block.h \
    Misc/geometryengine.h \
    Misc/BasicIO.h \
    Misc/textureloader.h \
    noise/src/basictypes.h \
    noise/src/exception.h \
    noise/src/interp.h \
    noise/src/latlon.h \
    noise/src/mathconsts.h \
    noise/src/misc.h \
    noise/src/model/cylinder.h \
    noise/src/model/line.h \
    noise/src/model/model.h \
    noise/src/model/plane.h \
    noise/src/model/sphere.h \
    noise/src/module/abs.h \
    noise/src/module/add.h \
    noise/src/module/billow.h \
    noise/src/module/blend.h \
    noise/src/module/cache.h \
    noise/src/module/checkerboard.h \
    noise/src/module/clamp.h \
    noise/src/module/const.h \
    noise/src/module/curve.h \
    noise/src/module/cylinders.h \
    noise/src/module/displace.h \
    noise/src/module/exponent.h \
    noise/src/module/invert.h \
    noise/src/module/max.h \
    noise/src/module/min.h \
    noise/src/module/module.h \
    noise/src/module/modulebase.h \
    noise/src/module/multiply.h \
    noise/src/module/perlin.h \
    noise/src/module/power.h \
    noise/src/module/ridgedmulti.h \
    noise/src/module/rotatepoint.h \
    noise/src/module/scalebias.h \
    noise/src/module/scalepoint.h \
    noise/src/module/select.h \
    noise/src/module/spheres.h \
    noise/src/module/terrace.h \
    noise/src/module/translatepoint.h \
    noise/src/module/turbulence.h \
    noise/src/module/voronoi.h \
    noise/src/noise.h \
    noise/src/noisegen.h \
    noise/src/vectortable.h \
    noise/src/win32/noise.rc \
    noise/src/win32/resource.h

RESOURCES += \
    Models/obj.qrc \
    Shaders/shaders.qrc \
    Textures/textures.qrc

CONFIG += console c++2a c++1z c++14
# install
target.path = "$$PWD/Build"
INSTALLS += target

DISTFILES += \
    noise/INSTALL \
    noise/doc/Doxyfile \
    noise/doc/html/abs_8h-source.html \
    noise/doc/html/add_8h-source.html \
    noise/doc/html/annotated.html \
    noise/doc/html/background.png \
    noise/doc/html/basictypes_8h-source.html \
    noise/doc/html/billow_8h-source.html \
    noise/doc/html/blend_8h-source.html \
    noise/doc/html/cache_8h-source.html \
    noise/doc/html/checkerboard_8h-source.html \
    noise/doc/html/clamp_8h-source.html \
    noise/doc/html/classnoise_1_1Exception.html \
    noise/doc/html/classnoise_1_1Exception.png \
    noise/doc/html/classnoise_1_1ExceptionInvalidParam.html \
    noise/doc/html/classnoise_1_1ExceptionInvalidParam.png \
    noise/doc/html/classnoise_1_1ExceptionNoModule.html \
    noise/doc/html/classnoise_1_1ExceptionNoModule.png \
    noise/doc/html/classnoise_1_1ExceptionOutOfMemory.html \
    noise/doc/html/classnoise_1_1ExceptionOutOfMemory.png \
    noise/doc/html/classnoise_1_1ExceptionUnknown.html \
    noise/doc/html/classnoise_1_1ExceptionUnknown.png \
    noise/doc/html/classnoise_1_1model_1_1Cylinder-members.html \
    noise/doc/html/classnoise_1_1model_1_1Cylinder.html \
    noise/doc/html/classnoise_1_1model_1_1Line-members.html \
    noise/doc/html/classnoise_1_1model_1_1Line.html \
    noise/doc/html/classnoise_1_1model_1_1Plane-members.html \
    noise/doc/html/classnoise_1_1model_1_1Plane.html \
    noise/doc/html/classnoise_1_1model_1_1Sphere-members.html \
    noise/doc/html/classnoise_1_1model_1_1Sphere.html \
    noise/doc/html/classnoise_1_1module_1_1Abs-members.html \
    noise/doc/html/classnoise_1_1module_1_1Abs.html \
    noise/doc/html/classnoise_1_1module_1_1Abs.png \
    noise/doc/html/classnoise_1_1module_1_1Add-members.html \
    noise/doc/html/classnoise_1_1module_1_1Add.html \
    noise/doc/html/classnoise_1_1module_1_1Add.png \
    noise/doc/html/classnoise_1_1module_1_1Billow-members.html \
    noise/doc/html/classnoise_1_1module_1_1Billow.html \
    noise/doc/html/classnoise_1_1module_1_1Billow.png \
    noise/doc/html/classnoise_1_1module_1_1Blend-members.html \
    noise/doc/html/classnoise_1_1module_1_1Blend.html \
    noise/doc/html/classnoise_1_1module_1_1Blend.png \
    noise/doc/html/classnoise_1_1module_1_1Cache-members.html \
    noise/doc/html/classnoise_1_1module_1_1Cache.html \
    noise/doc/html/classnoise_1_1module_1_1Cache.png \
    noise/doc/html/classnoise_1_1module_1_1Checkerboard-members.html \
    noise/doc/html/classnoise_1_1module_1_1Checkerboard.html \
    noise/doc/html/classnoise_1_1module_1_1Checkerboard.png \
    noise/doc/html/classnoise_1_1module_1_1Clamp-members.html \
    noise/doc/html/classnoise_1_1module_1_1Clamp.html \
    noise/doc/html/classnoise_1_1module_1_1Clamp.png \
    noise/doc/html/classnoise_1_1module_1_1Const-members.html \
    noise/doc/html/classnoise_1_1module_1_1Const.html \
    noise/doc/html/classnoise_1_1module_1_1Const.png \
    noise/doc/html/classnoise_1_1module_1_1Curve-members.html \
    noise/doc/html/classnoise_1_1module_1_1Curve.html \
    noise/doc/html/classnoise_1_1module_1_1Curve.png \
    noise/doc/html/classnoise_1_1module_1_1Cylinders-members.html \
    noise/doc/html/classnoise_1_1module_1_1Cylinders.html \
    noise/doc/html/classnoise_1_1module_1_1Cylinders.png \
    noise/doc/html/classnoise_1_1module_1_1Displace-members.html \
    noise/doc/html/classnoise_1_1module_1_1Displace.html \
    noise/doc/html/classnoise_1_1module_1_1Displace.png \
    noise/doc/html/classnoise_1_1module_1_1Exponent-members.html \
    noise/doc/html/classnoise_1_1module_1_1Exponent.html \
    noise/doc/html/classnoise_1_1module_1_1Exponent.png \
    noise/doc/html/classnoise_1_1module_1_1Invert-members.html \
    noise/doc/html/classnoise_1_1module_1_1Invert.html \
    noise/doc/html/classnoise_1_1module_1_1Invert.png \
    noise/doc/html/classnoise_1_1module_1_1Max-members.html \
    noise/doc/html/classnoise_1_1module_1_1Max.html \
    noise/doc/html/classnoise_1_1module_1_1Max.png \
    noise/doc/html/classnoise_1_1module_1_1Min-members.html \
    noise/doc/html/classnoise_1_1module_1_1Min.html \
    noise/doc/html/classnoise_1_1module_1_1Min.png \
    noise/doc/html/classnoise_1_1module_1_1Module-members.html \
    noise/doc/html/classnoise_1_1module_1_1Module.html \
    noise/doc/html/classnoise_1_1module_1_1Module.png \
    noise/doc/html/classnoise_1_1module_1_1Multiply-members.html \
    noise/doc/html/classnoise_1_1module_1_1Multiply.html \
    noise/doc/html/classnoise_1_1module_1_1Multiply.png \
    noise/doc/html/classnoise_1_1module_1_1Perlin-members.html \
    noise/doc/html/classnoise_1_1module_1_1Perlin.html \
    noise/doc/html/classnoise_1_1module_1_1Perlin.png \
    noise/doc/html/classnoise_1_1module_1_1Power-members.html \
    noise/doc/html/classnoise_1_1module_1_1Power.html \
    noise/doc/html/classnoise_1_1module_1_1Power.png \
    noise/doc/html/classnoise_1_1module_1_1RidgedMulti-members.html \
    noise/doc/html/classnoise_1_1module_1_1RidgedMulti.html \
    noise/doc/html/classnoise_1_1module_1_1RidgedMulti.png \
    noise/doc/html/classnoise_1_1module_1_1RotatePoint-members.html \
    noise/doc/html/classnoise_1_1module_1_1RotatePoint.html \
    noise/doc/html/classnoise_1_1module_1_1RotatePoint.png \
    noise/doc/html/classnoise_1_1module_1_1ScaleBias-members.html \
    noise/doc/html/classnoise_1_1module_1_1ScaleBias.html \
    noise/doc/html/classnoise_1_1module_1_1ScaleBias.png \
    noise/doc/html/classnoise_1_1module_1_1ScalePoint-members.html \
    noise/doc/html/classnoise_1_1module_1_1ScalePoint.html \
    noise/doc/html/classnoise_1_1module_1_1ScalePoint.png \
    noise/doc/html/classnoise_1_1module_1_1Select-members.html \
    noise/doc/html/classnoise_1_1module_1_1Select.html \
    noise/doc/html/classnoise_1_1module_1_1Select.png \
    noise/doc/html/classnoise_1_1module_1_1Spheres-members.html \
    noise/doc/html/classnoise_1_1module_1_1Spheres.html \
    noise/doc/html/classnoise_1_1module_1_1Spheres.png \
    noise/doc/html/classnoise_1_1module_1_1Terrace-members.html \
    noise/doc/html/classnoise_1_1module_1_1Terrace.html \
    noise/doc/html/classnoise_1_1module_1_1Terrace.png \
    noise/doc/html/classnoise_1_1module_1_1TranslatePoint-members.html \
    noise/doc/html/classnoise_1_1module_1_1TranslatePoint.html \
    noise/doc/html/classnoise_1_1module_1_1TranslatePoint.png \
    noise/doc/html/classnoise_1_1module_1_1Turbulence-members.html \
    noise/doc/html/classnoise_1_1module_1_1Turbulence.html \
    noise/doc/html/classnoise_1_1module_1_1Turbulence.png \
    noise/doc/html/classnoise_1_1module_1_1Voronoi-members.html \
    noise/doc/html/classnoise_1_1module_1_1Voronoi.html \
    noise/doc/html/classnoise_1_1module_1_1Voronoi.png \
    noise/doc/html/const_8h-source.html \
    noise/doc/html/curve.png \
    noise/doc/html/curve_8h-source.html \
    noise/doc/html/cylinder_8h-source.html \
    noise/doc/html/cylinders_8h-source.html \
    noise/doc/html/dir_000000.html \
    noise/doc/html/dir_000001.html \
    noise/doc/html/dir_000002.html \
    noise/doc/html/dir_000003.html \
    noise/doc/html/displace_8h-source.html \
    noise/doc/html/doxygen.css \
    noise/doc/html/doxygen.png \
    noise/doc/html/exception_8h-source.html \
    noise/doc/html/exponent_8h-source.html \
    noise/doc/html/files.html \
    noise/doc/html/functions.html \
    noise/doc/html/functions_func.html \
    noise/doc/html/functions_vars.html \
    noise/doc/html/group__combinermodules.html \
    noise/doc/html/group__generatormodules.html \
    noise/doc/html/group__libnoise.html \
    noise/doc/html/group__miscmodules.html \
    noise/doc/html/group__models.html \
    noise/doc/html/group__modifiermodules.html \
    noise/doc/html/group__modules.html \
    noise/doc/html/group__selectormodules.html \
    noise/doc/html/group__transformermodules.html \
    noise/doc/html/hierarchy.html \
    noise/doc/html/index.html \
    noise/doc/html/interp_8h-source.html \
    noise/doc/html/invert_8h-source.html \
    noise/doc/html/latlon_8h-source.html \
    noise/doc/html/libnoise.png \
    noise/doc/html/line_8h-source.html \
    noise/doc/html/mathconsts_8h-source.html \
    noise/doc/html/max_8h-source.html \
    noise/doc/html/min_8h-source.html \
    noise/doc/html/misc_8h-source.html \
    noise/doc/html/model_8h-source.html \
    noise/doc/html/modelcylinder.png \
    noise/doc/html/modelsphere.png \
    noise/doc/html/module_8h-source.html \
    noise/doc/html/moduleabs.png \
    noise/doc/html/moduleadd.png \
    noise/doc/html/modulebase_8h-source.html \
    noise/doc/html/modulebillow.png \
    noise/doc/html/moduleblend.png \
    noise/doc/html/modulecheckerboard.png \
    noise/doc/html/moduleclamp.png \
    noise/doc/html/moduleconst.png \
    noise/doc/html/modulecurve.png \
    noise/doc/html/modulecylinders.png \
    noise/doc/html/moduledisplace.png \
    noise/doc/html/moduleexponent.png \
    noise/doc/html/moduleinvert.png \
    noise/doc/html/modulemax.png \
    noise/doc/html/modulemin.png \
    noise/doc/html/modulemultiply.png \
    noise/doc/html/moduleperlin.png \
    noise/doc/html/modulepower.png \
    noise/doc/html/moduleridgedmulti.png \
    noise/doc/html/modulerotatepoint.png \
    noise/doc/html/modules.html \
    noise/doc/html/modulescalebias.png \
    noise/doc/html/modulescalepoint.png \
    noise/doc/html/moduleselect.png \
    noise/doc/html/modulespheres.png \
    noise/doc/html/moduleterrace.png \
    noise/doc/html/moduletranslatepoint.png \
    noise/doc/html/moduleturbulence.png \
    noise/doc/html/modulevoronoi.png \
    noise/doc/html/multiply_8h-source.html \
    noise/doc/html/noise_8h-source.html \
    noise/doc/html/noisegen_8h-source.html \
    noise/doc/html/perlin_8h-source.html \
    noise/doc/html/plane_8h-source.html \
    noise/doc/html/power_8h-source.html \
    noise/doc/html/resource_8h-source.html \
    noise/doc/html/ridgedmulti_8h-source.html \
    noise/doc/html/rotatepoint_8h-source.html \
    noise/doc/html/scalebias_8h-source.html \
    noise/doc/html/scalepoint_8h-source.html \
    noise/doc/html/select_8h-source.html \
    noise/doc/html/sphere_8h-source.html \
    noise/doc/html/spheres_8h-source.html \
    noise/doc/html/structnoise_1_1module_1_1ControlPoint-members.html \
    noise/doc/html/structnoise_1_1module_1_1ControlPoint.html \
    noise/doc/html/terrace.png \
    noise/doc/html/terrace_8h-source.html \
    noise/doc/html/translatepoint_8h-source.html \
    noise/doc/html/turbulence_8h-source.html \
    noise/doc/html/vectortable_8h-source.html \
    noise/doc/html/voronoi_8h-source.html \
    noise/doc/htmldata/background.png \
    noise/doc/htmldata/doxygen.css \
    noise/doc/htmldata/libnoise.png \
    noise/doc/htmldata/templatefooter.html \
    noise/doc/htmldata/templateheader.html \
    noise/doc/img/curve.png \
    noise/doc/img/gradientcolor.png \
    noise/doc/img/modelcylinder.png \
    noise/doc/img/modelsphere.png \
    noise/doc/img/moduleabs.png \
    noise/doc/img/moduleadd.png \
    noise/doc/img/modulebillow.png \
    noise/doc/img/moduleblend.png \
    noise/doc/img/modulecheckerboard.png \
    noise/doc/img/moduleclamp.png \
    noise/doc/img/moduleconst.png \
    noise/doc/img/modulecurve.png \
    noise/doc/img/modulecylinders.png \
    noise/doc/img/moduledisplace.png \
    noise/doc/img/moduleexponent.png \
    noise/doc/img/moduleinvert.png \
    noise/doc/img/modulemax.png \
    noise/doc/img/modulemin.png \
    noise/doc/img/modulemultiply.png \
    noise/doc/img/moduleperlin.png \
    noise/doc/img/modulepower.png \
    noise/doc/img/moduleridgedmulti.png \
    noise/doc/img/modulerotatepoint.png \
    noise/doc/img/modulescalebias.png \
    noise/doc/img/modulescalepoint.png \
    noise/doc/img/moduleselect.png \
    noise/doc/img/modulespheres.png \
    noise/doc/img/moduleterrace.png \
    noise/doc/img/moduletranslatepoint.png \
    noise/doc/img/moduleturbulence.png \
    noise/doc/img/modulevoronoi.png \
    noise/doc/img/terrace.png \
    noise/doc/readme.txt \
    noise/libnoise.dsp \
    noise/libnoise.dsw \
    noise/libnoise.ncb \
    noise/libnoise.opt \
    noise/libnoise.plg \
    noise/noise.aps \
    noise/src/Sources \
    noise/src/win32/libnoise.def \
    noise/src/win32/noise.aps



