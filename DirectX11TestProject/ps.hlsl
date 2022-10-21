// ピクセルシェーダーのメイン関数　→　ポリゴンを描画するのに必要なピクセル数だけ呼び出される
// 各ピクセルの色を指定するのが役目
// 戻り値：　このピクセルを何色にしたいか、RGBAで指定する
// 引数inputPos：　ピクセルの座標。ウインドウの左上を原点とするピクセル座標。

// テクスチャを受け取るグローバル変数
Texture2D gTexture : register(t0);

// サンプラーのグローバル変数
SamplerState gSampler : register(s0);


float4 ps_main(float4 inputPos : SV_POSITION, float4 inputColor : COLOR) : SV_Target{
	float2 inputTex = float2(0.0f, 0.0f);

	// Texture2D.Sample method gets a color from the texture by calculating with UVs.
	float4 pixelColor;// = gTexture.Sample(gSampler, inputTex);

	/*
	pixelColor.r = inputColor.r * (pixelColor.r * 1.1f + 0.10f);
	pixelColor.g = inputColor.g * (pixelColor.g + 0.15f);
	pixelColor.b = inputColor.b * (pixelColor.b + 0.15f);
	pixelColor.a = inputColor.a * pixelColor.a;
	*/

	pixelColor.r = inputColor.r * (1.1f + 0.10f);
	pixelColor.g = inputColor.g * (0.15f);
	pixelColor.b = inputColor.b * (0.15f);
	pixelColor.a = inputColor.a;

	return pixelColor;
}
