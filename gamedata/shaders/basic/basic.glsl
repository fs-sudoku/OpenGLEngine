void vertex() {
    gl_Position = PROJECTION * VIEW * MODEL * vec4(SELF_POSITION, 1.0);
}

void fragment() {
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}