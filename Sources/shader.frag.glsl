#version 450

out vec4 frag;
uniform vec2 iMouse;

void main() {
  float x = iMouse.x;
  float y = iMouse.y;
  frag = vec4(1.0, 0.0, 0.0, 1.0);
}
