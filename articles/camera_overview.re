
= デジタルカメラ機能説明

Spresenseはたくさんのサンプルプログラムがあります。

 * Spresense SDKのサンプルプログラム
    @<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html}

 * Arduino IDEのサンプルプログラム
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

