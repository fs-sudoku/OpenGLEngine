uniform float time;

void vertex() {
    POSITION = vec4(SELF_POSITION, 1.0);
}

void fragment() {
    COLOR = vec4(1.0, 1.0, 1.0, 1.0);
}