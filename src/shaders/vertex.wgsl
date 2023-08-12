const VERTICES: array<vec2f, 3> = array(
	vec2f(-.75, -.75),
	vec2f( 0,    .75),
	vec2f( .75, -.75),
);

@vertex
fn main(@builtin(vertex_index) vertex_index: u32) -> @builtin(position) vec4f {
	return vec4f(VERTICES[vertex_index], 0, 1);
}