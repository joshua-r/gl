#version 450

out gl_PerVertex {
    vec4 gl_Position;
};

layout(location = 0) out vec2 tex_coord;

void main() {
    // Vertex Shader Tricks by Bill Bilodeau - AMD at GDC 14
    gl_Position = vec4(float(gl_VertexID / 2) * 4.0 - 1.0, float(gl_VertexID % 2) * -4.0 + 1.0, 0.0, 1.0);
    tex_coord = vec2(float(gl_VertexID / 2) * 2.0, float(gl_VertexID % 2) * 2.0);
}
