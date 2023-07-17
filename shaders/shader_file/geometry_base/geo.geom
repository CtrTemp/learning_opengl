
// // render single point by using geom buffer
// #version 330 core
// layout (points) in;
// layout (points, max_vertices = 1) out;

// void main() {    
//     gl_Position = gl_in[0].gl_Position; 
//     EmitVertex();
//     EndPrimitive();
// }  

// // render line by using geom buffer
// #version 330 core
// layout (points) in;
// layout (line_strip, max_vertices = 2) out;

// void main() {    
//     gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0); 
//     EmitVertex();

//     gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.0, 0.0, 0.0);
//     EmitVertex();

//     EndPrimitive();
// } 

// render triangle by using geom buffer
#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

void main() {
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.25, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}