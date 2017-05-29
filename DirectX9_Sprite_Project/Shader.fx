uniform extern texture ScreenTexture;

sampler ScreenS = sampler_state
{
	Texture = <ScreenTexture>;
};


matrix mWorldTrans;

//TODO : Make VertexShader ~~
VS_OUTPUT VS_Main()

float4 PS_Main(float3 pos : SV_POSITION,
			   float4 color : COLOR0) : COLOR
{
	pos = mul(pos, mWorldTrans);

	color = 1;
	return color;
}

technique SpritePixelShader
{
	pass P0
	{
		PixelShader = compile ps_3_0 PS_Main();
	}
}
