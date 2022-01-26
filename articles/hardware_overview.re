
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
以降に各デバイスとのピン配置を書きます。

=== カメラ
カメラボードのフラットケーブルはメインボードのカメラ専用コネクタ（CN5）に接続します。

=== LCD
カメラのプレビュー画像をLCD（ILI9341 2.2inch LCD）に表示します。
LCDのピンは次の信号と接続されています。

 1. VCC - 3.3V
 2. GND - GND
 3. CS - 拡張ボード JP2-8 SPI4_CS_X
 4. RESET - Reset
 5. DC/RS - 拡張ボード JP2-9 PWM2
 6. MOSI - 拡張ボード JP2-7 SPI4_MOSI
 7. SCK - 拡張ボード JP2-5 SPI4_SCK
 8. LED - 3.3V
 9. MISO - 未接続

=== APS学習ボード タクトスイッチ（シルク: SW1）
APS学習ボードに実装されているタクトスイッチ（SW1）は押下で
デジタルカメラアプリケーション終了に使用することにしました。
仕様は次のとおりです。

 * 拡張ボードJP13-1 SPI3_CS1_Xに接続

 * プルアップ抵抗接続あり

 * タクトスイッチ押下なしで1:Highレベルを読み出し

 * タクトスイッチ押下ありで0:Lowレベルを読み出し


=== APS学習ボード タクトスイッチ（シルク: SW2）
APS学習ボードに実装されているタクトスイッチ（SW2）はシャッター機能に割り当て
押下でLCDにプレビュー表示している画像のファイル保存に使用することにしました。
仕様は次のとおりです。

 * 拡張ボードJP13-4 SPI2_MOSIに接続

 * プルアップ抵抗接続あり

 * タクトスイッチ押下なしで1:Highレベルを読み出し

 * タクトスイッチ押下ありで0:Lowレベルを読み出し


=== APS学習ボード LED（シルク: USER_LED1）
APS学習ボードに実装されているLED（USER_LED1）はタクトスイッチ（SW1）に連動して
点灯・消灯するようにしました。
SW1押下なしで点灯、SW1押下ありで消灯するようにしました。

=== APS学習ボード LED（シルク: USER_LED2）
APS学習ボードに実装されているLED（USER_LED2）はタクトスイッチ（SW2）に連動して
点灯・消灯するようにしました。
SW2押下なしで点灯、SW2押下ありで消灯するようにしました。

== ピン配置の注意点
@<strong>{【Tips】}@<br>{}
プログラムでGPIOを指定する際の注意点はSpresense SDKとArduino IDEで
GPIOピンを指定するピン番号が異なることです。
この情報は次の資料にまとめられています。@<br>{}

@<href>{https://developer.sony.com/develop/spresense/docs/hw_design_ja.html,ハードウェア設計資料}
@<br>{}
@<href>{https://github.com/sonydevworld/spresense-hw-design-files/raw/master/Pin/Spresense_pin_function_ja.xlsx,Spresense コネクタ ピンリスト コネクタ ピンリスト (xlsx)}

資料の【SDK上の名称】の列はSpresense SDKでGPIOを指定する際の名称になります。@<br>{}
資料の【ArduinoIDE上の名称】の列はArduino IDEでGPIOを指定する際の名称になります。

APS学習ボードのタクトスイッチSW1（拡張ボードJP13-1に接続）を例に説明します。
資料を参照すると拡張ボードJP13-1は次になります。

 * 【回路図上の名前】はSPI3_CS1_X

 * 【ArduinoIDE上の名称】はD07

 * 【SDK上の名称】はPIN_SPI3_CS1_X

 * 【SDK上のピン番号】は39


実際に開発する際はSpresense SDKとArduino IDEどちらかで開発すると思うので問題ないと思います。
今回Spresense SDK・Arduino IDEの2種類の開発環境でプログラムする際に少し混乱したので説明させていただきました。

=== Spresense SDKでGPIOを指定する場合
前述の資料でSpresense SDKでAPS学習ボードのタクトスイッチSW1（拡張ボードJP13-1に接続）を指定する名称がわかりました。
【SDK上の名称】・【SDK上のピン番号】は次のヘッダファイルに定義されています。

 * @<href>{https://github.com/sonydevworld/spresense-nuttx/blob/new-master/arch/arm/include/cxd56xx/pin.h,nuttx/arch/arm/include/cxd56xx/pin.h}@<br>{}
    ローカルPCに環境構築したソースコードの場合（Mac）は次のファイルパス@<br>{}
    /Users/ユーザー名/spresense/nuttx/arch/arm/include/cxd56xx/pin.h

このヘッダファイルに【SDK上の名称】・【SDK上のピン番号】がマクロで定義されています。

//list[sdk_pin_h_39][Spresense SDKピンヘッダーファイルの39ピンの定義]{
#define PIN_SPI3_CS1_X          (39)
//}

実際にタクトスイッチをリードするコードは次になります。

//list[spresense_sdk_sw1_read_list_1][Spresense SDKでSW1をリードするコード1]{
int sw1_status = board_gpio_read(PIN_SPI3_CS1_X);
//}

または

//list[spresense_sdk_sw1_read_list_2][Spresense SDKでSW1をリードするコード2]{
#define SWITCH_1  (39)

int sw1_status = board_gpio_read(SWITCH_1);
//}

=== Arduino IDEでGPIOを指定する場合
前述の資料でArduino IDEでAPS学習ボードのタクトスイッチSW1（拡張ボードJP13-1に接続）を指定する名称がわかりました。
【ArduinoIDE上の名称】は【D07】となっていました。
Arduino IDEでGPIOを指定する際は【7】を指定すればSW1を読み出せます。
実際にタクトスイッチをリードするコードは次になります。

//list[arduino_ide_sw1_read_list_1][Arduino IDEでSW1をリードするコード]{
const byte switch_1_pin = 7;

byte sw1_status = digitalRead(switch_1_pin);
//}

