// 頂点シェーダーのメイン関数
// 役割：各頂点の対して行いたい移動・回転・縮小などを実行する
// 戻り値：このシェーダーの処理の結果を、頂点のデータとして戻す
// 引数 inputPos：VRAMに転送された頂点データ（のうち１つ）が渡される
//      C言語で設定した頂点座標と同じ座標系

// return用の構造体
struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT vs_main(float4 inputPos : POSITION, float4 inputColor : COLOR) {
	VS_OUTPUT output;

	output.pos = inputPos;  // 渡されたxyとuvを変数に移す
	//output.uv = uv;
	output.color = inputColor;

	// 画面比率で横長になってしまうのを調整する
	//output.pos.x *= 480.0f / 640.0f;

	return output;
}