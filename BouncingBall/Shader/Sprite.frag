//GLSL 3.3 사용
#version 330

// vertex shader 에서 넘어온 데이터
in vec2 fragTextureCoord;

// Color Buffer에 넘겨줄 색값
out vec4 outColor;

// 텍스쳐 샘플링용
// 따로 값을 안넣어주면 가장 최근칼라 값으로 초기화됨
uniform sampler2D uTexture;

void main()
{
	// 텍스쳐에서 Color 값 가져오기
	outColor = texture(uTexture, fragTextureCoord);
}
