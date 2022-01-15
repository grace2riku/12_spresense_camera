
= ハードウェアの説明

== 必要な部品
デジタルカメラに必要な部品について書きます。

//table[camera_parts][部品一覧]{
.   部品名称                            詳細
----------------------------------------------------
1   メインボード                         .
2   拡張ボード                          .
3   カメラボード                        .
4   ILI9341 2.2inch LCD                 .
4   APS学習ボード                         .
5   マイクロSDカード                        .
6   USBケーブル                         USBタイプA-マイクロBタイプ
//}

=== メインボード
=== 拡張ボード
=== カメラボード
メインボード、拡張ボード、カメラボードは次に説明が書かれています。

@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_camera_%E3%83%81%E3%83%A5%E3%83%BC%E3%83%88%E3%83%AA%E3%82%A2%E3%83%AB}

メインボードは2.1.1. Spresense メインボードです。

拡張ボードは2.1.2. Spresense 拡張ボードです。

カメラボードは2.1.4. Spresense カメラボードです。

=== ILI9341 2.2inch LCD
電子工作でよく使われている印象のLCDです。
私は@<href>{https://www.aliexpress.com/snapshot/0.html?spm=a2g0o.9042647.6.2.7ba84c4doorRDS&orderId=8015268750165621&productId=32914366837,AliExpress}で購入しました。

=== APS学習ボード
こちらのリンクが取り扱い説明書です。

@<href>{https://www.aps-web.jp/academy/amp/8467/}@<br>{}

前述の@<table>{camera_parts}はAPS学習ボードに実装する部品を書いていません。
チップワンストップでは部品実装済み、LCDセット品もあるとのことです。

@<href>{https://www.chip1stop.com/view/dispDetail/DispDetail?partId=APS1-0000002}

=== マイクロSDカード
FAT32でフォーマットされたマイクロSDカードがあると便利です（必須ではないです）。

デジタルカメラで撮影した画像ファイルはマイクロSDカードがあればSDカードに保存します。
マイクロSDカードが接続されていない場合はメインボードのFlashROMに保存されます。

私はSDHC、8GBバイト、スピードクラス4（4MB/秒）のマイクロSDカードを使い、画像ファイルの保存を確認できました。

=== USBケーブル
一般的なタイプA-マイクロBタイプのUSBケーブルが必要です。
メインボードとPCを接続し、アプリケーションの書込み・アプリケーションとシリアル通信をします。

== ピン配置

