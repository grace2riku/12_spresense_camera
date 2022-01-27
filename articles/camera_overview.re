//footnote[aps_board][https://www.aps-web.jp/academy/amp/8467/]
//footnote[wifi_add_on_board][https://idy-design.com/product/is110b.html]

= デジタルカメラ機能説明

Spresenseはたくさんのサンプルプログラムがあります。

 * Spresense SDKのサンプルプログラム@<br>{}
    @<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html}

 * Arduino IDEのサンプルプログラム@<br>{}
    @<href>{https://developer.sony.com/develop/spresense/docs/arduino_tutorials_ja.html}

今回のデジタルカメラはSpresense SDKのサンプルプログラム【examples/camera】をベースにつくりました。

== examples/cameraサンプルプログラムの説明 
サンプルプログラムの概要は次のリンクに書かれています。

 * Spresense SDK@<br>{}
    @<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_camera_%E3%83%81%E3%83%A5%E3%83%BC%E3%83%88%E3%83%AA%E3%82%A2%E3%83%AB}

 * Arduino IDE@<br>{}
    @<href>{https://developer.sony.com/develop/spresense/docs/arduino_tutorials_ja.html#_tutorial_camera}


SDKの【examples/camera】サンプルプログラムは次のハードウェアを使う前提となっています。

 * Spresense Main Board（以降、メインボードと呼びます）

 * Spresense Camera Board（以降、カメラボードと呼びます）

 * Spresense Extension Board（以降、拡張ボードと呼びます）

 * Arduino UNO LCD Connector board

 * ILI9341 2.2inch LCD

サンプルプログラムはコマンドライン引数により動作が次のように変わります。
撮影画像はマイクロSDカードに保存されます。
もしマイクロSDカードが拡張ボードに挿入されていない場合はFlashROMに保存されます。

//cmd{
nsh> camera
//}
LCDにカメラの画像を表示し、10フレーム撮影後に終了します。
画像ファイルのフォーマットはRGB565形式になります。

//cmd{
nsh> camera -jpg
//}
LCDにカメラの画像を表示し、10フレーム撮影後に終了します。
画像ファイルのフォーマットはjpg形式になります。

//cmd{
nsh> camera n
//}
LCDにカメラの画像を表示し、nフレーム撮影後に終了します。
画像ファイルのフォーマットはRGB565形式になります。
nは0から100の範囲内で指定します。
nが0の場合はLCDに画像を表示し続け、画像ファイルを保存しません。

//cmd{
nsh> camera -jpg n
//}
LCDにカメラの画像を表示し、nフレーム撮影後に終了します。
画像ファイルのフォーマットはjpg形式になります。
nは0から100の範囲内で指定します。
nが0の場合はLCDに画像を表示し続け、画像ファイルを保存しません。

== デジタルカメラの要求仕様
サンプルプログラムは

 * 1〜100枚撮影したら終了

 * LCDに画像表示し続けている場合は画像保存せず、プログラムは終了しない。

という動きになっています。

一般的なデジタルカメラのように次の動作を実現したいと考えました。

 1. LCDに画像をプレビュー表示し続ける
 1. 任意のタイミングで画像を保存できること
 1. 任意のタイミングでカメラの使用を終了できること

ちょうど手元に以前購入していたAPS学習ボード@<fn>{aps_board}がありました。

//image[aps_board_surface][APS学習ボード（表）]{ 
//}

//image[aps_board_reverse][APS学習ボード（裏）]{ 
//}

APS学習ボードは拡張ボードにスタックして使うボードで次の特徴があります。

 * プログラムで使えるタクトスイッチが2つ

 * プログラムで使えるLEDが2つ

 * アナログコンデンサマイク左:2つ、右2つの合計4つ接続可能

 * LCD（ILI9341 2.2inch）接続用端子あり

 * カメラボードのカメラマウント用のネジ穴あり

 * メインボードにサードパーティー拡張ボードが接続できるよう基板中心がくり抜かれている

次が各ボードを接続したときの写真です。
メインボードにカメラボードを取り付け、拡張ボードの上にメインボードを装着した状態で

//image[main+ex+camera_board][拡張ボード+メインボード+カメラボード]{ 
//}

拡張ボードとAPS学習ボードを接続します。

//image[main+ex+camera+aps_board][拡張ボード+メインボード+カメラボード+APS学習ボード]{ 
//}

最後にAPS学習ボードとLCDを接続すればデジタルカメラのハードウェアが完成です。

//image[main+ex+camera+aps+lcd_board][拡張ボード+メインボード+カメラボード+APS学習ボード+LCD]{ 
//}


APS学習ボードを使えば前述の要求仕様を満たせると思ったので、デジタルカメラを作ってみることにしました。

 * サンプルプログラムと同じLCD（ILI9341 2.2inch LCD）を接続できること

 * カメラボードのカメラをマウントできること

 * シャッター代わりになるタクトスイッチがあること

 * プログラムの終了に使えるタクトスイッチがあること


特徴に挙げた、

 * メインボードにサードパーティー拡張ボードが接続できるよう基板中心がくり抜かれている

ですが@<img>{main+ex+camera+aps_board_ex}の実線になります。

//image[main+ex+camera+aps_board_ex][APS学習ボードの拡張性を考慮した設計]{ 
//}

APS学習ボードのくり抜かれている部分からメインボードが見えています。
メインボードのピン@<img>{main+ex+camera+aps_board_ex}の点線に
サードパーティー製の拡張ボードを装着できるようになっています。

@<img>{main+ex+camera+aps+wifi-addon_board}はメインボードに
SPRESENSE Wi-Fi Add-onボード iS110B@<fn>{wifi_add_on_board}を接続した場合です。

//image[main+ex+camera+aps+wifi-addon_board][メインボードにWi-Fi Add-onボードを接続した場合]{ 
//}

APS学習ボードの基板中心が切り抜かれていることで拡張性が確保されています。

@<img>{main+ex+camera+aps+wifi-addon+lcd_board_side}はWi-Fi Add-onボードと
LCDと接触していないか横から撮影したものです。

//image[main+ex+camera+aps+wifi-addon+lcd_board_side][Wi-Fi Add-onボードとLCDの干渉を確認]{ 
//}

例に挙げたWi-Fi Add-onボードとLCDは部品同士の干渉もないので、デジタルカメラにネットワーク機能を追加するなど
付加価値をつけたシステムをつくることも可能そうです。

※カメラと当該Wi-Fi Add-onボードを使用したサンプルプログラムが
@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_multiwebcam_%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB%E3%82%A2%E3%83%97%E3%83%AA%E3%82%B1%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3,Spresense SDKチュートリアル 5.2. multiwebcam サンプルアプリケーション}
に書かれていました。
