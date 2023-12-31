OBJS = Raytracer.o VertexAttrib.o TextureImage.o ScenegraphImporter.o Controller.o Model.o View.o AbstractSGNode.o GroupNode.o ChildSGNode.o LeafNode.o LightNode.o SpotlightNode.o ParentSGNode.o RotateTransform.o ScaleTransform.o TransformNode.o TranslateTransform.o AbstractRenderer.o GLScenegraphRenderer.o RaytracerRenderer.o Scenegraph.o Box.o Sphere.o Cylinder.o Cone.o Triangle.o MeshObject.o
INCLUDES = -I../include
LIBS = -L../lib
LDFLAGS = -lglad -lglfw3
CFLAGS = -g
PROGRAM = Raytracer
COMPILER = g++

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    LDFLAGS += -lopengl32 -lgdi32
    PROGRAM :=$(addsuffix .exe,$(PROGRAM))
else ifeq ($(shell uname -s),Darwin)     # is MACOSX
    LDFLAGS += -framework Cocoa -framework OpenGL -framework IOKit
endif

Raytracer: clean $(OBJS)
	$(COMPILER) -o $(PROGRAM) $(OBJS) $(LIBS) $(LDFLAGS)

Raytracer.o: Raytracer.cpp
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c Raytracer.cpp	

VertexAttrib.o: VertexAttrib.cpp
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c VertexAttrib.cpp

TextureImage.o: ../include/TextureImage.cpp
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c ../include/TextureImage.cpp

ScenegraphImporter.o: ScenegraphImporter.cpp ScenegraphImporter.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c ScenegraphImporter.cpp

Controller.o: Controller.cpp Controller.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c Controller.cpp	

Model.o: Model.cpp Model.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c Model.cpp	

View.o: View.cpp View.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c View.cpp	

AbstractSGNode.o: sgraph/nodes/AbstractSGNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/AbstractSGNode.cpp

GroupNode.o: sgraph/nodes/GroupNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/GroupNode.cpp

ChildSGNode.o: sgraph/nodes/ChildSGNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/ChildSGNode.cpp

LeafNode.o: sgraph/nodes/LeafNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/LeafNode.cpp

LightNode.o: sgraph/nodes/LightNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/LightNode.cpp

SpotlightNode.o: sgraph/nodes/SpotlightNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/SpotlightNode.cpp

ParentSGNode.o: sgraph/nodes/ParentSGNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/ParentSGNode.cpp

RotateTransform.o: sgraph/nodes/RotateTransform.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/RotateTransform.cpp

ScaleTransform.o: sgraph/nodes/ScaleTransform.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/ScaleTransform.cpp

TransformNode.o: sgraph/nodes/TransformNode.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/TransformNode.cpp

TranslateTransform.o: sgraph/nodes/TranslateTransform.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/nodes/TranslateTransform.cpp

AbstractRenderer.o: sgraph/AbstractRenderer.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/AbstractRenderer.cpp

GLScenegraphRenderer.o: sgraph/GLScenegraphRenderer.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/GLScenegraphRenderer.cpp

RaytracerRenderer.o: sgraph/RaytracerRenderer.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/RaytracerRenderer.cpp

Scenegraph.o: sgraph/Scenegraph.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c sgraph/Scenegraph.cpp

Box.o: objects/Box.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c objects/Box.cpp

Sphere.o: objects/Sphere.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c objects/Sphere.cpp

Cylinder.o: objects/Cylinder.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c objects/Cylinder.cpp

Cone.o: objects/Cone.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c objects/Cone.cpp

Triangle.o: objects/Triangle.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c objects/Triangle.cpp

MeshObject.o: objects/MeshObject.cpp 
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c objects/MeshObject.cpp

RM = rm	-f
ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    RM := del
endif

clean: 
	$(RM) $(OBJS) $(PROGRAM)