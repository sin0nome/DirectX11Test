
#include <windows.h>

// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


constexpr wchar_t CLASS_NAME[] = L"hogehoge";
constexpr wchar_t WINDOW_NAME[] = L"Hoge";


int WINAPI WinMain(const HINSTANCE hInstance, const  HINSTANCE hPrevInstance, const  LPSTR lpCmdLine, const  int nCmdShow) {

	WNDCLASSEX wc; // WND = Window

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc); // Windowsにウインドウ情報を登録

	HWND hWnd; // H=Handle=ポインタ WND=Window
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,	// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		640,// ウィンドウの幅
		480,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);


	UnregisterClass(CLASS_NAME, hInstance);

	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// uMsg（この関数の第2引数）が、ユーザー操作のID情報
	switch (uMsg) {
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;
	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;
	case WM_KEYDOWN:
		// キーが押された時のリアクションを書く
		// ESCが押されたのかどうかチェック
		if (LOWORD(wParam) == VK_ESCAPE) {
			// メッセージボックスで修了確認
			const int result = MessageBox(NULL, L"終了してよろしいですか？", L"終了確認", MB_YESNO | MB_ICONQUESTION);

			// 「はい」ボタンが押された時
			if (result == IDYES) {
				// xボタンが押されたのと同じ効果を発揮する
				PostMessage(hWnd, WM_CLOSE, wParam, lParam);
			}
		}
		break;
	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
