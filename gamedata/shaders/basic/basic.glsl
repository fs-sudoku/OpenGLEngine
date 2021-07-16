uniform float time;

void vertex() {
    POSITION = PROJECTION * VIEW * MODEL * vec4(SELF_POSITION, 1.0);
}

void fragment() {
    COLOR = vec4(1.0, 1.0, 1.0, 1.0);
}