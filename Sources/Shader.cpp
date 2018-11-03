#include <Kore/pch.h>
//#include "pch.h"

#include <Kore/Graphics4/Graphics.h>
#include <Kore/Graphics4/PipelineState.h>
#include <Kore/Graphics4/Shader.h>
#include <Kore/IO/FileReader.h>
#include <Kore/Input/Mouse.h>
#include <Kore/System.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits>

using namespace Kore;

namespace {
Graphics4::Shader* vertexShader;
Graphics4::Shader* fragmentShader;
Graphics4::PipelineState* pipeline;
Graphics4::VertexBuffer* vertices;
Graphics4::IndexBuffer* indices;
Graphics4::ConstantLocation mousePos;
int mouseX = 0;
int mouseY = 0;

void mouseMove(int windowId, int x, int y, int movementX, int movementY) {
  // mouseX = x;
  // printf("update\n");
}

void mousePress(int windowId, int button, int x, int y) {
  //   mouseX = x;
  //   mouseY = y;
  //   printf("update\n");
}

void mouseRelease(int windowId, int button, int x, int y) {
  mouseX = x;
  mouseY = y;
  printf("mouse.x: %i mouse.y: %i\n", mouseX, mouseY);
}

void update() {
  Graphics4::begin();
  Graphics4::clear(Kore::Graphics4::ClearColorFlag);
  Graphics4::setPipeline(pipeline);
  Graphics4::setFloat2(mousePos, (float)mouseX, (float)mouseY);
  Graphics4::setVertexBuffer(*vertices);
  Graphics4::setIndexBuffer(*indices);
  Graphics4::drawIndexedVertices();
  Graphics4::end();
  Graphics4::swapBuffers();
}
}  // namespace

int kore(int argc, char** argv) {
  Kore::System::init("Shader", 512, 512);
  Kore::System::setCallback(update);

  FileReader vs("shader.vert");
  FileReader fs("shader.frag");
  vertexShader =
      new Graphics4::Shader(vs.readAll(), vs.size(), Graphics4::VertexShader);
  fragmentShader =
      new Graphics4::Shader(fs.readAll(), fs.size(), Graphics4::FragmentShader);
  Graphics4::VertexStructure structure;
  structure.add("pos", Graphics4::Float3VertexData);
  pipeline = new Graphics4::PipelineState();
  pipeline->inputLayout[0] = &structure;
  pipeline->inputLayout[1] = nullptr;
  pipeline->vertexShader = vertexShader;
  pipeline->fragmentShader = fragmentShader;
  pipeline->compile();
  mousePos = pipeline->getConstantLocation("iMouse");

  vertices = new Graphics4::VertexBuffer(3, structure);
  float* v = vertices->lock();
  v[0] = -1;
  v[1] = -1;
  v[2] = 0.5;
  v[3] = 1;
  v[4] = -1;
  v[5] = 0.5;
  v[6] = -1;
  v[7] = 1;
  v[8] = 0.5;
  vertices->unlock();

  indices = new Graphics4::IndexBuffer(3);
  int* i = indices->lock();
  i[0] = 0;
  i[1] = 1;
  i[2] = 2;
  indices->unlock();

  Mouse::the()->Move = mouseMove;
  Mouse::the()->Press = mousePress;
  Mouse::the()->Release = mouseRelease;

  Kore::System::start();

  return 0;
}
