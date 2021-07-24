void vertex() {
    gl_Position = Projection * View * Model * vec4(Pos, 1.0);
}

void fragment() {
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}