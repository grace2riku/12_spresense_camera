
= 発展

今回のSoresense SDK・Arduinoのチュートリアル【Camera】のサンプルプログラムを
少し変更してデジタルカメラアプリケーションを作成しました。
Spresenseにはカメラの他にたくさんのサンプルプログラム、魅力的な機能があります。
本章ではその機能・魅力をピックアップして紹介します。
私がSpresense SDKの方に注力していることもあり【Spresense SDK】の紹介になります。
Spresense SDKのチュートリアルは次のリンクに書かれています。@<br>{}

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html,【リンク】Spresense SDK チュートリアル}

以降の章のタイトルはリンク先の章番号です。

== 4. Audio チュートリアル
音声の再生・録音が可能です。今回のデジタルカメラアプリケーションに機能追加し、シャッターのスイッチ押下で
シャッター音を再生する機能を追加すればよりデジタルカメラらしくなります。

== 10. Graphics チュートリアル
NuttXのグラフィックスシステムで【NX】に関するサンプルアプリケーションがあります。
実現可能か調査が必要かと思いますが、デジタルカメラアプリケーションと組み合わせて残り撮影可能枚数の表示をLCDプレビュー画像に
重ね合わせ表示するといった機能もよいかと思います。

== 13. FW Update チュートリアル
ファームウェアアップデートをおこなうサンプルプログラムです。
サンプルプログラムはUSBシリアル経由でファームウェアアップデートしているようです。
チュートリアルにも記載がありますがWiFiやLTEなどネットワーク経由、またはSDカードから
ファームウェアアップデートするなど応用が可能との記載があります。

== 14. その他のチュートリアル 
14.3. pdcurses サンプルアプリケーションを対象に紹介します。
NuttXの標準サンプルプログラム【pdcurses】です。
LCDに文字列表示、グラフィック表示したりと面白いサンプルアプリケーションです。

== 18. USB MSC 機能を使う
拡張ボードのマイクロSDカードをホストPCから直接参照することが可能になります。
SDカードの抜き差しが不要になり、保存データの確認が楽になります。
是非、導入したい機能だと思います。

== 21. アプリケーションの自動起動方法
Spresense SDK版はAruduino版と違い、シェルのコマンド実行をトリガにアプリケーションが動作します。
Arduino版は電源ONと同時に動作開始します。
Spresense SDK版のアプリケーションもこの機能を導入することで電源ONで動き出すアプリケーションが実現可能です。

== 22. ローダブルELFチュートリアル
チュートリアルの引用ですが、
【ローダブルELFはOSとアプリケーションを別々のバイナリで作成し、動作時にアプリケーションをロードして実行できる機能】です。
この機能があるとアプリケーションをSDカードに入れてSpresenseのFlashROMを削減したり、メモリ量を抑えたりできます。
PCで動くゲームのエミュレータのROMのようにアプリケーションを扱えるようになりますね。

== 24. SMP (Symmetric Multiprocessing)
マルチコア（SMP型）について書かれています。

※マルチコア構成についてはAPSのこちらの記事が詳しいです。@<br>{}

@<href>{https://www.aps-web.jp/academy/amp/22917/,【リンク】SPRESENSEを支えるリアルタイムOS「NuttX」により SMP × ASMP のシステムを構築！CPUコアを使いこなす3つのポイント}

記事によるとSpresenseではSMP・ASMPの両方のシステム構成が構築できるようです。


次のコマンドのように【feature/smp】を指定してコンフィギュレーション・makeします。
//cmd{
tools/config.py examples/hello feature/smp
make
//}

そうするとチュートリアルのように【ps】コマンドにコアの実行状態を表示できるようになります。
tasksetコマンドでコア番号を指定してプログラムを実行することができます。

次はCPU番号=0（コア0）で動かす場合のコマンドです。
//cmd{
nsh> taskset 1 hello
//}

== 25. Task Trace ツール
Trace Compassというツールを使用しタスクトレース情報をグラフィカルに表示することができます。
チュートリアルに書いてあるようにタスクの実行状態がグラフィカルに確認できます。
デバッグ時に重宝しそうですね。

== 26. デバッグログ機能について
デバッグ時に重宝するログ機能です。

【26.1. syslog 機能】はUART等のシリアルコンソールへログを出力する機能です。

【26.2. RAM log 機能】はRAMバッファへ出力するログ機能です。dmesgコマンドによってまとめてコンソールに出力できます。
syslogではオーバーヘッドが心配というときはこちらのRAM log 機能でログを溜めて後でdmesgで取り出すことができます。


== 動作確認したチュートリアル
紹介した機能のうちいくつかを動作確認してみました。

=== Graphics
NuttXのグラフィックスシステムである、NXに関するサンプルアプリケーションになります。
LCD画面がさかさまになっていますがコンフィギュレーションで設定可能なようです。

==== fb
サンプル名【fb】を確認しました。
fbはフレームバッファをダイレクトに操作するサンプルです。

//image[fb_1][fb実行結果]{ 
//}

==== nx
サンプル名【nx】を確認しました。
nxはNXのWindowシステムの描画に関するサンプルです。

//image[nx][nx実行結果]{ 
//}

==== nxdemo
サンプル名【nxdemo】を確認しました。
nxdemoはNXの描画に関するサンプルです。

//image[nxdemo_1][nxdemo実行結果]{ 
//}

==== nxhello
サンプル名【nxhello】を確認しました。
nxhelloはNXのテキスト描画に関するサンプルです。

//image[nxhello][nxhello実行結果]{ 
//}

==== nxlines
サンプル名【nxlines】を確認しました。
nxlinesはNXの直線描画に関するサンプルです。

//image[nxlines_2][nxlines実行結果]{ 
//}

==== nxtext
サンプル名【nxtext】を確認しました。
nxtextはNXのテキスト描画とポップアップウィンドウの描画に関するサンプルです。

//image[nxtext][nxtext実行結果]{ 
//}


=== pdcurses サンプルアプリケーション
NuttXの標準サンプルである、pdcursesに関するサンプルアプリケーションです。
charset以外は写真だとわかりずらいですがアニメーションなのでチュートリアルに記載の環境がある方は
確認してみると面白いと思います。

==== charset
charsetの動作確認結果は@<img>{charset}です。
//image[charset][charset動作確認結果]{ 
//}

==== newdemo
newdemoの動作確認結果は@<img>{newdemo}です。
//image[newdemo][newdemo動作確認結果]{ 
//}

==== worm
wormの動作確認結果は@<img>{worm}です。
//image[worm][worm動作確認結果]{ 
//}

==== firework
fireworkの動作確認結果は@<img>{firework}です。
//image[firework][firework動作確認結果]{ 
//}

==== rain
rainの動作確認結果は@<img>{rain}です。
//image[rain][rain動作確認結果]{ 
//}

==== tui
tuiの動作確認結果は@<img>{tui}です。
//image[tui][tui動作確認結果]{ 
//}

==== xmas
xmasの動作確認結果は@<img>{xmas}です。
//image[xmas][xmas動作確認結果]{ 
//}


=== USB MSC
@<kw>{USB MSC, Mass Storage Class}を有効にするとホストPCから拡張ボード上のマイクロSDカードへ直接アクセスすることができます。

動作確認方法を次に書きます。
拡張ボードにマイクロSDカードが挿入されている状態で、拡張ボードのUSB端子とホストPCをUSBケーブルで接続します。
@<img>{usbmsc_usb_setting}です。
//image[usbmsc_usb_setting][USB MSC確認時は拡張ボード側にUSBケーブルを接続]{ 
//}

@<img>{usbmsc_enviroment}のようにメインボード、拡張ボードにUSBケーブルを接続します。
//image[usbmsc_enviroment][USB MSC確認環境]{ 
//}

次のコマンドを実行します。
//cmd{
nsh> msconn
//}

@<img>{usbmsc}のようにホストPCに拡張ボードのマイクロSDカードがリムーバブルディスクとして認識されます。
//image[usbmsc][ホストPCでリムーバブルディスクを認識]{ 
//}

@<img>{usbmsc_share}はデジタルカメラアプリケーションで撮影した画像ファイルをホストPCで確認しているところです。
//image[usbmsc_share][デジタルカメラ撮影画像をPCで確認]{ 
//}

USB MSC機能があるおかげで画像ファイルの確認でマイクロSDカードを取り外しする必要がなくなります。
動作確認に非常に役立つ機能です。


=== Task Trace ツール
チュートリアルのとおりにコマンドを実行します。
デジタルカメラアプリケーション【myfirstcameraapp】のタスクをトレースしてみました。
タスクトレース開始後に次の操作をおこない、トレースデータを取得しました。

 * 1回だけ画像保存

 * アプリケーション終了

トレースデータはtrace.logというファイル名で保存しました。
次が実行したコマンドです。

//cmd{
nsh> trace start
nsh> myfirstcameraapp
nximage_listener: Connected
nximage_initialize: Screen resolution (320,240)
Take 10 pictures as JPEG file in /mnt/sd0 after 5 seconds.
 After finishing taking pictures, this app will be finished after 10 seconds.
sw2_status = 0
Start captureing...
sw2_status = 1
FILENAME:/mnt/sd0/VIDEO001.JPG
Finished captureing...
sw1_status = 0
sw1_status = 1
nsh> trace stop
nsh> trace dump /mnt/sd0/trace.log
nsh> ls /mnt/sd0/
/mnt/sd0:
 System Volume Information/
 VIDEO001.JPG
 VIDEO002.JPG
 VIDEO003.JPG
 PICT000.JPG
 PICT001.JPG
 PICT002.JPG
 .fseventsd/
 .Spotlight-V100/
 ._PICT000.JPG
 ._VIDEO001.JPG
 trace.log
 test.txt
 ._PICT001.JPG
 ._PICT002.JPG
//}

Trace Compassはチュートリアル、@<href>{https://nuttx.apache.org/docs/latest/guides/tasktraceuser.html,【リンク】NuttX Task Trace User Guideマニュアル}の
とおりにインストールしておきます。
Trace Compassは【バージョン7.2 Mac OS X 64bit】を使用しました。

@<img>{trace_2}はTrace Compassを起動し、保存したログを読み込んだ画面です。

//image[trace_2][Trace Compassを用いたタスクトレース情報のグラフィカル表示]{ 
//}

タスクの実行状況をグラフィカルに確認できればデバッグのときに役立ちそうです。
